#include "linkageprevrec.h"
#include "ui_linkageprevrec.h"
#include "QMouseEvent"
#include "QMessageBox"
#include "./include/ivms_public.h"

#define CHILD_MAP			1
#define CHANNEL_MAP			2
#define ALARM_IN_MAP		3
#define ALARM_OUT_MAP		4

LinkagePrevRec::LinkagePrevRec(QPoint point,LinkageActionType type, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::LinkagePrevRec)
{
    ui->setupUi(this);
	this->setGeometry(point.x(), point.y(), this->width(), this->height());
// 	if (type == LinkageActionType_Map)
// 		ui->label_2->setText(tr("MAP"));
// 	else if (type == LinkageActionType_PopImage)
// 		ui->label_2->setText(tr("PREVIEW"));
// 	else if (type == LinkageActionType_Record)
// 		ui->label_2->setText(tr("RECORD"));
// 	else if (type == LinkageActionType_Capture)
// 		ui->label_2->setText(tr("CAPTURE"));
	setWindowIcon(QIcon("./Resources/logo_1.png"));
	setAttribute(Qt::WA_TranslucentBackground, true);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint
		| Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint
		| Qt::WindowMaximizeButtonHint);
	ui->btn_minimum->setCursor(Qt::PointingHandCursor);
	ui->btn_close->setCursor(Qt::PointingHandCursor);
	ui->btnOK->setCursor(Qt::PointingHandCursor);
	ui->btnCancel->setCursor(Qt::PointingHandCursor);
	connect(ui->btn_minimum, SIGNAL(clicked()), this, SLOT(ShowMini()));//最小化
	connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(FrmClose()));//关闭
	connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(btnCancel_clicked()));//关闭窗口
	connect(ui->btnOK, SIGNAL(clicked()), this, SLOT(btnOK_clicked()));
	//设备树
	m_cmsDeviceTree = new CMSTreeView(this, CMSTreeView::PREVIEW, CMSTreeView::MULTI, CMSTreeView::ORIGIN, CMSTreeView::CH);
	m_cmsDeviceTree->expandAll();
	m_cmsDeviceTree->setHeaderHidden(true);
	ui->verticalLayout->addWidget(m_cmsDeviceTree);
	ui->rbAuto->setChecked(true);//选中自动停止模式
	connect(CMSTreeView::sta_m_pCMSTreeItemModel, SIGNAL(CMSTreeChanged(TreeChangeType, CMS_CONNECT_PARSE_Node*)), this, SLOT(onTreeChanged(TreeChangeType, CMS_CONNECT_PARSE_Node*)));
}


LinkagePrevRec::~LinkagePrevRec()
{
    delete ui;
}

//新添加设备树的时候过滤告警输入节点
void LinkagePrevRec::onTreeChanged(TreeChangeType type, CMS_CONNECT_PARSE_Node*)
{
	if (type == CT_AddDevice)
	{
		m_cmsDeviceTree->update();
	}
}

void LinkagePrevRec::hideModeSet()
{
	ui->widget_4->setVisible(false);
}

//确定按钮事件
void LinkagePrevRec::btnOK_clicked()
{
	LinkageInfo.channelList.clear();
	if (0<m_cmsDeviceTree->m_listCheckedIndex.size())
	{
		for (int i = 0; i<m_cmsDeviceTree->m_listCheckedIndex.size(); i++)
		{
			CMS_CONNECT_PARSE_Node* m_cmsSelectedItem = m_cmsDeviceTree->getNodebyModelIndex(m_cmsDeviceTree->m_listCheckedIndex[i]);
			if (m_cmsSelectedItem->eNodeType == NodeType_Channel)
			{
				AddLinkageRule::ChInfo info;
				info.strDeviceNumber = QString(((CMS_CONNECT_PARSE_ChannelNode *)m_cmsSelectedItem)->cSerialNum);//设备ID
				info.iChType = CHANNEL_MAP;
				info.iChannel = ((CMS_CONNECT_PARSE_ChannelNode *)m_cmsSelectedItem)->iChannelNo;
				//info.strName="DEVICES-"+QString(m_cmsSelectedItem->parent->cNodeName)+"-"+QString(m_cmsSelectedItem->cNodeName);//通道全名称
				LinkageInfo.channelList.append(info);
			}
			else if (m_cmsSelectedItem->eNodeType == NodeType_AlarmIn)
			{
				AddLinkageRule::ChInfo info;
				info.strDeviceNumber = QString(((CMS_CONNECT_PARSE_ChannelNode *)m_cmsSelectedItem)->cSerialNum);//设备ID
				info.iChType = ALARM_IN_MAP;
				info.iChannel = ((CMS_CONNECT_PARSE_ChannelNode *)m_cmsSelectedItem)->iChannelNo;
				//info.strName="DEVICES-"+QString(m_cmsSelectedItem->parent->cNodeName)+"-"+QString(m_cmsSelectedItem->cNodeName);//通道全名称
				LinkageInfo.channelList.append(info);
			}
			/*else if (m_cmsSelectedItem->eNodeType == NodeType_AlarmOut)
			{
			AddLinkageRule::ChInfo info;
			info.strDeviceNumber=QString(((CMS_CONNECT_PARSE_ChannelNode *)m_cmsSelectedItem)->cSerialNum);//设备ID
			info.iChType = ALARM_OUT_MAP;
			info.iChannel=((CMS_CONNECT_PARSE_ChannelNode *)m_cmsSelectedItem)->iChannelNo;
			//info.strName="DEVICES-"+QString(m_cmsSelectedItem->parent->cNodeName)+"-"+QString(m_cmsSelectedItem->cNodeName);//通道全名称
			LinkageInfo.channelList.append(info);
			}*/
		}
	}
	if (LinkageInfo.channelList.size() > MAX_LINKAGEACTION_PARAM_COUNT)
	{
		//insertEvent(tr("Up to 8 channels can only be linked!"));
		return;
	}
	//告警停止模式
	if (ui->rbAuto->isChecked())
		LinkageInfo.iStopMode = -1;
	else if (ui->rbTime->isChecked())
		LinkageInfo.iStopMode = ui->spinBox->value();
	accept();
}

//点击窗口取消按钮
void LinkagePrevRec::btnCancel_clicked()
{
	reject();
}
//最小化
void LinkagePrevRec::ShowMini()
{
	this->showMinimized();
}
//关闭
void LinkagePrevRec::FrmClose()
{
	this->close();
}
//添加背景图片
void LinkagePrevRec::resizeEvent(QResizeEvent *e)
{
	ui->widget_2->setAutoFillBackground(true);
	QPixmap *mBackPic1 = new QPixmap("./Resources/top.png");
	QPalette palette1;
	palette1.setBrush(QPalette::Background, QBrush((mBackPic1->scaled(ui->widget_2->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))));
	ui->widget_2->setPalette(palette1);

	ui->widget_5->setAutoFillBackground(true);
	QPixmap *mBackPic2 = new QPixmap("./Resources/mid.png");
	QPalette palette2;
	palette2.setBrush(QPalette::Background, QBrush((mBackPic2->scaled(ui->widget_5->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))));
	ui->widget_5->setPalette(palette2);

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
void LinkagePrevRec::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragPosition = QPoint(-1, -1);
		event->accept();
	}
}
//鼠标按下
void LinkagePrevRec::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragPosition = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
}
//鼠标拖动
void LinkagePrevRec::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() &Qt::LeftButton)
	{
		if (dragPosition != QPoint(-1, -1))
			move(event->globalPos() - dragPosition);
		event->accept();
	}
}