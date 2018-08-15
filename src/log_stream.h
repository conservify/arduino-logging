#ifndef ALOGGING_LOG_STREAM_H_INCLUDED
#define ALOGGING_LOG_STREAM_H_INCLUDED

#include <cinttypes>
#include <cstdarg>
#include <cstddef>

#include "logging.h"

#ifndef ARDUINO
#include <string>
#endif

class LogStream {
private:
    const char *facility { "Root" };
    LogLevels level { LogLevels::INFO };
    uint8_t message[ArduinoLoggingLineMax];
    uint32_t position{ 0 };

public:
    LogStream() {
    }

    LogStream(const char *facility, LogLevels level = LogLevels::INFO) : facility(facility), level(level) {
    }

    ~LogStream();

public:
    LogStream& printf(const char *f, ...) __attribute__((format(printf, 2, 3)));
    LogStream& print(const char *str);
    LogStream& flush();

public:
    LogStream& operator<<(uint8_t i) {
        return printf("%d", i);
    }

    LogStream& operator<<(uint16_t i) {
        return printf("%d", i);
    }

    LogStream& operator<<(uint32_t i) {
        return printf("%" PRIu32, i);
    }

    LogStream& operator<<(uint64_t i) {
        return printf("%" PRIu64, i);
    }

    LogStream& operator<<(int8_t i) {
        return printf("%d", i);
    }

    LogStream& operator<<(int16_t i) {
        return printf("%d", i);
    }

    LogStream& operator<<(int32_t i) {
        return printf("%" PRId32, i);
    }

    LogStream& operator<<(int64_t i) {
        return printf("%" PRId64, i);
    }

    LogStream& operator<<(size_t i) {
        return printf("%zd", i);
    }

    #if !defined(ARDUINO)
    LogStream& operator<<(std::string &v) {
        return printf("%s", v.c_str());
    }
    #endif

    LogStream& operator<<(double v) {
        return printf("%f", v);
    }

    LogStream& operator<<(float v) {
        return printf("%f", v);
    }

    LogStream& operator<<(const char c) {
        return printf("%c", c);
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
