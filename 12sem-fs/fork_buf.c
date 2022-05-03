#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("hello");

    if (fork() == 0) {
      //  _exit(0); /* hello -- так как системный вызов */ 
      //  exit(0); /* hellohello -- так как сброс буффера при exit и при return */
    };

    sleep(1);

    return 0;
}
