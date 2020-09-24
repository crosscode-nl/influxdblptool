#ifndef INFLUXDBLPTOOL_POINT_H
#define INFLUXDBLPTOOL_POINT_H
#include "influxdblptool/collections.h"
#include "influxdblptool/string_types.h"
#include <chrono>
#include <vector>


namespace influxdblptool {

    namespace intern {

        template<typename Tmeasurement_value=measurement_value, typename Ttags_map=tags_map, typename Tfields_map = fields_map>
        class point {
        public:
            Tmeasurement_value measurement{"measurement"};
            Ttags_map tags;
            Tfields_map fields;
            std::optional<std::chrono::system_clock::time_point> timestamp;

            point &operator<<(Tmeasurement_value m) {
                measurement = std::move(m);
                return *this;
            }

            point &operator<<(typename Ttags_map::value_type t) {
                tags.emplace(std::move(t));
                return *this;
            }

            point &operator<<(typename Tfields_map::value_type f) {
                fields.emplace(std::move(f));
                return *this;
            }

        };

    }

    using point = intern::point<>;
    using points = std::vector<point>;

}

#endif //INFLUXDBLPTOOL_POINT_H
