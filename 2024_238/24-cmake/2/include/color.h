#pragma once
#include <string>

struct Color {
    int r, g, b;
};

Color getColor(int iter, int max_iter);
void savePPM(const std::string& filename, const Color* pixels, int width, int height);
