#include "log.h"
#include "ui_log.h"
#include <QDebug>
#include "QDir"
#include<qmessagebox.h>
#include "QTranslator"
#include "alarminfowidget.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include "PipedServerApi.h"
// #include "./lib/cms_connect_parse_common.h"
// #include "./lib/cms_connect_client.h"
//#include "../json/include/json.h"


// #pragma comment(lib,"./lib/CMS_Connect_Parsed.lib")
// #pragma comment(lib,"./lib/CMS_Connect_Client.lib")
#pragma comment(lib,"ants_ivms_pipeserver.lib")
//#pragma comment(lib,"./json/lib/json_vc71_libmtd.lib")

#define ROW_HEIGHT 30
long _lLoginHandle;
QTranslator trans;
StruLocalCfg _struLocalCfg = { false, false, "C:\\Capture", "C:\\Download", "C:\\Logs", 30,{ "", "", "", "", "", "", "", "" }, 0, "V1.0.[20151109]",0, 80, 443, 0, 0, "4" };

Log* Log::stra_logs = NULL;
Log* Log::getLog(QWidget* parent)
{
    if (stra_logs == NULL)
    {
        stra_logs = new Log(parent);
    }
    return stra_logs;
}

Log::Log(QWidget *parent)
    :QWidget(parent)
    , m_iRowCount(22)
    , m_iCurPage(-1)
    , m_iPageCount(1)
    , m_iCount(0)
    , m_move(false)
    ,ui(new Ui::Log)
{
    ui->setupUi(this);

    ui->btnFirst->setFlat(true);
    ui->btnNext->setFlat(true);
    ui->btnPrevious->setFlat(true);
    ui->btnLast->setFlat(true);


    setUi();
    setButtons(0);
	initStyle();

    connect(ui->btnRetrieve, SIGNAL(clicked()), this, SLOT(onBtnRetrieve()));
    connect(ui->btnExport, SIGNAL(clicked()), this, SLOT(onBtnExport()));
    connect(ui->btnFirst, SIGNAL(clicked(bool)), this, SLOT(onBtnFirst()));
    connect(ui->btnPrevious, SIGNAL(clicked(bool)), this, SLOT(onBtnPrevious()));
    connect(ui->btnNext, SIGNAL(clicked(bool)), this, SLOT(onBtnNext()));
    connect(ui->btnLast, SIGNAL(clicked(bool)), this, SLOT(onBtnLast()));

#ifdef ZKTECO
    ui->widgetIn1->hide();
    ui->widgetIn3->hide();
    ui->widgetIn4->hide();
    ui->widgetOut1->hide();
    ui->widgetOut2->hide();
    ui->widgetOut3->hide();
    ui->widgetOut4->hide();
#endif

}

Log::~Log()
{
    stra_logs = NULL;
    delete ui;
}

void Log::resizeEvent(QResizeEvent * event)
{
    QRect rect = ui->tableWidgetLog->geometry();
	rect.setX(15);
	rect.setY(48);
	rect.setWidth(1356);
	rect.setHeight(649);
    setUserTable();

    ui->tableWidgetLog->setColumnWidth(0, rect.width() / 12);
    ui->tableWidgetLog->setColumnWidth(1, rect.width() / 6);
    ui->tableWidgetLog->setColumnWidth(2, rect.width() / 6);
    ui->tableWidgetLog->setColumnWidth(3, rect.width() / 6);
    ui->tableWidgetLog->setColumnWidth(4, rect.width() / 6);

    //计算后可能存在余数
    ui->tableWidgetLog->setColumnWidth(5, rect.width() - rect.width() / 12 - rect.width() / 6 - rect.width() / 6 - rect.width() / 6 - rect.width() / 6);

    //重新获取显示
    if (m_iCurPage >= 0)
    {
        getLogs(m_iCurPage);
    }
}

void Log::setUi()
{
    QStringList headerList;

    ui->labelLogCount->setText("0");
    ui->labelPageCount->setText(QString("%1/%2").arg(1).arg(1));

    ui->btnRetrieve->setCursor(Qt::PointingHandCursor);
    ui->btnExport->setCursor(Qt::PointingHandCursor);
    ui->btnFirst->setCursor(Qt::PointingHandCursor);
    ui->btnPrevious->setCursor(Qt::PointingHandCursor);
    ui->btnNext->setCursor(Qt::PointingHandCursor);
    ui->btnLast->setCursor(Qt::PointingHandCursor);

    QDateTime curDateTime = QDateTime::currentDateTime();

    QDateTime dateTimeFrom(curDateTime.date(), QTime(0, 0, 0, 0));
    QDateTime dateTimeTo(curDateTime.date(), QTime(23, 59, 59, 999));

    ui->dateTimeEditFrom->setDateTime(dateTimeFrom);
    ui->dateTimeEditTo->setDateTime(dateTimeTo);

    //tableWidget的设置
    //设置表头高度
    ui->tableWidgetLog->horizontalHeader()->setFixedHeight(ROW_HEIGHT);
    ui->tableWidgetLog->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    //设置表头字体加粗
    QFont font = ui->tableWidgetLog->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidgetLog->horizontalHeader()->setFont(font);

    ui->tableWidgetLog->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetLog->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetLog->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读

    ui->tableWidgetLog->setColumnCount(6);
    headerList << tr("No.") << tr("Time") << tr("User") << tr("IP address") << tr("Operation type") << tr("Target");
    ui->tableWidgetLog->setHorizontalHeaderLabels(headerList);

    ui->comboBoxType->addItem(tr("All type"));
    ui->comboBoxType->addItem(tr("Login/out"));
    ui->comboBoxType->addItem(tr("Device manage"));
    ui->comboBoxType->addItem(tr("Linkage manage"));
    this->setWindowFlags(Qt::FramelessWindowHint);
   // ui->comboBoxType->addItem(tr("Remote config"));

	trans.load("ldat_CH.qm");
	qApp->installTranslator(&trans);
	this->ui->retranslateUi(this);
}

void Log::setUserTable()
{
    //计算tableWidget应该设置的行数,行数的计算实际上要减去tableWidget的头的行高
    m_iRowCount = (ui->tableWidgetLog->height() - ui->tableWidgetLog->horizontalHeader()->height()) / ROW_HEIGHT;
	if (m_iRowCount == 0)
		m_iRowCount = 22;
    ui->tableWidgetLog->setRowCount(m_iRowCount);

    //设置每一行的高度为ROW_HEIGHT
    for (int i = 0; i < m_iRowCount; i++)
    {
        ui->tableWidgetLog->setRowHeight(i, ROW_HEIGHT);
    }
}

void Log::initStyle()
{

	QFile file("./ivms_Log.qss");

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

void Log::setButtons(int iCurPage)
{
    if (iCurPage == 0)
    {
        ui->btnFirst->setEnabled(false);
        ui->widget->setEnabled(false);
        ui->btnPrevious->setEnabled(false);
        ui->widget_2->setEnabled(false);
    }
    else
    {
        ui->btnFirst->setEnabled(true);
        ui->widget->setEnabled(true);
        ui->btnPrevious->setEnabled(true);
        ui->widget_2->setEnabled(true);
    }

    if (iCurPage == m_iPageCount - 1)
    {
        ui->btnNext->setEnabled(false);
        ui->widget_3->setEnabled(false);
        ui->btnLast->setEnabled(false);
    }
    else
    {
        ui->btnNext->setEnabled(true);
        ui->widget_3->setEnabled(true);
        ui->btnLast->setEnabled(true);
    }
}


bool Log::getLogs(int iCurPage)
{
	msgType type;
	int iCount = 2, iIndex = 0;
	QString strTemp = "";
	QJsonDocument doc;

	QJsonObject obj;
	obj.insert("msgType", "1");
	obj.insert("from", "ivms_Log");
	obj.insert("target", "ivms_serverMain");

	QJsonObject dataObj;
	dataObj.insert("topic", "IVMS/LoggerManagement");
	dataObj.insert("cmd", "/IVMS/LoggerManagement/v1/log/get");
	dataObj.insert("token", "121312312");
	dataObj.insert("connectTime", 12);

	QJsonObject data;
	data.insert("flag", 15);
	data.insert("timeBegin", 1514772610);
	data.insert("timeEnd", 1567756121);
	data.insert("offset", 0);
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
	int iRow = 0;
	if (iCurPage < m_iPageCount)
	{
		for (int i = 0; i < resultArray.size(); i++)
		{
			QJsonObject json = resultArray.at(i).toObject();
			int msgType = json.value("connectParseLogType").toInt();
			QString userName = json.value("userName").toString();
			QString clientIp = json.value("clientIp").toString();
			QString time = QDateTime::fromTime_t(json.value("time").toInt()).toUTC().toString("yyyy-MM-dd hh:mm:ss");
			QJsonArray paramInt = json.value("paramInt").toArray();

			strTemp = QString("%1").arg(iRow + 1 + iCurPage*m_iRowCount);
			ui->tableWidgetLog->setItem(iRow, 0, new QTableWidgetItem(strTemp));
			ui->tableWidgetLog->setItem(iRow, 1, new QTableWidgetItem(time));
			ui->tableWidgetLog->setItem(iRow, 2, new QTableWidgetItem(userName));
			ui->tableWidgetLog->setItem(iRow, 3, new QTableWidgetItem(clientIp));

			switch (msgType)
			{
			case Type_UserLogin:
				if (paramInt.at(0) == 0)
				{
					ui->tableWidgetLog->setItem(iRow, 4, new QTableWidgetItem(tr("logout")));
				}
				else if (paramInt.at(0) == 1)
				{
					ui->tableWidgetLog->setItem(iRow, 4, new QTableWidgetItem(tr("login")));
				}
				break;
			case Type_DeviceMgr:
				if (paramInt.at(0) == 0)
				{
					ui->tableWidgetLog->setItem(iRow, 4, new QTableWidgetItem(tr("Delete device")));
				}
				if (paramInt.at(0) == 1)
				{
					ui->tableWidgetLog->setItem(iRow, 4, new QTableWidgetItem(tr("Add device")));
				}
				if (paramInt.at(0) == 2)
				{
					ui->tableWidgetLog->setItem(iRow, 4, new QTableWidgetItem(tr("Modify device")));
				}
				break;
			case Type_LinkageRule:
				if (paramInt.at(0) == 0)
				{
					ui->tableWidgetLog->setItem(iRow, 4, new QTableWidgetItem(tr("Delete rule")));
				}
				if (paramInt.at(0) == 1)
				{
					ui->tableWidgetLog->setItem(iRow, 4, new QTableWidgetItem(tr("Add rule")));
				}
				if (paramInt.at(0) == 2)
				{
					ui->tableWidgetLog->setItem(iRow, 4, new QTableWidgetItem(tr("Modify rule")));
				}
				break;

				default:

					break;
			}
			iRow++;
		}
	}

	m_iPageCount = m_iCount / m_iRowCount;
	if (m_iPageCount == 0 || m_iCount % m_iRowCount > 0)
	{
		m_iPageCount += 1;
	}
	if (iCurPage > m_iPageCount - 1)
	{
		iCurPage = m_iPageCount - 1;
	}

	delete[] outBuffer;
	outBuffer = NULL;

    //以下是对列表框的下面的组件的处理
    ui->labelLogCount->setText(QString("%1").arg(m_iCount));
    if (iCurPage < 0)
    {
      iCurPage = 0;
    }
    ui->labelPageCount->setText(QString("%1/%2").arg(iCurPage + 1).arg(m_iPageCount));

    setButtons(iCurPage);

    ui->btnRetrieve->setEnabled(true);

    return true;
}

void Log::exportLogs()
{
	char szFileName[256] = "";
	msgType type;
	int iCount = 2, iIndex = 0;
	QString strTemp = "";
	QJsonDocument doc;

	QJsonObject obj;
	obj.insert("msgType", "1");
	obj.insert("from", "ivms_Log");
	obj.insert("target", "ivms_serverMain");

	QJsonObject dataObj;
	dataObj.insert("topic", "IVMS/LoggerManagement");
	dataObj.insert("cmd", "/IVMS/LoggerManagement/v1/log/get");
	dataObj.insert("token", "121312312");
	dataObj.insert("connectTime", 12);

	QJsonObject data;
	data.insert("flag", 15);
	data.insert("timeBegin", 1514772610);
	data.insert("timeEnd", 1567756121);
	data.insert("offset", 0);
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
	int iRow = 0;

	QDir dir(_struLocalCfg.strExportLogPath);

	if (!dir.exists())
	{
		dir.mkpath(_struLocalCfg.strExportLogPath);
	}

	strcpy(szFileName, _struLocalCfg.strExportLogPath.toUtf8().data());

	strTemp = ui->dateTimeEditFrom->dateTime().toString("yyyyMMddhhmmss") + (tr("_")) + ui->dateTimeEditTo->dateTime().toString("yyyyMMddhhmmss") +
		QString("_%1").arg(QDateTime::currentDateTime().toTime_t()) + ".txt";

	strcat(szFileName, "\\");
	strcat(szFileName, strTemp.toUtf8().data());

	QFile pFile(szFileName);
	pFile.open(QFile::WriteOnly);

	for (int i = 0; i < resultArray.size(); i++)
	{
		QJsonObject json = resultArray.at(i).toObject();
		int msgType = json.value("connectParseLogType").toInt();
		QString userName = json.value("userName").toString();
		QString clientIp = json.value("clientIp").toString();
		QString time = QDateTime::fromTime_t(json.value("time").toInt()).toUTC().toString("yyyy-MM-dd hh:mm:ss");
		QJsonArray paramInt = json.value("paramInt").toArray();

		strTemp = "";
		strTemp += QString("%1").arg(iRow + 1);
		strTemp += "  ";
		strTemp += time;
		strTemp += "  ";
		strTemp += QString(userName);
		strTemp += "  ";
		strTemp += QString(clientIp);
		strTemp += "  ";

		switch (msgType)
		{
		case Type_UserLogin:
			if (paramInt.at(0) == 0)
			{
				strTemp += tr("Logout");
			}
			else if (paramInt.at(0) == 1)
			{
				strTemp += tr("Login");
			}
			break;
		case Type_DeviceMgr:
			if (paramInt.at(0) == 0)
			{
				strTemp += tr("Delete device");
			}
			if (paramInt.at(0) == 1)
			{
				strTemp += tr("Add device");			
			}
			if (paramInt.at(0) == 2)
			{
				strTemp += tr("Modify device");			
			}
			break;
		case Type_LinkageRule:
			if (paramInt.at(0) == 0)
			{
				strTemp += tr("Delete rule");			
			}
			if (paramInt.at(0) == 1)
			{
				strTemp += tr("Add rule");				
			}
			if (paramInt.at(0) == 2)
			{
				strTemp += tr("Modify rule");				
			}
			break;

		default:

			break;
		}
		pFile.write(strTemp.toUtf8().data());
		QTextStream out(&pFile);
		out << endl;
	}
	pFile.close();
	ui->btnRetrieve->setEnabled(true);
	//insertEvent(tr("Export success! Path : ") + szFileName);
}

void Log::onBtnRetrieve()
{
	if (getLogs(0))
    {
        m_iCurPage = 0;
    }
}

void Log::onBtnExport()
{
    exportLogs();
}

void Log::onBtnFirst()
{
    if (m_iCurPage == 0)
    {
        ui->btnFirst->setEnabled(true);

        return;
    }

    m_iCurPage = 0;
    getLogs(m_iCurPage);
}

void Log::onBtnPrevious()
{
    if (m_iCurPage == 0)
    {
        ui->btnPrevious->setEnabled(true);

        return;
    }

    m_iCurPage--;

    getLogs(m_iCurPage);
}

void Log::onBtnNext()
{
    if (m_iCurPage == m_iPageCount - 1)
    {
        ui->btnNext->setEnabled(true);

        return;
    }

    m_iCurPage++;

    getLogs(m_iCurPage);
}

void Log::onBtnLast()
{
    if (m_iCurPage == m_iPageCount - 1)
    {
        ui->btnLast->setEnabled(true);

        return;
    }

    m_iCurPage = m_iPageCount - 1;

    getLogs(m_iCurPage);
}
//-->>Slot functions End end end
