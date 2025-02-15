#include <sys/types.h>
#include <unistd.h>

// do not run
int main() {
    while (1) {
        fork();
        sleep(2);
    }
}
