#ifndef LINKAGETVWALL_H
#define LINKAGETVWALL_H

#include <QDialog>
#include "addlinkagerule.h"
#include "./include/CMSTreeView.h"

namespace Ui {
class LinkageTVWall;
}

class LinkageTVWall : public QDialog
{
    Q_OBJECT

public:
	LinkageTVWall(QPoint point, QWidget *parent = 0);
	~LinkageTVWall();
	AddLinkageRule::TVWallLinkageInfo LinkageInfo;//告警地图动作详细信息
	CMSTreeView *m_cmsDeviceTree;//设备树

private slots:
	void onTreeChanged(TreeChangeType type, CMS_CONNECT_PARSE_Node*);
	void btnAdd_clicked();//添加
	void btnDelete_clicked();//删除
	void btnOK_clicked();//点击确认按钮事件
	void btnCancel_clicked();////点击窗口取消按钮
	void onCheckBox_stateChanged(int state);//自动分配解码器
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
    Ui::LinkageTVWall *ui;
};

#endif // LINKAGETVWALL_H
