#ifndef INFLUXDBLPTOOL_SERIALIZERS_H
#define INFLUXDBLPTOOL_SERIALIZERS_H
#include <ostream>
#include "field_value.h"
#include <map>
#include <vector>
#include "string_types.h"
#include "point.h"

namespace influxdblptool {

    std::ostream& serialize_timepoint(std::ostream& s, const std::chrono::system_clock::time_point& timePoint, timestamp_resolution tr);

    template <auto now>
    std::ostream& serialize_point_custom_timestamp(std::ostream& s, const point_custom_timestamp<now>& item, timestamp_resolution tr) {
        s << item.measurement();
        if (!item.tags().empty()) {
            s << ',' << item.tags();
        }
        s << ' ' << item.fields();
        if (item.timestamp().has_value()) {
            serialize_timepoint(s, item.timestamp().value(), tr);
        }
        return s;
    }

    template <auto now>
    std::ostream& serialize_point_custom_timestamp(std::ostream& s, const point_custom_timestamp<now>& item, timestamp_resolution tr, const std::string& prefix) {
        s << prefix;
        return serialize_point_custom_timestamp(s, item, tr);
    }

    template <auto now>
    std::ostream& operator<<(std::ostream& s, const point_custom_timestamp<now>& item){
        if (empty(item.prefix())) {
            return serialize_point_custom_timestamp(s, item, item.current_timestamp_resolution());
        }
        return serialize_point_custom_timestamp(s, item, item.current_timestamp_resolution(),item.prefix());
    }

    std::ostream& operator<<(std::ostream& s, const tag_key& tk);
    std::ostream& operator<<(std::ostream& s, const tag_value& tv);
    std::ostream& operator<<(std::ostream& s, const field_key& fk);
    std::ostream& operator<<(std::ostream& s, const field_string_value& fsv);
    std::ostream& operator<<(std::ostream& s, const measurement_value& mv);
    std::ostream& operator<<(std::ostream& s, const field_variant& fv);
    std::ostream& operator<<(std::ostream& s, const field_value& fv);
    std::ostream& operator<<(std::ostream& s, const fields_map& items);
    std::ostream& operator<<(std::ostream& s, const tags_map& items);
    std::ostream& operator<<(std::ostream& s, const points& items);

}

#endif //INFLUXDBLPTOOL_SERIALIZERS_H
