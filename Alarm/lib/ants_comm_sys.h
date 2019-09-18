#ifndef _ANTS_COMM_SYS_H_
#define _ANTS_COMM_SYS_H_

#include <sys/types.h>

#include "ants_comm_type.h"
#include "ants_comm_errno.h"

namespace ants_soft
{


	/*����ˮӡ��Ϣ����󳤶�*/
#define ANTS_WATER_MARK_INFO_MAX_LEN                  (128)

	struct timeval {
		unsigned int		tv_sec;		/* seconds */
		unsigned int		tv_usec;	/* microseconds */
	};

#define ANTSMID_FILE_STARTCODE 				   	(0xAA010000)
#define ANTS_FRAME_STARTCODE 					(0xAB010000)
	typedef enum {
		//!������֡����
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
		//!������֡����
		AntsPktSubSysHeader = 0x11,
		AntsPktSubIFrames = 0x12,
		AntsPktSubPFrames = 0x13,
		AntsPktSubBBPFrames = 0x14,
		AntsPktSubVIFrames = 0xa2,
		//!���ܷ�����Ϣ֡����
		AntsPktVacEventZones = 0x15,
		AntsPktVacObjects = 0x16,
		//!��������֡����
		AntsPktThirdSysHeader = 0x17,
		AntsPktThirdIFrames = 0x18,
		AntsPktThirdPFrames = 0x19,
		AntsPktThirdBBPFrames = 0x1a,

		//!���ܼ��֡����
		AntsPktSmartIFrames = 0x1b,
		AntsPktSmartPFrames = 0x1c
	}eANTS_FRAME_TYPE;



	typedef enum
	{
		ANTS_CODEC_ID_H264_hisi = 1,
		ANTS_CODEC_ID_MJPEG_hisi = 2,
		ANTS_CODEC_ID_H264_hisi_high = 4,
		ANTS_CODEC_ID_H264_hisi_RTP = 8,
		ANTS_CODEC_ID_H264_hisi_RTP_PACK = 9,//Tyco����
		ANTS_CODEC_ID_H265 = 16,
		ANTS_CODEC_ID_SVAC = 20,//SVAC
	}ants_vcodec_type;


	typedef struct _tagAudioHeader {
		char cCodecId;			//!��Ƶ��������
		char cSampleRate;			//!������
		char cBitRate;				//!������
		char cChannels;			//!ͨ����
		char cResolution;			//!�ֱ���
		char cResv[3];				//!����λ
	}ANTS_AUDIO_HEADER, *LPANTS_AUDIO_HEADER;

	typedef struct _tagVideoHeader {
		unsigned short usWidth;				//!��Ƶ���
		unsigned short usHeight;				//!��Ƶ�߶�
		char cCodecId;				//!��Ƶ��������
		char cResv[3];					//!����λ
	}ANTS_VIDEO_HEADER, *LPANTS_VIDEO_HEADER;


	typedef struct _tagSmartHeader {
		ANTS_U32 ivs_node_num;//ants_ivs_type ����ڵ����
		char resv[4]; //����λ
	}ANTS_SMART_HEADER, *LPANTS_SMART_HEADER;

	typedef struct _tagAntsFrameHeader {
		unsigned int uiStartId;					//!֡ͬ��ͷ
												//Ϊ�˷���ģ���ڲ������������޸ĳ�ö�٣����ڴ�����
#if 0	
		unsigned int uiFrameType;				//!֡����
#else
		eANTS_FRAME_TYPE uiFrameType;			//!֡����
#endif
		unsigned int uiFrameNo;					//!֡��

												//Ϊ�˷���ģ���ڲ������������޸ĳ�timeval��ԭ���Ķ����timeval��һ�µģ�����1.0�е����û���õ���������԰�����Ҳ�ĵ�
#if 0	
		unsigned int uiFrameTime;				//!UTCʱ��
		unsigned int uiFrameTickCount;			//!����Ϊ��λ�ĺ���ʱ��
#else
		struct timeval frame_time;	//��remote_agent�������ڲ������ͻ��˲��ô����������
#endif

		unsigned int uiFrameLen;				//!֡�س���
												//!������,���ڴ洢��Ƶ֡������Ƶ֡��Ϣ
		union {
			ANTS_AUDIO_HEADER struAudioHeader;	//!��Ƶ֡��Ϣ
			ANTS_VIDEO_HEADER struVideoHeader;	//!��Ƶ֡��Ϣ
			ANTS_SMART_HEADER smart_header; //���ܼ��֡��Ϣ

		}uMedia;
		unsigned int ucReserve;				//���ʱ�����������䣬NVR����������ۼӼ��㱾��ʱ��
	}AntsFrameHeader, *pAntsFrameHeader;

	typedef struct _tagAntsFileHeader {
		unsigned int uiFileStartId;				//!�ļ���ʼͷ���
		unsigned int uiStreamType;				//!����ʽ
		unsigned int uiFrameRate;				//!֡��
		unsigned int uiReserve[4];				//!����λ	
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
