#include "doctest.h"
#include "influxdblptool/collections.h"
#include <sstream>

using namespace std::literals;

using namespace influxdblptool;
TEST_SUITE("collections") {
    TEST_CASE ("tags serialize correctly in order") {
        SUBCASE("normal values") {
            static_assert(std::is_same_v<tags,intern::serializable_map<tag_key, tag_value>>);
            tags t;
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
            static_assert(std::is_same_v<fields,intern::serializable_map<field_key, field_value>>);
            fields t;
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
            fields t;
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
}
