add_compile_options("$<$<CONFIG:RELEASE>:-W;-Wall;-Werror;-Wshadow;-Wextra;-Wpedantic;-pedantic-errors>")
add_compile_options("$<$<CONFIG:DEBUG>:-W;-Wall;-Werror;-Wshadow;-Wextra;-Wpedantic;-pedantic-errors;-fprofile-arcs;-ftest-coverage>")
add_link_options("$<$<CONFIG:DEBUG>:-lgcov;-coverage>")

set(CMAKE_CXX_STANDARD 17)
