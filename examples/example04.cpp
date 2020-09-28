#include <iostream>
#include "influxdblptool.h"

// This example demonstrates removing a timestamp from a point.
//
// When a point does not have a timestamp it will get a timestamp of the current time when it is inserted into InfluxDB.
int main() {
    using namespace influxdblptool;
    using namespace std::literals;

    point pt{"measurement",field{"field_key","field_value"}};
    pt << optional_timestamp{};
    std::cout << pt;

    return 0;
}
// output:
// measurement field_key="field_value"
