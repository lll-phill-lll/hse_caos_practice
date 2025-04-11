add_library(private_lib private.cpp)
target_include_directories(private_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
