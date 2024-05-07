#ifndef Enemy_hpp
#define Enemy_hpp
#include<random>
class Character;

class Enemy {
private:
    mutable int hitPoints;
    int attackBonus;
    int damageBonus;
    int armorClass;
    Character* target;
    bool dead;



public:
    Enemy(); // Default constructor
    Enemy(int hitPoints, int attackBonus, int damageBonus, int armorClass); // Parameterized constructor
    Enemy(int hitPoints, int attackBonus, int damageBonus, int armorClass, Character* player); // Parameterized constructor

    // used to lock on target, can make all the enemys already have the character has an target too
    //void setTarget(Character* target); // Function to set the target player

    void attackPlayer(); // Function to attack the player

    void gotDamaged(int playerAttackBonus, int playerDamageBonus, int diceRoll); // Function to inflict damage to the enemy

    int getHitPoints() const; // Getter for hitPoints

    void setHitPoints(int damage) const;
    void setTarget(Character* target);
    bool getDead();

};


#include "Character.hpp"
#endif // ENEMY_H