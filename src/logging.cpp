#include "logging.h"
#include "platform.h"

extern size_t platform_write_fn(const LogMessage *m, const char *line);

static uint32_t always_zero();

static log_message_uptime_fn_t log_uptime_fn = millis;
static log_message_time_fn_t log_time_fn = always_zero;
static log_message_write_fn_t write_fn = platform_write_fn;

static log_message_hook_fn_t log_hook_fn = nullptr;
static void *log_hook_arg = nullptr;
static bool log_hook_enabled = false;

static uint32_t always_zero() {
    return 0;
}

void log_configure_writer(log_message_write_fn_t new_fn) {
    write_fn = new_fn;
}

void log_configure_hook_register(log_message_hook_fn_t hook, void *arg) {
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
    char formatted[ArduinoLoggingLineMax * 2];
    auto pos = snprintf(formatted, sizeof(formatted) - 3, "%06" PRIu32 " %-25s ", m->uptime, m->facility);
    auto len = strlen(m->message);
    memcpy(formatted + pos, m->message, len);
    pos += len;
    #if defined(ARDUINO_LOGGING_INCLUDE_CR)
    formatted[pos + 0] = '\r';
    formatted[pos + 1] = '\n';
    formatted[pos + 2] = 0;
    #else
    formatted[pos + 0] = '\n';
    formatted[pos + 1] = 0;
    #endif // defined(ARDUINO_LOGGING_INCLUDE_CR)

    if (write_fn != nullptr) {
        write_fn(m, formatted);
    }

    if (log_hook_fn != nullptr) {
        if (log_hook_enabled) {
            log_hook_enabled = false;
            log_hook_fn(m, formatted, log_hook_arg);
            log_hook_enabled = true;
        }
    }
}

void vlogf(LogLevels level, const char *facility, const char *f, va_list args) {
    char message[ArduinoLoggingLineMax];
    vsnprintf(message, ArduinoLoggingLineMax, f, args);

    LogMessage m;
    m.uptime = log_uptime_fn();
    m.time = log_time_fn();
    m.level = (uint8_t)level;
    m.facility = facility;
    m.message = message;

    log_raw(&m);
}

void logf(LogLevels level, const char *facility, const char *f, ...) {
    va_list args;
    va_start(args, f);
    vlogf(level, facility, f, args);
    va_end(args);
}

void logerrorf(const char *facility, const char *f, ...) {
    va_list args;
    va_start(args, f);
    vlogf(LogLevels::ERROR, facility, f, args);
    va_end(args);
}

void logtracef(const char *facility, const char *f, ...) {
    va_list args;
    va_start(args, f);
    vlogf(LogLevels::TRACE, facility, f, args);
    va_end(args);
}

void loginfof(const char *facility, const char *f, ...) {
    va_list args;
    va_start(args, f);
    vlogf(LogLevels::INFO, facility, f, args);
    va_end(args);
}