#include "Weapon.hpp"
#include <iostream>
#include <string>
#include <vector>
using std::string;

// Weapon constructors
Weapon::Weapon() : Item() {}
Weapon::Weapon(string name, Enhancement enhancement) {
    this->name = name;
    this->equipmentType = "Weapon";
    // Check if enhancement is compatible
    if ((enhancement.enhancementType == attackBonus ||
        enhancement.enhancementType == damageBonus)
        && (enhancement.enhancementBonus > 0 && enhancement.enhancementBonus < 6)) {
        this->enhancement = enhancement;
    }
    else { // Using default enhancement (none)
        this->enhancement = Enhancement();
    }
}
Weapon::Weapon(string name, EnhancementType enhancementType, int enhancementBonus) {
    // Same as above but just changing the checking
    this->name = name;
    this->equipmentType = "Weapon";
    // Check if enhancement is compatibles
    if ((enhancementType == attackBonus ||
        enhancementType == damageBonus)
        && (enhancementBonus > 0 && enhancementBonus < 6)) {
        Enhancement enhancement(enhancementType, enhancementBonus);
        this->enhancement = enhancement;
    }
    else { // Using default enhancement (none)
        this->enhancement = Enhancement();
    }
}
bool Weapon::operator==(Item& item) const {
    if (Weapon* weapon = dynamic_cast<Weapon*>(&item)) {
        if (name == item.getName()
            && enhancement.enhancementBonus == item.getEnhancement().enhancementBonus
            && enhancement.enhancementType == item.getEnhancement().enhancementType) {
            return true;
        }
    }
    return false;
}
bool Weapon::operator!=(Item& other) const {
    return !(*this == other);
};
bool Weapon::setEnhancement(Enhancement enhancement) {
    int enhancementBonus = enhancement.enhancementBonus;
    EnhancementType enhancementType = enhancement.enhancementType;
    if ((enhancementBonus > 0 && enhancementBonus < 6)
        && (enhancementType == attackBonus ||
            enhancementType == damageBonus)) {
        this->enhancement = enhancement;
        return true;
    }
    return false;
};
bool Weapon::setEnhancementBonus(int enhancementBonus) {
    if (enhancementBonus > 0 && enhancementBonus < 5) {
        this->enhancement.enhancementBonus = enhancementBonus;
        return true;
    }
    return false;
}
bool Weapon::setEnhancementType(EnhancementType enhancementType) {
    if (enhancementType == attackBonus ||
        enhancementType == damageBonus) {
        this->enhancement.enhancementType = enhancementType;
    }
    return true;
}

void Weapon::displayItem(){
    std::cout << "name: " << name
                 << " Enhancement Type: " << getEnhancementType()
                 << " Enhancement Bonus: " << getEnhancementBonus() << std::endl;
}
