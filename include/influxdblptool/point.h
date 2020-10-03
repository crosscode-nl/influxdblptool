#ifndef INFLUXDBLPTOOL_POINT_H
#define INFLUXDBLPTOOL_POINT_H
#include "influxdblptool/collections.h"
#include "influxdblptool/string_types.h"
#include <chrono>
#include <vector>

/// This is the main namespace. Users of this library only need to use this namespace.
namespace influxdblptool {

    using optional_timestamp = std::optional<std::chrono::system_clock::time_point>;

    /// base class for prefixes.
    struct prefix_base {
        [[nodiscard]] virtual std::string get() const = 0;
    };

    /// implementation for an insert prefix
    struct insert_prefix_type : prefix_base {
        [[nodiscard]] std::string get() const override;
    };

    /// insert prefix is used for enabling insert prefixes on point or points.
    inline constexpr insert_prefix_type insert_prefix = insert_prefix_type{};

    /// timestamp_resolution enumeration is used for changing the timestamp resolution on point or points.
    enum class timestamp_resolution {
        /// Used to set timestamp serialization resolution to nanoseconds.
        nanoseconds,
        /// Used to set timestamp serialization resolution to microseconds.
        microseconds,
        /// Used to set timestamp serialization resolution to milliseconds.
        milliseconds,
        /// Used to set timestamp serialization resolution to seconds.
        seconds,
        /// Used to disable timestamp serialization.
        none
    };

    /// This is an internal namespace. It is used to hide types from the main namespace. It is internally used by this library.
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

        /// Template class influxdblptool::intern::point template
        /// \tparam Measurement_value Type of the measurement value
        /// \tparam Tags_map Type of the tags map
        /// \tparam Fields_map Type of the fields map
        /// \tparam now Callable that returns the current time
        template<typename Measurement_value, typename Tags_map, typename Fields_map, auto now>
        class point : public serializable_config {
            Measurement_value measurement_;
            Fields_map fields_;
            Tags_map tags_;
            optional_timestamp timestamp_;
            public:
            /// Constructor for a point
            /// \tparam Measurement_value the type of the measurement string
            /// \tparam FieldType the type of the field string
            /// \param mv A type which can be accepted by template type Measurement_value's constructor
            /// \param field Field as template type Fields_map::value_type type
            template <typename String_type, typename Field_type>
            explicit point(String_type&& mv, Field_type&& field) : measurement_{Measurement_value{std::forward<String_type>(mv)}}, fields_{std::forward<Field_type>(field)}, timestamp_{now()} {}

            /// Return the current measurement name
            /// \return The current measurement name of template type Measurement_value.
            const Measurement_value& measurement() const { return measurement_; }

            /// Return the fields that are currently set
            /// \return The fields that are set of template type Fields_map
            const Fields_map& fields() const { return fields_; }

            /// Return the tags that are currently set
            /// \return The tags that are set of template type Tags_map
            const Tags_map& tags() const { return tags_; }
            [[nodiscard]] const optional_timestamp& timestamp() const { return timestamp_; }

            /// Changes the measurement value
            /// \param m The measurement value of template type Measurement_value
            /// \return a reference to this as template type point<Measurement_value, Tags_map, Fields_map, now>&
            point<Measurement_value, Tags_map, Fields_map, now>& operator<<(Measurement_value m) {
                measurement_ = std::move(m);
                return *this;
            }

            /// Adds a tag
            /// \param t The tag value of template type Tags_map::value_type
            /// \return a reference to this as template type point<Measurement_value, Tags_map, Fields_map, now>&
            point<Measurement_value, Tags_map, Fields_map, now>& operator<<(typename Tags_map::value_type t) {
                tags_.emplace(std::move(t));
                return *this;
            }

            /// Adds a field
            /// \param f The field value of template type Fields_map::value_type
            /// \return a reference to this as template type point<Measurement_value, Tags_map, Fields_map, now>&
            point<Measurement_value, Tags_map, Fields_map, now>& operator<<(typename Fields_map::value_type f) {
                fields_.emplace(std::move(f));
                return *this;
            }

            /// Changes the timestamp or disables the timestamp.
            /// \param ot An object of type optional_timestamp.
            /// \return a reference to this as template type point<Measurement_value, Tags_map, Fields_map, now>&
            point<Measurement_value, Tags_map, Fields_map, now>& operator<<(const optional_timestamp &ot) {
                timestamp_ = ot;
                return *this;
            }

            /// Changes the timestamp from a duration
            /// \tparam Rep part of std::chrono::duration
            /// \tparam Period part of std::chrono::duration
            /// \param d The duration of template type std::chrono::duration<Rep,Period>
            /// \return a reference to this as template type point<Measurement_value, Tags_map, Fields_map, now>&
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

            void reserve(typename std::vector<Point>::size_type size) {
                points_.reserve(size);
            }

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
