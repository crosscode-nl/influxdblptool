cmake_minimum_required(VERSION 3.17)

project(examples LANGUAGES C CXX)

file(GLOB EXAMPLES_SRC "example??.cpp")

foreach(EXAMPLE_CPP ${EXAMPLES_SRC})
    get_filename_component(EXAMPLE ${EXAMPLE_CPP} NAME_WE)
    message("Adding target ${EXAMPLE} with source file ${EXAMPLE_CPP}")
    add_executable(${EXAMPLE} ${EXAMPLE_CPP})
    target_link_libraries(${EXAMPLE} influxdblptool)
endforeach()
