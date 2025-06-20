#include <bpm/core.h>

#include <stdio.h>

void _assert_handler(const char* expression, const char* message, const char* file, int line) {
    fprintf(stderr, "[ASSERT] %s: %s (%s:%d)\n", expression, message, file, line);
}
