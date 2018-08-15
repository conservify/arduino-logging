#include <cstdio>
#include <cstring>

#include "log_stream.h"
#include "logging.h"

LogStream& LogStream::print(const char *str) {
    #if !defined(ARDUINO_LOGGING_DISABLE)
    auto remaining = sizeof(message_) - position_ - 1;
    auto length = strlen(str);
    auto copying = length > remaining ? remaining : length;
    memcpy(message_ + position_, str, copying);
    position_ += copying;
    message_[position_] = 0;
    #endif
    return *this;
}

LogStream& LogStream::printf(const char *f, ...) {
    #if !defined(ARDUINO_LOGGING_DISABLE)
    va_list args;
    va_start(args, f);
    auto remaining = (int32_t)(sizeof(message_) - position_ - 1);
    if (remaining > 0) {
        auto appended = vsnprintf((char *)(message_ + position_), remaining, f, args);
        position_ += appended;
        message_[position_] = 0;
    }
    va_end(args);
    #endif
    return *this;
}

LogStream Logger::begin(const char *facility) const {
    return LogStream{ facility };
}

LogStream Logger::begin() const {
    return LogStream{ facility_ };
}

LogStream::~LogStream() {
    flush();
}

LogStream& LogStream::flush() {
    #if !defined(ARDUINO_LOGGING_DISABLE)
    if (position_ > 0) {
        alogf(LogLevels::INFO, facility_, "%s", message_);
        position_ = 0;
    }
    #endif
    return *this;
}
