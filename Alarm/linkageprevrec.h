#ifndef LINKAGEPREVREC_H
#define LINKAGEPREVREC_H

#include <QDialog>
#include "addlinkagerule.h"
#include "./include/CMSTreeView.h"

namespace Ui {
class LinkagePrevRec;
}

class LinkagePrevRec : public QDialog
{
    Q_OBJECT

public:
	LinkagePrevRec(QPoint point, LinkageActionType type, QWidget *parent = 0);
	~LinkagePrevRec();
	AddLinkageRule::PrevLinkageInfo LinkageInfo;//告警地图动作详细信息
	CMSTreeView *m_cmsDeviceTree;//设备树
	void hideModeSet();//隐藏停止模式

private slots:
	void onTreeChanged(TreeChangeType type, CMS_CONNECT_PARSE_Node*);
	void btnOK_clicked();
	void btnCancel_clicked();////点击窗口取消按钮
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
    Ui::LinkagePrevRec *ui;
};

#endif // LINKAGEPREVREC_H
