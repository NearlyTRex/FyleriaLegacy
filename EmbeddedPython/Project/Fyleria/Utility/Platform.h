// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_PLATFORM_H_
#define _GECKO_UTILITY_PLATFORM_H_

// Target headers
#if __APPLE__
#include "TargetConditionals.h"
#elif _MSC_VER
#include "SDKDDKVer.h"
#endif

// x86-32 architecture
#if defined(_M_IX86) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386)
#define PLATFORM_ARCH_X86_32
#endif

// x86-64 architecture
#if defined(_M_X64) || defined(_M_AMD64) || defined(__ia64__) || defined(__x86_64__) || defined(_WIN64)
#define PLATFORM_ARCH_X86_64
#endif

// 32-bit architecture
#if defined(PLATFORM_ARCH_X86_32)
#define PLATFORM_32_BIT
#else
#define PLATFORM_64_BIT
#endif

// Endianness
#if (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || defined(PLATFORM_ARCH_X86_32) || defined(PLATFORM_ARCH_X86_64)
#define PLATFORM_LITTLE_ENDIAN
#else
#define PLATFORM_BIG_ENDIAN
#endif

// Posix
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
#define PLATFORM_POSIX
#endif

// Linux operating system
#if (defined(__linux) || defined(__linux__) || defined(__gnu_linux__)) && !defined(__ANDROID__) && !defined(__ANDROID_API__)
#define PLATFORM_OS_LINUX
#endif

// Windows operating system
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WINDOWS__) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__MINGW64__)
#define PLATFORM_OS_WINDOWS
#endif

// Specific windows versions
#if defined(PLATFORM_OS_WINDOWS) && (_WIN32_WINNT == _WIN32_WINNT_VISTA)
#define PLATFORM_OS_WINDOWS_VISTA
#elif defined(PLATFORM_OS_WINDOWS) && (_WIN32_WINNT == _WIN32_WINNT_WIN7)
#define PLATFORM_OS_WINDOWS_7
#elif defined(PLATFORM_OS_WINDOWS) && (_WIN32_WINNT == _WIN32_WINNT_WIN8)
#define PLATFORM_OS_WINDOWS_8
#elif defined(PLATFORM_OS_WINDOWS) && (_WIN32_WINNT == _WIN32_WINNT_WINBLUE)
#define PLATFORM_OS_WINDOWS_8_1
#elif defined(PLATFORM_OS_WINDOWS) && (_WIN32_WINNT == _WIN32_WINNT_WIN10)
#define PLATFORM_OS_WINDOWS_10
#endif

// MacOSX operating system
#if defined(__APPLE__) && defined(__MACH__) && (TARGET_OS_MAC == 1) && (TARGET_OS_IPHONE == 0)
#define PLATFORM_OS_MACOS
#endif

// iOS operating system
#if defined(__APPLE__) && defined(__MACH__) && ((TARGET_IPHONE_SIMULATOR == 1) || (TARGET_OS_IPHONE == 1))
#define PLATFORM_OS_IOS
#endif

// Android operating system
#if defined(__ANDROID__) || defined(__ANDROID_API__)
#define PLATFORM_OS_ANDROID
#endif

#endif
