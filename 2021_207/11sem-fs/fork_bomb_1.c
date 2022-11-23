#include <sys/types.h>
#include <unistd.h>

// do not run
int main() {
    while (1) {
        // Каждый процесс будет запускать себе ребенка и количество детей будет увеличиваться пока не израсходуется лимит
        fork();
    }
}
