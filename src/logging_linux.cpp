#if !defined(ARDUINO)

#include <cstdio>
#include <cstdlib>
#include <time.h>

#include "logging_linux.h"
#include "logging.h"

static uint64_t epoch = 0;

uint32_t millis() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    auto now  = (uint64_t)ts.tv_sec * (uint64_t)1000 + (uint64_t)(ts.tv_nsec / 1000000L);
    // NOTE: This isn't "Correct" because this sets epoch to the time of the first call.
    if (epoch == 0) {
        epoch = now;
    }
    return (uint32_t)(now - epoch);
}

size_t platform_write_fn(const LogMessage *m, const char *line) {
    fprintf(stderr, "%s", line);
    return 0;
}

void alogging_platform_abort() {
    abort();
}

#endif // !defined(ARDUINO)
