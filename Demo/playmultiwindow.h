#ifndef PLAYMULTIWINDOW_H
#define PLAYMULTIWINDOW_H

#include <QWidget>
#include "playframe.h"
#include "ui_mainwindow.h"

#define MAX_WINDOW_NUM 36
namespace Ui {
class playmultiwindow;
}

class playmultiwindow : public QWidget
{
    Q_OBJECT

public:
	playmultiwindow(int winCount = 4, int type = 0);
    ~playmultiwindow();

	void addOtherWindow();
	void setUi(int count, int type);
	void onFrameClose(int winId);
	void onLayoutWindow(int winCount);
	void hideWindow();
	void startRender(int index);
	void mousePressEvent(QMouseEvent *mE);
	void setFocusWin(int curFocus);
	void setFrameName(int index, QString deviceName, int channelNo);
signals:
	void sigFrameClose(int);
private:
	playframe *m_pFrame[MAX_WINDOW_NUM];
	int m_iCurFocusIndex;
	//窗口个数
	int m_iWinCount;
	//当前窗口分屏数
	int m_iCurWinCount;
	//窗口类型
	int m_iType; //0 Preview  1 Playback
	bool m_isMax;//是否是最大化
private:
    Ui::playmultiwindow *ui;
};

#endif // PLAYMULTIWINDOW_H
