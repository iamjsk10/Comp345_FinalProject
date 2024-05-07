#include "Shield.hpp"
// Shield constructors
Shield::Shield() : Item() {}
Shield::Shield(string name, Enhancement enhancement) {
    this->name = name;
    this->equipmentType = "Shield";
    // Check if enhancement is compatible
    if ((enhancement.enhancementType == armorClass)
        && (enhancement.enhancementBonus > 0 && enhancement.enhancementBonus < 6)) {
        this->enhancement = enhancement;
    }
    else { // Using default enhancement (none)
        this->enhancement = Enhancement();
    }
}
Shield::Shield(string name, EnhancementType enhancementType, int enhancementBonus) {
    // Same as above but just changing the checking
    this->name = name;
    this->equipmentType = "Shield";
    // Check if enhancement is compatible
    if ((enhancementType == armorClass)
        && (enhancementBonus > 0 && enhancementBonus < 6)) {
        Enhancement enhancement(enhancementType, enhancementBonus);
        this->enhancement = enhancement;
    }
    else { // Using default enhancement (none)
        this->enhancement = Enhancement();
    }
}

bool Shield::setEnhancement(Enhancement enhancement) {
    int enhancementBonus = enhancement.enhancementBonus;
    EnhancementType enhancementType = enhancement.enhancementType;
    if ((enhancementBonus > 0 && enhancementBonus < 6)
        && (enhancementType == armorClass)) {
        this->enhancement = enhancement;
        return true;
    }
    return false;
};
bool Shield::setEnhancementBonus(int enhancementBonus) {
    if (enhancementBonus > 0 && enhancementBonus < 5) {
        this->enhancement.enhancementBonus = enhancementBonus;
        return true;
    }
    return false;
}
bool Shield::setEnhancementType(EnhancementType enhancementType) {
    if (enhancementType == armorClass) {
        this->enhancement.enhancementType = enhancementType;
    }
    return true;
}

void Shield::displayItem(){
    std::cout << "name: " << name
                 << " Enhancement Type: " << getEnhancementType()
                 << " Enhancement Bonus: " << getEnhancementBonus() << std::endl;
}
