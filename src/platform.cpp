#include "logging.h"
#include "platform.h"

ostreamtype sdebug() {
    return LogStream{ };
}

extern "C" {

void __assert_func(const char *file, int32_t line, const char *func, const char *failedexpr) {
    logerrorf("assertion \"%s\" failed: file \"%s\", line %d%s%s\n",
              failedexpr, file, line,
              func ? ", function: " : "", func ? func : "");
    alogging_platform_abort();
    /* NOTREACHED */
}

}
