#ifndef _PYTHON3_EXTRA_PYCONFIG_H_
#define _PYTHON3_EXTRA_PYCONFIG_H_

// Python path
#ifndef PYTHONPATH
    #define PYTHONPATH ""
#endif

// Prefix
#ifndef PREFIX
    #define PREFIX ""
#endif

// Executable prefix
#ifndef EXEC_PREFIX
    #define EXEC_PREFIX ""
#endif

// Virtual path
#ifndef VPATH
    #define VPATH ""
#endif

// Version
#ifndef VERSION
    #define VERSION "3.9.0"
#endif

// Include the correct pyconfig.h
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
    #include "pyconfig-windows.h"
#elif defined(__linux__) && defined(__i386__)
    #include "pyconfig-linux_x86_32.h"
#elif defined(__linux__) && defined(__x86_64__)
    #include "pyconfig-linux_x86_64.h"
#endif

#endif
