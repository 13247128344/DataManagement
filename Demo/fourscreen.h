#ifndef FOURSCREEN_H
#define FOURSCREEN_H

#include <QWidget>

namespace Ui {
class fourscreen;
}

class fourscreen : public QWidget
{
    Q_OBJECT

public:
    explicit fourscreen(QWidget *parent = 0);
    ~fourscreen();

	HWND getHwnd();
private:
    Ui::fourscreen *ui;
};

#endif // FOURSCREEN_H
