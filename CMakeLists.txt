cmake_minimum_required(VERSION 3.17)
project(influxdblptool)

include(cmake/buildsetup.cmake)

list(APPEND INFLUXDBLPTOOL_HEADERS
        include/influxdblptool/abstractions/serializable.h
        include/influxdblptool/escapers.h
        include/influxdblptool/validators.h
        )

list(APPEND INFLUXDBLPTOOL_SRC
        src/influxdblptool/abstractions/serializable.cpp
        src/influxdblptool/validators.cpp
        src/influxdblptool/escapers.cpp
        )

add_library(influxdblptool ${INFLUXDBPLTOOL_HEADERS} ${INFLUXDBLPTOOL_SRC} src/influxdblptool/validatedstring.cpp include/influxdblptool/validatedstring.h)
target_include_directories(influxdblptool PUBLIC include)
add_subdirectory(tests)