// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "CharacterParty/CharacterPartyManager.h"
#include "Character/CharacterTypes.h"
#include "Utility/Errors.h"
#include "Utility/Constants.h"

namespace Gecko
{

CharacterPartyManager::CharacterPartyManager()
    : Singleton<CharacterPartyManager>()
{
}

String CharacterPartyManager::LoadParty(const CharacterParty& party, Bool bRegenerateData)
{
    // Check if party ID is valid
    const String& sPartyID = party.GetPartyID();
    if(!IsValidPartyID(sPartyID))
    {
        THROW_RUNTIME_ERROR("Party ID '" + sPartyID + "' was not valid");
    }

    // Check if party type is valid
    const String& sPartyType = party.GetPartyType();
    if(!IsValidEnumString<CharacterPartyType>(sPartyType))
    {
        THROW_RUNTIME_ERROR("Party type '" + sPartyType + "' was not valid");
    }

    // Load party
    GetParties().insert({sPartyID, party});
    if(bRegenerateData)
    {
        GetParties().at(sPartyID).RegenerateCharacterData();
    }
    return sPartyID;
}

String CharacterPartyManager::LoadPartyFromFile(const String& sFilename, const String& sType, Bool bRegenerateData)
{
    // Deserialize file into party data
    Json jsonData;
    Bool bSuccess = ReadSerializedFile(sFilename, sType, jsonData);
    if(!bSuccess)
    {
        THROW_RUNTIME_ERROR("Unable to read file '" + sFilename + "' as type '" + sType + "'");
    }

    // Load party
    return LoadParty(jsonData.get<CharacterParty>(), bRegenerateData);
}

void CharacterPartyManager::SavePartyToFile(const String& sPartyID, const String& sFilename, const String& sType)
{
    // Serialize party data into file
    Json jsonData = GetPartyByID(sPartyID);
    Bool bSuccess = WriteSerializedFile(sFilename, sType, jsonData);
    if(!bSuccess)
    {
        THROW_RUNTIME_ERROR("Unable to write file '" + sFilename + "' as type '" + sType + "'");
    }
}

void CharacterPartyManager::CreateParty(const String& sPartyID, const String& sPartyType, Bool bSetAsCurrent /*= false*/)
{
    // Check if party exists
    if(DoesPartyExistByID(sPartyID))
    {
        THROW_RUNTIME_ERROR("Party '" + sPartyID + "' was already registered");
    }

    // Check if party type was valid
    if(!IsValidEnumString<CharacterPartyType>(sPartyType))
    {
        THROW_RUNTIME_ERROR("Party type '" + sPartyType + "' was not valid");
    }

    // Create a new party
    StringArray vAvailableTargetTypes;
    for(UInt i = 1; i <= MAX_TEAM_CHARACTER_AMOUNT; i++)
    {
        vAvailableTargetTypes.push_back(sPartyType + String(STDToString(i)));
    }
    CharacterParty newParty;
    newParty.SetPartyID(sPartyID);
    newParty.SetPartyType(sPartyType);
    newParty.SetAvailableTargetTypes(vAvailableTargetTypes);
    newParty.ResetPlayTime();
    GetParties().insert({sPartyID, newParty});

    // Set as current ally/enemy
    if(bSetAsCurrent)
    {
        const CharacterPartyType ePartyType = GetEnumFromString<CharacterPartyType>(sPartyType);
        switch(ePartyType)
        {
            case CharacterPartyType::Ally:
                SetCurrentAllyPartyID(sPartyID);
                break;
            case CharacterPartyType::Enemy:
                SetCurrentEnemyPartyID(sPartyID);
                break;
            default:
                break;
        }
    }
}

void CharacterPartyManager::UnloadParty(const String& sPartyID)
{
    // Check if party exists
    if(!DoesPartyExistByID(sPartyID))
    {
        THROW_RUNTIME_ERROR("Party '" + sPartyID + "' was not registered");
    }

    // Unload party
    GetParties().erase(sPartyID);
    if(sPartyID == GetCurrentAllyPartyID())
    {
        SetCurrentAllyPartyID("");
    }
    else if(sPartyID == GetCurrentEnemyPartyID())
    {
        SetCurrentEnemyPartyID("");
    }
}

Bool CharacterPartyManager::DoesPartyExistByID(const String& sPartyID) const
{
    // Check if party exists
    auto iSearch = GetParties().find(sPartyID);
    return (iSearch != GetParties().end());
}

Bool CharacterPartyManager::DoesPartyExistByType(const String& sPartyType) const
{
    // Check if party exists
    for(auto it = GetParties().begin(); it != GetParties().end(); it++)
    {
        if(sPartyType == it->second.GetPartyType())
        {
            return true;
        }
    }
    return false;
}

Bool CharacterPartyManager::IsValidPartyID(const String& sPartyID) const
{
    // Check party ID validity
    return (!sPartyID.empty());
}

const CharacterParty& CharacterPartyManager::GetPartyByID(const String& sPartyID) const
{
    // Check if party exists
    if(!DoesPartyExistByID(sPartyID))
    {
        THROW_RUNTIME_ERROR("Party '" + sPartyID + "' was not registered");
    }

    // Get party
    auto iSearch = GetParties().find(sPartyID);
    if(iSearch != GetParties().end())
    {
        return iSearch->second;
    }
    THROW_RUNTIME_ERROR("Invalid or unknown party ID requested: " + sPartyID);
}

CharacterParty& CharacterPartyManager::GetPartyByID(const String& sPartyID)
{
    // Get party
    return const_cast<CharacterParty&>(static_cast<const CharacterPartyManager&>(*this).GetPartyByID(sPartyID));
}

const CharacterParty& CharacterPartyManager::GetPartyByType(const String& sPartyType) const
{
    // Get party
    const CharacterPartyType ePartyType = GetEnumFromString<CharacterPartyType>(sPartyType);
    switch(ePartyType)
    {
        case CharacterPartyType::Ally:
            return GetCurrentAllyParty();
        case CharacterPartyType::Enemy:
            return GetCurrentEnemyParty();
        default:
            break;
    }
    THROW_RUNTIME_ERROR("Invalid or unknown party type requested: " + sPartyType);
}

CharacterParty& CharacterPartyManager::GetPartyByType(const String& sPartyType)
{
    // Get party
    return const_cast<CharacterParty&>(static_cast<const CharacterPartyManager&>(*this).GetPartyByType(sPartyType));
}

const CharacterParty& CharacterPartyManager::GetCurrentAllyParty() const
{
    return GetPartyByID(GetCurrentAllyPartyID());
}

CharacterParty& CharacterPartyManager::GetCurrentAllyParty()
{
    return GetPartyByID(GetCurrentAllyPartyID());
}

const CharacterParty& CharacterPartyManager::GetCurrentEnemyParty() const
{
    return GetPartyByID(GetCurrentEnemyPartyID());
}

CharacterParty& CharacterPartyManager::GetCurrentEnemyParty()
{
    return GetPartyByID(GetCurrentEnemyPartyID());
}

StringArray CharacterPartyManager::GetAllPartyIDs() const
{
    StringArray vAllParties;
    for(auto it = GetParties().begin(); it != GetParties().end(); it++)
    {
        vAllParties.push_back(it->first);
    }
    return vAllParties;
}

};
