cmake_minimum_required(VERSION 3.18)

project(off_parser)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(BUILD_SHARED_LIBS "Specifies the type of libraries (SHARED or STATIC) to build" ON)

option(BUILD_RELEASE_TYPE "Specifies the type of libraries (RELEASE or DEBUG) to build" OFF)

set(LIB_NAME)

if (BUILD_RELEASE_TYPE)
    set(CMAKE_BUILD_TYPE Release)
    set(LIB_NAME ${PROJECT_NAME})
else()
    set(CMAKE_BUILD_TYPE Debug)
    set(LIB_NAME ${PROJECT_NAME}d)
endif()

if (BUILD_SHARED_LIBS)
    add_library(${LIB_NAME} SHARED src/off_parser.cpp)
    target_compile_definitions(${LIB_NAME} PRIVATE -DDLL_EXPORT)
else()
    add_library(${LIB_NAME} src/off_parser.cpp)
endif()

target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(ut_name ut_${PROJECT_NAME})

add_executable(${ut_name} src/main.cpp)

target_link_libraries(${ut_name} PRIVATE ${LIB_NAME})
target_include_directories(${ut_name} PUBLIC ${CMAKE_SOURCE_DIR}/include)

set_target_properties(${ut_name} ${LIB_NAME} PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
                      ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
                      LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
