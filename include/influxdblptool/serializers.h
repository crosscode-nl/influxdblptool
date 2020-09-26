#ifndef INFLUXDBLPTOOL_SERIALIZERS_H
#define INFLUXDBLPTOOL_SERIALIZERS_H
#include <ostream>
#include "field_value.h"
#include <map>
#include <vector>
#include "string_types.h"
#include "point.h"

namespace influxdblptool::serializers {

    template<typename TDuration=std::chrono::nanoseconds>
    std::ostream& serialize_timepoint(std::ostream& s, const std::chrono::system_clock::time_point& timePoint) {
        // This assumes that epoch is 1970-01-01T00:00:00Z, which it probably is in case of a system_clock. However,
        // technically it could be anything, because it is not specified in the spec of c++17. In the spec of c++2a
        // it is specified. So, lets assume all library implementors have this implemented as 1970-01-01T00:00:00Z
        // If a bug arises, it might be caused by a library that implemented a different epoch for system_clock.
        s << std::chrono::duration_cast<TDuration>(timePoint.time_since_epoch()).count();
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
            serialize_timepoint(s, item.timestamp().value());
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
