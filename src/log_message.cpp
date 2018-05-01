#include "log_message.h"

#include <cstring>
#include <cstdio>
#include <cinttypes>

static uint32_t always_zero();

static log_message_hook_fn_t log_hook_fn = nullptr;
static void *log_hook_arg = nullptr;
static bool log_hook_enabled = false;

#ifdef ARDUINO
static Stream *log_uart = &Serial;

static log_message_uptime_fn_t log_uptime_fn = millis;

void log_uart_set(Stream &standardOut) {
    log_uart = &standardOut;
}

Stream *log_uart_get() {
    return log_uart;
}
#else
#include <time.h>

static uint64_t epochMillis = 0;

static uint32_t millis() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    auto now  = (uint64_t)ts.tv_sec * (uint64_t)1000 + (uint64_t)(ts.tv_nsec / 1000000L);
    // This isn't "Correct" because this sets epoch to the time of the first call.
    if (epochMillis == 0) {
        epochMillis = now;
    }
    return (uint32_t)(now - epochMillis);
}

static log_message_uptime_fn_t log_uptime_fn = millis;
#endif
static log_message_time_fn_t log_time_fn = always_zero;

static uint32_t always_zero() {
    return 0;
}

void log_add_hook(log_message_hook_fn_t hook, void *arg) {
    log_hook_fn = hook;
    log_hook_arg = arg;
    log_hook_enabled = true;
}

void log_configure_hook(bool enabled) {
    log_hook_enabled = enabled;
}

void log_configure_time(log_message_uptime_fn_t uptime_fn, log_message_time_fn_t time_fn) {
    log_uptime_fn = uptime_fn == nullptr ? always_zero : uptime_fn;
    log_time_fn = time_fn == nullptr ? always_zero : time_fn;
}

void log_raw(const LogMessage *m) {
    char formatted[ArdunioLoggingLineMax * 2];
    auto pos = snprintf(formatted, sizeof(formatted) - 3, "%06" PRIu32 " %-25s ", m->uptime, m->facility);
    auto len = strlen(m->message);
    memcpy(formatted + pos, m->message, len);
    pos += len;
    #if ARDUINO_LOGGING_INCLUDE_CR
    formatted[pos + 0] = '\r';
    formatted[pos + 1] = '\n';
    formatted[pos + 2] = 0;
    #else
    formatted[pos + 0] = '\n';
    formatted[pos + 1] = 0;
    #endif

    #ifdef ARDUINO
    log_uart->print(formatted);
    #else
    fprintf(stderr, "%s", formatted);
    #endif

    if (log_hook_fn != nullptr) {
        if (log_hook_enabled) {
            log_hook_enabled = false;
            log_hook_fn(m, formatted, log_hook_arg);
            log_hook_enabled = true;
        }
    }
}

void vlogf(LogLevels level, const char *facility, const char *f, va_list args) {
    char message[ArdunioLoggingLineMax];
    vsnprintf(message, ArdunioLoggingLineMax, f, args);

    LogMessage m = {
        .uptime = log_uptime_fn(),
        .time = log_time_fn(),
        .level = (uint8_t)level,
        .facility = facility,
        .message = message,
    };

    log_raw(&m);
}

void logf(LogLevels level, const char *facility, const char *f, ...) {
    va_list args;
    va_start(args, f);
    vlogf(level, facility, f, args);
    va_end(args);
}

void logfpln(const char *facility, const char *f, ...) {
    va_list args;
    va_start(args, f);
    vlogf(LogLevels::INFO, facility, f, args);
    va_end(args);
}
