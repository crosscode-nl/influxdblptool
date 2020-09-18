#ifndef INFLUXDBLPTOOL_TAGKEY_H
#define INFLUXDBLPTOOL_TAGKEY_H

#include "abstractions/ikey.h"
#include "escapers/escaper.h"
#include "validators/keyvalidator.h"

namespace influxdblptool {

    using TagKey = IKey<TagKeyValidator,TagKeyEscaper>;

}

#endif //INFLUXDBLPTOOL_TAGKEY_H
