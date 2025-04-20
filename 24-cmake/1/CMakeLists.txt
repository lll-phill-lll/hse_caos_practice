cmake_minimum_required(VERSION 3.16)
project(fractal VERSION 1.0.0)

add_executable(fractal
    main.cpp 
    color.cpp 
    julia.cpp
)

target_compile_features(fractal PUBLIC cxx_constexpr)
# target_compile_options(fractal PRIVATE -Wall -W)
