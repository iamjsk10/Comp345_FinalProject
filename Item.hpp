#pragma once
//Although pragma is also header guard, it might not work for old compiler
#ifndef item_hpp
#define item_hpp
#include <iostream>
#include <string>
#include <vector>
using std::string;
// Enum is useful when selecting a value from a possible set of values
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
};
/// <summary>
/// A struct consist of enhancementType, enhancementBonus
/// Used as a variable for Item
/// </summary>
struct Enhancement {
    /// <summary>
    /// Different item type can only have certain enhancement
    /// It is implemented in enum EnhancementType
    /// </summary>
    EnhancementType enhancementType;
    /// <summary>
    /// An integer from 1 to 5
    /// </summary>
    int enhancementBonus;
    /// <summary>
    /// Default constructor
    /// enhancementBonus = 0
    /// enhancementType = none (a placeholder for undefined)
    /// </summary>
    Enhancement();
    /// <summary>
    /// Parameterized constructor
    /// </summary>
    /// <param name="enhancementType">enhancementType from enum</param>
    /// <param name="enhancementBonus">a number from 1 to 5</param>
    Enhancement(EnhancementType enhancementType, int enhancementBonus);
};
/// <summary>
/// This is the base Item class so that it can be derived from
/// </summary>
class Item
{
protected: //Note that private is noot inherited
    string name;
    Enhancement enhancement;
    string equipmentType;
public:
    /// <summary>
    /// Default constructor
    /// name = ""
    /// enhancement = default enhancement
    /// </summary>
    Item();
    /// <summary>
    /// Parameterized constructor
    /// </summary>
    /// <param name="name">string for name</param>
    /// <param name="enhancement">enhancement struct</param>
    Item(string name, Enhancement enhancement);
    /// <summary>
    /// Parameteriezed constructor
    /// </summary>
    /// <param name="name">string for name</param>
    /// <param name="enhancementType">a valid enhancementType</param>
    /// <param name="enhancementBonus">an int from 1 to 5</param>
    Item(string name, EnhancementType enhancementType, int enhancementBonus);
    /// <summary>
    /// A function to get name of the item
    /// </summary>
    /// <returns>name of the item</returns>
    string getName();
    /// <summary>
    /// A function to get the enhancement of the item
    /// </summary>
    /// <returns>enhancement of the item</returns>
    Enhancement getEnhancement() const;
    /// <summary>
    /// Change the enhancement of the current Item
    /// </summary>
    /// <param name="enhancement">A valid enhancement struct of the current Item</param>
    /// <returns>true if valid and changed, false otherwise</returns>
    virtual bool setEnhancement(Enhancement enhancement); // Need to be override depending on the Item type
    /// <summary>
    /// Change the enhancementBonus number of the current Item
    /// </summary>
    /// <param name="enhancemnetBonus">A valid integer from 1 to 5</param>
    /// <returns>true if valid and changed, false otherwise</returns>
    virtual bool setEnhancementBonus(int enhancemnetBonus);
    /// <summary>
    /// Get the enhancementBonus number of the current Item
    /// </summary>
    /// <returns>An integer of enhancementBonus </returns>
    int getEnhancementBonus() const;
    /// <summary>
    /// Change the enhancementType of the current Item
    /// </summary>
    /// <returns>true if valid and changed, false otherwise</returns>
    virtual bool setEnhancementType(EnhancementType enhancementType); // Need to be override depending on the Item type
    /// <summary>
    /// Get the enhancementType of the current Item
    /// </summary>
    /// <returns>The enhancementType of the current Item</returns>
    EnhancementType getEnhancementType() const;
    string getEquipmentType();
    virtual void displayItem();
    
};
// Useful when checking classes
/// Used to check if the 2 are the same class
bool isSameClass(Item& item1, Item& item2);


#endif
