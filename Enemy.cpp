
#include "Enemy.hpp"

Enemy::Enemy() {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 10);

    // Now generate random stats
    hitPoints =20;
    attackBonus = distrib(gen);
    damageBonus = distrib(gen);
    armorClass = distrib(gen);
    target = nullptr;
    dead = false;
}

Enemy::Enemy(int hitPoints, int attackBonus, int damageBonus, int armorClass) : hitPoints(hitPoints), attackBonus(attackBonus), damageBonus(damageBonus), armorClass(armorClass), target(nullptr) {
    this->dead = false;

}

Enemy::Enemy(int hitPoints, int attackBonus, int damageBonus, int armorClass, Character* player) : hitPoints(hitPoints), attackBonus(attackBonus), damageBonus(damageBonus), armorClass(armorClass), target(player) {
    this->dead = false;
}

void Enemy::attackPlayer() {
    if (this->dead != true) {
        uintptr_t address = reinterpret_cast<uintptr_t>(this);
        std::srand(static_cast<unsigned>(time(nullptr)) + static_cast<unsigned>(address));
        int diceRoll = rand() % 20 + 1;
        if (target != nullptr) {
            target->gotDamaged(this->attackBonus, this->damageBonus, diceRoll); // Trigger player's damage inflicted function
        }
    }

}

void Enemy::gotDamaged(int playerAttack, int playerDamage, int diceRoll) {
    // player rolls 20, guaranteed hit
    if (diceRoll == 20) {
        std::cout << "Player rolled 20 for confirmed Damage to Enemy HP!" << std::endl;
        setHitPoints(this->hitPoints - playerDamage);
    }
    // rolls 1, guaranteed miss
    else if (diceRoll == 1) {
        std::cout << "Player couldn't attack Enemy, but Enemy is attacking" << std::endl;
        // player notifies attack is missed
    }
    // 2-19 rolls, check if attakBonus his higher then armor class
    else if (playerAttack > armorClass) {
        setHitPoints(this->hitPoints - playerDamage);
        std::cout << "Player Have Broken Enemy's Armor with Hit of worth " + std::to_string(playerAttack) << std::endl;
    }
    else {
        std::cout << "Player damage blocked by Enemy's armor class(" + std::to_string(this->armorClass) + ")" << std::endl;
    }
    // if enemy is dead, unsign in as target for the player
    if (this->hitPoints < 1) {
        this->dead = true;
        // if player killed enemy, player levels up
        std::cout << "Player's last hit has defeated the Enemy" << std::endl;
    }

}

int Enemy::getHitPoints() const {
    return hitPoints;
}


void Enemy::setHitPoints(int damage) const {
    this->hitPoints = damage;
}


void Enemy::setTarget(Character* target) {
    this->target = target;
}

bool Enemy::getDead() {
    return this->dead;
}