#include "influxdblptool/serializers.h"
#include <numeric>

namespace influxdblptool {

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

    template<typename TValue>
    std::ostream& serialize_vector(std::ostream& s, const std::vector<TValue>& items, const std::string &prefix, time::Tserialize_timepoint timepoint_serializer) {
        auto serialize = [&s,&prefix,&timepoint_serializer](auto item) mutable {
            s << prefix ;
            serialize_point_custom_timestamp(s,item, timepoint_serializer) << "\n";
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

        return serialize_vector(s, static_cast<const std::vector<point>>(items), items.prefix(), items.timepoint_serializer());
    }

}