#include "Character.hpp"
#include <cstdint>
#include <iostream>
#include <QDebug>
using namespace std;


Character::Character(string name, int level){
    this->name = name;
    this->level = level;
    this->attacksPerRound =1;
    // when level is less than 5
    if (attacksPerRound==0) {
        attacksPerRound++;
    }
    this->x = 1;
    this->y = 1;
    this->prevX = 1;
    this->prevY = 1;

    generateAbilityScores();
    calculateBaseHitPoints();
    calculateBaseArmorClass();
    calculateBaseAttackBonus();
    calculateBaseDamageBonus();
    this->baseIntelligence =0;
    this->baseWisdom=0;
    this->baseCharisma=0;
    CharacterView* view = new CharacterView();
    attachObserver(view);
    this->ranAway=false;
    this->constitution = this->baseConstitution;
    this->dexterity = this->baseDexterity;
    this->strength = this->baseStrength;
    this->hitPoints = this->baseHitPoints;
    this->damageBonus = this->baseDamageBonus;
    this->armorClass = this->baseArmorClass;
    this->attackBonus = this->baseAttackBonus;
    this->intelligence = this->baseIntelligence ;
    this->wisdom = this->baseWisdom;
    this->charisma =  this->baseCharisma;

}
 
Character::Character(string name, int level, int strength, int dexterity, int constitution, int hitPoints, int armorClass, int attackBonus, int damageBonus, int attacksPerRound, int x, int y){
    this->name =name;
    this->level = level;
    this->strength = strength;
    this->dexterity = dexterity;
    this->constitution = constitution;
    this->hitPoints = hitPoints;
    this->armorClass = armorClass;
    this->attackBonus = attackBonus;
    this->damageBonus = damageBonus;
    this->attacksPerRound = attacksPerRound;
    this->x = x;
    this->y = y;

}
void Character::attachObserver(CharacterObserver* observer) {
    observers.push_back(observer);
}

void Character::notifyObservers(string desc) const {
    cout<<desc<<endl;
    for (auto observer : observers) {
        observer->update(*this);
    }
}

void Character::equip(Item* newEquipment ){
    string checkType = newEquipment->getEquipmentType();
    if (checkType=="Helmet") {
        setHelmet(static_cast<Helmet*>(newEquipment));
    }
    else if (checkType=="Boots"){
        setBoots(static_cast<Boots*>(newEquipment));
    }
    else if (checkType=="Shield"){
        setShield(static_cast<Shield*>(newEquipment));
    }
    else if (checkType=="Armor"){
        setArmor(static_cast<Armor*>(newEquipment));
    }
    else if (checkType=="Ring"){
        setRing(static_cast<Ring*>(newEquipment));
    }
    else if (checkType=="Belt"){
        setBelt(static_cast<Belt*>(newEquipment));
    }
    else if(checkType=="Weapon"){
        setWeapon(static_cast<Weapon*>(newEquipment));
    }
    else{
        cout<<"messed up somewhere"<<endl;
    }
    
}

void Character::openChest(){
    Enhancement attackBonusEnhancement(EnhancementType::attackBonus, 3); // Example attack bonus enhancement
    Enhancement damageBonusEnhancement(EnhancementType::damageBonus, 2); // Example damage bonus enhancement
    Enhancement defenseBonusEnhancement(EnhancementType::armorClass, 5); // Example defense bonus enhancement
    Enhancement strengthBonusEnhancement(EnhancementType::strength, 2); // Example strength bonus enhancement
    Enhancement agilityBonusEnhancement(EnhancementType::dexterity, 3); // Example agility bonus enhancement
    srand(static_cast<unsigned int>(time(nullptr)));

    // Create a vector to store the items
    std::vector<std::shared_ptr<Item>> items1;

    // Add all the items to the vector
    items1.push_back(std::make_shared<Weapon>("special", attackBonusEnhancement));
    items1.push_back(std::make_shared<Weapon>("special Axe", damageBonusEnhancement));
    items1.push_back(std::make_shared<Shield>("****Steel Shield", defenseBonusEnhancement));
    items1.push_back(std::make_shared<Helmet>("****Iron Helmet", defenseBonusEnhancement));
    items1.push_back(std::make_shared<Armor>("****Chainmail Armor", defenseBonusEnhancement));
    items1.push_back(std::make_shared<Ring>("****Ring of Strength", strengthBonusEnhancement));
    items1.push_back(std::make_shared<Belt>("****Belt of Agility", agilityBonusEnhancement));
    items1.push_back(std::make_shared<Boots>("****Leather Boots", agilityBonusEnhancement));

    // Check if items vector is empty
    if (items1.empty()) {
        return; // or handle the case where items vector is empty
    }

    // Generate a random index
    int randomIndex = rand() % items1.size();

    // Equip the random item
    equip(items1[randomIndex].get());
}

WornItems& Character::getWornItems() {
    return wornItems;
}

const WornItems& Character::getWornItems() const {
    return wornItems;
}
void Character::accountEnhancement(Enhancement* newEquiptment, Item* item) {
    if (newEquiptment->enhancementType == EnhancementType::intelligence) {
        int temp = intelligence;
          intelligence += newEquiptment->enhancementBonus;
        string notification = "Player equipped: " + item->getName() +" which increased intelligence from " + to_string(temp)+ " to " + to_string(intelligence);
        notifyObservers(notification);
      }
  else if (newEquiptment->enhancementType == EnhancementType::wisdom) {
      int temp = wisdom;
        wisdom += newEquiptment->enhancementBonus;
      string notification = "Player equipped: " + item->getName() +" which increased wisdom from " + to_string(temp)+ " to " + to_string(wisdom);
      notifyObservers(notification);
    }
    else if (newEquiptment->enhancementType == EnhancementType::charisma) {
        int temp = charisma;
        charisma += newEquiptment->enhancementBonus;
        string notification = "Player equipped: " + item->getName() +" which increased charisma from " + to_string(temp)+ " to " + to_string(charisma);
        notifyObservers(notification);
    }
    // item points applied on base points, base strength is inherit propery of character
    // strength = base strength + equipment (+ consumables)
    else if (newEquiptment->enhancementType == EnhancementType::armorClass) {
        int temp = armorClass;
       armorClass = baseArmorClass + newEquiptment->enhancementBonus;
        string notification = "Player equipped: " + item->getName() +" which increased Armor Class from " + to_string(temp)+ " to " + to_string(armorClass);
        notifyObservers(notification);
    }
    else if (newEquiptment->enhancementType == EnhancementType::strength) {
        int temp = strength;
       strength =  baseStrength + newEquiptment->enhancementBonus;
        string notification = "Player equipped: " + item->getName() +" which increased Strength from " + to_string(temp)+ " to " + to_string(strength);
        notifyObservers(notification);
        
    }
    else if (newEquiptment->enhancementType == EnhancementType::constitution) {
        int temp = constitution;
      constitution =  baseConstitution + newEquiptment->enhancementBonus;
        string notification = "Player equipped: " + item->getName() +" which increased Constitution from " + to_string(temp)+ " to " + to_string(constitution);
        notifyObservers(notification);
    }
    else if (newEquiptment->enhancementType == EnhancementType::dexterity) {
        int temp = dexterity;
       dexterity = baseDexterity + newEquiptment->enhancementBonus;
        string notification = "Player equipped: " + item->getName() +" which increased Dexterity from " + to_string(temp)+ " to " + to_string(dexterity);
        notifyObservers(notification);
    }
    else if (newEquiptment->enhancementType == EnhancementType::attackBonus) {
        int temp = attackBonus;
       attackBonus = baseAttackBonus + newEquiptment->enhancementBonus;
        string notification = "Player equipped: " + item->getName() +" which increased Attack Bonus from " + to_string(temp)+ " to " + to_string(attackBonus);
        notifyObservers(notification);
    }
    
    else if (newEquiptment->enhancementType == EnhancementType::damageBonus) {
        int temp = damageBonus;
       damageBonus= baseDamageBonus + newEquiptment->enhancementBonus;
        string notification = "Player equipped: " + item->getName() +" which increased Damage Bonus from " + to_string(temp)+ " to " + to_string(damageBonus);
        notifyObservers(notification);
    }

}

Backpack& Character::getBackpack() {
    return backpack;
}

const Backpack& Character::getBackpack() const {
    return backpack;
}
void Character::setBaseConstitution(int value) {
    this->baseConstitution = value;
};
void Character::setBaseDexterity(int value) {
    this->baseDexterity = value;
};
void Character::setBaseStrength(int value) {
    this->baseStrength = value;
};
void Character::setBaseHitPoints(int value) {
    string notification = "Player is damaged, health decreased from " + to_string(this->hitPoints) + " to " + to_string(value);
    notifyObservers(notification);
    this->hitPoints = value;
};
void Character::setBaseDamageBonus(int value) {
    this->baseDamageBonus = value;
};
void Character::setBaseArmorClass(int value) {
    this->baseArmorClass = value;
};
void Character::setBaseAttackBonus(int value) {
    this->baseAttackBonus = value;
};


void Character::setConstitution(int value) {
    this->constitution = value;
};
void Character::setDexterity(int value) {
    this->dexterity = value;
};
void Character::setStrength(int value) {
    this->strength = value;
};
void Character::setHitPoints(int value) {
    this->hitPoints = value;
};
void Character::setDamageBonus(int value) {
    this->damageBonus = value;
};
void Character::setArmorClass(int value) {
    this->armorClass = value;
};
void Character::setAttackBonus(int value) {
    this->attackBonus = value;
};
 
void Character::setIntelligence(int value) {
    this->intelligence = value;
};
void Character::setWisdom(int value) {
    this->wisdom = value;
};
void Character::setCharisma(int value) {
    this->charisma = value;
};
void Character::setHelmet(Helmet* newHelmet) {
    if (myHelmet) {
        wornItems.removeItem(myHelmet);
    }
    myHelmet = newHelmet;
    if (newHelmet) {
        Enhancement newEquipmentEnhancement = newHelmet->getEnhancement();
        accountEnhancement(&newEquipmentEnhancement, newHelmet);
        wornItems.addItem(newHelmet);
        notifyObservers("Equipped new helmet: " + newHelmet->getName());
    }
}

void Character::setArmor(Armor* newArmor) {
    if (myArmor) {
        wornItems.removeItem(myArmor);
    }
    myArmor = newArmor;
    if (newArmor) {
        Enhancement newEquipmentEnhancement = newArmor->getEnhancement();
        accountEnhancement(&newEquipmentEnhancement, newArmor);
        wornItems.addItem(newArmor);
        notifyObservers("Equipped new armor: " + newArmor->getName());
    }
}

void Character::setShield(Shield* newShield) {
    if (myShield) {
        wornItems.removeItem(myShield);
    }
    myShield = newShield;
    if (newShield) {
        Enhancement newEquipmentEnhancement = newShield->getEnhancement();
        accountEnhancement(&newEquipmentEnhancement, newShield);
        wornItems.addItem(newShield);
        notifyObservers("Equipped new shield: " + newShield->getName());
    }
}

void Character::setBoots(Boots* newBoots) {
    if (myBoots) {
        wornItems.removeItem(myBoots);
    }
    myBoots = newBoots;
    if (newBoots) {
        Enhancement newEquipmentEnhancement = newBoots->getEnhancement();
        accountEnhancement(&newEquipmentEnhancement, newBoots);
        wornItems.addItem(newBoots);
        notifyObservers("Equipped new boots: " + newBoots->getName());
    }
}

void Character::setRing(Ring* newRing) {
    if (myRing) {
        wornItems.removeItem(myRing);
    }
    myRing = newRing;
    if (newRing) {
        Enhancement newEquipmentEnhancement = newRing->getEnhancement();
        accountEnhancement(&newEquipmentEnhancement, newRing);
        wornItems.addItem(newRing);
        notifyObservers("Equipped new ring: " + newRing->getName());
    }
}

void Character::setBelt(Belt* newBelt) {
    if (myBelt) {
        wornItems.removeItem(myBelt);
    }
    myBelt = newBelt;
    if (newBelt) {
        Enhancement newEquipmentEnhancement = newBelt->getEnhancement();
        accountEnhancement(&newEquipmentEnhancement, newBelt);
        wornItems.addItem(newBelt);
        notifyObservers("Equipped new belt: " + newBelt->getName());
    }
}

void Character::setWeapon(Weapon* newWeapon) {
    if (myWeapon) {
        wornItems.removeItem(myWeapon);
    }
    myWeapon = newWeapon;
    if (newWeapon) {
        Enhancement newEquipmentEnhancement = newWeapon->getEnhancement();
        accountEnhancement(&newEquipmentEnhancement, newWeapon);
        wornItems.addItem(newWeapon);
        notifyObservers("Equipped new weapon: " + newWeapon->getName());
    }
}
void Character::levelUp(){
    level++;
    accountLevelUp();
    
}

// increases hitpoints for each level up
// increases attacks per round for every 5 level ups
void Character::accountLevelUp(){
    uintptr_t address = reinterpret_cast<uintptr_t>(this);
    std::srand(static_cast<unsigned>(time(nullptr)) + static_cast<unsigned>(address));
    int itemPoints = hitPoints - baseHitPoints;
    baseHitPoints += rand() % 10 + 1 + constitution;
    hitPoints = baseHitPoints + itemPoints;
    attacksPerRound = level/5;
    attackBonus++;
    if (attacksPerRound==0) {
        attacksPerRound++;
    }
    notifyObservers("Player Levelled Up");
}

void Character::setTarget(Enemy* target) {
    this->target = target;
    this->ranAway = false;
}


void Character::attack(Enemy* target) {
    char input;
    this->target = target;
    if (target != nullptr && !target->getDead()) {
        int temp = target->getHitPoints();
        for (int i = 0; i < 1; i++) {
            if (target == nullptr) {
                break;
            }
                uintptr_t address = reinterpret_cast<uintptr_t>(this);
                std::srand(static_cast<unsigned>(time(nullptr)) + static_cast<unsigned>(address));
                int diceRoll = rand() % 20 + 1;
                target->gotDamaged(attackBonus + diceRoll, damageBonus, diceRoll);
                string s;
                if (diceRoll == 1) {
                    s = "You Rolled 1 and therefore failed to land a hit";
                    qDebug() << s;

                }
                else if (diceRoll == 20) {
                    s = "You Rolled 20 for confirmed damage " + to_string(damageBonus) + " to the enemy.\nEnemy's current health: " + to_string(target->getHitPoints());
                    qDebug() << s;

                }
                else {

                    if (target != nullptr) {

                        s = "You have used attack " + to_string(i + 1) + " with total Attack points of " + to_string(attackBonus + diceRoll) + " (dice roll :" + to_string(diceRoll) + ", Attack Bonus: " + to_string(this->attackBonus) + " )\nEnemy's current Health: " + to_string(target->getHitPoints()) + "(damage done in last attack to enemy: " + to_string(temp - target->getHitPoints()) + ")";
                        qDebug() <<s ;
                    }
                    else {

                        s = "You have Defeated the Enemy";
                        qDebug() << s;
                        this->levelUp();
                    }

                }
                notifyObservers(s);
           

        }
        qDebug ()<< "Your Moves for this round are finished!!";

    }

    else {
        //can log this, may not be useful if the attack option pops up only when the target is locked
        cout << "NO ENEMY PRESENT/ALIVE" << endl;
    }

}

void Character::gotDamaged(int enemyAttackBonus, int enemyDamage, int diceRoll) {

    if (diceRoll == 20) {
        string s = "You have been attacked with a natural 20 dice roll attack!\n Health decrease from " + to_string(this->hitPoints) + " to " + to_string(this->hitPoints - enemyDamage);
        setHitPoints(this->hitPoints - enemyDamage);
        notifyObservers(s);
    }
    else if (diceRoll == 1) {
        notifyObservers("Enemy failed to attack by rolling 1 on dice!");
    }
    else {
        if (enemyAttackBonus > armorClass) {
            string s = "You have been attacked!\n Health decrease form " + to_string(this->hitPoints) + " to " + to_string(this->hitPoints - enemyDamage);
            setHitPoints(this->hitPoints - enemyDamage);
            notifyObservers(s);
        }
        else {
            notifyObservers("Enemy tried to attack but your Armor have blocked enemy's attack!");
        }
    }
    if (this->hitPoints < 0) {
        //target->setTarget(nullptr);
        cout << "Player is dead" << endl;
    }
    else {
        this->attack(target);
    }
}


string Character::getName() const {
    return this->name;
};

    int Character::getLevel() const{
    return this-> level;
};

int Character::getBaseHitPoints() const {
    return this->baseHitPoints;
};
int Character::getBaseArmorClass() const {
    return this->baseArmorClass;
};
int Character::getBaseAtackBonus() const {
    return this->baseAttackBonus;
};
int Character::getBaseDamageBonus() const {
    return this->baseDamageBonus;
};
int Character::getBaseConstitution() const {
    return this->baseConstitution;
}
int Character::getBaseDexterity() const {
    return this->baseDexterity;
}
int Character::getBaseStrength() const {
    return this->baseStrength;
};
int Character::getConstitution() const {
    return this->constitution;
};

int Character::getDexterity() const {
    return this->dexterity;
};
int Character::getStrength() const {
    return this->strength;
};
int Character::getHitPoints() const {
    return this->hitPoints;
};
int Character::getDamageBonus() const {
    return this->damageBonus;
};
int Character::getArmorClass() const {
    return this->armorClass;
};
int Character::getAttackBonus() const {
    return this->attackBonus;
};
int Character::getIntelligence() const {
    return this->intelligence;
};
int Character::getWisdom() const {
    return this->wisdom;
};
int Character::getCharisma() const {
    return this->charisma; 
};
int Character::getHealth() const {
    return this->hitPoints;
};
Helmet* Character::getHelmet() const {
    return myHelmet;
}

Boots* Character::getBoots() const {
    return myBoots;
}

Shield* Character::getShield() const {
    return myShield;
}

Armor* Character::getArmor() const {
    return myArmor;
}

Ring* Character::getRing() const {
    return myRing;
}

Belt* Character::getBelt() const {
    return myBelt;
}

Weapon* Character::getWeapon() const {
    return myWeapon;
};
bool Character::getRanAway() {
    return this->ranAway;
}

void Character::generateAbilityScores() {
    uintptr_t address = reinterpret_cast<uintptr_t>(this);
    std::srand(static_cast<unsigned>(time(nullptr)) + static_cast<unsigned>(address));
    this->baseStrength = rand() % 6 + 1 + rand() % 6 + 1 + rand() % 6 + 1; // Roll 3d6 for strength
    this->baseDexterity = rand() % 6 + 1 + rand() % 6 + 1 + rand() % 6 + 1; // Roll 3d6 for dexterity
    this->baseConstitution = rand() % 6 + 1 + rand() % 6 + 1 + rand() % 6 + 1; // Roll 3d6 for constitution
}

void Character::calculateBaseHitPoints() {
    this->baseHitPoints = (10 + (this->baseConstitution - 10) / 2) + (level - 1) * (5 + (this->baseConstitution - 10) / 2);
}

void Character::calculateBaseArmorClass() {
    this->baseArmorClass = 10 + (this->baseDexterity - 10) / 2;
}

void Character::calculateBaseAttackBonus() {
    this->baseAttackBonus = (this->level)/2; // Simplified for demonstration
}

void Character::calculateBaseDamageBonus() {
        this->baseDamageBonus = (this->baseStrength - 2) / 2; // Simplified for demonstration
}

void Character::printCharacterSheet() const {
    cout <<  this->name << endl;
    cout <<  this->level << endl;
    cout << this->strength << endl;
    cout <<  this->dexterity << endl;
    cout <<  this->constitution << endl;
    cout << this->hitPoints << endl;
    cout << this->armorClass << endl;
    cout <<  this->attackBonus << endl;
    cout <<  this->damageBonus << endl;
    cout<< this->attacksPerRound <<endl;
    cout<<   this->x <<endl;
    cout<< this->y <<endl;
 
}

// Implementation of update method in CharacterView class
void CharacterView::update(const Character& character) {
   // std::cout << "Character View(post stat changes):\n";
    //character.printCharacterSheet();
}

// Getter for the Y coordinate.
// Correct implementation of setX, ensuring there's only one definition.
void Character::setX(int newX) {
    if (x != newX) {
        prevX = x; // Save current x to prevX before changing
        x = newX; // Update current x
        // Notify observers if necessary
        notifyObservers("Character moved to new X position: " + std::to_string(newX));
    }
}

void Character::setY(int newY) {
    if (y != newY) {
        prevY = y; // Save current y to prevY before changing
        y = newY; // Update current y
        // Notify observers if necessary
        notifyObservers("Character moved to new Y position: " + std::to_string(newY));
    }
}

int Character::getPreviousX() const {
    return prevX;
}

int Character::getPreviousY() const {
    return prevY;
}int Character::getX() const {

    return x;
}

int Character::getY() const {
    return y;
}


void Character::setPosition(int newX, int newY) {
    prevX = x;
    prevY=y;
    x = newX;
    y = newY;
    notifyObservers("Character moved to new Y position: " + std::to_string(newY));



}
