#ifndef Character_hpp
#define Character_hpp

#include <vector>
#include <iostream>

#include "Armor.hpp"
#include "Belt.hpp"
#include "Boots.hpp"
#include "Helmet.hpp"
#include "Ring.hpp"
#include "Shield.hpp"
#include "Weapon.hpp"
#include "Enemy.hpp"
#include "ItemContainer.hpp"
// forward declaration of enemy do circular dependecy isn't created
class Enemy;
class TreasureChest;
// forward declaration so CharacterObserver can use character
class Character;

class CharacterObserver{
    public:
        virtual void update(const Character& character) = 0;
        virtual ~CharacterObserver() {};
};

class Character {
protected:
    std::string name;
    int level;
    int attacksPerRound;
    std::vector<CharacterObserver*> observers;
    int prevX, prevY; // Previous position
    int x = 1, y = 1;
    bool ranAway;
    bool dead;
    // Base stats
    int baseHitPoints; // health
    int baseArmorClass;
    int baseAttackBonus;
    int baseDamageBonus;
    int baseStrength;
    int baseDexterity;
    int baseConstitution;
    int baseIntelligence;
    int baseWisdom;
    int baseCharisma;
    // Current stats
    int constitution;
    int dexterity;
    int strength;
    int hitPoints;
    int damageBonus;
    int armorClass;
    int attackBonus;
    int intelligence;
    int wisdom;
    int charisma;
    // Equipment
    Helmet* myHelmet = nullptr;
    Ring* myRing = nullptr;
    Boots* myBoots = nullptr;
    Belt* myBelt = nullptr;
    Shield* myShield = nullptr;
    Armor* myArmor = nullptr;
    Weapon* myWeapon = nullptr;
    Backpack backpack;
    WornItems wornItems;
    Enemy* target = nullptr;
    TreasureChest* chest = nullptr;

public:
        Character(std::string name, int level);
        Character(string name, int level, int strength, int dexterity, int constitution, int hitPoints, int armorClass, int attackBonus, int damageBonus, int attacksPerRound, int x, int y);
        WornItems& getWornItems();
        const WornItems& getWornItems() const;

        // Functions used to generate the intital values
        void generateAbilityScores();
        void calculateBaseHitPoints();
        void calculateBaseArmorClass();
        void calculateBaseAttackBonus();
        void calculateBaseDamageBonus();
        Backpack& getBackpack();
        const Backpack& getBackpack() const;
        int getX() const;
        int getY() const;
        void setX(int newX);
        void setY(int newY);
        // Methods to get the previous position
        int getPreviousX() const;
        int getPreviousY() const;

    
        //void recalculateStats() ;
    
        // Display the stats
      virtual void printCharacterSheet() const ;
      void setPosition(int newX, int newY);
        // Observer functions
        void attachObserver(CharacterObserver* observer);
        void notifyObservers(std::string desc) const;
    
        // Functions for character level up
        void levelUp();
        void accountLevelUp();
            
        void setTarget(Enemy* target); // Function to set the target player
    
        // Function for attacking
        void attack(Enemy* target);
    
        // Function for decreasing health when enemy damages player
        void gotDamaged(int enemyAttackBonus, int enemyDamageBonus, int diceRoll);

        //opens a nearby chest
        void openChest();


        //function for equipping any wearable
        void equip(Item* item);
    
        // Checks which item(s) character has equipped and changes stats accordingly
        void accountWearables();

       // Checks which stat the item enhances and by what factor
       void accountEnhancement(Enhancement* current, Item* item);
        
        // Setters
        void setBaseConstitution(int value);
        void setBaseDexterity(int value);
        void setBaseStrength(int value);
        void setBaseHitPoints(int value);
        void setBaseDamageBonus(int value);
        void setBaseArmorClass(int value);
        void setBaseAttackBonus(int value);
    
        void setConstitution(int value);
        void setDexterity(int value);
        void setStrength(int value);
        void setHitPoints(int value);
        void setDamageBonus(int value);
        void setArmorClass(int value);
        void setAttackBonus(int value);
     
        void setIntelligence(int value);
        void setWisdom(int value);
        void setCharisma(int value);
        void setHelmet(Helmet* helmet);
        void setRing (Ring* ring);
        void setBoots(Boots* boots);
        void setBelt(Belt* belt);
        void setShield(Shield* shield);
        void setArmor(Armor* armor);
        void setWeapon(Weapon* weapon);
        
        
 
    // Getters
        std::string getName() const;
        int getLevel() const;
        int getHealth() const;
        int getBaseHitPoints() const;
        int getBaseArmorClass() const;
        int getBaseAtackBonus() const;
        int getBaseDamageBonus() const;
        int getBaseConstitution() const;
        int getBaseDexterity() const;
        int getBaseStrength() const;
        int getConstitution() const;
        int getDexterity() const;
        int getStrength() const;
        int getHitPoints() const;
        int getDamageBonus() const;
        int getArmorClass() const;
        int getAttackBonus() const;
        int getIntelligence() const;
        int getWisdom() const;
        int getCharisma() const;
        Helmet* getHelmet() const;
        Boots* getBoots() const;
        Shield* getShield() const;
        Armor* getArmor() const;
        Ring* getRing() const;
        Belt* getBelt() const;
        Weapon* getWeapon() const;
        bool getRanAway();
    
};


// CharacterView class declaration
class CharacterView : public CharacterObserver {
public:
void update(const Character& character);
};

#include "Enemy.hpp"
#endif
