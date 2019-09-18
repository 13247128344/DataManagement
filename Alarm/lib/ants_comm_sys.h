#ifndef _ANTS_COMM_SYS_H_
#define _ANTS_COMM_SYS_H_

#include <sys/types.h>

#include "ants_comm_type.h"
#include "ants_comm_errno.h"

namespace ants_soft
{


	/*设置水印信息的最大长度*/
#define ANTS_WATER_MARK_INFO_MAX_LEN                  (128)

	struct timeval {
		unsigned int		tv_sec;		/* seconds */
		unsigned int		tv_usec;	/* microseconds */
	};

#define ANTSMID_FILE_STARTCODE 				   	(0xAA010000)
#define ANTS_FRAME_STARTCODE 					(0xAB010000)
	typedef enum {
		//!主码流帧类型
		AntsPktError = 0x00,
		AntsPktIFrames = 0x01,
		AntsPktAudioFrames = 0x08,
		AntsPktPFrames = 0x09,
		AntsPktBBPFrames = 0x0a,
		AntsPktVIFrames = 0xa1,
		AntsPktMotionDetection = 0x0b,
		AntsPktDspStatus = 0x0c,
		AntsPktOrigImage = 0x0d,
		AntsPktSysHeader = 0x0e,
		AntsPktBPFrames = 0x0f,
		AntsPktSFrames = 0x10,
		//!子码流帧类型
		AntsPktSubSysHeader = 0x11,
		AntsPktSubIFrames = 0x12,
		AntsPktSubPFrames = 0x13,
		AntsPktSubBBPFrames = 0x14,
		AntsPktSubVIFrames = 0xa2,
		//!智能分析信息帧类型
		AntsPktVacEventZones = 0x15,
		AntsPktVacObjects = 0x16,
		//!第三码流帧类型
		AntsPktThirdSysHeader = 0x17,
		AntsPktThirdIFrames = 0x18,
		AntsPktThirdPFrames = 0x19,
		AntsPktThirdBBPFrames = 0x1a,

		//!智能检测帧类型
		AntsPktSmartIFrames = 0x1b,
		AntsPktSmartPFrames = 0x1c
	}eANTS_FRAME_TYPE;



	typedef enum
	{
		ANTS_CODEC_ID_H264_hisi = 1,
		ANTS_CODEC_ID_MJPEG_hisi = 2,
		ANTS_CODEC_ID_H264_hisi_high = 4,
		ANTS_CODEC_ID_H264_hisi_RTP = 8,
		ANTS_CODEC_ID_H264_hisi_RTP_PACK = 9,//Tyco定制
		ANTS_CODEC_ID_H265 = 16,
		ANTS_CODEC_ID_SVAC = 20,//SVAC
	}ants_vcodec_type;


	typedef struct _tagAudioHeader {
		char cCodecId;			//!音频编码类型
		char cSampleRate;			//!采样率
		char cBitRate;				//!比特率
		char cChannels;			//!通道数
		char cResolution;			//!分辨力
		char cResv[3];				//!保留位
	}ANTS_AUDIO_HEADER, *LPANTS_AUDIO_HEADER;

	typedef struct _tagVideoHeader {
		unsigned short usWidth;				//!视频宽度
		unsigned short usHeight;				//!视频高度
		char cCodecId;				//!视频编码类型
		char cResv[3];					//!保留位
	}ANTS_VIDEO_HEADER, *LPANTS_VIDEO_HEADER;


	typedef struct _tagSmartHeader {
		ANTS_U32 ivs_node_num;//ants_ivs_type 结果节点个数
		char resv[4]; //保留位
	}ANTS_SMART_HEADER, *LPANTS_SMART_HEADER;

	typedef struct _tagAntsFrameHeader {
		unsigned int uiStartId;					//!帧同步头
												//为了方便模块内部处理，将定义修改成枚举，便于代码检查
#if 0	
		unsigned int uiFrameType;				//!帧类型
#else
		eANTS_FRAME_TYPE uiFrameType;			//!帧类型
#endif
		unsigned int uiFrameNo;					//!帧号

												//为了方便模块内部处理，将定义修改成timeval，原来的定义和timeval是一致的，由于1.0中的软件没有用到这两项，所以把名字也改掉
#if 0	
		unsigned int uiFrameTime;				//!UTC时间
		unsigned int uiFrameTickCount;			//!毫秒为单位的毫秒时间
#else
		struct timeval frame_time;	//由remote_agent的链表内部处理，客户端不用处理这个变量
#endif

		unsigned int uiFrameLen;				//!帧载长度
												//!联合体,用于存储音频帧或是视频帧信息
		union {
			ANTS_AUDIO_HEADER struAudioHeader;	//!音频帧信息
			ANTS_VIDEO_HEADER struVideoHeader;	//!视频帧信息
			ANTS_SMART_HEADER smart_header; //智能检测帧信息

		}uMedia;
		unsigned int ucReserve;				//相对时间戳，必须填充，NVR根据这个来累加计算本地时间
	}AntsFrameHeader, *pAntsFrameHeader;

	typedef struct _tagAntsFileHeader {
		unsigned int uiFileStartId;				//!文件起始头标记
		unsigned int uiStreamType;				//!流方式
		unsigned int uiFrameRate;				//!帧率
		unsigned int uiReserve[4];				//!保留位	
	}ANTS_FILE_HEADER, *LPANTS_FILE_HEADER;

	typedef struct
	{
		ANTS_U32 frame_no;
		ANTS_U32 frame_time;
		ANTS_CHAR watermark[ANTS_WATER_MARK_INFO_MAX_LEN + 1];
	}ants_watermark_dec_info;

#pragma pack(push,1)
	typedef struct
	{
		ANTS_U32   uiStartID;
		ANTS_UCHAR byNalType;
		ANTS_UCHAR bySEIType;
		ANTS_UCHAR byLen;
		ANTS_UCHAR byUUID[16];
		ANTS_UCHAR byContextLen;
		ANTS_U32   wFrameNo;
		ANTS_U32   wFrameTime;
		ANTS_UCHAR byVerify;
		ANTS_U16   wZeroBits;
		ANTS_UCHAR byContext[ANTS_WATER_MARK_INFO_MAX_LEN];
	}ants_watermark_h264_set_info;

	typedef struct
	{
		ANTS_U32   uiStartID;
		ANTS_UCHAR byNalType;
		ANTS_UCHAR byNalType1;
		ANTS_UCHAR bySEIType;
		ANTS_UCHAR byLen;
		ANTS_UCHAR byUUID[16];
		ANTS_UCHAR byContextLen;
		ANTS_U32   wFrameNo;
		ANTS_U32   wFrameTime;
		ANTS_UCHAR byVerify;
		ANTS_U16   wZeroBits;
		ANTS_UCHAR byContext[ANTS_WATER_MARK_INFO_MAX_LEN];
	}ants_watermark_h265_set_info;
#pragma pack(pop)

}//namespace ants_soft {
#endif	//#ifndef _ANTS_COMM_SYS_H_#pragma once
