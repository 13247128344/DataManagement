#define  IVMS_DEBUG 0

#include "log.h"
#include "PipedServerApi.h"
#include "alarminfowidget.h"
#include <QApplication>
#include <QtWidgets/QApplication>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QFile>

#pragma comment(lib,"ivms_public.lib")
#if IVMS_DEBUG
#pragma comment(lib,"ants_ivms_pipeserver.lib")

//此处保存主窗口指针，方便命名管道回调的时候进行调用，如果有自己喜欢的其他方法，可以按自己喜好进行.
 //Log* g_DeviceManage = nullptr;

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
#endif

int main(int argc, char *argv[])
{

#if IVMS_DEBUG

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
#endif

	QApplication a(argc, argv);
	Log t;
	//AlarmInfoWidget w;
	QDir::setCurrent(QApplication::applicationDirPath());

	QFile file;
	file.setFileName("./cmssurface.qss");
	if (file.open(QIODevice::ReadOnly))
	{
		a.setStyleSheet(file.readAll());
		file.close();
	}

#if IVMS_DEBUG
	//初始化命名管道服务
		ants_named_pipe_init();
		ants_named_pipe_setCallback(my_NamedPipeMsgCallback);
		//设置命名管道服务，IVMS客户端其他进程通过该管道名称与当前进程通信
		const char p[] = "\\\\.\\pipe\\ivms_Log";
		char *path = new char[30];
		strcpy(path, p);
		if (!ants_named_pipe_setup(path))
		{
			return 0;
		}
	
		//g_DeviceManage = &w;
		WId id = t.winId();
	
		QJsonDocument doc;
		QJsonObject obj;
		obj.insert("msgType", "0");
		obj.insert("from", "ivms_Log");
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
		const char q[] = "\\\\.\\pipe\\ants_ivms_mainframe";
		char *word = new char[30];
		strcpy(word, q);
		DWORD result = ants_named_pipe_sendMsgToServer(word, byteArray.data(), byteArray.length(), outBuffer, 256, &outSize);
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
#endif
		t.show();
	return a.exec();
}

