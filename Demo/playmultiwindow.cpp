#include "playmultiwindow.h"
#include "ui_playmultiwindow.h"
#include "mainwindow.h"

playmultiwindow::playmultiwindow(int winCout, int type)
	: m_iWinCount(winCout)
	, m_iType(type)
{
}

playmultiwindow::~playmultiwindow()
{
    delete ui;
}

void playmultiwindow::setUi(int count, int type)
{
	for (int i = 0; i < 4; i++)
	{
		m_pFrame[i] = new playframe(0, i, m_iType);	
		m_pFrame[i]->setObjectName(QString("%1").arg(i));
		connect(m_pFrame[i], SIGNAL(sigCloseWin(int)), this, SLOT(onFrameClose(int)));
	}

	int tmp = sqrt((float)4);
	for (int i = 0; i < tmp; i++)
	{
		for (int j = 0; j < tmp; j++)
		{
			//ui->gridLayout->addWidget(m_pFrame[i*tmp + j], i, j);
		}
	}
	m_iCurFocusIndex = 0;
	m_iCurWinCount = count;
}

void playmultiwindow::addOtherWindow()
{
	//分屏
	for (int i = 4; i < m_iWinCount; i++)
	{
		m_pFrame[i] = new playframe(0, i, m_iType);
		m_pFrame[i]->setObjectName(QString("%1").arg(i));
		connect(m_pFrame[i], SIGNAL(sigCloseWin(int)), this, SLOT(onFrameClose(int)));
	}
	onLayoutWindow(4);

}

void playmultiwindow::onFrameClose(int winId)
{
	sigFrameClose(winId);
}

void playmultiwindow::hideWindow()
{
	//this->hide();
	for (int i = 0; i < m_iCurWinCount; i++)
	{
//		ui->gridLayout->removeWidget(m_pFrame[i]);
		//m_pFrame[i]->hide();
		m_pFrame[i]->setGeometry(0, 0, 0, 0);
	}
	//update();
}


void playmultiwindow::onLayoutWindow(int winCount)
{

	if (winCount == m_iCurWinCount && !m_isMax)
	{
		return;
	}

	hideWindow();

	int iUnit = sqrt((float)winCount);
	for (int i = 0; i < iUnit; i++) {
		for (int j = 0; j < iUnit; j++) {
//			ui->gridLayout->addWidget(m_pFrame[i * iUnit + j], i, j);
		}
	}
	//this->show();
	m_iCurWinCount = winCount;

}

void playmultiwindow::startRender(int index)
{
	m_pFrame[index]->startRender();
	//	ui.label_title->setText(m_pFrame[m_iCurFocusIndex]->getChannelName());
}

void playmultiwindow::mousePressEvent(QMouseEvent *mE)
{

	QWidget *widget = this->childAt(mE->pos());
	if (widget == NULL)
	{
		return QWidget::mousePressEvent(mE);;
	}

	QString strObjectName = widget->objectName();
	playframe *pPlayFrame = NULL;
	if (strObjectName == "widgetVedioArea")
	{
		pPlayFrame = (playframe *)widget->parentWidget();

	}
	else if (strObjectName == "label")
	{
		pPlayFrame = (playframe *)widget->parentWidget()->parentWidget();
	}

	if (pPlayFrame != NULL)
	{
		int curFocus = pPlayFrame->objectName().toInt();
		setFocusWin(curFocus);
	}
	return QWidget::mousePressEvent(mE);
}

void playmultiwindow::setFocusWin(int curFocus)
{
// 	if (curFocus != m_iCurFocusIndex)
// 	{
// 		m_pFrame[m_iCurFocusIndex]->showBorder(false);
// 		m_pFrame[curFocus]->showBorder(true);
// 		if (m_bPlaySound)//如果声音开关开启
// 		{
// 			m_pFrame[m_iCurFocusIndex]->stopSound();
// 			m_pFrame[curFocus]->openSound();
// 		}
		int oldFocus = m_iCurFocusIndex;
		m_iCurFocusIndex = curFocus;
		//sigFocusWndChange(oldFocus, m_iCurFocusIndex);
		//ui.label_title->setText(m_pFrame[m_iCurFocusIndex]->getChannelName());
		//update();
	
}

void playmultiwindow::setFrameName(int index, QString deviceName, int channelNo)
{
	return m_pFrame[index]->setChannelName(deviceName, channelNo);
}
