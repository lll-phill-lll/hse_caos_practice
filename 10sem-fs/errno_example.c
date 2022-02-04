// Из аргументов командной строки взять имя директории
// и вывести все ее содержимое (выводить ошибки с помощью errno)
//
// printf, fprintf
#include <stdio.h>
// exit
#include <stdlib.h>

// opendir, readdir
#include <dirent.h>
#include <sys/types.h>

// errno
#include <errno.h>
// strerror
#include <string.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "directory is required\n");
        exit(1);
    }

    DIR *d = opendir(argv[1]);

    // man 3 readdir
    // struct dirent {
    //     ino_t          d_ino;       /* Inode number */
    //     off_t          d_off;       /* Not an offset; see below */
    //     unsigned short d_reclen;    /* Length of this record */
    //     unsigned char  d_type;      /* Type of file; not supported
    //                                   by all filesystem types */
    //     char           d_name[256]; /* Null-terminated filename */
    // };


    // Можно использовать простую проверку на ошибки, но тогда не
    // получится узнать, почему именно возникла ошибка
    //
    // if (!d) {
    //     fprintf(stderr, "some error\n");
    //     exit(1);
    // }

    // Можно напечатать ошибки в человеческом формате, для этого
    // получим строку из errno
    // if (!d) {
    //     fprintf(stderr, "%s\n", strerror(errno));
    //     exit(1);
    // }

    // или можно использовать perror
    // if (!d) {
    //     // perror возьмет значение из errno, прибавит туда
    //     // переданное сообщение и выведет в stderr
    //     perror("my custom message");
    //     exit(1);
    // }

    if (!d) {
        switch(errno) {
            case ENOENT:
                fprintf(stderr, "directory <%s> not found\n", argv[1]);
                break;
            case ENOTDIR:
                fprintf(stderr, "<%s> is not a directory\n", argv[1]);
                break;
            default:
                fprintf(stderr, "some error\n");
        }
        exit(1);
    }

    // !!! NOTE !!!
    // errno может не измениться, если функция отработала корректно
    // Это значит, что нельзя проверять на наличие ошибок так:
    // if (errno != 0), потому что может быть, что наша функция
    // отработала корректно и не трогала errno, а значение там осталось
    // от какого-то другого вызова
    // Проверяйте возвращаемое значение из функции, чтобы удостовериться
    //, что произошла ошибка

    struct dirent *ent;

    // same about readdir
    while((ent = readdir(d))) {
        printf("%s\n", ent->d_name);
    }

    int close_res = closedir(d);
    if (!close_res) {
        fprintf(stderr, strerror(errno));
        exit(1);
    }
}
