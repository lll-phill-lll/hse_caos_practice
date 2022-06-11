#include <stdio.h>
#include <unistd.h>

void print_hello() {
    printf("%s", "Hello world");
    fflush(stdout);
    sleep(1);
    printf("\r"); // \r двигает каретку в начало
    fflush(stdout);
    sleep(1);
    printf("%15s lala\n %d fgdjhg \n \r 8989", "smth", 5);
}

void print_numbers() {
    for (int i = 0; i != 1 << 30; ++i) {
        printf("\r%d", i);
    }
}

int main() {
    print_hello();
    // print_numbers();
}

