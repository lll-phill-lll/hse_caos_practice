#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {

    struct addrinfo hints = { .ai_family = AF_INET, .ai_socktype = SOCK_STREAM };
    struct addrinfo *addrs = NULL;

    int res = getaddrinfo(argv[1], argv[2], &hints, &addrs);
    if (res) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
        return 1;
    }

    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("connect");
        return 1;
    }

    res = connect(fd, addrs->ai_addr, sizeof(struct sockaddr_in));
    if (res < 0) {
        perror("connect");
        return 1;
    }

    write(fd, "HI!\n\r", strlen("HI\n\r"));

    char c;
    while (read(fd, &c, 1) == 1) {
        write(1, &c, 1);
    }

    close(fd);
    freeaddrinfo(addrs);
}
