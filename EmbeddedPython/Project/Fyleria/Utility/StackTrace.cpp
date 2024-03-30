// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Utility/StackTrace.h"
#include "Utility/Logging.h"

namespace Gecko
{

#if defined(PLATFORM_OS_WINDOWS)
void DefaultSignalHandler(Int iSignal)
#else
void DefaultSignalHandler(Int iSignal, siginfo_t* pInfo, void* pContext)
#endif
{
    STDCerr << "Program terminated by signal " << GetSignalAsString(iSignal) << STDEndl;
#if defined(PLATFORM_OS_WINDOWS)
    DumpStacktrace(STDCerr, GetStacktrace());
    STDSignal(iSignal, SIG_DFL);
    STDRaise(iSignal);
#else
    psiginfo(pInfo, "Details");
    DumpStacktrace(STDCerr, GetStacktrace());
    STDRaise(iSignal);
#endif
}

void RegisterSignalHandler()
{
#if defined(PLATFORM_OS_WINDOWS)
    const IntArray vSignals = { SIGSEGV, SIGABRT, SIGFPE, SIGILL };
    for (Int iSignal : vSignals)
    {
        STDSignal(iSignal, DefaultSignalHandler);
    }
#else
    const IntArray vSignals = { SIGSEGV, SIGABRT, SIGBUS, SIGFPE, SIGILL, SIGXCPU, SIGXFSZ };
    for (Int iSignal : vSignals)
    {
        struct sigaction action;
        memset(&action, 0, sizeof(struct sigaction));
        sigfillset(&action.sa_mask);
        action.sa_sigaction = DefaultSignalHandler;
        action.sa_flags = static_cast<Int>(SA_SIGINFO | SA_RESETHAND);
        sigaction(iSignal, &action, nullptr);
    }
#endif
}

StackTrace GetStacktrace()
{
#if defined(PLATFORM_OS_WINDOWS)
    return STDMakePair(BoostStacktrace(), GetCurrentThreadId());
#else
    StackTrace stackTrace;
    stackTrace.load_here();
    return stackTrace;
#endif
}

String GetSignalAsString(Int iSignal)
{
    switch(iSignal)
    {
        case SIGSEGV:
            return "SIGSEGV";
        case SIGABRT:
            return "SIGABRT";
        case SIGILL:
            return "SIGILL";
        case SIGFPE:
            return "SIGFPE";
#if !defined(PLATFORM_OS_WINDOWS)
        case SIGBUS:
            return "SIGBUS";
        case SIGXCPU:
            return "SIGXCPU";
        case SIGXFSZ:
            return "SIGXFSZ";
#endif
        default:
            return "UNK";
    }
}

void DumpStacktrace(STDOutputStream& sStream, const StackTrace& stackTrace)
{
#if defined(PLATFORM_OS_WINDOWS)
    STDVector<StackResolvedTrace> vResolvedTraces;
    SizeType uFrameID = 0;
    for (const auto& stackFrame : stackTrace.first)
    {
        StackResolvedTrace resolvedTrace;
        resolvedTrace.addr = const_cast<void*>(stackFrame.address());
        resolvedTrace.idx = uFrameID++;
        resolvedTrace.source.function = stackFrame.name();
        resolvedTrace.source.filename = stackFrame.source_file();
        resolvedTrace.source.line = static_cast<UInt>(stackFrame.source_line());
        resolvedTrace.source.col = 0;
        resolvedTrace.object_filename = {};
        resolvedTrace.object_function = resolvedTrace.source.function;
        resolvedTrace.inliners = {};
        vResolvedTraces.push_back(resolvedTrace);
    }
#endif
    StackTracePrinter printer;
    printer.snippet = true;
    printer.address = true;
    printer.object = true;
    printer.color_mode = StackTracePrinterColorAlways;
#if defined(PLATFORM_OS_WINDOWS)
    printer.print(vResolvedTraces.rbegin(), vResolvedTraces.rend(), sStream, static_cast<size_t>(stackTrace.second));
#else
    printer.print(stackTrace, sStream);
#endif
    sStream.flush();
}

};
