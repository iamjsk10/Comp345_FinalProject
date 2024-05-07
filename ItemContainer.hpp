#pragma once
#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H
#include <iostream>
#include <string>
#include <vector>
#include "Item.hpp"
#include "Armor.hpp"
#include "Belt.hpp"
#include "Boots.hpp"
#include "Helmet.hpp"
#include "Ring.hpp"
#include "Shield.hpp"
#include "Weapon.hpp"
using std::string;
//This implementation right now is not the best as it only check for same name

/// <summary>
/// This is base class ItemContainer containing vector of items
/// </summary>
class ItemContainer
{
protected:
    /// <summary>
    /// A vector of item pointers the current ItemContainer is carrying
    /// </summary>
    std::vector<Item*> items; //So it avoids slicing/turn derived into base (array would be easier, but need vector to defined undefined size)
public:
    /// <summary>
    /// Default constructor
    /// items = empty vector taking in Item pointer
    /// </summary>
    ItemContainer();
    /// <summary>
    /// Adding an item to the container
    /// </summary>
    /// <param name="item">Pointer of the item wanted to be added</param>
    /// <returns>true if added, false otherwise</returns>
    virtual bool addItem(Item* item);
    /// <summary>
    /// Removing an item from the container
    /// </summary>
    /// <param name="item">Pointer of a same item</param>
    /// <returns>true if found and removed, false otherwise</returns>
    virtual bool removeItem(Item* item);  // probably implement a function item to check if two items are the same (done)
    /// <summary>
    /// Removing an item from the container
    /// Might cause problem if there's mulitple items with the same names
    /// </summary>
    /// <param name="name">Name of the item</param>
    /// <returns>true if found and removed, false otherwise</returns>
    virtual bool removeItem(string name);
    /// <summary>
    /// Take an item form the container
    /// </summary>
    /// <param name="name">Name of the item</param>
    /// <returns>a pointer to the item, nullptr if not found</returns>
    virtual Item* takeItem(string name);
    /// <summary>
    /// Get items vecotr
    /// </summary>
    /// <returns>vector items</returns>
    std::vector<Item*> getItems() const;
    
    void displayItems() const;
};
/// <summary>
/// This is a derived class from ItemContainer with a size limit
/// </summary>
class Backpack :public ItemContainer {
protected:
    /// <summary>
    /// Size limit of the backpack
    /// If items reaches this size, it will reject adding more
    /// </summary>

    int size;
public:
    /// <summary>
    /// Default constructor
    /// size = 20
    /// </summary>
    Backpack();
    /// <summary>
    /// Parameterized constructor
    /// Setting the size
    /// </summary>
    /// <param name="size">positive integer to be size</param>
    Backpack(int size);
    /// <summary>
    /// Adding an item to the container
    /// </summary>
    /// <param name="item">Pointer of the item wanted to be added</param>
    /// <returns>true if added, false otherwise</returns>
    bool addItem(std::shared_ptr<Item> item);
    /// <summary>
    /// Remove an item from the container
    /// Will not add the item if the vector is already at size limit
    /// </summary>
    /// <param name="item">Pointer of a same item</param>
    /// <returns>true if found and removed, false otherwise</returns>
    bool removeItem(Item* item);  // probably implement a function item to check if two items are the same (done)
    /// <summary>
    /// Removing an item from the container
    /// Might cause problem if there's mulitple items with the same names
    /// </summary>
    /// <param name="name">Name of the item</param>
    /// <returns>true if found and removed, false otherwise</returns>
    bool removeItem(string name);
    /// <summary>
    /// Take an item from the container
    /// </summary>
    /// <param name="name">Name of the item</param>
    /// <returns>a pointer to the item, nullptr if not found</returns>
    Item* takeItem(string name);
    /// <summary>
    /// Get the limit of the backpack
    /// </summary>
    /// <returns>Limit of the backpack</returns>
    int getSize() const;
    Item* getItemByName(const string& name) const;
};

/// <summary>
/// This is a derived class from ItemContainer with a Item type limit of 1 each
/// </summary>
class WornItems : public ItemContainer {
protected:
    /// <summary>
    /// This keeps track of which Item type is already equipped
    /// </summary>
    bool equipped[7];
public:
    /// <summary>
    /// Default constructor
    /// </summary>
    WornItems();
    /// <summary>
    /// Adding an item to the container
    /// Will not add if the Item of the same type (ex:Helmet) is already in the container
    /// </summary>
    /// <param name="item">Pointer of the item wanted to be added</param>
    /// <returns>true if added, false otherwise</returns>
    bool addItem(Item* item);
    /// <summary>
    /// Remove an item from the container
    /// </summary>
    /// <param name="item">Pointer of a same item</param>
    /// <returns>true if found and removed, false otherwise</returns>
    bool removeItem(Item* item);  // probably implement a function item to check if two items are the same (done)
    /// <summary>
    /// Removing an item from the container
    /// Might cause problem if there's mulitple items with the same names
    /// </summary>
    /// <param name="name">Name of the item</param>
    /// <returns>true if found and removed, false otherwise</returns>
    bool removeItem(string name);
    /// <summary>
    /// Take an item from the container
    /// </summary>
    /// <param name="name">Name of the item</param>
    /// <returns>a pointer to the item, nullptr if not found</returns>
    Item* takeItem(string name);
    /// <summary>
    /// Check if there's already an item of the same type
    /// </summary>
    /// <param name="item">pointer to the item wanted to add</param>
    /// <returns>true if there's already an item with same type, false otherwise</returns>
    bool checkIfEquipped(Item* item) const; // Check if the same equipment type is equipped
};

/// <summary>
/// This is a derived class from ItemContainer
/// </summary>
class TreasureChest : public ItemContainer {
public:
    /// <summary>
    /// Default constructor
    /// </summary>
    TreasureChest();
    /// <summary>
    /// Adding an item to the container
    /// </summary>
    /// <param name="item">Pointer of the item wanted to be added</param>
    /// <returns>true if added, false otherwise</returns>
    bool addItem(Item* item);
    /// <summary>
    /// Remove an item from the container
    /// </summary>
    /// <param name="item">Pointer of a same item</param>
    /// <returns>true if found and removed, false otherwise</returns>
    bool removeItem(Item* item);  // probably implement a function item to check if two items are the same (done)
    /// <summary>
    /// Removing an item from the container
    /// Might cause problem if there's mulitple items with the same names
    /// </summary>
    /// <param name="name">Name of the item</param>
    /// <returns>true if found and removed, false otherwise</returns>
    bool removeItem(string name);
    /// <summary>
    /// Take an item from the container
    /// </summary>
    /// <param name="name">Name of the item</param>
    /// <returns>a pointer to the item, nullptr if not found</returns>
    Item* takeItem(string name);

     Item* openChest();
};

#endif
