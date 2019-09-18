#define IVMS_DEBUG 1

#include "alarm.h"
#include "alarmcfg.h"
#include <QApplication>
#include <QApplication>
#include <QtWidgets/QApplication>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QFile>
#include "PipedServerApi.h"
#include "loading.h"
#include "linkageprevrec.h"
#include "QMessageBox"
#include "../include/ivms_public_function.h"
#include "../include/CMSTreeView.h"

#pragma comment(lib,"ants_ivms_pipeserver.lib")
#pragma comment(lib,"ivms_public.lib")

//�˴�����������ָ�룬���������ܵ��ص���ʱ����е��ã�������Լ�ϲ�����������������԰��Լ�ϲ�ý���.
//Log* g_DeviceManage = nullptr;

#if IVMS_DEBUG

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
// 	if (argc < 2)
// 	{
// 		return 0;
// 	}
// 
// // 	//���������ַ�����ֱ�ӷ���
// 	if (std::string(argv[1]) != "ants_ivms_childprocess_run")
// 	{
// 		return 0;
// 	}
#endif

	QApplication a(argc, argv);
	Alarm w;

//	QDir::setCurrent(QApplication::applicationDirPath());

// 	QFile file;
// 	file.setFileName("./ivms_Alarm.qss");
// 	if (file.open(QIODevice::ReadOnly))
// 	{
// 		a.setStyleSheet(file.readAll());
// 		file.close();
// 	}

#if IVMS_DEBUG
    //��ʼ�������ܵ�����
	ants_named_pipe_init();
	ants_named_pipe_setCallback(my_NamedPipeMsgCallback);
	//���������ܵ�����IVMS�ͻ�����������ͨ���ùܵ������뵱ǰ����ͨ��
	const char p[] = "\\\\.\\pipe\\ivms_AlarmLog";
	char *path = new char[30];
	strcpy(path, p);
	if (!ants_named_pipe_setup(path))
	{
		return 0;
	}


	QString strDevice = sendGrpcRequestToIVmsServer("ivms_AlarmLog", "IVMS/DeviceManagement", "/IVMS/DeviceManagement/v1/deviceTree/get", "");

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
				//����ʧ��ֱ���˳�����
				return 0;
			}
			CMSTreeView::initTreeModel(0);
		}
		else
		{
			//����ʧ��ֱ���˳�����
			return 0;
		}
	}
	else
	{
		QString str = error.errorString();
		return 0;
	}


	//g_DeviceManage = &w;
	WId id = w.winId();

	QJsonDocument doc;
	QJsonObject obj;
	obj.insert("msgType", "0");
	obj.insert("from", "ivms_AlarmLog");
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

	if (outBuffer)
	{
		delete[] outBuffer;
		outBuffer = nullptr;
	}
#endif

	w.show();
	return a.exec();
}

