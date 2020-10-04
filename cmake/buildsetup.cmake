option(INFLUXDBLPTOOL_ENABLE_CODE_COVERAGE "Set this to ON to build unit tests")

add_compile_options("$<$<CONFIG:RELEASE>:-W;-Wall;-Werror;-Wshadow;-Wextra;-Wpedantic;-pedantic-errors>")
if (INFLUXDBLPTOOL_ENABLE_CODE_COVERAGE)
    add_compile_options("$<$<CONFIG:DEBUG>:-W;-Wall;-Werror;-Wshadow;-Wextra;-Wpedantic;-pedantic-errors;-fprofile-arcs;-ftest-coverage>")
    add_link_options("$<$<CONFIG:DEBUG>:-lgcov;-coverage>")
else()
    add_compile_options("$<$<CONFIG:DEBUG>:-W;-Wall;-Werror;-Wshadow;-Wextra;-Wpedantic;-pedantic-errors;>")
endif()

set(CMAKE_CXX_STANDARD 17)
