#pragma once

#include <QWidget>
#include "ui_GameLogger.h"

class GameLogger : public QWidget
{
	Q_OBJECT

public:
	GameLogger(QWidget *parent = nullptr);
	~GameLogger();

private:
	Ui::GameLoggerClass ui;

};
