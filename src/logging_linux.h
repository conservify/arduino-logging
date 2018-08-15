#ifndef ALOGGING_LOGGING_LINUX_H_INCLUDED
#define ALOGGING_LOGGING_LINUX_H_INCLUDED

#ifndef ARDUINO

#include <cinttypes>
#include <ostream>

uint32_t millis();

constexpr char endl = '\n';

using ostreamtype = ::std::ostream;

#endif // !ARDUINO

#endif // ALOGGING_LOGGING_LINUX_H_INCLUDED
