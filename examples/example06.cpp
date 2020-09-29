#include <iostream>
#include "influxdblptool.h"

// This example demonstrates changing the timestamp resolution.
//
// The insert prefix can be used for loading the data via the CLI. https://docs.influxdata.com/influxdb/v1.8/tools/shell/
int main() {
    using namespace influxdblptool;
    using namespace std::literals;

    point ptn{"measurement",field{"field_key","field_value"}};
    ptn << 1000s;
    std::cout << ptn << "\n"; // default resolution is nanoseconds

    point ptmu{"measurement",field{"field_key","field_value"}};
    ptmu << timestamp_resolution::microseconds; // set resolution to microseconds
    ptmu << 1000s;
    std::cout << ptmu << "\n";

    point ptm{"measurement",field{"field_key","field_value"}};
    ptm << timestamp_resolution::milliseconds; // set resolution to milliseconds
    ptm << 1000s;
    std::cout << ptm << "\n";

    point pts{"measurement",field{"field_key","field_value"}};
    pts << timestamp_resolution::seconds; // set resolution to seconds
    pts << 1000s;
    std::cout << pts;

    return 0;
}
// output:
// measurement field_key="field_value" 1000000000000
// measurement field_key="field_value" 1000000000
// measurement field_key="field_value" 1000000
// measurement field_key="field_value" 1000

