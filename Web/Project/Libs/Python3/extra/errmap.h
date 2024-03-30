#ifndef _PYTHON3_EXTRA_ERRMAP_H_
#define _PYTHON3_EXTRA_ERRMAP_H_

// Include the correct errmap.h
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
#include "windows-errmap.h"
#endif

#endif
