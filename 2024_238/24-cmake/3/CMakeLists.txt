cmake_minimum_required(VERSION 3.16)
project(fractal VERSION 1.0.0 LANGUAGES CXX)

option(ANOTHER_FRAC "Use Julia constant C = 0.355 + 0.355i" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_library(fib INTERFACE)
target_include_directories(fib INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_compile_features(fib INTERFACE cxx_std_20)

add_library(fractal_lib STATIC
    src/julia.cpp
    src/color.cpp
)
target_include_directories(fractal_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(fractal_lib PRIVATE fib)
target_compile_features(fractal_lib PUBLIC cxx_std_20)

add_executable(fractal_app
    src/main.cpp
)
target_link_libraries(fractal_app PRIVATE fractal_lib)
target_compile_features(fractal_app PRIVATE cxx_std_20)

if(ANOTHER_FRAC)
    target_compile_definitions(fractal_app PRIVATE ANOTHER_FRAC)
endif()

enable_testing()

add_executable(test_fib
    tests/test_fib.cpp
)
target_link_libraries(test_fib PRIVATE fib)
add_test(NAME fib_test COMMAND test_fib)
