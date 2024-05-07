#include "Campaign.h"


Campaign::Campaign() : name(""), maps(0) {};
Campaign::Campaign(string name) : name(name), maps(0) {};
void Campaign::setName(string name) {
	this->name = name;
};
string Campaign::getName()const {
	return this->name;
};
vector<GameMap> Campaign::getMaps() const {
	return this->maps;
};

void Campaign::removeMap(string mapName) {
	for (int i = 0; i < this->maps.size(); i++) {
		if (maps.at(i).getName() == mapName) {
			maps.erase(maps.begin() + i);
			return;
		}
	}
	cout << "Cannot find the map";
};
void Campaign::displayAllMaps() {
	for (int i = 0; i < this->maps.size(); i++) {
		cout << to_string(i + 1) << ". " << maps.at(i).getName() << endl;
	}
};

bool Campaign::isValid() {
	for (int i = 0; i < this->maps.size(); i++) {
		if (!maps.at(i).verifyMap()) {
			return false;
		}
	}
	return true;
};
void Campaign::addMap(GameMap map) {
	maps.push_back(map);
};// Copy of a map is enough i think


int Campaign::getCurrentMapIndex() const {
	return currentMapIndex;
}

void Campaign::setCurrentMapIndex(int index) {
	currentMapIndex = index;
}

std::vector<std::shared_ptr<GameMap>> Campaign::getMapss() const {
	std::vector<std::shared_ptr<GameMap>> sharedMaps;
	for (const auto& map : maps) {
		sharedMaps.push_back(std::make_shared<GameMap>(map));
	}
	return sharedMaps;
}

void Campaign::swapMapOrder(int map1, int map2) {
	swap(maps[map1], maps[map2]);
};