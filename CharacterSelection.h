#pragma once

#include <QWidget>
#include "ui_CharacterSelection.h"
#include "Character.hpp"
class CharacterSelection : public QWidget
{
	Q_OBJECT

public:
	CharacterSelection(QWidget *parent = nullptr);
	~CharacterSelection();

signals:
	void characterReturned(const Character &character);
	void back();
public slots:
	void on_button_select_clicked();
	Character getCharacter() const;
	void on_button_createCharacter_clicked();
	void on_button_back_clicked();


private:
	Ui::CharacterSelectionClass ui;
	Character character;
};
