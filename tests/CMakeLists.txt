cmake_minimum_required(VERSION 3.15)
project(influxdblptooltests
        VERSION 0.0.1
        DESCRIPTION "InfluxDb Line Protocol Tool Tests"
        LANGUAGES C CXX
        )

include(cmake/googletest.cmake)

list(APPEND SRC
        src/escape_tests.cpp
        src/noteequaltostringvalidator_tests.cpp
)

list(APPEND INCLUDE
)


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(influxdblptooltests ${SRC} ${INCLUDE} )
target_link_libraries(influxdblptooltests influxdblptool ${3RDPARTY_LIBRARIES})
target_include_directories(influxdblptooltests PUBLIC include)

gtest_discover_tests(influxdblptooltests)

