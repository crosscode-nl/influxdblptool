cmake_minimum_required(VERSION 3.8.2)
project(benchmarks)

include(cmake/googlebenchmark.cmake)

file(GLOB BENCHMARKS_SRC "src/*.cpp")

add_executable(benchmarks ${BENCHMARKS_SRC})
target_link_libraries(benchmarks ${3RDPARTY_LIBRARIES} influxdblptool)
target_compile_features(benchmarks PUBLIC cxx_std_17)

