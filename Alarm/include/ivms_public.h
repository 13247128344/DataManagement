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

//�豸���ڵ�����
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



//�豸����
typedef enum
{
	DeviceType_DVR = 1,
	DeviceType_NVR,
	DeviceType_IPC,
	DeviceType_NVR_2,//NVR 2.0�豸
	DeviceType_Control,//�Ž���
	DeviceType_IPC_2,
	DeviceType_IPC_FISH,	//�������
	DeviceType_IPC_AI,
	DeviceType_NVR_AI
}CMS_CONNECT_PARSE_DeviceType;

//�豸Э������
typedef enum
{
	ProtocolType_Register = 1,	//����ע��
	ProtocolType_I8H = 2,			//HTTP��rtp over TCP
	ProtocolType_I8H_UDP = 3,		//HTTP��rtp over UDP,������豸ʱ��Ч
	ProtocolType_ONVIF = 4,			//Onvif
	ProtocolType_GB28181 = 8,		//GB/T28181
	ProtocolType_I8 = 16,			//I8
	ProtocolType_TUTK = 32,			//TUTK
	ProtocolType_Honey = 64,		//Honey
	ProtocolType_GoAhead = 128,		//Honey���汾ר�ã�I8H_GoAhead�豸�����д���ʽ��I8H����
	ProtocolType_GoAhead_UDP = 129,  //Honey���汾UDP
	ProtocolType_Taos = 256,			//���Э��
	ProtocolType_I9 = 512,			//I9Э��
	ProtocolType_AJ = 1024,			//Anjie
	ProtocolType_UMEYE = 2048,       //��ʦ��P2PЭ��
	ProtocolType_Honeywell = 4096,   //����ά��Э��
	ProtocolType_P2P = 8192,         //P2PЭ��
	ProtocolType_I8H_AI = 16384         //�����豸I8HЭ�飨I8H��
}CMS_CONNECT_PARSE_ProtocolType;

//֪ͨ��Ϣ����
typedef enum {
	NoticeType_AlarmMessage = 100,		//�澯��Ϣ����ӦCMS_CONNECT_PARSE_Alarm_Notice
	NoticeType_OnlineState,				//��������Ϣ����ӦCMS_CONNECT_PARSE_Online_Notice
	NoticeType_RecordState,				//¼��״̬����ӦCMS_CONNECT_PARSE_Record_Notice
	NoticeType_AddArea,					//�������򡣶�ӦCMS_CONNECT_PARSE_AddArea_Request
	NoticeType_DelArea,					//ɾ�����򡣶�ӦCMS_CONNECT_PARSE_DelArea_Request
	NoticeType_ModifyArea,				//�޸����򡣶�ӦCMS_CONNECT_PARSE_ModifyArea_Request
	NoticeType_AddDevice,				//����豸����ӦCMS_CONNECT_PARSE_AddDevice_Notice
	NoticeType_DelDevice,				//ɾ���豸����ӦCMS_CONNECT_PARSE_DelDevice_Request
	NoticeType_ModifyDevice,			//�޸��豸����ӦCMS_CONNECT_PARSE_ModifyDevice_Request
	NoticeType_SearchDevice,        //�����豸����ӦCMS_CONNECT_PARSE_SearchDeviceInfo
	NoticeType_AddCms,					//���CMS����ӦCMS_CONNECT_PARSE_CMSNodeָ��
	NoticeType_DelCms,					//�޸�CMS����Ӧ
	NoticeType_ModifyCms,				//�޸�CMS����Ӧ
	NoticeType_AddMap,					//���ӵ�ͼ����ӦCMS_CONNECT_PARSE_AddMap_Notice
	NoticeType_DelMap,					//ɾ����ͼ����ӦCMS_CONNECT_PARSE_Map
	NoticeType_AddGroup,				//��ӷ��顣��ӦCMS_CONNECT_PARSE_Group_Request
	NoticeType_DelGroup,				//ɾ�����顣��ӦCMS_CONNECT_PARSE_Group_Request
	NoticeType_GroupAddChannel,			//�������ͨ������ӦCMS_CONNECT_PARSE_ChannelInGroup
	NoticeType_GroupDelChannel,			//����ɾ��ͨ������ӦCMS_CONNECT_PARSE_ChannelInGroup
	NoticeType_AddDecoder,				//��ӽ���������ӦCMS_CONNECT_PARSE_DecoderNode
	NoticeType_DelDecoder,				//ɾ������������ӦCMS_CONNECT_PARSE_DelDecoder_Request
	NoticeType_ModifyDecoder,			//�޸Ľ���������ӦCMS_CONNECT_PARSE_ModifyDecoder_Notice
	NoticeType_SearchDecoder,        //��������������ӦCMS_CONNECT_PARSE_SearchDeviceInfo
	NoticeType_WallChangeGroup,     //����ǽ�л���ѯ���顣��ӦCMS_CONNECT_PARSE_WallChangeGroup_Notice
	NoticeType_DecoderAlarmState,   //����������״̬����ӦCMS_CONNECT_PARSE_DedoderAlarmState
	NoticeType_AddStorager,			//��Ӵ洢����������ӦCMS_CONNECT_PARSE_StoragerInfo
	NoticeType_DelStorager,			//ɾ���洢����������ӦCMS_CONNECT_PARSE_StoragerId
	NoticeType_ModifyStorager,		//�޸Ĵ洢����������ӦCMS_CONNECT_PARSE_StoragerInfo
	NoticeType_StoragerAddChannel,	//�洢���������ͨ��,��ӦCMS_CONNECT_PARSE_StoragerChNotice
	NoticeType_StoragerDelChannel,	//�洢������ɾ��ͨ��,��ӦCMS_CONNECT_PARSE_StoragerChNotice
	NoticeType_ModifyChName,			//�޸�ͨ����,��ӦCMS_CONNECT_PARSE_ModifyChName_Notice
	NoticeType_Decoder_OpenRealtime,   //��������Ԥ������ӦCMS_CONNECT_PARSE_DecoderOpenRealtime_Notice
	NoticeType_Decoder_CloseRealtime,   //�������ر�Ԥ������ӦCMS_CONNECT_PARSE_DecoderCloseRealtime_Notice
	NoticeType_Decoder_PollCtrl,               //��������ת���ơ���ӦCMS_CONNECT_PARSE_DecoderPollCtrl_Notice
	NoticeType_Decoder_OpenReplay,     //�������򿪻طš���ӦCMS_CONNECT_PARSE_DecoderOpenReplay_Notice
	NoticeType_Decoder_CloseReplay,    //�������رջطš���ӦCMS_CONNECT_PARSE_DecoderCloseReplay_Notice
	NoticeType_Decoder_AddGroup,	//��������������.��ӦCMS_CONNECT_PARSE_Decoder_Group
	NoticeType_Decoder_DelGroup,	//������ɾ������.��ӦCMS_CONNECT_PARSE_Decoder_DelGroup_Request
	NoticeType_Decoder_AddGroupCh,	//��������������.��ӦCMS_CONNECT_PARSE_Decoder_Group
	NoticeType_Decoder_DelGroupCh,	//��������������.��ӦCMS_CONNECT_PARSE_Decoder_Group
	NoticeType_AccessMessage,		//�Ž��澯��Ϣ����ӦCMS_CONNECT_PARSE_Access_Alarm_Notice
	NoticeType_AddAccess,			//����Ž�������ӦCMS_CONNECT_PASER_AccessControlInfo
	NoticeType_DelAccess,			//ɾ���Ž�������ӦCMS_CONNECT_PASER_AccessControlInfo
	NoticeType_ModifyAccess,		//�޸��Ž�������ӦCMS_CONNECT_PASER_AccessControlInfo
	NoticeType_SearchAccess,		//�����Ž��豸����ӦCMS_CONNECT_PARSE_SearchAccessInfo
	NoticeType_Decoder_ChangeScheme,	//������Ԥ����ѯ�л�,��ӦCMS_CONNECT_PARSE_Decoder_ChangeScheme_Notice
}CMS_CONNECT_PARSE_NoticeType;

typedef enum
{
	AccessAlarmType_OpenDoor = 1,				//���⿪��
	AccessAlarmType_Tamper = 2,					//���𱨾�
	AccessAlarmType_StressPwd = 4,				//в������
	AccessAlarmType_StressFingerprint = 8,		//в��ָ��
	AccessAlarmType_MagneticTimeOut = 16		//�Ŵų�ʱ
}CMS_CONNECT_PARSE_AccessAlarmType;

//�澯����
typedef enum
{
	AlarmType_Motion = 1,           //�ƶ����
	AlarmType_VideoLoss = 2,		//��Ƶ��ʧ
	AlarmType_Shelter = 4,			//��Ƶ�ڵ�
	AlarmType_AlarmIn = 8,			//�澯����
	AlarmType_Count = 16,           //�������
	AlarmType_Area = 32,            //������
	AlarmType_Object = 64,          //��Ʒ���
	AlarmType_Wire = 128           //���߼��
}CMS_CONNECT_PARSE_AlarmType;

//�豸���ڵ�
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
	char cSerialNum[MAX_NAME_LENGTH];	//���к�
	char cUserName[MAX_NAME_LENGTH];		//�û���
	char cPassword[MAX_NAME_LENGTH];		//����
	char cDeviceIP[MAX_NAME_LENGTH];		//IP
	int iDevicePort;		//�˿�
	CMS_CONNECT_PARSE_DeviceType eDeviceType;	//�豸����
	CMS_CONNECT_PARSE_ProtocolType eProtocolType;	//Э������
	int iChannelCount;		//ͨ������
	int iAlarmInCount;		//�澯�������
	int iAlarmOutCount;     //�澯�������
	int isOnline;			//�Ƿ�����
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
	char cSerialNum[MAX_NAME_LENGTH];	//���к�
	char cUserName[MAX_NAME_LENGTH];		//�û���
	char cPassword[MAX_NAME_LENGTH];		//����
	char cCMSIP[MAX_NAME_LENGTH];		//IP
	int iCMSPort;			//�˿�
	int isOnline;			//�Ƿ�����
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
	char cSerialNum[MAX_NAME_LENGTH];	//���к�
	int iChannelNo;			//ͨ����
	int isOnline;			//�Ƿ�����
	int isCMSRecord;		//�Ƿ���������¼��
	int isDeviceRecord;		//�Ƿ������豸¼��
	int isRecordRight;		//�Ƿ�������¼��Ȩ��
	int isPlaybackRight;	//�Ƿ��лط�Ȩ��
	int isIntercomRight;	//�Ƿ��жԽ�Ȩ��
	int iPtzLevel;			//��̨Ȩ�޵ȼ�
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
	char cSerialNum[MAX_NAME_LENGTH];	//���к�
	int iAlarmInNo;			//�澯�����
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
	char cSerialNum[MAX_NAME_LENGTH];	//���к�
	int iAlarmOutNo;			//�澯�����
};


//����豸֪ͨ
struct  CMS_CONNECT_PARSE_AddDevice_Notice
{
	char cAreaName[MAX_NAME_LENGTH];		//�豸������������
	CMS_CONNECT_PARSE_DeviceNode *pDevice;	//�豸�ڵ�ָ��
	~CMS_CONNECT_PARSE_AddDevice_Notice()
	{
		// 		delete pDevice;
	}
};

//�澯֪ͨ
typedef struct
{
	CMS_CONNECT_PARSE_AlarmType eAlarmType;		//�澯����
	char cSerialNum[MAX_NAME_LENGTH];						//�澯Դ�豸���к�
	int iParam;									//�澯�������澯����Ϊ�澯����ʱ��ʾ�澯����ţ�����Ϊͨ����
	int isStoped;								//0Ϊ�澯��ʼ��1Ϊ�澯����
	unsigned int timeUTC;						//ʱ��UTC
}CMS_CONNECT_PARSE_Alarm_Notice;

typedef struct
{
	CMS_CONNECT_PARSE_AccessAlarmType eAlarmType;		//�澯����
	char cSerialNum[MAX_NAME_LENGTH];						//�澯Դ�豸���к�
	int iParam;									//�澯�������澯����Ϊ�澯����ʱ��ʾ�澯����ţ�����Ϊͨ����
	int isStoped;								//0Ϊ�澯��ʼ��1Ϊ�澯����
	unsigned int timeUTC;						//ʱ��UTC
}CMS_CONNECT_PARSE_Access_Alarm_Notice;


//������֪ͨ
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//���кţ�ȫ0��ʾ��������������ʾ�豸���к�
	int isOnline;				//0Ϊ���ߣ�1Ϊ����
}CMS_CONNECT_PARSE_Online_Notice;



//¼��״̬�ı�֪ͨ
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//���кţ�ȫ0��ʾ��������������ʾ�豸���к�
	int iChannel;				//ͨ���ţ���1��ʼ
	int isCmsRecord;			//�Ƿ����Ķ�¼��
	int isDeviceRecord;			//�Ƿ��豸��¼��
}CMS_CONNECT_PARSE_Record_Notice;

//�����������
typedef struct
{
	char cParentName[MAX_NAME_LENGTH];		//���ڸ���������
	char cAreaName[MAX_NAME_LENGTH];		//��������
}CMS_CONNECT_PARSE_AddArea_Request;




//ɾ����������
typedef struct
{
	char cAreaName[MAX_NAME_LENGTH];	//��������
}CMS_CONNECT_PARSE_DelArea_Request;




//�޸���������
typedef struct
{
	char cOldName[MAX_NAME_LENGTH];		//��������
	char cNewName[MAX_NAME_LENGTH];		//����������
}CMS_CONNECT_PARSE_ModifyArea_Request;




//����豸����
typedef struct
{
	char cAreaName[MAX_NAME_LENGTH];		//������������
	CMS_CONNECT_PARSE_ProtocolType eProtocolType;	//Э������
	char cDevice[MAX_NAME_LENGTH];		//����ע��Э��Ϊ�豸���кţ�����Ϊ�豸IP
	int iDevicePort;		//�豸�˿ڣ�����ע��Э��ɲ���
	char cDeviceName[MAX_NAME_LENGTH];	//�豸��
	char cUserName[MAX_NAME_LENGTH];		//�豸�û���
	char cPassword[MAX_NAME_LENGTH];		//�豸����
}CMS_CONNECT_PARSE_AddDevice_Request;




//ɾ���豸����
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];	//�豸���к�
}CMS_CONNECT_PARSE_DelDevice_Request;





//�޸��豸����
typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];	//�豸���к�
	char cDeviceName[MAX_NAME_LENGTH];	//�豸��
	char cUserName[MAX_NAME_LENGTH];		//�豸�û���
	char cPassword[MAX_NAME_LENGTH];		//�豸����
}CMS_CONNECT_PARSE_ModifyDevice_Request;

typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//�豸���к�
	int iChannel;			//ͨ���ţ���1��ʼ
	char cName[MAX_NAME_LENGTH];	//������
}CMS_CONNECT_PARSE_ModifyChName_Notice;

typedef struct
{
	char cSerialNum[MAX_NAME_LENGTH];		//�豸���к�
	int iChannel;			//ͨ���ţ���1��ʼ
	char cName[MAX_NAME_LENGTH];	//������
}CMS_CONNECT_PARSE_ModifyChName_Request;

//#include "ivms_public_global.h"
//
//class IVMS_PUBLIC_EXPORT ivms_public
//{
//public:
//	ivms_public();
//};
