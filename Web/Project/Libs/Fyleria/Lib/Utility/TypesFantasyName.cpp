// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Utility/TypesFantasyName.h"

namespace Gecko
{

String GenerateRandomFantasyName(const String& sPattern)
{
    FantasyNameGenerator generator(sPattern);
    return generator.toString();
}

String GetCapitalizationToken() { return "!"; }
String GetReverseToken() { return "~"; }
String GetMiddleEarthNamePattern() { return MIDDLE_EARTH; }
String GetJapaneseNameConstrainedPattern() { return JAPANESE_NAMES_CONSTRAINED; }
String GetJapaneseNameDiversePattern() { return JAPANESE_NAMES_DIVERSE; }
String GetChineseNamePattern() { return CHINESE_NAMES; }
String GetGreekNamePattern() { return GREEK_NAMES; }
String GetHawaiianName1Pattern() { return HAWAIIAN_NAMES_1; }
String GetHawaiianName2Pattern() { return HAWAIIAN_NAMES_2; }
String GetOldLatinPlaceNamePattern() { return OLD_LATIN_PLACE_NAMES; }
String GetDragonPernNamePattern() { return DRAGONS_PERN; }
String GetDragonRiderNamePattern() { return DRAGON_RIDERS; }
String GetPokemonNamePattern() { return POKEMON; }
String GetFantasyVowelsRNamePattern() { return FANTASY_VOWELS_R; }
String GetFantasySANamePattern() { return FANTASY_S_A; }
String GetFantasyHLNamePattern() { return FANTASY_H_L; }
String GetFantasyNLNamePattern() { return FANTASY_N_L; }
String GetFantasyKNNamePattern() { return FANTASY_K_N; }
String GetFantasyJGZNamePattern() { return FANTASY_J_G_Z; }
String GetFantasyKJYNamePattern() { return FANTASY_K_J_Y; }
String GetFantasySENamePattern() { return FANTASY_S_E; }

};
