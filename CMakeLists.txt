cmake_minimum_required(VERSION 3.5)
project(iCompile)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES main.c)
add_executable(iCompile ${SOURCE_FILES})