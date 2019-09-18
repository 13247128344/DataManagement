#ifndef VPREVMULITWINDOW_H
#define VPREVMULITWINDOW_H

#include <QWidget>
#include "ui_vprevmulitwindow.h"
#include "vPrevWindow.h"
// #include "QMenu"
// #include "QAction"

#define MAX_PREV_WINDOW_NUM 16

namespace Ui {
class vPrevMulitWindow;
}

class vPrevMulitWindow : public QWidget
{
    Q_OBJECT

public:
    explicit vPrevMulitWindow(QWidget *parent = 0);
    ~vPrevMulitWindow();

	void layoutWindows(int iWinNum);
	void showMax();
	void switchWin(vPrevWindow *win1, vPrevWindow *win2);

	int getWinNum();
	void hidePrevWindow();
	void changePrevWindow();

protected:
	bool eventFilter(QObject *target, QEvent *e);

signals:
	void sig_double_clicked(bool, int);

public:
	vPrevWindow *m_pPressWin;
	vPrevWindow *m_pReleaseWin;
	vPrevWindow *m_pCurWin;
	vPrevWindow *m_pWindow[MAX_PREV_WINDOW_NUM];
	int m_iWinNum;
	int m_iFirstWin;
	//true显示最大化为1分屏
	bool m_bShowMax;

private:
	Ui::vPrevMulitWindow *ui;
};

#endif // VPREVMULITWINDOW_H
