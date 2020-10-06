cmake_minimum_required(VERSION 3.8.2)

project(influxdblptool
        VERSION 0.18.0
        #DESCRIPTION "InfluxDb Line Protocol Tool"
        LANGUAGES C CXX)

include(cmake/buildsetup.cmake)

option(BUILD_INFLUXDBLPTOOL_TESTS "Set this to ON to build unit tests" ON)
option(BUILD_INFLUXDBLPTOOL_DOCS "Set this to ON to build docs")
option(BUILD_INFLUXDBLPTOOL_EXAMPLES "Set this to ON to build examples")
option(BUILD_INFLUXDBLPTOOL_BENCHMARKS "Set this to ON to build benchmarks")

if (BUILD_INFLUXDBLPTOOL_DOCS)
    include(cmake/doxygen.cmake)
endif()

configure_file(src/influxdblptool/version.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/src/influxdblptool/version.cpp)

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
        ${CMAKE_CURRENT_BINARY_DIR}/src/influxdblptool/version.cpp
        )

add_library(influxdblptool ${INFLUXDBPLTOOL_HEADERS} ${INFLUXDBLPTOOL_SRC})
target_compile_features(influxdblptool PUBLIC cxx_std_17)

set_target_properties(influxdblptool PROPERTIES PUBLIC_HEADER "include/influxdblptool.h")

target_include_directories(influxdblptool INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
target_include_directories(influxdblptool PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

install(DIRECTORY include/influxdblptool DESTINATION ${CMAKE_INSTALL_PREFIX}/include/influxdblptool
        FILES_MATCHING PATTERN "*.h")

install(TARGETS influxdblptool
        EXPORT InfluxDBLPToolTargets
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)

include(CMakePackageConfigHelpers)

install(EXPORT InfluxDBLPToolTargets DESTINATION lib/cmake/InfluxDBLPTool)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/InfluxDBLPTool/InfluxDBLPToolConfigVersion.cmake"
        VERSION ${Upstream_VERSION}
        COMPATIBILITY AnyNewerVersion
)

install(
        FILES
        cmake/InfluxDBLPToolConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/InfluxDBLPTool/InfluxDBLPToolConfigVersion.cmake"
        DESTINATION
        lib/cmake/InfluxDBLPTool
        COMPONENT
        Devel
)

if (BUILD_INFLUXDBLPTOOL_EXAMPLES)
    add_subdirectory(examples)
endif()

if (BUILD_INFLUXDBLPTOOL_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

if (BUILD_INFLUXDBLPTOOL_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
