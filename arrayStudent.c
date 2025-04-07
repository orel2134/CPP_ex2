#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_FAIL 42

void get_names(char *names[], int num);
void print_names(const char *names[], int num);
void free_names(char *names[], int num);

void get_names(char *names[], int num) {
    int i = 0;
    char str[128];

    while (i < num) {
        puts("Enter a name (press CTRL/Z ENTER to stop) => ");
        if (gets(str) == NULL) break;

        names[i] = (char*) malloc(strlen(str) + 1);
        if (names[i] == NULL) {
            puts("Not enough memory. Sorry.\n");
            free_names(names, i); /* some memory has been allocated! */
            exit(EXIT_FAIL);
        }

        strcpy(names[i], str); /* copy the name into the memory */
        i++;
    }

    // For calling `print_names` inside `get_names` to avoid double calling
    print_names((const char **)names, i);
}

void print_names(const char *names[], int num) {
    for (int i = num - 1; i >= 0; i--) {
        for (int j = strlen(names[i]) - 1; j >= 0; j--) {
            putchar(names[i][j]);
        }
        putchar('\n');
    }
}

void free_names(char *names[], int num) {
    for (int i = 0; i < num; i++) {
        free(names[i]);
    }
}

int main() {
    int num;
    printf("Enter the number of students: ");
    scanf("%d", &num);
    getchar(); // clear the newline character from input buffer

    char *names[num];
    get_names(names, num);

    printf("Names in reverse order and each name reversed:\n");
    print_names((const char **)names, num);

    free_names(names, num);

    return 0;
}
 