#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "expected filename\n");
        exit(1);
    }
    char* filename = argv[1];
    char c = 'c';

    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("can't open");
        exit(1);
    }
    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("can't stat");
        exit(1);
    }

    int input_size = st.st_size;
    char *mp = mmap(NULL, input_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mp == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }

    // printf("File: %s", mp);
    for (int i = 0; i != input_size; ++i) {
        mp[i] = c;
    }

    if (munmap(mp, input_size) == -1) {
        perror("can't stat");
        exit(1);
    }

    if (close(fd) == -1) {
        perror("can't stat");
        exit(1);
    }

    return 0;
}
