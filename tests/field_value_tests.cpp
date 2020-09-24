#include "doctest.h"
#include "influxdblptool/field_value.h"
#include <sstream>

using namespace std::literals;
using namespace influxdblptool;

TEST_SUITE("field_value") {
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
    TEST_CASE("field_value constructs and serializes correctly") {
        static_assert(std::is_same_v<field_variant,std::variant<field_double,field_string_value,bool,std::uint64_t,std::int64_t>>);
        static_assert(std::is_base_of_v<field_variant,field_value>);
        SUBCASE("field_value accepts field_double and serializes correctly") {
            field_value f{field_double{100.5}};
            std::stringstream s;
            s << f;
            CHECK_EQ("100.5"s,s.str());
        }
        SUBCASE("field_value accepts double and serializes correctly") {
            field_value f{100.5};
            std::stringstream s;
            s << f;
            CHECK_EQ("100.5"s,s.str());
        }
        SUBCASE("field_value accepts float and serializes correctly") {
            field_value f{100.5f};
            std::stringstream s;
            s << f;
            CHECK_EQ("100.5"s,s.str());
        }
        SUBCASE("field_value accepts bool true and serializes correctly") {
            field_value f{true};
            std::stringstream s;
            s << f;
            CHECK_EQ("t"s,s.str());
        }
        SUBCASE("field_value accepts bool true and serializes correctly") {
            field_value f{false};
            std::stringstream s;
            s << f;
            CHECK_EQ("f"s,s.str());
        }
        SUBCASE("field_value accepts const char* string and serializes correctly") {
            field_value f{"string"};
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field_value accepts string_view and serializes correctly") {
            field_value f{"string"sv};
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field_value accepts string and serializes correctly") {
            field_value f{"string"s};
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field_value accepts field_string_value and serializes correctly") {
            field_string_value v{"string"s};
            field_value f{v};
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field_value accepts uint64_t and serializes correctly") {
            field_value f{std::numeric_limits<uint64_t>::max()};
            std::stringstream s;
            s << f;
            CHECK_EQ("18446744073709551615u"s,s.str());
        }
        SUBCASE("field_value accepts int64_t and serializes correctly") {
            field_value f{std::numeric_limits<int64_t>::min()};
            std::stringstream s;
            s << f;
            CHECK_EQ("-9223372036854775808i"s,s.str());
        }
        SUBCASE("field_value accepts uint32_t and serializes correctly") {
            field_value f{std::numeric_limits<uint32_t>::max()};
            std::stringstream s;
            s << f;
            CHECK_EQ("4294967295u"s,s.str());
        }
        SUBCASE("field_value accepts int32_t and serializes correctly") {
            field_value f{std::numeric_limits<int32_t>::min()};
            std::stringstream s;
            s << f;
            CHECK_EQ("-2147483648i"s,s.str());
        }
        SUBCASE("field_value accepts uint16_t and serializes correctly") {
            field_value f{std::numeric_limits<uint16_t>::max()};
            std::stringstream s;
            s << f;
            CHECK_EQ("65535u"s,s.str());
        }
        SUBCASE("field_value accepts int16_t and serializes correctly") {
            field_value f{std::numeric_limits<int16_t>::min()};
            std::stringstream s;
            s << f;
            CHECK_EQ("-32768i"s,s.str());
        }
        SUBCASE("field_value accepts uint8_t and serializes correctly") {
            field_value f{std::numeric_limits<uint8_t>::max()};
            std::stringstream s;
            s << f;
            CHECK_EQ("255u"s,s.str());
        }
        SUBCASE("field_value accepts int8_t and serializes correctly") {
            field_value f{std::numeric_limits<int8_t>::min()};
            std::stringstream s;
            s << f;
            CHECK_EQ("-128i"s,s.str());
        }
        SUBCASE("field_value accepts field by copy and serializes correctly") {
            field_value f2{std::numeric_limits<int8_t>::min()};
            field_value f{f2};
            f2 = std::numeric_limits<int8_t>::max();
            std::stringstream s;
            s << f;
            CHECK_EQ("-128i"s,s.str());
        }
        SUBCASE("field_value accepts field by move and serializes correctly") {
            field_value f2{std::numeric_limits<int8_t>::min()};
            field_value f(std::move(f2));
            std::stringstream s;
            s << f;
            CHECK_EQ("-128i"s,s.str());
        }
    }
    TEST_CASE("field_value assigns and serializes correctly") {
        SUBCASE("field_value assigns field_double and serializes correctly") {
            field_value f{};
            f = field_double{100.5};
            std::stringstream s;
            s << f;
            CHECK_EQ("100.5"s,s.str());
        }
        SUBCASE("field_value assigns double and serializes correctly") {
            field_value f{};
            f=100.5;
            std::stringstream s;
            s << f;
            CHECK_EQ("100.5"s,s.str());
        }
        SUBCASE("field_value assigns float and serializes correctly") {
            field_value f{};
            f=100.5f;
            std::stringstream s;
            s << f;
            CHECK_EQ("100.5"s,s.str());
        }
        SUBCASE("field_value assigns bool true and serializes correctly") {
            field_value f{};
            f=true;
            std::stringstream s;
            s << f;
            CHECK_EQ("t"s,s.str());
        }
        SUBCASE("field_value assigns bool true and serializes correctly") {
            field_value f{};
            f=false;
            std::stringstream s;
            s << f;
            CHECK_EQ("f"s,s.str());
        }
        SUBCASE("field_value assigns const char* string and serializes correctly") {
            field_value f{};
            f="string";
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field_value assigns string_view and serializes correctly") {
            field_value f{};
            f="string"sv;
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field_value assigns string and serializes correctly") {
            field_value f{};
            f="string"s;
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field_value assigns field_string_value and serializes correctly") {
            field_string_value v{"string"s};
            field_value f{};
            f=v;
            std::stringstream s;
            s << f;
            CHECK_EQ("\"string\""s,s.str());
        }
        SUBCASE("field_value assigns uint64_t and serializes correctly") {
            field_value f{};
            f=std::numeric_limits<uint64_t>::max();
            std::stringstream s;
            s << f;
            CHECK_EQ("18446744073709551615u"s,s.str());
        }
        SUBCASE("field_value assigns int64_t and serializes correctly") {
            field_value f{};
            f=std::numeric_limits<int64_t>::min();
            std::stringstream s;
            s << f;
            CHECK_EQ("-9223372036854775808i"s,s.str());
        }
        SUBCASE("field_value assigns uint32_t and serializes correctly") {
            field_value f{};
            f=std::numeric_limits<uint32_t>::max();
            std::stringstream s;
            s << f;
            CHECK_EQ("4294967295u"s,s.str());
        }
        SUBCASE("field_value assigns int32_t and serializes correctly") {
            field_value f{};
            f=std::numeric_limits<int32_t>::min();
            std::stringstream s;
            s << f;
            CHECK_EQ("-2147483648i"s,s.str());
        }
        SUBCASE("field_value assigns uint16_t and serializes correctly") {
            field_value f{};
            f=std::numeric_limits<uint16_t>::max();
            std::stringstream s;
            s << f;
            CHECK_EQ("65535u"s,s.str());
        }
        SUBCASE("field_value assigns int16_t and serializes correctly") {
            field_value f{};
            f=std::numeric_limits<int16_t>::min();
            std::stringstream s;
            s << f;
            CHECK_EQ("-32768i"s,s.str());
        }
        SUBCASE("field_value assigns uint8_t and serializes correctly") {
            field_value f{};
            f=std::numeric_limits<uint8_t>::max();
            std::stringstream s;
            s << f;
            CHECK_EQ("255u"s,s.str());
        }
        SUBCASE("field_value assigns int8_t and serializes correctly") {
            field_value f{};
            f=std::numeric_limits<int8_t>::min();
            std::stringstream s;
            s << f;
            CHECK_EQ("-128i"s,s.str());
        }
        SUBCASE("field_value assigns uint64_t field and serializes correctly") {
            field_value f2{std::numeric_limits<uint64_t>::max()};
            field_value f{};
            f=f2;
            std::stringstream s;
            s << f;
            CHECK_EQ("18446744073709551615u"s,s.str());
        }
        SUBCASE("field_value assigns int64_t field and serializes correctly") {
            field_value f2{std::numeric_limits<int64_t>::min()};
            field_value f{};
            f=f2;
            std::stringstream s;
            s << f;
            CHECK_EQ("-9223372036854775808i"s,s.str());
        }
        SUBCASE("field_value assigns field_double field and serializes correctly") {
            field_value f2{field_double{1.5}};
            field_value f{};
            f=f2;
            std::stringstream s;
            s << f;
            CHECK_EQ("1.5"s,s.str());
        }
        SUBCASE("field_value assigns bool field and serializes correctly") {
            field_value f2{true};
            field_value f{};
            f=f2;
            std::stringstream s;
            s << f;
            CHECK_EQ("t"s,s.str());
        }
        SUBCASE("field_value assigns field_string_value field and serializes correctly") {
            field_value f2{field_string_value{"test"}};
            field_value f{};
            f=f2;
            std::stringstream s;
            s << f;
            CHECK_EQ("\"test\""s,s.str());
        }
    }
}