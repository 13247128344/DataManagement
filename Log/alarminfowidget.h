#ifndef ALARMINFOWIDGET_H
#define ALARMINFOWIDGET_H

#include <QWidget>
#include "./include/CMSTreeView.h"
#include "./include/ivms_public.h"
namespace Ui {
class AlarmInfoWidget;
}

class AlarmInfoWidget : public QWidget
{
    Q_OBJECT

public:
     AlarmInfoWidget(QWidget *parent = 0);
    ~AlarmInfoWidget();

	public slots:
	void on_btn_hide_clicked();
signals:
	void sendAccessEvent(CMS_CONNECT_PARSE_Access_Alarm_Notice);
	void sendPlaySound(int);
	void sendInsertEvent(QString);
	void sendAlarmEvent(CMS_CONNECT_PARSE_Alarm_Notice);
	protected slots:
	void on_btn_alarm_clicked();
	void on_btn_event_clicked();

	void on_btn_stay_clicked();
	void on_btn_clear_clicked();
	void on_btn_alarm_info_clicked();
	void on_btn_close_sound_clicked();
	void on_btn_open_sound_clicked();
	void onSelectEventRow();
 	void onDeviceOnline(TreeChangeType changeType, CMS_CONNECT_PARSE_Node *pNode);
 	//void onItemDoubleClicked(QTableWidgetItem *item);
	void onOpenSound(int);
	void onInsertEvent(QString);
	void onInsertAlarmEvent(CMS_CONNECT_PARSE_Alarm_Notice);
	void onInsertAccessEvent(CMS_CONNECT_PARSE_Access_Alarm_Notice);
private:
	bool m_bIsStay;
	bool m_bOpenSound;
protected:
	void resizeEvent(QResizeEvent *e);
public:
	void insertAlarmEvent(CMS_CONNECT_PARSE_Alarm_Notice);
	void insertAccessEvent(CMS_CONNECT_PARSE_Access_Alarm_Notice);
	void insertOnOfflineEvent(CMS_CONNECT_PARSE_Node*);
	void insertEvent(QString);
	void initStyle();
	
private:
    Ui::AlarmInfoWidget *ui;
};

#endif // ALARMINFOWIDGET_H
