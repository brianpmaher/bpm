#pragma once

//
// SIMD detection.
//

#include "base.h"

#define SIMD_ENABLED 1

#if SIMD_ENABLED
    #if PLATFORM_WINDOWS || PLATFORM_LINUX || PLATFORM_MAC
        #if COMPILER_MSVC
            #if defined(_M_AMD64) || defined(_M_X64)
                #define SIMD_USE_SSE 1
                #define SIMD_USE_SSE2 1
            #elif defined(_M_IX86) && defined(_M_IX86_FP) && _M_IX86_FP >= 2
                #define SIMD_USE_SSE 1
                #define SIMD_USE_SSE2 1
            #elif defined(_M_IX86) && defined(_M_IX86_FP) && _M_IX86_FP >= 1
                #define SIMD_USE_SSE 1
            #endif
        #elif COMPILER_GCC || COMPILER_CLANG
            #ifdef __SSE2__
                #define SIMD_USE_SSE 1
                #define SIMD_USE_SSE2 1
            #elif defined(__SSE__)
                #define SIMD_USE_SSE 1
            #endif
            #ifdef __AVX__
                #define SIMD_USE_AVX 1
            #endif
            #ifdef __AVX2__
                #define SIMD_USE_AVX2 1
            #endif
        #endif
    #endif
    #if PLATFORM_IOS || PLATFORM_MAC || PLATFORM_ANDROID
        #ifdef __ARM_NEON
            #define SIMD_USE_NEON 1
        #endif
    #endif
    #if PLATFORM_WEB && COMPILER_EMSCRIPTEN
        #ifdef __wasm_simd128__
            #define SIMD_USE_WASM_SIMD 1
        #endif
    #endif
#endif

#ifndef SIMD_USE_SSE
    #define SIMD_USE_SSE 0
#endif
#ifndef SIMD_USE_SSE2
    #define SIMD_USE_SSE2 0
#endif
#ifndef SIMD_USE_AVX
    #define SIMD_USE_AVX 0
#endif
#ifndef SIMD_USE_AVX2
    #define SIMD_USE_AVX2 0
#endif
#ifndef SIMD_USE_NEON
    #define SIMD_USE_NEON 0
#endif
#ifndef SIMD_USE_WASM_SIMD
    #define SIMD_USE_WASM_SIMD 0
#endif

#if SIMD_USE_SSE
    #include <xmmintrin.h>
#endif
#if SIMD_USE_SSE2
    #include <emmintrin.h>
#endif
#if SIMD_USE_AVX
    #include <immintrin.h>
#endif
#if SIMD_USE_NEON
    #include <arm_neon.h>
#endif
#if SIMD_USE_WASM_SIMD
    #include <wasm_simd128.h>
#endif
