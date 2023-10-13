#include <iostream>

int main() {
    char buf[50] = "y";
    for (int j = 0; j < 9; ++j) {

        std::cout << (j * 1'000'000'000) << std::endl;
        if (buf[0] == 'x') break;
    }
}
