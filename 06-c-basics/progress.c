#include <unistd.h>
#include <stdio.h>

enum {
    PERCENT = 5,
    LEN = 100 / PERCENT,
};

void print(unsigned p) {
    int p_ = p / PERCENT;

    // Перенос каретки в начало строки - будем перезатирать уже написанное ранее, чтобы progress bar стоял статично на одном месте
    printf("\r[");

    for (int i = 0; i != p_; ++i) {
        printf("-");
    }
    printf(">");

    for (int i = p_; i < LEN; ++i) {
        printf(" ");
    }

    // %4u - отводим 4 символа под процент и выравниваем по правой стороне, чтобы при изменении значения `p` ширина поля не менялась
    // `]   5%`, `]  10%`, `] 100%`
    // %% - чтобы вывести символ %
    printf("]%4u%%", p);

    // сбрасываем буфер printf
    fflush(stdout);
}

void f() {
    sleep(1);
}

int main() {
    for (int i = 0; i <= LEN; ++i) {
        print(i*PERCENT);
        f();
    }
    printf("\n");
}
