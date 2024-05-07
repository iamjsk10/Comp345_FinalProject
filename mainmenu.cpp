#include "MainMenu.h"
#include <QPainter>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    // Initialize buttons
    startGameButton = new QPushButton("Start Game", this);
    MapEditorButton = new QPushButton("Map Editor", this);
    itemEditorButton = new QPushButton("Item Editor", this);

    CampaignEditorButton=new QPushButton("Campaign Editor", this);
    exitButton = new QPushButton("Exit", this);

    // Stylesheet for the buttons with transparent background and black text
    QString buttonStyle =
        "QPushButton { "
        "color: rgb(255, 255, 255); " // Black text color
        "background-color: rgba(0, 0, 0, 0); " // Fully transparent background
        "padding: 10px; "
        "font-size: 18px; "
        "font-weight: bold; "
        "text-shadow: 1px 1px 2px rgba(255, 255, 255, 0.7); " // White text shadow for better legibility
        "border: none; " // No border
        "}"
        "QPushButton:hover { "
        "background-color: rgba(0, 0, 0, 0.1); " // Slight background on hover for visual feedback
        "}"
        "QPushButton:pressed { "
        "background-color: rgba(0, 0, 0, 0.2); " // Slightly darker background for the pressed state
        "}";

    startGameButton->setStyleSheet(buttonStyle);
    MapEditorButton->setStyleSheet(buttonStyle);
    itemEditorButton->setStyleSheet(buttonStyle);

    CampaignEditorButton->setStyleSheet(buttonStyle);
    exitButton->setStyleSheet(buttonStyle);

    // Layout with less spacing and centered
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch(); // This will push the content to the center
    layout->addWidget(startGameButton);
    layout->addWidget(MapEditorButton);
    layout->addWidget(itemEditorButton);

    layout->addWidget(CampaignEditorButton);
    layout->addWidget(exitButton);
    layout->addStretch(); // This will push the content to the center
    layout->setSpacing(5); // Reduced spacing between buttons

    // Set alignment to center
    layout->setAlignment(Qt::AlignCenter);

    setLayout(layout);

    // Connect buttons to slots
    connect(startGameButton, &QPushButton::clicked, this, &MainMenu::on_startGameButton_clicked);

    connect(MapEditorButton, &QPushButton::clicked, this, &MainMenu::on_createMapButton_clicked);

    connect(itemEditorButton, &QPushButton::clicked, this, &MainMenu::on_createItemClicked);

    connect(CampaignEditorButton, &QPushButton::clicked, this, &MainMenu::on_createCampaign_clicked);

    connect(exitButton, &QPushButton::clicked, this, &MainMenu::on_exitButton_clicked);
}

void MainMenu::on_startGameButton_clicked() {
    emit startGameClicked();
}
void MainMenu::on_createItemClicked() {
    emit createItemClicked();
}
void MainMenu::on_createMapButton_clicked() {
    emit createMapClicked();
}

void MainMenu::on_createCampaign_clicked() {
    emit createCampaignClicked();
}
void MainMenu::on_exitButton_clicked() {
    emit exitClicked();
}
void MainMenu::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_W) {
        emit wKeyPressed(); // Emit wKeyPressed signal when 'W' key is pressed
    }
    QWidget::keyPressEvent(event); // Call base class implementation
}

