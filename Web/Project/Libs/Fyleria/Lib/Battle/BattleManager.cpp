// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Battle/BattleManager.h"

namespace Gecko
{

BattleManager::BattleManager()
    : Singleton<BattleManager>()
    , m_tBattles()
    , m_sCurrentBattleName()
{
}

void BattleManager::CreateBattle(const IndexedString& sBattleName)
{
    // Create a new battle
    ASSERT_ERROR(!DoesBattleExist(sBattleName), "Battle '%s' was already registered", sBattleName.c_str());
    Battle newBattle;
    m_tBattles.insert({sBattleName, newBattle});
}

void BattleManager::UnloadBattle(const IndexedString& sBattleName)
{
    // Unload battle
    ASSERT_ERROR(DoesBattleExist(sBattleName), "Battle '%s' was not registered", sBattleName.c_str());
    m_tBattles.erase(sBattleName);
}

Bool BattleManager::DoesBattleExist(const IndexedString& sBattleName) const
{
    // Check if battle exists
    auto iSearch = m_tBattles.find(sBattleName);
    return (iSearch != m_tBattles.end());
}

void BattleManager::SetAsCurrentBattle(const IndexedString& sBattleName)
{
    // Set the given battle name as the current battle
    ASSERT_ERROR(DoesBattleExist(sBattleName), "Battle '%s' was not registered", sBattleName.c_str());
    m_sCurrentBattleName = sBattleName;
}

const IndexedString& BattleManager::GetCurrentBattleName() const
{
    return m_sCurrentBattleName;
}

Battle& BattleManager::GetBattle(const IndexedString& sBattleName)
{
    // Get battle
    ASSERT_ERROR(DoesBattleExist(sBattleName), "Battle '%s' was not registered", sBattleName.c_str());
    return m_tBattles[sBattleName];
}

const Battle& BattleManager::GetBattle(const IndexedString& sBattleName) const
{
    // Get battle
    ASSERT_ERROR(DoesBattleExist(sBattleName), "Battle '%s' was not registered", sBattleName.c_str());
    auto iSearch = m_tBattles.find(sBattleName);
    return iSearch->second;
}

Battle& BattleManager::GetCurrentBattle()
{
    return GetBattle(GetCurrentBattleName());
}

const Battle& BattleManager::GetCurrentBattle() const
{
    return GetBattle(GetCurrentBattleName());
}

};
