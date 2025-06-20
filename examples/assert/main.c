#include <bpm/core.h>

#include <stdio.h>

int main(void) {
    int x = 1;
    int y = 2;
    printf("There should be an assertion failure below.\n");
    assert(x > y, "This assertion should fail");
    return 0;
}
