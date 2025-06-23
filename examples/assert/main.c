#include <bpm/core.h>

#include <stdio.h>

int main(void) {
    printf("There should be an assertion failure below.\n");
    assert(1 == 2, "This assertion should fail");
    return EXIT_SUCCESS;
}
