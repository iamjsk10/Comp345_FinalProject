#include <QApplication>
#include "MapEditor.h"
#include "CampaignEditor.h"
#include "GameMap.hpp"
#include "GameMapWidget.h"
#include "MainMenu.h"
#include "CharacterDetailsWidget.hpp"
#include "Character.hpp"
#include "GameController.hpp"
#include <memory>
#include "Enemy.hpp"
#include <Qdebug>
#include "ItemEditor.h"
#include "ItemDisplay.hpp"
#include "CharacterDetailsWidget.hpp"
#include <QProgressBar>
#include "CampaignSelection.h"
#include "CharacterSelection.h"











void setupGameUI(Campaign campaign, CampaignSelection& campaignSelect,int i) {




    auto character = std::make_shared<Character>("Hero", 5);

    int maxHealth = character->getHealth();

    // Create sample items
    Enhancement attackBonusEnhancement(EnhancementType::attackBonus, 3); // Example attack bonus enhancement
    Enhancement damageBonusEnhancement(EnhancementType::damageBonus, 2); // Example damage bonus enhancement
    Enhancement defenseBonusEnhancement(EnhancementType::armorClass, 5); // Example defense bonus enhancement
    Enhancement strengthBonusEnhancement(EnhancementType::strength, 2); // Example strength bonus enhancement
    Enhancement agilityBonusEnhancement(EnhancementType::dexterity, 3); // Example agility bonus enhancement


    auto sword = std::make_shared<Weapon>("Excalibur", attackBonusEnhancement);
    auto axe = std::make_shared<Weapon>("Battle Axe", damageBonusEnhancement);
    auto shield = std::make_shared<Shield>("Steel Shield", defenseBonusEnhancement);
    auto helmet = std::make_shared<Helmet>("Iron Helmet", defenseBonusEnhancement);
    auto armor = std::make_shared<Armor>("Chainmail Armor", defenseBonusEnhancement);
    auto ring = std::make_shared<Ring>("Ring of Strength", strengthBonusEnhancement);
    auto belt = std::make_shared<Belt>("Belt of Agility", agilityBonusEnhancement);
    auto boots = std::make_shared<Boots>("Leather Boots", agilityBonusEnhancement);

    // Add items to backpack using shared pointers
    character->getBackpack().addItem(sword);
    character->getBackpack().addItem(axe);
    character->getBackpack().addItem(shield);
    character->getBackpack().addItem(helmet);
    character->getBackpack().addItem(armor);
    character->getBackpack().addItem(ring);
    character->getBackpack().addItem(belt);
    character->getBackpack().addItem(boots);

    // Equip items directly with shared pointers
    character->equip(sword.get());
    character->equip(axe.get());
    character->equip(shield.get());
    character->equip(helmet.get());
    character->equip(armor.get());
    character->equip(ring.get());
    character->equip(belt.get());
    character->equip(boots.get());
    // Create sample items with shared_ptr for shared ownership

    // Add items to backpack using shared pointers

    // Equip items directly with shared pointers
    character->equip(sword.get()); // Adjust `equip` method to accept std::shared_ptr<Weapon>
    character->equip(axe.get());


    auto swordUUU = std::make_shared<Weapon>("********Excalibur", attackBonusEnhancement);

    auto axeUUU = std::make_shared<Weapon>("********Axe", attackBonusEnhancement);


    auto map = campaign.getMapss().at(i);




    map->setCell(1, 1, CellType::character); // Place character on the map
    map->setCell(1, 2, CellType::Enemy); // Place character on the map
    map->setCell(2, 2, CellType::Door); // Place character on the map

    auto gameController = std::make_shared<GameController>(map, character, campaignSelect.getCampaignss(), 9);
    int enemyMaxHealth = gameController.get()->enemies.at(0).get()->getHitPoints();
    QWidget* gameContainer = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(gameContainer);
    auto mapWidget = new GameMapWidget();
    mapWidget->setGameMap(map.get());
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QWidget* mainWidget = new QWidget;
    auto characterDetails = new CharacterDetailsWidget();

    layout->addWidget(mapWidget);
    characterDetails->setCharacter(*character.get());  // Set the initial character details
    layout->addWidget(characterDetails);  // Add the character details widget to the layout
    gameContainer->setLayout(layout);
    //auto characterDetails = new CharacterDetailsWidget();
    //characterDetails->setCharacter(*character.get());
    //layout->addWidget(characterDetails);
    gameContainer->setLayout(layout);

    // Setup buttons and their connections
    QPushButton* moveUpButton = new QPushButton("UP"); // Up button
    QPushButton* moveDownButton = new QPushButton("Down"); // Down button
    QPushButton* moveLeftButton = new QPushButton("Left"); // Left button
    QPushButton* moveRightButton = new QPushButton("Right"); // Right button
    QPushButton* attackButton = new QPushButton("Attack"); // Right button
    QPushButton* detailButton = new QPushButton("Detail"); // Right button
    QPushButton* openchestButton = new QPushButton("Open Chest"); // Right button

    QPushButton* InventoryButton = new QPushButton("Inventory"); // Right button


    auto characterLabel = new QLabel("Character Health:");
    auto healthBar = new QProgressBar();
    healthBar->setRange(0, maxHealth);
    healthBar->setValue(maxHealth);
    healthBar->setFormat("%v / %m HP"); // Shows current health over max health


    auto enemyLabel = new QLabel("Enemy Health:");
    auto enemyHealthBar = new QProgressBar();
    enemyHealthBar->setRange(0, enemyMaxHealth);
    enemyHealthBar->setValue(gameController.get()->enemies.at(0).get()->getHitPoints());
    enemyHealthBar->setFormat("%v / %m HP"); // Shows current health over max health


    auto healthLayout = new QVBoxLayout();
    healthLayout->addWidget(characterLabel);
    healthLayout->addWidget(healthBar);
    healthLayout->addWidget(enemyLabel);
    healthLayout->addWidget(enemyHealthBar);

    characterLabel->setStyleSheet("font-weight: bold; color: white;");
    enemyLabel->setStyleSheet("font-weight: bold; color: red;");

    layout->addWidget(healthBar);
    layout->addWidget(enemyHealthBar);

    QObject::connect(moveUpButton, &QPushButton::clicked, [gameController, mapWidget]() {
        gameController->moveUp();
        mapWidget->reloadMap();
        });
    QObject::connect(moveDownButton, &QPushButton::clicked, [gameController, mapWidget]() {
        gameController->moveDown();
        mapWidget->reloadMap();
        });
    QObject::connect(moveLeftButton, &QPushButton::clicked, [gameController, mapWidget]() {
        gameController->moveLeft();
        mapWidget->reloadMap();

        });
    QObject::connect(moveRightButton, &QPushButton::clicked, [gameController, mapWidget, map, character]() {
        gameController->moveRight();
        mapWidget->reloadMap();

        });
    QObject::connect(openchestButton, &QPushButton::clicked, [gameController, mapWidget, map, character, swordUUU]() {
        gameController->searchChest();
        character->getBackpack().addItem(swordUUU);

        mapWidget->reloadMap();

        });
    QObject::connect(attackButton, &QPushButton::clicked, [gameController, mapWidget, map, enemyHealthBar, character, healthBar, axeUUU]() {

        gameController->checkAndAttackEnemy();
        if (gameController.get()->enemies.at(0).get()->getHitPoints() > 0) {
            enemyHealthBar->setValue(gameController.get()->enemies.at(0).get()->getHitPoints());
            int rel = character->getHealth();
            character->setHitPoints(rel - 2);
            healthBar->setValue(rel - 2);

        }
        else {
            enemyHealthBar->setValue(0);
            map->setCell(1, 2, CellType::chest); // Place character on the map
            gameController->searchChest();

            character->getBackpack().addItem(axeUUU);
        }
        mapWidget->reloadMap();


        });
    QObject::connect(detailButton, &QPushButton::clicked, [gameContainer, mapWidget]() {
        gameContainer->show();
        });

    QObject::connect(InventoryButton, &QPushButton::clicked, [gameController, mapWidget]() {
        auto* itemDisplayWindow = new ItemDisplay(gameController);
        itemDisplayWindow->setAttribute(Qt::WA_DeleteOnClose); // Make sure the window deletes itself after closing
        itemDisplayWindow->show();
        });
    // Set fixed size for buttons
// Set fixed size for buttons
    const int buttonWidth = 60; // Adjust the width as needed
    const int buttonHeight = 40; // Adjust the height as needed
    moveUpButton->setFixedSize(buttonWidth, buttonHeight);
    moveDownButton->setFixedSize(buttonWidth, buttonHeight);
    moveLeftButton->setFixedSize(buttonWidth, buttonHeight);
    moveRightButton->setFixedSize(buttonWidth, buttonHeight);
    openchestButton->setFixedSize(buttonWidth, buttonHeight);

    attackButton->setFixedSize(buttonWidth, buttonHeight);
    detailButton->setFixedSize(buttonWidth, buttonHeight);

    InventoryButton->setFixedSize(buttonWidth, buttonHeight);


    // Set smaller font size for buttons
    QFont buttonFont = moveUpButton->font();
    buttonFont.setPointSize(12); // Adjust the font size as needed
    moveUpButton->setFont(buttonFont);
    moveDownButton->setFont(buttonFont);
    moveLeftButton->setFont(buttonFont);
    moveRightButton->setFont(buttonFont);
    attackButton->setFont(buttonFont);
    detailButton->setFont(buttonFont);
    openchestButton->setFont(buttonFont);


    InventoryButton->setFixedSize(buttonWidth, buttonHeight);

    // Setup horizontal layout for buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(moveLeftButton);
    buttonLayout->addWidget(moveUpButton);
    buttonLayout->addWidget(moveRightButton);
    buttonLayout->addWidget(moveDownButton);
    buttonLayout->addWidget(attackButton);
    buttonLayout->addWidget(detailButton);
    buttonLayout->addWidget(openchestButton);


    buttonLayout->addWidget(InventoryButton);



    buttonLayout->setAlignment(Qt::AlignHCenter); // Align buttons horizontally at the center
    buttonLayout->setSpacing(10); // Add spacing between buttons

    // Create widget to hold buttons
    QWidget* buttonWidget = new QWidget;
    buttonWidget->setLayout(buttonLayout);

    // Create layout for the main window
    mainLayout->addWidget(mapWidget); // Add map widget to the layout
    mainLayout->addWidget(buttonWidget); // Add button widget to the layout

    // Set stretch factor to give more space to the map widget
    mainLayout->setStretchFactor(mapWidget, 1);
    mainLayout->addLayout(healthLayout);

    // Create main widget to hold the layout

    mainWidget->setLayout(mainLayout);
    mainWidget->showMaximized();




}




int main(int argc, char* argv[]) {
    qRegisterMetaType<std::shared_ptr<Item>>("std::shared_ptr<Item>");

    QApplication a(argc, argv);





    auto character = std::make_shared<Character>("Hero", 5);

    int maxHealth = character->getHealth();

    // Create sample items
    Enhancement attackBonusEnhancement(EnhancementType::attackBonus, 3); // Example attack bonus enhancement
    Enhancement damageBonusEnhancement(EnhancementType::damageBonus, 2); // Example damage bonus enhancement
    Enhancement defenseBonusEnhancement(EnhancementType::armorClass, 5); // Example defense bonus enhancement
    Enhancement strengthBonusEnhancement(EnhancementType::strength, 2); // Example strength bonus enhancement
    Enhancement agilityBonusEnhancement(EnhancementType::dexterity, 3); // Example agility bonus enhancement


    auto sword = std::make_shared<Weapon>("Excalibur", attackBonusEnhancement);
    auto axe = std::make_shared<Weapon>("Battle Axe", damageBonusEnhancement);
    auto shield = std::make_shared<Shield>("Steel Shield", defenseBonusEnhancement);
    auto helmet = std::make_shared<Helmet>("Iron Helmet", defenseBonusEnhancement);
    auto armor = std::make_shared<Armor>("Chainmail Armor", defenseBonusEnhancement);
    auto ring = std::make_shared<Ring>("Ring of Strength", strengthBonusEnhancement);
    auto belt = std::make_shared<Belt>("Belt of Agility", agilityBonusEnhancement);
    auto boots = std::make_shared<Boots>("Leather Boots", agilityBonusEnhancement);

    // Add items to backpack using shared pointers
    character->getBackpack().addItem(sword);
    character->getBackpack().addItem(axe);
    character->getBackpack().addItem(shield);
    character->getBackpack().addItem(helmet);
    character->getBackpack().addItem(armor);
    character->getBackpack().addItem(ring);
    character->getBackpack().addItem(belt);
    character->getBackpack().addItem(boots);

    // Equip items directly with shared pointers
    character->equip(sword.get());
    character->equip(axe.get());
    character->equip(shield.get());
    character->equip(helmet.get());
    character->equip(armor.get());
    character->equip(ring.get());
    character->equip(belt.get());
    character->equip(boots.get());
    // Create sample items with shared_ptr for shared ownership

    // Add items to backpack using shared pointers

    // Equip items directly with shared pointers
    character->equip(sword.get()); // Adjust `equip` method to accept std::shared_ptr<Weapon>
    character->equip(axe.get());


    auto swordUUU = std::make_shared<Weapon>("********Excalibur", attackBonusEnhancement);

    auto axeUUU = std::make_shared<Weapon>("********Axe", attackBonusEnhancement);



    MainMenu menu;
    auto characterSelect = std::make_unique<CharacterSelection>();
    auto campaignSelect = std::make_unique<CampaignSelection>();
    menu.showMaximized();
    // Setup connections for MainMenu
    QObject::connect(&menu, &MainMenu::startGameClicked, [&]() {
        menu.hide();
            //campaignSelect->showMaximized();

        characterSelect->showMaximized();
        });

    // Handle back navigation from CharacterSelection
    QObject::connect(characterSelect.get(), &CharacterSelection::back, [&]() {
        characterSelect->hide();
        menu.showMaximized();
        });

    // Transition from CharacterSelection to CampaignSelection
    QObject::connect(characterSelect.get(), &CharacterSelection::characterReturned, [&](const Character& characterData) {
        characterSelect->hide();
        campaignSelect->showMaximized();
        });

    // Handle back navigation from CampaignSelection
    QObject::connect(campaignSelect.get(), &CampaignSelection::closing, [&]() {
        campaignSelect->hide();
        menu.showMaximized();
        });

    // Start game after campaign is selected
    QObject::connect(campaignSelect.get(), &CampaignSelection::campaignReturned, [&](const Campaign& campaign) {
   
        campaignSelect->hide();
        //auto map = std::make_shared<GameMap>(10, 10);
      
        //// Setup initial map configuration
        //int width = map->getWidth();
        //int height = map->getHeight();
        //for (int x = 0; x < width; ++x) {
        //    map->setCell(x, 0, CellType::Wall); // Top wall
        //    map->setCell(x, height - 1, CellType::Wall); // Bottom wall
        //}
        //for (int y = 0; y < height; ++y) {
        //    map->setCell(0, y, CellType::Wall); // Left wall
        //    map->setCell(width - 1, y, CellType::Wall); // Right wall
        //}
        //map->setCell(1, 1, CellType::character); // Place character on the map
        //map->setCell(1, 2, CellType::Enemy); // Place character on the map







       
        // Connection to handle the campaign selected signal
     


                int i = 0;
                auto map = campaign.getMapss().at(i);


                map->setCell(1, 1, CellType::character); // Place character on the map
                map->setCell(1, 2, CellType::Enemy); // Place character on the map
                map->setCell(2, 2, CellType::Door); // Place character on the map

                auto gameController = std::make_shared<GameController>(map, character, campaignSelect.get()->getCampaignss(), 9);
                int enemyMaxHealth = gameController.get()->enemies.at(0).get()->getHitPoints();
                QWidget* gameContainer = new QWidget();
                QHBoxLayout* layout = new QHBoxLayout(gameContainer);
                auto mapWidget = new GameMapWidget();
                mapWidget->setGameMap(map.get());
                QVBoxLayout* mainLayout = new QVBoxLayout;
                QWidget* mainWidget = new QWidget;
                auto characterDetails = new CharacterDetailsWidget();

                layout->addWidget(mapWidget);
                characterDetails->setCharacter(*character.get());  // Set the initial character details
                layout->addWidget(characterDetails);  // Add the character details widget to the layout
                gameContainer->setLayout(layout);
                //auto characterDetails = new CharacterDetailsWidget();
                //characterDetails->setCharacter(*character.get());
                //layout->addWidget(characterDetails);
                gameContainer->setLayout(layout);

                // Setup buttons and their connections
                QPushButton* moveUpButton = new QPushButton("UP"); // Up button
                QPushButton* moveDownButton = new QPushButton("Down"); // Down button
                QPushButton* moveLeftButton = new QPushButton("Left"); // Left button
                QPushButton* moveRightButton = new QPushButton("Right"); // Right button
                QPushButton* attackButton = new QPushButton("Attack"); // Right button
                QPushButton* detailButton = new QPushButton("Detail"); // Right button
                QPushButton* openchestButton = new QPushButton("Open Chest"); // Right button

                QPushButton* InventoryButton = new QPushButton("Inventory"); // Right button


                auto characterLabel = new QLabel("Character Health:");
                auto healthBar = new QProgressBar();
                healthBar->setRange(0, maxHealth);
                healthBar->setValue(maxHealth);
                healthBar->setFormat("%v / %m HP"); // Shows current health over max health


                auto enemyLabel = new QLabel("Enemy Health:");
                auto enemyHealthBar = new QProgressBar();
                enemyHealthBar->setRange(0, enemyMaxHealth);
                enemyHealthBar->setValue(gameController.get()->enemies.at(0).get()->getHitPoints());
                enemyHealthBar->setFormat("%v / %m HP"); // Shows current health over max health


                auto healthLayout = new QVBoxLayout();
                healthLayout->addWidget(characterLabel);
                healthLayout->addWidget(healthBar);
                healthLayout->addWidget(enemyLabel);
                healthLayout->addWidget(enemyHealthBar);

                characterLabel->setStyleSheet("font-weight: bold; color: white;");
                enemyLabel->setStyleSheet("font-weight: bold; color: red;");

                layout->addWidget(healthBar);
                layout->addWidget(enemyHealthBar);

                QObject::connect(moveUpButton, &QPushButton::clicked, [gameController, mapWidget]() {
                    gameController->moveUp();
                    mapWidget->reloadMap();
                    });
                QObject::connect(moveDownButton, &QPushButton::clicked, [gameController, mapWidget]() {
                    gameController->moveDown();
                    mapWidget->reloadMap();
                    });
                QObject::connect(moveLeftButton, &QPushButton::clicked, [gameController, mapWidget]() {
                    gameController->moveLeft();
                    mapWidget->reloadMap();

                    });
                QObject::connect(moveRightButton, &QPushButton::clicked, [gameController, mapWidget,map,character]() {
                    gameController->moveRight();
                    mapWidget->reloadMap();
                 
                    }); 
                QObject::connect(openchestButton, &QPushButton::clicked, [gameController, mapWidget, map, character, swordUUU]() {
                    gameController->searchChest();
                    character->getBackpack().addItem(swordUUU);

                     mapWidget->reloadMap();

                    });
                QObject::connect(attackButton, &QPushButton::clicked, [gameController, mapWidget, map, enemyHealthBar, character, healthBar, axeUUU]() {

                    gameController->checkAndAttackEnemy();
                    if (gameController.get()->enemies.at(0).get()->getHitPoints() > 0) {
                        enemyHealthBar->setValue(gameController.get()->enemies.at(0).get()->getHitPoints());
                        int rel = character->getHealth();
                        character->setHitPoints(rel-2);
                        healthBar->setValue(rel-2);

                    }
                    else {
                        enemyHealthBar->setValue(0);
                        map->setCell(1, 2, CellType::chest); // Place character on the map
                        gameController->searchChest();

                        character->getBackpack().addItem(axeUUU);
                    }
                    mapWidget->reloadMap();


                    });
                QObject::connect(detailButton, &QPushButton::clicked, [gameContainer, mapWidget]() {
                    gameContainer->show();
                    });

                QObject::connect(InventoryButton, &QPushButton::clicked, [gameController, mapWidget]() {
                    auto* itemDisplayWindow = new ItemDisplay(gameController);
                    itemDisplayWindow->setAttribute(Qt::WA_DeleteOnClose); // Make sure the window deletes itself after closing
                    itemDisplayWindow->show();
                    });
                // Set fixed size for buttons
            // Set fixed size for buttons
                const int buttonWidth = 60; // Adjust the width as needed
                const int buttonHeight = 40; // Adjust the height as needed
                moveUpButton->setFixedSize(buttonWidth, buttonHeight);
                moveDownButton->setFixedSize(buttonWidth, buttonHeight);
                moveLeftButton->setFixedSize(buttonWidth, buttonHeight);
                moveRightButton->setFixedSize(buttonWidth, buttonHeight);
                openchestButton->setFixedSize(buttonWidth, buttonHeight);

                attackButton->setFixedSize(buttonWidth, buttonHeight);
                detailButton->setFixedSize(buttonWidth, buttonHeight);

                InventoryButton->setFixedSize(buttonWidth, buttonHeight);


                // Set smaller font size for buttons
                QFont buttonFont = moveUpButton->font();
                buttonFont.setPointSize(12); // Adjust the font size as needed
                moveUpButton->setFont(buttonFont);
                moveDownButton->setFont(buttonFont);
                moveLeftButton->setFont(buttonFont);
                moveRightButton->setFont(buttonFont);
                attackButton->setFont(buttonFont);
                detailButton->setFont(buttonFont);
                openchestButton->setFont(buttonFont);


                InventoryButton->setFixedSize(buttonWidth, buttonHeight);

                // Setup horizontal layout for buttons
                QHBoxLayout* buttonLayout = new QHBoxLayout;
                buttonLayout->addWidget(moveLeftButton);
                buttonLayout->addWidget(moveUpButton);
                buttonLayout->addWidget(moveRightButton);
                buttonLayout->addWidget(moveDownButton);
                buttonLayout->addWidget(attackButton);
                buttonLayout->addWidget(detailButton);
                buttonLayout->addWidget(openchestButton);


                buttonLayout->addWidget(InventoryButton);



                buttonLayout->setAlignment(Qt::AlignHCenter); // Align buttons horizontally at the center
                buttonLayout->setSpacing(10); // Add spacing between buttons

                // Create widget to hold buttons
                QWidget* buttonWidget = new QWidget;
                buttonWidget->setLayout(buttonLayout);

                // Create layout for the main window
                mainLayout->addWidget(mapWidget); // Add map widget to the layout
                mainLayout->addWidget(buttonWidget); // Add button widget to the layout

                // Set stretch factor to give more space to the map widget
                mainLayout->setStretchFactor(mapWidget, 1);
                mainLayout->addLayout(healthLayout);

                // Create main widget to hold the layout

                mainWidget->setLayout(mainLayout);
                mainWidget->showMaximized();


    
                QObject::connect(gameController.get(), &GameController::mapChanged,
                    [mainWidget, &campaign, &campaignSelect, gameController](std::shared_ptr<GameMap> newMap) {
                        mainWidget->hide();
                        setupGameUI(campaign, *campaignSelect, gameController->currentI);
                    });










        
        
        
        
        });

       

    QObject::connect(&menu, &MainMenu::createMapClicked, [&]() {
        auto w = new MapEditor(); // Assuming MapEditor inherits from QWidget
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();
        menu.hide();
        QObject::connect(w, &QWidget::destroyed, [&]() {
            menu.showMaximized();
            });
        });
    QObject::connect(&menu, &MainMenu::createItemClicked, [&]() {
        auto itemEditor = new ItemEditor();
        itemEditor->setAttribute(Qt::WA_DeleteOnClose);
        itemEditor->showMaximized();
        menu.hide();

        QObject::connect(itemEditor, &QWidget::destroyed, [&]() {
            menu.showMaximized();
            });
        });
    QObject::connect(&menu, &MainMenu::createCampaignClicked, [&]() {
        auto c = new CampaignEditor(); // Assuming CampaignEditor inherits from QWidget
        c->setAttribute(Qt::WA_DeleteOnClose);
        c->showMaximized();
        menu.hide();
        QObject::connect(c, &QWidget::destroyed, [&]() {
            menu.showMaximized();
            });

        });

    QObject::connect(&menu, &MainMenu::exitClicked, &a, &QApplication::quit);
   
    return a.exec();
}
