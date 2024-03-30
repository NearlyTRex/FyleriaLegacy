// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_FANTASYNAME_H_
#define _GECKO_UTILITY_FANTASYNAME_H_

// External includes
#include <namegen.h>

// Internal includes
#include "Utility/Types.h"

namespace Gecko
{

// FantasyName types
typedef NameGen::Generator FantasyNameGenerator;

// Generate a random fantasy name
String GenerateRandomFantasyName(const String& sPattern);

// Get random name pattern
String GetRandomNamePattern();

// Tokens
String GetCapitalizationToken();
String GetReverseToken();

// Prebuilt patterns
String GetMiddleEarthNamePattern();
String GetJapaneseNameConstrainedPattern();
String GetJapaneseNameDiversePattern();
String GetChineseNamePattern();
String GetGreekNamePattern();
String GetHawaiianName1Pattern();
String GetHawaiianName2Pattern();
String GetOldLatinPlaceNamePattern();
String GetDragonPernNamePattern();
String GetDragonRiderNamePattern();
String GetPokemonNamePattern();
String GetFantasyVowelsRNamePattern();
String GetFantasySANamePattern();
String GetFantasyHLNamePattern();
String GetFantasyNLNamePattern();
String GetFantasyKNNamePattern();
String GetFantasyJGZNamePattern();
String GetFantasyKJYNamePattern();
String GetFantasySENamePattern();

};

#endif
