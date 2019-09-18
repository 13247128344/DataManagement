#ifndef DEVICESEARCHHELPER_H
#define DEVICESEARCHHELPER_H

#include <QObject>
#include <QList>
#include "cms_connect_server_common.h"

class DeviceSearchHelper : public QObject
{
    Q_OBJECT

public:
    DeviceSearchHelper(QObject *parent = 0);

    //对搜索到的设备过滤去重
    bool isExist(QString SerialNumber, QString ip);
    //清空为了去重而设的缓存
    void clearSearchingCache();

    CMS_SEARCHDEVICE_CALLBACK func;
    void *pUser;

private:
    QList<QString> searchingCache;
    QMutex mutexCache;


public slots:

};

#endif // DEVICESEARCHHELPER_H
