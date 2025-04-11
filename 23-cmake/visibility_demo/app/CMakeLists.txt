add_executable(app main.cpp)

target_link_libraries(app
    PRIVATE private_lib
    PRIVATE public_lib
    PRIVATE interface_lib
)
