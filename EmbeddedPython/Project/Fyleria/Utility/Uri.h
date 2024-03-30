// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_URI_H_
#define _GECKO_UTILITY_URI_H_

// External includes
#include <uriparser/Uri.h>

// Internal includes
#include "Utility/Platform.h"

// External function defines
#if defined(PLATFORM_OS_WINDOWS)
    #define ParseFilenameAsUri uriWindowsFilenameToUriStringA
#else
    #define ParseFilenameAsUri uriUnixFilenameToUriStringA
#endif

#endif
