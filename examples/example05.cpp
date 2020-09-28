#include <iostream>
#include "influxdblptool.h"

// This example demonstrates setting a custom timestamp
//
// You can use chrono::duration to set a timestamp since epoch (1970-01-01 00:00:00 UTC)
int main() {
    using namespace influxdblptool;
    using namespace std::literals;

    point pt{"measurement",field{"field_key","field_value"}};
    pt << 3s; // Could also be optional_timestamp{3s} if you want to be more explicit.
    std::cout << pt;

    return 0;
}
// output:
// measurement field_key="field_value" 3000000000
