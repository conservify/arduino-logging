#ifndef ALOGGING_LOGGING_ARDUINO_H_INCLUDED
#define ALOGGING_LOGGING_ARDUINO_H_INCLUDED

#if defined(ARDUINO)

#include <Arduino.h>

void log_uart_set(Stream &standardOut);

Stream *log_uart_get();

#endif // defined(ARDUINO)

#endif // ALOGGING_LOGGING_ARDUINO_H_INCLUDED
