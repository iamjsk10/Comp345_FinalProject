#include "CharacterEditor.h"
#include <QListView>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QDir> 

CharacterEditor::CharacterEditor(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this); 
	connect(ui.button_mainPage_newCharacter, SIGNAL(clicked()), this, SLOT(on_button_mainPage_newCharacter_clicked()));
	connect(ui.button_mainPage_exit, SIGNAL(clicked()), this, SLOT(on_button_mainPage_exit_clicked()));
	connect(ui.button_newCharacter_createCharacter, SIGNAL(clicked()), this, SLOT(on_button_newCharacter_createCharacter()));
	connect(ui.button_newCharacter_exit, SIGNAL(clicked()), this, SLOT(on_button_newCharacter_exit()));

}

CharacterEditor::~CharacterEditor()
{}
void CharacterEditor::on_button_mainPage_newCharacter() {
	ui.stackedWidget->setCurrentWidget(ui.widget_newCharacter);
}
void CharacterEditor::on_button_mainPage_exit() {
	hide();
};

void CharacterEditor::on_button_newCharacter_createCharacter() {
	QString name = ui.input_newCharacter_name->text();
	Character* newCharacter = new Character(name.toStdString(),1);
	//saveCharacter(newCharacter);
	ui.stackedWidget->setCurrentWidget(ui.widget_mainPage);
	
};
void CharacterEditor::on_button_newCharacter_exit() {
	ui.stackedWidget->setCurrentWidget(ui.widget_mainPage);
};