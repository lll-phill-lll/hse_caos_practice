#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/select.h>

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
    int fds[2 * child_num];
    for (int i = 0; i != child_num; ++i) {
        pipe(fds + i * 2);

        pid_t pid = fork();
        // if we are child
        if (!pid) {
            child_action(fds + i * 2, 5 + i * 5);
        }
    }

    fd_set rfds;

    while(1) {
        FD_ZERO(&rfds);

        int max_fd;
        for (int i = 0; i != child_num; ++i) {
            int fd = fds[i * 2];
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
        for (int i = 0; i != child_num; ++i) {
            if FD_ISSET(fds[i * 2], &rfds) {
                char buf[1024] = {0};
                int res = read(fds[i * 2], buf, sizeof(buf) - 1);
                printf("%s", buf);
                anyone_set = 1;
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
