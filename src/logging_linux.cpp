#if !defined(ARDUINO)

#include <cstdio>
#include <cstdlib>
#include <time.h>

#include "logging_linux.h"
#include "logging.h"

static uint64_t epoch = 0;

#ifdef __cplusplus
extern "C" {
#endif

uint32_t millis() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    auto now  = (uint64_t)ts.tv_sec * (uint64_t)1000 + (uint64_t)(ts.tv_nsec / 1000000L);
    if (epoch == 0) {
        epoch = now;
    }
    return (uint32_t)(now - epoch);
}

size_t platform_write_fn(const LogMessage *m, const char *fstring, va_list args) {
    fprintf(stderr, "%08" PRIu32 " %s: ", m->uptime, m->facility);
    vfprintf(stderr, fstring, args);
    fprintf(stderr, "\n");
    return 0;
}

void alogging_platform_abort() {
    abort();
}

#ifdef __cplusplus
}
#endif

#endif // !defined(ARDUINO)
