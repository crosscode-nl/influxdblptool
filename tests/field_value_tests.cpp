#include "doctest.h"
#include "influxdblptool/field_value.h"

using namespace std::literals;
using namespace influxdblptool;

TEST_SUITE("field_value") {
    TEST_CASE("field_double works correctly") {
        SUBCASE("field_double accepts double") {
            REQUIRE_NOTHROW(field_double fd{1.0});
        }
        SUBCASE("field_double accepts float") {
            REQUIRE_NOTHROW(field_double fd{1.0f});
        }
        SUBCASE("field_double casts to double") {
            const double d{100.5};
            field_double fd{d};
            REQUIRE(d==static_cast<double>(fd));
        }
        SUBCASE("field_double assigns from double") {
            const double d{100.5};
            field_double fd{};
            fd = d;
            REQUIRE(d==static_cast<double>(fd));
        }
        SUBCASE("field_double assigns from float") {
            field_double fd{};
            const float d{100.5};
            fd = d;
            REQUIRE(d==static_cast<double>(fd));
        }
        SUBCASE("field_double throws when infinite double is given") {
            REQUIRE_THROWS_AS_MESSAGE(field_double{std::numeric_limits<double>::infinity()},validator_exception,"Infinite value not allowed.");
        }
        SUBCASE("field_double throws when infinite float is given") {
            REQUIRE_THROWS_AS_MESSAGE(field_double{std::numeric_limits<float>::infinity()},validator_exception,"Infinite value not allowed.");
        }
        SUBCASE("field_double throws when quiet_NaN double is given") {
            REQUIRE_THROWS_AS_MESSAGE(field_double{std::numeric_limits<double>::quiet_NaN()},validator_exception,"NaN value not allowed.");
        }
        SUBCASE("field_double throws when quiet_NaN float is given") {
            REQUIRE_THROWS_AS_MESSAGE(field_double{std::numeric_limits<float>::quiet_NaN()},validator_exception,"NaN value not allowed.");
        }
        SUBCASE("field_double throws when signaling_NaN double is given") {
            REQUIRE_THROWS_AS_MESSAGE(field_double{std::numeric_limits<double>::signaling_NaN()},validator_exception,"NaN value not allowed.");
        }
        SUBCASE("field_double throws when signaling_NaN float is given") {
            REQUIRE_THROWS_AS_MESSAGE(field_double{std::numeric_limits<float>::signaling_NaN()},validator_exception,"NaN value not allowed.");
        }
    }

}