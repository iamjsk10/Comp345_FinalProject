#pragma once

#include "Campaign.h"
#include "GameMap.hpp"
#include "ui_CampaignSelection.h"
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
#include <QWidget>
#include <vector>

class CampaignSelection : public QWidget
{
	Q_OBJECT

public:
	CampaignSelection(QWidget *parent = nullptr);
	~CampaignSelection();
signals:
	void campaignReturned(const Campaign& campaign);
	void closing();
public slots:
	void on_button_startGame_clicked();
	void on_button_back_clicked();
	Campaign getCampaign() const;
	void addMap(string mapFileName);

	std::shared_ptr<Campaign> getCampaignss() const;
private:
	Ui::CampaignSelectionClass ui;
	Campaign campaign;
};
