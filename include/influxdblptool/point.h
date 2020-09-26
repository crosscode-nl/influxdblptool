#ifndef INFLUXDBLPTOOL_POINT_H
#define INFLUXDBLPTOOL_POINT_H
#include "influxdblptool/collections.h"
#include "influxdblptool/string_types.h"
#include <chrono>
#include <vector>

namespace influxdblptool {

    using opt_time = std::optional<std::chrono::system_clock::time_point>;

    namespace time {
        std::chrono::system_clock::time_point now();
        using Tcurrent_time_provider = std::chrono::system_clock::time_point (*)();
    }

    struct insert_prefix {
        explicit operator std::string() const;
    };

    namespace intern {

        template<typename Tmeasurement_value, typename Ttags_map, typename Tfields_map, time::Tcurrent_time_provider now>
        class point {
            Tmeasurement_value measurement_;
            Tfields_map fields_;
            Ttags_map tags_;
            opt_time timestamp_;

            public:
            explicit point(Tmeasurement_value mv, typename Tfields_map::value_type field) : measurement_{std::move(mv)}, fields_{std::move(field)}, timestamp_{now()} {}
            explicit point(const char* mv, typename Tfields_map::value_type field) : measurement_{Tmeasurement_value{mv}}, fields_{std::move(field)}, timestamp_{now()} {}
            explicit point(std::string_view mv, typename Tfields_map::value_type field) : measurement_{Tmeasurement_value{mv}}, fields_{std::move(field)}, timestamp_{now()} {}
            explicit point(const std::string& mv, typename Tfields_map::value_type field) : measurement_{Tmeasurement_value{mv}}, fields_{std::move(field)}, timestamp_{now()} {}
            explicit point(std::string&& mv, typename Tfields_map::value_type field) : measurement_{Tmeasurement_value{std::move(mv)}}, fields_{std::move(field)}, timestamp_{now()} {}

            const Tmeasurement_value& measurement() const { return measurement_; }
            const Tfields_map& fields() const { return fields_; }
            const Ttags_map& tags() const { return tags_; }
            [[nodiscard]] const opt_time& timestamp() const { return timestamp_; }

            point<Tmeasurement_value, Ttags_map, Tfields_map, now>& operator<<(Tmeasurement_value m) {
                measurement_ = std::move(m);
                return *this;
            }

            point<Tmeasurement_value, Ttags_map, Tfields_map, now>& operator<<(typename Ttags_map::value_type t) {
                tags_.emplace(std::move(t));
                return *this;
            }

            point<Tmeasurement_value, Ttags_map, Tfields_map, now>& operator<<(typename Tfields_map::value_type f) {
                fields_.emplace(std::move(f));
                return *this;
            }

            point<Tmeasurement_value, Ttags_map, Tfields_map, now>& operator<<(const opt_time &ot) {
                timestamp_ = ot;
                return *this;
            }

            template<typename Rep, typename Period>
            point<Tmeasurement_value, Ttags_map, Tfields_map, now>& operator<<(const std::chrono::duration<Rep,Period> &d) {
                timestamp_ = opt_time{d};
                return *this;
            }
        };

        template <typename Tpoint>
        class points {
            std::vector<Tpoint> points_{};
            std::string prefix_{};
        public:
            [[nodiscard]] std::string prefix() const {
                return prefix_;
            }
            points<Tpoint>& operator<<(const insert_prefix& p) {
                prefix_ = static_cast<std::string>(p);
                return *this;
            }
            points<Tpoint>& operator<<(Tpoint p) {
                points_.emplace_back(std::move(p));
                return *this;
            }
            explicit operator const std::vector<Tpoint>&() const {
                return points_;
            }
        };

    }

    template <time::Tcurrent_time_provider now>
    using point_custom_timestamp = intern::point<measurement_value, tags_map, fields_map, now>;
    using point = point_custom_timestamp<time::now>;
    using points = intern::points<point>;

}

#endif //INFLUXDBLPTOOL_POINT_H
