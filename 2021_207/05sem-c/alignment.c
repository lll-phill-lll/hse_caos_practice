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
}; // Размер равен 1

struct s2 {
    char ch;
    // char
    // char
    // char
    int i;
}; // Размер равен 8

struct s3 {
    char ch1;
    // char
    // char
    // char
    int i;
    char ch2;
    // char
    // char
    // char
}; // Размер равен 12

struct s4 {
    char ch1;
    char ch2;
    int i;
}; // Размер равен 8

struct s4_2 {
    char ch1;
    char ch2;
    short s;
    int i;
}; // Размер равен 8

struct s5 {
    int i;
    long long l;
}; // Размер равен 12

struct s6 {
    int i;
    short s[2];
}; // Размер равен 8

struct s7 {
    int i;
    short s[3];
    // short
}; // Размер равен 12

int main() {
    printf("1 %ld\n", sizeof(struct s1));
    printf("2 %ld\n", sizeof(struct s2));
    printf("3 %ld\n", sizeof(struct s3));
    printf("4 %ld\n", sizeof(struct s4));
    printf("4.2 %ld\n", sizeof(struct s4_2));
    printf("5 %ld\n", sizeof(struct s5));
    printf("6 %ld\n", sizeof(struct s6));
    printf("7 %ld\n", sizeof(struct s7));
}
