#ifndef INFLUXDBLPTOOL_SERIALIZERS_H
#define INFLUXDBLPTOOL_SERIALIZERS_H
#include <ostream>
#include "field_value.h"
#include <map>
#include <vector>
#include "string_types.h"
#include "point.h"

namespace influxdblptool {

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

    std::string to_string( const tag_key& tk);
    std::string to_string( const tag_value& tv);
    std::string to_string( const field_key& fk);
    std::string to_string( const field_string_value& fsv);
    std::string to_string( const measurement_value& mv);
    std::string to_string( const field_variant& fv);
    std::string to_string( const field_value& fv);
    std::string to_string( const fields_map& items);
    std::string to_string( const tags_map& items);
    std::string to_string( const points& items);

    /// Serializes a time_point.
    /// \param s The ostream to output to.
    /// \param timePoint The time_point to serialize.
    /// \param tr The resolution of the timestamp to serialize.
    /// \return The ostream that is outputted to.
    std::ostream& serialize_timepoint(std::ostream& s, const std::chrono::system_clock::time_point& timePoint, timestamp_resolution tr);

    /// Serializes a point with a custom 'now' Callable.
    /// \tparam now Callable that returns current time.
    /// \param s The ostream to output to.
    /// \param item The point with a custom 'now' Callable.
    /// \param tr The resolution of the timestamp to serialize.
    /// \return The ostream that is outputted to.
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

    /// Serializes a point with a custom 'now' Callable.
    /// \tparam now Callable that returns current time.
    /// \param s The ostream to output to.
    /// \param item The point with a custom 'now' Callable to serialize.
    /// \param tr The resolution of the timestamp to serialize.
    /// \param prefix Prefix to prepend for the serialized point with custom 'now' Callable.
    /// \return The ostream that is outputted to.
    template <auto now>
    std::ostream& serialize_point_custom_timestamp(std::ostream& s, const point_custom_timestamp<now>& item, timestamp_resolution tr, const std::string& prefix) {
        s << prefix;
        return serialize_point_custom_timestamp(s, item, tr);
    }

    /// Serializes a point with a custom 'now' Callable.
    /// \tparam now Callable that returns current time.
    /// \param s The ostream to output to.
    /// \param item The point with a custom 'now' Callable to serialize.
    /// \return The ostream to output to.
    template <auto now>
    std::ostream& operator<<(std::ostream& s, const point_custom_timestamp<now>& item){
        if (empty(item.prefix())) {
            return serialize_point_custom_timestamp(s, item, item.current_timestamp_resolution());
        }
        return serialize_point_custom_timestamp(s, item, item.current_timestamp_resolution(),item.prefix());
    }

    template <auto now>
    std::string to_string(const point_custom_timestamp<now>& item) {
        std::stringstream ss;
        ss << item;
        return ss.str();
    }


}

#endif //INFLUXDBLPTOOL_SERIALIZERS_H
