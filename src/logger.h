#ifndef ALOGGING_LOGGER_H_INCLUDED
#define ALOGGING_LOGGER_H_INCLUDED

#include <cinttypes>
#include <cstdarg>
#include <cstddef>
#ifndef ARDUINO
#undef min
#undef max
#include <string>
#endif
#include "log_message.h"

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

    LogStream& operator<<(uint32_t i) {
        return printf("%" PRIu32, i);
    }

    LogStream& operator<<(int8_t i) {
        return printf("%d", i);
    }

    LogStream& operator<<(int32_t i) {
        return printf("%" PRId32, i);
    }

    #ifdef ARDUINO // Ick
    LogStream& operator<<(size_t i) {
        return printf("%d", i);
    }
    #else
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

// NOTE: This is a C++11 feature.
template<const char *Name>
class SimpleLog {
public:
    static void log(const char *f, ...) __attribute__((format(printf, 1, 2))) {
        va_list args;
        va_start(args, f);
        vlogf(LogLevels::INFO, Name, f, args);
        va_end(args);
    }

    static void info(const char *f, ...) __attribute__((format(printf, 1, 2))) {
        va_list args;
        va_start(args, f);
        vlogf(LogLevels::INFO, Name, f, args);
        va_end(args);
    }

    static void trace(const char *f, ...) __attribute__((format(printf, 1, 2))) {
        va_list args;
        va_start(args, f);
        vlogf(LogLevels::TRACE, Name, f, args);
        va_end(args);
    }

    static void warn(const char *f, ...) __attribute__((format(printf, 1, 2))) {
        va_list args;
        va_start(args, f);
        vlogf(LogLevels::WARN, Name, f, args);
        va_end(args);
    }

    static void error(const char *f, ...) __attribute__((format(printf, 1, 2))) {
        va_list args;
        va_start(args, f);
        vlogf(LogLevels::ERROR, Name, f, args);
        va_end(args);
    }

};

#endif
