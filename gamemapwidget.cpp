#include "GameMapWidget.h"
#include <QPainter>
#include <QDebug>
#include "GameMap.hpp"

GameMapWidget::GameMapWidget(QWidget *parent) : QWidget(parent) {
    setMinimumSize(200, 200); // Example minimum size
    emptyCellImg = QPixmap("./images/ground.jpg");
    wallCellImg = QPixmap("./images/wall.jpg");
    chestCellImg = QPixmap("./images/chest.png");
    characterCellImg = QPixmap("./images/character.png");
     enemyCellImg = QPixmap("./images/enemy.png");
     doorCellImg = QPixmap("./images/door.png");
}

void GameMapWidget::setGameMap(const GameMap* gameMap) {
    if (gameMap != nullptr) {
        map = gameMap;  // Assuming currentMap is a raw pointer
        update();   // Refresh or update the map display
    }
    else {
        qDebug() << "Error: Null map received.";
    }
  
}

void GameMapWidget::updateCellSize() {
    if (map == nullptr) return;

    // Calculate the cell size as an integer to avoid subpixel issues
    cellSize = std::min(width() / map->getWidth(), height() / map->getHeight());

    // Make sure that cellSize * number of cells does not exceed the widget size
    cellSize = std::min(cellSize, width() / map->getWidth());
    cellSize = std::min(cellSize, height() / map->getHeight());

    update(); // Trigger a repaint with the new cell sizes
}

void GameMapWidget::resizeEvent(QResizeEvent* event) {
    // Call the function that adjusts the cell size
    updateCellSize();
    QWidget::resizeEvent(event); // Call the base class implementation
}
\

    void GameMapWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (!map) return;

    painter.setRenderHint(QPainter::Antialiasing, false); // Turn off anti-aliasing
    for (int y = 0; y < map->getHeight(); ++y) {
        for (int x = 0; x < map->getWidth(); ++x) {
            QRect cellRect(x * cellSize, y * cellSize, cellSize, cellSize);

            QPixmap cellImg;
            switch (map->getCellType(x, y)) {
            case CellType::Empty:
                cellImg = emptyCellImg;
                   //qDebug() << "Empty cell image is null:" << cellImg.isNull();
                break;
            case CellType::Wall:
                cellImg = wallCellImg;
                break;
            case CellType::chest:
                cellImg = chestCellImg;
                break;
            case CellType::character:
                cellImg = characterCellImg;
                break;
            case CellType::Enemy:
                cellImg = enemyCellImg;
                break;
            case CellType::Door:
                cellImg = doorCellImg;
                break;
            default:
                cellImg = QPixmap(); // An empty QPixmap for unknown cell types, could be set to a default image
                break;
            }

            // Draw the pixmap in the cellRect
            if (!cellImg.isNull()) {
                // Scale the pixmap to fit the cell size
                QPixmap scaledImg = cellImg.scaled(cellSize, cellSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

                painter.drawPixmap(cellRect.topLeft(), scaledImg);
            } else {
                // Optionally, fill the cell with a default color if the image is not available
                painter.fillRect(cellRect, Qt::lightGray);
            }
        }
    }
}
void GameMapWidget::reloadMap() {
    repaint(); // Schedule a repaint event, which triggers paintEvent
}
