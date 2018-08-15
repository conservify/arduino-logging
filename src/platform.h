#ifndef ALOGGING_PLATFORM_H_INCLUDED
#define ALOGGING_PLATFORM_H_INCLUDED

#include "log_stream.h"
#include "logging_arduino.h"
#include "logging_linux.h"

void alogging_platform_abort();

constexpr char endl = '\n';

using ostreamtype = LogStream;

ostreamtype sdebug();

#endif // ALOGGING_PLATFORM_H_INCLUDED
