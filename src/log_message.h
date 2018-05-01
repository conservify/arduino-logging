#ifndef ALOGGING_LOG_MESSAGE_H_INCLUDED
#define ALOGGING_LOG_MESSAGE_H_INCLUDED

#include <cstdint>
#include <cstddef>
#include <cstdarg>

constexpr size_t ArdunioLoggingLineMax = 255;

enum class LogLevels {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
};

struct LogMessage {
    uint32_t uptime;
    uint32_t time;
    uint8_t level;
    const char *facility;
    const char *message;
};

typedef size_t (*log_message_hook_fn_t)(const LogMessage *m, const char *formatted, void *arg);

typedef uint32_t (*log_message_time_fn_t)();

typedef uint32_t (*log_message_uptime_fn_t)();

void log_add_hook(log_message_hook_fn_t hook, void *arg);

void log_configure_hook(bool enabled);

void log_configure_time(log_message_uptime_fn_t uptime_fn, log_message_time_fn_t time_fn);

void log_raw(const LogMessage *m);

void vlogf(LogLevels level, const char *facility, const char *f, va_list args);

void logf(LogLevels level, const char *facility, const char *f, ...) __attribute__((format(printf, 3, 4)));

void logfpln(const char *facility, const char *f, ...) __attribute__((format(printf, 2, 3)));

#ifdef ARDUINO
#include <Arduino.h>

void log_uart_set(Stream &standardOut);

Stream *log_uart_get();
#endif

#endif
