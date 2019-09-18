#include "alarmcfg.h"
#include "ui_alarmcfg.h"
#include "ui_enabledcontrol.h"
#include "ui_tvwallctrl.h"
#include <QTimer>
#include <QBrush>
#include <QPixmap>
#include <QScrollBar>
#include "qdebug.h"
#include "qfile.h"
#include "QMessageBox"
#include "alarm.h"
#include "QMouseEvent"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include "alarmcfg.h"
#include "tvwallctrl.h"
#include "enabledcontrol.h"
#include "PipedServerApi.h"
#include "addlinkagerule.h"
#include "addaccesslinkagerule.h"
#include "./include/ivms_public.h"
#include "./include/CMSTreeView.h"

#define ROW_HEIGHT 30

AlarmCfg* AlarmCfg::stra_AlarmLinkageManage = NULL;
AlarmCfg* AlarmCfg::getAlarmLinkageManage(QWidget *parent)
{
	if (stra_AlarmLinkageManage == NULL)
	{
		stra_AlarmLinkageManage = new AlarmCfg(parent);
	}
	return stra_AlarmLinkageManage;
}

AlarmCfg::AlarmCfg(QWidget *parent)
	: QWidget(parent)
	, _pLoading(new Loading)
	, ui(new Ui::AlarmCfg)
{
	ui->setupUi(this);

	connect(ui->btnAddLinkRule, SIGNAL(clicked()), this, SLOT(btnAddLinkRule_clicked()));
	connect(ui->btnAddAccessLinkRule, SIGNAL(clicked()), this, SLOT(btnAddAccessLinkRule_clicked()));
	connect(ui->btnUpdLinkRule, SIGNAL(clicked()), this, SLOT(btnUpdLinkRule_clicked()));
	connect(ui->tableWidget_Linkage, SIGNAL(itemSelectionChanged()), this, SLOT(onItemSelectionChanged()));
	
	ui->textEdit->setReadOnly(true);
	
	ui->tableWidget_Linkage->setColumnCount(6);
	QStringList headerList;
	
	headerList << tr("Rule Name") << tr("Alarm Type") << tr("Alarm Source") << tr("Remarks") << tr("Enable") << tr("DESCRIPTION");
	ui->tableWidget_Linkage->setHorizontalHeaderLabels(headerList);
	ui->tableWidget_Linkage->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidget_Linkage->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableWidget_Linkage->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableWidget_Linkage->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	this->setWindowFlags(Qt::FramelessWindowHint);

 	QTimer::singleShot(100, this, SLOT(InitLinkRule()));

#ifdef ACCESSMANAGE
#else
	ui->btnAddAccessLinkRule->hide();
#endif
}

AlarmCfg::~AlarmCfg()
{
	stra_AlarmLinkageManage = NULL;
    delete ui;
}

void AlarmCfg::btnAddLinkRule_clicked()
{
	IVMS_CONNECT_PARSE_LinkageRuleParam param;
	AddLinkageRule addLinkageRule(param, this);
	if (QDialog::Accepted == addLinkageRule.exec())
	{
		btnUpdLinkRule_clicked();
	}
}

void AlarmCfg::btnAddAccessLinkRule_clicked()
{
	IVMS_CONNECT_PARSE_LinkageRuleParam param;
	AddLinkageRule addLinkageRule(param, this);
	if (QDialog::Accepted == addLinkageRule.exec())
	{
		btnUpdLinkRule_clicked();
	}

}

//刷新联动规则
void AlarmCfg::btnUpdLinkRule_clicked()
{
	if (_pLoading != NULL)
		_pLoading->startLoading();
	QTimer::singleShot(100, this, SLOT(InitLinkRule()));
}

//查看告警联动详细信息
void AlarmCfg::onItemSelectionChanged()
{
	QJsonDocument doc;
	QJsonObject obj;
	obj.insert("msgType", "1");
	obj.insert("from", "ivms_Log");
	obj.insert("target", "ivms_serverMain");

	QJsonObject dataObj;
	dataObj.insert("topic", "IVMS/LinkageManagement");
	dataObj.insert("cmd", "/IVMS/LinkageManagement/v1/linkage/rule/get");
	dataObj.insert("token", "121312312");
	dataObj.insert("connectTime", 12);

	QJsonObject data;
	data.insert("", "");


	QJsonDocument tempDoc;
	tempDoc.setObject(data);

	QByteArray temp = tempDoc.toJson(QJsonDocument::Compact);

	dataObj.insert("data", QString(temp));
	obj.insert("msgData", dataObj);
	doc.setObject(obj);

	int tmpIn = data.value("timeBegin").toInt();
	QByteArray byteArray = doc.toJson(QJsonDocument::Compact);

	//接收缓冲区大小，按自己需求申请大小
	char* outBuffer = new char[10000];
	int outSize = 0;
	const char q[] = "\\\\.\\pipe\\ants_ivms_mainframe";
	char *word = new char[30];
	strcpy(word, q);
	DWORD result = ants_named_pipe_sendMsgToServer(word, byteArray.data(), byteArray.length(), outBuffer, 10000, &outSize);

	outBuffer[outSize] = '\0';

	QJsonDocument jsonDocument = QJsonDocument::fromJson(outBuffer);
	QJsonObject jObj = jsonDocument.object();
	QJsonArray resultArray = jObj.value("result").toArray();

	QList<QTableWidgetItem *> items = ui->tableWidget_Linkage->selectedItems();

	if (items.size() > 0)
	{
		int iResult = items[0]->data(Qt::UserRole).value<int>();
		if (iResult == 1)
		{
			int iRow = ui->tableWidget_Linkage->row(items[0]);
			int iCount = ui->tableWidget_Linkage->rowSpan(iRow, 0);
			QString ruleName = ui->tableWidget_Linkage->item(iRow, 0)->text();
			for (int k = 0; k < resultArray.size(); k++)
			{
				QJsonObject json = resultArray.at(k).toObject();
				QString cRuleName = json.value("ruleName").toString();
				if (ruleName == QString(cRuleName))//判断是否存在,有可能已经被其他客户端删除了
				{
					QJsonDocument doc;
					QJsonObject obj;
					obj.insert("msgType", "1");
					obj.insert("from", "ivms_Log");
					obj.insert("target", "ivms_serverMain");

					QJsonObject dataObj;
					dataObj.insert("topic", "IVMS/LinkageManagement");
					dataObj.insert("cmd", "/IVMS/LinkageManagement/v1/linkage/action/get");
					dataObj.insert("token", "121312312");
					dataObj.insert("connectTime", 12);

					QJsonObject data;
					data.insert("ruleName", ruleName);


					QJsonDocument tempDoc;
					tempDoc.setObject(data);

					QByteArray temp = tempDoc.toJson(QJsonDocument::Compact);

					dataObj.insert("data", QString(temp));
					obj.insert("msgData", dataObj);
					doc.setObject(obj);

					int tmpIn = data.value("timeBegin").toInt();
					QByteArray byteArray = doc.toJson(QJsonDocument::Compact);

					//接收缓冲区大小，按自己需求申请大小
					char* outBuffer = new char[1024 * 10];
					int outSize = 0;
					const char q[] = "\\\\.\\pipe\\ants_ivms_mainframe";
					char *word = new char[30];
					strcpy(word, q);
					DWORD result = ants_named_pipe_sendMsgToServer(word, byteArray.data(), byteArray.length(), outBuffer, 1024 * 10, &outSize);

					outBuffer[outSize] = '\0';

					QJsonDocument jsonDocument = QJsonDocument::fromJson(outBuffer);
					QJsonObject jObj = jsonDocument.object();
					QJsonArray resultJsonArray = jObj.value("result").toArray();
					QJsonObject resultJson = resultJsonArray.at(0).toObject();

					int ruleActionCount = resultJson.value("paramCount").toInt();
					QString strLinkageInfo = "                   " + tr("DETAILS") + "\n";
					strLinkageInfo += tr("Rule Name") + ":\n  ";
					strLinkageInfo += ui->tableWidget_Linkage->item(iRow, 0)->text();
					strLinkageInfo += "\n\n" + tr("Alarm Type") + ":\n  ";
					strLinkageInfo += ui->tableWidget_Linkage->item(iRow, 1)->text();
					strLinkageInfo += "\n\n" + tr("Alarm Source") + ":\n  ";
					strLinkageInfo += ui->tableWidget_Linkage->item(iRow, 2)->text();
					strLinkageInfo += "\n\n" + tr("Linkage Action") + ":\n  ";
					qDebug() << "ruleActionCount" << ruleActionCount;

					if (ruleActionCount > 0)
					{
						for (int i = 0; i < ruleActionCount; i++)
						{
							int actiontype = resultJson.value("connectParseLinkageActionType").toInt();
							if (actiontype == ivms_LinkageActionType_PopImage)
								strLinkageInfo += "[" + tr("PREVIEW") + "]\n  ";
							else if (actiontype == ivms_LinkageActionType_Wall)
								strLinkageInfo += "[" + tr("TVWALL") + "]\n  ";
							else if (actiontype == ivms_LinkageActionType_Map)
								strLinkageInfo += "[" + tr("MAP") + "]\n  ";
							else if (actiontype == ivms_LinkageActionType_Record)
								strLinkageInfo += "[" + tr("RECORD") + "]\n  ";
							else if (actiontype == ivms_LinkageActionType_Capture)
								strLinkageInfo += "[" + tr("CAPTURE") + "]\n  ";
							else if (actiontype == ivms_LinkageActionType_PTZ)
								strLinkageInfo += "[" + tr("PTZ") + "]\n  ";
							for (int j = 0; j < ruleActionCount; j++)
							{
								QJsonArray actionParamArray = resultJson.value("linkageActionParam").toArray();
								QJsonObject linkageActionParam = actionParamArray.at(j).toObject();
								/*
								QModelIndex modelIndex = CMSTreeView::getModelIndexByDevSNandChNo(linkageActionParam.value("deviceSerialNum").toString(), linkageActionParam.value("channelNum").toInt());
								if (modelIndex == QModelIndex())
									return;
								if (actiontype == ivms_LinkageActionType_Wall)
								{

									strLinkageInfo += ("  " + QString(CMSTreeView::getNodebyModelIndex(modelIndex)->parent->cNodeName) + "_"
										+ QString(CMSTreeView::getNodebyModelIndex(modelIndex)->cNodeName) + " " +
										tr("to") + " " + ";\n  ");

								}
								else if (actiontype == ivms_LinkageActionType_PTZ)
								{
									strLinkageInfo += ("  " + QString(CMSTreeView::getNodebyModelIndex(modelIndex)->parent->cNodeName) + "_"
										+ QString(CMSTreeView::getNodebyModelIndex(modelIndex)->cNodeName) + ":");
									if (linkageActionParam.value("connectParseLinkagePtzType").toInt() == LinkagePtzType_GotoPreset)
									{
										strLinkageInfo += tr("Goto Preset") + QString("%1").arg(linkageActionParam.value("ptzIndex").toInt());
									}
									else
									{
										strLinkageInfo += tr("Run Cruise") + QString("%1").arg(linkageActionParam.value("ptzIndex").toInt());
									}
									strLinkageInfo += ";\n  ";
								}
								else
								{
									strLinkageInfo += ("  " + QString(CMSTreeView::getNodebyModelIndex(modelIndex)->parent->cNodeName) + "_"
										+ QString(CMSTreeView::getNodebyModelIndex(modelIndex)->cNodeName) + ";\n  ");
								}
								*/
							}
							if (actiontype != ivms_LinkageActionType_PTZ && actiontype != ivms_LinkageActionType_Capture && actiontype != ivms_LinkageActionType_Record)
							{
								int iSeconds = resultJson.value("stopSec").toInt();
								if (iSeconds == -1)
								{
									strLinkageInfo += "    " + tr("auto stop");
								}
								else
								{
									strLinkageInfo += "    " + tr("stop after") + "  " + QString("%1").arg(iSeconds) + tr("seconds");
								}

							}
							strLinkageInfo += "\n\n  ";
						}

					}
					strLinkageInfo += "\n" + tr("Remarks") + ":\n  ";
					strLinkageInfo += ui->tableWidget_Linkage->item(iRow, 3)->text();
					ui->textEdit->setPlainText(strLinkageInfo);
				}
			}
			delete[] outBuffer;
			outBuffer = NULL;
		}
	}
	delete[] outBuffer;
	outBuffer = NULL;
}

//启用/禁用规则
void AlarmCfg::OnStateChanged(int iState)
{
	QJsonDocument doc;
	QJsonObject obj;
	obj.insert("msgType", "1");
	obj.insert("from", "ivms_Log");
	obj.insert("target", "ivms_serverMain");

	QJsonObject dataObj;
	dataObj.insert("topic", "IVMS/LinkageManagement");
	dataObj.insert("cmd", "/IVMS/LinkageManagement/v1/linkage/rule/get");
	dataObj.insert("token", "121312312");
	dataObj.insert("connectTime", 12);

	QJsonObject data;
	data.insert("", "");


	QJsonDocument tempDoc;
	tempDoc.setObject(data);

	QByteArray temp = tempDoc.toJson(QJsonDocument::Compact);

	dataObj.insert("data", QString(temp));
	obj.insert("msgData", dataObj);
	doc.setObject(obj);

	int tmpIn = data.value("timeBegin").toInt();
	QByteArray byteArray = doc.toJson(QJsonDocument::Compact);

	//接收缓冲区大小，按自己需求申请大小
	char* outBuffer = new char[2048];
	int outSize = 0;
	const char q[] = "\\\\.\\pipe\\ants_ivms_mainframe";
	char *word = new char[30];
	strcpy(word, q);
	DWORD result = ants_named_pipe_sendMsgToServer(word, byteArray.data(), byteArray.length(), outBuffer, 2048, &outSize);

	outBuffer[outSize] = '\0';

	QJsonDocument jsonDocument = QJsonDocument::fromJson(outBuffer);
	QJsonObject jObj = jsonDocument.object();
	QJsonArray resultArray = jObj.value("result").toArray();

	int iRow = -1;
	for (int i = 0; i < ui->tableWidget_Linkage->rowCount(); i++)
	{
		if (ui->tableWidget_Linkage->cellWidget(i, 4) == sender()->parent())// 判断信号来源
		{
			iRow = i;
			break;
		}
	}
	if (iRow < 0)
		return;
	QString ruleName = ui->tableWidget_Linkage->item(iRow, 0)->text();

	int iResult = ui->tableWidget_Linkage->item(iRow, 0)->data(Qt::UserRole).value<int>();

	if (iResult == 1)
	{
		for (int i = 0; i < resultArray.size(); i++)
		{
			QJsonObject json = resultArray.at(i).toObject();
			QString cRuleName = json.value("ruleName").toString();
			if (ruleName == QString(cRuleName))//判断是否存在,有可能已经被其他客户端删除了
			{
				bool isEnabled = iState == Qt::Unchecked ? 0 : 1;

				QJsonDocument doc;
				QJsonObject obj;
				obj.insert("msgType", "1");
				obj.insert("from", "ivms_Log");
				obj.insert("target", "ivms_serverMain");

				QJsonObject dataObj;
				dataObj.insert("topic", "IVMS/LinkageManagement");
				dataObj.insert("cmd", "/IVMS/LinkageManagement/v1/linkage/rule/ena");
				dataObj.insert("token", "121312312");
				dataObj.insert("connectTime", 12);

				QJsonObject data;
				data.insert("ruleName", ruleName);
				data.insert("isEnabled", isEnabled);

				QJsonDocument tempDoc;
				tempDoc.setObject(data);

				QByteArray temp = tempDoc.toJson(QJsonDocument::Compact);

				dataObj.insert("data", QString(temp));
				obj.insert("msgData", dataObj);
				doc.setObject(obj);

				int tmpIn = data.value("timeBegin").toInt();
				QByteArray byteArray = doc.toJson(QJsonDocument::Compact);

				//接收缓冲区大小，按自己需求申请大小
				char* outBuffer = new char[2048];
				int outSize = 0;
				const char q[] = "\\\\.\\pipe\\ants_ivms_mainframe";
				char *word = new char[30];
				strcpy(word, q);
				DWORD result = ants_named_pipe_sendMsgToServer(word, byteArray.data(), byteArray.length(), outBuffer, 2048, &outSize);

				outBuffer[outSize] = '\0';
				/*for (int j = 0; j < m_RuleInfoList.size(); j++)
				{
				if (ruleName == m_RuleInfoList.at(j).first)
				{
				m_RuleInfoList[j].second.second = enableRequest.isEnabled;
				}
				}
				break;*/
				delete[] outBuffer;
				outBuffer = NULL;
			}
		}
		/*for (int y = 0; y < _listAlarm.size(); y++)
		{
		bool b_Delete = false;
		for (int m = 0; m < m_RuleInfoList.size(); m++)
		{
		if (m_RuleInfoList.at(m).second.first == _listAlarm.at(y) && m_RuleInfoList.at(m).second.second == 1)
		{
		b_Delete = true;
		break;
		}
		}
		if (b_Delete == false)
		{
		_listAlarm.removeAt(y);
		}
		}*/
	}

}

//修改规则
void AlarmCfg::OnUpdateRule()
{
	QJsonDocument doc;
	QJsonObject obj;
	obj.insert("msgType", "1");
	obj.insert("from", "ivms_Log");
	obj.insert("target", "ivms_serverMain");

	QJsonObject dataObj;
	dataObj.insert("topic", "IVMS/LinkageManagement");
	dataObj.insert("cmd", "/IVMS/LinkageManagement/v1/linkage/rule/get");
	dataObj.insert("token", "121312312");
	dataObj.insert("connectTime", 12);

	QJsonObject data;
	data.insert("", "");


	QJsonDocument tempDoc;
	tempDoc.setObject(data);

	QByteArray temp = tempDoc.toJson(QJsonDocument::Compact);

	dataObj.insert("data", QString(temp));
	obj.insert("msgData", dataObj);
	doc.setObject(obj);

	int tmpIn = data.value("timeBegin").toInt();
	QByteArray byteArray = doc.toJson(QJsonDocument::Compact);

	//接收缓冲区大小，按自己需求申请大小
	char* outBuffer = new char[10000];
	int outSize = 0;
	const char q[] = "\\\\.\\pipe\\ants_ivms_mainframe";
	char *word = new char[30];
	strcpy(word, q);
	DWORD result = ants_named_pipe_sendMsgToServer(word, byteArray.data(), byteArray.length(), outBuffer, 10000, &outSize);

	outBuffer[outSize] = '\0';

	QJsonDocument jsonDocument = QJsonDocument::fromJson(outBuffer);
	QJsonObject jObj = jsonDocument.object();
	QJsonArray resultArray = jObj.value("result").toArray();

	int iRow = -1;
	QWidget *widget = (QWidget *)sender()->parent()->parent();
	QString name = widget->objectName();
	for (int i = 0; i < ui->tableWidget_Linkage->rowCount(); i++)
	{
		if (ui->tableWidget_Linkage->cellWidget(i, 5) == sender()->parent())// 判断信号来源
		{
			iRow = i;
			break;
		}
	}
	if (iRow < 0)
		return;
	QString ruleName = ui->tableWidget_Linkage->item(iRow, 0)->text();

	int iResult = ui->tableWidget_Linkage->item(iRow, 0)->data(Qt::UserRole).value<int>();

	if (iResult == 1)
	{
		for (int i = 0; i < resultArray.size(); i++)
		{
			QJsonObject json = resultArray.at(i).toObject();
			QString cRuleName = json.value("ruleName").toString();
			if (ruleName == QString(cRuleName))//判断是否存在,有可能已经被其他客户端删除了
			{
				IVMS_CONNECT_PARSE_LinkageRuleParam _ruleParamRequest;
				_ruleParamRequest.ruleName = cRuleName;
				_ruleParamRequest.connectParseAlarmType = json.value("connectParseAlarmType").toInt();
				_ruleParamRequest.isEnabled = json.value("isEnabled").toBool();
				_ruleParamRequest.paramInt = json.value("paramInt").toInt();
				_ruleParamRequest.remarks = json.value("remarks").toString();
				AddLinkageRule addLinkageRule(_ruleParamRequest,this);
				if (QDialog::Accepted == addLinkageRule.exec())
					btnUpdLinkRule_clicked();//更新列表
				break;
			}
		}
	}
	delete[] outBuffer;
	outBuffer = NULL;
}

//删除规则
void AlarmCfg::OnDeleteRule()
{
	int iRow = -1;
	for (int i = 0; i < ui->tableWidget_Linkage->rowCount(); i++)
	{
		if (ui->tableWidget_Linkage->cellWidget(i, 5) == sender()->parent())// 判断信号来源
		{
			iRow = i;
			break;
		}
	}
	if (iRow < 0)
		return;
	QString strRuleName = ui->tableWidget_Linkage->item(iRow, 0)->text();

	int iResult = ui->tableWidget_Linkage->item(iRow, 0)->data(Qt::UserRole).value<int>();

	if (iResult == 1)
	{
		QJsonDocument doc;
		QJsonObject obj;
		obj.insert("msgType", "1");
		obj.insert("from", "ivms_Log");
		obj.insert("target", "ivms_serverMain");

		QJsonObject dataObj;
		dataObj.insert("topic", "IVMS/LinkageManagement");
		dataObj.insert("cmd", "/IVMS/LinkageManagement/v1/linkage/rule/del");
		dataObj.insert("token", "121312312");
		dataObj.insert("connectTime", 12);

		QJsonObject data;
		data.insert("ruleName", strRuleName);

		QJsonDocument tempDoc;
		tempDoc.setObject(data);

		QByteArray temp = tempDoc.toJson(QJsonDocument::Compact);

		dataObj.insert("data", QString(temp));
		obj.insert("msgData", dataObj);
		doc.setObject(obj);

		int tmpIn = data.value("timeBegin").toInt();
		QByteArray byteArray = doc.toJson(QJsonDocument::Compact);

		//接收缓冲区大小，按自己需求申请大小
		char* outBuffer = new char[2048];
		int outSize = 0;
		const char q[] = "\\\\.\\pipe\\ants_ivms_mainframe";
		char *word = new char[30];
		strcpy(word, q);
		DWORD result = ants_named_pipe_sendMsgToServer(word, byteArray.data(), byteArray.length(), outBuffer, 2048, &outSize);

		outBuffer[outSize] = '\0';

		delete[] outBuffer;
		outBuffer = NULL;
	}
}

//定时器获取告警规则数据
void AlarmCfg::InitLinkRule()
{
	GetLinkageRules();
}

void AlarmCfg::GetLinkageRules()
{
	{
		//获取告警联动
		QJsonDocument doc;
		QJsonObject obj;
		obj.insert("msgType", "1");
		obj.insert("from", "ivms_Log");
		obj.insert("target", "ivms_serverMain");

		QJsonObject dataObj;
		dataObj.insert("topic", "IVMS/LinkageManagement");
		dataObj.insert("cmd", "/IVMS/LinkageManagement/v1/linkage/rule/get");
		dataObj.insert("token", "121312312");
		dataObj.insert("connectTime", 12);

		QJsonObject data;
		data.insert("", "");


		QJsonDocument tempDoc;
		tempDoc.setObject(data);

		QByteArray temp = tempDoc.toJson(QJsonDocument::Compact);

		dataObj.insert("data", QString(temp));
		obj.insert("msgData", dataObj);
		doc.setObject(obj);

		int tmpIn = data.value("timeBegin").toInt();
		QByteArray byteArray = doc.toJson(QJsonDocument::Compact);

		//接收缓冲区大小，按自己需求申请大小
		char* outBuffer = new char[10000];
		int outSize = 0;
		const char q[] = "\\\\.\\pipe\\ants_ivms_mainframe";
		char *word = new char[30];
		strcpy(word, q);
		DWORD result = ants_named_pipe_sendMsgToServer(word, byteArray.data(), byteArray.length(), outBuffer, 10000, &outSize);

		outBuffer[outSize] = '\0';
		if (_pLoading != NULL)
			_pLoading->setHidden();

		QJsonDocument jsonDocument = QJsonDocument::fromJson(outBuffer);
		QJsonObject jObj = jsonDocument.object();
		QJsonArray resultArray = jObj.value("result").toArray();
		for (int i = 0; i < resultArray.size(); i++)
		{
			int rows = ui->tableWidget_Linkage->rowCount();
			ui->tableWidget_Linkage->insertRow(rows);//添加到列表中
			QString strAlarmType_display;
			QJsonObject json = resultArray.at(i).toObject();
			int msgType = json.value("connectParseAlarmType").toInt();
			if (AlarmType_AlarmIn == msgType)
				strAlarmType_display = tr("Alarm in");
			else if (AlarmType_Motion == msgType)
				strAlarmType_display = tr("Motion detection");
			else if (AlarmType_Shelter == msgType)
				strAlarmType_display = tr("Hide alarm");
			else if (AlarmType_VideoLoss == msgType)
				strAlarmType_display = tr("Video lost");
			else if (AlarmType_Count == msgType)
				strAlarmType_display = tr("Counting alarm");
			else if (AlarmType_Area == msgType)
				strAlarmType_display = tr("Area alarm");
			else if (AlarmType_Object == msgType)
				strAlarmType_display = tr("Object detection alarm");
			else if (AlarmType_Wire == msgType)
				strAlarmType_display = tr("Cross line alarm");
			// 		else if (AlarmType_Person == msgType)
			// 			strAlarmType_display = tr("Human detection");
			QString strAlarmSource;
			if (msgType == AlarmType_AlarmIn)
			{
				QModelIndex index = CMSTreeView::getModelIndexByDevSNandAlarmInNo((json.value("serialNum").toString()), json.value("paramInt").toInt());
				if (index == QModelIndex())
				{
				}
				//return;
				strAlarmSource = "12345";
			}
			else
			{
				QModelIndex index = CMSTreeView::getModelIndexByDevSNandChNo((json.value("serialNum").toString()), json.value("paramInt").toInt());
				if (index == QModelIndex())
				{
				}
				//return;
				strAlarmSource = "54321";
			}

			QTableWidgetItem *pItem = new QTableWidgetItem(QString(json.value("ruleName").toString()));

			//设置设备标识
			pItem->setData(Qt::UserRole, QVariant::fromValue<int>(1));

			ui->tableWidget_Linkage->setItem(i, 0, pItem);//规则名称


			ui->tableWidget_Linkage->setItem(i, 1, new QTableWidgetItem(strAlarmType_display));//告警类型
			ui->tableWidget_Linkage->setItem(i, 2, new QTableWidgetItem(strAlarmSource));//告警源
			ui->tableWidget_Linkage->setItem(i, 3, new QTableWidgetItem(QString(json.value("remarks").toString())));//备注
			EnabledControl *pcb = new EnabledControl();
			bool check = json.value("isEnabled").toBool();
			if (check == 1) {
				pcb->ui->checkBox->setCheckState(Qt::Checked);

			}
			else {
				pcb->ui->checkBox->setCheckState(Qt::Unchecked);
			}
			ui->tableWidget_Linkage->setCellWidget(i, 4, pcb);

			TvwallCtrl *pTvwallCtrl = new TvwallCtrl();
			pTvwallCtrl->ui->btnEnable->setVisible(false);
			pTvwallCtrl->ui->btnGroup->setVisible(false);
			pTvwallCtrl->setFixedWidth(230);
			ui->tableWidget_Linkage->setCellWidget(i, 5, pTvwallCtrl);

			connect(pcb->ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(OnStateChanged(int)));
			connect(pTvwallCtrl->ui->btnDelete, SIGNAL(clicked()), this, SLOT(OnDeleteRule()));
			connect(pTvwallCtrl->ui->btnModify, SIGNAL(clicked()), this, SLOT(OnUpdateRule()));
		}
	}

	{
		//获取门禁告警信息
	}
}
//设置列宽,并是列根据界面大小自动变更
void AlarmCfg::resizeEvent(QResizeEvent *e)
{
	int tableWidth = ui->tableWidget_Linkage->width();
	if (tableWidth == 100)
		tableWidth = 1021;
	ui->tableWidget_Linkage->setColumnWidth(5, 250);
	ui->tableWidget_Linkage->setColumnWidth(4, 100);
	int width = tableWidth - 350;
	ui->tableWidget_Linkage->setColumnWidth(0, width * 20 / 100);
	ui->tableWidget_Linkage->setColumnWidth(1, width * 15 / 100);
	ui->tableWidget_Linkage->setColumnWidth(2, width * 35 / 100);
	ui->tableWidget_Linkage->setColumnWidth(3, width * 30 / 100);

	int m_iRowSum = (ui->tableWidget_Linkage->height() - 40) / ROW_HEIGHT;
	if (m_iRowSum == 0)
		m_iRowSum = 22;
	ui->tableWidget_Linkage->setRowCount(m_iRowSum);
}