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
	AddLinkageRule::TVWallLinkageInfo LinkageInfo;//�澯��ͼ������ϸ��Ϣ
	CMSTreeView *m_cmsDeviceTree;//�豸��

private slots:
	void onTreeChanged(TreeChangeType type, CMS_CONNECT_PARSE_Node*);
	void btnAdd_clicked();//���
	void btnDelete_clicked();//ɾ��
	void btnOK_clicked();//���ȷ�ϰ�ť�¼�
	void btnCancel_clicked();////�������ȡ����ť
	void onCheckBox_stateChanged(int state);//�Զ����������
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
    Ui::LinkageTVWall *ui;
};

#endif // LINKAGETVWALL_H
