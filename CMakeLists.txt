cmake_minimum_required(VERSION 3.9)
project(cs444)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(./srcJoosC srcA)
aux_source_directory(./srcJoosC/parse srcB)
aux_source_directory(./srcJoosC/ast srcC)
aux_source_directory(./srcJoosC/semantic srcd)
include_directories(./srcJoosC)
add_executable(cs444 ${srcA} ${srcB} ${srcC} ${srcd})
target_compile_options(cs444 PUBLIC -fno-rtti -fno-exceptions -Wall -Wextra
        -Wformat=2 -Wcast-align -Wcast-qual -Wdisabled-optimization -Winit-self
        -Wmissing-include-dirs -Wredundant-decls -Wshadow -Wundef -Wno-variadic-macros
        -Wwrite-strings -Wfloat-conversion -Wnull-dereference
        -Wzero-as-null-pointer-constant -Wctor-dtor-privacy -Wnon-virtual-dtor
        -Woverloaded-virtual -Wno-unused-parameter -Wfatal-errors)
