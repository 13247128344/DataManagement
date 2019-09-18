/************************************************************************
*
*   文件名：cms_connect_parse_common.h
*
*   文件描述：用以描述Server与Client通讯的各指令参数结构体
*
*   创建人：Sunx, 2015年9月14日
*
*   版本号：1.0
*
*   修改记录：
*
************************************************************************/


#ifndef CMS_CONNECT_PARSE_COMMON_H
#define CMS_CONNECT_PARSE_COMMON_H




#if defined(WIN32)
#include <List>



#else
#include <list>
#include <string.h>
#include <time.h>

#endif


#define MAX_SPLIT_COUNT 64
#define MAX_LINKAGEACTION_COUNT 6
#define MAX_LINKAGEACTION_PARAM_COUNT   8
#define MAX_STORAGER_CH_COUNT   256
#define MAX_NAME_LENGTH 64
#define MAX_DESCRIB_LENGTH 256
#define MAX_GROUP_CH_COUNT 16
#define MAX_DECODER_OUTPUT_COUNT 8

#

//返回值错误码
typedef enum
{
	ResultCode_Succ = 0,
	ResultCode_Failed = 1,
	ResultCode_VersionMisMatch = 2,
	ResultCode_NotDone = 3,
	ResultCode_HasDone = 4,
	ResultCode_Unsupported = 5,
	ResultCode_HasStarted = 6,
	ResultCode_NoStart = 7,

	Resultcode_InvalidParam = 8,
	ResultCode_InvalidHandle = 9,
	ResultCode_NoMem = 10,
	ResultCode_NoHandle = 11,
	ResultCode_BufferTooSmall = 12,

	ResultCode_ConnectFailed = 13,
	ResultCode_SendFailed = 14,
	ResultCode_RecvFailed = 15,

	ResultCode_ConnectTimeout = 16,
	ResultCode_SendTimeout = 17,
	ResultCode_RecvTimeout = 18,

	ResultCode_TryConnect = 19,
	ResultCode_SelectError = 20,
	ResultCode_SocketInvalid = 21,
	ResultCode_ListenPortSame = 22,
	ResultCode_MatchMagicIdError = 23,
	ResultCode_MatchEndMarkError = 24,
	ResultCode_WaitSemaphoreError = 25,
	ResultCode_MatchSeqNoError = 26,
	ResultCode_ListFull = 27,
	ResultCode_P2PHostSame = 28,
	ResultCode_NoMatchList = 29,
	ResultCode_EmptyList = 30,
	ResultCode_NoEmptyList = 31,
	ResultCode_InvalidThread = 32,
	ResultCode_NoResource = 33,
	ResultCode_MatchLengthError = 34,
	ResultCode_RegisterUserExist = 35,
}CMS_CONNECT_PARSE_ResultCode;



//数据包类型
typedef enum
{
	PackType_Request = 1,	//请求
	PackType_Reply,			//响应
	PackType_Notice			//通知
}CMS_CONNECT_PARSE_PackType;



//命令字类型
typedef enum
{
	CmdType_AddUser = 1,		//添加用户。请求CMS_CONNECT_PARSE_AddUser_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_ModifyUserPassword, //修改用户密码。请求CMS_CONNECT_PARSE_UserParam，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_DelUser,			//删除用户。请求CMS_CONNECT_PARSE_User，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetUser,        //获取用户列表。请求无参数，响应CMS_CONNECT_PARSE_Common_Reply+CMS_CONNECT_PARSE_AddUser_Request[n]
	CmdType_Login,              //用户登录。请求CMS_CONNECT_PARSE_Login_Request，响应CMS_CONNECT_PARSE_Login_Reply
	CmdType_Logout,             //用户注销。请求无参数，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetDeviceTree,      //获取设备树。请求无参数，响应CMS_CONNECT_PARSE_Node指针
	CmdType_GetDeviceList,      //获取设备列表。请求无参数，响应CMS_CONNECT_PARSE_DeviceNode指针
	CmdType_AddArea,            //添加区域。请求CMS_CONNECT_PARSE_AddArea_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_DelArea,            //删除区域。请求CMS_CONNECT_PARSE_DelArea_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_ModifyArea,         //修改区域名称。请求CMS_CONNECT_PARSE_ModifyArea_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_AddDevice,          //添加设备。请求CMS_CONNECT_PARSE_AddDevice_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_DelDevice,          //删除设备。请求CMS_CONNECT_PARSE_DelDevice_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_ModifyDevice,       //修改设备。请求CMS_CONNECT_PARSE_ModifyDevice_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_StartSearchDevice,       //搜索设备。请求CMS_CONNECT_PARSE_SearchDevice_Request，响应CMS_CONNECT_PARSE_Common_Reply，回调CMS_CONNECT_PARSE_SearchDeviceInfo
	CmdType_StopSearchDevice,   //停止搜索。请求无参数，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_OpenRealtime,       //打开码流。请求CMS_CONNECT_PARSE_Realtime_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_CloseRealtime,      //关闭码流。请求CMS_CONNECT_PARSE_Realtime_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_CtrlPTZ,            //云台控制。请求CMS_CONNECT_PARSE_CtrlPtz_Request，无响应
	CmdType_CtrlPreset,         //预置点控制。请求CMS_CONNECT_PARSE_CtrlPreset_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetCruise,          //获取巡航路径信息。请求CMS_CONNECT_PARSE_CruiseRoute，响应CMS_CONNECT_PARSE_Common_Reply+CMS_CONNECT_PARSE_CruisePoint_Param[n]
	CmdType_SetCruisePoint,		//设置巡航点。请求CMS_CONNECT_PARSE_SetCruise_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_DelCruisePoint,     //删除巡航点。请求CMS_CONNECT_PARSE_CruisePoint，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_ClearCruiseRoute,	//清除巡航路径CMS_CONNECT_PARSE_CruiseRoute，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_RunCruise,          //启动巡航。请求CMS_CONNECT_PARSE_RunCruise_Request,响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_SetLocus,           //设置轨迹。请求CMS_CONNECT_PARSE_SetLocus_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_RunLocus,           //运行轨迹。请求CMS_CONNECT_PARSE_RunLocus_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_ClearLocus,         //清除轨迹。请求CMS_CONNECT_PARSE_Locus，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_OpenIntercom,       //开启对讲。请求CMS_CONNECT_PARSE_Intercom_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_CloseIntercom,      //结束对讲。请求CMS_CONNECT_PARSE_Intercom_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_OpenReplay,         //打开回放。请求CMS_CONNECT_PARSE_Replay_Param+CMS_CONNECT_PARSE_ChId[n]，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_CloseReplay,        //关闭回放。请求无参数，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_CtrlReplay,         //回放控制。请求CMS_CONNECT_PARSE_CtrlReplay_Request，无响应
	CmdType_SearchRecordByMonth,    //按月检索录像，只查询该月的每一天是否有录像。请求CMS_CONNECT_PARSE_InquiryRecByMonth_Request，响应CMS_CONNECT_PARSE_Common_Reply + CMS_CONNECT_PARSE_InquiryRecByMonth_Reply
	CmdType_SearchRecordByTime,       //按时间检索录像。请求CMS_CONNECT_PARSE_Replay_Param+CMS_CONNECT_PARSE_ChId[n]，响应CMS_CONNECT_PARSE_Common_Reply+CMS_CONNECT_PARSE_SearchRecord_Param[n]
	CmdType_GetMapTree,         //获取地图树。请求无参数，响应CMS_CONNECT_PARSE_MapNode指针链表
	CmdType_AddMap,             //添加地图。请求CMS_CONNECT_PARSE_AddMap_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_DelMap,             //删除地图。请求CMS_CONNECT_PARSE_Map，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetMapImage,        //获取地图图像。请求CMS_CONNECT_PARSE_Map，响应CMS_CONNECT_PARSE_Image
	CmdType_GetMapLayout,       //获取地图布局。请求CMS_CONNECT_PARSE_Map，响应CMS_CONNECT_PARSE_Common_Reply+CMS_CONNECT_PARSE_MapItemLayout[n]
	CmdType_MapLayoutSetItem,	//设置地图布局。请求CMS_CONNECT_PARSE_SetMapItemLayout_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_MapLayoutDelItem,	//删除地图布局。请求CMS_CONNECT_PARSE_DelMapItemLayout_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_SearchLog,          //获取操作日志。请求CMS_CONNECT_PARSE_SearchLog_Request,响应CMS_CONNECT_PARSE_SearchLog_Reply+CMS_CONNECT_PARSE_Log[n]
	CmdType_SearchAlarmLog, //获取报警日志。请求CMS_CONNECT_PARSE_SearchLog_Request,响应CMS_CONNECT_PARSE_SearchLog_Reply+CMS_CONNECT_PARSE_AlarmLog[n]
	CmdType_GetGroup,           //获取分组。请求无参数，响应CMS_CONNECT_PARSE_Common_Reply+CMS_CONNECT_PARSE_GroupInfo[n]
	CmdType_AddGroup,           //添加分组。请求CMS_CONNECT_PARSE_Group_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_DelGroup,           //添加分组。请求CMS_CONNECT_PARSE_Group_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GroupAddChannel,    //分组添加通道。请求CMS_CONNECT_PARSE_ChannelInGroup，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GroupDelChannel,    //分组删除通道。请求CMS_CONNECT_PARSE_ChannelInGroup，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetDecoders,        //获取解码器列表。请求无参数，响应CMS_CONNECT_PARSE_Common_Reply+CMS_CONNECT_PARSE_DecoderNode[n]
	CmdType_AddDecoder,			//添加解码器。请求CMS_CONNECT_PARSE_AddDecoder_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_DelDecoder,			//删除解码器。请求CMS_CONNECT_PARSE_DelDecoder_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_ModifyDecoder,		//删除解码器。请求CMS_CONNECT_PARSE_ModifyDecoder_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_StartSearchDecoder,       //搜索解码器。请求无参数，响应CMS_CONNECT_PARSE_Common_Reply，回调CMS_CONNECT_PARSE_SearchDeviceInfo
	CmdType_StopSearchDecoder,      //停止搜索解码器。请求无参数，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetWalls,			//获取电视墙列表。请求无参数，响应CMS_CONNECT_PARSE_Common_Reply+CMS_CONNECT_PARSE_WallInfo[n]
	CmdType_AddWall,			//添加电视墙。请求CMS_CONNECT_PARSE_WallInfo，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_DelWall,            //删除电视墙。请求CMS_CONNECT_PARSE_Wall，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_ModifyWall,         //修改电视墙。请求CMS_CONNECT_PARSE_WallInfo，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_SetWallEnabled,     //设置电视墙启用状态。请求CMS_CONNECT_PARSE_SetWallEnabled_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetWallLayout,      //获取电视墙内布局。请求CMS_CONNECT_PARSE_Wall，响应CMS_CONNECT_PARSE_Common_Reply+CMS_CONNECT_PARSE_WallLayoutItem[n]
	CmdType_SetWallLayout,      //设置电视墙内布局。请求CMS_CONNECT_PARSE_Wall+CMS_CONNECT_PARSE_WallLayoutItem[n]，响应CMS_CONNECT_PARSE_Common_Reply
	//CmdType_GetWallGroup,       //获取电视墙分组。请求CMS_CONNECT_PARSE_Wall，响应CMS_CONNECT_PARSE_DecoderGroup指针链表
	//CmdType_WallGroupOperate,   //电视墙分组操作。请求CMS_CONNECT_PARSE_Wall+CMS_CONNECT_PARSE_DecoderGroupOperate[n]，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_WallLock,                   //获取电视墙操作锁。请求CMS_CONNECT_PARSE_WallLock_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_Decoder_SetSplit,              //设置解码器分屏。请求CMS_CONNECT_PARSE_DecoderSplitCtrl_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_Decoder_OpenRealtime,   //解码器打开预览。请求CMS_CONNECT_PARSE_DecoderOpenRealtime_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_Decoder_CloseRealtime,   //解码器关闭预览。请求CMS_CONNECT_PARSE_DecoderCloseRealtime_Request，响应CMS_CONNECT_PARSE_Common_Reply
	//CmdType_Decoder_PollCtrl,               //解码器轮转控制。请求CMS_CONNECT_PARSE_DecoderPollCtrl_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_Decoder_OpenReplay,     //解码器打开回放。请求CMS_CONNECT_PARSE_DecoderOpenReplay_Request+CMS_CONNECT_PARSE_DecoderReplay_Param[n]，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_Decoder_CloseReplay,    //解码器关闭回放。请求无参数，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_Decoder_GetReplayTime,  //解码器获取回放时间。请求无参数，响应CMS_CONNECT_PARSE_Common_Reply+CMS_CONNECT_PARSE_DecoderReplayTime
	CmdType_Decoder_ReplayCtrl,          //解码器回放控制。请求CMS_CONNECT_PARSE_DecoderCtrlReplay_Request，无响应
	//CmdType_Decoder_SetAbility,     //解码器设置当前能力集。请求CMS_CONNECT_PARSE_DecoderSetAbility_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetWallRuntimeState,    //获取电视墙运行时状态。请求无参数，响应响应CMS_CONNECT_PARSE_Common_Reply+CMS_CONNECT_PARSE_WallRuntimeState+CMS_CONNECT_PARSE_DecoderRuntimeState[n]
	CmdType_Decoder_SetSplice,     //解码器拼接。请求CMS_CONNECT_PARSE_DecoderSetSplice_Request，响应CMS_CONNECT_PARSE_Common_Reply
	//CmdType_Decoder_GetSplice,     //解码器拼接。请求CMS_CONNECT_PARSE_DecoderGetSplice_Request，响应CMS_CONNECT_PARSE_DecoderGetSplice_Reply
	CmdType_GetUserAuth,            //获取用户权限。请求CMS_CONNECT_PARSE_User，响应CMS_CONNECT_PARSE_UserAuth
	CmdType_SetUserAuth,            //设置用户权限。请求CMS_CONNECT_PARSE_SetUserAuthRequest，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetLinkageRule,     //获取联动规则。请求无参数，响应CMS_CONNECT_PARSE_Common_Reply+CMS_CONNECT_PARSE_LinkageRuleParam[n]
	CmdType_GetLinkageAction,   //获取联动动作。请求CMS_CONNECT_PARSE_LinkageRule，响应CMS_CONNECT_PARSE_Common_Reply+CMS_CONNECT_PARSE_LinkageAction[n]
	CmdType_SetLinkageRule,     //设置联动规则。请求CMS_CONNECT_PARSE_SetLinkageRule_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_SetLinkageRuleEnabled,      //设置联动规则是否启用。请求CMS_CONNECT_PARSE_SetLinkageRuleEnabled_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_DelLinkageRule,         //删除联动规则。请求CMS_CONNECT_PARSE_LinkageRule，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_StopLinkageWall,        //停止联动上墙。请求CMS_CONNECT_PARSE_StopLinkageWall_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetLayout,           //获取布局。请求无参数，响应CMS_CONNECT_PARSE_Common_Reply+CMS_CONNECT_PARSE_GroupInfo[n]
	CmdType_AddLayout,           //添加布局。请求CMS_CONNECT_PARSE_Group_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_DelLayout,           //删除布局。请求CMS_CONNECT_PARSE_Group_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_TimeSync,           //校时。请求无参数，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetAutoTimeSyncParam,  //获取自动校时周期，请求无参数，响应CMS_CONNECT_PARSE_Common_Reply + CMS_CONNECT_PARSE_TimeSyncParam
	CmdType_SetAutoTimeSyncParam,  //获取自动校时周期，请求CMS_CONNECT_PARSE_TimeSyncParam，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetStoragerList,       //获取存储服务器列表，请求无参数，响应CMS_CONNECT_PARSE_Common_Reply + CMS_CONNECT_PARSE_StoragerInfo[n]
	CmdType_AddStorager,            //添加存储服务器，请求CMS_CONNECT_PARSE_StoragerId + CMS_CONNECT_PARSE_StoragerParam,响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_DeleteStorager,         //删除存储服务器，请求CMS_CONNECT_PARSE_StoragerId，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_ModifyStorager,     //修改存储服务器，请求CMS_CONNECT_PARSE_StoragerId + CMS_CONNECT_PARSE_StoragerParam,响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetStoragerDisk,    //获存储服务器磁盘信息，请求CMS_CONNECT_PARSE_StoragerId，响应CMS_CONNECT_PARSE_Common_Reply + CMS_CONNECT_PARSE_StoragerDisk[n]
	CmdType_SetRecPartition,    //设置存储服务器分区，请求CMS_CONNECT_PARSE_StoragerId + CMS_CONNECT_PARSE_RecPartitionMask，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetStoragerWorkAttr,    //获取存储服务器工作模式，请求CMS_CONNECT_PARSE_StoragerId，响应CMS_CONNECT_PARSE_Common_Reply + CMS_CONNECT_PARSE_StoragerWorkAttr
	CmdType_SetStoragerWorkAttr,    //设置存储服务器工作模式，请求CMS_CONNECT_PARSE_StoragerId + CMS_CONNECT_PARSE_StoragerWorkAttr，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetStoragerChList,      //获取存储服务器通道列表，请求CMS_CONNECT_PARSE_StoragerId，响应CMS_CONNECT_PARSE_Common_Reply + CMS_CONNECT_PARSE_ChId[n]
	CmdType_StoragerAddCh,       //存储服务器添加通道，请求CMS_CONNECT_PARSE_StoragerId + CMS_CONNECT_PARSE_ChId[n]，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_StoragerDeleteCh,   //存储服务器删除通道，请求CMS_CONNECT_PARSE_StoragerId + CMS_CONNECT_PARSE_ChId[n],响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetStoragerQuota,   //获取存储服务器配额，请求CMS_C0NNECT_PARSE_StoragerId，响应CMS_CONNECT_PARSE_Common_Reply + CMS_CONNECT_PARSE_StoragerQuota
	CmdType_SetStoragerQuota,   //设置存储服务器配额，请求CMS_CONNECT_PARSE_StoragerId + CMS_CONNECT_PARSE_StoragerQuota，响应 CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetChRecPlan,       //获取通道录像计划，请求CMS_CONNECT_PARSE_StoragerId + CMS_CONNECT_PARSE_ChId，响应CMS_CONNECT_PARSE_Common_Reply + CMS_CONNECT_PARSE_ChRecPlan
	CmdType_SetChRecPlan,       //设置通道录像计划，请求CMS_CONNECT_PARSE_StoragerId + CMS_CONNECT_PARSE_ChId[n] + CMS_CONNECT_PARSE_ChRecPlan，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetDeviceAlarmIO,   //获取设备报警IO状态。请求CMS_CONNECT_PARSE_GetDeviceAlarmIO_Request，响应CMS_CONNECT_PARSE_GsetDeviceAlarmIO_Reply
	CmdType_SetDeviceAlarmIO,   //设置设备的报警IO。请求CMS_CONNECT_PARSE_SetDeviceAlarmIO_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetMaxExtendedChCount,	//获取最大扩展路数。请求无参数，响应CMS_CONNECT_PARSE_GetMaxExtendedChCount_Reply
	CmdType_Set3D,				//3D定位。请求CMS_CONNECT_PARSE_Set3D_Request,无响应
	CmdType_UTC,					//UTC功能。请求CMS_CONNECT_PARSE_UTC_Request,无响应
	CmdType_ModifyChName,			//修改通道名称。请求CMS_CONNECT_PARSE_ModifyChName_Request,响应CMS_CONNECT_PARSE_Common_Reply
	//CmdType_Decoder_GetSplit,		//获取解码器分屏。请求CMS_CONNECT_PARSE_GetDecoderSplit_Request,响应CMS_CONNECT_PARSE_Common_Reply + CMS_CONNECT_PARSE_DecoderSplitState
	CmdType_TranData,				//向设备透传信息。请求CMS_CONNECT_PARSE_TranData_Request，响应CMS_CONNECT_PARSE_TranData_Reply
	CmdType_GetDecoderGroup,		//获取解码器分组.请求无参数,响应CMS_CONNECT_PARSE_Common_Reply + CMS_CONNECT_PARSE_Decoder_Group[n]
	CmdType_AddDecoderGroup,		//添加解码器分组.请求CMS_CONNECT_PARSE_Decoder_Group,响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_DelDecoderGroup,		//删除解码器分组.请求CMS_CONNECT_PARSE_Decoder_DelGroup_Request,响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_AddDecoderGroupCh,		//添加解码器分组通道.请求CMS_CONNECT_PARSE_Decoder_Group,响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_DelDecoderGroupCh,		//删除解码器分组通道.请求CMS_CONNECT_PARSE_Decoder_Group,响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_GetAccessControl,		//获取门禁配置。请求CMS_CONNECT_PASER_AccessControl，响应CMS_CONNECT_PASER_GetAccessControl
	CmdType_AddAccessControl,		//添加门禁
	CmdType_DelAccessControl,		//删除门禁
	CmdType_SendAccessControl,		//控制门禁器开关
	CmdType_StartSearchAccess,		//开始搜索门禁
	CmdType_StopSearchAccess,		//结束搜索门禁
	CmdType_SearchAccessLog,			//获取报警日志。请求CMS_CONNECT_PARSE_SearchLog_Request,响应CMS_CONNECT_PARSE_SearchLog_Reply+CMS_CONNECT_PARSE_AccessLog[n]
	CmdType_GetAccessLinkageRule,		    //获取联动规则。请求无参数，响应CMS_CONNECT_PARSE_Common_Reply+CMS_CONNECT_PARSE_AccessLinkageRuleParam[n]
	CmdType_GetAccessLinkageAction,   //获取联动动作。请求CMS_CONNECT_PARSE_LinkageRule，响应CMS_CONNECT_PARSE_Common_Reply+CMS_CONNECT_PARSE_LinkageAction[n]
	CmdType_SetAccessLinkageRule,     //设置联动规则。请求CMS_CONNECT_PARSE_SetAccessLinkageRule_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_SetAccessLinkageRuleEnabled,      //设置联动规则是否启用。请求CMS_CONNECT_PARSE_SetLinkageRuleEnabled_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_DelAccessLinkageRule,			//删除联动规则。请求CMS_CONNECT_PARSE_LinkageRule，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_StopAccessLinkageWall,        //停止联动上墙。请求CMS_CONNECT_PARSE_StopLinkageWall_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_Decoder_SetActive,			//设置解码器主动解码.请求CMS_CONNECT_PARSE_Decoder_SetActive_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_Decoder_SetScheme,			//设置解码器预案,请求CMS_CONNECT_PARSE_Decoder_SetScheme_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_Decoder_DeleteScheme,		//删除解码器预案,请求CMS_CONNECT_PARSE_Decoder_DeleteScheme_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_Decoder_SetSchemeStayTime,	//设置预案停留时间,请求CMS_CONNECT_PARSE_Decoder_SetSchemeStayTime_Request，响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_Decoder_GetScheme,			//获取解码器预案,请求无参数,响应CMS_CONNECT_PARSE_Decoder_GetScheme_Reply
	CmdType_Decoder_CtrlSchemePoll,	//控制预案轮询,请求CMS_CONNECT_PARSE_Decoder_CtrlSchemePoll_Request,响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_SaveString,					//保存配置字符串,请求char[n],响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_LoadString,					//获取配置字符串,请求无参数,响应char[n]
	CmdType_Decoder_SetSound,			//解码器设置播放声音的窗口,请求CMS_CONNECT_PARSE_Decoder_SetSound_Request,响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_Decoder_GetSplit,			//解码器获取分屏。请求CMS_CONNECT_PARSE_GetDecoderSplit_Request,响应CMS_CONNECT_PARSE_Common_Reply + CMS_CONNECT_PARSE_DecoderSplitState
	CmdType_Decoder_GetAbility,			//获取解码器当前解码能力。请求CMS_CONNECT_PARSE_GetDecoderAbility_Request,响应CMS_CONNECT_PARSE_Common_Reply + CMS_CONNECT_PARSE_DecoderAbility
	CmdType_FishEye_GetAbility,			//获取鱼眼相机能力集。请求CMS_CONNECT_PARSE_GetFishEyeAbility_Request,响应CMS_CONNECT_PARSE_Common_Reply + CMS_CONNECT_PARSE_FishEyeAbility
	CmdType_FishEye_GetMode,			//获取鱼眼相机工作模式。请求CMS_CONNECT_PARSE_GetFishEyeMode_Request,响应CMS_CONNECT_PARSE_Common_Reply + CMS_CONNECT_PARSE_FishEyeMode
	CmdType_FishEye_SetMode,			//设置鱼眼相机工作模式。请求CMS_CONNECT_PARSE_SetFishEyeMode_Request,响应CMS_CONNECT_PARSE_Common_Reply
	CmdType_UserRole,
}CMS_CONNECT_PARSE_CmdType;




//通知消息类型
typedef enum {
	NoticeType_AlarmMessage = 100,		//告警消息。对应CMS_CONNECT_PARSE_Alarm_Notice
	NoticeType_OnlineState,				//上下线消息。对应CMS_CONNECT_PARSE_Online_Notice
	NoticeType_RecordState,				//录像状态。对应CMS_CONNECT_PARSE_Record_Notice
	NoticeType_AddArea,					//增加区域。对应CMS_CONNECT_PARSE_AddArea_Request
	NoticeType_DelArea,					//删除区域。对应CMS_CONNECT_PARSE_DelArea_Request
	NoticeType_ModifyArea,				//修改区域。对应CMS_CONNECT_PARSE_ModifyArea_Request
	NoticeType_AddDevice,				//添加设备。对应CMS_CONNECT_PARSE_AddDevice_Notice
	NoticeType_DelDevice,				//删除设备。对应CMS_CONNECT_PARSE_DelDevice_Request
	NoticeType_ModifyDevice,			//修改设备。对应CMS_CONNECT_PARSE_ModifyDevice_Request
	NoticeType_SearchDevice,        //搜索设备。对应CMS_CONNECT_PARSE_SearchDeviceInfo
	NoticeType_AddCms,					//添加CMS。对应CMS_CONNECT_PARSE_CMSNode指针
	NoticeType_DelCms,					//修改CMS。对应
	NoticeType_ModifyCms,				//修改CMS。对应
	NoticeType_AddMap,					//增加地图。对应CMS_CONNECT_PARSE_AddMap_Notice
	NoticeType_DelMap,					//删除地图。对应CMS_CONNECT_PARSE_Map
	NoticeType_AddGroup,				//添加分组。对应CMS_CONNECT_PARSE_Group_Request
	NoticeType_DelGroup,				//删除分组。对应CMS_CONNECT_PARSE_Group_Request
	NoticeType_GroupAddChannel,			//分组添加通道。对应CMS_CONNECT_PARSE_ChannelInGroup
	NoticeType_GroupDelChannel,			//分组删除通道。对应CMS_CONNECT_PARSE_ChannelInGroup
	NoticeType_AddDecoder,				//添加解码器。对应CMS_CONNECT_PARSE_DecoderNode
	NoticeType_DelDecoder,				//删除解码器。对应CMS_CONNECT_PARSE_DelDecoder_Request
	NoticeType_ModifyDecoder,			//修改解码器。对应CMS_CONNECT_PARSE_ModifyDecoder_Notice
	NoticeType_SearchDecoder,        //搜索解码器。对应CMS_CONNECT_PARSE_SearchDeviceInfo
	NoticeType_WallChangeGroup,     //电视墙切换轮询分组。对应CMS_CONNECT_PARSE_WallChangeGroup_Notice
	NoticeType_DecoderAlarmState,   //解码器报警状态。对应CMS_CONNECT_PARSE_DedoderAlarmState
	NoticeType_AddStorager,			//添加存储服务器，对应CMS_CONNECT_PARSE_StoragerInfo
	NoticeType_DelStorager,			//删除存储服务器，对应CMS_CONNECT_PARSE_StoragerId
	NoticeType_ModifyStorager,		//修改存储服务器，对应CMS_CONNECT_PARSE_StoragerInfo
	NoticeType_StoragerAddChannel,	//存储服务器添加通道,对应CMS_CONNECT_PARSE_StoragerChNotice
	NoticeType_StoragerDelChannel,	//存储服务器删除通道,对应CMS_CONNECT_PARSE_StoragerChNotice
	NoticeType_ModifyChName,			//修改通道名,对应CMS_CONNECT_PARSE_ModifyChName_Notice
	NoticeType_Decoder_OpenRealtime,   //解码器打开预览。对应CMS_CONNECT_PARSE_DecoderOpenRealtime_Notice
	NoticeType_Decoder_CloseRealtime,   //解码器关闭预览。对应CMS_CONNECT_PARSE_DecoderCloseRealtime_Notice
	NoticeType_Decoder_PollCtrl,               //解码器轮转控制。对应CMS_CONNECT_PARSE_DecoderPollCtrl_Notice
	NoticeType_Decoder_OpenReplay,     //解码器打开回放。对应CMS_CONNECT_PARSE_DecoderOpenReplay_Notice
	NoticeType_Decoder_CloseReplay,    //解码器关闭回放。对应CMS_CONNECT_PARSE_DecoderCloseReplay_Notice
	NoticeType_Decoder_AddGroup,	//解码器新增分组.对应CMS_CONNECT_PARSE_Decoder_Group
	NoticeType_Decoder_DelGroup,	//解码器删除分组.对应CMS_CONNECT_PARSE_Decoder_DelGroup_Request
	NoticeType_Decoder_AddGroupCh,	//解码器新增分组.对应CMS_CONNECT_PARSE_Decoder_Group
	NoticeType_Decoder_DelGroupCh,	//解码器新增分组.对应CMS_CONNECT_PARSE_Decoder_Group
	NoticeType_AccessMessage,		//门禁告警消息，对应CMS_CONNECT_PARSE_Access_Alarm_Notice
	NoticeType_AddAccess,			//添加门禁器，对应CMS_CONNECT_PASER_AccessControlInfo
	NoticeType_DelAccess,			//删除门禁器，对应CMS_CONNECT_PASER_AccessControlInfo
	NoticeType_ModifyAccess,		//修改门禁器，对应CMS_CONNECT_PASER_AccessControlInfo
	NoticeType_SearchAccess,		//搜索门禁设备，对应CMS_CONNECT_PARSE_SearchAccessInfo
	NoticeType_Decoder_ChangeScheme,	//解码器预案轮询切换,对应CMS_CONNECT_PARSE_Decoder_ChangeScheme_Notice
}CMS_CONNECT_PARSE_NoticeType;




//客户端类型
typedef enum
{
	ClientType_Mobile = 1,		//手机
	ClientType_Browser,			//浏览器
	ClientType_Client,			//PC客户端
	ClientType_Server			//PC服务器
}CMS_CONNECT_PARSE_ClientType;




//用户类型
typedef enum
{
	UserType_Admin = 1,			//管理员
	UserType_Guest,				//普通用户
}CMS_CONNECT_PARSE_UserType;



//设备树节点类型
typedef enum
{
	NodeType_Root = 1,
	NodeType_EncoderForder,
	NodeType_CMSForder,
	NodeType_CMS,
	NodeType_Area,
	NodeType_Device,
	NodeType_Channel,
	NodeType_AlarmIn,
	NodeType_AlarmOut,
}CMS_CONNECT_PARSE_NodeType;



//设备类型
typedef enum
{
	DeviceType_DVR = 1,
	DeviceType_NVR,
	DeviceType_IPC,
	DeviceType_NVR_2,//NVR 2.0设备
	DeviceType_Control,//门禁器
	DeviceType_IPC_2,
	DeviceType_IPC_FISH,	//鱼眼相机
}CMS_CONNECT_PARSE_DeviceType;





//设备协议类型
typedef enum
{
	ProtocolType_Register = 1,	//主动注册
	ProtocolType_I8H = 2,			//HTTP，rtp over TCP
	ProtocolType_I8H_UDP = 3,		//HTTP，rtp over UDP,仅添加设备时有效
	ProtocolType_ONVIF = 4,			//Onvif
	ProtocolType_GB28181 = 8,		//GB/T28181
	ProtocolType_I8 = 16,			//I8
	ProtocolType_TUTK = 32,			//TUTK
	ProtocolType_Honey = 64,		//Honey
	ProtocolType_GoAhead = 128,		//Honey红标版本专用，I8H_GoAhead设备，所有处理方式按I8H处理
	ProtocolType_GoAhead_UDP = 129,  //Honey红标版本UDP
	ProtocolType_Taos = 256,			//韬视协议
	ProtocolType_I9 = 512,			//I9协议
	ProtocolType_AJ = 1024,			//Anjie
	ProtocolType_UMEYE = 2048,       //华师大P2P协议
	ProtocolType_Honeywell = 4096,  //
	ProtocolType_P2P = 8192
}CMS_CONNECT_PARSE_ProtocolType;

typedef enum
{
	AccessControlTpye_ZKT = 1	//ZKT门禁器
}CMS_CONNECT_PARSE_AccessControlType;


//码流类型
typedef enum
{
	StreamType_Intercom = 0,	//对讲流
	StreamType_Main = 1,		//主码流
	StreamType_Sub,				//子码流
}CMS_CONNECT_PARSE_StreamType;




//云台命令字
typedef enum
{
	PtzCtrlType_LightPowerOn = 1,	//灯光电源
	PtzCtrlType_WiperPowerOn,		//雨刷电源
	PtzCtrlType_FanPowerOn,			//风扇电源
	PtzCtrlType_ZoomIn,				//焦距大
	PtzCtrlType_ZoomOut,			//焦距小
	PtzCtrlType_FocusNear,			//焦点近
	PtzCtrlType_FocusFar,			//焦点远
	PtzCtrlType_IrisOpen,			//光圈开
	PtzCtrlType_IrisClose,			//光圈闭
	PtzCtrlType_TiltUp,				//上
	PtzCtrlType_TiltDown,			//下
	PtzCtrlType_PanLeft,			//左
	PtzCtrlType_PanRight,			//右
	PtzCtrlType_UpLeft,				//左上
	PtzCtrlType_UpRight,			//右上
	PtzCtrlType_DownLeft,			//左下
	PtzCtrlType_DownRight,			//右下
	PtzCtrlType_Auto				//自动
}CMS_CONNECT_PARSE_PtzCmdType;


//UTC命令字
typedef enum
{
	UtcCmdType_Auto = 0,
	UtcCmdType_Up = 1,
	UtcCmdType_Down = 2,
	UtcCmdType_Left = 3,
	UtcCmdType_Right = 4,
	UtcCmdType_FocusNear = 5,
	UtcCmdType_FocusFar = 6,
	UtcCmdType_ZoomIn = 7,
	UtcCmdType_ZoomOut = 8,
	UtcCmdType_Stop = 9
}CMS_CONNECT_PARSE_UtcCmdType;


//预置点命令字
typedef enum
{
	PresetCtrlType_Set = 1,		//设置预置点
	PresetCtrlType_Clear,		//清除预置点
	PresetCtrlType_Goto			//转到预置点
}CMS_CONNECT_PARSE_PresetCmdType;




//回放命令字
typedef enum
{
	ReplayCtrlType_IFrameOnly = 1,      //是否只弹I帧 参数 1-只弹I帧 0-弹所有帧
	ReplayCtrlType_SeekTime			//时间定位 参数 time_t(UTC)
}CMS_CONNECT_PARSE_ReplayCmdType;




//告警类型
typedef enum
{
	AlarmType_Motion = 1,           //移动侦测
	AlarmType_VideoLoss = 2,		//视频丢失
	AlarmType_Shelter = 4,			//视频遮挡
	AlarmType_AlarmIn = 8,			//告警输入
	AlarmType_Count = 16,           //计数检测
	AlarmType_Area = 32,            //区域检测
	AlarmType_Object = 64,          //物品检测
	AlarmType_Wire = 128,           //跨线检测
	AlarmType_Person = 256          //人形检测
}CMS_CONNECT_PARSE_AlarmType;

typedef enum
{
	AccessAlarmType_OpenDoor = 1,				//意外开门
	AccessAlarmType_Tamper = 2,					//防拆报警
	AccessAlarmType_StressPwd = 4,				//胁迫密码
	AccessAlarmType_StressFingerprint = 8,		//胁迫指纹
	AccessAlarmType_MagneticTimeOut = 16		//门磁超时
}CMS_CONNECT_PARSE_AccessAlarmType;


//录像位置类型
typedef enum
{
	RecLocation_Device = 1,		//设备端录像
	RecLocation_Storager			//存储服务器录像
}CMS_CONNECT_PARSE_RecLocationType;




//录像类型
typedef enum
{
	RecordType_None = 0,
	RecordType_Regular = 1 << 0, // 常规录像(1)
	RecordType_Motion = 1 << 1, // 移动侦测(2)
	RecordType_Alarm = 1 << 2, // 告警录像(3)
	RecordType_Schedule = 1 << 3, // 计划录像(8)
	RecordType_Manual = 1 << 4, // 手动录像(16)

	/* 智能侦测 */
	RecordType_Counter = 1 << 5, // 计数报警(32)
	RecordType_Wire = 1 << 6, // 跨线报警(64)
	RecordType_Region = 1 << 7, // 区域报警(128)
	RecordType_Object = 1 << 8, // 物品丢失报警(256)

	RecordType_Pre = RecordType_None, // 预录

	/* 注意:增加一种新智能类型就修改一下AllSmartType的定义 */
	RecordType_AllSmartType = RecordType_Counter\
	| RecordType_Wire\
	| RecordType_Region\
	| RecordType_Object,

	RecordType_AllType = RecordType_Regular\
	| RecordType_Motion\
	| RecordType_Alarm\
	| RecordType_Schedule\
	| RecordType_Manual\
	| RecordType_AllSmartType,

	RecordType_Undefined = 1 << 9  // 未定义
}CMS_CONNECT_PARSE_RecordType;

//录像类型满足条件
typedef enum
{
	RecordType_Condition_Or = 0,  /* 任意满足一种条件 */
	RecordType_Condition_And      /* 同时满足全部条件 */
}CMS_CONNECT_PARSE_RecordType_Condition;

//日志类型
typedef enum
{
	LogType_UserLogin = 0x01,		//用户登录	iParam[0]为0表示用户注销，1表示用户登录
	LogType_DeviceMgr = 0x02,		//设备管理  cParam为设备名称；iParam[0]为0表示删除设备，1表示添加设备，2表示修改设备
	//LogType_RecordMgr = 0x04,		//录像管理	cParam为设备名称；iParam[0]表示通道号；iParam[1]为0表示停止录像，1表示开始录像
	LogType_LinkageRule = 0x08,		//联动规则	cParam为规则名称；iParam[0]为0表示删除规则，1表示添加规则，2表示修改规则
}CMS_CONNECT_PARSE_LogType;



//解码器分组操作类型
typedef enum
{
	OperateType_AddGroup = 1,    //添加分组
	OperateType_ModifyGroup = 2,    //修改分组
	OperateType_DelGroup = 3,    //删除分组
	OperateType_AddLayout = 4,    //添加布局
	OperateType_ModifyLayout = 5,    //修改布局
	OperateType_DelLayout = 6,    //删除布局
	OperateType_SetSplit = 7,    //设置分屏
}CMS_CONNECT_PARSE_DecoderGroupOperateType;


//解码器分屏类型
typedef enum
{
	SplitType_1 = 0,
	SplitType_4,
	SplitType_1p5,
	SplitType_6,
	SplitType_1p7,
	SplitType_9,
	SplitType_16,
	SplitType_25,
	SplitType_36,
	SplitType_49,
	SplitType_64,
}CMS_CONNECT_PARSE_DecoderSplitType;



//轮询控制操作类型
typedef enum
{
	CtrlType_Start = 1,             //开始轮询
	CtrlType_Stop,                   //停止轮询
	CtrlType_Pause,                //暂停轮询
	CtrlType_PrevGroup,        //转到上一组
	CtrlType_NextGroup,        //转到下一组
}CMS_CONNECT_PARSE_PollCtrlType;


//电视墙轮转状态
typedef enum
{
	PollState_NotPoll = 0,         //未轮转
	PollState_Polling,                //正在轮转
	PollState_PollPaused,        //轮转暂停
}CMS_CONNECT_PARSE_WallPollState;


//电视墙回放状态
typedef enum
{
	ReplayState_NotReplay = 0,         //未回放
	ReplayState_Replaying,                //正在回放
	ReplayState_ReplayPaused,        //回放暂停
	ReplayState_FramePlay,              //帧播
}CMS_CONNECT_PARSE_WallReplayState;


//解码器工作状态
typedef enum
{
	WorkState_Preview = 0,
	WorkState_Playback,
	WorkState_Alarm,
}CMS_CONNECT_PARSE_DecoderWorkState;



//解码器回放命令字
typedef enum
{
	DecoderReplayCtrlType_Pause = 1,			//回放暂停  参数 1-暂停 0-恢复
	DecoderReplayCtrlType_FramePlay,       //帧播 参数1-帧播 0-恢复
	DecoderReplayCtrlType_SeekTime,			//时间定位 参数 time_t(UTC)
	DecoderReplayCtrlType_SetSpeed,         //设置回放速度 参数-4~4
}CMS_CONNECT_PARSE_DecoderReplayCmdType;



//联动动作类型
typedef enum
{
	LinkageActionType_Map = 1,       //地图
	LinkageActionType_PTZ,               //云台
	LinkageActionType_PopImage,      //弹图像
	LinkageActionType_Record,        //录像
	LinkageActionType_Capture,       //抓图
	LinkageActionType_Wall,              //上墙
}CMS_CONNECT_PARSE_LinkageActionType;


//联动云台类型
typedef enum
{
	LinkagePtzType_GotoPreset = 1,      //转到预置点
	LinkagePtzType_RunCruise,               //启用巡航
}CMS_CONNECT_PARSE_LinkagePtzType;


//录像计划布防类型
typedef enum
{
	RecArmingType_None = 0,

	RecArmingType_Timer,		//定时触发

	/* 根据新的录像策略，以下类型都被取消了，为了减少代码修改量，只留着保证编译能过，底下只支持ANTS_REC_ARMING_BY_TIMER */
	//ANTS_REC_ARMING_BY_MD,			//移动触发
	//ANTS_REC_ARMING_BY_AI,			//报警触发
	//ANTS_REC_ARMING_BY_MD_OR_AI,
	//ANTS_REC_ARMING_BY_MD_AND_AI,
}CMS_CONNECT_PARSE_RecArmingType;



//zhangw:录像设置模式
//定时录像+报警录像：时间计划和预录、延迟都生效；
//定时录像：时间计划生效，预录、延迟都禁用；
//报警录像：预录、延迟都生效，时间计划禁用；
//停止录像：时间计划和预录、延迟都禁用；
typedef enum
{
	ChRecMode_Stop = 0,
	ChRecMode_Timing = 0x01,
	ChRecMode_Alarming = 0x02,

	ChRecMode_TimingAndAlarming = (ChRecMode_Timing | ChRecMode_Alarming),
}CMS_CONNECT_PARSE_ChRecMode;


typedef enum
{
	IO_AlarmIn = 0,
	IO_AlarmOunt,
}CMS_CONNECT_PARSE_IOType;


//包内容类型
typedef union
{
	CMS_CONNECT_PARSE_CmdType eCmdType;				//命令类型
	CMS_CONNECT_PARSE_NoticeType eNoticeType;		//通知类型
}CMS_CONNECT_PARSE_ContentType;



//包头结构体
typedef struct
{
	CMS_CONNECT_PARSE_PackType ePackType;			//包类型
	CMS_CONNECT_PARSE_ContentType eContentType;		//ePackType为PackType_Notice时，eContentType.eNoticeType有效；否则eContentType.eCmdType有效
}CMS_CONNECT_PARSE_Header;




//告警通知
typedef struct
{
	CMS_CONNECT_PARSE_AlarmType eAlarmType;		//告警类型
	char cSerialNum[MAX_NAME_LENGTH];						//告警源设备序列号
	int iParam;									//告警参数，告警类型为告警输入时表示告警输入号，否则为通道号
	int isStoped;								//0为告警开始，1为告警结束
	unsigned int timeUTC;						//时间UTC
}CMS_CONNECT_PARSE_Alarm_Notice;

typedef struct
{
	CMS_CONNECT_PARSE_AccessAlarmType eAlarmType;		//告警类型
	char cSerialNum[MAX_NAME_LENGTH];						//告警源设备序列号
	int iParam;									//告警参数，告警类型为告警输入时表示告警输入号，否则为通道号
	int isStoped;								//0为告警开始，1为告警结束
	unsigned int timeUTC;						//时间UTC
}CMS_CONNECT_PARSE_Access_Alarm_Notice;


//上下线通知
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//序列号，全0表示服务器，其它表示设备序列号
	int isOnline;				//0为下线，1为上线
}CMS_CONNECT_PARSE_Online_Notice;



//录像状态改变通知
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//序列号，全0表示服务器，其它表示设备序列号
	int iChannel;				//通道号，从1开始
	int isCmsRecord;			//是否中心端录像
	int isDeviceRecord;			//是否设备端录像
}CMS_CONNECT_PARSE_Record_Notice;





//添加地图通知
typedef struct
{
	char cParentName[MAX_NAME_LENGTH];
	char cMapName[MAX_NAME_LENGTH];
}CMS_CONNECT_PARSE_AddMap_Notice;




//视频信息
typedef struct
{
	unsigned short uWidth;		//视频宽度
	unsigned short uHeight;		//视频高度
	char cCodecId;				//视频编码格式， 1-I8私有格式 2-H.264格式 3-H.265格式 4-AVI格式 (16-h265码流 2-MJPEG码流)
	char cRes[3];				//保留
}CMS_CONNECT_PARSE_VideoMedia;





//音频信息
typedef struct
{
	char cCodecId;			//音频编码格式，1-G711-U 2-G711-A 3-G726
	char cSampleRate;		//采样率, 1-8000HZ 2-32000HZ 3-48000HZ 4-960000HZ
	char cBitRate;			//比特率,1-8bit 2-16bit
	char cChannels;			//通道数,1-单通道 2-双通道
	char cResolution;		//分辨力
	char cRes[3];			//保留
}CMS_CONNECT_PARSE_AudioMedia;


typedef struct
{
	unsigned int iCount;
	char res[4];
}CMS_CONNECT_PARSE_SmartMedia;


//流数据头
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//设备序列号
	int iChannel;				//通道号，从1开始；对讲音频中0表示与设备对讲
	CMS_CONNECT_PARSE_StreamType eStreamType;			//码流类型
	int iFrameType;				//帧类型，	0-音频帧；1-I帧；2-P帧；3-智能规则帧；4-智能结果帧
	unsigned int timeUTC;		//帧时间UTC
	int iMicroSec;				//帧时间的微秒数
	union
	{
		CMS_CONNECT_PARSE_VideoMedia struVideoMedia;	//音频帧信息
		CMS_CONNECT_PARSE_AudioMedia struAudioMedia;	//视频帧信息
		CMS_CONNECT_PARSE_SmartMedia struSmartMedia;    //只能帧信息
	}unionMedia;
}CMS_CONNECT_PARSE_StreamHeader;




//通用响应
typedef struct
{
	int iResult;
}CMS_CONNECT_PARSE_Common_Reply;




//用户
typedef struct
{
	char cUserName[MAX_NAME_LENGTH];		//用户名
}CMS_CONNECT_PARSE_User;



//用户参数
typedef struct
{
	char cUserName[MAX_NAME_LENGTH];		//用户名
	char cPassword[MAX_NAME_LENGTH];		//密码
}CMS_CONNECT_PARSE_UserParam;



//添加用户请求
typedef struct
{
	CMS_CONNECT_PARSE_UserType eUserType;	//用户类型
	CMS_CONNECT_PARSE_UserParam sUserParam;
}CMS_CONNECT_PARSE_AddUser_Request;




//用户登录请求
typedef struct
{
	CMS_CONNECT_PARSE_ClientType eClientType;	//客户端类型
	CMS_CONNECT_PARSE_UserParam sUserParam;
}CMS_CONNECT_PARSE_Login_Request;




//用户登陆响应
typedef struct
{
	int iResult;		//返回值
	CMS_CONNECT_PARSE_UserType eUserType;	//用户类型
	int iToken;     //信令
}CMS_CONNECT_PARSE_Login_Reply;




//日志检索响应
typedef struct
{
	int iResult;		//返回值
	int iTotalCount;    //日志总条数
}CMS_CONNECT_PARSE_SearchLog_Reply;



//设备树节点
class CMS_CONNECT_PARSE_Node
{
public:
	CMS_CONNECT_PARSE_Node()
	{
		memset(cNodeName, 0, MAX_NAME_LENGTH);
		parent = NULL;
		children.clear();
	}
	virtual ~CMS_CONNECT_PARSE_Node()
	{
		if (NULL != parent)
		{
			parent->children.remove(this);
		}
		while (0 < children.size())
		{
			CMS_CONNECT_PARSE_Node *pNode = children.back();
			//children.pop_back();
			delete pNode;
		}
	}
	void AddChild(CMS_CONNECT_PARSE_Node *pChild)
	{
		children.push_back(pChild);
		pChild->parent = this;
	}
	void RemoveChild(CMS_CONNECT_PARSE_Node *pChild)
	{
		children.remove(pChild);
		pChild->parent = NULL;
	}

	CMS_CONNECT_PARSE_NodeType eNodeType;
	char cNodeName[MAX_NAME_LENGTH];
	CMS_CONNECT_PARSE_Node *parent;
	std::list<CMS_CONNECT_PARSE_Node *> children;
};



class CMS_CONNECT_PARSE_DeviceNode : public CMS_CONNECT_PARSE_Node
{
public:
	CMS_CONNECT_PARSE_DeviceNode()
	{
		eNodeType = NodeType_Device;
		memset(cSerialNum, 0, MAX_NAME_LENGTH);
		memset(cUserName, 0, MAX_NAME_LENGTH);
		memset(cPassword, 0, MAX_NAME_LENGTH);
		memset(cDeviceIP, 0, MAX_NAME_LENGTH);
	}
	~CMS_CONNECT_PARSE_DeviceNode()
	{

	}
	char cSerialNum[MAX_NAME_LENGTH];	//序列号
	char cUserName[MAX_NAME_LENGTH];		//用户名
	char cPassword[MAX_NAME_LENGTH];		//密码
	char cDeviceIP[MAX_NAME_LENGTH];		//IP
	int iDevicePort;		//端口
	CMS_CONNECT_PARSE_DeviceType eDeviceType;	//设备类型
	CMS_CONNECT_PARSE_ProtocolType eProtocolType;	//协议类型
	int iChannelCount;		//通道个数
	int iAlarmInCount;		//告警输入个数
	int iAlarmOutCount;     //告警输出个数
	int isOnline;			//是否在线
};



class CMS_CONNECT_PARSE_CMSNode : public CMS_CONNECT_PARSE_Node
{
public:
	CMS_CONNECT_PARSE_CMSNode()
	{
		eNodeType = NodeType_CMS;
		memset(cSerialNum, 0, MAX_NAME_LENGTH);
		memset(cUserName, 0, MAX_NAME_LENGTH);
		memset(cPassword, 0, MAX_NAME_LENGTH);
		memset(cCMSIP, 0, MAX_NAME_LENGTH);
	}
	~CMS_CONNECT_PARSE_CMSNode()
	{

	}
	char cSerialNum[MAX_NAME_LENGTH];	//序列号
	char cUserName[MAX_NAME_LENGTH];		//用户名
	char cPassword[MAX_NAME_LENGTH];		//密码
	char cCMSIP[MAX_NAME_LENGTH];		//IP
	int iCMSPort;			//端口
	int isOnline;			//是否在线
};



class CMS_CONNECT_PARSE_ChannelNode : public CMS_CONNECT_PARSE_Node
{
public:
	CMS_CONNECT_PARSE_ChannelNode()
	{
		eNodeType = NodeType_Channel;
		memset(cSerialNum, 0, MAX_NAME_LENGTH);
	}
	~CMS_CONNECT_PARSE_ChannelNode()
	{

	}
	char cSerialNum[MAX_NAME_LENGTH];	//序列号
	int iChannelNo;			//通道号
	int isOnline;			//是否在线
	int isCMSRecord;		//是否正在中心录像
	int isDeviceRecord;		//是否正在设备录像
	int isRecordRight;		//是否有中心录像权限
	int isPlaybackRight;	//是否有回放权限
	int isIntercomRight;	//是否有对讲权限
	int iPtzLevel;			//云台权限等级
};



class CMS_CONNECT_PARSE_AlarmInNode : public CMS_CONNECT_PARSE_Node
{
public:
	CMS_CONNECT_PARSE_AlarmInNode()
	{
		eNodeType = NodeType_AlarmIn;
		memset(cSerialNum, 0, MAX_NAME_LENGTH);
	}
	~CMS_CONNECT_PARSE_AlarmInNode()
	{

	}
	char cSerialNum[MAX_NAME_LENGTH];	//序列号
	int iAlarmInNo;			//告警输入号
};



class CMS_CONNECT_PARSE_AlarmOutNode : public CMS_CONNECT_PARSE_Node
{
public:
	CMS_CONNECT_PARSE_AlarmOutNode()
	{
		eNodeType = NodeType_AlarmOut;
		memset(cSerialNum, 0, MAX_NAME_LENGTH);
	}
	~CMS_CONNECT_PARSE_AlarmOutNode()
	{

	}
	char cSerialNum[MAX_NAME_LENGTH];	//序列号
	int iAlarmOutNo;			//告警输出号
};


//添加设备通知
struct  CMS_CONNECT_PARSE_AddDevice_Notice
{
	char cAreaName[MAX_NAME_LENGTH];		//设备所在区域名称
	CMS_CONNECT_PARSE_DeviceNode *pDevice;	//设备节点指针
	~CMS_CONNECT_PARSE_AddDevice_Notice()
	{
		// 		delete pDevice;
	}
};





//设备搜索请求
typedef struct
{
	int iProtocolTypeFlags;	//协议类型，按位取|
	int isStop;       //是否停止搜索 0-开始搜索 1-停止搜索
}CMS_CONNECT_PARSE_SearchDevice_Request;




//设备搜索结果
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];	//序列号
	CMS_CONNECT_PARSE_DeviceType eDeviceType;	//设备类型
	CMS_CONNECT_PARSE_ProtocolType eProtocolType;	//协议类型
	char cDeviceIP[MAX_NAME_LENGTH];		//设备IP
	int iDevicePort;		//设备端口
	char cUsername[MAX_NAME_LENGTH];	//用户名
	char cPassword[MAX_NAME_LENGTH];	//密码
	char cVersion[MAX_NAME_LENGTH];		//主控版本号
}CMS_CONNECT_PARSE_SearchDeviceInfo;

//设备搜索结果
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];	//序列号
	CMS_CONNECT_PARSE_DeviceType eDeviceType;	//设备类型
	CMS_CONNECT_PARSE_AccessControlType eProtocolType;	//协议类型
	char cDeviceIP[MAX_NAME_LENGTH];		//设备IP
	int iDevicePort;		//设备端口
	int iDoorCount;			//控制门的数量
	char cUsername[MAX_NAME_LENGTH];	//用户名
	char cPassword[MAX_NAME_LENGTH];	//密码
}CMS_CONNECT_PARSE_SearchAccessInfo;



//添加区域请求
typedef struct
{
	char cParentName[MAX_NAME_LENGTH];		//所在父区域名称
	char cAreaName[MAX_NAME_LENGTH];		//区域名称
}CMS_CONNECT_PARSE_AddArea_Request;




//删除区域请求
typedef struct
{
	char cAreaName[MAX_NAME_LENGTH];	//区域名称
}CMS_CONNECT_PARSE_DelArea_Request;




//修改区域请求
typedef struct
{
	char cOldName[MAX_NAME_LENGTH];		//区域名称
	char cNewName[MAX_NAME_LENGTH];		//区域新名称
}CMS_CONNECT_PARSE_ModifyArea_Request;




//添加设备请求
typedef struct
{
	char cAreaName[MAX_NAME_LENGTH];		//所在区域名称
	CMS_CONNECT_PARSE_ProtocolType eProtocolType;	//协议类型
	char cDevice[MAX_NAME_LENGTH];		//主动注册协议为设备序列号，其它为设备IP
	int iDevicePort;		//设备端口，主动注册协议可不填
	char cDeviceName[MAX_NAME_LENGTH];	//设备名
	char cUserName[MAX_NAME_LENGTH];		//设备用户名
	char cPassword[MAX_NAME_LENGTH];		//设备密码
}CMS_CONNECT_PARSE_AddDevice_Request;




//删除设备请求
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];	//设备序列号
}CMS_CONNECT_PARSE_DelDevice_Request;





//修改设备请求
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];	//设备序列号
	char cDeviceName[MAX_NAME_LENGTH];	//设备名
	char cUserName[MAX_NAME_LENGTH];		//设备用户名
	char cPassword[MAX_NAME_LENGTH];		//设备密码
}CMS_CONNECT_PARSE_ModifyDevice_Request;




//通道信息
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];	//设备序列号
	int iChannel;			//通道号，从1开始
}CMS_CONNECT_PARSE_Channel;



//分组信息
typedef struct
{
	char cGroupName[MAX_NAME_LENGTH];	//分组名称
	int iChannelCount;		//通道个数
	CMS_CONNECT_PARSE_Channel sChannel[MAX_NAME_LENGTH];	//通道数组
}CMS_CONNECT_PARSE_GroupInfo;



//添加删除分组请求
typedef struct
{
	char cGroupName[MAX_NAME_LENGTH];	//分组名称
}CMS_CONNECT_PARSE_Group_Request;



//分组添加删除通道
typedef struct
{
	char cGroupName[MAX_NAME_LENGTH];	//分组名称
	char cSerialNum[MAX_NAME_LENGTH];	//设备序列号
	int iChannel;			//通道号，从1开始
}CMS_CONNECT_PARSE_ChannelInGroup;




//打开和关闭实时流请求（参数一样）
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];	//设备序列号
	int iChannel;			//通道号，从1开始
	CMS_CONNECT_PARSE_StreamType eStreamType;	//码流类型
}CMS_CONNECT_PARSE_Realtime_Request;




//云台控制请求
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//设备序列号
	int iChannel;				//通道号，从1开始
	CMS_CONNECT_PARSE_PtzCmdType ePtzCmd;	//云台操作命令字
	int isStoped;				//0为开始，1为停止
	int iSpeed;					//转向速度
}CMS_CONNECT_PARSE_CtrlPtz_Request;




//预置点控制请求
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//设备序列号
	int iChannel;				//通道号，从1开始
	CMS_CONNECT_PARSE_PresetCmdType ePtzCmd;	//预置点操作命令字
	int iPresetIndex;			//预置点序号
}CMS_CONNECT_PARSE_CtrlPreset_Request;




//巡航路径
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//设备序列号
	int iChannel;				//通道号，从1开始
	int iCruiseRoute;		//巡航路径序号
}CMS_CONNECT_PARSE_CruiseRoute;




//巡航点
typedef struct
{
	CMS_CONNECT_PARSE_CruiseRoute sCruiseRoute;		//巡航路径
	int iCruisePoint;		//巡航点
}CMS_CONNECT_PARSE_CruisePoint;



//巡航点设置信息
typedef struct
{
	int iPreset;			//预置点
	int iStaySec;			//停留秒数
	int iSpeed;				//转向速度
}CMS_CONNECT_PARSE_CruisePoint_Param;




//巡航点设置请求
typedef struct
{
	CMS_CONNECT_PARSE_CruisePoint sCruisePoint;
	CMS_CONNECT_PARSE_CruisePoint_Param sParam;
}CMS_CONNECT_PARSE_SetCruise_Request;




//启动巡航请求
typedef struct
{
	CMS_CONNECT_PARSE_CruiseRoute sCruiseRoute;
	int isStoped;				//是否停止，0-启动巡航；1-停止巡航
}CMS_CONNECT_PARSE_RunCruise_Request;




//轨迹
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//设备序列号
	int iChannel;				//通道号，从1开始
	int iLocusIndex;		//轨迹序号
}CMS_CONNECT_PARSE_Locus;



//设置轨迹
typedef struct
{
	CMS_CONNECT_PARSE_Locus sLocus;
	int isStoped;	//是否停止记录；0-开始记录轨迹，1-停止记录轨迹
}CMS_CONNECT_PARSE_SetLocus_Request;




//运行轨迹
typedef struct
{
	CMS_CONNECT_PARSE_Locus sLocus;
	int isStoped;	//是否运行轨迹；0-开始运行轨迹，1-停止运行轨迹
}CMS_CONNECT_PARSE_RunLocus_Request;



//地图结点
struct CMS_CONNECT_PARSE_MapNode
{
	char cMapName[MAX_NAME_LENGTH];
	CMS_CONNECT_PARSE_MapNode *parent;
	std::list<CMS_CONNECT_PARSE_MapNode *> children;

	CMS_CONNECT_PARSE_MapNode()
	{
		parent = NULL;
	}
	~CMS_CONNECT_PARSE_MapNode()
	{
		while (0 < children.size())
		{
			CMS_CONNECT_PARSE_MapNode *pNode = children.back();
			children.pop_back();
			delete pNode;
		}
	}
};




//地图图片
struct CMS_CONNECT_PARSE_Image
{
	char cFormat[MAX_NAME_LENGTH];
	unsigned int iBufferSize;
	unsigned char *lpBufferData;

	CMS_CONNECT_PARSE_Image()
	{
		lpBufferData = NULL;
	}
	~CMS_CONNECT_PARSE_Image()
	{
		delete[]lpBufferData;
	}
};




//添加地图请求
typedef struct
{
	char cParentName[MAX_NAME_LENGTH];	//父地图名称，为空表示为顶级地图
	char cMapName[MAX_NAME_LENGTH];		//要添加的地图名称
	CMS_CONNECT_PARSE_Image image; //地图图片
}CMS_CONNECT_PARSE_AddMap_Request;




//地图
typedef struct
{
	char cMapName[MAX_NAME_LENGTH];		//要操作的地图名称
}CMS_CONNECT_PARSE_Map;





//地图内节点
typedef struct
{
	int iType;		//地图内节点类型 1-子地图，2-普通通道，3-报警输入，4-报警输出，5-球机，6-半球，7-枪机
	char cMapName[MAX_NAME_LENGTH];	//iType为1时表示子地图名称
	char cSerialNum[MAX_NAME_LENGTH];	//iType为2时表示设备序列号
	int iIndex;		//iType为2时表示通道号，为3表示报警输入号，为4表示报警输出号
}CMS_CONNECT_PARSE_MapItem;



//地图中子节点布局
typedef struct
{
	CMS_CONNECT_PARSE_MapItem sItem;
	int iPosX;
	int iPosY;
}CMS_CONNECT_PARSE_MapItemLayout;




//地图中设置子节点布局
typedef struct
{
	CMS_CONNECT_PARSE_Map sMap;
	CMS_CONNECT_PARSE_MapItemLayout sLayout;
}CMS_CONNECT_PARSE_SetMapItemLayout_Request;



//地图布局中删除子节点
typedef struct
{
	CMS_CONNECT_PARSE_Map sMap;
	CMS_CONNECT_PARSE_MapItem sItem;
}CMS_CONNECT_PARSE_DelMapItemLayout_Request;



//回放参数
typedef struct
{
	CMS_CONNECT_PARSE_RecLocationType eRecLocation;	//录像位置
	unsigned int timeUTC_Begin;	//开始时间 UTC
	unsigned int timeUTC_End;		//结束时间 UTC
	CMS_CONNECT_PARSE_StreamType eStreamType;	//码流类型
	unsigned int iRecordType;   //录像类型，CMS_CONNECT_PARSE_RecordType 进行 | 运算来增加查询的录像类型
	CMS_CONNECT_PARSE_RecordType_Condition eRecordType_Condition;   //录像查询条件
}CMS_CONNECT_PARSE_Replay_Param;


//通道标识
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];
	int iChannel;
}CMS_CONNECT_PARSE_ChId;


//录像检索响应参数
typedef struct
{
	CMS_CONNECT_PARSE_ChId ch; //通道
	unsigned int iRecordType;	//录像类型 CMS_CONNECT_PARSE_RecordType 进行 | 运算来增加查询的录像类型
	unsigned int timeUTC_Begin;	//开始时间 UTC
	unsigned int timeUTC_End;		//结束时间 UTC
	unsigned int lFileSize;		//文件大小
}CMS_CONNECT_PARSE_SearchRecord_Param;


//历史流控制请求
typedef struct
{
	CMS_CONNECT_PARSE_ReplayCmdType eCmdType;	//回放控制命令字 
	unsigned int lParam;  //参数  具体描述见CMS_CONNECT_PARSE_ReplayCmdType定义
}CMS_CONNECT_PARSE_CtrlReplay_Request;



//打开和关闭对讲请求（参数一样）
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//设备序列号
	int iChannel;				//通道号 0表示直接与NVR对讲，从1开始表示与对应通道对讲
}CMS_CONNECT_PARSE_Intercom_Request;



//打开和关闭录像请求（参数一样）
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//设备序列号
	int iChannel;				//通道号 从1开始
}CMS_CONNECT_PARSE_Record_Request;



typedef struct
{
	unsigned char cFlag;		//查询的日志类型组合，可以多项进行‘|’运算来组合
	unsigned int timeUTC_Begin;	//开始时间 UTC
	unsigned int timeUTC_End;	//结束时间 UTC
	unsigned int iOffset;        //偏移，从第几条开始
	unsigned int iCount;        //搜索多少条数据
}CMS_CONNECT_PARSE_SearchLog_Request;




typedef struct
{
	CMS_CONNECT_PARSE_LogType eType;	//日志类型
	unsigned int timeUTC;				//时间UTC
	char cUserName[MAX_NAME_LENGTH];					//用户名
	char cClientIP[MAX_NAME_LENGTH];					//客户端IP
	char cParam[MAX_NAME_LENGTH];					//参数1，见CMS_CONNECT_PARSE_LogType声明
	int iParam[2];						//参数2，见CMS_CONNECT_PARSE_LogType声明
}CMS_CONNECT_PARSE_Log;



//解码器结点
class CMS_CONNECT_PARSE_DecoderNode
{
public:
	CMS_CONNECT_PARSE_DecoderNode()
	{
		memset(cSerialNum, 0, MAX_NAME_LENGTH);
		memset(cDecoderName, 0, MAX_NAME_LENGTH);
		memset(cUserName, 0, MAX_NAME_LENGTH);
		memset(cPassword, 0, MAX_NAME_LENGTH);
		memset(cDecoderIP, 0, MAX_NAME_LENGTH);
	}
	~CMS_CONNECT_PARSE_DecoderNode()
	{

	}
	char cSerialNum[MAX_NAME_LENGTH];	//序列号
	char cDecoderName[MAX_NAME_LENGTH];	//名称
	char cDecoderIP[MAX_NAME_LENGTH];		//IP
	int iDecoderPort;		//端口
	char cUserName[MAX_NAME_LENGTH];		//用户名
	char cPassword[MAX_NAME_LENGTH];		//密码
	int iOutputCount;		//视频输出个数
	int isOnline;			//是否在线
};




//添加解码器请求
typedef struct
{
	char cDecoderIP[MAX_NAME_LENGTH];		//解码器IP
	int iDecoderPort;		//解码器端口
	char cDecoderName[MAX_NAME_LENGTH];	//解码器名称
	char cUserName[MAX_NAME_LENGTH];		//解码器用户名
	char cPassword[MAX_NAME_LENGTH];		//解码器密码
}CMS_CONNECT_PARSE_AddDecoder_Request;




//删除解码器请求
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];	//解码器序列号
}CMS_CONNECT_PARSE_DelDecoder_Request;



//修改解码器请求
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];	//解码器序列号
	char cDecoderName[MAX_NAME_LENGTH];	//解码器名称
	char cUserName[MAX_NAME_LENGTH];		//解码器用户名
	char cPassword[MAX_NAME_LENGTH];		//解码器密码
}CMS_CONNECT_PARSE_ModifyDecoder_Request;



//修改解码器通知
typedef struct {
	char cSerialNum[MAX_NAME_LENGTH];	//序列号
	char cDecoderName[MAX_NAME_LENGTH];	//名称
	char cUserName[MAX_NAME_LENGTH];		//用户名
	char cPassword[MAX_NAME_LENGTH];		//密码
	int isOnline;			//是否在线
}CMS_CONNECT_PARSE_ModifyDecoder_Notice;



//解码器搜索结果
typedef struct {
	char cSerialNum[MAX_NAME_LENGTH];	//解码器序列号
	char cDecoderIP[MAX_NAME_LENGTH];		//解码器IP
	int iDecoderPort;		//解码器端口
}CMS_CONNECT_PARSE_SearchDecoderInfo;



//电视墙信息
typedef struct {
	char cName[MAX_NAME_LENGTH];             //墙名称
	char cDescription[MAX_DESCRIB_LENGTH];     //描述
	int iRowCount;              //行数
	int iColumnCount;           //列数
	int isEnabled;              //是否启用
}CMS_CONNECT_PARSE_WallInfo;



//电视墙
typedef struct
{
	char cWallName[MAX_NAME_LENGTH];      //墙名称
}CMS_CONNECT_PARSE_Wall;




//电视墙里解码器布局
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];	//解码器序列号
	int iOutputNo;			//解码器输出序号,从1开始
	int iRow;               //行号，从1开始
	int iColumn;            //列号，从1开始
}CMS_CONNECT_PARSE_WallLayoutItem;



//设置电视墙是否启用
typedef struct
{
	char cWallName[MAX_NAME_LENGTH];     //墙名称
	int isEnabled;          //是否启用
}CMS_CONNECT_PARSE_SetWallEnabled_Request;



//电视墙轮询分组切换通知
typedef struct {
	char cDecoderSerial[MAX_NAME_LENGTH];    //解码器序列号
	int iOutputNo;				//解码器输出序号,从1开始
	int iSplitNo;               //解码器分屏号，从1开始
	char cDeviceSerial[MAX_NAME_LENGTH];     //设备序列号
	int iChNo;                  //通道号，从1开始
	CMS_CONNECT_PARSE_StreamType eStreamType;   //码流类型
}CMS_CONNECT_PARSE_WallChangeGroup_Notice;


typedef struct
{
	char cWallName[MAX_NAME_LENGTH];     //电视墙名称
	int isLock;                       //1-获取锁;0-释放锁
}CMS_CONNECT_PARSE_WallLock_Request;


//解码器分屏控制
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];	//解码器序列号
	int iOutputNo;
	CMS_CONNECT_PARSE_DecoderWorkState eWorkState;  //工作状态
	CMS_CONNECT_PARSE_DecoderSplitType eSplitType;  //分屏类型
	int iSplitNo;   //分屏号，从1开始
}CMS_CONNECT_PARSE_DecoderSplitCtrl_Request;



typedef struct {
	char cDeviceSerial[MAX_NAME_LENGTH];     //设备序列号
	int iChNo;                  //通道号，从1开始
	CMS_CONNECT_PARSE_StreamType eStreamType;   //码流类型
	int iStaySecond;			//暂停时间,秒
}CMS_CONNECT_PARSE_Decoder_RealtimeCh;

//解码器开启预览
typedef struct {
	char cDecoderSerial[MAX_NAME_LENGTH];    //解码器序列号
	int iOutputNo;				//解码器输出序号,从1开始
	int iSplitNo;               //解码器分屏号，从1开始
	int iChNum;					//要开启的通道个数
	CMS_CONNECT_PARSE_Decoder_RealtimeCh streams[MAX_GROUP_CH_COUNT];
}CMS_CONNECT_PARSE_DecoderOpenRealtime_Request;


//解码器关闭预览
typedef struct {
	char cDecoderSerial[MAX_NAME_LENGTH];    //解码器序列号
	int iOutputNo;				//解码器输出序号,从1开始
	int iSplitNo;               //解码器分屏号，从1开始
}CMS_CONNECT_PARSE_DecoderCloseRealtime_Request;


//解码器开启回放
typedef struct
{
	CMS_CONNECT_PARSE_RecLocationType eRecLocation;	//录像位置
	unsigned int timeUTC_Begin;	//开始时间 UTC
	unsigned int timeUTC_End;		//结束时间 UTC
	CMS_CONNECT_PARSE_StreamType eStreamType;	//码流类型
	unsigned int iRecordType;   //录像类型，CMS_CONNECT_PARSE_RecordType 进行 | 运算来增加查询的录像类型
	CMS_CONNECT_PARSE_RecordType_Condition eRecordType_Condition;   //录像查询条件
}CMS_CONNECT_PARSE_DecoderOpenReplay_Request;




//解码器回放参数，对应解码器分屏和回放通道
typedef struct {
	char cDecoderSerial[MAX_NAME_LENGTH];    //解码器序列号
	int iOutputNo;				//解码器输出序号,从1开始
	int iSplitNo;               //解码器分屏号，从1开始
	char cDeviceSerial[MAX_NAME_LENGTH];     //设备序列号
	int iChNo;                  //通道号，从1开始
}CMS_CONNECT_PARSE_DecoderReplay_Param;



//解码器回放时间
typedef struct
{
	unsigned int timeUTC;	//回放时间 UTC
}CMS_CONNECT_PARSE_DecoderReplayTime;


//解码器回放控制请求
typedef struct
{
	CMS_CONNECT_PARSE_DecoderReplayCmdType eCmdType;	//回放控制命令字
	unsigned int lParam;  //参数  具体描述见CMS_CONNECT_PARSE_DecoderReplayCmdType定义
}CMS_CONNECT_PARSE_DecoderCtrlReplay_Request;


typedef enum {
	SchemePollState_NotPoll = 0,
	SchemePollState_Polling,
}CMS_CONNECT_PARSE_Decoder_SchemePollState;

//电视墙运行时状态
typedef struct {
	CMS_CONNECT_PARSE_Decoder_SchemePollState eSchemePollState;	//预案轮询状态
	char cCurrentSchemeName[MAX_NAME_LENGTH];			//当前轮询的预案名称
	CMS_CONNECT_PARSE_WallReplayState eReplayState;     //回放状态
	CMS_CONNECT_PARSE_DecoderOpenReplay_Request replayParam;    //回放参数
	int iReplaySpeed;           //回放速度
	time_t timePlay;                //当前回放时间，UTC
	int isActive;				//是否主动解码 0-被动 1-主动
}CMS_CONNECT_PARSE_WallRuntimeState;



//解码器设置拼接请求
typedef struct {
	char cSerialNum[MAX_NAME_LENGTH];        //解码器序列号
	int iOutputNo;				//解码器输出序号,从1开始
	int isSplice;                 //是否拼接 0-正常 1-拼接
}CMS_CONNECT_PARSE_DecoderSetSplice_Request;

//解码器运行时状态
typedef struct {
	char cSerialNum[MAX_NAME_LENGTH];        //解码器序列号
	int iOutputNo;							//解码器输出序号,从1开始
	int isSplice;							//是否拼接
	struct {
		CMS_CONNECT_PARSE_DecoderSplitType eType;
		int iSplitNo;
		struct {
			int iChNum;					//要开启的通道个数
			CMS_CONNECT_PARSE_Decoder_RealtimeCh streams[MAX_GROUP_CH_COUNT];
		} splits[MAX_SPLIT_COUNT];
	} previewState;
	struct {
		CMS_CONNECT_PARSE_DecoderSplitType eType;
		int iSplitNo;
		struct {
			char cDeviceSerial[MAX_NAME_LENGTH];     //设备序列号
			int iChNo;                  //通道号，从1开始
		} splits[MAX_SPLIT_COUNT];
	} playbackState;
}CMS_CONNECT_PARSE_DecoderRuntimeState;



//用户的通道权限
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];            //通道序列号
	int iChannel;                           //通道号
	int isPlaybackRight;            //是否有回放权限
	int isRecordRight;                //是否有中心端录像权限
	int isIntercomRight;             //是否有对讲权限
	int iPtzLevel;                          //云台等级
}CMS_CONNECT_PARSE_ChannelAuth;


//用户权限
struct CMS_CONNECT_PARSE_UserAuth
{
	CMS_CONNECT_PARSE_ChannelAuth* pChannelAuth;
	int iChannelAuthCount;
	CMS_CONNECT_PARSE_Map* pMapAuth;
	int iMapAuthCount;
	CMS_CONNECT_PARSE_Wall* pWallAuth;
	int iWallAuthCount;
	CMS_CONNECT_PARSE_UserAuth() { pChannelAuth = NULL; iChannelAuthCount = 0; pMapAuth = NULL; iMapAuthCount = 0; pWallAuth = NULL; iWallAuthCount = 0; }
	~CMS_CONNECT_PARSE_UserAuth() { delete[]pChannelAuth; delete[]pMapAuth; delete[]pWallAuth; }
};


//设置用户权限请求
typedef struct
{
	CMS_CONNECT_PARSE_User sUser;
	CMS_CONNECT_PARSE_UserAuth sUserAuth;
}CMS_CONNECT_PARSE_SetUserAuthRequest;


//联动规则
typedef struct
{
	char cRuleName[MAX_NAME_LENGTH];     //联动规则名称
	CMS_CONNECT_PARSE_AlarmType eAlarmType;		//告警类型
	char cSerialNum[MAX_NAME_LENGTH];						//告警源设备序列号
	int iParam;									//告警参数，告警类型为告警输入时表示告警输入号，否则为通道号
	char cRemarks[MAX_DESCRIB_LENGTH];         //备注
	int isEnabled;                      //是否启用
}CMS_CONNECT_PARSE_LinkageRuleParam;



//设置联动规则是否启用请求
typedef struct
{
	char cRuleName[MAX_NAME_LENGTH];     //联动规则名称
	int isEnabled;                      //是否启用
}CMS_CONNECT_PARSE_SetLinkageRuleEnabled_Request;


//联动动作参数
typedef struct
{
	char cDeviceSerial[MAX_NAME_LENGTH];        //设备序列号
	int iChannel;                           //通道号
	CMS_CONNECT_PARSE_LinkagePtzType ePtzType;  //联动动作为LinageActionType_PTZ时有效
	int iPtzIndex;      //联动动作为LinageActionType_PTZ时有效，表示预置点序号或巡航路径序号
	char cDecoderSerial[MAX_NAME_LENGTH];        //解码器序列号   联动动作为LinageActionType_Wall时有效
	int iOutputNo;							//解码器输出序号
}CMS_CONNECT_PARSE_LinkageActionParam;


typedef struct
{
	CMS_CONNECT_PARSE_LinkageActionType eActionType;    //联动动作类型
	int iStopSec;                       //报警结束时间，0表示自动结束，其它值表示多少秒后结束，联动动作为录像或抓图时无效
	CMS_CONNECT_PARSE_LinkageActionParam sActionParam[MAX_LINKAGEACTION_PARAM_COUNT];
	int iParamCount;
}CMS_CONNECT_PARSE_LinkageAction;



typedef struct
{
	CMS_CONNECT_PARSE_LinkageRuleParam sRuleParam;
	CMS_CONNECT_PARSE_LinkageAction sAction[MAX_LINKAGEACTION_COUNT];
	int iActionCount;
}CMS_CONNECT_PARSE_SetLinkageRule_Request;


typedef struct
{
	char cRuleName[MAX_NAME_LENGTH];     //联动规则名称
}CMS_CONNECT_PARSE_LinkageRule;


typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];    //解码器序列号
	int iOutputNo;
}CMS_CONNECT_PARSE_StopLinkageWall_Request;


typedef struct
{
	char cDecoderSerial[MAX_NAME_LENGTH];        //解码器序列号
	int isStoped;                       //报警是否停止 0-联动开始 1-联动停止
	char cDeviceSerial[MAX_NAME_LENGTH];         //设备序列号,isStoped为0时有效
	int iChannel;               //通道号,isStoped为0时有效
}CMS_CONNECT_PARSE_DecoderAlarmState;



typedef struct
{
	CMS_CONNECT_PARSE_AlarmType eAlarmType;
	char cSerialNum[MAX_NAME_LENGTH];
	int iParam;
	unsigned int timeBegin;     //报警开始时间
	unsigned int timeEnd;       //报警结束时间
}CMS_CONNECT_PARSE_AlarmLog;

//布局信息
typedef struct
{
	char cLayoutName[MAX_NAME_LENGTH];	//布局名称
	int iStyle;             //布局样式风格
	int iScreenCount;		//屏幕个数(最大不能超过64)
	int iStaySec;			//停留秒数

	CMS_CONNECT_PARSE_Channel sChannel[MAX_NAME_LENGTH];	//通道数组, 数组的下标即为通道在布局窗口的位置, 序列号(cSerialNum)为空,且通道号(iChannel)为0,代表当前位置没有添加通道
}CMS_CONNECT_PARSE_LayoutInfo;


//自动校时参数
typedef struct
{
	int iHour;      //校时时间，时；0~23
	int iMinute;    //校时时间，分；0~59
	int iSecond;    //校时时间，秒；0~59
	int iDays;      //校时间隔，天；为0时表示禁用自动校时
}CMS_CONNECT_PARSE_AutoTimeSyncParam;

//存储服务器标识
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];
}CMS_CONNECT_PARSE_StoragerId;

//存储服务器参数
typedef struct
{
	char cName[MAX_NAME_LENGTH]; //服务器名称
	char cIP[MAX_NAME_LENGTH];  //服务器IP
	int iPort;    //服务器端口
	char cUsername[MAX_NAME_LENGTH];  //服务器用户名
	char cPassword[MAX_NAME_LENGTH];  //服务器密码
}CMS_CONNECT_PARSE_StoragerParam;

//存储服务器信息
typedef struct
{
	CMS_CONNECT_PARSE_StoragerId id;
	CMS_CONNECT_PARSE_StoragerParam param;
}CMS_CONNECT_PARSE_StoragerInfo;

//磁盘分区信息
typedef struct
{
	char mount_dir[16];	//分区挂载点
	unsigned int avail_space_MB;	//每个分区的可用空间
	unsigned int total_space_MB;	//每个分区的总空间
	int is_read_only;		//1-只能从中检索录像，不能写入录像；0-可读可写
}CMS_CONNECT_PARSE_StoragerPartition;

//磁盘信息
typedef struct
{
	char cDescribe[MAX_DESCRIB_LENGTH];
	char cSerialNum[MAX_DESCRIB_LENGTH];
	unsigned int 	part_num;		//分区数目
	CMS_CONNECT_PARSE_StoragerPartition partition[32];
}CMS_CONNECT_PARSE_StoragerDisk;

//设置录像分区
typedef struct
{
	//unsigned long iRecMask[26];//按位从低到高分别表示A、B、C、D盘……，以此类推
	unsigned long long preallocSize[26];//单位MB
}CMS_CONNECT_PARSE_RecPartitionMask;

//硬盘工作模式
typedef struct
{
	bool auto_rotate;				//是否自动轮转
}CMS_CONNECT_PARSE_StoragerWorkAttr;


//通道配额
typedef struct
{
	CMS_CONNECT_PARSE_ChId ch;
	unsigned int space_MB;
}CMS_CONNECT_PARSE_ChQuota;

//配额信息
typedef struct
{
	bool manual_distribute;
	CMS_CONNECT_PARSE_ChQuota ch_quota;
}CMS_CONNECT_PARSE_StoragerQuota;

//录像计划的时间段
typedef struct
{
	unsigned int start_hour;
	unsigned int start_minute;
	unsigned int stop_hour;
	unsigned int stop_minute;
}CMS_CONNECT_PARSE_ArmingTime;

//录像计划
typedef struct
{
	CMS_CONNECT_PARSE_ChRecMode mode;
	unsigned int pre_sec;
	unsigned int delay_sec;
	CMS_CONNECT_PARSE_ArmingTime time[7][8];  //布防时间 time[0]表示周日，time[1]表示周一，time[2]表示周二,以此类推；每天最多可设置8个时间段
}CMS_CONNECT_PARSE_ChRecPlan;

//按月查询录像请求
typedef struct
{
	char cStoragerSerialNum[MAX_NAME_LENGTH];	//存储服务器序列号
	int year;
	int month;
}CMS_CONNECT_PARSE_InquiryRecByMonth_Request;

//按月查询录像请求
typedef struct
{
	unsigned int iMask;
}CMS_CONNECT_PARSE_InquiryRecByMonth_Reply;

typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//设备序列号
	CMS_CONNECT_PARSE_IOType eType;	//IO类型
	int iIndex;			//报警输入或输出序号
}CMS_CONNECT_PARSE_GetDeviceAlarmIO_Request;


typedef struct
{
	int iResult;
	bool isOpen;		//1-打开；0-关闭
}CMS_CONNECT_PARSE_GetDeviceAlarmIO_Reply;


typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//设备序列号
	CMS_CONNECT_PARSE_IOType eType;	//IO类型
	int iIndex;			//报警输入或输出序号
	bool isOpen;		//1-打开；0-关闭
}CMS_CONNECT_PARSE_SetDeviceAlarmIO_Request;

typedef struct
{
	CMS_CONNECT_PARSE_StoragerId storager;
	CMS_CONNECT_PARSE_ChId ch;
}CMS_CONNECT_PARSE_StoragerChNotice;


const int DistributorServerAuthorityIndex = 0;
const int StoragerServerAuthorityIndex = 1;
const int MatrixServerAuthorityIndex = 2;

const int RegisterDeviceAuthorityIndex = 10;
const int OnvifDeviceAuthorityIndex = 11;
const int GB28181DeviceAuthorityIndex = 12;
const int I8DeviceAuthorityIndex = 13;
const int I8HDeviceAuthorityIndex = 14;
const int I9DeviceAuthorityIndex = 15;
const int HN1DeviceAuthorityIndex = 16;
const int TUTKDeviceAuthorityIndex = 17;
const int TaosDeviceAuthorityIndex = 18;

typedef struct
{
	int iResult;
	int iMaxExtendedChCount[64];
}CMS_CONNECT_PARSE_GetMaxExtendedChCount_Reply;

typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//设备序列号
	int iChannel;			//通道号，从1开始
	char cName[MAX_NAME_LENGTH];	//新名称
}CMS_CONNECT_PARSE_ModifyChName_Notice;

typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//设备序列号
	int iChannel;			//通道号，从1开始
	char cName[MAX_NAME_LENGTH];	//新名称
}CMS_CONNECT_PARSE_ModifyChName_Request;

typedef struct
{
	int iResult;
	char cTempPassword[MAX_NAME_LENGTH];
}CMS_CONNECT_PARSE_GetTempPassword_Reply;

typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];
	int iChannel;
	int iTopX;
	int iTopY;
	int iBottomX;
	int iBottomY;
}CMS_CONNECT_PARSE_Set3D_Request;

typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];
	int iChannel;
	CMS_CONNECT_PARSE_UtcCmdType eCmd;
}CMS_CONNECT_PARSE_UTC_Request;



#define MAX_URL_LENGTH 128

typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];
	char cUrl[MAX_URL_LENGTH];
	int iLength;
	char buffer[0];
}CMS_CONNECT_PARSE_TranData_Request;

typedef struct
{
	int iResultCode;
	int iLength;
	char buffer[0];
}CMS_CONNECT_PARSE_TranData_Reply;


//解码器开启预览消息
typedef struct {
	char cWallName[MAX_NAME_LENGTH];             //墙名称
	char cDecoderSerial[MAX_NAME_LENGTH];    //解码器序列号
	int iSplitNo;               //解码器分屏号，从1开始
	char cDeviceSerial[MAX_NAME_LENGTH];     //设备序列号
	int iChNo;                  //通道号，从1开始
	CMS_CONNECT_PARSE_StreamType eStreamType;   //码流类型
}CMS_CONNECT_PARSE_DecoderOpenRealtime_Notice;



//解码器关闭预览消息
typedef struct {
	char cWallName[MAX_NAME_LENGTH];             //墙名称
	char cDecoderSerial[MAX_NAME_LENGTH];    //解码器序列号
	int iSplitNo;               //解码器分屏号，从1开始
}CMS_CONNECT_PARSE_DecoderCloseRealtime_Notice;




//解码器轮询控制消息
typedef struct {
	char cWallName[MAX_NAME_LENGTH];             //墙名称
	CMS_CONNECT_PARSE_PollCtrlType eCtrlType;
}CMS_CONNECT_PARSE_DecoderPollCtrl_Notice;


//解码器开启回放消息
typedef struct {
	char cWallName[MAX_NAME_LENGTH];             //墙名称
	CMS_CONNECT_PARSE_RecLocationType eRecLocation;	//录像位置
	unsigned int timeUTC_Begin;	//开始时间 UTC
	unsigned int timeUTC_End;		//结束时间 UTC
	CMS_CONNECT_PARSE_StreamType eStreamType;	//码流类型
	unsigned int iRecordType;   //录像类型，CMS_CONNECT_PARSE_RecordType 进行 | 运算来增加查询的录像类型
	CMS_CONNECT_PARSE_RecordType_Condition eRecordType_Condition;   //录像查询条件
	unsigned int iParamCount;		//解码器回放参数个数
	CMS_CONNECT_PARSE_DecoderReplay_Param param[64];
}CMS_CONNECT_PARSE_DecoderOpenReplay_Notice;

//解码器关闭回放消息
typedef struct {
	char cWallName[MAX_NAME_LENGTH];             //墙名称
}CMS_CONNECT_PARSE_DecoderCloseReplay_Notice;


typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];				//序列号
	char cAccessName[MAX_NAME_LENGTH];				//门禁器名称
	bool isOnline;
	int iDoorCount;									//门的数量
	char cstrIP[MAX_NAME_LENGTH];					//IP
	int iPort;										//iPort
	CMS_CONNECT_PARSE_AccessControlType eProtocolType;	//协议类型
}CMS_CONNECT_PASER_AccessControlInfo;

typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];				//序列号（添加设备必需填写）
	CMS_CONNECT_PARSE_AccessControlType eProtocolType;	//协议类型（添加设备必需填写）
	char cAccessName[MAX_NAME_LENGTH];				//门禁器名称（添加设备必填）
}CMS_CONNECT_PASER_AccessRequest;

typedef struct
{
	int iControlCount;	//门禁控制器的数量
	CMS_CONNECT_PASER_AccessControlInfo *controlInfo;	//指向数组，数量由iControlCount决定
}CMS_CONNECT_PASER_AccessControl;

typedef struct
{
	bool bHistory;
}CMS_CONNECT_PASER_AccessControlRequest;

typedef struct
{
	bool bOpen;
	int iDoorNo;
	char cSerialNum[MAX_NAME_LENGTH];
}CMS_CONNECT_PARSE_AccessControl_Cmd;

typedef struct
{
	int iProtocolTypeFlags;	//协议类型，按位取|
	int isStop;       //是否停止搜索 0-开始搜索 1-停止搜索
}CMS_CONNECT_PARSE_SearchAccess_Request;

typedef struct
{
	CMS_CONNECT_PARSE_AccessAlarmType eAlarmType;
	char cSerialNum[MAX_NAME_LENGTH];
	int iParam;
	unsigned int timeBegin;     //报警开始时间
	unsigned int timeEnd;       //报警结束时间
}CMS_CONNECT_PARSE_AccessLog;

//联动规则
typedef struct
{
	char cRuleName[MAX_NAME_LENGTH];     //联动规则名称
	CMS_CONNECT_PARSE_AccessAlarmType eAlarmType;		//告警类型
	char cSerialNum[MAX_NAME_LENGTH];						//告警源设备序列号
	int iParam;									//告警参数，告警类型为告警输入时表示告警输入号，否则为通道号
	char cRemarks[MAX_DESCRIB_LENGTH];         //备注
	int isEnabled;                      //是否启用
}CMS_CONNECT_PARSE_AccessLinkageRuleParam;

typedef struct
{
	CMS_CONNECT_PARSE_AccessLinkageRuleParam sRuleParam;
	CMS_CONNECT_PARSE_LinkageAction sAction[MAX_LINKAGEACTION_COUNT];
	int iActionCount;
}CMS_CONNECT_PARSE_SetAccessLinkageRule_Request;

//解码器分组
typedef struct {
	char cGroupName[MAX_NAME_LENGTH];
	int iChCount;
	struct {
		char cSerialNum[MAX_NAME_LENGTH];		//设备序列号
		int iChannel;			//通道号，从1开始
		int iStaySecond;		//停留时间,秒
	} channels[MAX_GROUP_CH_COUNT];
}CMS_CONNECT_PARSE_Decoder_Group;




typedef struct {
	char cGroupName[MAX_NAME_LENGTH];
}CMS_CONNECT_PARSE_Decoder_DelGroup_Request;

typedef struct {
	char cWallName[MAX_NAME_LENGTH];
	int isActive;
}CMS_CONNECT_PARSE_Decoder_SetActive_Request;


#define MAX_OUTPUT_IN_WALL 64

typedef struct {
	char cSchemeName[MAX_NAME_LENGTH];
	int iStaySecond;
	int iCount;
	struct {
		char cSerialNum[MAX_NAME_LENGTH];        //解码器序列号
		int iOutputNo;							//解码器输出序号,从1开始
		CMS_CONNECT_PARSE_DecoderSplitType eType;
		int iSplitNo;
		int isSplice;					//是否拼接
		struct {
			int iChNum;					//要开启的通道个数
			CMS_CONNECT_PARSE_Decoder_RealtimeCh streams[MAX_GROUP_CH_COUNT];
		} splits[MAX_SPLIT_COUNT];
	} outputs[MAX_OUTPUT_IN_WALL];
}CMS_CONNECT_PARSE_DecoderScheme;


typedef struct {
	char cWallName[MAX_NAME_LENGTH];
	CMS_CONNECT_PARSE_DecoderScheme scheme;
}CMS_CONNECT_PARSE_Decoder_SetScheme_Request;

typedef struct {
	char cWallName[MAX_NAME_LENGTH];
	char cSchemeName[MAX_NAME_LENGTH];
}CMS_CONNECT_PARSE_Decoder_DeleteScheme_Request;

typedef struct {
	char cWallName[MAX_NAME_LENGTH];
	char cSchemeName[MAX_NAME_LENGTH];
	int iStaySecond;
}CMS_CONNECT_PARSE_Decoder_SetSchemeStayTime_Request;

typedef struct {
	char cWallName[MAX_NAME_LENGTH];
}CMS_CONNECT_PARSE_Decoder_GetScheme_Request;

#define MAX_SCHEME_COUNT 16

typedef struct {
	int iResultCode;
	int iSchemeCount;
	CMS_CONNECT_PARSE_DecoderScheme schemes[MAX_SCHEME_COUNT];
}CMS_CONNECT_PARSE_Decoder_GetScheme_Reply;


typedef struct {
	char cWallName[MAX_NAME_LENGTH];
	int isStop;	//0-开始轮询,1-停止轮询
}CMS_CONNECT_PARSE_Decoder_CtrlSchemePoll_Request;

typedef struct {
	char cWallName[MAX_NAME_LENGTH];
	char cSchemeName[MAX_NAME_LENGTH];
}CMS_CONNECT_PARSE_Decoder_ChangeScheme_Notice;

typedef struct {
	char cSerialNum[MAX_NAME_LENGTH];	//解码器序列号
	int iOutputNo;	//输出序号,从1开始,0表示关闭所有声音
	int iSplitNo;   //分屏号，从1开始,0表示关闭所有声音
}CMS_CONNECT_PARSE_Decoder_SetSound_Request;

typedef struct {
	char cSerialNum[MAX_NAME_LENGTH];	//解码器序列号
	int iOutputNo;	//输出序号,从1开始
}CMS_CONNECT_PARSE_GetDecoderSplit_Request;

typedef struct {
	CMS_CONNECT_PARSE_DecoderSplitType eSplitType;  //分屏类型
	int iSplitNo;   //分屏号，从1开始
}CMS_CONNECT_PARSE_DecoderSplitState;

typedef struct {
	char cSerialNum[MAX_NAME_LENGTH];	//解码器序列号
}CMS_CONNECT_PARSE_GetDecoderAbility_Request;

typedef struct {
	int iWidth;
	int iHeight;
	int iChCount;
}CMS_CONNECT_PARSE_DecoderAbility;

typedef struct {
	char cSerialNum[MAX_NAME_LENGTH];	//序列号
}CMS_CONNECT_PARSE_GetFishEyeAbility_Request;

typedef struct {
	int iFishEyeView;
	int iFullView;
	int iPtzView;
}CMS_CONNECT_PARSE_FishEyeViewMode;

#define MAX_FISHEYE_ABILITY_COUNT 8

typedef struct {
	int iCount;
	CMS_CONNECT_PARSE_FishEyeViewMode mode[MAX_FISHEYE_ABILITY_COUNT];
}CMS_CONNECT_PARSE_FishEyeAbility;


typedef struct {
	char cSerialNum[MAX_NAME_LENGTH];	//序列号
}CMS_CONNECT_PARSE_GetFishEyeMode_Request;


typedef enum {
	InstallMode_Top = 0,
	InstallMode_Wall,
	InstallMode_Land,
}CMS_CONNECT_PARSE_GetFishEyeInstallMode;

typedef enum {
	FullViewMode_180 = 0,
	FullViewMOde_360,
}CMS_CONNECT_PARSE_GetFishEyeFullViewMode;

typedef struct {
	CMS_CONNECT_PARSE_GetFishEyeInstallMode installMode;
	CMS_CONNECT_PARSE_FishEyeViewMode viewMode;
	CMS_CONNECT_PARSE_GetFishEyeFullViewMode fullViewMode;
}CMS_CONNECT_PARSE_FishEyeMode;

typedef struct {
	char cSerialNum[MAX_NAME_LENGTH];	//序列号
	CMS_CONNECT_PARSE_FishEyeMode mode;
}CMS_CONNECT_PARSE_SetFishEyeMode_Request;

typedef struct {
	char method[MAX_NAME_LENGTH];
	int length;
	char payload[0];
}CMS_CONNECT_PARSE_Post_Request;

typedef struct {
	int resultCode;
	int length;
	char payload[0];
}CMS_CONNECT_PARSE_Post_Reply;

#endif // CMS_CONNECT_PARSE_COMMON_H

