/************************************************************************
*
*   文件名： DeviceContext.h
*
*   文件描述：设备策略类，整合了各个协议的设备，对外提供统一的接口
*
*   创建人：Sunx, 2015年6月17日
*
*   版本号：1.0
*
*   修改记录：
*
************************************************************************/


#ifndef DEVICECONTEXT_H
#define DEVICECONTEXT_H

#include <QObject>
#include "cms_connect_parse_common.h"
//#include "client.h"
#include "AbstractDevice.h"
//#include "realdatapop.h"
//#include "realdatabuffer.h"
#include <QSharedPointer>
#include <QHash>
//#include "ptzarbitrate.h"

class DeviceContext : public QObject
{
	Q_OBJECT

public:
	~DeviceContext();
    bool ptzArbitrate(int iUserId, int iChannel);

	static QList<QSharedPointer<DeviceContext> > getAllDevice();
    static void startSearchDevice(int iProtocolTypeFlags, void *pUser);
    static void stopSearchDevice(int iProtocolTypeFlags);
	static bool login(CMS_CONNECT_PARSE_ProtocolType eProtocolType, QString strUsername, QString strPassword, AbstractDevice::LoginInfo &sLoginInfo);
    static bool logout(CMS_CONNECT_PARSE_ProtocolType eProtocolType, HANDLE hConnection);
    bool logout();

	static QSharedPointer<DeviceContext> createDeviceContext(CMS_CONNECT_PARSE_ProtocolType eProtocolType, QString strSerialNum);
	static void destoryDeviceContext(QString strSerialNum);
	static QSharedPointer<DeviceContext> getInstanceBySerial(QString strSerialNum);
	static void destoryAllDeviceContext();



	bool ptzCtrl(int iChNo, CMS_CONNECT_PARSE_PtzCmdType eCmdType, int isStop, int iSpeed);
	bool set3D(int iChNo, int iTopX, int iTopY, int iBottomX, int iBottomY);
	bool presetCtrl(int iChNo, int iPresetIndex, CMS_CONNECT_PARSE_PresetCmdType eCmdType);
    bool getCruise(int iChNo, int iCruiseRoute, CMS_CONNECT_PARSE_CruisePoint_Param * &results, int &iParamCount);
    bool setCruise(int iChNo, int iCruiseRoute, int iCruisePoint, CMS_CONNECT_PARSE_CruisePoint_Param request);
	bool deleteCruise(int iChNo, int iCruiseRoute, int iCruisePoint);
	bool clearCruise(int iChNo, int iCruiseRoute);
	bool runCruise(int iChNo, int iCruiseRoute, int isRun);
	bool locusCtrl(int iChNo, int iLocusIndex, int iCmd, int isStop);

    bool searchRecord(CMS_CONNECT_PARSE_StreamType eStreamType,
                      time_t beginTime,
                      time_t endTime,
                      unsigned int iRecordType,
                      CMS_CONNECT_PARSE_RecordType_Condition eRecordType_Condition,
                      QList<int> listChNo,
                      CMS_CONNECT_PARSE_SearchRecord_Param * &results,
                      int &iResultsCount);

	bool getAlarmIO(CMS_CONNECT_PARSE_IOType eType, int iIndex, bool &isOpen);
	bool setAlarmIO(CMS_CONNECT_PARSE_IOType eType, int iIndex, bool isOpen);
	bool timeSync();
	bool ctrlUtc(int iChNo, CMS_CONNECT_PARSE_UtcCmdType eCmd);
	bool modifyChName(int iChNo, QString strName);

	void freeMemory(void *pMemory);
	void setOnline(const bool bOnline);
	void setChannelRecState(int iChannel, CMS_CONNECT_PARSE_RecLocationType eType, int iState);
    CMS_CONNECT_PARSE_ProtocolType protocolType() const;

	void setConnectionHandle(HANDLE handle);

    const HANDLE connectionHandle();
    AbstractDevice *m_pDevice;

private:
	DeviceContext(CMS_CONNECT_PARSE_ProtocolType eProtocolType, QString strSerialNum, QObject *parent = 0);

	const CMS_CONNECT_PARSE_ProtocolType m_eProtocolType;

	static QHash<QString, QSharedPointer<DeviceContext> > sta_hashInstance;
	static QMutex sta_mutexInstance;

    QMutex m_mutexRecord;

   // QHash <int ,QSharedPointer<PtzArbitrate> > m_hashPtzArbitrate;
    QMutex m_mutexPtzArbitrate;
};

#endif // DEVICECONTEXT_H
