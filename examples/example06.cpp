#include <iostream>
#include "influxdblptool.h"

// This example demonstrates adding an INSERT prefix.
//
// The insert prefix can be used for loading the data via the CLI. https://docs.influxdata.com/influxdb/v1.8/tools/shell/
int main() {
    using namespace influxdblptool;

    point pt{"measurement",field{"field_key","field_value"}};
    pt << insert_prefix;
    std::cout << pt;

    return 0;
}
// possible output:
// INSERT measurement field_key="field_value" 1601367649959100561
