#ifndef ALOGGING_LOGGER_H_INCLUDED
#define ALOGGING_LOGGER_H_INCLUDED

#include <cstdint>
#include <cstdarg>
#include <cstddef>

#include "log_message.h"

class LogStream {
private:
    LogLevels level { LogLevels::INFO };
    const char *facility { "Root" };
    uint8_t message[ArdunioLoggingLineMax];
    uint32_t position{ 0 };

public:
    LogStream() {
    }

    LogStream(const char *facility, LogLevels level = LogLevels::INFO) : facility(facility), level(level) {
    }

    ~LogStream();

public:
    LogStream& printf(const char *f, ...);
    LogStream& print(const char *str);

public:
    LogStream& operator<<(uint8_t i) {
        return printf("%d", i);
    }

    LogStream& operator<<(uint32_t i) {
        return printf("%lu", i);
    }

    LogStream& operator<<(int8_t i) {
        return printf("%d", i);
    }

    LogStream& operator<<(int32_t i) {
        return printf("%d", i);
    }

    #ifdef ARDUINO // Ick
    LogStream& operator<<(size_t i) {
        return printf("%d", i);
    }
    #endif

    LogStream& operator<<(double v) {
        return printf("%f", v);
    }

    LogStream& operator<<(float v) {
        return printf("%f", v);
    }

    LogStream& operator<<(const char *s) {
        return printf("%s", s);
    }
};

class Logger {
private:
    const char *facility{ "Root" };

public:
    Logger() {
    }

    Logger(const char *facility) : facility(facility) {
    }

public:
    LogStream begin() const;

    LogStream begin(const char *facility) const;

    LogStream operator() () {
        return begin();
    }

    LogStream operator() (const char *facility) {
        return begin(facility);
    }

};

#endif
