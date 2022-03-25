# 14 Семинар 01.03.2022 dup/dup2/pipe/dup2+pipe+fork

## Файлики с кодом:

* [Примеры работы dup/dup2](dup.c)
* [что-то еще](dup_fork.c)
* [что-то еще](full_example.c)
* [что-то еще](pipe_fork.c)
* [что-то еще](pipe_simple.c)
* [что-то еще](program.c)


#  перенаправляем вывод в файловый дискриптор

```

void fdprint(int fd, char str[], int size) {
    while (size) {  // крутится пока мы что-то не запишем в дискриптор
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
    
    
```

Функция fdprint записывает строку "hello world\n" в файловый дискриптор, который передали в функции. Например fdprint(STDOUT_FILENO, hello, hello_size); выведет "hello world\n" в стандартный поток вывода.


