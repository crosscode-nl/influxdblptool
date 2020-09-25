#include "doctest.h"
#include "influxdblptool/serializers.h"

using namespace std::literals;
using namespace influxdblptool;
using namespace influxdblptool::serializers;

TEST_SUITE("serializers") {
  TEST_CASE("measurement")
  {
        SUBCASE("assigns and serializes correctly") {
            std::stringstream s;
            measurement_value m{"overwrite"};
            m = measurement_value{", \"\\=abc"s};
            s << m;
            CHECK_EQ("\\,\\ \"\\=abc"s,s.str());
        }
    }
    TEST_CASE("tag_key")
    {
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
        SUBCASE("assigns and serializes correctly") {
            std::stringstream s;
            field_string_value f{"overwrite"};
            f = field_string_value{", \"\\=abc"s};
            s << f;
            CHECK_EQ(", \\\"\\\\=abc"s,s.str());
        }
    }
    TEST_CASE ("tags serialize correctly in order") {
        SUBCASE("normal values") {
            static_assert(std::is_same_v<tags_map,std::map<tag_key, tag_value>>);
            tags_map t;
            t.emplace(tag{"keyC", "testValueC"});
            t.emplace(tag{"keyB", "testValueB"});
            t.emplace(tag{"keyA", "testValueA"});
            t.emplace(tag{"keyD", "testValueD"});
            std::stringstream ss;
            ss << t;
            CHECK_EQ("keyA=testValueA,keyB=testValueB,keyC=testValueC,keyD=testValueD"s,ss.str());
        }
    }
    TEST_CASE ("fields serialize correctly in order") {
        SUBCASE("normal values") {
            static_assert(std::is_same_v<fields_map,std::map<field_key, field_value>>);
            fields_map t;
            t.emplace(field{"keyC", "testValueC"});
            t.emplace(field{"keyB", 1.5});
            t.emplace(field{"keyA", uint32_t{1}});
            t.emplace(field{"keyD", int16_t{-1}});
            t.emplace(field{"keyE", true});
            std::stringstream ss;
            ss << t;
            CHECK_EQ("keyA=1u,keyB=1.5,keyC=\"testValueC\",keyD=-1i,keyE=t"s,ss.str());
        }
        SUBCASE("escape values") {
            fields_map t;
            t.emplace(field{"keyC", "test\"ValueC"});
            t.emplace(field{"keyB", 1.5});
            t.emplace(field{"keyA", uint32_t{1}});
            t.emplace(field{"keyD", int16_t{-1}});
            t.emplace(field{"keyE=", true});
            std::stringstream ss;
            ss << t;
            CHECK_EQ("keyA=1u,keyB=1.5,keyC=\"test\\\"ValueC\",keyD=-1i,keyE\\==t"s,ss.str());
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