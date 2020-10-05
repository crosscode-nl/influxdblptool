cmake_minimum_required(VERSION 3.8.2)
project(benchmarks)

set(CMAKE_CXX_STANDARD 17)

include(cmake/googlebenchmark.cmake)

file(GLOB BENCHMARKS_SRC "src/*.cpp")

add_executable(benchmarks ${BENCHMARKS_SRC})
target_link_libraries(benchmarks ${3RDPARTY_LIBRARIES} influxdblptool)
