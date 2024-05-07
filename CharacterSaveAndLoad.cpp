#include "CharacterSaveAndLoad.h"
#include "ItemSaveAndLoad.h"

void saveCharacter(Character* character) {
	/*
    // Current stats
    // Equipment
    Backpack backpack;
    WornItems wornItems;
    Enemy* target = nullptr;
	*/
	using namespace::std;
	// not sure of the naming convention or QT output
	QString characterName = QString::fromUtf8(character->getName().c_str());
	QString fileName = ".\\characters\\" + characterName + ".txt";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "Could not open file for writing";
		return; // Return false if file opening failed
	}
	QTextStream out(&file);
	out << QString::fromUtf8(character->getName().c_str()) << "\n";
	out << QString::fromUtf8(to_string(character->getLevel()).c_str()) << "\n";
	out << QString::fromUtf8(to_string(character->getBaseHitPoints()).c_str()) << "\n";
	out << QString::fromUtf8(to_string(character->getBaseArmorClass()).c_str()) << "\n";
	out << QString::fromUtf8(to_string(character->getBaseAtackBonus()).c_str()) << "\n";
	out << QString::fromUtf8(to_string(character->getBaseDamageBonus()).c_str()) << "\n";
	out << QString::fromUtf8(to_string(character->getBaseStrength()).c_str()) << "\n";
	out << QString::fromUtf8(to_string(character->getBaseDexterity()).c_str()) << "\n";
	out << QString::fromUtf8(to_string(character->getBaseConstitution()).c_str()) << "\n";
	//The rest of the base stat is 0
	//The rest of the stat should be calculated with the the item
	/*
	*/
	
	// Ensuring the items are saved
	saveItem(character->getArmor());
	saveItem(character->getBelt());
	saveItem(character->getBoots());
	saveItem(character->getHelmet());
	saveItem(character->getRing());
	saveItem(character->getShield());
	saveItem(character->getWeapon());
	out << QString::fromUtf8(character->getArmor()->getName().c_str()) << "\n";
	out << QString::fromUtf8(character->getBelt()->getName().c_str()) << "\n";
	out << QString::fromUtf8(character->getBoots()->getName().c_str()) << "\n";
	out << QString::fromUtf8(character->getHelmet()->getName().c_str()) << "\n";
	out << QString::fromUtf8(character->getRing()->getName().c_str()) << "\n";
	out << QString::fromUtf8(character->getShield()->getName().c_str()) << "\n";
	out << QString::fromUtf8(character->getWeapon()->getName().c_str()) << "\n";
	qDebug() << "Save equipped";
		
	out << character->getBackpack().getItems().size()<<"\n";
	qDebug() << character->getBackpack().getItems().size() << "\n";
	//Saving backpacks
	for (int i = 0; i < character->getBackpack().getItems().size(); i++) {
		Item* item = character->getBackpack().getItems()[i];
		saveItem(item);
		out << QString::fromUtf8(item->getName().c_str()) << "\n";
	}
	qDebug() << "Save backpack";
	file.close();

	
};
// File Names Have to be CHanged
Character* loadCharacter(std::string characterName) {
	QString fileName = ".\\characters\\" + QString::fromUtf8(characterName) + ".txt";
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Failed to open file for reading";
		return nullptr;
	}
	QTextStream in(&file);
	QString line;
	line = in.readLine();
	line = in.readLine();
	int level = line.toInt();
	Character* character = new Character(characterName, level);
	line = in.readLine();
	character->setBaseHitPoints(line.toInt());
	line = in.readLine();
	character->setBaseArmorClass(line.toInt());
	line = in.readLine();
	character->setBaseAttackBonus(line.toInt());
	line = in.readLine();
	character->setBaseDamageBonus(line.toInt());
	line = in.readLine();
	character->setBaseStrength(line.toInt());
	line = in.readLine();
	character->setBaseDexterity(line.toInt());
	line = in.readLine();
	character->setBaseDexterity(line.toInt());
	Item* item;
	line = in.readLine();
	item = loadItem(line.toStdString());
	character->equip(dynamic_cast<Armor*>(item));
	line = in.readLine();
	item = loadItem(line.toStdString());
	character->equip(dynamic_cast<Belt*>(item));
	line = in.readLine();
	item = loadItem(line.toStdString());
	character->equip(dynamic_cast<Boots*>(item));
	line = in.readLine();
	item = loadItem(line.toStdString());
	character->equip(dynamic_cast<Helmet*>(item));
	line = in.readLine();
	item = loadItem(line.toStdString());
	character->equip(dynamic_cast<Ring*>(item));
	line = in.readLine();
	item = loadItem(line.toStdString());
	character->equip(dynamic_cast<Shield*>(item));
	line = in.readLine();
	item = loadItem(line.toStdString());
	character->equip(dynamic_cast<Weapon*>(item));
	
	line = in.readLine();
	int backpackSize = line.toInt();
	qDebug() << backpackSize;
	/*
	for (int i = 0; i < backpackSize; i++) {
		qDebug() << "Read another item";
		line = in.readLine();
		item = loadItem(line.toStdString());
		qDebug() << "loadItem";
		string type = item->getEquipmentType();
		qDebug() << "Get item type";
		if (type == "Armor") {
			character->getBackpack().addItem(std::make_shared<Armor>(item->getName(), item->getEnhancement()));
		}
		if (type == "Belt") {
			character->getBackpack().addItem(std::make_shared<Belt>(item->getName(), item->getEnhancement()));
		}
		if (type == "Boots") {
			character->getBackpack().addItem(std::make_shared<Boots>(item->getName(), item->getEnhancement()));
		}
		if (type == "Helmet") {
			character->getBackpack().addItem(std::make_shared<Helmet>(item->getName(), item->getEnhancement()));
		}
		if (type == "Ring") {
			character->getBackpack().addItem(std::make_shared<Ring>(item->getName(), item->getEnhancement()));
		}
		if (type == "Shield") {
			character->getBackpack().addItem(std::make_shared<Shield>(item->getName(), item->getEnhancement()));
		}
		if (type == "Weapon") {
			character->getBackpack().addItem(std::make_shared<Weapon>(item->getName(), item->getEnhancement()));
		}
		qDebug() << "Added " << item->getName();
	}
	*/
	qDebug() << "Finished";
	file.close();
	return character;
};
