#include "assert.h"
#include "logging.h"
#include "platform.h"

extern "C" {

void __cfy_assert(const char *assertion, const char *file, int line) {
    logerrorf("assertion \"%s\" failed: file \"%s\", line %d",
              assertion, file, line);
    alogging_platform_abort();
    /* NOTREACHED */
}

}
