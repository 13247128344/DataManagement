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
// 宏定义
////////////////////////////////////////////////////////////////////////////////

//!输入参数
#ifndef IN
#define IN
#endif

//!输出参数
#ifndef OUT
#define OUT
#endif

//!输入输出参数
#ifndef INOUT
#define INOUT
#endif

#define PACKET_STX	(0xFEDCBA98) 						//!数据包起始码
#define PACKET_ETX	(0x12345678)						//!数据包终止码

#define PACKET_RAW_DATA		0							//!原始数据
#define PACKET_XML_DATA 	1							//!XML数据
#define PACKET_JSON_DATA 	2							//!JSON数据
	
#define PACKET_UNZIP		0							//!数据未经ZIP压缩处理
#define PACKET_ZIP			1							//!数据经ZIP压缩处理
////////////////////////////////////////////////////////////////////////////////
// 枚举定义
////////////////////////////////////////////////////////////////////////////////

//!接口返回值宏定义
typedef enum e_cloud_result_code
{
	Cloud_ResultCode_Succ = 0 ,							//!成功
	Cloud_ResultCode_Failed = 1 ,						//!失败
	Cloud_ResultCode_VersionMisMatch = 2,				//!版本不匹配
	Cloud_ResultCode_NoInit = 3,						//!sdk未初始化
	Cloud_ResultCode_NoStart = 4,						//!未启动
	Cloud_ResultCode_HasInit = 5,						//!sdk已初始化
	Cloud_ResultCode_HasStarted = 6,					//!已经启动
	Cloud_ResultCode_Unsupported = 7,					//!不支持的操作

	Cloud_ResultCode_InvalidParam = 8,					//!参数无效
	Cloud_ResultCode_InvalidHandle = 9,					//!句柄值无效
	Cloud_ResultCode_InValidUser = 10,					//!无效用户
	
	Cloud_ResultCode_NoMem = 11,						//!没有内存
	Cloud_ResultCode_NoHandle = 12,						//!没有句柄
	Cloud_ResultCode_BufTooSmall = 13,			    	//!缓冲区太小

	Cloud_ResultCode_ConnectFailed = 14 ,				//!连接失败
	Cloud_ResultCode_SendFailed = 15,					//!发送失败
	Cloud_ResultCode_RecvFailed = 16,					//!接收失败
	
	Cloud_ResultCode_ConnectTimeout = 17, 				//!连接超时
	Cloud_ResultCode_SendTimeout = 18, 					//!发送超时
	Cloud_ResultCode_RecvTimeout = 19, 					//!接收超时
	Cloud_ResultCode_TryConnectError = 20,				//!尝试连接错误
	Cloud_ResultCode_ListenPortSame = 21,				//!监听端口冲突

	Cloud_ResultCode_MatchMagicIdError = 22,			//!匹配Magic起始码错误
	Cloud_ResultCode_MatchMagicEtxError = 38,			//!匹配Magic终止码错误
	Cloud_ResultCode_MatchPacketEtxError = 23,			//!匹配包数据终止码错误
	Cloud_ResultCode_MatchSeqNoError = 24,				//!匹配包序号错误
	Cloud_ResultCode_DataFormatError = 25,				//!用户数据格式错误

	Cloud_ResultCode_WaitTimeOut = 26,					//!等待响应超时
	Cloud_ResultCode_ListFull = 27,						//!队列满
	Cloud_ResultCode_P2PHostSame = 28,					//!P2P地址冲突
	
	Cloud_ResultCode_AuthenticationError = 29,			//!用户认证错误
	Cloud_ResultCode_NoRight = 30,						//!当前操作无权限
	
	Cloud_ResultCode_CallNetLogicAPIError = 31,			//!调用逻辑库API接口失败
	Cloud_ResultCode_DevException = 32,					//!设备异常
	Cloud_ResultCode_SerializeDataError = 33,			//!序列化错误
	Cloud_ResultCode_DeserializeDataError = 34,			//!反序列化错误
	Cloud_ResultCode_NoResource = 35,					//!无资源
	Cloud_ResultCode_OverMaxNum = 36,					//!超过总数
	Cloud_ResultCode_HandleExist = 37,					//!句柄已存在
	Cloud_ResultCode_ReplayHandleError = 38,			//!回放句柄
	
}cloud_result_code_t ;


//!传输数据类型宏定义
typedef enum e_cloud_data_tran_type 
{
	Cloud_TranRealVideoData 	= 0x01,
	Cloud_TranRealAudioData 	= 0x02,
	Cloud_TranTalkData 			= 0x03,
	Cloud_TranHistroyVideoData 	= 0x04,
	Cloud_TranHistroyAudioData 	= 0x05,
}cloud_data_tran_type_t ;


//!音频编码格式宏定义
typedef enum e_cloud_audio_format
{
	Cloud_Audio_G711_U 		= 0x01,
	Cloud_Audio_G711_A		= 0x02,
	Cloud_Audio_G726		= 0x03,
}cloud_audio_format_t ;
	

//!视频编码格式宏定义
typedef enum e_cloud_video_format
{
	Cloud_Video_I8			= 0x01,
	Cloud_Video_H264		= 0x02,
	Cloud_Video_H265		= 0x03,
	Cloud_Video_AVI			= 0x04,
}cloud_video_format_t ;


//!帧类型宏定义
typedef enum e_cloud_frame_type
{
	Cloud_Main_IFrame 		= 0x01,	
	Cloud_Main_PFrame 		= 0x02,
	Cloud_Sub_IFrame		= 0x03,
	Cloud_Sub_PFrame		= 0x04,
	Cloud_Main_AudioFrame 	= 0x05,
	Cloud_Sub_AudioFrame 	= 0x06,	
}cloud_frame_type_t ;


//!音频采样率宏定义
typedef enum e_cloud_audio_samplerate
{
	Cloud_Audio_SampleRate_8000HZ	= 0x01,
	Cloud_Audio_SampleRate_32000HZ	= 0x02,
	Cloud_Audio_SampleRate_48000HZ	= 0x03,
	Cloud_Audio_SampleRate_96000HZ	= 0x04,	
}cloud_audio_samplerate_t ;

	
//!用户上下线状态宏定义
typedef enum e_cloud_user_status
{
	Cloud_User_OffLine 	= 0,	//!用户离线状态
	Cloud_User_OnLine 	= 1,	//!用户在线状态
}cloud_user_status_t ;


//!用户工作模式宏定义
typedef enum e_cloud_user_workmodel
{
	Cloud_User_None 		= 0,
	Cloud_User_RootModel 	= 1,		//!根连接用户(负责实时流/语音对讲/PTZ控制/报警信息推送/消息请求及响应)
	Cloud_User_ReplayModel 	= 2,		//!子连接用户(负责历史流下载/回放)
}cloud_user_workmodel_t ;


//!PTZ控制命令宏定义	
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


//!轨迹操作宏定义
typedef enum e_cloud_ptz_track_t
{
	CLOUD_PTZ_TRACK_START = 0x00, 	//!开始记录轨迹
	CLOUD_PTZ_TRACK_STOP, 			//!停止记录轨迹
	CLOUD_PTZ_TRACK_DEL,			//!删除记录轨迹
	CLOUD_PTZ_TRACK_RUN,			//!运行记录轨迹
	CLOUD_PTZ_TRACK_STOPRUN,		//!停止运行记录轨迹
}cloud_ptz_track_t ;



//!巡航操作宏定义
typedef enum e_cloud_ptz_cruise_t
{
	CLOUD_PTZ_CRUISE_ROUTE_ADD = 0x00,		//!巡航添加(添加整条巡航路径,填写CLOUD_CRUISE_ROUTE结构)
	CLOUD_PTZ_CRUISE_ROUTE_DEL,				//!巡航删除(删除整条巡航路径,填写CLOUD_CRUISE_ROUTE_NO结构)
	CLOUD_PTZ_CRUISE_ROUTE_RUN,				//!巡航路径运行(填写巡航路径,填写CLOUD_CRUISE_ROUTE_NO结构)
	CLOUD_PTZ_CRUISE_ROUTE_STOPRUN,			//!巡航路径运行停止(填写巡航路径,填写CLOUD_CRUISE_ROUTE_NO结构)
	CLOUD_PTZ_CRUISE_POINT_ADD,				//!巡航点添加(针对已存在巡航路径进行添加巡航点,填写CLOUD_ADD_CRUISE_POINT结构指针)
	CLOUD_PTZ_CRUISE_POINT_DEL,				//!巡航点删除(针对已存在巡航路径进行删除巡航点,填写CLOUD_DEL_CRUISE_POINT结构指针)
}cloud_ptz_cruise_t ;



//!报警类型宏定义	
typedef enum e_cloud_alarm_type
{
	CLOUD_ALARM_VIDEOMOTION_TYPE 	= 0x0001,			//!移动侦测报警类型
	CLOUD_ALARM_ALARMIN_TYPE 		= 0x0002,			//!输入报警类型
	CLOUD_ALARM_VIDEOLOST_TYPE 		= 0x0003,			//!视频丢失报警类型
	CLOUD_ALARM_VIDEOMASK_TYPE 		= 0x0004,			//!视频遮挡报警类型
	CLOUD_ALARM_DISKFULL_TYPE		= 0x0005,			//!硬盘满	
	CLOUD_ALARM_DISKERROR_TYPE 		= 0x0006,			//!硬盘错误
	CLOUD_ALARM_ILLEGEACCESS_TYPE	= 0x0007,			//!非法访问
	CLOUD_ALARM_NETDISCONNECT_TYPE	= 0x0008,			//!网线断开
	CLOUD_ALARM_IPCONFLICT_TYPE		= 0x0009,			//!IP冲突
}cloud_alarm_type_t ;

	
//!码流类型宏定义
typedef enum e_cloud_stream_type
{
	Cloud_MainStream = 1,
	Cloud_SubStream  = 2,
	Cloud_MixStream  = 3,
}cloud_stream_type_t ;


//!消息数据包版本宏定义
typedef enum e_cloud_version 
{
	Cloud_VersionV10 = 0x00010000 ,
}cloud_version_t ;


//!消息数据包类型
typedef enum e_cloud_message_type
{
	Cloud_Message4Request 	= 0x0000,
	Cloud_Message4Response 	= 0x0001,
	Cloud_Message4Notify 	= 0x0002,
}cloud_message_type_t ;


//!查找录像文件类型宏定义
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


//!消息命令宏定义
typedef enum e_cloud_message_cmd
{
	//!主动注册服务消息宏定义
	Cloud_Message_LoginNotify = 0x1000,
	Cloud_Message_UpDevWorkStatus,
	Cloud_Message_Authentication,			//!主动注册服务向设备进行用户名和密码认证请求命令
	
	Cloud_Message_RealPlay,					//!主动注册服务向设备进行实时流请求命令
	Cloud_Message_StopRealPlay,				//!主动注册服务向设备进行停止实时流请求命令
	Cloud_Message_ControlRealPlay,			//!主动注册服务向设备进行实时流控制请求命令(如:添加新通道实时流/删除已通道实时流)
	
	Cloud_Message_ZeroRealPlay,				//!主动注册服务向设备进行零通道实时流请求命令
	Cloud_Message_StopZeroRealPlay,			//!主动注册服务向设备进行停止零通道实时流请求命令
	
	Cloud_Message_Replay,					//!主动注册服务向设备进行历史流请求命令		
	Cloud_Message_StopReplay,				//!主动注册服务向设备进行停止历史流请求命令
	Cloud_Message_ControlReplay,			//!主动注册服务向设备进行控制历史流请求命令(如:Seek/Fast/Slow/SetSpeed等操作)
	
	Cloud_Message_AddAlarm,					//!主动注册服务向设备进行报警推送请求命令
	Cloud_Message_DelAlarm,					//!主动注册服务向设备进行停止报警推送请求命令
	Cloud_Message_AlarmInfo,				//!推送报警信息通知
	
	Cloud_Message_ControlPTZ,				//!主动注册服务向设备进行PTZ通知命令
	
	Cloud_Message_FindFile,					//!主动注册服务向设备进行历史文件查询请求
	
	Cloud_Message_Talk,						//!主动注册服务向设备进行语音对讲请求
	Cloud_Message_StopTalk,					//!主动注册服务向设备进行停止语音对讲请求
	
	Cloud_Message_GetConfig,				//!主动注册服务向设备获取配置参数请求
	Cloud_Message_SetConfig,				//!主动注册服务向设备设置配置参数请求
	
	Cloud_Message_CruisePTZ,				//!巡航操作命令
	Cloud_Message_QueryCruisePTZ,			//!查询巡航路径命令
	Cloud_Message_TrackPTZ,					//!轨迹操作命令
	Cloud_Message_TranPTZ,					//!透明通道传输命令
	
	//!私有P2P协议消息宏定义
	Cloud_Message_LoginV2 = 0x8000,			//!用户注册命令(c->s)
	Cloud_Message_LogoutV2,					//!用户注销命令(c->s)
	Cloud_Message_HeartBeatV2,				//!用户心跳命令(c->s)
	
	Cloud_Message_RealPlayV2,				//!实时流请求命令(c->s)
	Cloud_Message_StopRealPlayV2,			//!停止实时流请求命令(c->s)
	Cloud_Message_ControlRealPlayV2,		//!控制实时流控制请求命令(如:添加新通道实时流/删除已通道实时流)(c->s)
	
	Cloud_Message_ZeroRealPlayV2,			//!零通道实时流请求命令(c->s)
	Cloud_Message_StopZeroRealPlayV2,		//!停止零通道实时流请求命令(c->s)
	
	Cloud_Message_ReplayV2,					//!历史流请求命令(c->s)
	Cloud_Message_StopReplayV2,				//!停止历史流请求命令(c->s)
	Cloud_Message_ControlReplayV2,			//!控制历史流请求命令(如:Seek/Fast/Slow/SetSpeed等操作)(c->s)
	
	Cloud_Message_AddAlarmV2,				//!报警推送请求命令(c->s)
	Cloud_Message_DelAlarmV2,				//!停止报警推送请求命令(c->s)
	Cloud_Message_AlarmInfoV2,				//!推送报警信息通知(s->c)
	
	Cloud_Message_ControlPTZV2,				//!PTZ请求命令(c->s)
	
	Cloud_Message_FindFileV2,				//!历史文件查询请求(c->s)
	
	Cloud_Message_TalkV2,					//!语音对讲请求(c->s)
	Cloud_Message_StopTalkV2,				//!停止语音对讲请求(c->s)
	
	Cloud_Message_GetConfigV2,				//!获取配置参数请求(c->s)
	Cloud_Message_SetConfigV2,				//!设置配置参数请求(c->s)
	
	Cloud_Message_QueryLinkUuidV2,			//!查询当前连接UUID(c->s)
	Cloud_Message_StopRealPlayV22,			//!停止实时流请求命令(c->s)(扩展命令)

	Cloud_Message_TranControlV2,			//!透传信息请求命令
	
	//!仅供转发模块使用的宏定义
	Cloud_Dev2Agent_Message_Login = 0x9000,	//!设备注册通知	
	Cloud_Dev2Agent_Message_Logout,			//!设备注销通知
	Cloud_Dev2Agent_Message_HeartBeat,	    //!设备心跳消息
	Cloud_Dev2Agent_Message_RealPlay,		//!设备预览控制
	Cloud_Dev2Agent_Message_Talk,			//!设备语音开启
	Cloud_Dev2Agent_Message_StopTalk,		//!设备语音关闭
	
}cloud_message_cmd_t ;



//!扩展消息命令
typedef enum e_cloud_message_cmdv2
{
	Cloud_Cmd_DevStatus 			= (1 << 0),		//!设备工作状态推送命令(c->s)	
	Cloud_Cmd_DevAlarm 				= (1 << 1),		//!设备报警推送命令(c->s)
	Cloud_Cmd_DevConnect 			= (1 << 2),		//!设备注册主动注册服务命令(s->c)
	Cloud_Cmd_DevDisconnect 		= (1 << 3),		//!设备注销主动注册服务命令(s->c)
	Cloud_Cmd_DevSubscribeAlarm 	= (1 << 4),		//!设备报警订阅命令(s->c)
	Cloud_Cmd_DevUnsubscribeAlarm 	= (1 << 5),		//!设备取消报警订阅命令(s->c)
}cloud_message_cmdv2_t ;



//!配置参数获取与设置宏定义
typedef enum e_cloud_config_cmd
{
	Cloud_Config_GetDevInfo =0x2000,	//!获取设备基本信息(针对主动注册服务)	
	Cloud_Config_GetDevWorkStatus,		//!获取设备工作状态
	
	Cloud_Config_GetDevCfg,				//!获取设备基本参数
	Cloud_Config_SetDevCfg,				//!设置设备基本参数
	
	Cloud_Config_GetNetCfg,				//!获取设备网络参数
	Cloud_Config_SetNetCfg,				//!设置设备网络参数
	
	Cloud_Config_GetUserCfg,			//!获取设备用户参数(针对主动注册服务)
	Cloud_Config_SetUserCfg,			//!设置设备用户参数(针对主动注册服务)

	Cloud_Config_GetTimeCfg,			//!获取设备用户参数
	Cloud_Config_SetTimeCfg,			//!设置设备用户参数

	Cloud_Config_GetDevInfoV2 = 0x8000,	//!获取设备基本信息(针对P2P服务)
	Cloud_Config_GetUserCfgV2,			//!获取设备用户参数(针对P2P服务)
	Cloud_Config_SetUserCfgV2,			//!设置设备用户参数(针对P2P服务)

}cloud_config_cmd_t ;


//!实时流播放控制命令
typedef enum e_cloud_control_realplay_cmd
{
	Cloud_ControlRealplay_PlayAudio			= 1,	//!打开声音 使用CLOUD_CONTROL_REALPLAY_COND结构中 dwParams[0]描述主子码流类型 1-主码流 2-子码流 dwParams[1]描述通道号
	Cloud_ControlRealPlay_StopAudio			= 2,	//!关闭声音 使用CLOUD_CONTROL_REALPLAY_COND结构中 dwParams[0]描述主子码流类型 1-主码流 2-子码流 dwParams[1]描述通道号
	Cloud_ControlRealPlay_SwitchStreamType	= 3,	//!切换主子码流类型 使用CLOUD_CONTROL_REALPLAY_COND结构中 dwParams[0]描述 1-主码流 2-子码流 dwParams[1]描述通道号 dwParams[2]描述切换目标码流类型 1-主码流 2-子码流
	Cloud_ControlRealPlay_AddChan			= 4,	//!加入通道 使用CLOUD_CONTROL_REALPLAY_COND结构中 dwParams[0]描述码流类型 1-主码流 2-子码流 dwParams[1]描述通道号 
	Cloud_ControlRealPlay_DelChan			= 5,	//!删除通道 使用CLOUD_CONTROL_REALPLAY_COND结构中 dwParams[0]描述码流类型 1-主码流 2-子码流 dwParams[1]描述通道号
}cloud_control_realplay_cmd_t ;


//!历史流回放/下载播放控制命令
typedef enum e_cloud_control_replay_cmd
{
	Cloud_ControlReplay_Play				= 0x1,	//!暂停播放 使用CLOUD_CONTROL_REALPLAY_COND结构中 dwInParams[0]描述码流类型 1-主码流 2-子码流 dwInParams[1]描述通道号
	Cloud_ControlReplay_Pause				= 0x2,	//!暂停播放 使用CLOUD_CONTROL_REALPLAY_COND结构中 dwInParams[0]描述码流类型 1-主码流 2-子码流 dwInParams[1]描述通道号
	Cloud_ControlReplay_Repeat				= 0x3,	//!恢复播放 使用CLOUD_CONTROL_REALPLAY_COND结构中 dwInParams[0]描述码流类型 1-主码流 2-子码流 dwInParams[1]描述通道号
	Cloud_ControlReplay_PlayAudio			= 0x4,	//!打开声音 使用CLOUD_CONTROL_REALPLAY_COND结构中 dwInParams[0]描述码流类型 1-主码流 2-子码流 dwInParams[1]描述通道号
	Cloud_ControlReplay_StopAudio			= 0x5,	//!关闭声音 使用CLOUD_CONTROL_REALPLAY_COND结构中 dwInParams[0]描述码流类型 1-主码流 2-子码流 dwInParams[1]描述通道号
	Cloud_ControlReplay_SetSpeed			= 0x6,	//!设置播放速度 使用CLOUD_CONTROL_REALPLAY_COND结构中 dwInParams[0]描述码流类型 1-主码流 2-子码流 dwInParams[1]描述通道号 dwInParams[2]描述速度值 -16~16
	Cloud_ControlReplay_SetTime				= 0x7,	//!设置回放时间 使用CLOUD_CONTROL_REALPLAY_COND结构中 dwInParams[0]描述码流类型 1-主码流 2-子码流 dwInParams[1]描述通道号 dwInParams[2]描述秒数
	Cloud_ControlReplay_SwitchStreamType 	= 0x8,	//!切换主子码流类型 使用CLOUD_CONTROL_REALPLAY_COND结构中 dwInParams[0]描述码流类型 1-主码流 2-子码流 dwInParams[1]描述通道号 dwInParams[2]描述切换目标码流类型
	Cloud_ControlReplay_PlayDirect			= 0x9,	//!控制回放正放/倒放 使用CLOUD_CONTROL_REPLAY_COND结构中 dwInParams[0]描述码流类型 1-主码流 2-子码流 dwInParams[1]描述通道号 dwInParams[2]描述是否正放倒放 0-正放 1-倒放
	Cloud_ControlReplay_AddChan				= 0xa,	//!加入同步通道 使用CLOUD_CONTROL_REPLAY_COND结构中 dwInParams[0]描述码流类型 1-主码流 2-子码流 dwInParams[1]描述通道号
	Cloud_ControlReplay_DelChan				= 0xb,	//!移除同步通道 使用CLOUD_CONTROL_REPLAY_COND结构中 dwInParams[0]描述码流类型 1-主码流 2-子码流 dwInParams[1]描述通道号
}cloud_control_replay_cmd_t ;


////////////////////////////////////////////////////////////////////////////////
// 结构体定义
////////////////////////////////////////////////////////////////////////////////	
//!Cloud 设备基本信息数据结构
typedef struct _tagDeviceInfo
{
	BYTE bySerialNo[48] ;		//!设备序列号
	BYTE byAlarmInNum ;			//!报警输入总数
	BYTE byAlarmOutNum ;		//!报警输出总数
	BYTE byDiskNum ;			//!硬盘总数
	BYTE byDeviceType ;			//!设备类型
	WORD wChanNum ;				//!设备视频通道总数
	WORD wStartChan ;			//!设备视频起始通道
	WORD wAudioChanNum ;		//!设备音频通道总数
	WORD wZeroChanNum ;			//!设备零通道总数
	DWORD dwSupport ;			//!设备能力,位与结果为0表示不支持,1表示支持
	BYTE byDevName[32] ;		//!设备名称
}CLOUD_DEVICE_INFO, *LPCLOUD_DEVICE_INFO ;


typedef struct _tagDeviceInfov2
{
	BYTE byAlarmInNum ;			//!报警输入总数
	BYTE byAlarmOutNum ;		//!报警输出总数
	BYTE byDiskNum ;			//!硬盘总数
	BYTE byDeviceType ;			//!设备类型
	WORD wChanNum ;				//!设备视频通道总数
	WORD wStartChan ;			//!设备视频起始通道
	WORD wAudioChanNum ;		//!设备音频通道总数
	WORD wZeroChanNum ;			//!设备零通道总数
	DWORD dwSupport ;			//!设备能力,位与结果为0表示不支持,1表示支持
	BYTE byDevName[32] ;		//!设备名称	
	BYTE byLocalIP[40] ;		//!设备IP地址
}CLOUD_DEVICE_INFO_V2, *LPCLOUD_DEVICE_INFO_V2 ;


//!Cloud 设备工作状态数据结构
typedef struct _tagDeviceWorkStatus
{
	DWORD dwChannel[256] ;				//!设备通道工作状态 用移位方式定义 bit0-表示是否有视频 bit1-表示是否录像 bit2-表示语音对讲是否开启
	CLOUD_DEVICE_INFO_V2 struDevInfo ;	//!设备基本信息
	BYTE byRes[40] ;					//!保留位
}CLOUD_DEVICE_WORKSTATUS, *LPCLOUD_DEVICE_WORKSTATUS ;


//!Cloud 设备用户认证数据结构
typedef struct _tagDevUserAuth
{
	char szUserName[32] ;	//!当前用户名
	char szPassword[16] ;	//!当前密码
	DWORD dwChannel[256] ;	//!通道权限 bit0-是否有远程预览权限 bit1-是否有远程回放/下载权限 bit2-是否有远程PTZ控制权限 bit3-是否有远程语音转发权限
	BYTE byLocalTalkRight ;	//!当前用户是否有语音对讲权限 0-无权限 1-有权限
	BYTE byGetConfigRight ;	//!当前用户是否有获取配置参数权限
	BYTE bySetConfigRight ;	//!当前用户是否有设置配置参数权限
	BYTE byRes[13] ;		//!保留位,暂时不用	
}CLOUD_DEVICE_AUTHENTICATION, *LPCLOUD_DEVICE_AUTHENTICATION ;


//!Cloud 校时数据结构
typedef struct _tagTime
{
	DWORD dwYear;	//!年
	DWORD dwMonth;	//!月
	DWORD dwDay;	//!日
	DWORD dwHour;	//!时
	DWORD dwMinute;	//!分
	DWORD dwSecond;	//!秒
}CLOUD_TIME, *LPCLOUD_TIME;


//!Cloud 实时流请求结构
typedef struct _tagRealPlayCond
{
	WORD wResult ;								//!返回错误码,参考cloud_result_code_t
	WORD wRes ;									//!保留位
	WORD wChannel ;								//!实时流请求通道(从1开始)	
	WORD wStreamType ;							//!实时流请求码流类型
	BYTE byRes[32] ;							//!保留位,暂时不用
}CLOUD_REALPLAY_COND, *LPCLOUD_REALPLAY_COND ;


//!Cloud 实时流控制结构
typedef struct _tagControlRealPlayCond
{
	WORD wResult ;								//!返回错误码,参考cloud_result_code_t
	WORD wRes ;									//!保留位
	DWORD dwRealPlayCmd ;						//!实时流控制命令
	DWORD dwParams[4] ;							//!实时流控制参数
}CLOUD_CONTROL_REALPLAY_COND, *LPCLOUD_CONTROL_REALPLAY_COND ;


//!Cloud 语音对讲请求结构
typedef struct _tagTalkCond
{
	WORD wResult ;								//!返回错误码,参考cloud_result_code_t
	WORD wRes ;									//!保留位
	WORD wChannel ;								//!语音对讲通道号(第15位表示是否与设备端对讲,1-表示与设备端对讲,0-表示与前端IPC对讲,第0位~第14位表示视频通道号,视频通道号从1开始)
	BYTE byEncodeType ;							//!语音对讲编码类型 0-G711-U 1-G711A 
	BYTE byTrack ;								//!语音对讲单双声道 0/1-mono 2-stero
	BYTE bySampleBitWidth ;						//!语音对讲采样位率 8bit 16bit
	BYTE byRes1[3] ;							//!保留位
	DWORD dwSampleRate ;						//!语音对讲采样率 8000kbs
	BYTE byRes2[32] ;							//!保留位
}CLOUD_TALK_COND, *LPCLOUD_TALK_COND ;


typedef struct _tagTalkParam
{
	BYTE byType;				//!0- G711.u;1-G711.a;2-G.726.3;
	BYTE bySampleBitsWidth; 	//!0无效，8 or 16
	BYTE byTrack; 				//!0:无效(mono);1: mono, 2: stero
	BYTE byFrameRate;			//!0:无效(25)
	DWORD dwSampleRate;			//!0无效(8000)
	DWORD dwBitRate;			//!0无效
}CLOUD_TALK_PARAM,*LPCLOUD_TALK_PARAM ;


typedef struct _tagTalkAudioHeader
{
	BYTE byType;						//!0-无效; 1-G711u;2- G711.a;2-G726;
	BYTE bySampleBitsWidth; 			//!8 or 16, 0-无效(16)
	BYTE byChannels; 					//!0:无效(mono);1: mono, 2: stero
	BYTE byFrameRate;					//!0-无效(25)
	DWORD dwSampleRate;					//!0-无效(8000)
	DWORD dwBitRate;					//!0-无效
	DWORD dwPayloadLength;
	U64 u64TimeStamp;					//!0-无效
}CLOUD_TALK_AUDIOHEADER, *LPCLOUD_TALK_AUDIOHEADER ;


//!Cloud 历史流请求结构
typedef struct _tagReplayCond
{
	WORD wResult ;								//!返回错误码,参考cloud_result_code_t
	WORD wRes ;									//!保留位
	WORD wChannel ;								//!历史流请求通道(从1开始)
	WORD wStreamType ;							//!历史流请求码流类型
	CLOUD_TIME struStartTime ;					//!历史流开始时间
	CLOUD_TIME struStopTime ;					//!历史流结束时间
	BYTE byRes[32] ;							//!保留位,暂时不用
}CLOUD_REPLAY_COND, *LPCLOUD_REPLAY_COND ;


//!*Cloud 历史流控制结构
typedef struct _tagControlReplayCond
{
	WORD wResult ;								//!返回错误码,参考cloud_result_code_t
	WORD wRes ;									//!保留位
	DWORD dwReplayCmd ;							//!历史流控制命令
	DWORD dwInParams[4] ;						//!历史流控制输入参数
	DWORD dwOutParams[4] ;						//!历史流控制输出参数
}CLOUD_CONTROL_REPLAY_COND, *LPCLOUD_CONTROL_REPLAY_COND ;


//!Cloud PTZ控制参数结构
typedef struct _tagControlPTZCond
{
	WORD wResult ;							//!返回错误码,参考cloud_result_code_t
	WORD wRes ;								//!保留位
	WORD wChannel ;							//!通道号(从1开始)
	WORD wPTZCmd ;							//!PTZ控制ID
	DWORD dwInParams[4] ;					//!PTZ控制输入参数
}CLOUD_CONTROL_PTZ_COND, *LPCLOUD_CONTROL_PTZ_COND ;


//!Cloud PTZ巡航控制参数结构
typedef struct _tagCruisePoint
{
	BYTE byPresetNo ;						//!预置点号(从1开始)
	BYTE bySpeed ;							//!预置点调用速度(1-16)
	WORD wDWellTime ;						//!预置点停留时间(单位:秒 取值范围为1-3600)
}CLOUD_CRUISE_POINT, *LPCLOUD_CRUISE_POINT ;


//!Cloud PTZ巡航路径参数结构
typedef struct _tagCruiseRoute
{
	WORD wRoute ;								//!巡航路径号(从1开始)
	WORD wCruisePointNum ;						//!实际巡航点总数
	CLOUD_CRUISE_POINT struCruisePoint[256] ;	//!巡航点集合
}CLOUD_CRUISE_ROUTE, *LPCLOUD_CRUISE_ROUTE ;


//!Cloud PTZ巡航运行/停止运行结构
typedef struct _tagCruiseRouteNo
{
	WORD wRoute ;								//!巡航路径号(从1开始)
	WORD wRes ;									//!保留位
}CLOUD_CRUISE_ROUTE_NO, *LPCLOUD_CRUISE_ROUTE_NO ;


//!Cloud PTZ巡航点添加结构
typedef struct _tagAddCruisePoint
{
	WORD wRoute ;								//!巡航路径号(从1开始)
	WORD wPoint ;								//!巡航点,如果为0xFFFF则表示在尾部插入,否则按当前点号插入
	BYTE byPresetNo ;							//!预置点号(从1开始)
	BYTE bySpeed ;								//!预置点调用速度(1-16)
	WORD wDWellTime ;							//!预置点停留时间(单位:秒 取值范围为1-3600)
}CLOUD_ADD_CRUISE_POINT, *LPCLOUD_ADD_CRUISE_POINT ;


//!Cloud PTZ巡航点删除结构
typedef struct _tagDelCruisePoint
{
	WORD wRoute ;								//!巡航路径号(从1开始)
	WORD wPoint ;								//!巡航点号(从1开始)
}CLOUD_DEL_CRUISE_POINT, *LPCLOUD_DEL_CRUISE_POINT ;


//!Cloud 报警参数结构
typedef struct _tagUpAlarmCond
{
	WORD wResult ;								//!返回错误码,参考cloud_result_code_t
	WORD wRes ;									//!保留位
	DWORD dwAlarmType ;							//!报警类型
	WORD wParam ;								//!此报警类型是否关联通道(涉及到与通道有关联的报警类型,如果报警类型与通道无关,则置为0xFFFF)
	WORD wRes1[7] ;								//!保留位
}CLOUD_UPALARM_COND, *LPCLOUD_UPALARM_COND ;


//!Cloud 报警信息结构
typedef struct _tagAlarmInfo
{
	DWORD dwAlarmType ;							//!报警类型
	WORD wParam ;								//!报警关联参数
	WORD wRes ;									//!保留位
	DWORD dwTimeStamp ;							//!报警时间戳
}CLOUD_ALARM_INFO, *LPCLOUD_ALARM_INFO ;


//!Cloud 文件查询条件数据结构
typedef struct _tagFindFileCond
{
	WORD wChannel ;							//!查询通道号(从1开始)
	WORD wRes ;								//!保留位,暂时不用
	DWORD dwFileType ;						//!录像文件类型0xff－全部，0－定时录像,1-移动侦测 ，2－报警触发，3-报警|移动侦测 4-报警&移动侦测 5-命令触发 6-手动录像
	CLOUD_TIME struBeginTime ;				//!开始时间
	CLOUD_TIME struEndTime ;				//!结束时间
	BYTE byRes[16] ;						//!保留位	
}CLOUD_FIND_FILE_COND, *LPCLOUD_FIND_FILE_COND ;


//!Cloud 查询文件结果
typedef struct _tagFindFileData
{
	char szFileName[128];					//!文件名
	CLOUD_TIME struStartTime;				//!文件的开始时间
	CLOUD_TIME struStopTime;				//!文件的结束时间
	DWORD dwFileSize;						//!文件的大小
	BYTE byFileType;						//!文件类型
	WORD wChannel ;							//!视频通道号(从1开始)
	BYTE byRes[21];							//!保留位
}CLOUD_FIND_FILE_DATA, *LPCLOUD_FIND_FILE_DATA ;



////////////////////////////////////////////////////////////////////////////////
// 回调函数定义
////////////////////////////////////////////////////////////////////////////////
/*!
* 有效用户在线状态回调
* \param hRegisterId		注册服务器ID句柄
* \param hUserId			注册用户ID句柄
* \param lpUserIP			注册用户当前IP地址
* \param eUserWorkModel		注册用户工作模式
* \param eUserStatus		注册用户状态
* \param lpUser				回调函数上下文
* \return 返回VOID类型
*/
typedef VOID (CALLBACK *fValidUserCallBack)(IN HANDLE hRegisterId, IN HANDLE hUserId, IN S8 *lpUserIP, IN cloud_user_workmodel_t eUserWorkModel, IN cloud_user_status_t eUserStatus, IN LPCLOUD_DEVICE_INFO lpDeviceInfo, IN VOID *lpUser) ;


/*!
* 用户工作状态信息回调
* \param hUserId		注册用户ID句柄
* \param lpInBuffer		数据指针地址
* \param s32BufSize		数据长度
* \param lpUser			回调函数上下文
* \return 返回VOID类型
*/
typedef VOID (CALLBACK *fUserWorkStatusCallBack)(IN HANDLE hUserId, IN S8 *lpInBuffer, IN S32 s32BufSize, IN VOID *lpUser) ;


/*!
* 用户流数据回调
* \param hUserId		注册用户ID句柄
* \param lpInBuffer1	数据1有效指针地址
* \param s32BufSize1	数据1有效长度
* \param lpInBuffer2	数据2有效指针地址
* \param s32BufSize2	数据2有效长度
* \param lpUser			回调函数上下文
* \return 返回VOID类型
*/
typedef VOID (CALLBACK *fUserStreamDataCallBack)(IN HANDLE hUserId, IN S8 *lpInBuffer1, IN S32 s32BufSize1, IN S8 *lpInBuffer2, IN S32 s32BufSize2, IN VOID *lpUser) ;


/*!
* 报警数据回调
* \param hUserId		注册用户ID句柄
* \param lpInBuffer1	报警信息内容
* \param s32BufSize1	报警信息长度
* \param lpUser			回调函数上下文
* \return 返回VOID类型
*/
typedef VOID (CALLBACK *fUserAlarmMessageCallBack)(IN HANDLE hUserId, IN S8 *lpInBuffer, IN S32 s32BufSize, IN VOID *lpUser) ;



/*!
* 有效用户在线状态回调v2 2016-07-21
* \param lpUuid			设备序列号(唯一标识符)
* \param lpUserIP		设备当前IP地址
* \param eUserStatus	设备在线状态
* \param lpDeviceInfo	设备基本信息
* \param lpUser			回调函数上下文
* \return 返回VOID类型
*/
typedef VOID (CALLBACK *fValidUserCallBackv2)(IN S8 *lpUuid, IN S8 *lpIPAddr, IN cloud_user_status_t eUserStatus, IN LPCLOUD_DEVICE_INFO_V2 lpDeviceInfo, IN VOID *lpUser) ;



/*!
* 报警数据回调v2 2016-07-21
* \param lpUuid			设备序列号(唯一标识)
* \param lpInBuffer1	报警信息内容
* \param s32BufSize1	报警信息长度
* \param lpUser			回调函数上下文
* \return 返回VOID类型
*/
typedef VOID (CALLBACK *fUserAlarmMessageCallBackv2)(IN S8 *lpUuid, IN S8 *lpInBuffer, IN S32 s32BufSize, IN VOID *lpUser) ;



/*!
* 用户工作状态信息回调v2 2016-07-21
* \param lpUuid			设备序列号(唯一标识)
* \param lpInBuffer		数据指针地址
* \param s32BufSize		数据长度
* \param lpUser			回调函数上下文
* \return 返回VOID类型
*/
typedef VOID (CALLBACK *fUserWorkStatusCallBackv2)(IN S8 *lpUuid, IN S8 *lpInBuffer, IN S32 s32BufSize, IN VOID *lpUser) ;



#endif

