// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_MANAGER_H_
#define _GECKO_CHARACTER_MANAGER_H_

// Internal includes
#include "Character/Character.h"
#include "Character/CharacterGenerator.h"
#include "Utility/ResultManager.h"

namespace Gecko
{

class CharacterManager : public Singleton<CharacterManager>
{
public:

    // Types
    typedef STDUnorderedMap<String, Character> CharacterMappingType;

    // Constructors
    CharacterManager();

    // Load a character and return the character ID
    // This will overwrite any existing matching data
    String LoadCharacter(const Character& character, Bool bRegenerateData);

    // Load a character from a file and return the character ID
    // This will overwrite any existing matching data
    String LoadCharacterFromFile(const String& sFilename, const String& sType, Bool bRegenerateData);

    // Save a character to file
    void SaveCharacterToFile(const String& sCharacterID, const String& sFilename, const String& sType);

    // Create a character
    void CreateCharacter(const String& sCharacterID);

    // Unload a character
    void UnloadCharacter(const String& sCharacterID);

    // Does a character exist
    Bool DoesCharacterExist(const String& sCharacterID) const;
    MAKE_MODULE_RESULT_VARIANT_A1(DoesCharacterExist, const String&);

    // Generate a character
    void GenerateCharacter(const String& sCharacterID, const CharacterGenerator& generator);

    // Check if character ID is valid
    Bool IsValidCharacterID(const String& sCharacterID) const;
    MAKE_MODULE_RESULT_VARIANT_A1(IsValidCharacterID, const String&);

    // Get character
    const Character& GetCharacter(const String& sCharacterID) const;
    Character& GetCharacter(const String& sCharacterID);
    MAKE_MODULE_RESULT_VARIANT_A1(GetCharacter, const String&);

    // Get all character IDs
    StringArray GetAllCharacterIDs() const;
    MAKE_MODULE_RESULT_VARIANT(GetAllCharacterIDs);

    // Apply a stat change
    void ApplyStatChange(
        const String& sSegment,
        const StatChange& change,
        Bool& bAllChangesApplied,
        Bool& bAtLeastOneChange,
        Bool bApplyAllEntries = false);

    // Apply a stat change entry
    Bool ApplyStatChangeEntry(const String& sSegment, const StatChangeEntry& entry);

    // Apply a stat change entry bool operation
    Bool ApplyStatChangeEntryOperation(
        const String& sSegment,
        const String& sCharacterID,
        const String& sOperation,
        const String& sStat,
        Bool bValue);

    // Apply a stat change entry int operation
    Bool ApplyStatChangeEntryOperation(
        const String& sSegment,
        const String& sCharacterID,
        const String& sOperation,
        const String& sStat,
        Int iValue);

    // Apply a stat change entry float operation
    Bool ApplyStatChangeEntryOperation(
        const String& sSegment,
        const String& sCharacterID,
        const String& sOperation,
        const String& sStat,
        Float fValue);

    // Apply a stat change entry string operation
    Bool ApplyStatChangeEntryOperation(
        const String& sSegment,
        const String& sCharacterID,
        const String& sOperation,
        const String& sStat,
        const String& sValue);

    // Apply a stat change entry string array operation
    Bool ApplyStatChangeEntryOperation(
        const String& sSegment,
        const String& sCharacterID,
        const String& sOperation,
        const String& sStat,
        const StringArray& sValue);

    // Determine if stat change entry uses a delta from source to destination characters
    Bool DoesStatChangeEntryUseDelta(const StatChangeEntry& changeEntry) const;

    // Get delta changed values from stat change entry
    Bool GetDeltaStatChangeEntryValues(
        const String& sSegment,
        const String& sCharacterID,
        const StatChangeEntry& changeEntry,
        BoolArray& vBoolValues,
        IntArray& vIntValues,
        FloatArray& vFloatValues,
        StringArray& vStringValues) const;

    // Get fully changed values from stat change entry
    Bool GetFullStatChangeEntryValues(
        const String& sSegment,
        const String& sCharacterID,
        const StatChangeEntry& changeEntry,
        BoolArray& vBoolValues,
        IntArray& vIntValues,
        FloatArray& vFloatValues,
        StringArray& vStringValues) const;

    // Characters
    MAKE_RAW_TYPE_ACCESSORS(Characters, CharacterMappingType);
};

};

#endif
