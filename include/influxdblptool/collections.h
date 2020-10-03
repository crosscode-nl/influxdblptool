#ifndef INFLUXDBLPTOOL_COLLECTIONS_H
#define INFLUXDBLPTOOL_COLLECTIONS_H
#include <map>
#include <algorithm>
#include "string_types.h"
#include "field_value.h"

namespace influxdblptool {

    /// tags_map is an alias of std::map<tag_key, tag_value>
    using tags_map = std::map<tag_key, tag_value>;
    /// fields_map is an alias of std::map<field_key, field_value>
    using fields_map = std::map<field_key, field_value>;
    /// tag is an alias of tags_map::value_type;
    using tag = tags_map::value_type;
    /// field is an alis of fields_map::value_type;
    using field = fields_map::value_type;

}

#endif