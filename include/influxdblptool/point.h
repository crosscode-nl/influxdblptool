#ifndef INFLUXDBLPTOOL_POINT_H
#define INFLUXDBLPTOOL_POINT_H
#include "influxdblptool/collections.h"
#include "influxdblptool/string_types.h"
#include <chrono>
#include <vector>

namespace influxdblptool {

    using optional_timestamp = std::optional<std::chrono::system_clock::time_point>;

    struct prefix_base {
        [[nodiscard]] virtual std::string get() const = 0;
    };

    struct insert_prefix_type : prefix_base {
        [[nodiscard]] std::string get() const override;
    };

    inline constexpr insert_prefix_type insert_prefix = insert_prefix_type{};


    enum class timestamp_resolution {
        nanoseconds,
        microseconds,
        milliseconds,
        seconds,
    };

    namespace intern {
        class serializable_config {
            std::string prefix_{};
            timestamp_resolution timestamp_resolution_{timestamp_resolution::nanoseconds};
        public:
            void set_current_timestamp_resolution(timestamp_resolution ts) {
                timestamp_resolution_ = ts;
            }

            [[nodiscard]] timestamp_resolution current_timestamp_resolution() const {
                return timestamp_resolution_;
            }

            void set_prefix(const prefix_base &p) {
                prefix_ = p.get();
            }

            [[nodiscard]] std::string prefix() const {
                return prefix_;
            }

            virtual ~serializable_config()=default;

        };

        template<typename Measurement_value, typename Tags_map, typename Fields_map, auto now>
        class point : public serializable_config {
            Measurement_value measurement_;
            Fields_map fields_;
            Tags_map tags_;
            optional_timestamp timestamp_;
            public:

            explicit point(Measurement_value mv, typename Fields_map::value_type field) : measurement_{std::move(mv)}, fields_{std::move(field)}, timestamp_{now()} {}
            explicit point(const char* mv, typename Fields_map::value_type field) : measurement_{Measurement_value{mv}}, fields_{std::move(field)}, timestamp_{now()} {}
            explicit point(std::string_view mv, typename Fields_map::value_type field) : measurement_{Measurement_value{mv}}, fields_{std::move(field)}, timestamp_{now()} {}
            explicit point(const std::string& mv, typename Fields_map::value_type field) : measurement_{Measurement_value{mv}}, fields_{std::move(field)}, timestamp_{now()} {}
            explicit point(std::string&& mv, typename Fields_map::value_type field) : measurement_{Measurement_value{std::move(mv)}}, fields_{std::move(field)}, timestamp_{now()} {}

            const Measurement_value& measurement() const { return measurement_; }
            const Fields_map& fields() const { return fields_; }
            const Tags_map& tags() const { return tags_; }
            [[nodiscard]] const optional_timestamp& timestamp() const { return timestamp_; }

            point<Measurement_value, Tags_map, Fields_map, now>& operator<<(Measurement_value m) {
                measurement_ = std::move(m);
                return *this;
            }

            point<Measurement_value, Tags_map, Fields_map, now>& operator<<(typename Tags_map::value_type t) {
                tags_.emplace(std::move(t));
                return *this;
            }

            point<Measurement_value, Tags_map, Fields_map, now>& operator<<(typename Fields_map::value_type f) {
                fields_.emplace(std::move(f));
                return *this;
            }

            point<Measurement_value, Tags_map, Fields_map, now>& operator<<(const optional_timestamp &ot) {
                timestamp_ = ot;
                return *this;
            }

            template<typename Rep, typename Period>
            point<Measurement_value, Tags_map, Fields_map, now>& operator<<(const std::chrono::duration<Rep,Period> &d) {
                timestamp_ = optional_timestamp{d};
                return *this;
            }

        };

        template <typename Point>
        class points : public serializable_config {
            std::vector<Point> points_{};
        public:

            points<Point>& operator<<(Point p) {
                points_.emplace_back(std::move(p));
                return *this;
            }

            explicit operator const std::vector<Point>&() const {
                return points_;
            }
        };

    }

    template<typename Type>
    typename std::enable_if<std::is_base_of_v<intern::serializable_config,Type>,Type>::type&
    operator<<(Type& o,timestamp_resolution tr) {
        o.set_current_timestamp_resolution(tr);
        return o;
    }

    template<typename Type>
    typename std::enable_if<std::is_base_of_v<intern::serializable_config,Type>,Type>::type&
    operator<<(Type& o,const insert_prefix_type& p) {
        o.set_prefix(p);
        return o;
    }

    template <auto now>
    using point_custom_timestamp = intern::point<measurement_value, tags_map, fields_map, now>;
    using point = point_custom_timestamp<std::chrono::system_clock::now>;
    using points = intern::points<point>;

}

#endif //INFLUXDBLPTOOL_POINT_H
