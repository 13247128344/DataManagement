#include "DeviceContext.h"
#include "DeviceHttp.h"
#include "DeviceI8.h"
#include "DeviceRegister.h"
#include "DeviceTutk.h"
#include "DeviceHoney.h"
#include "DeviceTaos.h"
#include "DeviceI9.h"
#include "DeviceAnjie.h"
#include "DeviceUmeye.h"
#include "DeviceHoneywell.h"
#include "DeviceP2P.h"
#include "messagesendmgr.h"
#include "realdatabuffer.h"
#include "sqlconnection.h"
#include "alarmmgr.h"
#include "cms_client_instance.h"
#include "DeviceGB28181.h"
#include "DeviceOnvif.h"
#include <QDateTime>
#include <QDebug>
#include "ants_ipc_api.h"
#include "Storager.h"
#include "cms_connect_server_common.h"
QHash<QString, QSharedPointer<DeviceContext> > DeviceContext::sta_hashInstance;
QMutex DeviceContext::sta_mutexInstance;


/****************************
		报警回调
*****************************/
void __stdcall CMS_AlarmMessage_Callback(CMS_CONNECT_PARSE_AlarmType eAlarmType, QString strSerialNum, int iParam, void *pUser) {
	CMSService_AlarmInfo sAlarm;
	sAlarm.eAlarmType = eAlarmType;
	sAlarm.strSerialNum = strSerialNum;
	sAlarm.iParam = iParam;
	//告警处理
	AlarmMgr::GetInstance()->AlarmProc(sAlarm);
}


DeviceContext::DeviceContext(CMS_CONNECT_PARSE_ProtocolType eProtocolType, QString strSerialNum, QObject *parent)
	: QObject(parent), m_eProtocolType(eProtocolType) {
	switch (m_eProtocolType) {
	case ProtocolType_Register:
		m_pDevice = new DeviceRegister(strSerialNum);
		break;
	case ProtocolType_I8H:
		m_pDevice = new DeviceHttp(strSerialNum, RTP_OVER_TCP);
		break;
	case ProtocolType_I8H_UDP:
		m_pDevice = new DeviceHttp(strSerialNum, RTP_OVER_UDP);
		break;
	case ProtocolType_GoAhead:
		m_pDevice = new DeviceHttp(strSerialNum, RTP_OVER_TCP);
		break;
	case ProtocolType_GoAhead_UDP:
		m_pDevice = new DeviceHttp(strSerialNum, RTP_OVER_UDP);
		break;
	case ProtocolType_ONVIF:
		m_pDevice = new DeviceOnvif(strSerialNum);
		break;
	case ProtocolType_GB28181:
		m_pDevice = new DeviceGB28181(strSerialNum);
		break;
	case ProtocolType_I8:
		m_pDevice = new DeviceI8(strSerialNum);
		break;
	case ProtocolType_TUTK:
		m_pDevice = new DeviceTutk(strSerialNum);
		break;
	case ProtocolType_Honey:
		m_pDevice = new DeviceHoney(strSerialNum);
		break;
	case ProtocolType_Taos:
		m_pDevice = new DeviceTaos(strSerialNum);
		break;
	case ProtocolType_I9:
		m_pDevice = new DeviceI9(strSerialNum);
		break;	
	case ProtocolType_AJ:
		m_pDevice = new DeviceAnjie(strSerialNum);
		break;
	case ProtocolType_UMEYE:
		m_pDevice = new DeviceUmeye(strSerialNum);
		break;
	case ProtocolType_Honeywell:
		m_pDevice = new DeviceHoneywell(strSerialNum);
		break;
	case ProtocolType_P2P:
		m_pDevice = new DeviceP2P(strSerialNum);
		break;
	}


	m_pIntercomClient = NULL;
	m_pDevice->setAlarmCallback(CMS_AlarmMessage_Callback, NULL);

	for (int i = 0; i < 256; i++) {
		m_pRecordPop[i] = NULL;
		m_pRecordPop[i + 256] = NULL;
	}
}

DeviceContext::~DeviceContext() {
	{
		QMutexLocker locker(&m_mutexRecord);
		for (int i = 0; i < 512; i++) {
			if (NULL != m_pRecordPop[i]) {
				delete m_pRecordPop[i];
				m_pRecordPop[i] = NULL;
			}
		}
	}

	RealDataBuffer::SetDeviceBufferClosed(m_pDevice->serialNum());

	logout();

	setConnectionHandle(NULL);

	m_pDevice->setAlarmCallback(NULL, NULL);

	delete m_pDevice;
	m_pDevice = NULL;
}

QSharedPointer<DeviceContext> DeviceContext::createDeviceContext(CMS_CONNECT_PARSE_ProtocolType eProtocolType, QString strSerialNum) {
	QSharedPointer<DeviceContext> ptr(new DeviceContext(eProtocolType, strSerialNum));

	{
		QMutexLocker locker(&sta_mutexInstance);
		sta_hashInstance.insert(strSerialNum, ptr);
	}
	return ptr;
}

void DeviceContext::destoryDeviceContext(QString strSerialNum) {
	//pDevice保证DeviceContext对象的释放在锁sta_mutexInstance外面，避免关闭流时与流回调中调用的getInstanceBySerial接口导致死锁
	QSharedPointer<DeviceContext> pDevice;

	{
		QMutexLocker locker(&sta_mutexInstance);
		pDevice = sta_hashInstance.take(strSerialNum);
	}
}

void DeviceContext::destoryAllDeviceContext() {
	{
		QMutexLocker locker(&sta_mutexInstance);
		sta_hashInstance.clear();
	}
}

QSharedPointer<DeviceContext> DeviceContext::getInstanceBySerial(QString strSerialNum) {
	{
		QMutexLocker locker(&sta_mutexInstance);
		return sta_hashInstance.value(strSerialNum, QSharedPointer<DeviceContext>());
	}
}

QList<QSharedPointer<DeviceContext> > DeviceContext::getAllDevice() {
	{
		QMutexLocker locker(&sta_mutexInstance);
		return sta_hashInstance.values();
	}
}

/****************************
		实时流回调
*****************************/
time_t current_frame_time = 0;
void __stdcall CMS_RealData_Callback(StreamFrameData *pFrameData, void *pUser) {
	RealDataBuffer *pBuffer = (RealDataBuffer *)pUser;
	//    if (3 == pFrameData->GetStreamHeader().iFrameType || 4 == pFrameData->GetStreamHeader().iFrameType)
	//    {
	//        delete pFrameData;
	//        return;
	//    }
	//    if(1 == pFrameData->GetStreamHeader().iFrameType || 2 == pFrameData->GetStreamHeader().iFrameType)
	//    {
	//        current_frame_time = pFrameData->GetStreamHeader().timeUTC;
	//    }
	//    else if (3 == pFrameData->GetStreamHeader().iFrameType)
	//    {
	//        pFrameData->GetStreamHeader().timeUTC = current_frame_time;
	//    }

	pBuffer->AddFrameData(pFrameData);
}

bool DeviceContext::openRealtime(RealDataBuffer *pBuffer) {
	bool retVal = m_pDevice->openRealtime(pBuffer->GetChannel(), pBuffer->GetStreamType(), CMS_RealData_Callback, pBuffer);
	qDebug() << __FUNCTION__ << m_pDevice->serialNum() << pBuffer->GetChannel() << pBuffer->GetStreamType() << "returns" << retVal;
	return retVal;
}

bool DeviceContext::closeRealtime(RealDataBuffer *pBuffer) {
	qDebug() << __FUNCTION__ << m_pDevice->serialNum() << pBuffer->GetChannel() << pBuffer->GetStreamType();
	return m_pDevice->closeRealtime(pBuffer->GetChannel(), pBuffer->GetStreamType());
}

/****************************
		音频流回调
*****************************/
void __stdcall CMS_IntercomData_Callback(StreamFrameData *pFrameData, void *pUser) {
	Client *pClient = (Client *)pUser;
	pClient->SendFrameData(pFrameData);
}

bool DeviceContext::openIntercom(int iChNo, Client *pClient) {
	return m_pDevice->openIntercom(iChNo, CMS_IntercomData_Callback, pClient);
}

bool DeviceContext::closeIntercom(int iChNo) {
	return m_pDevice->closeIntercom(iChNo);
}

bool DeviceContext::sendIntercom(CMS_CONNECT_PARSE_StreamHeader header, unsigned char * lpBuffer, unsigned int iBufferSize) {
	return m_pDevice->sendIntercom(header, lpBuffer, iBufferSize);
}

bool DeviceContext::ptzCtrl(int iChNo, CMS_CONNECT_PARSE_PtzCmdType eCmdType, int isStop, int iSpeed) {
	return m_pDevice->ptzCtrl(iChNo, eCmdType, isStop, iSpeed);
}

bool DeviceContext::set3D(int iChNo, int iTopX, int iTopY, int iBottomX, int iBottomY) {
	return m_pDevice->set3D(iChNo, iTopX, iTopY, iBottomX, iBottomY);
}

bool DeviceContext::presetCtrl(int iChNo, int iPresetIndex, CMS_CONNECT_PARSE_PresetCmdType eCmdType) {
	return m_pDevice->presetCtrl(iChNo, iPresetIndex, eCmdType);
}

bool DeviceContext::getCruise(int iChNo, int iCruiseRoute, CMS_CONNECT_PARSE_CruisePoint_Param * &results, int &iParamCount) {
	return m_pDevice->getCruise(iChNo, iCruiseRoute, results, iParamCount);
}

bool DeviceContext::setCruise(int iChNo, int iCruiseRoute, int iCruisePoint, CMS_CONNECT_PARSE_CruisePoint_Param request) {
	return m_pDevice->setCruise(iChNo, iCruiseRoute, iCruisePoint, request);
}

bool DeviceContext::deleteCruise(int iChNo, int iCruiseRoute, int iCruisePoint) {
	return m_pDevice->deleteCruise(iChNo, iCruiseRoute, iCruisePoint);
}

bool DeviceContext::clearCruise(int iChNo, int iCruiseRoute) {
	return m_pDevice->clearCruise(iChNo, iCruiseRoute);
}

bool DeviceContext::runCruise(int iChNo, int iCruiseRoute, int isRun) {
	return m_pDevice->runCruise(iChNo, iCruiseRoute, isRun);
}

bool DeviceContext::locusCtrl(int iChNo, int iLocusIndex, int iCmd, int isStop) {
	return m_pDevice->locusCtrl(iChNo, iLocusIndex, iCmd, isStop);
}

bool DeviceContext::searchRecord(CMS_CONNECT_PARSE_StreamType eStreamType,
	time_t beginTime,
	time_t endTime,
	unsigned int iRecordType,
	CMS_CONNECT_PARSE_RecordType_Condition eRecordType_Condition,
	QList<int> listChNo,
	CMS_CONNECT_PARSE_SearchRecord_Param * &results,
	int &iResultsCount) {
	return m_pDevice->searchRecord(eStreamType, beginTime, endTime, iRecordType, eRecordType_Condition, listChNo, results, iResultsCount);
}


/****************************
		历史流回调
*****************************/
void __stdcall Device_HistoryData_Callback(StreamFrameData *pFrameData, void *pUser) {
	Replay *pReplay = (Replay *)pUser;

	if (0 != pReplay->m_timeSeek) {
		if (pFrameData->GetStreamHeader().iFrameType == 1 || pFrameData->GetStreamHeader().iFrameType == 2) {
			if (10 < qAbs(pFrameData->GetStreamHeader().timeUTC - pReplay->m_timeSeek)) {
				qDebug() << QString("data droped!! frame time utc:[%1], seek time:[%2]").arg(pFrameData->GetStreamHeader().timeUTC).arg(pReplay->m_timeSeek);
				return;
			} else {
				pReplay->m_timeSeek = 0;
			}
		} else {
			return;
		}
	}

	if (NULL != pReplay->m_pFunc) {
		pReplay->m_pFunc(pFrameData, pReplay->m_pUser);
	}
}


bool DeviceContext::openReplay(Replay *pReplay) {
	pReplay->m_sReplayInfo.setCallback(Device_HistoryData_Callback, pReplay);
	return m_pDevice->openReplay(&pReplay->m_sReplayInfo);
}

bool DeviceContext::closeReplay(Replay *pReplay) {
	return m_pDevice->closeReplay(&pReplay->m_sReplayInfo);
}

bool DeviceContext::ctrlReplay(Replay *pReplay, CMS_CONNECT_PARSE_ReplayCmdType eCmdType, int iParam) {
	if (ReplayCtrlType_SeekTime == eCmdType)
		pReplay->m_timeSeek = iParam;

	return m_pDevice->ctrlReplay(&pReplay->m_sReplayInfo, eCmdType, iParam);
}

bool DeviceContext::getAlarmIO(CMS_CONNECT_PARSE_IOType eType, int iIndex, bool &isOpen) {
	return m_pDevice->getAlarmIO(eType, iIndex, isOpen);
}

bool DeviceContext::setAlarmIO(CMS_CONNECT_PARSE_IOType eType, int iIndex, bool isOpen) {
	return m_pDevice->setAlarmIO(eType, iIndex, isOpen);
}

bool DeviceContext::timeSync() {
	return m_pDevice->timeSync();
}

bool DeviceContext::ctrlUtc(int iChNo, CMS_CONNECT_PARSE_UtcCmdType eCmd) {
	return m_pDevice->ctrlUtc(iChNo, eCmd);
}

void __stdcall CMS_Server_Record_Callback(StreamFrameData *pFrameData, void *pUser) {
	QString s = SqlConnection::FindStoragerByCh(pFrameData->GetStreamHeader().cSerialNum, pFrameData->GetStreamHeader().iChannel);
	QSharedPointer<Storager> pStorager = Storager::FindInstanceBySerialNum(s);
	if (!pStorager.isNull()) {
		pStorager->InputStreamData(pFrameData);
	}
}


void DeviceContext::openRecStream(int iChNo) {
	{
		QMutexLocker locker(&m_mutexRecord);

		if (NULL != m_pRecordPop[iChNo - 1] && NULL != m_pRecordPop[iChNo + 256 - 1])
			return;

		if (NULL == m_pRecordPop[iChNo - 1]) {
			m_pRecordPop[iChNo - 1] = new RealDataPop(m_pDevice->serialNum(), iChNo, StreamType_Main, CMS_Server_Record_Callback, NULL);
			m_pRecordPop[iChNo - 1]->start();
		}

		if (NULL == m_pRecordPop[iChNo + 256 - 1]) {
			m_pRecordPop[iChNo + 256 - 1] = new RealDataPop(m_pDevice->serialNum(), iChNo, StreamType_Sub, CMS_Server_Record_Callback, NULL);
			m_pRecordPop[iChNo + 256 - 1]->start();
		}
	}

	setChannelRecState(iChNo, RecLocation_Storager, 1);
}

void DeviceContext::closeRecStream(int iChNo) {
	{
		QMutexLocker locker(&m_mutexRecord);

		if (NULL == m_pRecordPop[iChNo - 1] && NULL == m_pRecordPop[iChNo + 256 - 1])
			return;

		if (NULL != m_pRecordPop[iChNo - 1]) {
			delete m_pRecordPop[iChNo - 1];
			m_pRecordPop[iChNo - 1] = NULL;
		}

		if (NULL != m_pRecordPop[iChNo + 256 - 1]) {
			delete m_pRecordPop[iChNo + 256 - 1];
			m_pRecordPop[iChNo + 256 - 1] = NULL;
		}
	}

	setChannelRecState(iChNo, RecLocation_Storager, 0);
}

void DeviceContext::setOnline(const bool bOnline) {
	qDebug() << "serial:" << m_pDevice->serialNum() << "bOnline:" << bOnline << " m_pDevice->isOnline():" << m_pDevice->isOnline();
	if (bOnline == m_pDevice->isOnline()) {
		return;
	}
	m_pDevice->setOnline(bOnline);

	CMS_CONNECT_PARSE_Online_Notice *pNotice = new CMS_CONNECT_PARSE_Online_Notice();
	strcpy(pNotice->cSerialNum, m_pDevice->serialNum().toUtf8().data());
	pNotice->isOnline = bOnline;
	MessageSendMgr::GetInstance()->Proc(NoticeType_OnlineState, 0, pNotice);

	if (bOnline) {
		int days, hour, minute, second;
		SqlConnection::GetTimeSyncParam(days, hour, minute, second);
		if (0 != days) {
			timeSync();
		}	
	}
}

void DeviceContext::setChannelRecState(int iChannel, CMS_CONNECT_PARSE_RecLocationType eType, int iState) {
	int iChannelId = SqlConnection::FindChannelBySerialNumAndChannel(m_pDevice->serialNum(), iChannel);
	if (0 != iChannelId) {
		int iDeviceRec = 0;
		int iCmsRec = 0;
		SqlConnection::GetChannelRecStateById(iChannelId, iCmsRec, iDeviceRec);

		if (RecLocation_Device == eType && iDeviceRec != iState) {
			iDeviceRec = iState;
		}
		else if (RecLocation_Storager == eType && iCmsRec != iState) {
			iCmsRec = iState;
		}
		else {
			return;
		}

		SqlConnection::UpdateChannelRecStateById(iChannelId, iCmsRec, iDeviceRec);

		CMS_CONNECT_PARSE_Record_Notice *pNotice = new CMS_CONNECT_PARSE_Record_Notice();
		strcpy(pNotice->cSerialNum, m_pDevice->serialNum().toUtf8().data());
		pNotice->iChannel = iChannel;
		pNotice->isCmsRecord = iCmsRec;
		pNotice->isDeviceRecord = iDeviceRec;
		MessageSendMgr::GetInstance()->Proc(NoticeType_RecordState, 0, pNotice);
	}
}

CMS_CONNECT_PARSE_ProtocolType DeviceContext::protocolType() const {
	return m_eProtocolType;
}

void DeviceContext::freeMemory(void *pMemory) {
	m_pDevice->freeMemory(pMemory);
}

void DeviceContext::setConnectionHandle(HANDLE handle) {
	m_pDevice->setConnectionHandle(handle);
}

const HANDLE DeviceContext::connectionHandle() {
	return m_pDevice->connectionHandle();
}

/************************
		设备搜索回调
************************/
void __stdcall CMS_SearchDevice_Callback(CMS_CONNECT_PARSE_SearchDeviceInfo sInfo, void *pUser) {
	CMS_Client_Instance *pInstance = (CMS_Client_Instance *)pUser;

	CMS_CONNECT_PARSE_Header header;
	header.ePackType = PackType_Notice;
	header.eContentType.eNoticeType = NoticeType_SearchDevice;

	unsigned int opt = 0xFFFF;
	pInstance->SendData(opt, (char *)&header, sizeof(header), (char *)&sInfo, sizeof(CMS_CONNECT_PARSE_SearchDeviceInfo));
}

void DeviceContext::startSearchDevice(int iProtocolTypeFlags, void *pUser) {
	if (0 != (ProtocolType_Register & iProtocolTypeFlags)) {
		DeviceRegister::startSearchDevice(CMS_SearchDevice_Callback, pUser);
	}
	if (0 != (ProtocolType_I8H & iProtocolTypeFlags)) {
		DeviceHttp::startSearchDevice(CMS_SearchDevice_Callback, pUser);
	}
	if (0 != (ProtocolType_ONVIF & iProtocolTypeFlags)) {
		DeviceOnvif::startSearchDevice(CMS_SearchDevice_Callback, pUser);
	}
	if (0 != (ProtocolType_GB28181 & iProtocolTypeFlags)) {
		DeviceGB28181::startSearchDevice(CMS_SearchDevice_Callback, pUser);
	}
	if (0 != (ProtocolType_I8 & iProtocolTypeFlags)) {
		DeviceI8::startSearchDevice(CMS_SearchDevice_Callback, pUser);
	}
	if (ProtocolType_TUTK & iProtocolTypeFlags) {
		DeviceTutk::startSearchDevice(CMS_SearchDevice_Callback, pUser);
	}
	if (ProtocolType_Honey & iProtocolTypeFlags) {
		DeviceHoney::startSearchDevice(CMS_SearchDevice_Callback, pUser);
	}
	if (ProtocolType_Taos & iProtocolTypeFlags) {
		DeviceTaos::startSearchDevice(CMS_SearchDevice_Callback, pUser);
	}
	if (ProtocolType_I9 & iProtocolTypeFlags) {
		DeviceI9::startSearchDevice(CMS_SearchDevice_Callback, pUser);
	}
	if (ProtocolType_Honeywell & iProtocolTypeFlags){
		DeviceHoneywell::startSearchDevice(CMS_SearchDevice_Callback, pUser);
	}
	if (ProtocolType_P2P & iProtocolTypeFlags)
	{
		DeviceP2P::startSearchDevice(CMS_SearchDevice_Callback,pUser);
	}
}

void DeviceContext::stopSearchDevice(int iProtocolTypeFlags) {
	if (0 != (ProtocolType_Register & iProtocolTypeFlags)) {
		DeviceRegister::stopSearchDevice();
	}
	if (0 != (ProtocolType_I8H & iProtocolTypeFlags)) {
		DeviceHttp::stopSearchDevice();
	}
	if (0 != (ProtocolType_ONVIF & iProtocolTypeFlags)) {
		DeviceOnvif::stopSearchDevice();
	}
	if (0 != (ProtocolType_GB28181 & iProtocolTypeFlags)) {
		DeviceGB28181::stopSearchDevice();
	}
	if (0 != (ProtocolType_I8 & iProtocolTypeFlags)) {
		DeviceI8::stopSearchDevice();
	}
	if (ProtocolType_TUTK & iProtocolTypeFlags) {
		DeviceTutk::stopSearchDevice();
	}
	if (ProtocolType_Honey & iProtocolTypeFlags) {
		DeviceHoney::stopSearchDevice();
	}
	if (ProtocolType_Taos & iProtocolTypeFlags) {
		DeviceTaos::stopSearchDevice();
	}
	if (ProtocolType_I9 & iProtocolTypeFlags) {
		DeviceI9::stopSearchDevice();
	}
	if (ProtocolType_Honeywell & iProtocolTypeFlags){
		DeviceHoneywell::stopSearchDevice();
	}
	if (ProtocolType_P2P & iProtocolTypeFlags)
	{
		DeviceP2P::stopSearchDevice();
	}
}

bool DeviceContext::login(CMS_CONNECT_PARSE_ProtocolType eProtocolType, QString strUsername, QString strPassword, AbstractDevice::LoginInfo &sLoginInfo) {
	QMutexLocker lck(&g_mutexExtendedCount);

	if (ProtocolType_Register == eProtocolType) {
		if (!DeviceRegister::login(strUsername, strPassword, sLoginInfo))
			return false;

		if (-1 != g_iMaxExtendedCount[RegisterDeviceAuthorityIndex] && g_iCurrentExtendedCount[RegisterDeviceAuthorityIndex] + sLoginInfo.iChannelCount > g_iMaxExtendedCount[RegisterDeviceAuthorityIndex]) {
			DeviceRegister::logout(sLoginInfo.handle);

			return false;
		}

		g_iCurrentExtendedCount[RegisterDeviceAuthorityIndex] += sLoginInfo.iChannelCount;
	}
	else if (ProtocolType_I8H == eProtocolType) {
		if (!DeviceHttp::login(strUsername, strPassword, sLoginInfo))
			return false;

		if (-1 != g_iMaxExtendedCount[I8HDeviceAuthorityIndex] && g_iCurrentExtendedCount[I8HDeviceAuthorityIndex] + sLoginInfo.iChannelCount > g_iMaxExtendedCount[I8HDeviceAuthorityIndex]) {
			DeviceHttp::logout(sLoginInfo.handle);

			return false;
		}

		g_iCurrentExtendedCount[I8HDeviceAuthorityIndex] += sLoginInfo.iChannelCount;

	}
	else if (ProtocolType_I8H_UDP == eProtocolType) {
		if (!DeviceHttp::login(strUsername, strPassword, sLoginInfo))
			return false;

		if (-1 != g_iMaxExtendedCount[I8HDeviceAuthorityIndex] && g_iCurrentExtendedCount[I8HDeviceAuthorityIndex] + sLoginInfo.iChannelCount > g_iMaxExtendedCount[I8HDeviceAuthorityIndex]) {
			DeviceHttp::logout(sLoginInfo.handle);

			return false;
		}

		g_iCurrentExtendedCount[I8HDeviceAuthorityIndex] += sLoginInfo.iChannelCount;

	}
	else if (ProtocolType_GoAhead == eProtocolType) {
		if (!DeviceHttp::login(strUsername, strPassword, sLoginInfo))
			return false;

		if (-1 != g_iMaxExtendedCount[I8HDeviceAuthorityIndex] && g_iCurrentExtendedCount[I8HDeviceAuthorityIndex] + sLoginInfo.iChannelCount > g_iMaxExtendedCount[I8HDeviceAuthorityIndex]) {
			DeviceHttp::logout(sLoginInfo.handle);

			return false;
		}

		g_iCurrentExtendedCount[I8HDeviceAuthorityIndex] += sLoginInfo.iChannelCount;

	}
	else if (ProtocolType_GoAhead_UDP == eProtocolType) {
		if (!DeviceHttp::login(strUsername, strPassword, sLoginInfo))
			return false;

		if (-1 != g_iMaxExtendedCount[I8HDeviceAuthorityIndex] && g_iCurrentExtendedCount[I8HDeviceAuthorityIndex] + sLoginInfo.iChannelCount > g_iMaxExtendedCount[I8HDeviceAuthorityIndex]) {
			DeviceHttp::logout(sLoginInfo.handle);

			return false;
		}

		g_iCurrentExtendedCount[I8HDeviceAuthorityIndex] += sLoginInfo.iChannelCount;

	}
	else if (ProtocolType_ONVIF == eProtocolType) {
		if (!DeviceOnvif::login(strUsername, strPassword, sLoginInfo))
			return false;

		if (-1 != g_iMaxExtendedCount[OnvifDeviceAuthorityIndex] && g_iCurrentExtendedCount[OnvifDeviceAuthorityIndex] + sLoginInfo.iChannelCount > g_iMaxExtendedCount[OnvifDeviceAuthorityIndex]) {
			DeviceOnvif::logout(sLoginInfo.handle);

			return false;
		}

		g_iCurrentExtendedCount[OnvifDeviceAuthorityIndex] += sLoginInfo.iChannelCount;

	}
	else if (ProtocolType_GB28181 == eProtocolType) {
		if (!DeviceGB28181::login(strUsername, strPassword, sLoginInfo))
			return false;

		if (-1 != g_iMaxExtendedCount[GB28181DeviceAuthorityIndex] && g_iCurrentExtendedCount[GB28181DeviceAuthorityIndex] + sLoginInfo.iChannelCount > g_iMaxExtendedCount[GB28181DeviceAuthorityIndex]) {
			DeviceGB28181::logout(sLoginInfo.handle);

			return false;
		}

		g_iCurrentExtendedCount[GB28181DeviceAuthorityIndex] += sLoginInfo.iChannelCount;

	}
	else if (ProtocolType_I8 == eProtocolType) {
		if (!DeviceI8::login(strUsername, strPassword, sLoginInfo))
			return false;

		if (-1 != g_iMaxExtendedCount[I8DeviceAuthorityIndex] && g_iCurrentExtendedCount[I8DeviceAuthorityIndex] + sLoginInfo.iChannelCount > g_iMaxExtendedCount[I8DeviceAuthorityIndex]) {
			DeviceI8::logout(sLoginInfo.handle);

			return false;
		}

		g_iCurrentExtendedCount[I8DeviceAuthorityIndex] += sLoginInfo.iChannelCount;

	}
	else if (ProtocolType_TUTK == eProtocolType) {
		if (!DeviceTutk::login(strUsername, strPassword, sLoginInfo))
			return false;

// 		if (-1 != g_iMaxExtendedCount[TUTKDeviceAuthorityIndex] && g_iCurrentExtendedCount[TUTKDeviceAuthorityIndex] + sLoginInfo.iChannelCount > g_iMaxExtendedCount[TUTKDeviceAuthorityIndex]) {
// 			DeviceTutk::logout(sLoginInfo.handle);
// 			return false;
// 		}
// 
// 		g_iCurrentExtendedCount[TUTKDeviceAuthorityIndex] += sLoginInfo.iChannelCount;

	}
	else if (ProtocolType_Honey == eProtocolType) {
		if (!DeviceHoney::login(strUsername, strPassword, sLoginInfo))
			return false;

		if (-1 != g_iMaxExtendedCount[HN1DeviceAuthorityIndex] && g_iCurrentExtendedCount[HN1DeviceAuthorityIndex] + sLoginInfo.iChannelCount > g_iMaxExtendedCount[HN1DeviceAuthorityIndex]) {
			DeviceHoney::logout(sLoginInfo.handle);

			return false;
		}

		g_iCurrentExtendedCount[HN1DeviceAuthorityIndex] += sLoginInfo.iChannelCount;

	}
	else if (ProtocolType_Taos == eProtocolType) {
		if (!DeviceTaos::login(strUsername, strPassword, sLoginInfo))
			return false;

		if (-1 != g_iMaxExtendedCount[TaosDeviceAuthorityIndex] && g_iCurrentExtendedCount[TaosDeviceAuthorityIndex] + sLoginInfo.iChannelCount > g_iMaxExtendedCount[TaosDeviceAuthorityIndex]) {
			DeviceTaos::logout(sLoginInfo.handle);

			return false;
		}

		g_iCurrentExtendedCount[TaosDeviceAuthorityIndex] += sLoginInfo.iChannelCount;

	}
	else if (ProtocolType_I9 == eProtocolType) {
// 		if (!DeviceTaos::login(strUsername, strPassword, sLoginInfo))
// 			return false;
// 
// 		if (-1 != g_iMaxExtendedCount[TaosDeviceAuthorityIndex] && g_iCurrentExtendedCount[TaosDeviceAuthorityIndex] + sLoginInfo.iChannelCount > g_iMaxExtendedCount[TaosDeviceAuthorityIndex]) {
// 			DeviceTaos::logout(sLoginInfo.handle);
// 
// 			return false;
// 		}
// 
// 		g_iCurrentExtendedCount[TaosDeviceAuthorityIndex] += sLoginInfo.iChannelCount;
		if (!DeviceI9::login(strUsername, strPassword, sLoginInfo))
		{
			return false;
		}

	}
	else if (ProtocolType_AJ == eProtocolType) {
		// 		if (!DeviceTaos::login(strUsername, strPassword, sLoginInfo))
		// 			return false;
		// 
		// 		if (-1 != g_iMaxExtendedCount[TaosDeviceAuthorityIndex] && g_iCurrentExtendedCount[TaosDeviceAuthorityIndex] + sLoginInfo.iChannelCount > g_iMaxExtendedCount[TaosDeviceAuthorityIndex]) {
		// 			DeviceTaos::logout(sLoginInfo.handle);
		// 
		// 			return false;
		// 		}
		// 
		// 		g_iCurrentExtendedCount[TaosDeviceAuthorityIndex] += sLoginInfo.iChannelCount;
		if (!DeviceAnjie::login(strUsername, strPassword, sLoginInfo))
		{
			return false;
		}

	}
	else if (ProtocolType_UMEYE == eProtocolType) {
		if (!DeviceUmeye::login(strUsername, strPassword, sLoginInfo))
		{
			return false;
		}

	}
	else if (ProtocolType_Honeywell == eProtocolType)
	{
		if (!DeviceHoneywell::login(strUsername, strPassword, sLoginInfo))
		{
			return false;
		}
	}
	else if (ProtocolType_P2P == eProtocolType)
	{
		if (!DeviceP2P::login(strUsername, strPassword, sLoginInfo))
		{
			return false;
		}
	}

	return true;
}

bool DeviceContext::logout(CMS_CONNECT_PARSE_ProtocolType eProtocolType, HANDLE hConnection) {
	QMutexLocker lck(&g_mutexExtendedCount);

	if (ProtocolType_Register == eProtocolType) {
		g_iCurrentExtendedCount[RegisterDeviceAuthorityIndex] -= DeviceRegister::logout(hConnection);
	}
	else if (ProtocolType_I8H == eProtocolType) {
		g_iCurrentExtendedCount[I8HDeviceAuthorityIndex] -= DeviceHttp::logout(hConnection);
	}
	else if (ProtocolType_I8H_UDP == eProtocolType) {
		g_iCurrentExtendedCount[I8HDeviceAuthorityIndex] -= DeviceHttp::logout(hConnection);
	}
	else if (ProtocolType_GoAhead_UDP == eProtocolType) {
		g_iCurrentExtendedCount[I8HDeviceAuthorityIndex] -= DeviceHttp::logout(hConnection);
	}
	else if (ProtocolType_GoAhead == eProtocolType) {
		g_iCurrentExtendedCount[I8HDeviceAuthorityIndex] -= DeviceHttp::logout(hConnection);
	}
	else if (ProtocolType_ONVIF == eProtocolType) {
		g_iCurrentExtendedCount[OnvifDeviceAuthorityIndex] -= DeviceOnvif::logout(hConnection);
	}
	else if (ProtocolType_GB28181 == eProtocolType) {
		g_iCurrentExtendedCount[GB28181DeviceAuthorityIndex] -= DeviceGB28181::logout(hConnection);
	}
	else if (ProtocolType_I8 == eProtocolType) {
		g_iCurrentExtendedCount[I8DeviceAuthorityIndex] -= DeviceI8::logout(hConnection);
	}
	else if (ProtocolType_TUTK == eProtocolType) {
		g_iCurrentExtendedCount[TUTKDeviceAuthorityIndex] -= DeviceTutk::logout(hConnection);
	}
	else if (ProtocolType_Honey == eProtocolType) {
		g_iCurrentExtendedCount[HN1DeviceAuthorityIndex] -= DeviceHoney::logout(hConnection);
	}
	else if (ProtocolType_Taos == eProtocolType) {
		g_iCurrentExtendedCount[TaosDeviceAuthorityIndex] -= DeviceTaos::logout(hConnection);
	}
	else if (ProtocolType_I9 == eProtocolType) {
// 		g_iCurrentExtendedCount[TaosDeviceAuthorityIndex] -= DeviceTaos::logout(hConnection);
		DeviceI9::logout(hConnection);
	}
	else if (ProtocolType_AJ == eProtocolType) {
	// 		g_iCurrentExtendedCount[TaosDeviceAuthorityIndex] -= DeviceTaos::logout(hConnection);
		DeviceAnjie::logout(hConnection);
	}
	else if (ProtocolType_UMEYE == eProtocolType) {
		DeviceUmeye::logout(hConnection);
	}
	else if (ProtocolType_Honeywell == eProtocolType) {
		DeviceHoneywell::logout(hConnection);
	}
	else if (ProtocolType_P2P == eProtocolType)
	{
		DeviceP2P::logout(hConnection);
	}

	return true;
}

bool DeviceContext::logout() {
	if (ProtocolType_I8H == m_eProtocolType || ProtocolType_I8H_UDP == m_eProtocolType || ProtocolType_GoAhead == m_eProtocolType || ProtocolType_GoAhead_UDP == m_eProtocolType) {
		((DeviceHttp *)m_pDevice)->clearRealtimeCount();
	}

	return logout(m_eProtocolType, m_pDevice->connectionHandle());
}

bool DeviceContext::modifyChName(int iChNo, QString strName) {
	return m_pDevice->modifyChName(iChNo, strName);
}

bool DeviceContext::ptzArbitrate(int iUserId, int iChannel) {
	time_t currentTime = QDateTime::currentDateTime().toTime_t();
	int iPtzLevel = SqlConnection::GetPtzLevel(iUserId, m_pDevice->serialNum(), iChannel);

	if (0 == iPtzLevel) {
		return false;
	}

	{
		QMutexLocker locker(&m_mutexPtzArbitrate);
		if (!m_hashPtzArbitrate.contains(iChannel)) {
			m_hashPtzArbitrate.insert(iChannel, QSharedPointer<PtzArbitrate>(new PtzArbitrate(iUserId, iPtzLevel, currentTime)));
			return true;
		}
		else {
			QSharedPointer<PtzArbitrate> &aribitrate = m_hashPtzArbitrate[iChannel];

			if (aribitrate->userId() == iUserId) {
				aribitrate->updateTime(currentTime);
				return true;
			}
			else {
				if (iPtzLevel > aribitrate->ptzLevel() || currentTime - aribitrate->time() > 30) {
					aribitrate->updateUser(iUserId, iPtzLevel, currentTime);
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
}
