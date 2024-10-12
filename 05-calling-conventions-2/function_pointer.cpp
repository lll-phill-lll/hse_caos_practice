#include <iostream>
#include <vector>


void my_abs(int* num) {
    if (*num < 0) *num = -*num;
}

void my_mult(int* num) {
    *num = *num * 2;
}
// func_t
typedef void (*func_t)(int*);

extern "C" void my_for_each(int* arr, int size, func_t modifier);

int main() {

    std::vector<int> nums;

    int num;
    while(std::cin >> num) {
        nums.push_back(num);
    }

    my_for_each(nums.data(), nums.size(), my_mult);


    for (int i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << std::endl;
    }

}
