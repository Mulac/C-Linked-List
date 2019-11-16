cmake_minimum_required(VERSION 3.13)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_library(dllist dllist.c dllist.h)

add_executable(test test.c)

TARGET_LINK_LIBRARIES(test dllist)