#ifndef HANDLEHTTP_H
#define HANDLEHTTP_H

#include "DeviceHttp.h"
#include "QJsonObject"
#include "QJsonDocument"
#include "QJsonArray"
#include "QJsonValue"
using namespace std;

QMap< string,std::function<string(QString)>> constructors;




std::string getCommonResponse(int resultCode, QString msg)
{
	QJsonObject obj;
	obj["resultCode"] = resultCode;
	obj["errorMessage"] = msg;

	QJsonDocument json_doc;
	json_doc.setObject(obj);
	return json_doc.toJson(QJsonDocument::Compact).constData();

}


QJsonObject getJsonObject(QString json) {

	QJsonDocument jsonDocument = QJsonDocument::fromJson(json.toUtf8().data());

	QJsonObject jsonObject = jsonDocument.object();
	return jsonObject;
}



//增加设备
string addDevice(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	//DeviceHttp::login(obj);
	QString username = obj.value("username").toString();
	QString password = obj.value("password").toString();
	LoginInfo loginInfo;

	loginInfo.strDeviceIP = obj.value("deviceIp").toString();
	loginInfo.iDevicePort = obj.value("devicePort").toInt(0);

	//qDebug() << QString(buffer->data().c_str()) << username << password << loginInfo.strDeviceIP << loginInfo.iDevicePort;

	if (!DeviceHttp::login(username, password, loginInfo))
	{
		//buffer->set_data(getCommonResponse(1, "login failed,please check param"));
		return getCommonResponse(1, "login failed,please check param");
	}
	else
	{

		//登录成功
		QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(loginInfo.strSerialNum);
		if (!device.isNull())
		{
			DeviceHttp::logout(loginInfo.handle);
			//有重复设备
			//buffer->set_data(getCommonResponse(3, "this device has been add"));
			return getCommonResponse(3, "this device has been add");
		}
		else {
			QSharedPointer<DeviceHttp> ptr(new DeviceHttp(loginInfo.strSerialNum, obj.value("rtpType").toInt(1)));

			{
				//QMutexLocker locker(&sta_mutexInstance);
				DeviceHttp::sta_hashInstance.insert(loginInfo.strSerialNum, ptr);
			}
			ptr->setConnectionHandle(loginInfo.handle);


			QJsonObject response;
			response["resultCode"] = 0;
			response["errorMessage"] = "";
			QJsonObject deviceInfo;
			deviceInfo["serialNum"] = loginInfo.strSerialNum;
			deviceInfo["deviceType"] = loginInfo.eDeviceType;
			deviceInfo["deviceIp"] = loginInfo.strDeviceIP;
			deviceInfo["devicePort"] = loginInfo.iDevicePort;
			deviceInfo["channelCount"] = loginInfo.iChannelCount;
			deviceInfo["alarmInCount"] = loginInfo.iAlarmInCount;
			deviceInfo["alarmOutCount"] = loginInfo.iAlarmOutCount;
			response["deviceInfo"] = deviceInfo;

			QJsonDocument json_doc;
			json_doc.setObject(response);
			//buffer->set_data(json_doc.toJson(QJsonDocument::Compact).data());
			return json_doc.toJson(QJsonDocument::Compact).data();
		}

	}

}


//删除设备
string delDevice(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		DeviceHttp::logout(device->connectionHandle());
	}
	DeviceHttp::sta_hashInstance.take(obj.value("serialNum").toString());
	return getCommonResponse(0, "");
}


//操作云台
string ptzCtrl(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iChannel = obj.value("channel").toInt();
		int iIsStop = obj.value("isStop").toInt();
		int iSpeed = obj.value("speed").toInt();
		int iPtzType = obj.value("ptzType").toInt();
		if (!device->ptzCtrl(iChannel, CMS_CONNECT_PARSE_PtzCmdType(iPtzType), iIsStop, iSpeed))
		{
			return getCommonResponse(1, "Operation ptz failed");
		}

		return getCommonResponse(0, "");
	}
	return getCommonResponse(1, "this device has not found");
}

//预置点设置
string presetCtrl(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iChannel = obj.value("channel").toInt();
		int iPresetIndex = obj.value("presetIndex").toInt();
		int iPresetType = obj.value("presetType").toInt();
		if (!device->presetCtrl(iChannel, iPresetIndex, CMS_CONNECT_PARSE_PresetCmdType(iPresetType)))
		{
			return getCommonResponse(1, "Operation presetCtrl failed");
		}
		return getCommonResponse(0, "");
	}
	return getCommonResponse(1, "this device has not found");
}

//获取巡航
string getCruise(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iChannel = obj.value("channel").toInt();
		int iCruiseRoute = obj.value("cruiseRoute").toInt();
		CMS_CONNECT_PARSE_CruisePoint_Param * results = NULL;
		int iParamCount = 0;
		if (!device->getCruise(iChannel, iCruiseRoute, results, iParamCount))
		{
			return getCommonResponse(1, "Operation getCruise failed");
		}
		QJsonObject object;
		object.insert("resultCode", 0);
		QJsonObject jsonObject;
		QJsonArray array;
		for (int i = 0; i < iParamCount; i++)
		{
			jsonObject.insert("presetIndex", results[i].iPreset);
			jsonObject.insert("staySec", results[i].iStaySec);
			jsonObject.insert("speed", results[i].iSpeed);
			array.append(jsonObject);
		}
		object.insert("cruises", QJsonValue(array));
		QJsonDocument json_doc;
		json_doc.setObject(object);
		delete[]results;
		return json_doc.toJson(QJsonDocument::Compact).data();
	}
	return getCommonResponse(1, "this device has not found");
}

//设置巡航
string setCruise(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iChannel = obj.value("channel").toInt();
		int iCruiseRoute = obj.value("cruiseRoute").toInt();
		int iCruisePoint = obj.value("cruisePoint").toInt();
		int iPresetIndex = obj.value("presetIndex").toInt();
		int iStaySec = obj.value("staySec").toInt();
		int iSpeed = obj.value("speed").toInt();
		CMS_CONNECT_PARSE_CruisePoint_Param requst;
		memset(&requst, 0, sizeof(CMS_CONNECT_PARSE_CruisePoint_Param));
		requst.iPreset = iPresetIndex;
		requst.iSpeed = iSpeed;
		requst.iStaySec = iStaySec;
		if (!device->setCruise(iChannel, iCruiseRoute, iCruisePoint, requst))
		{
			return getCommonResponse(1, "setCruise failed");
		}
		return getCommonResponse(0, "");
	}
	return getCommonResponse(1, "this device has not found");
}


//删除巡航点
string deleteCruise(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iChannel = obj.value("channel").toInt();
		int iCruiseRoute = obj.value("cruiseRoute").toInt();
		int iCruisePoint = obj.value("cruisePoint").toInt();
		if (!device->deleteCruise(iChannel, iCruiseRoute, iCruisePoint))
		{
			return getCommonResponse(1, "deleteCruise failed");
		}
		return getCommonResponse(0, "");
	}
	return getCommonResponse(1, "this device has not found");
}

//清理巡航
string clearCruise(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iChannel = obj.value("channel").toInt();
		int iCruiseRoute = obj.value("cruiseRoute").toInt();
		if (!device->clearCruise(iChannel, iCruiseRoute))
		{
			return getCommonResponse(1, "clearCruise failed");
		}
		return getCommonResponse(0, "");
	}
	return getCommonResponse(1, "this device has not found");
}

//开启或停止巡航
string runCruise(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iChannel = obj.value("channel").toInt();
		int iCruiseRoute = obj.value("cruiseRoute").toInt();
		int iIsStop = obj.value("isStoped").toInt();
		if (!device->runCruise(iChannel, iCruiseRoute,iIsStop))
		{
			return getCommonResponse(1, "runCruise failed");
		}
		return getCommonResponse(0, "");
	}
	return getCommonResponse(1, "this device has not found");
}

//设置轨迹
string setlocusCtrl(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iChannel = obj.value("channel").toInt();
		int iLocusIndex = obj.value("locusIndex").toInt();
		int iIsStop = obj.value("isStoped").toInt();
		if (!device->locusCtrl(iChannel, iLocusIndex, LOCUS_SET, iIsStop))
		{
			return getCommonResponse(1, "setlocusCtrl failed");
		}
		return getCommonResponse(0, "");
	}
	return getCommonResponse(1, "this device has not found");
}

//运行轨迹
string runlocusCtrl(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iChannel = obj.value("channel").toInt();
		int iLocusIndex = obj.value("locusIndex").toInt();
		int iIsStop = obj.value("isStoped").toInt();
		if (!device->locusCtrl(iChannel, iLocusIndex, LOCUS_RUN, iIsStop))
		{
			return getCommonResponse(1, "runlocusCtrl failed");
		}
		return getCommonResponse(0, "");
	}
	return getCommonResponse(1, "this device has not found");
}

//3d定位
string set3D(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iChannel = obj.value("channel").toInt();
		int iTopX = obj.value("topX").toInt();
		int iTopY = obj.value("topY").toInt();
		int iBottomX = obj.value("bottomX").toInt();
		int iBottomY = obj.value("bottomY").toInt();
		if (!device->set3D(iChannel, iTopX, iTopY, iBottomX, iBottomY));
		{
			return getCommonResponse(1, "set3D failed");
		}
		return getCommonResponse(0, "");
	}
	return getCommonResponse(1, "this device has not found");
}

//搜索录像
string searchRecord(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iBeginTime = obj.value("beginTimeUTC").toInt();
		int iEndTime = obj.value("endTimeUTC").toInt();
		int iRecordType = obj.value("recordType").toInt();
		int iRecordType_condition = obj.value("recordType_condition").toInt();
		QJsonArray jsonArray = obj["channels"].toArray();
		QList<int> chList;
		for (int i = 0; i < jsonArray.size(); i++)
		{
			chList.append(jsonArray.at(i).toInt());
		}
		CMS_CONNECT_PARSE_SearchRecord_Param* p_cmsRecSearch = NULL;
		int listCount = 0;
		if (!device->searchRecord(StreamType_Main, iBeginTime, iEndTime, iRecordType, CMS_CONNECT_PARSE_RecordType_Condition(iRecordType_condition), chList, p_cmsRecSearch, listCount))
		{
			return getCommonResponse(1, "searchRecord failed");
		}
		QJsonObject object;
		object.insert("resultCode", 0);
		QJsonObject jsonObject;
		QJsonArray array;
		for (int j = 0; j < listCount; j++)
		{
			jsonObject.insert("serialNum", QString(p_cmsRecSearch[j].ch.cSerialNum));
			jsonObject.insert("channel", p_cmsRecSearch[j].ch.iChannel);
			jsonObject.insert("recordType", int(p_cmsRecSearch[j].iRecordType));
			jsonObject.insert("beginTimeUTC", int(p_cmsRecSearch[j].timeUTC_Begin));
			jsonObject.insert("endTimeUTC", int(p_cmsRecSearch[j].timeUTC_End));
			jsonObject.insert("fileSize", int(p_cmsRecSearch[j].lFileSize));
			array.append(jsonObject);
		}
		object.insert("records", QJsonValue(array));
		QJsonDocument json_doc;
		json_doc.setObject(object);
		if (listCount > 0)
		{
			delete[]p_cmsRecSearch;
		}
		return json_doc.toJson(QJsonDocument::Compact).data();
	}
	return getCommonResponse(1, "this device has not found");
}

//获取预览rtsp流地址
string getPreviewRtsp(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iChannel = obj.value("channel").toInt();
		int iStreamType = obj.value("streamType").toInt();
		int iIsStandard = obj.value("isStandard").toInt();
		I8HCache *cache = DeviceHttp::sta_mapCache.value(device->connectionHandle());
		if (NULL == cache)
		{
			return getCommonResponse(1, "this device has not found");
		}
		QString strIp = cache->m_strDeviceIP;
		if (iIsStandard)
		{
			QString strRtspUrl = "";
			QString rtspChannel= QString("%1").arg(iChannel, 2, 10, QChar('0'));
			if (iStreamType == StreamType_Main)
			{
				strRtspUrl = QString("rtsp://%1:%2/ch%3.264?ptype=udp").arg(strIp).arg(554).arg(rtspChannel);
			}
			else
			{
				strRtspUrl = QString("rtsp://%1:%2/ch%3_sub.264?ptype=udp").arg(strIp).arg(554).arg(rtspChannel);
			}

			QJsonObject rtspObject;
			rtspObject.insert("resultCode", 0);
			rtspObject.insert("RtspUrl", strRtspUrl);
			QJsonDocument json_doc;
			json_doc.setObject(rtspObject);
			return json_doc.toJson(QJsonDocument::Compact).data();
		}
		else
		{
			char *url = "frmGetRtspUrl";
			QJsonObject object;
			object.insert("Ch", 1);
			object.insert("Type", 0);
			QJsonObject dataObject;
			dataObject.insert("Channel", iChannel);
			dataObject.insert("Ip", strIp);
			dataObject.insert("StreamType", iStreamType);
			object.insert("Data", QJsonValue(dataObject));
			QJsonDocument document;
			document.setObject(object);
			QByteArray array = document.toJson(QJsonDocument::Compact);
			char *outBuffer = NULL;
			int outLen = 0;
			if (!device->tranData(url, array.data(), array.length(), 10, 1, outBuffer, outLen));
			{
				return getCommonResponse(1, "tranData failed");
			}
			if (outBuffer != NULL)
			{
				QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
				QJsonObject root = doc.object();
				free(outBuffer);
				if (root["Result"].toInt(-1) == 0)
				{
					QJsonObject jsonObject = root.value("Data").toObject();
					QString strRtsp = jsonObject["RtspUrl"].toString();
					QJsonObject rtspObject;
					rtspObject.insert("resultCode", 0);
					rtspObject.insert("RtspUrl", strRtsp);
					QJsonDocument json_doc;
					json_doc.setObject(rtspObject);
					return json_doc.toJson(QJsonDocument::Compact).data();
				}
				return getCommonResponse(1, "getPreviewRtsp failed");
			}
			return getCommonResponse(1, "getPreviewRtsp failed");
		}
		
	}
	return getCommonResponse(1, "this device has not found");
}

//获取对讲rtsp地址

string getTalkRtsp(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iChannel = obj.value("channel").toInt();
		int iAudioType = obj.value("audioType").toInt();
		I8HCache *cache = DeviceHttp::sta_mapCache.value(device->connectionHandle());
		if (NULL == cache)
		{
			return getCommonResponse(1, "this device has not found");
		}
		QString strIp = cache->m_strDeviceIP;
	
		char *url = "frmGetRtspUrl";
		QJsonObject object;
		object.insert("Ch", 1);
		object.insert("Type", 1);
		QJsonObject dataObject;
		dataObject.insert("Channel", iChannel);
		dataObject.insert("Ip", strIp);
		dataObject.insert("AudioType", iAudioType);
		object.insert("Data", QJsonValue(dataObject));
		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 10, 1, outBuffer, outLen));
		{
			return getCommonResponse(1, "tranData failed");
		}
		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				QJsonObject jsonObject = root.value("Data").toObject();
				QString strRtsp = jsonObject["RtspUrl"].toString();
				QJsonObject rtspObject;
				rtspObject.insert("resultCode", 0);
				rtspObject.insert("RtspUrl", strRtsp);
				QJsonDocument json_doc;
				json_doc.setObject(rtspObject);
				return json_doc.toJson(QJsonDocument::Compact).data();
			}
			return getCommonResponse(1, "getTalkRtsp failed");
		}
		return getCommonResponse(1, "getTalkRtsp failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//获取回放rtsp地址
string getReplayRtsp(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iChannel = obj.value("channel").toInt();
		int iStreamType = obj.value("streamType").toInt();
		int iIsStandard = obj.value("isStandard").toInt();
		QString strStartTime = obj.value("startTime").toString();
		QString strEndTime = obj.value("stopTime").toString();
		int iIsAnd = obj.value("isAnd").toInt();
		int iInquiryType = obj.value("inquiryType").toInt();
		I8HCache *cache = DeviceHttp::sta_mapCache.value(device->connectionHandle());
		if (NULL == cache)
		{
			return getCommonResponse(1, "this device has not found");
		}
		QString strIp = cache->m_strDeviceIP;
		if (iIsStandard)
		{
			QString strRtspUrl = "";
			if (iStreamType == StreamType_Main)
			{
				strRtspUrl = QString("rtsp://%1:%2/recording?ch=%3&stream=0&start=%4&stop=%5").arg(strIp).arg(554).arg(iChannel).arg(strStartTime).arg(strEndTime);
			}
			else
			{
				strRtspUrl = QString("rtsp://%1:%2/recording?ch=%3&stream=1&start=%4&stop=%5").arg(strIp).arg(554).arg(iChannel).arg(strStartTime).arg(strEndTime);
			}

			QJsonObject rtspObject;
			rtspObject.insert("resultCode", 0);
			rtspObject.insert("RtspUrl", strRtspUrl);
			QJsonDocument json_doc;
			json_doc.setObject(rtspObject);
			return json_doc.toJson(QJsonDocument::Compact).data();
		}
		else
		{
			char *url = "frmGetRtspUrl";
			QJsonObject object;
			object.insert("Ch", 1);
			object.insert("Type", 3);
			QJsonObject dataObject;
			dataObject.insert("Channel", iChannel);
			dataObject.insert("Ip", strIp);
			dataObject.insert("StreamType", iStreamType);
			dataObject.insert("StartTime", strStartTime);
			dataObject.insert("StopTime", strEndTime);
			dataObject.insert("IsAnd", iIsAnd);
			dataObject.insert("InquiryType", iInquiryType);
			object.insert("Data", QJsonValue(dataObject));
			QJsonDocument document;
			document.setObject(object);
			QByteArray array = document.toJson(QJsonDocument::Compact);
			char *outBuffer = NULL;
			int outLen = 0;
			if (!device->tranData(url, array.data(), array.length(), 10, 1, outBuffer, outLen));
			{
				return getCommonResponse(1, "tranData failed");
			}
			if (outBuffer != NULL)
			{
				QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
				QJsonObject root = doc.object();
				free(outBuffer);
				if (root["Result"].toInt(-1) == 0)
				{
					QJsonObject jsonObject = root.value("Data").toObject();
					QString strRtsp = jsonObject["RtspUrl"].toString();
					QJsonObject rtspObject;
					rtspObject.insert("resultCode", 0);
					rtspObject.insert("RtspUrl", strRtsp);
					QJsonDocument json_doc;
					json_doc.setObject(rtspObject);
					return json_doc.toJson(QJsonDocument::Compact).data();
				}
				return getCommonResponse(1, "getReplayRtsp failed");
			}
			return getCommonResponse(1, "getReplayRtsp failed");
		}

	}
	return getCommonResponse(1, "this device has not found");
}

////获取回放rtsp地址v2
//string getReplayRtspV2(QString buffer)
//{
//	QJsonObject obj = getJsonObject(buffer);
//	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
//	if (!device.isNull())
//	{
//		int iChannel = obj.value("channel").toInt();
//		int iStreamType = obj.value("streamType").toInt();
//		int iIsStandard = obj.value("isStandard").toInt();
//		QString strStartTime = obj.value("startTime").toString();
//		QString strEndTime = obj.value("stopTime").toString();
//		int iIsAnd = obj.value("isAnd").toInt();
//		int iInquiryType = obj.value("inquiryType").toInt();
//		I8HCache *cache = DeviceHttp::sta_mapCache.value(device->connectionHandle());
//		if (NULL == cache)
//		{
//			return getCommonResponse(1, "this device has not found");
//		}
//		QString strIp = cache->m_strDeviceIP;
//		if (iIsStandard)
//		{
//			QString strRtspUrl = "";
//			if (iStreamType == StreamType_Main)
//			{
//				strRtspUrl = QString("rtsp://%1:%2/recording?ch=%3&stream=0&start=%4&stop=%5").arg(strIp).arg(554).arg(iChannel).arg(strStartTime).arg(strEndTime);
//			}
//			else
//			{
//				strRtspUrl = QString("rtsp://%1:%2/recording?ch=%3&stream=1&start=%4&stop=%5").arg(strIp).arg(554).arg(iChannel).arg(strStartTime).arg(strEndTime);
//			}
//
//			QJsonObject rtspObject;
//			rtspObject.insert("resultCode", 0);
//			rtspObject.insert("RtspUrl", strRtspUrl);
//			QJsonDocument json_doc;
//			json_doc.setObject(rtspObject);
//			return json_doc.toJson(QJsonDocument::Compact).data();
//		}
//	}
//	return getCommonResponse(1, "this device has not found");
//}

//获取智能rtsp地址
string getIntelligentRtsp(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iChannel = obj.value("channel").toInt();
		int iMediaType = obj.value("mediaType").toInt();
		
		I8HCache *cache = DeviceHttp::sta_mapCache.value(device->connectionHandle());
		if (NULL == cache)
		{
			return getCommonResponse(1, "this device has not found");
		}
		QString strIp = cache->m_strDeviceIP;
		QString rtspChannel = QString("%1").arg(iChannel, 2, 10, QChar('0'));
		QString strRtspUrl = QString("rtsp://%1:%2/living_comb%3.264?MediaType=%4").arg(strIp).arg(554).arg(rtspChannel).arg(iMediaType);

		QJsonObject rtspObject;
		rtspObject.insert("resultCode", 0);
		rtspObject.insert("RtspUrl", strRtspUrl);
		QJsonDocument json_doc;
		json_doc.setObject(rtspObject);
		return json_doc.toJson(QJsonDocument::Compact).data();
	}
	return getCommonResponse(1, "this device has not found");
}

//添加人脸库
string addSample(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		QString strTargetName = obj.value("TargetName").toString();
		int iTargetType = obj.value("TargetType").toInt();
		char *url = "frmFaceDatabase";
		QJsonObject object;
		object.insert("Type", 0);
		object.insert("Ch", 1);
		QJsonObject jsonObject;
		jsonObject.insert("TargetName", strTargetName);
		jsonObject.insert("TargetType", iTargetType);
		object.insert("Data", QJsonValue(jsonObject));
		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 10, 1, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				return getCommonResponse(0, "");
			}
			else
			{
				return getCommonResponse(1, "addSample failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//删除人脸库
string deleteSample(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		QString strTargetName = obj.value("TargetName").toString();
		char *url = "frmFaceDatabase";
		QJsonObject object;
		object.insert("Type", 1);
		object.insert("Ch", 1);
		QJsonObject jsonObject;
		jsonObject.insert("TargetName", strTargetName);
		object.insert("Data", QJsonValue(jsonObject));
		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 10, 1, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				return getCommonResponse(0, "");
			}
			else
			{
				return getCommonResponse(1, "deleteSample failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//修改人脸数据库
string modifySample(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		QString strTargetName = obj.value("TargetName").toString();
		QString strNewTargetName = obj.value("NewTargetName").toString();
		int iTargetType = obj.value("TargetType").toInt();
		char *url = "frmFaceDatabase";
		QJsonObject object;
		object.insert("Type", 2);
		object.insert("Ch", 1);
		QJsonObject jsonObject;
		jsonObject.insert("TargetName", strTargetName);
		jsonObject.insert("NewTargetName", strNewTargetName);
		jsonObject.insert("TargetType", iTargetType);
		object.insert("Data", QJsonValue(jsonObject));
		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 10, 1, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				return getCommonResponse(0, "");
			}
			else
			{
				return getCommonResponse(1, "modifySample failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//清空人脸数据库
string clearSample(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		QString strTargetName = obj.value("TargetName").toString();
		char *url = "frmFaceDatabase";
		QJsonObject object;
		object.insert("Type", 3);
		object.insert("Ch", 1);
		QJsonObject jsonObject;
		jsonObject.insert("TargetName", strTargetName);
		object.insert("Data", QJsonValue(jsonObject));
		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 10, 1, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				return getCommonResponse(0, "");
			}
			else
			{
				return getCommonResponse(1, "clearSample failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//获取人脸数据库数目
string getSampleNum(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		char *url = "frmFaceDatabase";
		QJsonObject object;
		object.insert("Type", 4);
		object.insert("Ch", 1);
		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 10, 1, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				QJsonObject dataObject = root["Data"].toObject();
				int iSampleNum = dataObject.value("TargetItemTotalNum").toInt();
				QJsonObject rtspObject;
				rtspObject.insert("resultCode", 0);
				rtspObject.insert("SampleNum", iSampleNum);
				QJsonDocument json_doc;
				json_doc.setObject(rtspObject);
				return json_doc.toJson(QJsonDocument::Compact).data();
			}
			else
			{
				return getCommonResponse(1, "getSampleNum failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//获取人脸库详细信息
string getSampleInfo(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iOffset = obj.value("Offset").toInt();
		int iNum = obj.value("Num").toInt();

		char *url = "frmFaceDatabase";
		QJsonObject object;
		object.insert("Type", 5);
		object.insert("Ch", 1);
		QJsonObject jsonObject;
		jsonObject.insert("Offset", iOffset);
		jsonObject.insert("Num", iNum);
		object.insert("Data", QJsonValue(jsonObject));
		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 10, 1, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				
				QJsonObject data = root.value("Data").toObject();
				QJsonObject targetresults = data.value("TargetResults").toObject();
				QJsonArray list = targetresults.value("TargetItems").toArray();

				QJsonObject resultObject;
				resultObject.insert("resultCode", 0);
				QJsonArray resultArray;

				for (int i = 0; i < list.size(); ++i)
				{
					QJsonObject item = list.at(i).toObject();

					QJsonObject listItemObject;
					listItemObject.insert("TargetName", item.value("TargetName").toString());
					listItemObject.insert("TargetType", item.value("TargetType").toInt());
					listItemObject.insert("Count", item.value("Count").toInt());
					resultArray.append(listItemObject);
				}

				resultObject.insert("TargetItems", QJsonValue(resultArray));
		
				QJsonDocument json_doc;
				json_doc.setObject(resultObject);
				return json_doc.toJson(QJsonDocument::Compact).data();
			}
			else
			{
				return getCommonResponse(1, "getSampleInfo failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//设置人脸库关联通道
string setSampleRelevanceChannel(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		QString strTargetName = obj.value("TargetName").toString();
		QJsonArray jsonArray = obj["LinkChList"].toArray();
		
		char *url = "frmFaceDatabase";
		QJsonObject object;
		object.insert("Type", 6);
		object.insert("Ch", 1);
		QJsonObject jsonObject;
		jsonObject.insert("TargetName", strTargetName);
		jsonObject.insert("LinkChList", QJsonValue(jsonArray));
		object.insert("Data", QJsonValue(jsonObject));
		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 10, 1, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				return getCommonResponse(0, "");
			}
			else
			{
				return getCommonResponse(1, "setSampleRelevanceChannel failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//获取人脸库关联通道
string getSampleRelevanceChannel(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		QString strTargetName = obj.value("TargetName").toString();
		char *url = "frmFaceDatabase";
		QJsonObject object;
		object.insert("Type", 7);
		object.insert("Ch", 1);
		QJsonObject jsonObject;
		jsonObject.insert("TargetName", strTargetName);
		object.insert("Data", QJsonValue(jsonObject));
		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 10, 1, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				QJsonObject resultObject = root["Data"].toObject();
				QString strSampleName = resultObject["TargetName"].toString();
				QJsonArray resultArray = resultObject["LinkChList"].toArray();
				QJsonObject sendObject;
				sendObject.insert("resultCode", 0);
				sendObject.insert("TargetName", strSampleName);
				sendObject.insert("LinkChList", QJsonValue(resultArray));
				QJsonDocument json_doc;
				json_doc.setObject(sendObject);
				return json_doc.toJson(QJsonDocument::Compact).data();
			}
			else
			{
				return getCommonResponse(1, "getSampleRelevanceChannel failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//人脸模板添加
string addFaceTemplet(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		QString strTargetName = obj.value("TargetName").toString();
		QJsonArray jsonArray = obj["List"].toArray();
		char *url = "frmFacePicture";
		QJsonObject object;
		object.insert("Type", 0);
		object.insert("Ch", 1);
		QJsonObject jsonObject;
		jsonObject.insert("TargetName", strTargetName);
		jsonObject.insert("List", QJsonValue(jsonArray));
		object.insert("Data", QJsonValue(jsonObject));
		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 10, 3, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				QJsonObject resultObject = root["Data"].toObject();
				QJsonArray resultArray = resultObject["ResultList"].toArray();

				QJsonObject sendObject;
				sendObject.insert("resultCode", 0);
				sendObject.insert("ResultList", QJsonValue(resultArray));
				QJsonDocument json_doc;
				json_doc.setObject(sendObject);
				return json_doc.toJson(QJsonDocument::Compact).data();
			}
			else
			{
				return getCommonResponse(1, "addFaceTemplet failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//人脸模板删除

string deleteFaceTemplet(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		QString strFaceId = obj.value("FaceId").toString();
		char *url = "frmFacePicture";
		QJsonObject object;
		object.insert("Type", 1);
		object.insert("Ch", 1);
		QJsonObject jsonObject;
		jsonObject.insert("FaceId", strFaceId);
		object.insert("Data", QJsonValue(jsonObject));
		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 10, 1, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				return getCommonResponse(0, "");
			}
			else
			{
				return getCommonResponse(1, "deleteFaceTemplet failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//人脸模板数目查询
string searchFaceTempletNum(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iMatchType = obj.value("MatchType").toInt();
		QString strTargetName = obj.value("TargetName").toString();
		QString strName = obj.value("Name").toString();
		QString strDescribe = obj.value("Describe").toString();
		char *url = "frmFacePicture";
		
		QJsonObject object;
		object.insert("Type", 2);
		object.insert("Ch", 1);
		QJsonObject dataobj;
		dataobj.insert("MatchType", iMatchType);
		dataobj.insert("TargetName", strTargetName);
		dataobj.insert("Name", strName);
		dataobj.insert("Describe", strDescribe);
		dataobj.insert("Similarity", 0);
		dataobj.insert("FaceData", "");
		dataobj.insert("ParamMask", 0x07);

		object.insert("Data", dataobj);

		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 30, 1, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				QJsonObject dataJsonObject = root["Data"].toObject();
				QString strFaceResults = dataJsonObject["FaceResults"].toString();
				QJsonObject rtspObject;
				rtspObject.insert("resultCode", 0);
				rtspObject.insert("FaceResults", strFaceResults);
				QJsonDocument json_doc;
				json_doc.setObject(rtspObject);
				return json_doc.toJson(QJsonDocument::Compact).data();
			}
			else
			{
				return getCommonResponse(1, "searchFaceTempletNum failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//查询人脸模板信息
string searchFaceTempletInfo(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		int iMatchType = obj.value("MatchType").toInt();
		QString strTargetName = obj.value("TargetName").toString();
		QString strName = obj.value("Name").toString();
		QString strDescribe = obj.value("Describe").toString();
		int iOffset = obj.value("Offset").toInt();
		int iNum = obj.value("Num").toInt();
		char *url = "frmFacePicture";

		QJsonObject object;
		object.insert("Type", 3);
		object.insert("Ch", 1);
		QJsonObject dataobj;
		dataobj.insert("MatchType", iMatchType);
		dataobj.insert("TargetName", strTargetName);
		dataobj.insert("Name", strName);
		dataobj.insert("Describe", strDescribe);
		dataobj.insert("Similarity", 0);
		dataobj.insert("FaceData", "");
		dataobj.insert("ParamMask", 0x07);
		dataobj.insert("Offset", iOffset);
		dataobj.insert("Num", iNum);

		object.insert("Data", dataobj);

		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 30, 8, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				QJsonObject dataJsonObject = root["Data"].toObject();
				QJsonArray FaceResultsArray = dataJsonObject["FaceResults"].toArray();

				QJsonObject rtspObject;
				rtspObject.insert("resultCode", 0);
				rtspObject.insert("FaceResults", QJsonValue(FaceResultsArray));
				QJsonDocument json_doc;
				json_doc.setObject(rtspObject);
				return json_doc.toJson(QJsonDocument::Compact).data();
			}
			else
			{
				return getCommonResponse(1, "searchFaceTempletInfo failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//人脸模板修改
string modifyFaceTemplet(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{
		
		QString strTargetName = obj.value("TargetName").toString();
		QJsonArray jsonArray = obj["List"].toArray();
		char *url = "frmFacePicture";

		QJsonObject object;
		object.insert("Type", 4);
		object.insert("Ch", 1);
		QJsonObject dataobj;
		dataobj.insert("TargetName", strTargetName);
		dataobj.insert("List", QJsonValue(jsonArray));
		object.insert("Data", dataobj);

		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 30, 3, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				QJsonObject dataJsonObject = root["Data"].toObject();
				QJsonArray FaceResultsArray = dataJsonObject["ResultList"].toArray();

				QJsonObject rtspObject;
				rtspObject.insert("resultCode", 0);
				rtspObject.insert("ResultList", QJsonValue(FaceResultsArray));
				QJsonDocument json_doc;
				json_doc.setObject(rtspObject);
				return json_doc.toJson(QJsonDocument::Compact).data();
			}
			else
			{
				return getCommonResponse(1, "modifyFaceTemplet failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//获取人脸比对查询句柄（不限定条件查询）
string searchFaceRecordWithNothing(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{

		QString strBeginTime = obj.value("BeginDateTime").toString();
		QString strEndTime = obj.value("EndDateTime").toString();
		QJsonArray jsonArray = obj["Channels"].toArray();
		char *url = "frmFacePicture";

		QJsonObject object;
		object.insert("Type", 0);
		QJsonObject dataobj;
		dataobj.insert("BeginDateTime", strBeginTime);
		dataobj.insert("EndDateTime", strBeginTime);
		dataobj.insert("Channels", QJsonValue(jsonArray));
		object.insert("Data", dataobj);

		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 30, 1, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				QJsonObject dataJsonObject = root["Data"].toObject();
				int iResultHandle = dataJsonObject["ResultHandle"].toInt();

				QJsonObject rtspObject;
				rtspObject.insert("resultCode", 0);
				rtspObject.insert("ResultHandle", iResultHandle);
				QJsonDocument json_doc;
				json_doc.setObject(rtspObject);
				return json_doc.toJson(QJsonDocument::Compact).data();
			}
			else
			{
				return getCommonResponse(1, "searchFaceRecordWithNothing failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//获取人脸比对查询句柄（图片）
string searchFaceRecordWithPic(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{

		QString strBeginTime = obj.value("BeginDateTime").toString();
		QString strEndTime = obj.value("EndDateTime").toString();
		int iSimilarity = obj.value("Similarity").toInt();
		QString strFaceData = obj.value("FaceData").toString();
		QJsonArray jsonArray = obj["Channels"].toArray();
		char *url = "frmFacePicture";

		QJsonObject object;
		object.insert("Type", 2);
		QJsonObject dataobj;
		dataobj.insert("BeginDateTime", strBeginTime);
		dataobj.insert("EndDateTime", strBeginTime);
		dataobj.insert("Similarity", iSimilarity);
		dataobj.insert("FaceData", strFaceData);
		dataobj.insert("Channels", QJsonValue(jsonArray));
		object.insert("Data", dataobj);

		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 30, 1, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				QJsonObject dataJsonObject = root["Data"].toObject();
				int iResultHandle = dataJsonObject["ResultHandle"].toInt();

				QJsonObject rtspObject;
				rtspObject.insert("resultCode", 0);
				rtspObject.insert("ResultHandle", iResultHandle);
				QJsonDocument json_doc;
				json_doc.setObject(rtspObject);
				return json_doc.toJson(QJsonDocument::Compact).data();
			}
			else
			{
				return getCommonResponse(1, "searchFaceRecordWithPic failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//获取人脸比对查询句柄（黑白名单）
string searchFaceRecordWithListType(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{

		QString strBeginTime = obj.value("BeginDateTime").toString();
		QString strEndTime = obj.value("EndDateTime").toString();
		int iSearchType = obj.value("SearchType").toInt();
		QJsonArray jsonArray = obj["Channels"].toArray();
		char *url = "frmFacePicture";

		QJsonObject object;
		object.insert("Type", 3);
		QJsonObject dataobj;
		dataobj.insert("BeginDateTime", strBeginTime);
		dataobj.insert("EndDateTime", strBeginTime);
		dataobj.insert("SearchType", iSearchType);
		dataobj.insert("Channels", QJsonValue(jsonArray));
		object.insert("Data", dataobj);

		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 30, 1, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				QJsonObject dataJsonObject = root["Data"].toObject();
				int iResultHandle = dataJsonObject["ResultHandle"].toInt();

				QJsonObject rtspObject;
				rtspObject.insert("resultCode", 0);
				rtspObject.insert("ResultHandle", iResultHandle);
				QJsonDocument json_doc;
				json_doc.setObject(rtspObject);
				return json_doc.toJson(QJsonDocument::Compact).data();
			}
			else
			{
				return getCommonResponse(1, "searchFaceRecordWithListType failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//获取查询进度
string searchFaceRecordState(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{

		int iResultHandle = obj.value("ResultHandle").toInt();
		char *url = "frmFacePicture";

		QJsonObject object;
		object.insert("Type", 4);
		QJsonObject dataobj;
		dataobj.insert("ResultHandle", iResultHandle);
		object.insert("Data", dataobj);

		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 30, 1, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				QJsonObject dataJsonObject = root["Data"].toObject();
				int iTotalSearchNum = dataJsonObject["TotalSearchNum"].toInt();
				int iCurrentSearchNum = dataJsonObject["CurrentSearchNum"].toInt();
				int iMatchNum = dataJsonObject["MatchNum"].toInt();
				int iStatusCode = dataJsonObject["StatusCode"].toInt();
				QJsonObject rtspObject;
				rtspObject.insert("resultCode", 0);
				rtspObject.insert("TotalSearchNum", iTotalSearchNum);
				rtspObject.insert("CurrentSearchNum", iCurrentSearchNum);
				rtspObject.insert("MatchNum", iMatchNum);
				rtspObject.insert("StatusCode", iStatusCode);

				QJsonDocument json_doc;
				json_doc.setObject(rtspObject);
				return json_doc.toJson(QJsonDocument::Compact).data();
			}
			else
			{
				return getCommonResponse(1, "searchFaceRecordState failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

//获取查询结果
string getSearchFaceRecordResult(QString buffer)
{
	QJsonObject obj = getJsonObject(buffer);
	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
	if (!device.isNull())
	{

		int iResultHandle = obj.value("ResultHandle").toInt();
		int iOffset = obj.value("Offset").toInt();
		int iNum = obj.value("Num").toInt();
		char *url = "frmFacePicture";

		QJsonObject object;
		object.insert("Type", 5);
		QJsonObject dataobj;
		dataobj.insert("ResultHandle", iResultHandle);
		dataobj.insert("Offset", iOffset);
		dataobj.insert("Num", iNum);
		object.insert("Data", dataobj);

		QJsonDocument document;
		document.setObject(object);
		QByteArray array = document.toJson(QJsonDocument::Compact);
		char *outBuffer = NULL;
		int outLen = 0;
		if (!device->tranData(url, array.data(), array.length(), 30, 8, outBuffer, outLen))
		{
			return getCommonResponse(1, "tranData failed");
		}

		if (outBuffer != NULL)
		{
			QJsonDocument doc = QJsonDocument::fromJson(outBuffer);
			QJsonObject root = doc.object();
			free(outBuffer);
			if (root["Result"].toInt(-1) == 0)
			{
				QJsonObject dataJsonObject = root["Data"].toObject();
				QJsonArray dataJsonArrray = root["FaceResults"].toArray();
				QJsonObject rtspObject;
				rtspObject.insert("resultCode", 0);
				rtspObject.insert("FaceResults", QJsonValue(dataJsonArrray));
				QJsonDocument json_doc;
				json_doc.setObject(rtspObject);
				return json_doc.toJson(QJsonDocument::Compact).data();
			}
			else
			{
				return getCommonResponse(1, "getSearchFaceRecordResult failed");
			}
		}
		return getCommonResponse(1, "tranData failed");
	}
	return getCommonResponse(1, "this device has not found");
}

////获取通道名
//string getChName(QString buffer)
//{
//	QJsonObject obj = getJsonObject(buffer);
//	QSharedPointer<DeviceHttp> device = DeviceHttp::sta_hashInstance.value(obj.value("serialNum").toString());
//	if (!device.isNull())
//	{
//		I8HCache *cache = DeviceHttp::sta_mapCache.value(device->connectionHandle());
//		device->getChName(cache->m_iVersion, device->connectionHandle(), cache->m_strDeviceIP, cache->m_strUsername, cache->m_strPassword);
//	}
//	return getCommonResponse(1, "this device has not found");
//}


void initHandleFunc() {
	constructors["/IVMS/DeviceManagement/v1/device/add"] = addDevice;
	constructors["/IVMS/DeviceManagement/v1/device/del"] = delDevice;
	constructors["/IVMS/DeviceManagement/v1/ptz"] = ptzCtrl;
	constructors["/IVMS/DeviceManagement/v1/preset"] = presetCtrl;
	constructors["/IVMS/DeviceManagement/v1/cruise/get"] = getCruise;
	constructors["/IVMS/DeviceManagement/v1/cruise/point/set"] = setCruise;
	constructors["/IVMS/DeviceManagement/v1/cruise/point/del"] = deleteCruise;
	constructors["/IVMS/DeviceManagement/v1/cruise/point/clear"] = clearCruise;
	constructors["/IVMS/DeviceManagement/v1/cruise"] = runCruise;
	constructors["/IVMS/DeviceManagement/v1/locus/set"] = setlocusCtrl;
	constructors["/IVMS/DeviceManagement/v1/locus/run"] = runlocusCtrl;
	constructors["/IVMS/DeviceManagement/v1/3D/set"] = set3D;
	constructors["/IVMS/DeviceManagement/v1/device/record"] = searchRecord;
	constructors["/IVMS/DeviceManagement/v1/device/getPreviewRtsp"] = searchRecord;
	constructors["/IVMS/DeviceManagement/v1/device/record"] = searchRecord;
	constructors["/IVMS/DeviceManagement/v1/device/record"] = searchRecord;
	constructors["/IVMS/DeviceManagement/v1/device/record"] = searchRecord;
	constructors["/IVMS/DeviceManagement/v1/device/record"] = searchRecord;
	constructors["/IVMS/DeviceManagement/v1/device/record"] = searchRecord;
	constructors["/IVMS/DeviceManagement/v1/device/record"] = searchRecord;
	constructors["/IVMS/DeviceManagement/v1/device/record"] = searchRecord;
	constructors["/IVMS/DeviceManagement/v1/device/record"] = searchRecord;
	constructors["/IVMS/DeviceManagement/v1/device/record"] = searchRecord;
	constructors["/IVMS/DeviceManagement/v1/device/record"] = searchRecord;
}

















#endif // HANDLEHTTP_H
