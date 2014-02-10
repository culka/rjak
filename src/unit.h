// unit.h
//
// Teemu Mäkinen <culkah@gmail.com> 2014

#ifndef UNIT_H_
#define UNIT_H_

#include "baseunit.h"

class BaseHeroUnit : public BaseUnit {
public:
    BaseHeroUnit();
    ~BaseHeroUnit();
    
    UNITTYPE getUnitType() const;
    HEROABILITYFLAG getHeroAbilities() const;
    ITEMSLOT getItemSlots() const;
private:
    uint8_t heroCaster_;
    HEROABILITYFLAG heroicAbilities_;
    ITEMSLOT itemSlots_;
}; 

class Unit {
 public:
    Unit(BaseUnit* baseunit);
    ~Unit();
    
    UNITTYPE getUnitType() const;
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
    uint16_t getExperience() const;
    uint8_t getExpLevel() const;
    std::bitset<3> getMovementType() const;
    Upkeep getUpkeep() const;
    std::string* getName();
    const std::string* getDescription();
    std::bitset<41> getAbilities() const;
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
    Image* getImage() const;
 private:
    BaseUnit* baseunit_;
    uint8_t movement_;
    uint8_t num_;
    uint8_t health_;
    uint8_t ammo_;
    uint8_t mana_;
    uint16_t experience_;
    std::string name_;
    bool crusade_;
    bool warlord_;
    
};

#endif
