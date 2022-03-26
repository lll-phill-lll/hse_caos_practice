#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void child_read_no_limit(int fds[]) {  // но мы можем со стороны ребенка не знать сколько мы хотим прочесть
    int val;
    close(fds[1]);    // если бы ни этот close, который закрывает все дискрипторы, мы бы зациклись, потому что
                      // ребенок не заканчивал считывание, если бы хотя бы кто-то мог что-либо писать
    while(read(fds[0], &val, sizeof(val))) {
        printf("[child] read: %d\n", val);
    }

    printf("[child] finish reading\n");
    _exit(0);
}

void child_read_with_limit(int fds[]) {  // читает и выводит то, что прочитал e родителя
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
    write(fds[1], &max_iter, sizeof(max_iter));    // выводит 5

    int square;
    for (int i = 0; i != max_iter; ++i) {
        sleep(1);
        square = i * i;
        printf("[parent] writing: %d\n", square);
        write(fds[1], &square, sizeof(square));     // пять раз выводит i*i
    }
    printf("[parent] finish writing\n");

    close(fds[0]);
    close(fds[1]);
}

int main() {
    int fds[2];
    pipe(fds);                      // создаем канал
    pid_t pid = fork();             // создаем потомка
    if (!pid) {
        child_read_no_limit(fds);   // ребенок будет читать то, что пишет родитель
    }
    parent_write_with_limit(fds);   // родитель пишет
    wait(NULL);
}
