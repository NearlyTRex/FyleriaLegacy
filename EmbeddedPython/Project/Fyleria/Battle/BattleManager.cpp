// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Battle/BattleManager.h"

namespace Gecko
{

BattleManager::BattleManager()
    : Singleton<BattleManager>()
{
}

void BattleManager::CreateBattle(const String& sBattleName)
{
    // Check if battle exists
    if(DoesBattleExist(sBattleName))
    {
        THROW_RUNTIME_ERROR("Battle '" + sBattleName + "' was already registered");
    }

    // Create a new battle
    Battle newBattle;
    GetBattles().insert({sBattleName, newBattle});
}

void BattleManager::UnloadBattle(const String& sBattleName)
{
    // Check if battle exists
    if(!DoesBattleExist(sBattleName))
    {
        THROW_RUNTIME_ERROR("Battle '" + sBattleName + "' was not registered");
    }

    // Unload battle
    GetBattles().erase(sBattleName);
}

Bool BattleManager::DoesBattleExist(const String& sBattleName) const
{
    // Check if battle exists
    auto iSearch = GetBattles().find(sBattleName);
    return (iSearch != GetBattles().end());
}

const Battle& BattleManager::GetBattle(const String& sBattleName) const
{
    // Check if battle exists
    if(!DoesBattleExist(sBattleName))
    {
        THROW_RUNTIME_ERROR("Battle '" + sBattleName + "' was not registered");
    }

    // Get battle
    auto iSearch = GetBattles().find(sBattleName);
    return iSearch->second;
}

Battle& BattleManager::GetBattle(const String& sBattleName)
{
    // Get battle
    return const_cast<Battle&>(static_cast<const BattleManager&>(*this).GetBattle(sBattleName));
}

const Battle& BattleManager::GetCurrentBattle() const
{
    // Get current battle
    return GetBattle(GetCurrentBattleID());
}

Battle& BattleManager::GetCurrentBattle()
{
    // Get current battle
    return const_cast<Battle&>(static_cast<const BattleManager&>(*this).GetCurrentBattle());
}

};
