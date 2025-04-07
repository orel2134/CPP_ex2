#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h> 
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define PACKET_SIZE 64 // size of ICMP packet
#define HOPS 30 // maximum number of hops to check in traceroute

// structure for ICMP packet
struct icmp_packet
{
    struct icmphdr icmp; // ICMP header
    char msg[PACKET_SIZE - sizeof(struct icmphdr)]; // message content
};


struct ipv4_header
{
    unsigned int ihl : 4; // internet Header Length (IHL)
    unsigned int version : 4; // IP version (IPv4)
    unsigned char tos; // type of Service
    unsigned short int total_length; // total packet length
    unsigned short int identification; // packet identification
    unsigned short int flags : 3; // fragmentation flags
    unsigned short int fragment_offset : 13; // fragment offset
    unsigned char ttl; // time To Live (TTL)
    unsigned char protocol; // protocol (ICMP, TCP, UDP.....)
    unsigned short int checksum; // header checksum
    unsigned int source_address; // source IP address
    unsigned int destination_address; // destination IP address
};

// function to calculate checksum for ICMP packet
unsigned short calculate_checksum(void *data, int len)
{
    unsigned short *ptr = data;
    unsigned int sum = 0;
    while (len > 1)
    {
        sum += *ptr++;
        len -= 2;
    }
    if (len > 0)
    {
        sum += *(unsigned char *)ptr;
    }
    while (sum >> 16)
    {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }
    return ~sum;
}

// function to perform traceroute to the given destination IP
void traceroute(int sockdf, struct sockaddr_in dest_addr)
{
    struct icmp_packet packet = {0}; // ICMP packet initialization
    struct sockaddr_in addr; // address struct for responses
    socklen_t addr_len = sizeof(addr);
    struct timeval timeout = {1, 0}; 
    struct timeval start, end; // time tracking variables
    struct ipv4_header *ip_header;

    // set socket receive timeout
    setsockopt(sockdf, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    // loop for each TTL (hop) from 1 to HOPS (max 30 hops)
    for (int i = 1; i <= HOPS; i++)
    {
        setsockopt(sockdf, IPPROTO_IP, IP_TTL, &i, sizeof(i)); // set TTL
        double rtt[3] = {-1, -1, -1}; // store Round Trip Time (RTT) for three attempts
        int received = 0; // counter for successful replies

        for (int j = 1; j <= 3; j++) // send 3 ICMP Echo Requests per hop
        {
            // build ICMP packet with Echo Request type
            packet.icmp.type = ICMP_ECHO;
            packet.icmp.code = 0;
            packet.icmp.un.echo.id = getpid() & 0xFFFF;
            packet.icmp.un.echo.sequence = j;
            packet.icmp.checksum = 0;
            packet.icmp.checksum = calculate_checksum(&packet, sizeof(packet));

            // record the start time before sending
            gettimeofday(&start, NULL);
            if (sendto(sockdf, &packet, sizeof(packet), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0)
            {
                perror("sendto() error");
                exit(1);
            }

            // receive response and record the time
            int recv_len = recvfrom(sockdf, &packet, sizeof(packet), 0, (struct sockaddr *)&addr, &addr_len);
            gettimeofday(&end, NULL);

            // check if no response was received
            if (recv_len < 0)
            {
                continue;
            }

            // extract headers from received packet
            ip_header = (struct ipv4_header *)&packet;
            struct icmphdr *icmp_header = (struct icmphdr *)((char *)ip_header + ip_header->ihl * 4);

            // if the destination is not reached, receiver returns ICMP_TIME_EXCEEDED
            if (icmp_header->type == ICMP_TIME_EXCEEDED)
            {
                received++;
                rtt[j - 1] = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
            }
            // if destination is reached, receiver returns ICMP_ECHOREPLY
            else if (icmp_header->type == ICMP_ECHOREPLY)
            {
                received++;
                rtt[j - 1] = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
            }
        }

        
        if (received == 0)
        {
            printf("%d\t*\t*\t*\n", i);
        }
        else
        {
            printf("%d. %s\t", i, inet_ntoa((struct in_addr){ip_header->source_address}));
            for (int j = 0; j < 3; j++)
            {
                if (rtt[j] == -1)
                {
                    printf("*\t");
                }
                else
                {
                    printf("%.2f ms\t", rtt[j]);
                }
            }
            printf("\n");
        }

        // if the destination IP is reached, exit traceroute
        if (received > 0 && ip_header->source_address == dest_addr.sin_addr.s_addr)
        {
            return;
        }
    }

    printf("Destination host unreachable\n");
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s -a <ip address>\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "-a") != 0)
    {
        printf("Usage: %s -a <ip address>\n", argv[0]);
        exit(1);
    }

    int sockdf;

    if ((sockdf = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
    {
        perror("socket() error");
        exit(1);
    }

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = 0;

    // check if the provided IP address is valid
    if (inet_pton(AF_INET, argv[2], &dest_addr.sin_addr) != 1)
    {
        printf("Invalid IP address\n");
        exit(1);
    } 

    // start traceroute to the given destination
    traceroute(sockdf, dest_addr);

    return 0;
}
