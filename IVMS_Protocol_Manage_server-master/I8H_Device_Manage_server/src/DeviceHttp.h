#ifndef DEVICEHTTP_H
#define DEVICEHTTP_H

#include <QString>
#include <QList>
#include <QDebug>
#include <QSemaphore>
#include <QMap>
#include <QDateTime>
#include "QMutex"
#include "public.h"

#include "cms_connect_parse_common.h"

#ifndef HANDLE
typedef void *HANDLE;
#endif



#define LOCUS_SET 1
#define LOCUS_RUN 2
#define LOCUS_CLEAR 3

static int iConstruct = 0;
static int iDestruct = 0;

const int RTP_OVER_TCP = 1;
const int RTP_OVER_UDP = 2;


struct LoginInfo
{
	HANDLE handle;
	QString strSerialNum;
	QString strDeviceIP;
	int iDevicePort;
	CMS_CONNECT_PARSE_DeviceType eDeviceType;
	int iChannelCount;
	int iAlarmInCount;
	int iAlarmOutCount;
	QVector<QString> vecChannelName;

	LoginInfo()
	{
		handle = NULL;
		strSerialNum = "";
		strDeviceIP = "";
		iDevicePort = 0;
		eDeviceType = DeviceType_IPC;
		iChannelCount = 0;
		iAlarmInCount = 0;
		iAlarmOutCount = 0;
	}
};



class I8HCache
{
public:
	I8HCache(QString strUsername,
		QString strPassword,
		QString strSerialNum,
		QString strIP,
		int iPort,
		int iDeviceType,
		unsigned char iVersion,
		int iChannelCount);
	~I8HCache();

	const QString m_strUsername;
	const QString m_strPassword;
	const QString m_strSerialNum;   //设备序列号
	const QString m_strDeviceIP;    //设备IP
	const int m_iPort;              //设备端口
	const int m_eDeviceType;        //设备类型
	const int m_iVersion;           //设备版本
	const int m_iChannelCount;      //设备视频通道总数
	unsigned long m_hConnection;    //连接句柄
};

class DeviceHttp
{

public:
    struct I8H_StreamInfo
    {
        char cSerialNum[64];		//设备序列号
        int iChannel;				//通道号，从1开始；
        //CMS_STREAMDATA_CALLBACK pFunc;
        void *pUser;
       
		DeviceHttp *pDevice;
        /* 回放用参数 */
        //ReplayInfo *replay;
    };


	




	DeviceHttp(QString strSerialNum, int rtp_type = RTP_OVER_TCP, QObject *parent = 0);
	~DeviceHttp();

	static void setCAllback(CMS_MESSAGEINFO_CALLBACK pFunc);
    //static void startSearchDevice(CMS_SEARCHDEVICE_CALLBACK func, void *pUser);
    static void stopSearchDevice();

    static bool startService();
    static bool stopService();

	static bool login(QString strUsername, QString strPassword, LoginInfo &sLoginInfo);
	static int logout(HANDLE handle);
	
	bool ptzCtrl(int iChNo, CMS_CONNECT_PARSE_PtzCmdType eCmdType, int isStop, int iSpeed) ;
	bool presetCtrl(int iChNo, int iPresetIndex, CMS_CONNECT_PARSE_PresetCmdType eCmdType) ;
	bool getCruise(int iChNo, int iCruiseRoute, CMS_CONNECT_PARSE_CruisePoint_Param * &results, int &iParamCount) ;
	bool setCruise(int iChNo, int iCruiseRoute, int iCruisePoint, CMS_CONNECT_PARSE_CruisePoint_Param request) ;
	bool deleteCruise(int iChNo, int iCruiseRoute, int iCruisePoint) ;
	bool clearCruise(int iChNo, int iCruiseRoute) ;
	bool runCruise(int iChNo, int iCruiseRoute, int isRun) ;
	bool locusCtrl(int iChNo, int iLocusIndex, int iCmd, int isStop) ;
	//3D定位
	bool set3D(int iChNo, int iTopX, int iTopY, int iBottomX, int iBottomY) ;
	bool searchRecord(CMS_CONNECT_PARSE_StreamType eStreamType,
		time_t beginTime,
		time_t endTime,
		unsigned int iRecordType,
		CMS_CONNECT_PARSE_RecordType_Condition eRecordType_Condition,
		QList<int> listChNo,
		CMS_CONNECT_PARSE_SearchRecord_Param * &results,
		int &iResultsCount) ;
	
	bool tranData(char* url, char* inBuffer, int inLen, int inOverTime, int inNeedSize, char* &outBuffer, int &outLen);
	void setConnectionHandle(HANDLE handle);
	const HANDLE connectionHandle();

	static QMap<HANDLE, I8HCache *> sta_mapCache;
	static QMutex sta_mutexCache;
	static QHash<QString, QSharedPointer<DeviceHttp> > sta_hashInstance;
private:

	static QList<QString> getChName(int version, HANDLE handle, QString ip, QString usr, QString pwd);
	static QList<QString> getChIP(int version, HANDLE handle);
	


	HANDLE m_alarmHandle;

	int m_rtpType;
	const QString m_strSerialNum;
	bool m_isOnline;
	HANDLE m_hConnection;
	
};

#endif // DEVICEHTTP_H
