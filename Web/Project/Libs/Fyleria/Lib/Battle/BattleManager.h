// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_BATTLE_MANAGER_H_
#define _GECKO_BATTLE_MANAGER_H_

#include "Battle/Battle.h"
#include "Utility/Singleton.h"

namespace Gecko
{

class BattleManager : public Singleton<BattleManager>
{
public:

    // Constructors
    BattleManager();

    // Create a battle
    void CreateBattle(const IndexedString& sBattleName);

    // Unload battle
    void UnloadBattle(const IndexedString& sBattleName);

    // Determine if battle exists
    Bool DoesBattleExist(const IndexedString& sBattleName) const;

    // Set given name as current battle
    void SetAsCurrentBattle(const IndexedString& sBattleName);

    // Battle names
    const IndexedString& GetCurrentBattleName() const;

    // Get battle
    Battle& GetBattle(const IndexedString& sPartyName);
    const Battle& GetBattle(const IndexedString& sPartyName) const;
    Battle& GetCurrentBattle();
    const Battle& GetCurrentBattle() const;

private:

    // Battles
    STDUnorderedMap<IndexedString, Battle, IndexedStringHasher> m_tBattles;

    // Current battle
    IndexedString m_sCurrentBattleName;
};

};

#endif
