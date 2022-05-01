#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/epoll.h>


#define MAX_EVENTS 10
#define BUFFER_SIZE 1024

int get_listen_socket() {
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("");
        exit(1);
    }

    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons(33333);
    if (bind(fd, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
        perror("");
        exit(1);
    }

    if (listen(fd, 1) < 0) {
        perror("");
        exit(1);
    }

    return fd;
}

int main() {
    struct epoll_event ev, events[MAX_EVENTS];
    int listen_sock = get_listen_socket();

    int epollfd = epoll_create1(0);
    if (epollfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = listen_sock;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
        perror("epoll_ctl: listen_sock");
        exit(EXIT_FAILURE);
    }

    int nfds;
    for (;;) {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (int n = 0; n < nfds; ++n) {
            if (events[n].data.fd == listen_sock) {
                struct sockaddr_in addr;
                socklen_t addrlen = sizeof(addr);
                int conn_sock = accept4(listen_sock,
                                   (struct sockaddr *) &addr, &addrlen, SOCK_NONBLOCK);
                if (conn_sock == -1) {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
                ev.events = EPOLLIN;
                ev.data.fd = conn_sock;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
            } else {
                char buffer[BUFFER_SIZE] = {0};
                int ret = read(events[n].data.fd, buffer, BUFFER_SIZE - 1);
                buffer[ret] = '\0';
                fprintf(stdout, "%s", buffer);
            }
        }
    }
}
