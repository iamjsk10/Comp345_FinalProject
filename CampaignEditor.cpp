#include "CampaignEditor.h"

CampaignEditor::CampaignEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.stackedWidget->setCurrentWidget(ui.widget_mainPage);
	connect(ui.button_mainPage_exit, SIGNAL(clicked()), this, SLOT(on_button_mainPage_exit_clicked()));
	connect(ui.button_mainPage_newCampaign, SIGNAL(clicked()), this, SLOT(on_button_mainPage_newCampaign_clicked()));
	connect(ui.button_mainPage_loadCampaign, SIGNAL(clicked()), this, SLOT(on_button_mainPage_loadCampaign_clicked()));

	connect(ui.button_addMap_exit, SIGNAL(clicked()), this, SLOT(on_button_addMap_exit_clicked()));
	connect(ui.button_addMap_load, SIGNAL(clicked()), this, SLOT(on_button_addMap_load_clicked()));

	connect(ui.button_campaignEditor_exit, SIGNAL(clicked()), this, SLOT(on_button_campaignEditor_exit_clicked()));
	connect(ui.button_campaignEditor_save, SIGNAL(clicked()), this, SLOT(on_button_campaignEditor_save_clicked()));

	connect(ui.button_createNewCampaign_createCampaign, SIGNAL(clicked()), this, SLOT(on_button_createNewCampaign_createCampaign_clicked()));
}

CampaignEditor::~CampaignEditor()
{}

void CampaignEditor::on_button_mainPage_exit_clicked() {
	close();
};
void CampaignEditor::on_button_mainPage_newCampaign_clicked() {
	ui.stackedWidget->setCurrentWidget(ui.widget_createNewCampaign);

};
void CampaignEditor::on_button_mainPage_loadCampaign_clicked() {
	QStringListModel* model = new QStringListModel();
	QDir directory(".\\campaigns\\");
	QStringList fileNames = directory.entryList(QDir::Files);
	int index = 1;
	for (int i = 0; i < fileNames.size(); i++) {
		fileNames[i] = QString::fromUtf8(std::to_string(index)) + ". " + fileNames[i];
		index++;
	}
	model->setStringList(fileNames);
	ui.list_loadCampaign_campaignList->setModel(model);
	ui.stackedWidget->setCurrentWidget(ui.widget_loadCampaign);
};

void CampaignEditor::on_button_addMap_exit_clicked() {
	ui.stackedWidget->setCurrentWidget(ui.widget_campaignEditor);
};
void CampaignEditor::on_button_addMap_load_clicked() {
	QDir directory(".\\maps\\");
	QStringList fileNames = directory.entryList(QDir::Files);
	QModelIndexList selectedIndexes = ui.list_addMap_mapList->selectionModel()->selectedIndexes();
	if (selectedIndexes.isEmpty()) {
		qDebug() << "Not selected";
		return;
	}
	QModelIndex selectedIndex = selectedIndexes.first();
	QVariant selectedItemData = selectedIndex.data(Qt::DisplayRole); // Assuming DisplayRole is used for displaying item data
	int mapNumber = selectedIndex.row();
	addMap(fileNames[mapNumber].toStdString());
	refresh_campaignDisplay();
	ui.stackedWidget->setCurrentWidget(ui.widget_campaignEditor);
};


void CampaignEditor::on_button_campaignEditor_addMap_clicked() {
	QStringListModel* model = new QStringListModel();
	QDir directory(".\\maps\\"); 
	QStringList fileNames = directory.entryList(QDir::Files); 
	int index = 1; 
	for (int i = 0; i < fileNames.size(); i++) {
		fileNames[i] = QString::fromUtf8(std::to_string(index)) + ". " + fileNames[i]; 
		index++; 
	} 
	model->setStringList(fileNames); 
	ui.list_addMap_mapList->setModel(model);
	ui.stackedWidget->setCurrentWidget(ui.widget_addMap);
};
void CampaignEditor::on_button_campaignEditor_removeMap_clicked() {
	QModelIndexList selectedIndexes = ui.list_campaignEditor_mapList->selectionModel()->selectedIndexes();
	if (selectedIndexes.isEmpty()) {
		qDebug() << "Not selected";
		return;
	}
	QModelIndex selectedIndex = selectedIndexes.first();
	QVariant selectedItemData = selectedIndex.data(Qt::DisplayRole); // Assuming DisplayRole is used for displaying item data
	int mapNumber = selectedIndex.row();
	campaign.removeMap(campaign.getMaps()[mapNumber].getName());
	refresh_campaignDisplay();

};


void CampaignEditor::on_button_campaignEditor_changeOrder_clicked() {
	int firstMap = ui.input_campaignEditor_firstMap->value();
	int secondMap = ui.input_campaignEditor_secondMap->value();
	campaign.swapMapOrder(firstMap-1, secondMap-1);
	refresh_campaignDisplay();
};
void CampaignEditor::on_button_campaignEditor_exit_clicked() {
	ui.stackedWidget->setCurrentWidget(ui.widget_mainPage);
};
void CampaignEditor::on_button_campaignEditor_save_clicked() {
	QString campaignName = QString::fromUtf8(campaign.getName().c_str()); 
	QString fileName = ".\\campaigns\\" + campaignName + ".txt";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "Could not open file for writing";
		return; // Return false if file opening failed
	}
	QTextStream out(&file);
	// Writing the name
	out << QString::fromUtf8(campaign.getName()) << "\n";
	out << QString::fromUtf8(to_string(campaign.getMaps().size())) << "\n";
	for (int i = 0; i < campaign.getMaps().size(); i++) {
		out << QString::fromUtf8(campaign.getMaps().at(i).getName()) << ".txt" << "\n";
	}
	file.close();
};

void CampaignEditor::on_button_createNewCampaign_createCampaign_clicked() {
	QString campaignName = ui.input_createNewCampaign_campaignName->text();
	campaign = Campaign(campaignName.toStdString());
	refresh_campaignDisplay();
	ui.stackedWidget->setCurrentWidget(ui.widget_campaignEditor);
};

void CampaignEditor::on_button_loadCampaign_exit_clicked() {
	ui.stackedWidget->setCurrentWidget(ui.widget_mainPage);
};
void CampaignEditor::on_button_loadCampaign_load_clicked() {


	QModelIndexList selectedIndexes = ui.list_loadCampaign_campaignList->selectionModel()->selectedIndexes();
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
	refresh_campaignDisplay();
	ui.stackedWidget->setCurrentWidget(ui.widget_campaignEditor);
};

void CampaignEditor::addMap(string mapFileName) {
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

void CampaignEditor::refresh_campaignDisplay() {
	QStringListModel* model = new QStringListModel();
	QStringList mapList;
	vector<GameMap> maps = campaign.getMaps();
	for (int i = 0; i < maps.size(); i++) {
		mapList.append(QString::fromUtf8(std::to_string(i + 1)) + ". " + QString::fromUtf8(maps[i].getName()));
	}
	model->setStringList(mapList);
	ui.list_campaignEditor_mapList->setModel(model);
};