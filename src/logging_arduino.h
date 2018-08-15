#ifndef ALOGGING_LOGGING_ARDUINO_H_INCLUDED
#define ALOGGING_LOGGING_ARDUINO_H_INCLUDED

#if defined(ARDUINO)

class Stream;

#ifdef __cplusplus
extern "C" {
#endif

uint32_t millis();

#ifdef __cplusplus
}
#endif

#include "log_stream.h"

void log_uart_set(Stream &standardOut);

Stream *log_uart_get();

#endif // defined(ARDUINO)

#endif // ALOGGING_LOGGING_ARDUINO_H_INCLUDED
