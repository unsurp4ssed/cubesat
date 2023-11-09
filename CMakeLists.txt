cmake_minimum_required(VERSION 3.24)
project(cubesat)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(src)

add_executable(binar binar.cpp src/bitmapRW.cpp include/bitmapRW.h)
add_executable(median median.cpp src/bitmapRW.cpp include/bitmapRW.h include/border_checker.h)
add_executable(close-open close-open.cpp src/bitmapRW.cpp include/bitmapRW.h include/border_checker.h)