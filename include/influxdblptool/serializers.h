#ifndef INFLUXDBLPTOOL_SERIALIZERS_H
#define INFLUXDBLPTOOL_SERIALIZERS_H
#include <ostream>
#include "field_value.h"
#include <map>
#include <vector>
#include "string_types.h"
#include "point.h"

namespace influxdblptool {

    template <time::Tcurrent_time_provider currentTimeProvider>
    std::ostream& serialize_point_custom_timestamp(std::ostream& s, const point_custom_timestamp<currentTimeProvider>& item, time::Tserialize_timepoint serialize_timepoint){
        s << item.measurement();
        if (!item.tags().empty()) {
            s << "," << item.tags();
        }
        s << " " << item.fields();
        if (item.timestamp().has_value()) {
            s << " ";
            serialize_timepoint(s, item.timestamp().value());
        }
        return s;
    }

    template <time::Tcurrent_time_provider currentTimeProvider>
    std::ostream& operator<<(std::ostream& s, const point_custom_timestamp<currentTimeProvider>& item){
        s << item.measurement();
        if (!item.tags().empty()) {
            s << "," << item.tags();
        }
        s << " " << item.fields();
        if (item.timestamp().has_value()) {
            s << " ";
            time::serialize_timepoint(s,item.timestamp().value());;
        }
        return s;
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
