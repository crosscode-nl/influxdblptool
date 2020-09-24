cmake_minimum_required(VERSION 3.15)
project(influxdblptooltests
        VERSION 0.0.1
        DESCRIPTION "InfluxDb Line Protocol Tool Tests"
        LANGUAGES C CXX
        )

list(APPEND TEST_SRC
        main.cpp
        escapers_tests.cpp
        validators_tests.cpp
        field_value_tests.cpp
        string_types_tests.cpp
        collections_tests.cpp
        )

list(APPEND TEST_INCLUDE
        )


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(influxdblptooltests ${TEST_SRC} ${TEST_INCLUDE})
target_link_libraries(influxdblptooltests influxdblptool ${3RDPARTY_LIBRARIES})
target_include_directories(influxdblptooltests PUBLIC include)



