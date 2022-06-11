#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/timerfd.h>
#include <stdint.h>

void child_action(int fds[], int sleep_time) {
    close(fds[0]);

    while(1) {
        sleep(sleep_time);
        dprintf(fds[1], "child was sleeping %d sec\n", sleep_time);
    }
    _exit(0);
}

int main() {
    const int child_num = 2;
    const int read_fds_size = 3;
    int read_fds[read_fds_size];

    // set children
    int fds[2 * child_num];
    for (int i = 0; i != child_num; ++i) {
        pipe(fds + i * 2);

        pid_t pid = fork();
        // if we are child
        if (!pid) {
            child_action(fds + i * 2, 5 + i * 5);
        }

        read_fds[i] = fds[i * 2];
    }
    // ----

    // set timer
    int timer_fd = timerfd_create(CLOCK_REALTIME, 0);

    struct itimerspec new_value;
    new_value.it_value.tv_sec = 5;
    new_value.it_value.tv_nsec = 0;
    new_value.it_interval.tv_sec = 3;
    new_value.it_interval.tv_nsec = 0;

    timerfd_settime(timer_fd, 0, &new_value, NULL);

    read_fds[2] = timer_fd;
    // ----

    fd_set rfds;

    while(1) {
        FD_ZERO(&rfds);

        int max_fd;
        for (int i = 0; i != read_fds_size; ++i) {
            int fd = read_fds[i];
            FD_SET(fd, &rfds);
            if (fd > max_fd) {
                max_fd = fd;
            }
        }

        struct timeval tv;
        tv.tv_sec = 2;
        tv.tv_usec = 0;

        select(max_fd + 1, &rfds, NULL, NULL, &tv);

        int anyone_set = 0;
        for (int i = 0; i != read_fds_size; ++i) {
            if FD_ISSET(read_fds[i], &rfds) {
                anyone_set = 1;
                if (read_fds[i] == timer_fd) {
                    printf("alarm!\n");
                    uint64_t exp;
                    read(read_fds[i], &exp, sizeof(exp));
                    continue;
                }
                char buf[1024] = {0};
                int res = read(read_fds[i], buf, sizeof(buf) - 1);
                printf("%s", buf);
            }
        }
        if (!anyone_set) {
            printf("nothing is ready\n");
        }
    }


    for (int i = 0; i != child_num; ++i) {
        wait(NULL);
    }
}
