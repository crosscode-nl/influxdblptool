#ifndef INFLUXDBLPTOOL_ESCAPERS_H
#define INFLUXDBLPTOOL_ESCAPERS_H
#include <algorithm>
#include <sstream>
#include <array>

/// The escapers namespace contains all escapers. It is internally used by this library.
namespace influxdblptool::escapers {

    std::string escape_measurement_value(std::string_view s);
    std::string escape_tag_key(std::string_view s);
    std::string escape_tag_value(std::string_view s);
    std::string escape_field_key(std::string_view s);
    std::string escape_field_string_value(std::string_view s);

}

#endif //INFLUXDBLPTOOL_ESCAPERS_H
