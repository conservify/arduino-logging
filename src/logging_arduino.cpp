#if defined(ARDUINO)

#include <Arduino.h>

#include "logging.h"
#include "logging_arduino.h"

#if !defined(ARDUINO_LOGGING_DISABLE)

static Stream *log_uart = &Serial;

void log_uart_set(Stream &standardOut) {
    log_uart = &standardOut;
}

Stream *log_uart_get() {
    return log_uart;
}

#ifdef __cplusplus
extern "C" {
#endif

size_t platform_write_fn(const LogMessage *m, const char *line) {
    log_uart->print(line);
    return 0;
}

#ifdef __cplusplus
}
#endif

#else

#ifdef __cplusplus
extern "C" {
#endif

size_t platform_write_fn(const LogMessage *m, const char *line) {
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif

#ifdef __cplusplus
extern "C" {
#endif

void alogging_platform_abort() {
    while (true) {
        delay(100);
    }
}

#ifdef __cplusplus
}
#endif

#endif // defined(ARDUINO)
