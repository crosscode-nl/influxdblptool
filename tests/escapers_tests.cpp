#include "doctest.h"
#include "influxdblptool/escapers.h"
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
    TEST_CASE("escape_measurement escapes: Comma, Space")
    {
        CHECK_EQ("\\,\\ \"\\=abc"s,escape_measurement(", \"\\=abc"s));
    }

    TEST_CASE("escape_tag_key escapes: Comma, Equals Sign, Space")
    {
        CHECK_EQ("\\,\\ \"\\\\=abc"s,escape_tag_key(", \"\\=abc"s));
    }

    TEST_CASE("escape_tag_value escapes: Comma, Equals Sign, Space")
    {
        CHECK_EQ("\\,\\ \"\\\\=abc"s,escape_tag_value(", \"\\=abc"s));
    }

    TEST_CASE("escape_field_key escapes: Comma, Equals Sign, Space")
    {
        CHECK_EQ("\\,\\ \"\\\\=abc"s,escape_field_key(", \"\\=abc"s));
    }

    TEST_CASE("escape_field_value escapes: Double quote, Backslash")
    {
        CHECK_EQ(", \\\"\\\\=abc"s, escape_field_string_value(", \"\\=abc"s));
    }
}

