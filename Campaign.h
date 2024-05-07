#pragma once
#include "GameMap.hpp"
#include <iostream>
#include <string>
using namespace::std;

class Campaign {
public:
    Campaign();
    Campaign(string name);
    void setName(string name);
    string getName()const;
    vector<GameMap> getMaps() const;

    void addMap(GameMap map);// Copy of a map is enough i think
    void removeMap(string mapName);

    void swapMapOrder(int map1, int map2);
    void displayAllMaps();

    int getCurrentMapIndex() const;
    void setCurrentMapIndex(int index);
    std::vector<std::shared_ptr<GameMap>> getMapss() const;
    bool isValid();

protected:
    string name;
    vector<GameMap> maps;
    int currentMapIndex; // Track the index of the current map
};