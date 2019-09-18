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
	connect(ui->btn_minimum, SIGNAL(clicked()), this, SLOT(ShowMini()));//最小化
	connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(FrmClose()));//关闭
	ui->btn_minimum->setCursor(Qt::PointingHandCursor);
	ui->btn_close->setCursor(Qt::PointingHandCursor);
	ui->btnSelAlarmSource->setCursor(Qt::PointingHandCursor);
	ui->btnOK->setCursor(Qt::PointingHandCursor);
	ui->btnCancel->setCursor(Qt::PointingHandCursor);

	connect(ui->btnSelAlarmSource, SIGNAL(clicked()), this, SLOT(btnSelAlarmSource_clicked()));//选择报警源
	
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

	connect(ui->cbMap, SIGNAL(stateChanged(int)), this, SLOT(OnCbMapStateChanged(int)));//地图
	connect(ui->cbTVWall, SIGNAL(stateChanged(int)), this, SLOT(OnCbTVWallStateChanged(int)));//电视墙
	connect(ui->cbPreview, SIGNAL(stateChanged(int)), this, SLOT(OnCbPreviewStateChanged(int)));//弹图像
	connect(ui->cbRecord, SIGNAL(stateChanged(int)), this, SLOT(OnCbRecordStateChanged(int)));//录像
	connect(ui->cbCapture, SIGNAL(stateChanged(int)), this, SLOT(OnCbCaptureStateChanged(int)));//抓图
	connect(ui->cbPTZ, SIGNAL(stateChanged(int)), this, SLOT(OnCbPTZStateChanged(int)));//云台
	connect(ui->rbOpenDoor, SIGNAL(clicked()), this, SLOT(onRadioStateChanged()));//隐藏设备数
	connect(ui->rbTamper, SIGNAL(clicked()), this, SLOT(onRadioStateChanged()));
	connect(ui->rbStressPwd, SIGNAL(clicked()), this, SLOT(onRadioStateChanged()));
	connect(ui->rbStressFingerPrint, SIGNAL(clicked()), this, SLOT(onRadioStateChanged()));
	connect(ui->btnOK, SIGNAL(clicked()), this, SLOT(btnSave_clicked()));
	connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(btnCancel_clicked()));//关闭窗口
	//connect(CMSTreeView::sta_m_pCMSTreeItemModel, SIGNAL(CMSTreeChanged(TreeChangeType, CMS_CONNECT_PARSE_Node*)), this, SLOT(onTreeChanged(TreeChangeType, CMS_CONNECT_PARSE_Node*)));
	//connect(AccessInfo::GetInstance(), SIGNAL(sigAccessStateChange(CMS_CONNECT_PARSE_NoticeType, QString)), this, SLOT(onAccessChange(CMS_CONNECT_PARSE_NoticeType, QString)));

	dragPosition = QPoint(-1, -1);
}

AddAccessLinkageRule::~AddAccessLinkageRule()
{
    delete ui;
}


//隐藏设备树
void AddAccessLinkageRule::onRadioStateChanged()
{
	
}
//选择不同报警类型的报警源
void AddAccessLinkageRule::btnSelAlarmSource_clicked()
{
	
}

//初始化要修改的数据
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

//保存报警联动
void AddAccessLinkageRule::btnSave_clicked()
{

}

void AddAccessLinkageRule::btnCancel_clicked()
{
	reject();
}

void AddAccessLinkageRule::OnCbMapStateChanged(int state)
{
	if (Qt::Checked == state)//勾选时设置动作
	{
		QPoint pointCb = ui->cbMap->pos();
		pointCb.ry() = pointCb.ry() + ui->cbMap->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkagePrevRec dlg(point, ivms_LinkageActionType_Map, this);
		if (QDialog::Accepted == dlg.exec())//点击确定按钮
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//循环添加地图动作
				linkage_Map.channelList.append(dlg.LinkageInfo.channelList[i]);
			linkage_Map.iStopMode = dlg.LinkageInfo.iStopMode;//设置地图动作停止模式
		}
		else//点击取消按钮,设置地图选项未勾选
		{
			ui->cbMap->setCheckState(Qt::Unchecked);
			return;
		}
	}
	else//清除地图动作列表
	{
		linkage_Map.channelList.clear();
	}
	refresh_ParaEdit();
}

//电视墙
void AddAccessLinkageRule::OnCbTVWallStateChanged(int state)
{
	if (Qt::Checked == state)//勾选时设置动作
	{
		QPoint pointCb = ui->cbTVWall->pos();
		pointCb.ry() = pointCb.ry() + ui->cbTVWall->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkageTVWall dlg(point, this);
		if (QDialog::Accepted == dlg.exec())//点击确定按钮
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//循环添加电视墙动作
			{
				linkage_TVWall.channelList.append(dlg.LinkageInfo.channelList[i]);
			}
			linkage_TVWall.iStopMode = dlg.LinkageInfo.iStopMode;//设置电视墙动作停止模式
		}
		else//点击取消按钮,设置电视墙选项未勾选
		{
			ui->cbTVWall->setCheckState(Qt::Unchecked);
			return;
		}
	}
	else//清除电视墙动作列表
	{
		linkage_TVWall.channelList.clear();
	}
	refresh_ParaEdit();
}

//预览
void AddAccessLinkageRule::OnCbPreviewStateChanged(int state)
{
	if (Qt::Checked == state)
	{
		QPoint pointCb = ui->cbPreview->pos();
		pointCb.ry() = pointCb.ry() + ui->cbPreview->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkagePrevRec dlg(point, ivms_LinkageActionType_PopImage, this);
		if (QDialog::Accepted == dlg.exec())//点击确认按钮
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//循环获取抓图动作
				linkage_Prev.channelList.append(dlg.LinkageInfo.channelList[i]);
			linkage_Prev.iStopMode = dlg.LinkageInfo.iStopMode;
		}
		else//点击取消按钮,设置预览未勾选
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

//录像
void AddAccessLinkageRule::OnCbRecordStateChanged(int state)
{
	if (Qt::Checked == state)
	{
		QPoint pointCb = ui->cbRecord->pos();
		pointCb.ry() = pointCb.ry() + ui->cbRecord->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkagePrevRec dlg(point, ivms_LinkageActionType_Record, this);
		dlg.hideModeSet();//隐藏停止模式
		if (QDialog::Accepted == dlg.exec())//点击确认按钮
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//循环获取抓图动作
				linkage_Record.channelList.append(dlg.LinkageInfo.channelList[i]);
			linkage_Record.iStopMode = dlg.LinkageInfo.iStopMode;
		}
		else//点击取消按钮,设置录像未勾选
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
//抓图
void AddAccessLinkageRule::OnCbCaptureStateChanged(int state)
{
	if (Qt::Checked == state)
	{
		QPoint pointCb = ui->cbCapture->pos();
		pointCb.ry() = pointCb.ry() + ui->cbCapture->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkagePrevRec dlg(point, ivms_LinkageActionType_Capture, this);
		dlg.hideModeSet();//隐藏停止模式
		if (QDialog::Accepted == dlg.exec())//点击确认按钮
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//循环获取抓图动作
				linkage_Capture.channelList.append(dlg.LinkageInfo.channelList[i]);
			linkage_Capture.iStopMode = dlg.LinkageInfo.iStopMode;
		}
		else//点击取消按钮,设置抓图未勾选
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
//云台
void AddAccessLinkageRule::OnCbPTZStateChanged(int state)
{
	if (Qt::Checked == state)//设置云台动作
	{
		QPoint pointCb = ui->cbPTZ->pos();
		pointCb.ry() = pointCb.ry() + ui->cbPTZ->height() * 2 + 15;
		QPoint point = mapToGlobal(pointCb);
		LinkagePTZ dlg(point, this);
		if (QDialog::Accepted == dlg.exec())//点击确认按钮
		{
			for (int i = 0; i < dlg.LinkageInfo.channelList.size(); i++)//获取动作列表循环添加
			{
				linkage_PTZ.channelList.append(dlg.LinkageInfo.channelList[i]);
			}
		}
		else//点击取消按钮,设置云台未为勾选
		{
			ui->cbPTZ->setCheckState(Qt::Unchecked);
			return;
		}
	}
	else//清除云台动作列表
	{
		linkage_PTZ.channelList.clear();
	}
	refresh_ParaEdit();
}
//更新显示动作的详细信息
void AddAccessLinkageRule::refresh_ParaEdit()
{
	
}


//添加背景图片
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
/* 鼠标拖动窗口                                                         */
/************************************************************************/
//鼠标释放
void AddAccessLinkageRule::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragPosition = QPoint(-1, -1);
		event->accept();
	}
}
//鼠标拖动
void AddAccessLinkageRule::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() &Qt::LeftButton)
	{
		if (dragPosition != QPoint(-1, -1))
			move(event->globalPos() - dragPosition);
		event->accept();
	}
}

//最小化
void AddAccessLinkageRule::ShowMini()
{
	this->showMinimized();
}
//关闭
void AddAccessLinkageRule::FrmClose()
{
	this->close();
}

void AddAccessLinkageRule::onAccessChange(QString strSerial)
{

}
