#include "doctest.h"
#include "influxdblptool/validators.h"
#include <vector>
#include <algorithm>


using namespace influxdblptool;
using namespace influxdblptool::validators;

const int KB = 1024;


TEST_SUITE("validators") {
    TEST_CASE("throw_when_measurement_invalid")
    {
        auto fut=&throw_when_measurement_invalid;
        SUBCASE("invalid input") {
            SUBCASE("# at start of string throws validator_exception(\"Input must not start with hashtags.\")") {
                CHECK_THROWS_WITH_AS(fut("#something"), "Input must not start with hashtags.", validator_exception);
            }
            SUBCASE("_ at start of string throws validator_exception(\"Input must not start with underscore.\")") {
                CHECK_THROWS_WITH_AS(fut("_something"), "Input must not start with underscore.", validator_exception);
            }
            SUBCASE("empty string throws validator_exception(\"Input must not start with hashtags.\")") {
                CHECK_THROWS_WITH_AS(fut(""), "Input must not be empty.", validator_exception);
            }
            SUBCASE("string with newline character throws validator_exception(\"Input must not contain new line character '\\\\n'\")") {
                CHECK_THROWS_WITH_AS(fut("some\nthing"), "Input must not contain new line character '\\n'", validator_exception);
            }
            SUBCASE("string case insensitive compares to time throws validator_exception(\"Input must not be equal to `time'\")") {
                CHECK_THROWS_WITH_AS(fut("tImE"), "Input must not be equal to `time'", validator_exception);
            }
            SUBCASE("string exceeding 64KB throws validator_exception(\"Input must be <64KB\")") {
                std::string s;
                s.resize(64*KB);
                fill(begin(s),end(s),' ');
                CHECK_THROWS_WITH_AS(fut(s), "Input must be <64KB", validator_exception);
            }
        }
        SUBCASE("valid input") {
            SUBCASE("The string \"valid_#input_time\" does not throw") {
                CHECK_NOTHROW(fut("valid_#input_time"));
            }
            SUBCASE("string of 64KB-1 does not throw") {
                std::string s;
                s.resize(64*KB-1);
                fill(begin(s),end(s),' ');
                CHECK_NOTHROW(fut(s));
            }
        }
    }
    TEST_CASE("throw_when_tag_key_invalid")
    {
        auto fut=&throw_when_tag_key_invalid;
        SUBCASE("invalid input") {

            SUBCASE("_ at start of string throws validator_exception(\"Input must not start with underscore.\")") {
                CHECK_THROWS_WITH_AS(fut("_something"), "Input must not start with underscore.", validator_exception);
            }
            SUBCASE("empty string throws validator_exception(\"Input must not start with hashtags.\")") {
                CHECK_THROWS_WITH_AS(fut(""), "Input must not be empty.", validator_exception);
            }
            SUBCASE("string with newline character throws validator_exception(\"Input must not contain new line character '\\\\n'\")") {
                CHECK_THROWS_WITH_AS(fut("some\nthing"), "Input must not contain new line character '\\n'", validator_exception);
            }
            SUBCASE("string case insensitive compares to time throws validator_exception(\"Input must not be equal to `time'\")") {
                CHECK_THROWS_WITH_AS(fut("tImE"), "Input must not be equal to `time'", validator_exception);
            }
            SUBCASE("string exceeding 64KB throws validator_exception(\"Input must be <64KB\")") {
                std::string s;
                s.resize(64*KB);
                fill(begin(s),end(s),' ');
                CHECK_THROWS_WITH_AS(fut(s), "Input must be <64KB", validator_exception);
            }
        }
        SUBCASE("valid input") {
            SUBCASE("# at start of string does not throw") {
                CHECK_NOTHROW(fut("#something"));
            }
            SUBCASE("The string \"valid_#input_time\" does not throw") {
                CHECK_NOTHROW(fut("valid_#input_time"));
            }
            SUBCASE("string of 64KB-1 does not throw") {
                std::string s;
                s.resize(64*KB-1);
                fill(begin(s),end(s),' ');
                CHECK_NOTHROW(fut(s));
            }
        }
    }
    TEST_CASE("throw_when_field_key_invalid")
    {
        auto fut=&throw_when_field_key_invalid;
        SUBCASE("invalid input") {

            SUBCASE("_ at start of string throws validator_exception(\"Input must not start with underscore.\")") {
                CHECK_THROWS_WITH_AS(fut("_something"), "Input must not start with underscore.", validator_exception);
            }
            SUBCASE("empty string throws validator_exception(\"Input must not start with hashtags.\")") {
                CHECK_THROWS_WITH_AS(fut(""), "Input must not be empty.", validator_exception);
            }
            SUBCASE("string with newline character throws validator_exception(\"Input must not contain new line character '\\\\n'\")") {
                CHECK_THROWS_WITH_AS(fut("some\nthing"), "Input must not contain new line character '\\n'", validator_exception);
            }
            SUBCASE("string case insensitive compares to time throws validator_exception(\"Input must not be equal to `time'\")") {
                CHECK_THROWS_WITH_AS(fut("tImE"), "Input must not be equal to `time'", validator_exception);
            }
            SUBCASE("string exceeding 64KB throws validator_exception(\"Input must be <64KB\")") {
                std::string s;
                s.resize(64*KB);
                fill(begin(s),end(s),' ');
                CHECK_THROWS_WITH_AS(fut(s), "Input must be <64KB", validator_exception);
            }
        }
        SUBCASE("valid input") {
            SUBCASE("# at start of string does not throw") {
                CHECK_NOTHROW(fut("#something"));
            }
            SUBCASE("The string \"valid_#input_time\" does not throw") {
                CHECK_NOTHROW(fut("valid_#input_time"));
            }
            SUBCASE("string of 64KB-1 does not throw") {
                std::string s;
                s.resize(64*KB-1);
                fill(begin(s),end(s),' ');
                CHECK_NOTHROW(fut(s));
            }
        }
    }
    TEST_CASE("throw_when_tag_value_invalid")
    {
        auto fut=&throw_when_tag_value_invalid;
        SUBCASE("invalid input") {
            SUBCASE("string with newline character throws validator_exception(\"Input must not contain new line character '\\\\n'\")") {
                CHECK_THROWS_WITH_AS(fut("some\nthing"), "Input must not contain new line character '\\n'", validator_exception);
            }
            SUBCASE("string exceeding 64KB throws validator_exception(\"Input must be <64KB\")") {
                std::string s;
                s.resize(64*KB);
                fill(begin(s),end(s),' ');
                CHECK_THROWS_WITH_AS(fut(s), "Input must be <64KB", validator_exception);
            }
        }
        SUBCASE("valid input") {
            SUBCASE("string case insensitive compares to time does not throw") {
                CHECK_NOTHROW(fut("tImE"));
            }
            SUBCASE("_ at start of string does not throw") {
                CHECK_NOTHROW(fut("_something"));
            }
            SUBCASE("empty string does not throw") {
                CHECK_NOTHROW(fut(""));
            }
            SUBCASE("# at start of string does not throw") {
                CHECK_NOTHROW(fut("#something"));
            }
            SUBCASE("The string \"valid_#input_time\" does not throw") {
                CHECK_NOTHROW(fut("valid_#input_time"));
            }
            SUBCASE("string of 64KB-1 does not throw") {
                std::string s;
                s.resize(64*KB-1);
                fill(begin(s),end(s),' ');
                CHECK_NOTHROW(fut(s));
            }
        }
    }
    TEST_CASE("throw_when_field_value_invalid")
    {
        auto fut= &throw_when_field_string_value_invalid;
        SUBCASE("invalid input") {
            SUBCASE("string with newline character throws validator_exception(\"Input must not contain new line character '\\\\n'\")") {
                CHECK_THROWS_WITH_AS(fut("some\nthing"), "Input must not contain new line character '\\n'", validator_exception);
            }
            SUBCASE("string exceeding 64KB throws validator_exception(\"Input must be <64KB\")") {
                std::string s;
                s.resize(64*KB);
                fill(begin(s),end(s),' ');
                CHECK_THROWS_WITH_AS(fut(s), "Input must be <64KB", validator_exception);
            }
        }
        SUBCASE("valid input") {
            SUBCASE("string case insensitive compares to time does not throw") {
                CHECK_NOTHROW(fut("tImE"));
            }
            SUBCASE("_ at start of string does not throw") {
                CHECK_NOTHROW(fut("_something"));
            }
            SUBCASE("empty string does not throw") {
                CHECK_NOTHROW(fut(""));
            }
            SUBCASE("# at start of string does not throw") {
                CHECK_NOTHROW(fut("#something"));
            }
            SUBCASE("The string \"valid_#input_time\" does not throw") {
                CHECK_NOTHROW(fut("valid_#input_time"));
            }
            SUBCASE("string of 64KB-1 does not throw") {
                std::string s;
                s.resize(64*KB-1);
                fill(begin(s),end(s),' ');
                CHECK_NOTHROW(fut(s));
            }
        }
    }
}

