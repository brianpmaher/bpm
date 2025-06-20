//
// Compiler detection
//

#if defined(EMSCRIPTEN)
    #define COMPILER_EMSCRIPTEN 1
#elif defined(__clang__)
    #define COMPILER_CLANG 1
#elif defined(__GNUC__) || defined(__GNUG__)
    #define COMPILER_GCC 1
#elif defined(_MSC_VER)
    #define COMPILER_MSVC 1
#else
    #error "Unknown compiler"
#endif

#ifndef COMPILER_EMSCRIPTEN
    #define COMPILER_EMSCRIPTEN 0
#endif
#ifndef COMPILER_CLANG
    #define COMPILER_CLANG 0
#endif
#ifndef COMPILER_GCC
    #define COMPILER_GCC 0
#endif
#ifndef COMPILER_MSVC
    #define COMPILER_MSVC 0
#endif

//
// Standard version check
//

#if COMPILER_MSVC
    #if _MSC_VER < 1800
        #error "C11 or later is required"
    #endif
#elif COMPILER_GCC || COMPILER_CLANG || COMPILER_EMSCRIPTEN
    #if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
        #error "C11 or later is required"
    #endif
#else
    #error "Unknown compiler"
#endif

//
// Platform detection
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define PLATFORM_WINDOWS 1
    #ifndef _WIN64
        #error "64-bit Windows is required"
    #endif
#elif defined(__linux__) || defined(__gnu_linux__)
    #define PLATFORM_LINUX 1
    #if defined(__ANDROID__)
        #define PLATFORM_ANDROID 1
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #define PLATFORM_APPLE 1
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
        #define PLATFORM_IOS 1
        #define PLATFORM_IOS_SIMULATOR 1
    #elif TARGET_OS_IPHONE
        #define PLATFORM_IOS 1
    #elif TARGET_OS_MAC
        #define PLATFORM_MAC 1
    #else
        #error "Unknown Apple platform"
    #endif
#elif defined(EMSCRIPTEN)
    #define PLATFORM_WEB 1
#else
    #error "Unknown platform"
#endif

#ifndef PLATFORM_WINDOWS
    #define PLATFORM_WINDOWS 0
#endif
#ifndef PLATFORM_LINUX
    #define PLATFORM_LINUX 0
#endif
#ifndef PLATFORM_ANDROID
    #define PLATFORM_ANDROID 0
#endif
#ifndef PLATFORM_APPLE
    #define PLATFORM_APPLE 0
#endif
#ifndef PLATFORM_IOS
    #define PLATFORM_IOS 0
#endif
#ifndef PLATFORM_IOS_SIMULATOR
    #define PLATFORM_IOS_SIMULATOR 0
#endif
#ifndef PLATFORM_MAC
    #define PLATFORM_MAC 0
#endif
#ifndef PLATFORM_WEB
    #define PLATFORM_WEB 0
#endif

//
// Dynamic library
//

#ifdef DLL_EXPORT
    #if COMPILER_MSVC
        #define API __declspec(dllexport)
    #elif COMPILER_GCC || COMPILER_CLANG || COMPILER_EMSCRIPTEN
        #define API __attribute__((visibility("default")))
    #else
        #define API
    #endif
#else
    #if COMPILER_MSVC
        #define API __declspec(dllimport)
    #elif COMPILER_GCC || COMPILER_CLANG || COMPILER_EMSCRIPTEN
        #define API
    #else
        #define API
    #endif
#endif

//
// Assertions
//

#if COMPILER_MSVC
    #include <intrin.h>
    #define debug_break() __debugbreak()
#elif COMPILER_GCC || COMPILER_CLANG || COMPILER_EMSCRIPTEN
    #define debug_break() __builtin_trap()
#else
    #error "Unknown compiler"
#endif

API void _assert_fail(const char* expression, const char* message, const char* file, int line);
#define _get_assert_macro(_1, _2, NAME, ...) NAME
#define _assert1(expression) \
    do { \
        if (!(expression)) { \
            _assert_fail(#expression, "Assertion failed", __FILE__, __LINE__); \
            debug_break(); \
        } \
    } while (0)
#define _assert2(expression, message) \
    do { \
        if (!(expression)) { \
            _assert_fail(#expression, message, __FILE__, __LINE__); \
            debug_break(); \
        } \
    } while (0)
#define assert(...) _get_assert_macro(__VA_ARGS__, _assert2, _assert1)(__VA_ARGS__)

//
// Types
//

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

typedef bool b8;
typedef uint16_t b16;
typedef uint32_t b32;
typedef uint64_t b64;

//
// SIMD
//

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
