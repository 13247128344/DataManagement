#include "vprevmulitwindow.h"
#include "ui_vprevmulitwindow.h"
#include "QMouseEvent"

vPrevMulitWindow::vPrevMulitWindow(QWidget *parent) :
    QWidget(parent)
	, m_bShowMax(false)
	, m_iWinNum(MAX_PREV_WINDOW_NUM)
	, m_pPressWin(0)
	, m_pReleaseWin(0)
	, m_iFirstWin(0)
   , ui(new Ui::vPrevMulitWindow)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint
		| Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint
		| Qt::WindowMaximizeButtonHint);

	for (int i = 0; i < MAX_PREV_WINDOW_NUM; i++) {
		m_pWindow[i] = new vPrevWindow(this, false, 16, 9);
		m_pWindow[i]->getPrevMulitWindow((void *)this);
		m_pWindow[i]->adjustVideoArea();
		m_pWindow[i]->setObjectName(QString("%1").arg(i));
		m_pWindow[i]->m_iIndex = i;
		m_pWindow[i]->showFrame(false);
	}
	int iUnit = (int)sqrt((float)MAX_PREV_WINDOW_NUM);
	for (int i = 0; i < iUnit; i++) {
		for (int j = 0; j < iUnit; j++) {
			ui->gridLayout->addWidget(m_pWindow[i * iUnit + j], i, j);
			m_pWindow[i * iUnit + j]->getWinID();
		}
	}
	m_pCurWin = m_pWindow[0];
	m_pCurWin->showFrame(true);
	installEventFilter(this);
}

vPrevMulitWindow::~vPrevMulitWindow()
{
    delete ui;
}

void vPrevMulitWindow::hidePrevWindow() {
	// 	this->hide();
	for (int i = 0; i < MAX_PREV_WINDOW_NUM; i++) {
		ui->gridLayout->removeWidget(m_pWindow[i]);
		m_pWindow[i]->hideWidget();
		m_pWindow[i]->resize(0, 0);
		m_pWindow[i]->hide();
	}
	// 	this->update();
}

void vPrevMulitWindow::layoutWindows(int iWinNum)
{
	for (int i = 0; i < MAX_PREV_WINDOW_NUM; i++)
	{
		if (m_pWindow[i] == m_pCurWin)
		{
			int firstWin = (i / iWinNum) * iWinNum;
			if (MAX_PREV_WINDOW_NUM - firstWin == 1)
			{
				firstWin = MAX_PREV_WINDOW_NUM - iWinNum;
			}
			else
			{
				if (MAX_PREV_WINDOW_NUM - firstWin < iWinNum)
				{
					firstWin = MAX_PREV_WINDOW_NUM - firstWin;
				}
			}
			m_iFirstWin = firstWin;
			break;
		}
	}
	int iUnit = ceil(sqrt((float)iWinNum));
	for (int i = 0; i < iUnit; i++) {
		for (int j = 0; j < iUnit; j++) {
			ui->gridLayout->addWidget(m_pWindow[i * iUnit + j + m_iFirstWin], i, j);
		}
	}
	for (int i = 0; i < iWinNum; ++i)
	{
		m_pWindow[i + m_iFirstWin]->update();
	}
	m_bShowMax = false;
	changePrevWindow();
	//QTimer::singleShot(100, this, [=]() {
	for (int i = 0; i < MAX_PREV_WINDOW_NUM; i++) {
		m_pWindow[i]->show();
	}
	//});
	// 	QSettings settings(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
	// 	settings.setValue(QString("Preview/splitNum"), iWinNum);
// 	if (Type_Split1 != iWinNum)
// 	{
// 		m_iWinNum = iWinNum;
// 	}
}

void vPrevMulitWindow::showMax()
{
	if (!m_bShowMax)
	{
		hidePrevWindow();
		update();
		layoutWindows(1);
		m_bShowMax = true;
		emit sig_double_clicked(m_bShowMax, m_iFirstWin);
	}
	else
	{
		layoutWindows(m_iWinNum);
		m_bShowMax = false;
		emit sig_double_clicked(m_bShowMax, m_iFirstWin);
	}
}

void vPrevMulitWindow::changePrevWindow()
{
	/**modify by HG_Panda*/
	this->show();
	for (int i = 0; i < MAX_PREV_WINDOW_NUM; ++i)
	{
		m_pWindow[i]->showWidget();
	}
}

void vPrevMulitWindow::switchWin(vPrevWindow *win1, vPrevWindow *win2)
{
	int layOutIndex1 = 0, layOutIndex2 = 0;
	int index1 = 0, index2 = 0;
	int row1, column1, rowpan1, columnpan1, row2, column2, rowpan2, columnpan2;

	index1 = ui->gridLayout->indexOf(win1);
	index2 = ui->gridLayout->indexOf(win2);

	ui->gridLayout->getItemPosition(index1, &row1, &column1, &rowpan1, &columnpan1);
	ui->gridLayout->getItemPosition(index2, &row2, &column2, &rowpan2, &columnpan2);

	ui->gridLayout->removeWidget(win1);
	ui->gridLayout->removeWidget(win2);
	ui->gridLayout->addWidget(win2, row1, column1, rowpan1, columnpan1);
	ui->gridLayout->addWidget(win1, row2, column2, rowpan2, columnpan2);

	m_pWindow[win1->m_iIndex] = win2; //modify by HG_Panda
	m_pWindow[win2->m_iIndex] = win1;

	int index = win1->m_iIndex;
	win1->m_iIndex = win2->m_iIndex;
	win2->m_iIndex = index;
}

int vPrevMulitWindow::getWinNum()
{
	return m_iWinNum;
}

bool isMove = false;

bool vPrevMulitWindow::eventFilter(QObject *target, QEvent *e)
{
	if (e->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* mouseEvent = (QMouseEvent*)e;

		QWidget *child = childAt(mouseEvent->pos());
		if (!child)
		{
			return QWidget::eventFilter(target, e);
		}
		else if (child->parentWidget()->objectName() == "widget_5")
		{
			isMove = false;
			if (m_pCurWin != NULL) {
				m_pCurWin->showFrame(false);
			}
			m_pCurWin = (vPrevWindow *)child->parentWidget()->parentWidget();
			m_pCurWin->showFrame(true);

			// 			QSettings settings(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
			// 			settings.setValue("Preview/currentIndex", m_pCurWin->m_iIndex);

			m_pPressWin = (vPrevWindow *)child->parentWidget()->parentWidget();
		}
	}
	else if (e->type() == QEvent::MouseMove)
	{
		isMove = true;
	}
	else if (e->type() == QEvent::MouseButtonRelease)
	{
		QMouseEvent* mouseEvent = (QMouseEvent*)e;

		QWidget *child = childAt(mouseEvent->pos());
		if (!child)
		{
			return QWidget::eventFilter(target, e);
		}
		else if (child->parentWidget()->objectName() == "widget_5")
		{
			m_pReleaseWin = (vPrevWindow *)child->parentWidget()->parentWidget();
			if (m_pPressWin != NULL && m_pPressWin != m_pReleaseWin && m_pReleaseWin != NULL && isMove)
			{
				switchWin(m_pPressWin, m_pReleaseWin);
				m_pPressWin = NULL;
				m_pReleaseWin = NULL;
			}
		}
		else if (child->objectName() == "widget_Ctrl_Logo")
		{
			m_pReleaseWin = (vPrevWindow *)child->parentWidget()->parentWidget()->parentWidget();
			if (m_pPressWin != NULL && m_pPressWin != m_pReleaseWin && m_pReleaseWin != NULL && isMove)
			{
				switchWin(m_pPressWin, m_pReleaseWin);
				m_pPressWin = NULL;
				m_pReleaseWin = NULL;
			}
		}
	}
	return QWidget::eventFilter(target, e);
}