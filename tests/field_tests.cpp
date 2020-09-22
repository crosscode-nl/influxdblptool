#include "doctest.h"
#include "influxdblptool/field.h"
#include <sstream>

using namespace std::literals;
using namespace influxdblptool;

TEST_SUITE("field") {
    TEST_CASE("field_double works correctly") {
        SUBCASE("field_double accepts double") {
            CHECK_NOTHROW(field_double fd{1.0});
        }
        SUBCASE("field_double accepts float") {
            CHECK_NOTHROW(field_double fd{1.0f});
        }
        SUBCASE("field_double casts to double") {
            const double d{100.5};
            field_double fd{d};
            CHECK_EQ(d,double{fd});
        }
        SUBCASE("field_double assigns from double") {
            const double d{100.5};
            field_double fd{};
            fd = d;
            CHECK_EQ(d,double{fd});
        }
        SUBCASE("field_double assigns from float") {
            const float d{100.5};
            field_double fd{};
            fd = d;
            CHECK_EQ(d,double{fd});
        }
        SUBCASE("field_double throws when infinite double is given") {
            CHECK_THROWS_AS_MESSAGE(field_double{std::numeric_limits<double>::infinity()},validator_exception,"Infinite value not allowed.");
        }
        SUBCASE("field_double throws when infinite float is given") {
            CHECK_THROWS_AS_MESSAGE(field_double{std::numeric_limits<float>::infinity()},validator_exception,"Infinite value not allowed.");
        }
        SUBCASE("field_double throws when quiet_NaN double is given") {
            CHECK_THROWS_AS_MESSAGE(field_double{std::numeric_limits<double>::quiet_NaN()},validator_exception,"NaN value not allowed.");
        }
        SUBCASE("field_double throws when quiet_NaN float is given") {
            CHECK_THROWS_AS_MESSAGE(field_double{std::numeric_limits<float>::quiet_NaN()},validator_exception,"NaN value not allowed.");
        }
        SUBCASE("field_double throws when signaling_NaN double is given") {
            CHECK_THROWS_AS_MESSAGE(field_double{std::numeric_limits<double>::signaling_NaN()},validator_exception,"NaN value not allowed.");
        }
        SUBCASE("field_double throws when signaling_NaN float is given") {
            CHECK_THROWS_AS_MESSAGE(field_double{std::numeric_limits<float>::signaling_NaN()},validator_exception,"NaN value not allowed.");
        }
    }
    TEST_CASE("field constructs and serializes correctly") {
        SUBCASE("field accepts field_double and serializes correctly") {
            field f{field_double{100.5}};
            std::stringstream s;
            s << f;
            CHECK_EQ("100.5"s,s.str());
        }
        SUBCASE("field accepts double and serializes correctly") {
            field f{100.5};
            std::stringstream s;
            s << f;
            CHECK_EQ("100.5"s,s.str());
        }
        SUBCASE("field accepts float and serializes correctly") {
            field f{100.5f};
            std::stringstream s;
            s << f;
            CHECK_EQ("100.5"s,s.str());
        }
        SUBCASE("field accepts bool true and serializes correctly") {
            field f{true};
            std::stringstream s;
            s << f;
            CHECK_EQ("t"s,s.str());
        }
        SUBCASE("field accepts bool true and serializes correctly") {
            field f{false};
            std::stringstream s;
            s << f;
            CHECK_EQ("f"s,s.str());
        }
        SUBCASE("field accepts const char* string and serializes correctly") {
            field f{"string"};
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field accepts string_view and serializes correctly") {
            field f{"string"sv};
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field accepts string and serializes correctly") {
            field f{"string"s};
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field accepts field_string_value and serializes correctly") {
            field_string_value v{"string"s};
            field f{v};
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field accepts uint64_t and serializes correctly") {
            field f{std::numeric_limits<uint64_t>::max()};
            std::stringstream s;
            s << f;
            CHECK_EQ("18446744073709551615"s,s.str());
        }
        SUBCASE("field accepts int64_t and serializes correctly") {
            field f{std::numeric_limits<int64_t>::min()};
            std::stringstream s;
            s << f;
            CHECK_EQ("-9223372036854775808"s,s.str());
        }
        SUBCASE("field accepts uint32_t and serializes correctly") {
            field f{std::numeric_limits<uint32_t>::max()};
            std::stringstream s;
            s << f;
            CHECK_EQ("4294967295"s,s.str());
        }
        SUBCASE("field accepts int32_t and serializes correctly") {
            field f{std::numeric_limits<int32_t>::min()};
            std::stringstream s;
            s << f;
            CHECK_EQ("-2147483648"s,s.str());
        }
        SUBCASE("field accepts uint16_t and serializes correctly") {
            field f{std::numeric_limits<uint16_t>::max()};
            std::stringstream s;
            s << f;
            CHECK_EQ("65535"s,s.str());
        }
        SUBCASE("field accepts int16_t and serializes correctly") {
            field f{std::numeric_limits<int16_t>::min()};
            std::stringstream s;
            s << f;
            CHECK_EQ("-32768"s,s.str());
        }
        SUBCASE("field accepts uint8_t and serializes correctly") {
            field f{std::numeric_limits<uint8_t>::max()};
            std::stringstream s;
            s << f;
            CHECK_EQ("255"s,s.str());
        }
        SUBCASE("field accepts int8_t and serializes correctly") {
            field f{std::numeric_limits<int8_t>::min()};
            std::stringstream s;
            s << f;
            CHECK_EQ("-128"s,s.str());
        }
        SUBCASE("field accepts field by copy and serializes correctly") {
            field f2{std::numeric_limits<int8_t>::min()};
            field f{f2};
            f2 = std::numeric_limits<int8_t>::max();
            std::stringstream s;
            s << f;
            CHECK_EQ("-128"s,s.str());
        }
        SUBCASE("field accepts field by move and serializes correctly") {
            field f2{std::numeric_limits<int8_t>::min()};
            field f(std::move(f2));
            std::stringstream s;
            s << f;
            CHECK_EQ("-128"s,s.str());
        }
    }
    TEST_CASE("field assigns and serializes correctly") {
        SUBCASE("field assigns field_double and serializes correctly") {
            field f{};
            f = field_double{100.5};
            std::stringstream s;
            s << f;
            CHECK_EQ("100.5"s,s.str());
        }
        SUBCASE("field assigns double and serializes correctly") {
            field f{};
            f=100.5;
            std::stringstream s;
            s << f;
            CHECK_EQ("100.5"s,s.str());
        }
        SUBCASE("field assigns float and serializes correctly") {
            field f{};
            f=100.5f;
            std::stringstream s;
            s << f;
            CHECK_EQ("100.5"s,s.str());
        }
        SUBCASE("field assigns bool true and serializes correctly") {
            field f{};
            f=true;
            std::stringstream s;
            s << f;
            CHECK_EQ("t"s,s.str());
        }
        SUBCASE("field assigns bool true and serializes correctly") {
            field f{};
            f=false;
            std::stringstream s;
            s << f;
            CHECK_EQ("f"s,s.str());
        }
        SUBCASE("field assigns const char* string and serializes correctly") {
            field f{};
            f="string";
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field assigns string_view and serializes correctly") {
            field f{};
            f="string"sv;
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field assigns string and serializes correctly") {
            field f{};
            f="string"s;
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field assigns field_string_value and serializes correctly") {
            field_string_value v{"string"s};
            field f{};
            f=v;
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field assigns uint64_t and serializes correctly") {
            field f{};
            f=std::numeric_limits<uint64_t>::max();
            std::stringstream s;
            s << f;
            CHECK_EQ("18446744073709551615"s,s.str());
        }
        SUBCASE("field assigns int64_t and serializes correctly") {
            field f{};
            f=std::numeric_limits<int64_t>::min();
            std::stringstream s;
            s << f;
            CHECK_EQ("-9223372036854775808"s,s.str());
        }
        SUBCASE("field assigns uint32_t and serializes correctly") {
            field f{};
            f=std::numeric_limits<uint32_t>::max();
            std::stringstream s;
            s << f;
            CHECK_EQ("4294967295"s,s.str());
        }
        SUBCASE("field assigns int32_t and serializes correctly") {
            field f{};
            f=std::numeric_limits<int32_t>::min();
            std::stringstream s;
            s << f;
            CHECK_EQ("-2147483648"s,s.str());
        }
        SUBCASE("field assigns uint16_t and serializes correctly") {
            field f{};
            f=std::numeric_limits<uint16_t>::max();
            std::stringstream s;
            s << f;
            CHECK_EQ("65535"s,s.str());
        }
        SUBCASE("field assigns int16_t and serializes correctly") {
            field f{};
            f=std::numeric_limits<int16_t>::min();
            std::stringstream s;
            s << f;
            CHECK_EQ("-32768"s,s.str());
        }
        SUBCASE("field assigns uint8_t and serializes correctly") {
            field f{};
            f=std::numeric_limits<uint8_t>::max();
            std::stringstream s;
            s << f;
            CHECK_EQ("255"s,s.str());
        }
        SUBCASE("field assigns int8_t and serializes correctly") {
            field f{};
            f=std::numeric_limits<int8_t>::min();
            std::stringstream s;
            s << f;
            CHECK_EQ("-128"s,s.str());
        }
        SUBCASE("field assigns uint64_t field and serializes correctly") {
            field f2{std::numeric_limits<uint64_t>::max()};
            field f{};
            f=f2;
            std::stringstream s;
            s << f;
            CHECK_EQ("18446744073709551615"s,s.str());
        }
        SUBCASE("field assigns int64_t field and serializes correctly") {
            field f2{std::numeric_limits<int64_t>::min()};
            field f{};
            f=f2;
            std::stringstream s;
            s << f;
            CHECK_EQ("-9223372036854775808"s,s.str());
        }
        SUBCASE("field assigns field_double field and serializes correctly") {
            field f2{field_double{1.5}};
            field f{};
            f=f2;
            std::stringstream s;
            s << f;
            CHECK_EQ("1.5"s,s.str());
        }
        SUBCASE("field assigns bool field and serializes correctly") {
            field f2{true};
            field f{};
            f=f2;
            std::stringstream s;
            s << f;
            CHECK_EQ("t"s,s.str());
        }
        SUBCASE("field assigns field_string_value field and serializes correctly") {
            field f2{field_string_value{"test"}};
            field f{};
            f=f2;
            std::stringstream s;
            s << f;
            CHECK_EQ("\"test\""s,s.str());
        }
    }
}