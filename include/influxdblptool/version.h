#ifndef INFLUXDBLPTOOL_VERSION_H
#define INFLUXDBLPTOOL_VERSION_H
#include <string_view>

/// Get the semver version of this library. See: https://www.semver.org
/// \return A std::string_view containing the a semver formatted version of this library
std::string_view version();

#endif //INFLUXDBLPTOOL_VERSION_H
