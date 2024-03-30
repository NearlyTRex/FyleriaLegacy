// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Utility/ResultManager.h"

namespace Gecko
{

ResultManager::ResultManager()
    : Singleton<ResultManager>()
{
}

void ResultManager::StoreResult(const String& sID, const String& sResult)
{
    GetResults().insert({sID, sResult});
}

void ResultManager::StoreCurrentResult(const String& sResult)
{
    StoreResult(GetCurrentResultID(), sResult);
}

String ResultManager::GetResult(const String& sID)
{
    auto iSearch = GetResults().find(sID);
    if(iSearch != GetResults().end())
    {
        return iSearch->second;
    }
    else
    {
        return String();
    }
}

Bool ResultManager::DoesResultExist(const String& sID)
{
    auto iSearch = GetResults().find(sID);
    return (iSearch != GetResults().end());
}

void ResultManager::ClearResult(const String& sID)
{
    GetResults().erase(sID);
}

void ResultManager::ClearAllResults()
{
    GetResults().clear();
}

};
