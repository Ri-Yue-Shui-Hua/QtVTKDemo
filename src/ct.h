#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ct.h"

class ct : public QMainWindow
{
	Q_OBJECT

public:
	ct(QWidget *parent = Q_NULLPTR);

private:
	Ui::ctClass ui;

private slots:
	void on_actionOpen_triggered();
	void on_action3D_triggered();
	void on_actionQuit_triggered();
};
