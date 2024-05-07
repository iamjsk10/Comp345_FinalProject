#include "CharacterDetailsWidget.hpp"
#include <QVBoxLayout>

CharacterDetailsWidget::CharacterDetailsWidget(QWidget* parent)
    : QWidget(parent), currentCharacter(nullptr), nameLabel(new QLabel(this)), levelLabel(new QLabel(this)) {
    QVBoxLayout* layout = new QVBoxLayout(this); // Create a vertical layout
    layout->addWidget(nameLabel); // Add the nameLabel to the layout
    layout->addWidget(levelLabel); // Add the levelLabel to the layout
    this->setLayout(layout); // Set the layout to the widget
    this->setFixedSize(200, 100); // You can adjust or remove this fixed size later
}
void CharacterDetailsWidget::setCharacter(const Character& character) {
    if (!currentCharacter) currentCharacter = new Character(character); // Assuming proper copy constructor
    else *currentCharacter = character;
    updateDisplay();
}

void CharacterDetailsWidget::updateDisplay() {
    if (currentCharacter) {
        nameLabel->setText(QString::fromStdString(currentCharacter->getName()));
        levelLabel->setText(QString("Level: %1").arg(currentCharacter->getLevel()));
    }
    // Make sure to delete currentCharacter in the destructor if it's not nullptr
}