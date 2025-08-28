#include <iostream>

#include "ppm.h"
#include "grayscale.h"
#include "blur.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Choose: Gray or Blur" << std::endl;
        exit(1);
    }

    PPMImage img;
    img.ReadFromFile("dogs.ppm");

    std::string input = argv[1];

    if (input == "Gray") {
        MakeGray(img.data);
    } else if (input == "Blur") {
        ApplyBlur(img.data, img.x, img.y);
    } else {
        std::cerr << "Not recognized" << std::endl;
        exit(1);
    }
    img.SaveToFile("dogsResult.ppm");
}
