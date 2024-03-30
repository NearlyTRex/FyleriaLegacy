// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_PARTY_MANAGER_H_
#define _GECKO_CHARACTER_PARTY_MANAGER_H_

#include "Character/CharacterParty.h"
#include "Utility/Singleton.h"

namespace Gecko
{

class CharacterPartyManager : public Singleton<CharacterPartyManager>
{
public:

    // Constructors
    CharacterPartyManager();

    // Load a party
    // This will overwrite any existing matching data
    void LoadParty(const IndexedString& sPartyID, const CharacterParty& party);

    // Load a party from a file
    // This will overwrite any existing matching data
    void LoadPartyFromFile(const IndexedString& sPartyID, const IndexedString& sFilename, const IndexedString& sType);

    // Save a party to file
    void SavePartyToFile(const IndexedString& sPartyID, const IndexedString& sFilename, const IndexedString& sType);

    // Create a party
    void CreateParty(const IndexedString& sPartyID, const IndexedString& sPartyType, Bool bSetAsCurrent = false);

    // Unload party
    void UnloadParty(const IndexedString& sPartyID);

    // Determine if party exists
    Bool DoesPartyExist(const IndexedString& sPartyID) const;

    // Set party ID as current ally/enemy party
    void SetAsCurrentAllyParty(const IndexedString& sPartyID);
    void SetAsCurrentEnemyParty(const IndexedString& sPartyID);

    // Get current party IDs
    const IndexedString& GetCurrentAllyPartyID() const;
    const IndexedString& GetCurrentEnemyPartyID() const;

    // Get party
    CharacterParty& GetPartyByID(const IndexedString& sPartyID);
    const CharacterParty& GetPartyByID(const IndexedString& sPartyID) const;
    CharacterParty& GetPartyByType(const IndexedString& sPartyType);
    const CharacterParty& GetPartyByType(const IndexedString& sPartyType) const;
    CharacterParty& GetCurrentAllyParty();
    const CharacterParty& GetCurrentAllyParty() const;
    CharacterParty& GetCurrentEnemyParty();
    const CharacterParty& GetCurrentEnemyParty() const;

private:

    // Parties
    STDUnorderedMap<IndexedString, CharacterParty, IndexedStringHasher> m_tParties;

    // Current ally/enemy party
    IndexedString m_sCurrentAllyPartyName;
    IndexedString m_sCurrentEnemyPartyName;

    // Empty party
    CharacterParty m_EmptyParty;
};

};

#endif
