#include "addaccesslinkagerule.h"
#include "ui_addaccesslinkagerule.h"
#include <QMouseEvent>
#include "linkageprevrec.h"
#include "linkageptz.h"
#include "linkagetvwall.h"
#include "./include/ivms_public.h"

long _lLoginHandle;
AddAccessLinkageRule::AddAccessLinkageRule(int ruleParam, QWidget *parent)
    :QDialog(parent)
    ,ui(new Ui::AddAccessLinkageRule)
{
    ui->setupUi(this);
	setWindowIcon(QIcon("./Resources/logo_1.png"));
	setAttribute(Qt::WA_TranslucentBackground, true);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint
		| Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint
		| Qt::WindowMaximizeButtonHint);
	connect(ui->btn_minimum, SIGNAL(clicked()), this, SLOT(ShowMini()));//��С��
	connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(FrmClose()));//�ر�
	ui->btn_minimum->setCursor(Qt::PointingHandCursor);
	ui->btn_close->setCursor(Qt::PointingHandCursor);
	ui->btnSelAlarmSource->setCursor(Qt::PointingHandCursor);
	ui->btnOK->setCursor(Qt::PointingHandCursor);
	ui->btnCancel->setCursor(Qt::PointingHandCursor);

	connect(ui->btnSelAlarmSource, SIGNAL(clicked()), this, SLOT(btnSelAlarmSource_clicked()));//ѡ�񱨾�Դ
	
	ui->textEdit_LinkagePara->setReadOnly(true);
	ui->rbOpenDoor->setChecked(true);

// 	if (_iUserType == UserType_Guest)
// 	{
// 		ui->cbPTZ->setVisible(false);
// 		ui->cbTVWall->setVisible(false);
// 	}
// 
// 	if (QString(ruleParam.cRuleName) != "")
// 	{
		//m_pRuleParam = ruleParam;
		ui->btnSelAlarmSource->setEnabled(false);
		ui->lineEdit_ruleName->setReadOnly(true);
		ui->lineEdit_alarmSource->setReadOnly(true);
		getUpdateSources();
	//}

	connect(ui->cbMap, SIGNAL(stateChanged(int)), this, SLOT(OnCbMapStateChanged(int)));//��ͼ
	connect(ui->cbTVWall, SIGNAL(stateChanged(int)), this, SLOT(OnCbTVWallStateChanged(int)));//����ǽ
	connect(ui->cbPreview, SIGNAL(stateChanged(int)), this, SLOT(OnCbPreviewStateChanged(int)));//��ͼ��
	connect(ui->cbRecord, SIGNAL(stateChanged(int)), this, SLOT(OnCbRecordStateChanged(int)));//¼��
	connect(ui->cbCapture, SIGNAL(stateChanged(int)), this, SLOT(OnCbCaptureStateChanged(int)));//ץͼ
	connect(ui->cbPTZ, SIGNAL(stateChanged(int)), this, SLOT(OnCbPTZStateChanged(int)));//��̨
	connect(ui->rbOpenDoor, SIGNAL(clicked()), this, SLOT(onRadioStateChanged()));//�����豸��
	connect(ui->rbTamper, SIGNAL(clicked()), this, SLOT(onRadioStateChanged()));
	connect(ui->rbStressPwd, SIGNAL(clicked()), this, SLOT(onRadioStateChanged()));
	connect(ui->rbStressFingerPrint, SIGNAL(clicked()), this, SLOT(onRadioStateChanged()));
	connect(ui->btnOK, SIGNAL(clicked()), this, SLOT(btnSave_clicked()));
	connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(btnCancel_clicked()));//�رմ���
	//connect(CMSTreeView::sta_m_pCMSTreeItemModel, SIGNAL(CMSTreeChanged(TreeChangeType, CMS_CONNECT_PARSE_Node*)), this, SLOT(onTreeChanged(TreeChangeType, CMS_CONNECT_PARSE_Node*)));
	//connect(AccessInfo::GetInstance(), SIGNAL(sigAccessStateChange(CMS_CONNECT_PARSE_NoticeType, QString)), this, SLOT(onAccessChange(CMS_CONNECT_PARSE_NoticeType, QString)));

	dragPosition = QPoint(-1, -1);
}

AddAccessLinkageRule::~AddAccessLinkageRule()
{
    delete ui;
}


//�����豸��
void AddAccessLinkageRule::onRadioStateChanged()
{
	
}
//ѡ��ͬ�������͵ı���Դ
void AddAccessLinkageRule::btnSelAlarmSource_clicked()
{
	
}

//��ʼ��Ҫ�޸ĵ�����
void AddAccessLinkageRule::getUpdateSources()
{
	
}

void AddAccessLinkageRule::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		dragPosition = e->globalPos() - frameGeometry().topLeft();
		e->accept();
	}
}

//���汨������
void AddAccessLinkageRule::btnSave_clicked()
{

}

void AddAccessLinkageRule::btnCancel_clicked()
{
	reject();
}

void AddAccessLinkageRule::OnCbMapStateChanged(int state)
{
	if (Qt::Checked == state)//��ѡʱ���ö���
	{
		QPoint pointCb = ui->cbMap->pos();
		pointCb.ry() = pointCb.ry() + ui->cbMap->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkagePrevRec dlg(point, ivms_LinkageActionType_Map, this);
		if (QDialog::Accepted == dlg.exec())//���ȷ����ť
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//ѭ����ӵ�ͼ����
				linkage_Map.channelList.append(dlg.LinkageInfo.channelList[i]);
			linkage_Map.iStopMode = dlg.LinkageInfo.iStopMode;//���õ�ͼ����ֹͣģʽ
		}
		else//���ȡ����ť,���õ�ͼѡ��δ��ѡ
		{
			ui->cbMap->setCheckState(Qt::Unchecked);
			return;
		}
	}
	else//�����ͼ�����б�
	{
		linkage_Map.channelList.clear();
	}
	refresh_ParaEdit();
}

//����ǽ
void AddAccessLinkageRule::OnCbTVWallStateChanged(int state)
{
	if (Qt::Checked == state)//��ѡʱ���ö���
	{
		QPoint pointCb = ui->cbTVWall->pos();
		pointCb.ry() = pointCb.ry() + ui->cbTVWall->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkageTVWall dlg(point, this);
		if (QDialog::Accepted == dlg.exec())//���ȷ����ť
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//ѭ����ӵ���ǽ����
			{
				linkage_TVWall.channelList.append(dlg.LinkageInfo.channelList[i]);
			}
			linkage_TVWall.iStopMode = dlg.LinkageInfo.iStopMode;//���õ���ǽ����ֹͣģʽ
		}
		else//���ȡ����ť,���õ���ǽѡ��δ��ѡ
		{
			ui->cbTVWall->setCheckState(Qt::Unchecked);
			return;
		}
	}
	else//�������ǽ�����б�
	{
		linkage_TVWall.channelList.clear();
	}
	refresh_ParaEdit();
}

//Ԥ��
void AddAccessLinkageRule::OnCbPreviewStateChanged(int state)
{
	if (Qt::Checked == state)
	{
		QPoint pointCb = ui->cbPreview->pos();
		pointCb.ry() = pointCb.ry() + ui->cbPreview->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkagePrevRec dlg(point, ivms_LinkageActionType_PopImage, this);
		if (QDialog::Accepted == dlg.exec())//���ȷ�ϰ�ť
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//ѭ����ȡץͼ����
				linkage_Prev.channelList.append(dlg.LinkageInfo.channelList[i]);
			linkage_Prev.iStopMode = dlg.LinkageInfo.iStopMode;
		}
		else//���ȡ����ť,����Ԥ��δ��ѡ
		{
			ui->cbPreview->setCheckState(Qt::Unchecked);
			return;
		}
	}
	else
	{
		linkage_Prev.channelList.clear();
	}
	refresh_ParaEdit();
}

//¼��
void AddAccessLinkageRule::OnCbRecordStateChanged(int state)
{
	if (Qt::Checked == state)
	{
		QPoint pointCb = ui->cbRecord->pos();
		pointCb.ry() = pointCb.ry() + ui->cbRecord->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkagePrevRec dlg(point, ivms_LinkageActionType_Record, this);
		dlg.hideModeSet();//����ֹͣģʽ
		if (QDialog::Accepted == dlg.exec())//���ȷ�ϰ�ť
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//ѭ����ȡץͼ����
				linkage_Record.channelList.append(dlg.LinkageInfo.channelList[i]);
			linkage_Record.iStopMode = dlg.LinkageInfo.iStopMode;
		}
		else//���ȡ����ť,����¼��δ��ѡ
		{
			ui->cbRecord->setCheckState(Qt::Unchecked);
			return;
		}
	}
	else
	{
		linkage_Record.channelList.clear();
	}
	refresh_ParaEdit();
}
//ץͼ
void AddAccessLinkageRule::OnCbCaptureStateChanged(int state)
{
	if (Qt::Checked == state)
	{
		QPoint pointCb = ui->cbCapture->pos();
		pointCb.ry() = pointCb.ry() + ui->cbCapture->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkagePrevRec dlg(point, ivms_LinkageActionType_Capture, this);
		dlg.hideModeSet();//����ֹͣģʽ
		if (QDialog::Accepted == dlg.exec())//���ȷ�ϰ�ť
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//ѭ����ȡץͼ����
				linkage_Capture.channelList.append(dlg.LinkageInfo.channelList[i]);
			linkage_Capture.iStopMode = dlg.LinkageInfo.iStopMode;
		}
		else//���ȡ����ť,����ץͼδ��ѡ
		{
			ui->cbCapture->setCheckState(Qt::Unchecked);
			return;
		}
	}
	else
	{
		linkage_Capture.channelList.clear();
	}
	refresh_ParaEdit();
}
//��̨
void AddAccessLinkageRule::OnCbPTZStateChanged(int state)
{
	if (Qt::Checked == state)//������̨����
	{
		QPoint pointCb = ui->cbPTZ->pos();
		pointCb.ry() = pointCb.ry() + ui->cbPTZ->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkagePTZ dlg(point, this);
		if (QDialog::Accepted == dlg.exec())//���ȷ�ϰ�ť
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//��ȡ�����б�ѭ�����
			{
				linkage_PTZ.channelList.append(dlg.LinkageInfo.channelList[i]);
			}
		}
		else//���ȡ����ť,������̨δΪ��ѡ
		{
			ui->cbPTZ->setCheckState(Qt::Unchecked);
			return;
		}
	}
	else//�����̨�����б�
	{
		linkage_PTZ.channelList.clear();
	}
	refresh_ParaEdit();
}
//������ʾ��������ϸ��Ϣ
void AddAccessLinkageRule::refresh_ParaEdit()
{
	
}


//��ӱ���ͼƬ
void AddAccessLinkageRule::resizeEvent(QResizeEvent *e)
{
	ui->widget_2->setAutoFillBackground(true);
	QPixmap *mBackPic1 = new QPixmap("./resource/top.png");
	QPalette palette1;
	palette1.setBrush(QPalette::Background, QBrush((mBackPic1->scaled(ui->widget_2->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))));
	ui->widget_2->setPalette(palette1);

	ui->widget->setAutoFillBackground(true);
	QPixmap *mBackPic2 = new QPixmap("./resource/mid.png");
	QPalette palette2;
	palette2.setBrush(QPalette::Background, QBrush((mBackPic2->scaled(ui->widget->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))));
	ui->widget->setPalette(palette2);

	ui->widget_3->setAutoFillBackground(true);
	QPixmap *mBackPic3 = new QPixmap("./resource/bottom.png");
	QPalette palette3;
	palette3.setBrush(QPalette::Background, QBrush((mBackPic3->scaled(ui->widget_3->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))));
	ui->widget_3->setPalette(palette3);
}
/************************************************************************/
/* ����϶�����                                                         */
/************************************************************************/
//����ͷ�
void AddAccessLinkageRule::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragPosition = QPoint(-1, -1);
		event->accept();
	}
}
//����϶�
void AddAccessLinkageRule::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() &Qt::LeftButton)
	{
		if (dragPosition != QPoint(-1, -1))
			move(event->globalPos() - dragPosition);
		event->accept();
	}
}

//��С��
void AddAccessLinkageRule::ShowMini()
{
	this->showMinimized();
}
//�ر�
void AddAccessLinkageRule::FrmClose()
{
	this->close();
}

void AddAccessLinkageRule::onAccessChange(QString strSerial)
{

}
