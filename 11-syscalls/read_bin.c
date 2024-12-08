#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // argv[0] = "./a.out"
    if (argc < 2) {
        fprintf(stderr, "expected filename\n");
        exit(1);
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file");
        return 1;
    }


    unsigned res = 0;

    ssize_t bytes_read;

    while ((bytes_read = read(fd, &res, sizeof(unsigned))) > 0) {
        assert(bytes_read == sizeof(unsigned));
        printf("%u\n", res);
    }

    close(fd);

    return 0;
}

