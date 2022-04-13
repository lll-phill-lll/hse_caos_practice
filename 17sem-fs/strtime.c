// man example

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char outstr[200]; 
    time_t t;
    struct tm *tmp;

    t = time(NULL);
    tmp = localtime(&t);
    if (tmp == NULL) {
       perror("localtime");
       exit(EXIT_FAILURE);
    }
    
    // подробнее: man strftime
    // strftime представляет структуру tm в виде отформатированной строки
    if (strftime(outstr, sizeof(outstr), argv[1], tmp) == 0) {
        // Возвращает количество символов, записанных в массив,если в нем достаточно места
        // в противном случае возвращает 0
        // В данном случае:
        // outstr - куда нужно положить результат
        // sizeof(outstr) - размер
        // argv[1] - формат
        // tmp - указатель на структуру tm
       fprintf(stderr, "strftime returned 0");
       exit(EXIT_FAILURE);
    }

    printf("Result string is \"%s\"\n", outstr);
    exit(EXIT_SUCCESS);
}
