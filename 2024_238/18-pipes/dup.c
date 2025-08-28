#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dprintf(fd, "Writing to fd: %d\n", fd);

    // int fd2 = dup(fd);
    // dprintf(fd2, "Writing to fd: %d\n", fd2);
    // close(fd2);

    close(fd);
    return 0;
}

