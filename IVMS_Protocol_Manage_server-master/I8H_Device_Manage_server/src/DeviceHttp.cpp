#include "DeviceHttp.h"
#include <QString>
#include <QDebug>
#include "I8H_SDK.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCoreApplication>
#include <QFile>
#include "QMutexLocker"

#define I8H_G711_U 1
#define DEVICE_MESSAGE_ONLINE "device.message.online"
#define DEVICE_MESSAGE_ALARM "device.message.alarm"

QMap<HANDLE, I8HCache *> DeviceHttp::sta_mapCache;
QMutex DeviceHttp::sta_mutexCache;
QHash<QString, QSharedPointer<DeviceHttp> > DeviceHttp::sta_hashInstance;

CMS_MESSAGEINFO_CALLBACK G_FUNC = NULL;

DeviceHttp::DeviceHttp(QString strSerialNum, int rtp_type, QObject *parent)
{
	
}

DeviceHttp::~DeviceHttp() {

}

void DeviceHttp::setCAllback(CMS_MESSAGEINFO_CALLBACK pFunc)
{
	G_FUNC = pFunc;
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

	QSharedPointer<DeviceHttp> pContext = DeviceHttp::sta_hashInstance.value(pCache->m_strSerialNum);
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
				else if (I8H_ALARMTYPE_IVS_PERSONDETECT_ALARM == lpAlarm->dwMainAlarmType) {
					eAlarmType = AlarmType_Person;
				}
				else {
					continue;
				}

				iParam = QString((char *)lpAlarm->lpBuffer).toInt();
			}


		/*	if (NULL != pContext->m_pDevice && NULL != pContext->m_pDevice->m_pAlarmCallbackFunc) {
				pContext->m_pDevice->m_pAlarmCallbackFunc(eAlarmType, pContext->m_pDevice->serialNum(), iParam, pContext->m_pDevice->m_pAlarmCallbackUser);
			}*/
			if (G_FUNC != NULL)
			{
				QJsonObject object;
				object.insert("serialNum", pCache->m_strSerialNum);
				object.insert("alarmType", eAlarmType);
				object.insert("iParam", iParam);
				object.insert("isStoped", 0);
				QDateTime dtCurrent = QDateTime::currentDateTime();
				time_t timeCurrent = dtCurrent.toTime_t();
				object.insert("timeUTC", timeCurrent);
				QJsonDocument document;
				document.setObject(object);
				QByteArray array = document.toJson(QJsonDocument::Compact);

				G_FUNC(DEVICE_MESSAGE_ALARM, array.data());
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
	QSharedPointer<DeviceHttp> pContext = DeviceHttp::sta_hashInstance.value(pCache->m_strSerialNum);
	if (pContext.isNull())
		return;

	if (dwType == I8H_DEVICE_ONLINE) {
	
		if (G_FUNC != NULL)
		{
			QJsonObject object;
			object.insert("serialNum", pCache->m_strSerialNum);
			object.insert("isOnline", 1);
			QJsonDocument document;
			document.setObject(object);
			QByteArray array = document.toJson(QJsonDocument::Compact);
			G_FUNC(DEVICE_MESSAGE_ONLINE, array.data());
		}
	}
	else if (dwType == I8H_DEVICE_OFFLINE) {
		
		if (G_FUNC != NULL)
		{

			QJsonObject object;
			object.insert("serialNum", pCache->m_strSerialNum);
			object.insert("isOnline", 0);
			QJsonDocument document;
			document.setObject(object);
			QByteArray array = document.toJson(QJsonDocument::Compact);
			G_FUNC(DEVICE_MESSAGE_ONLINE, array.data());
		}
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

		//判断授权
		/*if (-1 != g_iMaxExtendedCount[I8HDeviceAuthorityIndex] && g_iCurrentExtendedCount[I8HDeviceAuthorityIndex] + sLoginInfo.iChannelCount > g_iMaxExtendedCount[I8HDeviceAuthorityIndex]) {
			I8H_SDK_Logout(loginHandle);
			return false;
		}*/

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

bool DeviceHttp::tranData(char* url, char* inBuffer, int inLen, int inOverTime, int inNeedSise, char* &outBuffer, int &outLen) {
	outBuffer = NULL;
	outLen = 0;

	DWORD dwOutBufSize = 32 * 1024 * 1024;
	DWORD dwBufSize = inNeedSise * 1024 * 1024;
	BYTE *lpOutBuffer = new BYTE[dwOutBufSize];
	DWORD dwOutSize = 0;

	//!I8H_SDK_TranData(HANDLE hUserId, BYTE *lpUrl, BYTE *lpInBuffer, DWORD dwInSize, BYTE *lpOutBuffer, DWORD dwOutBufSize, DWORD *lpOutSize);

	//!dwTimeout = (超时时间(秒)<< 16)|(尝试次数) dwBufSize需要多大的缓冲区(以字节为单位,默认为1 * 1024 * 1024)
	//I8H_SDK_TranDatav3(HANDLE hUserId, BYTE *lpUrl, BYTE *lpInBuffer, DWORD dwInSize, BYTE *lpOutBuffer, DWORD dwOutBufSize, DWORD *lpOutSize, 30<<16|1);//!dwTimeout = (超时时间(秒)<< 16)|(尝试次数)



	if (!I8H_SDK_TranDatav3(this->connectionHandle(), (BYTE*)url, (BYTE*)inBuffer, inLen, lpOutBuffer, dwOutBufSize, &dwOutSize, inOverTime << 16 | 1, dwBufSize)) {
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

const HANDLE DeviceHttp::connectionHandle()
{
	return m_hConnection;
}


I8HCache::I8HCache(QString strUsername,
	QString strPassword,
	QString strSerialNum,
	QString strIP,
	int iPort,
	int iDeviceType,
	unsigned char iVersion,
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