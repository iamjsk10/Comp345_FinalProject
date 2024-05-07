#pragma once

#include <QMainWindow>
#include "ui_ItemEditor.h"
#include "ItemSaveAndLoad.h"
class ItemEditor : public QMainWindow
{
	Q_OBJECT

public:
	ItemEditor(QWidget *parent = nullptr);
	~ItemEditor();

public slots:
	void on_button_mainPage_exit_clicked();
	void on_button_mainPage_newItem_clicked();

	void on_button_createItem_createAndSave_clicked();
	void on_button_createItem_exit_clicked();

private:
	Ui::ItemEditorClass ui;
};
