// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterBattleData.h"
#include "Character/CharacterTypes.h"
#include "Config/ConfigManager.h"
#include "Items/ItemTree.h"
#include "Items/ItemTypes.h"

namespace Gecko
{

CharacterBattleData::CharacterBattleData()
{
    // Init stat names
    InitAllStatNames();

    // Clear data
    Clear();
}

CharacterBattleData::CharacterBattleData(const Json& jsonData)
{
    from_json(jsonData, *this);
}

void CharacterBattleData::Clear()
{
    // Get current configuration
    const Config& config = ConfigManager::GetInstance()->GetCurrentConfig();

    // -- Target Characters --
    SetAttackTargetsThisAction({});
    SetAttackTargetsThisRound({});
    SetAttackTargetsLastRound({});
    SetDefendTargetThisAction({});
    SetDefendTargetsThisRound({});
    SetDefendTargetsLastRound({});
    SetMostRecentAttackTargets({});
    SetMostRecentDefendTarget({});

    // -- Target Amounts --
    SetAllowedTargetAmount(config.GetDefaultAllowedTargetAmount());

    // -- Status --
    SetIsDead(config.GetDefaultIsDead());
    SetIsUnconscious(config.GetDefaultIsUnconscious());

    // -- Equipment Ratings --
    SetEquippedWeaponLeftBluntRating(config.GetDefaultEquippedWeaponLeftBluntRating());
    SetEquippedWeaponLeftPierceRating(config.GetDefaultEquippedWeaponLeftPierceRating());
    SetEquippedWeaponLeftSlashRating(config.GetDefaultEquippedWeaponLeftSlashRating());
    SetEquippedWeaponRightBluntRating(config.GetDefaultEquippedWeaponRightBluntRating());
    SetEquippedWeaponRightPierceRating(config.GetDefaultEquippedWeaponRightPierceRating());
    SetEquippedWeaponRightSlashRating(config.GetDefaultEquippedWeaponRightSlashRating());
    SetEquippedShieldLeftBluntRating(config.GetDefaultEquippedShieldLeftBluntRating());
    SetEquippedShieldLeftPierceRating(config.GetDefaultEquippedShieldLeftPierceRating());
    SetEquippedShieldLeftSlashRating(config.GetDefaultEquippedShieldLeftSlashRating());
    SetEquippedShieldLeftMagicRating(config.GetDefaultEquippedShieldLeftMagicRating());
    SetEquippedShieldRightBluntRating(config.GetDefaultEquippedShieldRightBluntRating());
    SetEquippedShieldRightPierceRating(config.GetDefaultEquippedShieldRightPierceRating());
    SetEquippedShieldRightSlashRating(config.GetDefaultEquippedShieldRightSlashRating());
    SetEquippedShieldRightMagicRating(config.GetDefaultEquippedShieldRightMagicRating());
    SetEquippedArmorBluntRating(config.GetDefaultEquippedArmorBluntRating());
    SetEquippedArmorPierceRating(config.GetDefaultEquippedArmorPierceRating());
    SetEquippedArmorSlashRating(config.GetDefaultEquippedArmorSlashRating());
    SetEquippedArmorMagicRating(config.GetDefaultEquippedArmorMagicRating());

    // -- Critical Hits --
    SetChanceToCauseCriticalHit(config.GetDefaultChanceToCauseCriticalHit());
    SetChanceToBlockCriticalHit(config.GetDefaultChanceToBlockCriticalHit());
    SetCriticalHitMultiplier(config.GetDefaultCriticalHitMultiplier());

    // -- Multiple Attacks --
    SetChanceToApplyMultipleAttacks(config.GetDefaultChanceToApplyMultipleAttacks());
    SetAttacksMultiplier(config.GetDefaultAttacksMultiplier());

    // -- Damage Counters --
    SetDamageTakenThisRound(config.GetDefaultDamageTakenThisRound());
    SetDamageTakenThisBattle(config.GetDefaultDamageTakenThisBattle());
    SetDamageGivenThisRound(config.GetDefaultDamageGivenThisRound());
    SetDamageGivenThisBattle(config.GetDefaultDamageGivenThisBattle());

    // -- Damage Bonus --
    SetWeaponPrimaryDamageBonusValue(config.GetDefaultWeaponPrimaryDamageBonusValue());
    SetWeaponPrimaryDamageBonusPercent(config.GetDefaultWeaponPrimaryDamageBonusPercent());
    SetWeaponSecondaryDamageBonusValue(config.GetDefaultWeaponSecondaryDamageBonusValue());
    SetWeaponSecondaryDamageBonusPercent(config.GetDefaultWeaponSecondaryDamageBonusPercent());
    SetGeneralDamageBonusValue(config.GetDefaultGeneralDamageBonusValue());
    SetGeneralDamageBonusPercent(config.GetDefaultGeneralDamageBonusPercent());

    // -- Effects Bonus --
    SetDefensivePowerEffectsBonusValue(config.GetDefaultDefensivePowerEffectsBonusValue());
    SetDefensivePowerEffectsBonusPercent(config.GetDefaultDefensivePowerEffectsBonusPercent());
    SetOffensivePowerEffectsBonusValue(config.GetDefaultOffensivePowerEffectsBonusValue());
    SetOffensivePowerEffectsBonusPercent(config.GetDefaultOffensivePowerEffectsBonusPercent());
}

void CharacterBattleData::ApplyNewStatus(const CharacterProgressData& progressData)
{
    SetIsDead(progressData.GetHealthPointsCurrent() <= 0);
    SetIsUnconscious(progressData.GetMagicPointsCurrent() <= 0 || progressData.GetEnergyPointsCurrent() <= 0);
}

void CharacterBattleData::ApplyGivenDamage(Int iDamage)
{
    SetDamageGivenThisRound(GetDamageGivenThisRound() + abs(iDamage));
    SetDamageGivenThisBattle(GetDamageGivenThisBattle() + abs(iDamage));
}

void CharacterBattleData::ApplyTakenDamage(Int iDamage)
{
    SetDamageTakenThisRound(GetDamageTakenThisRound() + abs(iDamage));
    SetDamageTakenThisBattle(GetDamageTakenThisBattle() + abs(iDamage));
}

void CharacterBattleData::AdvanceRound(CharacterProgressData& progressData)
{
    // Apply regeneration
    Bool bCanRegenHP = CanRegenerateFromStat(IndexedString("HealthRegen"));
    Bool bCanRegenMP = CanRegenerateFromStat(IndexedString("MagicRegen"));
    Bool bCanRegenEP = CanRegenerateFromStat(IndexedString("EnergyRegen"));
    if(bCanRegenHP || bCanRegenMP || bCanRegenEP)
    {
        progressData.ApplyRegeneration(bCanRegenHP, bCanRegenMP, bCanRegenEP);
    }

    // Apply new status
    ApplyNewStatus(progressData);

    // Clear this round's damage
    SetDamageGivenThisRound(0);
    SetDamageTakenThisRound(0);

    // Move this round's targets to last round
    SetAttackTargetsLastRound(GetAttackTargetsThisRound());
    SetDefendTargetsLastRound(GetDefendTargetsThisRound());
    SetAttackTargetsThisRound({});
    SetDefendTargetsThisRound({});
}

void CharacterBattleData::FinishBattle(CharacterProgressData& progressData)
{
    // Update character health if they are "dead"
    if(GetIsDead())
    {
        progressData.SetHealthPointsCurrent(1);
    }

    // Apply new status
    ApplyNewStatus(progressData);

    // Apply regeneration
    Bool bCanRegenHP = CanRegenerateFromStat(IndexedString("HealthRegen"));
    Bool bCanRegenMP = CanRegenerateFromStat(IndexedString("MagicRegen"));
    Bool bCanRegenEP = CanRegenerateFromStat(IndexedString("EnergyRegen"));
    if(bCanRegenHP || bCanRegenMP || bCanRegenEP)
    {
        progressData.ApplyRegeneration(bCanRegenHP, bCanRegenMP, bCanRegenEP);
    }

    // Clear this battle's damage
    SetDamageGivenThisBattle(0);
    SetDamageTakenThisBattle(0);
}

Bool CharacterBattleData::CanRegenerateFromStat(const IndexedString& sRegenStat) const
{
    const CharacterProgressStatType eProgressType = StringToCharacterProgressStatType(sRegenStat);
    switch(eProgressType)
    {
        case CharacterProgressStatType::HealthRegen:
            return (!GetIsDead());
        case CharacterProgressStatType::MagicRegen:
            return (!GetIsDead());
        case CharacterProgressStatType::EnergyRegen:
            return true;
        default:
            break;
    }
    return false;
}

void CharacterBattleData::UpdateEquipmentRatings(const IndexedString& sWeaponSet, const CharacterProgressItemList& vEquippedItems, const CharacterProgressData& progressData)
{
    // Get weapon set
    const CharacterWeaponSetType eWeaponSetType = StringToCharacterWeaponSetType(sWeaponSet);
    const Bool bIsWeaponSetSelected1 = (eWeaponSetType == +CharacterWeaponSetType::WeaponSet1);
    const Bool bIsWeaponSetSelected2 = (eWeaponSetType == +CharacterWeaponSetType::WeaponSet2);

    // Look through equipped items and gather information
    Float fArmor_BluntDefendPercent = 0;
    Float fArmor_PierceDefendPercent = 0;
    Float fArmor_SlashDefendPercent = 0;
    Float fArmor_MagicDefendPercent = 0;
    Float fShieldLeft_BluntDefendPercent = 0;
    Float fShieldLeft_PierceDefendPercent = 0;
    Float fShieldLeft_SlashDefendPercent = 0;
    Float fShieldLeft_MagicDefendPercent = 0;
    Float fShieldRight_BluntDefendPercent = 0;
    Float fShieldRight_PierceDefendPercent = 0;
    Float fShieldRight_SlashDefendPercent = 0;
    Float fShieldRight_MagicDefendPercent = 0;
    Float fWeaponLeft_BluntAttackPercent = 0;
    Float fWeaponLeft_PierceAttackPercent = 0;
    Float fWeaponLeft_SlashAttackPercent = 0;
    Float fWeaponRight_BluntAttackPercent = 0;
    Float fWeaponRight_PierceAttackPercent = 0;
    Float fWeaponRight_SlashAttackPercent = 0;
    for(auto&& progressItem : vEquippedItems)
    {
        const ItemTreeType eItemTreeType = StringToItemTreeType(progressItem.GetTreeIndex().GetTree());
        const CharacterEquipmentType eEquipType = StringToCharacterEquipmentType(progressItem.GetItemSlot());
        const Bool bValidEquipLeft =
            (bIsWeaponSetSelected1 && (eEquipType == +CharacterEquipmentType::Weapon1Left)) ||
            (bIsWeaponSetSelected2 && (eEquipType == +CharacterEquipmentType::Weapon2Left));
        const Bool bValidEquipRight =
            (bIsWeaponSetSelected1 && (eEquipType == +CharacterEquipmentType::Weapon1Right)) ||
            (bIsWeaponSetSelected2 && (eEquipType == +CharacterEquipmentType::Weapon2Right));
        switch(eItemTreeType)
        {
            case ItemTreeType::Armor:
            {
                const Bool bIsShield = IsItemShield(progressItem.GetTreeIndex());
                const ItemDataArmor& itemArmor = RetrieveItemDataArmor(progressItem.GetTreeIndex());
                if(bIsShield && bValidEquipLeft)
                {
                    fShieldLeft_BluntDefendPercent = itemArmor.GetBluntDefendPercent();
                    fShieldLeft_PierceDefendPercent = itemArmor.GetPierceDefendPercent();
                    fShieldLeft_SlashDefendPercent = itemArmor.GetSlashDefendPercent();
                    fShieldLeft_MagicDefendPercent = itemArmor.GetMagicDefendPercent();
                }
                else if(bIsShield && bValidEquipRight)
                {
                    fShieldRight_BluntDefendPercent = itemArmor.GetBluntDefendPercent();
                    fShieldRight_PierceDefendPercent = itemArmor.GetPierceDefendPercent();
                    fShieldRight_SlashDefendPercent = itemArmor.GetSlashDefendPercent();
                    fShieldRight_MagicDefendPercent = itemArmor.GetMagicDefendPercent();
                }
                else
                {
                    fArmor_BluntDefendPercent += itemArmor.GetBluntDefendPercent();
                    fArmor_PierceDefendPercent += itemArmor.GetPierceDefendPercent();
                    fArmor_SlashDefendPercent += itemArmor.GetSlashDefendPercent();
                    fArmor_MagicDefendPercent += itemArmor.GetMagicDefendPercent();
                }
                break;
            }
            case ItemTreeType::Weapon:
            {
                const ItemDataWeapon& itemWeapon = RetrieveItemDataWeapon(progressItem.GetTreeIndex());
                if(bValidEquipLeft)
                {
                    fWeaponLeft_BluntAttackPercent = itemWeapon.GetBluntAttackPercent();
                    fWeaponLeft_PierceAttackPercent = itemWeapon.GetPierceAttackPercent();
                    fWeaponLeft_SlashAttackPercent = itemWeapon.GetSlashAttackPercent();
                }
                else if(bValidEquipRight)
                {
                    fWeaponRight_BluntAttackPercent = itemWeapon.GetBluntAttackPercent();
                    fWeaponRight_PierceAttackPercent = itemWeapon.GetPierceAttackPercent();
                    fWeaponRight_SlashAttackPercent = itemWeapon.GetSlashAttackPercent();
                }
                break;
            }
            default:
                break;
        }
    }

    // Fill out equipment ratings
    SetEquippedWeaponLeftBluntRating(fWeaponLeft_BluntAttackPercent * progressData.GetBluntAttack());
    SetEquippedWeaponLeftPierceRating(fWeaponLeft_PierceAttackPercent * progressData.GetPierceAttack());
    SetEquippedWeaponLeftSlashRating(fWeaponLeft_SlashAttackPercent * progressData.GetSlashAttack());
    SetEquippedWeaponRightBluntRating(fWeaponRight_BluntAttackPercent * progressData.GetBluntAttack());
    SetEquippedWeaponRightPierceRating(fWeaponRight_PierceAttackPercent * progressData.GetPierceAttack());
    SetEquippedWeaponRightSlashRating(fWeaponRight_SlashAttackPercent * progressData.GetSlashAttack());
    SetEquippedShieldLeftBluntRating(fShieldLeft_BluntDefendPercent * progressData.GetBluntDefense());
    SetEquippedShieldLeftPierceRating(fShieldLeft_PierceDefendPercent * progressData.GetPierceDefense());
    SetEquippedShieldLeftSlashRating(fShieldLeft_SlashDefendPercent * progressData.GetSlashDefense());
    SetEquippedShieldLeftMagicRating(fShieldLeft_MagicDefendPercent * progressData.GetMagicDefense());
    SetEquippedShieldRightBluntRating(fShieldRight_BluntDefendPercent * progressData.GetBluntDefense());
    SetEquippedShieldRightPierceRating(fShieldRight_PierceDefendPercent * progressData.GetPierceDefense());
    SetEquippedShieldRightSlashRating(fShieldRight_SlashDefendPercent * progressData.GetSlashDefense());
    SetEquippedShieldRightMagicRating(fShieldRight_MagicDefendPercent * progressData.GetMagicDefense());
    SetEquippedArmorBluntRating(fArmor_BluntDefendPercent * progressData.GetBluntDefense());
    SetEquippedArmorPierceRating(fArmor_PierceDefendPercent * progressData.GetPierceDefense());
    SetEquippedArmorSlashRating(fArmor_SlashDefendPercent * progressData.GetSlashDefense());
    SetEquippedArmorMagicRating(fArmor_MagicDefendPercent * progressData.GetMagicDefense());
}

Bool CharacterBattleData::GetPrimaryWeaponRatings(const IndexedString& sHandedness,
    Float& fPrimaryBlunt,
    Float& fPrimaryPierce,
    Float& fPrimarySlash) const
{
    const CharacterHandednessType eType = StringToCharacterHandednessType(sHandedness);
    switch(eType)
    {
        case CharacterHandednessType::LeftHanded:
            fPrimaryBlunt = GetEquippedWeaponLeftBluntRating();
            fPrimaryPierce = GetEquippedWeaponLeftPierceRating();
            fPrimarySlash = GetEquippedWeaponLeftSlashRating();
            return true;
        case CharacterHandednessType::RightHanded:
            fPrimaryBlunt = GetEquippedWeaponRightBluntRating();
            fPrimaryPierce = GetEquippedWeaponRightPierceRating();
            fPrimarySlash = GetEquippedWeaponRightSlashRating();
            return true;
        default:
            break;
    }
    return false;
}

Bool CharacterBattleData::GetSecondaryWeaponRatings(const IndexedString& sHandedness,
    Float& fSecondaryBlunt,
    Float& fSecondaryPierce,
    Float& fSecondarySlash) const
{
    const CharacterHandednessType eType = StringToCharacterHandednessType(sHandedness);
    switch(eType)
    {
        case CharacterHandednessType::LeftHanded:
            fSecondaryBlunt = GetEquippedWeaponRightBluntRating();
            fSecondaryPierce = GetEquippedWeaponRightPierceRating();
            fSecondarySlash = GetEquippedWeaponRightSlashRating();
            return true;
        case CharacterHandednessType::RightHanded:
            fSecondaryBlunt = GetEquippedWeaponLeftBluntRating();
            fSecondaryPierce = GetEquippedWeaponLeftPierceRating();
            fSecondarySlash = GetEquippedWeaponLeftSlashRating();
            return true;
        default:
            break;
    }
    return false;
}

Bool CharacterBattleData::GetPrimaryShieldRatings(const IndexedString& sHandedness,
    Float& fPrimaryBlunt,
    Float& fPrimaryPierce,
    Float& fPrimarySlash) const
{
    const CharacterHandednessType eType = StringToCharacterHandednessType(sHandedness);
    switch(eType)
    {
        case CharacterHandednessType::LeftHanded:
            fPrimaryBlunt = GetEquippedShieldLeftBluntRating();
            fPrimaryPierce = GetEquippedShieldLeftPierceRating();
            fPrimarySlash = GetEquippedShieldLeftSlashRating();
            return true;
        case CharacterHandednessType::RightHanded:
            fPrimaryBlunt = GetEquippedShieldRightBluntRating();
            fPrimaryPierce = GetEquippedShieldRightPierceRating();
            fPrimarySlash = GetEquippedShieldRightSlashRating();
            return true;
        default:
            break;
    }
    return false;
}

Bool CharacterBattleData::GetSecondaryShieldRatings(const IndexedString& sHandedness,
    Float& fSecondaryBlunt,
    Float& fSecondaryPierce,
    Float& fSecondarySlash) const
{
    const CharacterHandednessType eType = StringToCharacterHandednessType(sHandedness);
    switch(eType)
    {
        case CharacterHandednessType::LeftHanded:
            fSecondaryBlunt = GetEquippedShieldRightBluntRating();
            fSecondaryPierce = GetEquippedShieldRightPierceRating();
            fSecondarySlash = GetEquippedShieldRightSlashRating();
            return true;
        case CharacterHandednessType::RightHanded:
            fSecondaryBlunt = GetEquippedShieldLeftBluntRating();
            fSecondaryPierce = GetEquippedShieldLeftPierceRating();
            fSecondarySlash = GetEquippedShieldLeftSlashRating();
            return true;
        default:
            break;
    }
    return false;
}

Bool CharacterBattleData::GetBoolStatValue(const IndexedString& sStat, Bool& bValue) const
{
    const CharacterBattleStatType eBattleType = (IsValidCharacterBattleStatType(sStat)) ? StringToCharacterBattleStatType(sStat) : +CharacterBattleStatType::None;
    switch(eBattleType)
    {
        case CharacterBattleStatType::IsDead:
            bValue = GetIsDead();
            return true;
        case CharacterBattleStatType::IsUnconscious:
            bValue = GetIsUnconscious();
            return true;
        default:
            break;
    }
    return false;
}

Bool CharacterBattleData::GetIntStatValue(const IndexedString& sStat, Int& iValue) const
{
    const CharacterBattleStatType eBattleType = (IsValidCharacterBattleStatType(sStat)) ? StringToCharacterBattleStatType(sStat) : +CharacterBattleStatType::None;
    switch(eBattleType)
    {
        case CharacterBattleStatType::AllowedTargetAmount:
            iValue = GetAllowedTargetAmount();
            return true;
        case CharacterBattleStatType::DamageTakenThisRound:
            iValue = GetDamageTakenThisRound();
            return true;
        case CharacterBattleStatType::DamageTakenThisBattle:
            iValue = GetDamageTakenThisBattle();
            return true;
        case CharacterBattleStatType::DamageGivenThisRound:
            iValue = GetDamageGivenThisRound();
            return true;
        case CharacterBattleStatType::DamageGivenThisBattle:
            iValue = GetDamageGivenThisBattle();
            return true;
        default:
            break;
    }
    return false;
}

Bool CharacterBattleData::GetFloatStatValue(const IndexedString& sStat, Float& fValue) const
{
    const CharacterBattleStatType eBattleType = (IsValidCharacterBattleStatType(sStat)) ? StringToCharacterBattleStatType(sStat) : +CharacterBattleStatType::None;
    switch(eBattleType)
    {
        case CharacterBattleStatType::EquippedWeaponLeftBluntRating:
            fValue = GetEquippedWeaponLeftBluntRating();
            return true;
        case CharacterBattleStatType::EquippedWeaponLeftPierceRating:
            fValue = GetEquippedWeaponLeftPierceRating();
            return true;
        case CharacterBattleStatType::EquippedWeaponLeftSlashRating:
            fValue = GetEquippedWeaponLeftSlashRating();
            return true;
        case CharacterBattleStatType::EquippedWeaponRightBluntRating:
            fValue = GetEquippedWeaponRightBluntRating();
            return true;
        case CharacterBattleStatType::EquippedWeaponRightPierceRating:
            fValue = GetEquippedWeaponRightPierceRating();
            return true;
        case CharacterBattleStatType::EquippedWeaponRightSlashRating:
            fValue = GetEquippedWeaponRightSlashRating();
            return true;
        case CharacterBattleStatType::EquippedShieldLeftBluntRating:
            fValue = GetEquippedShieldLeftBluntRating();
            return true;
        case CharacterBattleStatType::EquippedShieldLeftPierceRating:
            fValue = GetEquippedShieldLeftPierceRating();
            return true;
        case CharacterBattleStatType::EquippedShieldLeftSlashRating:
            fValue = GetEquippedShieldLeftSlashRating();
            return true;
        case CharacterBattleStatType::EquippedShieldLeftMagicRating:
            fValue = GetEquippedShieldLeftMagicRating();
            return true;
        case CharacterBattleStatType::EquippedShieldRightBluntRating:
            fValue = GetEquippedShieldRightBluntRating();
            return true;
        case CharacterBattleStatType::EquippedShieldRightPierceRating:
            fValue = GetEquippedShieldRightPierceRating();
            return true;
        case CharacterBattleStatType::EquippedShieldRightSlashRating:
            fValue = GetEquippedShieldRightSlashRating();
            return true;
        case CharacterBattleStatType::EquippedShieldRightMagicRating:
            fValue = GetEquippedShieldRightMagicRating();
            return true;
        case CharacterBattleStatType::EquippedArmorBluntRating:
            fValue = GetEquippedArmorBluntRating();
            return true;
        case CharacterBattleStatType::EquippedArmorPierceRating:
            fValue = GetEquippedArmorPierceRating();
            return true;
        case CharacterBattleStatType::EquippedArmorSlashRating:
            fValue = GetEquippedArmorSlashRating();
            return true;
        case CharacterBattleStatType::EquippedArmorMagicRating:
            fValue = GetEquippedArmorMagicRating();
            return true;
        case CharacterBattleStatType::ChanceToCauseCriticalHit:
            fValue = GetChanceToCauseCriticalHit();
            return true;
        case CharacterBattleStatType::ChanceToBlockCriticalHit:
            fValue = GetChanceToBlockCriticalHit();
            return true;
        case CharacterBattleStatType::CriticalHitMultiplier:
            fValue = GetCriticalHitMultiplier();
            return true;
        case CharacterBattleStatType::ChanceToApplyMultipleAttacks:
            fValue = GetChanceToApplyMultipleAttacks();
            return true;
        case CharacterBattleStatType::AttacksMultiplier:
            fValue = GetAttacksMultiplier();
            return true;
        case CharacterBattleStatType::WeaponPrimaryDamageBonusValue:
            fValue = GetWeaponPrimaryDamageBonusValue();
            return true;
        case CharacterBattleStatType::WeaponPrimaryDamageBonusPercent:
            fValue = GetWeaponPrimaryDamageBonusPercent();
            return true;
        case CharacterBattleStatType::WeaponSecondaryDamageBonusValue:
            fValue = GetWeaponSecondaryDamageBonusValue();
            return true;
        case CharacterBattleStatType::WeaponSecondaryDamageBonusPercent:
            fValue = GetWeaponSecondaryDamageBonusPercent();
            return true;
        case CharacterBattleStatType::GeneralDamageBonusValue:
            fValue = GetGeneralDamageBonusValue();
            return true;
        case CharacterBattleStatType::GeneralDamageBonusPercent:
            fValue = GetGeneralDamageBonusPercent();
            return true;
        case CharacterBattleStatType::DefensivePowerEffectsBonusValue:
            fValue = GetDefensivePowerEffectsBonusValue();
            return true;
        case CharacterBattleStatType::DefensivePowerEffectsBonusPercent:
            fValue = GetDefensivePowerEffectsBonusPercent();
            return true;
        case CharacterBattleStatType::OffensivePowerEffectsBonusValue:
            fValue = GetOffensivePowerEffectsBonusValue();
            return true;
        case CharacterBattleStatType::OffensivePowerEffectsBonusPercent:
            fValue = GetOffensivePowerEffectsBonusPercent();
            return true;
        default:
            break;
    }
    return false;
}

Bool CharacterBattleData::GetStringStatValue(const IndexedString& sStat, IndexedString& sValue) const
{
    const CharacterBattleStatType eBattleType = (IsValidCharacterBattleStatType(sStat)) ? StringToCharacterBattleStatType(sStat) : +CharacterBattleStatType::None;
    switch(eBattleType)
    {
        case CharacterBattleStatType::DefendTargetThisAction:
            sValue = GetDefendTargetThisAction();
            return true;
        case CharacterBattleStatType::MostRecentDefendTarget:
            sValue = GetMostRecentDefendTarget();
            return true;
        default:
            break;
    }
    return false;
}

Bool CharacterBattleData::GetStringListStatValue(const IndexedString& sStat, IndexedStringList& vValues) const
{
    const CharacterBattleStatType eBattleType = (IsValidCharacterBattleStatType(sStat)) ? StringToCharacterBattleStatType(sStat) : +CharacterBattleStatType::None;
    switch(eBattleType)
    {
        case CharacterBattleStatType::AttackTargetsThisAction:
            vValues = GetAttackTargetsThisAction();
            return true;
        case CharacterBattleStatType::AttackTargetsThisRound:
            vValues = GetAttackTargetsThisRound();
            return true;
        case CharacterBattleStatType::DefendTargetsThisRound:
            vValues = GetDefendTargetsThisRound();
            return true;
        case CharacterBattleStatType::AttackTargetsLastRound:
            vValues = GetAttackTargetsLastRound();
            return true;
        case CharacterBattleStatType::DefendTargetsLastRound:
            vValues = GetDefendTargetsLastRound();
            return true;
        case CharacterBattleStatType::MostRecentAttackTargets:
            vValues = GetMostRecentAttackTargets();
            return true;
        default:
            break;
    }
    return false;
}

Bool CharacterBattleData::SetBoolStatValue(const IndexedString& sStat, const Bool& bValue)
{
    const CharacterBattleStatType eBattleType = (IsValidCharacterBattleStatType(sStat)) ? StringToCharacterBattleStatType(sStat) : +CharacterBattleStatType::None;
    switch(eBattleType)
    {
        case CharacterBattleStatType::IsDead:
            SetIsDead(bValue);
            return true;
        case CharacterBattleStatType::IsUnconscious:
            SetIsUnconscious(bValue);
            return true;
        default:
            break;
    }
    return false;
}

Bool CharacterBattleData::SetIntStatValue(const IndexedString& sStat, const Int& iValue)
{
    const CharacterBattleStatType eBattleType = (IsValidCharacterBattleStatType(sStat)) ? StringToCharacterBattleStatType(sStat) : +CharacterBattleStatType::None;
    switch(eBattleType)
    {
        case CharacterBattleStatType::AllowedTargetAmount:
            SetAllowedTargetAmount(iValue);
            return true;
        case CharacterBattleStatType::DamageTakenThisRound:
            SetDamageTakenThisRound(iValue);
            return true;
        case CharacterBattleStatType::DamageTakenThisBattle:
            SetDamageTakenThisBattle(iValue);
            return true;
        case CharacterBattleStatType::DamageGivenThisRound:
            SetDamageGivenThisRound(iValue);
            return true;
        case CharacterBattleStatType::DamageGivenThisBattle:
            SetDamageGivenThisBattle(iValue);
            return true;
        default:
            break;
    }
    return false;
}

Bool CharacterBattleData::SetFloatStatValue(const IndexedString& sStat, const Float& fValue)
{
    const CharacterBattleStatType eBattleType = (IsValidCharacterBattleStatType(sStat)) ? StringToCharacterBattleStatType(sStat) : +CharacterBattleStatType::None;
    switch(eBattleType)
    {
        case CharacterBattleStatType::EquippedWeaponLeftBluntRating:
            SetEquippedWeaponLeftBluntRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedWeaponLeftPierceRating:
            SetEquippedWeaponLeftPierceRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedWeaponLeftSlashRating:
            SetEquippedWeaponLeftSlashRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedWeaponRightBluntRating:
            SetEquippedWeaponRightBluntRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedWeaponRightPierceRating:
            SetEquippedWeaponRightPierceRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedWeaponRightSlashRating:
            SetEquippedWeaponRightSlashRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedShieldLeftBluntRating:
            SetEquippedShieldLeftBluntRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedShieldLeftPierceRating:
            SetEquippedShieldLeftPierceRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedShieldLeftSlashRating:
            SetEquippedShieldLeftSlashRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedShieldLeftMagicRating:
            SetEquippedShieldLeftMagicRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedShieldRightBluntRating:
            SetEquippedShieldRightBluntRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedShieldRightPierceRating:
            SetEquippedShieldRightPierceRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedShieldRightSlashRating:
            SetEquippedShieldRightSlashRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedShieldRightMagicRating:
            SetEquippedShieldRightMagicRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedArmorBluntRating:
            SetEquippedArmorBluntRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedArmorPierceRating:
            SetEquippedArmorPierceRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedArmorSlashRating:
            SetEquippedArmorSlashRating(fValue);
            return true;
        case CharacterBattleStatType::EquippedArmorMagicRating:
            SetEquippedArmorMagicRating(fValue);
            return true;
        case CharacterBattleStatType::ChanceToCauseCriticalHit:
            SetChanceToCauseCriticalHit(fValue);
            return true;
        case CharacterBattleStatType::ChanceToBlockCriticalHit:
            SetChanceToBlockCriticalHit(fValue);
            return true;
        case CharacterBattleStatType::CriticalHitMultiplier:
            SetCriticalHitMultiplier(fValue);
            return true;
        case CharacterBattleStatType::ChanceToApplyMultipleAttacks:
            SetChanceToApplyMultipleAttacks(fValue);
            return true;
        case CharacterBattleStatType::AttacksMultiplier:
            SetAttacksMultiplier(fValue);
            return true;
        case CharacterBattleStatType::WeaponPrimaryDamageBonusValue:
            SetWeaponPrimaryDamageBonusValue(fValue);
            return true;
        case CharacterBattleStatType::WeaponPrimaryDamageBonusPercent:
            SetWeaponPrimaryDamageBonusPercent(fValue);
            return true;
        case CharacterBattleStatType::WeaponSecondaryDamageBonusValue:
            SetWeaponSecondaryDamageBonusValue(fValue);
            return true;
        case CharacterBattleStatType::WeaponSecondaryDamageBonusPercent:
            SetWeaponSecondaryDamageBonusPercent(fValue);
            return true;
        case CharacterBattleStatType::GeneralDamageBonusValue:
            SetGeneralDamageBonusValue(fValue);
            return true;
        case CharacterBattleStatType::GeneralDamageBonusPercent:
            SetGeneralDamageBonusPercent(fValue);
            return true;
        case CharacterBattleStatType::DefensivePowerEffectsBonusValue:
            SetDefensivePowerEffectsBonusValue(fValue);
            return true;
        case CharacterBattleStatType::DefensivePowerEffectsBonusPercent:
            SetDefensivePowerEffectsBonusPercent(fValue);
            return true;
        case CharacterBattleStatType::OffensivePowerEffectsBonusValue:
            SetOffensivePowerEffectsBonusValue(fValue);
            return true;
        case CharacterBattleStatType::OffensivePowerEffectsBonusPercent:
            SetOffensivePowerEffectsBonusPercent(fValue);
            return true;
        default:
            break;
    }
    return false;
}

Bool CharacterBattleData::SetStringStatValue(const IndexedString& sStat, const IndexedString& sValue)
{
    const CharacterBattleStatType eBattleType = (IsValidCharacterBattleStatType(sStat)) ? StringToCharacterBattleStatType(sStat) : +CharacterBattleStatType::None;
    switch(eBattleType)
    {
        case CharacterBattleStatType::DefendTargetThisAction:
            SetDefendTargetThisAction(sValue);
            return true;
        case CharacterBattleStatType::MostRecentDefendTarget:
            SetMostRecentDefendTarget(sValue);
            return true;
        default:
            break;
    }
    return false;
}

Bool CharacterBattleData::SetStringListStatValue(const IndexedString& sStat, const IndexedStringList& vValues)
{
    const CharacterBattleStatType eBattleType = (IsValidCharacterBattleStatType(sStat)) ? StringToCharacterBattleStatType(sStat) : +CharacterBattleStatType::None;
    switch(eBattleType)
    {
        case CharacterBattleStatType::AttackTargetsThisAction:
            SetAttackTargetsThisAction(vValues);
            return true;
        case CharacterBattleStatType::AttackTargetsThisRound:
            SetAttackTargetsThisRound(vValues);
            return true;
        case CharacterBattleStatType::DefendTargetsThisRound:
            SetDefendTargetsThisRound(vValues);
            return true;
        case CharacterBattleStatType::AttackTargetsLastRound:
            SetAttackTargetsLastRound(vValues);
            return true;
        case CharacterBattleStatType::DefendTargetsLastRound:
            SetDefendTargetsLastRound(vValues);
            return true;
        case CharacterBattleStatType::MostRecentAttackTargets:
            SetMostRecentAttackTargets(vValues);
            return true;
        default:
            break;
    }
    return false;
}

static STDUnorderedSet<String> s_tBoolStatNames = {};
static STDUnorderedSet<String> s_tUByteStatNames = {};
static STDUnorderedSet<String> s_tIntStatNames = {};
static STDUnorderedSet<String> s_tFloatStatNames = {};
static STDUnorderedSet<String> s_tIndexedStringStatNames = {};
static STDUnorderedSet<String> s_tIndexedStringListStatNames = {};
STDUnorderedSet<String>& CharacterBattleData::GetBoolStatNames() { return s_tBoolStatNames; }
STDUnorderedSet<String>& CharacterBattleData::GetUByteStatNames() { return s_tUByteStatNames; }
STDUnorderedSet<String>& CharacterBattleData::GetIntStatNames() { return s_tIntStatNames; }
STDUnorderedSet<String>& CharacterBattleData::GetFloatStatNames() { return s_tFloatStatNames; }
STDUnorderedSet<String>& CharacterBattleData::GetIndexedStringStatNames() { return s_tIndexedStringStatNames; }
STDUnorderedSet<String>& CharacterBattleData::GetIndexedStringListStatNames() { return s_tIndexedStringListStatNames; }

static Bool s_bCharacterBattleData_StatNamesInitialized = false;
void CharacterBattleData::InitAllStatNames()
{
    // Check initialization
    if(s_bCharacterBattleData_StatNamesInitialized)
    {
        return;
    }

    // -- Target Characters --
    InitAttackTargetsThisAction();
    InitAttackTargetsThisRound();
    InitAttackTargetsLastRound();
    InitDefendTargetThisAction();
    InitDefendTargetsThisRound();
    InitDefendTargetsLastRound();
    InitMostRecentAttackTargets();
    InitMostRecentDefendTarget();

    // -- Target Amounts --
    InitAllowedTargetAmount();

    // -- Status --
    InitIsDead();
    InitIsUnconscious();

    // -- Equipment Ratings --
    InitEquippedWeaponLeftBluntRating();
    InitEquippedWeaponLeftPierceRating();
    InitEquippedWeaponLeftSlashRating();
    InitEquippedWeaponRightBluntRating();
    InitEquippedWeaponRightPierceRating();
    InitEquippedWeaponRightSlashRating();
    InitEquippedShieldLeftBluntRating();
    InitEquippedShieldLeftPierceRating();
    InitEquippedShieldLeftSlashRating();
    InitEquippedShieldLeftMagicRating();
    InitEquippedShieldRightBluntRating();
    InitEquippedShieldRightPierceRating();
    InitEquippedShieldRightSlashRating();
    InitEquippedShieldRightMagicRating();
    InitEquippedArmorBluntRating();
    InitEquippedArmorPierceRating();
    InitEquippedArmorSlashRating();
    InitEquippedArmorMagicRating();

    // -- Critical Hits --
    InitChanceToCauseCriticalHit();
    InitChanceToBlockCriticalHit();
    InitCriticalHitMultiplier();

    // -- Multiple Attacks --
    InitChanceToApplyMultipleAttacks();
    InitAttacksMultiplier();

    // -- Damage Counters --
    InitDamageTakenThisRound();
    InitDamageTakenThisBattle();
    InitDamageGivenThisRound();
    InitDamageGivenThisBattle();

    // -- Damage Bonus --
    InitWeaponPrimaryDamageBonusValue();
    InitWeaponPrimaryDamageBonusPercent();
    InitWeaponSecondaryDamageBonusValue();
    InitWeaponSecondaryDamageBonusPercent();
    InitGeneralDamageBonusValue();
    InitGeneralDamageBonusPercent();

    // -- Effects Bonus --
    InitDefensivePowerEffectsBonusValue();
    InitDefensivePowerEffectsBonusPercent();
    InitOffensivePowerEffectsBonusValue();
    InitOffensivePowerEffectsBonusPercent();

    // Finished
    s_bCharacterBattleData_StatNamesInitialized = true;
}

Bool CharacterBattleData::operator==(const CharacterBattleData& other) const
{
    return (Json(*this) == Json(other));
}

Bool CharacterBattleData::operator!=(const CharacterBattleData& other) const
{
    return not operator==(other);
}

void to_json(Json& jsonData, const CharacterBattleData& obj)
{
    // Get current configuration
    const Config& config = ConfigManager::GetInstance()->GetCurrentConfig();

    // -- Target Amounts --
    SET_JSON_DATA_IF_NOT_DEFAULT(AllowedTargetAmount, config.GetDefaultAllowedTargetAmount());

    // -- Equipment Ratings --
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedWeaponLeftBluntRating, config.GetDefaultEquippedWeaponLeftBluntRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedWeaponLeftPierceRating, config.GetDefaultEquippedWeaponLeftPierceRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedWeaponLeftSlashRating, config.GetDefaultEquippedWeaponLeftSlashRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedWeaponRightBluntRating, config.GetDefaultEquippedWeaponRightBluntRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedWeaponRightPierceRating, config.GetDefaultEquippedWeaponRightPierceRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedWeaponRightSlashRating, config.GetDefaultEquippedWeaponRightSlashRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedShieldLeftBluntRating, config.GetDefaultEquippedShieldLeftBluntRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedShieldLeftPierceRating, config.GetDefaultEquippedShieldLeftPierceRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedShieldLeftSlashRating, config.GetDefaultEquippedShieldLeftSlashRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedShieldLeftMagicRating, config.GetDefaultEquippedShieldLeftMagicRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedShieldRightBluntRating, config.GetDefaultEquippedShieldRightBluntRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedShieldRightPierceRating, config.GetDefaultEquippedShieldRightPierceRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedShieldRightSlashRating, config.GetDefaultEquippedShieldRightSlashRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedShieldRightMagicRating, config.GetDefaultEquippedShieldRightMagicRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedArmorBluntRating, config.GetDefaultEquippedArmorBluntRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedArmorPierceRating, config.GetDefaultEquippedArmorPierceRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedArmorSlashRating, config.GetDefaultEquippedArmorSlashRating());
    SET_JSON_DATA_IF_NOT_DEFAULT(EquippedArmorMagicRating, config.GetDefaultEquippedArmorMagicRating());

    // -- Critical Hits --
    SET_JSON_DATA_IF_NOT_DEFAULT(ChanceToCauseCriticalHit, config.GetDefaultChanceToCauseCriticalHit());
    SET_JSON_DATA_IF_NOT_DEFAULT(ChanceToBlockCriticalHit, config.GetDefaultChanceToBlockCriticalHit());
    SET_JSON_DATA_IF_NOT_DEFAULT(CriticalHitMultiplier, config.GetDefaultCriticalHitMultiplier());

    // -- Multiple Attacks --
    SET_JSON_DATA_IF_NOT_DEFAULT(ChanceToApplyMultipleAttacks, config.GetDefaultChanceToApplyMultipleAttacks());
    SET_JSON_DATA_IF_NOT_DEFAULT(AttacksMultiplier, config.GetDefaultAttacksMultiplier());

    // -- Damage Bonus --
    SET_JSON_DATA_IF_NOT_DEFAULT(WeaponPrimaryDamageBonusValue, config.GetDefaultWeaponPrimaryDamageBonusValue());
    SET_JSON_DATA_IF_NOT_DEFAULT(WeaponPrimaryDamageBonusPercent, config.GetDefaultWeaponPrimaryDamageBonusPercent());
    SET_JSON_DATA_IF_NOT_DEFAULT(WeaponSecondaryDamageBonusValue, config.GetDefaultWeaponSecondaryDamageBonusValue());
    SET_JSON_DATA_IF_NOT_DEFAULT(WeaponSecondaryDamageBonusPercent, config.GetDefaultWeaponSecondaryDamageBonusPercent());
    SET_JSON_DATA_IF_NOT_DEFAULT(GeneralDamageBonusValue, config.GetDefaultGeneralDamageBonusValue());
    SET_JSON_DATA_IF_NOT_DEFAULT(GeneralDamageBonusPercent, config.GetDefaultGeneralDamageBonusPercent());

    // -- Effects Bonus --
    SET_JSON_DATA_IF_NOT_DEFAULT(DefensivePowerEffectsBonusValue, config.GetDefaultDefensivePowerEffectsBonusValue());
    SET_JSON_DATA_IF_NOT_DEFAULT(DefensivePowerEffectsBonusPercent, config.GetDefaultDefensivePowerEffectsBonusPercent());
    SET_JSON_DATA_IF_NOT_DEFAULT(OffensivePowerEffectsBonusValue, config.GetDefaultOffensivePowerEffectsBonusValue());
    SET_JSON_DATA_IF_NOT_DEFAULT(OffensivePowerEffectsBonusPercent, config.GetDefaultOffensivePowerEffectsBonusPercent());
}

void from_json(const Json& jsonData, CharacterBattleData& obj)
{
    // Get current configuration
    const Config& config = ConfigManager::GetInstance()->GetCurrentConfig();

    // -- Target Amounts --
    obj.SetAllowedTargetAmount(GET_JSON_DATA_OR_DEFAULT(AllowedTargetAmount, Int, config.GetDefaultAllowedTargetAmount()));

    // -- Equipment Ratings --
    obj.SetEquippedWeaponLeftBluntRating(GET_JSON_DATA_OR_DEFAULT(EquippedWeaponLeftBluntRating, Float, config.GetDefaultEquippedWeaponLeftBluntRating()));
    obj.SetEquippedWeaponLeftPierceRating(GET_JSON_DATA_OR_DEFAULT(EquippedWeaponLeftPierceRating, Float, config.GetDefaultEquippedWeaponLeftPierceRating()));
    obj.SetEquippedWeaponLeftSlashRating(GET_JSON_DATA_OR_DEFAULT(EquippedWeaponLeftSlashRating, Float, config.GetDefaultEquippedWeaponLeftSlashRating()));
    obj.SetEquippedWeaponRightBluntRating(GET_JSON_DATA_OR_DEFAULT(EquippedWeaponRightBluntRating, Float, config.GetDefaultEquippedWeaponRightBluntRating()));
    obj.SetEquippedWeaponRightPierceRating(GET_JSON_DATA_OR_DEFAULT(EquippedWeaponRightPierceRating, Float, config.GetDefaultEquippedWeaponRightPierceRating()));
    obj.SetEquippedWeaponRightSlashRating(GET_JSON_DATA_OR_DEFAULT(EquippedWeaponRightSlashRating, Float, config.GetDefaultEquippedWeaponRightSlashRating()));
    obj.SetEquippedShieldLeftBluntRating(GET_JSON_DATA_OR_DEFAULT(EquippedShieldLeftBluntRating, Float, config.GetDefaultEquippedShieldLeftBluntRating()));
    obj.SetEquippedShieldLeftPierceRating(GET_JSON_DATA_OR_DEFAULT(EquippedShieldLeftPierceRating, Float, config.GetDefaultEquippedShieldLeftPierceRating()));
    obj.SetEquippedShieldLeftSlashRating(GET_JSON_DATA_OR_DEFAULT(EquippedShieldLeftSlashRating, Float, config.GetDefaultEquippedShieldLeftSlashRating()));
    obj.SetEquippedShieldLeftMagicRating(GET_JSON_DATA_OR_DEFAULT(EquippedShieldLeftMagicRating, Float, config.GetDefaultEquippedShieldLeftMagicRating()));
    obj.SetEquippedShieldRightBluntRating(GET_JSON_DATA_OR_DEFAULT(EquippedShieldRightBluntRating, Float, config.GetDefaultEquippedShieldRightBluntRating()));
    obj.SetEquippedShieldRightPierceRating(GET_JSON_DATA_OR_DEFAULT(EquippedShieldRightPierceRating, Float, config.GetDefaultEquippedShieldRightPierceRating()));
    obj.SetEquippedShieldRightSlashRating(GET_JSON_DATA_OR_DEFAULT(EquippedShieldRightSlashRating, Float, config.GetDefaultEquippedShieldRightSlashRating()));
    obj.SetEquippedShieldRightMagicRating(GET_JSON_DATA_OR_DEFAULT(EquippedShieldRightMagicRating, Float, config.GetDefaultEquippedShieldRightMagicRating()));
    obj.SetEquippedArmorBluntRating(GET_JSON_DATA_OR_DEFAULT(EquippedArmorBluntRating, Float, config.GetDefaultEquippedArmorBluntRating()));
    obj.SetEquippedArmorPierceRating(GET_JSON_DATA_OR_DEFAULT(EquippedArmorPierceRating, Float, config.GetDefaultEquippedArmorPierceRating()));
    obj.SetEquippedArmorSlashRating(GET_JSON_DATA_OR_DEFAULT(EquippedArmorSlashRating, Float, config.GetDefaultEquippedArmorSlashRating()));
    obj.SetEquippedArmorMagicRating(GET_JSON_DATA_OR_DEFAULT(EquippedArmorMagicRating, Float, config.GetDefaultEquippedArmorMagicRating()));

    // -- Critical Hits --
    obj.SetChanceToCauseCriticalHit(GET_JSON_DATA_OR_DEFAULT(ChanceToCauseCriticalHit, Float, config.GetDefaultChanceToCauseCriticalHit()));
    obj.SetChanceToBlockCriticalHit(GET_JSON_DATA_OR_DEFAULT(ChanceToBlockCriticalHit, Float, config.GetDefaultChanceToBlockCriticalHit()));
    obj.SetCriticalHitMultiplier(GET_JSON_DATA_OR_DEFAULT(CriticalHitMultiplier, Float, config.GetDefaultCriticalHitMultiplier()));

    // -- Multiple Attacks --
    obj.SetChanceToApplyMultipleAttacks(GET_JSON_DATA_OR_DEFAULT(ChanceToApplyMultipleAttacks, Float, config.GetDefaultChanceToApplyMultipleAttacks()));
    obj.SetAttacksMultiplier(GET_JSON_DATA_OR_DEFAULT(AttacksMultiplier, Float, config.GetDefaultAttacksMultiplier()));

    // -- Damage Bonus --
    obj.SetWeaponPrimaryDamageBonusValue(GET_JSON_DATA_OR_DEFAULT(WeaponPrimaryDamageBonusValue, Float, config.GetDefaultWeaponPrimaryDamageBonusValue()));
    obj.SetWeaponPrimaryDamageBonusPercent(GET_JSON_DATA_OR_DEFAULT(WeaponPrimaryDamageBonusPercent, Float, config.GetDefaultWeaponPrimaryDamageBonusPercent()));
    obj.SetWeaponSecondaryDamageBonusValue(GET_JSON_DATA_OR_DEFAULT(WeaponSecondaryDamageBonusValue, Float, config.GetDefaultWeaponSecondaryDamageBonusValue()));
    obj.SetWeaponSecondaryDamageBonusPercent(GET_JSON_DATA_OR_DEFAULT(WeaponSecondaryDamageBonusPercent, Float, config.GetDefaultWeaponSecondaryDamageBonusPercent()));
    obj.SetGeneralDamageBonusValue(GET_JSON_DATA_OR_DEFAULT(GeneralDamageBonusValue, Float, config.GetDefaultGeneralDamageBonusValue()));
    obj.SetGeneralDamageBonusPercent(GET_JSON_DATA_OR_DEFAULT(GeneralDamageBonusPercent, Float, config.GetDefaultGeneralDamageBonusPercent()));

    // -- Effects Bonus --
    obj.SetDefensivePowerEffectsBonusValue(GET_JSON_DATA_OR_DEFAULT(DefensivePowerEffectsBonusValue, Float, config.GetDefaultDefensivePowerEffectsBonusValue()));
    obj.SetDefensivePowerEffectsBonusPercent(GET_JSON_DATA_OR_DEFAULT(DefensivePowerEffectsBonusPercent, Float, config.GetDefaultDefensivePowerEffectsBonusPercent()));
    obj.SetOffensivePowerEffectsBonusValue(GET_JSON_DATA_OR_DEFAULT(OffensivePowerEffectsBonusValue, Float, config.GetDefaultOffensivePowerEffectsBonusValue()));
    obj.SetOffensivePowerEffectsBonusPercent(GET_JSON_DATA_OR_DEFAULT(OffensivePowerEffectsBonusPercent, Float, config.GetDefaultOffensivePowerEffectsBonusPercent()));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(CharacterBattleData, CharacterBattleData);

};
