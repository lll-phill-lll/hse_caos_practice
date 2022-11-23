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

    struct dirent *ent;

    while((ent = readdir(d))) {
        printf("%s\n", ent->d_name);
    }

    closedir(d);
}
