#pragma once

#include "Campaign.h"
#include "GameMap.hpp"
#include "MapCell.hpp"
#include "ui_CampaignEditor.h"
#include <QAbstractListModel>
#include <QCoreApplication>
#include <QDebug>
#include <Qdir>
#include <QFile>
#include <QListView>
#include <QMainWindow>
#include <QStackedWidget>
#include <QStandardItemModel>
#include <QStringlist>
#include <QStringListModel>
#include <QTextStream>
#include <vector>
class CampaignEditor : public QMainWindow
{
	Q_OBJECT

public:
	CampaignEditor(QWidget *parent = nullptr);
	~CampaignEditor();

public slots:
	void on_button_mainPage_exit_clicked();
	void on_button_mainPage_newCampaign_clicked();
	void on_button_mainPage_loadCampaign_clicked();

	void on_button_addMap_exit_clicked();
	void on_button_addMap_load_clicked();
	
	void on_button_campaignEditor_addMap_clicked();
	void on_button_campaignEditor_removeMap_clicked();
	void on_button_campaignEditor_changeOrder_clicked();
	void on_button_campaignEditor_exit_clicked();
	void on_button_campaignEditor_save_clicked();
	
	void on_button_createNewCampaign_createCampaign_clicked();

	void on_button_loadCampaign_exit_clicked();
	void on_button_loadCampaign_load_clicked();

private:
	Ui::CampaignEditorClass ui;
	Campaign campaign;
protected:
	void refresh_campaignDisplay();
	void addMap(string mapFileName);
};
