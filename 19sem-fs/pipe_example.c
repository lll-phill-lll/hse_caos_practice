#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

void child_action(int fds[], int sleep_time) {
    close(fds[0]);

    while(1) {
        sleep(sleep_time);
        dprintf(fds[1], "child was sleeping %d sec\n", sleep_time);
    }

    // do something
    _exit(0);
}

int main() {
    int fds[2];
    pipe(fds);

    pid_t pid = fork();
    // if we are child
    if (!pid) {
        child_action(fds, 10);
    }

    pid = fork();
    // if we are child
    if (!pid) {
        child_action(fds, 5);
    }

    close(fds[1]);
    char buf[1024] = {0};
    while (read(fds[0], &buf, sizeof(buf))) {
        printf("%s", buf);
    }

    wait(NULL);
    wait(NULL);
}
