#include <iostream>
#include "influxdblptool.h"

// This example demonstrates adding fields and field types.
//
// Each point must have at least one field, but they can have more.
// Extra fields can be added to the point using the output operator (<<) of point.
//
// A field can have 5 different types:
// * uint64_t
// * int64_t
// * bool
// * double
// * string
//
// Overloads of the value parameter of the field constructor exist to convert from C++ types that don't cause narrowing.
int main() {
    using namespace crosscode::influxdblptool;
    point pt{"measurement",field{"string","string value"}};
    pt << field{"double",1.5};
    pt << field{"bool",true};
    pt << field{"int",1};
    pt << field{"uint",1u};
    std::cout << pt;
    return 0;
}
// possible output:
// measurement bool=t,double=1.5,int=1i,string="string value",uint=1u 1601205708923005205
