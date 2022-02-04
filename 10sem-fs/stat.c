#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr, "filename is required");
        exit(1);
    }

    struct stat file_stat;
    if (stat(argv[1], &file_stat) < 0) {
        perror(argv[1]);
        exit(1);
    }

    printf("Size of file: %lu bytes\n", file_stat.st_size);
    printf("File inode: %lu\n", file_stat.st_ino);
    printf("Is file symlink: %d\n", S_ISLNK(file_stat.st_mode));

    char perm[] = "---";
    printf("User permissions: ");
    if (file_stat.st_mode & S_IRUSR) {
        perm[0] = 'r';
    }

    if (file_stat.st_mode & S_IWUSR) {
        perm[1] = 'w';
    }

    if (file_stat.st_mode & S_IXUSR) {
        if (file_stat.st_mode & S_ISUID) {
            perm[2] = 's';
        } else {
            perm[2] = 'x';
        }
    } else {
        if (file_stat.st_mode & S_ISUID) {
            perm[2] = 'S';
        }
    }

    printf("%s\n", perm);

    return 0;
}
