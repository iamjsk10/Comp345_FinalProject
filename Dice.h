#pragma once
#ifndef DICE_H
#define DICE_H
#include <iostream> 
#include <random>
#include <regex>
#include <string>
class Dice {
public:
    
    /**

@brief Roll the specified number of dice and return the result.
@param diceExpression A string representing the dice expression in the format xdy[+z],
where x is the number of dice, y is the type of dice (4, 6, 8, 10, 12, 20, 100),
and z is an optional modifier to add to the result.
@return The result of rolling the dice.
@details Example usage:
dice.roll("2d6+3") rolls 2 six-sided dice and adds 3 to the total result.
dice.roll("1d20") rolls a single twenty-sided die without any modifier.
*/
    int roll(const std::string& diceExpression);
protected:
    /**

@brief Roll a specified number of dice of a given type and return the total result.
@param numDice The number of dice to roll.
@param diceType The type of dice to roll (e.g., 4, 6, 8, 10, 12, 20, 100).
@return The total result obtained from rolling the dice.
*/
    int rollDice(int numDice, int diceType);
};
#endif