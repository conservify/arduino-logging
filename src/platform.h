#ifndef ALOGGING_PLATFORM_H_INCLUDED
#define ALOGGING_PLATFORM_H_INCLUDED

#include "logging_arduino.h"
#include "logging_linux.h"

void alogging_platform_abort();

extern ostreamtype &clog;

inline ostreamtype &sdebug() {
    return clog;
}

#endif // ALOGGING_PLATFORM_H_INCLUDED
