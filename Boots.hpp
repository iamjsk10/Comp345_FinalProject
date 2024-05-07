
#pragma once
#ifndef Boots_hpp
#define Boots_hpp
#include "Item.hpp"
#include <iostream>
#include <string>
using std::string;
/// <summary>
/// This is a derived class from Item
/// It only have 2 possible enhancement types (Armor class, Dexterity)
/// </summary>
class Boots :public Item {
public:
    /// <summary>
    /// Default constructor
    /// name = ""
    /// enhancement = default enhancement
    /// </summary>
    Boots();
    /// <summary>
    /// Parameterized constructor
    /// </summary>
    /// <param name="name">string for name</param>
    /// <param name="enhancement">enhancement struct</param>
    Boots(string name, Enhancement enhancement);
    /// <summary>
    /// Parameteriezed constructor
    /// </summary>
    /// <param name="name">string for name</param>
    /// <param name="enhancementType">a valid enhancementType</param>
    /// <param name="enhancementBonus">an int from 1 to 5</param>
    Boots(string name, EnhancementType enhancementType, int enhancementBonus);
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
