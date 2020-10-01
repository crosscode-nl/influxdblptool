cmake_minimum_required(VERSION 3.17)
project(benchmarks)

set(CMAKE_CXX_STANDARD 17)

include(cmake/googlebenchmark.cmake)

SET(SRC
        src/stack_container_bm.cpp
)

add_executable(benchmarks ${SRC})
target_link_libraries(benchmarks ${3RDPARTY_LIBRARIES})
