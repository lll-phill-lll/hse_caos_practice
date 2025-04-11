add_library(public_lib public.cpp)
target_include_directories(public_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
