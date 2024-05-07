#include "Dice.h"

int Dice::roll(const std::string& diceExpression) {
        std::regex pattern("(\\d+)d(4|6|8|10|12|20|100)(\\+(\\d+))?");
        std::smatch matches;

        if (std::regex_match(diceExpression, matches, pattern)) {
            int numDice = std::stoi(matches[1]);
            int diceType = std::stoi(matches[2]);
            int modifier = matches[4].matched ? std::stoi(matches[4]) : 0;

            return rollDice(numDice, diceType) + modifier;
        }
        else {
            std::cerr << "Invalid dice expression: " << diceExpression << std::endl;
            return 0; // Or throw an exception if you prefer
        }
    }


int Dice::rollDice(int numDice, int diceType) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(1, diceType);

        int total = 0;
        for (int i = 0; i < numDice; ++i) {
            total += distribution(gen);
        }
        return total;
    }