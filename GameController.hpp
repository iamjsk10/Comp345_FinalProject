#pragma once
#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include "MapCell.hpp"
#include "Dice.h"
#include "Character.hpp"
#include "GameMap.hpp"
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <memory>
#include "Enemy.hpp"
#include <Qdebug>
#include "campaign.h"
#include <QObject>
class GameController : public QObject {
    Q_OBJECT

private:
    std::shared_ptr<GameMap> gameMap; // Use smart pointer for the game map
    std::shared_ptr<Character> character; // Use smart pointer for the character
    std::shared_ptr<Campaign> campaign; // Use smart pointer for the character
    int maxSteps;
public:
    std::vector<std::shared_ptr<Enemy>> enemies;

    int currentI;
    // Constructor that takes references to the game map and character
    GameController(std::shared_ptr<GameMap> map, std::shared_ptr<Character> character, std::shared_ptr<Campaign> campaign, int maxSteps);
    void addRandomEnemy();

    std::shared_ptr<Character> getCharacter() const;
    // Function to handle character movement
    void moveCharacter();
    // Function to move the character up
    void moveUp();

    // Function to move the character down
    void moveDown();

    // Function to move the character left
    void moveLeft();

    // Function to move the character right
    void moveRight();
    void searchChest();
    bool isAdjacentToChest(int x, int y) const;
    void checkAndAttackEnemy();
    bool isAdjacentToEnemy(int x, int y) const;
    void transportToNextMap();

private:
  
    // Function to move the character to a new position
    void moveCharacterToPosition(int newX, int newY);

    // Functions related to chest and enemy interactions
signals:
    void mapChanged(std::shared_ptr<GameMap> newMap);
    void enemyHealthChanged(int newHealth);
};

#endif // GAMECONTROLLER_HPP
