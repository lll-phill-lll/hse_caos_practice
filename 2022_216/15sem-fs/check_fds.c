#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>
#include <fcntl.h>

int main() {

    struct rlimit rlim;

    int res = getrlimit(RLIMIT_NOFILE, &rlim);
    if (res < 0) {
        perror("limit");
    }
    // printf("%ld, %ld\n", rlim.rlim_cur, rlim.rlim_max);

    char buf[1024];
    for (int i = 3; i != rlim.rlim_cur; ++i) {
        int res;
        while ((res = read(i, buf, sizeof(buf))) > 0) {
            printf("%s", buf);
        }
    }

}
