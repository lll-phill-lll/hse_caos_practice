// Прочитать имя директории, вывести дерево ее структуры.
// папки выделить синим, симлинки фиолетовым
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
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

void tree(char *path, int depth) {
    DIR *dir;
    struct dirent *entry;
    size_t len = strlen(path);

    dir = opendir(path);
    if (!dir) {
        perror(path);
        return;
    }

    while ((entry = readdir(dir))) {
        char *name = entry->d_name;

        if (!strcmp(name, ".") || !strcmp(name, ".."))
            continue;

        for (int i = 0; i < depth; i++) {
            printf("| ");
        }
        printf("|-");

        switch(entry->d_type) {
            case DT_DIR:
                // строки при такой записи просто конкатенируются
                // в конце применяем нейтральный цвет, чтобы не
                // остался синий навсегда
                printf(BLU "%s\n" RESET, name);

                if (len + strlen(name) + 1 > PATH_MAX) {
                    fprintf(stderr, "path is too long: %s/%s\n", path, name);
                    return;
                }

                path[len] = '/';
                strcpy(path + len + 1, name);
                tree(path, depth + 1);
                path[len] = '\0';
                break;
            case DT_LNK:
                printf(MAG "%s\n" RESET, name);
                break;
            default:
                printf("%s\n", name);
        }
    }
    closedir(dir);
}


int main() {
    char path[PATH_MAX + 1];

    printf("Enter path: ");
    scanf("%s", path);

    tree(path, 0);

    return 0;
}
