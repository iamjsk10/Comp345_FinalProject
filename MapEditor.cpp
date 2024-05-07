#include "MapEditor.h"
#include <windows.h>
#include <QListView>
#include <QStandardItemModel>
#include <QDir> 

MapEditor::MapEditor(QWidget* parent)
	: QMainWindow(parent), map()
{
	ui.setupUi(this);
	connect(ui.button_mainPage_newMap, SIGNAL(clicked()), this, SLOT(on_button_mainPage_newMap_clicked()));
	connect(ui.button_mainPage_loadMap, SIGNAL(clicked()), this, SLOT(on_button_mainPage_loadMap_clicked()));
	connect(ui.button_mainPage_exit, SIGNAL(clicked()), this, SLOT(on_button_mainPage_exit_clicked()));
	connect(ui.button_mapEditor_reset, SIGNAL(clicked()), this, SLOT(on_button_mapEditor_reset_clicked()));
	connect(ui.button_mapEditor_save, SIGNAL(clicked()), this, SLOT(on_button_mapEditor_save_clicked()));
	connect(ui.button_loadMap_load, SIGNAL(clicked()), this, SLOT(on_button_loadMap_load_clicked()));
	connect(ui.button_loadMap_exit, SIGNAL(clicked()), this, SLOT(on_button_loadMap_exit_clicked())); 

	ui.stackedWidget->setCurrentWidget(ui.widget_mainPage);
}

MapEditor::~MapEditor()
{}

void MapEditor::on_button_mainPage_newMap_clicked() {
	ui.stackedWidget->setCurrentWidget(ui.widget_createNewMap);
};
void MapEditor::on_button_mainPage_loadMap_clicked() {
	QStringListModel *model = new QStringListModel();
	QDir directory(".\\maps\\"); 
	QStringList fileNames = directory.entryList(QDir::Files); 
	int index = 1;
	for (int i = 0; i < fileNames.size(); i++) {
		fileNames[i] = QString::fromUtf8(std::to_string(index)) + ". " + fileNames[i];
		index++;
	}
	model->setStringList(fileNames);  
	ui.list_loadMap_mapList->setModel(model);
	ui.stackedWidget->setCurrentWidget(ui.widget_loadMap);
};

void MapEditor::on_button_loadMap_exit_clicked() {
	ui.stackedWidget->setCurrentWidget(ui.widget_mainPage);
};

void MapEditor::on_button_loadMap_load_clicked() {
	QDir directory(".\\maps\\"); 
	QStringList fileNames = directory.entryList(QDir::Files); 
	QModelIndexList selectedIndexes = ui.list_loadMap_mapList->selectionModel()->selectedIndexes();
	if (selectedIndexes.isEmpty()) {
		qDebug() << "Not selected";
		return;
	}
	QModelIndex selectedIndex = selectedIndexes.first();
	QVariant selectedItemData = selectedIndex.data(Qt::DisplayRole); // Assuming DisplayRole is used for displaying item data
	int mapNumber = selectedIndex.row();
	QString fileName = ".\\maps\\" + fileNames[mapNumber];
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
	this->map = loadedMap;
	file.close();
	refresh_mapDisplay();
	ui.stackedWidget->setCurrentWidget(ui.widget_mapEditor);
};


void MapEditor::on_button_mainPage_exit_clicked() {
	close();
};

void MapEditor::on_button_createNewMap_createMap_clicked() {
	
	QString newMapName = ui.input_createNewMap_mapName->text();
	int mapWidth = ui.input_createNewMap_mapWidth->value();
	int mapHeight = ui.input_createNewMap_mapHeight->value();
	if (mapWidth == 0 || mapHeight == 0 || newMapName == "") {
		return;
	}
	map = GameMap(mapWidth, mapHeight);
	map.setName(newMapName.toStdString());
	qDebug()<< "Map Name is " << newMapName;
	refresh_mapDisplay();
	ui.stackedWidget->setCurrentWidget(ui.widget_mapEditor);
};

void MapEditor::on_button_mapEditor_reset_clicked() {
	// Resetting every value for map
	for (int i = 0; i < map.getWidth(); i++) {
		for (int j = 0; j < map.getHeight(); j++) {
			map.setCell(i, j, CellType::Empty);
		}
	}
	map.setStartX(0);
	map.setStartY(0);
	map.setEndX(0);
	map.setEndY(0);

	//Resetting the editor (for fun)
	ui.input_mapEditor_emptyCellColumn->setValue(0);
	ui.input_mapEditor_emptyCellRow->setValue(0);
	ui.input_mapEditor_placeWallRow->setValue(0);
	ui.input_mapEditor_placeWallColumn->setValue(0);
	ui.input_mapEditor_placeObjectColumn->setValue(0);
	ui.input_mapEditor_placeObjectRow->setValue(0);

	ui.input_mapEditor_startingColumn->setValue(0);
	ui.input_mapEditor_startingRow->setValue(0);
	ui.input_mapEditor_endingColumn->setValue(0);
	ui.input_mapEditor_endingRow->setValue(0);

};
void MapEditor::on_button_mapEditor_exit_clicked() const {
	ui.stackedWidget->setCurrentWidget(ui.widget_mainPage);
};




void MapEditor::on_button_mapEditor_save_clicked() {
	QString mapName = QString::fromUtf8(map.getName().c_str());
	QString fileName = ".\\maps\\" + mapName+".txt";
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "Could not open file for writing";
		return; // Return false if file opening failed
	}
	QTextStream out(&file);

	out << QString::fromUtf8(map.getName()) << "\n";
	out << QString::fromUtf8(std::to_string(map.getWidth())) << "\n";
	out << QString::fromUtf8(std::to_string(map.getHeight())) << "\n";
	out << QString::fromUtf8(std::to_string(map.getStartX())) + ","
		<< QString::fromUtf8(std::to_string(map.getStartY())) + ","
		<< QString::fromUtf8(std::to_string(map.getEndX())) + ","
		<< QString::fromUtf8(std::to_string(map.getEndY())) << "\n";
	std::vector<std::vector <MapCell>> grid = map.getGrid();
	//Writing the map (Non-binary, human readable cause it's easier
	for (std::vector<MapCell> rows : grid) {
		for (MapCell cell : rows) {
			CellType type = cell.getType();
			switch (type) {
			case CellType::Empty:
				out << "E,";
				break;
			case CellType::character:
				out << "C,";
				break;
			case CellType::chest:
				out << "T,";
				break;
			case CellType::Wall:
				out << "W,";
				break;
			}
		}
		out << "\n";
	}
	file.close();

};

// The location is not checked here (not sure if 1-index or 0-index)
void MapEditor::on_button_mapEditor_placeWall_clicked() {
	int x = ui.input_mapEditor_placeWallColumn->value();
	int y = ui.input_mapEditor_placeWallRow->value();
	map.setCell(x, y, CellType::Wall);
	refresh_mapDisplay();
};
void MapEditor::on_button_mapEditor_placeObject_clicked() {
	int x = ui.input_mapEditor_placeObjectColumn->value();
	int y = ui.input_mapEditor_placeObjectRow->value();
	map.setCell(x, y, CellType::chest);
	refresh_mapDisplay();
};
void MapEditor::on_button_mapEditor_emptyCell_clicked() {
	int x = ui.input_mapEditor_placeObjectColumn->value();
	int y = ui.input_mapEditor_placeObjectRow->value();
	map.setCell(x, y, CellType::Empty);
	refresh_mapDisplay();
};


void MapEditor::refresh_mapDisplay() {
	ui.widget_mapEditor_map->setGameMap(&map);
	ui.widget_mapEditor_map->raise(); // Brings the widget to the front
	ui.widget_mapEditor_map->show();
	// Adding the map here (refresh every time something is done)
};