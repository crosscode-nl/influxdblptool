cmake_minimum_required(VERSION 3.17)
project(influxdblptool)

include(cmake/buildsetup.cmake)

list(APPEND INFLUXDBLPTOOL_HEADERS
        include/influxdblptool/escapers.h
        include/influxdblptool/validators.h
        include/influxdblptool/string_types.h
        include/influxdblptool/field_value.h
        include/influxdblptool/collections.h
        )

list(APPEND INFLUXDBLPTOOL_SRC
        src/influxdblptool/validators.cpp
        src/influxdblptool/escapers.cpp
        src/influxdblptool/field_value.cpp
        )

add_library(influxdblptool ${INFLUXDBPLTOOL_HEADERS} ${INFLUXDBLPTOOL_SRC} src/influxdblptool/point.cpp include/influxdblptool/point.h src/influxdblptool/serializers.cpp include/influxdblptool/serializers.h)
target_include_directories(influxdblptool PUBLIC include)
add_subdirectory(tests)