#include "DeviceHttp.h"
//#include "sqlconnection.h"
#include "DeviceContext.h"
#include "ants_ipc_api.h"
#include <QString>
#include <QDebug>
#include "I8H_SDK.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCoreApplication>
//#include <QSqlQuery>
#include <QFile>
#define I8H_G711_U 1

//#include "log_file.h"

//jhy 2018/11/15 S-Viewer版本要求NVR显示通道IP地址
//#define  _SVIEW_
//

bool DeviceHttp::sta_isSearching = false;
QMutex DeviceHttp::sta_mutexSearching;
QMap<HANDLE, I8HCache *> DeviceHttp::sta_mapCache;
QMutex DeviceHttp::sta_mutexCache;
DeviceSearchHelper DeviceHttp::sta_searchHelper;

DeviceHttp::DeviceHttp(QString strSerialNum, int rtp_type, QObject *parent)
	: AbstractDevice(strSerialNum, parent),
	m_intercomHandle(NULL),
	m_alarmHandle(NULL),
	m_rtpType(rtp_type) {
	m_streamInfo = new I8H_StreamInfo[512];
	m_realtimeParam = new RealtimeParam[512 / 8];
}

DeviceHttp::~DeviceHttp() {
	delete[]m_streamInfo;
	delete[]m_realtimeParam;
}

//unsigned int sta_frameNo[512];

/**********************************************
				预览回调
**********************************************/
void CALLBACK Http_RealData_CallBack(HANDLE hHandle, DWORD dwOption, DWORD dwDataType, BYTE *lpBuffer, DWORD dwBufferSize, LPVOID lpUser) {
	if (dwDataType == I8H_STREAMDATA_STREAMDATA || dwDataType == I8H_STREAMDATA_AUDIOSTREAMDATA) {
		DeviceHttp::I8H_StreamInfo *info = (DeviceHttp::I8H_StreamInfo *)lpUser;
		AntsIPCFrameHeader_T *i8Header = (AntsIPCFrameHeader_T *)lpBuffer;
		CMS_CONNECT_PARSE_StreamHeader struStreamHeader;
		struStreamHeader.timeUTC = i8Header->uiFrameTime;
		struStreamHeader.iMicroSec = i8Header->uiFrameTickCount;
		struStreamHeader.iChannel = (dwOption >> 16) & 0xFFFF;

		if (0 == (dwOption & 0x00FF)) {
			struStreamHeader.eStreamType = StreamType_Main;
		}
		else {
			struStreamHeader.eStreamType = StreamType_Sub;
		}

		int chIndex;
		if (StreamType_Main == struStreamHeader.eStreamType)//开主码流
		{
			chIndex = struStreamHeader.iChannel - 1;
		}
		else {
			chIndex = struStreamHeader.iChannel - 1 + 256;
		}

		strcpy(struStreamHeader.cSerialNum, info[chIndex].cSerialNum);

		if (AntsIPCFrameType_IFrames == i8Header->uiFrameType
			|| AntsIPCFrameType_SubIFrames == i8Header->uiFrameType
			|| AntsIPCFrameType_PFrames == i8Header->uiFrameType
			|| AntsIPCFrameType_SubPFrames == i8Header->uiFrameType) {
			//if (sta_frameNo[chIndex] != 0 && sta_frameNo[chIndex] + 1 != i8Header->uiFrameNo) {
			//	log_file::getInstance()->log(QString("ch %1 lost frame sta_frameNo[%2, %3)").arg(struStreamHeader.iChannel).arg(sta_frameNo[chIndex] + 1).arg(i8Header->uiFrameNo));
			//}

			//sta_frameNo[chIndex] = i8Header->uiFrameNo;

			switch (i8Header->uiFrameType) {
			case AntsIPCFrameType_IFrames:
			{
				struStreamHeader.iFrameType = 1;//帧类型，	0-音频帧；1-I帧；2-P帧；3-智能规则帧；4-智能结果帧         
			}break;
			case AntsIPCFrameType_SubIFrames:
				struStreamHeader.iFrameType = 1;
				break;
			case AntsIPCFrameType_PFrames:
				struStreamHeader.iFrameType = 2;
				break;
			case AntsIPCFrameType_SubPFrames:
				struStreamHeader.iFrameType = 2;
				break;
			default:
				return;
			}

			struStreamHeader.unionMedia.struVideoMedia.cCodecId = i8Header->uMedia.struVideoHeader.cCodecId;
			struStreamHeader.unionMedia.struVideoMedia.uWidth = i8Header->uMedia.struVideoHeader.usWidth;
			struStreamHeader.unionMedia.struVideoMedia.uHeight = i8Header->uMedia.struVideoHeader.usHeight;
		}
		else if (AntsIPCFrameType_AudioFrames == i8Header->uiFrameType) {
			int iFrameLength = 320 + sizeof(AntsIPCFrameHeader_T);
			int iFrameNum = dwBufferSize / iFrameLength;
			for (int i = 0; i < iFrameNum; ++i) {
				unsigned char *  pFrame = (unsigned char *)lpBuffer + iFrameLength * i;
				i8Header = (AntsIPCFrameHeader_T *)pFrame;

				struStreamHeader.iFrameType = 0;//音频帧
				struStreamHeader.unionMedia.struAudioMedia.cCodecId = i8Header->uMedia.struAudioHeader.cCodecId;
				struStreamHeader.unionMedia.struAudioMedia.cSampleRate = i8Header->uMedia.struAudioHeader.cSampleRate;
				struStreamHeader.unionMedia.struAudioMedia.cBitRate = i8Header->uMedia.struAudioHeader.cBitRate;
				struStreamHeader.unionMedia.struAudioMedia.cChannels = i8Header->uMedia.struAudioHeader.cChannels;
				struStreamHeader.unionMedia.struAudioMedia.cResolution = i8Header->uMedia.struAudioHeader.cResolution;

				if (NULL != info[chIndex].pFunc) {
					QMutexLocker lck(&info[chIndex].pDevice->m_callbackMutex);

					if (NULL != info[chIndex].pFunc) {
						StreamFrameData *frameData = new StreamFrameData(struStreamHeader, (unsigned char *)lpBuffer, dwBufferSize);	//创建数据帧
						info[chIndex].pFunc(frameData, info[chIndex].pUser);
					}
				}
			}

			return;
		}
		else if (AntsIPCFrameType_SmartIFrames == i8Header->uiFrameType || AntsIPCFrameType_SmartPFrames == i8Header->uiFrameType) {
			if (AntsIPCFrameType_SmartIFrames == i8Header->uiFrameType) {
				struStreamHeader.iFrameType = 3;
			}
			else {
				struStreamHeader.iFrameType = 4;
			}
		}

		if (NULL != info[chIndex].pFunc) {
			QMutexLocker lck(&info[chIndex].pDevice->m_callbackMutex);

			if (NULL != info[chIndex].pFunc) {
				StreamFrameData *frameData = new StreamFrameData(struStreamHeader, (unsigned char *)lpBuffer, dwBufferSize);	//创建数据帧
				info[chIndex].pFunc(frameData, info[chIndex].pUser);
			}
		}
	}
}

/**********************************************
				告警回调
**********************************************/
void CALLBACK Http_AlarmMessageCallback(HANDLE hUserId, HANDLE hAlarmHandle, LONG lCommand, LPVOID lpAlarmInfo, DWORD dwAlarmInfoLen, LPVOID lpUser) {
	int alarmCount = dwAlarmInfoLen / sizeof(I8H_ALARMINFO_V2);

	I8HCache *pCache = NULL;
	{
		QMutexLocker locker(&DeviceHttp::sta_mutexCache);
		if (!DeviceHttp::sta_mapCache.contains(hUserId))
			return;
		pCache = DeviceHttp::sta_mapCache[hUserId];
	}
	if (NULL == pCache)
		return;

	QSharedPointer<DeviceContext> pContext = DeviceContext::getInstanceBySerial(pCache->m_strSerialNum);
	if (pContext.isNull())
		return;

	if (lpAlarmInfo != NULL) {
		I8H_ALARMINFO_V2* lpAlarm = (I8H_ALARMINFO_V2*)lpAlarmInfo;

		for (int index = 0; index < alarmCount; index++) {
			CMS_CONNECT_PARSE_AlarmType eAlarmType;
			int iParam;

			if (lpAlarm->wState == 0)
				continue;

			if (5 == pCache->m_iVersion || 10 == pCache->m_iVersion) {
				if (I8H_EVENT_CH_EVENT == lpAlarm->dwMainAlarmType) {
					if (I8H_EVENT_MD == lpAlarm->dwSubAlarmType) {
						eAlarmType = AlarmType_Motion;
					}
					else if (I8H_EVENT_OD == lpAlarm->dwSubAlarmType) {
						eAlarmType = AlarmType_Shelter;
					}
					else if (I8H_EVENT_VIDEO_LOST == lpAlarm->dwSubAlarmType) {
						eAlarmType = AlarmType_VideoLoss;
					}
					else if (I8H_EVENT_SMART_OBJECT_COUNT == lpAlarm->dwSubAlarmType) {
						eAlarmType = AlarmType_Count;
					}
					else if (I8H_EVENT_SMART_CROSS_LINE == lpAlarm->dwSubAlarmType) {
						eAlarmType = AlarmType_Wire;
					}
					else if (I8H_EVENT_SMART_REGION_DETECT == lpAlarm->dwSubAlarmType) {
						eAlarmType = AlarmType_Area;
					}
					else if (I8H_EVENT_SMART_GOODS_DETECT == lpAlarm->dwSubAlarmType) {
						eAlarmType = AlarmType_Object;
					}
					else {
						continue;
					}

					iParam = QString((char *)lpAlarm->lpBuffer).toInt();
				}
				else if (I8H_EVENT_ALARM_EVENT == lpAlarm->dwMainAlarmType) {
					eAlarmType = AlarmType_AlarmIn;

					if (I8H_EVENT_LOCAL_ALRAM_IN == lpAlarm->dwSubAlarmType) {
						iParam = QString((char *)lpAlarm->lpBuffer).toInt();
					}
					else {
						iParam = QString((char *)lpAlarm->lpBuffer).toInt() + pCache->m_iChannelCount;
					}
				}
				else {
					continue;
				}
			}
			else {
				if (I8H_ALARMTYPE_ALARMIN == lpAlarm->dwMainAlarmType) {
					eAlarmType = AlarmType_AlarmIn;
				}
				else if (I8H_ALARMTYPE_VIDEOLOSS == lpAlarm->dwMainAlarmType) {
					eAlarmType = AlarmType_VideoLoss;
				}
				else if (I8H_ALARMTYPE_MOTION == lpAlarm->dwMainAlarmType) {
					eAlarmType = AlarmType_Motion;
				}
				else if (I8H_ALARMTYPE_MASK == lpAlarm->dwMainAlarmType) {
					eAlarmType = AlarmType_Shelter;
				}
				else if (I8H_ALARMTYPE_IVS_COUNTWIRE == lpAlarm->dwMainAlarmType) {
					eAlarmType = AlarmType_Count;
				}
				else if (I8H_ALARMTYPE_IVS_DETECTWIRE == lpAlarm->dwMainAlarmType) {
					eAlarmType = AlarmType_Wire;
				}
				else if (I8H_ALARMTYPE_IVS_DETECTREGION == lpAlarm->dwMainAlarmType) {
					eAlarmType = AlarmType_Area;
				}
				else if (I8H_ALARMTYPE_IVS_OBJECTREGION == lpAlarm->dwMainAlarmType) {
					eAlarmType = AlarmType_Object;
				}
				else {
					continue;
				}

				iParam = QString((char *)lpAlarm->lpBuffer).toInt();
			}


			if (NULL != pContext->m_pDevice && NULL != pContext->m_pDevice->m_pAlarmCallbackFunc) {
				pContext->m_pDevice->m_pAlarmCallbackFunc(eAlarmType, pContext->m_pDevice->serialNum(), iParam, pContext->m_pDevice->m_pAlarmCallbackUser);
			}

			lpAlarm += 1;
		}
	}
	if (((1 << 31) & lCommand) != 0) {
		I8H_SDK_FreeMemory((BYTE *)lpAlarmInfo);
	}
}

/**********************************************
				异常回调
**********************************************/
void CALLBACK exceptionCallBack(DWORD dwType, HANDLE hUserId, HANDLE hHandle, LPVOID lpUser) {
	I8HCache *pCache = NULL;
	{
		QMutexLocker locker(&DeviceHttp::sta_mutexCache);
		if (!DeviceHttp::sta_mapCache.contains(hUserId))
			return;
		pCache = DeviceHttp::sta_mapCache[hUserId];
	}
	if (NULL == pCache)
		return;
	QSharedPointer<DeviceContext> pContext = DeviceContext::getInstanceBySerial(pCache->m_strSerialNum);
	if (pContext.isNull())
		return;

	if (dwType == I8H_DEVICE_ONLINE) {
		int iDeviceId = SqlConnection::FindDeviceBySerialNum(pContext->m_pDevice->serialNum());
		if (0 != iDeviceId) {
			SqlConnection::UpdateDeviceOnOfflineById(iDeviceId, true);
		}
		pContext->setOnline(true);
	}
	else if (dwType == I8H_DEVICE_OFFLINE) {
		int iDeviceId = SqlConnection::FindDeviceBySerialNum(pContext->m_pDevice->serialNum());
		if (0 != iDeviceId) {
			SqlConnection::UpdateDeviceOnOfflineById(iDeviceId, false);
		}
		pContext->setOnline(false);
	}
}

void CALLBACK transAlarmCallBack(HANDLE hUserId, BYTE *lpBuffer, DWORD dwBufferSize, LPVOID lpUser) {

}

bool DeviceHttp::startService() {
	QString configfile = QCoreApplication::applicationDirPath() + "/self.pem";
	I8H_INIT_PARAM initParam = { 0 };
	strcpy((char *)initParam.byKeyPath, configfile.toUtf8().data());
	initParam.byEnableHeartBeat = true;
	initParam.bAsync = TRUE;
	BOOL res = I8H_SDK_Initv2(&initParam);
	if (res) {
		I8H_SDK_SetExceptionCallBack(exceptionCallBack, NULL);
		I8H_SDK_SetAlarmDataCallBackv3(Http_AlarmMessageCallback, NULL);
	}
	else {
		int ret = I8H_SDK_GetLastError();
	}
	return res;
}

bool DeviceHttp::stopService() {
	return I8H_SDK_Cleanup();
}



bool DeviceHttp::login(QString strUsername, QString strPassword, LoginInfo &sLoginInfo) {
	I8H_DEVICEINFO strDevInfo = { 0 };
	HANDLE loginHandle = I8H_SDK_Login(sLoginInfo.strDeviceIP.toUtf8().data(), sLoginInfo.iDevicePort, strUsername.toUtf8().data(), strPassword.toUtf8().data(), &strDevInfo);

	if (NULL != loginHandle) {
		//登陆成功之后就将此设备记录下来
		sLoginInfo.handle = loginHandle;
		sLoginInfo.strSerialNum = QString((char *)strDevInfo.bySerialNumber).toUpper();
		if (1 == strDevInfo.wDVRType)
			sLoginInfo.eDeviceType = DeviceType_DVR;
		else if (2 == strDevInfo.wDVRType)
			sLoginInfo.eDeviceType = DeviceType_NVR;
		else if (3 == strDevInfo.wDVRType)
			sLoginInfo.eDeviceType = DeviceType_IPC;
		else if (5 == strDevInfo.wDVRType)
			sLoginInfo.eDeviceType = DeviceType_NVR_2;
		else if (8 == strDevInfo.wDVRType)
			sLoginInfo.eDeviceType = DeviceType_NVR_2;
		else {
			I8H_SDK_Logout(loginHandle);
			return false;
		}

		//if (sLoginInfo.eDeviceType == DeviceType_IPC && strDevInfo.byVer == I8H_IPC_OVFS_NGINX) {
		//	sLoginInfo.eDeviceType = DeviceType_IPC_2;
		//}
		//else if (sLoginInfo.eDeviceType == DeviceType_IPC && strDevInfo.byVer == I8H_IPC_FISHEYE_NGINX) {
		//	sLoginInfo.eDeviceType = DeviceType_IPC_FISH;
		//}


		sLoginInfo.iChannelCount = strDevInfo.wChanNum;
		sLoginInfo.iAlarmInCount = strDevInfo.wAlarmInNum;
		sLoginInfo.iAlarmOutCount = strDevInfo.wAlarmOutNum;

		if (-1 != g_iMaxExtendedCount[I8HDeviceAuthorityIndex] && g_iCurrentExtendedCount[I8HDeviceAuthorityIndex] + sLoginInfo.iChannelCount > g_iMaxExtendedCount[I8HDeviceAuthorityIndex]) {
			I8H_SDK_Logout(loginHandle);

			return false;
		}

		QList<QString> chNames = getChName(strDevInfo.byVer, loginHandle, sLoginInfo.strDeviceIP, strUsername, strPassword);

		for (int i = 0; i < sLoginInfo.iChannelCount; i++) {
			QString chName = QString("CH%1").arg(i + 1, 2, 10, QChar('0'));
			if (i < chNames.size() && "" != chNames[i]) {
				chName = chNames[i];
			}

			sLoginInfo.vecChannelName.append(chName);
		}

		I8HCache *cache = new I8HCache(strUsername, strPassword, sLoginInfo.strSerialNum, sLoginInfo.strDeviceIP, sLoginInfo.iDevicePort, (int)sLoginInfo.eDeviceType, strDevInfo.byVer, sLoginInfo.iChannelCount);
		QMutexLocker locker(&DeviceHttp::sta_mutexCache);
		DeviceHttp::sta_mapCache.insert(loginHandle, cache);

		return true;
	}
	else {
		return false;
	}
}

int DeviceHttp::logout(HANDLE handle) {
	int chCount = 0;
	{
		QMutexLocker locker(&DeviceHttp::sta_mutexCache);
		I8HCache *cache = DeviceHttp::sta_mapCache.take(handle);
		if (NULL != cache) {
			chCount = cache->m_iChannelCount;
			delete cache;
			cache = NULL;
		}
	}

	I8H_SDK_Logout(handle);
	return chCount;
}

//HANDLE sta_lRealHandle[512];

bool DeviceHttp::openRealtime(int iChNo, CMS_CONNECT_PARSE_StreamType eStreamType, CMS_STREAMDATA_CALLBACK func, void *pUser) {
	if (NULL == connectionHandle())
		return false;

	int chIndex;
	if (StreamType_Main == eStreamType)//开主码流
	{
		chIndex = iChNo - 1;
	}
	else {
		chIndex = iChNo - 1 + 256;
	}

	{
		QMutexLocker lck(&m_callbackMutex);
		if (NULL != m_streamInfo[chIndex].pFunc) {
			return true;
		}
	}

	//I8H_CLIENTINFO struClientInfo;
	//memset(&struClientInfo, 0, sizeof(I8H_CLIENTINFO));
	//struClientInfo.lChannel = iChNo;
	//struClientInfo.lLinkMode = (8 * 1024) << 16;

	//if (RTP_OVER_TCP == m_rtpType) {
	//	if (StreamType_Main == eStreamType)//开主码流
	//	{
	//		struClientInfo.lLinkMode |= 0;//!TCP主码流方式
	//	} else {
	//		struClientInfo.lLinkMode |= (1 << 8);//!TCP子码流方式
	//	}
	//} else {
	//	if (StreamType_Main == eStreamType)//开主码流
	//	{
	//		struClientInfo.lLinkMode |= 1;//!UDP主码流方式
	//	} else {
	//		struClientInfo.lLinkMode |= (1 | (1 << 8));//!UDP子码流方式
	//	}
	//}

	//sta_lRealHandle[chIndex] = I8H_SDK_RealPlay(
	//	this->connectionHandle(),
	//	&struClientInfo,
	//	Http_RealData_CallBack,
	//	(LPVOID)m_streamInfo);

	//if (sta_lRealHandle[chIndex] == NULL) {
	//	qDebug() << "I8H_SDK_RealPlay failed" << I8H_SDK_GetLastError();
	//	return false;
	//}

	//I8H_CHANNEL_INFO struChannelInfo;
	//struChannelInfo.wChannel = iChNo;
	//struChannelInfo.byAudioFlag = 1;
	//if (StreamType_Main == eStreamType)//开主码流
	//{
	//    struChannelInfo.byStreamType = 0;
	//}
	//else
	//{
	//    struChannelInfo.byStreamType = 1;
	//}
	//I8H_SDK_ControlRealPlay(sta_lRealHandle[chIndex], I8H_REALPLAY_PLAYSTARTAUDIO, &struChannelInfo, sizeof(struChannelInfo));

	{
		QMutexLocker locker(&m_realtimeParam[chIndex / 8].m_mutex_realtimeChannelOpened);
		I8H_CHANNEL_INFO struChannelInfo;
		struChannelInfo.wChannel = iChNo;
		struChannelInfo.byAudioFlag = 1;
		if (StreamType_Main == eStreamType)//开主码流
		{
			struChannelInfo.byStreamType = 0;
		}
		else {
			struChannelInfo.byStreamType = 1;
		}
		if (m_realtimeParam[chIndex / 8].m_realtimeChannelOpened > 0) {
			if (!I8H_SDK_ControlRealPlay(m_realtimeParam[chIndex / 8].m_lRealHandle, I8H_REALPLAY_ADDCHAN, &struChannelInfo, sizeof(struChannelInfo))) {
				qDebug() << "I8H_SDK_ControlRealPlay add chan failed.handle:" << m_realtimeParam[chIndex / 8].m_lRealHandle << I8H_SDK_GetLastError();
				return false;
			}
		}
		else {
			I8H_CLIENTINFO struClientInfo;
			memset(&struClientInfo, 0, sizeof(I8H_CLIENTINFO));
			struClientInfo.lChannel = (iChNo & 0xFFFF) + (0x03 << 28);
			struClientInfo.lLinkMode = (8 * 1024) << 16;

			if (RTP_OVER_TCP == m_rtpType) {
				if (StreamType_Main == eStreamType)//开主码流
				{
					struClientInfo.lLinkMode |= 0;//!TCP主码流方式
				}
				else {
					struClientInfo.lLinkMode |= (1 << 8);//!TCP子码流方式
				}
			}
			else {
				if (StreamType_Main == eStreamType)//开主码流
				{
					struClientInfo.lLinkMode |= 1;//!UDP主码流方式
				}
				else {
					struClientInfo.lLinkMode |= (1 | (1 << 8));//!UDP子码流方式
				}
			}

			m_realtimeParam[chIndex / 8].m_lRealHandle = I8H_SDK_RealPlay(
				this->connectionHandle(),
				&struClientInfo,
				Http_RealData_CallBack,
				(LPVOID)m_streamInfo);

			if (m_realtimeParam[chIndex / 8].m_lRealHandle == NULL) {
				qDebug() << "I8H_SDK_RealPlay failed" << I8H_SDK_GetLastError();
				return false;
			}

			qDebug() << "I8H_SDK_RealPlay succ. ch:" << iChNo << "stream type:" << eStreamType << "handle:" << m_realtimeParam[chIndex / 8].m_lRealHandle;
		}

		I8H_SDK_ControlRealPlay(m_realtimeParam[chIndex / 8].m_lRealHandle, I8H_REALPLAY_PLAYSTARTAUDIO, &struChannelInfo, sizeof(struChannelInfo));

		m_realtimeParam[chIndex / 8].m_realtimeChannelOpened++;
	}

	{
		QMutexLocker lck(&m_callbackMutex);
		m_streamInfo[chIndex].pFunc = func;
		m_streamInfo[chIndex].pUser = pUser;
		strcpy(m_streamInfo[chIndex].cSerialNum, this->serialNum().toUtf8().data());
		m_streamInfo[chIndex].iChannel = iChNo;
		m_streamInfo[chIndex].eStreamType = eStreamType;
		m_streamInfo[chIndex].pDevice = this;
	}

	//sta_frameNo[chIndex] = 0;

	qDebug() << "open I8H realplay succ" << iChNo << eStreamType;
	return true;
}

bool DeviceHttp::closeRealtime(int iChNo, CMS_CONNECT_PARSE_StreamType eStreamType) {
	int chIndex;
	if (StreamType_Main == eStreamType)//开主码流
	{
		chIndex = iChNo - 1;
	}
	else {
		chIndex = iChNo - 1 + 256;
	}

	{
		QMutexLocker lck(&m_callbackMutex);
		if (NULL == m_streamInfo[chIndex].pFunc) {
			return true;
		}

		if (0 == m_realtimeParam[chIndex / 8].m_lRealHandle) {
			return true;
		}
	}

	//if (!I8H_SDK_StopRealPlay(sta_lRealHandle[chIndex]))
	//{
	//	qDebug() << "I8H_SDK_StopRealPlay failed.handle:" << sta_lRealHandle[chIndex] << I8H_SDK_GetLastError();
	//	return false;
	//}

	{
		QMutexLocker locker(&m_realtimeParam[chIndex / 8].m_mutex_realtimeChannelOpened);
		if (m_realtimeParam[chIndex / 8].m_realtimeChannelOpened > 1) {
			I8H_CHANNEL_INFO struChannelInfo;
			struChannelInfo.wChannel = iChNo;
			struChannelInfo.byAudioFlag = 1;
			if (StreamType_Main == eStreamType)//开主码流
			{
				struChannelInfo.byStreamType = 0;
			}
			else {
				struChannelInfo.byStreamType = 1;
			}
			if (!I8H_SDK_ControlRealPlay(m_realtimeParam[chIndex / 8].m_lRealHandle, I8H_REALPLAY_DELCHAN, &struChannelInfo, sizeof(struChannelInfo))) {
				//if (I8H_ERROR_CODE_CALL3THAPI_ERROR == I8H_SDK_GetLastError()) {
				qDebug() << "I8H_SDK_ControlRealPlay del chan failed.handle:" << m_realtimeParam[chIndex / 8].m_lRealHandle << I8H_SDK_GetLastError();
				return false;
				//}
			}
		}
		else {
			if (!I8H_SDK_StopRealPlay(m_realtimeParam[chIndex / 8].m_lRealHandle)) {
				qDebug() << "I8H_SDK_StopRealPlay failed.handle:" << m_realtimeParam[chIndex / 8].m_lRealHandle << I8H_SDK_GetLastError();
				return false;
			}

			m_realtimeParam[chIndex / 8].m_lRealHandle = 0;
		}
		m_realtimeParam[chIndex / 8].m_realtimeChannelOpened--;
	}

	{
		QMutexLocker lck(&m_callbackMutex);
		m_streamInfo[chIndex].pFunc = NULL;
		m_streamInfo[chIndex].pUser = NULL;
	}

	return true;
}

void DeviceHttp::clearRealtimeCount() {
	for (int i = 0; i < 512; ++i) {
		m_streamInfo[i].pFunc = NULL;
		m_streamInfo[i].pUser = NULL;
	}

	for (int i = 0; i < 512 / 8; ++i) {
		{
			QMutexLocker locker(&m_realtimeParam[i].m_mutex_realtimeChannelOpened);
			m_realtimeParam[i].m_realtimeChannelOpened = 0;

			qDebug() << "clearRealtimeCount set realhandle=0";
			if (0 != m_realtimeParam[i].m_lRealHandle) {
				I8H_SDK_StopRealPlay(m_realtimeParam[i].m_lRealHandle);
				m_realtimeParam[i].m_lRealHandle = 0;
			}
		}
	}
}

/**********************************************
				对讲回调
**********************************************/
void CALLBACK Http_Intercom_CallBack(HANDLE hVoiceHandle, BYTE *lpBuffer, DWORD dwBufferSize, DWORD dwAudioOpt, LPVOID lpUser) {
	//printf("~");
	DeviceHttp::I8H_StreamInfo *info = (DeviceHttp::I8H_StreamInfo *)lpUser;
	if (NULL == info->pFunc) {
		return;
	}

	CMS_CONNECT_PARSE_StreamHeader struStreamHeader = { 0 };
	struStreamHeader.iFrameType = 0;//音频帧
	struStreamHeader.unionMedia.struAudioMedia.cCodecId = 1;//音频编码格式，1-G711-U
	struStreamHeader.unionMedia.struAudioMedia.cSampleRate = 1;//采样率, 1-8000HZ
	struStreamHeader.unionMedia.struAudioMedia.cBitRate = 2;//比特率,2-16bit
	struStreamHeader.unionMedia.struAudioMedia.cChannels = 1;//通道数,1-单通道
	struStreamHeader.unionMedia.struAudioMedia.cResolution = 0;
	struStreamHeader.iChannel = info->iChannel;
	strcpy(struStreamHeader.cSerialNum, info->cSerialNum);
	struStreamHeader.eStreamType = info->eStreamType;

	StreamFrameData* frameData = new StreamFrameData(struStreamHeader, (unsigned char *)lpBuffer, dwBufferSize);	//创建数据帧
	info->pFunc(frameData, info->pUser);
}

bool DeviceHttp::openIntercom(int iChNo, CMS_STREAMDATA_CALLBACK func, void *pUser) {
	QMutexLocker locker(&m_mutex_intercomHandle);
	if (m_intercomHandle == 0) {
		strcpy(m_intercomStreamInfo.cSerialNum, this->serialNum().toUtf8().data());
		m_intercomStreamInfo.eStreamType = StreamType_Intercom;
		m_intercomStreamInfo.iChannel = iChNo;
		m_intercomStreamInfo.pFunc = func;
		m_intercomStreamInfo.pUser = pUser;
		m_intercomHandle = I8H_SDK_StartVoiceComv2(m_hConnection, (DWORD)iChNo, Http_Intercom_CallBack, (LPVOID)(&m_intercomStreamInfo), I8H_G711_U);
		if (m_intercomHandle != NULL) {
			return true;
		}
	}
	return false;
}

bool DeviceHttp::closeIntercom(int iChNo) {
	{
		QMutexLocker locker(&m_mutex_intercomHandle);
		if (!I8H_SDK_StopVoiceCom(m_intercomHandle)) {
			return false;
		}

		m_intercomHandle = NULL;
	}
	return true;
}

bool DeviceHttp::sendIntercom(CMS_CONNECT_PARSE_StreamHeader header, unsigned char * lpBuffer, unsigned int iBufferSize) {
	if (lpBuffer == NULL || iBufferSize <= 0) {
		return false;
	}

	if (m_intercomHandle != NULL) {
		/*
		 * 音频编码类型[codeId]bit0~bit7:1--G711_U
		   采样率[sampleRate]bit8~bit15:0--8000HZ
		   位率[bitRate]bit16~bit23:0--16bit
		   声道[channels]bit24~bit31:1--单声道
		 */
		char codeId = 1;
		char sampleRate = 0;
		char bitRate = 0;
		char channels = 1;
		DWORD dwOpt = codeId | (sampleRate << 8) | (bitRate << 16) | (channels << 24);
		if (I8H_SDK_VoiceComSendDatav2(m_intercomHandle, dwOpt, lpBuffer, iBufferSize)) {
			return true;
		}

	}
	return false;
}

QString getJsonValue(QString json, QString key) {
	QString keyInContent = QString("\"%1\":").arg(key);
	int begin = json.indexOf(keyInContent) + keyInContent.size();
	int end = json.indexOf(',', begin);
	QString value = json.mid(begin, end - begin);
	if (2 <= value.size() && value.at(0) == QChar('\"') && value.at(value.size() - 1) == QChar('\"')) {
		value = value.mid(1, value.size() - 2);
	}
	return value;
}

QString replaceJsonValue(QString json, QString key, QString value) {
	QString keyInContent = QString("\"%1\":").arg(key);
	int begin = json.indexOf(keyInContent) + keyInContent.size();
	int end = json.indexOf(',', begin);
	return json.replace(begin, end - begin, value);
}

bool DeviceHttp::ptzCtrl(int iChNo, CMS_CONNECT_PARSE_PtzCmdType eCmdType, int isStop, int iSpeed) {

	I8HCache *cache = DeviceHttp::sta_mapCache.value(this->connectionHandle());
	if (NULL == cache)
		return false;

	//鱼眼通道的云台操作
	if (I8H_IPC_FISHEYE_NGINX == cache->m_iVersion)
	{
		BYTE lpOutBuffer[8192];
		memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
		DWORD dwOutBufSize = 8192;
		DWORD dwOutSize = 0;

		QString strUrl("frmFisheyeChanMove");
		QJsonObject req;
		req["Ch"] = 1;
		req["Type"] = 1;
		QJsonObject data;
		data["ChanNum"] = iChNo - 1;
		data["Operation"] = "ContinousMove";

		float fSpeed = iSpeed*0.1;

		switch (eCmdType) {
		case PtzCtrlType_ZoomIn:
			data["ZoomRate"] = 1; //-1表示缩小,0表示停止,1表示放大
			data["ZoomSpeed"] = fSpeed; //倍率速度：0~1.0
			break;
		case PtzCtrlType_ZoomOut:
			data["ZoomRate"] = -1;
			data["ZoomSpeed"] = fSpeed;
			break;
		case PtzCtrlType_TiltUp:
			data["TiltAngle"] = 1;  //-1表示下,0表示停止,1表示上
			data["TiltSpeed"] = fSpeed;  //垂直移动速度：0~1.00~1.0
			break;
		case PtzCtrlType_TiltDown:
			data["TiltAngle"] = -1;
			data["TiltSpeed"] = fSpeed;
			break;
		case PtzCtrlType_PanLeft:
			data["PanAngle"] = -1;  //-1表示左,0表示停止,1表示右
			data["PanSpeed"] = fSpeed; //水平移动速度：0~1.0
			break;
		case PtzCtrlType_PanRight:
			data["PanAngle"] = 1;
			data["PanSpeed"] = fSpeed;
			break;
		case PtzCtrlType_UpLeft:
			data["PanAngle"] = -1;
			data["PanSpeed"] = fSpeed;
			data["TiltAngle"] = 1;
			data["TiltSpeed"] = fSpeed;
			break;
		case PtzCtrlType_UpRight:
			data["PanAngle"] = 1;
			data["PanSpeed"] = fSpeed;
			data["TiltAngle"] = 1;
			data["TiltSpeed"] = fSpeed;
			break;
		case PtzCtrlType_DownLeft:
			data["PanAngle"] = -1;
			data["PanSpeed"] = fSpeed;
			data["TiltAngle"] = -1;
			data["TiltSpeed"] = fSpeed;
			break;
		case PtzCtrlType_DownRight:
			data["PanAngle"] = 1;
			data["PanSpeed"] = fSpeed;
			data["TiltAngle"] = -1;
			data["TiltSpeed"] = fSpeed;
			break;
		case PtzCtrlType_Auto:
			data["Operation"] = "Auto";
			data["PanAngle"] = 1;
			data["PanSpeed"] = fSpeed;
			break;
		default:
			return false;
			break;
		}

		if (isStop == 1)
		{
			data["PanAngle"] = 0;
			data["TiltAngle"] = 0;
			data["ZoomRate"] = 0;
		}

		req["Data"] = data;

		QByteArray baReq = QJsonDocument(req).toJson();

		memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)baReq.data(), baReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		if (0 != getJsonValue(QString((char*)lpOutBuffer), "Result").toInt())
			return false;

		return true;
	}


	DWORD cmd;
	switch (eCmdType) {
	case PtzCtrlType_LightPowerOn:
		cmd = I8H_LIGHT_PWRON;
		break;
	case PtzCtrlType_WiperPowerOn:
		cmd = I8H_WIPER_PWRON;
		break;
	case PtzCtrlType_FanPowerOn:
		cmd = I8H_FAN_PWRON;
		break;
	case PtzCtrlType_ZoomIn:
		cmd = I8H_ZOOM_IN;
		break;
	case PtzCtrlType_ZoomOut:
		cmd = I8H_ZOOM_OUT;
		break;
	case PtzCtrlType_FocusNear:
		cmd = I8H_FOCUS_NEAR;
		break;
	case PtzCtrlType_FocusFar:
		cmd = I8H_FOCUS_FAR;
		break;
	case PtzCtrlType_IrisOpen:
		cmd = I8H_IRIS_OPEN;
		break;
	case PtzCtrlType_IrisClose:
		cmd = I8H_IRIS_CLOSE;
		break;
	case PtzCtrlType_TiltUp:
		cmd = I8H_TILT_UP;
		break;
	case PtzCtrlType_TiltDown:
		cmd = I8H_TILT_DOWN;
		break;
	case PtzCtrlType_PanLeft:
		cmd = I8H_PAN_LEFT;
		break;
	case PtzCtrlType_PanRight:
		cmd = I8H_PAN_RIGHT;
		break;
	case PtzCtrlType_UpLeft:
		cmd = I8H_UP_LEFT;
		break;
	case PtzCtrlType_UpRight:
		cmd = I8H_UP_RIGHT;
		break;
	case PtzCtrlType_DownLeft:
		cmd = I8H_DOWN_LEFT;
		break;
	case PtzCtrlType_DownRight:
		cmd = I8H_DOWN_RIGHT;
		break;
	case PtzCtrlType_Auto:
		cmd = I8H_PAN_AUTO;
		break;
	default:
		return false;
		break;
	}

	return I8H_SDK_PTZControl(m_hConnection, iChNo, cmd, isStop, iSpeed);
}

bool DeviceHttp::presetCtrl(int iChNo, int iPresetIndex, CMS_CONNECT_PARSE_PresetCmdType eCmdType) {

	I8HCache *cache = DeviceHttp::sta_mapCache.value(this->connectionHandle());
	if (NULL == cache)
		return false;

	//鱼眼通道的预置点操作
	if (I8H_IPC_FISHEYE_NGINX == cache->m_iVersion)
	{
		BYTE lpOutBuffer[8192];
		memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
		DWORD dwOutBufSize = 8192;
		DWORD dwOutSize = 0;

		QString strUrl("frmFisheyeChanPreset");
		QJsonObject req;
		req["Ch"] = 1;

		int type;   //0-获取 1-设置 2-调用 3-删除
		if (PresetCtrlType_Set == eCmdType) {
			type = 1;
		}
		else if (PresetCtrlType_Clear == eCmdType) {
			type = 3;
		}
		else if (PresetCtrlType_Goto == eCmdType) {
			type = 2;
		}
		else {
			return false;
		}

		req["Type"] = type;
		QJsonObject data;
		data["ChanNum"] = iChNo - 1;
		data["Preset"] = iPresetIndex;
		req["Data"] = data;
		QByteArray baReq = QJsonDocument(req).toJson();

		memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)baReq.data(), baReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		if (0 != getJsonValue(QString((char*)lpOutBuffer), "Result").toInt())
			return false;

		return true;

	}



	DWORD cmd;
	if (PresetCtrlType_Set == eCmdType) {
		cmd = I8H_SET_PRESET;
	}
	else if (PresetCtrlType_Clear == eCmdType) {
		cmd = I8H_CLE_PRESET;
	}
	else if (PresetCtrlType_Goto == eCmdType) {
		cmd = I8H_GOTO_PRESET;
	}
	else {
		return false;
	}
	return I8H_SDK_PTZPreset(m_hConnection, iChNo, cmd, iPresetIndex);
}

bool DeviceHttp::getCruise(int iChNo, int iCruiseRoute, CMS_CONNECT_PARSE_CruisePoint_Param * &results, int &iParamCount) {
	I8H_CRUISE_RET struCruiseRet;
	memset(&struCruiseRet, 0, sizeof(I8H_CRUISE_RET));
	if (I8H_SDK_GetPTZCruise(m_hConnection, iChNo, iCruiseRoute, &struCruiseRet)) {
		for (int i = 0; i < sizeof(I8H_CRUISE_RET) / sizeof(I8H_CRUISE_POINT); i++) {
			if (0 == struCruiseRet.struCruisePoint[i].byPresetNo) {
				break;
			}
			iParamCount++;
		}
		/* 在外面delete */
		results = new CMS_CONNECT_PARSE_CruisePoint_Param[iParamCount];
		memset(results, 0, sizeof(CMS_CONNECT_PARSE_CruisePoint_Param)*iParamCount);
		for (int i = 0; i < iParamCount; i++) {
			results[i].iPreset = struCruiseRet.struCruisePoint[i].byPresetNo;
			results[i].iStaySec = struCruiseRet.struCruisePoint[i].byDWell;
			results[i].iSpeed = struCruiseRet.struCruisePoint[i].bySpeed;
		}
		return true;
	}
	else {
		return false;
	}
}

bool DeviceHttp::setCruise(int iChNo, int iCruiseRoute, int iCruisePoint, CMS_CONNECT_PARSE_CruisePoint_Param request) {
	DWORD wInput = request.iStaySec & 0xFFFF;
	wInput = wInput | ((request.iSpeed << 16) & 0xFF0000);
	wInput = wInput | ((request.iPreset << 24) & 0xFF000000);
	//wInput:输入参数 bit0-bit15:dwell, bit16-bit23:speed, bit24-bit32:preset
	return I8H_SDK_PTZCruise(m_hConnection, iChNo, I8H_ADD_CRUISE_ROUTE_POINT, iCruiseRoute, iCruisePoint, wInput);
}

bool DeviceHttp::deleteCruise(int iChNo, int iCruiseRoute, int iCruisePoint) {
	return I8H_SDK_PTZCruise(m_hConnection, iChNo, I8H_DEL_CRUISE_ROUTE_POINT, iCruiseRoute, iCruisePoint, 0);
}

bool DeviceHttp::clearCruise(int iChNo, int iCruiseRoute) {
	return I8H_SDK_PTZCruise(m_hConnection, iChNo, I8H_DEL_CRUISE_ROUTE, iCruiseRoute, 0, 0);
}

bool DeviceHttp::runCruise(int iChNo, int iCruiseRoute, int isRun) {
	return I8H_SDK_PTZCruise(m_hConnection, iChNo, (isRun == 0) ? I8H_RUN_CRUISE_ROUTE : I8H_STOPRUN_CRUISE_ROUTE, iCruiseRoute, 0, 0);
}

//轨迹
bool DeviceHttp::locusCtrl(int iChNo, int iLocusIndex, int iCmd, int isStop) {
	WORD wTrackCmd;
	if (LOCUS_SET == iCmd) {
		if (!isStop) {
			wTrackCmd = I8H_START_TRACK;//!开始记录轨迹
		}
		else {
			wTrackCmd = I8H_STOP_TRACK;//!停止记录轨迹
		}
	}
	else if (LOCUS_RUN == iCmd) {
		wTrackCmd = I8H_RUN_TRACK;//!运行记录轨迹
	}
	else {
		return false;
	}
	return I8H_SDK_PTZTrack(m_hConnection, iChNo, wTrackCmd, iLocusIndex);
}

bool DeviceHttp::set3D(int iChNo, int iTopX, int iTopY, int iBottomX, int iBottomY) {
	return I8H_SDK_PTZSet3D(m_hConnection, iChNo, iTopX, iTopY, iBottomX, iBottomY);
}

bool DeviceHttp::searchRecord(CMS_CONNECT_PARSE_StreamType eStreamType,
	time_t beginTime,
	time_t endTime,
	unsigned int iRecordType,
	CMS_CONNECT_PARSE_RecordType_Condition eRecordType_Condition,
	QList<int> listChNo,
	CMS_CONNECT_PARSE_SearchRecord_Param * &results,
	int &iResultsCount) {
	int iChannelCount = listChNo.size();
	if (iChannelCount <= 0) {
		return false;
	}
	I8HCache *cache = DeviceHttp::sta_mapCache.value(this->connectionHandle());
	if (NULL == cache)
		return false;

	I8H_FILECOND    findCond;
	I8H_FILECONDV2  findCondV2;
	QDateTime bDateTime = QDateTime::fromTime_t(beginTime).toUTC();
	I8H_TIME startTime;
	startTime.wYear = bDateTime.date().year();
	startTime.wMonth = bDateTime.date().month();
	startTime.wDay = bDateTime.date().day();
	startTime.wHour = bDateTime.time().hour();
	startTime.wMinute = bDateTime.time().minute();
	startTime.wSecond = bDateTime.time().second();
	findCond.struStartTime = startTime;
	findCondV2.struStartTime = startTime;

	QDateTime eDateTime = QDateTime::fromTime_t(endTime).toUTC();
	I8H_TIME stopTime;
	stopTime.wYear = eDateTime.date().year();
	stopTime.wMonth = eDateTime.date().month();
	stopTime.wDay = eDateTime.date().day();
	stopTime.wHour = eDateTime.time().hour();
	stopTime.wMinute = eDateTime.time().minute();
	stopTime.wSecond = eDateTime.time().second();
	findCond.struStopTime = stopTime;
	findCondV2.struStopTime = stopTime;

	//录像文件信息链表this->connectionHandle()
	QList<CMS_CONNECT_PARSE_SearchRecord_Param> Http_RecordInfoList;
	foreach(int iChannel, listChNo) {
		findCond.wChannel = iChannel;
		findCondV2.wChannel = iChannel;
		I8H_FINDDATA *lpOutBuffer = NULL;
		DWORD dwOutSize = 0;
		CMS_CONNECT_PARSE_SearchRecord_Param info;
		if (5 == cache->m_iVersion || 10 == cache->m_iVersion)/* 2.0设备 */
		{
			findCondV2.wIsAnd = (RecordType_Condition_Or == eRecordType_Condition) ? 0 : 1;
			int trigType = 0;
			if (0 != (iRecordType & RecordType_Regular)) {
				trigType |= I8H_REC_TRIG_BY_REGULAR;
			}
			if (0 != (iRecordType & RecordType_Motion)) {
				trigType |= I8H_REC_TRIG_BY_MD;
			}
			if (0 != (iRecordType & RecordType_Alarm)) {
				trigType |= I8H_REC_TRIG_BY_AI;
			}
			if (0 != (iRecordType & RecordType_Counter)) {
				trigType |= I8H_REC_TRIG_BY_COUNTER;
			}
			if (0 != (iRecordType & RecordType_Wire)) {
				trigType |= I8H_REC_TRIG_BY_WIRE;
			}
			if (0 != (iRecordType & RecordType_Region)) {
				trigType |= I8H_REC_TRIG_BY_REGION;
			}
			if (0 != (iRecordType & RecordType_Object)) {
				trigType |= I8H_REC_TRIG_BY_OBJECT;
			}
			findCondV2.wFileType = trigType;
			BOOL ret = I8H_SDK_FindFilev2(m_hConnection, &findCondV2, (BYTE **)(&lpOutBuffer), &dwOutSize);
			if (ret && lpOutBuffer != NULL) {
				int recordsCount = dwOutSize / sizeof(I8H_FINDDATA);
				for (int i = 0; i < recordsCount; i++) {
					memset(&info, 0, sizeof(info));
					strcpy(info.ch.cSerialNum, m_strSerialNum.toUtf8().data());
					info.ch.iChannel = iChannel;
					int fileType = lpOutBuffer[i].wFileType;
					if (0 != (fileType & 0x04)) {
						info.iRecordType |= RecordType_Alarm;
					}
					if (0 != (fileType & 0x02)) {
						info.iRecordType |= RecordType_Motion;
					}
					if (0 != (fileType & 0x08)) {
						info.iRecordType |= RecordType_Counter;
					}
					if (0 != (fileType & 0x10)) {
						info.iRecordType |= RecordType_Wire;
					}
					if (0 != (fileType & 0x20)) {
						info.iRecordType |= RecordType_Region;
					}
					if (0 != (fileType & 0x40)) {
						info.iRecordType |= RecordType_Object;
					}
					if (0 != (fileType & 0x01)) {
						info.iRecordType |= RecordType_Regular;
					}

					info.timeUTC_Begin = QDateTime(
						QDate(lpOutBuffer[i].struStartTime.wYear,
							lpOutBuffer[i].struStartTime.wMonth,
							lpOutBuffer[i].struStartTime.wDay),
						QTime(lpOutBuffer[i].struStartTime.wHour,
							lpOutBuffer[i].struStartTime.wMinute,
							lpOutBuffer[i].struStartTime.wSecond),
						Qt::UTC).toTime_t();
					info.timeUTC_End = QDateTime(
						QDate(lpOutBuffer[i].struStopTime.wYear,
							lpOutBuffer[i].struStopTime.wMonth,
							lpOutBuffer[i].struStopTime.wDay),
						QTime(lpOutBuffer[i].struStopTime.wHour,
							lpOutBuffer[i].struStopTime.wMinute,
							lpOutBuffer[i].struStopTime.wSecond),
						Qt::UTC).toTime_t();
					info.lFileSize = lpOutBuffer[i].dwFileSize;
					Http_RecordInfoList.append(info);
				}
				I8H_SDK_FreeMemory((BYTE *)lpOutBuffer);
			}
		}
		else {
			findCond.wFileType = 0xFF;//全部
			BOOL ret = I8H_SDK_FindFile(m_hConnection, &findCond, (BYTE **)(&lpOutBuffer), &dwOutSize);
			if (ret && lpOutBuffer != NULL) {
				int recordsCount = dwOutSize / sizeof(I8H_FINDDATA);
				for (int i = 0; i < recordsCount; i++) {
					strcpy(info.ch.cSerialNum, m_strSerialNum.toUtf8().data());
					info.ch.iChannel = iChannel;
					int fileType = lpOutBuffer[i].wFileType;
					switch (fileType) {
					case 0:
						info.iRecordType = RecordType_Schedule;
						break;
					case 1:
						info.iRecordType = RecordType_Motion;
						break;
					case 2:
						info.iRecordType = RecordType_Alarm;
						break;
					case 4:
						info.iRecordType = RecordType_Motion;
						break;
					case 6:
						info.iRecordType = RecordType_Manual;
						break;
					default:
						info.iRecordType = RecordType_Undefined;
						break;
					}
					info.timeUTC_Begin = QDateTime(
						QDate(lpOutBuffer[i].struStartTime.wYear,
							lpOutBuffer[i].struStartTime.wMonth,
							lpOutBuffer[i].struStartTime.wDay),
						QTime(lpOutBuffer[i].struStartTime.wHour,
							lpOutBuffer[i].struStartTime.wMinute,
							lpOutBuffer[i].struStartTime.wSecond),
						Qt::UTC).toTime_t();
					info.timeUTC_End = QDateTime(
						QDate(lpOutBuffer[i].struStopTime.wYear,
							lpOutBuffer[i].struStopTime.wMonth,
							lpOutBuffer[i].struStopTime.wDay),
						QTime(lpOutBuffer[i].struStopTime.wHour,
							lpOutBuffer[i].struStopTime.wMinute,
							lpOutBuffer[i].struStopTime.wSecond),
						Qt::UTC).toTime_t();
					info.lFileSize = lpOutBuffer[i].dwFileSize;
					Http_RecordInfoList.append(info);
				}
				I8H_SDK_FreeMemory((BYTE *)lpOutBuffer);
			}
		}
	}

	iResultsCount = Http_RecordInfoList.size();
	if (0 == iResultsCount) {
		return false;
	}
	//此处new的数组在本函数外面释放
	results = new CMS_CONNECT_PARSE_SearchRecord_Param[iResultsCount];
	for (int i = 0; i < iResultsCount; i++) {
		memcpy(&(results[i]), &(Http_RecordInfoList[i]), sizeof(CMS_CONNECT_PARSE_SearchRecord_Param));
	}
	return true;
}

void CALLBACK Http_Playback_CallBack(HANDLE hHandle, DWORD dwOption, DWORD dwDataType, BYTE *lpBuffer, DWORD dwBufferSize, LPVOID lpUser) {
	if (dwDataType == I8H_STREAMDATA_STREAMDATA || dwDataType == I8H_STREAMDATA_AUDIOSTREAMDATA) {
		ReplayInfo *replay = (ReplayInfo *)lpUser;
		if (replay == NULL) {
			return;
		}
		AntsIPCFrameHeader_T *i8Header = (AntsIPCFrameHeader_T *)lpBuffer;
		CMS_CONNECT_PARSE_StreamHeader struStreamHeader;
		struStreamHeader.iChannel = (dwOption >> 16) & 0xFFFF;
		strcpy(struStreamHeader.cSerialNum, replay->m_strSerialNum.toUtf8().data());

		//qDebug() << __FUNCTION__ << "i8Header->uiFrameType" << i8Header->uiFrameType;


		if (AntsIPCFrameType_IFrames == i8Header->uiFrameType || AntsIPCFrameType_SubIFrames == i8Header->uiFrameType) {
			struStreamHeader.iFrameType = 1;//帧类型，	0-音频帧；1-I帧；2-P帧
			struStreamHeader.unionMedia.struVideoMedia.cCodecId = i8Header->uMedia.struVideoHeader.cCodecId;
			struStreamHeader.unionMedia.struVideoMedia.uWidth = i8Header->uMedia.struVideoHeader.usWidth;
			struStreamHeader.unionMedia.struVideoMedia.uHeight = i8Header->uMedia.struVideoHeader.usHeight;
			//            qDebug()<<"#";
		}
		else if (AntsIPCFrameType_PFrames == i8Header->uiFrameType || AntsIPCFrameType_SubPFrames == i8Header->uiFrameType) {
			struStreamHeader.iFrameType = 2;//帧类型，	0-音频帧；1-I帧；2-P帧
			struStreamHeader.unionMedia.struVideoMedia.cCodecId = i8Header->uMedia.struVideoHeader.cCodecId;
			struStreamHeader.unionMedia.struVideoMedia.uWidth = i8Header->uMedia.struVideoHeader.usWidth;
			struStreamHeader.unionMedia.struVideoMedia.uHeight = i8Header->uMedia.struVideoHeader.usHeight;
			//            qDebug()<<"#";
		}
		else if (AntsIPCFrameType_AudioFrames == i8Header->uiFrameType) {
			struStreamHeader.iFrameType = 0;//帧类型，	0-音频帧；1-I帧；2-P帧
			struStreamHeader.unionMedia.struAudioMedia.cCodecId = i8Header->uMedia.struAudioHeader.cCodecId;
			struStreamHeader.unionMedia.struAudioMedia.cSampleRate = i8Header->uMedia.struAudioHeader.cSampleRate;
			struStreamHeader.unionMedia.struAudioMedia.cBitRate = i8Header->uMedia.struAudioHeader.cBitRate;
			struStreamHeader.unionMedia.struAudioMedia.cChannels = i8Header->uMedia.struAudioHeader.cChannels;
			struStreamHeader.unionMedia.struAudioMedia.cResolution = i8Header->uMedia.struAudioHeader.cResolution;
		}
		else if (AntsIPCFrameType_SmartIFrames == i8Header->uiFrameType) {
			struStreamHeader.iFrameType = 3;
		}
		else if (AntsIPCFrameType_SmartPFrames == i8Header->uiFrameType) {
			struStreamHeader.iFrameType = 4;
		}
		else {
			return;
		}

		struStreamHeader.timeUTC = i8Header->uiFrameTime;
		struStreamHeader.iMicroSec = i8Header->uiFrameTickCount;
		struStreamHeader.eStreamType = replay->m_eStreamType;

		if (NULL != replay->m_pFunc) {
			StreamFrameData frameData(struStreamHeader, (unsigned char *)lpBuffer, dwBufferSize);	//创建数据帧
			replay->m_pFunc(&frameData, replay->m_pUser);
		}
	}
	else {
		return;
	}
}

bool DeviceHttp::openReplay(ReplayInfo *replay) {
	QDateTime dtBegin = QDateTime::fromTime_t(replay->m_timeBegin).toUTC();
	QDateTime dtEnd = QDateTime::fromTime_t(replay->m_timeEnd).toUTC();

	int iCount = replay->m_listCh.size();
	for (int i = 0; i < iCount; i++) {
		I8H_CHANNEL_INFO struChannelInfo;
		struChannelInfo.wChannel = replay->m_listCh[i].iChannel;
		struChannelInfo.byAudioFlag = 1;
		if (StreamType_Main == replay->m_eStreamType)//开主码流
		{
			struChannelInfo.byStreamType = 0;
		}
		else {
			struChannelInfo.byStreamType = 1;
		}
		if (0 == i) {
			I8H_PLAYBACK_COND cond;
			memset(&cond, 0, sizeof(I8H_PLAYBACK_COND));

			cond.wChannel = replay->m_listCh[i].iChannel;
			cond.wStreamType = (StreamType_Main == replay->m_eStreamType) ? 0 : 1;
			cond.wIsAnd = (RecordType_Condition_Or == replay->m_condition) ? 0 : 1;
			int trigType = 0;
			if (0 != (replay->m_recordType & RecordType_Regular)) {
				trigType |= I8H_REC_TRIG_BY_REGULAR;
			}
			if (0 != (replay->m_recordType & RecordType_Motion)) {
				trigType |= I8H_REC_TRIG_BY_MD;
			}
			if (0 != (replay->m_recordType & RecordType_Alarm)) {
				trigType |= I8H_REC_TRIG_BY_AI;
			}
			if (0 != (replay->m_recordType & RecordType_Counter)) {
				trigType |= I8H_REC_TRIG_BY_COUNTER;
			}
			if (0 != (replay->m_recordType & RecordType_Wire)) {
				trigType |= I8H_REC_TRIG_BY_WIRE;
			}
			if (0 != (replay->m_recordType & RecordType_Region)) {
				trigType |= I8H_REC_TRIG_BY_REGION;
			}
			if (0 != (replay->m_recordType & RecordType_Object)) {
				trigType |= I8H_REC_TRIG_BY_OBJECT;
			}
			cond.dwFileType = trigType;
			//cond.dwFileType = I8H_REC_TRIG_BY_ALL;

			cond.struStartTime.wYear = dtBegin.date().year();
			cond.struStartTime.wMonth = dtBegin.date().month();
			cond.struStartTime.wDay = dtBegin.date().day();
			cond.struStartTime.wHour = dtBegin.time().hour();
			cond.struStartTime.wMinute = dtBegin.time().minute();
			cond.struStartTime.wSecond = dtBegin.time().second();
			cond.struStartTime.wZoneTime = 0;
			cond.struStopTime.wYear = dtEnd.date().year();
			cond.struStopTime.wMonth = dtEnd.date().month();
			cond.struStopTime.wDay = dtEnd.date().day();
			cond.struStopTime.wHour = dtEnd.time().hour();
			cond.struStopTime.wMinute = dtEnd.time().minute();
			cond.struStopTime.wSecond = dtEnd.time().second();
			cond.struStopTime.wZoneTime = 0;

			replay->m_hReplay = I8H_SDK_PlayBackByTimev2(
				m_hConnection,
				&cond,
				Http_Playback_CallBack,
				(LPVOID)(replay));
			if (replay->m_hReplay == NULL) {
				return false;
			}


		}
		else {
			I8H_SDK_PlayBackControl(replay->m_hReplay, I8H_PLAYBACK_ADDCHAN, &struChannelInfo, sizeof(struChannelInfo), NULL, 0);
		}

		I8H_SDK_PlayBackControl(replay->m_hReplay, I8H_PLAYBACK_PLAYSTARTAUDIO, &struChannelInfo, sizeof(struChannelInfo), NULL, NULL);

	}
	return true;
}

bool DeviceHttp::closeReplay(ReplayInfo *replay) {
	int res = I8H_SDK_StopPlayBack(replay->m_hReplay);
	qDebug() << "close Replay";
	return (res == 0) ? true : false;
}

bool DeviceHttp::ctrlReplay(ReplayInfo *replay, CMS_CONNECT_PARSE_ReplayCmdType eCmdType, int iParam) {
	bool res;
	if (ReplayCtrlType_IFrameOnly == eCmdType) {
		int inputParam = iParam;/* (int)只要I帧,0-所有帧,1-只I帧 */
		
		if (iParam == 0)
		{
			inputParam = 4;
			res = I8H_SDK_PlayBackControl(replay->m_hReplay,
				I8H_PLAYBACK_SETSPEED,
				&inputParam,
				sizeof(inputParam),
				NULL,
				0);
		}
		else if (iParam == 1)
		{
			inputParam = 16;
			res = I8H_SDK_PlayBackControl(replay->m_hReplay,
				I8H_PLAYBACK_SETSPEED,
				&inputParam,
				sizeof(inputParam),
				NULL,
				0);
		}
		else
		{
			return false;
		}
	}
	else if (ReplayCtrlType_SeekTime == eCmdType) {
		I8H_TIME seekTime;
		QDateTime seekQDateTime = QDateTime::fromTime_t(iParam).toUTC();
		seekTime.wYear = seekQDateTime.date().year();
		seekTime.wMonth = seekQDateTime.date().month();
		seekTime.wDay = seekQDateTime.date().day();
		seekTime.wHour = seekQDateTime.time().hour();
		seekTime.wMinute = seekQDateTime.time().minute();
		seekTime.wSecond = seekQDateTime.time().second();
		seekTime.wZoneTime = 0;
		seekTime.wRes = 0;
		res = I8H_SDK_PlayBackControl(replay->m_hReplay,
			I8H_PLAYBACK_PLAYSETTIME,
			&seekTime,
			sizeof(seekTime),
			NULL,
			0);
	}
	else {
		return false;
	}

	return res;
}

bool DeviceHttp::getAlarmIO(CMS_CONNECT_PARSE_IOType eType, int iIndex, bool &isOpen) {
	QString strUrl;
	QString strReq;
	BYTE lpOutBuffer[8192];
	memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
	DWORD dwOutBufSize = 8192;
	DWORD dwOutSize = 0;
	I8HCache *cache = DeviceHttp::sta_mapCache.value(this->connectionHandle());
	if (NULL == cache)
		return false;

	if (eType == IO_AlarmIn) {
		switch (cache->m_iVersion) {
		case 2: //NVR1.0_GO_AHEAD
		{
			strUrl = QString("frmAlarmInPara");
			strReq = QString(
				"{"
				"\"type\":0,"
				"\"ch\":%1,"
				"\"param\":{"
				"	\"ip\":\"%2\","
				"	\"username\":\"%3\","
				"	\"pwd\":\"%4\""
				"},"
				"\"data\":{}"
				"}"
			).arg(iIndex - 1).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			QString result((char*)lpOutBuffer);
			if (0 != getJsonValue(result, "result").toInt())
				return false;

			isOpen = getJsonValue(result, "byAlarmInHandle").toInt() == 1;
		}
		break;

		case 5: //NVR2.0_GO_AHEAD
		{
			strUrl = QString("frmAlarmInPara");
			strReq = QString(
				"{"
				"\"type\":0,"
				"\"ch\":%1,"
				"\"param\":{"
				"	\"ip\":\"%2\","
				"	\"username\":\"%3\","
				"	\"pwd\":\"%4\""
				"},"
				"\"data\":{}"
				"}"
			).arg(iIndex).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			QString result((char*)lpOutBuffer);
			if (0 != getJsonValue(result, "result").toInt())
				return false;

			isOpen = getJsonValue(result, "byAlarmInHandle").toInt() == 1;
		}
		break;

		case 3: //IPC_GO_AHEAD
		{
			strUrl = QString("frmAlarmInPara");
			strReq = QString(
				"{"
				"\"type\":0,"
				"\"ch\":%1,"
				"\"param\":{"
				"	\"ip\":\"%2\","
				"	\"username\":\"%3\","
				"	\"pwd\":\"%4\""
				"},"
				"\"data\":{}"
				"}"
			).arg(iIndex).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			QString result((char*)lpOutBuffer);
			if (0 != getJsonValue(result, "result").toInt())
				return false;

			isOpen = getJsonValue(result, "AIHandle").toInt() == 1;
		}
		break;

		case 7: //NVR1.0_NGINX
		{
			strUrl = QString("frmAlarmInPara");
			strReq = QString(
				"{"
				"\"Type\":0,"
				"\"Ch\":%1,"
				"\"Data\":{}"
				"}"
			).arg(iIndex);

			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			QString result((char*)lpOutBuffer);
			if (0 != getJsonValue(result, "Result").toInt())
				return false;

			isOpen = getJsonValue(result, "AlarmHandle").toInt() == 1;
		}
		break;

		case 8: //IPC_NGINX
		{
			strUrl = QString("frmAlarmInPara");
			strReq = QString(
				"{"
				"\"Type\":0,"
				"\"Ch\":%1,"
				"\"Data\":{}"
				"}"
			).arg(iIndex);

			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			QString result((char*)lpOutBuffer);
			if (0 != getJsonValue(result, "Result").toInt())
				return false;

			isOpen = getJsonValue(result, "AIHandle").toInt() == 1;
		}
		break;

		case 10: //NVR2.0_NGINX 
		{
			strUrl = QString("frmAlarmInPara");
			strReq = QString(
				"{"
				"\"Type\":0,"
				"\"Ch\":%1,"
				"\"Data\":{}"
				"}"
			).arg(iIndex);

			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			QString result((char*)lpOutBuffer);
			if (0 != getJsonValue(result, "Result").toInt())
				return false;

			isOpen = getJsonValue(result, "AlarmHandle").toInt() == 1;
		}
		break;

		default:
			return false;
		}
	}
	else {
		switch (cache->m_iVersion) {
		case 2: //NVR1.0_GO_AHEAD
			break;

		case 3: //IPC_GO_AHEAD

			break;

		case 5: //NVR2.0_GO_AHEAD

			break;

		case 7: //NVR1.0_NGINX
		{
			strUrl = QString("frmAlarmManualCtrl");
			strReq = QString(
				"{"
				"\"Type\":0,"
				"\"Ch\":%1,"
				"\"Data\":{}"
				"}"
			).arg(iIndex);

			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			QString result((char*)lpOutBuffer);
			if (0 != getJsonValue(result, "Result").toInt())
				return false;

			isOpen = getJsonValue(result, "ManualCtrl").toInt() == 1;
		}
		break;

		case 8: //IPC_NGINX
			return false;
			break;

		case 10: //NVR2.0_NGINX 
			return false;
			break;
		default:
			return false;
		}
	}

	return true;
}

bool DeviceHttp::getFisheyeAbility(CMS_CONNECT_PARSE_FishEyeAbility &ability)
{
	I8HCache *cache = DeviceHttp::sta_mapCache.value(this->connectionHandle());
	if (NULL == cache)
		return false;

	if (I8H_IPC_FISHEYE_NGINX != cache->m_iVersion)
		return false;

	BYTE lpOutBuffer[8192];
	memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
	DWORD dwOutBufSize = 8192;
	DWORD dwOutSize = 0;


	QString strUrl("frmFisheyeAbility");
	QString strReq(
		"{"
		"\"Type\":0,"
		"\"Ch\":1,"
		"\"Data\":{}"
		"}"
	);

	if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
		return false;

	QJsonDocument doc = QJsonDocument::fromJson((char*)lpOutBuffer);
	QJsonObject root = doc.object();
	if (root["Result"].toInt() != 0)
		return false;

	QJsonObject data = root["Data"].toObject();
	QJsonArray modes = data["ViewMode"].toArray();

	ability.iCount = modes.count();
	for (int i = 0; i < ability.iCount; ++i) {
		QJsonObject mode = modes[i].toObject();
		ability.mode[i].iFishEyeView = mode["FisheyeView"].toInt();
		ability.mode[i].iFullView = mode["FullView"].toInt();
		ability.mode[i].iPtzView = mode["PtzView"].toInt();
	}

	return true;
}

bool DeviceHttp::getFisheyeMode(CMS_CONNECT_PARSE_FishEyeMode &mode)
{
	I8HCache *cache = DeviceHttp::sta_mapCache.value(this->connectionHandle());
	if (NULL == cache)
		return false;

	if (I8H_IPC_FISHEYE_NGINX != cache->m_iVersion)
		return false;

	BYTE lpOutBuffer[8192];
	memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
	DWORD dwOutBufSize = 8192;
	DWORD dwOutSize = 0;


	QString strUrl("frmFisheyeMode");
	QString strReq(
		"{"
		"\"Type\":0,"
		"\"Ch\":1,"
		"\"Data\":{}"
		"}"
	);

	if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
		return false;

	QJsonDocument doc = QJsonDocument::fromJson((char*)lpOutBuffer);
	QJsonObject root = doc.object();
	if (root["Result"].toInt() != 0)
		return false;

	QJsonObject data = root["Data"].toObject();
	mode.installMode = (CMS_CONNECT_PARSE_GetFishEyeInstallMode)data["InstallMode"].toInt();
	mode.viewMode.iFishEyeView = data["ViewMode"].toObject()["FisheyeView"].toInt();
	mode.viewMode.iFullView = data["ViewMode"].toObject()["FullView"].toInt();
	mode.viewMode.iPtzView = data["ViewMode"].toObject()["PtzView"].toInt();
	mode.fullViewMode = (CMS_CONNECT_PARSE_GetFishEyeFullViewMode)data["FullViewMode"].toInt();

	qDebug() << "installMode" << mode.installMode << "View" << mode.viewMode.iFishEyeView << mode.viewMode.iFullView << mode.viewMode.iPtzView << mode.fullViewMode;

	return true;
}

bool DeviceHttp::setFisheyeMode(CMS_CONNECT_PARSE_FishEyeMode &mode)
{
	I8HCache *cache = DeviceHttp::sta_mapCache.value(this->connectionHandle());
	if (NULL == cache)
		return false;

	if (I8H_IPC_FISHEYE_NGINX != cache->m_iVersion)
		return false;

	BYTE lpOutBuffer[8192];
	memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
	DWORD dwOutBufSize = 8192;
	DWORD dwOutSize = 0;


	QString strUrl("frmFisheyeMode");
	QJsonObject req;
	req["Type"] = 1;
	req["Ch"] = 1;
	QJsonObject data;
	data["InstallMode"] = (int)mode.installMode;
	QJsonObject view;
	view["FisheyeView"] = mode.viewMode.iFishEyeView;
	view["FullView"] = mode.viewMode.iFullView;
	view["PtzView"] = mode.viewMode.iPtzView;
	data["ViewMode"] = view;
	data["FullViewMode"] = (int)mode.fullViewMode;

	req["Data"] = data;

	QByteArray baReq = QJsonDocument(req).toJson();

	memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
	if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)baReq.data(), baReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
		return false;

	if (0 != getJsonValue(QString((char*)lpOutBuffer), "Result").toInt())
		return false;

	return true;
}

bool DeviceHttp::setAlarmIO(CMS_CONNECT_PARSE_IOType eType, int iIndex, bool isOpen) {
	QString strUrl;
	QString strReq;
	BYTE lpOutBuffer[8192];
	memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
	DWORD dwOutBufSize = 8192;
	DWORD dwOutSize = 0;
	I8HCache *cache = DeviceHttp::sta_mapCache.value(this->connectionHandle());
	if (NULL == cache)
		return false;

	if (eType == IO_AlarmIn) {
		switch (cache->m_iVersion) {
		case 2: //NVR1.0_GO_AHEAD
		{
			strUrl = QString("frmAlarmInPara");
			strReq = QString(
				"{"
				"\"type\":0,"
				"\"ch\":%1,"
				"\"param\":{"
				"	\"ip\":\"%2\","
				"	\"username\":\"%3\","
				"	\"pwd\":\"%4\""
				"},"
				"\"data\":{}"
				"}"
			).arg(iIndex - 1).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			QString result((char*)lpOutBuffer);
			if (0 != getJsonValue(result, "result").toInt())
				return false;


			QString keyInContent = QString("\"data\":");
			int begin = result.indexOf(keyInContent) + keyInContent.size();
			QString strData = result.right(result.size() - begin);

			QString strReq2 = QString(
				"{"
				"\"type\":1,"
				"\"ch\":%1,"
				"\"param\":{"
				"	\"ip\":\"%2\","
				"	\"username\":\"%3\","
				"	\"pwd\":\"%4\""
				"},"
				"\"data\":"
			).arg(iIndex - 1).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

			strReq2 += replaceJsonValue(strData, "byAlarmInHandle", (isOpen ? "1" : "0"));;

			memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq2.toUtf8().data(), strReq2.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			if (0 != getJsonValue(QString((char*)lpOutBuffer), "result").toInt())
				return false;
		}
		break;

		case 5: //NVR2.0_GO_AHEAD
		{
			strUrl = QString("frmAlarmInPara");
			strReq = QString(
				"{"
				"\"type\":0,"
				"\"ch\":%1,"
				"\"param\":{"
				"	\"ip\":\"%2\","
				"	\"username\":\"%3\","
				"	\"pwd\":\"%4\""
				"},"
				"\"data\":{}"
				"}"
			).arg(iIndex).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			QString result((char*)lpOutBuffer);
			if (0 != getJsonValue(result, "result").toInt())
				return false;


			QString keyInContent = QString("\"data\":");
			int begin = result.indexOf(keyInContent) + keyInContent.size();
			QString strData = result.right(result.size() - begin);

			QString strReq2 = QString(
				"{"
				"\"type\":1,"
				"\"ch\":%1,"
				"\"param\":{"
				"	\"ip\":\"%2\","
				"	\"username\":\"%3\","
				"	\"pwd\":\"%4\""
				"},"
				"\"data\":"
			).arg(iIndex).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

			strReq2 += replaceJsonValue(strData, "byAlarmInHandle", (isOpen ? "1" : "0"));;

			memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq2.toUtf8().data(), strReq2.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			if (0 != getJsonValue(QString((char*)lpOutBuffer), "result").toInt())
				return false;
		}
		break;

		case 3: //IPC_GO_AHEAD
		{
			strUrl = QString("frmAlarmInPara");
			strReq = QString(
				"{"
				"\"type\":0,"
				"\"ch\":%1,"
				"\"param\":{"
				"	\"ip\":\"%2\","
				"	\"username\":\"%3\","
				"	\"pwd\":\"%4\""
				"},"
				"\"data\":{}"
				"}"
			).arg(iIndex).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			QString result((char*)lpOutBuffer);
			if (0 != getJsonValue(result, "result").toInt())
				return false;


			QString keyInContent = QString("\"data\":");
			int begin = result.indexOf(keyInContent) + keyInContent.size();
			QString strData = result.right(result.size() - begin);

			QString strReq2 = QString(
				"{"
				"\"type\":1,"
				"\"ch\":%1,"
				"\"param\":{"
				"	\"ip\":\"%2\","
				"	\"username\":\"%3\","
				"	\"pwd\":\"%4\""
				"},"
				"\"data\":"
			).arg(iIndex).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

			strReq2 += replaceJsonValue(strData, "AIHandle", (isOpen ? "1" : "0"));;

			memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq2.toUtf8().data(), strReq2.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			if (0 != getJsonValue(QString((char*)lpOutBuffer), "result").toInt())
				return false;
		}
		break;

		case 7: //NVR1.0_NGINX
		{
			strUrl = QString("frmAlarmInPara");
			strReq = QString(
				"{"
				"\"Type\":0,"
				"\"Ch\":%1,"
				"\"Data\":{}"
				"}"
			).arg(iIndex);

			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			QString result((char*)lpOutBuffer);
			if (0 != getJsonValue(result, "Result").toInt())
				return false;


			QString keyInContent = QString("\"Data\":");
			int begin = result.indexOf(keyInContent) + keyInContent.size();
			QString strData = result.right(begin);
			replaceJsonValue(strData, "AlarmInHandle", (isOpen ? "1" : "0"));

			QString strReq2 = QString(
				"{"
				"\"Type\":1,"
				"\"Ch\":%1,"
				"\"Data\":"
			).arg(iIndex);

			strReq2 += strData;

			memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq2.toUtf8().data(), strReq2.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			if (0 != getJsonValue(QString((char*)lpOutBuffer), "Result").toInt())
				return false;
		}
		break;

		case 8: //IPC_NGINX
		{
			strUrl = QString("frmAlarmInPara");
			strReq = QString(
				"{"
				"\"Type\":0,"
				"\"Ch\":%1,"
				"\"Data\":{}"
				"}"
			).arg(iIndex);

			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			QString result((char*)lpOutBuffer);
			if (0 != getJsonValue(result, "Result").toInt())
				return false;


			QString keyInContent = QString("\"Data\":");
			int begin = result.indexOf(keyInContent) + keyInContent.size();
			QString strData = result.right(begin);
			replaceJsonValue(strData, "AIHandle", (isOpen ? "1" : "0"));

			QString strReq2 = QString(
				"{"
				"\"Type\":1,"
				"\"Ch\":%1,"
				"\"Data\":"
			).arg(iIndex);

			strReq2 += strData;

			memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq2.toUtf8().data(), strReq2.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			if (0 != getJsonValue(QString((char*)lpOutBuffer), "Result").toInt())
				return false;
		}
		break;

		case 10: //NVR2.0_NGINX 
		{
			strUrl = QString("frmAlarmInPara");
			strReq = QString(
				"{"
				"\"Type\":0,"
				"\"Ch\":%1,"
				"\"Data\":{}"
				"}"
			).arg(iIndex);

			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			QJsonDocument doc = QJsonDocument::fromJson((char*)lpOutBuffer);
			QJsonObject root = doc.object();
			if (root["result"].toInt() != 0)
				return false;

			QJsonObject data = root["Data"].toObject();
			data["AlarmHandle"] = isOpen ? 1 : 0;

			QJsonObject req2;
			req2["Type"] = 1;
			req2["Ch"] = iIndex;
			req2["Data"] = data;

			QByteArray baReq2 = QJsonDocument(req2).toJson();

			memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)baReq2.data(), baReq2.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			if (0 != getJsonValue(QString((char*)lpOutBuffer), "Result").toInt())
				return false;
		}
		break;

		default:
			return false;
		}
	}
	else {
		switch (cache->m_iVersion) {
		case 2: //NVR1.0_GO_AHEAD
			return false;
			break;

		case 3: //IPC_GO_AHEAD
			return false;
			break;

		case 5: //NVR2.0_GO_AHEAD
			return false;
			break;

		case 7: //NVR1.0_NGINX
		{
			strUrl = QString("frmAlarmManualCtrl");
			strReq = QString(
				"{"
				"\"Type\":1,"
				"\"Ch\":%1,"
				"\"Data\":{"
				"\"ManualCtrl\":%2"
				"}"
				"}"
			).arg(iIndex).arg(isOpen ? 1 : 0);

			if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return false;

			QString result((char*)lpOutBuffer);
			if (0 != getJsonValue(result, "Result").toInt())
				return false;
		}
		break;

		case 8: //IPC_NGINX
			return false;
			break;

		case 10: //NVR2.0_NGINX 
			return false;
			break;

		default:
			return false;
		}
	}



	return true;
}

QList<QString> DeviceHttp::getChName(int version, HANDLE handle, QString ip, QString usr, QString pwd) {
	QList<QString> names;

	QString strUrl;
	QString strReq;
	BYTE lpOutBuffer[64000];
	memset(lpOutBuffer, 0, sizeof(BYTE) * 64000);
	DWORD dwOutBufSize = 64000;
	DWORD dwOutSize = 0;

	switch (version) {
	case 2: //NVR1.0_GO_AHEAD
	{
		strUrl = QString("frmGetPreviewInfo");
		strReq = QString(
			"{"
			"\"type\":0,"
			"\"ch\":0,"
			"\"param\":{"
			"	\"ip\":\"%1\","
			"	\"username\":\"%2\","
			"	\"pwd\":\"%3\""
			"},"
			"\"data\":{}"
			"}"
		).arg(ip).arg(usr).arg(pwd);

		if (!I8H_SDK_TranData(handle, (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return names;

		QJsonDocument doc = QJsonDocument::fromJson((char*)lpOutBuffer);
		QJsonObject root = doc.object();
		if (root["result"].toInt() != 0)
			return names;

		QJsonArray arr = root["data"].toObject()["data"].toArray();
		for (int i = 0; i < arr.size(); i++) {
			names.append(arr[i].toArray()[0].toString());
		}
	}
	break;

	case 5: //NVR2.0_GO_AHEAD
	{
#ifdef _SVIEW_
		strUrl = QString("frmGetNetDevCFG");
		strReq = QString(
			"{"
			"\"type\":0,"
			"\"ch\":%1,"
			"\"param\":{"
			"	\"ip\":\"%2\","
			"	\"username\":\"%3\","
			"	\"pwd\":\"%4\""
			"},"
			"\"data\":{}"
			"}"
		).arg(1).arg(ip).arg(usr).arg(pwd);

		if (!I8H_SDK_TranData(handle, (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return names;

		QJsonDocument doc = QJsonDocument::fromJson((char*)lpOutBuffer);
		QJsonObject root = doc.object();
		if (root["Result"].toInt() != 0)
			return names;

		QJsonArray arr = root["Data"].toObject()["IpcList"].toArray();
		for (int i = 0; i < arr.size(); i++) {
			names.append(arr[i].toObject()["szIP"].toString());
		}
#else

		strUrl = QString("frmGetPreviewInfo");
		strReq = QString(
			"{"
			"\"type\":0,"
			"\"ch\":0,"
			"\"param\":{"
			"	\"ip\":\"%1\","
			"	\"username\":\"%2\","
			"	\"pwd\":\"%3\""
			"},"
			"\"data\":{}"
			"}"
		).arg(ip).arg(usr).arg(pwd);

		if (!I8H_SDK_TranData(handle, (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return names;

		QJsonDocument doc = QJsonDocument::fromJson((char*)lpOutBuffer);
		QJsonObject root = doc.object();
		if (root["result"].toInt() != 0)
			return names;

		QJsonArray arr = root["data"].toObject()["data"].toArray();
		for (int i = 0; i < arr.size(); i++) {
			names.append(arr[i].toArray()[0].toString());
		}
#endif
	}
	break;

	case 3: //IPC_GO_AHEAD
	{
		strUrl = QString("frmVideoShowParaCtrl");
		strReq = QString(
			"{"
			"\"type\":0,"
			"\"ch\":%1,"
			"\"param\":{"
			"	\"ip\":\"%2\","
			"	\"username\":\"%3\","
			"	\"pwd\":\"%4\""
			"},"
			"\"data\":{}"
			"}"
		).arg(1).arg(ip).arg(usr).arg(pwd);

		if (!I8H_SDK_TranData(handle, (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return names;

		QString result((char*)lpOutBuffer);
		if (0 != getJsonValue(result, "result").toInt())
			return names;

		names.append(getJsonValue(result, "sChanName"));
	}
	break;

	case 7: //NVR1.0_NGINX
	{

	}
	break;

	case 8: //IPC_NGINX
	{
		strUrl = QString("frmSingleLineOSD");
		strReq = QString(
			"{"
			"\"Type\":0,"
			"\"Ch\":%1,"
			"\"Data\":{}"
			"}"
		).arg(0);

		if (!I8H_SDK_TranData(handle, (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return names;

		QString result((char*)lpOutBuffer);
		if (0 != getJsonValue(result, "Result").toInt())
			return names;

		names.append(getJsonValue(result, "ChanName"));
	}
	break;

	case 10: //NVR2.0_NGINX 
	{
#ifdef _SVIEW_
		strUrl = QString("frmNetDevCFG");
		QString strReq = "{"
			"\"Type\":	0,"
			"\"Ch\" : 0,"
			"\"Data\" : {}"
			"}";

		if (!I8H_SDK_TranData(handle, (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return names;

		QJsonDocument doc = QJsonDocument::fromJson((char*)lpOutBuffer);
		QJsonObject root = doc.object();
		if (root["Result"].toInt() != 0)
			return names;

		QJsonArray arr = root["Data"].toObject()["NetChannelList"].toArray();
		for (int i = 0; i < arr.size(); i++) {
			names.append(arr[i].toObject()["IP"].toString());
		}
#else
		strUrl = QString("frmGetPreviewInfo");
		strReq = QString(
			"{"
			"\"Type\":0,"
			"\"Ch\":0,"
			"\"Data\":{}"
			"}"
		);

		if (!I8H_SDK_TranData(handle, (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return names;

		QJsonDocument doc = QJsonDocument::fromJson((char*)lpOutBuffer);
		QJsonObject root = doc.object();
		if (root["Result"].toInt() != 0)
			return names;

		QJsonArray arr = root["Data"].toObject()["Channels"].toArray();
		for (int i = 0; i < arr.size(); i++) {
			names.append(arr[i].toArray()[0].toString());
		}
#endif
	}
	break;

	default:
		return names;
	}

	return names;
}

QList<QString> DeviceHttp::getChIP(int version, HANDLE handle)
{
	QList<QString> ips;
	QString strUrl;

	BYTE lpOutBuffer[64000];
	memset(lpOutBuffer, 0, sizeof(BYTE) * 64000);
	DWORD dwOutBufSize = 64000;
	DWORD dwOutSize = 0;

	switch (version) {
	case 2: //NVR1.0_GO_AHEAD
		{
		
		}
	break;

	case 5: //NVR2.0_GO_AHEAD
		{
		
		}
	break;

	case 3: //IPC_GO_AHEAD
		{
		
		}
	break;

	case 8: //IPC_NGINX
		{
			
		}
	case 7: //NVR1.0_NGINX
	{

	}
	case 10: //NVR2.0_NGINX 
		{
			strUrl = QString("frmNetDevCFG");
			QString strReq = "{"
				"\"Type\":	0,"
				"\"Ch\" : 0,"
				"\"Data\" : {}"
				"}";

			if (!I8H_SDK_TranData(handle, (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
				return ips;

			QJsonDocument doc = QJsonDocument::fromJson((char*)lpOutBuffer);
			QJsonObject root = doc.object();
			if (root["Result"].toInt() != 0)
				return ips;

			QJsonArray arr = root["Data"].toObject()["NetChannelList"].toArray();
			for (int i = 0; i < arr.size(); i++) {
				ips.append(arr[i].toObject()["IP"].toString());
			}
		}
	break;

	default:
		return ips;
	}

	return ips;
}

bool DeviceHttp::modifyChName(int iChNo, QString strName) {
	QString strUrl;
	QString strReq;
	BYTE lpOutBuffer[64000];
	memset(lpOutBuffer, 0, sizeof(BYTE) * 64000);
	DWORD dwOutBufSize = 64000;
	DWORD dwOutSize = 0;

	I8HCache *cache = DeviceHttp::sta_mapCache.value(this->connectionHandle());
	if (NULL == cache)
		return false;

	switch (cache->m_iVersion) {
	case 2: //NVR1.0_GO_AHEAD
	{
		strUrl = QString("frmVideoShowParaCtrl");
		strReq = QString(
			"{"
			"\"type\":0,"
			"\"ch\":%1,"
			"\"param\":{"
			"	\"ip\":\"%2\","
			"	\"username\":\"%3\","
			"	\"pwd\":\"%4\""
			"},"
			"\"data\":{}"
			"}"
		).arg(iChNo).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		QString result((char*)lpOutBuffer);
		if (0 != getJsonValue(result, "result").toInt())
			return false;

		QString keyInContent = QString("\"data\":");
		int begin = result.indexOf(keyInContent) + keyInContent.size();
		QString strData = result.right(result.size() - begin);

		QString strReq2 = QString(
			"{"
			"\"type\":1,"
			"\"ch\":%1,"
			"\"param\":{"
			"	\"ip\":\"%2\","
			"	\"username\":\"%3\","
			"	\"pwd\":\"%4\""
			"},"
			"\"data\":"
		).arg(iChNo).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

		strReq2 += replaceJsonValue(strData, "szChanName", QString("\"%1\"").arg(strName));

		memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);

		QByteArray ba = strReq2.toUtf8();
		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)ba.data(), ba.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		if (0 != getJsonValue(QString((char*)lpOutBuffer), "result").toInt())
			return false;
	}
	break;

	case 5: //NVR2.0_GO_AHEAD
	{
		strUrl = QString("frmVideoShowParaCtrl");
		strReq = QString(
			"{"
			"\"type\":0,"
			"\"ch\":%1,"
			"\"param\":{"
			"	\"ip\":\"%2\","
			"	\"username\":\"%3\","
			"	\"pwd\":\"%4\""
			"},"
			"\"data\":{}"
			"}"
		).arg(iChNo).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		QString result((char*)lpOutBuffer);
		if (0 != getJsonValue(result, "result").toInt())
			return false;

		QString keyInContent = QString("\"data\":");
		int begin = result.indexOf(keyInContent) + keyInContent.size();
		QString strData = result.right(result.size() - begin);

		QString strReq2 = QString(
			"{"
			"\"type\":1,"
			"\"ch\":%1,"
			"\"param\":{"
			"	\"ip\":\"%2\","
			"	\"username\":\"%3\","
			"	\"pwd\":\"%4\""
			"},"
			"\"data\":"
		).arg(iChNo).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

		strReq2 += replaceJsonValue(strData, "szChanName", QString("\"%1\"").arg(strName));

		memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);

		QByteArray ba = strReq2.toUtf8();
		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)ba.data(), ba.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		if (0 != getJsonValue(QString((char*)lpOutBuffer), "result").toInt())
			return false;
	}
	break;

	case 3: //IPC_GO_AHEAD
	{
		strUrl = QString("frmVideoShowParaCtrl");
		strReq = QString(
			"{"
			"\"type\":0,"
			"\"ch\":%1,"
			"\"param\":{"
			"	\"ip\":\"%2\","
			"	\"username\":\"%3\","
			"	\"pwd\":\"%4\""
			"},"
			"\"data\":{}"
			"}"
		).arg(iChNo).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		QString result((char*)lpOutBuffer);
		if (0 != getJsonValue(result, "result").toInt())
			return false;

		QString keyInContent = QString("\"data\":");
		int begin = result.indexOf(keyInContent) + keyInContent.size();
		QString strData = result.right(result.size() - begin);

		QString strReq2 = QString(
			"{"
			"\"type\":1,"
			"\"ch\":%1,"
			"\"param\":{"
			"	\"ip\":\"%2\","
			"	\"username\":\"%3\","
			"	\"pwd\":\"%4\""
			"},"
			"\"data\":"
		).arg(iChNo).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

		strReq2 += replaceJsonValue(strData, "sChanName", QString("\"%1\"").arg(strName));

		memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);

		QByteArray ba = strReq2.toUtf8();
		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)ba.data(), ba.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		if (0 != getJsonValue(QString((char*)lpOutBuffer), "result").toInt())
			return false;
	}
	break;

	case 7: //NVR1.0_NGINX
	{

	}
	break;

	case 8: //IPC_NGINX
	{
		strUrl = QString("frmSingleLineOSD");
		strReq = QString(
			"{"
			"\"Type\":0,"
			"\"Ch\":%1,"
			"\"Data\":{}"
			"}"
		).arg(iChNo);

		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		QString result((char*)lpOutBuffer);
		if (0 != getJsonValue(result, "Result").toInt())
			return false;

		QString keyInContent = QString("\"Data\":");
		int begin = result.indexOf(keyInContent) + keyInContent.size();
		QString strData = result.right(result.size() - begin);

		QString strReq2 = QString(
			"{"
			"\"Type\":1,"
			"\"Ch\":%1,"
			"\"Data\":"
			"}"
		).arg(iChNo).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword);

		strReq2 += replaceJsonValue(strData, "ChanName", QString("\"%1\"").arg(strName));

		memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);

		QByteArray ba = strReq2.toUtf8();
		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)ba.data(), ba.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		if (0 != getJsonValue(QString((char*)lpOutBuffer), "result").toInt())
			return false;
	}
	break;

	case 10: //NVR2.0_NGINX 
	{
		strUrl = QString("frmDeviceChannelName");
		strReq = QString(
			"{"
			"\"Type\":1,"
			"\"Ch\":%1,"
			"\"Data\":{"
			"\"DeviceChannel\":{"
			"\"DeviceChanName\":\"%2\","
			"\"Enable\":1"
			"},"
			"\"CopyChannels\":[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]"
			"}"
			"}"
		).arg(iChNo).arg(strName);

		QByteArray ba = strReq.toUtf8();
		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)ba.data(), ba.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		QString result((char*)lpOutBuffer);
		if (0 != getJsonValue(result, "Result").toInt())
			return false;
	}
	break;

	default:
		return false;
	}

	return true;
}

bool DeviceHttp::timeSync() {
	QString strUrl;
	QString strReq;
	BYTE lpOutBuffer[8192];
	memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
	DWORD dwOutBufSize = 8192;
	DWORD dwOutSize = 0;
	I8HCache *cache = DeviceHttp::sta_mapCache.value(this->connectionHandle());
	if (NULL == cache)
		return false;

	QDateTime current = QDateTime::currentDateTime();

	switch (cache->m_iVersion) {
	case 2: //NVR1.0_GO_AHEAD
	{
		strUrl = QString("frmSetTimeCtrl");
		strReq = QString(
			"{"
			"\"type\":1,"
			"\"ch\":0,"
			"\"param\":{"
			"	\"ip\":\"%1\","
			"	\"username\":\"%2\","
			"	\"pwd\":\"%3\""
			"},"
			"\"data\":{"
			"	\"time\":[%4,%5,%6,%7,%8,%9]"
			"}"
			"}"
		).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword)
			.arg(current.date().year()).arg(current.date().month()).arg(current.date().day())
			.arg(current.time().hour()).arg(current.time().minute()).arg(current.time().second());

		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		QString result((char*)lpOutBuffer);
		if (0 != getJsonValue(result, "result").toInt())
			return false;
	}
	break;

	case 5: //NVR2.0_GO_AHEAD
	{
		strUrl = QString("frmSetTimeCtrl");
		strReq = QString(
			"{"
			"\"type\":1,"
			"\"ch\":0,"
			"\"param\":{"
			"	\"ip\":\"%1\","
			"	\"username\":\"%2\","
			"	\"pwd\":\"%3\""
			"},"
			"\"data\":{"
			"	\"time\":[%4,%5,%6,%7,%8,%9]"
			"}"
			"}"
		).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword)
			.arg(current.date().year()).arg(current.date().month()).arg(current.date().day())
			.arg(current.time().hour()).arg(current.time().minute()).arg(current.time().second());

		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		QString result((char*)lpOutBuffer);
		if (0 != getJsonValue(result, "result").toInt())
			return false;
	}
	break;

	case 3: //IPC_GO_AHEAD
	{
		strUrl = QString("frmSetTimeCtrl");
		strReq = QString(
			"{"
			"\"type\":1,"
			"\"ch\":0,"
			"\"param\":{"
			"	\"ip\":\"%1\","
			"	\"username\":\"%2\","
			"	\"pwd\":\"%3\""
			"},"
			"\"data\":{"
			"	\"time\":[%4,%5,%6,%7,%8,%9]"
			"}"
			"}"
		).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword)
			.arg(current.date().year()).arg(current.date().month()).arg(current.date().day())
			.arg(current.time().hour()).arg(current.time().minute()).arg(current.time().second());

		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		QString result((char*)lpOutBuffer);
		if (0 != getJsonValue(result, "result").toInt())
			return false;
	}
	break;

	case 7: //NVR1.0_NGINX
	{
		strUrl = QString("frmDeviceTimeCtrl");
		strReq = QString(
			"{"
			"\"Type\":1,"
			"\"Ch\":1,"
			"\"Data\":{"
			"	\"Time\":[%1,%2,%3,%4,%5,%6]"
			"}"
			"}"
		).arg(current.date().year()).arg(current.date().month()).arg(current.date().day())
			.arg(current.time().hour()).arg(current.time().minute()).arg(current.time().second());

		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		QString result((char*)lpOutBuffer);
		if (0 != getJsonValue(result, "Result").toInt())
			return false;
	}
	break;

	case 8: //IPC_NGINX
	{
		strUrl = QString("frmDeviceTimeCtrl");
		strReq = QString(
			"{"
			"\"Type\":1,"
			"\"Ch\":1,"
			"\"Data\":{"
			"	\"Time\":[%1,%2,%3,%4,%5,%6]"
			"}"
			"}"
		).arg(current.date().year()).arg(current.date().month()).arg(current.date().day())
			.arg(current.time().hour()).arg(current.time().minute()).arg(current.time().second());

		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		QString result((char*)lpOutBuffer);
		if (0 != getJsonValue(result, "Result").toInt())
			return false;
	}
	break;

	case 10: //NVR2.0_NGINX 
	{
		strUrl = QString("frmDeviceTimeCtrl");
		strReq = QString(
			"{"
			"\"Type\":1,"
			"\"Ch\":1,"
			"\"Data\":{"
			"	\"Time\":[%1,%2,%3,%4,%5,%6]"
			"}"
			"}"
		).arg(current.date().year()).arg(current.date().month()).arg(current.date().day())
			.arg(current.time().hour()).arg(current.time().minute()).arg(current.time().second());

		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		QString result((char*)lpOutBuffer);
		if (0 != getJsonValue(result, "Result").toInt())
			return false;
	}
	break;

	default:
		return false;
	}

	return true;
}

bool DeviceHttp::ctrlUtc(int iChNo, CMS_CONNECT_PARSE_UtcCmdType eCmd) {
	I8HCache *cache = DeviceHttp::sta_mapCache.value(this->connectionHandle());
	if (NULL == cache)
		return false;

	QDateTime current = QDateTime::currentDateTime();

	if (2 == cache->m_iVersion) {
		QString strUrl = QString("frmUTCControl");
		QString strReq = QString(
			"{"
			"\"type\":1,"
			"\"ch\":%1,"
			"\"param\":{"
			"	\"ip\":\"%2\","
			"	\"username\":\"%3\","
			"	\"pwd\":\"%4\""
			"},"
			"\"data\":{"
			"	\"oper\":%5,"
			"	\"start\":0,"
			"	\"speed\":5"
			"}"
			"}"
		).arg(iChNo).arg(cache->m_strDeviceIP).arg(cache->m_strUsername).arg(cache->m_strPassword).arg((int)eCmd);

		BYTE lpOutBuffer[8192];
		memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
		DWORD dwOutBufSize = 8192;
		DWORD dwOutSize = 0;

		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		QString result((char*)lpOutBuffer);
		if (0 != getJsonValue(result, "result").toInt())
			return false;
	}
	else if (10 == cache->m_iVersion) {
		QString strUrl = QString("frmUtcControl");
		QString strReq = QString(
			"{"
			"\"Type\":1,"
			"\"Ch\":%1,"
			"\"Data\":{"
			"	\"Cmd\":%2"
			"}"
			"}"
		).arg(iChNo).arg((int)eCmd);

		BYTE lpOutBuffer[8192];
		memset(lpOutBuffer, 0, sizeof(BYTE) * 8192);
		DWORD dwOutBufSize = 8192;
		DWORD dwOutSize = 0;

		if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)strUrl.toUtf8().data(), (BYTE*)strReq.toUtf8().data(), strReq.size() + 1, lpOutBuffer, dwOutBufSize, &dwOutSize))
			return false;

		QString result((char*)lpOutBuffer);
		if (0 != getJsonValue(result, "Result").toInt())
			return false;
	}
	else {
		return false;
	}

	return true;
}

bool DeviceHttp::tranData(char* url, char* inBuffer, int inLen, char* &outBuffer, int &outLen) {
	outBuffer = NULL;
	outLen = 0;

	DWORD dwOutBufSize = 32 * 1024 * 1024;
	BYTE *lpOutBuffer = new BYTE[dwOutBufSize];
	DWORD dwOutSize = 0;

	if (!I8H_SDK_TranData(this->connectionHandle(), (BYTE*)url, (BYTE*)inBuffer, inLen, lpOutBuffer, dwOutBufSize, &dwOutSize)) {
		qDebug() << "I8H_SDK_TranData failed" << I8H_SDK_GetLastError();
		delete[]lpOutBuffer;
		return false;
	}

	if (dwOutSize == 0) {
		qDebug() << "dwOutSize == 0";
		delete[]lpOutBuffer;
		return false;
	}

	outLen = dwOutSize;
	outBuffer = (char*)malloc(outLen);
	memcpy(outBuffer, lpOutBuffer, outLen);

	delete[]lpOutBuffer;
	return true;
}

void DeviceHttp::setConnectionHandle(HANDLE handle) {
	if (NULL != handle) {
		m_alarmHandle = I8H_SDK_SetupAlarmByRTSP(handle);
	}
	else {
		I8H_SDK_CloseAlarmByRTSP(m_alarmHandle);
	}

	m_hConnection = handle;
}

void CALLBACK Http_Search_CallBack(LPI8H_DEV_NODE lpDev, LPVOID lpUser) {
	{
		QMutexLocker locker(&DeviceHttp::sta_mutexSearching);
		if (!DeviceHttp::sta_isSearching) {
			return;
		}
	}
	if (lpDev == NULL) {
		return;
	}


	QString strSerialNumber = QString((char *)lpDev->bySerialNo).toUpper();

#ifdef TE_VERSION
	QString str = strSerialNumber.left(2);

	str = QString(lpDev->struNetInfos->szIP);

	if (QString("05") != str) {
		return;
	}
#endif

	QString strIp(lpDev->struNetInfos[0].szIP);


	if (!(((lpDev->bWebApi_ServerStatus && lpDev->bWebApi_ServerValid)
		|| (lpDev->bWebNginx_ServerStatus && lpDev->bWebNginx_ServerValid))
		&& lpDev->byRTSPStatus
		&& lpDev->byRTSPValid)) {
		//过滤不支持i8H协议的设备
		return;
	}

	if (DeviceHttp::sta_searchHelper.isExist(strSerialNumber, strIp)) {
		//过滤搜索到的重复设备
		return;
	}

	CMS_CONNECT_PARSE_SearchDeviceInfo searchDeviceInfo;
	memset(&searchDeviceInfo, 0, sizeof(CMS_CONNECT_PARSE_SearchDeviceInfo));
	//传回来的序列号是错误的，所以暂时屏蔽掉
	strcpy(searchDeviceInfo.cSerialNum, strSerialNumber.toUtf8().data());
	strcpy(searchDeviceInfo.cDeviceIP, strIp.toUtf8().data());
	//if (0 != lpDev->bOvfs_IPC) {
	//	searchDeviceInfo.eDeviceType = DeviceType_IPC_2;
	//}
	//else {
		if (strstr(lpDev->szDeviceType, "DVR") != NULL) {
			searchDeviceInfo.eDeviceType = DeviceType_DVR;
		}
		else if (strstr(lpDev->szDeviceType, "NVR") != NULL) {
			searchDeviceInfo.eDeviceType = DeviceType_NVR;
		}
		else if (strstr(lpDev->szDeviceType, "IPC") != NULL) {
			searchDeviceInfo.eDeviceType = DeviceType_IPC;
		}
		else {
			//根据通道数判断
			return;
		}
	//}

	int iMainVersion = lpDev->dwSoftwareVersion >> 16;
	int iSubVerion = lpDev->dwSoftwareVersion & 0xFFFF;
	union {
		struct
		{
			char day;
			char mon;
			short year;
		};
		int date;
	} BuildDate;
	BuildDate.date = lpDev->dwSoftwareBuildDate;

	QString strVersion = QString("V%1.%2.%3%4%5").arg(iMainVersion).arg(iSubVerion).arg(BuildDate.year).arg((int)BuildDate.mon, 2, 10, QLatin1Char('0')).arg((int)BuildDate.day, 2, 10, QLatin1Char('0'));
	qDebug() << "CMS_CONNECT_PARSE_SearchDeviceInfo version" << strVersion;

	strcpy(searchDeviceInfo.cUsername, lpDev->szName);
	strcpy(searchDeviceInfo.cPassword, lpDev->szPwd);
	strcpy(searchDeviceInfo.cVersion, strVersion.toUtf8().data());

	if (lpDev->bWebApi_ServerStatus && lpDev->bWebApi_ServerValid) {
		searchDeviceInfo.eProtocolType = ProtocolType_I8H;
	}
	else {
		searchDeviceInfo.eProtocolType = ProtocolType_GoAhead;
	}

	// 	searchDeviceInfo.eProtocolType = ProtocolType_I8H;

	// 	if ((lpDev->bWebNginx_ServerValid && lpDev->bWebNginx_ServerStatus))
	//     {
	//         /*server为nginx, 需要使用https端口*/
	//         searchDeviceInfo.iDevicePort = lpDev->wPorts[3];
	//     }
	//     else
	//     {
	//         searchDeviceInfo.iDevicePort = lpDev->wPorts[1];
	//     }

	searchDeviceInfo.iDevicePort = lpDev->wPorts[1];


	DeviceHttp::sta_searchHelper.func(searchDeviceInfo, DeviceHttp::sta_searchHelper.pUser);
}


void DeviceHttp::startSearchDevice(CMS_SEARCHDEVICE_CALLBACK func, void *pUser) {
	DeviceHttp::sta_searchHelper.clearSearchingCache();
	DeviceHttp::sta_searchHelper.func = func;
	DeviceHttp::sta_searchHelper.pUser = pUser;
	{
		QMutexLocker locker(&DeviceHttp::sta_mutexSearching);
		DeviceHttp::sta_isSearching = true;
	}
	bool ret = I8H_SDK_StartDiscovery("ch0", Http_Search_CallBack, NULL);
}

void DeviceHttp::stopSearchDevice() {
	{
		QMutexLocker locker(&DeviceHttp::sta_mutexSearching);
		DeviceHttp::sta_isSearching = false;
	}
	I8H_SDK_StopDiscovery();
}

I8HCache::I8HCache(QString strUsername,
	QString strPassword,
	QString strSerialNum,
	QString strIP,
	int iPort,
	int iDeviceType,
	BYTE iVersion,
	int iChannelCount)
	: m_strUsername(strUsername),
	m_strPassword(strPassword),
	m_strSerialNum(strSerialNum),
	m_strDeviceIP(strIP),
	m_iPort(iPort),
	m_eDeviceType(iDeviceType),
	m_iVersion(iVersion),
	m_iChannelCount(iChannelCount) {

}


I8HCache::~I8HCache() {

}


