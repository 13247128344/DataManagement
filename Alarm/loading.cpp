#include "loading.h"
#include "ui_loading.h"
#include <QRadialGradient>
#include <QFile>
#include <QBitmap>
#include <qtimer.h>
#include <qmovie.h>
#include "qpainter.h"
#include "alarmcfg.h"

Loading::Loading(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
	setWindowIcon(QIcon("./Resources/logo_1.png"));
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint
		| Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint
		| Qt::WindowMaximizeButtonHint | Qt::WindowStaysOnTopHint);
	movie = new QMovie("./Resources/loading.gif");
	ui->label_2->setMovie(movie);
	movie->start();

	m_iFrameCount = 0;
	//新建一个QTimer对象  
	QTimer* timer = new QTimer();
	//设置定时器每个多少毫秒发送一个timeout()信号  
	timer->setInterval(1000 / 60);
	//启动定时器  
	timer->start();

	connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
	ui->label_progress->setVisible(false);
}

Loading::~Loading()
{
    delete ui;
}

void Loading::startLoading()
{
	this->setParent(NULL);
	movie->start();
	this->setModal(true);
// 	if (_pMainDlg != NULL)
// 	{
// 		move(_pMainDlg->x() + (_pMainDlg->width() - this->width()) / 2, _pMainDlg->y() + (_pMainDlg->height() - this->height()) / 2);
// 		this->resize(206, 130);
// 	}
	// 	if (parent() != NULL)
	// 	{
	// 		if (parent()->isWidgetType())
	// 		{
	// 			QWidget *pWidget = (QWidget*)parent();
	// 			this->resize(pWidget->size());
	// 			this->move(0, 0);
	// 		}
	// 	}

	m_iFrameCount = 0;
	this->show();
}

void Loading::setText(QString text)
{
	ui->label->setText(text);
}

void Loading::setHidden()
{
	movie->stop();
	this->setParent(NULL);
	this->close();
}


void Loading::closeEvent(QCloseEvent *e)
{
	emit closeSignal();
}

//关闭
void Loading::FrmClose()
{
	this->close();
}
//添加背景图片
void Loading::resizeEvent(QResizeEvent *e)
{
	QPixmap *mBackPic1 = new QPixmap("./Resources/mid2.png");
	QPalette palette1;
	palette1.setBrush(QPalette::Background, QBrush((mBackPic1->scaled(this->size(), Qt::IgnoreAspectRatio, Qt::FastTransformation))));
	// 	palette1.setBrush(QPalette::Background, QBrush(QColor(0,0,0,0)));
	this->setPalette(palette1);

	QBitmap objBitmap(size());
	QPainter painter(&objBitmap);
	painter.fillRect(rect(), Qt::white);
	painter.setBrush(QColor(61, 61, 61));
	painter.drawRoundedRect(this->rect(), 20, 20);
	setMask(objBitmap);
}