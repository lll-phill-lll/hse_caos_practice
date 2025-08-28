#include <vector>
#include <iostream>

struct Triangle {
    int leg1;
    int leg2;
    int hypot;
};

extern "C" void compute_hypots(Triangle* arr, int size);


int main() {
    std::vector<Triangle> triangles;
    int leg1, leg2;
    while(std::cin >> leg1 >> leg2) {
        triangles.push_back({leg1, leg2, 0});
    }

    compute_hypots(triangles.data(), triangles.size());


    for(const auto& triangle : triangles) {
        std::cout << triangle.leg1 << " " << triangle.leg2 << " " << triangle.hypot << std::endl;
    }

}
