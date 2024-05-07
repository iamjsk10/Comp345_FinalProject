#include "GameMap.hpp"


void GameMap::setName(std::string name) {
    this->name = name;
};

std::string GameMap::getName() const {
    return this->name;
};
GameMap::GameMap() : width(0), height(0), grid(0, std::vector<MapCell>(0)), startX(0), startY(0), endX(0), endY(0) {}

GameMap::GameMap(int w, int h) : width(w), height(h), grid(h, std::vector<MapCell>(w)), startX(0), startY(0), endX(0), endY(0) {}




void GameMap::setStartX(int x) {
    startX = x;
};
void GameMap::setStartY(int y) {
    startY = y;
};
void GameMap::setEndX(int x) {
    endX = x;
};
void GameMap::setEndY(int y) {
    endY = y;
};
int GameMap::getStartX() const {
    return startX;
};
int GameMap::getStartY() const {
    return startY;
};;
int GameMap::getEndX() const {
    return endX;
};;
int GameMap::getEndY() const {
    return endY;
};;

void GameMap::setGrid(std::vector<std::vector<MapCell>> grid) {
    this->grid = grid;
};
std::vector<std::vector<MapCell>> GameMap::getGrid() const {
    return this->grid;
}
void GameMap::addObserver(std::function<void(const GameMap&)> observer) {
    observers.push_back(observer);
}

void GameMap::notifyObservers() const {
    for (const auto& observer : observers) {
        observer(*this);
    }
}

void GameMap::setCell(int x, int y, CellType type) {
    if (isInBounds(x, y)) {
        grid[y][x].setType(type);
        notifyObservers(); // Existing functionality to notify character observers
        notifyMapObservers(); // New functionality to notify UI observers 
    }
}

void GameMap::setDoor(int x, int y) {
    if (isInBounds(x, y)) {
        grid[y][x].setType(CellType::Door);
        endX = x;
        endY = y;
        notifyObservers(); // Notify character observers about the change
        notifyMapObservers(); // Notify UI observers about the change
    }
}

int GameMap::getWidth() const {
    return width;
}

int GameMap::getHeight() const {
    return height;
}

CellType GameMap::getCellType(int x, int y) const {
    if (isInBounds(x, y)) {
        return grid[y][x].getType();
    }
    return CellType::Wall; // Default return if out of bounds
}

bool GameMap::isInBounds(int x, int y) const {
    return x >= 0 && y >= 0 && x < width && y < height;
}

bool GameMap::verifyMap(int startX, int startY, int endX, int endY) {
    if (!isInBounds(startX, startY) || !isInBounds(endX, endY) ||
        getCellType(startX, startY) != CellType::Empty || getCellType(endX, endY) != CellType::Empty) {
        return false; // Start or end is out of bounds or not empty.
    }

    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::queue<std::pair<int, int>> q;

    auto enqueueIfValid = [&](int x, int y) {
        if (isInBounds(x, y) && getCellType(x, y) == CellType::Empty && !visited[y][x]) {
            q.push({ x, y });
            visited[y][x] = true;
        }
        };

    q.push({ startX, startY });
    visited[startY][startX] = true;

    while (!q.empty()) {
        std::pair<int, int> front = q.front();
        q.pop();

        if (front.first == endX && front.second == endY) {
            return true; // Path found
        }

        // Check and enqueue all adjacent cells
        enqueueIfValid(front.first, front.second - 1); // Up
        enqueueIfValid(front.first + 1, front.second); // Right
        enqueueIfValid(front.first, front.second + 1); // Down
        enqueueIfValid(front.first - 1, front.second); // Left
    }

    return false; // No path found
}

void GameMap::characterMoved(const Character& character) {
    // Logic to update the map based on character's new position
    int x = character.getX();
    int y = character.getY();
    std::cout << "Character moved to: " << x << ", " << y << std::endl;

    // Potentially refresh the map display or perform other actions
}

void GameMap::observeCharacter(Character& character) {
    character.attachObserver(this);
}



void GameMap::update(const Character& character) {
    // Example action: printing the character's new position
    std::cout << "Character has moved. New position is: "
        << character.getX() << ", " << character.getY() << std::endl;
    setCell(character.getPreviousX(), character.getPreviousY(), CellType::Empty);
    setCell(character.getX(), character.getY(), CellType::character);

}

void GameMap::addMapObserver(MapObserver* observer) {
    mapObservers.push_back(observer);
}

void GameMap::removeMapObserver(MapObserver* observer) {
    mapObservers.remove(observer);
}
void GameMap::notifyMapObservers() const {
    for (auto* observer : mapObservers) {
        observer->updateMapDisplay();
    }
}

bool GameMap::verifyMap() const {
    if (!isInBounds(startX, startY) || !isInBounds(endX, endY) ||
        getCellType(startX, startY) != CellType::Empty || getCellType(endX, endY) != CellType::Empty) {
        return false; // Start or end is out of bounds or not empty.
    }

    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::queue<std::pair<int, int>> q;

    auto enqueueIfValid = [&](int x, int y) {
        if (isInBounds(x, y) && getCellType(x, y) == CellType::Empty && !visited[y][x]) {
            q.push({ x, y });
            visited[y][x] = true;
        }
        };

    q.push({ startX, startY });
    visited[startY][startX] = true;

    while (!q.empty()) {
        std::pair<int, int> front = q.front();
        q.pop();

        if (front.first == endX && front.second == endY) {
            return true; // Path found
        }

        // Check and enqueue all adjacent cells
        enqueueIfValid(front.first, front.second - 1); // Up
        enqueueIfValid(front.first + 1, front.second); // Right
        enqueueIfValid(front.first, front.second + 1); // Down
        enqueueIfValid(front.first - 1, front.second); // Left
    }

    return false; // No path found
};