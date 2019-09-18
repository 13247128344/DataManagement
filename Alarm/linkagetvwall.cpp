#include "linkagetvwall.h"
#include "ui_linkagetvwall.h"
#include "QMouseEvent"
#include "QMessageBox"
#include "./include/CMSTreeView.h"

LinkageTVWall::LinkageTVWall(QPoint point, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::LinkageTVWall)
{
    ui->setupUi(this);
	this->setGeometry(point.x(), point.y(), this->width(), this->height());
	setWindowIcon(QIcon("./Resources/logo_1.png"));
	setAttribute(Qt::WA_TranslucentBackground, true);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint
		| Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint
		| Qt::WindowMaximizeButtonHint);
	connect(ui->btn_minimum, SIGNAL(clicked()), this, SLOT(ShowMini()));//最小化
	connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(FrmClose()));//关闭
	ui->btn_minimum->setCursor(Qt::PointingHandCursor);
	ui->btn_close->setCursor(Qt::PointingHandCursor);
	ui->btnOK->setCursor(Qt::PointingHandCursor);
	ui->btnCancel->setCursor(Qt::PointingHandCursor);
	ui->btnAdd->setCursor(Qt::PointingHandCursor);
	ui->btnDelete->setCursor(Qt::PointingHandCursor);
	//设备树
	m_cmsDeviceTree = new CMSTreeView(this, CMSTreeView::PLAYBACK, CMSTreeView::RADIO, CMSTreeView::ORIGIN, CMSTreeView::CH);
	m_cmsDeviceTree->expandAll();
	m_cmsDeviceTree->setHeaderHidden(true);
	ui->verticalLayout->addWidget(m_cmsDeviceTree);

	connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(btnAdd_clicked()));//添加事件
	connect(ui->btnDelete, SIGNAL(clicked()), this, SLOT(btnDelete_clicked()));//删除事件
	connect(ui->btnOK, SIGNAL(clicked()), this, SLOT(btnOK_clicked()));//确认事件
	connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(btnCancel_clicked()));//关闭窗口
	connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(onCheckBox_stateChanged(int)));//自动分配解码器,勾选则禁用解码器树
	connect(CMSTreeView::sta_m_pCMSTreeItemModel, SIGNAL(CMSTreeChanged(TreeChangeType, CMS_CONNECT_PARSE_Node*)), this, SLOT(onTreeChanged(TreeChangeType, CMS_CONNECT_PARSE_Node*)));

	ui->rbAuto->setChecked(true);
	ui->checkBox->hide();

	ui->tableWidget->setColumnCount(2);
	QStringList headerList;
	headerList << tr("CHANNEL") << tr("DECODER");
	ui->tableWidget->setHorizontalHeaderLabels(headerList);
	ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使列完全填充并平分
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
}

LinkageTVWall::~LinkageTVWall()
{
    delete ui;
}

//新添加设备树的时候过滤告警输入节点
void LinkageTVWall::onTreeChanged(TreeChangeType type, CMS_CONNECT_PARSE_Node*)
{
	if (type == CT_AddDevice)
	{
		m_cmsDeviceTree->update();
	}
}

void LinkageTVWall::onCheckBox_stateChanged(int state)
{

}
////添加设备,解码器
void LinkageTVWall::btnAdd_clicked()
{
	CMS_CONNECT_PARSE_Node *pSelectedItem = NULL;
	if (0 < m_cmsDeviceTree->m_listCheckedIndex.size())
		pSelectedItem = m_cmsDeviceTree->getNodebyModelIndex(m_cmsDeviceTree->m_listCheckedIndex[0]);
	if (NULL == pSelectedItem || NodeType_Channel != pSelectedItem->eNodeType)
	{
		//insertEvent(tr("Select a Channel"));
		return;
	}
	AddLinkageRule::ChInfo info;
	info.strDeviceNumber = QString(((CMS_CONNECT_PARSE_ChannelNode *)pSelectedItem)->cSerialNum);//设备ID
	info.iChannel = ((CMS_CONNECT_PARSE_ChannelNode *)pSelectedItem)->iChannelNo;
	QString strName = "DEVICES-" + QString(pSelectedItem->parent->cNodeName) + "-" + QString(pSelectedItem->cNodeName);//通道全名称


	int iRow = ui->tableWidget->rowCount();
	ui->tableWidget->insertRow(iRow);
	ui->tableWidget->setItem(iRow, 0, new QTableWidgetItem(strName));

	LinkageInfo.channelList.append(info);
}

void LinkageTVWall::btnOK_clicked()
{
	if (ui->rbAuto->isChecked())
		LinkageInfo.iStopMode = -1;
	else if (ui->rbTime->isChecked())
		LinkageInfo.iStopMode = ui->spinBox->value();
	if (LinkageInfo.channelList.size() > MAX_LINKAGEACTION_PARAM_COUNT) {
		//insertEvent(tr("Up to 8 channels can only be linked!"));
		return;
	}
	accept();
}

////删除设备,解码器
void LinkageTVWall::btnDelete_clicked()
{
	QList<QTableWidgetItem *> items = ui->tableWidget->selectedItems();
	if (items.count() == 0)
	{
		//insertEvent(tr("Select a record"));
		return;
	}
	int iRow = ui->tableWidget->row(items[0]);//获取列
	ui->tableWidget->removeRow(iRow);//删除列表数据
	LinkageInfo.channelList.removeAt(iRow);//删除通道
}

void LinkageTVWall::btnCancel_clicked()
{
	reject();
}
//最小化
void LinkageTVWall::ShowMini()
{
	this->showMinimized();
}
//关闭
void LinkageTVWall::FrmClose()
{
	this->close();
}
//添加背景图片
void LinkageTVWall::resizeEvent(QResizeEvent *e)
{
	ui->widget_2->setAutoFillBackground(true);
	QPixmap *mBackPic1 = new QPixmap("./Resources/top.png");
	QPalette palette1;
	palette1.setBrush(QPalette::Background, QBrush((mBackPic1->scaled(ui->widget_2->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))));
	ui->widget_2->setPalette(palette1);

	ui->widget->setAutoFillBackground(true);
	QPixmap *mBackPic2 = new QPixmap("./Resources/mid.png");
	QPalette palette2;
	palette2.setBrush(QPalette::Background, QBrush((mBackPic2->scaled(ui->widget->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))));
	ui->widget->setPalette(palette2);

	ui->widget_3->setAutoFillBackground(true);
	QPixmap *mBackPic3 = new QPixmap("./Resources/bottom.png");
	QPalette palette3;
	palette3.setBrush(QPalette::Background, QBrush((mBackPic3->scaled(ui->widget_3->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))));
	ui->widget_3->setPalette(palette3);
}

/************************************************************************/
/* 鼠标拖动窗口                                                         */
/************************************************************************/
//鼠标释放
void LinkageTVWall::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragPosition = QPoint(-1, -1);
		event->accept();
	}
}
//鼠标按下
void LinkageTVWall::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragPosition = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
}
//鼠标拖动
void LinkageTVWall::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() &Qt::LeftButton)
	{
		if (dragPosition != QPoint(-1, -1))
			move(event->globalPos() - dragPosition);
		event->accept();
	}
}