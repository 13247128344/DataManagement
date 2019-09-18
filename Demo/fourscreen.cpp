#include "fourscreen.h"
#include "ui_fourscreen.h"

fourscreen::fourscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fourscreen)
{
    ui->setupUi(this);
}

fourscreen::~fourscreen()
{
    delete ui;
}

HWND fourscreen::getHwnd()
{
	int Id = ui->widget->winId();
	HWND hwnd = (HWND)Id;
	return hwnd;
}