#include "Debug.hh"

#include <cstdio>

namespace Debug {
    void Log(const char *format, ...) {
        va_list args;
        va_start (args, format);
        printf("\033[1m\033[36mEngine: \033[0m");
        vprintf(format, args);
        printf("\n");
        va_end(args);
    }
    void Error(const char *format, ...) {
        va_list args;
        va_start (args, format);
        printf("\033[1m\033[31mEngine: \033[0m");
        vprintf(format, args);
        printf("\n");
        va_end(args);
    }
}
