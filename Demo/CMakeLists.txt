cmake_minimum_required(VERSION 3.14)
project(xWindow)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Demo)

add_executable(Demo main.cpp)
target_link_libraries(Demo PRIVATE xWindow)