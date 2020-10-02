#include "doctest.h"
#include "influxdblptool.h"
using namespace std::literals;

/*
 * Escape characters per mode:
 *
 * Measurement	= Comma, Space
 * Tag key	    = Comma, Equals Sign, Space
 * Tag value	= Comma, Equals Sign, Space
 * Field key	= Comma, Equals Sign, Space
 * Field value	= Double quote, Backslash
*/

using namespace influxdblptool::escapers;
TEST_SUITE("escapers") {
    TEST_CASE("escape_measurement_value escapes: Comma, Space")
    {
        REQUIRE("\\,\\ \"\\=abc"s==escape_measurement_value(", \"\\=abc"s));
    }

    TEST_CASE("escape_tag_key escapes: Comma, Equals Sign, Space")
    {
        REQUIRE("\\,\\ \"\\\\=abc"s==escape_tag_key(", \"\\=abc"s));
    }

    TEST_CASE("escape_tag_value escapes: Comma, Equals Sign, Space")
    {
        REQUIRE("\\,\\ \"\\\\=abc"s==escape_tag_value(", \"\\=abc"s));
    }

    TEST_CASE("escape_field_key escapes: Comma, Equals Sign, Space")
    {
        REQUIRE("\\,\\ \"\\\\=abc"s==escape_field_key(", \"\\=abc"s));
    }

    TEST_CASE("escape_field_string_value escapes: Double quote, Backslash")
    {
        REQUIRE(", \\\"\\\\=abc"s==escape_field_string_value(", \"\\=abc"s));
    }
}

