#include "baseunit.h"

BaseUnit::BaseUnit() : unitType_(UNIT_MUNDANE), numInUnit_(1),
                       cost_(10), baseHealth_(1),
                       baseAttack_(1), baseRanged_(0), baseAmmo_(0),
                       baseMana_(0), baseDefense_(1), baseResistance_(1),
                       baseToHit_(0), baseMovement_(1),
                       baseMoveType_(MOVETYPE_WALK),
                       baseUpkeep_(1,1,0), name_("undefined"),
                       description_("no description"),
                       baseAbilities_(ABILITY_NONE),
                       ability_Caster_(0), ability_Death_Gaze_(0),
                       ability_Doom_Gaze_(0), ability_Fire_Breath_(0),
                       ability_Holy_Bonus_(0), ability_Life_Steal_(0),
                       ability_Lightning_Breath_(0),
                       ability_Poison_Touch_(0),
                       ability_Resistance_To_All_(0),
                       ability_Scouting_(0), ability_Stoning_Gaze_(0),
                       ability_Stoning_Touch_(0), ability_Thrown_(0),
                       baseElement_(ELEMENT_MUNDANE), image_(nullptr)
{

}

// why oh why did I make everything constant?
BaseUnit::BaseUnit(UNITTYPE unittype, uint8_t numInUnit,
                   uint16_t cost, uint8_t health,
                   uint8_t attack, uint8_t ranged, uint8_t ammo,
                   uint8_t mana, uint8_t defense, uint8_t resistance,
                   uint8_t tohitbonus, uint8_t movement,
                   MOVEMENTTYPE movementtype, uint8_t goldupkeep,
                   uint8_t foodupkeep, uint8_t manaupkeep,
                   std::string &name, std::string &description,
                   ABILITYFLAG abilities, ELEMENT element,
                   uint8_t firebreath, uint8_t lightningbreath,
                   uint8_t deathgaze, uint8_t doomgaze,
                   uint8_t stoninggaze, uint8_t thrown,
                   uint8_t caster, uint8_t holybonus, uint8_t lifesteal,
                   uint8_t poisontouch, uint8_t resistancetoall,
                   uint8_t scouting, uint8_t stoningtouch,
                   Image* image) : unitType_(unittype),
     numInUnit_(numInUnit), cost_(cost), baseHealth_(health),
     baseAttack_(attack), baseRanged_(ranged), baseAmmo_(ammo),
     baseMana_(mana), baseDefense_(defense),
     baseResistance_(resistance), baseToHit_(tohitbonus),
     baseMovement_(movement), baseMoveType_(movementtype),
     baseUpkeep_(goldupkeep,foodupkeep,manaupkeep), name_(name),
     description_(description), baseAbilities_(abilities),
     ability_Caster_(caster), ability_Death_Gaze_(deathgaze),
     ability_Doom_Gaze_(doomgaze), ability_Fire_Breath_(firebreath),
     ability_Holy_Bonus_(holybonus), ability_Life_Steal_(lifesteal),
     ability_Lightning_Breath_(lightningbreath),
     ability_Poison_Touch_(poisontouch),
     ability_Resistance_To_All_(resistancetoall),
     ability_Scouting_(scouting), ability_Stoning_Gaze_(stoninggaze),
     ability_Stoning_Touch_(stoningtouch), ability_Thrown_(thrown),
     baseElement_(element), image_(image) {

}

BaseUnit::~BaseUnit() {
    
}

UNITTYPE BaseUnit::getUnitType() const {
    return unitType_;
}

uint16_t BaseUnit::getCost() const {
    return cost_;
}

uint8_t BaseUnit::getNum() const {
    return numInUnit_;
}

uint8_t BaseUnit::getHealth() const {
    return baseHealth_;
}

uint8_t BaseUnit::getAttack() const {
    return baseAttack_;
}

uint8_t BaseUnit::getRanged() const {
    return baseRanged_;
}

uint8_t BaseUnit::getAmmo() const {
    return baseAmmo_;
}

uint8_t BaseUnit::getMana() const {
    return baseMana_;
}

uint8_t BaseUnit::getDefense() const {
    return baseDefense_;
}

uint8_t BaseUnit::getResistance() const {
    return baseResistance_;
}

uint8_t BaseUnit::getToHitBonus() const {
    return baseToHit_;
}

uint8_t BaseUnit::getMovement() const {
    return baseMovement_;
}

MOVEMENTTYPE BaseUnit::getMovementType() const {
    return baseMoveType_;
}

Upkeep BaseUnit::getUpkeep() const {
    return baseUpkeep_;
}

const std::string* BaseUnit::getName() {
    return &name_;
}

const std::string* BaseUnit::getDescription() {
    return &description_;
}

ABILITYFLAG BaseUnit::getAbilities() const {
    return baseAbilities_;
}

ELEMENT BaseUnit::getElement() const {
    return baseElement_;
}

bool BaseUnit::getBreath(uint8_t &fire, uint8_t &lightning) const {
    fire = ability_Fire_Breath_;
    lightning = ability_Lightning_Breath_;
    
    return ((fire > 0) | (lightning > 0));
}

bool BaseUnit::getGaze(uint8_t &death, uint8_t &doom, uint8_t &stoning) const {
    death = ability_Death_Gaze_;
    doom = ability_Doom_Gaze_;
    stoning = ability_Stoning_Gaze_;
    
    return (((death > 0) | (doom > 0)) | (stoning > 0));
}

uint8_t BaseUnit::getThrown() const {
    return ability_Thrown_;
}

uint8_t BaseUnit::getCaster() const {
    return ability_Caster_;
}

uint8_t BaseUnit::getHolyBonus() const {
    return ability_Holy_Bonus_;
}

uint8_t BaseUnit::getLifeSteal() const {
    return ability_Life_Steal_;
}

uint8_t BaseUnit::getPoisonTouch() const {
    return ability_Poison_Touch_;
}

uint8_t BaseUnit::getResistanceToAll() const {
    return ability_Resistance_To_All_;
}

uint8_t BaseUnit::getScouting() const {
    return ability_Scouting_;
}

uint8_t BaseUnit::getStoningTouch() const {
    return ability_Stoning_Touch_;
}

Image* BaseUnit::getImage() const {
    return image_;
}
