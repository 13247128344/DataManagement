#pragma once
#include <QString>

//联动动作类型
typedef enum
{
	ivms_LinkageActionType_Map = 1,       //地图
	ivms_LinkageActionType_PTZ,               //云台
	ivms_LinkageActionType_PopImage,      //弹图像
	ivms_LinkageActionType_Record,        //录像
	ivms_LinkageActionType_Capture,       //抓图
	ivms_LinkageActionType_Wall,              //上墙
}LinkageActionType;

//联动云台类型
typedef enum
{
	LinkagePtzType_GotoPreset = 1,      //转到预置点
	LinkagePtzType_RunCruise,               //启用巡航
}LinkagePtzType;

//用户类型
typedef enum
{
	ivms_UserType_Admin = 1,			//管理员
	ivms_UserType_Guest,				//普通用户
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