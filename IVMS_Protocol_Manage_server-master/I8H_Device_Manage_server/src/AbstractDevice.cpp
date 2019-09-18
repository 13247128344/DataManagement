#include "AbstractDevice.h"

AbstractDevice::AbstractDevice(QString strSerialNum, QObject *parent)
	: QObject(parent), m_strSerialNum(strSerialNum)
{
	m_isOnline = false;
	m_pAlarmCallbackFunc = NULL;
	m_pAlarmCallbackUser = NULL;
	m_hConnection = NULL;
}




AbstractDevice::~AbstractDevice()
{

}

void AbstractDevice::freeMemory(void *pMemory)
{
	delete []pMemory;
}

void AbstractDevice::setAlarmCallback(CMS_ALARM_MESSAGE_CALLBACK func, void *pUser)
{
	m_pAlarmCallbackFunc = func;
	m_pAlarmCallbackUser = pUser;
}

const QString AbstractDevice::serialNum()
{
	return m_strSerialNum;
}

void AbstractDevice::setConnectionHandle(HANDLE handle)
{
	m_hConnection = handle;
}

const HANDLE AbstractDevice::connectionHandle()
{
	return m_hConnection;
}

const bool AbstractDevice::isOnline()
{
	return m_isOnline;
}

void AbstractDevice::setOnline(const bool bOnline)
{
	m_isOnline = bOnline;
}

bool AbstractDevice::login(QString strUsername, QString strPassword, LoginInfo &sLoginInfo)
{
	
	return true;
}

int AbstractDevice::logout(HANDLE handle)
{
	return 0;
}

void AbstractDevice::startSearchDevice(CMS_SEARCHDEVICE_CALLBACK func, void *pUser)
{

}

void AbstractDevice::stopSearchDevice()
{

}
