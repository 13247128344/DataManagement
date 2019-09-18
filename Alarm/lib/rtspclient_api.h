#ifndef _RTSP_CLIENT_API_H_
#define _RTSP_CLIENT_API_H_

typedef enum
{
    ANTS_RTPTransProto_AUTO,
    ANTS_RTPTransProto_UDP,
    ANTS_RTPTransProto_MULTICAST,
    ANTS_RTPTransProto_TCP,
    ANTS_RTPTransProto_HTTP,
    ANTS_RTPTransProto_BUTT

}ANTS_RTPTransProto;

typedef enum
{
    ANTS_RTPClientCallbackType_Stream = 0,
    ANTS_RTPClientCallbackType_RTCP,
    ANTS_RTPClientCallbackType_Status,
    ANTS_RTPClientCallbackType_Error,
    ANTS_RTPClientCallbackType_BUTT
}ANTS_RTPClientCallbackType;


typedef enum
{
    
    ANTS_RTSP_STREAM_H264 = 0,
    ANTS_RTSP_STREAM_MPEG4,
    ANTS_RTSP_STREAM_JPEG,
    ANTS_RTSP_STREAM_G711A,
    ANTS_RTSP_STREAM_G711U,
    ANTS_RTSP_STREAM_G726 = 5,
    ANTS_RTSP_STREAM_AAC,
    ANTS_RTSP_STREAM_H265,
    ANTS_RTSP_STREAM_AntsComb,
    ANTS_RTSP_STREAM_APP = 20,
    ANTS_RTSP_STREAM_UNKNOW = 0x10000, //低16位为对应的编码号
}ANTS_RTSP_STREAM_TYPE;

typedef enum
{
    ANTS_RTSP_RTCP_Video,
    ANTS_RTSP_RTCP_Audio,
}ANTS_RTSP_RTCPTYPE;
typedef enum
{
    ANTS_RTSP_STATUS_Connected,
    ANTS_RTSP_STATUS_Disconnected,
    ANTS_RTSP_STATUS_Error,
    ANTS_RTSP_STATUS_RECONNECT,
    ANTS_RTSP_STATUS_BUFFERFILL, // 缓冲自上次空了后，第一次有数据填充
    ANTS_RTSP_STATUS_BUFFERFULL,
}ANTS_RTSP_STATUS_TYPE;
typedef enum
{
    ANTS_RTSP_ERROR_NoError = 0,
    ANTS_RTSP_ERROR_NoAnyData,
    ANTS_RTSP_ERROR_MallocError,
    ANTS_RTSP_ERROR_BufferTooSmall,
    ANTS_RTSP_ERROR_SocketClose,
    ANTS_RTSP_ERROR_SocketError = 5,
    ANTS_RTSP_ERROR_InvSeqNo,
    ANTS_RTSP_ERROR_ResError,
    ANTS_RTSP_ERROR_ParseError,
    ANTS_RTSP_ERROR_InvSdpParam,
    ANTS_RTSP_ERROR_SDP_PlayloadType = 10,
    ANTS_RTSP_ERROR_SDP_Rtpmap,
    ANTS_RTSP_ERROR_InvSessionID,
    ANTS_RTSP_ERROR_InvTransPort,
    ANTS_RTSP_ERROR_InvStreamDataLen,
    ANTS_RTSP_ERROR_Authenticate = 15,
    ANTS_RTSP_ERROR_NoSupportIPV6,
    ANTS_RTSP_ERROR_InvalidMulticast,
    ANTS_RTSP_ERROR_DisMatchPlayloadType = 18,
}ANTS_RTSP_ERROR_TYPE;

typedef struct
{
    int nStatusType; // ANTS_RTSP_STATUS_TYPE
    int nStatusCode; // ANTS_RTSP_ERROR_TYPE
    unsigned char byOPResult;// 0- 默认操作，1-忽略状态
    unsigned char byRes[3];
    int nRes[5];
}ANTS_RTSP_STATUS_T;

#ifndef __ANTS_RTSP_DAYTIME__
#define __ANTS_RTSP_DAYTIME__
typedef struct _Ants_RtspDayTime
{
    unsigned short wYear;
    unsigned char byMon;
    unsigned char byDay;

    unsigned char byHour;
    unsigned char byMin;
    unsigned char bySec;
    unsigned char byZone;

    unsigned short wMsec;
    unsigned short wRes;

}Ants_RtspDayTime;
#endif
#ifndef ANTS_RTSP_ANTS_HEADER_DEFINE
#define ANTS_RTSP_ANTS_HEADER_DEFINE
#pragma pack(push,1)
typedef  struct _tagAudioHeader{
    char cCodecId;			//!音频编码类型
    char cSampleRate;			//!采样率
    char cBitRate;				//!比特率
    char cChannels;			//!通道数
    char cResolution;			//!分辨力
    char cResv[3];			//!保留位
}AntsAudioHeader,*pAntsAudioHeader;

typedef  struct _tagVideoHeader{
    unsigned short usWidth;				//!视频宽度
    unsigned short usHeight;				//!视频高度
    char cCodecId;				//!视频编码类型
    char cColorSpace;         // 0-yuv420,1-yuv422,2-444
    char cResv[2];					//!保留位
}AntsVideoHeader,*pAntsVideoHeader;

typedef  struct _tagANTSAPPHeader{
    unsigned char byAppPayloadType;				//!APP 负载类型
    unsigned char byAppNameLen;                 //! APP 名称长度,接在帧头之后，数据之前,最大255个字节 nul结束
    unsigned char byRes[6];
}AntsAppHeader,*pAntsAppHeader;

typedef  struct _tagAntsFrameHeader{
    unsigned int uiStartId;					//!帧同步头
    unsigned int uiFrameType;				//!帧类型
    unsigned int uiFrameNo;				//!帧号
    unsigned int uiFrameTime;				//!UTC时间
    unsigned int uiFrameTickCount;			//!毫秒为单位的毫秒时间
    unsigned int uiFrameLen;				//!帧载长度
    //!联合体,用于存储音频帧或是视频帧信息
    union {
        AntsAudioHeader struAudioHeader;	//!音频帧信息
        AntsVideoHeader struVideoHeader;	//!视频帧信息
        AntsAppHeader   struAppHeader;
    }uMedia; // 8bytes
    //unsigned char ucReserve[4];				//!保留位		
    unsigned int uiTimeStamp;
}AntsFrameHeader,*pAntsFrameHeader;

typedef  struct _tagAntsFileHeader{
    unsigned int uiFileStartId;				//!文件起始头标记
    unsigned int uiStreamType;				//!流方式
    unsigned int uiFrameRate;				//!帧率
    unsigned int uiReserve[4];				//!保留位	
}AntsFileHeader,*pAntsFileHeader;

typedef enum {
    AntsH264_hisi=1,//base/main
    AntsMJPEG_hisi=2,
    AntsH264_advance=3,
    AntsH264_hisi_high=4,//high
    AntsH264_hisi_RTP=8,//high
    AntsH264_RTP_PACK=9, // 
    AntsH265=16, // 
    AntsH265_RTP_PACK=17, // 
}eAntsVideoCodecId;

typedef enum{
    AntsOggVorbis=0,
    AntsG711A=1,
    AntsG711U=2,
    AntsG722Ex=3,
    AntsG726Ex=4,
    AntsADPCM=8,
}eAntsVoiceCodecId;

#pragma pack(pop)

typedef enum {
    //!主码流帧类型
    AntsPktError=0x0,
    AntsPktIFrames=0x01,
    AntsPktAudioFrames=0x08,
    AntsPktPFrames=0x09,
    AntsPktBBPFrames=0x0a,
    AntsPktMotionDetection=0x0b,
    AntsPktDspStatus=0x0c,
    AntsPktOrigImage=0x0d,
    AntsPktSysHeader=0x0e,
    AntsPktBPFrames=0x0f,
    AntsPktSFrames=0x10,
    //!子码流帧类型
    AntsPktSubSysHeader=0x11,
    AntsPktSubIFrames=0x12,
    AntsPktSubPFrames=0x13,
    AntsPktSubBBPFrames=0x14,
    //!智能分析信息帧类型
    AntsPktVacEventZones=0x15,
    AntsPktVacObjects=0x16,
	
//zhangw:这是在接入智能帧数据时加入的	
	//!第三码流帧类型
	AntsPktThirdSysHeader=0x17,
	AntsPktThirdIFrames=0x18,
	AntsPktThirdPFrames=0x19,
	AntsPktThirdBBPFrames=0x1a,

	//!智能检测帧类型
	AntsPktSmartIFrames=0x1b,
	AntsPktSmartPFrames=0x1c,
//zhangw

    // APP metedata帧.
    AntsPktAppFrames=0x20,
    // AntsComb 帧
    AntsPktAntsCombFrames=0x21,
}eAntsFrameType;

//#define ANTS_FRAME_STARTCODE    0xAB010000
//#define ANTS_FILE_STARTCODE    0xAA010000
#define ANTS_MOTION_STARTCODE    0xAC010000
#define ANTS_APP_STARTCODE    0xAD010000
#endif

// 应用生效序号如何处理?
typedef enum
{
    ANTS_RTSP_CONTROL_CMD_START = 1, // 开始连接服务器.
    ANTS_RTSP_CONTROL_CMD_PAUSE,// 暂停
    ANTS_RTSP_CONTROL_CMD_PLAY,//播放 (int)=0默认1x正放 >0 正放:1-1x,2-2x,3-3x... < 0 倒放:-1 1x,-2 2X,-3 3X...
    ANTS_RTSP_CONTROL_CMD_SEEK, // seek,Ants_RtspDayTime *pSeekTime
    ANTS_RTSP_CONTROL_CMD_RATECONTROL = 5, // 设定服务器是否控制速率(int) 0-服务器不控制速率，1-服务器控制速率
    ANTS_RTSP_CONTROL_CMD_ONLYIFRAME, // (int)只要I帧,0-所有帧,1-只I帧
    ANTS_RTSP_CONTROL_CMD_STEP,       // 单帧进
    ANTS_RTSP_CONTROL_CMD_RCVBUFFSIZE, // 设置接收缓冲大小
    ANTS_RTSP_CONTROL_CMD_TALKDATA = 20, // 语音对讲数据
    ANTS_RTSP_CONTROL_CMD_ANTSCOMB_ADDCH, // pInBuffer = int ch[] ,主码流是正，子码流是负,nInSize = count
    ANTS_RTSP_CONTROL_CMD_ANTSCOMB_DELCH
}ANTS_RTSP_CONTROL_CMD_TYPE;

//!预览回调函数
#define ANTS_RTSP_DATATYPE_STATUS				            0		//! 状态  ANTS_RTSP_STATUS_T
#define ANTS_RTSP_DATATYPE_SYSHEAD							1		//!系统头数据
#define ANTS_RTSP_DATATYPE_STREAMDATA						2		//!视频流数据（包括复合流和音视频分开的视频流数据）
#define ANTS_RTSP_DATATYPE_AUDIOSTREAMDATA			        3		//!音频流数据
#define ANTS_RTSP_DATATYPE_STD_VIDEODATA				    4		//!标准视频流数据
#define ANTS_RTSP_DATATYPE_STD_AUDIODATA				    5		//!标准音频流数据
#define ANTS_RTSP_DATATYPE_TALK_AUDIODATA				    6		//!对讲音频流数据
#define ANTS_RTSP_DATATYPE_STREAMDATA_ANTSCOMB				7		//! 多通道复合数据



#ifdef __cplusplus
extern "C" {
#endif

typedef int (*ANTS_RTSPCLIENTCALLBACK) (int hRtspHandle,ANTS_RTPClientCallbackType nCallbackType,int nSubType,int nDataType, void *pData,int nDataLen,void *pUserData);
typedef void (*ANTS_RTSPREALDATACALLBACKFXN)(long lRealHandle,unsigned long dwDataType,unsigned char *lpBuffer,unsigned long dwBufSize,void* lpUser);


    int Ants_RTSPClient_Init(int bUnInit);
    int Ants_RTSPClient_Open(char *pUrl,ANTS_RTPTransProto nProto,ANTS_RTSPCLIENTCALLBACK pCallback,char *pUserName,char *pPassword,void *pUserData);
    int Ants_RTSPClient_Open_Ex(char *pUrl,ANTS_RTPTransProto nProto,ANTS_RTSPREALDATACALLBACKFXN pCallback,char *pUserName,char *pPassword,void *pUserData);
    /*********
    *Ants_RTSPClient_Open_Ex与Ants_RTSPClient_Open区别是回调函数不同
    *Ants_RTSPClient_Open_Ex2是天视通专用接口
    */
    int Ants_RTSPClient_Open_Ex2(char *pUrl,ANTS_RTPTransProto nProto,ANTS_RTSPREALDATACALLBACKFXN pCallback,char *pUserName,char *pPassword,void *pUserData);
    int Ants_RTSPClient_GetTstConfig(int hRtspHandle,int *pVideoType,int *pAudioType,char *pConfig,int nConfigBufsize,int *pWidth,int *pHeight,int *pFrameFrate);
    int Ants_RTSPClient_Close(int hRtspHandle);

    // dwProp : bit0(内存管理模式:0-由调用者释放，1-由被调用者释放); 
    //   dwDataType==ANTS_RTSP_DATATYPE_STREAMDATA_ANTSCOMB时       bit8-15: nStreamIdx,bit16-31:nChan
    // 历史流时,dwDataType==ANTS_RTSP_DATATYPE_STREAMDATA,bit16-31:=dwApplyID表示命令起作用的ID。由Control接口设定
typedef void (*ANTS_RTSPREALDATACALLBACKFXN_V2)(long hRtspHandle,unsigned long dwDataType,unsigned long dwProp,unsigned char *lpBuffer,unsigned long dwBufSize,void* lpUser);
    // dwProp : bit0(内存管理模式:0-由调用者释放，1-由被调用者释放) ; bit1(0-一般接口，1-天视能专用接口) ,
    // bit2(0-实时流，1-历史流),历史流时，不自动连接，需要用开始命令来连接；也不会自动重连。
    // [bit3-视频,bit4-音频,bit5-onvif metedata (bit[3-5]可或操作,全不设定时即默认开启音/视频)] 
    // bit6-语音对讲
    // bit7-: 0-自动连接 ,1-不自动连接
    // bit8: 0- 流回调方式,1-流读取方式
    // bit9: 0-自动重连，1-不自动重连(语音对讲/回放，默认不重连)
    // bit24-31:nPhyIdx, 0- 默认网关，1-eth0,2-eth1
    int Ants_RTSPClient_Open_V2(char *pUrl,ANTS_RTPTransProto nProto,unsigned long dwProp,ANTS_RTSPREALDATACALLBACKFXN_V2 pCallback,char *pUserName,char *pPassword,void *pUserData);
    // dwApplyID:设定命令生效的ID,16bits，保证唯一值即可。
    int Ants_RTSPClient_Control(int hRtspHandle,int nCmd,unsigned long dwApplyID,void *pInBuffer,int nInSize,void *pOutBuffer,int nOutSize);

    // nChan: 
    // nStream: 
    // nStreamType: 0-视频,1-音频,2-对讲,3-app
    // 返回:当前缓冲中帧数(包括正在读取的帧)
    int Ants_RTSPClient_Read(long hRtspHandle,int *nChan,int *nStream,int *nStreamType,unsigned char **lpBuffer,unsigned long *dwBufSize);
    int Ants_RTSPClient_ReadRelease(long hRtspHandle);

#ifdef __cplusplus
}
#endif
#endif 