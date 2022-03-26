#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// в данной задаче мы будем смотреть как перенаправлять данные из одного файла в другой. 
// знаем, что каждому файлу соотнесен его файловый дискриптор, его мы и будем передавать в функции.

// как раз функция для записи в файловый дискриптор fd, который передаем функции.
void fdprint(int fd, char str[], int size) {
    while (size) {   // крутится пока пока не вычтим все size или пока не сломается
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

    fdprint(STDOUT_FILENO, hello, hello_size);     // печатает строку в STDOUT

/* ---------------п-р-и-м-е-р--1------------------------------------------------------------------------------------- */
    // открываем файл
    // O_WRONLY - хотим только в него записывать
    // O_CREAT  - если не существует файла, то хотим его создать
    // O_TRUNC  - писать мы будем с самого начала файла
    // S_IRUSR|S_IWUSR - права (read/write for user)

    fd = open("dup_stdout", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
    fdprint(fd, hello, hello_size);                // печатает строку в файл "dup_stdout", которому соотвествует fd
    close(fd);

/* ---------------п-р-и-м-е-р--2------------------------------------------------------------------------------------- */
	
    // O_APPEND - писать в конец файла, после всего-всего, что уже есть в нем.
	
    fd1 = open("dup_stdout", O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    fd2 = dup(fd1);          // создаем дубликат fd1, кладем его в fd2
	// // check error    // dup() возвращает -1, если что-то пошло не так, поэтому тут по хорошему нужно обработать ошибки
       // // fd2 = fd1;      // так делать плохо, потому что при закрытии не создастся новый файловый дискриптор
    fdprint(fd1, hello, hello_size);
    fdprint(fd2, hello, hello_size);
    close(fd1);
    close(fd2);
	
    // итого в "dup_stdout" будет содержаться "hello world\nhello world\n"
    // как раз из-за того, что O_APPEND и из-за того, что fd2 - дубликат fd1 и указывают они на один и тот же файл
	
/* ---------------п-р-и-м-е-р--3------------------------------------------------------------------------------------- */
	
    // dup2(fd, 1) - заменяет один файловый дискриптор другим
    // в данном случае fd заменяет 1. то есть если будем писать в 1, на самом деле будет записано в fd.
    // манипуляции да и только (ну это пока)

    fd = open("dup_stdout", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
    dup2(fd, 1);
    dup2(fd, 2);
    close(fd);                      // закрываем fd, несмотря на это stdout(он же 1) не закрывается
    fprintf(stdout, "stdout\n");    // "stdout\n" будет напечатано в "dup_stdout"
    fprintf(stderr, "stderr\n");    // "stderr\n" будет напечатано в "dup_stdout"
    close(fd);
	
    // но мы можем так потерять stdout, так что, чтобы спасти раненого,
    // нужно его куда-нибудь сохранить (тоже использовав dup())

/* ---------------п-р-и-м-е-р--4------------------------------------------------------------------------------------- */
    fd = open("dup_stdin", O_RDONLY);
    dup2(fd, STDIN_FILENO);
    close(fd);

    // таким образом можем считывать данные в файл, потому что заменили поток dup2(fd, STDIN_FILENO);
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d %d\n", a, b);

}
