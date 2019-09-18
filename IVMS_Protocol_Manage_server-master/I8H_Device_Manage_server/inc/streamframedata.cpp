#include "streamframedata.h"
#include "register_sdk.h"
#include <QMutexLocker>

StreamFrameData::StreamFrameData(CMS_CONNECT_PARSE_StreamHeader struStreamHeader, unsigned char * lpDataBuffer, unsigned long lDataLength)
	: m_struStreamHeader(struStreamHeader),m_lDataLength(lDataLength)
{
	m_iRefCount = 0;
	m_lFrameNum = 0;
	
	m_lpDataBuffer = new unsigned char[m_lDataLength];
	memcpy(m_lpDataBuffer, lpDataBuffer, m_lDataLength);
}

StreamFrameData::~StreamFrameData()
{
	delete []m_lpDataBuffer;
}

CMS_CONNECT_PARSE_StreamHeader& StreamFrameData::GetStreamHeader()
{
	return m_struStreamHeader;
}

const unsigned long long StreamFrameData::GetFrameNum()
{
	return m_lFrameNum;
}

void StreamFrameData::SetFrameNum(unsigned long long frameNum)
{
	m_lFrameNum = frameNum;
}

const unsigned char* StreamFrameData::GetDataBuffer()
{
	return m_lpDataBuffer;
}

const unsigned long StreamFrameData::GetDataLength()
{
	return m_lDataLength;
}

void StreamFrameData::RefCountAdd()
{
	{
		QMutexLocker locker(&m_mutexRefCount);
		m_iRefCount += 1;
	}
}

void StreamFrameData::RefCountDel()
{
	{
		QMutexLocker locker(&m_mutexRefCount);
		m_iRefCount -= 1;
	}
}

const int StreamFrameData::GetRefCount()
{
	{
		QMutexLocker locker(&m_mutexRefCount);
		return m_iRefCount;
	}
}
