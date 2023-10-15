cmake_minimum_required(VERSION 3.24)
project(cubesat)

set(CMAKE_CXX_STANDARD 17)

add_executable(binar.exe binar.cpp bitmapRW.cpp bitmapRW.h)
add_executable(median.exe median.cpp bitmapRW.cpp bitmapRW.h)
