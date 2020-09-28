#include "influxdblptool/point.h"

namespace influxdblptool {

    using namespace std::literals;

    namespace time {

        std::chrono::system_clock::time_point now()
        {
            return std::chrono::system_clock::now();
        }

    }

    [[nodiscard]] std::string insert_prefix::get() const {
        return "INSERT "s;
    }

}