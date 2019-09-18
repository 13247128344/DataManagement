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
	void onItemSelectionChanged();//查看规则详情
	void btnAddLinkRule_clicked();//添加告警联动规则事件
	void btnUpdLinkRule_clicked();//更新告警联动规则事件
	void OnStateChanged(int iState);//启用/禁用告警联动
	void OnUpdateRule();//修改告警联动
	void OnDeleteRule();//删除告警联动
	void GetLinkageRules();//获取所有的规则
	void InitLinkRule();//初始化告警联动规则列表
	void btnAddAccessLinkRule_clicked();//添加门禁联动规则

protected:
	//窗口改变事件
	void resizeEvent(QResizeEvent *e);
private:
    Ui::AlarmCfg *ui;
};

#endif // ALARMCFG_H
