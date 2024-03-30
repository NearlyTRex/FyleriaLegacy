#ifndef _CPPFS_EXTRA_WINDOWS_H_
#define _CPPFS_EXTRA_WINDOWS_H_

// Include the correct windows.h
#if defined(__MINGW32__) || defined(__MINGW64__)
#define _WIN32_WINNT 0x0600
#include <windows.h>
#endif

#endif
