#ifndef CHARACTER_DETAILS_WIDGET_HPP
#define CHARACTER_DETAILS_WIDGET_HPP


#include "Character.hpp"
#include <QWidget>
#include <QLabel>

class CharacterDetailsWidget : public QWidget {
    Q_OBJECT
public:
    explicit CharacterDetailsWidget(QWidget* parent = nullptr);
    void setCharacter(const Character& character); // Add this line
    void updateDisplay();
private:
    Character* currentCharacter;
    QLabel* nameLabel; // Assuming you have QLabel for character name, add more as needed
    QLabel* levelLabel; // And for other character details
}; 
#endif // CHARACTER_DETAILS_WIDGET_HPP