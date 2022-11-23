#if defined(IO_FGETC_UNLOCKED)
// Need _POSIX_C_SOURCE for *_unlocked
#define _POSIX_C_SOURCE 1
#endif

#include <stdio.h>
#include <unistd.h>

int main() {
    unsigned long long charsum = 0;
    while (1) {
#if defined(IO_READ)
        char c;
        if (read(0, &c, sizeof(c)) == 0) {
            break;
        }
#elif defined(IO_FSCANF)
        char c;
        if (fscanf(stdin, "%c", &c) == EOF) {
            break;
        }
#elif defined(IO_FGETC)
        int c;
        if ((c = fgetc(stdin)) == EOF) {
            break;
        }
#elif defined(IO_GETC)
        int c;
        if ((c = getc(stdin)) == EOF) {
            break;
        }
#elif defined(IO_GETC_UNLOCKED)
        int c;
        if ((c = getc_unlocked(stdin)) == EOF) {
            break;
        }
#else
#error Unknown IO method!
#endif
        charsum += (unsigned char) c;
    }
    printf("%llu\n", charsum);
    return 0;
}
