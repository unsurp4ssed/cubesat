cmake_minimum_required(VERSION 3.24)
project(cubesat)

set(CMAKE_CXX_STANDARD 17)

add_executable(binar binar.cpp bitmapRW.cpp bitmapRW.h)
add_executable(median median.cpp bitmapRW.cpp bitmapRW.h)
