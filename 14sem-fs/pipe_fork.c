#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void child_read_no_limit(int fds[]) {
    int val;
    close(fds[1]);
    while(read(fds[0], &val, sizeof(val))) {
        printf("[child] read: %d\n", val);
    }

    printf("[child] finish reading\n");
    _exit(0);
}

void child_read_with_limit(int fds[]) {
    int iter_num;
    read(fds[0], &iter_num, sizeof(iter_num));

    printf("[child] want to read: %d\n", iter_num);

    int val;
    for (int i = 0; i != iter_num; ++i) {
        read(fds[0], &val, sizeof(val));
        printf("[child] read: %d\n", val);
    }

    printf("[child] finish reading\n");
    _exit(0);
}

void parent_write_with_limit(int fds[]) {
    int max_iter = 5;
    printf("[parent] want to write: %d\n", max_iter);
    write(fds[1], &max_iter, sizeof(max_iter));

    int square;
    for (int i = 0; i != max_iter; ++i) {
        sleep(1);
        square = i * i;
        printf("[parent] writing: %d\n", square);
        write(fds[1], &square, sizeof(square));
    }
    printf("[parent] finish writing\n");

    close(fds[0]);
    close(fds[1]);
}

int main() {
	int fds[2];
    pipe(fds);
    pid_t pid = fork();

    if (!pid) {
        child_read_no_limit(fds);
    }

    parent_write_with_limit(fds);

    wait(NULL);
}
