#include "julia.h"
#include "color.h"
#include "fib.h"
#include <vector>
#include <iostream>

constexpr int WIDTH = Fib<50>::value % 800 + 2000;
constexpr int HEIGHT = Fib<46>::value % 600 + 1500;
constexpr int MAX_ITER = Fib<40>::value % 500 + 1500;

constexpr double C_RE = -0.7;
constexpr double C_IM = 0.27015;

// constexpr double C_RE = 0.355;
// constexpr double C_IM = 0.355;

// constexpr double C_RE = 0.285;
// constexpr double C_IM = 0.01;

int main() {
    std::cout << "Generating Julia set image (" << WIDTH << "x" << HEIGHT << ")\n";

    std::vector<Color> pixels(WIDTH * HEIGHT);

    const double x_min = -1.5, x_max = 1.5;
    const double y_min = -1.2, y_max = 1.2;

    for (int py = 0; py < HEIGHT; ++py) {
        double y0 = y_min + py * (y_max - y_min) / HEIGHT;
        for (int px = 0; px < WIDTH; ++px) {
            double x0 = x_min + px * (x_max - x_min) / WIDTH;
            int iter = julia(x0, y0, MAX_ITER, C_RE, C_IM);
            pixels[py * WIDTH + px] = getColor(iter, MAX_ITER);
        }
    }

    savePPM("image.ppm", pixels.data(), WIDTH, HEIGHT);
    std::cout << "Image saved to image.ppm\n";
    return 0;
}
