#ifndef LOG_H
#define LOG_H

#include <QWidget>
#include <QMap>
#include<QMouseEvent>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include "QTranslator"
#include "alarminfowidget.h"

namespace Ui {
class Log;
}

typedef struct
{
	bool bAutoLogin;  //自动登录
	bool bRememberPsw; //记住密码 //add by HG_Panda
	QString strCapPath;  //抓图路径
	QString strDownloadPath;  //录像下载路径
	QString strExportLogPath;  //导出日志路径
	int iIntervalPreRoll;  //预览轮巡间隔时间
						   //int iIntervalTVWallRoll;  //电视墙轮巡间隔时间
	QString strAlarmSound[9];  //0--Alarm in;1--Motion detect;2--Shelter;3--Video loss;
	int iWindowScale;  //0--Full screen;1--4:3;2--16:9;
	QString strVersion;  //版本号
	int iEnableWeb;
	int iHttpPort;
	int iHttpsPort;
	int iAutoStream;
	int iStreamMode;
	QString strStreamSplit;
}StruLocalCfg;

typedef enum
{
	Type_UserLogin = 1,		//用户登录	iParam[0]为0表示用户注销，1表示用户登录
	Type_DeviceMgr = 2,		//设备管理  cParam为设备名称；iParam[0]为0表示删除设备，1表示添加设备，2表示修改设备
	//LogType_RecordMgr = 0x04,		//录像管理	cParam为设备名称；iParam[0]表示通道号；iParam[1]为0表示停止录像，1表示开始录像
	Type_LinkageRule = 8,		//联动规则	cParam为规则名称；iParam[0]为0表示删除规则，1表示添加规则，2表示修改规则
}msgType;

class Log : public QWidget
{
    Q_OBJECT

public:
    static Log* getLog(QWidget* parent);
     Log(QWidget *parent = 0);
    ~Log();

private:
    static Log* stra_logs;

private slots:
    void onBtnRetrieve();//查询
    void onBtnExport();//导出
    void onBtnFirst();//第一页
    void onBtnPrevious();//前一页
    void onBtnNext();//下一页
    void onBtnLast();//最后一页
//	void oneProcessFinished(QNetworkReply *reply);
//	void scanUrlIsok();

private:
    int m_iCurPage;
    int m_iPageCount;
    int m_iRowCount;
    int m_iCount;
    bool m_move;
    QPoint m_startPoint;
    QPoint m_windowPoint;
	QTranslator *translator;
	AlarmInfoWidget *alarm;

signals:
	void sendInsertEvent(QString);

protected:
    void resizeEvent(QResizeEvent * event);

public:
	void initStyle();
    void setUi();
    void setUserTable();
    void setButtons(int iCurPage);//设置按钮可用状态
    bool getLogs(int iCurPage);//获取日志
    void exportLogs();//导出日志
	//void insertEvent(QString eventInfo);

private:
    Ui::Log *ui;
	QNetworkAccessManager *manage;
};

#endif // LOG_H
