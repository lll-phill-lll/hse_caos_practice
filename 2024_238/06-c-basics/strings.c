#include <stdio.h>
#include <string.h>

int main() {
    char hello[] = "Hello world!";

    printf("sizeof(hello): %ld\n", sizeof(hello));
    printf("strlen(hello): %ld\n", strlen(hello));

    printf("%s\n", hello);


    const char* hello2 = "Hello world!";

    printf("sizeof(hello): %ld\n", sizeof(hello2));
    printf("strlen(hello): %ld\n", strlen(hello2));

    
    // hello2[0] = 'a';

    
}
