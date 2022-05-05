#include <stdio.h>
#include <unistd.h>

int main() {
	// Если раскомментить, то сначала вывод, потом сон
    // setbuf(stdout, NULL); 
    // Сначала сон, потом вывод (потому что буфферизация) 
    for (int i=0; i<10; ++i) fprintf(stdout,"%d",i);
    sleep(10);
    return 0;
}

