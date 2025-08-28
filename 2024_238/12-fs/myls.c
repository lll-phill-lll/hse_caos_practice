#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#include "colors.h"

void PrintPerm(mode_t mode) {
    if (S_ISDIR(mode)) {
        printf("d");
    } else if (S_ISLNK(mode)) {
        printf("l");
    } else {
        printf("-");
    }

    if (S_IRUSR & mode) {
        printf("r");
    } else {
        printf("-");
    }
    printf("-------- ");
}

void PrintLine(const char* path, const char* name) {
    char full_path[PATH_MAX];
    sprintf(full_path, "%s/%s", path, name);

    struct stat st;

    if (lstat(full_path, &st)) {
        perror("lstat");
        exit(1);
    }

    PrintPerm(st.st_mode);

    printf("%ld\t", st.st_nlink);

    printf("%ld\t", st.st_size);

    char time_buf[64];
    struct tm *timeinfo = localtime(&st.st_mtime);
    strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", timeinfo);
    printf("%s ", time_buf);

    if (S_ISDIR(st.st_mode)) {
        printf(BLU"%s"CRESET, name);
    } else if (S_ISLNK(st.st_mode)){
        char buf[PATH_MAX];
        int size = readlink(full_path, buf, sizeof(buf));
        if (size < 0) {
            perror("readlink");
            exit(1);
        }
        buf[size] = '\0';
        printf(YEL"%s -> %s"CRESET, name, buf); 

    } else {
        printf("%s", name);
    }






    // if (access(full_path, F_OK | R_OK) == 0) {
    //     printf("%s\n", full_path);
    // } else {
    //     printf(URED"%s\n"CRESET, full_path);

    // }
}

void Traverse(const char* path) {
    DIR* dir = opendir(path);
    if (!dir) {
        perror("opendir");
        exit(1);
    }

    struct dirent* ent;


    while ((ent = readdir(dir))) {
        if (ent->d_name[0] == '.') continue;
        PrintLine(path, ent->d_name);
        printf("\n");
    }

    closedir(dir);
}
int main(int argc, char** argv) {
    const char* name = argc > 1 ? argv[1] : ".";
    Traverse(name);
}
