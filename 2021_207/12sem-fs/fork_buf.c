#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("hello");

    if (fork() == 0) {
        
      //  _exit(0); 
                    /* hello -- так как системный вызов */ 
      //  exit(0); 
                    /* hellohello -- Сброс буффера в ребенке при exit и в родителе при return,
                                     так как буффер скопировался в ребенка при вызове fork */
    };

    sleep(1);

    return 0;
}
