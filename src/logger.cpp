#include <cstdio>
#include <cstring>

#include "logger.h"

LogStream& LogStream::print(const char *str) {
    auto remaining = sizeof(message) - position - 1;
    auto length = strlen(str);
    auto copying = length > remaining ? remaining : length;
    memcpy(message + position, str, copying);
    position += copying;
    message[position] = 0;
    return *this;
}

LogStream& LogStream::printf(const char *f, ...) {
    va_list args;
    va_start(args, f);
    auto remaining = (int32_t)(sizeof(message) - position - 1);
    if (remaining > 0) {
        auto appended = vsnprintf((char *)(message + position), remaining, f, args);
        position += appended;
        message[position] = 0;
    }
    va_end(args);
    return *this;
}

LogStream Logger::begin(const char *facility) const {
    return LogStream{ facility };
}

LogStream Logger::begin() const {
    return LogStream{ facility };
}

LogStream::~LogStream() {
    flush();
}

LogStream& LogStream::flush() {
    if (position > 0) {
        logf(LogLevels::INFO, facility, "%s", message);
        position = 0;
    }
    return *this;
}
