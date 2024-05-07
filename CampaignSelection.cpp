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


CampaignSelection::CampaignSelection(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QStringListModel* model = new QStringListModel();
	QDir directory(".\\campaigns\\");
	QStringList fileNames = directory.entryList(QDir::Files);
	int index = 1;
	for (int i = 0; i < fileNames.size(); i++) {
		fileNames[i] = QString::fromUtf8(std::to_string(index)) + ". " + fileNames[i];
		index++;
	}
	model->setStringList(fileNames);
	ui.list_campaign->setModel(model);
	connect(ui.button_startGame, SIGNAL(clicked()), this, SLOT(on_button_startGame_clicked()));
	connect(ui.button_back, SIGNAL(clicked()), this, SLOT(on_button_back_clicked()));

}

CampaignSelection::~CampaignSelection()
{}

void CampaignSelection::on_button_startGame_clicked() {

	QModelIndexList selectedIndexes = ui.list_campaign->selectionModel()->selectedIndexes();
	if (selectedIndexes.isEmpty()) {
		qDebug() << "Not selected";
		return;
	}
	QModelIndex selectedIndex = selectedIndexes.first();
	QVariant selectedItemData = selectedIndex.data(Qt::DisplayRole); // Assuming DisplayRole is used for displaying item data
	int mapNumber = selectedIndex.row();
	QDir directory(".\\campaigns\\");
	QStringList fileNames = directory.entryList(QDir::Files);
	QString fileName = ".\\campaigns\\" + fileNames[mapNumber];
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Failed to open file for reading";
		return;
	}
	QTextStream in(&file);
	QString line;
	line = in.readLine();
	campaign = Campaign();
	campaign.setName(line.toStdString());
	line = in.readLine();
	int size = stoi(line.toStdString());
	for (int i = 0; i < size; i++) {
		line = in.readLine();
		addMap(line.toStdString()); // mapName with .txt
	}
	emit campaignReturned(campaign);
   
};
void CampaignSelection::on_button_back_clicked() {
	emit closing();
	close();
};





Campaign CampaignSelection::getCampaign() const {
	return campaign;
};


std::shared_ptr<Campaign> CampaignSelection::getCampaignss() const {
	return std::make_shared<Campaign>(campaign);
};
void CampaignSelection::addMap(string mapFileName) {
	QString fileName = ".\\maps\\" + QString::fromUtf8(mapFileName);
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Failed to open file for reading";
		return;
	}
	QTextStream in(&file);
	QString line;
	line = in.readLine();
	std::string mapName = line.toStdString();
	// Reading height/width
	int width, height;
	line = in.readLine();
	width = stoi(line.toStdString());
	line = in.readLine();
	height = stoi(line.toStdString());

	line = in.readLine();
	QStringList pos = line.split(",");
	std::vector<int> loc;
	for (QString s : pos) {
		loc.push_back(stoi(s.toStdString()));
	}
	std::vector<std::vector <MapCell>> grid(height, std::vector<MapCell>(width));
	for (int i = 0; i < height; i++) {
		line = in.readLine();
		QStringList cells = line.split(",");
		for (int j = 0; j < width; j++) {
			if (cells[j] == "E") {
				grid[i][j].setType(CellType::Empty);
			}
			if (cells[j] == "W") {
				grid[i][j].setType(CellType::Wall);
			}
			if (cells[j] == "C") {
				grid[i][j].setType(CellType::character);
			}
			if (cells[j] == "T") {
				grid[i][j].setType(CellType::chest);
			}
		}
	}
	GameMap loadedMap(width, height);
	loadedMap.setGrid(grid);
	loadedMap.setStartX(loc[0]);
	loadedMap.setStartY(loc[1]);
	loadedMap.setEndX(loc[2]);
	loadedMap.setEndY(loc[3]);
	loadedMap.setName(mapName);
	file.close();

	campaign.addMap(loadedMap);
};
