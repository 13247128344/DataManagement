#include "ivms_devicemanage.h"
#include <QtWidgets/QApplication>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QFile>
#include "PipedServerApi.h"
#include "../ivms_public/ivms_public_function.h"
#include "../ivms_public/CMSTreeView.h"

//此处保存主窗口指针，方便命名管道回调的时候进行调用，如果有自己喜欢的其他方法，可以按自己喜好进行.
ivms_devicemanage* g_DeviceManage = nullptr;

void __stdcall my_NamedPipeMsgCallback(char* inBuffer, int inBufferSize, char* outBuffer, int outBufferSize, int* outSize)
{
	if (!inBuffer || !outBuffer)
	{
		return;
	}

	//IVMS客户端各进程使用JSON格式数据进行消息传递
	QJsonParseError error;
	QByteArray jsonArray(inBuffer, inBufferSize);
	QJsonDocument doc = QJsonDocument::fromJson(jsonArray, &error);
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			QJsonObject obj = doc.object();
			if (!obj.isEmpty())
			{
				QString msgType = obj["msgType"].toString();
				if (msgType == "2")
				{

				}
			}
		}
	}
}

int main(int argc, char *argv[])
{
	//不允许IVMS客户端子进程手动点击启动
	if (argc < 2)
	{
		return 0;
	}

	//不是启动字符串，直接返回
	if (std::string(argv[1]) != "ants_ivms_childprocess_run")
	{
		return 0;
	}

	QApplication a(argc, argv);

	QDir::setCurrent(QApplication::applicationDirPath());

	QFile file;
	file.setFileName("./ivms_devicemanage.qss");
	if (file.open(QIODevice::ReadOnly))
	{
		a.setStyleSheet(file.readAll());
		file.close();
	}

	//初始化命名管道服务
	ants_named_pipe_init();
	ants_named_pipe_setCallback(my_NamedPipeMsgCallback);
	//设置命名管道服务，IVMS客户端其他进程通过该管道名称与当前进程通信
	if (!ants_named_pipe_setup("\\\\.\\pipe\\ivms_devicemanage"))
	{
		return 0;
	}

	//请求设备数据,若请求失败，则退出程序,  设备管理客户端向服务端请求设备数据，其他进程向设备管理客户端请求数据
	/*char* strJson = "{\"resultCode\":0,\"errorMessage\":\"\",\"areas\":["
		"{ \"areaName\":\"测试test\",\"devices\":[{ \"serialNum\":\"0210398219831\",\"deviceName\":\"办公室\","
		"\"username\":\"admin\",\"password\":\"123456\",\"deviceIP\":\"192.168.9.1\",\"devicePort\":8000 ,"
		" \"deviceType\":1,\"protocolType\":1,\"channelCount\":1,\"alarmInCount\":4,\"alarmOutCount\":1 "
		",\"isOnline\":1,\"channels\":[ { \"channelNo\":1,\"channelName\":\"ants\",\"isCMSRecord\":1,\"isDeviceRecord\":1 ,"
		" \"isRecordRight\":1,\"isPlaybackRight\":1,\"isIntercomRight\":1,\"ptzLevel\":1 } ] }] ,\"areas\":[]}  ]}";*/

	QString strDevice = sendGrpcRequestToIVmsServer("ivms_devicemanage","IVMS/DeviceManagement","/IVMS/DeviceManagement/v1/deviceTree/get","");

	QJsonParseError error;
	//QJsonDocument docTree = QJsonDocument::fromJson(QString::fromLocal8Bit(strJson).toUtf8(), &error);
	QJsonDocument docTree = QJsonDocument::fromJson(strDevice.toUtf8(), &error);

	if (error.error == QJsonParseError::NoError)
	{
		if (docTree.isObject())
		{
			QJsonObject obj = docTree.object();
			if (!InitTreeModel(obj))
			{
				//解析失败直接退出程序
				return 0;
			}
			CMSTreeView::initTreeModel(0);
		}
		else
		{
			//解析失败直接退出程序
			return 0;
		}
	}
	else
	{
		QString str = error.errorString();
		return 0;
	}

	ivms_devicemanage w;
	g_DeviceManage = &w;
	WId id = w.winId();

	QJsonDocument doc;
	QJsonObject obj;
	obj.insert("msgType", "0");
	obj.insert("from", "ivms_devicemanage");
	obj.insert("target", "");

	QJsonObject dataObj;
	QJsonArray array;
	QJsonObject jobj;
	jobj.insert("name", "application");   //application为该进程主窗口
	jobj.insert("WId", QString::number((int)id));
	array.append(jobj);
	dataObj.insert("data", array);
	obj.insert("msgData", dataObj);
	doc.setObject(obj);

	QByteArray byteArray = doc.toJson(QJsonDocument::Compact);

	//接收缓冲区大小，按自己需求申请大小
	char* outBuffer = new char[256];
	int outSize = 0;
	DWORD result = ants_named_pipe_sendMsgToServer("\\\\.\\pipe\\ants_ivms_mainframe", byteArray.data(), byteArray.length(), outBuffer, 256, &outSize);
	if (result != NAMED_PIPE_NO_ERROR)
	{
		if (outBuffer)
		{
			delete[] outBuffer;
			outBuffer = nullptr;
		}
		return 0;
	}

	//解析JSON

	//

	if (outBuffer)
	{
		delete[] outBuffer;
		outBuffer = nullptr;
	}

	w.show();
	return a.exec();
}
