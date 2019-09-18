#include "preview.h"
#include "QQuickWidget"
#include "QQmlContext"
#include <QTimer>
#include <QSettings>
#include "smartFrameRender.h"
#include "rtspclient_api.h"
#include "vPrevMulitWindow.h"
#include "vPrevWindow.h"
#include "faceServer/faceServer.h"
#include "eventController/videoController.h"
#include "faceServer/recognitiveAnts.h"
#include "eventController/channelController.h"

void rtsp_data_cb(long hRtspHandle, unsigned long dwDataType, unsigned long dwProp, unsigned char *lpBuffer, unsigned long dwBufSize, void* lpUser)
{
	if (!g_bShowPreview)
	{
		return;
	}
	AntsFrameHeader *frame_head = (AntsFrameHeader *)lpBuffer;
	if (frame_head->uiFrameType != 0x01 &&
		frame_head->uiFrameType != 0x08 &&
		frame_head->uiFrameType != 0x09 &&
		frame_head->uiFrameType != 0x12 &&
		frame_head->uiFrameType != 0x13 &&
		frame_head->uiFrameType != 0x1b &&
		frame_head->uiFrameType != 0x1c)
	{
		return;
	}

	VPrevWindow *pPreview = (VPrevWindow *)lpUser;
	if (pPreview == NULL || pPreview->m_bSpilt == true || pPreview->isHidden())
	{
		return;
	}
	if (((VPrevMulitWindow*)(pPreview->m_pMulitWindow))->isHidden())
	{
		return;
	}

	if (0x1b == frame_head->uiFrameType || 0x1c == frame_head->uiFrameType) {
		SFR_inputSmartData(pPreview->iPlayPort, lpBuffer, dwBufSize);
	}
	else
	{
		if (!((VPrevMulitWindow*)(pPreview->m_pMulitWindow))->m_bShowMax)
		{
			if (frame_head->uiFrameType == 0x01 || frame_head->uiFrameType == 0x09)
			{
				return;
			}
		}
		else
		{
			if (frame_head->uiFrameType == 0x12 || frame_head->uiFrameType == 0x13)
			{
				return;
			}
		}
		while (!I8_MP4Play_InputData(pPreview->iPlayPort, lpBuffer, dwBufSize)) {
			Sleep(4);
		}
	}
}

long __stdcall I8DRAWFUNEx_v1(long nPort, HDC hDC, unsigned int width, unsigned int heigth, LONG nUser) {
	VPrevWindow *prev = (VPrevWindow *)nUser;
	SFR_drawSmartData(nPort, hDC, width, heigth, prev->ui.widgetVideoArea->width(), prev->ui.widgetVideoArea->height());
	if (prev->m_3DPos != QPoint(-1, -1)) {
		HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
		QPoint g_3DPos = QPoint(prev->m_3DPos.x()*width / prev->ui.widgetVideoArea->width(), prev->m_3DPos.y()*heigth / prev->ui.widgetVideoArea->height());
		QPoint g_3DMovePos = QPoint(prev->m_3DMovePos.x()*width / prev->ui.widgetVideoArea->width(), prev->m_3DMovePos.y()*heigth / prev->ui.widgetVideoArea->height());
		MoveToEx(hDC, g_3DPos.x(), g_3DPos.y(), NULL);
		LineTo(hDC, g_3DMovePos.x(), g_3DPos.y());
		LineTo(hDC, g_3DMovePos.x(), g_3DMovePos.y());
		LineTo(hDC, g_3DPos.x(), g_3DMovePos.y());
		LineTo(hDC, g_3DPos.x(), g_3DPos.y());
		DeleteObject(hPen);
	}
	return 0;
}

//sta_listStream是已经开流的map，根据通道号索引，存入相应句柄
QMap<int, int> Preview::sta_listStream;

Preview::Preview(QWidget *parent)
	: QWidget(parent)
	, m_pMulitWindow(NULL)
{
	ui.setupUi(this);

	m_pMulitWindow = new VPrevMulitWindow(this);
	ui.horizontalLayout_3->insertWidget(0, m_pMulitWindow);
	connect(ui.btnSplit_1, SIGNAL(clicked()), this, SLOT(slot_split1()));
	connect(ui.btnSplit_4, SIGNAL(clicked()), this, SLOT(slot_split4()));
	connect(ui.btnSplit_9, SIGNAL(clicked()), this, SLOT(slot_split9()));
	connect(ui.btnSplit_16, SIGNAL(clicked()), this, SLOT(slot_split16()));
	connect(m_pMulitWindow, SIGNAL(sig_double_clicked(bool, int)), this, SLOT(slot_double_clicked(bool, int)));
	for (int i = 0; i < MAX_PREV_WINDOW_NUM; i++) {
		connect(m_pMulitWindow->m_pWindow[i], SIGNAL(sig_pre_close(int)), this, SLOT(slot_pre_close(int)));
	}

	//channel list
	ui.quickWidget_channel->rootContext()->setContextProperty("VideoController", VideoController::getInstance());
	ui.quickWidget_channel->setSource(QUrl("./Qml/Infrastructure/VideoLeft.qml"));
	ui.quickWidget_channel->setClearColor(Qt::transparent);
	ui.quickWidget_channel->setAttribute(Qt::WA_AlwaysStackOnTop);
	ui.quickWidget_channel->setResizeMode(QQuickWidget::SizeRootObjectToView);
	connect(ui.btnHide, SIGNAL(clicked()), this, SLOT(slot_hide()));
	connect(VideoController::getInstance(), SIGNAL(sig_open_realstream(int)), this, SLOT(slot_open_realstream(int)));
	connect(ChannelController::getInstance(), SIGNAL(sig_close_by_channel(int)), this, SLOT(slot_close_by_channel(int)));

	//抓拍和告警的推送
	RecognitiveAnts *pWorker = RecognitiveAnts::getInstance();
	pWorker->start();
	connect(pWorker, SIGNAL(sig_send_facepic(QString, int, QString)), VideoController::getInstance(), SLOT(slot_addCapture(QString, int, QString)));
	connect(pWorker, SIGNAL(sig_recognitive_result(QString, int, QString, QSharedPointer<FACE_PARSE_RecogInfo>, int)), VideoController::getInstance(), SLOT(slot_addAlarm(QString, int, QString, QSharedPointer<FACE_PARSE_RecogInfo>, int)));

	//capture list
	ui.quickWidget_capture->rootContext()->setContextProperty("VideoController", VideoController::getInstance());
	ui.quickWidget_capture->setSource(QUrl("./Qml/Infrastructure/VideoBottom.qml"));
	ui.quickWidget_capture->setClearColor(Qt::transparent);
	ui.quickWidget_capture->setAttribute(Qt::WA_AlwaysStackOnTop);
	ui.quickWidget_capture->setResizeMode(QQuickWidget::SizeRootObjectToView);

	//alarm list
	ui.quickWidget_alarm->rootContext()->setContextProperty("VideoController", VideoController::getInstance());
	ui.quickWidget_alarm->setSource(QUrl("./Qml/Infrastructure/VideoRight.qml"));
	ui.quickWidget_alarm->setClearColor(Qt::transparent);
	ui.quickWidget_alarm->setAttribute(Qt::WA_AlwaysStackOnTop);
	ui.quickWidget_alarm->setResizeMode(QQuickWidget::SizeRootObjectToView);
}

Preview::~Preview()
{
	closeAllStream();
}

void Preview::slot_hide() {
	if (!ui.widget_channel->isHidden()) {
		ui.widget_channel->hide();
	}else{
		ui.widget_channel->show();
	}
}

void Preview::closeAllStream() {
	for (int i = 0; i < MAX_PREV_WINDOW_NUM; i++)
	{
		VPrevWindow *pPrevWindow = m_pMulitWindow->m_pWindow[i];
		//如果此窗口正在播放实时流
		if (pPrevWindow->m_bPlay) {
			int ret = closeRealtimeStream(sta_listStream[pPrevWindow->m_iChannelNo]);
			if (ret == ResultCode_Succ) {
				sta_listStream.remove(pPrevWindow->m_iChannelNo);
				//窗口关闭解码和界面初始化
				pPrevWindow->restoreDefaults();
			}
			else
			{
				qDebug() << "Preview::closeAllStream:close window realtime stream failed,window is " << i;
			}
		}
	}
}

void Preview::slot_split1() {
	if (m_pMulitWindow->m_bShowMax) {
		return;
	}
	//m_pMulitWindow->update();
// 	QSettings settings(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
// 	settings.setValue("Preview/splitNum", Type_Split1);
	m_pMulitWindow->showMax();
}

void Preview::slot_split4() {
	layoutWinsByChans(Type_Split4);
// 	QSettings settings(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
// 	settings.setValue("Preview/splitNum", Type_Split4);
}

void Preview::slot_split9() {
	layoutWinsByChans(Type_Split9);
// 	QSettings settings(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
// 	settings.setValue("Preview/splitNum", Type_Split9);
}

void Preview::slot_split16() {
	layoutWinsByChans(Type_Split16);
// 	QSettings settings(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
// 	settings.setValue("Preview/splitNum", Type_Split16);
}

void Preview::layoutWinsByChans(int iChans) {
	//如果窗口不是最大化 并且 分屏m_iWinNum与想要的分屏数iChans相等
	if (!m_pMulitWindow->m_bShowMax && m_pMulitWindow->m_iWinNum == iChans)
	{
		return;
	}
	//如果此窗口最大化
	if (m_pMulitWindow->m_bShowMax) {
		slot_double_clicked(false, m_pMulitWindow->m_pCurWin->m_iIndex);
	}
	m_pMulitWindow->hidePrevWindow();
	m_pMulitWindow->update();

// 	for (int i = 0; i < MAX_PREV_WINDOW_NUM; i++) {
// 		m_pMulitWindow->m_pWindow[i]->m_bSpilt = true;
// 	}
	m_pMulitWindow->layoutWindows(iChans);
// 	for (int i = 0; i < MAX_PREV_WINDOW_NUM; i++) {
// 		m_pMulitWindow->m_pWindow[i]->m_bSpilt = false;
// 	}
}

//双击左侧设备开流，channel是设备通道号，显示在焦点窗口
void Preview::slot_open_realstream(int channel) {
	//焦点窗口已经有流，且设备通道号与需要开流的设备通道号一致
	if (m_pMulitWindow->m_pCurWin->m_iChannelNo == channel) {
		return;
	}
	//如果此设备的实时流已经打开,关流
	if (sta_listStream.contains(channel)) {
		for (int i = 0; i < MAX_PREV_WINDOW_NUM; i++)
		{
			//找到显示此设备实时流的窗口
			if (m_pMulitWindow->m_pWindow[i]->m_iChannelNo == channel)
			{
				VPrevWindow *pPrevWindow = m_pMulitWindow->m_pWindow[i];
				int ret = closeRealtimeStream(sta_listStream[pPrevWindow->m_iChannelNo]);
				if (ResultCode_Succ == ret) {
					//窗口关闭解码和界面初始化
					pPrevWindow->restoreDefaults();
					sta_listStream.remove(pPrevWindow->m_iChannelNo);
					//设备开流只能显示在唯一一个窗口，不能在多个窗口显示同一个窗口的流
					break;
				}
				else
				{
					qDebug() << "Preview::slot_open_realstream:close channel realtime stream failed";
					//关闭设备的实时流失败，直接退出
					return;
				}
			}
		}
	}
	//如果焦点窗口有流,关流
	if (m_pMulitWindow->m_pCurWin->m_bPlay) {
		int ret = closeRealtimeStream(sta_listStream[m_pMulitWindow->m_pCurWin->m_iChannelNo]);
		if (ResultCode_Succ == ret) {
			sta_listStream.remove(m_pMulitWindow->m_pCurWin->m_iChannelNo);
			m_pMulitWindow->m_pCurWin->restoreDefaults();
		}
		else
		{
			qDebug() << "Preview::slot_open_realstream:close curwin realtime stream failed";
			return;
		}
	}
	//焦点窗口开此设备的流
	int streamType;
	if (m_pMulitWindow->m_bShowMax) {
		streamType = StreamType_Main;
	}
	else {
		streamType = StreamType_Sub;
	}
	FACE_Client_GetRtspUrl(channel, streamType, [=](int iResultCode, QString url)
	{
		QString strRtspUrl = url;
		int handle = openRealtimeStream(strRtspUrl, "admin", "123456", rtsp_data_cb, m_pMulitWindow->m_pCurWin);
		if (handle) 
		{
			sta_listStream.insert(channel, handle);
			m_pMulitWindow->m_pCurWin->getWinID();
			m_pMulitWindow->m_pCurWin->iPlayPort = I8_MP4Play_GetFreePort();
			if (m_pMulitWindow->m_pCurWin->iPlayPort == -1) {
				qDebug() << "Preview::slot_open_realstream:get free port failed";
				return;
			}
			int headLen = I8_MP4Play_GetFileHeadLength();
			char headBuffer[28];
			memset(headBuffer, 0, headLen);
			headBuffer[2] = 0x01;
			headBuffer[3] = 0xaa;
			headBuffer[4] = 0x03;
			headBuffer[8] = 0x19;
			I8_MP4Play_SetStreamOpenMode(m_pMulitWindow->m_pCurWin->iPlayPort, I8_STREAME_REALTIME);
			I8_MP4Play_ResetSourceBuffer(m_pMulitWindow->m_pCurWin->iPlayPort);
			I8_MP4Play_OpenStream(m_pMulitWindow->m_pCurWin->iPlayPort, (PBYTE)headBuffer, headLen, 2 * 1024 * 1024);
			I8_MP4Play_RigisterDrawFunEx(m_pMulitWindow->m_pCurWin->iPlayPort, I8DRAWFUNEx_v1, (LONG)m_pMulitWindow->m_pCurWin);
			SFR_initOnceSmartRender(m_pMulitWindow->m_pCurWin->iPlayPort);
			I8_MP4Play_SetPlayerBufNumber(m_pMulitWindow->m_pCurWin->iPlayPort, 5);
			I8_MP4Play_Play(m_pMulitWindow->m_pCurWin->iPlayPort, (HWND)m_pMulitWindow->m_pCurWin->ui.widgetVideoArea->winId());
			m_pMulitWindow->m_pCurWin->m_bPlay = true;
			m_pMulitWindow->m_pCurWin->m_iChannelNo = channel;
			m_pMulitWindow->m_pCurWin->ui.label->setText(QString("Ch%1").arg(channel));
			m_pMulitWindow->m_pCurWin->ui.widgetTitle->show();
			m_pMulitWindow->m_pCurWin->showTitle();
			m_pMulitWindow->m_pCurWin->ui.label->adjustSize();
			m_pMulitWindow->m_pCurWin->slot_change_winsize();
			m_pMulitWindow->m_pCurWin->update();
		}
		else
		{
			qDebug() << "Preview::slot_open_realstream:open realtime stream failed";
			return;
		}
	});
}

void Preview::slot_double_clicked(bool bShowMax, int iFirstWin) {
	int channel = m_pMulitWindow->m_pCurWin->m_iChannelNo;
	if (channel == -1) {
		return;
	}
	//焦点窗口关流，没有关解码
	if (sta_listStream.contains(channel)) {
		int ret = closeRealtimeStream(sta_listStream[channel]);
		if(ret == ResultCode_Succ){
			m_pMulitWindow->m_pCurWin->m_bPlay = false;
			sta_listStream.remove(channel);
		}
		else
		{
			qDebug() << "Preview::slot_double_clicked:close curwin realtime stream failed";
			return;
		}
	}
	//焦点窗口开流
	int streamType;
	if (bShowMax) {
		streamType = StreamType_Main;
	}
	else {
		streamType = StreamType_Sub;
	}
	FACE_Client_GetRtspUrl(m_pMulitWindow->m_pCurWin->m_iChannelNo, streamType, [=](int iResultCode, QString url)
	{
		QString strRtspUrl = url;
		int handle = openRealtimeStream(strRtspUrl, "admin", "123456", rtsp_data_cb, m_pMulitWindow->m_pCurWin);
		if (handle) {
			sta_listStream.insert(channel, handle);
			if (m_pMulitWindow->m_pCurWin->iPlayPort < 0) {
				m_pMulitWindow->m_pCurWin->getWinID();
				m_pMulitWindow->m_pCurWin->iPlayPort = I8_MP4Play_GetFreePort();
				if (m_pMulitWindow->m_pCurWin->iPlayPort == -1) {
					qDebug() << "Preview::slot_double_clicked: failed";
					return;
				}
				int headLen = I8_MP4Play_GetFileHeadLength();
				char headBuffer[28];
				memset(headBuffer, 0, headLen);
				headBuffer[2] = 0x01;
				headBuffer[3] = 0xaa;
				headBuffer[4] = 0x03;
				headBuffer[8] = 0x19;
				I8_MP4Play_SetStreamOpenMode(m_pMulitWindow->m_pCurWin->iPlayPort, I8_STREAME_REALTIME);
				I8_MP4Play_ResetSourceBuffer(m_pMulitWindow->m_pCurWin->iPlayPort);
				I8_MP4Play_OpenStream(m_pMulitWindow->m_pCurWin->iPlayPort, (PBYTE)headBuffer, headLen, 1024 * 1024);
				I8_MP4Play_RigisterDrawFunEx(m_pMulitWindow->m_pCurWin->iPlayPort, I8DRAWFUNEx_v1, (LONG)m_pMulitWindow->m_pCurWin);
				SFR_initOnceSmartRender(m_pMulitWindow->m_pCurWin->iPlayPort);
				I8_MP4Play_SetPlayerBufNumber(m_pMulitWindow->m_pCurWin->iPlayPort, 5);
				I8_MP4Play_Play(m_pMulitWindow->m_pCurWin->iPlayPort, (HWND)m_pMulitWindow->m_pCurWin->ui.widgetVideoArea->winId());
			}
			m_pMulitWindow->m_pCurWin->m_bPlay = true;
			m_pMulitWindow->m_pCurWin->m_iChannelNo = channel;
			m_pMulitWindow->m_pCurWin->ui.label->setText(QString("Ch%1").arg(channel));
		}
		else
		{
			qDebug() << "Preview::slot_double_clicked:open curwin realtime stream failed";
		}
	});
}

//点击当个窗口的关闭按钮关流
void Preview::slot_pre_close(int index) {
	VPrevWindow* pPrevWindow = m_pMulitWindow->m_pWindow[index];
	if (NULL != pPrevWindow) {
		m_pMulitWindow->m_pCurWin->showFrame(false);
		m_pMulitWindow->m_pCurWin = pPrevWindow;
		m_pMulitWindow->m_pCurWin->showFrame(true);
		int ret = closeRealtimeStream(sta_listStream[pPrevWindow->m_iChannelNo]);
		if (ResultCode_Succ == ret) {
			sta_listStream.remove(pPrevWindow->m_iChannelNo);
			pPrevWindow->restoreDefaults();
		}
		else
		{
			qDebug() << "Preview::slot_pre_close:close window realtime stream failed";
			return;
		}
	}
}

//根据设备通道号关流
void Preview::slot_close_by_channel(int iChannel) {
	//如果此设备的实时流已经打开
	if (sta_listStream.contains(iChannel)) {
		for (int i = 0; i < MAX_PREV_WINDOW_NUM; i++)
		{
			//找到显示此设备实时流的窗口
			if (m_pMulitWindow->m_pWindow[i]->m_iChannelNo == iChannel)
			{
				VPrevWindow *pPrevWindow = m_pMulitWindow->m_pWindow[i];
				int ret = closeRealtimeStream(sta_listStream[pPrevWindow->m_iChannelNo]);
				if (ResultCode_Succ == ret) {
					//窗口关闭解码和界面初始化
					pPrevWindow->restoreDefaults();
					sta_listStream.remove(pPrevWindow->m_iChannelNo);
				}
			}
		}
	}
}

void Preview::resizeEvent(QResizeEvent *e)
{
	this->update();
}