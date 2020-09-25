#include "influxdblptool/serializers.h"

namespace influxdblptool::serializers {

    std::ostream& operator<<(std::ostream& s, const tag_key& tk) {
        s << escapers::escape_tag_key(static_cast<std::string_view>(tk));
        return s;
    }

    std::ostream& operator<<(std::ostream& s, const tag_value& tv) {
        s << escapers::escape_tag_value(static_cast<std::string_view>(tv));
        return s;
    }

    std::ostream& operator<<(std::ostream& s, const field_key& fk) {
        s << escapers::escape_field_key(static_cast<std::string_view>(fk));
        return s;
    }

    std::ostream& operator<<(std::ostream& s, const field_string_value& fsv) {
        s << escapers::escape_field_string_value(static_cast<std::string_view>(fsv));
        return s;
    }

    std::ostream& operator<<(std::ostream& s, const measurement_value& mv) {
        s << escapers::escape_measurement(static_cast<std::string_view>(mv));
        return s;
    }

    class serializing_visitor {
        std::ostream *os_;
    public:
        explicit serializing_visitor(std::ostream *os) : os_(os) {}

        void operator()(const field_double& v) {
            *os_ << (double) v;
        }

        void operator()(const field_string_value& v) {
            *os_ << "\"" << v << "\"";

        }

        void operator()(const bool& v) {
            *os_ << (v ? "t" : "f");
        }

        void operator()(const uint64_t& v) {
            *os_ << std::to_string(v) << "u";
        }

        void operator()(const int64_t& v) {
            *os_ << std::to_string(v) << "i";
        }
    };

    std::ostream& operator<<(std::ostream& s, const field_variant& fv) {
        std::visit(serializing_visitor{&s}, fv);
        return s;
    }

    template<typename TDuration=std::chrono::nanoseconds>
    std::ostream& operator<<(std::ostream& s, const std::chrono::system_clock::time_point& timePoint) {
        // This assumes that epoch is 1970-01-01T00:00:00Z, which it probably is in case of a system_clock. However,
        // technically it could be anything, because it is not specified in the spec of c++17. In the spec of c++2a
        // it is specified. So, lets assume all library implementors have this implemented as 1970-01-01T00:00:00Z
        // If a bug arises, it might be caused by a library that implemented a different epoch for system_clock.
        s << std::chrono::duration_cast<TDuration>(timePoint.time_since_epoch()).count();
        return s;
    }

    template<typename TKey, typename TValue>
    std::ostream& serialize_map(std::ostream& s, const std::map<TKey, TValue>& items) {
        auto serialize_pair = [&s, first = true](auto item) mutable {
            if (first) {
                first = false;
            } else {
                s << ",";
            }
            s << item.first << "=" << item.second;
        };
        std::for_each(begin(items), end(items), serialize_pair);
        return s;
    }

    template<typename TValue>
    std::ostream& serialize_vector(std::ostream& s, const std::vector<TValue>& items) {
        auto serialize = [&s, first = true](auto item) mutable {
            s << item;
        };
        std::for_each(begin(items), end(items), serialize);
        return s;
    }


    std::ostream& operator<<(std::ostream& s, const fields_map& items) {
        return serialize_map(s, items);
    }

    std::ostream& operator<<(std::ostream& s, const tags_map& items) {
        return serialize_map(s, items);
    }

    template<typename TDuration=std::chrono::nanoseconds>
    std::ostream& serialize_timepoint(std::ostream& s, const std::chrono::system_clock::time_point& timePoint) {
        // This assumes that epoch is 1970-01-01T00:00:00Z, which it probably is in case of a system_clock. However,
        // technically it could be anything, because it is not specified in the spec of c++17. In the spec of c++2a
        // it is specified. So, lets assume all library implementors have this implemented as 1970-01-01T00:00:00Z
        // If a bug arises, it might be caused by a library that implemented a different epoch for system_clock.
        s << std::chrono::duration_cast<TDuration>(timePoint.time_since_epoch()).count();
        return s;
    }

    std::ostream& operator<<(std::ostream& s, const point& item) {
        s << item.measurement;
        if (!item.tags.empty()) {
            s << "," << item.tags;
        }
        s << item.fields;
        if (item.timestamp.has_value()) {
            s << " ";
            serialize_timepoint(s, item.timestamp.value());
        }
        return s;
    }

    std::ostream& operator<<(std::ostream& s, const points& items) {
        return serialize_vector(s, items);
    }

}