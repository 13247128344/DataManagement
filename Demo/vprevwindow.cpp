#include "vprevwindow.h"
#include "ui_vprevwindow.h"
#include "vprevmulitwindow.h"

vPrevWindow::vPrevWindow(QWidget *parent) :
    QWidget(parent)
	, m_bPlay(false)
	, m_bWidth(false)
	, m_iChannelNo(-1)
	, m_iModeWidth(0)
	, m_iModeHeight(0)
	, m_iIndex(0)
	, m_bSpilt(false)
	, m_pMulitWindow(NULL)
    ,ui(new Ui::vPrevWindow)
{
    ui->setupUi(this);
	m_3DPos = QPoint(-1, -1);
	m_3DMovePos = QPoint(-1, -1);
}

vPrevWindow::vPrevWindow(QWidget *parent, bool bWidth, int iModeWidth, int iModeHeight)
	: QWidget(parent)
	, m_bPlay(false)
	, m_bWidth(false)
	, m_b3DPos(false)
	, m_iChannelNo(-1)
	, m_iModeWidth(0)
	, m_iModeHeight(0)
	, m_iMainHandle(0)
	, m_iSubHandle(0)
	, hWndHandle(NULL)
	, m_iIndex(0)
	, m_bSpilt(false)
	, m_pMulitWindow(NULL)
{
	ui->setupUi(this);
	m_strSerialNumber = "";

	iPlayPort = -1;

	m_bWidth = bWidth;
	m_iModeWidth = iModeWidth;
	m_iModeHeight = iModeHeight;


	iWidth = 1000;
	iHeight = 1000;
	iZoomCount = 0;

	ui->widgetTitle->hide();
	ui->label->setText("");
	ui->label->adjustSize();

	m_3DPos = QPoint(-1, -1);
	m_3DMovePos = QPoint(-1, -1);

	ui->widgetVideoArea->installEventFilter(this);

	connect(ui->btnWinClose, SIGNAL(clicked()), this, SLOT(slot_close()));
}


vPrevWindow::~vPrevWindow()
{
    delete ui;
}

void vPrevWindow::update()
{
	ui->widgetVideoArea->update();
}

void vPrevWindow::getWinID()
{
	if (hWndHandle == NULL)
	{
		hWndHandle = (HWND)(ui->widgetVideoArea->winId());
	}
}

void vPrevWindow::slot_close()
{
	emit sig_pre_close(m_iIndex);
}

//关闭窗口解码和初始化窗口
void vPrevWindow::restoreDefaults()
{
// 	SFR_cleanOnceSmartRender(iPlayPort);
// 	I8_MP4Play_ResetSourceBuffer(iPlayPort);
// 	I8_MP4Play_RigisterDrawFunEx(iPlayPort, NULL, NULL);
// 	I8_MP4Play_CloseStream(iPlayPort);
// 	I8_MP4Play_Stop(iPlayPort);
	iPlayPort = -1;
	m_iChannelNo = -1;
	m_strSerialNumber = "";
	m_bPlay = false;
// 	m_3DPos = QPoint(-1, -1);
// 	m_3DMovePos = QPoint(-1, -1);
	ui->label->setText("");
	ui->label->adjustSize();
	update();
	slot_change_winsize();
	ui->widgetTitle->hide();
}

void vPrevWindow::adjustVideoArea()
{
	int iX = 0, iY = 0;
	int iVideoWidth = 0, iVideoHeight = 0;
	if (m_bWidth)
	{
		iVideoWidth = ui->widgetVideoArea->width();
		iVideoHeight = iVideoWidth * m_iModeHeight / m_iModeWidth;
		iX = 0;
		iY = (ui->widgetVideoArea->height() - iVideoHeight) / 2;
		ui->widgetVideoArea->setGeometry(iX, iY, iVideoWidth, iVideoHeight);
	}
	else
	{
		iVideoHeight = ui->widgetVideoArea->height();
		iVideoWidth = iVideoHeight * m_iModeWidth / m_iModeHeight;
		iX = (ui->widgetVideoArea->width() - iVideoWidth) / 2;
		iY = 0;
		ui->widgetVideoArea->setGeometry(iX, iY, iVideoWidth, iVideoHeight);
	}
}

void vPrevWindow::getPrevMulitWindow(void *pMulitWindow)
{
	if (pMulitWindow == 0)
	{
		return;
	}
	m_pMulitWindow = (void *)pMulitWindow;
}

// bool vPrevWindow::eventFilter(QObject *target, QEvent *e)
// {
// 	if (target == ui->widgetVideoArea) {
// 		QEvent::Type eventType = e->type();
// 		if (eventType == QEvent::MouseMove) {
// 			QMouseEvent* mouseEvent = (QMouseEvent*)e;
// 			QPoint curPosLocal = mouseEvent->pos();
// 			if (m_bPressed) {
// 				if (m_b3DPos) {
// 					if (m_3DPos != QPoint(-1, -1)) {
// 						m_3DMovePos = curPosLocal;
// 
// 						if (m_3DMovePos.x() < 0) {
// 							m_3DMovePos.setX(0);
// 						}
// 
// 						if (m_3DMovePos.x() > ui->widgetVideoArea->width()) {
// 							m_3DMovePos.setX(ui->widgetVideoArea->width());
// 						}
// 
// 						if (m_3DMovePos.y() < 0) {
// 							m_3DMovePos.setY(0);
// 						}
// 
// 						if (m_3DMovePos.y() > ui->widgetVideoArea->height()) {
// 							m_3DMovePos.setY(ui->widgetVideoArea->height());
// 						}
// 					}
// 				}
// 			}
// 			if (iZoomCount > 0) {
// 				if (m_bPressed)
// 				{
// 					int _x = floatToInt((float)(curPosLocal.x() - m_ptOriginPos.x())*(m_rect.right - m_rect.left) / width());
// 					int _y = floatToInt((float)(curPosLocal.y() - m_ptOriginPos.y())*(m_rect.bottom - m_rect.top) / height());
// 					RECT rect1;
// 					if (m_rect.left - _x < 0) {
// 						rect1.left = 0;
// 						rect1.right = m_rect.right - m_rect.left;
// 					}
// 					else if (m_rect.right - _x > iWidth) {
// 						rect1.left = iWidth - m_rect.right + m_rect.left;
// 						rect1.right = iWidth;
// 					}
// 					else {
// 						rect1.left = m_rect.left - _x;
// 						rect1.right = m_rect.right - _x;
// 					}
// 					if (m_rect.top - _y < 0) {
// 						rect1.top = 0;
// 						rect1.bottom = m_rect.bottom - m_rect.top;
// 					}
// 					else if (m_rect.bottom - _y > iHeight) {
// 						rect1.top = iHeight - m_rect.bottom + m_rect.top;
// 						rect1.bottom = iHeight;
// 					}
// 					else {
// 						rect1.top = m_rect.top - _y;
// 						rect1.bottom = m_rect.bottom - _y;
// 					}
// 					I8_MP4Play_SetDisplayRegion(iPlayPort, 0, &rect1, NULL, true);
// 					m_ptOriginPos = curPosLocal;
// 					m_rect.left = rect1.left;
// 					m_rect.right = rect1.right;
// 					m_rect.top = rect1.top;
// 					m_rect.bottom = rect1.bottom;
// 				}
// 				return QWidget::eventFilter(target, e);
// 			}
// 		}
// 		else if (eventType == QEvent::MouseButtonPress) {
// 			QMouseEvent* mouseEvent = (QMouseEvent*)e;
// 			if (mouseEvent->button() == Qt::LeftButton) {
// 				if (iZoomCount > 0) {
// 					m_bPressed = true;
// 					m_ptOriginPos = mouseEvent->pos();
// 				}
// 				else {
// 					if (m_b3DPos) {
// 						m_3DPos = mouseEvent->pos();
// 						m_3DMovePos = m_3DPos;
// 					}
// 				}
// 			}
// 		}
// 		else if (eventType == QEvent::MouseButtonRelease) {
// 			QMouseEvent* mouseEvent = (QMouseEvent*)e;
// 			if (iZoomCount > 0) {
// 				m_bPressed = false;
// 			}
// 			else {
// 				if (mouseEvent->button() == Qt::LeftButton) {
// 
// 					if (m_b3DPos) {
// 
// 						m_3DMovePos = mouseEvent->pos();
// 
// 						if (m_3DMovePos.x() < 0) {
// 							m_3DMovePos.setX(0);
// 						}
// 
// 						if (m_3DMovePos.x() > ui->widgetVideoArea->width()) {
// 							m_3DMovePos.setX(ui->widgetVideoArea->width());
// 						}
// 
// 						if (m_3DMovePos.y() < 0) {
// 							m_3DMovePos.setY(0);
// 						}
// 
// 						if (m_3DMovePos.y() > ui->widgetVideoArea->height()) {
// 							m_3DMovePos.setY(ui->widgetVideoArea->height());
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	return QWidget::eventFilter(target, e);
// }

void vPrevWindow::mouseDoubleClickEvent(QMouseEvent *e)
{
	if (m_pMulitWindow == 0 || (!((vPrevMulitWindow *)m_pMulitWindow)->m_bShowMax && !m_bPlay))
	{
		return;
	}
	((vPrevMulitWindow *)m_pMulitWindow)->showMax();
}

void vPrevWindow::showFrame(bool bSel)
{
	//show red bolder
	ui->widgetPrevUp->setDisabled(bSel);
	ui->widgetPrevDown->setDisabled(bSel);
	ui->widgetPrevLeft->setDisabled(bSel);
	ui->widgetPrevRight->setDisabled(bSel);
}

void vPrevWindow::resizeEvent(QResizeEvent * event)
{
	QPixmap *mBackPic1 = new QPixmap("./Resources/pre_bg.png");
	QPalette palette1;
	palette1.setBrush(QPalette::Background, QBrush((mBackPic1->scaled(ui->widget_5->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))));
	ui->widget_5->setPalette(palette1);
	palette1.setBrush(QPalette::Background, QBrush((mBackPic1->scaled(ui->widgetVideoArea->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))));
	ui->widgetVideoArea->setPalette(palette1);
	showTitle();
	slot_change_winsize();
	/*QTimer::singleShot(1000, this, SLOT(slot_change_winsize()));*/
}

void vPrevWindow::showTitle()
{
	int iTitleWidth = 0;
	QRect rectPre = QRect(0, 0, 0, 0);
	QRect rect = QRect(0, 0, 0, 0);

	iTitleWidth = ui->widgetTitle->width();

	if (iTitleWidth > 0)
	{
		rectPre = ui->btnWinClose->geometry();
		//把widgetBtns的宽度直接写死140，如果是取rectPre宽度，可能出现不断双击单窗，widgetBtns向左移动的问题
		rect.setLeft(iTitleWidth - ui->btnWinClose->width());
		rect.setRight(rect.left() + rectPre.width() - 6);
		rect.setTop(rectPre.top());
		rect.setBottom(rectPre.bottom());
		ui->btnWinClose->setGeometry(rect);
		if (m_strSerialNumber != "")
		{
			ui->label->setGeometry(QRect(ui->label->rect().left(), rectPre.top(), rectPre.right() + ui->btnWinClose->width(), rectPre.bottom()));
		}
	}
};

void vPrevWindow::slot_change_winsize()
{
	//hideWidget();
	int winWidth = ui->widget_5->width();
	int winHeight = ui->widget_5->height();
	int diffWidth = 0;
	int diffHeight = 0;
	ui->widget->setMinimumHeight(1);
	ui->widget->setMaximumHeight(1);
	ui->widget_2->setMinimumHeight(1);
	ui->widget_2->setMaximumHeight(1);
	ui->widget_video_3->setMinimumWidth(1);
	ui->widget_video_3->setMaximumWidth(1);
	ui->widget_video_4->setMinimumWidth(1);
	ui->widget_video_4->setMaximumWidth(1);
}

void vPrevWindow::hideWidget()
{
	ui->widget->setVisible(false);
	ui->widget_2->setVisible(false);
	ui->widget_video_3->setVisible(false);
	ui->widget_video_4->setVisible(false);
	ui->widget->setFixedHeight(0);
	ui->widget_2->setFixedHeight(0);
	ui->widget_video_3->setFixedWidth(0);
	ui->widget_video_4->setFixedWidth(0);
}

void vPrevWindow::showWidget()
{
	ui->widget->show();
	ui->widget_2->show();
	ui->widget_video_3->show();
	ui->widget_video_4->show();
}