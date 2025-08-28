add_executable(test_fib
    test_fib.cpp
)

target_link_libraries(test_fib
    PRIVATE
      GTest::gtest_main
      fib
)

target_include_directories(test_fib
    PRIVATE
      ${PROJECT_SOURCE_DIR}/include
)

include(GoogleTest)
gtest_discover_tests(test_fib)

