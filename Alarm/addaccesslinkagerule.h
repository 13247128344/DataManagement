#ifndef ADDACCESSLINKAGERULE_H
#define ADDACCESSLINKAGERULE_H

#include <QDialog>
#include "addlinkagerule.h"
namespace Ui {
class AddAccessLinkageRule;
}

class AddAccessLinkageRule : public QDialog
{
    Q_OBJECT

public:
	AddAccessLinkageRule(int ruleParam, QWidget *parent = Q_NULLPTR);
	~AddAccessLinkageRule();


private:
	AddLinkageRule::PrevLinkageInfo linkage_Map;
	AddLinkageRule::PrevLinkageInfo linkage_Prev;
	AddLinkageRule::PrevLinkageInfo linkage_Record;
	AddLinkageRule::PrevLinkageInfo linkage_Capture;
	AddLinkageRule::PTZLinkageInfo linkage_PTZ;
	AddLinkageRule::TVWallLinkageInfo linkage_TVWall;

	
	void refresh_ParaEdit();
	void getUpdateSources();
private slots:
	void OnCbMapStateChanged(int state);//��ͼ
	void OnCbTVWallStateChanged(int state);//����ǽ
	void OnCbPreviewStateChanged(int state);//Ԥ��
	void OnCbRecordStateChanged(int state);//¼��
	void OnCbCaptureStateChanged(int state);//ץͼ
	void OnCbPTZStateChanged(int state);//��̨
	void onRadioStateChanged();//���������л�ʱ�����豸��
	void btnSelAlarmSource_clicked();//ѡ�񱨾�Դ
	void btnSave_clicked();//���汨��������Ϣ
	void btnCancel_clicked();//ȡ��
	void ShowMini();//��С��
	void FrmClose();//�ر�
	void onAccessChange(QString);
protected:
	//���ڸı��¼�,����¼�
	void resizeEvent(QResizeEvent *e);
	void mouseMoveEvent(QMouseEvent*event);
	void mousePressEvent(QMouseEvent*event);
	void mouseReleaseEvent(QMouseEvent*event);
	QPoint dragPosition;//����λ��
private:
    Ui::AddAccessLinkageRule *ui;
};

#endif // ADDACCESSLINKAGERULE_H
