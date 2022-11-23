#include <stdio.h>

// Отключено выравнивание и размер ее будет 10
struct S_p {
    unsigned char c1;
    unsigned int i1;
    unsigned char c2;
    unsigned int i2;
}__attribute__((packed));

// Есть выравнивание и она занимает 16
struct S_a {
    unsigned char c1;
    unsigned int i1;
    unsigned char c2;
    unsigned int i2;
};

struct S_p s;

int main() {
    printf("%ld %ld\n", sizeof(struct S_p), sizeof(struct S_a));
    for (unsigned i = 0; i != 100000000; ++i) {
        for (unsigned j = 0; j != 10; ++j) {
            // прибавляем единички к полям много раз
            s.c1 += 1;
            s.i1 += 1;
            s.c2 += 1;
            s.i2 += 1;
        }
    }
 // На некоторых архитектурах разницы во времени почти нет 2.007 и 2.032, 
 // но на каких-то может быть кардинально быстрее
}
