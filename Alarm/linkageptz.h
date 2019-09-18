#ifndef LINKAGEPTZ_H
#define LINKAGEPTZ_H

#include <QDialog>
#include "addlinkagerule.h"

namespace Ui {
class LinkagePTZ;
}

class LinkagePTZ : public QDialog
{
    Q_OBJECT

public:
	LinkagePTZ(QPoint point, QWidget *parent = 0);
	~LinkagePTZ();
	AddLinkageRule::PTZLinkageInfo LinkageInfo;//�澯��ͼ������ϸ��Ϣ
	CMSTreeView *m_cmsDeviceTree;//�豸��

private slots:
	void onTreeChanged(TreeChangeType type, CMS_CONNECT_PARSE_Node*);
	void btnAdd_clicked();//���
	void btnDelete_clicked();//ɾ��
	void btnOK_clicked();//���ȷ�ϰ�ť�¼�
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
    Ui::LinkagePTZ *ui;
};

#endif // LINKAGEPTZ_H
