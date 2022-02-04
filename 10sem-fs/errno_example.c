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


    // you may want to use this simple check for errors
    // but with this check we can;t identify the type of error
    // non existing directory, wrong type and so on
    // if (!d) {
    //     fprintf(stderr, "some error\n");
    //     exit(1);
    // }

    // you may print error in human readable format
    // if (!d) {
    //     fprintf(stderr, "%s\n", strerror(errno));
    //     exit(1);
    // }

    // or
    // if (!d) {
    //     // perror takes value from errno, adds custom message to it
    //     // and prints to stderr
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
    // errno may not be changed if function correctly worked
    // dont use if (errno != 0). check result of function call.
    // because value of errno may be from previous function call

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
