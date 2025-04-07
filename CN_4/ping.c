#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <poll.h>
#include <float.h>
#include <bits/getopt_core.h>
#include <netinet/ip6.h>
#include <math.h>

#ifndef timersub
#define timersub(a, b, result)                     \
    do {                                           \
        (result)->tv_sec = (a)->tv_sec - (b)->tv_sec;  \
        (result)->tv_usec = (a)->tv_usec - (b)->tv_usec; \
        if ((result)->tv_usec < 0) {               \
            --(result)->tv_sec;                    \
            (result)->tv_usec += 1000000;          \
        }                                          \
    } while (0)
#endif
#ifndef timersub
#define timersub(a, b, result)                     \
    do {                                           \
        (result)->tv_sec = (a)->tv_sec - (b)->tv_sec;  \
        (result)->tv_usec = (a)->tv_usec - (b)->tv_usec; \
        if ((result)->tv_usec < 0) {               \
            --(result)->tv_sec;                    \
            (result)->tv_usec += 1000000;          \
        }                                          \
    } while (0)
#endif


// מבנה נתונים לשמירת הדגלים
typedef struct {
    char *address; // כתובת ה-IP
    int protocol;  // סוג הפרוטוקול (4 או 6)
    int count;     // מספר חבילות לשליחה
    int flood;     // האם לבצע מצב שיטפון
} PingOptions;

// מבנה נתונים לניהול סטטיסטיקות
typedef struct {
    int packets_sent;
    int packets_received;
    double min_rtt;
    double max_rtt;
    double total_rtt;
    double rtt_squared_sum;
    struct timeval start_time;
    struct timeval end_time;
} PingStats;

unsigned short calculate_checksum(void *data, int len) {
    unsigned short *ptr = data;
    unsigned int sum = 0;
    while (len > 1) {
        sum += *ptr++;
        len -= 2;
    }
    if (len > 0) {
        sum += *(unsigned char *)ptr;
    }
    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }
    return ~sum;
}

// פונקציה לקריאת הדגלים
int parse_flags(int argc, char *argv[], PingOptions *options) {
    int opt;

    // אתחול הערכים כברירת מחדל
    options->address = NULL;
    options->protocol = 0;
    options->count = 0;
    options->flood = 0;

    // שימוש ב-getopt לעיבוד הדגלים
    while ((opt = getopt(argc, argv, "a:t:c:f")) != -1) {
        switch (opt) {
            case 'a':
                options->address = optarg;
                break;
            case 't':
                options->protocol = atoi(optarg);
                if (options->protocol != 4 && options->protocol != 6) {
                    fprintf(stderr, "Error: Protocol must be 4 (IPv4) or 6 (IPv6).\n");
                    return -1;
                }
                break;
            case 'c':
                options->count = atoi(optarg);
                if (options->count <= 0) {
                    fprintf(stderr, "Error: Count must be a positive integer.\n");
                    return -1;
                }
                break;
            case 'f':
                options->flood = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s -a <address> -t <4|6> [-c <count>] [-f]\n", argv[0]);
                return -1;
        }
    }

    // בדיקה שהדגלים החיוניים (a ו-t) ניתנו
    if (!options->address || !options->protocol) {
        fprintf(stderr, "Error: Both -a <address> and -t <4|6> are required.\n");
        return -1;
    }

    return 0;
}

void update_stats(PingStats *stats, double rtt) {
    stats->packets_received++;
    stats->total_rtt += rtt;
    stats->rtt_squared_sum += rtt*rtt;
    if (rtt < stats->min_rtt) {
        stats->min_rtt = rtt;
    }
    if (rtt > stats->max_rtt) {
        stats->max_rtt = rtt;
    }
}

void print_stats(const PingStats *stats, const char *address) {
    struct timeval total_time;
    timersub(&stats->end_time, &stats->start_time, &total_time);

    printf("\n--- %s ping statistics ---\n", address);
    printf("%d packets transmitted, %d received, time %ld.%06lds\n",
           stats->packets_sent, stats->packets_received,
           (long)total_time.tv_sec, (long)total_time.tv_usec);

    if (stats->packets_received > 0) {
        double avg_rtt = stats->total_rtt / stats->packets_received;
        double variance = (stats->rtt_squared_sum / stats->packets_received) - (avg_rtt * avg_rtt);
        double mdev = (variance > 0) ? sqrt(variance) : 0;

        printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
               stats->min_rtt,
               avg_rtt,
               stats->max_rtt,
               mdev);
    }
}

// פונקציה לשליחת ICMPv6
void send_icmpv6(PingOptions *options) {
    int sock = socket(AF_INET6, SOCK_RAW, IPPROTO_ICMPV6);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in6 dest_addr = {0};
    dest_addr.sin6_family = AF_INET6;
    if (inet_pton(AF_INET6, options->address, &dest_addr.sin6_addr) != 1) {
        fprintf(stderr, "Invalid IPv6 address: %s\n", options->address);
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    struct icmp6_hdr icmp_header = {0};
    icmp_header.icmp6_type = ICMP6_ECHO_REQUEST;
    icmp_header.icmp6_code = 0;
    icmp_header.icmp6_id = htons(getpid());

    PingStats stats = {0, 0, DBL_MAX, 0, 0,0,{0,0},{0,0}};
    gettimeofday(&stats.start_time, NULL);

    printf("Pinging %s with 64 bytes of data:\n", options->address);
    for (int i = 0; i < options->count || options->count == 0; i++) {
        stats.packets_sent++;
        icmp_header.icmp6_seq = htons(i);
        icmp_header.icmp6_cksum = 0;
        memcpy(buffer, &icmp_header, sizeof(icmp_header));

        struct timeval start, end;
        gettimeofday(&start, NULL);

        if (sendto(sock, buffer, sizeof(icmp_header), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
            perror("sendto");
            continue;
        }

        struct pollfd fds = {sock, POLLIN, 0};
        int ret = poll(&fds, 1, 1000);

        if (ret > 0) {
            struct sockaddr_in6 reply_addr;
            socklen_t addr_len = sizeof(reply_addr);
            if (recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&reply_addr, &addr_len) > 0) {
                struct ip6_hdr *ip_header = (struct ip6_hdr *)buffer;
                int hop_limit = ip_header->ip6_hlim; // Updated field
                gettimeofday(&end, NULL);
                double rtt = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
                printf("64 bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", options->address, i + 1, hop_limit, rtt);
                update_stats(&stats, rtt);
            }
        } else {
            printf("Request timeout for icmp_seq %d\n", i + 1);
        }

        if (!options->flood) {
            sleep(1);
        }
    }

    gettimeofday(&stats.end_time, NULL);
    print_stats(&stats, options->address);
    close(sock);
}

void send_icmpv4(PingOptions *options) {
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in dest_addr = {0};
    dest_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, options->address, &dest_addr.sin_addr) != 1) {
        fprintf(stderr, "Invalid IPv4 address: %s\n", options->address);
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    struct icmphdr icmp_header = {0};
    icmp_header.type = ICMP_ECHO;
    icmp_header.code = 0;
    icmp_header.un.echo.id = htons(getpid());

    PingStats stats = {0, 0, DBL_MAX, 0, 0,0,{0,0},{0,0}};
    gettimeofday(&stats.start_time, NULL);

    printf("Pinging %s with 64 bytes of data:\n", options->address);
    for (int i = 0; i < options->count || options->count == 0; i++) {
        stats.packets_sent++;
        icmp_header.un.echo.sequence = htons(i);
        icmp_header.checksum = 0;
        memcpy(buffer, &icmp_header, sizeof(icmp_header));
        icmp_header.checksum = calculate_checksum(buffer, sizeof(icmp_header));
        memcpy(buffer, &icmp_header, sizeof(icmp_header));

        struct timeval start, end;
        gettimeofday(&start, NULL);

        if (sendto(sock, buffer, sizeof(icmp_header), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
            perror("sendto");
            continue;
        }

        struct pollfd fds = {sock, POLLIN, 0};
        int ret = poll(&fds, 1, 1000);

        if (ret > 0) {
            struct sockaddr_in reply_addr;
            socklen_t addr_len = sizeof(reply_addr);
            if (recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&reply_addr, &addr_len) > 0) {
                struct iphdr *ip_header = (struct iphdr *)buffer;
                int ttl = ip_header->ttl;
                gettimeofday(&end, NULL);
                double rtt = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
                printf("64 bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", options->address, i + 1, ttl, rtt);
                update_stats(&stats, rtt);
            }
        } else {
            printf("Request timeout for icmp_seq %d\n", i + 1);
        }

        if (!options->flood) {
            sleep(1);
        }
    }

    gettimeofday(&stats.end_time, NULL);
    print_stats(&stats, options->address);
    close(sock);
}

int main(int argc, char *argv[]) {
    PingOptions options;

    // קריאת הדגלים
    if (parse_flags(argc, argv, &options) != 0) {
        return 1;
    }
    // שליחת חבילות בהתאם לפרוטוקול
    if (options.protocol == 6) {
        send_icmpv6(&options);
    }
    if (options.protocol == 4) {
        send_icmpv4(&options);
    }
    return 0;
}