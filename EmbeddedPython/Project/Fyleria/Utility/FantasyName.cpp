// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Utility/FantasyName.h"
#include "Utility/Templates.h"
#include "Utility/Converters.h"

namespace Gecko
{

String GenerateRandomFantasyName(const String& sPattern)
{
    FantasyNameGenerator generator(sPattern);
    return ConvertToSimpleCaseString(generator.toString());
}

String GetRandomNamePattern()
{
    const StringArray vNamePatterns = {
        GetMiddleEarthNamePattern(),
        GetJapaneseNameConstrainedPattern(),
        GetJapaneseNameDiversePattern(),
        GetChineseNamePattern(),
        GetGreekNamePattern(),
        GetHawaiianName1Pattern(),
        GetHawaiianName2Pattern(),
        GetOldLatinPlaceNamePattern(),
        GetDragonPernNamePattern(),
        GetDragonRiderNamePattern(),
        GetPokemonNamePattern(),
        GetFantasySANamePattern(),
        GetFantasyHLNamePattern(),
        GetFantasyNLNamePattern(),
        GetFantasyKNNamePattern(),
        GetFantasyJGZNamePattern(),
        GetFantasyKJYNamePattern(),
        GetFantasySENamePattern()
    };
    return GetRandomVectorValue<String>(vNamePatterns);
}

String GetCapitalizationToken() { return String("!"); }
String GetReverseToken() { return String("~"); }
String GetMiddleEarthNamePattern() { return String(MIDDLE_EARTH); }
String GetJapaneseNameConstrainedPattern() { return String(JAPANESE_NAMES_CONSTRAINED); }
String GetJapaneseNameDiversePattern() { return String(JAPANESE_NAMES_DIVERSE); }
String GetChineseNamePattern() { return String(CHINESE_NAMES); }
String GetGreekNamePattern() { return String(GREEK_NAMES); }
String GetHawaiianName1Pattern() { return String(HAWAIIAN_NAMES_1); }
String GetHawaiianName2Pattern() { return String(HAWAIIAN_NAMES_2); }
String GetOldLatinPlaceNamePattern() { return String(OLD_LATIN_PLACE_NAMES); }
String GetDragonPernNamePattern() { return String(DRAGONS_PERN); }
String GetDragonRiderNamePattern() { return String(DRAGON_RIDERS); }
String GetPokemonNamePattern() { return String(POKEMON); }
String GetFantasyVowelsRNamePattern() { return String(FANTASY_VOWELS_R); }
String GetFantasySANamePattern() { return String(FANTASY_S_A); }
String GetFantasyHLNamePattern() { return String(FANTASY_H_L); }
String GetFantasyNLNamePattern() { return String(FANTASY_N_L); }
String GetFantasyKNNamePattern() { return String(FANTASY_K_N); }
String GetFantasyJGZNamePattern() { return String(FANTASY_J_G_Z); }
String GetFantasyKJYNamePattern() { return String(FANTASY_K_J_Y); }
String GetFantasySENamePattern() { return String(FANTASY_S_E); }

};
