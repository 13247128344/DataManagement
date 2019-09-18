#ifndef ENABLEDCONTROL_H
#define ENABLEDCONTROL_H

#include <QWidget>

namespace Ui {
class EnabledControl;
}

class EnabledControl : public QWidget
{
    Q_OBJECT

public:
    explicit EnabledControl(QWidget *parent = 0);
    ~EnabledControl();
    Ui::EnabledControl *ui;
};

#endif // ENABLEDCONTROL_H
