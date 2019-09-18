#include "alarm.h"
#include "ui_alarm.h"
#include <QTime>
#include <QDateTime>
#include <QDebug>
#include <qfile.h>
#include<QMessageBox>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include "alarmcfg.h"
#include "QMouseEvent"
#include "PipedServerApi.h"
#include "./include/ivms_public.h"
#define ROW_HEIGHT 30

#pragma comment(lib,"ants_ivms_pipeserver.lib")
Alarm* Alarm::stra_AlarmInfo;
Alarm* Alarm::getAlarmInfo(QWidget *parent)
{
	if (stra_AlarmInfo == NULL)
	{
		stra_AlarmInfo = new Alarm(parent);
	}
	return stra_AlarmInfo;
}

Alarm::Alarm(QWidget *parent)
    : QWidget(parent)
    , m_iAlarmLogSum(0)
    , m_iPage(0)
    , m_iPageCount(1)
    , m_bCondition(false)
    , m_bAlarmLog(true)
	, ui(new Ui::Alarm)
{
    ui->setupUi(this);

	initStyle();
    ui->tableWidget->setSortingEnabled(false);
    ui->tableWidget->setColumnCount(4);
    QStringList headerList;
    headerList<<tr("ALARM SOUCRES")<<tr("ALARM TYPE")<<tr("START TIME")<<tr("END TIME");
    ui->tableWidget->setHorizontalHeaderLabels(headerList);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使列完全填充并平分
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    ui->btnSearch->setCursor(Qt::PointingHandCursor);
    QDateTime curDateTime = QDateTime::currentDateTime();
    QDateTime dateTimeFrom(curDateTime.date(), QTime(0, 0, 0, 0));
    QDateTime dateTimeTo(curDateTime.date(), curDateTime.time());
    ui->dateTimeEditFrom->setDateTime(dateTimeFrom);
    ui->dateTimeEditTo->setDateTime(dateTimeTo);

    ui->comboBoxType->addItem(tr("All Type"));//所有类型
    ui->comboBoxType->addItem(tr("Motion detection"));//移动侦测
    ui->comboBoxType->addItem(tr("Video lost"));//视频丢失
    ui->comboBoxType->addItem(tr("Hide alarm"));//视频遮挡
    ui->comboBoxType->addItem(tr("Alarm in"));//告警输入

#ifndef _SVIEW_
    ui->comboBoxType->addItem(tr("Counting alarm"));//目标计数
    ui->comboBoxType->addItem(tr("Area alarm"));//区域报警
    ui->comboBoxType->addItem(tr("Object detection alarm"));//物品检测
    ui->comboBoxType->addItem(tr("Cross line alarm"));//跨线报警

#endif // _SVIEW_
    ui->comboBoxType->addItem(tr("Human detection"));//人形检测
    ui->btnFirst->setCursor(Qt::PointingHandCursor);
    ui->btnPrev->setCursor(Qt::PointingHandCursor);
    ui->btnNext->setCursor(Qt::PointingHandCursor);
    ui->btnLast->setCursor(Qt::PointingHandCursor);
    ui->lblPage->setText(QString("%1").arg(m_iAlarmLogSum) + QString(tr(" records")) + QString(" %2/%3").arg(m_iPage+1).arg(m_iPageCount) + QString(tr(" pages")));
    connect(ui->btnSearch,SIGNAL(clicked()),this,SLOT(getAlarmInfoByCondition()));//条件查询
    connect(ui->btnPrev,SIGNAL(clicked()),this,SLOT(getPrev()));//获取前一页数据
    connect(ui->btnFirst,SIGNAL(clicked()),this,SLOT(getFirst()));//获取首页数据
    connect(ui->btnLast,SIGNAL(clicked()),this,SLOT(getLast()));//获取尾页数据
    connect(ui->btnNext,SIGNAL(clicked()),this,SLOT(getNext()));//获取下一页数据
    connect(ui->btn_alarmlog, SIGNAL(clicked()), this, SLOT(onBtnAlarmLog()));
    connect(ui->btn_accesslog, SIGNAL(clicked()), this, SLOT(onBtnAccessLog()));

    ui->btn_accesslog->setCheckable(true);
    ui->btn_alarmlog->setCheckable(true);
    ui->btn_alarmlog->setChecked(true);
    ui->btn_accesslog->hide();
    ui->btn_alarmlog->hide();
	this->setWindowFlags(Qt::FramelessWindowHint);
}

Alarm::~Alarm()
{
	delete ui;
}

void Alarm::initStyle()
{
	QFile file("./ivms_Alarm.qss");

	if (!file.open(QFile::ReadOnly))
	{
		QMessageBox::information(NULL, "Title", "wrong", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}
	QString qss = QLatin1String(file.readAll());
	QString paletteColor = qss.mid(20, 7);
	qApp->setPalette(QPalette(QColor(paletteColor)));
	qApp->setStyleSheet(qss);
	file.close();
}

void Alarm::resizeEvent(QResizeEvent *e)
{
	int height = ui->tableWidget->height();
	m_iRowSum = (height - 38) / ROW_HEIGHT;
	if (m_iRowSum == 0)
		m_iRowSum = 20;
	ui->tableWidget->setRowCount(m_iRowSum);
	if (m_bAlarmLog == true)
	{
		getAlarmInfo();
	}
	else
	{
		getAccessInfo();
	}
	enabledBtn();
}

void Alarm::getAccessInfo()
{
	QJsonDocument doc;

	QJsonObject obj;
	obj.insert("msgType", "1");
	obj.insert("from", "ivms_Log");
	obj.insert("target", "ivms_serverMain");

	QJsonObject dataObj;
	dataObj.insert("topic", "IVMS/LoggerManagement");
	dataObj.insert("cmd", "/IVMS/LoggerManagement/v1/alarm/get");
	dataObj.insert("token", "121312312");
	dataObj.insert("connectTime", 12);

	QJsonObject data;
	data.insert("offset", 0);
	data.insert("timeBegin", 1514772610);
	data.insert("timeEnd", 1567999848);
	data.insert("flag", 15);
	data.insert("searchCount", 3);


	QJsonDocument tempDoc;
	tempDoc.setObject(data);

	QByteArray temp = tempDoc.toJson(QJsonDocument::Compact);

	dataObj.insert("data", QString(temp));
	obj.insert("msgData", dataObj);
	doc.setObject(obj);

	int tmpIn = data.value("timeBegin").toInt();
	QByteArray byteArray = doc.toJson(QJsonDocument::Compact);

	//接收缓冲区大小，按自己需求申请大小
	char* outBuffer = new char[1024];
	int outSize = 0;
	const char q[] = "\\\\.\\pipe\\ants_ivms_mainframe";
	char *word = new char[30];
	strcpy(word, q);
	DWORD result = ants_named_pipe_sendMsgToServer(word, byteArray.data(), byteArray.length(), outBuffer, 1024, &outSize);

	outBuffer[outSize] = '\0';

	QJsonDocument jsonDocument = QJsonDocument::fromJson(outBuffer);
	QJsonObject jObj = jsonDocument.object();
	QJsonArray resultArray = jObj.value("result").toArray();

	for (int i = 0; i < resultArray.size(); i++)
	{
		QString alarm_type;
		QJsonObject json = resultArray.at(i).toObject();
		int msgType = json.value("connectParseAlarmType").toInt();
		if (msgType == AccessAlarmType_OpenDoor)
			alarm_type = tr("Alarm in");//意外开门
		else if (msgType == AccessAlarmType_Tamper)
			alarm_type = tr("Motion detection");//防拆报警
		else if (msgType == AccessAlarmType_StressPwd)
			alarm_type = tr("Hide alarm");//胁迫密码
		else if (msgType == AccessAlarmType_StressFingerprint)
			alarm_type = tr("Cross line alarm");//胁迫指纹
		else if (msgType == AccessAlarmType_MagneticTimeOut)
			alarm_type = tr("Object detection alarm");//门磁超时

		QString alarmSource = json.value("serialNum").toString();

		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(alarmSource));//告警源（暂时直接用从服务器拿到的）
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(alarm_type));//告警类型
		ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QDateTime::fromTime_t(json.value("timeBegin").toInt()).toUTC().toString("yyyy-MM-dd hh:mm:ss")));//告警起始时间
		ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QDateTime::fromTime_t(json.value("timeEnd").toInt()).toUTC().toString("yyyy-MM-dd hh:mm:ss")));//告警结束时间
	}

	delete[] outBuffer;
	outBuffer = NULL;

	m_iPageCount = m_iAlarmLogSum / m_iRowSum;
	if (m_iAlarmLogSum % m_iRowSum > 0) {
		m_iPageCount++;
	}
	if (m_iPageCount == 0) {
		ui->lblPage->setText(QString("%1").arg(m_iAlarmLogSum) + tr("alarm logs,") +
			QString("%1/1").arg(m_iPage + 1) + tr("pages").arg(m_iAlarmLogSum));
	}
	else {
		ui->lblPage->setText(QString("%1").arg(m_iAlarmLogSum) + tr("alarm logs,") +
			QString("%1/%2").arg(m_iPage + 1).arg(m_iPageCount) + tr("pages").arg(m_iAlarmLogSum));
	}
}

void Alarm::getAlarmInfo()
{

	QJsonDocument doc;

	QJsonObject obj;
	obj.insert("msgType", "1");
	obj.insert("from", "ivms_Log");
	obj.insert("target", "ivms_serverMain");

	QJsonObject dataObj;
	dataObj.insert("topic", "IVMS/LoggerManagement");
	dataObj.insert("cmd", "/IVMS/LoggerManagement/v1/alarm/get");
	dataObj.insert("token", "121312312");
	dataObj.insert("connectTime", 12);

	QJsonObject data;
	data.insert("offset", 0);
	data.insert("timeBegin", 1514772610);
	data.insert("timeEnd", 1567999848);
	data.insert("flag", 15);
	data.insert("searchCount", 3);


	QJsonDocument tempDoc;
	tempDoc.setObject(data);

	QByteArray temp = tempDoc.toJson(QJsonDocument::Compact);

	dataObj.insert("data", QString(temp));
	obj.insert("msgData", dataObj);
	doc.setObject(obj);

	int tmpIn = data.value("timeBegin").toInt();
	QByteArray byteArray = doc.toJson(QJsonDocument::Compact);

	//接收缓冲区大小，按自己需求申请大小
	char* outBuffer = new char[1024];
	int outSize = 0;
	const char q[] = "\\\\.\\pipe\\ants_ivms_mainframe";
	char *word = new char[30];
	strcpy(word, q);
	DWORD result = ants_named_pipe_sendMsgToServer(word, byteArray.data(), byteArray.length(), outBuffer, 1024, &outSize);

	outBuffer[outSize] = '\0';

	QJsonDocument jsonDocument = QJsonDocument::fromJson(outBuffer);
	QJsonObject jObj = jsonDocument.object();
	QJsonArray resultArray = jObj.value("result").toArray();

	for (int i = 0; i < resultArray.size(); i++)
	{
		QString alarm_type;
		QJsonObject json = resultArray.at(i).toObject();
		int msgType = json.value("connectParseAlarmType").toInt();
		if (msgType == AlarmType_AlarmIn)
			alarm_type = tr("Alarm in");//告警输入
		else if (msgType == AlarmType_Motion)
			alarm_type = tr("Motion detection");//移动侦测
		else if (msgType == AlarmType_Shelter)
			alarm_type = tr("Hide alarm");//视频遮挡
		else if (msgType == AlarmType_VideoLoss)
			alarm_type = tr("Video lost");//视频丢失
		else if (msgType == AlarmType_Wire)
			alarm_type = tr("Cross line alarm");//跨线报警
		else if (msgType == AlarmType_Object)
			alarm_type = tr("Object detection alarm");//物品检测报警
		else if (msgType == AlarmType_Area)
			alarm_type = tr("Area alarm");//区域报警
		else if (msgType == AlarmType_Count)
			alarm_type = tr("Counting alarm");//计数报警
// 		else if (msgType == AlarmType_Person)
// 			alarm_type = tr("Human detection");//人形检测报警

		QString alarmSource = json.value("serialNum").toString();

		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(alarmSource));//告警源（暂时直接用从服务器拿到的）
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(alarm_type));//告警类型
		ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QDateTime::fromTime_t(json.value("timeBegin").toInt()).toUTC().toString("yyyy-MM-dd hh:mm:ss")));//告警起始时间
		ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QDateTime::fromTime_t(json.value("timeEnd").toInt()).toUTC().toString("yyyy-MM-dd hh:mm:ss")));//告警结束时间
	}

	delete[] outBuffer;
	outBuffer = NULL;

	m_iPageCount = m_iAlarmLogSum / m_iRowSum;
	if (m_iAlarmLogSum % m_iRowSum > 0) {
		m_iPageCount++;
	}
	if (m_iPageCount == 0) {
		ui->lblPage->setText(QString("%1").arg(m_iAlarmLogSum) + tr("alarm logs,") +
			QString("%1/1").arg(m_iPage + 1) + tr("pages").arg(m_iAlarmLogSum));
	}
	else {
		ui->lblPage->setText(QString("%1").arg(m_iAlarmLogSum) + tr("alarm logs,") +
			QString("%1/%2").arg(m_iPage + 1).arg(m_iPageCount) + tr("pages").arg(m_iAlarmLogSum));
	}
}

void Alarm::getAlarmInfoByCondition()
{
	if (m_bAlarmLog == true)
	{
		getAlarmInfo();
	}
	else
	{
		getAccessInfo();
	}
	enabledBtn();
}

void Alarm::getFirst()
{
	if (m_iPage == 0)
		return;
	m_iPage = 0;
	enabledBtn();
	if (m_bAlarmLog == true)
	{
		getAlarmInfo();
	}
	else
	{
		getAccessInfo();
	}
}
//获取上一页数据
void Alarm::getPrev()
{
	if (m_iPage == 0)
		return;
	m_iPage--;
	enabledBtn();
	if (m_bAlarmLog == true)
	{
		getAlarmInfo();
	}
	else
	{
		getAccessInfo();
	}
}
//获取下一页数据
void Alarm::getNext()
{
	if (m_iPage == m_iPageCount - 1)
		return;
	m_iPage++;
	enabledBtn();
	if (m_bAlarmLog == true)
	{
		getAlarmInfo();
	}
	else
	{
		getAccessInfo();
	}
}
//获取最后页数据
void Alarm::getLast()
{
	m_iPage = m_iPageCount - 1;
	enabledBtn();
	if (m_bAlarmLog == true)
	{
		getAlarmInfo();
	}
	else
	{
		getAccessInfo();
	}
}

void Alarm::enabledBtn()
{
	if (m_iPage == 0) {
		ui->btnFirst->setEnabled(false);
		ui->btnPrev->setEnabled(false);
	}
	else {
		ui->btnFirst->setEnabled(true);
		ui->btnPrev->setEnabled(true);
	}
	if ((m_iPage == m_iPageCount - 1 && m_iPageCount != 0) || m_iPageCount == 0 || m_iPageCount == 1) {
		ui->btnLast->setEnabled(false);
		ui->btnNext->setEnabled(false);
	}
	else {
		ui->btnLast->setEnabled(true);
		ui->btnNext->setEnabled(true);
	}
}

void Alarm::onBtnAccessLog()
{
	m_bAlarmLog = false;

	ui->btn_accesslog->setChecked(true);
	ui->btn_alarmlog->setChecked(false);

	ui->comboBoxType->clear();

	QStringList strList;

	strList << tr("All") << tr("Open Door") << tr("Tamper") << tr("Stress Password") << tr("Stress Finger print") << tr("Magnetic Time Out");

	ui->comboBoxType->addItems(strList);
}

//点击告警按钮
void Alarm::onBtnAlarmLog()
{
	m_bAlarmLog = true;

	ui->btn_accesslog->setChecked(false);
	ui->btn_alarmlog->setChecked(true);

	ui->comboBoxType->clear();

	ui->comboBoxType->addItem(tr("All Type"));//所有类型
	ui->comboBoxType->addItem(tr("Motion detection"));//移动侦测
	ui->comboBoxType->addItem(tr("Video lost"));//视频丢失
	ui->comboBoxType->addItem(tr("Hide alarm"));//视频遮挡
	ui->comboBoxType->addItem(tr("Alarm in"));//告警输入
#ifndef _SVIEW_
	ui->comboBoxType->addItem(tr("Counting alarm"));//计数报警
	ui->comboBoxType->addItem(tr("Area alarm"));//区域报警
	ui->comboBoxType->addItem(tr("Object detection alarm"));//物品检测
	ui->comboBoxType->addItem(tr("Cross line alarm"));//跨线报警
#endif // !_SVIEW_
}
void Alarm::on_pushButton_clicked()
{
	AlarmCfg *w = new AlarmCfg();
	w->show();
}
