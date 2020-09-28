#include <iostream>
#include "influxdblptool.h"

// This example demonstrates adding a tag to the point.
//
// This example generates a point and directly sends it to std::cout.
// The point is augmented with a tag. One or more tags can be added.
// A tag is something you would like to filter on in InfluxDB.
int main() {
    using namespace influxdblptool;
    point pt{"measurement",field{"field_key","field_value"}};
    pt << tag{"tag_key1","tag_value1"} << tag{"tag_key2","tag_value2"};
    std::cout <<  pt;
    return 0;
}
// possible output:
// measurement,tag_key1=tag_value1,tag_key2=tag_value2 field_key="field_value" 1601317477746478874
