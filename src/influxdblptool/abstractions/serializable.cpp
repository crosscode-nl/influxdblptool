#include "influxdblptool/abstractions/serializable.h"

namespace influxdblptool::abstractions {

    std::ostream &operator<<(std::ostream &os, const serializable &serializable) {
        serializable.serialize(os);
        return os;
    }
}