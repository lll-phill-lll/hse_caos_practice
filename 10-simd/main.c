#include <stdio.h>

// float process(float a, float b, float c, int d) {
//     return (a + b) / (c + (float)d);
// }

float process(float a, float b, float c, int d);

int main() {
    float a = 1.1;
    float b = 2.2;
    float c = 3.3;
    int d = 4;

    float res = process(a, b, c, d);

    printf("%f\n", res);
}
