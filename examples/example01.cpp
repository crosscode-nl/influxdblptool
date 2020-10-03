#include <iostream>
#include "influxdblptool.h"

// Most basic example, and explains some concepts.
//
// This example generates a point and directly sends it to std::cout.
// From the InfluxDB documentation: https://docs.influxdata.com/influxdb/v1.8/concepts/key_concepts/
//
// > A point represents a single data record that has four components:
// > a measurement, tag set, field set, and a timestamp.
// >
// > A point is uniquely identified by its series and timestamp.
//
// Each point has a measurement. This is the first parameter for the constructor of point. It's like a table name.
// At least one field is required. That is needed as the second parameter for the constructor of the point class.
// By default the current timestamp is added with a nanosecond resolution.
// The point can be serialized to an ostream.
int main() {
    using namespace influxdblptool;
    std::cout << point{"measurement",field{"field_key","field_value"}};
    return 0;
}
// possible output:
// measurement field_key="field_value" 1601205691780532675