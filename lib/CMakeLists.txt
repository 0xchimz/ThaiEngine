cmake_minimum_required(VERSION 3.3)
project(readfile)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Reader.cpp Reader.h)
add_library(thaiengine ${SOURCE_FILES})