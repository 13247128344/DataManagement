#ifndef PREVSCREENNUMCTRL_H
#define PREVSCREENNUMCTRL_H

#include <QWidget>

namespace Ui {
class prevscreennumctrl;
}

class prevscreennumctrl : public QWidget
{
    Q_OBJECT

public:
    explicit prevscreennumctrl(QWidget *parent = 0);
    ~prevscreennumctrl();

	private slots:
	void onSplit1();
	void onSplit4();
	void onSplit8();
	void onSplit12();
	void onSplit16();
	void onSplit36();

signals:
	void onSplitWindow(int);

private:
    Ui::prevscreennumctrl *ui;
};

#endif // PREVSCREENNUMCTRL_H
