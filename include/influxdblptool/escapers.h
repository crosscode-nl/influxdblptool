#ifndef INFLUXDBLPTOOL_ESCAPERS_H
#define INFLUXDBLPTOOL_ESCAPERS_H
#include <algorithm>
#include <sstream>
#include <array>

/// The escapers namespace contains all escapers. It is internally used by this library.
namespace influxdblptool::escapers {

    /// Escapes a string_view to become an acceptable input as a measurement.
    /// Escapes commas and spaces.
    /// \param The string_view to be escaped.
    /// \return The escaped string.
    std::string escape_measurement_value(std::string_view s);

    /// Escapes a string_view to become an acceptable input as a tag key.
    /// Escapes commas, equal signs and spaces.
    /// \param The string_view to be escaped.
    /// \return The escaped string.
    std::string escape_tag_key(std::string_view s);

    /// Escapes a string_view to become an acceptable input as a tag value.
    /// Escapes commas, equal signs and spaces.
    /// \param The string_view to be escaped.
    /// \return The escaped string.
    std::string escape_tag_value(std::string_view s);

    /// Escapes a string_view to become an acceptable input as a field key.
    /// Escapes commas, equal signs and spaces.
    /// \param The string_view to be escaped.
    /// \return The escaped string.
    std::string escape_field_key(std::string_view s);

    /// Escapes a string_view to become an acceptable input as a field string value.
    /// Escapes backslashes and double quotes.
    /// \param The string_view to be escaped.
    /// \return The escaped string.
    std::string escape_field_string_value(std::string_view s);

}

#endif //INFLUXDBLPTOOL_ESCAPERS_H
