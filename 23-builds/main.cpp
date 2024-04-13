#include <iostream>

#include "ppm.h"
#include "grayscale.h"
#include "blur.h"

int main() {
    PPMImage img;
    img.ReadFromFile("dogs.ppm");
    ApplyBlur(img.data, img.x, img.y);
    img.SaveToFile("dogsBlurred.ppm");
}
