#include "prevscreennumctrl.h"
#include "ui_prevscreennumctrl.h"

prevscreennumctrl::prevscreennumctrl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::prevscreennumctrl)
{
    ui->setupUi(this);
	connect(ui->btn_screenSplit1, SIGNAL(clicked()), this, SLOT(onSplit1())); //1分屏
	connect(ui->btn_screenSplit9, SIGNAL(clicked()), this, SLOT(onSplit8())); //8分屏
	connect(ui->btn_screenSplit16, SIGNAL(clicked()), this, SLOT(onSplit12())); //12分屏
	connect(ui->btn_screenSplit25, SIGNAL(clicked()), this, SLOT(onSplit16())); //16分屏
}

prevscreennumctrl::~prevscreennumctrl()
{
    delete ui;
}

void prevscreennumctrl::onSplit1()
{
	emit onSplitWindow(1);
}

void prevscreennumctrl::onSplit4()
{
	emit onSplitWindow(4);
}

void prevscreennumctrl::onSplit8()
{
	emit onSplitWindow(9);
}

void prevscreennumctrl::onSplit12()
{
	emit onSplitWindow(16);
}

void prevscreennumctrl::onSplit16()
{
	emit onSplitWindow(25);
}

void prevscreennumctrl::onSplit36()
{
	emit onSplitWindow(36);
}