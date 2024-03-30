// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterProgressData.h"
#include "Character/CharacterTypes.h"
#include "Skills/SkillTree.h"

namespace Gecko
{

CharacterProgressData::CharacterProgressData()
{
    // Init stat names
    InitAllStatNames();

    // Clear data
    Clear();
}

CharacterProgressData::CharacterProgressData(const Json& jsonData)
{
    from_json(jsonData, *this);
}

void CharacterProgressData::Clear()
{
    // -- Meters --
    SetHealthPointsCurrent(0);
    SetMagicPointsCurrent(0);
    SetEnergyPointsCurrent(0);
    SetHealthPointsMax(0);
    SetMagicPointsMax(0);
    SetEnergyPointsMax(0);
    SetHealthRegen(0);
    SetMagicRegen(0);
    SetEnergyRegen(0);
    SetHealthCostDelta(0);
    SetMagicCostDelta(0);
    SetEnergyCostDelta(0);
    SetSpeed(0);

    // -- Gemstones --
    SetAmberValueDelta(0);
    SetRubyValueDelta(0);
    SetDiamondValueDelta(0);
    SetCitrineValueDelta(0);
    SetOnyxValueDelta(0);
    SetQuartzValueDelta(0);
    SetSapphireValueDelta(0);
    SetAmethystValueDelta(0);
    SetEmeraldValueDelta(0);
    SetGarnetValueDelta(0);
    SetIvoryValueDelta(0);
    SetOpalValueDelta(0);

    // -- Attack and Defense Scoring --
    SetBluntAttack(0);
    SetBluntDefense(0);
    SetMagicAttack(0);
    SetMagicDefense(0);
    SetPierceAttack(0);
    SetPierceDefense(0);
    SetSlashAttack(0);
    SetSlashDefense(0);
    SetEnergyAttack(0);
    SetEnergyDefense(0);

    // -- Action Points --
    SetSlashPoints(0);
    SetSeverPoints(0);
    SetSlicePoints(0);
    SetSlitPoints(0);
    SetCleavePoints(0);
    SetDecapitatePoints(0);
    SetParryPoints(0);
    SetRipostePoints(0);
    SetBashPoints(0);
    SetSmashPoints(0);
    SetImpactPoints(0);
    SetCrushPoints(0);
    SetBreakPoints(0);
    SetCrackPoints(0);
    SetBlockPoints(0);
    SetRushPoints(0);
    SetPiercePoints(0);
    SetDrillPoints(0);
    SetShootPoints(0);
    SetImpalePoints(0);
    SetStealthStrikePoints(0);
    SetCriticalShotPoints(0);
    SetDodgePoints(0);
    SetCounterPoints(0);
}

void CharacterProgressData::ApplyTakenDamage(Int iDamage)
{
    Int iNewHealthPoints = STDClip<Int>(GetHealthPointsCurrent() - iDamage, 0, GetHealthPointsMax());
    SetHealthPointsCurrent(iNewHealthPoints);
}

void CharacterProgressData::ApplyRegeneration(Bool bCanRegenHP, Bool bCanRegenMP, Bool bCanRegenEP)
{
    // Get new values
    Int iNewHP = STDClip<Int>(GetHealthPointsCurrent() + GetHealthRegen(), 0, GetHealthPointsMax());
    Int iNewMP = STDClip<Int>(GetMagicPointsCurrent() + GetMagicRegen(), -GetMagicPointsMax(), GetMagicPointsMax());
    Int iNewEP = STDClip<Int>(GetEnergyPointsCurrent() + GetEnergyRegen(), -GetEnergyPointsMax(), GetEnergyPointsMax());

    // Apply new values
    if(bCanRegenHP) { SetHealthPointsCurrent(iNewHP); }
    if(bCanRegenMP) { SetMagicPointsCurrent(iNewMP); }
    if(bCanRegenEP) { SetEnergyPointsCurrent(iNewEP); }
}

void CharacterProgressData::ApplyActionCost(const CharacterActionSharedPtr& pAction)
{
    // Check action first
    if(!pAction)
    {
        return;
    }

    // Get total costs
    const Int iTotalHPCost = pAction->GetCostHP() + GetHealthCostDelta();
    const Int iTotalMPCost = pAction->GetCostMP() + GetMagicCostDelta();
    const Int iTotalEPCost = pAction->GetCostHP() + GetEnergyCostDelta();
    const Int iTotalAPCost = pAction->GetCostAP();

    // Apply HP/MP/EP costs
    if(iTotalHPCost > 0) { SetHealthPointsCurrent(GetHealthPointsCurrent() - iTotalHPCost); }
    if(iTotalMPCost > 0) { SetMagicPointsCurrent(GetMagicPointsCurrent() - iTotalMPCost); }
    if(iTotalEPCost > 0) { SetEnergyPointsCurrent(GetEnergyPointsCurrent() - iTotalEPCost); }

    // Apply AP cost
    if(iTotalAPCost > 0)
    {
        // Typedefs for member functions
        typedef UByte (CharacterProgressData::*APCostGetter)() const;
        typedef void (CharacterProgressData::*APCostSetter)(UByte);

        // AP functions
        APCostGetter fnGetPointsAP = nullptr;
        APCostSetter fnSetPointsAP = nullptr;

        // Get weapon AP cost funcs
        if(DoesSkillDataWeaponExist(pAction->GetSkillTreeIndex()))
        {
            const SkillDataWeapon& skillDataWeapon = RetrieveSkillDataWeapon(pAction->GetSkillTreeIndex());
            const SkillWeaponType eSkillWeaponType = StringToSkillWeaponType(skillDataWeapon.GetSkillType());
            switch(eSkillWeaponType)
            {
                case SkillWeaponType::Slash:
                    fnGetPointsAP = &CharacterProgressData::GetSeverPoints;
                    fnSetPointsAP = &CharacterProgressData::SetSeverPoints;
                    break;
                case SkillWeaponType::Sever:
                    fnGetPointsAP = &CharacterProgressData::GetSeverPoints;
                    fnSetPointsAP = &CharacterProgressData::SetSeverPoints;
                    break;
                case SkillWeaponType::Slice:
                    fnGetPointsAP = &CharacterProgressData::GetSlicePoints;
                    fnSetPointsAP = &CharacterProgressData::SetSlicePoints;
                    break;
                case SkillWeaponType::Slit:
                    fnGetPointsAP = &CharacterProgressData::GetSlitPoints;
                    fnSetPointsAP = &CharacterProgressData::SetSlitPoints;
                    break;
                case SkillWeaponType::Cleave:
                    fnGetPointsAP = &CharacterProgressData::GetCleavePoints;
                    fnSetPointsAP = &CharacterProgressData::SetCleavePoints;
                    break;
                case SkillWeaponType::Decapitate:
                    fnGetPointsAP = &CharacterProgressData::GetDecapitatePoints;
                    fnSetPointsAP = &CharacterProgressData::SetDecapitatePoints;
                    break;
                case SkillWeaponType::Parry:
                    fnGetPointsAP = &CharacterProgressData::GetParryPoints;
                    fnSetPointsAP = &CharacterProgressData::SetParryPoints;
                    break;
                case SkillWeaponType::Riposte:
                    fnGetPointsAP = &CharacterProgressData::GetRipostePoints;
                    fnSetPointsAP = &CharacterProgressData::SetRipostePoints;
                    break;
                case SkillWeaponType::Bash:
                    fnGetPointsAP = &CharacterProgressData::GetBashPoints;
                    fnSetPointsAP = &CharacterProgressData::SetBashPoints;
                    break;
                case SkillWeaponType::Smash:
                    fnGetPointsAP = &CharacterProgressData::GetSmashPoints;
                    fnSetPointsAP = &CharacterProgressData::SetSmashPoints;
                    break;
                case SkillWeaponType::Impact:
                    fnGetPointsAP = &CharacterProgressData::GetImpactPoints;
                    fnSetPointsAP = &CharacterProgressData::SetImpactPoints;
                    break;
                case SkillWeaponType::Crush:
                    fnGetPointsAP = &CharacterProgressData::GetCrushPoints;
                    fnSetPointsAP = &CharacterProgressData::SetCrushPoints;
                    break;
                case SkillWeaponType::Break:
                    fnGetPointsAP = &CharacterProgressData::GetBreakPoints;
                    fnSetPointsAP = &CharacterProgressData::SetBreakPoints;
                    break;
                case SkillWeaponType::Crack:
                    fnGetPointsAP = &CharacterProgressData::GetCrackPoints;
                    fnSetPointsAP = &CharacterProgressData::SetCrackPoints;
                    break;
                case SkillWeaponType::Block:
                    fnGetPointsAP = &CharacterProgressData::GetBlockPoints;
                    fnSetPointsAP = &CharacterProgressData::SetBlockPoints;
                    break;
                case SkillWeaponType::Rush:
                    fnGetPointsAP = &CharacterProgressData::GetRushPoints;
                    fnSetPointsAP = &CharacterProgressData::SetRushPoints;
                    break;
                case SkillWeaponType::Pierce:
                    fnGetPointsAP = &CharacterProgressData::GetPiercePoints;
                    fnSetPointsAP = &CharacterProgressData::SetPiercePoints;
                    break;
                case SkillWeaponType::Drill:
                    fnGetPointsAP = &CharacterProgressData::GetDrillPoints;
                    fnSetPointsAP = &CharacterProgressData::SetDrillPoints;
                    break;
                case SkillWeaponType::Shoot:
                    fnGetPointsAP = &CharacterProgressData::GetShootPoints;
                    fnSetPointsAP = &CharacterProgressData::SetShootPoints;
                    break;
                case SkillWeaponType::Impale:
                    fnGetPointsAP = &CharacterProgressData::GetImpalePoints;
                    fnSetPointsAP = &CharacterProgressData::SetImpalePoints;
                    break;
                case SkillWeaponType::StealthStrike:
                    fnGetPointsAP = &CharacterProgressData::GetStealthStrikePoints;
                    fnSetPointsAP = &CharacterProgressData::SetStealthStrikePoints;
                    break;
                case SkillWeaponType::CriticalShot:
                    fnGetPointsAP = &CharacterProgressData::GetCriticalShotPoints;
                    fnSetPointsAP = &CharacterProgressData::SetCriticalShotPoints;
                    break;
                case SkillWeaponType::Dodge:
                    fnGetPointsAP = &CharacterProgressData::GetDodgePoints;
                    fnSetPointsAP = &CharacterProgressData::SetDodgePoints;
                    break;
                case SkillWeaponType::Counter:
                    fnGetPointsAP = &CharacterProgressData::GetCounterPoints;
                    fnSetPointsAP = &CharacterProgressData::SetCounterPoints;
                    break;
                default:
                    break;
            }
        }

        // Set new AP value
        if(fnGetPointsAP && fnSetPointsAP)
        {
            Int iNewAPValue = CALL_SELF_MEMBER_FN_PTR(fnGetPointsAP)() - iTotalAPCost;
            if(iNewAPValue >= 0)
            {
                CALL_SELF_MEMBER_FN_PTR(fnSetPointsAP)(iNewAPValue);
            }
        }
    }
}

void CharacterProgressData::UpdateAvailableAP(const TreeIndexList& vIndices)
{
    // Action point count type
    struct ActionPointCountEntry
    {
        UByte uCount;
        TreeIndex skillIndex;
    };

    // Populate a table of the highest amount of action points
    STDUnorderedMap<IndexedString, ActionPointCountEntry, IndexedStringHasher> tHighestActionPointCounts;
    for(const TreeIndex& index : vIndices)
    {
        // Skill based action points
        if(DoesSkillDataWeaponExist(index) && !IsBaseWeaponSkill(index))
        {
            // Get skill information
            const SkillDataWeapon& skillDataWeapon = RetrieveSkillDataWeapon(index);
            IndexedString sKey = index.GetTreeBranchType();
            UByte uActionPoints = skillDataWeapon.GetActionPoints();

            // Update or add new information
            if(tHighestActionPointCounts.count(sKey))
            {
                if(uActionPoints > tHighestActionPointCounts[sKey].uCount)
                {
                    tHighestActionPointCounts[sKey].uCount = uActionPoints;
                    tHighestActionPointCounts[sKey].skillIndex = index;
                }
            }
            else
            {
                ActionPointCountEntry entry;
                entry.uCount = uActionPoints;
                entry.skillIndex = index;
                tHighestActionPointCounts[sKey] = entry;
            }
        }
    }

    // Now that we have the highest action point values, record them as AP
    for(auto it = tHighestActionPointCounts.begin(); it != tHighestActionPointCounts.end(); it++)
    {
        UByte uActionPoints = it->second.uCount;
        const TreeIndex& skillIndex = it->second.skillIndex;
        if(!skillIndex.empty())
        {
            // Update AP in each area
            const SkillDataWeapon& skillDataWeapon = RetrieveSkillDataWeapon(skillIndex);
            const SkillWeaponType eSkillWeaponType = StringToSkillWeaponType(skillDataWeapon.GetSkillType());
            switch(eSkillWeaponType)
            {
                case SkillWeaponType::Slash:
                    SetSlashPoints(uActionPoints);
                    break;
                case SkillWeaponType::Sever:
                    SetSeverPoints(uActionPoints);
                    break;
                case SkillWeaponType::Slice:
                    SetSlicePoints(uActionPoints);
                    break;
                case SkillWeaponType::Slit:
                    SetSlitPoints(uActionPoints);
                    break;
                case SkillWeaponType::Cleave:
                    SetCleavePoints(uActionPoints);
                    break;
                case SkillWeaponType::Decapitate:
                    SetDecapitatePoints(uActionPoints);
                    break;
                case SkillWeaponType::Parry:
                    SetParryPoints(uActionPoints);
                    break;
                case SkillWeaponType::Riposte:
                    SetRipostePoints(uActionPoints);
                    break;
                case SkillWeaponType::Bash:
                    SetBashPoints(uActionPoints);
                    break;
                case SkillWeaponType::Smash:
                    SetSmashPoints(uActionPoints);
                    break;
                case SkillWeaponType::Impact:
                    SetImpactPoints(uActionPoints);
                    break;
                case SkillWeaponType::Crush:
                    SetCrushPoints(uActionPoints);
                    break;
                case SkillWeaponType::Break:
                    SetBreakPoints(uActionPoints);
                    break;
                case SkillWeaponType::Crack:
                    SetCrackPoints(uActionPoints);
                    break;
                case SkillWeaponType::Block:
                    SetBlockPoints(uActionPoints);
                    break;
                case SkillWeaponType::Rush:
                    SetRushPoints(uActionPoints);
                    break;
                case SkillWeaponType::Pierce:
                    SetPiercePoints(uActionPoints);
                    break;
                case SkillWeaponType::Drill:
                    SetDrillPoints(uActionPoints);
                    break;
                case SkillWeaponType::Shoot:
                    SetShootPoints(uActionPoints);
                    break;
                case SkillWeaponType::Impale:
                    SetImpalePoints(uActionPoints);
                    break;
                case SkillWeaponType::StealthStrike:
                    SetStealthStrikePoints(uActionPoints);
                    break;
                case SkillWeaponType::CriticalShot:
                    SetCriticalShotPoints(uActionPoints);
                    break;
                case SkillWeaponType::Dodge:
                    SetDodgePoints(uActionPoints);
                    break;
                case SkillWeaponType::Counter:
                    SetCounterPoints(uActionPoints);
                    break;
                default:
                    break;
            }
        }
    }
}

Bool CharacterProgressData::CharacterProgressData::GetIntStatValue(const IndexedString& sStat, Int& iValue) const
{
    const CharacterProgressStatType eProgressType = (IsValidCharacterProgressStatType(sStat)) ? StringToCharacterProgressStatType(sStat) : +CharacterProgressStatType::None;
    switch(eProgressType)
    {
        case CharacterProgressStatType::HealthPointsCurrent:
            iValue = GetHealthPointsCurrent();
            return true;
        case CharacterProgressStatType::MagicPointsCurrent:
            iValue = GetMagicPointsCurrent();
            return true;
        case CharacterProgressStatType::EnergyPointsCurrent:
            iValue = GetEnergyPointsCurrent();
            return true;
        case CharacterProgressStatType::HealthPointsMax:
            iValue = GetHealthPointsMax();
            return true;
        case CharacterProgressStatType::MagicPointsMax:
            iValue = GetMagicPointsMax();
            return true;
        case CharacterProgressStatType::EnergyPointsMax:
            iValue = GetEnergyPointsMax();
            return true;
        case CharacterProgressStatType::HealthRegen:
            iValue = GetHealthRegen();
            return true;
        case CharacterProgressStatType::MagicRegen:
            iValue = GetMagicRegen();
            return true;
        case CharacterProgressStatType::EnergyRegen:
            iValue = GetEnergyRegen();
            return true;
        case CharacterProgressStatType::HealthCostDelta:
            iValue = GetHealthCostDelta();
            return true;
        case CharacterProgressStatType::MagicCostDelta:
            iValue = GetMagicCostDelta();
            return true;
        case CharacterProgressStatType::EnergyCostDelta:
            iValue = GetEnergyCostDelta();
            return true;
        case CharacterProgressStatType::Speed:
            iValue = GetSpeed();
            return true;
        case CharacterProgressStatType::AmberValueDelta:
            iValue = GetAmberValueDelta();
            return true;
        case CharacterProgressStatType::RubyValueDelta:
            iValue = GetRubyValueDelta();
            return true;
        case CharacterProgressStatType::DiamondValueDelta:
            iValue = GetDiamondValueDelta();
            return true;
        case CharacterProgressStatType::CitrineValueDelta:
            iValue = GetCitrineValueDelta();
            return true;
        case CharacterProgressStatType::OnyxValueDelta:
            iValue = GetOnyxValueDelta();
            return true;
        case CharacterProgressStatType::QuartzValueDelta:
            iValue = GetQuartzValueDelta();
            return true;
        case CharacterProgressStatType::SapphireValueDelta:
            iValue = GetSapphireValueDelta();
            return true;
        case CharacterProgressStatType::AmethystValueDelta:
            iValue = GetAmethystValueDelta();
            return true;
        case CharacterProgressStatType::EmeraldValueDelta:
            iValue = GetEmeraldValueDelta();
            return true;
        case CharacterProgressStatType::GarnetValueDelta:
            iValue = GetGarnetValueDelta();
            return true;
        case CharacterProgressStatType::IvoryValueDelta:
            iValue = GetIvoryValueDelta();
            return true;
        case CharacterProgressStatType::OpalValueDelta:
            iValue = GetOpalValueDelta();
            return true;
        case CharacterProgressStatType::BluntAttack:
            iValue = GetBluntAttack();
            return true;
        case CharacterProgressStatType::BluntDefense:
            iValue = GetBluntDefense();
            return true;
        case CharacterProgressStatType::PierceAttack:
            iValue = GetPierceAttack();
            return true;
        case CharacterProgressStatType::PierceDefense:
            iValue = GetPierceDefense();
            return true;
        case CharacterProgressStatType::SlashAttack:
            iValue = GetSlashAttack();
            return true;
        case CharacterProgressStatType::SlashDefense:
            iValue = GetSlashDefense();
            return true;
        case CharacterProgressStatType::MagicAttack:
            iValue = GetMagicAttack();
            return true;
        case CharacterProgressStatType::MagicDefense:
            iValue = GetMagicDefense();
            return true;
        case CharacterProgressStatType::EnergyAttack:
            iValue = GetEnergyAttack();
            return true;
        case CharacterProgressStatType::EnergyDefense:
            iValue = GetEnergyDefense();
            return true;
        case CharacterProgressStatType::SlashPoints:
            iValue = GetSlashPoints();
            return true;
        case CharacterProgressStatType::SeverPoints:
            iValue = GetSeverPoints();
            return true;
        case CharacterProgressStatType::SlicePoints:
            iValue = GetSlicePoints();
            return true;
        case CharacterProgressStatType::SlitPoints:
            iValue = GetSlitPoints();
            return true;
        case CharacterProgressStatType::CleavePoints:
            iValue = GetCleavePoints();
            return true;
        case CharacterProgressStatType::DecapitatePoints:
            iValue = GetDecapitatePoints();
            return true;
        case CharacterProgressStatType::ParryPoints:
            iValue = GetParryPoints();
            return true;
        case CharacterProgressStatType::RipostePoints:
            iValue = GetRipostePoints();
            return true;
        case CharacterProgressStatType::BashPoints:
            iValue = GetBashPoints();
            return true;
        case CharacterProgressStatType::SmashPoints:
            iValue = GetSmashPoints();
            return true;
        case CharacterProgressStatType::ImpactPoints:
            iValue = GetImpactPoints();
            return true;
        case CharacterProgressStatType::CrushPoints:
            iValue = GetCrushPoints();
            return true;
        case CharacterProgressStatType::BreakPoints:
            iValue = GetBreakPoints();
            return true;
        case CharacterProgressStatType::CrackPoints:
            iValue = GetCrackPoints();
            return true;
        case CharacterProgressStatType::BlockPoints:
            iValue = GetBlockPoints();
            return true;
        case CharacterProgressStatType::RushPoints:
            iValue = GetRushPoints();
            return true;
        case CharacterProgressStatType::PiercePoints:
            iValue = GetPiercePoints();
            return true;
        case CharacterProgressStatType::DrillPoints:
            iValue = GetDrillPoints();
            return true;
        case CharacterProgressStatType::ShootPoints:
            iValue = GetShootPoints();
            return true;
        case CharacterProgressStatType::ImpalePoints:
            iValue = GetImpalePoints();
            return true;
        case CharacterProgressStatType::StealthStrikePoints:
            iValue = GetStealthStrikePoints();
            return true;
        case CharacterProgressStatType::CriticalShotPoints:
            iValue = GetCriticalShotPoints();
            return true;
        case CharacterProgressStatType::DodgePoints:
            iValue = GetDodgePoints();
            return true;
        case CharacterProgressStatType::CounterPoints:
            iValue = GetCounterPoints();
            return true;
        default:
            break;
    }
    return false;
}

Bool CharacterProgressData::SetIntStatValue(const IndexedString& sStat, const Int& iValue)
{
    const CharacterProgressStatType eProgressType = (IsValidCharacterProgressStatType(sStat)) ? StringToCharacterProgressStatType(sStat) : +CharacterProgressStatType::None;
    switch(eProgressType)
    {
        case CharacterProgressStatType::HealthPointsCurrent:
            SetHealthPointsCurrent(iValue);
            return true;
        case CharacterProgressStatType::MagicPointsCurrent:
            SetMagicPointsCurrent(iValue);
            return true;
        case CharacterProgressStatType::EnergyPointsCurrent:
            SetEnergyPointsCurrent(iValue);
            return true;
        case CharacterProgressStatType::HealthPointsMax:
            SetHealthPointsMax(iValue);
            return true;
        case CharacterProgressStatType::MagicPointsMax:
            SetMagicPointsMax(iValue);
            return true;
        case CharacterProgressStatType::EnergyPointsMax:
            SetEnergyPointsMax(iValue);
            return true;
        case CharacterProgressStatType::HealthRegen:
            SetHealthRegen(iValue);
            return true;
        case CharacterProgressStatType::MagicRegen:
            SetMagicRegen(iValue);
            return true;
        case CharacterProgressStatType::EnergyRegen:
            SetEnergyRegen(iValue);
            return true;
        case CharacterProgressStatType::HealthCostDelta:
            SetHealthCostDelta(iValue);
            return true;
        case CharacterProgressStatType::MagicCostDelta:
            SetMagicCostDelta(iValue);
            return true;
        case CharacterProgressStatType::EnergyCostDelta:
            SetEnergyCostDelta(iValue);
            return true;
        case CharacterProgressStatType::Speed:
            SetSpeed(iValue);
            return true;
        case CharacterProgressStatType::AmberValueDelta:
            SetAmberValueDelta(iValue);
            return true;
        case CharacterProgressStatType::RubyValueDelta:
            SetRubyValueDelta(iValue);
            return true;
        case CharacterProgressStatType::DiamondValueDelta:
            SetDiamondValueDelta(iValue);
            return true;
        case CharacterProgressStatType::CitrineValueDelta:
            SetCitrineValueDelta(iValue);
            return true;
        case CharacterProgressStatType::OnyxValueDelta:
            SetOnyxValueDelta(iValue);
            return true;
        case CharacterProgressStatType::QuartzValueDelta:
            SetQuartzValueDelta(iValue);
            return true;
        case CharacterProgressStatType::SapphireValueDelta:
            SetSapphireValueDelta(iValue);
            return true;
        case CharacterProgressStatType::AmethystValueDelta:
            SetAmethystValueDelta(iValue);
            return true;
        case CharacterProgressStatType::EmeraldValueDelta:
            SetEmeraldValueDelta(iValue);
            return true;
        case CharacterProgressStatType::GarnetValueDelta:
            SetGarnetValueDelta(iValue);
            return true;
        case CharacterProgressStatType::IvoryValueDelta:
            SetIvoryValueDelta(iValue);
            return true;
        case CharacterProgressStatType::OpalValueDelta:
            SetOpalValueDelta(iValue);
            return true;
        case CharacterProgressStatType::BluntAttack:
            SetBluntAttack(iValue);
            return true;
        case CharacterProgressStatType::BluntDefense:
            SetBluntDefense(iValue);
            return true;
        case CharacterProgressStatType::PierceAttack:
            SetPierceAttack(iValue);
            return true;
        case CharacterProgressStatType::PierceDefense:
            SetPierceDefense(iValue);
            return true;
        case CharacterProgressStatType::SlashAttack:
            SetSlashAttack(iValue);
            return true;
        case CharacterProgressStatType::SlashDefense:
            SetSlashDefense(iValue);
            return true;
        case CharacterProgressStatType::MagicAttack:
            SetMagicAttack(iValue);
            return true;
        case CharacterProgressStatType::MagicDefense:
            SetMagicDefense(iValue);
            return true;
        case CharacterProgressStatType::EnergyAttack:
            SetEnergyAttack(iValue);
            return true;
        case CharacterProgressStatType::EnergyDefense:
            SetEnergyDefense(iValue);
            return true;
        case CharacterProgressStatType::SlashPoints:
            SetSlashPoints(iValue);
            return true;
        case CharacterProgressStatType::SeverPoints:
            SetSeverPoints(iValue);
            return true;
        case CharacterProgressStatType::SlicePoints:
            SetSlicePoints(iValue);
            return true;
        case CharacterProgressStatType::SlitPoints:
            SetSlitPoints(iValue);
            return true;
        case CharacterProgressStatType::CleavePoints:
            SetCleavePoints(iValue);
            return true;
        case CharacterProgressStatType::DecapitatePoints:
            SetDecapitatePoints(iValue);
            return true;
        case CharacterProgressStatType::ParryPoints:
            SetParryPoints(iValue);
            return true;
        case CharacterProgressStatType::RipostePoints:
            SetRipostePoints(iValue);
            return true;
        case CharacterProgressStatType::BashPoints:
            SetBashPoints(iValue);
            return true;
        case CharacterProgressStatType::SmashPoints:
            SetSmashPoints(iValue);
            return true;
        case CharacterProgressStatType::ImpactPoints:
            SetImpactPoints(iValue);
            return true;
        case CharacterProgressStatType::CrushPoints:
            SetCrushPoints(iValue);
            return true;
        case CharacterProgressStatType::BreakPoints:
            SetBreakPoints(iValue);
            return true;
        case CharacterProgressStatType::CrackPoints:
            SetCrackPoints(iValue);
            return true;
        case CharacterProgressStatType::BlockPoints:
            SetBlockPoints(iValue);
            return true;
        case CharacterProgressStatType::RushPoints:
            SetRushPoints(iValue);
            return true;
        case CharacterProgressStatType::PiercePoints:
            SetPiercePoints(iValue);
            return true;
        case CharacterProgressStatType::DrillPoints:
            SetDrillPoints(iValue);
            return true;
        case CharacterProgressStatType::ShootPoints:
            SetShootPoints(iValue);
            return true;
        case CharacterProgressStatType::ImpalePoints:
            SetImpalePoints(iValue);
            return true;
        case CharacterProgressStatType::StealthStrikePoints:
            SetStealthStrikePoints(iValue);
            return true;
        case CharacterProgressStatType::CriticalShotPoints:
            SetCriticalShotPoints(iValue);
            return true;
        case CharacterProgressStatType::DodgePoints:
            SetDodgePoints(iValue);
            return true;
        case CharacterProgressStatType::CounterPoints:
            SetCounterPoints(iValue);
            return true;
        default:
            break;
    }
    return false;
}

static STDUnorderedSet<String> s_tUByteStatNames = {};
static STDUnorderedSet<String> s_tUShortStatNames = {};
static STDUnorderedSet<String> s_tShortStatNames = {};
STDUnorderedSet<String>& CharacterProgressData::GetUByteStatNames() { return s_tUByteStatNames; }
STDUnorderedSet<String>& CharacterProgressData::GetUShortStatNames() { return s_tUShortStatNames; }
STDUnorderedSet<String>& CharacterProgressData::GetShortStatNames() { return s_tShortStatNames; }

static Bool s_bCharacterProgressData_StatNamesInitialized = false;
void CharacterProgressData::InitAllStatNames()
{
    // Check initialization
    if(s_bCharacterProgressData_StatNamesInitialized)
    {
        return;
    }

    // -- Meters --
    InitHealthPointsCurrent();
    InitMagicPointsCurrent();
    InitEnergyPointsCurrent();
    InitHealthPointsMax();
    InitMagicPointsMax();
    InitEnergyPointsMax();
    InitHealthRegen();
    InitMagicRegen();
    InitEnergyRegen();
    InitHealthCostDelta();
    InitMagicCostDelta();
    InitEnergyCostDelta();
    InitSpeed();

    // -- Gemstones --
    InitAmberValueDelta();
    InitRubyValueDelta();
    InitDiamondValueDelta();
    InitCitrineValueDelta();
    InitOnyxValueDelta();
    InitQuartzValueDelta();
    InitSapphireValueDelta();
    InitAmethystValueDelta();
    InitEmeraldValueDelta();
    InitGarnetValueDelta();
    InitIvoryValueDelta();
    InitOpalValueDelta();

    // -- Attack and Defense Scoring --
    InitBluntAttack();
    InitBluntDefense();
    InitMagicAttack();
    InitMagicDefense();
    InitPierceAttack();
    InitPierceDefense();
    InitSlashAttack();
    InitSlashDefense();
    InitEnergyAttack();
    InitEnergyDefense();

    // -- Action Points --
    InitSlashPoints();
    InitSeverPoints();
    InitSlicePoints();
    InitSlitPoints();
    InitCleavePoints();
    InitDecapitatePoints();
    InitParryPoints();
    InitRipostePoints();
    InitBashPoints();
    InitSmashPoints();
    InitImpactPoints();
    InitCrushPoints();
    InitBreakPoints();
    InitCrackPoints();
    InitBlockPoints();
    InitRushPoints();
    InitPiercePoints();
    InitDrillPoints();
    InitShootPoints();
    InitImpalePoints();
    InitStealthStrikePoints();
    InitCriticalShotPoints();
    InitDodgePoints();
    InitCounterPoints();

    // Finished
    s_bCharacterProgressData_StatNamesInitialized = true;
}

Bool CharacterProgressData::operator==(const CharacterProgressData& other) const
{
    return (Json(*this) == Json(other));
}

Bool CharacterProgressData::operator!=(const CharacterProgressData& other) const
{
    return not operator==(other);
}

void to_json(Json& jsonData, const CharacterProgressData& obj)
{
    // -- Meters --
    SET_JSON_DATA_IF_NOT_DEFAULT(HealthPointsCurrent, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(MagicPointsCurrent, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(EnergyPointsCurrent, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(HealthPointsMax, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(MagicPointsMax, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(EnergyPointsMax, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(HealthRegen, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(MagicRegen, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(EnergyRegen, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(HealthCostDelta, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(MagicCostDelta, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(EnergyCostDelta, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(Speed, 0);

    // -- Gemstones --
    SET_JSON_DATA_IF_NOT_DEFAULT(AmberValueDelta, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(RubyValueDelta, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(DiamondValueDelta, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(CitrineValueDelta, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(OnyxValueDelta, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(QuartzValueDelta, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(SapphireValueDelta, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(AmethystValueDelta, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(EmeraldValueDelta, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(GarnetValueDelta, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(IvoryValueDelta, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(OpalValueDelta, 0);

    // -- Attack and Defense Scoring --
    SET_JSON_DATA_IF_NOT_DEFAULT(BluntAttack, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(BluntDefense, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(MagicAttack, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(MagicDefense, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(PierceAttack, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(PierceDefense, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(SlashAttack, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(SlashDefense, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(EnergyAttack, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(EnergyDefense, 0);

    // -- Action Points --
    SET_JSON_DATA_IF_NOT_DEFAULT(SlashPoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(SeverPoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(SlicePoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(SlitPoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(CleavePoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(DecapitatePoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(ParryPoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(RipostePoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(BashPoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(SmashPoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(ImpactPoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(CrushPoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(BreakPoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(CrackPoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(BlockPoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(RushPoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(PiercePoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(DrillPoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(ShootPoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(ImpalePoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(StealthStrikePoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(CriticalShotPoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(DodgePoints, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(CounterPoints, 0);
}

void from_json(const Json& jsonData, CharacterProgressData& obj)
{
    // -- Meters --
    obj.SetHealthPointsCurrent(GET_JSON_DATA_OR_DEFAULT(HealthPointsCurrent, Int, 0));
    obj.SetMagicPointsCurrent(GET_JSON_DATA_OR_DEFAULT(MagicPointsCurrent, Int, 0));
    obj.SetEnergyPointsCurrent(GET_JSON_DATA_OR_DEFAULT(EnergyPointsCurrent, Int, 0));
    obj.SetHealthPointsMax(GET_JSON_DATA_OR_DEFAULT(HealthPointsMax, Int, 0));
    obj.SetMagicPointsMax(GET_JSON_DATA_OR_DEFAULT(MagicPointsMax, Int, 0));
    obj.SetEnergyPointsMax(GET_JSON_DATA_OR_DEFAULT(EnergyPointsMax, Int, 0));
    obj.SetHealthRegen(GET_JSON_DATA_OR_DEFAULT(HealthRegen, Int, 0));
    obj.SetMagicRegen(GET_JSON_DATA_OR_DEFAULT(MagicRegen, Int, 0));
    obj.SetEnergyRegen(GET_JSON_DATA_OR_DEFAULT(EnergyRegen, Int, 0));
    obj.SetHealthCostDelta(GET_JSON_DATA_OR_DEFAULT(HealthCostDelta, Int, 0));
    obj.SetMagicCostDelta(GET_JSON_DATA_OR_DEFAULT(MagicCostDelta, Int, 0));
    obj.SetEnergyCostDelta(GET_JSON_DATA_OR_DEFAULT(EnergyCostDelta, Int, 0));
    obj.SetSpeed(GET_JSON_DATA_OR_DEFAULT(Speed, Int, 0));

    // -- Gemstones --
    obj.SetAmberValueDelta(GET_JSON_DATA_OR_DEFAULT(AmberValueDelta, Int, 0));
    obj.SetRubyValueDelta(GET_JSON_DATA_OR_DEFAULT(RubyValueDelta, Int, 0));
    obj.SetDiamondValueDelta(GET_JSON_DATA_OR_DEFAULT(DiamondValueDelta, Int, 0));
    obj.SetCitrineValueDelta(GET_JSON_DATA_OR_DEFAULT(CitrineValueDelta, Int, 0));
    obj.SetOnyxValueDelta(GET_JSON_DATA_OR_DEFAULT(OnyxValueDelta, Int, 0));
    obj.SetQuartzValueDelta(GET_JSON_DATA_OR_DEFAULT(QuartzValueDelta, Int, 0));
    obj.SetSapphireValueDelta(GET_JSON_DATA_OR_DEFAULT(SapphireValueDelta, Int, 0));
    obj.SetAmethystValueDelta(GET_JSON_DATA_OR_DEFAULT(AmethystValueDelta, Int, 0));
    obj.SetEmeraldValueDelta(GET_JSON_DATA_OR_DEFAULT(EmeraldValueDelta, Int, 0));
    obj.SetGarnetValueDelta(GET_JSON_DATA_OR_DEFAULT(GarnetValueDelta, Int, 0));
    obj.SetIvoryValueDelta(GET_JSON_DATA_OR_DEFAULT(IvoryValueDelta, Int, 0));
    obj.SetOpalValueDelta(GET_JSON_DATA_OR_DEFAULT(OpalValueDelta, Int, 0));

    // -- Attack and Defense Scoring --
    obj.SetBluntAttack(GET_JSON_DATA_OR_DEFAULT(BluntAttack, Int, 0));
    obj.SetBluntDefense(GET_JSON_DATA_OR_DEFAULT(BluntDefense, Int, 0));
    obj.SetMagicAttack(GET_JSON_DATA_OR_DEFAULT(MagicAttack, Int, 0));
    obj.SetMagicDefense(GET_JSON_DATA_OR_DEFAULT(MagicDefense, Int, 0));
    obj.SetPierceAttack(GET_JSON_DATA_OR_DEFAULT(PierceAttack, Int, 0));
    obj.SetPierceDefense(GET_JSON_DATA_OR_DEFAULT(PierceDefense, Int, 0));
    obj.SetSlashAttack(GET_JSON_DATA_OR_DEFAULT(SlashAttack, Int, 0));
    obj.SetSlashDefense(GET_JSON_DATA_OR_DEFAULT(SlashDefense, Int, 0));
    obj.SetEnergyAttack(GET_JSON_DATA_OR_DEFAULT(EnergyAttack, Int, 0));
    obj.SetEnergyDefense(GET_JSON_DATA_OR_DEFAULT(EnergyDefense, Int, 0));

    // -- Action Points --
    obj.SetSlashPoints(GET_JSON_DATA_OR_DEFAULT(SlashPoints, Int, 0));
    obj.SetSeverPoints(GET_JSON_DATA_OR_DEFAULT(SeverPoints, Int, 0));
    obj.SetSlicePoints(GET_JSON_DATA_OR_DEFAULT(SlicePoints, Int, 0));
    obj.SetSlitPoints(GET_JSON_DATA_OR_DEFAULT(SlitPoints, Int, 0));
    obj.SetCleavePoints(GET_JSON_DATA_OR_DEFAULT(CleavePoints, Int, 0));
    obj.SetDecapitatePoints(GET_JSON_DATA_OR_DEFAULT(DecapitatePoints, Int, 0));
    obj.SetParryPoints(GET_JSON_DATA_OR_DEFAULT(ParryPoints, Int, 0));
    obj.SetRipostePoints(GET_JSON_DATA_OR_DEFAULT(RipostePoints, Int, 0));
    obj.SetBashPoints(GET_JSON_DATA_OR_DEFAULT(BashPoints, Int, 0));
    obj.SetSmashPoints(GET_JSON_DATA_OR_DEFAULT(SmashPoints, Int, 0));
    obj.SetImpactPoints(GET_JSON_DATA_OR_DEFAULT(ImpactPoints, Int, 0));
    obj.SetCrushPoints(GET_JSON_DATA_OR_DEFAULT(CrushPoints, Int, 0));
    obj.SetBreakPoints(GET_JSON_DATA_OR_DEFAULT(BreakPoints, Int, 0));
    obj.SetCrackPoints(GET_JSON_DATA_OR_DEFAULT(CrackPoints, Int, 0));
    obj.SetBlockPoints(GET_JSON_DATA_OR_DEFAULT(BlockPoints, Int, 0));
    obj.SetRushPoints(GET_JSON_DATA_OR_DEFAULT(RushPoints, Int, 0));
    obj.SetPiercePoints(GET_JSON_DATA_OR_DEFAULT(PiercePoints, Int, 0));
    obj.SetDrillPoints(GET_JSON_DATA_OR_DEFAULT(DrillPoints, Int, 0));
    obj.SetShootPoints(GET_JSON_DATA_OR_DEFAULT(ShootPoints, Int, 0));
    obj.SetImpalePoints(GET_JSON_DATA_OR_DEFAULT(ImpalePoints, Int, 0));
    obj.SetStealthStrikePoints(GET_JSON_DATA_OR_DEFAULT(StealthStrikePoints, Int, 0));
    obj.SetCriticalShotPoints(GET_JSON_DATA_OR_DEFAULT(CriticalShotPoints, Int, 0));
    obj.SetDodgePoints(GET_JSON_DATA_OR_DEFAULT(DodgePoints, Int, 0));
    obj.SetCounterPoints(GET_JSON_DATA_OR_DEFAULT(CounterPoints, Int, 0));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(CharacterProgressData, CharacterProgressData);

};
