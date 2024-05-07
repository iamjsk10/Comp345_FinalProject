#include "ItemDisplay.hpp"
#include "GameController.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QVariant>
#include <Qdebug>

ItemDisplay::ItemDisplay(std::shared_ptr<GameController> gameController, QWidget* parent)
    : QWidget(parent), gameController(gameController) {
    setupUI();
}

void ItemDisplay::setupUI() {
    backpackListWidget = new QListWidget(this);
    wornItemsListWidget = new QListWidget(this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Backpack:"));
    layout->addWidget(backpackListWidget);
    layout->addWidget(new QLabel("Worn Items:"));
    layout->addWidget(wornItemsListWidget);

    populateBackpack();
    populateWornItems();

    connect(backpackListWidget, &QListWidget::itemClicked, this, &ItemDisplay::handleBackpackItemClicked);
    // Additional connections for worn items can be added here as needed
}
void ItemDisplay::populateBackpack() {
    auto backpackItems = gameController->getCharacter()->getBackpack().getItems();
    for (const auto& item : backpackItems) {
        qDebug() << item->getName();
        QListWidgetItem* listItem = new QListWidgetItem(QString::fromStdString(item->getName()), backpackListWidget);
        listItem->setData(Qt::UserRole, QString::fromStdString(item->getName()));
    }
}

void ItemDisplay::populateWornItems() {
    auto wornItems = gameController->getCharacter()->getWornItems().getItems();
    for (const auto& item : wornItems) {
        QListWidgetItem* listItem = new QListWidgetItem(QString::fromStdString(item->getName()), wornItemsListWidget);
        listItem->setData(Qt::UserRole, QString::fromStdString(item->getName()));
    }
}
void ItemDisplay::handleBackpackItemClicked(QListWidgetItem* item) {
    QString itemName = item->data(Qt::UserRole).toString();

    QMessageBox msgBox;
    msgBox.setText("What would you like to do with " + itemName + "?");
    QPushButton* equipButton = msgBox.addButton("Equip", QMessageBox::ActionRole);
    QPushButton* removeButton = msgBox.addButton("Remove", QMessageBox::ActionRole);

    msgBox.exec();

    if (msgBox.clickedButton() == equipButton) {
        // Retrieve the shared_ptr<Item> from the character's backpack based on itemName
        auto clickedItem = gameController->getCharacter()->getBackpack().getItemByName(itemName.toStdString());
        if (clickedItem) {
            gameController->getCharacter()->equip(clickedItem);
        }
    }
    else if (msgBox.clickedButton() == removeButton) {
        gameController->getCharacter()->getBackpack().removeItem(itemName.toStdString());
    }

    refreshDisplay();
}

void ItemDisplay::refreshDisplay() {
    backpackListWidget->clear();
    wornItemsListWidget->clear();
    populateBackpack();
    populateWornItems();
}