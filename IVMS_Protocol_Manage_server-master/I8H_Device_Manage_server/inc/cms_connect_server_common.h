/************************************************************************
*
*   文件名： cms_connect_server_common.h
*
*   文件描述：服务器公共定义，定义了一些全局使用的对象和结构体
*
*   创建人：Sunx, 2015年6月17日
*
*   版本号：1.0
*
*   修改记录：
*
************************************************************************/


#ifndef CMS_CONNECT_SERVER_COMMON_H
#define CMS_CONNECT_SERVER_COMMON_H


#include "cms_connect_parse_common.h"
#include "cloud_common.h"
#include <QString>
#include "streamframedata.h"
#include <QMutex>


#pragma pack(1) //设置1字节对齐

typedef struct
{
    char UUId[48];				//设备唯一标识符,通常使用设备序列号
    unsigned short ChNo;		//通道号 0x0001--0xFFFF
    unsigned short StreamType;	//数据传输模式, 1-实时流视频数据 2-实时流音频数据 3-语音流 4-历史流视频数据 5-历史流音频数据
}RegisterStreamHeader;


typedef struct
{
    unsigned char Codec;		//语音编码类型, 1-G711-U 2-G711-A 3-G726
    unsigned char SampleRate;	//语音对讲采样率, 1-8000HZ 2-32000HZ 3-48000HZ 4-960000HZ
    unsigned char BitRate;		//语音对讲比特率, 1-8bit 2-16bit
    unsigned char Channel;		//语音对讲声道, 1-单通道 2-双通道
    unsigned int TimeUTC;		//当前时间戳秒
    unsigned int MicroSec;	    //当前时间戳微秒
    unsigned int Length;		//语音对讲音频数据长度
}RegisterIntercomHeader;


typedef struct
{
    unsigned char Codec;		//编码类型, 1-I8私有格式 2-H.264格式 3-H.265格式 4-AVI格式
    unsigned short FrameType;	//帧类型,1-主码流I帧 2-主码流P帧 3-子码流I帧 4-子码流P帧 5-主码流音频帧 6-子码流音频帧
    unsigned int TimeUTC;		//当前时间戳秒
    unsigned int MicroSec;	    //当前时间戳微秒
    unsigned short Width;		//视频帧宽度
    unsigned short Height;		//视频帧高度
    unsigned int Length;		//视频数据长度
}RegisterRealVideoHeader;


typedef struct
{
    unsigned char Codec;		//1-G711-U 2-G711-A 3-G726
    unsigned short FrameType;	//帧类型,1-主码流I帧 2-主码流P帧 3-子码流I帧 4-子码流P帧 5-主码流音频帧 6-子码流音频帧
    unsigned char SampleRate;	//语音对讲采样率, 1-8000HZ 2-32000HZ 3-48000HZ 4-960000HZ
    unsigned char BitRate;		//语音对讲比特率, 1-8bit 2-16bit
    unsigned char Channel;		//语音对讲声道, 1-单通道 2-双通道
    unsigned int TimeUTC;		//当前时间戳秒
    unsigned int MicroSec;	    //当前时间戳微秒
    unsigned int Length;		//音频数据长度
}RegisterRealAudioHeader;


typedef struct
{
    unsigned int HistoryId;	//当前回放ID
    unsigned char Codec;		//编码类型, 1-I8私有格式 2-H.264格式 3-H.265格式 4-AVI格式
    unsigned short FrameType;	//帧类型,1-主码流I帧 2-主码流P帧 3-子码流I帧 4-子码流P帧 5-主码流音频帧 6-子码流音频帧
    unsigned int TimeUTC;		//当前时间戳秒
    unsigned int MicroSec;	    //当前时间戳微秒
    unsigned short Width;		//视频帧宽度
    unsigned short Height;		//视频帧高度
    unsigned int Length;		//视频数据长度，0表示回放结束
}RegisterHistoryVideoHeader;


typedef struct
{
    unsigned int HistoryId;	//当前回放ID
    unsigned char Codec;		//1-G711-U 2-G711-A 3-G726
    unsigned short FrameType;	//帧类型,1-主码流I帧 2-主码流P帧 3-子码流I帧 4-子码流P帧 5-主码流音频帧 6-子码流音频帧
    unsigned char SampleRate;	//语音对讲采样率, 1-8000HZ 2-32000HZ 3-48000HZ 4-960000HZ
    unsigned char BitRate;		//语音对讲比特率, 1-8bit 2-16bit
    unsigned char Channel;		//语音对讲声道, 1-单通道 2-双通道
    unsigned int TimeUTC;		//当前时间戳秒
    unsigned int MicroSec;	    //当前时间戳微秒
    unsigned int Length;		//音频数据长度，0表示回放结束
}RegisterHistoryAudioHeader;

#pragma pack() // 恢复先前的pack设置,取消设置的字节对齐方式


struct CMSService_AlarmInfo
{
    CMS_CONNECT_PARSE_AlarmType eAlarmType;		//告警类型
    QString strSerialNum;						//设备序列号
    int iParam;									//参数，当告警类型为告警输入时，其为告警输入号；其它告警类型时，其为通道号。都是从1开始

    bool operator==(CMSService_AlarmInfo const  &ins) const
    {
        if(ins.eAlarmType==this->eAlarmType && ins.strSerialNum==this->strSerialNum && ins.iParam==this->iParam)
            return true;
        else
            return false;
    }

    bool operator<(CMSService_AlarmInfo const  &ins) const
    {
        if(this->eAlarmType<ins.eAlarmType)
        {
            return true;
        }
        else if(this->eAlarmType==ins.eAlarmType)
        {
            if(this->strSerialNum < ins.strSerialNum)
            {
                return true;
            }
            else if(this->strSerialNum == ins.strSerialNum && this->iParam < ins.iParam)
            {
                return true;
            }
        }
        return false;
    }
};

struct CMSService_AccessAlarmInfo
{
	CMS_CONNECT_PARSE_AccessAlarmType eAlarmType;		//告警类型
	QString strSerialNum;						//设备序列号
	int iParam;									//参数，当告警类型为告警输入时，其为告警输入号；其它告警类型时，其为通道号。都是从1开始
	int iTimeUtc;

	bool operator==(CMSService_AccessAlarmInfo const  &ins) const
	{
		if (ins.eAlarmType == this->eAlarmType && ins.strSerialNum == this->strSerialNum && ins.iParam == this->iParam && ins.iTimeUtc == this->iTimeUtc)
			return true;
		else
			return false;
	}

	bool operator<(CMSService_AccessAlarmInfo const  &ins) const
	{
		if (this->eAlarmType < ins.eAlarmType)
		{
			return true;
		}
		else if (this->eAlarmType == ins.eAlarmType)
		{
			if (this->strSerialNum < ins.strSerialNum)
			{
				return true;
			}
			else if (this->strSerialNum == ins.strSerialNum && this->iParam < ins.iParam)
			{
				return true;
			}
		}
		return false;
	}
};


struct CMSService_OnlineInfo
{
    QString strSerialNum;						//设备序列号
    bool isOnline;								//是否在线
};


typedef void (__stdcall *CMS_STREAMDATA_CALLBACK)(StreamFrameData *pFrameData, void *pUser);
typedef void(__stdcall *CMS_ALARM_MESSAGE_CALLBACK)(CMS_CONNECT_PARSE_AlarmType eAlarmType, QString strSerialNum, int iParam, void *pUser);
typedef void(__stdcall *CMS_AccessALARM_MESSAGE_CALLBACK)(CMS_CONNECT_PARSE_AccessAlarmType eAlarmType,unsigned int dateTime, QString strSerialNum, int iParam, void *pUser);
typedef void (__stdcall *CMS_SEARCHDEVICE_CALLBACK)(CMS_CONNECT_PARSE_SearchDeviceInfo sInfo, void *pUser);
typedef void(__stdcall *CMS_SEARCHACCESS_CALLBACK)(CMS_CONNECT_PARSE_SearchAccessInfo sInfo, void *pUser);


VOID CALLBACK Register_ValidUserCallBackV2(IN S8 *lpUuid, IN S8 *lpIPAddr, IN cloud_user_status_t eUserStatus, IN LPCLOUD_DEVICE_INFO_V2 lpDeviceInfo, IN VOID *lpUser);
VOID CALLBACK Register_ValidUserCallBack(IN HANDLE hRegisterId, IN HANDLE hUserId, IN S8 *lpUserIP, IN cloud_user_workmodel_t eUserWorkModel, IN cloud_user_status_t eUserStatus, IN LPCLOUD_DEVICE_INFO lpDeviceInfo, IN VOID *lpUser);
VOID CALLBACK Register_UserWorkStatusCallBackV2(IN S8 *lpUuid, IN S8 *lpInBuffer, IN S32 s32BufSize, IN VOID *lpUser);
VOID CALLBACK Register_AlarmMessage_CallBackV2(IN S8 *lpUuid, IN S8 *lpInBuffer, IN S32 s32BufSize, IN VOID *lpUser);
void CALLBACK DecoderOnlineCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser);




extern int g_iMaxClientCount;
extern int g_iMaxDeviceCount;
extern long g_iMaxExtendedCount[64];
extern long g_iCurrentExtendedCount[64];
extern QMutex g_mutexExtendedCount;

extern int g_iClientListenPort;
extern int g_iDeviceListenPort;

#endif // CMS_CONNECT_SERVER_COMMON_H

