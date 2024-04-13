#pragma once

#include "pixel.h"

#include <vector>


void ApplyBlur(std::vector<Pixel>& image, int width, int height) {
    std::vector<Pixel> blurredImage(image.size());

    int blurRadius = 5;

    for (int y = blurRadius; y < height - blurRadius; ++y) {
        for (int x = blurRadius; x < width - blurRadius; ++x) {
            int index = y * width + x;

            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            for (int dy = -blurRadius; dy <= blurRadius; ++dy) {
                for (int dx = -blurRadius; dx <= blurRadius; ++dx) {
                    int neighborIndex = (y + dy) * width + (x + dx);
                    totalRed += image[neighborIndex].red;
                    totalGreen += image[neighborIndex].green;
                    totalBlue += image[neighborIndex].blue;
                }
            }
            int avgRed = totalRed / ((2 * blurRadius + 1) * (2 * blurRadius + 1));
            int avgGreen = totalGreen / ((2 * blurRadius + 1) * (2 * blurRadius + 1));
            int avgBlue = totalBlue / ((2 * blurRadius + 1) * (2 * blurRadius + 1));

            blurredImage[index].red = avgRed;
            blurredImage[index].green = avgGreen;
            blurredImage[index].blue = avgBlue;
        }
    }
	image = blurredImage;
}
