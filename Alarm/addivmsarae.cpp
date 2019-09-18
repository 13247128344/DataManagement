#include "addivmsarae.h"
#include "ui_addivmsarae.h"

AddIVMSArae::AddIVMSArae(QWidget *parent) 
    :QWidget(parent)
    ,ui(new Ui::AddIVMSArae)
{
    ui->setupUi(this);
	setWindowIcon(QIcon("./Resources/logo_1.png"));
	//setAttribute(Qt::WA_TranslucentBackground, true);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint
		| Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint
		| Qt::WindowMaximizeButtonHint);
	// 	m_pCMSTreeView = new CMSTreeView(this, CMSTreeView::PLAYBACK, CMSTreeView::RADIO, CMSTreeView::ORIGIN, CMSTreeView::CH);
	// 	m_pCMSTreeView->setHeaderHidden(true);
	// 	m_pCMSTreeView->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
	// 	ui.verticalLayout_2->addWidget(m_pCMSTreeView);
}

AddIVMSArae::~AddIVMSArae()
{
    delete ui;
}

void AddIVMSArae::resizeEvent(QResizeEvent *event)
{
	this->setAutoFillBackground(true);
	QPalette palette;
#ifdef ZKTECO
	palette.setBrush(QPalette::Background, QBrush(QColor(232, 235, 237)));
#else
	palette.setBrush(QPalette::Background, QBrush(QColor(42, 43, 48)));
#endif
	this->setPalette(palette);
}

void AddIVMSArae::on_btn_cancel_clicked()
{
	this->hide();
}

void AddIVMSArae::on_btn_confirm_clicked()
{
	/*
	if (m_iType == 0)
	{
		m_pRecDownLoad->m_cmsSelectedItem = NULL;
		if (0 < m_pCMSTreeView->m_listCheckedIndex.size())
		{
			for (int i = 0; i < m_pCMSTreeView->m_listCheckedIndex.size(); i++)
			{
				if (m_pCMSTreeView->getNodebyModelIndex(m_pCMSTreeView->m_listCheckedIndex[i])->eNodeType == NodeType_Channel)
				{
					m_pRecDownLoad->m_cmsSelectedItem = m_pCMSTreeView->getNodebyModelIndex(m_pCMSTreeView->m_listCheckedIndex[i]);
					break;
				}
			}
		}
		if (NULL != m_pRecDownLoad->m_cmsSelectedItem)
		{
			QString strChFullName = QString(tr("DEVICE-")) + QString(m_pRecDownLoad->m_cmsSelectedItem->parent->cNodeName)
				+ QString("-") + QString(((CMS_CONNECT_PARSE_ChannelNode*)m_pRecDownLoad->m_cmsSelectedItem)->cNodeName);
			QString strFilePath;
			m_pRecDownLoad->ui.lineEditCh->setText(strChFullName);
			if (LOCATION_DEVICE == m_pRecDownLoad->m_iRecordLocation)
			{
				strFilePath = _struLocalCfg.strDownloadPath + "\\" + strChFullName.trimmed() + "\\device\\";
			}
			else if (LOCATION_STORAGE == m_pRecDownLoad->m_iRecordLocation)
			{
				strFilePath = _struLocalCfg.strDownloadPath + "\\" + strChFullName.trimmed() + "\\storage\\";
			}
			m_pRecDownLoad->ui.lineEditSavePath->setText(strFilePath);
		}
	}
	else if (m_iType == 1)
	{
		m_pAddLinkageRule->m_pSelectedItem = NULL;
		for (int i = 0; i < m_pCMSTreeView->m_listCheckedIndex.size(); i++) {
			if (m_pCMSTreeView->getNodebyModelIndex(m_pCMSTreeView->m_listCheckedIndex[i])->eNodeType == NodeType_AlarmIn ||
				m_pCMSTreeView->getNodebyModelIndex(m_pCMSTreeView->m_listCheckedIndex[i])->eNodeType == NodeType_Channel)
			{
				m_pAddLinkageRule->m_pSelectedItem = m_pCMSTreeView->getNodebyModelIndex(m_pCMSTreeView->m_listCheckedIndex[i]);
				break;
			}
		}
		if (NULL != m_pAddLinkageRule->m_pSelectedItem)
		{
			QString strChFullName = "DEVICES-" + QString(m_pAddLinkageRule->m_pSelectedItem->parent->cNodeName) + "-" + QString(m_pAddLinkageRule->m_pSelectedItem->cNodeName);//通道全名称
			m_pAddLinkageRule->ui.lineEdit_alarmSource->setText(strChFullName);
			if (m_pAddLinkageRule->m_pSelectedItem->eNodeType == NodeType_AlarmIn)
			{
				strcpy(m_pAddLinkageRule->m_pRuleParam.cSerialNum, ((CMS_CONNECT_PARSE_AlarmInNode *)m_pAddLinkageRule->m_pSelectedItem)->cSerialNum);
				m_pAddLinkageRule->m_pRuleParam.iParam = ((CMS_CONNECT_PARSE_AlarmInNode *)m_pAddLinkageRule->m_pSelectedItem)->iAlarmInNo;
			}
			else {
				strcpy(m_pAddLinkageRule->m_pRuleParam.cSerialNum, ((CMS_CONNECT_PARSE_ChannelNode *)m_pAddLinkageRule->m_pSelectedItem)->cSerialNum);
				m_pAddLinkageRule->m_pRuleParam.iParam = ((CMS_CONNECT_PARSE_ChannelNode *)m_pAddLinkageRule->m_pSelectedItem)->iChannelNo;
			}
		}
	}
	else if (m_iType == 2)
	{
		QString strSerialNum;
		QString strAccessName;
		for (int i = 0; i < m_pListWidget->count(); i++)
		{
			auto pItem = m_pListWidget->item(i);

			if (pItem != NULL && pItem->checkState())
			{
				strSerialNum = pItem->data(Qt::UserRole).value<QString>();
				strAccessName = pItem->text();
			}
		}

		if ("" != strSerialNum)
		{
			QString strChFullName = QString(strAccessName);//通道全名称
			m_pAddAccessLinkageRule->ui.lineEdit_alarmSource->setText(strChFullName);
			strcpy(m_pAddAccessLinkageRule->m_pRuleParam.cSerialNum, strSerialNum.toUtf8().data());
			m_pAddAccessLinkageRule->m_pRuleParam.iParam = 0;
		}

	}
	this->hide();
	*/
}