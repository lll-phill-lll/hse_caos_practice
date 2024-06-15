#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/timerfd.h>

#define MAX_EVENTS 10
#define PORT 33333

int clients_connected = 0;

void set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int setup_server(int epoll_fd) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 5) == -1) {
        perror("listen");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    set_nonblocking(sockfd);

    struct epoll_event event;
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = sockfd;

    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &event);
    return sockfd;
}

int setup_timer(int epoll_fd) {
    int tfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);

    struct itimerspec new_value;
    new_value.it_value.tv_sec = 1;
    new_value.it_value.tv_nsec = 0;
    new_value.it_interval.tv_sec = 5;
    new_value.it_interval.tv_nsec = 0;

    timerfd_settime(tfd, 0, &new_value, NULL);

    struct epoll_event event;
    event.data.fd = tfd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, tfd, &event);

    return tfd;
}

const char http_response_template[] =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: %d\r\n"
    "\r\n"
    "<html><body><h1>Echo Server</h1><p>%.*s</p></body></html>";

void handle_client_events(int epoll_fd, struct epoll_event *events, int i) {
    int fd = events[i].data.fd;

    if (events[i].events & EPOLLHUP) {
        printf("Disconnected. Freed fd: %d\n", fd);
        close(fd);
    } else if (events[i].events & EPOLLIN) {
        char buffer[1024];
        ssize_t count;
        while ((count = read(fd, buffer, sizeof(buffer))) > 0) {
            printf("[MSG%d] %.*s\n", fd, (int)count, buffer);


            char response[2048];
            int content_length = snprintf(NULL, 0, "<html><body><h1>Echo Server</h1><p>%.*s</p></body></html>", (int)count, buffer);
            int response_length = snprintf(response, sizeof(response), http_response_template, content_length, (int)count, buffer);

            ssize_t total_written = 0;
            while (total_written < response_length) {
                ssize_t written = write(fd, response + total_written, response_length - total_written);
                if (written == -1) {
                    perror("write");
                    close(fd);
                    break;
                }
                total_written += written;
            }
        }
        if (count == -1 && errno != EAGAIN) {
            perror("read");
            close(fd);
        } else if (count == 0) {
            --clients_connected;
            printf("Disconnected fd: %d\n", fd);
            close(fd);
        }
    }
}

void handle_new_client(int epoll_fd, struct epoll_event *events, int i) {
    int server_fd = events[i].data.fd;

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break;
            } else {
                perror("accept");
                break;
            }
        }

        set_nonblocking(client_fd);
        struct epoll_event event;
        event.events = EPOLLIN | EPOLLET | EPOLLHUP;
        event.data.fd = client_fd;

        ++clients_connected;

        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event) == -1) {
            perror("epoll_ctl");
            close(client_fd);
        }
        printf("Connected fd: %d\n", client_fd);
    }
}

void handle_print_log(int fd) {
    uint64_t expirations;
    ssize_t s = read(fd, &expirations, sizeof(expirations));
    printf("[LOG] clients connected: %d\n", clients_connected);
}

int main() {
    int epoll_fd = epoll_create1(0);

    int server_fd = setup_server(epoll_fd);

    int timer_fd = setup_timer(epoll_fd);

    struct epoll_event events[MAX_EVENTS];
    while (1) {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        for (int i = 0; i < nfds; ++i) {
            if (events[i].data.fd == server_fd) {
                handle_new_client(epoll_fd, events, i);
            } else if (events[i].data.fd == timer_fd) {
                handle_print_log(timer_fd);
            } else {
                handle_client_events(epoll_fd, events, i);
            }
        }
    }

    close(server_fd);
    close(epoll_fd);
    return 0;
}
