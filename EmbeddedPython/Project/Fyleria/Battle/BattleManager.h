// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_BATTLE_MANAGER_H_
#define _GECKO_BATTLE_MANAGER_H_

// Internal includes
#include "Battle/Battle.h"
#include "Utility/ResultManager.h"

namespace Gecko
{

class BattleManager : public Singleton<BattleManager>
{
public:

    // Types
    typedef STDUnorderedMap<String, Battle> BattleMappingType;

    // Constructors
    BattleManager();

    // Create a battle
    void CreateBattle(const String& sBattleName);

    // Unload battle
    void UnloadBattle(const String& sBattleName);

    // Determine if battle exists
    Bool DoesBattleExist(const String& sBattleName) const;
    MAKE_MODULE_RESULT_VARIANT_A1(DoesBattleExist, const String&);

    // Get battle
    const Battle& GetBattle(const String& sPartyName) const;
    Battle& GetBattle(const String& sPartyName);
    MAKE_MODULE_RESULT_VARIANT_A1(GetBattle, const String&);

    // Get current battle
    const Battle& GetCurrentBattle() const;
    Battle& GetCurrentBattle();
    MAKE_MODULE_RESULT_VARIANT(GetCurrentBattle);

    // Battles
    MAKE_RAW_TYPE_ACCESSORS(Battles, BattleMappingType);

    // Current battle ID
    MAKE_RAW_TYPE_ACCESSORS(CurrentBattleID, String);
};

};

#endif
