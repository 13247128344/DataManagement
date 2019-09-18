#pragma once
#include <QString>

//������������
typedef enum
{
	ivms_LinkageActionType_Map = 1,       //��ͼ
	ivms_LinkageActionType_PTZ,               //��̨
	ivms_LinkageActionType_PopImage,      //��ͼ��
	ivms_LinkageActionType_Record,        //¼��
	ivms_LinkageActionType_Capture,       //ץͼ
	ivms_LinkageActionType_Wall,              //��ǽ
}LinkageActionType;

//������̨����
typedef enum
{
	LinkagePtzType_GotoPreset = 1,      //ת��Ԥ�õ�
	LinkagePtzType_RunCruise,               //����Ѳ��
}LinkagePtzType;

//�û�����
typedef enum
{
	ivms_UserType_Admin = 1,			//����Ա
	ivms_UserType_Guest,				//��ͨ�û�
}UserType;

struct IVMS_CONNECT_PARSE_LinkageRuleParam
{
	QString ruleName;
	int connectParseAlarmType;
	QString serialNum;
	int paramInt;
	QString remarks;
	bool isEnabled;
};