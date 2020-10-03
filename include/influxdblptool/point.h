#ifndef INFLUXDBLPTOOL_POINT_H
#define INFLUXDBLPTOOL_POINT_H
#include "influxdblptool/collections.h"
#include "influxdblptool/string_types.h"
#include <chrono>
#include <vector>

/// This is the main namespace. Users of this library only need to use this namespace.
namespace influxdblptool {

    /// \brief The option_timestamp can be used to provide a time_point or nothing.
    ///
    /// This allows for selectively disable timestamps on points.
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

    /// \brief timestamp_resolution enumeration is used for changing the timestamp resolution on point or points.
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
        /// Base class for types that allow setting a prefix or timestamp_resolution. points and point both need
        /// this functionality.
        class serializable_config {
            std::string prefix_{};
            timestamp_resolution timestamp_resolution_{timestamp_resolution::nanoseconds};
        public:
            /// Set the timestamp resolution to be used during serialization.
            /// \param ts The timestamp_resolution
            void set_current_timestamp_resolution(timestamp_resolution ts) {
                timestamp_resolution_ = ts;
            }

            /// Returns the timestamp resolution to be used during serialization.
            /// \return the timestamp resolution to be used during serialization.
            [[nodiscard]] timestamp_resolution current_timestamp_resolution() const {
                return timestamp_resolution_;
            }

            /// Set the prefix to prepend for each point that is serialized.
            /// \param p The prefix to prepend for each point that is serialized.
            void set_prefix(const prefix_base &p) {
                prefix_ = p.get();
            }

            /// Returns the prefix to prepend for each point that is serialized.
            /// \return The prefix to prepend for each point that is serialized.
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

        /// A point aggregate that accepts any any point type.
        /// This is templated to enable unit testing with fakes.
        /// \tparam Point the type of point in this collectin.
        template <typename Point>
        class points : public serializable_config {
            std::vector<Point> points_{};
        public:

            /// Reserve size when you know the amount of points you are going to add. This decreases allocations.
            /// \param size The vector size
            void reserve(typename std::vector<Point>::size_type size) {
                points_.reserve(size);
            }

            /// Output operator that accepts a point.
            /// \param p The point to add to points.
            /// \return A reference to the object the point is outputted to.
            points<Point>& operator<<(Point p) {
                points_.emplace_back(std::move(p));
                return *this;
            }

            /// Cast operator that returns a const reference to the vector<Point> member field.
            /// \return a const reference to the vector<Point> member field.
            explicit operator const std::vector<Point>&() const {
                return points_;
            }
        };

    }

    /// Output operator that accepts an object of timestamp_resolution.
    /// This is used to change the resolution of timestamps serialization.
    /// \tparam A type inheriting intern::serializable_config, basically point or points.
    /// \param o An object of type inheriting intern::serializable_config, basically point or points.
    /// \param tr An object of timestamp_resolution.
    /// \return The operator returns a reference to the object of type inheriting intern::serializable_config, basically point or points.
    template<typename Type>
    typename std::enable_if<std::is_base_of_v<intern::serializable_config,Type>,Type>::type&
    operator<<(Type& o,timestamp_resolution tr) {
        o.set_current_timestamp_resolution(tr);
        return o;
    }

    /// Output operator that accepts an object implementing prefix_base.
    /// This is used to allow a prefix for each serialized point to be enabled.
    /// \tparam A type inheriting intern::serializable_config, basically point or points.
    /// \param o An object of type inheriting intern::serializable_config, basically point or points.
    /// \param p An object implementing prefix_base.
    /// \return The operator returns a reference to the object of type inheriting intern::serializable_config, basically point or points.
    template<typename Type>
    typename std::enable_if<std::is_base_of_v<intern::serializable_config,Type>,Type>::type&
    operator<<(Type& o,const prefix_base& p) {
        o.set_prefix(p);
        return o;
    }

    /// \brief This is a serializable point template that allows for a different implementation for now being passed as
    //// a parameter. Used for testing.
    template <auto now>
    using point_custom_timestamp = intern::point<measurement_value, tags_map, fields_map, now>;
    /// \brief This is a serializable point. See examples how to use this.
    using point = point_custom_timestamp<std::chrono::system_clock::now>;
    /// \brief This is a serializable collection of point. See examples how to use this.
    using points = intern::points<point>;

}

/// \example example01.cpp
/// \example example02.cpp
/// \example example03.cpp
/// \example example04.cpp
/// \example example05.cpp
/// \example example06.cpp
/// \example example07.cpp
/// \example example08.cpp
/// \example example09.cpp

#endif //INFLUXDBLPTOOL_POINT_H
