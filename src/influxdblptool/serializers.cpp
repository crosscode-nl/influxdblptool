#include "influxdblptool/serializers.h"
#include <numeric>

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
        s << escapers::escape_measurement_value(static_cast<std::string_view>(mv));
        return s;
    }

    std::size_t escape_count(const tag_key& tk) {
        return escapers::escape_tag_key_count(static_cast<std::string_view>(tk));
    }

    std::size_t escape_count(const tag_value& tk) {
        return escapers::escape_tag_value_count(static_cast<std::string_view>(tk));
    }

    std::size_t escape_count(const field_key& tk) {
        return escapers::escape_field_key_count(static_cast<std::string_view>(tk));
    }

    std::size_t escape_count(const field_string_value& tk) {
        return escapers::escape_field_string_value_count(static_cast<std::string_view>(tk));
    }

    std::size_t escape_count(const measurement_value& tk) {
        return escapers::escape_measurement_value_count(static_cast<std::string_view>(tk));
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

    std::ostream& operator<<(std::ostream& s, const field_value& fv) {
        s << static_cast<const field_variant>(fv);
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

    template<typename TValue>
    std::ostream& serialize_vector(std::ostream& s, const std::vector<TValue>& items) {
        auto serialize = [&s](auto item) mutable {
            s << item << "\n";
        };
        std::for_each(begin(items), end(items), serialize);
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

    std::ostream& operator<<(std::ostream& s, const fields_map& items) {
        return serialize_map(s, items);
    }

    std::ostream& operator<<(std::ostream& s, const tags_map& items) {
        return serialize_map(s, items);
    }



    std::ostream& operator<<(std::ostream& s, const points& items) {
        return serialize_vector(s, static_cast<const std::vector<point>>(items));
    }

}