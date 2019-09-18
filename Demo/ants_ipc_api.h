#ifndef __ANTS_IPC_API_H__
#define __ANTS_IPC_API_H__

#ifdef WIN32
typedef __int64 S64;
typedef unsigned __int64 U64;

#else
typedef long long S64;
typedef unsigned long long U64;

#endif
typedef int S32;
typedef char S8;
typedef short S16;

typedef unsigned int U32;
typedef unsigned char U8;
typedef unsigned short U16;

typedef float F32;
typedef double F64;

//typedef void VOID;
#ifndef VOID
#define VOID void
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif


#define ANTS_IPC_FOURCC(c0,c1,c2,c3) ((c0)|(c1 << 8) |(c2 << 16) | (c3 << 24))

//#define DEBUGPRINT
#ifdef DEBUGPRINT

#define IPC_TRACE_INFO(x...) 		do{printf("[INFO.%s.%d][%s]",__FUNCTION__,__LINE__,IPC_NAME);printf(x);}while(0)
#define IPC_TRACE_ERROR(x...)		do{printf("[ERR .%s.%d][%s]",__FUNCTION__,__LINE__,IPC_NAME);printf(x);}while(0)
#define IPC_TRACE_DEBUG(x...)		do{printf("[DBG .%s.%d][%s]",__FUNCTION__,__LINE__,IPC_NAME);printf(x);}while(0)
#define IPC_TRACE_WARN(x...)		do{printf("[WARN.%s.%d][%s]",__FUNCTION__,__LINE__,IPC_NAME);printf(x);}while(0)
#define IPC_TRACE_FATAL(x...)		do{printf("[FATL.%s.%d][%s]",__FUNCTION__,__LINE__,IPC_NAME);printf(x);}while(0)

#else
#define IPC_TRACE_INFO(x)
#define IPC_TRACE_ERROR(x)
#define IPC_TRACE_DEBUG(x)
#define IPC_TRACE_WARN(x)
#define IPC_TRACE_FATAL(x)
#endif




// ֧�ֵİ汾
#define ANTS_IPC_VERSION  0x00010000
#define ANTS_IPC_VERSION1 0x00010001

#define ANTS_IPC_VERSION_MAX ANTS_IPC_VERSION1








//����IPCЭ��
#define ANTS_IPC_FLAG0 ANTS_IPC_FOURCC('A','N','T','S')
#define ANTS_IPC_FLAG1 ANTS_IPC_FOURCC('I','P','C','P')



// �����ļ�ͷ��֡ͷ
#pragma pack(push,1)
#ifndef ANTS_FRAME_STARTCODE
#define ANTS_FRAME_STARTCODE 					(0xAB010000)
#endif

#ifndef ANTS_FILE_STARTCODE
#define ANTS_FILE_STARTCODE 					(0xAA010000)
#endif

typedef enum {
	//!������֡����
	AntsIPCFrameType_Error=0x00,
	AntsIPCFrameType_IFrames=0x01,
	AntsIPCFrameType_AudioFrames=0x08,
	AntsIPCFrameType_PFrames=0x09,
	AntsIPCFrameType_BBPFrames=0x0a,
	AntsIPCFrameType_MotionDetection=0x0b,
	AntsIPCFrameType_DspStatus=0x0c,
	AntsIPCFrameType_OrigImage=0x0d,
	AntsIPCFrameType_SysHeader=0x0e,
	AntsIPCFrameType_BPFrames=0x0f,
	AntsIPCFrameType_SFrames=0x10,
	//!������֡����
	AntsIPCFrameType_SubSysHeader=0x11,
	AntsIPCFrameType_SubIFrames=0x12,
	AntsIPCFrameType_SubPFrames=0x13,
	AntsIPCFrameType_SubBBPFrames=0x14,
	//!���ܷ�����Ϣ֡����
	AntsIPCFrameType_VacEventZones=0x15,
	AntsIPCFrameType_VacObjects=0x16,
	//!��������֡����
	AntsIPCFrameType_ThirdSysHeader=0x17,
	AntsIPCFrameType_ThirdIFrames=0x18,
	AntsIPCFrameType_ThirdPFrames=0x19,
	AntsIPCFrameType_ThirdBBPFrames=0x1a
}AntsIPCFrameType_E;


typedef enum{
	AntsIPCVoiceCodecID_OggVorbis=0,
	AntsIPCVoiceCodecID_G711A=1,
	AntsIPCVoiceCodecID_G711U=2,
	AntsIPCVoiceCodecID_G722Ex=3,
	AntsIPCVoiceCodecID_G726Ex=4
}AntsIPCVoiceCodecID_E;

typedef enum {
	AntsIPCVideoCodecID_H264_hisi=1,
	AntsIPCVideoCodecID_MJPEG_hisi=2,
	AntsIPCVideoCodecID_H264_hisi_high=4,
	AntsIPCVideoCodecID_H264_hisi_RTP=8,
}AntsIPCVideoCodecID_E;


typedef struct _tagAntsIPCAudioHeader{
	S8 cCodecId;			//!��Ƶ��������
	S8 cSampleRate;			//!������
	S8 cBitRate;				//!������
	S8 cChannels;			//!ͨ����
	S8 cResolution;			//!�ֱ���
	S8 cResv[3];				//!����λ
}AntsIPCAudioHeader_T;

typedef struct _tagAntsIPCVideoHeader{
	U16 usWidth;				//!��Ƶ���
	U16 usHeight;				//!��Ƶ�߶�
	S8 cCodecId;				//!��Ƶ��������
	S8 cResv[3];					//!����λ
}AntsIPCVideoHeader_T;

typedef struct _tagAntsIPCFrameHeader{
	U32 uiStartId;					//!֡ͬ��ͷANTS_FRAME_STARTCODE
	U32 uiFrameType;				//!֡����
	U32 uiFrameNo;					//!֡��
	U32 uiFrameTime;				//!UTCʱ��
	U32 uiFrameTickCount;			//!΢��Ϊ��λ��΢��ʱ��
	U32 uiFrameLen;				//!֡�س���
										//!������,���ڴ洢��Ƶ֡������Ƶ֡��Ϣ
	union {
		AntsIPCAudioHeader_T struAudioHeader;	//!��Ƶ֡��Ϣ
		AntsIPCVideoHeader_T struVideoHeader;	//!��Ƶ֡��Ϣ
	}uMedia;
	U32 dwTimeStamp;				//!���ʱ��� ms * 90		
}AntsIPCFrameHeader_T;

typedef struct _tagAntsIPCFileHeader{
	U32 uiFileStartId;				//!�ļ���ʼͷ���ANTS_FILE_STARTCODE
	U32 uiStreamType;				//!����ʽ
	U32 uiFrameRate;				//!֡��
	U32 uiReserve[4];				//!����λ	
}AntsIPCFileHeader_T;

#pragma pack(pop)

typedef struct _tagAntsIPCAlarmInfo
{
	U32 dwType;// 1- Motion,2-HideAlarm,3-AlarmIn
	U32 dwStatus; // 
	U32 dwParams[6];
}AntsIPCAlarmInfo_T;


//״̬����
typedef enum _tagAntsIPCStatusType
{
	AntsIPCStatusType_Connected = 1,
	AntsIPCStatusType_Disconnected,
	AntsIPCStatusType_LoginOk,
	AntsIPCStatusType_LoginFailed,
	AntsIPCStatusType_RealPlayOK,
	AntsIPCStatusType_RealPlayFailed,
}AntsIPCStatusType_T;

typedef enum _tagAntsIPCAlarmType
{
	AntsIPCAlarmType_No = 0,
	AntsIPCAlarmType_Motion =1,
	AntsIPCAlarmType_AlarmIn,
	AntsIPCAlarmType_VideoLoss,
	AntsIPCAlarmType_Mask,// �ڵ�����
	AntsIPCAlarmType_DiskFull,
	AntsIPCAlarmType_DiskError,
	AntsIPCAlarmType_IllegeAccess, // �Ƿ�����
	AntsIPCAlarmType_ReticleDisconnect, // ���߶�
	AntsIPCAlarmType_IpConelict, // IP��ͻ
	AntsIPCAlarmType_MAX,
}AntsIPCAlarmType_E;

typedef struct _tagAntsIPCStatusAlarm
{
	U32 dwAlarmType; // AntsIPCAlarmType_E
	U32 dwAlarmParam[32];// dwAlarmParam[0]��Դͨ��,dwAlarmParam[1]:�Ƿ񾯱�(0/1)
}AntsIPCStatusAlarm_T;

//��������
typedef enum _tagAntsIPCConfigCommand
{
	AntsIPCConfig_OSD                = 1, // OSD  AntsIPCOSD_T
	AntsIPCConfig_VideoEffect, 			  //���ȣ��Աȶȣ����Ͷ�...AntsIPCColor_T
	AntsIPCConfig_VideoEncode, 			  //��Ƶ����AntsIPCVideoEnc_T
	AntsIPCConfig_AudioEncode,            //��Ƶ����AntsIPCAudioEnc_T
	AntsIPCConfig_Motion             = 5, //�ƶ�AntsIPCMotion_T
	AntsIPCConfig_HideAlarm,              //�ڵ����� AntsIPCHideAlarm_T
	AntsIPCConfig_Shelter,                //�ڵ�AntsIPCShelter_T
	AntsIPCConfig_PTZDecoder,             //PTZ Decoder����AntsIPCPTZDecoder_T
	AntsIPCConfig_Time,                   // ʱ������AntsIPCTime_T
	AntsIPCConfig_Sensor             = 10,// Sensor����AntsIPCSensorCfg_T
	AntsIPCConfig_DeviceInfo,             // �豸��ϢAntsIPCDeviceInfo_T
	AntsIPCConfig_VideoEncodeV2, 			  //��Ƶ����AntsIPCVideoEncV2_T
}AntsIPCConfigCommand_E;
//���ýṹ





typedef struct _tagAntsIPCDeviceInfo
{
	
	S8	sDVRName[32];     //DVR����
	U32 dwDVRID;				//DVR ID,����ң����
	U32 dwRecycleRecord;		//�Ƿ�ѭ��¼��,0:����; 1:��

	//����ֻ��
	U8	sSerialNumber[48];  //���к�
	U32	dwSoftwareVersion;		//����汾��,��16λ�����汾,��16λ�Ǵΰ汾
	U32	dwSoftwareBuildDate;	//�����������,0xYYYYMMDD
	U32	dwDSPSoftwareVersion;	//DSP����汾,��16λ�����汾,��16λ�Ǵΰ汾
	U32	dwDSPSoftwareBuildDate;	// DSP�����������,0xYYYYMMDD
	U32	dwPanelVersion;			// ǰ���汾,��16λ�����汾,��16λ�Ǵΰ汾
	U32	dwHardwareVersion;		//Ӳ���汾,��16λ�����汾,��16λ�Ǵΰ汾
	U8	byAlarmInPortNum;		//DVR�����������
	U8	byAlarmOutPortNum;		//DVR�����������
	U8	byRS232Num;				//DVR 232���ڸ���
	U8	byRS485Num;				//DVR 485���ڸ���
	U8	byNetworkPortNum;		//����ڸ���
	U8	byDiskCtrlNum;			//DVR Ӳ�̿���������
	U8	byDiskNum;				//DVR Ӳ�̸���
	U8	byDVRType;				//DVR����, 1:DVR 2:NVR 3:IPC 4:DEC ......
	U8	byChanNum;				//DVR ͨ������
	U8	byStartChan;			//��ʼͨ����,����DVS-1,DVR - 1
	U8	byDecodeChans;			//DVR ����·��
	U8	byVGANum;				//VGA�ڵĸ���
	U8	byUSBNum;				//USB�ڵĸ���
    U8	byAuxoutNum;			//���ڵĸ���
    U8	byAudioNum;				//�����ڵĸ���
    U8	byIPChanNum;			//�������ͨ����
    U8  byRes[64];
}AntsIPCDeviceInfo_T;


// ->AntsIPCConfig_VideoEffect
typedef struct _tagAntsIPCColor
{
	S32	lBrightness;  	/*����,0-255,-1��֧�ֻ��߻ָ�Ĭ��*/
	S32	lContrast;    	/*�Աȶ�,0-255,-1��֧��*/	
	S32	lSaturation;  	/*���Ͷ�,0-255, -1��֧��*/
	S32	lHue;    		/*ɫ��,0-255,-1��֧��*/
}AntsIPCColor_T;


typedef struct _tagAntsIPCSensorDayNightMode
{
	S32 lDayNightMode;// -1--��֧��;0--�ⲿ�������;1--�Զ�ģʽ;2--ǿ�ư���;3--ǿ�ƺ�ҹ
	S32 lDelay ;// �Զ�ת���ӳ٣��Զ�ģʽ��Ч��0-30
	S32 lNighttoDayThreshold ;// �Զ�ת����ҹ���������ֵ0-255��Ĭ��0xEE
	S32 lDaytoNightThreshold ;// �Զ�ת�����쵽��ҹ����ֵ0-255��Ĭ��0x57
}AntsIPCSensorDayNightMode_T;


typedef struct _tagAntsIPCSensorCfg
{
	U32 dwSize;
	U32 dwValidMask;// ��Ӧλ0-��Ч��1-��Ч; 
	// bit0 - DayNightMode,bit1-lMinorMode,bit2-lGainMode,bit3-lAntiflickerMode,
	// bit4-lPicQualityMode,bit5-lWBMode   ,bit6-lBacklightMode,bit7-lShutterMode
	// bit8-lIrisMode         ,bit9-lSharpnessMode,bit10-l3DNRMode,bit11-3DNRTfode,
	// bit12-WDMode,bit13-GammaMode,bit14-AntiflickerFreqMode
	AntsIPCSensorDayNightMode_T DayNightMode;
	S32 lMinorMode ;//���� -1--��֧��;0--����;1--ˮƽ��ת;2--��ֱ��ת;3--180�㷭ת
	S32 lGainMode ;//���� -1--��֧��;0--��;1--��;2--��
	S32 lAntiflickerMode ;//���� -1--��֧��;0--��;1--��
	S32 lPicQualityMode ;//ͼ��Ч�� -1--��֧��;0--����;1--����;2--��Ȼ
	S32 lWBMode ;//��ƽ�� -1--��֧��;0--�Զ���ƽ��;1--����ģʽ;2--����ģʽ
	S32 lBacklightMode;// ���ⲹ��ģʽ-1--��֧��; 0--�ر�;1--BLC;2--HBLC
	S32 lShutterMode;// ����ģʽ -1--��֧��; 0--�Զ�����;
				/*����ģʽ:
				0x01:1/30(1/25), 
				0x02:1/60(1/50), 
				0x03:Flicker, 
				0x04:1/250, 
				0x05:1/500, 
				0x06:1/1000, 
				0x07:1/2000, 
				0x08:1/5000, 
				0x09:1/10000, 
				0x0A:1/50000, 
				0x0B:x2, 
				0x0C:x4, 
				0x0D:x6, 
				0x0E:x8, 
				0x0F:x10, 
				0x10:x15, 
				0x11:x20,
				0x12:x25,
				0x13:x30 */
	S32 lIrisMode;// ��ͷ��Ȧģʽ:-1--��֧��; 0--�Զ���Ȧ;1--�ֶ���̶���Ȧ
	S32 lSharpnessMode;// ���ģʽ: -1--��֧��;0--�ر�;1--��
	S32 lSharpnessLevel;// 0-100
	S32 l3DNRMode;// 3D����ģʽ : -1--��֧��;0--�ر�;1--��
	S32 l3DNRLevel;// 0-100
	S32 l3DNRTfode; // 3D����ʱ��-1--��֧�� 0--�ر�;1--��;2--��;3--�ϸ�;4--��
	S32 lWDMode; // ��̬ģʽ-1--��֧��0--�ر�;1--��;2--��;3--��
	S32 lGammaMode;// Gammaģʽ-1--��֧�� 0--Curve_1_6;1--Curve_1_6;2--Curve_2_0;3--Curve_2_2
	S32 lAntiflickerFreqMode; // ����ģʽ	-1--��֧��;0--�Զ�;1--50HZ;2--60HZ
	S32 lRes[1];
}AntsIPCSensorCfg_T;


// ->AntsIPCConfig_OSD
typedef struct _tagAntsIPCOSD
{ //  �����С704*576
	S8	sText[32]; // һ��Ϊͨ����
	
	//��ʾͨ����
	U32	dwShowOsd; 				// bit0:ͨ������ʾ,0-����ʾ,1-��ʾ;bit1:ʱ����ʾ0-����ʾ��1-��ʾ
	U32	dwTextTopLeftX;				/* ͨ��������ʾλ�õ�x���� */
	U32	dwTextTopLeftY;				/* ͨ��������ʾλ�õ�y���� */
	U32	dwTimeTopLeftX;					/* OSD��x���� */
	U32	dwTimeTopLeftY;					/* OSD��y���� */
	U32 dwTimeAttrib;// byte0:OSD��ʽ;byte1:�Ƿ���ʾ����,byte2:͸������,byte3:0-24Сʱ��,1-12Сʱ��
         /* OSD����(��Ҫ�������ո�ʽ) */
		/* 0: XXXX-XX-XX ������ */
		/* 1: XX-XX-XXXX ������ */
		/* 2: XXXX��XX��XX�� */
		/* 3: XX��XX��XXXX�� */
		/* 4: XX-XX-XXXX ������*/
		/* 5: XX��XX��XXXX�� */
}AntsIPCOSD_T;


typedef enum _tagAntsIPCResolution
{
	AntsIPCResolution_QQCIF = 1, // 88 x72
	AntsIPCResolution_SQCIF,     //128x96
	AntsIPCResolution_QQVGA,     //160x120
	AntsIPCResolution_QCIF,      //176x144
	AntsIPCResolution_SQVGA = 5,     //220x176
	AntsIPCResolution_QQ960H ,      //240x144
	AntsIPCResolution_QQ720P,       //320x180
	AntsIPCResolution_CGA,       //320x200
	AntsIPCResolution_QVGA,      //320x240
	AntsIPCResolution_CIF=10,       //352x288
	AntsIPCResolution_WQVGA ,     //480x240
	AntsIPCResolution_Q960H ,      //480x288
	AntsIPCResolution_HQVGA ,     //480x320
	AntsIPCResolution_DCIF,      //528x384
	AntsIPCResolution_VGA=15,       //640x480
	AntsIPCResolution_Q720P,       //640x360
	AntsIPCResolution_2CIF ,      // 704x288
	AntsIPCResolution_480P ,      // 720x 480
	AntsIPCResolution_4CIF ,       //704x576
	AntsIPCResolution_D1P=20,        //720x576
	AntsIPCResolution_SVGA,      //800x600
	AntsIPCResolution_960H ,      //960x576
	AntsIPCResolution_DVGA ,      //960x640
	AntsIPCResolution_XGA ,       //1024x768
	AntsIPCResolution_720P=25 ,      // 1280x720P
	AntsIPCResolution_720I,      // 1280x720I
	AntsIPCResolution_960P,    // 1280x960
	AntsIPCResolution_1024P ,    // 1280x1024
	AntsIPCResolution_UXGA ,      //1600x1200
	AntsIPCResolution_1080P=30 ,     // 1920x1080P
	AntsIPCResolution_1080I,     // 1920x1080I
	AntsIPCResolution_3MP,       // 2048x1536
	AntsIPCResolution_5MP ,       // 2592x1920
	AntsIPCResolution_USERDEFINE = 100
	
}AntsIPCResolution_E;
// ->AntsIPCConfig_VideoEncode
typedef struct _tagAntsIPCVideoEnc
{
	U8		byVideoEncType;		//��Ƶ��������: 0- ��֧��,1-h264;2-mpeg4;3-M-JPEG
	U8		byIntervalBPFrame;	//0- P֡,1-BP֡; 2-BP֡ (����)
	U8		byBitrateType;		//�������� 0:������, 1:������
	U8		byPicQuality;		//ͼ������ 0-��� 1-�κ� 2-�Ϻ� 3-һ�� 4-�ϲ� 5-��
	U8		byResolution;  		//�ֱ���0-�Զ���,AntsIPCResolution_E
	U32     dwResWidth;      //�ֱ��� ��,�Զ���ʱ����
	U32     dwResHeight;     // �ֱ��ʸ�
	U32		dwVideoBitrate; 	//��Ƶ���� kbps,���λΪ1ʱΪ�Զ��塣
	U32		dwVideoFrameRate;	//֡�� 0-��֡; 
	U32		dwIntervalFrameI;	//I֡���
 	
}AntsIPCVideoEnc_T;

typedef struct _tagAntsIPCVideoEncV2
{
	U8		byVideoEncType;		//��Ƶ��������: 0- ��֧��,1-h264;2-mpeg4;3-M-JPEG
	U8		byIntervalBPFrame;	//0- P֡,1-BP֡; 2-BP֡ (����)
	U8		byBitrateType;		//�������� 0:������, 1:������
	U8		byPicQuality;		//ͼ������ 0-��� 1-�κ� 2-�Ϻ� 3-һ�� 4-�ϲ� 5-��
	U8		byResolution;  		//�ֱ���0-�Զ���,AntsIPCResolution_E
	U32     dwResWidth;      //�ֱ��� ��,�Զ���ʱ����
	U32     dwResHeight;     // �ֱ��ʸ�
	U32		dwVideoBitrate; 	//��Ƶ���� kbps,���λΪ1ʱΪ�Զ��塣
	U32		dwVideoFrameRate;	//֡�� 0-��֡; 
	U32		dwIntervalFrameI;	//I֡���
 	U8		byVideoH264Profile;	 //��Ƶ��������: 0-Baseline;1-MainProfile;2-HighProfile
	U8      byRes[14];
}AntsIPCVideoEncV2_T;


// ->AntsIPCConfig_AudioEncode
typedef struct _tagAntsIPCAudioEnc
{
 	U8		byAudioEncType;		//��Ƶ�������� 0-��֧��;1-G711_U;2-G711_A,3-G726
 	U8      byAudioChan;//  ��Ƶͨ��,1-��ͨ��,
 	U8      byAudiobitWidth; // 8λ,16λ
 	U8      byEnable; // 0-�رգ�1-����
 	U32     dwSampleRate;// ������8K
 	U32     dwBitRate;// ����
}AntsIPCAudioEnc_T;

// ->AntsIPCConfig_Motion
typedef struct _tagAntsIPCMotion
{//22 x18
	U32      byEnable;//0-��ʹ�ܣ�1-ʹ��
	U32     dwMotionScope[2 * 64]; // ���֧�� 64x64,��λ
	U32     dwMotionSize;// ��16λ:��,��16λ����
	U32		byMotionSensitive;		/* �ƶ����������, 0 - 5,Խ��Խ���� */
}AntsIPCMotion_T;

// ->AntsIPCConfig_HideAlarm
typedef struct _tagAntsIPCHideAlarm
{// 704 x576
	U32	dwEnable;				/* �Ƿ������ڵ����� ,0-��,1-�������� 2-�������� 3-��������*/
	U16	wAreaTopLeftX;			/* �ڵ������x���� */
	U16	wAreaTopLeftY;			/* �ڵ������y���� */
	U16	wAreaWidth;			/* �ڵ�����Ŀ� */
	U16	wAreaHeight;			/* �ڵ�����ĸ�*/
}AntsIPCHideAlarm_T;

// ->AntsIPCConfig_Shelter
typedef struct _tagAntsIPCShelter
{
	//�ڵ�	�����С704*576
	U32	dwEnable;					/* �Ƿ������ڵ� ,0-��,1-��*/
	U32 dwTopLeftX[4];
	U32 dwTopLeftY[4];
	U32 dwWidth[4];
	U32 dwHeight[4];
}AntsIPCShelter_T;



typedef enum _tagAntsIPCAbilityType
{
	AntsIPCAbilityType_VideoEncode = 1,
	AntsIPCAbilityType_VideoEncode_TransType, // 0-��������1-��������2-�¼�����
	AntsIPCAbilityType_VideoEncode_StreamType, //0- ��Ƶ����1-������
	AntsIPCAbilityType_VideoEncode_MainResolution,
	AntsIPCAbilityType_VideoEncode_SubResolution = 5,
	AntsIPCAbilityType_VideoEncode_EventResolution,
	AntsIPCAbilityType_VideoEncode_BitrateType,//�����ʣ�������
	AntsIPCAbilityType_VideoEncode_Bitrate,
	AntsIPCAbilityType_VideoEncode_Framerate,
	AntsIPCAbilityType_VideoEncode_PicQuality = 10, // ��ã��κã��Ϻã�һ�㣬�ϲ��
	AntsIPCAbilityType_VideoEncode_EncType, // 0-H264,1-MPEG4,2-MJPEG
	AntsIPCAbilityType_VideoEncode_H264Profiles, // 0-Baseline,1-main,2-high
	AntsIPCAbilityType_AudioEncode_EncType, // 0-����Ƶ��֧��,1-G711u,2-G711a,3-G726
	AntsIPCAbilityType_PTZDecoderProtocol = 20,
}AntsIPCAbilityType_T;

typedef struct _tagAntsIPCAbilityNode
{
	// ֡��, 0-��֡
	U32 dwValue;// �����ʣ�-1Ϊ�Զ���,0-����
	S8  sDescribe[32];
}AntsIPCAbilityNode_T;

typedef struct _tagAntsIPCAbilityList
{
	U32	dwAbilityType;
	U32	dwNodeNum;
	AntsIPCAbilityNode_T tNode[256];
}AntsIPCAbilityList_T;

typedef struct _tagAntsIPCAbilitySets
{
	U32	dwAbilityNum;
	AntsIPCAbilityList_T tList[12];
}AntsIPCAbilitySets_T;


// ->AntsIPCConfig_PTZDecoder
//ͨ��������(��̨)��������
typedef struct _tagAntsIPCPTZDecoder
{
	U32	dwBaudRate;						//������(bps)��
	U8	byDataBit;						//�����м�λ5λ��6λ��7λ��8λ;
	U8	byStopBit;						//ֹͣλ :1λ��2λ;
	U8	byParity;						//У�� 0����У�飬1����У�飬2��żУ��;
	U8	byFlowcontrol;					//0���ޣ�1��������,2-Ӳ����
	U16	wDecoderType;					//����������  ����������õ�
	U16	wDecoderAddress;				/*��������ַ:0 - 255*/
}AntsIPCPTZDecoder_T;

//Уʱ�ṹ����
typedef struct _tagAntsIPCTime
{
	U32	dwYear;			//��
	U32	dwMonth;		//��
	U32	dwDay;			//��
	U32	dwHour;			//ʱ
	U32	dwMinute;		//��
	U32	dwSecond;		//��
	S32 dwZone;         //ʱ��
}AntsIPCTime_T;

typedef struct _tagAntsIPCRect
{
	S32 lx;
	S32 ly;
	S32 lw;
	S32 lh;
}AntsIPCRect;


//Զ�̿�������
typedef enum _tagAntsIPCControlCmd 
{
	AntsIPCControlCmd_PTZ = 2,
	AntsIPCControlCmd_Reboot = 10,
	AntsIPCControlCmd_Halt,
	AntsIPCControlCmd_EnableAlarm, // ���������� U32
	AntsIPCControlCmd_RemoteHistoryPlayControl=20,
	AntsIPCControlCmd_RemoteRecordControl=25, // Զ��¼�����
	AntsIPCControlCmd_VideoEffectDefault = 30, // �ָ�ͼ�����ΪĬ��ֵ
}AntsIPCControlCmd_E;


typedef enum _tagAntsIPCPTZCmd
{
	AntsIPCPTZCmd_LightPowerOn = 2,
	AntsIPCPTZCmd_WiperPowerOn,
	AntsIPCPTZCmd_FanPowerOn,
	AntsIPCPTZCmd_HeaterPowerOn = 5,
	AntsIPCPTZCmd_AuxPowerOn1,
	AntsIPCPTZCmd_AuxPowerOn2,
	AntsIPCPTZCmd_SetPreset,
	AntsIPCPTZCmd_ClearPreset,
	AntsIPCPTZCmd_ZoomIn = 11,
	AntsIPCPTZCmd_ZoomOut,
	AntsIPCPTZCmd_FocusNear,
	AntsIPCPTZCmd_FocusFar,
	AntsIPCPTZCmd_IrisOpen = 15,
	AntsIPCPTZCmd_IrisClose,
	AntsIPCPTZCmd_Up = 21,
	AntsIPCPTZCmd_Down,
	AntsIPCPTZCmd_Left,
	AntsIPCPTZCmd_Right,
	AntsIPCPTZCmd_UpLeft = 25,
	AntsIPCPTZCmd_UpRight,
	AntsIPCPTZCmd_DownLeft,
	AntsIPCPTZCmd_DownRight,
	AntsIPCPTZCmd_PanAuto = 29,//��SS���ٶ������Զ�ɨ��
	AntsIPCPTZCmd_SeqAddPreset = 30,
	AntsIPCPTZCmd_SeqSetDWell,// Ѳ����ͣ��ʱ��
	AntsIPCPTZCmd_SeqSetSpeed,// �ٶ�
	AntsIPCPTZCmd_SeqDelPreset,//ɾ��Ԥ�õ�
	AntsIPCPTZCmd_CruiseRecStart,// ��ʼ��¼�켣
	AntsIPCPTZCmd_CruiseRecStop=35,// ֹͣ��¼�켣
	AntsIPCPTZCmd_CruiseRun,//��ʼ�켣
	AntsIPCPTZCmd_SeqRun,//��ʼѲ��
	AntsIPCPTZCmd_SeqStop,//ֹͣѲ��
	AntsIPCPTZCmd_GotoPreset,// ת����
	AntsIPCPTZCmd_SeqFill=40,//��Ѳ���������õ���̨
	AntsIPCPTZCmd_Home,
	AntsIPCPTZCmd_TransPTZ = 100,// ͸��ͨ��

	AntsIPCPTZCmd_GetCruisePoint = 0x10000, // ��ȡѲ����
}AntsIPCPTZCmd_E;
//������ؽṹ
// ->AntsIPCControlCmd_PTZ
typedef struct _tagAntsIPCPTZControl
{
	U32 dwCmd;
	U32 dwParams[6]; // 0- ��Чֵ
	// �������:dwParams[0] :1-ֹͣ;dwParams[1]:�ٶ�1-16
	//Ԥ�õ�:dwParams[0]:Ԥ�õ�
	//Ѳ��:dwParams[0]:Ѳ����ţ�dwParams[1]Ѳ���㣬dwParams[2]�������
	//�켣:���ò���
	//���� ��Դ:dwParams[0],1-����2-��
	// ͸��ͨ��: dwParams[0]:0-��Ч�����򻺳�ָ�룻dwParams[1]�����峤��
	// ��ȡѲ����: dwParams[0] Ѳ�����
}AntsIPCPTZControl_T;

typedef struct _tagAntsIPCPTZCruisePoint
{
	U8	PresetNum;
	U8	Dwell;
	U8	Speed;
	U8	Reserve;
}AntsIPCPTZCruisePoint_T;

typedef struct _tagAntsIPCPTZCruiseSets
{
	AntsIPCPTZCruisePoint_T		struCruisePoint[32];
}AntsIPCPTZCruiseSets_T;


//�������
typedef struct _tagAntsIPCIPv4
{
	U32 dwValid;// ָʾ��Ч��,bit0-mac,1-ip,2-mask,3-gateway,4-dns1,5-dns2
	U8  byMac[8];	// �޸�ʱ����������ṩ
	S8  szIpAddr[16];
	S8  szNetMask[16];
	S8  szGateway[16];
	S8  szDns1[16];
	S8  szDns2[16];
}AntsIPCIPv4_T;


typedef struct _tagAntsIPCSearchInfo
{
	U16       bAddressType;// 0- ipv4,1-dnsname,2-ipv6
	U16		  wPort;
	U8       dwTransType;// ֧�ֵĴ�������,�ɻ�:1-TCP,2-UDP
	U8       byDeviceType;// 0-δ����� (��Ĭ��ΪIPC),  1-dvr,2-nvr,3-ipc,4-dec
	U8       byRes[2];
	S8		  szDeviceName[64];
	S8        szUserName[64];
	S8        szPassword[64];
	union 
	{
		S8            szUrl[256];
		S8            szIPv6[64];
		AntsIPCIPv4_T struIPInfo;
	}uAddress;
}AntsIPCSearchInfo_T;


//�ص�����

//////////////////////////////
// ANTS_IPC_STATUS_CALLBACK ״̬�ص�
//S32 hLogin: ״̬��Ӧ�ľ��, 0- ����޹ص�״̬
// lChannel: 0- ͨ���޹�
// nStreamIdx: 0- ���޹�
//dwStatusType��״̬����AntsIPCStatusType_T
//pBuffer:״̬��Ӧ������
//dwBufSize:���ݳ���
//pUser:�ص����û�����


typedef VOID (*ANTS_IPC_STATUS_CALLBACK)(S32 hLogin,S32 lChannel,S32 lStreamIdx,U32 dwStatusType,U8 *pBuffer,U32 dwBufSize,VOID* pUser);

///////////////////////////////////
//ANTS_IPC_STREAM_CALLBACK,���ص�
//S32 hLogin: ��½��ȡ�ľ��
//lChannel: ͨ����,0-ͨ���޹�,1,2,3,4...ͨ����
//nStreamIdx:�����,0-������޹�,1-��������2-��������3-��������
//dwDataType:�������ͣ�0-�ļ�ͷ,1-��Ƶ,2-��Ƶ3-������Ϣ(AntsIPCAlarmInfo_T)
//pBuffer:���ݻ��壬���������Ƶ�����������֡ͷ
//dwBufSize:���ݴ�С
//pUser:�ص�ʱ���õ��û�����


typedef VOID (*ANTS_IPC_STREAM_CALLBACK)(S32 hLogin,S32 lChannel,S32 lStreamIdx,U32 dwDataType,U8 *pBuffer,U32 dwBufSize,VOID* pUser);



typedef VOID (*ANTS_IPC_ALARM_CALLBACK)(S32 hLogin,S32 lChannel,S32 lStreamIdx,U32 dwAlarmType,U8 *pBuffer,U32 dwBufSize,VOID* pUser);


//�ӿں�������

typedef S32 (*ANTS_IPC_INIT)(VOID *pParam);
typedef S32 (*ANTS_IPC_UNINIT)(VOID *pParam);


typedef S32 (*ANTS_IPC_GETSUPPORTFUNCTIONS)(VOID *pFxnsBuffer,U32 dwBufferSize);


//////
//����״̬�ص�����
typedef S32 (*ANTS_IPC_SETSTATUSCALLBACK)(ANTS_IPC_STATUS_CALLBACK fxn,VOID *pUser);

typedef S32 (*ANTS_IPC_SETALARMCALLBACK)(S32 hLogin,ANTS_IPC_ALARM_CALLBACK fxn,VOID *pUser);


/////////////////////////////////////////////////
//ANTS_IPC_LOGIN:��½IPC
//nLinkProtocol:0-TCP,1-UDP
//pIPv4:IPC��ַ
//dwPort:�˿ں�
// pUsername:�û���
//pPassword:����
//fxn:���ص�����
// pUser:�ص������û�����
//����:<= 0-ʧ�ܣ�>0���ؾ��


typedef S32 (*ANTS_IPC_LOGIN)(U32 nLinkProtocol,S8 *pUrl,U16 dwPort,S8 *pUsername,S8 *pPassword,ANTS_IPC_STREAM_CALLBACK fxn, VOID *pUser);

//����0-�ɹ���-1ʧ��
typedef S32 (*ANTS_IPC_STARTREALPLAY)(S32 hLogin,S32 lChannel,S32 nStreamIdx);
typedef S32 (*ANTS_IPC_STOPREALPLAY)(S32 hLogin,S32 lChannel,S32 nStreamIdx);
typedef S32 (*ANTS_IPC_LOGOUT)(S32 hLogin);
typedef S32	(*ANTS_IPC_SETCONFIG)(S32 hLogin, U32 dwCommand, S32 lChannel,S32 nStreamIdx, VOID* lpInBuffer, U32 dwInBufferSize);
typedef S32	(*ANTS_IPC_GETCONFIG)(S32 hLogin, U32 dwCommand, S32 lChannel,S32 nStreamIdx, VOID* lpOutBuffer, U32 dwOutBufferSize, U32* lpBytesReturned);
typedef S32	(*ANTS_IPC_CONTROL)(S32 hLogin, U32 dwCommand, S32 lChannel,S32 nStreamIdx, VOID *pInBuf, U32 dwInLength, VOID *pOutBuf, U32 dwOutLength);
typedef S32	(*ANTS_IPC_CAPTUREPICTURE)(S32 hLogin,S32 lChannel,S32 nStreamIdx, S8 *sPicBuffer, U32 dwBufferSize, U32 *lpReturnSize);
typedef S32	(*ANTS_IPC_GETABILITY)(S32 hLogin, U32 dwAbilityType, S8 *pInBuf, U32 dwInLength, S8 *pOutBuf, U32 dwOutLength);

//�����ص�

// bOperation:0-��ʼ��1-ֹͣ2-������
typedef S32 (*ANTS_IPC_SEARCHIPC)(S32 bOperation);
//pResult==NULLʱ�����������ܸ���
//���򷵻ػ�����ʵ�ʴ�ŵĸ���
// idx == -1 ��һ�η��ػ�����ݸ���
// idx >= 0Ϊ��ȡ������һ�����
//dwResultMaxCount �����ٸ�sizeof(AntsIPCSearchInfo_T)
typedef S32 (*ANTS_IPC_GETSEARCHRESULT)(S32 idx,AntsIPCSearchInfo_T *pResult,U32 dwResultMaxCount);
typedef S32 (*ANTS_IPC_ModifyIPInfo)(AntsIPCIPv4_T *pIPModifyInfo);






typedef struct _tagAntsIPCFunctions
{
	U32 dwFlag[2];//fourcc("ANTSIPCP") ANTS_IPC_FLAG0,ANTS_IPC_FLAG1
	U32 dwSize;// sizeof(AntsIPCFunctions_T)
	U32 dwVersion;// ANTS_IPC_VERSION
	U32 dwMaxNum;//���֧�ֵ�IPC�豸��
	S8  sProtocolName[16];// Э����,����
	ANTS_IPC_SEARCHIPC fSearch;
	ANTS_IPC_GETSEARCHRESULT fGetSearchResult;
	ANTS_IPC_ModifyIPInfo  fModifyIPInfo;
	ANTS_IPC_SETSTATUSCALLBACK fSetStatusCallback;
	ANTS_IPC_LOGIN fLogin;
	ANTS_IPC_LOGOUT fLogout;
	ANTS_IPC_SETALARMCALLBACK fSetAlarmCallback;
	ANTS_IPC_GETCONFIG fGetConfig;
	ANTS_IPC_SETCONFIG fSetConfig;
	ANTS_IPC_STARTREALPLAY fStartRealPlay;
	ANTS_IPC_STOPREALPLAY fStopRealPlay;
	ANTS_IPC_CONTROL fControl;
	ANTS_IPC_GETABILITY fGetAbility;
	ANTS_IPC_CAPTUREPICTURE fCapturePicture;
	// Version > 10001
	ANTS_IPC_INIT  fInit;
	ANTS_IPC_UNINIT fUnInit;
	
}AntsIPCFunctions_T;

#ifdef __cplusplus
extern "C" {
#endif
// ��ȡ��Э��֧�ֵĹ���
// pFxnsBuffer: AntsIPCFunctions_T,��ͬ�İ汾���ܴ˽ṹ��С��һ��
// dwBufferSize: ָʾ�ṩ����Ĵ�С.�������СС�ڱ��汾Э�鹦�ܽṹ�Ĵ�Сʱ,�����ṩ�ܽ��ܵĽϵͰ汾����.
//����ṩ�Ļ����С����Ͱ汾��Ҫ�Ļ��廹С���򷵻�ʧ��.
//����:0-�ɹ�,-1ʧ��
S32 ants_ipc_GetSupportFunctions(VOID *pFxnsBuffer,U32 dwBufferSize);

#ifdef __cplusplus
}
#endif

#endif


