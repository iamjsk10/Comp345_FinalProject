#pragma once

#include <QWidget>
#include "ui_CharacterEditor.h"
#include "Character.hpp"

class CharacterEditor : public QWidget
{
	Q_OBJECT

public:
	CharacterEditor(QWidget *parent = nullptr);
	~CharacterEditor();
public slots:
	void on_button_mainPage_newCharacter();
	void on_button_mainPage_exit();

	void on_button_newCharacter_createCharacter();
	void on_button_newCharacter_exit();
private:
	Ui::CharacterEditorClass ui;
	Character* character;
};
