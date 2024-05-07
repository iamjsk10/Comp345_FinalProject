
#include "Ring.hpp"

Ring::Ring() : Item() {}
Ring::Ring(string name, Enhancement enhancement) {
    this->name = name;
    this->equipmentType = "Ring";
    // Check if enhancement is compatible
    if ((enhancement.enhancementType == armorClass ||
        enhancement.enhancementType == strength ||
        enhancement.enhancementType == constitution ||
        enhancement.enhancementType == wisdom ||
        enhancement.enhancementType == charisma)
        && (enhancement.enhancementBonus > 0 && enhancement.enhancementBonus < 6)) {
        this->enhancement = enhancement;
    }
    else { // Using default enhancement (none)
        this->enhancement = Enhancement();
    }
}
Ring::Ring(string name, EnhancementType enhancementType, int enhancementBonus) {
    // Same as above but just changing the checking
    this->name = name;
    this->equipmentType = "Ring";
    // Check if enhancement is compatible
    if ((enhancementType == armorClass ||
        enhancementType == strength ||
        enhancementType == constitution ||
        enhancementType == wisdom ||
        enhancementType == charisma)
        && (enhancementBonus > 0 && enhancementBonus < 6)) {
        Enhancement enhancement(enhancementType, enhancementBonus);
        this->enhancement = enhancement;
    }
    else { // Using default enhancement (none)
        this->enhancement = Enhancement();
    }
}
bool Ring::setEnhancement(Enhancement enhancement) {
    int enhancementBonus = enhancement.enhancementBonus;
    EnhancementType enhancementType = enhancement.enhancementType;
    if ((enhancementBonus > 0 && enhancementBonus < 6)
        && (enhancementType == armorClass ||
            enhancementType == strength ||
            enhancementType == constitution ||
            enhancementType == wisdom ||
            enhancementType == charisma)) {
        this->enhancement = enhancement;
        return true;
    }
    return false;
};
bool Ring::setEnhancementBonus(int enhancementBonus) {
    if (enhancementBonus > 0 && enhancementBonus < 5) {
        this->enhancement.enhancementBonus = enhancementBonus;
        return true;
    }
    return false;
}
bool Ring::setEnhancementType(EnhancementType enhancementType) {
    if (enhancementType == armorClass ||
        enhancementType == strength ||
        enhancementType == constitution ||
        enhancementType == wisdom ||
        enhancementType == charisma) {
        this->enhancement.enhancementType = enhancementType;
    }
    return true;
}

void Ring::displayItem(){
    std::cout << "name: " << name
                 << " Enhancement Type: " << getEnhancementType()
                 << " Enhancement Bonus: " << getEnhancementBonus() << std::endl;
}
