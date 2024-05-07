#include "Item.hpp"

#include "Armor.hpp"
#include "Belt.hpp"
#include "Boots.hpp"
#include "Helmet.hpp"
#include "Ring.hpp"
#include "Shield.hpp"
#include "Weapon.hpp"



bool isSameClass(Item& item1, Item& item2) {
    
    if (dynamic_cast<Helmet*>(&item1) && dynamic_cast<Helmet*>(&item2)) {
        return true;
    }
    if (dynamic_cast<Armor*>(&item1) && dynamic_cast<Armor*>(&item2)) {
        return true;
    }
    if (dynamic_cast<Shield*>(&item1) && dynamic_cast<Shield*>(&item2)) {
        return true;
    }
    if (dynamic_cast<Ring*>(&item1) && dynamic_cast<Ring*>(&item2)) {
        return true;
    }
    if (dynamic_cast<Belt* > (&item1) && dynamic_cast<Belt*>(&item2)) {
        return true;
    }
    if (dynamic_cast<Boots*>(&item1) && dynamic_cast<Boots*>(&item2)) {
        return true;
    }
    if (dynamic_cast<Weapon*>(&item1) && dynamic_cast<Weapon*>(&item2)) {
        return true;
    }
    return false;
}
// Enhancement constructors
Enhancement::Enhancement():enhancementType(none),enhancementBonus(0){}
Enhancement::Enhancement(EnhancementType enhancementType, int enhancementBonus) :
    enhancementType(enhancementType), enhancementBonus(enhancementBonus) {}

// Item constructors
Item::Item() : name(""), enhancement() {}
Item::Item(string name, Enhancement enhancement) :name(name), enhancement(enhancement) {};
Item::Item(string name, EnhancementType enhancementType, int enhancementBonus) :
    name(name), enhancement(enhancementType, enhancementBonus) {}
string Item::getName()
{
    return name;
}
Enhancement Item::getEnhancement() const {
    return enhancement;
}
int Item::getEnhancementBonus() const {
    return this->enhancement.enhancementBonus;
}
EnhancementType Item::getEnhancementType() const {
    return this->enhancement.enhancementType;
}
bool Item::setEnhancement(Enhancement enhancement) {
    int enhancementBonus = enhancement.enhancementBonus;
    if (enhancementBonus > 0 && enhancementBonus < 6) {
        this->enhancement = enhancement;
        return true;
    }
    return false;
};
bool Item::setEnhancementBonus(int enhancementBonus) {
    if (enhancementBonus > 0 && enhancementBonus < 6) {
        this->enhancement.enhancementBonus = enhancementBonus;
        return true;
    }
    return false;
}
bool Item::setEnhancementType(EnhancementType enhancementType) {
    this->enhancement.enhancementType = enhancementType;
    return true;
}

string Item::getEquipmentType(){
    return this->equipmentType;
}

void Item::displayItem() {
   std::cout<<"parent function called \n";
}
