// Еще один способ, как можно получить
// части float числа

#include <stdio.h>
#include <string.h>

#define SIGN_BITS 1
#define MANT_BITS 23
#define EXP_BITS 8

// печатаем число в бинарном виде
// первый аргмент - само число, второй аргумент
// - сколько бит нужно печатать
void print_bin(unsigned n, unsigned size) {
    unsigned i;
    for (i = 1 << (size - 1); i > 0; i = i >> 1) {
        (n & i) ? printf("1") : printf("0");
    }
    printf("\n");
}

// функция для получения экспоненты
unsigned get_exp(float num) {
    // такое преобразование позволяет переложить
    // биты из float в unsigned, чтобы мы могли спокойно
    // воспользоваться операцией сдвига
    // в exp будут лежать ровно те же биты в том же порядке,
    // что лежали в num.
    // если бы мы сделали exp = num, то у нас бы случилось
    // преобразование float к unsigned int и биты лежали бы уже
    // другие
    // unsigned exp;
    // memcpy(&exp, &num, sizeof(num));

    // код ниже приводит к нарушению strict aliasing rule
    // хотя много где он и используется
    // см пример из: https://en.cppreference.com/w/c/string/byte/memcpy
    // подробнее про strict aliasing:
    // https://habr.com/ru/company/otus/blog/443602/
    unsigned exp = *(unsigned*)&num;

    // Чтобы получить экспоненту нужно избавится от бита знака (сдвинуть на один
    // влево) и избавиться от мантиссы (сдвинуть на 23 вправо (и еще на один
    // вправо так как мы до этого вдигали влево))
    return exp << SIGN_BITS >> (SIGN_BITS + MANT_BITS);
}

// получим мантиссу
unsigned get_mant(float num) {

    // unsigned mant;
    // memcpy(&mant, &num, sizeof(num));

    // код ниже приводит к нарушению strict aliasing rule
    // хотя много где он и используется
    // см пример из: https://en.cppreference.com/w/c/string/byte/memcpy
    // подробнее про strict aliasing:
    // https://habr.com/ru/company/otus/blog/443602/
    unsigned mant = *(unsigned*)&num;

    int to_remove = SIGN_BITS + EXP_BITS;
    // сдвинем на знак и экспонену влево, чтобы обнулить их
    // а затем обратно вправо
    return mant << (to_remove) >> to_remove;
}

// Получим знак числа
unsigned get_sign(float num) {
    unsigned sign;
    memcpy(&sign, &num, sizeof(num));

    // код ниже приводит к нарушению strict aliasing rule
    // хотя много где он и используется
    // см пример из: https://en.cppreference.com/w/c/string/byte/memcpy
    // подробнее про strict aliasing:
    // https://habr.com/ru/company/otus/blog/443602/ unsigned sign =
    // sign = *(unsigned*)&num;

    // сдвинем число на 31 вправо, чтобы остался только бит знака
    return sign >> (MANT_BITS + EXP_BITS);
}

int main() {
    float f = -114.3;

    unsigned sign = get_sign(f);
    unsigned exp = get_exp(f);
    unsigned mant = get_mant(f);

    printf("%f\n", f);
    printf("sign\t = \t");
    print_bin(sign, SIGN_BITS);
    printf("exponent = \t");
    print_bin(exp, EXP_BITS);
    printf("mantissa = \t");
    print_bin(mant, MANT_BITS);
}
