#include "CharacterSelection.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QListView>
#include <QMainWindow>
#include <QStackedWidget>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QTextStream>
#include <vector>
#include "CharacterSaveAndLoad.h"
CharacterSelection::CharacterSelection(QWidget *parent)
	: QWidget(parent), character("",1)
{
	ui.setupUi(this);

	QStringListModel* model = new QStringListModel();
	QDir directory(".\\characters\\");
	QStringList fileNames = directory.entryList(QDir::Files);
	int index = 1;
	for (int i = 0; i < fileNames.size(); i++) {
		fileNames[i] = QString::fromUtf8(std::to_string(index)) + ". " + fileNames[i];
		index++;
	}
	model->setStringList(fileNames);
	ui.list_character->setModel(model); 
	connect(ui.button_selectCharacter, SIGNAL(clicked()), this, SLOT(on_button_select_clicked()));
	connect(ui.button_back, SIGNAL(clicked()), this, SLOT(on_button_back_clicked()));

}

CharacterSelection::~CharacterSelection()
{}

void CharacterSelection::on_button_select_clicked() {
	QDir directory(".\\characters\\");
	QStringList fileNames = directory.entryList(QDir::Files);
	QModelIndexList selectedIndexes = ui.list_character->selectionModel()->selectedIndexes();
	if (selectedIndexes.isEmpty()) {
		qDebug() << "Not selected";
		return;
	}
	QModelIndex selectedIndex = selectedIndexes.first();
	QVariant selectedItemData = selectedIndex.data(Qt::DisplayRole); // Assuming DisplayRole is used for displaying item data
	int mapNumber = selectedIndex.row();
	QString fileName = fileNames[mapNumber];
	character = *loadCharacter(fileName.toStdString().substr(0,fileName.size()-4));
	emit characterReturned(character);
};
void CharacterSelection::on_button_back_clicked() {
	emit back();
};

Character CharacterSelection::getCharacter() const {
	return character;
};
void CharacterSelection::on_button_createCharacter_clicked() {
	QString name = ui.input_characterName->text();
	character = Character(name.toStdString(), 1);
	emit characterReturned(character);
};