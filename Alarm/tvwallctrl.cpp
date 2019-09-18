#include "tvwallctrl.h"
#include "ui_tvwallctrl.h"

TvwallCtrl::TvwallCtrl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TvwallCtrl)
{
    ui->setupUi(this);
	ui->btnDelete->setCursor(Qt::PointingHandCursor);
	ui->btnEnable->setCursor(Qt::PointingHandCursor);
	ui->btnModify->setCursor(Qt::PointingHandCursor);
}

TvwallCtrl::~TvwallCtrl()
{
    delete ui;
}
