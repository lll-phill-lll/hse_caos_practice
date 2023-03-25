#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

unsigned good_checksum = 109205;

unsigned compute_checksum(int fd) {
    unsigned sum = 0;
    char buf[32];
    ssize_t res;
    while ((res = read(fd, buf, sizeof(buf))) > 0) {
        for (int i = 0; i != res; ++i) {
            sum += buf[i];
        }
    }

    return sum;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
    }
    unsigned checksum = compute_checksum(fd);
    if (checksum != good_checksum) {
        printf("Hack prevented!\n");
        exit(1);
    }
    sleep(10);

    // execl(argv[1], argv[1], NULL);

    char* env[] = {NULL};
    char* args[] = {argv[1], argv[1], NULL};
    fexecve(fd, args,env);

}
