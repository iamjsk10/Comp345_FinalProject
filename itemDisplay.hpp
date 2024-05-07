#ifndef ITEMDISPLAY_HPP
#define ITEMDISPLAY_HPP

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <memory>

class GameController; // Forward declaration to avoid circular dependency

// ItemDisplay class definition
class ItemDisplay : public QWidget {
    Q_OBJECT
public:
    explicit ItemDisplay(std::shared_ptr<GameController> gameController, QWidget* parent = nullptr);

private:
    std::shared_ptr<GameController> gameController;
    QListWidget* backpackListWidget;
    QListWidget* wornItemsListWidget;

    void setupUI();
    void populateBackpack();
    void populateWornItems();
    void refreshDisplay();
    void handleBackpackItemClicked(QListWidgetItem* item);
};

#endif // ITEMDISPLAY_HPP
