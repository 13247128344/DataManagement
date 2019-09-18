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
	connect(ui->btn_minimum, SIGNAL(clicked()), this, SLOT(ShowMini()));//��С��
	connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(FrmClose()));//�ر�
	ui->btn_minimum->setCursor(Qt::PointingHandCursor);
	ui->btn_close->setCursor(Qt::PointingHandCursor);
	ui->btnOK->setCursor(Qt::PointingHandCursor);
	ui->btnCancel->setCursor(Qt::PointingHandCursor);
	ui->btnAdd->setCursor(Qt::PointingHandCursor);
	ui->btnDelete->setCursor(Qt::PointingHandCursor);
	//�豸��
	m_cmsDeviceTree = new CMSTreeView(this, CMSTreeView::PLAYBACK, CMSTreeView::RADIO, CMSTreeView::ORIGIN, CMSTreeView::CH);
	m_cmsDeviceTree->expandAll();
	m_cmsDeviceTree->setHeaderHidden(true);
	ui->verticalLayout->addWidget(m_cmsDeviceTree);

	connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(btnAdd_clicked()));//�����¼�
	connect(ui->btnDelete, SIGNAL(clicked()), this, SLOT(btnDelete_clicked()));//ɾ���¼�
	connect(ui->btnOK, SIGNAL(clicked()), this, SLOT(btnOK_clicked()));//ȷ���¼�
	connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(btnCancel_clicked()));//�رմ���
	connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(onCheckBox_stateChanged(int)));//�Զ����������,��ѡ����ý�������
	connect(CMSTreeView::sta_m_pCMSTreeItemModel, SIGNAL(CMSTreeChanged(TreeChangeType, CMS_CONNECT_PARSE_Node*)), this, SLOT(onTreeChanged(TreeChangeType, CMS_CONNECT_PARSE_Node*)));

	ui->rbAuto->setChecked(true);
	ui->checkBox->hide();

	ui->tableWidget->setColumnCount(2);
	QStringList headerList;
	headerList << tr("CHANNEL") << tr("DECODER");
	ui->tableWidget->setHorizontalHeaderLabels(headerList);
	ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//ʹ����ȫ��䲢ƽ��
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//ֻ��
}

LinkageTVWall::~LinkageTVWall()
{
    delete ui;
}

//�������豸����ʱ����˸澯����ڵ�
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
////�����豸,������
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
	info.strDeviceNumber = QString(((CMS_CONNECT_PARSE_ChannelNode *)pSelectedItem)->cSerialNum);//�豸ID
	info.iChannel = ((CMS_CONNECT_PARSE_ChannelNode *)pSelectedItem)->iChannelNo;
	QString strName = "DEVICES-" + QString(pSelectedItem->parent->cNodeName) + "-" + QString(pSelectedItem->cNodeName);//ͨ��ȫ����


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

////ɾ���豸,������
void LinkageTVWall::btnDelete_clicked()
{
	QList<QTableWidgetItem *> items = ui->tableWidget->selectedItems();
	if (items.count() == 0)
	{
		//insertEvent(tr("Select a record"));
		return;
	}
	int iRow = ui->tableWidget->row(items[0]);//��ȡ��
	ui->tableWidget->removeRow(iRow);//ɾ���б�����
	LinkageInfo.channelList.removeAt(iRow);//ɾ��ͨ��
}

void LinkageTVWall::btnCancel_clicked()
{
	reject();
}
//��С��
void LinkageTVWall::ShowMini()
{
	this->showMinimized();
}
//�ر�
void LinkageTVWall::FrmClose()
{
	this->close();
}
//���ӱ���ͼƬ
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
/* ����϶�����                                                         */
/************************************************************************/
//����ͷ�
void LinkageTVWall::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragPosition = QPoint(-1, -1);
		event->accept();
	}
}
//��갴��
void LinkageTVWall::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragPosition = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
}
//����϶�
void LinkageTVWall::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() &Qt::LeftButton)
	{
		if (dragPosition != QPoint(-1, -1))
			move(event->globalPos() - dragPosition);
		event->accept();
	}
}