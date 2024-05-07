
#include "Boots.hpp"

Boots::Boots() : Item() {}
Boots::Boots(string name, Enhancement enhancement) {
    this->name = name;
    this->equipmentType = "Boots";
    // Check if enhancement is compatible
    if ((enhancement.enhancementType == armorClass ||
        enhancement.enhancementType == dexterity)
        && (enhancement.enhancementBonus > 0 && enhancement.enhancementBonus < 6)) {
        this->enhancement = enhancement;
    }
    else { // Using default enhancement (none)
        this->enhancement = Enhancement();
    }
}
Boots::Boots(string name, EnhancementType enhancementType, int enhancementBonus) {
    // Same as above but just changing the checking
    this->name = name;
    this->equipmentType = 2;
    // Check if enhancement is compatible
    if ((enhancementType == armorClass ||
        enhancementType == dexterity)
        && (enhancementBonus > 0 && enhancementBonus < 6)) {
        Enhancement enhancement(enhancementType, enhancementBonus);
        this->enhancement = enhancement;
    }
    else { // Using default enhancement (none)
        this->enhancement = Enhancement();
    }
}
bool Boots::setEnhancement(Enhancement enhancement) {
    int enhancementBonus = enhancement.enhancementBonus;
    EnhancementType enhancementType = enhancement.enhancementType;
    if ((enhancementBonus > 0 && enhancementBonus < 6)
        && (enhancementType == armorClass ||
            enhancementType == dexterity)) {
        this->enhancement = enhancement;
        return true;
    }
    return false;
};
bool Boots::setEnhancementBonus(int enhancementBonus) {
    if (enhancementBonus > 0 && enhancementBonus < 5) {
        this->enhancement.enhancementBonus = enhancementBonus;
        return true;
    }
    return false;
}
bool Boots::setEnhancementType(EnhancementType enhancementType) {
    if (enhancementType == armorClass ||
        enhancementType == dexterity) {
        this->enhancement.enhancementType = enhancementType;
    }
    return true;
}

void Boots::displayItem(){
    std::cout << "name: " << name
                 << " Enhancement Type: " << getEnhancementType()
                 << " Enhancement Bonus: " << getEnhancementBonus() << std::endl;
}
