cmake_minimum_required(VERSION 3.3)
project(ThaiEngine)
add_subdirectory(lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(ThaiEngine ${SOURCE_FILES})
target_link_libraries(ThaiEngine thaiengine)