#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

#define BUFFER_SIZE 1024
#define MAX_EVENTS 2

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        exit(1);
    }

    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_RDONLY);

    char buf[BUFFER_SIZE];

    int epoll_fd = epoll_create1(0);

    struct epoll_event event;
    event.events = EPOLLIN | EPOLLHUP;

    event.data.fd = fd1;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd1, &event);

    event.data.fd = fd2;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd2, &event);

    while (1) {
        struct epoll_event events[MAX_EVENTS];
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);

        for (int i = 0; i < num_events; i++) {
            int fd = events[i].data.fd;

            if (events[i].events & EPOLLHUP) {
                printf("channel closed\n");
                close(fd);

            } else {
                ssize_t size = read(fd, buf, BUFFER_SIZE);
                if (size > 0) {
                    if (fd == fd1)
                        printf("[CH1]: %.*s", (int)size, buf);
                    else if (fd == fd2)
                        printf("[CH2]: %.*s", (int)size, buf);
                } else if (size == 0) {
                    close(fd);
                }
            }
        }
    }

    close(epoll_fd);

    return 0;
}

