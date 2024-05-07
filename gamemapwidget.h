#ifndef GAMEMAPWIDGET_H
#define GAMEMAPWIDGET_H

#include <QWidget>
#include <QPixmap>
#include "GameMap.hpp" // Include the GameMap header

class GameMapWidget : public QWidget {
    Q_OBJECT // Ensure Q_OBJECT macro is present for any QObject-based class

public:
    explicit GameMapWidget(QWidget *parent = nullptr);
    void setGameMap(const GameMap* gameMap); // Function to set the GameMap pointer
    void updateCellSize(); // Function to update the size of each cell
    void reloadMap();

protected:
    void paintEvent(QPaintEvent *event) override; // Override paintEvent
    void resizeEvent(QResizeEvent *event) override; // Override resizeEvent to handle widget resizing

private:
    QPixmap emptyCellImg;
    QPixmap wallCellImg;
    QPixmap chestCellImg;
    QPixmap characterCellImg;
    QPixmap enemyCellImg;
    QPixmap doorCellImg;

    const GameMap* map = nullptr; // Store a pointer to GameMap
    int cellSize; // Variable to hold the dynamic size of each cell
};

#endif // GAMEMAPWIDGET_H
