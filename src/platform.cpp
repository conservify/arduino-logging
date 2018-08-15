#include "logging.h"
#include "platform.h"

ostreamtype sdebug() {
    return LogStream{ };
}
