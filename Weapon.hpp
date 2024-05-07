
#pragma once
#ifndef Weapon_hpp
#define Weapon_hpp
#include "Item.hpp"
#include <iostream>
#include <string>
using std::string;

/// <summary>
/// This is a derived class from Item
/// It only have 2 possible enhancement types (Attack bonus, Damage bonus)
/// </summary>
class Weapon :public Item {
public:
    /// <summary>
    /// Default constructor
    /// name = ""
    /// enhancement = default enhancement
    /// </summary>
    Weapon();
    /// <summary>
    /// Parameterized constructor
    /// </summary>
    /// <param name="name">string for name</param>
    /// <param name="enhancement">enhancement struct</param>
    Weapon(string name, Enhancement enhancement);
    /// <summary>
    /// Parameteriezed constructor
    /// </summary>
    /// <param name="name">string for name</param>
    /// <param name="enhancementType">a valid enhancementType</param>
    /// <param name="enhancementBonus">an int from 1 to 5</param>
    Weapon(string name, EnhancementType enhancementType, int enhancementBonus);
    /// <summary>
    /// This override the operator== so it can compare 2 Items
    /// </summary>
    /// <param name="other">The other item to be compared to the first one</param>
    /// <returns>true if all variables are the same, false otherwise</returns>
    bool operator==(Item& other) const;
    /// <summary>
    /// This override the operator!= so it can compare 2 Items
    /// Reversing the operator==
    /// </summary>
    /// <param name="other">The other item to be compared to the first one</param>
    /// <returns>false if all variables are the same, true otherwise</returns>
    bool operator!=(Item& other) const;
    /// Change the enhancement of the current Item
    /// </summary>
    /// <param name="enhancement">A valid enhancement struct of the current Item</param>
    /// <returns>true if valid and changed, false otherwise</returns>
    bool setEnhancement(Enhancement enhancement) override;
    /// <summary>
    /// Change the enhancementBonus number of the current Item
    /// </summary>
    /// <param name="enhancemnetBonus">A valid integer from 1 to 5</param>
    /// <returns>true if valid and changed, false otherwise</returns>
    bool setEnhancementBonus(int enhancemnetBonus) override;
    /// <summary>
    /// Change the enhancementType of the current Item
    /// </summary>
    /// <returns>true if valid and changed, false otherwise</returns>
    bool setEnhancementType(EnhancementType enhancementType) override;
    
    void displayItem() override;
};

#endif
