cmake_minimum_required(VERSION 3.17)
project(influxdblptool)

include(cmake/buildsetup.cmake)

list(APPEND INFLUXDBLPTOOL_HEADERS
        include/influxdblptool/escapers.h
        include/influxdblptool/validators.h
        include/influxdblptool/string_types.h
        include/influxdblptool/field_value.h
        include/influxdblptool/collections.h
        include/influxdblptool/point.h
        include/influxdblptool/serializers.h
        )

list(APPEND INFLUXDBLPTOOL_SRC
        src/influxdblptool/validators.cpp
        src/influxdblptool/escapers.cpp
        src/influxdblptool/field_value.cpp
        src/influxdblptool/serializers.cpp
        )

add_library(influxdblptool ${INFLUXDBPLTOOL_HEADERS} ${INFLUXDBLPTOOL_SRC} src/influxdblptool/point.cpp)
target_include_directories(influxdblptool PUBLIC include)
add_subdirectory(tests)