// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Module/Module.h"

namespace Gecko
{

namespace ModuleResult
{
    static String s_sRunResultID;
    static STDMap<String, String> s_tResultsStorage;

    void SetRunResultID(const String& sID)
    {
        s_sRunResultID = sID;
    }

    const String& GetRunResultID()
    {
        return s_sRunResultID;
    }

    void StoreResult(const String& sID, const String& sResult)
    {
        s_tResultsStorage[sID] = sResult;
    }

    void StoreRunResult(const String& sResult)
    {
        StoreResult(GetRunResultID(), sResult);
    }

    String GetResult(const String& sID)
    {
        auto iSearch = s_tResultsStorage.find(sID);
        if(iSearch != s_tResultsStorage.end())
        {
            return iSearch->second;
        }
        else
        {
            return String();
        }
    }

    Bool DoesResultExist(const String& sID)
    {
        auto iSearch = s_tResultsStorage.find(sID);
        return (iSearch != s_tResultsStorage.end());
    }

    void ClearResult(const String& sID)
    {
        s_tResultsStorage.erase(sID);
    }

    void ClearAllResults()
    {
        s_tResultsStorage.clear();
    }
};

};
