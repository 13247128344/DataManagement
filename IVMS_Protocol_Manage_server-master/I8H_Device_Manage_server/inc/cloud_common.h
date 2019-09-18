#ifndef _Cloud_Common_H_
#define _Cloud_Common_H_

#ifndef VOID 
typedef void VOID;
#endif

#ifndef U64
typedef unsigned long long U64 ;
#endif

#ifndef U32
typedef unsigned int U32;
#endif
	
#ifndef U16
typedef unsigned short U16 ;
#endif

#ifndef U8
typedef unsigned char U8 ;
#endif

#ifndef S32
typedef int S32;
#endif
	
#ifndef S16
typedef short S16 ;
#endif

#ifndef S8
typedef char S8 ;
#endif

#if (defined(WIN32) || defined(_WIN64))
#include <Windows.h>
typedef HANDLE pthread_t ;
#if (!defined(_WIN64))
typedef int intptr_t;
#endif
#else
#define CALLBACK 
#include <pthread.h>

#ifndef DWORD
typedef unsigned int DWORD;
#endif

#ifndef UINT
typedef unsigned int UINT;
#endif

#ifndef WORD
typedef unsigned short WORD;
#endif

#ifndef USHORT
typedef unsigned short USHORT;
#endif

#ifndef LONG 
typedef int LONG;
#endif

#ifndef BOOL
typedef int BOOL;
#endif

#ifndef BYTE
typedef unsigned char BYTE;
#endif

#ifndef HANDLE
typedef void* HANDLE;
#endif

#ifndef INFINITE
#ifdef WIN32
#define INFINITE 0xFFFFFFFFFFFFFFFF
#else
#define INFINITE 0xFFFFFFFF
#endif
#endif

#ifndef INVALID_HANDLE_VALUE
#ifdef WIN32
#define INVALID_HANDLE_VALUE	(VOID *)0xFFFFFFFFFFFFFFFF
#else
#define INVALID_HANDLE_VALUE 	(VOID *)0xFFFFFFFF
#endif
#endif

#ifndef NULL
#define NULL	0
#endif

#ifndef TRUE
#define	TRUE	1
#endif

#ifndef FALSE
#define	FALSE 	0
#endif

#endif

#define CLOUD_MAX_PROTOCOL_NUM			64
#define CLOUD_MAX_RTSPURL_LEN			128
#define CLOUD_MAX_IPC_CHANNUM			256
#define CLOUD_SERIALNO_LEN				48
#define CLOUD_NAME_LEN					32
#define CLOUD_PASSWD_LEN				16
#define CLOUD_MACADDR_LEN				6
#define CLOUD_MAX_ETHERNET				2
#define CLOUD_MAX_DOMAIN_NAME			64
#define CLOUD_MAX_RIGHT					32
#define CLOUD_MAX_CHANNUM				64
#define CLOUD_MAX_USERNUM				8
#define CLOUD_MAX_UUID_LEN				48

////////////////////////////////////////////////////////////////////////////////
// �궨��
////////////////////////////////////////////////////////////////////////////////

//!�������
#ifndef IN
#define IN
#endif

//!�������
#ifndef OUT
#define OUT
#endif

//!�����������
#ifndef INOUT
#define INOUT
#endif

#define PACKET_STX	(0xFEDCBA98) 						//!���ݰ���ʼ��
#define PACKET_ETX	(0x12345678)						//!���ݰ���ֹ��

#define PACKET_RAW_DATA		0							//!ԭʼ����
#define PACKET_XML_DATA 	1							//!XML����
#define PACKET_JSON_DATA 	2							//!JSON����
	
#define PACKET_UNZIP		0							//!����δ��ZIPѹ������
#define PACKET_ZIP			1							//!���ݾ�ZIPѹ������
////////////////////////////////////////////////////////////////////////////////
// ö�ٶ���
////////////////////////////////////////////////////////////////////////////////

//!�ӿڷ���ֵ�궨��
typedef enum e_cloud_result_code
{
	Cloud_ResultCode_Succ = 0 ,							//!�ɹ�
	Cloud_ResultCode_Failed = 1 ,						//!ʧ��
	Cloud_ResultCode_VersionMisMatch = 2,				//!�汾��ƥ��
	Cloud_ResultCode_NoInit = 3,						//!sdkδ��ʼ��
	Cloud_ResultCode_NoStart = 4,						//!δ����
	Cloud_ResultCode_HasInit = 5,						//!sdk�ѳ�ʼ��
	Cloud_ResultCode_HasStarted = 6,					//!�Ѿ�����
	Cloud_ResultCode_Unsupported = 7,					//!��֧�ֵĲ���

	Cloud_ResultCode_InvalidParam = 8,					//!������Ч
	Cloud_ResultCode_InvalidHandle = 9,					//!���ֵ��Ч
	Cloud_ResultCode_InValidUser = 10,					//!��Ч�û�
	
	Cloud_ResultCode_NoMem = 11,						//!û���ڴ�
	Cloud_ResultCode_NoHandle = 12,						//!û�о��
	Cloud_ResultCode_BufTooSmall = 13,			    	//!������̫С

	Cloud_ResultCode_ConnectFailed = 14 ,				//!����ʧ��
	Cloud_ResultCode_SendFailed = 15,					//!����ʧ��
	Cloud_ResultCode_RecvFailed = 16,					//!����ʧ��
	
	Cloud_ResultCode_ConnectTimeout = 17, 				//!���ӳ�ʱ
	Cloud_ResultCode_SendTimeout = 18, 					//!���ͳ�ʱ
	Cloud_ResultCode_RecvTimeout = 19, 					//!���ճ�ʱ
	Cloud_ResultCode_TryConnectError = 20,				//!�������Ӵ���
	Cloud_ResultCode_ListenPortSame = 21,				//!�����˿ڳ�ͻ

	Cloud_ResultCode_MatchMagicIdError = 22,			//!ƥ��Magic��ʼ�����
	Cloud_ResultCode_MatchMagicEtxError = 38,			//!ƥ��Magic��ֹ�����
	Cloud_ResultCode_MatchPacketEtxError = 23,			//!ƥ���������ֹ�����
	Cloud_ResultCode_MatchSeqNoError = 24,				//!ƥ�����Ŵ���
	Cloud_ResultCode_DataFormatError = 25,				//!�û����ݸ�ʽ����

	Cloud_ResultCode_WaitTimeOut = 26,					//!�ȴ���Ӧ��ʱ
	Cloud_ResultCode_ListFull = 27,						//!������
	Cloud_ResultCode_P2PHostSame = 28,					//!P2P��ַ��ͻ
	
	Cloud_ResultCode_AuthenticationError = 29,			//!�û���֤����
	Cloud_ResultCode_NoRight = 30,						//!��ǰ������Ȩ��
	
	Cloud_ResultCode_CallNetLogicAPIError = 31,			//!�����߼���API�ӿ�ʧ��
	Cloud_ResultCode_DevException = 32,					//!�豸�쳣
	Cloud_ResultCode_SerializeDataError = 33,			//!���л�����
	Cloud_ResultCode_DeserializeDataError = 34,			//!�����л�����
	Cloud_ResultCode_NoResource = 35,					//!����Դ
	Cloud_ResultCode_OverMaxNum = 36,					//!��������
	Cloud_ResultCode_HandleExist = 37,					//!����Ѵ���
	Cloud_ResultCode_ReplayHandleError = 38,			//!�طž��
	
}cloud_result_code_t ;


//!�����������ͺ궨��
typedef enum e_cloud_data_tran_type 
{
	Cloud_TranRealVideoData 	= 0x01,
	Cloud_TranRealAudioData 	= 0x02,
	Cloud_TranTalkData 			= 0x03,
	Cloud_TranHistroyVideoData 	= 0x04,
	Cloud_TranHistroyAudioData 	= 0x05,
}cloud_data_tran_type_t ;


//!��Ƶ�����ʽ�궨��
typedef enum e_cloud_audio_format
{
	Cloud_Audio_G711_U 		= 0x01,
	Cloud_Audio_G711_A		= 0x02,
	Cloud_Audio_G726		= 0x03,
}cloud_audio_format_t ;
	

//!��Ƶ�����ʽ�궨��
typedef enum e_cloud_video_format
{
	Cloud_Video_I8			= 0x01,
	Cloud_Video_H264		= 0x02,
	Cloud_Video_H265		= 0x03,
	Cloud_Video_AVI			= 0x04,
}cloud_video_format_t ;


//!֡���ͺ궨��
typedef enum e_cloud_frame_type
{
	Cloud_Main_IFrame 		= 0x01,	
	Cloud_Main_PFrame 		= 0x02,
	Cloud_Sub_IFrame		= 0x03,
	Cloud_Sub_PFrame		= 0x04,
	Cloud_Main_AudioFrame 	= 0x05,
	Cloud_Sub_AudioFrame 	= 0x06,	
}cloud_frame_type_t ;


//!��Ƶ�����ʺ궨��
typedef enum e_cloud_audio_samplerate
{
	Cloud_Audio_SampleRate_8000HZ	= 0x01,
	Cloud_Audio_SampleRate_32000HZ	= 0x02,
	Cloud_Audio_SampleRate_48000HZ	= 0x03,
	Cloud_Audio_SampleRate_96000HZ	= 0x04,	
}cloud_audio_samplerate_t ;

	
//!�û�������״̬�궨��
typedef enum e_cloud_user_status
{
	Cloud_User_OffLine 	= 0,	//!�û�����״̬
	Cloud_User_OnLine 	= 1,	//!�û�����״̬
}cloud_user_status_t ;


//!�û�����ģʽ�궨��
typedef enum e_cloud_user_workmodel
{
	Cloud_User_None 		= 0,
	Cloud_User_RootModel 	= 1,		//!�������û�(����ʵʱ��/�����Խ�/PTZ����/������Ϣ����/��Ϣ������Ӧ)
	Cloud_User_ReplayModel 	= 2,		//!�������û�(������ʷ������/�ط�)
}cloud_user_workmodel_t ;


//!PTZ��������궨��	
typedef enum e_cloud_ptz_ctrl
{
	CLOUD_PTZ_CTRL_STOP = 100 , 
	CLOUD_PTZ_CTRL_MOVE_UP , 
	CLOUD_PTZ_CTRL_MOVE_DOWN , 
	CLOUD_PTZ_CTRL_MOVE_LEFT ,
	CLOUD_PTZ_CTRL_MOVE_RIGHT ,  
	CLOUD_PTZ_CTRL_MOVE_UPLEFT , 
	CLOUD_PTZ_CTRL_MOVE_DOWNLEFT , 
	CLOUD_PTZ_CTRL_MOVE_UPRIGHT , 
	CLOUD_PTZ_CTRL_MOVE_DOWNRIGHT , 

	CLOUD_PTZ_CTRL_IRIS_IN , 
	CLOUD_PTZ_CTRL_IRIS_OUT , 
	CLOUD_PTZ_CTRL_FOCUS_IN , 
	CLOUD_PTZ_CTRL_FOCUS_OUT , 
	CLOUD_PTZ_CTRL_ZOOM_IN , 
	CLOUD_PTZ_CTRL_ZOOM_OUT , 

	CLOUD_PTZ_CTRL_SET_PRESET , 
	CLOUD_PTZ_CTRL_CALL_PRESET , 
	CLOUD_PTZ_CTRL_DELETE_PRESET , 

	CLOUD_PTZ_CTRL_BEGIN_CRUISE_SET, 
	CLOUD_PTZ_CTRL_SET_CRUISE, 
	CLOUD_PTZ_CTRL_END_CRUISE_SET, 
	CLOUD_PTZ_CTRL_CALL_CRUISE, 
	CLOUD_PTZ_CTRL_DELETE_CRUISE, 
	CLOUD_PTZ_CTRL_STOP_CRUISE, 

	CLOUD_PTZ_CTRL_AUTO_SCAN, 

	CLOUD_PTZ_CTRL_RAINBRUSH_START, 
	CLOUD_PTZ_CTRL_RAINBRUSH_STOP,
	CLOUD_PTZ_CTRL_LIGHT_ON, 
	CLOUD_PTZ_CTRL_LIGHT_OFF,

	CLOUD_PTZ_CTRL_MAX, 	
}cloud_ptz_ctrl_t ;


//!�켣�����궨��
typedef enum e_cloud_ptz_track_t
{
	CLOUD_PTZ_TRACK_START = 0x00, 	//!��ʼ��¼�켣
	CLOUD_PTZ_TRACK_STOP, 			//!ֹͣ��¼�켣
	CLOUD_PTZ_TRACK_DEL,			//!ɾ����¼�켣
	CLOUD_PTZ_TRACK_RUN,			//!���м�¼�켣
	CLOUD_PTZ_TRACK_STOPRUN,		//!ֹͣ���м�¼�켣
}cloud_ptz_track_t ;



//!Ѳ�������궨��
typedef enum e_cloud_ptz_cruise_t
{
	CLOUD_PTZ_CRUISE_ROUTE_ADD = 0x00,		//!Ѳ�����(�������Ѳ��·��,��дCLOUD_CRUISE_ROUTE�ṹ)
	CLOUD_PTZ_CRUISE_ROUTE_DEL,				//!Ѳ��ɾ��(ɾ������Ѳ��·��,��дCLOUD_CRUISE_ROUTE_NO�ṹ)
	CLOUD_PTZ_CRUISE_ROUTE_RUN,				//!Ѳ��·������(��дѲ��·��,��дCLOUD_CRUISE_ROUTE_NO�ṹ)
	CLOUD_PTZ_CRUISE_ROUTE_STOPRUN,			//!Ѳ��·������ֹͣ(��дѲ��·��,��дCLOUD_CRUISE_ROUTE_NO�ṹ)
	CLOUD_PTZ_CRUISE_POINT_ADD,				//!Ѳ�������(����Ѵ���Ѳ��·���������Ѳ����,��дCLOUD_ADD_CRUISE_POINT�ṹָ��)
	CLOUD_PTZ_CRUISE_POINT_DEL,				//!Ѳ����ɾ��(����Ѵ���Ѳ��·������ɾ��Ѳ����,��дCLOUD_DEL_CRUISE_POINT�ṹָ��)
}cloud_ptz_cruise_t ;



//!�������ͺ궨��	
typedef enum e_cloud_alarm_type
{
	CLOUD_ALARM_VIDEOMOTION_TYPE 	= 0x0001,			//!�ƶ���ⱨ������
	CLOUD_ALARM_ALARMIN_TYPE 		= 0x0002,			//!���뱨������
	CLOUD_ALARM_VIDEOLOST_TYPE 		= 0x0003,			//!��Ƶ��ʧ��������
	CLOUD_ALARM_VIDEOMASK_TYPE 		= 0x0004,			//!��Ƶ�ڵ���������
	CLOUD_ALARM_DISKFULL_TYPE		= 0x0005,			//!Ӳ����	
	CLOUD_ALARM_DISKERROR_TYPE 		= 0x0006,			//!Ӳ�̴���
	CLOUD_ALARM_ILLEGEACCESS_TYPE	= 0x0007,			//!�Ƿ�����
	CLOUD_ALARM_NETDISCONNECT_TYPE	= 0x0008,			//!���߶Ͽ�
	CLOUD_ALARM_IPCONFLICT_TYPE		= 0x0009,			//!IP��ͻ
}cloud_alarm_type_t ;

	
//!�������ͺ궨��
typedef enum e_cloud_stream_type
{
	Cloud_MainStream = 1,
	Cloud_SubStream  = 2,
	Cloud_MixStream  = 3,
}cloud_stream_type_t ;


//!��Ϣ���ݰ��汾�궨��
typedef enum e_cloud_version 
{
	Cloud_VersionV10 = 0x00010000 ,
}cloud_version_t ;


//!��Ϣ���ݰ�����
typedef enum e_cloud_message_type
{
	Cloud_Message4Request 	= 0x0000,
	Cloud_Message4Response 	= 0x0001,
	Cloud_Message4Notify 	= 0x0002,
}cloud_message_type_t ;


//!����¼���ļ����ͺ궨��
typedef enum e_cloud_findfile_type
{
	CLOUD_FINDFILE_TYPE_ALL 				= 0xFF,
	CLOUD_FINDFILE_TYPE_TIME 				= 0,
	CLOUD_FINDFILE_TYPE_MOTION 				= 1 ,
	CLOUD_FINDFILE_TYPE_ALARM 				= 2 ,
	CLOUD_FINDFILE_TYPE_MOTION_OR_ALARM 	= 3 ,
	CLOUD_FINDFILE_TYPE_MOTION_AND_ALARM 	= 4,
	CLOUD_FINDFILE_TYPE_COMMAND 			= 5,
	CLOUD_FINDFILE_TYPE_MANUAL 				= 6,	
}cloud_findfile_type_t ;


//!��Ϣ����궨��
typedef enum e_cloud_message_cmd
{
	//!����ע�������Ϣ�궨��
	Cloud_Message_LoginNotify = 0x1000,
	Cloud_Message_UpDevWorkStatus,
	Cloud_Message_Authentication,			//!����ע��������豸�����û�����������֤��������
	
	Cloud_Message_RealPlay,					//!����ע��������豸����ʵʱ����������
	Cloud_Message_StopRealPlay,				//!����ע��������豸����ֹͣʵʱ����������
	Cloud_Message_ControlRealPlay,			//!����ע��������豸����ʵʱ��������������(��:�����ͨ��ʵʱ��/ɾ����ͨ��ʵʱ��)
	
	Cloud_Message_ZeroRealPlay,				//!����ע��������豸������ͨ��ʵʱ����������
	Cloud_Message_StopZeroRealPlay,			//!����ע��������豸����ֹͣ��ͨ��ʵʱ����������
	
	Cloud_Message_Replay,					//!����ע��������豸������ʷ����������		
	Cloud_Message_StopReplay,				//!����ע��������豸����ֹͣ��ʷ����������
	Cloud_Message_ControlReplay,			//!����ע��������豸���п�����ʷ����������(��:Seek/Fast/Slow/SetSpeed�Ȳ���)
	
	Cloud_Message_AddAlarm,					//!����ע��������豸���б���������������
	Cloud_Message_DelAlarm,					//!����ע��������豸����ֹͣ����������������
	Cloud_Message_AlarmInfo,				//!���ͱ�����Ϣ֪ͨ
	
	Cloud_Message_ControlPTZ,				//!����ע��������豸����PTZ֪ͨ����
	
	Cloud_Message_FindFile,					//!����ע��������豸������ʷ�ļ���ѯ����
	
	Cloud_Message_Talk,						//!����ע��������豸���������Խ�����
	Cloud_Message_StopTalk,					//!����ע��������豸����ֹͣ�����Խ�����
	
	Cloud_Message_GetConfig,				//!����ע��������豸��ȡ���ò�������
	Cloud_Message_SetConfig,				//!����ע��������豸�������ò�������
	
	Cloud_Message_CruisePTZ,				//!Ѳ����������
	Cloud_Message_QueryCruisePTZ,			//!��ѯѲ��·������
	Cloud_Message_TrackPTZ,					//!�켣��������
	Cloud_Message_TranPTZ,					//!͸��ͨ����������
	
	//!˽��P2PЭ����Ϣ�궨��
	Cloud_Message_LoginV2 = 0x8000,			//!�û�ע������(c->s)
	Cloud_Message_LogoutV2,					//!�û�ע������(c->s)
	Cloud_Message_HeartBeatV2,				//!�û���������(c->s)
	
	Cloud_Message_RealPlayV2,				//!ʵʱ����������(c->s)
	Cloud_Message_StopRealPlayV2,			//!ֹͣʵʱ����������(c->s)
	Cloud_Message_ControlRealPlayV2,		//!����ʵʱ��������������(��:�����ͨ��ʵʱ��/ɾ����ͨ��ʵʱ��)(c->s)
	
	Cloud_Message_ZeroRealPlayV2,			//!��ͨ��ʵʱ����������(c->s)
	Cloud_Message_StopZeroRealPlayV2,		//!ֹͣ��ͨ��ʵʱ����������(c->s)
	
	Cloud_Message_ReplayV2,					//!��ʷ����������(c->s)
	Cloud_Message_StopReplayV2,				//!ֹͣ��ʷ����������(c->s)
	Cloud_Message_ControlReplayV2,			//!������ʷ����������(��:Seek/Fast/Slow/SetSpeed�Ȳ���)(c->s)
	
	Cloud_Message_AddAlarmV2,				//!����������������(c->s)
	Cloud_Message_DelAlarmV2,				//!ֹͣ����������������(c->s)
	Cloud_Message_AlarmInfoV2,				//!���ͱ�����Ϣ֪ͨ(s->c)
	
	Cloud_Message_ControlPTZV2,				//!PTZ��������(c->s)
	
	Cloud_Message_FindFileV2,				//!��ʷ�ļ���ѯ����(c->s)
	
	Cloud_Message_TalkV2,					//!�����Խ�����(c->s)
	Cloud_Message_StopTalkV2,				//!ֹͣ�����Խ�����(c->s)
	
	Cloud_Message_GetConfigV2,				//!��ȡ���ò�������(c->s)
	Cloud_Message_SetConfigV2,				//!�������ò�������(c->s)
	
	Cloud_Message_QueryLinkUuidV2,			//!��ѯ��ǰ����UUID(c->s)
	Cloud_Message_StopRealPlayV22,			//!ֹͣʵʱ����������(c->s)(��չ����)

	Cloud_Message_TranControlV2,			//!͸����Ϣ��������
	
	//!����ת��ģ��ʹ�õĺ궨��
	Cloud_Dev2Agent_Message_Login = 0x9000,	//!�豸ע��֪ͨ	
	Cloud_Dev2Agent_Message_Logout,			//!�豸ע��֪ͨ
	Cloud_Dev2Agent_Message_HeartBeat,	    //!�豸������Ϣ
	Cloud_Dev2Agent_Message_RealPlay,		//!�豸Ԥ������
	Cloud_Dev2Agent_Message_Talk,			//!�豸��������
	Cloud_Dev2Agent_Message_StopTalk,		//!�豸�����ر�
	
}cloud_message_cmd_t ;



//!��չ��Ϣ����
typedef enum e_cloud_message_cmdv2
{
	Cloud_Cmd_DevStatus 			= (1 << 0),		//!�豸����״̬��������(c->s)	
	Cloud_Cmd_DevAlarm 				= (1 << 1),		//!�豸������������(c->s)
	Cloud_Cmd_DevConnect 			= (1 << 2),		//!�豸ע������ע���������(s->c)
	Cloud_Cmd_DevDisconnect 		= (1 << 3),		//!�豸ע������ע���������(s->c)
	Cloud_Cmd_DevSubscribeAlarm 	= (1 << 4),		//!�豸������������(s->c)
	Cloud_Cmd_DevUnsubscribeAlarm 	= (1 << 5),		//!�豸ȡ��������������(s->c)
}cloud_message_cmdv2_t ;



//!���ò�����ȡ�����ú궨��
typedef enum e_cloud_config_cmd
{
	Cloud_Config_GetDevInfo =0x2000,	//!��ȡ�豸������Ϣ(�������ע�����)	
	Cloud_Config_GetDevWorkStatus,		//!��ȡ�豸����״̬
	
	Cloud_Config_GetDevCfg,				//!��ȡ�豸��������
	Cloud_Config_SetDevCfg,				//!�����豸��������
	
	Cloud_Config_GetNetCfg,				//!��ȡ�豸�������
	Cloud_Config_SetNetCfg,				//!�����豸�������
	
	Cloud_Config_GetUserCfg,			//!��ȡ�豸�û�����(�������ע�����)
	Cloud_Config_SetUserCfg,			//!�����豸�û�����(�������ע�����)

	Cloud_Config_GetTimeCfg,			//!��ȡ�豸�û�����
	Cloud_Config_SetTimeCfg,			//!�����豸�û�����

	Cloud_Config_GetDevInfoV2 = 0x8000,	//!��ȡ�豸������Ϣ(���P2P����)
	Cloud_Config_GetUserCfgV2,			//!��ȡ�豸�û�����(���P2P����)
	Cloud_Config_SetUserCfgV2,			//!�����豸�û�����(���P2P����)

}cloud_config_cmd_t ;


//!ʵʱ�����ſ�������
typedef enum e_cloud_control_realplay_cmd
{
	Cloud_ControlRealplay_PlayAudio			= 1,	//!������ ʹ��CLOUD_CONTROL_REALPLAY_COND�ṹ�� dwParams[0]���������������� 1-������ 2-������ dwParams[1]����ͨ����
	Cloud_ControlRealPlay_StopAudio			= 2,	//!�ر����� ʹ��CLOUD_CONTROL_REALPLAY_COND�ṹ�� dwParams[0]���������������� 1-������ 2-������ dwParams[1]����ͨ����
	Cloud_ControlRealPlay_SwitchStreamType	= 3,	//!�л������������� ʹ��CLOUD_CONTROL_REALPLAY_COND�ṹ�� dwParams[0]���� 1-������ 2-������ dwParams[1]����ͨ���� dwParams[2]�����л�Ŀ���������� 1-������ 2-������
	Cloud_ControlRealPlay_AddChan			= 4,	//!����ͨ�� ʹ��CLOUD_CONTROL_REALPLAY_COND�ṹ�� dwParams[0]������������ 1-������ 2-������ dwParams[1]����ͨ���� 
	Cloud_ControlRealPlay_DelChan			= 5,	//!ɾ��ͨ�� ʹ��CLOUD_CONTROL_REALPLAY_COND�ṹ�� dwParams[0]������������ 1-������ 2-������ dwParams[1]����ͨ����
}cloud_control_realplay_cmd_t ;


//!��ʷ���ط�/���ز��ſ�������
typedef enum e_cloud_control_replay_cmd
{
	Cloud_ControlReplay_Play				= 0x1,	//!��ͣ���� ʹ��CLOUD_CONTROL_REALPLAY_COND�ṹ�� dwInParams[0]������������ 1-������ 2-������ dwInParams[1]����ͨ����
	Cloud_ControlReplay_Pause				= 0x2,	//!��ͣ���� ʹ��CLOUD_CONTROL_REALPLAY_COND�ṹ�� dwInParams[0]������������ 1-������ 2-������ dwInParams[1]����ͨ����
	Cloud_ControlReplay_Repeat				= 0x3,	//!�ָ����� ʹ��CLOUD_CONTROL_REALPLAY_COND�ṹ�� dwInParams[0]������������ 1-������ 2-������ dwInParams[1]����ͨ����
	Cloud_ControlReplay_PlayAudio			= 0x4,	//!������ ʹ��CLOUD_CONTROL_REALPLAY_COND�ṹ�� dwInParams[0]������������ 1-������ 2-������ dwInParams[1]����ͨ����
	Cloud_ControlReplay_StopAudio			= 0x5,	//!�ر����� ʹ��CLOUD_CONTROL_REALPLAY_COND�ṹ�� dwInParams[0]������������ 1-������ 2-������ dwInParams[1]����ͨ����
	Cloud_ControlReplay_SetSpeed			= 0x6,	//!���ò����ٶ� ʹ��CLOUD_CONTROL_REALPLAY_COND�ṹ�� dwInParams[0]������������ 1-������ 2-������ dwInParams[1]����ͨ���� dwInParams[2]�����ٶ�ֵ -16~16
	Cloud_ControlReplay_SetTime				= 0x7,	//!���ûط�ʱ�� ʹ��CLOUD_CONTROL_REALPLAY_COND�ṹ�� dwInParams[0]������������ 1-������ 2-������ dwInParams[1]����ͨ���� dwInParams[2]��������
	Cloud_ControlReplay_SwitchStreamType 	= 0x8,	//!�л������������� ʹ��CLOUD_CONTROL_REALPLAY_COND�ṹ�� dwInParams[0]������������ 1-������ 2-������ dwInParams[1]����ͨ���� dwInParams[2]�����л�Ŀ����������
	Cloud_ControlReplay_PlayDirect			= 0x9,	//!���ƻط�����/���� ʹ��CLOUD_CONTROL_REPLAY_COND�ṹ�� dwInParams[0]������������ 1-������ 2-������ dwInParams[1]����ͨ���� dwInParams[2]�����Ƿ����ŵ��� 0-���� 1-����
	Cloud_ControlReplay_AddChan				= 0xa,	//!����ͬ��ͨ�� ʹ��CLOUD_CONTROL_REPLAY_COND�ṹ�� dwInParams[0]������������ 1-������ 2-������ dwInParams[1]����ͨ����
	Cloud_ControlReplay_DelChan				= 0xb,	//!�Ƴ�ͬ��ͨ�� ʹ��CLOUD_CONTROL_REPLAY_COND�ṹ�� dwInParams[0]������������ 1-������ 2-������ dwInParams[1]����ͨ����
}cloud_control_replay_cmd_t ;


////////////////////////////////////////////////////////////////////////////////
// �ṹ�嶨��
////////////////////////////////////////////////////////////////////////////////	
//!Cloud �豸������Ϣ���ݽṹ
typedef struct _tagDeviceInfo
{
	BYTE bySerialNo[48] ;		//!�豸���к�
	BYTE byAlarmInNum ;			//!������������
	BYTE byAlarmOutNum ;		//!�����������
	BYTE byDiskNum ;			//!Ӳ������
	BYTE byDeviceType ;			//!�豸����
	WORD wChanNum ;				//!�豸��Ƶͨ������
	WORD wStartChan ;			//!�豸��Ƶ��ʼͨ��
	WORD wAudioChanNum ;		//!�豸��Ƶͨ������
	WORD wZeroChanNum ;			//!�豸��ͨ������
	DWORD dwSupport ;			//!�豸����,λ����Ϊ0��ʾ��֧��,1��ʾ֧��
	BYTE byDevName[32] ;		//!�豸����
}CLOUD_DEVICE_INFO, *LPCLOUD_DEVICE_INFO ;


typedef struct _tagDeviceInfov2
{
	BYTE byAlarmInNum ;			//!������������
	BYTE byAlarmOutNum ;		//!�����������
	BYTE byDiskNum ;			//!Ӳ������
	BYTE byDeviceType ;			//!�豸����
	WORD wChanNum ;				//!�豸��Ƶͨ������
	WORD wStartChan ;			//!�豸��Ƶ��ʼͨ��
	WORD wAudioChanNum ;		//!�豸��Ƶͨ������
	WORD wZeroChanNum ;			//!�豸��ͨ������
	DWORD dwSupport ;			//!�豸����,λ����Ϊ0��ʾ��֧��,1��ʾ֧��
	BYTE byDevName[32] ;		//!�豸����	
	BYTE byLocalIP[40] ;		//!�豸IP��ַ
}CLOUD_DEVICE_INFO_V2, *LPCLOUD_DEVICE_INFO_V2 ;


//!Cloud �豸����״̬���ݽṹ
typedef struct _tagDeviceWorkStatus
{
	DWORD dwChannel[256] ;				//!�豸ͨ������״̬ ����λ��ʽ���� bit0-��ʾ�Ƿ�����Ƶ bit1-��ʾ�Ƿ�¼�� bit2-��ʾ�����Խ��Ƿ���
	CLOUD_DEVICE_INFO_V2 struDevInfo ;	//!�豸������Ϣ
	BYTE byRes[40] ;					//!����λ
}CLOUD_DEVICE_WORKSTATUS, *LPCLOUD_DEVICE_WORKSTATUS ;


//!Cloud �豸�û���֤���ݽṹ
typedef struct _tagDevUserAuth
{
	char szUserName[32] ;	//!��ǰ�û���
	char szPassword[16] ;	//!��ǰ����
	DWORD dwChannel[256] ;	//!ͨ��Ȩ�� bit0-�Ƿ���Զ��Ԥ��Ȩ�� bit1-�Ƿ���Զ�̻ط�/����Ȩ�� bit2-�Ƿ���Զ��PTZ����Ȩ�� bit3-�Ƿ���Զ������ת��Ȩ��
	BYTE byLocalTalkRight ;	//!��ǰ�û��Ƿ��������Խ�Ȩ�� 0-��Ȩ�� 1-��Ȩ��
	BYTE byGetConfigRight ;	//!��ǰ�û��Ƿ��л�ȡ���ò���Ȩ��
	BYTE bySetConfigRight ;	//!��ǰ�û��Ƿ����������ò���Ȩ��
	BYTE byRes[13] ;		//!����λ,��ʱ����	
}CLOUD_DEVICE_AUTHENTICATION, *LPCLOUD_DEVICE_AUTHENTICATION ;


//!Cloud Уʱ���ݽṹ
typedef struct _tagTime
{
	DWORD dwYear;	//!��
	DWORD dwMonth;	//!��
	DWORD dwDay;	//!��
	DWORD dwHour;	//!ʱ
	DWORD dwMinute;	//!��
	DWORD dwSecond;	//!��
}CLOUD_TIME, *LPCLOUD_TIME;


//!Cloud ʵʱ������ṹ
typedef struct _tagRealPlayCond
{
	WORD wResult ;								//!���ش�����,�ο�cloud_result_code_t
	WORD wRes ;									//!����λ
	WORD wChannel ;								//!ʵʱ������ͨ��(��1��ʼ)	
	WORD wStreamType ;							//!ʵʱ��������������
	BYTE byRes[32] ;							//!����λ,��ʱ����
}CLOUD_REALPLAY_COND, *LPCLOUD_REALPLAY_COND ;


//!Cloud ʵʱ�����ƽṹ
typedef struct _tagControlRealPlayCond
{
	WORD wResult ;								//!���ش�����,�ο�cloud_result_code_t
	WORD wRes ;									//!����λ
	DWORD dwRealPlayCmd ;						//!ʵʱ����������
	DWORD dwParams[4] ;							//!ʵʱ�����Ʋ���
}CLOUD_CONTROL_REALPLAY_COND, *LPCLOUD_CONTROL_REALPLAY_COND ;


//!Cloud �����Խ�����ṹ
typedef struct _tagTalkCond
{
	WORD wResult ;								//!���ش�����,�ο�cloud_result_code_t
	WORD wRes ;									//!����λ
	WORD wChannel ;								//!�����Խ�ͨ����(��15λ��ʾ�Ƿ����豸�˶Խ�,1-��ʾ���豸�˶Խ�,0-��ʾ��ǰ��IPC�Խ�,��0λ~��14λ��ʾ��Ƶͨ����,��Ƶͨ���Ŵ�1��ʼ)
	BYTE byEncodeType ;							//!�����Խ��������� 0-G711-U 1-G711A 
	BYTE byTrack ;								//!�����Խ���˫���� 0/1-mono 2-stero
	BYTE bySampleBitWidth ;						//!�����Խ�����λ�� 8bit 16bit
	BYTE byRes1[3] ;							//!����λ
	DWORD dwSampleRate ;						//!�����Խ������� 8000kbs
	BYTE byRes2[32] ;							//!����λ
}CLOUD_TALK_COND, *LPCLOUD_TALK_COND ;


typedef struct _tagTalkParam
{
	BYTE byType;				//!0- G711.u;1-G711.a;2-G.726.3;
	BYTE bySampleBitsWidth; 	//!0��Ч��8 or 16
	BYTE byTrack; 				//!0:��Ч(mono);1: mono, 2: stero
	BYTE byFrameRate;			//!0:��Ч(25)
	DWORD dwSampleRate;			//!0��Ч(8000)
	DWORD dwBitRate;			//!0��Ч
}CLOUD_TALK_PARAM,*LPCLOUD_TALK_PARAM ;


typedef struct _tagTalkAudioHeader
{
	BYTE byType;						//!0-��Ч; 1-G711u;2- G711.a;2-G726;
	BYTE bySampleBitsWidth; 			//!8 or 16, 0-��Ч(16)
	BYTE byChannels; 					//!0:��Ч(mono);1: mono, 2: stero
	BYTE byFrameRate;					//!0-��Ч(25)
	DWORD dwSampleRate;					//!0-��Ч(8000)
	DWORD dwBitRate;					//!0-��Ч
	DWORD dwPayloadLength;
	U64 u64TimeStamp;					//!0-��Ч
}CLOUD_TALK_AUDIOHEADER, *LPCLOUD_TALK_AUDIOHEADER ;


//!Cloud ��ʷ������ṹ
typedef struct _tagReplayCond
{
	WORD wResult ;								//!���ش�����,�ο�cloud_result_code_t
	WORD wRes ;									//!����λ
	WORD wChannel ;								//!��ʷ������ͨ��(��1��ʼ)
	WORD wStreamType ;							//!��ʷ��������������
	CLOUD_TIME struStartTime ;					//!��ʷ����ʼʱ��
	CLOUD_TIME struStopTime ;					//!��ʷ������ʱ��
	BYTE byRes[32] ;							//!����λ,��ʱ����
}CLOUD_REPLAY_COND, *LPCLOUD_REPLAY_COND ;


//!*Cloud ��ʷ�����ƽṹ
typedef struct _tagControlReplayCond
{
	WORD wResult ;								//!���ش�����,�ο�cloud_result_code_t
	WORD wRes ;									//!����λ
	DWORD dwReplayCmd ;							//!��ʷ����������
	DWORD dwInParams[4] ;						//!��ʷ�������������
	DWORD dwOutParams[4] ;						//!��ʷ�������������
}CLOUD_CONTROL_REPLAY_COND, *LPCLOUD_CONTROL_REPLAY_COND ;


//!Cloud PTZ���Ʋ����ṹ
typedef struct _tagControlPTZCond
{
	WORD wResult ;							//!���ش�����,�ο�cloud_result_code_t
	WORD wRes ;								//!����λ
	WORD wChannel ;							//!ͨ����(��1��ʼ)
	WORD wPTZCmd ;							//!PTZ����ID
	DWORD dwInParams[4] ;					//!PTZ�����������
}CLOUD_CONTROL_PTZ_COND, *LPCLOUD_CONTROL_PTZ_COND ;


//!Cloud PTZѲ�����Ʋ����ṹ
typedef struct _tagCruisePoint
{
	BYTE byPresetNo ;						//!Ԥ�õ��(��1��ʼ)
	BYTE bySpeed ;							//!Ԥ�õ�����ٶ�(1-16)
	WORD wDWellTime ;						//!Ԥ�õ�ͣ��ʱ��(��λ:�� ȡֵ��ΧΪ1-3600)
}CLOUD_CRUISE_POINT, *LPCLOUD_CRUISE_POINT ;


//!Cloud PTZѲ��·�������ṹ
typedef struct _tagCruiseRoute
{
	WORD wRoute ;								//!Ѳ��·����(��1��ʼ)
	WORD wCruisePointNum ;						//!ʵ��Ѳ��������
	CLOUD_CRUISE_POINT struCruisePoint[256] ;	//!Ѳ���㼯��
}CLOUD_CRUISE_ROUTE, *LPCLOUD_CRUISE_ROUTE ;


//!Cloud PTZѲ������/ֹͣ���нṹ
typedef struct _tagCruiseRouteNo
{
	WORD wRoute ;								//!Ѳ��·����(��1��ʼ)
	WORD wRes ;									//!����λ
}CLOUD_CRUISE_ROUTE_NO, *LPCLOUD_CRUISE_ROUTE_NO ;


//!Cloud PTZѲ������ӽṹ
typedef struct _tagAddCruisePoint
{
	WORD wRoute ;								//!Ѳ��·����(��1��ʼ)
	WORD wPoint ;								//!Ѳ����,���Ϊ0xFFFF���ʾ��β������,���򰴵�ǰ��Ų���
	BYTE byPresetNo ;							//!Ԥ�õ��(��1��ʼ)
	BYTE bySpeed ;								//!Ԥ�õ�����ٶ�(1-16)
	WORD wDWellTime ;							//!Ԥ�õ�ͣ��ʱ��(��λ:�� ȡֵ��ΧΪ1-3600)
}CLOUD_ADD_CRUISE_POINT, *LPCLOUD_ADD_CRUISE_POINT ;


//!Cloud PTZѲ����ɾ���ṹ
typedef struct _tagDelCruisePoint
{
	WORD wRoute ;								//!Ѳ��·����(��1��ʼ)
	WORD wPoint ;								//!Ѳ�����(��1��ʼ)
}CLOUD_DEL_CRUISE_POINT, *LPCLOUD_DEL_CRUISE_POINT ;


//!Cloud ���������ṹ
typedef struct _tagUpAlarmCond
{
	WORD wResult ;								//!���ش�����,�ο�cloud_result_code_t
	WORD wRes ;									//!����λ
	DWORD dwAlarmType ;							//!��������
	WORD wParam ;								//!�˱��������Ƿ����ͨ��(�漰����ͨ���й����ı�������,�������������ͨ���޹�,����Ϊ0xFFFF)
	WORD wRes1[7] ;								//!����λ
}CLOUD_UPALARM_COND, *LPCLOUD_UPALARM_COND ;


//!Cloud ������Ϣ�ṹ
typedef struct _tagAlarmInfo
{
	DWORD dwAlarmType ;							//!��������
	WORD wParam ;								//!������������
	WORD wRes ;									//!����λ
	DWORD dwTimeStamp ;							//!����ʱ���
}CLOUD_ALARM_INFO, *LPCLOUD_ALARM_INFO ;


//!Cloud �ļ���ѯ�������ݽṹ
typedef struct _tagFindFileCond
{
	WORD wChannel ;							//!��ѯͨ����(��1��ʼ)
	WORD wRes ;								//!����λ,��ʱ����
	DWORD dwFileType ;						//!¼���ļ�����0xff��ȫ����0����ʱ¼��,1-�ƶ���� ��2������������3-����|�ƶ���� 4-����&�ƶ���� 5-����� 6-�ֶ�¼��
	CLOUD_TIME struBeginTime ;				//!��ʼʱ��
	CLOUD_TIME struEndTime ;				//!����ʱ��
	BYTE byRes[16] ;						//!����λ	
}CLOUD_FIND_FILE_COND, *LPCLOUD_FIND_FILE_COND ;


//!Cloud ��ѯ�ļ����
typedef struct _tagFindFileData
{
	char szFileName[128];					//!�ļ���
	CLOUD_TIME struStartTime;				//!�ļ��Ŀ�ʼʱ��
	CLOUD_TIME struStopTime;				//!�ļ��Ľ���ʱ��
	DWORD dwFileSize;						//!�ļ��Ĵ�С
	BYTE byFileType;						//!�ļ�����
	WORD wChannel ;							//!��Ƶͨ����(��1��ʼ)
	BYTE byRes[21];							//!����λ
}CLOUD_FIND_FILE_DATA, *LPCLOUD_FIND_FILE_DATA ;



////////////////////////////////////////////////////////////////////////////////
// �ص���������
////////////////////////////////////////////////////////////////////////////////
/*!
* ��Ч�û�����״̬�ص�
* \param hRegisterId		ע�������ID���
* \param hUserId			ע���û�ID���
* \param lpUserIP			ע���û���ǰIP��ַ
* \param eUserWorkModel		ע���û�����ģʽ
* \param eUserStatus		ע���û�״̬
* \param lpUser				�ص�����������
* \return ����VOID����
*/
typedef VOID (CALLBACK *fValidUserCallBack)(IN HANDLE hRegisterId, IN HANDLE hUserId, IN S8 *lpUserIP, IN cloud_user_workmodel_t eUserWorkModel, IN cloud_user_status_t eUserStatus, IN LPCLOUD_DEVICE_INFO lpDeviceInfo, IN VOID *lpUser) ;


/*!
* �û�����״̬��Ϣ�ص�
* \param hUserId		ע���û�ID���
* \param lpInBuffer		����ָ���ַ
* \param s32BufSize		���ݳ���
* \param lpUser			�ص�����������
* \return ����VOID����
*/
typedef VOID (CALLBACK *fUserWorkStatusCallBack)(IN HANDLE hUserId, IN S8 *lpInBuffer, IN S32 s32BufSize, IN VOID *lpUser) ;


/*!
* �û������ݻص�
* \param hUserId		ע���û�ID���
* \param lpInBuffer1	����1��Чָ���ַ
* \param s32BufSize1	����1��Ч����
* \param lpInBuffer2	����2��Чָ���ַ
* \param s32BufSize2	����2��Ч����
* \param lpUser			�ص�����������
* \return ����VOID����
*/
typedef VOID (CALLBACK *fUserStreamDataCallBack)(IN HANDLE hUserId, IN S8 *lpInBuffer1, IN S32 s32BufSize1, IN S8 *lpInBuffer2, IN S32 s32BufSize2, IN VOID *lpUser) ;


/*!
* �������ݻص�
* \param hUserId		ע���û�ID���
* \param lpInBuffer1	������Ϣ����
* \param s32BufSize1	������Ϣ����
* \param lpUser			�ص�����������
* \return ����VOID����
*/
typedef VOID (CALLBACK *fUserAlarmMessageCallBack)(IN HANDLE hUserId, IN S8 *lpInBuffer, IN S32 s32BufSize, IN VOID *lpUser) ;



/*!
* ��Ч�û�����״̬�ص�v2 2016-07-21
* \param lpUuid			�豸���к�(Ψһ��ʶ��)
* \param lpUserIP		�豸��ǰIP��ַ
* \param eUserStatus	�豸����״̬
* \param lpDeviceInfo	�豸������Ϣ
* \param lpUser			�ص�����������
* \return ����VOID����
*/
typedef VOID (CALLBACK *fValidUserCallBackv2)(IN S8 *lpUuid, IN S8 *lpIPAddr, IN cloud_user_status_t eUserStatus, IN LPCLOUD_DEVICE_INFO_V2 lpDeviceInfo, IN VOID *lpUser) ;



/*!
* �������ݻص�v2 2016-07-21
* \param lpUuid			�豸���к�(Ψһ��ʶ)
* \param lpInBuffer1	������Ϣ����
* \param s32BufSize1	������Ϣ����
* \param lpUser			�ص�����������
* \return ����VOID����
*/
typedef VOID (CALLBACK *fUserAlarmMessageCallBackv2)(IN S8 *lpUuid, IN S8 *lpInBuffer, IN S32 s32BufSize, IN VOID *lpUser) ;



/*!
* �û�����״̬��Ϣ�ص�v2 2016-07-21
* \param lpUuid			�豸���к�(Ψһ��ʶ)
* \param lpInBuffer		����ָ���ַ
* \param s32BufSize		���ݳ���
* \param lpUser			�ص�����������
* \return ����VOID����
*/
typedef VOID (CALLBACK *fUserWorkStatusCallBackv2)(IN S8 *lpUuid, IN S8 *lpInBuffer, IN S32 s32BufSize, IN VOID *lpUser) ;



#endif

