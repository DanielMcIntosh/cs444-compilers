cmake_minimum_required(VERSION 3.15)
project(cs444)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(cs444
        src/main.cpp
        src/utility.cpp
        src/utility.h)
