cmake_minimum_required(VERSION 3.6)
project(kingfighter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c)
#set(SOURCE_FILES array.c)

add_executable(kingfighter ${SOURCE_FILES})