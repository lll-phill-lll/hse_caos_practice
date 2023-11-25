#include <cmath>
#include <iostream>
#include <vector>

double get_distance(int x, int y) { return std::sqrt(x * x + y * y); }

class Point {
   public:
    Point(int x, int y) : x(x), y(y), len(get_distance(x, y)){};

    int x;
    int y;
    double len;
};

int main() {
    const auto points =
        // std::vector<Point*>{new Point(1, 2), new Point(3, 4), new Point(5, 6)};
        std::vector<Point>{{1, 2}, {3, 4}, {5, 6}};

    for (const auto& point : points) {
        std::cout << point.len << std::endl;
    }
}

