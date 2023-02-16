// Из аргументов командной строки взять имя директории
// и вывести все ее содержимое
//
// printf, fprintf
#include <stdio.h>
// exit
#include <stdlib.h>

// opendir, readdir
#include <dirent.h>
#include <sys/types.h>

#include <string.h>
#include <errno.h>
#include <unistd.h>

// https://www.linuxjournal.com/article/8603
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "directory is required\n");
        exit(1);
    }

    DIR *d = opendir(argv[1]);
    if (!d) {
        perror("[opendir]");
        exit(1);
    }

    // man 3 readdir
    // struct dirent {
    //     ino_t          d_ino;       /* Inode number */
    //     off_t          d_off;       /* Not an offset; see below */
    //     unsigned short d_reclen;    /* Length of this record */
    //     unsigned char  d_type;      /* Type of file; not supported
    //                                   by all filesystem types */
    //     char           d_name[256]; /* Null-terminated filename */
    // };

    struct dirent *ent;

    while((ent = readdir(d))) {
        char* filename = ent->d_name;
        if (access(filename, R_OK | W_OK) == 0) {
            printf(GRN "%s\n" RESET, ent->d_name);

        } else {
            printf(RED "%s\n" RESET, ent->d_name);
        }

    }

    closedir(d);
}
