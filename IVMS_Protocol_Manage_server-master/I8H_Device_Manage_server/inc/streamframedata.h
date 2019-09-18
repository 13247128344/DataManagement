/************************************************************************
*
*   文件名： streamframedata.h
*
*   文件描述：流数据定义
*
*   创建人：Sunx, 2015年6月17日
*
*   版本号：1.0
*
*   修改记录：
*
************************************************************************/


#ifndef STREAMFRAMEDATA_H
#define STREAMFRAMEDATA_H

#include <QMutex>
#include "cms_connect_parse_common.h"

class StreamFrameData
{
public:
	StreamFrameData(CMS_CONNECT_PARSE_StreamHeader struStreamHeader, unsigned char * lpDataBuffer, unsigned long lDataLength);
	~StreamFrameData();
	CMS_CONNECT_PARSE_StreamHeader& GetStreamHeader();
	const unsigned long long GetFrameNum();
	void SetFrameNum(unsigned long long frameNum);
	const unsigned char* GetDataBuffer();
	const unsigned long GetDataLength();
	void RefCountAdd();
	void RefCountDel();
	const int GetRefCount();

private:
	unsigned long long m_lFrameNum;
	unsigned char *m_lpDataBuffer;
	const unsigned long m_lDataLength;
	CMS_CONNECT_PARSE_StreamHeader m_struStreamHeader;

	int m_iRefCount;
	QMutex m_mutexRefCount;
};

#endif // STREAMFRAMEDATA_H
