// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Utility/TypesTrace.h"

namespace Gecko
{
    STDVector<Gecko::Int> GetTraceSignals()
    {
        STDVector<Gecko::Int> vSignals;
        vSignals.push_back(SIGABRT);
        vSignals.push_back(SIGFPE);
        vSignals.push_back(SIGILL);
        vSignals.push_back(SIGSEGV);
#ifdef __linux__
        vSignals.push_back(SIGBUS);
        vSignals.push_back(SIGSYS);
        vSignals.push_back(SIGTRAP);
        vSignals.push_back(SIGXCPU);
        vSignals.push_back(SIGXFSZ);
#endif
        return vSignals;
    }
};
