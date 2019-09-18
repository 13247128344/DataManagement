#include "addlinkagerule.h"
#include "ui_addlinkagerule.h"
#include "ui_addivmsarae.h"
#include "QMap"
#include "qfile.h"
#include "QMessageBox"
#include "alarmcfg.h"
#include <QMouseEvent>
#include "linkageprevrec.h"
#include "linkageptz.h"
#include "linkagetvwall.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include "PipedServerApi.h"
#include "./include/ivms_public.h"
#include "./include/CMSTreeView.h"

UserType _iUserType;
bool _isShowMap = true;
bool _isShowDecoder = true;
bool _isShowAlarm = true;
bool _isShowIntelligent = true;

AddLinkageRule::AddLinkageRule(IVMS_CONNECT_PARSE_LinkageRuleParam ruleParam, QWidget *parent)
    : QDialog(parent)
    ,ui(new Ui::AddLinkageRule)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("./Resources/logo_1.png"));
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint
        | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint
        | Qt::WindowMaximizeButtonHint);
    connect(ui->btn_minimum, SIGNAL(clicked()), this, SLOT(ShowMini()));
    connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(FrmClose()));
    ui->btn_minimum->setCursor(Qt::PointingHandCursor);
    ui->btn_close->setCursor(Qt::PointingHandCursor);
    ui->btnSelAlarmSource->setCursor(Qt::PointingHandCursor);
    ui->btnOK->setCursor(Qt::PointingHandCursor);
    ui->btnCancel->setCursor(Qt::PointingHandCursor);
	//报警源
    connect(ui->btnSelAlarmSource, SIGNAL(clicked()), this, SLOT(btnSelAlarmSource_clicked()));//选择报警源
	m_ivmsDeviceTree_AlarmIn = new CMSTreeView(this, CMSTreeView::PLAYBACK, CMSTreeView::RADIO, CMSTreeView::ORIGIN, CMSTreeView::CH);
	m_ivmsDeviceTree_AlarmIn->expandAll();
	m_ivmsDeviceTree_AlarmIn->setHeaderHidden(true);
	m_ivmsDeviceTree_AlarmIn->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
	m_ivmsDeviceTree_AlarmIn->hide();

	//报警源--视频丢失,移动侦测,遮盖
	m_pDeviceTree_Other = new CMSTreeView(this, CMSTreeView::PLAYBACK, CMSTreeView::RADIO, CMSTreeView::ORIGIN, CMSTreeView::CH);
	m_pDeviceTree_Other->expandAll();
	m_pDeviceTree_Other->setHeaderHidden(true);
	m_pDeviceTree_Other->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
	m_pDeviceTree_Other->hide();
	m_pCurTree = m_pDeviceTree_Other;
	m_pAddIVMSArea = new AddIVMSArae(this);
	m_pAddIVMSArea->m_pCMSTreeView = m_pDeviceTree_Other;
	m_pAddIVMSArea->m_pAddLinkageRule = this;
	m_pAddIVMSArea->ui->verticalLayout_2->addWidget(m_pDeviceTree_Other);
	m_pAddIVMSArea->ui->verticalLayout_2->addWidget(m_ivmsDeviceTree_AlarmIn);
	m_pAddIVMSArea->hide();

	ui->textEdit_LinkagePara->setReadOnly(true);
	ui->cbAlarmType->addItem(tr("Alarm In"), AlarmType_AlarmIn);
	ui->cbAlarmType->addItem(tr("Motion detection"), AlarmType_Motion);
	ui->cbAlarmType->addItem(tr("Hide alarm"), AlarmType_Shelter);
	ui->cbAlarmType->addItem(tr("Video Loss"), AlarmType_VideoLoss);
	//ui->cbAlarmType->addItem(tr("Human detection"), AlarmType_Person);
#ifndef _SVIEW_
	ui->cbAlarmType->addItem(tr("Area alarm"), AlarmType_Area);
	ui->cbAlarmType->addItem(tr("Object detection alarm"), AlarmType_Object);
	ui->cbAlarmType->addItem(tr("Cross line alarm"), AlarmType_Wire);
	ui->cbAlarmType->addItem(tr("Counting alarm"), AlarmType_Count);
#endif // !_SVIEW_

	if (!_isShowDecoder)
	{
		ui->cbTVWall->hide();
	}
	if (!_isShowMap)
	{
		ui->cbMap->hide();
	}
	if (_iUserType == ivms_UserType_Guest)
	{
		ui->cbPTZ->setVisible(false);
		ui->cbTVWall->setVisible(false);
	}

	if (QString(ruleParam.ruleName) != "")
	{
		m_pRuleParam = ruleParam;
// 		ui->rbAlarmInput->setEnabled(false);
// 		ui->rbMotion->setEnabled(false);
// 		ui->rbVideoCover->setEnabled(false);
// 		ui->rbVideoLoss->setEnabled(false);
		ui->btnSelAlarmSource->setEnabled(false);
		ui->lineEdit_ruleName->setReadOnly(true);
		ui->lineEdit_alarmSource->setReadOnly(true);
		getUpdateSources();
	}

	connect(ui->cbMap, SIGNAL(stateChanged(int)), this, SLOT(OnCbMapStateChanged(int)));//地图
	connect(ui->cbTVWall, SIGNAL(stateChanged(int)), this, SLOT(OnCbTVWallStateChanged(int)));//电视墙
	connect(ui->cbPreview, SIGNAL(stateChanged(int)), this, SLOT(OnCbPreviewStateChanged(int)));//弹图像
	connect(ui->cbRecord, SIGNAL(stateChanged(int)), this, SLOT(OnCbRecordStateChanged(int)));//录像
	connect(ui->cbCapture, SIGNAL(stateChanged(int)), this, SLOT(OnCbCaptureStateChanged(int)));//抓图
	connect(ui->cbPTZ, SIGNAL(stateChanged(int)), this, SLOT(OnCbPTZStateChanged(int)));//云台
	connect(ui->cbAlarmType, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
	connect(ui->btnOK, SIGNAL(clicked()), this, SLOT(btnSave_clicked()));
	connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(btnCancel_clicked()));//关闭窗口
	dragPosition = QPoint(-1, -1);
}


AddLinkageRule::~AddLinkageRule()
{
    delete ui;
}

//新添加设备树的时候过滤告警输入节点
void AddLinkageRule::onTreeChanged(TreeChangeType type, CMS_CONNECT_PARSE_Node*)
{
	if (type == CT_AddDevice)
	{
		m_pCurTree->update();
		m_pDeviceTree_Other->update();
		m_ivmsDeviceTree_AlarmIn->update();
	}
}

//隐藏设备树
void AddLinkageRule::onCurrentIndexChanged(int index)
{
	m_pAddIVMSArea->hide();
}

//初始化要修改的数据
void AddLinkageRule::getUpdateSources()
{
	QString strAlarmSource;
	if (m_pRuleParam.connectParseAlarmType == AlarmType_AlarmIn)
	{
		QModelIndex index = CMSTreeView::getModelIndexByDevSNandAlarmInNo(m_pRuleParam.serialNum, m_pRuleParam.paramInt);
		if (index == QModelIndex())
		{
		}
			//return;
		//CMS_CONNECT_PARSE_AlarmInNode *node = (CMS_CONNECT_PARSE_AlarmInNode *)CMSTreeView::getNodebyModelIndex(index);
		//strAlarmSource = "DEVICES-" + QString(node->parent->cNodeName) + tr("-") + QString(node->cNodeName);
	}
	else
	{
		QModelIndex index = CMSTreeView::getModelIndexByDevSNandChNo(m_pRuleParam.serialNum, m_pRuleParam.paramInt);
		if (index == QModelIndex())
		{ }
			//return;
		//CMS_CONNECT_PARSE_ChannelNode *node = (CMS_CONNECT_PARSE_ChannelNode *)CMSTreeView::getNodebyModelIndex(index);
		//strAlarmSource = "DEVICES-" + QString(node->parent->cNodeName) + tr("-") + QString(node->cNodeName);
	}
	ui->lineEdit_ruleName->setText(QString(m_pRuleParam.ruleName));
	ui->lineEdit_alarmSource->setText(strAlarmSource);
	ui->textEdit_remark->setText(QString(m_pRuleParam.remarks));
	ui->cbAlarmType->setCurrentText(m_mapAlarmType.value((CMS_CONNECT_PARSE_AlarmType)m_pRuleParam.connectParseAlarmType));

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
	data.insert("ruleName", m_pRuleParam.ruleName);


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
	QJsonArray resultJsonArray = jObj.value("result").toArray();
	QJsonObject resultJson = resultJsonArray.at(0).toObject();
	int ruleActionCount = resultJson.value("paramCount").toInt();

	if (ruleActionCount > 0)
	{
		for (int i = 0; i < ruleActionCount; i++)
		{
			int actiontype = resultJson.value("connectParseLinkageActionType").toInt();
			if (actiontype == ivms_LinkageActionType_Map)
				ui->cbMap->setChecked(true);
			else if (actiontype == ivms_LinkageActionType_Wall)
				ui->cbTVWall->setChecked(true);
			else if (actiontype == ivms_LinkageActionType_PopImage)
				ui->cbPreview->setChecked(true);
			else if (actiontype == ivms_LinkageActionType_Record)
				ui->cbRecord->setChecked(true);
			else if (actiontype == ivms_LinkageActionType_Capture)
				ui->cbCapture->setChecked(true);
			else if (actiontype == ivms_LinkageActionType_PTZ)
				ui->cbPTZ->setChecked(true);
			for (int j = 0; j < ruleActionCount; j++)
			{
				QJsonArray actionAyyay = resultJson.value("linkageActionParam").toArray();
				QJsonObject actionParam = actionAyyay.at(j).toObject();
				AddLinkageRule::ChInfo info;//通道信息
				info.strDeviceNumber = actionParam.value("deviceSerialNum").toString();
				info.iChannel = actionParam.value("channelNum").toInt();//通道号
				if (actiontype == ivms_LinkageActionType_Wall)
				{
					if (QString(actionParam.value("decoderSerialNum").toString()) == "")
					{
						info.strDecoderSerial = "";
						info.iOutputNo = 0;
					}
					else
					{
						info.strDecoderSerial = QString(actionParam.value("decoderSerialNum").toString());//通道ID
						info.iOutputNo = actionParam.value("outputNo").toInt();
					}
					linkage_TVWall.channelList.append(info);
					linkage_TVWall.iStopMode = resultJson.value("stopSec").toInt();
				}
				else if (actiontype == ivms_LinkageActionType_PTZ)
				{
					info.ptzType = (LinkagePtzType)actionParam.value("connectParseLinkagePtzType").toInt();
					info.ptzIndex = actionParam.value("ptzIndex").toInt();
					linkage_PTZ.channelList.append(info);
				}
				else if (actiontype == ivms_LinkageActionType_Map)
				{
					linkage_Map.channelList.append(info);
					linkage_Map.iStopMode = resultJson.value("stopSec").toInt();
				}
				else if (actiontype == ivms_LinkageActionType_Capture)
				{
					linkage_Capture.channelList.append(info);
					linkage_Capture.iStopMode = resultJson.value("stopSec").toInt();
				}
				else if (actiontype == ivms_LinkageActionType_Record)
				{
					linkage_Record.channelList.append(info);
					linkage_Record.iStopMode = resultJson.value("stopSec").toInt();
				}
				else if (actiontype == ivms_LinkageActionType_PopImage)
				{
					linkage_Prev.channelList.append(info);
					linkage_Prev.iStopMode = resultJson.value("stopSec").toInt();
				}
			}
		}
		delete[] outBuffer;
		outBuffer = NULL;
	}
	refresh_ParaEdit();
}

//选择不同报警类型的报警源
void AddLinkageRule::btnSelAlarmSource_clicked()
{
	if (m_pAddIVMSArea->isHidden())
	{
		if (AlarmType_AlarmIn == ui->cbAlarmType->currentData().toInt())//报警输入类型
		{
			m_pCurTree = m_ivmsDeviceTree_AlarmIn;
		}
		else
		{
			m_pCurTree = m_pDeviceTree_Other;
		}
		QPoint pointBtn = ui->btnSelAlarmSource->pos();
		pointBtn.ry() = pointBtn.ry() + ui->btnSelAlarmSource->height() * 2 + 10;
		m_pCurTree->setMaximumSize(m_pCurTree->width(), m_pCurTree->height());
		QPoint point = mapToGlobal(pointBtn);
		m_pAddIVMSArea->m_pCMSTreeView->hide();
		m_pAddIVMSArea->m_pCMSTreeView = m_pCurTree;
		m_pCurTree->show();
		m_pAddIVMSArea->show();
		m_pAddIVMSArea->raise();
		m_pAddIVMSArea->setGeometry(point.x(), point.y(), m_pCurTree->width(), m_pCurTree->height() + 35);
	}
	else
	{
		m_pAddIVMSArea->hide();
	}
}
//保存报警联动
void AddLinkageRule::btnSave_clicked()
{
	QJsonDocument doc;

	QJsonObject obj;
	obj.insert("msgType", "1");
	obj.insert("from", "ivms_AlarmLog");
	obj.insert("target", "ivms_serverMain");
	QJsonObject dataObj;
	dataObj.insert("topic", "IVMS/LinkageManagement");
	dataObj.insert("cmd", "/IVMS/LinkageManagement/v1/linkage/rule/set");
	dataObj.insert("token", "121312312");
	dataObj.insert("connectTime", 12);

	QJsonObject data;
	QJsonObject linkageAction;
	QJsonObject linkageRule;
	QJsonObject linkageActionParam;

	if (ui->lineEdit_ruleName->text().trimmed() == "")//报警规则名称不能为空
	{
		//insertEvent(tr("Fill in rule name"));
		QMessageBox::information(NULL, "Title", "Fill in rule name", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}
// 	if (ui->lineEdit_alarmSource->text().trimmed() == "")
// 	{
// 		//insertEvent(tr("select an alarm source"));//报警源不能为空
// 		QMessageBox::information(NULL, "Title", "select an alarm source", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
// 		return;
// 	}
	//必须选择一个报警动作
	if (
		Qt::Unchecked == ui->cbMap->checkState() && Qt::Unchecked == ui->cbTVWall->checkState() &&
		Qt::Unchecked == ui->cbCapture->checkState() && Qt::Unchecked == ui->cbPreview->checkState()
		&& Qt::Unchecked == ui->cbPTZ->checkState() && Qt::Unchecked == ui->cbRecord->checkState())
	{
		//insertEvent(tr("set Linkage actions"));
		QMessageBox::information(NULL, "Title", "set Linkage actions", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}

	IVMS_CONNECT_PARSE_LinkageRuleParam rule;
	rule.ruleName = ui->lineEdit_ruleName->text().trimmed();//告警规则名称
	rule.remarks = ui->textEdit_remark->toPlainText();//备注
	rule.connectParseAlarmType = ui->cbAlarmType->currentData().toInt();
	//同名同源处理
// 	if (!ui->lineEdit_ruleName->isReadOnly())
// 	{
// 		for (int i = 0; i < _iRuleCount; i++)
// 		{
// 			if (ruleName == QString(item.cRuleName))
// 			{
// 				insertEvent(tr("There is the same alarm rule name, please re-enter!"));
// 				return;
// 			}
// 			if (QString(m_pRuleParam.cSerialNum) == QString(item.cSerialNum) && m_pRuleParam.iParam == item.iParam && alarmType == item.eAlarmType)
// 			{
// 				insertEvent(tr("With the same alarm source, please re-enter! "));
// 				return;
// 			}
// 		}
// 	}
	rule.isEnabled = true;
	rule.paramInt = 123;
	rule.serialNum = "222";
	linkageRule.insert("ruleName", rule.ruleName);
	linkageRule.insert("remarks", rule.remarks);
	linkageRule.insert("serialNum", rule.serialNum);
	linkageRule.insert("paramInt", rule.paramInt);
	linkageRule.insert("connectParseAlarmType", rule.connectParseAlarmType);
	linkageRule.insert("isEnabled", rule.isEnabled);
	int actionCount = 0;

	//if (linkage_Map.channelList.size() > 0)//包含地图动作
	//{
		linkageAction.insert("connectParseLinkageActionType", 6);
		int iParamCount = linkage_Map.channelList.size();
		linkageAction.insert("paramCount", iParamCount);

		linkageActionParam.insert("deviceSerialNum", "1122");
		linkageActionParam.insert("channelNum",123);
		for (int i = 0; i < linkage_Map.channelList.size(); i++)
		{
			QString cDeviceSerial = linkage_Map.channelList[0].strDeviceNumber.toUtf8().data();
			linkageActionParam.insert("deviceSerialNum", cDeviceSerial);
			int iChannel = linkage_Map.channelList[0].iChannel;
			linkageActionParam.insert("channelNum", iChannel);
		}
		int iStopSec = linkage_Map.iStopMode;
		linkageAction.insert("stopSec", iStopSec);
		actionCount++;
	//}
	if (linkage_TVWall.channelList.size() > 0)//电视墙
	{
		linkageAction.insert("connectParseLinkageActionType", 6);
		int iParamCount = linkage_TVWall.channelList.size();
		for (int i = 0; i < linkage_TVWall.channelList.size(); i++)
		{
			QString cDecoderSerial = linkage_TVWall.channelList[i].strDecoderSerial.toUtf8().data();
			linkageActionParam.insert("decoderSerialNum", cDecoderSerial);
			int iChannel = linkage_TVWall.channelList[i].iChannel;
			linkageActionParam.insert("channelNum", iChannel);
			QString cDeviceSerial = linkage_TVWall.channelList[i].strDeviceNumber.toUtf8().data();
			linkageActionParam.insert("deviceSerialNum", cDeviceSerial);
		}
		int iStopSec = linkage_TVWall.iStopMode;
		linkageAction.insert("stopSec", iStopSec);
		actionCount++;
	}
	if (linkage_Prev.channelList.size() > 0)//预览
	{
		linkageAction.insert("connectParseLinkageActionType", 3);
		int iParamCount = linkage_Prev.channelList.size();
		for (int i = 0; i < linkage_Prev.channelList.size(); i++)
		{
			QString cDeviceSerial = linkage_Prev.channelList[i].strDeviceNumber.toUtf8().data();
			linkageActionParam.insert("deviceSerialNum", cDeviceSerial);
			int	iChannel = linkage_Prev.channelList[i].iChannel;
			linkageActionParam.insert("channelNum", iChannel);
		}
		int iStopSec = linkage_Prev.iStopMode;
		linkageAction.insert("stopSec", iStopSec);
		actionCount++;
	}
	if (linkage_Record.channelList.size() > 0)//录像
	{
		linkageAction.insert("connectParseLinkageActionType", 4);
		int iParamCount = linkage_Record.channelList.size();
		for (int i = 0; i < linkage_Record.channelList.size(); i++)
		{
			QString cDeviceSerial = linkage_Record.channelList[i].strDeviceNumber.toUtf8().data();
			linkageActionParam.insert("deviceSerialNum", cDeviceSerial);
			int	iChannel = linkage_Record.channelList[i].iChannel;
			linkageActionParam.insert("channelNum", iChannel);
		}
		int iStopSec = linkage_Record.iStopMode;
		linkageAction.insert("stopSec", iStopSec);
		actionCount ++;
	}
	if (linkage_Capture.channelList.size() > 0)//抓图
	{
		linkageAction.insert("connectParseLinkageActionType", 5);
		int iParamCount = linkage_Capture.channelList.size();
		for (int i = 0; i < linkage_Capture.channelList.size(); i++)
		{
			QString cDeviceSerial = linkage_Capture.channelList[i].strDeviceNumber.toUtf8().data();
			linkageActionParam.insert("deviceSerialNum", cDeviceSerial);
			int	iChannel = linkage_Capture.channelList[i].iChannel;
			linkageActionParam.insert("channelNum", iChannel);
		}
		int iStopSec = linkage_Capture.iStopMode;
		linkageAction.insert("stopSec", iStopSec);
		actionCount++;
	}

	if (linkage_PTZ.channelList.size() > 0)//云台
	{
		linkageAction.insert("connectParseLinkageActionType", 2);
		int iParamCount = linkage_PTZ.channelList.size();
		for (int i = 0; i < linkage_PTZ.channelList.size(); i++)
		{
			QString cDeviceSerial = linkage_PTZ.channelList[i].strDeviceNumber.toUtf8().data();
			linkageActionParam.insert("", cDeviceSerial);
			int	iChannel = linkage_PTZ.channelList[i].iChannel;
			linkageActionParam.insert("channelNum", iChannel);
		//	int ePtzType = linkage_PTZ.channelList[i].ptzType;
		//	linkageActionParam.insert("connectParseLinkagePtzType", ePtzType);
			int iPtzIndex = linkage_PTZ.channelList[i].ptzIndex;
			linkageActionParam.insert("ptzIndex", iPtzIndex);
		}
		actionCount++;
	}

	QJsonArray array;
	array.append(linkageActionParam);
	linkageAction.insert("linkageActionParam", array);

	QJsonDocument tempDocss;
	tempDocss.setObject(linkageRule);
	data.insert("linkageRule", linkageRule);

	QJsonArray linkArray;
	linkArray.append(linkageAction);
	data.insert("linkageAction", linkArray);
	data.insert("actionCount", actionCount);

	QJsonDocument dataDocs;
	dataDocs.setObject(data);
	QByteArray tempData = dataDocs.toJson(QJsonDocument::Compact);
	dataObj.insert("data", QString(tempData));

	obj.insert("msgData", dataObj);
	doc.setObject(obj);
	QByteArray byteArray = doc.toJson(QJsonDocument::Compact);
	char* outBuffer = new char[1024];
	int outSize = 0;
	const char q[] = "\\\\.\\pipe\\ants_ivms_mainframe";
	char *word = new char[30];
	strcpy(word, q);
	DWORD result = ants_named_pipe_sendMsgToServer(word, byteArray.data(), byteArray.length(), outBuffer, 1024, &outSize);

	outBuffer[outSize] = '\0';

	delete[] outBuffer;
	outBuffer = NULL;
}

//点击窗口取消按钮
void AddLinkageRule::btnCancel_clicked()
{
	reject();
}
//地图
void AddLinkageRule::OnCbMapStateChanged(int state)
{
	if (Qt::Checked == state)//勾选时设置动作
	{
		QPoint pointCb = ui->cbMap->pos();
		pointCb.ry() = pointCb.ry() + ui->cbMap->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkagePrevRec dlg(point, ivms_LinkageActionType_Map, this);
		if (QDialog::Accepted == dlg.exec())//点击确定按钮
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//循环添加地图动作
				linkage_Map.channelList.append(dlg.LinkageInfo.channelList[i]);
			linkage_Map.iStopMode = dlg.LinkageInfo.iStopMode;//设置地图动作停止模式
		}
		else//点击取消按钮,设置地图选项未勾选
		{
			ui->cbMap->setCheckState(Qt::Unchecked);
			return;
		}
	}
	else//清除地图动作列表
	{
		linkage_Map.channelList.clear();
	}
	refresh_ParaEdit();
}
//电视墙
void AddLinkageRule::OnCbTVWallStateChanged(int state)
{
	if (Qt::Checked == state)//勾选时设置动作
	{
		QPoint pointCb = ui->cbTVWall->pos();
		pointCb.ry() = pointCb.ry() + ui->cbTVWall->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkageTVWall dlg(point, this);
		if (QDialog::Accepted == dlg.exec())//点击确定按钮
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//循环添加电视墙动作
			{
				linkage_TVWall.channelList.append(dlg.LinkageInfo.channelList[i]);
			}
			linkage_TVWall.iStopMode = dlg.LinkageInfo.iStopMode;//设置电视墙动作停止模式
		}
		else//点击取消按钮,设置电视墙选项未勾选
		{
			ui->cbTVWall->setCheckState(Qt::Unchecked);
			return;
		}
	}
	else//清除电视墙动作列表
	{
		linkage_TVWall.channelList.clear();
	}
	refresh_ParaEdit();
}
//预览
void AddLinkageRule::OnCbPreviewStateChanged(int state)
{
	if (Qt::Checked == state)
	{
		QPoint pointCb = ui->cbPreview->pos();
		pointCb.ry() = pointCb.ry() + ui->cbPreview->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkagePrevRec dlg(point, ivms_LinkageActionType_PopImage, this);
		if (QDialog::Accepted == dlg.exec())//点击确认按钮
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//循环获取抓图动作
				linkage_Prev.channelList.append(dlg.LinkageInfo.channelList[i]);
			linkage_Prev.iStopMode = dlg.LinkageInfo.iStopMode;
		}
		else//点击取消按钮,设置预览未勾选
		{
			ui->cbPreview->setCheckState(Qt::Unchecked);
			return;
		}
	}
	else
	{
		linkage_Prev.channelList.clear();
	}
	refresh_ParaEdit();
}
//录像
void AddLinkageRule::OnCbRecordStateChanged(int state)
{
	if (Qt::Checked == state)
	{
		QPoint pointCb = ui->cbRecord->pos();
		pointCb.ry() = pointCb.ry() + ui->cbRecord->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkagePrevRec dlg(point, ivms_LinkageActionType_Record, this);
		dlg.hideModeSet();//隐藏停止模式
		if (QDialog::Accepted == dlg.exec())//点击确认按钮
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//循环获取抓图动作
				linkage_Record.channelList.append(dlg.LinkageInfo.channelList[i]);
			linkage_Record.iStopMode = dlg.LinkageInfo.iStopMode;
		}
		else//点击取消按钮,设置录像未勾选
		{
			ui->cbRecord->setCheckState(Qt::Unchecked);
			return;
		}
	}
	else
	{
		linkage_Record.channelList.clear();
	}
	refresh_ParaEdit();
}
//抓图
void AddLinkageRule::OnCbCaptureStateChanged(int state)
{
	if (Qt::Checked == state)
	{
		QPoint pointCb = ui->cbCapture->pos();
		pointCb.ry() = pointCb.ry() + ui->cbCapture->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkagePrevRec dlg(point, ivms_LinkageActionType_Capture, this);
		dlg.hideModeSet();//隐藏停止模式
		if (QDialog::Accepted == dlg.exec())//点击确认按钮
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//循环获取抓图动作
				linkage_Capture.channelList.append(dlg.LinkageInfo.channelList[i]);
			linkage_Capture.iStopMode = dlg.LinkageInfo.iStopMode;
		}
		else//点击取消按钮,设置抓图未勾选
		{
			ui->cbCapture->setCheckState(Qt::Unchecked);
			return;
		}
	}
	else
	{
		linkage_Capture.channelList.clear();
	}
	refresh_ParaEdit();
}
//云台
void AddLinkageRule::OnCbPTZStateChanged(int state)
{
	if (Qt::Checked == state)//设置云台动作
	{
		QPoint pointCb = ui->cbPTZ->pos();
		pointCb.ry() = pointCb.ry() + ui->cbPTZ->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkagePTZ dlg(point, this);
		if (QDialog::Accepted == dlg.exec())//点击确认按钮
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//获取动作列表循环添加
			{
				linkage_PTZ.channelList.append(dlg.LinkageInfo.channelList[i]);
			}
		}
		else//点击取消按钮,设置云台未为勾选
		{
			ui->cbPTZ->setCheckState(Qt::Unchecked);
			return;
		}
	}
	else//清除云台动作列表
	{
		linkage_PTZ.channelList.clear();
	}
	refresh_ParaEdit();
}

void AddLinkageRule::refresh_ParaEdit()
{
	QString strInfo = "";

	if (linkage_Map.channelList.size() > 0)//地图动作
	{
		strInfo += ("----------------" + tr("MAP") + "----------------" + "\n");
		strInfo += ("  [" + tr("Channels") + "]\n");
		for (int i = 0; i < linkage_Map.channelList.size(); i++) {
			QModelIndex modelIndex = CMSTreeView::getModelIndexByDevSNandChNo(linkage_Map.channelList[i].strDeviceNumber, linkage_Map.channelList[i].iChannel);
			if (modelIndex == QModelIndex())
				continue;
			strInfo += ("    " + QString("(%1)").arg(i + 1) + QString(CMSTreeView::getNodebyModelIndex(modelIndex)->parent->cNodeName) + "_"
				+ QString(CMSTreeView::getNodebyModelIndex(modelIndex)->cNodeName) + "\n");
		}
		strInfo += ("  [" + tr("Stop Mode") + "]\n");
		if (-1 == linkage_Map.iStopMode)
			strInfo += ("    " + tr("auto stop") + "\n");
		else
			strInfo += ("    " + tr("stop after") + QString("%1").arg(linkage_Map.iStopMode) + tr("seconds") + "\n");
		strInfo += "\n";
	}

	if (linkage_TVWall.channelList.size() > 0)//电视墙
	{
		strInfo += ("----------------" + tr("TVWALL") + "----------------" + "\n");
		strInfo += ("  [" + tr("Channels") + "]\n");
		for (int i = 0; i < linkage_TVWall.channelList.size(); i++)
		{
			QModelIndex modelIndex = CMSTreeView::getModelIndexByDevSNandChNo(linkage_TVWall.channelList[i].strDeviceNumber, linkage_TVWall.channelList[i].iChannel);
			if (modelIndex == QModelIndex())
				continue;
			//xuwenjie
			//DecoderTreeNode *decodeNode = DecoderTreeView::GetNodeBySerialNum(linkage_TVWall.channelList[i].strDecoderSerial, 1);
			//strInfo += ("    " + QString("(%1)").arg(i + 1) + QString(CMSTreeView::getNodebyModelIndex(modelIndex)->parent->cNodeName) + "_"
				//+ QString(CMSTreeView::getNodebyModelIndex(modelIndex)->cNodeName) + "    " + (decodeNode == NULL ? "auto" : decodeNode->m_pParent->m_strName) + "\n");
		}
		strInfo += ("  [" + tr("Stop Mode") + "]\n");
		if (-1 == linkage_TVWall.iStopMode)
		{
			strInfo += ("    " + tr("auto stop") + "\n");
		}
		else
		{
			strInfo += ("    " + tr("stop after") + QString("%1").arg(linkage_TVWall.iStopMode) + tr("seconds") + "\n");
		}
		strInfo += "\n";
	}
	if (linkage_Prev.channelList.size() > 0)//预览
	{
		strInfo += ("----------------" + tr("POP IMAGE") + "----------------" + "\n");
		strInfo += ("  [" + tr("Channels") + "]\n");
		for (int i = 0; i < linkage_Prev.channelList.size(); i++) {
			QModelIndex modelIndex = CMSTreeView::getModelIndexByDevSNandChNo(linkage_Prev.channelList[i].strDeviceNumber, linkage_Prev.channelList[i].iChannel);
			if (modelIndex == QModelIndex())
				continue;
			strInfo += ("    " + QString("(%1)").arg(i + 1) + QString(CMSTreeView::getNodebyModelIndex(modelIndex)->parent->cNodeName) + "_"
				+ QString(CMSTreeView::getNodebyModelIndex(modelIndex)->cNodeName) + "\n");
		}
		strInfo += ("  [" + tr("Stop Mode") + "]\n");
		if (-1 == linkage_Prev.iStopMode)
			strInfo += ("    " + tr("auto stop") + "\n");
		else
			strInfo += ("    " + tr("stop after") + QString("%1").arg(linkage_Prev.iStopMode) + tr("seconds") + "\n");
		strInfo += "\n";
	}
	if (linkage_Record.channelList.size() > 0)//录像
	{
		strInfo += ("----------------" + tr("RECORD") + "----------------" + "\n");
		strInfo += ("  [" + tr("channels") + "]\n");
		for (int i = 0; i < linkage_Record.channelList.size(); i++) {
			QModelIndex modelIndex = CMSTreeView::getModelIndexByDevSNandChNo(linkage_Record.channelList[i].strDeviceNumber, linkage_Record.channelList[i].iChannel);
			if (modelIndex == QModelIndex())
				continue;
			strInfo += ("    " + QString("(%1)").arg(i + 1) + QString(CMSTreeView::getNodebyModelIndex(modelIndex)->parent->cNodeName) + "_"
				+ QString(CMSTreeView::getNodebyModelIndex(modelIndex)->cNodeName) + "\n");
		}
		strInfo += ("  [" + tr("Stop Mode") + "]\n");
		if (-1 == linkage_Record.iStopMode)
			strInfo += ("    " + tr("auto stop") + "\n");
		else
			strInfo += ("    " + tr("stop after") + QString("%1").arg(linkage_Record.iStopMode) + tr("seconds") + "\n");
		strInfo += "\n";
	}
	if (linkage_Capture.channelList.size() > 0)//抓图
	{
		strInfo += ("----------------" + tr("CAPTURE") + "----------------" + "\n");
		strInfo += ("  [" + tr("Channels") + "]\n");
		for (int i = 0; i < linkage_Capture.channelList.size(); i++) {
			QModelIndex modelIndex = CMSTreeView::getModelIndexByDevSNandChNo(linkage_Capture.channelList[i].strDeviceNumber, linkage_Capture.channelList[i].iChannel);
			if (modelIndex == QModelIndex())
				continue;
			strInfo += ("    " + QString("(%1)").arg(i + 1) + QString(CMSTreeView::getNodebyModelIndex(modelIndex)->parent->cNodeName) + "_"
				+ QString(CMSTreeView::getNodebyModelIndex(modelIndex)->cNodeName) + "\n");
		}
		strInfo += ("  [" + tr("Stop Mode") + "]\n");
		if (-1 == linkage_Capture.iStopMode)
			strInfo += ("    " + tr("auto stop") + "\n");
		else
			strInfo += ("    " + tr("stop after") + QString("%1").arg(linkage_Capture.iStopMode) + tr("seconds") + "\n");
		strInfo += "\n";
	}
	if (linkage_PTZ.channelList.size() > 0)//云台
	{
		strInfo += ("----------------" + tr("PTZ") + "----------------" + "\n");
		strInfo += ("  [" + tr("Channels") + "]\n");
		for (int i = 0; i < linkage_PTZ.channelList.size(); i++)
		{
			QModelIndex modelIndex = CMSTreeView::getModelIndexByDevSNandChNo(linkage_PTZ.channelList[i].strDeviceNumber, linkage_PTZ.channelList[i].iChannel);
			if (modelIndex == QModelIndex())
				continue;
			strInfo += ("    " + QString("(%1)").arg(i + 1) + QString(CMSTreeView::getNodebyModelIndex(modelIndex)->parent->cNodeName) + "_"
				+ QString(CMSTreeView::getNodebyModelIndex(modelIndex)->cNodeName) + "    ");
			if (LinkagePtzType_GotoPreset == linkage_PTZ.channelList[i].ptzType)
				strInfo += (tr("Goto Preset") + QString("%1").arg(linkage_PTZ.channelList[i].ptzIndex));
			else
				strInfo += (tr("Run Cruise") + QString("%1").arg(linkage_PTZ.channelList[i].ptzIndex));
			strInfo += "\n";
		}
	}
	ui->textEdit_LinkagePara->setText(strInfo);
}

//添加背景图片
void AddLinkageRule::resizeEvent(QResizeEvent *e)
{
	ui->widget_2->setAutoFillBackground(true);
	QPixmap *mBackPic1 = new QPixmap("./Resources/top.png");
	QPalette palette1;
	palette1.setBrush(QPalette::Background, QBrush((mBackPic1->scaled(ui->widget_2->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))));
	ui->widget_2->setPalette(palette1);

	ui->widget->setAutoFillBackground(true);
	QPixmap *mBackPic2 = new QPixmap("./Resources/mid.png");
	QPalette palette2;
	palette2.setBrush(QPalette::Background, QBrush((mBackPic2->scaled(ui->widget->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))));
	ui->widget->setPalette(palette2);

	ui->widget_3->setAutoFillBackground(true);
	QPixmap *mBackPic3 = new QPixmap("./Resources/bottom.png");
	QPalette palette3;
	palette3.setBrush(QPalette::Background, QBrush((mBackPic3->scaled(ui->widget_3->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))));
	ui->widget_3->setPalette(palette3);
}
/************************************************************************/
/* 鼠标拖动窗口                                                         */
/************************************************************************/

//鼠标按下
void AddLinkageRule::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		dragPosition = e->globalPos() - frameGeometry().topLeft();
		e->accept();
	}
}
//鼠标释放
void AddLinkageRule::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragPosition = QPoint(-1, -1);
		event->accept();
	}
}
//鼠标拖动
void AddLinkageRule::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() &Qt::LeftButton)
	{
		if (dragPosition != QPoint(-1, -1))
			move(event->globalPos() - dragPosition);
		event->accept();
	}
}

//最小化
void AddLinkageRule::ShowMini()
{
	this->showMinimized();
}
//关闭
void AddLinkageRule::FrmClose()
{
	this->close();
}
