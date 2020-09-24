#ifndef INFLUXDBLPTOOL_COLLECTIONS_H
#define INFLUXDBLPTOOL_COLLECTIONS_H
#include <map>
#include <algorithm>
#include "string_types.h"
#include "field_value.h"

namespace influxdblptool {

    using tags_map = std::map<tag_key, tag_value>;
    using fields_map = std::map<field_key, field_value>;
    using tag = tags_map::value_type;
    using field = fields_map::value_type;

}

#endif