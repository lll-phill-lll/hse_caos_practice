

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

void print_space(size_t repeats) {
    for (size_t i = 0; i < repeats; ++i) {
        printf("%lu - Hello world ", i);
    }
}

void print_new_line(size_t repeats) {
    for (size_t i = 0; i < repeats; ++i) {
        printf("%lu - Hello world\n", i);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    int repeats = atoi(argv[1]);

    char buf[0];
    setvbuf(stdout, buf, _IOFBF, 0);

    clock_t space_time = clock();
    print_space(repeats);
    space_time = clock() - space_time;
    double space_time_taken = ((double)space_time) / CLOCKS_PER_SEC;

    clock_t new_line_time = clock();
    print_new_line(repeats);
    new_line_time = clock() - new_line_time;
    double new_line_time_taken = ((double)new_line_time) / CLOCKS_PER_SEC;

    printf("\nSpace time:\t%f sec\nNew Line time:\t%f sec\n", space_time_taken,
           new_line_time_taken);

    fflush(stdout);
}
