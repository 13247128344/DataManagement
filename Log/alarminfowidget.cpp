#include "alarminfowidget.h"
#include "ui_alarminfowidget.h"
#include <QDebug>
#include <QScrollBar>
#include "QDateTime"
#include "qfile.h"
#include "QTimer"
#include "QSettings"
#include "QMessageBox"

//获取程序安装路径
QString GetAppPath()
{
	QString path = QCoreApplication::applicationDirPath(); //获取应用程序路径
	return path;
}

AlarmInfoWidget::AlarmInfoWidget(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::AlarmInfoWidget)
{
    ui->setupUi(this);
	
	initStyle();
	m_bIsStay = false;
	ui->btn_hide->setCheckable(true);
	ui->btn_hide->setChecked(false);
	ui->btn_stay->setCheckable(true);
	ui->btn_stay->setChecked(false);
	ui->stackedWidget->setFixedHeight(125);
	ui->btn_alarm->setCheckable(true);
	ui->btn_event->setCheckable(true);
	ui->btn_open_sound->setCheckable(true);
	ui->btn_open_sound->setChecked(false);
	on_btn_alarm_clicked();

//	qRegisterMetaType<CMS_CONNECT_PARSE_Alarm_Notice>("CMS_CONNECT_PARSE_Alarm_Notice");
//	qRegisterMetaType<CMS_CONNECT_PARSE_Access_Alarm_Notice>("CMS_CONNECT_PARSE_Access_Alarm_Notice");

	ui->table_alarm->setColumnCount(6);
	QStringList alarmHeader;
	alarmHeader << tr("Alarm Time") << tr("Alarm Type") << tr("Device Serial") << tr("Param") << tr("Alarm Source") << tr("Alarm State");
	ui->table_alarm->setHorizontalHeaderLabels(alarmHeader);
	ui->table_alarm->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	ui->table_alarm->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	ui->table_alarm->horizontalHeader()->setSortIndicatorShown(false);
	ui->table_alarm->setFrameShape(QFrame::NoFrame); //设置无边框
	ui->table_alarm->verticalHeader()->setVisible(false); //设置垂直头不可见
	ui->table_alarm->setSelectionMode(QAbstractItemView::SingleSelection); //单选
	ui->table_alarm->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行
	ui->table_alarm->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
	ui->table_alarm->horizontalHeader()->resizeSection(0, 150); //设置表头第一列的宽度为150
	connect(ui->table_alarm, SIGNAL(itemSelectionChanged()), this, SLOT(onSelectEventRow()));
	connect(ui->table_alarm, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(onItemDoubleClicked(QTableWidgetItem *)));
	//connect(this, SIGNAL(sendAlarmEvent(CMS_CONNECT_PARSE_Alarm_Notice)), this, SLOT(onInsertAlarmEvent(CMS_CONNECT_PARSE_Alarm_Notice)));
	connect(this, SIGNAL(sendAccessEvent(CMS_CONNECT_PARSE_Access_Alarm_Notice)), this, SLOT(onInsertAccessEvent(CMS_CONNECT_PARSE_Access_Alarm_Notice)));
	ui->table_event->setColumnCount(2);
	QStringList eventHeader;
	eventHeader << tr("Time") << tr("Messages");
	ui->table_event->setHorizontalHeaderLabels(eventHeader);
	ui->table_event->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	ui->table_event->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	ui->table_event->horizontalHeader()->setSortIndicatorShown(false);
	ui->table_event->setFrameShape(QFrame::NoFrame); //设置无边框
	ui->table_event->verticalHeader()->setVisible(false); //设置垂直头不可见
	ui->table_event->setSelectionMode(QAbstractItemView::SingleSelection); //单选
	ui->table_event->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行
	ui->table_event->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
	ui->table_event->horizontalHeader()->resizeSection(0, 300); //设置表头第一列的宽度为300
	connect(ui->table_event, SIGNAL(itemSelectionChanged()), this, SLOT(onSelectEventRow()));
	QSettings settings(GetAppPath() + "/config.ini", QSettings::IniFormat);
	m_bOpenSound = settings.value("Sound/sound", 1).toInt() == 1 ? true : false;
	if (m_bOpenSound)
	{
		ui->btn_open_sound->setChecked(true);
	}
	else
	{
		ui->btn_open_sound->setChecked(false);
	}
	on_btn_open_sound_clicked();
	ui->btn_close_sound->hide();
	connect(this, SIGNAL(sendPlaySound(int)), this, SLOT(onOpenSound(int)));
	connect(this, SIGNAL(sendInsertEvent(QString)), this, SLOT(onInsertEvent(QString)));

	ui->btn_alarm_info->hide();

}


AlarmInfoWidget::~AlarmInfoWidget()
{
    delete ui;
}

void AlarmInfoWidget::initStyle()
{

	QFile file("./cmssurface.qss");

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

//隐私
void AlarmInfoWidget::on_btn_hide_clicked()
{
	if (0 == ui->stackedWidget->height())
	{
		ui->stackedWidget->setFixedHeight(125);
		ui->btn_hide->setChecked(false);
	}
	else
	{
		ui->stackedWidget->setFixedHeight(0);
		ui->btn_hide->setChecked(true);
	}
}

//告警
void AlarmInfoWidget::on_btn_alarm_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
	ui->btn_alarm->setChecked(true);
	ui->btn_event->setChecked(false);
}
//事件
void AlarmInfoWidget::on_btn_event_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
	ui->btn_alarm->setChecked(false);
	ui->btn_event->setChecked(true);
}
//固定按钮事件
void AlarmInfoWidget::on_btn_stay_clicked()
{
	if (m_bIsStay)
	{
		ui->btn_hide->setEnabled(true);
	}
	else
	{
		ui->btn_hide->setEnabled(false);
	}
	m_bIsStay = !m_bIsStay;
}
//重新布局事件列大小
void AlarmInfoWidget::resizeEvent(QResizeEvent *e)
{
	int tableWidth = this->width();
	int width = tableWidth - 317;
	ui->table_event->setColumnWidth(1, width);
	int alarmWidth = tableWidth - 150;
	ui->table_alarm->setColumnWidth(1, alarmWidth * 15 / 100);
	ui->table_alarm->setColumnWidth(2, alarmWidth * 25 / 100);
	ui->table_alarm->setColumnWidth(3, alarmWidth * 15 / 100);
	ui->table_alarm->setColumnWidth(4, alarmWidth * 30 / 100);
	ui->table_alarm->setColumnWidth(5, alarmWidth * 15 / 100);
}
//清除告警和事件信息
void AlarmInfoWidget::on_btn_clear_clicked()
{
	if (ui->stackedWidget->currentIndex() == 0)
		ui->table_alarm->clearContents();
	else
		ui->table_event->clearContents();
}

void AlarmInfoWidget::on_btn_alarm_info_clicked()
{

}

//关闭声音
void AlarmInfoWidget::on_btn_close_sound_clicked()
{
	ui->btn_open_sound->setEnabled(true);
	ui->btn_close_sound->setEnabled(false);

	m_bOpenSound = false;
	QSettings settings(GetAppPath() + "/config.ini", QSettings::IniFormat); // 当前目录的INI文件
																			//把登陆信息写入QSettings
	settings.beginGroup("Sound");
	settings.setValue("sound", 0);
	settings.endGroup();
}
//打开声音
void AlarmInfoWidget::on_btn_open_sound_clicked()
{
	if (ui->btn_open_sound->isChecked())
	{
		ui->btn_open_sound->setToolTip(tr("Close sound"));
	}
	else
	{
		ui->btn_open_sound->setToolTip(tr("Open sound"));
	}

	m_bOpenSound = ui->btn_open_sound->isChecked();

	QSettings settings(GetAppPath() + "/config.ini", QSettings::IniFormat); // 当前目录的INI文件
																			//把登陆信息写入QSettings
	settings.beginGroup("Sound");
	settings.setValue("sound", 1);
	settings.endGroup();
}
//将访问过的item字体设置为白色
void AlarmInfoWidget::onSelectEventRow()
{
#ifndef ZKTECO
	QList<QTableWidgetItem *> items_event = ui->table_event->selectedItems();
	if (items_event.count() >= 2)
	{
		items_event[0]->setTextColor(Qt::white);
		items_event[1]->setTextColor(Qt::white);
	}
	QList<QTableWidgetItem *> items_alarm = ui->table_alarm->selectedItems();
	if (items_alarm.count() >= 4)
	{
		items_alarm[0]->setTextColor(Qt::white);
		items_alarm[1]->setTextColor(Qt::white);
		items_alarm[2]->setTextColor(Qt::white);
		items_alarm[3]->setTextColor(Qt::white);
		items_alarm[4]->setTextColor(Qt::white);
		items_alarm[5]->setTextColor(Qt::white);
	}
#endif
}

void AlarmInfoWidget::insertEvent(QString eventInfo)
{
	emit sendInsertEvent(eventInfo);
}

void AlarmInfoWidget::onInsertEvent(QString eventInfo)
{
	ui->table_event->insertRow(0);
	QString datetime = QDateTime::currentDateTime().date().toString("yyyy-MM-dd") + QDateTime::currentDateTime().time().toString(" hh:mm:ss");
	ui->table_event->setItem(0, 0, new QTableWidgetItem(datetime));
	ui->table_event->setItem(0, 1, new QTableWidgetItem(eventInfo));
	if (ui->table_event->rowCount() > 100)
		ui->table_event->removeRow(100);
	ui->btn_event->click();
}

void AlarmInfoWidget::insertAccessEvent(CMS_CONNECT_PARSE_Access_Alarm_Notice sAccessInfo)
{
	emit sendAccessEvent(sAccessInfo);
}

void AlarmInfoWidget::onInsertAccessEvent(CMS_CONNECT_PARSE_Access_Alarm_Notice sAccessInfo)
{
	QString alarmtype;

	if (sAccessInfo.eAlarmType == AccessAlarmType_OpenDoor) {
		alarmtype = tr("Accident Open Door");
	}
	else if (sAccessInfo.eAlarmType == AccessAlarmType_Tamper) {
		alarmtype = tr("Tamper");
	}
	else if (sAccessInfo.eAlarmType == AccessAlarmType_StressPwd) {
		alarmtype = tr("Stress Password");
	}
	else if (sAccessInfo.eAlarmType == AccessAlarmType_StressFingerprint) {
		alarmtype = tr("Stress Finger Print");
	}
	else if (sAccessInfo.eAlarmType == AccessAlarmType_MagneticTimeOut) {
		alarmtype = tr("Magnetic Time Out");
	}
	else {
		//alarmtype=tr("Unknown type");
		return;
	}

	//暂时没有节点找
	ui->table_alarm->insertRow(0);
	ui->table_alarm->setItem(0, 0, new QTableWidgetItem(QDateTime::fromTime_t(sAccessInfo.timeUTC).toString("yyyy-MM-dd hh:mm:ss")));//告警时间
	ui->table_alarm->setItem(0, 1, new QTableWidgetItem(alarmtype));//告警类型
	ui->table_alarm->setItem(0, 2, new QTableWidgetItem(QString(sAccessInfo.cSerialNum)));//设备序列号
	ui->table_alarm->setItem(0, 3, new QTableWidgetItem(QString("%1").arg(sAccessInfo.iParam)));//参数
	ui->table_alarm->setItem(0, 4, new QTableWidgetItem(QString("Access") + "-" + QString(sAccessInfo.cSerialNum)));//告警源
	QString alarmState = sAccessInfo.isStoped == 0 ? tr("Start Alarm") : tr("Stop Alarm");
	ui->table_alarm->setItem(0, 5, new QTableWidgetItem(alarmState));//告警状态

}

void AlarmInfoWidget::insertAlarmEvent(CMS_CONNECT_PARSE_Alarm_Notice sAlarmInfo)
{
	emit sendAlarmEvent(sAlarmInfo);
}

//添加告警信息
	void AlarmInfoWidget::onInsertAlarmEvent(CMS_CONNECT_PARSE_Alarm_Notice sAlarmInfo) {
	
	
		QString alarmtype;
	
		if (sAlarmInfo.eAlarmType == AlarmType_Motion) {
			alarmtype = tr("Motion detection");
		}
		else if (sAlarmInfo.eAlarmType == AlarmType_AlarmIn) {
			alarmtype = tr("Alarm In");
		}
		else if (sAlarmInfo.eAlarmType == AlarmType_Shelter) {
			alarmtype = tr("Hide alarm");
		}
		else if (sAlarmInfo.eAlarmType == AlarmType_VideoLoss) {
			alarmtype = tr("Video lost");
		}
// 		else if (sAlarmInfo.eAlarmType == AlarmType_Person) {
// 			alarmtype = tr("Human detection");
// 		}
		else if (sAlarmInfo.eAlarmType == AlarmType_Count) {
			alarmtype = tr("Counting alarm");
	#ifdef _SVIEW_
			return;
	#endif // _SVIEW_
	
		}
		else if (sAlarmInfo.eAlarmType == AlarmType_Area) {
			alarmtype = tr("Area alarm");
	#ifdef _SVIEW_
			return;
	#endif // _SVIEW_
		}
		else if (sAlarmInfo.eAlarmType == AlarmType_Object) {
			alarmtype = tr("Object detection alarm");
	#ifdef _SVIEW_
			return;
	#endif // _SVIEW_
		}
		else if (sAlarmInfo.eAlarmType == AlarmType_Wire) {
			alarmtype = tr("Cross line alarm");
	#ifdef _SVIEW_
			return;
	#endif // _SVIEW_
		}
		else {
			//alarmtype=tr("Unknown type");
			return;
		}
		
	if (m_bOpenSound && sAlarmInfo.isStoped == 0)
		emit sendPlaySound(sAlarmInfo.eAlarmType);
	CMS_CONNECT_PARSE_Node *pNode = NULL;
	if (sAlarmInfo.eAlarmType == AlarmType_AlarmIn)
	{
		QModelIndex index = CMSTreeView::getModelIndexByDevSNandAlarmInNo((sAlarmInfo.cSerialNum), sAlarmInfo.iParam);
		if (index == QModelIndex())
			return;
		pNode = CMSTreeView::getNodebyModelIndex(index);
	}
	else
	{
		QModelIndex index = CMSTreeView::getModelIndexByDevSNandChNo((sAlarmInfo.cSerialNum), sAlarmInfo.iParam);
		if (index == QModelIndex())
			return;
		pNode = CMSTreeView::getNodebyModelIndex(index);
	}
	if (NULL != pNode)
	{
		ui->table_alarm->insertRow(0);
		ui->table_alarm->setItem(0, 0, new QTableWidgetItem(QDateTime::fromTime_t(sAlarmInfo.timeUTC).toUTC().toString("yyyy-MM-dd hh:mm:ss")));//告警时间
		ui->table_alarm->setItem(0, 1, new QTableWidgetItem(alarmtype));//告警类型
		ui->table_alarm->setItem(0, 2, new QTableWidgetItem(QString(sAlarmInfo.cSerialNum)));//设备序列号
		ui->table_alarm->setItem(0, 3, new QTableWidgetItem(QString("%1").arg(sAlarmInfo.iParam)));//参数
		ui->table_alarm->setItem(0, 4, new QTableWidgetItem(QString(pNode->parent->cNodeName) + "-" + QString(pNode->cNodeName)));//告警源
		QString alarmState = sAlarmInfo.isStoped == 0 ? tr("Start Alarm") : tr("Stop Alarm");
		ui->table_alarm->setItem(0, 5, new QTableWidgetItem(alarmState));//告警状态
	}
	if (ui->table_alarm->rowCount() > 100)
		ui->table_alarm->removeRow(100);
}

void AlarmInfoWidget::onOpenSound(int type)
{
// 	QString dir = QCoreApplication::applicationDirPath();
// 	if (type == AlarmType_Motion) {
// 		QSound::play(dir + "/AlarmSound/motion.wav");
// 	}
// 	else if (type == AlarmType_AlarmIn) {
// 		QSound::play(dir + "/AlarmSound/alarmInput.wav");
// 	}
// 	else if (type == AlarmType_Shelter) {
// 		QSound::play(dir + "/AlarmSound/videoCover.wav");
// 	}
// 	else if (type == AlarmType_VideoLoss) {
// 		QSound::play(dir + "/AlarmSound/videoLoss.wav");
// 	}
// 	else if (type == AlarmType_Count) {
// 		QSound::play(dir + "/AlarmSound/countAlarm.wav");
// 	}
// 	else if (type == AlarmType_Area) {
// 		QSound::play(dir + "/AlarmSound/areaAlarm.wav");
// 	}
// 	else if (type == AlarmType_Object) {
// 		QSound::play(dir + "/AlarmSound/objectAlarm.wav");
// 	}
// 	else if (type == AlarmType_Wire) {
// 		QSound::play(dir + "/AlarmSound/crossAlarm.wav");
// 	}
// 	else if (type == AlarmType_Person)
// 	{
// 		QSound::play(dir + "/AlarmSound/humanDetection.wav");
// 	}
}

void AlarmInfoWidget::insertOnOfflineEvent(CMS_CONNECT_PARSE_Node *node)
{
	if (NULL != node && NodeType_Device == node->eNodeType)
	{
		CMS_CONNECT_PARSE_DeviceNode *deviceNode = (CMS_CONNECT_PARSE_DeviceNode *)node;
		QString deviceType = tr("Device state");
		QString alarmState = deviceNode->isOnline == 1 ? tr("Online") : tr("Offline");
		insertEvent(deviceType + " " + QString(node->cNodeName) + " " + alarmState);
	}
}
//设备上下线提示
void AlarmInfoWidget::onDeviceOnline(TreeChangeType changeType, CMS_CONNECT_PARSE_Node *pNode)
{
	if (changeType == CT_DevOnOffLine)
	{
		insertOnOfflineEvent(pNode);
	}
}



//双击查看视频
/*
void AlarmInfoWidget::onItemDoubleClicked(QTableWidgetItem *item)
{
	if (item == NULL)
		return;
	int row = ui->table_alarm->row(item);
	QString alarmSource = ui->table_alarm->item(row, 4)->text();
	if (alarmSource.contains("Local"))
		return;
	QString alarmSerial = ui->table_alarm->item(row, 2)->text();
	int param = ui->table_alarm->item(row, 3)->text().toInt();
	QString alarmType = ui->table_alarm->item(row, 1)->text();
	int channel = param;
	if (alarmType == tr("Alarm In")) {
		QModelIndex index = CMSTreeView::getModelIndexByDevSNandAlarmInNo(alarmSerial, param);
		if (index == QModelIndex())
			return;
		CMS_CONNECT_PARSE_AlarmInNode *node = (CMS_CONNECT_PARSE_AlarmInNode *)CMSTreeView::getNodebyModelIndex(index);
		int localAlarmInCount = ((CMS_CONNECT_PARSE_DeviceNode *)node->parent)->iAlarmInCount - ((CMS_CONNECT_PARSE_DeviceNode *)node->parent)->iChannelCount;
		channel = param - localAlarmInCount;
	}
	else {
		QModelIndex index = CMSTreeView::getModelIndexByDevSNandChNo(alarmSerial, param);
		if (index == QModelIndex())
			return;
	}

	PreviewMap *prevDlg;
	if (MapChDlg.contains(alarmSerial + QString("%1").arg(channel))) {
		//判断该通道是否打开
		prevDlg = MapChDlg.value(alarmSerial + QString("%1").arg(channel));
	}
	else {
		//创建预览窗口
		prevDlg = new PreviewMap(alarmSerial, channel, this);
		prevDlg->move(prevDlg->pos().x() + MapChDlg.size() * 30, prevDlg->pos().y() + MapChDlg.size() * 30);
	}
	prevDlg->show();
	prevDlg->raise();
	prevDlg->activateWindow();
}
*/