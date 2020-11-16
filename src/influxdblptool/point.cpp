#include "influxdblptool/point.h"

namespace crosscode::influxdblptool {

    using namespace std::literals;

    [[nodiscard]] std::string insert_prefix_type::get() const {
        return "INSERT "s;
    }

}
