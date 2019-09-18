#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inc/I8_PlaySDK.h"
#include <QDir>
#include <qmessagebox.h>
#include "frmmain.h"
#include "playmultiwindow.h"
#include <tchar.h>
#include "equipment.h"
#include <qfile.h>
#include <qdir.h>
#include <shlobj.h> 
#include "windows.h"


#define CH(text) QString::fromLocal8Bit(text)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_init = initSDK();
}

MainWindow::~MainWindow()
{
    delete ui;
	if (m_init != -1)
	{
		I8H_SDK_Cleanup();
		I8_MP4Play_Stop(m_dwPort);
		I8_MP4Play_CloseStream(m_dwPort);
		I8_MP4Play_StopSound();
	}
}

BOOL MainWindow::initSDK()
{
    QString ipKeyPath = QDir::currentPath();
    ipKeyPath.append("\\self.pem");
    I8H_INIT_PARAM initParam;
    strcpy_s((char*)initParam.byKeyPath, sizeof(initParam.byKeyPath), ipKeyPath.toLocal8Bit().data());
    initParam.bAsync = 1;    
    m_init = -1;
    m_ipClientInfor = NULL;

    ui->ipEdit->setText("10.0.0.211");
    ui->portEdit->setText("80");
    ui->nameEdit->setText("admin");
    ui->pwdEdit->setText("aa123456");

    BYTE byFileHeaders[28]={0x00,0x00,0x01,0xAA,0x03,0x00,0x00,0x00,0x19,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    m_dwPort = I8_MP4Play_GetFreePort();
    if(-1 == m_dwPort)
    {
        return FALSE;
    }

    I8_MP4Play_SetStreamOpenMode(m_dwPort, I8_STREAME_REALTIME);
    I8_MP4Play_OpenStream(m_dwPort, byFileHeaders, sizeof(byFileHeaders), 2 * 1024 * 1024);
    I8_MP4Play_SetDisplayCallBack(m_dwPort, NULL);
    I8_MP4Play_SetPlayerBufNumber(m_dwPort, 100);
    BOOL res = I8H_SDK_Initv2(&initParam);
    I8H_SDK_SetConnectTime(2, 2);

    return res;
}

 BOOL MainWindow::isPlay()
 {
    if (m_ipClientInfor == NULL || m_ipClientInfor->hUserId == NULL)
    {
        QMessageBox::information(this, CH("提示"), CH("请先登入"));
        return FALSE;
    }
    if (m_ipClientInfor->hRealPlay == NULL)
    {
        QMessageBox::information(this, CH("提示"), CH("请先点击播放"));
        return FALSE;
    }
    return TRUE;
 }

 VOID CALLBACK MainWindow::captureCbFun(long lPort, char *pBuf, long nSize, long nWidth, long nHeight, long nStamp, long nReserved1, long nReserved2)
 {
	 QDir dir("D:\\123");
	 if (!dir.exists())
	 {
		 dir.mkdir("D:\\123");
	 }
	 static int i = 1;
	 static QString fileName = "capture.bmp";
	 QString strFilepath = "D:\\123\\";
	 QString strFilename = strFilepath.append(fileName);
	 I8_MP4Play_ConvertToBmpFile(pBuf, nSize, nWidth, nHeight, nReserved1, nReserved2, strFilename.toLocal8Bit().data());
	 I8_MP4Play_SetDisplayCallBack(lPort, NULL);
	 QString str = QString::number(i);
	 fileName = fileName.left(7).append(str).append(".bmp");
	 i++;
 }

VOID CALLBACK MainWindow::fStreamDataCallBack(HANDLE hHandle, DWORD dwOption, DWORD dwDataType, BYTE *lpBuffer, DWORD dwBufferSize, LPVOID lpUser)
{
	int nCount = 4;
	BOOL bInputData = FALSE;
	WORD wChannel = (dwOption >> 16) & 0xFFFF;
	WORD wStreameType = dwOption & 0xFF;
	int wFreePort = -1;
	MainWindow* lpDialog = (MainWindow*)lpUser;

	while (!bInputData && nCount)
	{
		bInputData = I8_MP4Play_InputData(lpDialog->m_dwPort, (PBYTE)lpBuffer, dwBufferSize);

		if (!bInputData)
		{
			nCount--;

			Sleep(10);

			continue;
		}
		break;
	}
}

void MainWindow::on_LoginBtn_clicked()
{
    if(!m_init)
    {
        QMessageBox::information(this, CH("提示"), CH("SKD 未初始化"));
        return;
    }
    if(m_ipClientInfor != NULL)
    {
        on_LogoutBtn_clicked();
    }

    m_ipClientInfor = new I8H_BASIC_INFO;
    memset(m_ipClientInfor, 0, sizeof(I8H_BASIC_INFO));

    QString strIp = ui->ipEdit->text();
    QString strPort = ui->portEdit->text();
    QString strName = ui->nameEdit->text();
    QString strPwd = ui->pwdEdit->text();
    if(strIp.size() == 0 || strPort.size() == 0
            ||strName.size() == 0 || strPwd.size() == 0)
	{
		QMessageBox::information(this, CH("提示"), CH("请输入完整信息"));
        return;
    }

    I8H_DEVICEINFO deviceInfor = {0};
    HANDLE userId = I8H_SDK_Login(strIp.toLocal8Bit().data(), (WORD)(strPort.toShort()),
                                  strName.toLocal8Bit().data(), strPwd.toLocal8Bit().data(), &deviceInfor);

	I8_MP4Play_SetStreamOpenMode(m_dwPort, I8_STREAME_REALTIME);//实时
    if(userId == NULL)
    {
        if(m_ipClientInfor != NULL)
        {
            delete m_ipClientInfor;
            m_ipClientInfor = NULL;
        }
        QMessageBox::information(this, CH("提示"), CH("登入失败"));
        return;
    }
    else
    {
		if (count == 0)
		{
			userName = strName;
			passowrd = strPwd;
			m_ipClientInfor->wChanNum = deviceInfor.wChanNum;
			m_ipClientInfor->hUserId = userId;
			QMessageBox::information(this, CH("提示"), CH("登入成功"));
			count++;
		}
		else
		{
			QMessageBox::information(this, CH("提示"), CH("您已登陆"));
		}
    }
}

void MainWindow::on_LogoutBtn_clicked()
{
	if (!isPlay())
	{
		return;
	}
	if (!I8H_SDK_CALL I8H_SDK_Logout(m_ipClientInfor->hUserId))
	{
		QMessageBox::information(this, CH("提示"), CH("注销失败"));
	}
	else
	{
		QMessageBox::information(this, CH("提示"), CH("注销成功"));
		count--;
		delete m_ipClientInfor;

		m_ipClientInfor = NULL;
	}
}

void MainWindow::on_downBtn_clicked()
{
    if (!isPlay())
    {
        return;
    }

    if (!I8H_SDK_PTZControl(m_ipClientInfor->hUserId, 1, I8H_TILT_UP, 0, 5))
    {
        QMessageBox::information(this, CH("提示"), CH("控制失败"));
    }
}

void MainWindow::on_rightBtn_clicked()
{
    if (!isPlay())
    {
        return;
    }

    if (!I8H_SDK_PTZControl(m_ipClientInfor->hUserId, 1, I8H_PAN_LEFT, 0, 5))
    {
        QMessageBox::information(this, CH("提示"), CH("控制失败"));
    }
}

void MainWindow::on_upBtn_clicked()
{
    if (!isPlay())
    {
        return;
    }

    if (!I8H_SDK_PTZControl(m_ipClientInfor->hUserId, 1, I8H_TILT_DOWN, 0, 5))
    {
        QMessageBox::information(this, CH("提示"), CH("控制失败"));
    }
}

void MainWindow::on_leftBtn_clicked()
{
    if (!isPlay())
    {
        return;
    }

    if (!I8H_SDK_PTZControl(m_ipClientInfor->hUserId, 1, I8H_PAN_RIGHT, 0, 5))
    {
        QMessageBox::information(this, CH("提示"), CH("控制失败"));
    }
}

void MainWindow::on_stopBtn_clicked()
{
    if (!isPlay())
    {
        return;
    }

    if (!I8H_SDK_PTZControl(m_ipClientInfor->hUserId, 1, I8H_PAN_RIGHT, 1, 5))
    {
        QMessageBox::information(this, CH("提示"), CH("控制失败"));
    }
}

void MainWindow::on_playBtn_clicked()
{
    I8H_CLIENTINFO clientInfor;
    memset(&clientInfor, 0, sizeof(I8H_CLIENTINFO));
	if (m_ipClientInfor == NULL || m_ipClientInfor->hUserId == NULL)
	{
		QMessageBox::information(this, CH("提示"), CH("请先登入"));
	}

    clientInfor.lChannel = 1;
    if (m_ipClientInfor != NULL)
    {
		hPlay = I8H_SDK_RealPlay(m_ipClientInfor->hUserId, &clientInfor, fStreamDataCallBack, this);
        if (hPlay != NULL)
        {
			I8_MP4Play_Play(m_dwPort, (HWND)ui->widget_1->winId());
            I8_MP4Play_PlaySound(m_dwPort);
            m_ipClientInfor->hRealPlay = hPlay;
        }
    }
}

void MainWindow::on_captureBtn_clicked()
{
    if (!isPlay())
    {
        return;
    }
	I8_MP4Play_SetDisplayCallBack(m_dwPort, captureCbFun);
}

void MainWindow::on_reBootBtn_clicked()
{
	if (!isPlay())
	{
		return;
	}
	if (TRUE == I8H_SDK_RebootDVR(m_ipClientInfor->hUserId))
	{
		QMessageBox::information(this, CH("提示"), CH("设备已重启"));
	}

}

void MainWindow::on_alarmBtn_clicked()
{
	if (!isPlay())
	{
		return;
	}
	if (NULL==I8H_SDK_SetupAlarmByRTSP(hPlay))
	{
		QMessageBox::information(this, CH("提示"), CH("报警开启失败"));
	}
	else
	{
		QMessageBox::information(this, CH("提示"), CH("报警已开启"));
	}
	
}

void MainWindow::on_closeAlarmBtn_clicked()
{
	if (!isPlay())
	{
		return;
	}
	if (FALSE == I8H_SDK_CloseAlarmChan(hPlay))
	{

		QMessageBox::information(this, CH("提示"), CH("报警关闭失败"));
	}
	else
	{
		QMessageBox::information(this, CH("提示"), CH("报警已关闭"));
	}
}

void MainWindow::on_pushButton_clicked()
{
	if (!isPlay())
	{
		return;
	}
	m_Channel = new I8H_CHANNEL_INFO;
	m_Channel->byAudioFlag = 0;
	m_Channel->byStreamType = 0;
	m_Channel->wChannel = 1;

	char position[] = "D:\\123\\vidio.avi";
	QDir dir("D:\\123");
	if (!dir.exists())
	{
		dir.mkdir("D:\\123");
	}
	if (TRUE == I8H_SDK_StartRealPlayRecord(hPlay, m_Channel, 0, position))
	{
		QMessageBox::information(this, CH("提示"), CH("正在录像"));
	}
	else
	{
		QMessageBox::information(this, CH("提示"), CH("录像失败"));
		DWORD dwLastError = I8H_SDK_GetLastError();
	}

}

void MainWindow::on_pushButton_2_clicked()
{
	if (!isPlay())
	{
		return;
	}
	if (TRUE == I8H_SDK_StopRealPlayRecord(hPlay, m_Channel, 0))
	{
		QMessageBox::information(this, CH("提示"), CH("停止录像"));
	}
}

std::string MainWindow::getDeskTop()
{
	LPITEMIDLIST pidl;
	LPMALLOC pShellMalloc;
	char szDir[200];
	if (SUCCEEDED(SHGetMalloc(&pShellMalloc)))
	{
		if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl))) {
			// 如果成功返回true  
			SHGetPathFromIDListA(pidl, szDir);
			pShellMalloc->Free(pidl);
		}
		pShellMalloc->Release();
	}
	return std::string(szDir);
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
	std::string path = getDeskTop();
	const char* ch = path.append("\\Demo").c_str();
	if(translator)
	{
		qApp->removeTranslator(translator);
	}
	if (arg1 == tr("chinese"))
	{
		if (translator->load("cloudbox_zh_CN.qm", ch))
		{
			qApp->installTranslator(translator);
			qDebug() << arg1 << translator;
		}
	}
	else if (arg1 == tr("English"))
	{
		if (translator->load("cloudbox_en_CN.qm", ch))
		{
			qApp->installTranslator(translator);
			qDebug() << arg1 << translator;
		}
	}
	ui->retranslateUi(this);
	
}

void MainWindow::setTranslator(QTranslator* translator)
{
	this->translator = translator;
}

void MainWindow::on_pushButton_3_clicked()
{
	if (screenNum == 4)
	{
		ui->widget_2->hide();
		ui->widget_3->hide();
		ui->widget_4->hide();
	}
	else if (screenNum == 8)
	{
		ui->widget_2->hide();
		ui->widget_3->hide();
		ui->widget_4->hide();
		ui->widget_5->hide();
		ui->widget_6->hide();
		ui->widget_7->hide();
		ui->widget_8->hide();
	}
	else if (screenNum == 12)
	{
		ui->widget_2->hide();
		ui->widget_3->hide();
		ui->widget_4->hide();
		ui->widget_5->hide();
		ui->widget_6->hide();
		ui->widget_7->hide();
		ui->widget_8->hide();
		ui->widget_9->hide();
		ui->widget_10->hide();
		ui->widget_11->hide();
		ui->widget_12->hide();
	}
	else if(screenNum == 16)
	{
		ui->widget_2->hide();
		ui->widget_3->hide();
		ui->widget_4->hide();
		ui->widget_5->hide();
		ui->widget_6->hide();
		ui->widget_7->hide();
		ui->widget_8->hide();
		ui->widget_9->hide();
		ui->widget_10->hide();
		ui->widget_11->hide();
		ui->widget_12->hide();
		ui->widget_13->hide();
		ui->widget_14->hide();
		ui->widget_15->hide();
		ui->widget_16->hide();
	}
	screenNum = 1;
}

void MainWindow::on_pushButton_5_clicked()
{
	if (screenNum == 1)
	{
		//ui->widget_1->setFixedSize(300, 300);
		ui->widget_2->show();
		//ui->widget_2->setFixedSize(100, 100);
		ui->widget_3->show();
		ui->widget_4->show();
		ui->widget_5->show();
		ui->widget_6->show();
		ui->widget_7->show();
		ui->widget_8->show();
	}
	else if (screenNum == 4)
	{
		ui->widget_5->show();
		ui->widget_6->show();
		ui->widget_7->show();
		ui->widget_8->show();
	}
	else if (screenNum == 12)
	{
		ui->widget_9->hide();
		ui->widget_10->hide();
		ui->widget_11->hide();
		ui->widget_12->hide();
	}
	else if (screenNum == 16)
	{
		ui->widget_9->hide();
		ui->widget_10->hide();
		ui->widget_11->hide();
		ui->widget_12->hide();
		ui->widget_13->hide();
		ui->widget_14->hide();
		ui->widget_15->hide();
		ui->widget_16->hide();
	}
	screenNum = 8;
}

void MainWindow::on_pushButton_6_clicked()
{
	if (screenNum == 1)
	{
		ui->widget_2->show();
		ui->widget_3->show();
		ui->widget_4->show();
		ui->widget_5->show();
		ui->widget_6->show();
		ui->widget_7->show();
		ui->widget_8->show();
		ui->widget_9->show();
		ui->widget_10->show();
		ui->widget_11->show();
		ui->widget_12->show();
	}
	else if (screenNum == 4)
	{
		ui->widget_5->show();
		ui->widget_6->show();
		ui->widget_7->show();
		ui->widget_8->show();
		ui->widget_9->show();
		ui->widget_10->show();
		ui->widget_11->show();
		ui->widget_12->show();
	}
	else if (screenNum == 8)
	{
		ui->widget_9->show();
		ui->widget_10->show();
		ui->widget_11->show();
		ui->widget_12->show();
	}
	else if (screenNum == 16)
	{
		ui->widget_13->hide();
		ui->widget_14->hide();
		ui->widget_15->hide();
		ui->widget_16->hide();
	}
	screenNum = 12;
}

void MainWindow::on_pushButton_7_clicked()
{
	if (screenNum == 1)
	{
		ui->widget_2->show();
		ui->widget_3->show();
		ui->widget_4->show();
		ui->widget_5->show();
		ui->widget_6->show();
		ui->widget_7->show();
		ui->widget_8->show();
		ui->widget_9->show();
		ui->widget_10->show();
		ui->widget_11->show();
		ui->widget_12->show();
		ui->widget_13->show();
		ui->widget_14->show();
		ui->widget_15->show();
		ui->widget_16->show();
	}
	else if (screenNum == 4)
	{
		ui->widget_5->show();
		ui->widget_6->show();
		ui->widget_7->show();
		ui->widget_8->show();
		ui->widget_9->show();
		ui->widget_10->show();
		ui->widget_11->show();
		ui->widget_12->show();
		ui->widget_13->show();
		ui->widget_14->show();
		ui->widget_15->show();
		ui->widget_16->show();
	}
	else if (screenNum == 8)
	{
		ui->widget_9->show();
		ui->widget_10->show();
		ui->widget_11->show();
		ui->widget_12->show();
		ui->widget_13->show();
		ui->widget_14->show();
		ui->widget_15->show();
		ui->widget_16->show();
	}
	else if (screenNum == 12)
	{
		ui->widget_13->show();
		ui->widget_14->show();
		ui->widget_15->show();
		ui->widget_16->show();
	}
	screenNum = 16;
}

void MainWindow::on_pushButton_4_clicked()
{
	w = new treeview;
	std::string path = getDeskTop();
	const char* ch = path.append("\\Demo\\resouse\\1235.png").c_str();
    QIcon icon(ch);
    w->setWindowIcon(icon);
	w->setWindowTitle(QString::fromUtf16(u"设备管理"));
	w->show();

}
