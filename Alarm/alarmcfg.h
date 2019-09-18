#ifndef ALARMCFG_H
#define ALARMCFG_H

#include <QWidget>
#include "loading.h"

namespace Ui {
class AlarmCfg;
}

class AlarmCfg : public QWidget
{
    Q_OBJECT

public:
	~AlarmCfg();
	static AlarmCfg* getAlarmLinkageManage(QWidget *parent);
	AlarmCfg(QWidget *parent = 0);

private:
	static AlarmCfg* stra_AlarmLinkageManage;
	int m_nTimerId;
	bool m_move;
	QPoint m_startPoint;
	QPoint m_windowPoint;
	QList<QPair<QString, QPair<QString, int>>> m_RuleInfoList;
	Loading *_pLoading;
	int _iRuleCount = 0;
	

protected slots:
	void onItemSelectionChanged();//�鿴��������
	void btnAddLinkRule_clicked();//��Ӹ澯���������¼�
	void btnUpdLinkRule_clicked();//���¸澯���������¼�
	void OnStateChanged(int iState);//����/���ø澯����
	void OnUpdateRule();//�޸ĸ澯����
	void OnDeleteRule();//ɾ���澯����
	void GetLinkageRules();//��ȡ���еĹ���
	void InitLinkRule();//��ʼ���澯���������б�
	void btnAddAccessLinkRule_clicked();//����Ž���������

protected:
	//���ڸı��¼�
	void resizeEvent(QResizeEvent *e);
private:
    Ui::AlarmCfg *ui;
};

#endif // ALARMCFG_H
