/************************************************************************
*
*   文件名： AbstractDevice.h
*
*   文件描述：设备的抽象，定义各协议的设备公共接口
*
*   创建人：Sunx, 2015年6月17日
*
*   版本号：1.0
*
*   修改记录：
*
************************************************************************/


#ifndef ABSTRACTDEVICE_H
#define ABSTRACTDEVICE_H

//加这个是为了解决GB28181协议库头文件winsock版本不兼容报错的问题
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <QObject>
#include "cms_connect_parse_common.h"
//#include "ReplayInfo.h"
#include "cms_connect_server_common.h"
#include <QMap>
#include <QVector>

#define LOCUS_SET 1
#define LOCUS_RUN 2
#define LOCUS_CLEAR 3

class AbstractDevice : public QObject
{
	Q_OBJECT

public:
	struct CallbackParam
	{
		CMS_STREAMDATA_CALLBACK pFunc;
		void *pUser;

		CallbackParam()
		{
			pFunc = NULL;
			pUser = NULL;
		}
		CallbackParam(const CallbackParam& other)
		{
			this->pFunc = other.pFunc;
			this->pUser = other.pUser;
		}
	};

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

	virtual ~AbstractDevice();

	//以下须重载overload
	static bool login(QString strUsername, QString strPassword, LoginInfo &sLoginInfo);

	//返回设备通道个数
	static int logout(HANDLE handle);

    static void startSearchDevice(CMS_SEARCHDEVICE_CALLBACK func, void *pUser);
    static void stopSearchDevice();

	//以下须重写override
	//virtual bool openRealtime(int iChNo, CMS_CONNECT_PARSE_StreamType eStreamType, CMS_STREAMDATA_CALLBACK func, void *pUser) = 0;
	//virtual bool closeRealtime(int iChNo, CMS_CONNECT_PARSE_StreamType eStreamType) = 0;
	//virtual bool openIntercom(int iChNo, CMS_STREAMDATA_CALLBACK func, void *pUser) = 0;
	//virtual bool closeIntercom(int iChNo) = 0;
	//virtual bool sendIntercom(CMS_CONNECT_PARSE_StreamHeader header, unsigned char * lpBuffer, unsigned int iBufferSize) = 0;
	virtual bool ptzCtrl(int iChNo, CMS_CONNECT_PARSE_PtzCmdType eCmdType, int isStop, int iSpeed) = 0;
	virtual bool set3D(int iChNo, int iTopX, int iTopY, int iBottomX, int iBottomY) = 0;
	virtual bool presetCtrl(int iChNo, int iPresetIndex, CMS_CONNECT_PARSE_PresetCmdType eCmdType) = 0;
    virtual bool getCruise(int iChNo, int iCruiseRoute, CMS_CONNECT_PARSE_CruisePoint_Param * &results, int &iParamCount) = 0;
    /*
     * 从巡航路径里删除一个预置点
     * iCruisePoint:巡航点序号,删除巡航点时,需要先获取巡航信息,删除点只能在尾部删除     *
     */
    virtual bool setCruise(int iChNo, int iCruiseRoute, int iCruisePoint, CMS_CONNECT_PARSE_CruisePoint_Param request) = 0;

	virtual bool deleteCruise(int iChNo, int iCruiseRoute, int iCruisePoint) = 0;
	virtual bool clearCruise(int iChNo, int iCruiseRoute) = 0;
	virtual bool runCruise(int iChNo, int iCruiseRoute, int isRun) = 0;
	virtual bool locusCtrl(int iChNo, int iLocusIndex, int iCmd, int isStop) = 0;
    virtual bool searchRecord(CMS_CONNECT_PARSE_StreamType eStreamType,
                              time_t beginTime,
                              time_t endTime,
                              unsigned int iRecordType,
                              CMS_CONNECT_PARSE_RecordType_Condition eRecordType_Condition,
                              QList<int> listChNo,
                              CMS_CONNECT_PARSE_SearchRecord_Param * &results,
                              int &iResultsCount) = 0;
	//virtual bool openReplay(ReplayInfo *replay) = 0;
	//virtual bool closeReplay(ReplayInfo *replay) = 0;
	//virtual bool ctrlReplay(ReplayInfo *replay, CMS_CONNECT_PARSE_ReplayCmdType eCmdType, int iParam) = 0;
	virtual bool getAlarmIO(CMS_CONNECT_PARSE_IOType eType, int iIndex, bool &isOpen) = 0;
	virtual bool setAlarmIO(CMS_CONNECT_PARSE_IOType eType, int iIndex, bool isOpen) = 0;
	virtual bool timeSync() = 0;
	virtual bool ctrlUtc(int iChNo, CMS_CONNECT_PARSE_UtcCmdType eCmd) = 0;
	virtual bool modifyChName(int iChNo, QString strName) = 0;

    virtual void setConnectionHandle(HANDLE handle);
    virtual const HANDLE connectionHandle();

	//以下不需处理，继承即可
	void freeMemory(void *pMemory);
	void setAlarmCallback(CMS_ALARM_MESSAGE_CALLBACK func, void *pUser);
    const QString serialNum();
	const bool isOnline();
	void setOnline(const bool bOnline);

	CMS_ALARM_MESSAGE_CALLBACK m_pAlarmCallbackFunc;
	void *m_pAlarmCallbackUser;

	CallbackParam m_sRealplayCallback[512];	//最大256通道*2种码流
	CallbackParam m_sIntercomCallback[257];	//最大256通道+设备对讲

protected:
	AbstractDevice(QString strSerialNum, QObject *parent = 0);
	const QString m_strSerialNum;
	bool m_isOnline;
	HANDLE m_hConnection;

private:
	
};

#endif // ABSTRACTDEVICE_H
