// gameconstants.h
//
// Teemu Mäkinen <culkah@gmail.com> 2014

#ifndef GAMECONSTANTS_H_
#define GAMECONSTANTS_H_

#include <string>
#include <stdint.h>
#include <bitset>

const std::string baseExpRank[6] = {
    "Recruit",
    "Regular",
    "Veteran",
    "Elite",
    "Ultra-Elite",
    "Champion"
};

const uint8_t baseExpRequirement[4] = {0, 20, 60, 120};

enum ATTRIBUTE_TYPE {
    ATTRIBUTE_ATTACK = 0,
    ATTRIBUTE_TO_HIT = 1,
    ATTRIBUTE_DEFENSE = 2,
    ATTRIBUTE_RESISTANCE = 3,
    ATTRIBUTE_HEALTH = 4
};

const uint8_t expTable[6][5] = {
//    att   tohit     def     res      hp
    {   0,      0,      0,      0,      0},
    {   1,      0,      0,      1,      0},
    {   1,      0,      1,      2,      0},
    {   2,      1,      1,      3,      1},
    {   2,      2,      2,      4,      1},
    {   3,      3,      2,      5,      2}
};

enum ELEMENT {
    ELEMENT_MUNDANE = 0x01,
    ELEMENT_LIFE    = 0x02,
    ELEMENT_DEATH   = 0x04,
    ELEMENT_CHAOS   = 0x08,
    ELEMENT_SORCERY = 0x10,
    ELEMENT_NATURE  = 0x20
};

enum UNITTYPE {
    UNIT_MUNDANE = 0x0,
    UNIT_FANTASTIC = 0x1,
    UNIT_HERO = 0x2
};

enum RANGEDTYPE {
    RANGED_NONE = 0,
    RANGED_MISSILE = 1,
    RANGED_STONE = 2,
    RANGED_MAGIC = 3
};

enum RACE {
	RACE_BARBARIAN,
	RACE_GNOLL,
	RACE_HALFLING,
	RACE_HIGH_ELF,
	RACE_HIGH_MAN,
	RACE_KLACKON,
	RACE_LIZARDMAN,
	RACE_NOMAD,
	RACE_ORC,
	RACE_BEASTMAN,
	RACE_DRACONIAN,
	RACE_DWARF,
	RACE_DARK_ELF,
	RACE_TROLL
};

enum ABILITYFLAG {
    ABILITY_ARMOR_PIERCING      = 0,
    ABILITY_CAUSE_FEAR          = 1,
    ABILITY_COLD_IMMUNE         = 2,
    ABILITY_CONSTRUCTION        = 3,
    ABILITY_CREATE_OUTPOST      = 4,
    ABILITY_CREATE_UNDEAD       = 5,
    ABILITY_DEATH_IMMUNITY      = 6,
    ABILITY_DISPEL_EVIL         = 7,
    ABILITY_DOOM_BOLT_SPELL     = 8,
    ABILITY_FIREBALL_SPELL      = 9,
    ABILITY_FIRE_IMMUNITY       = 10,
    ABILITY_FIRST_STRIKE        = 11,
    ABILITY_FORESTER            = 12,
    ABILITY_HEALER              = 13,
    ABILITY_HEALING_SPELL       = 14,
    ABILITY_ILLUSION            = 15,
    ABILITY_ILLUSION_IMMUNITY   = 16,
    ABILITY_IMMOLATION          = 17,
    ABILITY_INVISIBILITY        = 18,
    ABILITY_LARGE_SHIELD        = 19,
    ABILITY_LONG_RANGE          = 20,
    ABILITY_LUCKY               = 21,
    ABILITY_MAGIC_IMMUNITY      = 22,
    ABILITY_MELD                = 23,
    ABILITY_MERGING             = 24,
    ABILITY_MISSILE_IMMUNITY    = 25,
    ABILITY_MOUNTAINEER         = 26,
    ABILITY_NEGATE_FIRST_STRIKE = 27,
    ABILITY_NONCORPOREAL        = 28,
    ABILITY_PATHFINDING         = 29,
    ABILITY_PLANE_SHIFT         = 30,
    ABILITY_POISON_IMMUNITY     = 31,
    ABILITY_PURIFY              = 32,
    ABILITY_REGENERATION        = 33,
    ABILITY_STONING_IMMUNITY    = 34,
    ABILITY_SUMMON_DEMONS       = 35,
    ABILITY_TELEPORTING         = 36,
    ABILITY_WALL_CRUSHER        = 37,
    ABILITY_WEAPON_IMMUNITY     = 38,
    ABILITY_WEB_SPELL           = 39,
    ABILITY_WIND_WALKING        = 40
};

enum HEROABILITYFLAG {
    HERO_AGILITY            = 0x000001,
    HERO_ARCANE_POWER       = 0x000002,
    HERO_ARMSMASTER         = 0x000004,
    HERO_BLADEMASTER        = 0x000008,
    HERO_CHARMED            = 0x000010,
    HERO_CONSTITUTION       = 0x000020,
    HERO_LEADERSHIP         = 0x000040,
    HERO_LEGENDARY          = 0x000080,
    HERO_LUCKY              = 0x000100,
    HERO_MIGHT              = 0x000200,
    HERO_NOBLE              = 0x000400,
    HERO_PRAYERMASTER       = 0x000800,
    HERO_SAGE               = 0x001000,
    HERO_AGILITY_SUPER      = 0x002000,
    HERO_ARCANE_POWER_SUPER = 0x004000,
    HERO_ARMSMASTER_SUPER   = 0x008000,
    HERO_BLADEMASTER_SUPER  = 0x010000,
    HERO_CONSTITUTION_SUPER = 0x020000,
    HERO_LEADERSHIP_SUPER   = 0x040000,
    HERO_LEGENDARY_SUPER    = 0x080000,
    HERO_MIGHT_SUPER        = 0x100000,
    HERO_PRAYERMASTER_SUPER = 0x200000,
    HERO_SAGE_SUPER         = 0x400000

};

enum ITEMSLOT {
    SLOT_SWORD      = 0x01,
    SLOT_BOW        = 0x02,
    SLOT_STAFF      = 0x04,
    SLOT_ANY_WEAPON = 0x08,
    SLOT_ARMOR      = 0x10,
    SLOT_RING       = 0x20
};

enum MOVEMENTTYPE {
    MOVETYPE_WALK = 0,
    MOVETYPE_SWIM = 1,
    MOVETYPE_FLY  = 2
};

inline MOVEMENTTYPE operator|(MOVEMENTTYPE &mv1, MOVEMENTTYPE &mv2) {
    return static_cast<MOVEMENTTYPE>(static_cast<int>(mv1) | static_cast<int>(mv2));
}

#endif
