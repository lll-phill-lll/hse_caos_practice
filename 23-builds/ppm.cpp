#include "ppm.h"

#include <iostream>
#include <fstream>

void PPMImage::ReadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File: " << filename << " not found" << std::endl;
        return;
    }

    std::string fileFormat;
    file >> fileFormat;

    if (fileFormat != "P3") {
        std::cout << "Format no supported" <<std::endl;
        exit(1);
    }

    int rgb_comp_color;
    file >> x >> y;
    file >> rgb_comp_color;

    data.resize(x * y);
    for (int i = 0; i < x * y; i++){
        file >> data[i].red >> data[i].green >> data[i].blue;
    }

    file.close();
}

void PPMImage::SaveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ofstream::out);
    file << "P3" << std::endl;
    file << x << " " << y << " "<< std::endl;
    file << 255 << std::endl;

    for(int i = 0; i < x * y; i++){
        file << data[i].red << " " << data[i].green << " " << data[i].blue << (((i + 1) % x == 0)? "\n" : " ");
    }
    file.close();
}
