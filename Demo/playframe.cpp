#include "playframe.h"
#include "ui_playframe.h"
#include "ants_ipc_api.h"

playframe::playframe(QWidget *parent, int index, int type)
	: QWidget(parent),
	ui(new Ui::playframe)
{
    ui->setupUi(this);

	connect(ui->btn_frameClose, SIGNAL(clicked()), this, SLOT(onFrameClose()));
	ui->btn_frameClose->hide();

	m_iPort = -1;
	m_iType = type;
	m_hWndHandle = nullptr;
	m_strDeviceName = "";
	m_iChannel = 0;

}

playframe::~playframe()
{
	stopRender();
}

void playframe::getWinId()
{
	if (nullptr == m_hWndHandle)
	{
		m_hWndHandle = (HWND)(ui->widgetVedioArea->winId());
		//m_hWndHandle = (HWND)(this->winId());
	}
	return;
}

//初始化解码器
void playframe::initWndRender(int type)
{
	m_iPort = I8_MP4Play_GetFreePort();
	if (type == 1)
	{
		I8_MP4Play_SetStreamOpenMode(m_iPort, I8_STREAME_FILE);//文件流
	}
	else
	{
		I8_MP4Play_SetStreamOpenMode(m_iPort, I8_STREAME_REALTIME);//实时
	}

	AntsIPCFileHeader_T struAntsClientFileHeader;
	memset((void *)&struAntsClientFileHeader, 0, sizeof(AntsIPCFileHeader_T));
	struAntsClientFileHeader.uiFileStartId = 0xAA010000;
	struAntsClientFileHeader.uiFrameRate = 25;
	struAntsClientFileHeader.uiStreamType = 3;
	struAntsClientFileHeader.uiReserve[0] = 0;
	struAntsClientFileHeader.uiReserve[1] = 0;
	struAntsClientFileHeader.uiReserve[2] = 0;
	struAntsClientFileHeader.uiReserve[3] = 0;
	I8_MP4Play_OpenStream(m_iPort, (BYTE *)&struAntsClientFileHeader, sizeof(AntsIPCFileHeader_T), 1 * 1024 * 1024);
	//I8_MP4Play_SetPlayerBufNumber(m_iPort,100);
	//openSound();
}

void playframe::startRender()
{
	if (m_iPort >= 0)
	{
		return;
	}
	initWndRender(m_iType);
	getWinId();
	I8_MP4Play_Play(m_iPort, (HWND)ui->widgetVedioArea->winId());
	if (m_iType == 0)
	{
		//ui.widget_titleBar->show();
		//ui.btn_frameClose->show();
	}
}

int playframe::inputData(char *buf, int len)
{
	if (m_iPort >= 0)
	{
		return I8_MP4Play_InputData(m_iPort, (PBYTE)buf, len);
	}
	return 0;
}

void playframe::stopRender()
{
	if (m_iPort >= 0)
	{
		//ui.widget_titleBar->hide();
		ui->btn_frameClose->hide();
		I8_MP4Play_ResetSourceBuffer(m_iPort);
		I8_MP4Play_Stop(m_iPort);
		m_strDeviceName = "";
		m_iChannel = 0;
		unInitWndRender();
		update();
	}
}

void playframe::unInitWndRender()
{
	if (m_iPort >= 0)
	{
		I8_MP4Play_CloseStream(m_iPort);
		m_iPort = -1;
	}
}

void playframe::setChannelName(QString deviceName, int channelNo)
{
	m_strDeviceName = deviceName;
	m_iChannel = channelNo;
}