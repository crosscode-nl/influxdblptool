#include "gtest/gtest.h"
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

TEST(escapers,escape_measurement_escapes_comma_and_space_only)
{
    ASSERT_EQ("\\,\\ \"\\=abc"s,::escape_measurement(", \"\\=abc"s));
}

TEST(escapers,escape_tag_key_escapes_equal_sign_comma_and_space_only)
{
    ASSERT_EQ("\\,\\ \"\\\\=abc"s,escape_tag_key(", \"\\=abc"s));
}

TEST(escapers,escape_tag_value_escapes_equal_sign_comma_and_space_only)
{
    ASSERT_EQ("\\,\\ \"\\\\=abc"s,escape_tag_value(", \"\\=abc"s));
}

TEST(escapers,escape_field_key_escapes_equal_sign_comma_and_space_only)
{
    ASSERT_EQ("\\,\\ \"\\\\=abc"s,escape_tag_key(", \"\\=abc"s));
}

TEST(escapers,escape_field_value_escapes_double_quote_and_backslash_only)
{
    ASSERT_EQ(", \\\"\\\\=abc"s,escape_field_value(", \"\\=abc"s));
}


