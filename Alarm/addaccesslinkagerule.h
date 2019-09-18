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
	void OnCbMapStateChanged(int state);//地图
	void OnCbTVWallStateChanged(int state);//电视墙
	void OnCbPreviewStateChanged(int state);//预览
	void OnCbRecordStateChanged(int state);//录像
	void OnCbCaptureStateChanged(int state);//抓图
	void OnCbPTZStateChanged(int state);//云台
	void onRadioStateChanged();//报警类型切换时隐藏设备树
	void btnSelAlarmSource_clicked();//选择报警源
	void btnSave_clicked();//保存报警联动信息
	void btnCancel_clicked();//取消
	void ShowMini();//最小化
	void FrmClose();//关闭
	void onAccessChange(QString);
protected:
	//窗口改变事件,鼠标事件
	void resizeEvent(QResizeEvent *e);
	void mouseMoveEvent(QMouseEvent*event);
	void mousePressEvent(QMouseEvent*event);
	void mouseReleaseEvent(QMouseEvent*event);
	QPoint dragPosition;//窗口位置
private:
    Ui::AddAccessLinkageRule *ui;
};

#endif // ADDACCESSLINKAGERULE_H
