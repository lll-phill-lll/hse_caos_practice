



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define MAX_EVENTS 10

int main() {
    int efd, tfd;
    struct epoll_event event;
    struct epoll_event events[MAX_EVENTS];

    // Создание epoll instance
    efd = epoll_create1(0);
    if (efd == -1) {
        handle_error("epoll_create1");
    }

    // Создание timerfd
    tfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);
    if (tfd == -1) {
        handle_error("timerfd_create");
    }

    // Настройка таймера (интервал 1 секунда)
    struct itimerspec new_value;
    new_value.it_value.tv_sec = 1;
    new_value.it_value.tv_nsec = 0;
    new_value.it_interval.tv_sec = 1;
    new_value.it_interval.tv_nsec = 0;

    if (timerfd_settime(tfd, 0, &new_value, NULL) == -1) {
        handle_error("timerfd_settime");
    }

    // Добавление timerfd в epoll instance
    event.data.fd = tfd;
    event.events = EPOLLIN | EPOLLET;  // Используем Edge-Triggered режим
    if (epoll_ctl(efd, EPOLL_CTL_ADD, tfd, &event) == -1) {
        handle_error("epoll_ctl");
    }

    while (1) {
        int n = epoll_wait(efd, events, MAX_EVENTS, -1);
        if (n == -1) {
            if (errno == EINTR) {
                continue;  // Системный вызов прерван, продолжаем ожидание
            } else {
                handle_error("epoll_wait");
            }
        }

        for (int i = 0; i < n; i++) {
            if (events[i].events & EPOLLIN) {
                uint64_t expirations;
                ssize_t s = read(events[i].data.fd, &expirations, sizeof(expirations));
                if (s != sizeof(expirations)) {
                    handle_error("read");
                }
                printf("Timer expired %llu times\n", (unsigned long long) expirations);
            }
        }
    }

    close(tfd);
    close(efd);
    return 0;
}
