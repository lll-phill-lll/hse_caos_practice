#include <stdio.h>
#include <unistd.h>

int main() {
    // setbuf(stdout, NULL);
    for (int i=0; i<10; ++i) fprintf(stdout,"%d",i);
    sleep(10);
    return 0;
}

