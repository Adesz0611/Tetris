#ifndef DEBUG_H
#define DEBUG_H

#include <cstdarg>

namespace Debug {
    void Log(const char *format, ...);
    void Error(const char *format, ...);
}

#endif
