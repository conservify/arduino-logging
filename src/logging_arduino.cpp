#include "logging_arduino.h"

#if defined(ARDUINO)

static Stream *log_uart = &Serial;

void log_uart_set(Stream &standardOut) {
    log_uart = &standardOut;
}

Stream *log_uart_get() {
    return log_uart;
}

size_t platform_write_fn(const LogMessage *m, const char *line) {
    log_uart->print(line);
    return 0;
}

#endif // defined(ARDUINO)
