#ifndef _PYTHON3_EXTRA_PYCONFIG_H_
#define _PYTHON3_EXTRA_PYCONFIG_H_

// Include the correct pyconfig.h
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
    #include "windows-pyconfig.h"
#elif defined(__linux__) && defined(__i386__)
    #include "linux_x86_32-pyconfig.h"
#elif defined(__linux__) && defined(__x86_64__)
    #include "linux_x86_64-pyconfig.h"
#elif defined(__linux__) && defined(__ppc__)
    #include "linux_ppc_32-pyconfig.h"
#elif defined(__linux__) && defined(__ppc64__)
    #include "linux_ppc_64-pyconfig.h"
#endif

#endif
