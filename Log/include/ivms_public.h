#pragma once

#include <List>

#define MAX_SPLIT_COUNT 64
#define MAX_LINKAGEACTION_COUNT 6
#define MAX_LINKAGEACTION_PARAM_COUNT   8
#define MAX_STORAGER_CH_COUNT   256
#define MAX_NAME_LENGTH 64
#define MAX_DESCRIB_LENGTH 256
#define MAX_GROUP_CH_COUNT 16
#define MAX_DECODER_OUTPUT_COUNT 8

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
	DeviceType_IPC_AI,
	DeviceType_NVR_AI
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
	ProtocolType_Honeywell = 4096,   //霍尼维尔协议
	ProtocolType_P2P = 8192,         //P2P协议
	ProtocolType_I8H_AI = 16384         //智能设备I8H协议（I8H）
}CMS_CONNECT_PARSE_ProtocolType;

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

typedef enum
{
	AccessAlarmType_OpenDoor = 1,				//意外开门
	AccessAlarmType_Tamper = 2,					//防拆报警
	AccessAlarmType_StressPwd = 4,				//胁迫密码
	AccessAlarmType_StressFingerprint = 8,		//胁迫指纹
	AccessAlarmType_MagneticTimeOut = 16		//门磁超时
}CMS_CONNECT_PARSE_AccessAlarmType;

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
	AlarmType_Wire = 128           //跨线检测
}CMS_CONNECT_PARSE_AlarmType;

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

//#include "ivms_public_global.h"
//
//class IVMS_PUBLIC_EXPORT ivms_public
//{
//public:
//	ivms_public();
//};
