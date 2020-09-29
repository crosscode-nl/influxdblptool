#include <iostream>
#include "influxdblptool.h"

// This example demonstrates the points collection.
//
// This example builds on and uses principles from the previous examples.
// It is assumed the previous examples are understood.
//
// On points you can also set insert_prefix, or time_resolution. It will have an affect on all points
// in the collection. It makes no sense to individually change these settings per point, and when you do so
// it will not have an effect.

using namespace influxdblptool;

point make_point() {
    return (point{"measurement",field{"field_string","field_string_value"}}
                << tag{"example_tag_key","example_tag_value"}
                << field("field_double",1.5)
                );
}

int main() {
    using namespace std::literals;

    points pts;
    pts << insert_prefix;
    pts << timestamp_resolution::milliseconds;
    pts << (make_point() << 1s);
    // setting timestamp_resolution has no effect
    pts << (make_point() << 2s << timestamp_resolution::microseconds);
    std::cout << pts;

    return 0;
}
// possible output:
// INSERT measurement,example_tag_key=example_tag_value field_double=1.5,field_string="field_string_value" 1000
// INSERT measurement,example_tag_key=example_tag_value field_double=1.5,field_string="field_string_value" 2000


