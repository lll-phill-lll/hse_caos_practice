#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fds[2];
    if (pipe(fds)) {
        perror("pipe");
        exit(1);
    }

    // write/read
    // {
    //     char wbuf[] = "hello";
    //     char rbuf[6];

    //     write(fds[1], wbuf, sizeof(wbuf));

    //     ssize_t read_size = read(fds[0], rbuf, sizeof(rbuf));
    //     printf("read bytes: %lu\n", read_size);
    //     int string_len = read_size;
    //     printf("read from pipe: %.*s\n", string_len, rbuf);
    // }

    // {
    //     char wbuf[] = "hello";
    //     char rbuf[6];

    //     ssize_t read_size = read(fds[0], rbuf, sizeof(rbuf));
    //     write(fds[1], wbuf, sizeof(wbuf));
    //     printf("read bytes: %lu\n", read_size);
    //     printf("read from pipe: %s\n", rbuf);
    // }

    // {
    //     char wbuf[] = "hello";
    //     char rbuf[6];

    //     close(fds[1]);
    //     ssize_t read_size = read(fds[0], rbuf, sizeof(rbuf));
    //     write(fds[1], wbuf, sizeof(wbuf));
    //     printf("read bytes: %lu\n", read_size);
    //     printf("read from pipe: %s\n", rbuf);
    // }

    // {
    //     // signal(SIGPIPE, SIG_IGN);
    //     char wbuf[] = "hello";
    //     // close(fds[0]);
    //     close(fds[1]);
    //     int res = write(fds[1], wbuf, sizeof(wbuf));
    //     if (res < 0) {
    //         perror("write");
    //     } else {
    //         printf("success\n");
    //     }
    // }

    {
        char wbuf[] = "hello";
        write(fds[1], wbuf, sizeof(wbuf));
        char rbuf[2];
        ssize_t read_size = read(fds[0], rbuf, sizeof(rbuf));
        printf("read bytes: %lu\n", read_size);
        int string_len = read_size;
        printf("read from pipe: %.*s\n", string_len, rbuf);
    }


}
