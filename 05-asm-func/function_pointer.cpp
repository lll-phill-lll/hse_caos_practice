#include <iostream>
#include <vector>
#include <algorithm>


void my_abs(int* num) {
    if (*num < 0) *num = -*num;
}

void my_abs_ref(int& num) {
    if (num < 0) num = -num;
}

// func_t
typedef void (*func_t)(int&);

extern "C" void my_for_each(int* arr, int size, func_t modifier);

int main() {

    std::vector<int> nums;

    int num;
    while(std::cin >> num) {
        nums.push_back(num);
    }

    // for (int i = 0; i < nums.size(); ++i) {
    //     my_abs(&nums[i]);
    // }



    // std::for_each(nums.begin(), nums.end(), my_abs_ref);

    my_for_each(nums.data(), nums.size(), my_abs);



    for (int i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << std::endl;
    }

}
