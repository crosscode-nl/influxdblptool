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

TEST(EscaperTests,EscaperWorksCorrecty)
{
    influxdblptool::escaper<'o','a','c'> escaper;
    ASSERT_EQ("\\c\\a\\c\\a\\o test"s,escaper.escape("cacao test"s));
}

TEST(EscaperTests,MeasurementEscaperEscapesCommaAndSpaceOnly)
{
    influxdblptool::MeasurementEscaper escaper;
    ASSERT_EQ("\\,\\ \"\\=abc"s,escaper.escape(", \"\\=abc"s));
}

TEST(EscaperTests,TagKeyEscaperEscapesCommaEqualsSignAndSpaceOnly)
{
    influxdblptool::TagKeyEscaper escaper;
    ASSERT_EQ("\\,\\ \"\\\\=abc"s,escaper.escape(", \"\\=abc"s));
}

TEST(EscaperTests,TagValueEscaperEscapesCommaEqualsSignAndSpaceOnly)
{
    influxdblptool::TagValueEscaper escaper;
    ASSERT_EQ("\\,\\ \"\\\\=abc"s,escaper.escape(", \"\\=abc"s));
}

TEST(EscaperTests,FieldKeyEscaperEscapesCommaEqualsSignAndSpaceOnly)
{
    influxdblptool::FieldKeyEscaper escaper;
    ASSERT_EQ("\\,\\ \"\\\\=abc"s,escaper.escape(", \"\\=abc"s));
}

TEST(EscaperTests,FieldValueEscaperEscapesDoubleQuoteAndBackslashOnly)
{
    influxdblptool::FieldValueEscaper escaper;
    ASSERT_EQ(", \\\"\\\\=abc"s,escaper.escape(", \"\\=abc"s));
}

