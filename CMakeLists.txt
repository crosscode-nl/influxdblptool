cmake_minimum_required(VERSION 3.17)

project(influxdblptool
        VERSION 0.10.0
        DESCRIPTION "InfluxDb Line Protocol Tool"
        LANGUAGES C CXX)

include(cmake/buildsetup.cmake)
include(cmake/doxygen.cmake)

configure_file(src/influxdblptool/version.cpp.in src/influxdblptool/version.cpp)

list(APPEND INFLUXDBLPTOOL_HEADERS
        include/influxdblptool.h
        include/influxdblptool/escapers.h
        include/influxdblptool/validators.h
        include/influxdblptool/string_types.h
        include/influxdblptool/field_value.h
        include/influxdblptool/collections.h
        include/influxdblptool/version.h
        include/influxdblptool/point.h
        include/influxdblptool/serializers.h
        )

list(APPEND INFLUXDBLPTOOL_SRC
        src/influxdblptool/validators.cpp
        src/influxdblptool/escapers.cpp
        src/influxdblptool/field_value.cpp
        src/influxdblptool/serializers.cpp
        src/influxdblptool/point.cpp
        ${CMAKE_BINARY_DIR}/src/influxdblptool/version.cpp
        )

add_library(influxdblptool ${INFLUXDBPLTOOL_HEADERS} ${INFLUXDBLPTOOL_SRC})

set_target_properties(influxdblptool PROPERTIES PUBLIC_HEADER "include/influxdblptool.h")

install(TARGETS influxdblptool
        EXPORT influxdblptool
        PUBLIC_HEADER
        LIBRARY)

install(DIRECTORY include/influxdblptool DESTINATION ${CMAKE_INSTALL_PREFIX}/include/influxdblptool
        FILES_MATCHING PATTERN "*.h")

target_include_directories(influxdblptool PUBLIC include)

add_subdirectory(tests)
add_subdirectory(examples)
add_subdirectory(benchmarks)



