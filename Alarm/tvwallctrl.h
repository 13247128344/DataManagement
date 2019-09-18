#ifndef TVWALLCTRL_H
#define TVWALLCTRL_H

#include <QWidget>

namespace Ui {
class TvwallCtrl;
}

class TvwallCtrl : public QWidget
{
    Q_OBJECT

public:
    explicit TvwallCtrl(QWidget *parent = 0);
    ~TvwallCtrl();
    Ui::TvwallCtrl *ui;
};

#endif // TVWALLCTRL_H
