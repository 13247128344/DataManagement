#ifndef DEVICEHTTP_H
#define DEVICEHTTP_H

#include "AbstractDevice.h"
#include <QString>
#include <QList>
#include <QDebug>
#include "DeviceSearchHelper.h"
#include <QSemaphore>
#include <QMap>
#include <QDateTime>

static int iConstruct = 0;
static int iDestruct = 0;

const int RTP_OVER_TCP = 1;
const int RTP_OVER_UDP = 2;

class I8HCache
{
public:
    I8HCache(QString strUsername,
			 QString strPassword,
			 QString strSerialNum,
             QString strIP,
             int iPort,
             int iDeviceType,
             BYTE iVersion,
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

class DeviceHttp : public AbstractDevice
{
	Q_OBJECT

public:
    struct I8H_StreamInfo
    {
        char cSerialNum[64];		//设备序列号
        int iChannel;				//通道号，从1开始；
        CMS_STREAMDATA_CALLBACK pFunc;
        void *pUser;
        CMS_CONNECT_PARSE_StreamType eStreamType;
		DeviceHttp *pDevice;
        /* 回放用参数 */
//        ReplayInfo *replay;
        int playbackChannel;
        /* 回放用参数 */
        I8H_StreamInfo(){
            memset(cSerialNum,0,64);
            iChannel = 0;
            pFunc = NULL;
            pUser = NULL;
            eStreamType = StreamType_Main;
//            replay = NULL;
            playbackChannel = 0;
        }
    };

	DeviceHttp(QString strSerialNum, int rtp_type = RTP_OVER_TCP, QObject *parent = 0);
	~DeviceHttp();

    static void startSearchDevice(CMS_SEARCHDEVICE_CALLBACK func, void *pUser);
    static void stopSearchDevice();

    static bool startService();
    static bool stopService();

	static bool login(QString strUsername, QString strPassword, LoginInfo &sLoginInfo);
	static int logout(HANDLE handle);
	//bool openRealtime(int iChNo, CMS_CONNECT_PARSE_StreamType eStreamType, CMS_STREAMDATA_CALLBACK func, void *pUser) Q_DECL_OVERRIDE;
	//bool closeRealtime(int iChNo, CMS_CONNECT_PARSE_StreamType eStreamType) Q_DECL_OVERRIDE;
	//bool openIntercom(int iChNo, CMS_STREAMDATA_CALLBACK func, void *pUser) Q_DECL_OVERRIDE;
	//bool closeIntercom(int iChNo) Q_DECL_OVERRIDE;
	//bool sendIntercom(CMS_CONNECT_PARSE_StreamHeader header, unsigned char * lpBuffer, unsigned int iBufferSize) Q_DECL_OVERRIDE;
	bool ptzCtrl(int iChNo, CMS_CONNECT_PARSE_PtzCmdType eCmdType, int isStop, int iSpeed) Q_DECL_OVERRIDE;
	bool presetCtrl(int iChNo, int iPresetIndex, CMS_CONNECT_PARSE_PresetCmdType eCmdType) Q_DECL_OVERRIDE;
    bool getCruise(int iChNo, int iCruiseRoute, CMS_CONNECT_PARSE_CruisePoint_Param * &results, int &iParamCount) Q_DECL_OVERRIDE;
    bool setCruise(int iChNo, int iCruiseRoute, int iCruisePoint, CMS_CONNECT_PARSE_CruisePoint_Param request) Q_DECL_OVERRIDE;
	bool deleteCruise(int iChNo, int iCruiseRoute, int iCruisePoint) Q_DECL_OVERRIDE;
	bool clearCruise(int iChNo, int iCruiseRoute) Q_DECL_OVERRIDE;
	bool runCruise(int iChNo, int iCruiseRoute, int isRun) Q_DECL_OVERRIDE;
	bool locusCtrl(int iChNo, int iLocusIndex, int iCmd, int isStop) Q_DECL_OVERRIDE;
	//3D定位
	bool set3D(int iChNo, int iTopX, int iTopY, int iBottomX, int iBottomY) Q_DECL_OVERRIDE;
    bool searchRecord(CMS_CONNECT_PARSE_StreamType eStreamType,
                      time_t beginTime,
                      time_t endTime,
                      unsigned int iRecordType,
                      CMS_CONNECT_PARSE_RecordType_Condition eRecordType_Condition,
                      QList<int> listChNo,
                      CMS_CONNECT_PARSE_SearchRecord_Param * &results,
                      int &iResultsCount) Q_DECL_OVERRIDE;
	/*bool openReplay(ReplayInfo *replay) Q_DECL_OVERRIDE;
	bool closeReplay(ReplayInfo *replay) Q_DECL_OVERRIDE;
	bool ctrlReplay(ReplayInfo *replay, CMS_CONNECT_PARSE_ReplayCmdType eCmdType, int iParam) Q_DECL_OVERRIDE;*/
	bool getAlarmIO(CMS_CONNECT_PARSE_IOType eType, int iIndex, bool &isOpen) Q_DECL_OVERRIDE;
	bool setAlarmIO(CMS_CONNECT_PARSE_IOType eType, int iIndex, bool isOpen) Q_DECL_OVERRIDE;
	bool timeSync() Q_DECL_OVERRIDE;
	bool ctrlUtc(int iChNo, CMS_CONNECT_PARSE_UtcCmdType eCmd) Q_DECL_OVERRIDE;
	bool modifyChName(int iChNo, QString strName) Q_DECL_OVERRIDE;

	bool tranData(char* url, char* inBuffer, int inLen, char* &outBuffer, int &outLen);

	void setConnectionHandle(HANDLE handle) Q_DECL_OVERRIDE;

	void clearRealtimeCount();

	bool getFisheyeAbility(CMS_CONNECT_PARSE_FishEyeAbility &ability);
	bool getFisheyeMode(CMS_CONNECT_PARSE_FishEyeMode &mode);
	bool setFisheyeMode(CMS_CONNECT_PARSE_FishEyeMode &mode);

    static DeviceSearchHelper sta_searchHelper;
    static bool sta_isSearching;
    static QMutex sta_mutexSearching;
    static QMap<HANDLE, I8HCache *> sta_mapCache;
    static QMutex sta_mutexCache;

	I8H_StreamInfo *m_streamInfo;	//最大256通道*2种码流
	QMutex m_mutexStreamInfo;
   
	QMutex m_callbackMutex;

private:
	static QList<QString> getChName(int version, HANDLE handle, QString ip, QString usr, QString pwd);
	static QList<QString> getChIP(int version, HANDLE handle);
 

    I8H_StreamInfo m_intercomStreamInfo;	//对讲流
    QMutex m_mutex_intercomHandle;//加锁
    HANDLE m_intercomHandle;
    
    HANDLE m_alarmHandle;

	int m_rtpType;

	struct RealtimeParam {
		int m_realtimeChannelOpened;//记录当前设备有多少个实时流通道已经被打开了。
		QMutex m_mutex_realtimeChannelOpened;//加锁
		HANDLE m_lRealHandle;	//实时流句柄
		RealtimeParam() {
			m_realtimeChannelOpened = 0;
			m_lRealHandle = 0;
		};
	};

	RealtimeParam *m_realtimeParam;
};

#endif // DEVICEHTTP_H
