#include <bpm/core.h>

#include <stdio.h>
#include <stdlib.h>

void _assert_fail(const char* expression, const char* message, const char* file, int line) {
    fprintf(stderr, "[ASSERT] %s: %s (%s:%d)\n", expression, message, file, line);
    exit(EXIT_FAILURE);
}
