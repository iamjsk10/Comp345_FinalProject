
#include "Belt.hpp"

// Belt constructors
Belt::Belt() : Item() {}
Belt::Belt(string name, Enhancement enhancement) {
    this->name = name;
    this->equipmentType = "Belt";
    // Check if enhancement is compatible
    if ((enhancement.enhancementType == constitution ||
        enhancement.enhancementType == strength)
        && (enhancement.enhancementBonus > 0 && enhancement.enhancementBonus < 6)) {
        this->enhancement = enhancement;
    }
    else { // Using default enhancement (none)
        this->enhancement = Enhancement();
    }
}
Belt::Belt(string name, EnhancementType enhancementType, int enhancementBonus) {
    // Same as above but just changing the checking
    this->name = name;
    this->equipmentType = "Belt";
    // Check if enhancement is compatible
    if ((enhancementType == constitution ||
        enhancementType == strength)
        && (enhancementBonus > 0 && enhancementBonus < 6)) {
        Enhancement enhancement(enhancementType, enhancementBonus);
        this->enhancement = enhancement;
    }
    else { // Using default enhancement (none)
        this->enhancement = Enhancement();
    }
}
bool Belt::setEnhancement(Enhancement enhancement) {
    int enhancementBonus = enhancement.enhancementBonus;
    EnhancementType enhancementType = enhancement.enhancementType;
    if ((enhancementBonus > 0 && enhancementBonus < 6)
        && (enhancementType == constitution ||
            enhancementType == strength)) {
        this->enhancement = enhancement;
        return true;
    }
    return false;
};
bool Belt::setEnhancementBonus(int enhancementBonus) {
    if (enhancementBonus > 0 && enhancementBonus < 5) {
        this->enhancement.enhancementBonus = enhancementBonus;
        return true;
    }
    return false;
}
bool Belt::setEnhancementType(EnhancementType enhancementType) {
    if (enhancementType == constitution ||
        enhancementType == strength) {
        this->enhancement.enhancementType = enhancementType;
    }
    return true;
}

void Belt::displayItem(){
    std::cout << "name: " << name
                 << " Enhancement Type: " << getEnhancementType()
                 << " Enhancement Bonus: " << getEnhancementBonus() << std::endl;
}
