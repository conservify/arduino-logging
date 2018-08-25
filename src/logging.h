#ifndef ALOGGING_LOGGING_H_INCLUDED
#define ALOGGING_LOGGING_H_INCLUDED

#include <cinttypes>
//#include <cstring>
#include <cstddef>
#include <cstdarg>
#include <cstdio>

constexpr size_t ArduinoLoggingLineMax = 255;

enum class LogLevels {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
};

typedef struct LogMessage {
    uint32_t uptime;
    uint32_t time;
    uint8_t level;
    const char *facility;
    const char *message;
} LogMessage;

typedef size_t (*log_message_write_fn_t)(const LogMessage *m, const char *line);

typedef size_t (*log_message_hook_fn_t)(const LogMessage *m, const char *formatted, void *arg);

typedef uint32_t (*log_message_time_fn_t)();

typedef uint32_t (*log_message_uptime_fn_t)();

#ifdef __cplusplus
extern "C" {
#endif

void log_configure_writer(log_message_write_fn_t writer);

void log_configure_hook_register(log_message_hook_fn_t hook, void *arg);

void log_configure_hook(bool enabled);

void log_configure_time(log_message_uptime_fn_t uptime_fn, log_message_time_fn_t time_fn);

void log_raw(const LogMessage *m);

void valogf(LogLevels level, const char *facility, const char *f, va_list args);

void alogf(LogLevels level, const char *facility, const char *f, ...) __attribute__((format(printf, 3, 4)));

void logerrorf(const char *facility, const char *f, ...) __attribute__((format(printf, 2, 3)));

void logtracef(const char *facility, const char *f, ...) __attribute__((format(printf, 2, 3)));

void loginfof(const char *facility, const char *f, ...) __attribute__((format(printf, 2, 3)));

#ifdef __cplusplus
}
#endif

#endif
