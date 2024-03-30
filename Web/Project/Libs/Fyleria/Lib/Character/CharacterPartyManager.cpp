// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterPartyManager.h"
#include "Character/CharacterTypes.h"
#include "Utility/Constants.h"

namespace Gecko
{

CharacterPartyManager::CharacterPartyManager()
    : Singleton<CharacterPartyManager>()
    , m_tParties()
    , m_sCurrentAllyPartyName()
    , m_sCurrentEnemyPartyName()
{
}

void CharacterPartyManager::LoadParty(const IndexedString& sPartyID, const CharacterParty& party)
{
    // Load a party
    ASSERT_ERROR(!party.GetPartyID().empty(), "Invalid party ID '%s'", party.GetPartyID().c_str());
    ASSERT_ERROR(IsValidCharacterPartyType(party.GetPartyType()), "Party type '%s' was not valid", party.GetPartyType().c_str());
    m_tParties[party.GetPartyID()] = party;
    m_tParties[party.GetPartyID()].SetPartyID(sPartyID);
}

void CharacterPartyManager::LoadPartyFromFile(const IndexedString& sPartyID, const IndexedString& sFilename, const IndexedString& sType)
{
    // Load a party
    Json jsonData;
    Bool bSuccess = ReadSerializedFile(sFilename, sType, jsonData);
    ASSERT_ERROR(bSuccess, "Unable to read file '%s' as type '%s'", sFilename.c_str(), sType.c_str());
    LoadParty(sPartyID, jsonData.get<CharacterParty>());
}

void CharacterPartyManager::SavePartyToFile(const IndexedString& sPartyID, const IndexedString& sFilename, const IndexedString& sType)
{
    // Save a party
    Json jsonData = GetPartyByID(sPartyID);
    Bool bSuccess = WriteSerializedFile(sFilename, sType, jsonData);
    ASSERT_ERROR(bSuccess, "Unable to write file '%s' as type '%s'", sFilename.c_str(), sType.c_str());
}

void CharacterPartyManager::CreateParty(const IndexedString& sPartyID, const IndexedString& sPartyType, Bool bSetAsCurrent /*= false*/)
{
    // Create a new party
    ASSERT_ERROR(!DoesPartyExist(sPartyID), "Party '%s' was already registered", sPartyID.c_str());
    ASSERT_ERROR(IsValidCharacterPartyType(sPartyType), "Party type '%s' was not valid", sPartyType.c_str());
    IndexedStringList vAvailableTargetTypes;
    for(UInt i = 1; i <= s_kuMaxTeamCharacterAmount; i++)
    {
        vAvailableTargetTypes.push_back(sPartyType + IndexedString(STDToString(i)));
    }
    CharacterParty newParty;
    newParty.SetPartyID(sPartyID);
    newParty.SetPartyType(sPartyType);
    newParty.SetAvailableTargetTypes(vAvailableTargetTypes);
    m_tParties.insert({sPartyID, newParty});

    // Set as current ally/enemy
    if(bSetAsCurrent)
    {
        const CharacterPartyType ePartyType = StringToCharacterPartyType(sPartyType);
        switch(ePartyType)
        {
            case CharacterPartyType::Ally:
                SetAsCurrentAllyParty(sPartyID);
                break;
            case CharacterPartyType::Enemy:
                SetAsCurrentEnemyParty(sPartyID);
                break;
            default:
                break;
        }
    }
}

void CharacterPartyManager::UnloadParty(const IndexedString& sPartyID)
{
    // Unload party
    ASSERT_ERROR(DoesPartyExist(sPartyID), "Party '%s' was not registered", sPartyID.c_str());
    m_tParties.erase(sPartyID);
}

Bool CharacterPartyManager::DoesPartyExist(const IndexedString& sPartyID) const
{
    // Check if party exists
    auto iSearch = m_tParties.find(sPartyID);
    return (iSearch != m_tParties.end());
}

void CharacterPartyManager::SetAsCurrentAllyParty(const IndexedString& sPartyID)
{
    // Set the given party name as the "ally" party
    ASSERT_ERROR(DoesPartyExist(sPartyID), "Party '%s' was not registered", sPartyID.c_str());
    m_sCurrentAllyPartyName = sPartyID;
}

void CharacterPartyManager::SetAsCurrentEnemyParty(const IndexedString& sPartyID)
{
    // Set the given party name as the "enemy" party
    ASSERT_ERROR(DoesPartyExist(sPartyID), "Party '%s' was not registered", sPartyID.c_str());
    m_sCurrentEnemyPartyName = sPartyID;
}

const IndexedString& CharacterPartyManager::GetCurrentAllyPartyID() const
{
    return m_sCurrentAllyPartyName;
}

const IndexedString& CharacterPartyManager::GetCurrentEnemyPartyID() const
{
    return m_sCurrentEnemyPartyName;
}

CharacterParty& CharacterPartyManager::GetPartyByID(const IndexedString& sPartyID)
{
    // Get party
    ASSERT_ERROR(DoesPartyExist(sPartyID), "Party '%s' was not registered", sPartyID.c_str());
    return m_tParties[sPartyID];
}

const CharacterParty& CharacterPartyManager::GetPartyByID(const IndexedString& sPartyID) const
{
    // Get party
    ASSERT_ERROR(DoesPartyExist(sPartyID), "Party '%s' was not registered", sPartyID.c_str());
    auto iSearch = m_tParties.find(sPartyID);
    return iSearch->second;
}

CharacterParty& CharacterPartyManager::GetPartyByType(const IndexedString& sPartyType)
{
    // Get party
    const CharacterPartyType ePartyType = StringToCharacterPartyType(sPartyType);
    if(ePartyType == +CharacterPartyType::Ally) { return GetCurrentAllyParty(); }
    else if(ePartyType == +CharacterPartyType::Enemy) { return GetCurrentEnemyParty(); }
    return m_EmptyParty;
}

const CharacterParty& CharacterPartyManager::GetPartyByType(const IndexedString& sPartyType) const
{
    // Get party
    const CharacterPartyType ePartyType = StringToCharacterPartyType(sPartyType);
    if(ePartyType == +CharacterPartyType::Ally) { return GetCurrentAllyParty(); }
    else if(ePartyType == +CharacterPartyType::Enemy) { return GetCurrentEnemyParty(); }
    return m_EmptyParty;
}

CharacterParty& CharacterPartyManager::GetCurrentAllyParty()
{
    return GetPartyByID(GetCurrentAllyPartyID());
}

const CharacterParty& CharacterPartyManager::GetCurrentAllyParty() const
{
    return GetPartyByID(GetCurrentAllyPartyID());
}

CharacterParty& CharacterPartyManager::GetCurrentEnemyParty()
{
    return GetPartyByID(GetCurrentEnemyPartyID());
}

const CharacterParty& CharacterPartyManager::GetCurrentEnemyParty() const
{
    return GetPartyByID(GetCurrentEnemyPartyID());
}

};
