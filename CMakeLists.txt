cmake_minimum_required(VERSION 3.9)
project(cs444)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(./srcJoosC srcA)
aux_source_directory(./srcJoosC/parse srcB)
aux_source_directory(./srcJoosC/ast srcC)
include_directories(./srcJoosC)
add_executable(cs444 ${srcA} ${srcB} ${srcC})
