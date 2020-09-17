#include "influxdblptool/abstractions/iserializable.h"

namespace influxdblptool {

    std::ostream &operator<<(std::ostream &os, const ISerializable &serializable) {
        serializable.serialize(os);
        return os;
    }
}