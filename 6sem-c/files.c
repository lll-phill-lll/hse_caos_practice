#include <stdio.h>
#include <stdlib.h>

enum {
    N = 5,
};

int main(int argc, char* argv[]) {

    FILE* file = fopen(argv[1], "r"); // хотим уметь только читать

	if (file == NULL) {
        perror("lala"); // более осмысленная ошибка
        exit(1);
    }

    long x;
    sscanf(argv[2], "%ld", &x);
    long y;
    sscanf(argv[3], "%ld", &y);

    long offset = y * (N + 1) + x;

    // выставляет filepointer в нужное место
    if (fseek(file, offset, SEEK_SET) != 0) {
        perror("fseek");
        exit(1);
    }

    char c = fgetc(file); // для того, чтобы считать char
    if (c == '1') {
        printf("Found\n");
    } else {
        printf("Try again\n");
    }

    fclose(file);
}
