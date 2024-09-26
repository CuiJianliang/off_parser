cmake_minimum_required(VERSION 3.18)

project(OFF_PARSE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(off_parser off_parser.cpp)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC off_parser)
