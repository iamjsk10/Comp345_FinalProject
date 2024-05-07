#include "GameController.hpp"
#include "CampaignEditor.h"

GameController::GameController(std::shared_ptr<GameMap> map, std::shared_ptr<Character> player, std::shared_ptr<Campaign> camp, int maxSteps)
    : gameMap(map), character(player), campaign(camp), maxSteps(maxSteps) {
    addRandomEnemy();
    currentI = 0;
}
void GameController::addRandomEnemy() {
    auto enemy = std::make_shared<Enemy>(); // Enemy with random stats
    enemies.push_back(enemy); // Store the enemy. Assuming 'enemies' is a vector of shared_ptr<Enemy>
    // Further initialization or setup as needed, e.g., positioning on the game map
}

void GameController::moveCharacter() {
    Dice dice;
    int steps = dice.roll("1d6");
    maxSteps = steps;
    std::cout << "You rolled a " << steps << ". You can move " << steps << " steps." << std::endl;
    // Implementation for moving the character in specific directions based on user input
}

void GameController::moveUp() {
    
    int newX = character->getX();
    int newY = character->getY() - 1;
    moveCharacterToPosition(newX, newY);
    --maxSteps;
}

void GameController::moveDown() {
    int newX = character->getX();
    int newY = character->getY() + 1;
    moveCharacterToPosition(newX, newY);
    --maxSteps;
}

void GameController::moveLeft() {
    int newX = character->getX() - 1;
    int newY = character->getY();
    moveCharacterToPosition(newX, newY);
    --maxSteps;
}

void GameController::moveRight() {
    int newX = character->getX() + 1;
    int newY = character->getY();
    moveCharacterToPosition(newX, newY);
    --maxSteps;
}

void GameController::moveCharacterToPosition(int newX, int newY) {
    // Check if the new position is within the bounds of the map
    if (newX < 0 || newY < 0 || newX >= gameMap->getWidth() || newY >= gameMap->getHeight()) {
        std::cout << "Cannot move out of bounds! Try again." << std::endl;
        return;
    }

    // Check if the new position is occupied
    if (gameMap->getCellType(newX, newY) != CellType::Empty && gameMap->getCellType(newX, newY) != CellType::Door) {
        std::cout << "Cannot move to occupied space! Try again." << std::endl;
        return;
    }
     if (gameMap->getCellType(newX, newY) == CellType::Door) {
        character->setPosition(newX, newY);

        gameMap->setCell(newX, newY, CellType::character);
        gameMap->setCell(character->getPreviousX(), character->getPreviousY(), CellType::Empty);
        transportToNextMap();
        return;
    }

    // Check number of Steps left
    if (maxSteps <= 0) {
        std::cout << "You're out of steps!" << std::endl;
        return;
    }
    
    // Move the character to the new position
    character->setPosition(newX, newY);

    // Update the map to reflect the character's new position
    gameMap->setCell(newX, newY, CellType::character);
    gameMap->setCell(character->getPreviousX(), character->getPreviousY(), CellType::Empty);

    // Optionally, you can update the view or print the map here
    // gameMap.printMap();
}


// Additional methods implementation...

// Chest and enemy interaction methods
 void GameController::searchChest() {
    int x = character->getX();
    int y = character->getY();

    if (isAdjacentToChest(x, y)) {
        std::cout << "You found a chest!" << std::endl;
        
    }
    else {
        std::cout << "No chest adjacent to you." << std::endl;
    }
}
bool GameController::isAdjacentToChest(int x, int y) const {
    if (gameMap->getCellType(x, y - 1) == CellType::chest) {
        gameMap->setCell(x,y-1, CellType::Empty);

   }
    if (gameMap->getCellType(x, y + 1) == CellType::chest) {
        gameMap->setCell(x, y + 1, CellType::Empty);

    }if (gameMap->getCellType(x - 1, y) == CellType::chest) {
        gameMap->setCell(x - 1, y, CellType::Empty);

    }if (gameMap->getCellType(x + 1, y) == CellType::chest) {
        gameMap->setCell(x + 1, y, CellType::Empty);

    }





    return gameMap->getCellType(x, y - 1) == CellType::chest || // Up
        gameMap->getCellType(x, y + 1) == CellType::chest || // Down
        gameMap->getCellType(x - 1, y) == CellType::chest || // Left
        gameMap->getCellType(x + 1, y) == CellType::chest;   // Right

}


std::shared_ptr<Character> GameController::getCharacter() const {
    return character;
}
void GameController::checkAndAttackEnemy() {
    // Get character's position
    int x = character->getX();
    int y = character->getY();
    qDebug() << x;
    qDebug() << "No enemy adjacent to you.";
    bool enemyFoundAndAttacked = false;
    for (auto& currentEnemy : enemies) {
        if (currentEnemy && isAdjacentToEnemy(x, y)) {
            qDebug() << "Enemy detected! Initiating attack...";
            character->attack(currentEnemy.get());
            enemyFoundAndAttacked = true;
            int newHealth = currentEnemy.get()->getHitPoints();
     


            break; // Remove this if you want to attack all adjacent enemies
        }
    }

    if (!enemyFoundAndAttacked) {
        qDebug() << "No enemy adjacent to you.";
    }
}

bool GameController::isAdjacentToEnemy(int x, int y) const {
    return gameMap->getCellType(x, y - 1) == CellType::Enemy || // Up
        gameMap->getCellType(x, y + 1) == CellType::Enemy || // Down
        gameMap->getCellType(x - 1, y) == CellType::Enemy || // Left
        gameMap->getCellType(x + 1, y) == CellType::Enemy;   // Right
}
void GameController::transportToNextMap() {
    std::cout << "Attempting to transport to the next map..." << std::endl;
    std::cout << "Current Map Index: " << currentI << std::endl;
    qDebug() << currentI;
    qDebug() << campaign->getMapss().size();

    if (currentI + 2 < campaign->getMapss().size()) {
        campaign->setCurrentMapIndex(currentI + 2);
        std::shared_ptr<GameMap> nextMap = campaign->getMapss().at(currentI + 2);

        std::cout << "Switching to map index " << currentI + 2 << std::endl;

        character->setPosition(nextMap->getStartX(), nextMap->getStartY());
        gameMap = nextMap; // Ensure gameMap points to the new map
        gameMap->setCell(character->getX(), character->getY(), CellType::character);
        currentI = currentI + 2;

        qDebug() << "working";
        emit mapChanged(nextMap);
    }
    else {
        std::cout << "You've reached the end of the campaign!" << std::endl;
    }
}