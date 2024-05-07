#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QKeyEvent> // Include QKeyEvent header for key event handling

class MainMenu : public QWidget {
    Q_OBJECT

public:
    explicit MainMenu(QWidget* parent = nullptr);

    // Override key press event to handle 'W' key press
    void keyPressEvent(QKeyEvent* event) override;

signals:
    void startGameClicked();
    void createMapClicked();
    void createItemClicked();  // Corrected from creteItemClicked
    void createCampaignClicked();
    void exitClicked();
    void wKeyPressed();
private slots:
    void on_startGameButton_clicked();
    void on_createMapButton_clicked();
    void on_createItemClicked();
    void on_createCampaign_clicked();
    void on_exitButton_clicked();

private:
    QPushButton* startGameButton;
    QPushButton* MapEditorButton;
    QPushButton* itemEditorButton;
    QPushButton* CampaignEditorButton;
    QPushButton* exitButton;
};

#endif // MAINMENU_H
