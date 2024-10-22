#include <stdio.h>

int main() {
    char c = 'c';
    int i = 127;
    unsigned u = 12;
    float f = 12.225;

    char str[] = "hello world";

    printf("Char: %c\n", c);
    printf("(int)Char: %d\n", c);     
    printf("Int: %d\n", i);    
    printf("Hex: %x\n", i);   
    printf("Unsigned: %u\n", u); 
    printf("Hex (-1): %x\n", -1);
    printf("Float: %f\n", f); 
    printf("Float (prec): %.2f\n", f);

    printf("%d, %c\n", c, c);



    printf("%s\n", str);
    
}
