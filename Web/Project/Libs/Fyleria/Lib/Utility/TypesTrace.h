// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_TYPES_TRACE_H_
#define _GECKO_TYPES_TRACE_H_

// Internal includes
#include "Utility/TypesSimple.h"

// System includes
#include <signal.h>

// External includes
#include <backward.hpp>

namespace Gecko
{

// Signal handler
typedef backward::SignalHandling SignalHandler;

// Stack trace
typedef backward::StackTrace StackTraceGenerator;
typedef backward::Printer StackTracePrinter;
typedef backward::TraceResolver StackTraceResolver;
typedef backward::ResolvedTrace StackResolvedTrace;

// Get signals
STDVector<Gecko::Int> GetTraceSignals();

};

#endif
