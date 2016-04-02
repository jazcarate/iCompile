cmake_minimum_required(VERSION 3.5)
project(iCompile)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

file(GLOB_RECURSE Foo_SOURCES "src/*.cpp")
file(GLOB_RECURSE Foo_HEADERS "src/*.h")

set (Foo_INCLUDE_DIRS "")
foreach (_headerFile ${Foo_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Foo_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Foo_INCLUDE_DIRS)

include_directories(${Foo_INCLUDE_DIRS})


set(SOURCE_FILES src/main.c src/tests/test_suite.c src/server/server.c src/webProvider/webProvider.c src/webProvider/webProvider.h src/tests/webProvider/webProvider.c)
add_executable(iCompile ${SOURCE_FILES})
target_link_libraries (iCompile commons)
