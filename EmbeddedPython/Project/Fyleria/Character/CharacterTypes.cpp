// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Character/CharacterTypes.h"
#include "Items/ItemTypes.h"
#include "Skills/SkillTypes.h"
#include "Utility/Assert.h"

namespace Gecko
{

String ConvertCharacterEquipmentTypeToCharacterWeaponSetType(const String& sCharacterEquipmentType)
{
    if(sCharacterEquipmentType.empty())
    {
        return GetNoneTypeForEnum<CharacterEquipmentType>();
    }

    const CharacterEquipmentType eCharacterEquipmentType = GetEnumFromStringOrNone<CharacterEquipmentType>(sCharacterEquipmentType);
    switch(eCharacterEquipmentType)
    {
        case CharacterEquipmentType::Weapon1Left:
        case CharacterEquipmentType::Weapon1Right:
            return (+CharacterWeaponSetType::WeaponSet1)._to_string();
        case CharacterEquipmentType::Weapon2Left:
        case CharacterEquipmentType::Weapon2Right:
            return (+CharacterWeaponSetType::WeaponSet2)._to_string();
        default:
            return GetNoneTypeForEnum<CharacterWeaponSetType>();
    }
}

String ConvertCharacterTargetTypeToCharacterPartyType(const String& sCharacterTargetType)
{
    if(sCharacterTargetType.empty())
    {
        return GetNoneTypeForEnum<CharacterTargetType>();
    }

    const CharacterTargetType eCharacterTargetType = GetEnumFromStringOrNone<CharacterTargetType>(sCharacterTargetType);
    switch(eCharacterTargetType)
    {
        case CharacterTargetType::AllAllies:
        case CharacterTargetType::Ally1:
        case CharacterTargetType::Ally2:
        case CharacterTargetType::Ally3:
        case CharacterTargetType::Ally4:
        case CharacterTargetType::Ally5:
        case CharacterTargetType::Ally6:
            return (+CharacterPartyType::Ally)._to_string();
        case CharacterTargetType::AllEnemies:
        case CharacterTargetType::Enemy1:
        case CharacterTargetType::Enemy2:
        case CharacterTargetType::Enemy3:
        case CharacterTargetType::Enemy4:
        case CharacterTargetType::Enemy5:
        case CharacterTargetType::Enemy6:
            return (+CharacterPartyType::Enemy)._to_string();
        default:
            return GetNoneTypeForEnum<CharacterPartyType>();
    }
}

String ConvertItemTypeToCharacterActionType(const String& sItemType)
{
    if(sItemType.empty())
    {
        return GetNoneTypeForEnum<CharacterActionType>();
    }

    const ItemType eItemType = GetEnumFromStringOrNone<ItemType>(sItemType);
    switch(eItemType)
    {
        case ItemType::WeaponPierce:
        case ItemType::ArmorShieldPierce:
            return (+CharacterActionType::WeaponBasePierce)._to_string();
        case ItemType::WeaponBlunt:
        case ItemType::ArmorShieldBlunt:
            return (+CharacterActionType::WeaponBaseBlunt)._to_string();
        case ItemType::WeaponSlash:
        case ItemType::ArmorShieldSlash:
            return (+CharacterActionType::WeaponBaseSlash)._to_string();
        default:
            return GetNoneTypeForEnum<CharacterActionType>();
    }
}

StringArray ConvertItemTypeToCharacterEquipTypes(const String& sItemType)
{
    StringArray vEquipTypes;
    if(sItemType.empty())
    {
        return vEquipTypes;
    }

    const ItemType eItemType = GetEnumFromStringOrNone<ItemType>(sItemType);
    switch(eItemType)
    {
        case ItemType::WeaponPierce:
        case ItemType::WeaponBlunt:
        case ItemType::WeaponSlash:
        case ItemType::WeaponMage:
        case ItemType::ArmorShieldPierce:
        case ItemType::ArmorShieldBlunt:
        case ItemType::ArmorShieldSlash:
            vEquipTypes.push_back((+CharacterEquipmentType::Weapon1Left)._to_string());
            vEquipTypes.push_back((+CharacterEquipmentType::Weapon1Right)._to_string());
            vEquipTypes.push_back((+CharacterEquipmentType::Weapon2Left)._to_string());
            vEquipTypes.push_back((+CharacterEquipmentType::Weapon2Right)._to_string());
            break;
        case ItemType::ArmorChest:
            vEquipTypes.push_back((+CharacterEquipmentType::Chest)._to_string());
            break;
        case ItemType::ArmorFeet:
            vEquipTypes.push_back((+CharacterEquipmentType::Feet)._to_string());
            break;
        case ItemType::ArmorFinger:
            vEquipTypes.push_back((+CharacterEquipmentType::LeftFingers)._to_string());
            vEquipTypes.push_back((+CharacterEquipmentType::RightFingers)._to_string());
            break;
        case ItemType::ArmorHands:
            vEquipTypes.push_back((+CharacterEquipmentType::Hands)._to_string());
            break;
        case ItemType::ArmorHead:
            vEquipTypes.push_back((+CharacterEquipmentType::Head)._to_string());
            break;
        case ItemType::ArmorLegs:
            vEquipTypes.push_back((+CharacterEquipmentType::Legs)._to_string());
            break;
        case ItemType::ArmorNeck:
            vEquipTypes.push_back((+CharacterEquipmentType::Neck)._to_string());
            break;
        default:
            break;
    }
    return vEquipTypes;
}

String ConvertSkillWeaponBaseTypeToCharacterActionType(const String& sSkillWeaponBaseType)
{
    if(sSkillWeaponBaseType.empty())
    {
        return GetNoneTypeForEnum<CharacterActionType>();
    }

    const SkillWeaponBaseType eSkillWeaponBaseType = GetEnumFromStringOrNone<SkillWeaponBaseType>(sSkillWeaponBaseType);
    switch(eSkillWeaponBaseType)
    {
        case SkillWeaponBaseType::Slash:
            return (+CharacterActionType::WeaponBaseSlash)._to_string();
        case SkillWeaponBaseType::Blunt:
            return (+CharacterActionType::WeaponBaseBlunt)._to_string();
        case SkillWeaponBaseType::Pierce:
            return (+CharacterActionType::WeaponBasePierce)._to_string();
        default:
            return GetNoneTypeForEnum<CharacterActionType>();
    }
}

String ConvertSkillWeaponTypeToCharacterActionType(const String& sSkillWeaponType)
{
    if(sSkillWeaponType.empty())
    {
        return GetNoneTypeForEnum<CharacterActionType>();
    }

    const SkillWeaponType eSkillWeaponType = GetEnumFromStringOrNone<SkillWeaponType>(sSkillWeaponType);
    switch(eSkillWeaponType)
    {
        case SkillWeaponType::Slash:
            return (+CharacterActionType::WeaponSlash)._to_string();
        case SkillWeaponType::Sever:
            return (+CharacterActionType::WeaponSever)._to_string();
        case SkillWeaponType::Slice:
            return (+CharacterActionType::WeaponSlice)._to_string();
        case SkillWeaponType::Slit:
            return (+CharacterActionType::WeaponSlit)._to_string();
        case SkillWeaponType::Cleave:
            return (+CharacterActionType::WeaponCleave)._to_string();
        case SkillWeaponType::Decapitate:
            return (+CharacterActionType::WeaponDecapitate)._to_string();
        case SkillWeaponType::Parry:
            return (+CharacterActionType::WeaponParry)._to_string();
        case SkillWeaponType::Riposte:
            return (+CharacterActionType::WeaponRiposte)._to_string();
        case SkillWeaponType::Bash:
            return (+CharacterActionType::WeaponBash)._to_string();
        case SkillWeaponType::Smash:
            return (+CharacterActionType::WeaponSmash)._to_string();
        case SkillWeaponType::Impact:
            return (+CharacterActionType::WeaponImpact)._to_string();
        case SkillWeaponType::Crush:
            return (+CharacterActionType::WeaponCrush)._to_string();
        case SkillWeaponType::Break:
            return (+CharacterActionType::WeaponBreak)._to_string();
        case SkillWeaponType::Crack:
            return (+CharacterActionType::WeaponCrack)._to_string();
        case SkillWeaponType::Block:
            return (+CharacterActionType::WeaponBlock)._to_string();
        case SkillWeaponType::Rush:
            return (+CharacterActionType::WeaponRush)._to_string();
        case SkillWeaponType::Pierce:
            return (+CharacterActionType::WeaponPierce)._to_string();
        case SkillWeaponType::Drill:
            return (+CharacterActionType::WeaponDrill)._to_string();
        case SkillWeaponType::Shoot:
            return (+CharacterActionType::WeaponShoot)._to_string();
        case SkillWeaponType::Impale:
            return (+CharacterActionType::WeaponImpale)._to_string();
        case SkillWeaponType::StealthStrike:
            return (+CharacterActionType::WeaponStealthStrike)._to_string();
        case SkillWeaponType::CriticalShot:
            return (+CharacterActionType::WeaponCriticalShot)._to_string();
        case SkillWeaponType::Dodge:
            return (+CharacterActionType::WeaponDodge)._to_string();
        case SkillWeaponType::Counter:
            return (+CharacterActionType::WeaponCounter)._to_string();
        default:
            return GetNoneTypeForEnum<CharacterActionType>();
    }
}

String ConvertSkillWeaponTypeToCharacterActionStatType(const String& sSkillWeaponType)
{
    if(sSkillWeaponType.empty())
    {
        return GetNoneTypeForEnum<CharacterActionStatType_Int>();
    }

    const SkillWeaponType eSkillWeaponType = GetEnumFromStringOrNone<SkillWeaponType>(sSkillWeaponType);
    switch(eSkillWeaponType)
    {
        case SkillWeaponType::Slash:
            return (+CharacterActionStatType_Int::SlashPoints)._to_string();
        case SkillWeaponType::Sever:
            return (+CharacterActionStatType_Int::SeverPoints)._to_string();
        case SkillWeaponType::Slice:
            return (+CharacterActionStatType_Int::SlicePoints)._to_string();
        case SkillWeaponType::Slit:
            return (+CharacterActionStatType_Int::SlitPoints)._to_string();
        case SkillWeaponType::Cleave:
            return (+CharacterActionStatType_Int::CleavePoints)._to_string();
        case SkillWeaponType::Decapitate:
            return (+CharacterActionStatType_Int::DecapitatePoints)._to_string();
        case SkillWeaponType::Parry:
            return (+CharacterActionStatType_Int::ParryPoints)._to_string();
        case SkillWeaponType::Riposte:
            return (+CharacterActionStatType_Int::RipostePoints)._to_string();
        case SkillWeaponType::Bash:
            return (+CharacterActionStatType_Int::BashPoints)._to_string();
        case SkillWeaponType::Smash:
            return (+CharacterActionStatType_Int::SmashPoints)._to_string();
        case SkillWeaponType::Impact:
            return (+CharacterActionStatType_Int::ImpactPoints)._to_string();
        case SkillWeaponType::Crush:
            return (+CharacterActionStatType_Int::CrushPoints)._to_string();
        case SkillWeaponType::Break:
            return (+CharacterActionStatType_Int::BreakPoints)._to_string();
        case SkillWeaponType::Crack:
            return (+CharacterActionStatType_Int::CrackPoints)._to_string();
        case SkillWeaponType::Block:
            return (+CharacterActionStatType_Int::BlockPoints)._to_string();
        case SkillWeaponType::Rush:
            return (+CharacterActionStatType_Int::RushPoints)._to_string();
        case SkillWeaponType::Pierce:
            return (+CharacterActionStatType_Int::PiercePoints)._to_string();
        case SkillWeaponType::Drill:
            return (+CharacterActionStatType_Int::DrillPoints)._to_string();
        case SkillWeaponType::Shoot:
            return (+CharacterActionStatType_Int::ShootPoints)._to_string();
        case SkillWeaponType::Impale:
            return (+CharacterActionStatType_Int::ImpalePoints)._to_string();
        case SkillWeaponType::StealthStrike:
            return (+CharacterActionStatType_Int::StealthStrikePoints)._to_string();
        case SkillWeaponType::CriticalShot:
            return (+CharacterActionStatType_Int::CriticalShotPoints)._to_string();
        case SkillWeaponType::Dodge:
            return (+CharacterActionStatType_Int::DodgePoints)._to_string();
        case SkillWeaponType::Counter:
            return (+CharacterActionStatType_Int::CounterPoints)._to_string();
        default:
            return GetNoneTypeForEnum<CharacterActionStatType_Int>();
    }
}

};
