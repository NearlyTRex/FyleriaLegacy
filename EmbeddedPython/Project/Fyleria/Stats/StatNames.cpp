// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Stats/StatNames.h"
#include "CharacterData/CharacterActionData.h"
#include "CharacterData/CharacterBasicData.h"
#include "CharacterData/CharacterProgressData.h"
#include "CharacterData/CharacterBattleData.h"
#include "CharacterData/CharacterSkillData.h"

namespace Gecko
{

static SafeStatNameSetType s_pBoolStatNames = {};
static SafeStatNameSetType s_pByteStatNames = {};
static SafeStatNameSetType s_pShortStatNames = {};
static SafeStatNameSetType s_pIntStatNames = {};
static SafeStatNameSetType s_pLongStatNames = {};
static SafeStatNameSetType s_pLongLongStatNames = {};
static SafeStatNameSetType s_pUByteStatNames = {};
static SafeStatNameSetType s_pUShortStatNames = {};
static SafeStatNameSetType s_pUIntStatNames = {};
static SafeStatNameSetType s_pULongStatNames = {};
static SafeStatNameSetType s_pULongLongStatNames = {};
static SafeStatNameSetType s_pFloatStatNames = {};
static SafeStatNameSetType s_pDoubleStatNames = {};
static SafeStatNameSetType s_pLongDoubleStatNames = {};
static SafeStatNameSetType s_pStringStatNames = {};
static SafeStatNameSetType s_pStringArrayStatNames = {};

SafeStatNameSetType& GetBoolStatNames() { return s_pBoolStatNames; }
SafeStatNameSetType& GetByteStatNames() { return s_pByteStatNames; }
SafeStatNameSetType& GetShortStatNames() { return s_pShortStatNames; }
SafeStatNameSetType& GetIntStatNames() { return s_pIntStatNames; }
SafeStatNameSetType& GetLongStatNames() { return s_pLongStatNames; }
SafeStatNameSetType& GetLongLongStatNames() { return s_pLongLongStatNames; }
SafeStatNameSetType& GetUByteStatNames() { return s_pUByteStatNames; }
SafeStatNameSetType& GetUShortStatNames() { return s_pUShortStatNames; }
SafeStatNameSetType& GetUIntStatNames() { return s_pUIntStatNames; }
SafeStatNameSetType& GetULongStatNames() { return s_pULongStatNames; }
SafeStatNameSetType& GetULongLongStatNames() { return s_pULongLongStatNames; }
SafeStatNameSetType& GetFloatStatNames() { return s_pFloatStatNames; }
SafeStatNameSetType& GetDoubleStatNames() { return s_pDoubleStatNames; }
SafeStatNameSetType& GetLongDoubleStatNames() { return s_pLongDoubleStatNames; }
SafeStatNameSetType& GetStringStatNames() { return s_pStringStatNames; }
SafeStatNameSetType& GetStringArrayStatNames() { return s_pStringArrayStatNames; }

Bool IsStatBool(const String& sStat) { return (GetBoolStatNames()->find(sStat) != GetBoolStatNames()->end()); }
Bool IsStatByte(const String& sStat) { return (GetByteStatNames()->find(sStat) != GetByteStatNames()->end()); }
Bool IsStatShort(const String& sStat) { return (GetShortStatNames()->find(sStat) != GetShortStatNames()->end()); }
Bool IsStatInt(const String& sStat) { return (GetIntStatNames()->find(sStat) != GetIntStatNames()->end()); }
Bool IsStatLong(const String& sStat) { return (GetLongStatNames()->find(sStat) != GetLongStatNames()->end()); }
Bool IsStatLongLong(const String& sStat) { return (GetLongLongStatNames()->find(sStat) != GetLongLongStatNames()->end()); }
Bool IsStatUByte(const String& sStat) { return (GetUByteStatNames()->find(sStat) != GetUByteStatNames()->end()); }
Bool IsStatUShort(const String& sStat) { return (GetUShortStatNames()->find(sStat) != GetUShortStatNames()->end()); }
Bool IsStatUInt(const String& sStat) { return (GetUIntStatNames()->find(sStat) != GetUIntStatNames()->end()); }
Bool IsStatULong(const String& sStat) { return (GetULongStatNames()->find(sStat) != GetULongStatNames()->end()); }
Bool IsStatULongLong(const String& sStat) { return (GetULongLongStatNames()->find(sStat) != GetULongLongStatNames()->end()); }
Bool IsStatFloat(const String& sStat) { return (GetFloatStatNames()->find(sStat) != GetFloatStatNames()->end()); }
Bool IsStatDouble(const String& sStat) { return (GetDoubleStatNames()->find(sStat) != GetDoubleStatNames()->end()); }
Bool IsStatLongDouble(const String& sStat) { return (GetLongDoubleStatNames()->find(sStat) != GetLongDoubleStatNames()->end()); }
Bool IsStatString(const String& sStat) { return (GetStringStatNames()->find(sStat) != GetStringStatNames()->end()); }
Bool IsStatStringArray(const String& sStat) { return (GetStringArrayStatNames()->find(sStat) != GetStringArrayStatNames()->end()); }

void InitializeAllStatNames()
{
    CharacterActionData::InitAllStatNames();
    CharacterBasicData::InitAllStatNames();
    CharacterProgressData::InitAllStatNames();
    CharacterBattleData::InitAllStatNames();
    CharacterSkillData::InitAllStatNames();
}

};
