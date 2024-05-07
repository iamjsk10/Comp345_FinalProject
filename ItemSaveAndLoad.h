#pragma once
#include "Armor.hpp";
#include "Belt.hpp";
#include "Boots.hpp";
#include "Helmet.hpp";
#include "Item.hpp";
#include "Ring.hpp";
#include "Shield.hpp";
#include "Weapon.hpp";
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDir>
#include <QDebug>

void saveItem(Item* item);
Item* loadItem(std::string itemName);