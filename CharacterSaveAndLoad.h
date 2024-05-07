#pragma once
#include "Character.hpp"
#include "Item.hpp"
#include "Armor.hpp"
#include "Belt.hpp"
#include "Boots.hpp"
#include "Helmet.hpp"
#include "Ring.hpp"
#include "Shield.hpp"
#include "Weapon.hpp"
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
void saveCharacter(Character* character);
Character* loadCharacter(std::string characterName);