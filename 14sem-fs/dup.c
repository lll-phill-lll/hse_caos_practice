#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void fdprint(int fd, char str[], int size) {
    while (size) {
        ssize_t written_size = write(fd, str,  size);
        if (written_size < 0) {
            perror("write");
            exit(1);
        }
        size -= written_size;
    }
}

int main() {
    char hello[] = "hello world\n";
    int hello_size = sizeof(hello);
    int fd, fd1, fd2;

    fdprint(STDOUT_FILENO, hello, hello_size);

    // fd = open("dup_stdout", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
    // fdprint(fd, hello, hello_size);
    // close(fd);

    // fd1 = open("dup_stdout", O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    // fd2 = dup(fd1);
	// // check error
    // // fd2 = fd1;
    // fdprint(fd1, hello, hello_size);
    // fdprint(fd2, hello, hello_size);
    // close(fd1);
    // close(fd2);

    // fd = open("dup_stdout", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
    // dup2(fd, 1);
    // dup2(fd, 2);
    // close(fd);
    // fprintf(stdout, "stdout\n");
    // fprintf(stderr, "stderr\n");
    // close(fd);


    fd = open("dup_stdin", O_RDONLY);
    dup2(fd, STDIN_FILENO);
    close(fd);

    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d %d\n", a, b);

}
