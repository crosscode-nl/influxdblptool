#include "gtest/gtest.h"
#include "influxdblptool/escapers/escaper.h"

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

TEST(Escaper,WorksCorrecty)
{
    influxdblptool::escaper<'o','a','c'> escaper;
    ASSERT_EQ("\\c\\a\\c\\a\\o test"s,escaper.escape("cacao test"s));
}

TEST(MeasurementEscaper,EscapesCommaAndSpaceOnly)
{
    influxdblptool::MeasurementEscaper escaper;
    ASSERT_EQ("\\,\\ \"\\=abc"s,escaper.escape(", \"\\=abc"s));
}

TEST(TagKeyEscaper,EscapesCommaEqualsSignAndSpaceOnly)
{
    influxdblptool::TagKeyEscaper escaper;
    ASSERT_EQ("\\,\\ \"\\\\=abc"s,escaper.escape(", \"\\=abc"s));
}

TEST(TagValueEscaper,EscapesCommaEqualsSignAndSpaceOnly)
{
    influxdblptool::TagValueEscaper escaper;
    ASSERT_EQ("\\,\\ \"\\\\=abc"s,escaper.escape(", \"\\=abc"s));
}

TEST(FieldKeyEscaper,EscapesCommaEqualsSignAndSpaceOnly)
{
    influxdblptool::FieldKeyEscaper escaper;
    ASSERT_EQ("\\,\\ \"\\\\=abc"s,escaper.escape(", \"\\=abc"s));
}

TEST(FieldValueEscaper,EscapesDoubleQuoteAndBackslashOnly)
{
    influxdblptool::FieldValueEscaper escaper;
    ASSERT_EQ(", \\\"\\\\=abc"s,escaper.escape(", \"\\=abc"s));
}

