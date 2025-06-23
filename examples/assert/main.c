#include <bpm/core.h>

#include <stdio.h>

int main(void) {
    print_lib_info();
    printf("There should be an assertion failure below.\n");
    assert(false, "This assertion should fail");
    return 0;
}
