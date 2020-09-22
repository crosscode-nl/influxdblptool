#include "doctest.h"
#include "influxdblptool/string_types.h"

using namespace influxdblptool;
using namespace std::literals;

const int KB = 1024;

TEST_SUITE("string_types_tests") {
  TEST_CASE("measurement")
  {
        SUBCASE("invalid input") {
            SUBCASE("# at start of string throws validator_exception(\"Input must not start with hashtags.\")") {
                CHECK_THROWS_WITH_AS(measurement{"#something"}, "Input must not start with hashtags.", validator_exception);
            }
            SUBCASE("_ at start of string throws validator_exception(\"Input must not start with underscore.\")") {
                CHECK_THROWS_WITH_AS(measurement{"_something"}, "Input must not start with underscore.", validator_exception);
            }
            SUBCASE("empty string throws validator_exception(\"Input must not start with hashtags.\")") {
                CHECK_THROWS_WITH_AS(measurement{""}, "Input must not be empty.", validator_exception);
            }
            SUBCASE("string with newline character throws validator_exception(\"Input must not contain new line character '\\\\n'\")") {
                CHECK_THROWS_WITH_AS(measurement{"some\nthing"}, "Input must not contain new line character '\\n'", validator_exception);
            }
            SUBCASE("string case insensitive compares to time throws validator_exception(\"Input must not be equal to `time'\")") {
                CHECK_THROWS_WITH_AS(measurement{"tImE"}, "Input must not be equal to `time'", validator_exception);
            }
            SUBCASE("string exceeding 64KB throws validator_exception(\"Input must be <64KB\")") {
                std::string s;
                s.resize(64*KB);
                fill(begin(s),end(s),' ');
                CHECK_THROWS_WITH_AS(measurement{s}, "Input must be <64KB", validator_exception);
            }
        }
        SUBCASE("valid input") {
            SUBCASE("The string \"valid_#input_time\" does not throw") {
                CHECK_NOTHROW(measurement{"valid_#input_time"});
            }
            SUBCASE("string of 64KB-1 does not throw") {
                std::string s;
                s.resize(64*KB-1);
                fill(begin(s),end(s),' ');
                CHECK_NOTHROW(measurement{s});
            }
        }
        SUBCASE("assigns and serializes correctly") {
            std::stringstream s;
            measurement m{"overwrite"};
            m = measurement{", \"\\=abc"s};
            s << m;
            CHECK_EQ("\\,\\ \"\\=abc"s,s.str());
        }
    }
    TEST_CASE("tag_key")
    {
        SUBCASE("invalid input") {

            SUBCASE("_ at start of string throws validator_exception(\"Input must not start with underscore.\")") {
                CHECK_THROWS_WITH_AS(tag_key{"_something"}, "Input must not start with underscore.", validator_exception);
            }
            SUBCASE("empty string throws validator_exception(\"Input must not start with hashtags.\")") {
                CHECK_THROWS_WITH_AS(tag_key{""}, "Input must not be empty.", validator_exception);
            }
            SUBCASE("string with newline character throws validator_exception(\"Input must not contain new line character '\\\\n'\")") {
                CHECK_THROWS_WITH_AS(tag_key{"some\nthing"}, "Input must not contain new line character '\\n'", validator_exception);
            }
            SUBCASE("string case insensitive compares to time throws validator_exception(\"Input must not be equal to `time'\")") {
                CHECK_THROWS_WITH_AS(tag_key{"tImE"}, "Input must not be equal to `time'", validator_exception);
            }
            SUBCASE("string exceeding 64KB throws validator_exception(\"Input must be <64KB\")") {
                std::string s;
                s.resize(64*KB);
                fill(begin(s),end(s),' ');
                CHECK_THROWS_WITH_AS(tag_key{s}, "Input must be <64KB", validator_exception);
            }
        }
        SUBCASE("valid input") {
            SUBCASE("# at start of string does not throw") {
                CHECK_NOTHROW(tag_key{"#something"});
            }
            SUBCASE("The string \"valid_#input_time\" does not throw") {
                CHECK_NOTHROW(tag_key{"valid_#input_time"});
            }
            SUBCASE("string of 64KB-1 does not throw") {
                std::string s;
                s.resize(64*KB-1);
                fill(begin(s),end(s),' ');
                CHECK_NOTHROW(tag_key{s});
            }
        }
        SUBCASE("assigns and serializes correctly") {
            std::stringstream s;
            tag_key t{"overwrite"};
            t = tag_key{", \"\\=abc"s};
            s << t;
            CHECK_EQ("\\,\\ \"\\\\=abc"s,s.str());
        }
    }
    TEST_CASE("field_key")
    {       
        SUBCASE("invalid input") {

            SUBCASE("_ at start of string throws validator_exception(\"Input must not start with underscore.\")") {
                CHECK_THROWS_WITH_AS(field_key{"_something"}, "Input must not start with underscore.", validator_exception);
            }
            SUBCASE("empty string throws validator_exception(\"Input must not start with hashtags.\")") {
                CHECK_THROWS_WITH_AS(field_key{""}, "Input must not be empty.", validator_exception);
            }
            SUBCASE("string with newline character throws validator_exception(\"Input must not contain new line character '\\\\n'\")") {
                CHECK_THROWS_WITH_AS(field_key{"some\nthing"}, "Input must not contain new line character '\\n'", validator_exception);
            }
            SUBCASE("string case insensitive compares to time throws validator_exception(\"Input must not be equal to `time'\")") {
                CHECK_THROWS_WITH_AS(field_key{"tImE"}, "Input must not be equal to `time'", validator_exception);
            }
            SUBCASE("string exceeding 64KB throws validator_exception(\"Input must be <64KB\")") {
                std::string s;
                s.resize(64*KB);
                fill(begin(s),end(s),' ');
                CHECK_THROWS_WITH_AS(field_key{s}, "Input must be <64KB", validator_exception);
            }
        }
        SUBCASE("valid input") {
            SUBCASE("# at start of string does not throw") {
                CHECK_NOTHROW(field_key{"#something"});
            }
            SUBCASE("The string \"valid_#input_time\" does not throw") {
                CHECK_NOTHROW(field_key{"valid_#input_time"});
            }
            SUBCASE("string of 64KB-1 does not throw") {
                std::string s;
                s.resize(64*KB-1);
                fill(begin(s),end(s),' ');
                CHECK_NOTHROW(field_key{s});
            }
        }
        SUBCASE("assigns and serializes correctly") {
            std::stringstream s;
            field_key f{"overwrite"};
            f = field_key{", \"\\=abc"s};
            s << f;
            CHECK_EQ("\\,\\ \"\\\\=abc"s,s.str());
        }
    }
    TEST_CASE("tag_value")
    {
        SUBCASE("invalid input") {
            SUBCASE("string with newline character throws validator_exception(\"Input must not contain new line character '\\\\n'\")") {
                CHECK_THROWS_WITH_AS(tag_value{"some\nthing"}, "Input must not contain new line character '\\n'", validator_exception);
            }
            SUBCASE("string exceeding 64KB throws validator_exception(\"Input must be <64KB\")") {
                std::string s;
                s.resize(64*KB);
                fill(begin(s),end(s),' ');
                CHECK_THROWS_WITH_AS(tag_value{s}, "Input must be <64KB", validator_exception);
            }
        }
        SUBCASE("valid input") {
            SUBCASE("string case insensitive compares to time does not throw") {
                CHECK_NOTHROW(tag_value{"tImE"});
            }
            SUBCASE("_ at start of string does not throw") {
                CHECK_NOTHROW(tag_value{"_something"});
            }
            SUBCASE("empty string does not throw") {
                CHECK_NOTHROW(tag_value{""});
            }
            SUBCASE("# at start of string does not throw") {
                CHECK_NOTHROW(tag_value{"#something"});
            }
            SUBCASE("The string \"valid_#input_time\" does not throw") {
                CHECK_NOTHROW(tag_value{"valid_#input_time"});
            }
            SUBCASE("string of 64KB-1 does not throw") {
                std::string s;
                s.resize(64*KB-1);
                fill(begin(s),end(s),' ');
                CHECK_NOTHROW(tag_value{s});
            }
        }
        SUBCASE("assigns and serializes correctly") {
            std::stringstream s;
            tag_value t{"overwrite"};
            t = tag_value{", \"\\=abc"s};
            s << t;
            CHECK_EQ("\\,\\ \"\\\\=abc"s,s.str());
        }
    }
    TEST_CASE("field_value")
    {
        SUBCASE("invalid input") {
            SUBCASE("string with newline character throws validator_exception(\"Input must not contain new line character '\\\\n'\")") {
                CHECK_THROWS_WITH_AS(field_string_value{"some\nthing"}, "Input must not contain new line character '\\n'", validator_exception);
            }
            SUBCASE("string exceeding 64KB throws validator_exception(\"Input must be <64KB\")") {
                std::string s;
                s.resize(64*KB);
                fill(begin(s),end(s),' ');
                CHECK_THROWS_WITH_AS(field_string_value{s}, "Input must be <64KB", validator_exception);
            }
        }
        SUBCASE("valid input") {
            SUBCASE("string case insensitive compares to time does not throw") {
                CHECK_NOTHROW(field_string_value{"tImE"});
            }
            SUBCASE("_ at start of string does not throw") {
                CHECK_NOTHROW(field_string_value{"_something"});
            }
            SUBCASE("empty string does not throw") {
                CHECK_NOTHROW(field_string_value{""});
            }
            SUBCASE("# at start of string does not throw") {
                CHECK_NOTHROW(field_string_value{"#something"});
            }
            SUBCASE("The string \"valid_#input_time\" does not throw") {
                CHECK_NOTHROW(field_string_value{"valid_#input_time"});
            }
            SUBCASE("string of 64KB-1 does not throw") {
                std::string s;
                s.resize(64*KB-1);
                fill(begin(s),end(s),' ');
                CHECK_NOTHROW(field_string_value{s});
            }
        }
        SUBCASE("assigns and serializes correctly") {
            std::stringstream s;
            field_string_value f{"overwrite"};
            f = field_string_value{", \"\\=abc"s};
            s << f;
            CHECK_EQ(", \\\"\\\\=abc"s,s.str());
        }
    }
}