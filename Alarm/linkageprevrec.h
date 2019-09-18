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
	AddLinkageRule::PrevLinkageInfo LinkageInfo;//�澯��ͼ������ϸ��Ϣ
	CMSTreeView *m_cmsDeviceTree;//�豸��
	void hideModeSet();//����ֹͣģʽ

private slots:
	void onTreeChanged(TreeChangeType type, CMS_CONNECT_PARSE_Node*);
	void btnOK_clicked();
	void btnCancel_clicked();////�������ȡ����ť
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
    Ui::LinkagePrevRec *ui;
};

#endif // LINKAGEPREVREC_H
