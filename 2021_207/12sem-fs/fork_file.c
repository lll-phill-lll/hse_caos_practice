#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void write_to_file(int fd) {
    const char* hello = "hello\n";
    // think about small write
    ssize_t output_size = write(fd, hello, strlen(hello));
    if (output_size != strlen(hello)) {
        perror("hello");
        exit(1);
    }
}


int main(int argc, char* argv[]) {
    // argv[0] = "./a.out"
    if (argc < 2) {
        fprintf(stderr, "expected filename\n");
        exit(1);
    }

    int fd = open(argv[1], O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    if (fd < 0) {
        fprintf(stderr, "failed open file\n");
        exit(1);
    }

    write_to_file(fd);

    if (fork() == 0) {
        write_to_file(fd);
        printf("%d\n", getpid());
        sleep(100);
        exit(0);
    }

    printf("%d\n", getpid());
    wait(NULL);

    write_to_file(fd);

    int close_res = close(fd);
    if (close_res == -1) {
        fprintf(stderr, "failed write\n");
        exit(1);
    }

    return 0;
}
