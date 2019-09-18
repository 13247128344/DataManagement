#ifndef ADDLINKRULE_H
#define ADDLINKRULE_H

#include <QDialog>
#include "QMap"
#include "addivmsarae.h"
#include "public.h"

namespace Ui {
class AddLinkageRule;
}

class AddLinkageRule : public QDialog
{
    Q_OBJECT

public:
	struct  ChInfo
	{
		QString strDeviceNumber;
		int iChannel;
		int iChType;
		QString strDecoderSerial;
		LinkagePtzType ptzType;
		int iOutputNo;
		int ptzIndex;
	};

	struct	PrevLinkageInfo
	{
		QList<ChInfo> channelList;
		int iStopMode;
	};

	struct	PTZLinkageInfo
	{
		QList<ChInfo> channelList;
	};

	struct	TVWallLinkageInfo
	{
		QList<ChInfo> channelList;
		int iStopMode;
	};

public:
	AddLinkageRule(IVMS_CONNECT_PARSE_LinkageRuleParam ruleParam, QWidget *parent = 0);
	~AddLinkageRule();
	IVMS_CONNECT_PARSE_LinkageRuleParam m_pRuleParam;
    
private:
	PrevLinkageInfo linkage_Prev;
	PrevLinkageInfo linkage_Record;
	PrevLinkageInfo linkage_Capture;
	PTZLinkageInfo linkage_PTZ;
	PrevLinkageInfo linkage_Map;
	TVWallLinkageInfo linkage_TVWall;

	CMSTreeView *m_ivmsDeviceTree_AlarmIn;
	CMSTreeView *m_pDeviceTree_Other;
	CMSTreeView *m_pCurTree;//显示的设备树

	QMap<CMS_CONNECT_PARSE_AlarmType, QString> m_mapAlarmType;

	AddIVMSArae *m_pAddIVMSArea;
	bool isLoading;
	void refresh_ParaEdit();
	void getUpdateSources();
private slots:
	void onTreeChanged(TreeChangeType type, CMS_CONNECT_PARSE_Node*);
    void OnCbMapStateChanged(int state);//地图
    void OnCbTVWallStateChanged(int state);//电视墙
    void OnCbPreviewStateChanged(int state);//预览
    void OnCbRecordStateChanged(int state);//录像
    void OnCbCaptureStateChanged(int state);//抓图
    void OnCbPTZStateChanged(int state);//云台
    void onCurrentIndexChanged(int);//报警类型切换时隐藏设备树
    void btnSelAlarmSource_clicked();//选择报警源
    void btnSave_clicked();//保存报警联动信息
    void btnCancel_clicked();//取消
    void ShowMini();//最小化
    void FrmClose();//关闭
    protected:
    	//窗口改变事件,鼠标事件
	void resizeEvent(QResizeEvent *e);
	void mouseMoveEvent(QMouseEvent*event);
	void mousePressEvent(QMouseEvent*event);
	void mouseReleaseEvent(QMouseEvent*event);
	QPoint dragPosition;//窗口位置
private:
    Ui::AddLinkageRule *ui;
};

#endif // ADDLINKRULE_H
