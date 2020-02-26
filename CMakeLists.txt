cmake_minimum_required(VERSION 3.9)
project(cs444)

set(CMAKE_CXX_STANDARD 17)

file(STRINGS ./make/jc.txt jc_source)
file(STRINGS ./make/joosc.txt joosc_source)

include_directories(./srcJoosC)

add_library(
        jc
        SHARED
        ${jc_source}
)

target_compile_options(jc PRIVATE -fvisibility=hidden -O3 -flto -fno-rtti -fno-exceptions)
target_link_options(jc PRIVATE -fvisibility=hidden -flto -O3 -fno-rtti -fno-exceptions)

add_executable(
        cs444
        ${joosc_source}
        )

target_link_libraries(cs444
        jc
        )