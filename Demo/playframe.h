#ifndef PLAYFRAME_H
#define PLAYFRAME_H

#include <QWidget>
#include "inc/I8H_SDK.h"
#include "inc/I8_PlaySDK.h"

namespace Ui {
class playframe;
}

class playframe : public QWidget
{
    Q_OBJECT

public:
	playframe(QWidget *parent = 0, int index = 0, int type = 0);
    ~playframe();
	void startRender();
	void initWndRender(int type);
	void getWinId();
	int inputData(char *buf, int len);
	void stopRender();
	void unInitWndRender();
	void setChannelName(QString deviceName, int channelNo);//设置名称
signals:
	void sigCloseWin(int winId);

private:
    Ui::playframe *ui;
	int m_iPort;
	int m_iType;
	HWND m_hWndHandle;
	QString m_strDeviceName;//设备名
	int m_iChannel;//通道号
};

#endif // PLAYFRAME_H
