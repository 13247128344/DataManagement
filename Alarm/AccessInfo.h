#pragma once

#include <QObject>
#include "public.h"

class AccessInfo : public QObject
{
	Q_OBJECT

signals:

	void sigAccessStateChange(CMS_CONNECT_PARSE_NoticeType, QString);

public:
	AccessInfo(QObject *parent = nullptr);
	~AccessInfo();

	//作为全局检索用
	static CMS_CONNECT_PASER_AccessControlInfo* GetControlInfoBySerialNum(QString strSerialNum);
	static void InitControlInfo();
	static AccessInfo* GetInstance();
	static QList<CMS_CONNECT_PASER_AccessControlInfo*> GetListInstance();
private:
	static QList<CMS_CONNECT_PASER_AccessControlInfo*> m_listInfo;
	static AccessInfo* sta_instance;
public slots:
	void onAccessChange(CMS_CONNECT_PARSE_NoticeType, unsigned char*);

};
