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

//�˴�����������ָ�룬���������ܵ��ص���ʱ����е��ã�������Լ�ϲ�����������������԰��Լ�ϲ�ý���.
 //Log* g_DeviceManage = nullptr;

void __stdcall my_NamedPipeMsgCallback(char* inBuffer, int inBufferSize, char* outBuffer, int outBufferSize, int* outSize)
{
	if (!inBuffer || !outBuffer)
	{
		return;
	}

	//IVMS�ͻ��˸�����ʹ��JSON��ʽ���ݽ�����Ϣ����
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

	//������IVMS�ͻ����ӽ����ֶ��������
	if (argc < 2)
	{
		return 0;
	}

	//���������ַ�����ֱ�ӷ���
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
	//��ʼ�������ܵ�����
		ants_named_pipe_init();
		ants_named_pipe_setCallback(my_NamedPipeMsgCallback);
		//���������ܵ�����IVMS�ͻ�����������ͨ���ùܵ������뵱ǰ����ͨ��
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
		jobj.insert("name", "application");   //applicationΪ�ý���������
		jobj.insert("WId", QString::number((int)id));
		array.append(jobj);
		dataObj.insert("data", array);
		obj.insert("msgData", dataObj);
		doc.setObject(obj);
	
		QByteArray byteArray = doc.toJson(QJsonDocument::Compact);
	
		//���ջ�������С�����Լ����������С
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
	
		//����JSON
	
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

