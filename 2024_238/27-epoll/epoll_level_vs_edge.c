#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>

#define BUFFER_SIZE 2

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file1> \n", argv[0]);
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY | O_NONBLOCK);

    char buf[BUFFER_SIZE];

    int epoll_fd = epoll_create1(0);

    struct epoll_event event;
    event.events = EPOLLIN | EPOLLET;

    event.data.fd = fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);

    while (1) {
        struct epoll_event event;
        int num_events = epoll_wait(epoll_fd, &event, 1, -1);

        for (int i = 0; i < num_events; i++) {
            int efd = event.data.fd;
            printf("Event happened\n");

            if (event.events & EPOLLIN) {
                ssize_t size;
                while ((size = read(efd, buf, BUFFER_SIZE)) > 0) {
                    printf("[CH]: %.*s\n", (int)size, buf);
                }
                if (size == -1 && errno == EAGAIN) {
                    perror("read");
                }
            } 

            if (event.events & EPOLLHUP) {
                close(efd);
                return 0;
            }
        }
        sleep(1);
    }

    close(epoll_fd);

    return 0;
}

