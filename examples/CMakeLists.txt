cmake_minimum_required(VERSION 3.17)

project(examples LANGUAGES C CXX)

add_executable(example01 example01.cpp)
target_link_libraries(example01 influxdblptool)
add_executable(example02 example02.cpp)
target_link_libraries(example02 influxdblptool)