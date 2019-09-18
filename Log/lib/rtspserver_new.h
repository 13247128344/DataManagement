#ifndef _RTSPSERVERNEW_H_
#define _RTSPSERVERNEW_H_




#ifdef WIN32
//typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#include <sys/types.h>
#endif


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

} Ants_RtspDayTime;
#endif


#ifndef ANTS_RTSP_ANTS_HEADER_DEFINE
#define ANTS_RTSP_ANTS_HEADER_DEFINE
#pragma pack(push,1)
typedef  struct _tagAudioHeader{
    char cCodecId;			//!��Ƶ��������
    char cSampleRate;			//!������
    char cBitRate;				//!������
    char cChannels;			//!ͨ����
    char cResolution;			//!�ֱ���
    char cResv[3];			//!����λ
}AntsAudioHeader,*pAntsAudioHeader;

typedef  struct _tagVideoHeader{
    unsigned short usWidth;				//!��Ƶ���
    unsigned short usHeight;				//!��Ƶ�߶�
    char cCodecId;				//!��Ƶ��������
    char cColorSpace;         // 0-yuv420,1-yuv422,2-444
    char cResv[2];					//!����λ
}AntsVideoHeader,*pAntsVideoHeader;

typedef  struct _tagANTSAPPHeader{
    unsigned char byAppPayloadType;				//!APP ��������
    unsigned char byAppNameLen;                 //! APP ���Ƴ���,����֡ͷ֮������֮ǰ,���255���ֽ� nul����
    unsigned char byRes[6];
}AntsAppHeader,*pAntsAppHeader;

typedef  struct _tagAntsFrameHeader{
    unsigned int uiStartId;					//!֡ͬ��ͷ
    unsigned int uiFrameType;				//!֡����
    unsigned int uiFrameNo;				//!֡��
    unsigned int uiFrameTime;				//!UTCʱ��
    unsigned int uiFrameTickCount;			//!����Ϊ��λ�ĺ���ʱ��
    unsigned int uiFrameLen;				//!֡�س���
    //!������,���ڴ洢��Ƶ֡������Ƶ֡��Ϣ
    union {
        AntsAudioHeader struAudioHeader;	//!��Ƶ֡��Ϣ
        AntsVideoHeader struVideoHeader;	//!��Ƶ֡��Ϣ
        AntsAppHeader   struAppHeader;
    }uMedia; // 8bytes
    //unsigned char ucReserve[4];				//!����λ		
    unsigned int uiTimeStamp;
}AntsFrameHeader,*pAntsFrameHeader;

typedef  struct _tagAntsFileHeader{
    unsigned int uiFileStartId;				//!�ļ���ʼͷ���
    unsigned int uiStreamType;				//!����ʽ
    unsigned int uiFrameRate;				//!֡��
    unsigned int uiReserve[4];				//!����λ	
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
    AntsSVAC=20, // 
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
    //!������֡����
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
    //!������֡����
    AntsPktSubSysHeader=0x11,
    AntsPktSubIFrames=0x12,
    AntsPktSubPFrames=0x13,
    AntsPktSubBBPFrames=0x14,
    //!���ܷ�����Ϣ֡����
    AntsPktVacEventZones=0x15,
    AntsPktVacObjects=0x16,
    // APP metedata֡.
    AntsPktAppFrames=0x20,
    // AntsComb ֡
    AntsPktAntsCombFrames=0x21,
}eAntsFrameType;
#define ANTS_FRAME_STARTCODE    0xAB010000
#define ANTS_FILE_STARTCODE    0xAA010000
#define ANTS_MOTION_STARTCODE    0xAC010000
#define ANTS_APP_STARTCODE    0xAD010000
#endif

typedef struct _Ants_RTSPV2_InParam
{
    char *pUrl;
    unsigned int dwClientIP;
    short wRemotePort;
    short wSize; // �ṹ��С
    unsigned int dwSessionID;// �ỰID
    char *pRequire; // ˫����  ʱ��Ч

    int bRecording;// �ط�����.
    int nStreamType;// 0-VA,1-V,2-A,3-VA
    int nChan; // 0,1,2...ͨ��
    int nStream;//0,1,��/������
    int bRateControl;// -1 ��ֵ�����ڣ�����ͬ1(����ʵʱ��)��0- �ͻ��˿��ƻط��ٶ�,�����������ܿ�ķ�������;1-���������ƻط��ٶ�
    // �ط�ʱΪ0;
    int nFrame:8; // 0-all ;1-I Frame,2- I+P Frame
    int nInterval:24;// msec I֡�����Сʱ��.bFrame = 1ʱ��Ч.
    int nScale;
    int bPause;// 0��Ч,1-��ͣ
    int nPlaySeq;
    int bRangeValid;// bit0-start,bit1-stop
    Ants_RtspDayTime tRangeStart;
    Ants_RtspDayTime tRangeStop;

    int nAppPayloadType;
    int nAntsComb;
    char *pChChange;    
} Ants_RTSPV2_InParam_T;

typedef struct _Ants_RTSPV2_OutParam
{
    int nRet;// 0- �ɹ�,
    int hStreamHandle;
    char *pDescribe;
    int nRequireType;// �Ƿ����REQUIRE;���pRequire��Ч�Ļ�������Ҫ����,������Ϊ��֧�ֶ��ر���. 0- ������/��Ч;1-��Ƶ,2-��Ƶ;3-����Ƶ
    int nRequireVideoType;
    int nRequireAudioType;

    int nCh;
    int nStream;
} Ants_RTSPV2_OutParam_T;

typedef struct _Ants_RTSPV2_AuthInParam
{
    char *pUrl;
    unsigned int dwClientIP;
    short wRemotePort;
    short wSize; // �ṹ��С
    unsigned int dwSessionID;// �ỰID
    char *pUserName;// ��֤�û���,����ΪNULL
    int bRecording;// �ط�����.
      
} Ants_RTSPV2_AuthInParam_T;

typedef struct _Ants_RTSPV2_AuthOutParam
{
    int nAuthType; // -1: ����֤,0:�Զ�(�ɿͻ��˾���),1:base64,2:http-Digest(ǿ��)
    char *pUserName;// ��֤�û���,����ΪNULL,malloc
    char *pPassword; // ��Ӧ������ ,malloc

} Ants_RTSPV2_AuthOutParam_T;


typedef struct
{
    unsigned int  uiFrameType;
    unsigned int  uiCodecID;
    unsigned int  uiWidth;
    unsigned int  uiHeight;
    unsigned int  timestamp;
    unsigned short wCh;
    unsigned char byStream;
    unsigned char unRes[29];
} rtsp_stream_info;


#ifndef ANTS_RTSP_COM_DEFINE
#define ANTS_RTSP_COM_DEFINE

#define MAX_RTSPSERVER_NUM     10
#define MAX_RTSPSERVER_STREAM_NUM     512

#define ANTS_RTSPSERVER_PAYLOADTYPE_G711U             (0)
#define ANTS_RTSPSERVER_PAYLOADTYPE_G711A             (8)
#define ANTS_RTSPSERVER_PAYLOADTYPE_MJPEG             (26)
#define ANTS_RTSPSERVER_PAYLOADTYPE_H264             (96)
#define ANTS_RTSPSERVER_PAYLOADTYPE_G726_16             (97)
#define ANTS_RTSPSERVER_PAYLOADTYPE_H265             (98)
#define ANTS_RTSPSERVER_PAYLOADTYPE_AAC             (99)
#define ANTS_RTSPSERVER_PAYLOADTYPE_APP             (106)
#define ANTS_RTSPSERVER_PAYLOADTYPE_ANTSCOMB         (110) // name="AntsComb"



//������

#define ANTS_RTSPSERVER_STREAMTYPE_ALL             0
#define ANTS_RTSPSERVER_STREAMTYPE_VIDEO           1
#define ANTS_RTSPSERVER_STREAMTYPE_AUDIO           2
#define ANTS_RTSPSERVER_STREAMTYPE_APP              4

#define ANTS_RTSPSERVER_FRAMETYPE_IFRAME           1
#define ANTS_RTSPSERVER_FRAMETYPE_PFRAME           2
#define ANTS_RTSPSERVER_FRAMETYPE_BFRAME           3

#define ANTS_RTSPSERVER_FRAMETYPE_AUDIO            8

#define ANTS_RTSPSERVER_FRAMETYPE_XML              10



//Դ����
#define ANTS_RTSPSERVER_SOURCETYPE_LIVE            (0)
#define ANTS_RTSPSERVER_SOURCETYPE_FILE            (1)
#define ANTS_RTSPSERVER_SOURCETYPE_BACK            (2)

//�ص�����

// ��֪�ϲ㵱ǰ�����URL,
// hRtspHandle:RTSP���������
// hStreamHandle:����
// pInParam:Ants_RTSPV2_InParam_T
// pOutParam:Ants_RTSPV2_OutParam_T
// ���أ�0-�ɹ���-1ʧ��

#define ANTS_RTSPSERVER_CALLBACK_TYPE_OPEN_URL  1 // ����,�����ڴ���Ӧ�������û�д򿪵Ļ�
#define ANTS_RTSPSERVER_CALLBACK_TYPE_CLOSE_URL  2 // �ر���,�����ڹر���Ӧ�������û�������Ự��ʹ�õĻ�

#define ANTS_RTSPSERVER_CALLBACK_TYPE_SET_PARAM  3
#define ANTS_RTSPSERVER_CALLBACK_TYPE_SET_APP    4

#define ANTS_RTSPSERVER_CALLBACK_TYPE_ADDCH    5 // ���ͨ��
#define ANTS_RTSPSERVER_CALLBACK_TYPE_DECCH    6 // ����ͨ��

#define ANTS_RTSPSERVER_CALLBACK_TYPE_PLAYING   8 //��ʼPlay��������ǿ�ƹؼ�֡
#define ANTS_RTSPSERVER_CALLBACK_TYPE_STOPPING  9 //ֹͣ����

#define ANTS_RTSPSERVER_CALLBACK_TYPE_AUTH     10 // ��֤

#define ANTS_RTSPSERVER_CALLBACK_TYPE_SENDFAIL_ASKING  16 //��������ʧ��,ѯ���Ƿ��������,����0-�����ͣ�1-��������


// ��������
#define ANTS_RTSPSERVER_DATATYPE_SYSHEAD							1		//!ϵͳͷ����
#define ANTS_RTSPSERVER_DATATYPE_STREAMDATA						2		//!��Ƶ�����ݣ�����������������Ƶ�ֿ�����Ƶ�����ݣ�
#define ANTS_RTSPSERVER_DATATYPE_AUDIOSTREAMDATA			        3		//!��Ƶ������
#define ANTS_RTSPSERVER_DATATYPE_STD_VIDEODATA				    4		//!��׼��Ƶ������
#define ANTS_RTSPSERVER_DATATYPE_STD_AUDIODATA				    5		//!��׼��Ƶ������
#define ANTS_RTSPSERVER_DATATYPE_TALK_AUDIODATA				    6		//!�Խ���Ƶ������




// ���Կͻ��˵���(˫����)
// dwSessionID��ĳ���ỰID
typedef void (*ANTS_RTSPSERVER_STREAMDATA)(int hStreamHandle,unsigned int dwSessionID,unsigned long dwDataType,unsigned long dwProp,unsigned char *lpBuffer,unsigned long dwBufSize,void* lpUser);


typedef int (*ANTS_RTSPSTATUSCALLBACK) (int hRtspHandle,int hSessionHandle,int nType, void *pInParam,void *pOutParam,void *pUser);
#endif
// �����ݻص�
// ����ֵ:0-�ɹ�,-1ʧ��,
typedef int (*ANTS_RTSP_CALLBACK_OPEN) (int hRtspHandle,int hStreamHandle,void *pInParam,void *pOutParam,void **pStreamUser,void *pUser);

typedef int (*ANTS_RTSP_CALLBACK_CLOSE) (int hRtspHandle,int hStreamHandle,void *pStreamUser,int nStreamType,char *pUrl);
typedef int (*ANTS_RTSP_CALLBACK_CONTROL) (int hRtspHandle,int hStreamHandle,int nType,void *pInParam,void *pOutParam,void *pStreamUser);

typedef int (*ANTS_RTSP_CALLBACK_READ) (int hRtspHandle,int hStreamHandle,void *pStreamUser,int nStreamType,char **pData,int *pDataSize,void *pStreamInfo, int *nReadType, int *bAdpcm2G711u);
typedef int (*ANTS_RTSP_CALLBACK_READ_RELEASE) (int hRtspHandle,int hStreamHandle,void *pStreamUser,int nStreamType);


typedef struct
{
    ANTS_RTSP_CALLBACK_OPEN          fxnOpen;
    ANTS_RTSP_CALLBACK_CLOSE         fxnClose;
    ANTS_RTSP_CALLBACK_READ          fxnRead;
    ANTS_RTSP_CALLBACK_READ_RELEASE  fxnRelease;
    ANTS_RTSP_CALLBACK_CONTROL       fxnControl;
    unsigned char                    unRes[32];
} RTSPServer_StreamControl;


#ifdef __cplusplus
extern "C" {
#endif
int Ants_RTSPServerV2_Init();
//����RTSP������
int Ants_RTSPServerV2_Start(int nPort);//����handle

int Ants_RTSPServerV2_SetTunnelingOverHTTP(int hRtspHandle,int nHttpPort);
//������
// [rtsp,urtsp]://[ip,dnsname][:port]/file?ctype=[video;audio;videoback;audioback;appxxx]&stype=[unicast,multicast]&ptype=[tcp,http,udp]&ip=[224.x.x.x]&port=x
// �ط�
//  rtsp://192.168.25.84/recordstream?starttime=20140627T154000Z&endtime=20140627T154002Z // ����IPC
//  rtsp://192.168.25.84/recording?ch=0&stream=0&start=20140627154000&stop=20140627154002
//  rtsp://192.168.25.84/recording_comb?ch=0&stream=0&start=20140627154000&stop=20140627154002 // ��ͨ���ط�
//  rtsp://192.168.25.84/living_comb01.264 // ��ͨ��ʵʱ��

// "ANTS_ADDCH" "ANTS_DECCH"
// "Channel-Number: 3;9;11"
//int Ants_RTSPServer_CreateStream(int hRtspHandle,char *pToken,int bStreamType,int nVideoPayloadType,int nAudioPayloadType,int bFixed);//������handle

// ���ö����ݻص�
//
//int Ants_RTSPServer_SetReadDataCallback(int hRtspHandle,int hStreamHandle,ANTS_RTSP_READDATA_CALLBACK fRead,ANTS_RTSP_READDATA_RELEASE_CALLBACK fRelease,void *pUser);
//


//��ӻ��߸ı�
int Ants_RTSPServerV2_AddAppStream(int hRtspHandle,int hSessionHandle,int nAppPayloadType,unsigned int dwClockRate,char *szAppName);
//ɾ��
//int Ants_RTSPServer_DeleteAppStream(int hStreamHandle,int nAppPayloadType);
//nCmdType:
//          1- ���������� ,ANTS_RTSPSERVER_STREAMTYPE_ALL/
//          2- ������Ƶ���������Զ� 1-�Զ�,0-���Զ�
//          3- ������Ƶ���������Զ� 1-�Զ�,0-���Զ�
//          4- ������Ƶ��������
//          5- ������Ƶ��������
//          6- ������Ϊ¼��Դ�� 0-ʵʱ��,1-��ʷ��
//          7- ���ò���Ӱ���play Seq; // �ӻص��еõ�
//          8- �����Ƿ���������ʧ�ܲ����Ƿ�ѯ��,0-���ʣ�1-��.
//          9- ����recordstream��ַ�Ƿ�Ϊ�µĻطŷ�ʽ,0-�Ϸ�ʽ��1-�·�ʽ���·�ʽ�����ڲ������õģ������ⲿ����.ʹ�ô�����ʱ����hStreamHandle=hRtspHandle
//          10-����֡��

int Ants_RTSPServerV2_SetConfig(int hRtspHandle,int hStreamHandle,int nCmdType,void *pData,int nDataSize);//
int Ants_RTSPServerV2_SetStreamInfo(int hRtspHandle, int hSessionHandle,int bStreamType,int nVideoPayloadType,int nAudioPayloadType);
int Ants_RTSPServerV2_InputDataEx(int hRtspHandle,int hStreamHandle,int nPayloadType,void *pData,int nDataSize,int64_t timestamp,int bRelTimeStamp);

// bTimeStampValid :bit0 - 1:Reltimestamp ��Ч; bit1 -1:AbstimestampSec/AbstimestampUSec ��Ч,����ʱ��һ�����ڻط�
int Ants_RTSPServerV2_InputDataV2(int hRtspHandle,int hStreamHandle,int nPayloadType,int nFrameType,void *pData,int nDataSize,uint32_t Reltimestamp,uint32_t AbstimestampSec,uint32_t AbstimestampUSec,int bTimeStampValid);

// "ANTSCOMB_ADDCH" "ANTSCOMB_DECCH"
// "Channel-Number: 3;9;11;-1"
// ���ı�ʾ������
// nType :0
// nChan/nStreamIdx:͸��
int Ants_RTSPServerV2_InputAntsCombData(int hRtspHandle,int hStreamHandle,int nType,int nChan,int nStreamIdx,void *pData,int nDataSize);

int Ants_RTSPServerV2_SetStatusCallBack(ANTS_RTSPSTATUSCALLBACK fxn,void *pUser);

// dwProp : bit0(�ڴ����ģʽ:0-�ɵ������ͷţ�1-�ɱ��������ͷ�);
// dwSessionID:-1�ܵĻص��������Ƕ�ĳһ���Ự���ûص�����״̬�ص���á�
int Ants_RTSPServerV2_SetStreamCallBack(int hRtspHandle,unsigned int dwSessionID,unsigned long dwProp,ANTS_RTSPSERVER_STREAMDATA fxn,void *pUser);
//������
int Ants_RTSPServerV2_InputData(int hRtspHandle,int hStreamHandle,void *pData,int nDataSize,int64_t timestamp,int bAudio,int bAdpcm2G711u);

int Ants_RTSPServerV2_InputAntsData(int hRtspHandle,int hStreamHandle,void *pData,int nDataSize,int bAdpcm2G711u);


// ָ��ĳ���ͻ��˻Ự
//int Ants_RTSPServer_InputDataBySession(int hStreamHandle,unsigned int dwSessionID,void *pData,int nDataSize,int64_t timestamp,int bAudio,int bAdpcm2G711u);
//int Ants_RTSPServer_InputAntsDataBySession(int hStreamHandle,unsigned int dwSessionID,void *pData,int nDataSize,int bAdpcm2G711u);
// �鲥
int Ants_RTSPServerV2_SetMulticastAddressIPv4(int hRtspHandle,int hSessionHandle,int bAudio,const char *pIP,int nPort,int nTTL);
//int Ants_RTSPServer_SetMulticastAddressIPv4NoApply(int hStreamHandle,int bAudio,const char *pIP,int nPort,int nTTL);

// hStreamHandle == -1:��ʾ���޹ء�
int Ants_RTSPServerV2_EnableMulticast(int hRtspHandle,int hSessionHandle,int bEnable);

int Ants_RTSPServerV2_CloseStream(int hRtspHandle, int hSessionHandle);
//������
//int Ants_RTSPServer_DestroyStreamByToken(char *pToken);
//int Ants_RTSPServer_DestroyStreamByHandleToken(int hRtspHandle,char *pToken);
//int Ants_RTSPServer_DestroyStream(int hStreamHandle);
//����RTSP������
int Ants_RTSPServerV2_Stop(int hRtspHandle);



int Ants_RTSPServerV2_SetStreamControlCallBack(int hRtspHandle, RTSPServer_StreamControl *pStreamControl, void *pUser);

#ifndef ANTS_RTSP_COM_INTERFACE_DEFINE
#define ANTS_RTSP_COM_INTERFACE_DEFINE
typedef struct  _tagANTS_RTSP_H264_RTP_PARAM
{
    // input params
     int nMTUSize; // <= 1500
     int nWidth;
     int nHeight;
     uint8_t *pInData[16];
     int nInDataSize[16];
     int nInCount;
     int bIFrame;
     uint32_t Reltimestamp;
     uint32_t AbstimestampSec;
     uint32_t AbstimestampUSec;
     uint8_t *pOutData;// out,1Mbytes
     int nOutSize; // in/out
     uint32_t dwSSRC;
     uint32_t dwCodecType; // 0-264,1-265,2-g711u,3-g711a,4-mjpeg
     uint32_t dwRes[7];
     

     // ----no change---
     uint32_t dwFrameNo;
     int nStartIdx;
     int nStartPos;
     int nStopIdx;
     int nStopPos;
     uint16_t wSeq;
     int discontinuity;
     int eSectionEnd;
     int cIFrameStart;
     uint32_t ntpTimeStamp0;
     uint32_t ntpTimeStamp1;
     int nWritePos;
     uint32_t dwRes1[8];
}ANTS_RTSP_H264_RTP_PARAM_T;
// 264 �ӿڿ���ͨ������������
int Ants_RTSPServer_H264toRTP_InputData(ANTS_RTSP_H264_RTP_PARAM_T *pParam);
int Ants_RTSPServer_H265toRTP_InputData(ANTS_RTSP_H264_RTP_PARAM_T *pParam);

typedef struct  _tagANTS_RTSP_RTP_H264_PARAM
{
    // input params
    uint8_t *pInData;
    int nInDataSize;

  
    uint8_t *pOutData;// out,1Mbytes
    int nOutSize; // in/out
    uint8_t byRes[32];

}ANTS_RTSP_RTP_H264_PARAM_T;
int Ants_RTSPServer_RTPtoH264_InputData(ANTS_RTSP_RTP_H264_PARAM_T *pParam);
int Ants_RTSPServer_RTPtoH265_InputData(ANTS_RTSP_RTP_H264_PARAM_T *pParam);

int64_t Ants_RTSPServer_GetCurrentTime();

void Ants_RTSPServer_WaitTime(int nSec,int MicroSec);

#endif


#ifdef __cplusplus
}
#endif

#endif

