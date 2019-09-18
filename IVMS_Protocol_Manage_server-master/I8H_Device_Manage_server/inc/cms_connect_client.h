/************************************************************************
*
*   文件名：cms_connect_client.h
*
*   文件描述：CMS客户端接口
*
*   创建人：Sunx, 2015年6月17日
*
*   版本号：1.0
*
*   修改记录：
*
************************************************************************/

#ifndef CMS_CONNECT_CLIENT_H
#define CMS_CONNECT_CLIENT_H



#if defined(WIN32)
	#if defined(__cplusplus)
        #if defined(CMS_CONNECT_CLIENT_LIB)
			#define CMS_CONNECT_CLIENT_API extern "C" __declspec(dllexport)
		#else
			#define CMS_CONNECT_CLIENT_API extern "C" __declspec(dllimport)
		#endif
	#else
		#define CMS_CONNECT_CLIENT_API
	#endif	
	#define CMS_CONNECT_CLIENT_CALLBACK __stdcall
#elif defined(__APPLE__)
	#if defined(__cplusplus)
		#define CMS_CONNECT_CLIENT_API extern "C"
	#else
		#define CMS_CONNECT_CLIENT_API
	#endif
	#define CMS_CONNECT_CLIENT_CALLBACK
#else
	#if defined(__cplusplus)
		#define CMS_CONNECT_CLIENT_API extern "C"
	#else
		#define CMS_CONNECT_CLIENT_API
	#endif
	#define CMS_CONNECT_CLIENT_CALLBACK
#endif

#ifndef	NULL
	#define	NULL 0
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

#include "cms_connect_parse_common.h"




//消息回调
typedef void (CMS_CONNECT_CLIENT_CALLBACK *CMS_CONNECT_CLIENT_MESSAGE_CALLBACK)(IN long lHandle, IN CMS_CONNECT_PARSE_NoticeType eNoticeType, IN unsigned char *lpMessage, IN unsigned int iSize, IN void *pUser);
//实时流回调
typedef void (CMS_CONNECT_CLIENT_CALLBACK *CMS_CONNECT_CLIENT_REALDATA_CALLBACK)(IN long lHandle, IN CMS_CONNECT_PARSE_StreamHeader *header, IN unsigned char *lpBuffer, IN unsigned int iSize, IN void *pUser);
//历史流回调
typedef void (CMS_CONNECT_CLIENT_CALLBACK *CMS_CONNECT_CLIENT_HISTORYDATA_CALLBACK)(IN long lHandle, IN long handle, IN CMS_CONNECT_PARSE_StreamHeader header, IN unsigned char *lpBuffer, IN unsigned int iSize, IN void *pUser);
//搜索设备回调,sDeviceInfo.cSerialNum为空表示搜索完毕
typedef void (CMS_CONNECT_CLIENT_CALLBACK *CMS_CONNECT_CLIENT_SEARCHDEVICE_CALLBACK)(IN long lHandle, IN CMS_CONNECT_PARSE_SearchDeviceInfo sDeviceInfo, IN void *pUser);
//搜索解码器回调
typedef void (CMS_CONNECT_CLIENT_CALLBACK *CMS_CONNECT_CLIENT_SEARCHDECODER_CALLBACK)(IN long lHandle, IN CMS_CONNECT_PARSE_SearchDecoderInfo sDecoderInfo, IN void *pUser);
//搜索门禁器回调
typedef void (CMS_CONNECT_CLIENT_CALLBACK *CMS_CONNECT_CLIENT_SEARCHACCESS_CALLBACK)(IN long lHandle, IN CMS_CONNECT_PARSE_SearchAccessInfo sAccessInfo, IN void *pUser);

//初始化
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_Init();
//反初始化
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_Uninit();

//用户登录
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_Login(OUT long &lHandle, IN char *lpHostName, IN unsigned int iPort, IN CMS_CONNECT_PARSE_Login_Request &request);
//用户注销
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_Logout(IN long lHandle);

//获取用户类型
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetUserType(IN long lHandle, OUT CMS_CONNECT_PARSE_UserType &eUserType);

//设置消息回调
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetMessageCallback(IN long lHandle, IN CMS_CONNECT_CLIENT_MESSAGE_CALLBACK func, IN void *pUser);

//用户注册
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_AddUser(IN long lHandle, IN CMS_CONNECT_PARSE_AddUser_Request &request);
//用户修改
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_ModifyUserPassword(IN long lHandle, IN CMS_CONNECT_PARSE_UserParam &request);
//用户删除
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DelUser(IN long lHandle, IN CMS_CONNECT_PARSE_User &request);
//获取用户列表
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetUser(IN long lHandle, OUT CMS_CONNECT_PARSE_AddUser_Request *&pUser, int &iUserCount);

//获取设备树
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetDeviceTree(IN long lHandle, OUT CMS_CONNECT_PARSE_Node *&pRootNode);
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_FreeDeviceNode(IN CMS_CONNECT_PARSE_Node *pRootNode);


//获取设备列表（忽略区域）
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetDeviceList(IN long lHandle, OUT CMS_CONNECT_PARSE_DeviceNode *&pDeviceNode, int &iDeviceCount);
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_FreeDeviceList(IN CMS_CONNECT_PARSE_DeviceNode *pDeviceNode);

CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetDeviceList_Json(IN long lHandle, char* &pBuffer, int &iBuffSize);

//添加区域
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_AddArea(IN long lHandle, IN CMS_CONNECT_PARSE_AddArea_Request &request);
//删除区域
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DelArea(IN long lHandle, IN CMS_CONNECT_PARSE_DelArea_Request &request);
//修改区域
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_ModifyArea(IN long lHandle, IN CMS_CONNECT_PARSE_ModifyArea_Request &request);

//添加设备
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_AddDevice(IN long lHandle, IN CMS_CONNECT_PARSE_AddDevice_Request &request);
//删除设备
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DelDevice(IN long lHandle, IN CMS_CONNECT_PARSE_DelDevice_Request &request);
//修改设备
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_ModifyDevice(IN long lHandle, IN CMS_CONNECT_PARSE_ModifyDevice_Request &request);
//搜索设备
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_StartSearchDevice(IN long lHandle, IN CMS_CONNECT_PARSE_SearchDevice_Request &request, IN CMS_CONNECT_CLIENT_SEARCHDEVICE_CALLBACK fun, IN void *pUser);
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_StopSearchDevice(IN long lHandle);
//修改通道名
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_ModifyChName(IN long lHandle, IN CMS_CONNECT_PARSE_ModifyChName_Request &request);

//获取分组
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetGroup(IN long lHandle, OUT CMS_CONNECT_PARSE_GroupInfo *&pGroupInfo, OUT int &iCount);
//添加轮询分组
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_AddGroup(IN long lHandle, IN CMS_CONNECT_PARSE_Group_Request &request);
//删除轮询分组
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DelGroup(IN long lHandle, IN CMS_CONNECT_PARSE_Group_Request &request);
//添加通道到分组
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GroupAddChannel(IN long lHandle, IN CMS_CONNECT_PARSE_ChannelInGroup &request);
//从分组删除通道
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GroupDelChannel(IN long lHandle, IN CMS_CONNECT_PARSE_ChannelInGroup &request);

//打开实时流。同一个源（通道和码流类型）只能打开一次
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_OpenRealtime(IN long lHandle, IN CMS_CONNECT_PARSE_Realtime_Request &request, IN CMS_CONNECT_CLIENT_REALDATA_CALLBACK func, IN void *pUser);
//关闭实时流。
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_CloseRealtime(IN long lHandle, IN CMS_CONNECT_PARSE_Realtime_Request &request);

//云台控制
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_CtrlPtz(IN long lHandle, IN CMS_CONNECT_PARSE_CtrlPtz_Request &request);
//预置点操作
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_CtrlPreset(IN long lHandle, IN CMS_CONNECT_PARSE_CtrlPreset_Request &request);
//获取巡航信息
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetCruise(IN long lHandle, IN CMS_CONNECT_PARSE_CruiseRoute &request, OUT CMS_CONNECT_PARSE_CruisePoint_Param * &Param, OUT int &iParamCount);
//CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetCruise_Json(IN long lHandle, IN CMS_CONNECT_PARSE_GetCruise_Request request,OUT char *&lpBuffer, OUT int &iBufferSize);
//设置巡航点
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetCruisePoint(IN long lHandle, IN CMS_CONNECT_PARSE_SetCruise_Request &request);
//删除巡航点
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DelCruisePoint(IN long lHandle, IN CMS_CONNECT_PARSE_CruisePoint &request);
//清除巡航路径
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_ClearCruiseRoute(IN long lHandle, IN CMS_CONNECT_PARSE_CruiseRoute &request);
//启动巡航
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_RunCruise(IN long lHandle, IN CMS_CONNECT_PARSE_RunCruise_Request &request);

//设置轨迹
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetLocus(IN long lHandle, IN CMS_CONNECT_PARSE_SetLocus_Request &request);
//运行轨迹
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_RunLocus(IN long lHandle, IN CMS_CONNECT_PARSE_RunLocus_Request &request);
//清除轨迹
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_ClearLocus(IN long lHandle, IN CMS_CONNECT_PARSE_Locus &request);

//3D定位
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_Set3D(IN long lHandle, IN CMS_CONNECT_PARSE_Set3D_Request &request);

//开启对讲
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_OpenIntercom(IN long lHandle, IN CMS_CONNECT_PARSE_Intercom_Request &request, IN CMS_CONNECT_CLIENT_REALDATA_CALLBACK func, IN void *pUser);
//关闭对讲
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_CloseIntercom(IN long lHandle, IN CMS_CONNECT_PARSE_Intercom_Request &request);
//发送对讲音频流
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SendIntercomData(IN long lHandle, IN CMS_CONNECT_PARSE_StreamHeader &header, IN unsigned char *lpBuffer, IN int iSize);

//录像检索
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SearchRecord(IN long lHandle, IN CMS_CONNECT_PARSE_Replay_Param &param, IN CMS_CONNECT_PARSE_ChId *ch, IN int iChCount, OUT CMS_CONNECT_PARSE_SearchRecord_Param * &RecordParam, OUT int &iRecCount);
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SearchRecord_Json(IN long lHandle, IN CMS_CONNECT_PARSE_Replay_Param param, IN CMS_CONNECT_PARSE_ChId *ch, IN int iChCount,OUT char *&lpBuffer, OUT int &iBufferSize);

//检索存储服务器一个月的录像
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SearchRecordByMonth(IN long lHandle, IN CMS_CONNECT_PARSE_InquiryRecByMonth_Request &request, OUT CMS_CONNECT_PARSE_InquiryRecByMonth_Reply &reply);

//打开回放
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_OpenReplay(OUT long &playhandle, IN long lHandle, IN CMS_CONNECT_PARSE_Replay_Param &param, IN CMS_CONNECT_PARSE_ChId *ch,  IN int iChCount, IN CMS_CONNECT_CLIENT_HISTORYDATA_CALLBACK func, IN void *pUser);
//关闭回放
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_CloseReplay(IN long playhandle);
//回放控制
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_CtrlReplay(IN long playhandle, IN CMS_CONNECT_PARSE_CtrlReplay_Request &request);


//获取地图树
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetMaps(IN long lHandle, OUT CMS_CONNECT_PARSE_MapNode *&pRootNode);
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_FreeMaps(IN CMS_CONNECT_PARSE_MapNode *pRootNode);
//添加地图结点
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_AddMap(IN long lHandle, IN CMS_CONNECT_PARSE_AddMap_Request &request);
//删除地图结点
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DelMap(IN long lHandle, IN CMS_CONNECT_PARSE_Map &request);
//获取地图图片
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetMapImage(IN long lHandle, IN CMS_CONNECT_PARSE_Map &request, OUT CMS_CONNECT_PARSE_Image *&pImage);
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_FreeMapImage(CMS_CONNECT_PARSE_Image *pImage);
//获取地图内布局
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetMapLayout(IN long lHandle, IN CMS_CONNECT_PARSE_Map &request, OUT CMS_CONNECT_PARSE_MapItemLayout *&pItemLayout, OUT int &iCount);
//地图中设置子结点布局
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_MapLayoutSetItem(IN long lHandle, IN CMS_CONNECT_PARSE_SetMapItemLayout_Request &request);
//从地图布局中删除子结点
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_MapLayoutDelItem(IN long lHandle, IN CMS_CONNECT_PARSE_DelMapItemLayout_Request &request);


//日志查询
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetLogs(IN long lHandle, IN CMS_CONNECT_PARSE_SearchLog_Request &request, OUT int &iTotalCount, OUT CMS_CONNECT_PARSE_Log *&pLogs, OUT int &iCount);

//报警日志查询
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetAlarmLogs(IN long lHandle, IN CMS_CONNECT_PARSE_SearchLog_Request &request, OUT int &iTotalCount, OUT CMS_CONNECT_PARSE_AlarmLog *&pLogs, OUT int &iCount);


//获取解码器
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetDecoders(IN long lHandle, OUT CMS_CONNECT_PARSE_DecoderNode *&pDecoders, OUT int &iCount);
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_FreeDecoders(IN CMS_CONNECT_PARSE_DecoderNode *pDecoders);
//添加解码器
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_AddDecoder(IN long lHandle, IN CMS_CONNECT_PARSE_AddDecoder_Request &request);
//删除解码器
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DelDecoder(IN long lHandle, IN CMS_CONNECT_PARSE_DelDecoder_Request &request);
//修改解码器
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_ModifyDecoder(IN long lHandle, IN CMS_CONNECT_PARSE_ModifyDecoder_Request &request);
//搜索解码器
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_StartSearchDecoder(IN long lHandle, IN CMS_CONNECT_CLIENT_SEARCHDECODER_CALLBACK fun, IN void *pUser);
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_StopSearchDecoder(IN long lHandle);
//获取电视墙列表
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetWalls(IN long lHandle, OUT CMS_CONNECT_PARSE_WallInfo *&pWalls, OUT int &iCount);
//添加电视墙
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_AddWall(IN long lHandle, IN CMS_CONNECT_PARSE_WallInfo &request);
//修改电视墙
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DelWall(IN long lHandle, IN CMS_CONNECT_PARSE_Wall &request);
//删除电视墙
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_ModifyWall(IN long lHandle, IN CMS_CONNECT_PARSE_WallInfo &request);
//启用电视墙
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetWallEnalbed(IN long lHandle, IN CMS_CONNECT_PARSE_SetWallEnabled_Request &request);
//获取电视墙内解码器布局
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetWallLayout(IN long lHandle, IN CMS_CONNECT_PARSE_Wall &request, OUT CMS_CONNECT_PARSE_WallLayoutItem *&pLayout, OUT int &iCount);
//设置电视墙内解码器布局
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetWallLayout(IN long lHandle, IN CMS_CONNECT_PARSE_Wall &request, IN CMS_CONNECT_PARSE_WallLayoutItem *pLayout, IN int iCount);
//获取电视墙锁
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_WallLock(IN long lHandle, IN CMS_CONNECT_PARSE_WallLock_Request &request);
//解码器分屏设置
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderSetSplit(IN long lHandle, IN CMS_CONNECT_PARSE_DecoderSplitCtrl_Request &request);
//解码器分屏获取
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderGetSplit(IN long lHandle, IN CMS_CONNECT_PARSE_GetDecoderSplit_Request &request, OUT CMS_CONNECT_PARSE_DecoderSplitState &state);
//解码器获取解码能力
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderGetAbility(IN long lHandle, IN CMS_CONNECT_PARSE_GetDecoderAbility_Request &request, OUT CMS_CONNECT_PARSE_DecoderAbility &ability);
//解码器打开预览
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderOpenRealtime(IN long lHandle, IN CMS_CONNECT_PARSE_DecoderOpenRealtime_Request &request);
//解码器关闭预览
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderCloseRealtime(IN long lHandle, IN CMS_CONNECT_PARSE_DecoderCloseRealtime_Request &request);
//解码器打开回放
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderOpenReplay(IN long lHandle, IN CMS_CONNECT_PARSE_DecoderOpenReplay_Request &request, IN CMS_CONNECT_PARSE_DecoderReplay_Param *param, IN int iParamCount);
//解码器关闭回放
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderCloseReplay(IN long lHandle);
//解码器获取回放时间
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderGetReplayTime(IN long lHandle, OUT CMS_CONNECT_PARSE_DecoderReplayTime &time);
//解码器回放控制
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderReplayCtrl(IN long lHandle, IN CMS_CONNECT_PARSE_DecoderCtrlReplay_Request &request);
//获取电视墙运行状态
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetWallRuntimeState(IN long lHandle, OUT CMS_CONNECT_PARSE_WallRuntimeState &wallState, OUT CMS_CONNECT_PARSE_DecoderRuntimeState *&pDecoderState, int &iDecoderCount);
//设置解码器拼接状态
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderSetSplice(IN long lHandle, IN CMS_CONNECT_PARSE_DecoderSetSplice_Request &request);
//解码器主动解码设置
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderSetActive(IN long lHandle, IN CMS_CONNECT_PARSE_Decoder_SetActive_Request &request);
//解码器声音设置
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderSetSound(IN long lHandle, IN CMS_CONNECT_PARSE_Decoder_SetSound_Request &request);

//获取解码器分组
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetDecoderGroup(IN long lHandle, OUT CMS_CONNECT_PARSE_Decoder_Group *&pGroup, OUT int &iCount);
//新增解码器分组
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderAddGroup(IN long lHandle, IN CMS_CONNECT_PARSE_Decoder_Group &group);
//删除解码器分组
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderDelGroup(IN long lHandle, IN CMS_CONNECT_PARSE_Decoder_DelGroup_Request &request);
//新增解码器分组通道
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderAddGroupCh(IN long lHandle, IN CMS_CONNECT_PARSE_Decoder_Group &group);
//删除解码器分组通道
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderDelAddGroupCh(IN long lHandle, IN CMS_CONNECT_PARSE_Decoder_Group &group);

//获取解码器预案
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderGetScheme(IN long lHandle, IN CMS_CONNECT_PARSE_Decoder_GetScheme_Request &request, OUT CMS_CONNECT_PARSE_DecoderScheme* &pScheme, OUT int &iCount);
//设置解码器预案
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderSetScheme(IN long lHandle, IN CMS_CONNECT_PARSE_Decoder_SetScheme_Request &request);
//删除解码器预案
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderDeleteScheme(IN long lHandle, IN CMS_CONNECT_PARSE_Decoder_DeleteScheme_Request &request);
//设置预案停留时间
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderSetSchemeStayTime(IN long lHandle, IN CMS_CONNECT_PARSE_Decoder_SetSchemeStayTime_Request &request);
//控制解码器预案轮询
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DecoderCtrlSchemePoll(IN long lHandle, IN CMS_CONNECT_PARSE_Decoder_CtrlSchemePoll_Request &request);

//获取用户权限
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetUserAuth(IN long lHandle, IN CMS_CONNECT_PARSE_User &request, OUT CMS_CONNECT_PARSE_UserAuth *&pUserAuth);
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_FreeUserAuth(IN CMS_CONNECT_PARSE_UserAuth *pUserAuth);
//设置用户权限
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetUserAuth(IN long lHandle, IN CMS_CONNECT_PARSE_SetUserAuthRequest &request);

//获取联动规则列表
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetLinkageRule(IN long lHandle, OUT CMS_CONNECT_PARSE_LinkageRuleParam *&pRuleParam, int &iRuleCount);
//获取联动动作
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetLinkageAction(IN long lHandle, IN CMS_CONNECT_PARSE_LinkageRule &request, CMS_CONNECT_PARSE_LinkageAction *&pAction, int &iActionCount);
//设置联动规则
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetLinkageRule(IN long lHandle, IN CMS_CONNECT_PARSE_SetLinkageRule_Request &request);
//设置联动规则是否启用
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetLinkageRuleEnabled(IN long lHandle, IN CMS_CONNECT_PARSE_SetLinkageRuleEnabled_Request &request);
//删除联动规则
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DelLinkageRule(IN long lHandle, IN CMS_CONNECT_PARSE_LinkageRule &request);

//停止联动上墙
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_StopLinkageWall(IN long lHandle, IN CMS_CONNECT_PARSE_StopLinkageWall_Request &request);

//获取布局信息
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetLayoutInfo(IN long lHandle, OUT CMS_CONNECT_PARSE_LayoutInfo *&pInfoArray, OUT int &infoCount);

//保存布局信息
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SaveLayoutInfo(IN long lHandle, IN const CMS_CONNECT_PARSE_LayoutInfo &info);

//删除布局信息
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DeleteLayoutInfo(IN long lHandle, IN const CMS_CONNECT_PARSE_LayoutInfo &info);

//手动校时
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_TimeSync(IN long lHandle);

//获取自动校时周期（天）
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetAutoTimeSyncParam(IN long lHandle, OUT CMS_CONNECT_PARSE_AutoTimeSyncParam &param);

//设置自动校时周期（天）
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetAutoTimeSyncParam(IN long lHandle, IN CMS_CONNECT_PARSE_AutoTimeSyncParam param);

//获取鱼眼相机能力集
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_FishEye_GetAbility(IN long lHandle, IN CMS_CONNECT_PARSE_GetFishEyeAbility_Request &request, OUT CMS_CONNECT_PARSE_FishEyeAbility &ability);
//获取鱼眼相机工作模式
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_FishEye_GetMode(IN long lHandle, IN CMS_CONNECT_PARSE_GetFishEyeMode_Request &request, OUT CMS_CONNECT_PARSE_FishEyeMode &mode);
//设置鱼眼相机工作模式
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_FishEye_SetMode(IN long lHandle, IN CMS_CONNECT_PARSE_SetFishEyeMode_Request &request);

/*************************
 * 移植存储功能
 * Add by sunx
 * 2016.09.09
*************************/

//获取存储服务器列表
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetStoragerList(IN long lHandle, OUT CMS_CONNECT_PARSE_StoragerInfo* &param, OUT int &iCount);
//添加存储服务器
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_AddStorager(IN long lHandle, IN CMS_CONNECT_PARSE_StoragerId &storager, IN CMS_CONNECT_PARSE_StoragerParam &param);
//删除存储服务器
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DeleteStorager(IN long lHandle, IN CMS_CONNECT_PARSE_StoragerId &storager);
//修改存储服务器
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_ModifyStorager(IN long lHandle, IN CMS_CONNECT_PARSE_StoragerId &storager, IN CMS_CONNECT_PARSE_StoragerParam &param);

//获取存储服务器的硬盘信息
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetStoragerDisk(IN long lHandle, IN CMS_CONNECT_PARSE_StoragerId &storager, OUT CMS_CONNECT_PARSE_StoragerDisk* &param, OUT int &iCount);

//设置录像分区
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetRecPartition(IN long lHandle, IN CMS_CONNECT_PARSE_StoragerId &storager, IN CMS_CONNECT_PARSE_RecPartitionMask &partitionMask);

//获取硬盘工作配置
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetStoragerWorkAttr(IN long lHandle, IN CMS_CONNECT_PARSE_StoragerId &storager, OUT CMS_CONNECT_PARSE_StoragerWorkAttr &attr);
//设置硬盘工作配置
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetStoragerWorkAttr(IN long lHandle, IN CMS_CONNECT_PARSE_StoragerId &storager, IN CMS_CONNECT_PARSE_StoragerWorkAttr &attr);

//获取通道列表
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetStoragerChList(IN long lHandle, IN CMS_CONNECT_PARSE_StoragerId &storager, OUT CMS_CONNECT_PARSE_ChId* &channel, OUT int &iCount);
//添加通道到存储服务器
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_StoragerAddCh(IN long lHandle, IN CMS_CONNECT_PARSE_StoragerId &storager, IN CMS_CONNECT_PARSE_ChId* channel, IN int iCount);
//从存储服务器中删除通道
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_StoragerDeleteCh(IN long lHandle, IN CMS_CONNECT_PARSE_StoragerId &storager, IN CMS_CONNECT_PARSE_ChId* channel, IN int iCount);

//获取通道配额
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetStoragerQuota(IN long lHandle, IN CMS_CONNECT_PARSE_StoragerId &storager, OUT CMS_CONNECT_PARSE_StoragerQuota &quota);
//设置通道配额
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetStoragerQuota(IN long lHandle, IN CMS_CONNECT_PARSE_StoragerId &storager, IN CMS_CONNECT_PARSE_StoragerQuota &quota);

//获取录像计划
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetChRecPlan(IN long lHandle, IN CMS_CONNECT_PARSE_StoragerId &storager, IN CMS_CONNECT_PARSE_ChId &channel, OUT CMS_CONNECT_PARSE_ChRecPlan &plan);
//设置录像计划
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetChRecPlan(IN long lHandle, IN CMS_CONNECT_PARSE_StoragerId &storager, IN CMS_CONNECT_PARSE_ChId *channel, IN int iCount, IN CMS_CONNECT_PARSE_ChRecPlan &plan);

//获取报警IO状态
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetDeviceAlarmIO(IN long lHandle, IN CMS_CONNECT_PARSE_GetDeviceAlarmIO_Request &request, OUT bool &isOpen);
//设置报警IO开关
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetDeviceAlarmIO(IN long lHandle, IN CMS_CONNECT_PARSE_SetDeviceAlarmIO_Request &request);

//获取最大扩展通道路数
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetMaxExtendedChCount(IN long lHandle, OUT int count[]);

//获取临时密码
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetTempPassword(OUT char cTempPassword[MAX_NAME_LENGTH]);

//UTC功能
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_UtcCtrl(IN long lHandle, IN CMS_CONNECT_PARSE_UTC_Request &request);

//透传数据
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_TranData(IN long lHandle, IN char* deviceSerialNum, IN char* url, IN char* inBuffer, IN int inLen, OUT char* &outBuffer, OUT int &outLen);

//获取门禁设备列表
CMS_CONNECT_CLIENT_API int CMS_Conncet_Client_GetControlList(IN long lHandle, OUT CMS_CONNECT_PASER_AccessControl* &reply);

//添加门禁设备
CMS_CONNECT_CLIENT_API int CMS_Conncet_Client_AddController(IN long lHandle, IN CMS_CONNECT_PASER_AccessRequest &controlInfo);

//删除门禁设备
CMS_CONNECT_CLIENT_API int CMS_Conncet_Client_DelController(IN long lHandle, IN CMS_CONNECT_PASER_AccessRequest &controlInfo);

//控制门禁器开关门 
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SendControlCmd(IN long lHandle, IN CMS_CONNECT_PARSE_AccessControl_Cmd &controlCmd);

//开始搜索门禁设备 Protocal是需要搜索的CMS_CONNECT_PARSE_AccessControlType枚举类型或运算后的值
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_StartSearchAccess(IN long lHandle,IN CMS_CONNECT_PARSE_SearchAccess_Request eProtocal, IN CMS_CONNECT_CLIENT_SEARCHACCESS_CALLBACK pSearchCallback,void* pUser);

//停止搜索门禁设备
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_StopSearchAccess(IN long lHandle);

//获取门禁告警信息
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetAccessAlarmLogs(IN long lHandle, IN CMS_CONNECT_PARSE_SearchLog_Request &request, OUT int &iTotalCount, OUT CMS_CONNECT_PARSE_AccessLog *&pLogs, OUT int &iCount);

//获取门禁联动规则列表
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetAccessLinkageRule(IN long lHandle, OUT CMS_CONNECT_PARSE_AccessLinkageRuleParam *&pRuleParam, int &iRuleCount);
//获取门禁联动动作
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_GetAccessLinkageAction(IN long lHandle, IN CMS_CONNECT_PARSE_LinkageRule &request, CMS_CONNECT_PARSE_LinkageAction *&pAction, int &iActionCount);
//设置门禁联动规则
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetAccessLinkageRule(IN long lHandle, IN CMS_CONNECT_PARSE_SetAccessLinkageRule_Request &request);
//设置门禁联动规则是否启用
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SetAccessLinkageRuleEnabled(IN long lHandle, IN CMS_CONNECT_PARSE_SetLinkageRuleEnabled_Request &request);
//删除门禁联动规则
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_DelAccessLinkageRule(IN long lHandle, IN CMS_CONNECT_PARSE_LinkageRule &request);
//停止门禁联动上墙
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_StopAccessLinkageWall(IN long lHandle, IN CMS_CONNECT_PARSE_StopLinkageWall_Request &request);

/*********************************
* 新增配置字符串的读取和保存
* Add by sunx
* 2017.11.13
************************************/
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_SaveString(IN long lHandle, char* string, int length);
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_LoadString(IN long lHandle, char* &string, int &length);

//自定义透传接口,role的值从CmdType_UserRole起始
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_Post(IN long lHandle, char* method, char* req, int reqLength, char* &resp, int &respLength);


/*********************************************************************
*
*	释放内存，用于以下情况：
*	1、CMS_Connect_Client_SearchRecord返回的录像结果数组
*	2、CMS_Connect_Client_GetDevicesInArea返回的设备信息数组
*	3、CMS_Connect_Client_GetCruise返回的巡航信息数组
*	4、CMS_Connect_Client_GetAlarmOrder返回的告警订阅数组
*   5、CMS_Connect_Client_GetLogs返回的日志数组
*   6、CMS_Connect_Client_GetMapImage返回的二进制数据
*   7、CMS_Connect_Client_GetMapLayout返回的地图布局数组
*   8、CMS_Connect_Client_GetMaps返回的地图节点指针
*	9、CMS_Connect_Client_GetDeviceTree返回的节点指针
*   10、CMS_Connect_Client_GetWallGroups返回的分组节点指针
*   11、CMS_Connect_Client_GetWalls返回的电视墙数组
*   12、CMS_Connect_Client_GetDecoders返回的解码器数组
*   13、CMS_Connect_Client_GetWallLayout返回的电视墙布局数组
*   14、CMS_Connect_Client_GetWallRuntimeState返回的解码器运行状态数组
*   15、CMS_Connect_Client_GetUserAuth返回的用户权限指针
*   16、CMS_Connect_Client_GetLayoutInfo获取布局信息
*   17、CMS_Connect_Client_GetStoragerList获取的存储服务器数组
*   18、CMS_Connect_Client_GetStoragerDisk获取的磁盘数组
*   19、CMS_Connect_Client_GetStoragerChList获取的通道数组
*   20 CMS_Connect_Client_LoadString返回的string
*   21 CMS_Connect_Client_Post的resp
*
********************************************************************/
CMS_CONNECT_CLIENT_API int CMS_Connect_Client_ReleaseMemory(IN void *pBuffer);

#endif // CMS_CONNECT_CLIENT_H
