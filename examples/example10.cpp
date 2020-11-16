#include <iostream>
#include "influxdblptool.h"

// This example demonstrates to_string serialization
//
// Serialization can be achieved using the output stream operator, but to_string method is also supported.

using namespace crosscode::influxdblptool;

int main() {
    using namespace std::literals;

    point pt{"measurement",field{"field_key","field_value"}};
    std::cout << to_string(pt) << "\n";

}
// possible output:
// measurement field_key="field_value" 1603015046702615356


