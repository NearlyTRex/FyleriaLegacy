// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CONSTANTS_H_
#define _GECKO_CONSTANTS_H_

#include "Utility/TypesSimple.h"

namespace Gecko
{

// Binary file markers
static const FixedUnsigned8List s_ksvBinaryMarkerCBR = {'C', 'B', 'R'};
static const FixedUnsigned8List s_ksvBinaryMarkerMSG = {'M', 'S', 'G'};

// Save limits
static const UByte s_kuMaxSaveSlot = 5;

// Tree limits
static const UInt s_kuMaxSkillRank = 20;

// Character limits
static const UInt s_kuMaxTeamCharacterAmount = 6;

// Character index for team size of 6
static const UInt s_kuCharacterIndex1 = 0;
static const UInt s_kuCharacterIndex2 = 1;
static const UInt s_kuCharacterIndex3 = 2;
static const UInt s_kuCharacterIndex4 = 3;
static const UInt s_kuCharacterIndex5 = 4;
static const UInt s_kuCharacterIndex6 = 5;

// Limits on equipped items
static const UInt s_kuHandSizeLimit = 4;
static const UInt s_kuBodySizeLimit = 1;

// Skill attacks
static const UInt s_kuBaseNumberOfSkillAttacks = 1;

// Skill damage boundary
static const Float s_kfSkillDamageBoundaryPercent = 0.1f;
static const Float s_kfSkillDamageBoundaryDefaultValue = 1.0f;

// Skill rank upgrade amount
static const UInt s_kuSkillRankUpgradeAmount = 10;

};

#endif
