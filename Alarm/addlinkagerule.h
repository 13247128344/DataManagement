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
	CMSTreeView *m_pCurTree;//��ʾ���豸��

	QMap<CMS_CONNECT_PARSE_AlarmType, QString> m_mapAlarmType;

	AddIVMSArae *m_pAddIVMSArea;
	bool isLoading;
	void refresh_ParaEdit();
	void getUpdateSources();
private slots:
	void onTreeChanged(TreeChangeType type, CMS_CONNECT_PARSE_Node*);
    void OnCbMapStateChanged(int state);//��ͼ
    void OnCbTVWallStateChanged(int state);//����ǽ
    void OnCbPreviewStateChanged(int state);//Ԥ��
    void OnCbRecordStateChanged(int state);//¼��
    void OnCbCaptureStateChanged(int state);//ץͼ
    void OnCbPTZStateChanged(int state);//��̨
    void onCurrentIndexChanged(int);//���������л�ʱ�����豸��
    void btnSelAlarmSource_clicked();//ѡ�񱨾�Դ
    void btnSave_clicked();//���汨��������Ϣ
    void btnCancel_clicked();//ȡ��
    void ShowMini();//��С��
    void FrmClose();//�ر�
    protected:
    	//���ڸı��¼�,����¼�
	void resizeEvent(QResizeEvent *e);
	void mouseMoveEvent(QMouseEvent*event);
	void mousePressEvent(QMouseEvent*event);
	void mouseReleaseEvent(QMouseEvent*event);
	QPoint dragPosition;//����λ��
private:
    Ui::AddLinkageRule *ui;
};

#endif // ADDLINKRULE_H
