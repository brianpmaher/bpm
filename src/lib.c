#include <bpm/core.h>

#include <stdio.h>

void print_lib_info(void) {
    printf("BPM Library Information:\n");
    printf("\n");
    printf("\tCOMPILER_EMSCRIPTEN: %d\n", COMPILER_EMSCRIPTEN);
    printf("\tCOMPILER_CLANG: %d\n", COMPILER_CLANG);
    printf("\tCOMPILER_GCC: %d\n", COMPILER_GCC);
    printf("\tCOMPILER_MSVC: %d\n", COMPILER_MSVC);
    printf("\n");
    printf("\tPLATFORM_WINDOWS: %d\n", PLATFORM_WINDOWS);
    printf("\tPLATFORM_LINUX: %d\n", PLATFORM_LINUX);
    printf("\tPLATFORM_ANDROID: %d\n", PLATFORM_ANDROID);
    printf("\tPLATFORM_APPLE: %d\n", PLATFORM_APPLE);
    printf("\tPLATFORM_IOS: %d\n", PLATFORM_IOS);
    printf("\tPLATFORM_IOS_SIMULATOR: %d\n", PLATFORM_IOS_SIMULATOR);
    printf("\tPLATFORM_MAC: %d\n", PLATFORM_MAC);
    printf("\tPLATFORM_WEB: %d\n", PLATFORM_WEB);
    printf("\n");
    printf("\tSIMD_ENABLED: %d\n", SIMD_ENABLED);
    printf("\n");
    printf("\tSIMD_USE_SSE: %d\n", SIMD_USE_SSE);
    printf("\tSIMD_USE_SSE2: %d\n", SIMD_USE_SSE2);
    printf("\tSIMD_USE_AVX: %d\n", SIMD_USE_AVX);
    printf("\tSIMD_USE_AVX2: %d\n", SIMD_USE_AVX2);
    printf("\tSIMD_USE_NEON: %d\n", SIMD_USE_NEON);
    printf("\tSIMD_USE_WASM_SIMD: %d\n", SIMD_USE_WASM_SIMD);
}
