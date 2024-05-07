#pragma once

#include "GameMap.hpp"
#include "MapCell.hpp"
#include "ui_MapEditor.h"
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QListView>
#include <QMainWindow>
#include <QStackedWidget>
#include <QStringListModel>
#include <QTextStream>
#include <vector>
#include "gamemapwidget.h"

class MapEditor : public QMainWindow
{
	Q_OBJECT

public:
	MapEditor(QWidget *parent = nullptr);
	~MapEditor();

private:
	Ui::MapEditorClass ui;
	GameMap map;
	GameMapWidget mapWidget;
public slots:
	void on_button_mainPage_newMap_clicked();
	void on_button_mainPage_loadMap_clicked();
	void on_button_mainPage_exit_clicked(); 
	void on_button_createNewMap_createMap_clicked();

	void on_button_loadMap_load_clicked();
	void on_button_loadMap_exit_clicked();

	void on_button_mapEditor_save_clicked();
	void on_button_mapEditor_reset_clicked();
	void on_button_mapEditor_exit_clicked() const;
	void on_button_mapEditor_placeWall_clicked();
	void on_button_mapEditor_placeObject_clicked();
	void on_button_mapEditor_emptyCell_clicked();
protected:
	void refresh_mapDisplay();

};
