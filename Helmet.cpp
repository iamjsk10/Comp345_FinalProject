
#include "Helmet.hpp"
// Helmet constructors
Helmet::Helmet() : Item() {} //Default nothing different
Helmet::Helmet(string name, Enhancement enhancement) {
    this->name = name;
    this->equipmentType = "Helmet";
    // Check if enhancement is compatible
    if ((enhancement.enhancementType == intelligence ||
        enhancement.enhancementType == wisdom ||
        enhancement.enhancementType == armorClass)
        && (enhancement.enhancementBonus > 0 && enhancement.enhancementBonus < 6)
        ) {
        this->enhancement = enhancement;
    }
    else { // Using default enhancement (none)
        this->enhancement = Enhancement();
    }
}
Helmet::Helmet(string name, EnhancementType enhancementType, int enhancementBonus) {
    // Same as above but just changing the checking
    this->name = name;
    this->equipmentType = "Helmet";
    // Check if enhancement is compatible
    if ((enhancementType == intelligence ||
        enhancementType == wisdom ||
        enhancementType == armorClass)
        && (enhancementBonus > 0 && enhancementBonus < 6)
        ) {
        Enhancement enhancement(enhancementType, enhancementBonus);
        this->enhancement = enhancement;
    }
    else { // Using default enhancement (none)
        this->enhancement = Enhancement();
    }
}
bool Helmet::setEnhancement(Enhancement enhancement) {
    int enhancementBonus = enhancement.enhancementBonus;
    EnhancementType enhancementType = enhancement.enhancementType;
    if ((enhancementBonus > 0 && enhancementBonus < 6)
        && (enhancementType == intelligence ||
            enhancementType == wisdom ||
            enhancementType == armorClass)) {
        this->enhancement = enhancement;
        return true;
    }
    return false;
};
bool Helmet::setEnhancementBonus(int enhancementBonus) {
    if (enhancementBonus > 0 && enhancementBonus < 5) {
        this->enhancement.enhancementBonus = enhancementBonus;
        return true;
    }
    return false;
}
bool Helmet::setEnhancementType(EnhancementType enhancementType) {
    if (enhancementType == intelligence ||
        enhancementType == wisdom ||
        enhancementType == armorClass) {
        this->enhancement.enhancementType = enhancementType;
    }
    return true;
}

void Helmet::displayItem(){
    std::cout << "name: " << name
                 << " Enhancement Type: " << getEnhancementType()
                 << " Enhancement Bonus: " << getEnhancementBonus() << std::endl;
}
