#include <iostream>
#include "influxdblptool.h"

// This example demonstrates setting a custom timestamp.
//
// You can use chrono::duration to set a timestamp since epoch (1970-01-01 00:00:00 UTC)
int main() {
    using namespace crosscode::influxdblptool;
    using namespace std::literals;

    point pt1{"measurement",field{"field_key","field_value"}};
    pt1 << 3s;
    std::cout << pt1 << '\n';

    point pt2{"measurement",field{"field_key","field_value"}};
    pt2 << optional_timestamp{3s};
    std::cout << pt2;

    return 0;
}
// output:
// measurement field_key="field_value" 3000000000
// measurement field_key="field_value" 3000000000
