#include "enabledcontrol.h"
#include "ui_enabledcontrol.h"

EnabledControl::EnabledControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnabledControl)
{
    ui->setupUi(this);
}

EnabledControl::~EnabledControl()
{
    delete ui;
}
