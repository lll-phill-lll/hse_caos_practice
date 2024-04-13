#pragma once

#include <string>
#include <vector>

#include "pixel.h"

class PPMImage {
public:
    std::vector<Pixel> data;

    int x, y;

    void ReadFromFile(const std::string& filename);

    void SaveToFile(const std::string& filename);
};
