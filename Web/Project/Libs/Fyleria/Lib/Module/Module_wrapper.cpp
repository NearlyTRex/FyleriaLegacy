// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Module/Module.h"
#include "Utility/Macros.h"
#include "Utility/TypesPython.h"

PYBIND11_EMBEDDED_MODULE(GeckoModule, m)
{
    // Module.h
    WRAPPING_STANDALONE_METHOD_SIMPLE(SetRunResultID, Gecko::ModuleResult);
    WRAPPING_STANDALONE_METHOD_POLICY(GetRunResultID, Gecko::ModuleResult, PyBindReturnCopy);
    WRAPPING_STANDALONE_METHOD_SIMPLE(StoreResult, Gecko::ModuleResult);
    WRAPPING_STANDALONE_METHOD_SIMPLE(StoreRunResult, Gecko::ModuleResult);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetResult, Gecko::ModuleResult);
    WRAPPING_STANDALONE_METHOD_SIMPLE(DoesResultExist, Gecko::ModuleResult);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ClearResult, Gecko::ModuleResult);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ClearAllResults, Gecko::ModuleResult);
}
