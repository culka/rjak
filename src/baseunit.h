// baseunit.h
// Base unit holds all the information of an unmodified unit
// every unit gets its stats from here, only one exists per unit type
//
// Teemu Mäkinen <teemu.m.makinen@tut.fi> 2013

#ifndef BASEUNIT_H_
#define BASEUNIT_H_

#include <stdint.h>
#include <string>
#include "gameconstants.h"

struct Image;

struct Upkeep {
    Upkeep(uint8_t gold_, uint8_t food_, uint8_t mana_) : gold(gold_), food(food_), mana(mana_) {};
    uint8_t gold;
    uint8_t food;
    uint8_t mana;
};

class BaseUnit {
 public:
    BaseUnit();
    // Holy hell
    BaseUnit(UNITTYPE unittype, uint8_t numInUnit,
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
             Image* image);
    ~BaseUnit();
    
    // Getters for every needed value
    // Read the game manual if you need to know what they do
    // ...or gameconstants.h
    UNITTYPE getUnitType() const;
    uint16_t getCost() const;
    uint8_t getNum() const;
    uint8_t getHealth() const;
    uint8_t getAttack() const;
    uint8_t getRanged() const;
    uint8_t getAmmo() const;
    uint8_t getMana() const;
    uint8_t getDefense() const;
    uint8_t getResistance() const;
    uint8_t getToHitBonus() const;
    uint8_t getMovement() const;
    MOVEMENTTYPE getMovementType() const;
    Upkeep getUpkeep() const;
    const std::string* getName();
    const std::string* getDescription();
    ABILITYFLAG getAbilities() const;
    ELEMENT getElement() const;
    bool getBreath(uint8_t &fire, uint8_t &lightning) const;
    bool getGaze(uint8_t &death, uint8_t &doom, uint8_t &stoning) const;
    uint8_t getThrown() const;
    uint8_t getCaster() const;
    uint8_t getHolyBonus() const;
    uint8_t getLifeSteal() const;
    uint8_t getPoisonTouch() const;
    uint8_t getResistanceToAll() const;
    uint8_t getScouting() const;
    uint8_t getStoningTouch() const;
    // Image points to the Image-struct, handled by the renderer
    Image* getImage() const;
 private:
    UNITTYPE const unitType_;
    uint8_t const numInUnit_;
    uint16_t const cost_;
    uint8_t const baseHealth_;
    uint8_t const baseAttack_;
    uint8_t const baseRanged_;
    uint8_t const baseAmmo_;
    uint8_t const baseMana_;
    uint8_t const baseDefense_;
    uint8_t const baseResistance_;
    uint8_t const baseToHit_;
    uint8_t const baseMovement_;
    MOVEMENTTYPE const baseMoveType_;
    Upkeep const baseUpkeep_;
    std::string const name_;
    std::string const description_;
    ABILITYFLAG const baseAbilities_;
    uint8_t const ability_Caster_;
    uint8_t const ability_Death_Gaze_;
    uint8_t const ability_Doom_Gaze_;
    uint8_t const ability_Fire_Breath_;
    uint8_t const ability_Holy_Bonus_;
    uint8_t const ability_Life_Steal_;
    uint8_t const ability_Lightning_Breath_;
    uint8_t const ability_Poison_Touch_;
    uint8_t const ability_Resistance_To_All_;
    uint8_t const ability_Scouting_;
    uint8_t const ability_Stoning_Gaze_;
    uint8_t const ability_Stoning_Touch_;
    uint8_t const ability_Thrown_;
    ELEMENT const baseElement_;
    Image* const image_;
};

#endif
