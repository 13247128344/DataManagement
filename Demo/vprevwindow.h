#ifndef VPREVWINDOW_H
#define VPREVWINDOW_H

#include <QWidget>
#include "ui_vprevmulitwindow.h"
// #include "QAbstractItemModel"
// #include "public.h"
// #include "I8_PlaySDK.h"

class QTimer;
namespace Ui {
class vPrevWindow;
}

class vPrevWindow : public QWidget
{
    Q_OBJECT

public:
	vPrevWindow(QWidget *parent = 0);
	vPrevWindow(QWidget *parent, bool bWidth, int iModeWidth, int iModeHeight);
    ~vPrevWindow();

	void update();
	void getWinID();
	void hideWidget();
	void showWidget();
	void showTitle();
	void restoreDefaults();
	void adjustVideoArea();
	void showFrame(bool bSel);
	void getPrevMulitWindow(void *pMulitWindow);

protected:
	void mouseDoubleClickEvent(QMouseEvent *e);
	//bool eventFilter(QObject *target, QEvent *e);
	void resizeEvent(QResizeEvent * event);

signals:
	void sig_sendfacepic_message(QString strSerialNum, char *picBuf, int picSize, char*recBuf, int recSize);
	void sig_pre_close(int);

	public slots:
	void slot_change_winsize();
	void slot_close();

public:
	//播放端口
	int iPlayPort;
	HWND hWndHandle;
	int m_iMainHandle;
	int m_iSubHandle;
	int m_iIndex;
	int m_iDeviceType;
	//Is video playing?
	bool m_bPlay;
	bool m_bSpilt;
	QModelIndex m_modelIndex;
	QString m_strSerialNumber;
	//窗口播放通道号
	int m_iChannelNo;
	//width is standard
	bool m_bWidth;
	//mode of show width/height
	int m_iModeWidth;
	int m_iModeHeight;
	//window FrameView *p
	void *m_pMulitWindow;
	bool m_bPressed;
	QPoint m_ptOriginPos;
	//是否开启3D定位，手动画框，在faceSelect里有开启
	bool m_b3DPos;
	QPoint m_3DPos;
	QPoint m_3DMovePos;
	long iWidth;
	long iHeight;
	int iZoomCount;

private:
    Ui::vPrevWindow *ui;
};

#endif // VPREVWINDOW_H
