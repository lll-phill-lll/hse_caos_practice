#include <stdio.h>

// struct alignment = max field alignment
// on 32:
// char      - 1
// short     - 2
// int       - 4
// long      - 4
// long long - 8
struct s1 {
    char ch;
};

struct s2 {
    char ch;
    int i;
};

struct s3 {
    char ch1;
    int i;
    char ch2;
};

struct s4 {
    char ch1;
    char ch2;
    short s;
    int i;
};

struct s5 {
    int i;
    long long l;
};

struct s6 {
    int i;
    short s[2];
};

struct s7 {
    int i;
    short s[3];
};

int main() {
    // printf("%ld\n", sizeof(struct s1));
    // printf("%ld\n", sizeof(struct s2));
    // printf("%ld\n", sizeof(struct s3));
    printf("%ld\n", sizeof(struct s4));
    // printf("%ld\n", sizeof(struct s5));
    // printf("%ld\n", sizeof(struct s6));
    // printf("%ld\n", sizeof(struct s7));
}
