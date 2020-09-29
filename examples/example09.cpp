#include <iostream>
#include "influxdblptool.h"

// This example demonstrates validation.
//
// All input is validated as early as possible.
// The interface is designed so invalid state should not be possible.
// All input is validated and can throw an validation_exception.
// Examples of invalid input are:
// * Keys cannot start with an underscore
// * doubles cannot be INF or NaN.
//
// See validators.cpp or InfluxDB documentation for all possible invalid input.

using namespace influxdblptool;

int main() {
    using namespace std::literals;

    try {
        std::cout << R"(tag{"_invalidkey", "validvalue"};)" << "\n";
        tag{"_invalidkey", "validvalue"};
    } catch (validator_exception &e) {
        std::cout << e.what() << "\n";
    }

    try {
        std::cout << R"(field{"invaliddouble", std::numeric_limits<double>::infinity()};)" << "\n";
        field{"invaliddouble", std::numeric_limits<double>::infinity()};
    } catch (validator_exception &e) {
        std::cout << e.what() << "\n";
    }

    return 0;
}
// output:
// tag{"_invalidkey", "validvalue"};
// Input must not start with underscore.
// field{"invaliddouble", std::numeric_limits<double>::infinity()};
// Infinite value not allowed.


