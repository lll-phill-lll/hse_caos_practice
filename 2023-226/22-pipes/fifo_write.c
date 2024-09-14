#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "not enough args\n");
        exit(1);
    }
    int messages_num = strtol(argv[1], NULL, 10);
    char message[] = "Hello, world!";

    int fd = open("myfifo", O_WRONLY);

    printf("Opened fifo for write\n");

    for (int i = 0; i < messages_num; ++i) {
        sleep(1);
        dprintf(fd, "[%d] - %s\n", getpid(), message);
        printf("Message sent\n");
    }

    close(fd);
    printf("Closed fifo for write\n");
}
