#include "grayscale.h"

void MakeGray(std::vector<Pixel>& image) {
    for (int i = 0; i < image.size(); ++i) {
        int val = 0.11 * image[i].red + 0.59 * image[i].green + 0.3 * image[i].blue;
        image[i].red = val;
        image[i].green = val;
        image[i].blue = val;
    }
}
