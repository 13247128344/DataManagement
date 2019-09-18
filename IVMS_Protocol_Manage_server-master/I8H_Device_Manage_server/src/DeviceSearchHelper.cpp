#include "DeviceSearchHelper.h"

DeviceSearchHelper::DeviceSearchHelper(QObject *parent)
    : QObject(parent)
{

}

bool DeviceSearchHelper::isExist(QString SerialNumber, QString ip)
{
    QString key = SerialNumber;
    key.append(QString("=="));
    key.append(ip);

    foreach (QString deviceKey, searchingCache) {
        if (0 == key.compare(&deviceKey)){
            return true;
        }
    }
    {
        QMutexLocker locker(&mutexCache);
        this->searchingCache.append(key);
    }

    return false;
}

void DeviceSearchHelper::clearSearchingCache()
{
    QMutexLocker locker(&mutexCache);
    this->searchingCache.clear();
}
