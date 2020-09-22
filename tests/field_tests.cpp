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
}