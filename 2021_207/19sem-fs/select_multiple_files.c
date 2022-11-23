#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main() {

    int fds[1];

    fds[0] = open("file1.txt", O_CREAT | O_TRUNC | O_RDWR, 0666);
    fd_set rfds;
    while(1) {

        struct timeval tv;
        int retval;

        /* Watch stdin (fd 0) to see when it has input. */

        FD_ZERO(&rfds);
        FD_SET(fds[0], &rfds);

        /* Wait up to five seconds. */

        tv.tv_sec = 5;
        tv.tv_usec = 0;

        retval = select(fds[0]+1, &rfds, NULL, NULL, &tv);
        if (retval < 0) {
            perror("select");
        }
        /* Don't rely on the value of tv now! */

        for (int i = 0; i != sizeof(fds); ++i) {
            if FD_ISSET(fds[i], &rfds) {
                char buf[1024] = {0};
                int res = read(fds[i], buf, sizeof(buf) - 1);
                if (res < 0) {
                    perror("read");
                }
                if (res > 0) {
                    printf("%s\n", buf);
                }
            }
        }
    }

}
