cmake_minimum_required(VERSION 3.9)
project(cs444)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(./srcJoosC the_src)
aux_source_directory(./srcJoosC/parse the_parse)
aux_source_directory(./srcJoosC/ast the_ast)

add_executable(cs444 ${the_src} ${the_parse} ${the_ast})
