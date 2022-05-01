#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/timerfd.h>
#include <stdint.h>
#include <sys/epoll.h>

void child_action(int fds[], int sleep_time) {
    close(fds[0]);

    while(1) {
        sleep(sleep_time);
        dprintf(fds[1], "child was sleeping %d sec\n", sleep_time);
    }
    _exit(0);
}

void create_children(int epoll_fd, int child_num) {
    int fds[2 * child_num];
    for (int i = 0; i != child_num; ++i) {
        pipe(fds + i * 2);

        pid_t pid = fork();
        // if we are child
        if (!pid) {
            child_action(fds + i * 2, 5 + i * 5);
        }

        struct epoll_event evt = {.events=EPOLLIN, .data.fd=fds[i*2]};
        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fds[i * 2], &evt);
    }
}

int create_timer(int epoll_fd) {
    int timer_fd = timerfd_create(CLOCK_REALTIME, 0);

    struct itimerspec new_value;
    new_value.it_value.tv_sec = 5;
    new_value.it_value.tv_nsec = 0;
    new_value.it_interval.tv_sec = 3;
    new_value.it_interval.tv_nsec = 0;

    timerfd_settime(timer_fd, 0, &new_value, NULL);

    struct epoll_event evt = {.events=EPOLLIN, .data.fd=timer_fd};
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, timer_fd, &evt);

    return timer_fd;
}

int main() {
    const int child_num = 2;

    int epoll_fd = epoll_create1(0);

    create_children(epoll_fd, child_num);

    int timer_fd = create_timer(epoll_fd);

    while(1) {
        struct epoll_event evt;
        epoll_wait(epoll_fd, &evt, 1, -1);
        if (evt.data.fd == timer_fd) {
            printf("alarm!\n");
            uint64_t exp;
            read(evt.data.fd, &exp, sizeof(exp));
            continue;
        }
        char buf[1024] = {0};
        int res = read(evt.data.fd, buf, sizeof(buf) - 1);
        printf("%s", buf);
    }


    for (int i = 0; i != child_num; ++i) {
        wait(NULL);
    }
}
