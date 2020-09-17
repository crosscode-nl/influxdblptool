cmake_minimum_required(VERSION 3.17)
project(influxdblptool)

include(cmake/buildsetup.cmake)

list(APPEND INFLUXDBLPTOOL_HEADERS
        include/influxdblptool/abstractions/iescape.h
        include/influxdblptool/abstractions/iserializable.h
        include/influxdblptool/abstractions/ikey.h
        include/influxdblptool/abstractions/ivalidator.h
        include/influxdblptool/escapers/escaper.h
        include/influxdblptool/validators/notemptyvalidator.h
        include/influxdblptool/validators/notstartingwithunderscorevalidator.h
        include/influxdblptool/validators/notequaltostringvalidator.h
        )

list(APPEND INFLUXDBLPTOOL_SRC
        src/influxdblptool/abstractions/iserializable.cpp
        src/influxdblptool/validators/notemptyvalidator.cpp
        src/influxdblptool/validators/notstartingwithunderscorevalidator.cpp
        )

add_library(influxdblptool ${INFLUXDBPLTOOL_HEADERS} ${INFLUXDBLPTOOL_SRC})
target_include_directories(influxdblptool PUBLIC include)
add_subdirectory(tests)