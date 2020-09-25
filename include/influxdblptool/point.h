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
            void throw_when_fields_are_empty() const {
                if (fields.empty()) {
                    throw validator_exception("At least one field must be provided.");
                }
            }

            public:
            Tmeasurement_value measurement{"measurement"};
            Ttags_map tags;
            Tfields_map fields;
            std::optional<std::chrono::system_clock::time_point> timestamp;

            void validate() const {
                throw_when_fields_are_empty();
            }

            point& operator<<(Tmeasurement_value m) {
                measurement = std::move(m);
                return *this;
            }

            point& operator<<(typename Ttags_map::value_type t) {
                tags.emplace(std::move(t));
                return *this;
            }

            point& operator<<(typename Tfields_map::value_type f) {
                fields.emplace(std::move(f));
                return *this;
            }
        };

        template <typename Tpoint>
        class points {
            std::vector<Tpoint> points_;
        public:
            Tpoint& operator<<(Tpoint p) {
                points_.emplace_back(std::move(p));
                return *this;
            }
            explicit operator const std::vector<Tpoint>&() const {
                return points_;
            }
        };

    }

    using point = intern::point<>;
    using points = intern::points<point>;


}

#endif //INFLUXDBLPTOOL_POINT_H
