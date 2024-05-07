#include "ItemSaveAndLoad.h"
/*
enum EnhancementType {
    intelligence,
    wisdom,
    armorClass,
    strength,
    constitution,
    charisma,
    dexterity,
    attackBonus,
    damageBonus,
    none //Place holder for error, not-defined and other stuffs
};*/
std::string getEnhancementTypeName(Item* item) {
	EnhancementType type = item->getEnhancementType();
	switch (type) {
	case EnhancementType::intelligence:
		return "intelligence";
	case EnhancementType::wisdom:
		return "wisdom";
	case EnhancementType::armorClass:
		return "armorClass";
	case EnhancementType::strength:
		return "strength";
	case EnhancementType::constitution:
		return "constitution";
	case EnhancementType::charisma:
		return "charisma";
	case EnhancementType::dexterity:
		return "dexterity";
	case EnhancementType::attackBonus:
		return "attackBonus";
	case EnhancementType::damageBonus:
		return "damageBonus";
	case EnhancementType::none:
		return "none";
	}
}
EnhancementType stringToEnhancementType(std::string enhancementType) {
	if (enhancementType == "intelligence") {
		return EnhancementType::intelligence;
	}
	if (enhancementType == "wisdom") {
		return EnhancementType::wisdom;
	}
	if (enhancementType == "armorClass") {
		return EnhancementType::armorClass;
	}
	if (enhancementType == "strength") {
		return EnhancementType::strength;
	}
	if (enhancementType == "constitution") {
		return EnhancementType::constitution;
	}
	if (enhancementType == "charisma") {
		return EnhancementType::charisma;
	}
	if (enhancementType == "dexterity") {
		return EnhancementType::dexterity;
	}
	if (enhancementType == "attackBonus") {
		return EnhancementType::attackBonus;
	}
	if (enhancementType == "damageBonus") {
		return EnhancementType::damageBonus;
	}
	if (enhancementType == "none") {
		return EnhancementType::none;
	}
}

void saveItem(Item* item) {
	QString itemName = QString::fromUtf8(item->getName().c_str());
	QString fileName = ".\\items\\" + itemName + ".txt";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "Could not open file for writing";
		return; // Return false if file opening failed
	}
	QTextStream out(&file);
	out << QString::fromUtf8(item->getName().c_str()) << "\n";
	out << QString::fromUtf8(item->getEquipmentType()) << "\n";
	out << QString::fromUtf8(getEnhancementTypeName(item)) << "\n";
	out << QString::fromUtf8(std::to_string(item->getEnhancementBonus())) << "\n";
	file.close();

};

Item* loadItem(std::string itemName) {
	QString fileName = ".\\items\\" + QString::fromUtf8(itemName) + ".txt";
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Failed to open file for reading";
		return nullptr;
	}
	QTextStream in(&file);
	QString line;
	line = in.readLine();
	itemName = line.toStdString();
	line = in.readLine();
	std::string itemType = line.toStdString();
	line = in.readLine();
	std::string itemEnhancementType = line.toStdString();
	line = in.readLine();
	int itemEnhancementBonus = std::stoi(line.toStdString());
	if (itemType == "Armor") {
		return new Armor(itemName, stringToEnhancementType(itemEnhancementType), itemEnhancementBonus);
	}
	if (itemType == "Belt") {
		return new Belt(itemName, stringToEnhancementType(itemEnhancementType), itemEnhancementBonus);
	}
	if (itemType == "Boots") {
		return new Boots(itemName, stringToEnhancementType(itemEnhancementType), itemEnhancementBonus);
	}
	if (itemType == "Helmet") {
		return new Helmet(itemName, stringToEnhancementType(itemEnhancementType), itemEnhancementBonus);
	}
	if (itemType == "Ring") {
		return new Ring(itemName, stringToEnhancementType(itemEnhancementType), itemEnhancementBonus);
	}
	if (itemType == "Shield") {
		return new Shield(itemName, stringToEnhancementType(itemEnhancementType), itemEnhancementBonus);
	}
	if (itemType == "Weapon") {
		return new Weapon(itemName, stringToEnhancementType(itemEnhancementType), itemEnhancementBonus);
	}
	return nullptr;
};