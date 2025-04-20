#include "color.h"
#include "fib.h"
#include <fstream>

#define aa "xxxxxxxxxxxxxxx"
#define bb aa aa aa aa aa aa aa aa aa
#define cc bb bb bb bb bb bb bb bb bb
#define dd cc cc cc cc cc cc cc cc cc
#define ee dd dd dd dd dd dd dd dd dd
#define ff ee ee ee ee ee ee ee ee ee
#define gg ff ff ff ff ff ff ff ff ff
#define hh gg gg gg gg gg gg gg gg gg
#define ii hh hh hh hh hh hh hh hh hh

constexpr const char* smth = ii;

constexpr int COLOR_STEPS = (Fib<50>::value % 256) + 256;

Color gradient(double t) {
    const Color palette[] = {
        { 0,   7, 100 },
        { 32, 107, 203 },
        { 237, 255, 255 },
        { 255, 170, 0 },
        { 0,   2, 0 }
    };
    const int n = sizeof(palette) / sizeof(Color) - 1;
    t = (t < 0 ? 0 : (t > 1 ? 1 : t)) * n;
    int i = int(t);
    double f = t - i;
    return {
        int(palette[i].r + (palette[i+1].r - palette[i].r) * f),
        int(palette[i].g + (palette[i+1].g - palette[i].g) * f),
        int(palette[i].b + (palette[i+1].b - palette[i].b) * f)
    };
}

Color getColor(int iter, int max_iter) {
    if (iter >= max_iter) 
        return {0, 0, 0};
    return gradient(double(iter % COLOR_STEPS) / COLOR_STEPS);
}

void savePPM(const std::string& filename, const Color* pixels, int width, int height) {
    std::ofstream img(filename);
    img << "P3\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < width * height; ++i)
        img << pixels[i].r << " " << pixels[i].g << " " << pixels[i].b << "\n";
}

