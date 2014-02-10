// unit.cc
//
// Teemu Mäkinen <culkah@gmail.com> 2014

#include "unit.h"
#include "gameconstants.h"

Unit::Unit(BaseUnit* baseunit) : baseunit_(baseunit), experience_(0)
{
    movement_ = baseunit_->getMovement();
    num_ = baseunit_->getNum();
    health_ = baseunit_->getHealth();
    ammo_ = baseunit_->getAmmo();
    mana_ = baseunit_->getMana();
    name_ = *(baseunit_->getName());
}

Unit::~Unit() {
}

UNITTYPE Unit::getUnitType() const {
    return baseunit_->getUnitType();
}

uint8_t Unit::getNum() const {
    return num_;
}

uint8_t Unit::getHealth() const {
    return health_;
}

uint8_t Unit::getAttack() const {
    uint8_t attack = baseunit_->getAttack();
    
    // Attack modifiers from experience, buffs and whatever here
    
    attack += expTable[getExpLevel()][(int)ATTRIBUTE_ATTACK];
    
    return attack;
}

uint8_t Unit::getRanged() const {
    uint8_t ranged = baseunit_->getRanged();
    
    // Attack modifiers from experience, buffs and whatever here
    
    return ranged;
}

uint8_t Unit::getAmmo() const {
    return ammo_;
}

uint8_t Unit::getMana() const {
    return mana_;
}

uint8_t Unit::getDefense() const {
    uint8_t defense = baseunit_->getDefense();
    
    // Defense modifiers from experience, buffs and whatever here
    defense += expTable[getExpLevel()][(int)ATTRIBUTE_DEFENSE];
    
    return defense;
}

uint8_t Unit::getResistance() const {
    uint8_t resistance = baseunit_->getResistance();
    
    // Resistance modifiers from experience, buffs and whatever here
    resistance += expTable[getExpLevel()][(int)ATTRIBUTE_RESISTANCE];
    
    return resistance;
}

uint8_t Unit::getMovement() const {
    return movement_;
}

uint16_t Unit::getExperience() const {
    return experience_;
}

uint8_t Unit::getExpLevel() const {
    uint8_t level = 0;
    if (crusade_) level++;
    if (warlord_) level++;
    
    if (getExperience() >= baseExpRequirement[3]) level += 3;
    else if (getExperience() >= baseExpRequirement[2]) level += 2;
    else if (getExperience() >= baseExpRequirement[1]) level += 1;
    
    return level;
}

std::bitset<3> Unit::getMovementType() const {
    std::bitset<3> mt = baseunit_->getMovementType();
    
    // Check for buffs
    
    return mt;
}

Upkeep Unit::getUpkeep() const {
    Upkeep upkeep = baseunit_->getUpkeep();
    
    // Add upkeep from ongoing spells or something like that
    
    return upkeep;
}

std::string* Unit::getName() {
    return &name_;
}

const std::string* Unit::getDescription() {
    return baseunit_->getDescription();
}

std::bitset<41> Unit::getAbilities() const {
    std::bitset<41> ability = baseunit_->getAbilities();
    
    // Check buffs and others and add them to the flag;
    
    return ability;
}

ELEMENT Unit::getElement() const {
    ELEMENT e = baseunit_->getElement();
    
    // check modifiers
    
    return e;
}

bool Unit::getBreath(uint8_t &fire, uint8_t &lightning) const {
    // TODO: modifiers
    
    return baseunit_->getBreath(fire, lightning);
}

bool Unit::getGaze(uint8_t &death, uint8_t &doom, uint8_t &stoning) const {
    // TODO: modifiers
    
    return baseunit_->getGaze(death, doom, stoning);
}

uint8_t Unit::getThrown() const {
    // TODO: modifiers
    return baseunit_->getThrown();
}

uint8_t Unit::getCaster() const {
    // TODO: modifiers
    return baseunit_->getCaster();
}

uint8_t Unit::getHolyBonus() const {
    // TODO: modifiers
    return baseunit_->getHolyBonus();
}

uint8_t Unit::getLifeSteal() const {
    // TODO: modifiers
    return baseunit_->getLifeSteal();
}

uint8_t Unit::getPoisonTouch() const {
    // TODO: modifiers
    return baseunit_->getPoisonTouch();
}

uint8_t Unit::getResistanceToAll() const {
    // TODO: modifiers
    return baseunit_->getResistanceToAll();
}

uint8_t Unit::getScouting() const {
    // TODO: modifiers
    return baseunit_->getScouting();
}

uint8_t Unit::getStoningTouch() const {
    // TODO: modifiers
    return baseunit_->getStoningTouch();
}

Image* Unit::getImage() const {
    return baseunit_->getImage();
}
