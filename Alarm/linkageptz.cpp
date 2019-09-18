#include "linkageptz.h"
#include "ui_linkageptz.h"
#include "QMouseEvent"
#include "QMessageBox"
#include "addlinkagerule.h"

LinkagePTZ::LinkagePTZ(QPoint point, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::LinkagePTZ)
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
	connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(btnCancel_clicked()));//取消事件
	connect(CMSTreeView::sta_m_pCMSTreeItemModel, SIGNAL(CMSTreeChanged(TreeChangeType, CMS_CONNECT_PARSE_Node*)), this, SLOT(onTreeChanged(TreeChangeType, CMS_CONNECT_PARSE_Node*)));

	//添加预置点,巡航数据
	ui->rbPreset->setChecked(true);
	for (int i = 0; i < 255; i++)
	{
		ui->cbPreset->addItem(QString("%1").arg(i + 1));
		ui->cbCruise->addItem(QString("%1").arg(i + 1));
	}
	ui->cbPreset->setCurrentIndex(0);
	ui->cbCruise->setCurrentIndex(0);

	//设置列表表头和宽度
	ui->tableWidget->setColumnCount(2);
	QStringList headerList;
	headerList << tr("CHANNEL") << tr("OPERATION");
	ui->tableWidget->setHorizontalHeaderLabels(headerList);
	ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使列完全填充并平分
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
}

LinkagePTZ::~LinkagePTZ()
{
    delete ui;
}

//新添加设备树的时候过滤告警输入节点
void LinkagePTZ::onTreeChanged(TreeChangeType type, CMS_CONNECT_PARSE_Node*)
{
	if (type == CT_AddDevice)
	{
		m_cmsDeviceTree->update();
	}
}

//添加预置点,巡航设定
void LinkagePTZ::btnAdd_clicked()
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

	QString strOperate = "";
	if (ui->rbPreset->isChecked())
	{
		info.ptzType = LinkagePtzType_GotoPreset;//预置点
		strOperate += tr("Goto Preset");
		int iIndex = ui->cbPreset->currentIndex() + 1;//预置点下拉列表索引
		info.ptzIndex = iIndex;
		strOperate += QString("%1").arg(iIndex);
	}
	else
	{
		info.ptzType = LinkagePtzType_RunCruise;//巡航
		strOperate += tr("Run Cruise");
		int iIndex = ui->cbCruise->currentIndex() + 1;//巡航下拉列表索引
		info.ptzIndex = iIndex;
		strOperate += QString("%1").arg(iIndex);
	}

	LinkageInfo.channelList.append(info);
	int iRow = ui->tableWidget->rowCount();
	ui->tableWidget->insertRow(iRow);//添加到列表中
	ui->tableWidget->setItem(iRow, 0, new QTableWidgetItem(strName));//通道名称
	ui->tableWidget->setItem(iRow, 1, new QTableWidgetItem(strOperate));//预置点,巡航
}

//删除预置点,巡航设定
void LinkagePTZ::btnDelete_clicked()
{
	QList<QTableWidgetItem *> items = ui->tableWidget->selectedItems();
	if (items.count() == 0)
	{
		//insertEvent(tr("Select a record"));
		return;
	}
	int iRow = ui->tableWidget->row(items[0]);//获取选中行号
	ui->tableWidget->removeRow(iRow);//删除TABLE中显示的数据
	LinkageInfo.channelList.removeAt(iRow);//删除通道列表对应项
}

//确认按钮
void LinkagePTZ::btnOK_clicked()
{
	if (LinkageInfo.channelList.size() > MAX_LINKAGEACTION_PARAM_COUNT) {
		//insertEvent(tr("Up to 8 channels can only be linked!"));
		return;
	}
	accept();
}
//点击窗口取消按钮
void LinkagePTZ::btnCancel_clicked()
{
	reject();
}
//最小化
void LinkagePTZ::ShowMini()
{
	this->showMinimized();
}
//关闭
void LinkagePTZ::FrmClose()
{
	this->close();
}
//添加背景图片
void LinkagePTZ::resizeEvent(QResizeEvent *e)
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
void LinkagePTZ::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragPosition = QPoint(-1, -1);
		event->accept();
	}
}
//鼠标按下
void LinkagePTZ::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragPosition = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
}
//鼠标拖动
void LinkagePTZ::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() &Qt::LeftButton)
	{
		if (dragPosition != QPoint(-1, -1))
			move(event->globalPos() - dragPosition);
		event->accept();
	}
}