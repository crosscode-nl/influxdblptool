#ifndef INFLUXDBLPTOOL_COLLECTIONS_H
#define INFLUXDBLPTOOL_COLLECTIONS_H
#include <map>
#include "abstractions/serializable.h"
#include <algorithm>
#include "string_types.h"
#include "field_value.h"

namespace influxdblptool {

    template<typename TKey, typename TValue>
    class serializable_map : public std::map<TKey, TValue>, public abstractions::serializable {
        public:
        using std::map<TKey, TValue>::map;
        void serialize(std::ostream &s) const override {
            std::for_each(begin(*this),end(*this),[&s,first=true](auto item) mutable {
                if (first) {
                    first = false;
                } else {
                    s << ",";
                }
                s << item.first << "=" << item.second;
            });
        }
    };

    using tags = serializable_map<tag_key, tag_value>;
    using fields = serializable_map<field_key, field_value>;
    using tag = tags::value_type;
    using field = fields::value_type;
}

#endif