// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_MANAGER_H_
#define _GECKO_CHARACTER_MANAGER_H_

#include "Character/Character.h"
#include "Character/CharacterGenerator.h"
#include "Utility/Singleton.h"

namespace Gecko
{

class CharacterManager : public Singleton<CharacterManager>
{
public:

    // Constructors
    CharacterManager();

    // Load a character
    // This will overwrite any existing matching data
    void LoadCharacter(const IndexedString& sCharacterID, const Character& character);

    // Load a character from a file
    // This will overwrite any existing matching data
    void LoadCharacterFromFile(const IndexedString& sCharacterID, const IndexedString& sFilename, const IndexedString& sType);

    // Save a character to file
    void SaveCharacterToFile(const IndexedString& sCharacterID, const IndexedString& sFilename, const IndexedString& sType);

    // Create a character
    void CreateCharacter(const IndexedString& sCharacterID);

    // Unload a character
    void UnloadCharacter(const IndexedString& sCharacterID);

    // Does a character exist
    Bool DoesCharacterExist(const IndexedString& sCharacterID) const;

    // Generate a character
    void GenerateCharacter(const IndexedString& sCharacterID, const CharacterGenerator& generator);

    // Get character
    Character& GetCharacter(const IndexedString& sCharacterID);
    const Character& GetCharacter(const IndexedString& sCharacterID) const;

    // Apply a stat change
    void ApplyStatChange(const IndexedString& sSegment, const StatChange& change, Bool& bAllChangesApplied, Bool& bAtLeastOneChange, Bool bApplyAllEntries = false);
    Bool ApplyStatChangeEntry(const IndexedString& sSegment, const StatChangeEntry& entry);
    Bool ApplyStatChangeEntryOperation(const IndexedString& sSegment, const IndexedString& sCharacterID, const IndexedString& sOperation, const IndexedString& sStat, Float fValue);
    Bool ApplyStatChangeEntryOperation(const IndexedString& sSegment, const IndexedString& sCharacterID, const IndexedString& sOperation, const IndexedString& sStat, Int iValue);
    Bool ApplyStatChangeEntryOperation(const IndexedString& sSegment, const IndexedString& sCharacterID, const IndexedString& sOperation, const IndexedString& sStat, Bool bValue);
    Bool ApplyStatChangeEntryOperation(const IndexedString& sSegment, const IndexedString& sCharacterID, const IndexedString& sOperation, const IndexedString& sStat, const IndexedString& sValue);
    Bool ApplyStatChangeEntryOperation(const IndexedString& sSegment, const IndexedString& sCharacterID, const IndexedString& sOperation, const IndexedString& sStat, const IndexedStringList& sValue);

    // Determine if stat change entry uses a delta from source to destination characters
    Bool DoesStatChangeEntryUseDelta(const StatChangeEntry& changeEntry) const;

    // Determine stat value types
    Bool IsStatFloat(const IndexedString& sStat) const;
    Bool IsStatInt(const IndexedString& sStat) const;
    Bool IsStatBool(const IndexedString& sStat) const;
    Bool IsStatString(const IndexedString& sStat) const;
    Bool IsStatStringList(const IndexedString& sStat) const;

    // Get values from stat change entry
    Bool GetSourceStatChangeEntryValues(const IndexedString& sSegment, const IndexedString& sCharacterID, const IndexedString& sStat, const StatChangeEntry& changeEntry,
        FloatList& vFloatValues,
        IntList& vIntValues,
        BoolList& vBoolValues,
        IndexedStringList& vStringValues) const;
    Bool GetDestStatChangeEntryValues(const IndexedString& sSegment, const IndexedString& sCharacterID, const IndexedString& sStat, const StatChangeEntry& changeEntry,
        FloatList& vFloatValues,
        IntList& vIntValues,
        BoolList& vBoolValues,
        IndexedStringList& vStringValues) const;

private:

    // Characters
    STDUnorderedMap<IndexedString, Character, IndexedStringHasher> m_tCharacters;
};

};

#endif
