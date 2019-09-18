#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
#include <QtWidgets>
#endif

#include <QMainWindow>
#include "inc/I8H_SDK.h"
#include "prevscreennumctrl.h"
#include "playmultiwindow.h"
#include <string.h>

#define  LHT_SYNCCLIENT_EN_FILE  "cloudbox_en_CN.ts" 
#define  LHT_SYNCCLIENT_ZH_FILE  "cloudbox_zh_CN.ts" 
namespace Ui {
class MainWindow;
}

typedef struct _tagBasicInfo
{
    WORD wStreamType ;
    WORD wChanNum;
    HANDLE hUserId;
    HANDLE hRealPlay;
	HANDLE hReplay;

}I8H_BASIC_INFO, *LPI8H_BASIC_INFO;

class MainWindow : public QMainWindow 
{
    Q_OBJECT

public:
	void setTranslator(QTranslator* translator);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

     //PTZ控制
     void on_LoginBtn_clicked();
     void on_LogoutBtn_clicked();
     void on_downBtn_clicked();
     void on_rightBtn_clicked();
     void on_upBtn_clicked();
     void on_leftBtn_clicked();
     void on_stopBtn_clicked();
     void on_playBtn_clicked();
     void on_captureBtn_clicked();
	 void on_reBootBtn_clicked();
     void on_alarmBtn_clicked();
     void on_closeAlarmBtn_clicked();
     void on_pushButton_clicked();
     void on_pushButton_2_clicked();

     void on_comboBox_activated(const QString &arg1);
     void on_pushButton_3_clicked();
     void on_pushButton_5_clicked();
     void on_pushButton_6_clicked();
     void on_pushButton_7_clicked();

     void on_pushButton_4_clicked();
	 std::string getDeskTop();

private:
	QWidget *w;
    Ui::MainWindow *ui;
    BOOL m_init;
    DWORD m_dwPort;
    LPI8H_BASIC_INFO m_ipClientInfor;
	LPI8H_CHANNEL_INFO m_Channel;
    QString userName;
    QString passowrd;
    int count = 0;
	HANDLE hPlay = NULL;
	int screenNum = 16;
	

	bool videoMax;
	QMenu *videoMenu;
	int videoCount;
	QString videoType;
	QList<QLabel *> widgets;
	QTranslator *translator;
	prevscreennumctrl *m_pPrevScreenNumCtrl;
	playmultiwindow *m_pMultiWindow;
	
    BOOL initSDK();
	BOOL isPlay();
	static VOID CALLBACK captureCbFun(long lPort, char *pBuf, long nSize, long nWidth, long nHeight, long nStamp, long nReserved1, long nReserved2);
	static VOID CALLBACK fStreamDataCallBack(HANDLE hHandle, DWORD dwOption, DWORD dwDataType, BYTE *lpBuffer, DWORD dwBufferSize, LPVOID lpUser);
};

#endif // MAINWINDOW_H
