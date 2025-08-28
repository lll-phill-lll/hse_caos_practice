#pragma once
#include <cstdint>

template<int N>
struct Fib {
    static constexpr uint64_t value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template<> struct Fib<1> { static constexpr uint64_t value = 1; };
template<> struct Fib<0> { static constexpr uint64_t value = 0; };

