// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterTypes.h"
#include "Items/ItemTypes.h"
#include "Skills/SkillTypes.h"

namespace Gecko
{

IndexedString ConvertCharacterEquipmentTypeToCharacterWeaponSetType(const IndexedString& sCharacterEquipmentType)
{
    if(!sCharacterEquipmentType.IsValid())
    {
        return IndexedString("None");
    }

    const CharacterEquipmentType eCharacterEquipmentType = (IsValidCharacterEquipmentType(sCharacterEquipmentType)) ? StringToCharacterEquipmentType(sCharacterEquipmentType) : +CharacterEquipmentType::None;
    switch(eCharacterEquipmentType)
    {
        case CharacterEquipmentType::Weapon1Left:
        case CharacterEquipmentType::Weapon1Right:
            return IndexedString("WeaponSet1");
        case CharacterEquipmentType::Weapon2Left:
        case CharacterEquipmentType::Weapon2Right:
            return IndexedString("WeaponSet2");
        default:
            return IndexedString("None");
    }
}

IndexedString ConvertCharacterTargetTypeToCharacterPartyType(const IndexedString& sCharacterTargetType)
{
    if(!sCharacterTargetType.IsValid())
    {
        return IndexedString("None");
    }

    const CharacterTargetType eCharacterTargetType = (IsValidCharacterTargetType(sCharacterTargetType)) ? StringToCharacterTargetType(sCharacterTargetType) : +CharacterTargetType::None;
    switch(eCharacterTargetType)
    {
        case CharacterTargetType::AllAllies:
        case CharacterTargetType::Ally1:
        case CharacterTargetType::Ally2:
        case CharacterTargetType::Ally3:
        case CharacterTargetType::Ally4:
        case CharacterTargetType::Ally5:
        case CharacterTargetType::Ally6:
            return IndexedString("Ally");
        case CharacterTargetType::AllEnemies:
        case CharacterTargetType::Enemy1:
        case CharacterTargetType::Enemy2:
        case CharacterTargetType::Enemy3:
        case CharacterTargetType::Enemy4:
        case CharacterTargetType::Enemy5:
        case CharacterTargetType::Enemy6:
            return IndexedString("Enemy");
        default:
            return IndexedString("None");
    }
}

IndexedString ConvertItemTypeToCharacterActionType(const IndexedString& sItemType)
{
    if(!sItemType.IsValid())
    {
        return IndexedString("None");
    }

    const ItemType eItemType = (IsValidItemType(sItemType)) ? StringToItemType(sItemType) : +ItemType::None;
    switch(eItemType)
    {
        case ItemType::WeaponPierce:
        case ItemType::ArmorShieldPierce:
            return IndexedString("WeaponBasePierce");
        case ItemType::WeaponBlunt:
        case ItemType::ArmorShieldBlunt:
            return IndexedString("WeaponBaseBlunt");
        case ItemType::WeaponSlash:
        case ItemType::ArmorShieldSlash:
            return IndexedString("WeaponBaseSlash");
        default:
            return IndexedString("None");
    }
}

IndexedStringList ConvertItemTypeToCharacterEquipTypes(const IndexedString& sItemType)
{
    IndexedStringList vEquipTypes;
    if(!sItemType.IsValid())
    {
        return vEquipTypes;
    }

    const ItemType eItemType = (IsValidItemType(sItemType)) ? StringToItemType(sItemType) : +ItemType::None;
    switch(eItemType)
    {
        case ItemType::WeaponPierce:
        case ItemType::WeaponBlunt:
        case ItemType::WeaponSlash:
        case ItemType::WeaponMage:
        case ItemType::ArmorShieldPierce:
        case ItemType::ArmorShieldBlunt:
        case ItemType::ArmorShieldSlash:
            vEquipTypes.push_back(IndexedString("Weapon1Left"));
            vEquipTypes.push_back(IndexedString("Weapon1Right"));
            vEquipTypes.push_back(IndexedString("Weapon2Left"));
            vEquipTypes.push_back(IndexedString("Weapon2Right"));
            break;
        case ItemType::ArmorChest:
            vEquipTypes.push_back(IndexedString("Chest"));
            break;
        case ItemType::ArmorFeet:
            vEquipTypes.push_back(IndexedString("Feet"));
            break;
        case ItemType::ArmorFinger:
            vEquipTypes.push_back(IndexedString("LeftFingers"));
            vEquipTypes.push_back(IndexedString("RightFingers"));
            break;
        case ItemType::ArmorHands:
            vEquipTypes.push_back(IndexedString("Hands"));
            break;
        case ItemType::ArmorHead:
            vEquipTypes.push_back(IndexedString("Head"));
            break;
        case ItemType::ArmorLegs:
            vEquipTypes.push_back(IndexedString("Legs"));
            break;
        case ItemType::ArmorNeck:
            vEquipTypes.push_back(IndexedString("Neck"));
            break;
        default:
            break;
    }
    return vEquipTypes;
}

IndexedString ConvertSkillWeaponBaseTypeToCharacterActionType(const IndexedString& sSkillWeaponBaseType)
{
    if(!sSkillWeaponBaseType.IsValid())
    {
        return IndexedString("None");
    }

    const SkillWeaponBaseType eSkillWeaponBaseType = (IsValidSkillWeaponBaseType(sSkillWeaponBaseType)) ? StringToSkillWeaponBaseType(sSkillWeaponBaseType) : +SkillWeaponBaseType::None;
    switch(eSkillWeaponBaseType)
    {
        case SkillWeaponBaseType::Slash:
            return IndexedString("WeaponBaseSlash");
        case SkillWeaponBaseType::Blunt:
            return IndexedString("WeaponBaseBlunt");
        case SkillWeaponBaseType::Pierce:
            return IndexedString("WeaponBasePierce");
        default:
            return IndexedString("None");
    }
}

IndexedString ConvertSkillWeaponTypeToCharacterActionType(const IndexedString& sSkillWeaponType)
{
    if(!sSkillWeaponType.IsValid())
    {
        return IndexedString("None");
    }

    const SkillWeaponType eSkillWeaponType = (IsValidSkillWeaponType(sSkillWeaponType)) ? StringToSkillWeaponType(sSkillWeaponType) : +SkillWeaponType::None;
    switch(eSkillWeaponType)
    {
        case SkillWeaponType::Slash:
            return IndexedString("WeaponSlash");
        case SkillWeaponType::Sever:
            return IndexedString("WeaponSever");
        case SkillWeaponType::Slice:
            return IndexedString("WeaponSlice");
        case SkillWeaponType::Slit:
            return IndexedString("WeaponSlit");
        case SkillWeaponType::Cleave:
            return IndexedString("WeaponCleave");
        case SkillWeaponType::Decapitate:
            return IndexedString("WeaponDecapitate");
        case SkillWeaponType::Parry:
            return IndexedString("WeaponParry");
        case SkillWeaponType::Riposte:
            return IndexedString("WeaponRiposte");
        case SkillWeaponType::Bash:
            return IndexedString("WeaponBash");
        case SkillWeaponType::Smash:
            return IndexedString("WeaponSmash");
        case SkillWeaponType::Impact:
            return IndexedString("WeaponImpact");
        case SkillWeaponType::Crush:
            return IndexedString("WeaponCrush");
        case SkillWeaponType::Break:
            return IndexedString("WeaponBreak");
        case SkillWeaponType::Crack:
            return IndexedString("WeaponCrack");
        case SkillWeaponType::Block:
            return IndexedString("WeaponBlock");
        case SkillWeaponType::Rush:
            return IndexedString("WeaponRush");
        case SkillWeaponType::Pierce:
            return IndexedString("WeaponPierce");
        case SkillWeaponType::Drill:
            return IndexedString("WeaponDrill");
        case SkillWeaponType::Shoot:
            return IndexedString("WeaponShoot");
        case SkillWeaponType::Impale:
            return IndexedString("WeaponImpale");
        case SkillWeaponType::StealthStrike:
            return IndexedString("WeaponStealthStrike");
        case SkillWeaponType::CriticalShot:
            return IndexedString("WeaponCriticalShot");
        case SkillWeaponType::Dodge:
            return IndexedString("WeaponDodge");
        case SkillWeaponType::Counter:
            return IndexedString("WeaponCounter");
        default:
            return IndexedString("None");
    }
}

MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterTreeIndexType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterSegmentType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterProgressStatType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterBattleStatType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterStatusType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterBaseRaceType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterTransformedRaceType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterPowerSetType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterWeaponSetType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterGenderType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterHairType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterEyeType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterHandednessType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterHandType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterEquipmentType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterTargetType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterPartyType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterActionType);
MAKE_ENUM_GETSTRINGLIST_IMPL(CharacterActionRunType);

MAKE_ENUM_CONVERTERS_IMPL(CharacterTreeIndexType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterSegmentType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterProgressStatType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterBattleStatType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterStatusType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterBaseRaceType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterTransformedRaceType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterPowerSetType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterWeaponSetType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterGenderType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterHairType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterEyeType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterHandednessType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterHandType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterEquipmentType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterTargetType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterPartyType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterActionType);
MAKE_ENUM_CONVERTERS_IMPL(CharacterActionRunType);

};
