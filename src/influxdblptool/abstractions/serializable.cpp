#include "influxdblptool/abstractions/serializable.h"

namespace influxdblptool::abstractions {

    std::ostream &operator<<(std::ostream &os, const ISerializable &serializable) {
        serializable.serialize(os);
        return os;
    }
}