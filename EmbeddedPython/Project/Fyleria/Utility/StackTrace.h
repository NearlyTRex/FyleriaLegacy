// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_STACKTRACE_H_
#define _GECKO_UTILITY_STACKTRACE_H_

// Internal includes
#include "Utility/Types.h"

// System includes
#include <signal.h>

// External includes
#if defined(PLATFORM_OS_WINDOWS)
    #define __attribute__(param)
    #define backtrace(buffer, size) (0)
    #define BACKWARD_CXX11
    #define BACKWARD_ATLEAST_CXX11
    #define BACKWARD_ATLEAST_CXX98
#endif
#include <backward.hpp>
#if defined(PLATFORM_OS_WINDOWS)
    #undef backtrace
    #undef __attribute__
    #include <windows.h>
#endif

// Printer defines
#define StackTracePrinterColorAutomatic backward::ColorMode::automatic
#define StackTracePrinterColorAlways backward::ColorMode::always
#define StackTracePrinterColorNone backward::ColorMode::never

namespace Gecko
{

// Thread ID
typedef FixedUnsigned64 ThreadID;

// Signal handler
typedef backward::SignalHandling SignalHandler;

// Stack trace
#if defined(PLATFORM_OS_WINDOWS)
    typedef STDPair<BoostStacktrace, ThreadID> StackTrace;
#else
    typedef backward::StackTrace StackTrace;
#endif
typedef backward::Printer StackTracePrinter;
typedef backward::TraceResolver StackTraceResolver;
typedef backward::ResolvedTrace StackResolvedTrace;

// Register signal handler
void RegisterSignalHandler();

// Get current stacktrace
StackTrace GetStacktrace();

// Get signal string representation
String GetSignalAsString(Int iSignal);

// Dump the given stacktrace
void DumpStacktrace(STDOutputStream& sStream, const StackTrace& stackTrace);

};

#endif
