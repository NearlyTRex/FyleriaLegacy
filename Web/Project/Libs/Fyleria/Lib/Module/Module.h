// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_MODULE_H_
#define _GECKO_MODULE_H_

#include "Utility/TypesSimple.h"

namespace Gecko
{

namespace ModuleResult
{
    // Set run command/file result ID
    void SetRunResultID(const String& sID);

    // Get run command/file result ID
    const String& GetRunResultID();

    // Store result in the given id
    void StoreResult(const String& sID, const String& sResult);

    // Store result in the run id
    void StoreRunResult(const String& sResult);

    // Get result from the given slot
    String GetResult(const String& sID);

    // Determine if result exists
    Bool DoesResultExist(const String& sID);

    // Clear the results from the given slot
    void ClearResult(const String& sID);

    // Clear all the results
    void ClearAllResults();
};

};

#endif
