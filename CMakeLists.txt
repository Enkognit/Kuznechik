cmake_minimum_required(VERSION 3.26)
project(kuznechik)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(main main.cpp kuznyechik.h)
add_compile_options(-O3 -Wall -Wextra -Wpedantic)

add_executable(gen_table gen_table.cpp kuznyechik.h)

add_executable(tests tests.cpp)
target_link_libraries(tests GTest::gtest GTest::gtest_main)
