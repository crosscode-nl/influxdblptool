# Download and unpack googletest at configure time
SET(BENCHMARK_ENABLE_GTEST_TESTS OFF)
SET(BENCHMARK_ENABLE_TESTING OFF)
SET(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)

configure_file(cmake/googlebenchmark.cmake.in googlebenchmark-download/CMakeLists.txt)

execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark-download"
        )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark-download"
        )

add_subdirectory("${CMAKE_BINARY_DIR}/googlebenchmark-src"
        "${CMAKE_BINARY_DIR}/googlebenchmark-build")

LIST(APPEND 3RDPARTY_LIBRARIES benchmark)