#ifndef __I8H_SDK_H__
#define __I8H_SDK_H__

#ifdef WIN32 
#include <windows.h>
#define I8H_SDK_API 	extern "C" __declspec(dllexport)
#define I8H_SDK_CALL	
#else
typedef unsigned int    	DWORD;
typedef unsigned int   		UINT;
typedef unsigned short  	WORD;
typedef unsigned short  	USHORT;
typedef int            		LONG;
typedef int 				BOOL;
typedef unsigned char		BYTE;
typedef unsigned int*  		LPDWORD; 
typedef void* 				LPVOID;
typedef void* 				HANDLE;

#ifndef TRUE
#define	TRUE			1
#endif

#ifndef FALSE
#define	FALSE 			0
#endif

#ifndef	NULL
#define	NULL 			0
#endif

#define CALLBACK 
#define I8H_SDK_API 	extern "C"
#define I8H_SDK_CALL	
#endif


//!宏定义
#define I8H_NAME_LEN			    						32  //!用户名长度
#define I8H_PASSWD_LEN			    						32  //!密码长度
#define I8H_SERIALNO_LEN		    						48  //!序列号长度
#define I8H_MACADDR_LEN			    						6   //!mac地址长度
#define I8H_MAX_PRESET										256 //!设备支持的云台预置点数 
#define I8H_MAX_TRACK										256 //!设备支持的云台轨迹数 
#define I8H_MAX_CRUISE										256 //!设备支持的云台巡航数 
#define I8H_CRUISE_MAX_PRESET_NUMS							32  //!一条巡航最多的巡航点 
#define I8H_MAX_CHANNUM			        					64  //!设备最大通道数
#define I8H_MAX_ALARMOUT									4
#define I8H_MAX_DISKNUM										24


	
/************************************************************************
			   全局错误码宏定义  
*************************************************************************/	
#define I8H_ERROR_CODE_NOERROR 								0	//!没有错误
#define I8H_ERROR_CODE_FAIL									1   //!失败
#define I8H_ERROR_CODE_PASSWORD_ERROR 						2	//!用户名密码错误
#define I8H_ERROR_CODE_NOENOUGHPRI 							3	//!权限不足
#define I8H_ERROR_CODE_NOINIT 								4	//!没有初始化
#define I8H_ERROR_CODE_HASINIT 	     						5	//!已经初始化
#define I8H_ERROR_CODE_ORDER_ERROR							6	//!调用次序错误
#define I8H_ERROR_CODE_PARAMETER_ERROR 						7  //!参数错误
#define I8H_ERROR_CODE_ALLOC_RESOURCE_ERROR					8  //!资源分配错误
#define I8H_ERROR_CODE_CALL3THAPI_ERROR						9	//!调用第三方接口错误
#define I8H_ERROR_CODE_CHAN_ERROR	 						10	//!通道号错误
#define I8H_ERROR_CODE_CHAN_NOTSUPPORT             			11 	//!通道不支持该操作
#define I8H_ERROR_CODE_OVER_MAXLINK 						12	//!连接到DVR的客户端个数超过最大
#define I8H_ERROR_CODE_VERSIONNOMATCH						13	//!版本不匹配
#define I8H_ERROR_CODE_NETWORK_FAIL							14   //!网络错误(包括连接 发送 接收等错误)
#define I8H_ERROR_CODE_OPENFILE_FAIL						15  //!打开文件出错
#define I8H_ERROR_CODE_UPGRADE_FAIL							16  //!DVR升级失败
#define I8H_ERROR_CODE_DATASERIALIZE_FAIL					17	//!数据序列化错误
#define I8H_ERROR_CODE_DATADESERIALIZE_FAIL					18	//!数据反序列化错误
#define I8H_ERROR_CODE_NOENOUGH_BUF							19	//!缓冲区太小
#define I8H_ERROR_CODE_USERNOTEXIST							20	//!用户不存在
#define I8H_ERROR_CODE_COMMAND_UNSUPPORT					21	//!命令不支持
#define I8H_ERROR_CODE_INVALID_HANDLE						22  //!无效句柄
#define I8H_ERROR_CODE_SERVER_FORBIDDEN						23  //!服务禁止
#define I8H_ERROR_CODE_CONNECT_SSL_ERROR					24  //!SSL连接错误
#define I8H_ERROR_CODE_OPTERATION_BUSY						25 //!操作忙


/************************************************************************
			   云台控制命令宏定义  
*************************************************************************/	
#define I8H_LIGHT_PWRON										2	//! 接通灯光电源 
#define I8H_WIPER_PWRON										3	//! 接通雨刷开关 
#define I8H_FAN_PWRON										4	//! 接通风扇开关 
#define I8H_HEATER_PWRON									5	//! 接通加热器开关 
#define I8H_AUX_PWRON1										6	//! 接通辅助设备开关 
#define I8H_AUX_PWRON2										7	//! 接通辅助设备开关 
#define I8H_SET_PRESET										8	//! 设置预置点 
#define I8H_CLE_PRESET										9	//! 清除预置点 

#define I8H_ZOOM_IN											11	//! 焦距以速度SS变大(倍率变大) 
#define I8H_ZOOM_OUT										12	//! 焦距以速度SS变小(倍率变小) 
#define I8H_FOCUS_NEAR      								13  //! 焦点以速度SS前调 
#define I8H_FOCUS_FAR       								14  //! 焦点以速度SS后调 
#define I8H_IRIS_OPEN       								15  //! 光圈以速度SS扩大 
#define I8H_IRIS_CLOSE      								16  //! 光圈以速度SS缩小 

#define I8H_TILT_UP											21	//! 云台以SS的速度上仰 
#define I8H_TILT_DOWN										22	//! 云台以SS的速度下俯 
#define I8H_PAN_LEFT										23	//! 云台以SS的速度左转 
#define I8H_PAN_RIGHT										24	//! 云台以SS的速度右转 
#define I8H_UP_LEFT											25	//! 云台以SS的速度上仰和左转 
#define I8H_UP_RIGHT										26	//! 云台以SS的速度上仰和右转 
#define I8H_DOWN_LEFT										27	//! 云台以SS的速度下俯和左转 
#define I8H_DOWN_RIGHT										28	//! 云台以SS的速度下俯和右转 
#define I8H_PAN_AUTO										29	//! 云台以SS的速度左右自动扫描 

#define I8H_ADD_CRUISE_ROUTE_POINT							30	//!添加巡航序列巡航点 
#define I8H_DEL_CRUISE_ROUTE_POINT							31	//!删除巡航序列巡航点
#define I8H_DEL_CRUISE_ROUTE								32	//!删除巡航序列
#define I8H_RUN_CRUISE_ROUTE								33	//!运行巡航序列
#define I8H_STOPRUN_CRUISE_ROUTE							34	//!停止运行巡航序列

#define I8H_START_TRACK										35	//!开始记录轨迹
#define I8H_STOP_TRACK										36	//!停止记录轨迹
#define I8H_RUN_TRACK										37  //!运行记录轨迹
#define I8H_GOTO_PRESET										39	//! 调用预置点 



/************************************************************************
			   回放控制命令宏定义   
*************************************************************************/	
#define I8H_PLAYBACK_PLAYPAUSE								1	//!暂停播放
#define I8H_PLAYBACK_PLAYRESTART							2	//!恢复播放
#define I8H_PLAYBACK_PLAYSTARTAUDIO							3	//!打开声音
#define I8H_PLAYBACK_PLAYSTOPAUDIO							4	//!关闭声音
#define I8H_PLAYBACK_SETSPEED								5	//!设置码流速度
#define I8H_PLAYBACK_PLAYSETTIME							6	//!按绝对时间定位,结构为I8H_TIME
#define I8H_PLAYBACK_ADDCHAN								7	//!回放添加通道
#define I8H_PLAYBACK_DELCHAN								8	//!回放删除通道



/************************************************************************
			 预览控制命令宏定义   
*************************************************************************/	
#define I8H_REALPLAY_ADDCHAN								1	//!添加通道到组,与打开预览效果一样,但是不单独打开连接,与之前打开的预览共用一个连接;同一设备的不同通道支持此操作,不同的设备不支持加组的功能
#define I8H_REALPLAY_DELCHAN								2	//!删除通道
#define I8H_REALPLAY_PLAYSTARTAUDIO							3	//!打开声音
#define I8H_REALPLAY_PLAYSTOPAUDIO							4	//!关闭声音



/************************************************************************
			   报警方式类型宏定义
*************************************************************************/	
#define I8H_COMM_ALARM										0x1100	//!报警信息主动上传
#define I8H_COMM_TRADEINFO									0x1500 	//!ATMDVR主动上传交易信息
#define I8H_COMM_IPCCFG			        					0x4001	//!设备IPC接入配置改变报警信息主动上传



/************************************************************************
			   操作异常类型(消息方式, 回调方式(保留))宏定义
*************************************************************************/	
#define I8H_EXCEPTION_EXCHANGE								0x8000	//!用户交互时异常
#define I8H_EXCEPTION_AUDIOEXCHANGE							0x8001	//!语音对讲异常
#define I8H_EXCEPTION_ALARM									0x8002	//!报警异常
#define I8H_EXCEPTION_PREVIEW								0x8003	//!网络预览异常
#define I8H_EXCEPTION_SERIAL								0x8004	//!透明通道异常
#define I8H_EXCEPTION_RECONNECT								0x8005	//!预览时重连
#define I8H_EXCEPTION_ALARMRECONNECT						0x8006	//!报警时重连
#define I8H_EXCEPTION_SERIALRECONNECT						0x8007	//!透明通道重连
#define I8H_SERIAL_RECONNECTSUCCESS 						0x8008	//!透明通道重连成功
#define I8H_EXCEPTION_PLAYBACK	        					0x8010	//!回放异常
#define I8H_EXCEPTION_DISKFMT	        					0x8011	//!硬盘格式化
#define I8H_EXCEPTION_PASSIVEDECODE     					0x8012 	//!被动解码异常
#define I8H_EXCEPTION_EMAILTEST            					0x8013 	//!邮件测试异常    
#define I8H_EXCEPTION_BACKUP               					0x8014 	//!备份异常
#define I8H_PREVIEW_RECONNECTSUCCESS      					0x8015 	//!预览时重连成功
#define I8H_ALARM_RECONNECTSUCCESS     						0x8016 	//!报警时重连成功
#define I8H_DEVICE_ONLINE     								0x8017 	//!设备上线成功
#define I8H_DEVICE_OFFLINE     								0x8018 	//!设备下线



/************************************************************************
			   预览回调函数数据类型宏定义
*************************************************************************/	
#define I8H_STREAMDATA_SYSHEAD								0x0001	//!系统头数据
#define I8H_STREAMDATA_STREAMDATA							0x0002	//!视频流数据（包括复合流和音视频分开的视频流数据）
#define I8H_STREAMDATA_AUDIOSTREAMDATA						0x0003	//!音频流数据
#define I8H_STREAMDATA_STD_VIDEODATA						0x0004	//!标准视频流数据
#define I8H_STREAMDATA_STD_AUDIODATA						0x0005	//!标准音频流数据



/************************************************************************
			   设备型号宏定义
*************************************************************************/	
#define I8H_PRODUCT_DVR										0x0001
#define I8H_PRODUCT_NVR										0x0002
#define I8H_PRODUCT_IPC										0x0003
#define I8H_PRODUCT_DEC										0x0004
#define I8H_PRODUCT_NVR2									0x0005


/************************************************************************
			   设备软件版本宏定义
*************************************************************************/	
#define I8H_DVR_GO_AHEAD									0x0001
#define I8H_NVR1_GO_AHEAD									0x0002
#define I8H_IPC_GO_AHEAD									0x0003
#define I8H_DEC_GO_AHEAD									0x0004
#define I8H_NVR2_GO_AHEAD									0x0005
#define I8H_DVR_NGINX										0x0006
#define I8H_NVR1_NGINX										0x0007
#define I8H_IPC_NGINX										0x0008
#define I8H_DEC_NGINX										0x0009
#define I8H_NVR2_NGINX										0x000A
#define I8H_IPC_JULONG_NGINX								0x000B
#define I8H_IPC_OVFS_NGINX									0x000C
#define I8H_IPC_FISHEYE_NGINX								0x000D
#define I8H_IPC_AI                                          0x000E
#define I8H_NVR_AI                                          0x000F

/************************************************************************
			   报警类型宏定义
*************************************************************************/	
#define I8H_ALARMTYPE_ALARMIN 								0	//!信号量报警
#define I8H_ALARMTYPE_DISKFULL 								1	//!硬盘满
#define I8H_ALARMTYPE_VIDEOLOSS								2	//!信号丢失
#define I8H_ALARMTYPE_MOTION								3	//!移动侦测
#define I8H_ALARMTYPE_DISKNOFORMAT							4	//!硬盘未格式化
#define I8H_ALARMTYPE_DISKIOERROR							5	//!读写硬盘出错
#define I8H_ALARMTYPE_MASK									6	//!遮挡报警
#define I8H_ALARMTYPE_VIDEOSTANDARDEXCEPTION				7	//!制式不匹配
#define I8H_ALARMTYPE_ILLEGEACCESS							8	//!非法访问
#define I8H_ALARMTYPE_VIDEOEXCEPTION						9	//!视频信号异常
#define I8H_ALARMTYPE_RECEXCEPTION							10	//!录像异常

#define I8H_ALARMTYPE_RETICLEDISCONNECT						20	//!网线断
#define I8H_ALARMTYPE_IPCONELICT							21	//!IP冲突
#define I8H_ALARMTYPE_IVS_COUNTWIRE							22	//!计数检测
#define I8H_ALARMTYPE_IVS_DETECTWIRE						23	//!过线检测
#define I8H_ALARMTYPE_IVS_DETECTREGION						24	//!区域检测
#define I8H_ALARMTYPE_IVS_OBJECTREGION						25	//!物品检测
#define I8H_ALARMTYPE_IVS_SOUNDALARM						26	//!异常声音报警
#define I8H_ALARMTYPE_IVS_PLATEDETECT_ALARM					27	//!车牌识别
#define I8H_ALARMTYPE_IVS_FACEDETECT_ALARM					28	//!人脸检测
#define I8H_ALARMTYPE_IVS_FIREDETECT_ALARM					29	//!火焰检测
#define I8H_ALARMTYPE_IVS_VIDEODIAGNOSE_COLOR				30	//!视频诊断_偏色
#define I8H_ALARMTYPE_IVS_VIDEODIAGNOSE_BRIGHT				31	//!视频诊断_偏亮
#define I8H_ALARMTYPE_IVS_VIDEODIAGNOSE_BLUR				32	//!视频诊断_模糊 
#define I8H_ALARMTYPE_IVS_MOTION_DETECT						33	//!智能移动侦测
#define I8H_ALARMTYPE_IVS_VIDEODIAGNOSE_DARK				34	//!视频诊断_偏暗
#define I8H_ALARMTYPE_IVS_VIDEODIAGNOSE_VI_LOST				35	//!视频诊断_视频丢失
#define I8H_ALARMTYPE_IVS_PERSONDETECT_ALARM				36	//!人形检测报警


typedef enum
{
	I8H_EVENT_MAIN_TYPE_UNKNOW = 0x0,        //未知主类型(代码中不应该出现此类型)
	I8H_EVENT_MAIN_TYPE_ANY,                 //任意主类型

	I8H_EVENT_CH_EVENT,						 //通道相关事件                         
	I8H_EVENT_DISK_EVENT,					 //硬盘相关事件         
	I8H_EVENT_NET_EVENT,                     //网络相关事件      
	I8H_EVENT_ALARM_EVENT,                   //报警相关事件   

	I8H_EVENT_MAIN_MAX,                      //事件主类型最大值，代码中不应该出现此类型      
}I8H_EVENT_MAIN_TYPE;


typedef enum 
{
	I8H_EVENT_SUB_TYPE_UNKNOW = 0x0,               
	I8H_EVENT_SUB_TYPE_ANY,                                 

	/*通道子事件*/
	I8H_EVENT_MD,                             //移动侦测
	I8H_EVENT_OD,                             //视频遮挡
	I8H_EVENT_VIDEO_LOST,                     //视频丢失
	I8H_EVENT_SMART_OBJECT_COUNT,             //目标计数
	I8H_EVENT_SMART_CROSS_LINE,               //跨线检测
	I8H_EVENT_SMART_REGION_DETECT,            //区域检测 
	I8H_EVENT_SMART_GOODS_DETECT,             //物品检测
	I8H_EVENT_SMART_SCENE_CHNAGE,             //情景变换
	I8H_EVENT_SMART_SOUND_DETECT,             //声音检测
	I8H_EVENT_SMART_FIRE_DETECT,              //火灾检测
	I8H_EVENT_SMART_FACE_DETECT,              //人脸检测
	I8H_EVENT_SMART_CAR_PLATE_DETECT,         //车牌检测
	I8H_EVENT_SMART_CAR_PLATE_BLACK,          //车牌黑名单
	I8H_EVENT_SMART_CAR_PLATE_WHITE,          //车牌白名单    
	I8H_EVENT_SMART_VIDEO_DIAGNOSE,           //视频诊断

	/*磁盘子事件*/
	I8H_EVENT_DISK_FULL,                      //磁盘满
	I8H_EVENT_DISK_LOST,                      //磁盘丢失
	I8H_EVENT_DISK_ERROR,                     //磁盘错误
	I8H_EVENT_DISK_DISCONNECT,                //磁盘掉线(网络磁盘)
	I8H_EVENT_DISK_READ_ONLY,                 //磁盘只读
	I8H_EVENT_DISK_RAID_DEGRADED,             //磁盘降级(RAID)
	I8H_EVENT_DISK_RAID_FAULT,                //磁盘下线(RAID)
	I8H_EVENT_DISK_SMART_ERROR,               //磁盘Smart信息错误

	/*网络子事件*/
	I8H_EVENT_NET_DISCONNECT,                 //网络断开
	I8H_EVENT_NET_IP_CONFLICT,                //IP冲突

	/*报警子事件*/
	I8H_EVENT_LOCAL_ALRAM_IN,                 //本地报警输入
	I8H_EVENT_REMOTE_ALARM_IN,                //远端报警输入
	
	I8H_EVENT_SMART_PERSON_DETECT,              //人形检测

	I8H_EVENT_SUB_MAX,                        //事件子类型最大值,代码中不应该出现此子类型
}I8H_EVENT_SUB_TYPE;


typedef enum 
{
	I8H_EVENT_THIRD_TYPE_UNKNOW = 0x0,	      //未知三级类型
	I8H_EVENT_THIRD_TYPE_ANY,                 //任意子类型

	/*声音报警三级事件*/
	I8H_EVENT_SMART_BABY_CRY,                 //婴儿哭声
	I8H_EVENT_SMART_SCREAM,                   //尖叫声
	I8H_EVENT_SMART_GUNSHOTS,                 //枪声
	I8H_EVENT_SMART_EXPLOSION,                //爆炸声

	/*视频诊断三级事件*/
	I8H_EVENT_SMART_VIDEO_DIM,                //视频昏暗
	I8H_EVENT_SMART_VIDEO_BRIGHT,             //视频过亮
	I8H_EVENT_SMART_VIDEO_FRINGE,             //视频条纹
	I8H_EVENT_SMART_VIDEO_SNOW,               //视频雪花
	I8H_EVENT_SMART_VIDEO_OD,                 //视频遮挡
	I8H_EVENT_SMART_VIDEO_FREEZE,             //视频冻结
	I8H_EVENT_SMART_VIDEO_LOST,               //视频丢失
	I8H_EVENT_SMART_VIDEO_OBSCURE,            //视频模糊            
	I8H_EVENT_SMART_VIDEO_SHAKE,              //视频抖动
	I8H_EVENT_SMART_VIDEO_COLOR_CAST,	      //视频偏色
	I8H_EVENT_SMART_VIDEO_PTZ_ABNORMAL,		  //PTZ异常

	I8H_EVENT_THIRD_MAX,                      //事件三级类型最大值,代码中不应该出现此类型
}I8H_EVENT_THIRD_TYPE;



/************************************************************************
			   广播修改操作类型
*************************************************************************/	
typedef enum MODIFY_CMD
{
	I8H_MODIFY_IPADDR = 0x0001,
	I8H_MODIFY_GOOLINK,
	I8H_MODIFY_UMEYE,
}I8H_MODIFY_COMMAND ;


typedef enum 
{
	//!主码流帧类型
	I8H_PktError=0x0,
	I8H_PktIFrames=0x01,
	I8H_PktAudioFrames=0x08,
	I8H_PktPFrames=0x09,
	I8H_PktBBPFrames=0x0a,
	I8H_PktMotionDetection=0x0b,
	I8H_PktDspStatus=0x0c,
	I8H_PktOrigImage=0x0d,
	I8H_PktSysHeader=0x0e,
	I8H_PktBPFrames=0x0f,
	I8H_PktSFrames=0x10,

	//!子码流帧类型
	I8H_PktSubSysHeader=0x11,
	I8H_PktSubIFrames=0x12,
	I8H_PktSubPFrames=0x13,
	I8H_PktSubBBPFrames=0x14,

	//!智能分析信息帧类型
	I8H_PktVacEventZones=0x15,
	I8H_PktVacObjects=0x16,

	//!第三码流帧类型
	I8H_PktThirdSysHeader=0x17,
	I8H_PktThirdIFrames=0x18,
	I8H_PktThirdPFrames=0x19,
	I8H_PktThirdBBPFrames=0x1a,

	//!智能检测帧类型
	I8H_PktSmartIFrames=0x1b,
	I8H_PktSmartPFrames=0x1c,

	// APP metedata帧.
	I8H_PktAppFrames=0x20,

	// I8HComb 帧
	I8H_PktI8HCombFrames=0x21,
}I8H_FrameType;



/************************************************************************
						视频帧编码类型
*************************************************************************/	
typedef enum 
{
	I8H_H264 = 1,
	I8H_MJPEG ,
	I8H_H265 ,   
	I8H_SVAC ,
	I8H_VIDEO_UNKNOWN ,
}I8H_VideoCodecType;


/************************************************************************
						音频帧编码类型
*************************************************************************/	
typedef enum 
{
	I8H_G711A = 1,
	I8H_G711U ,
	I8H_AUDIO_UNKNOWN ,
}I8H_AudioCodecType;


/************************************************************************
			  Nvr2.0设备录像类型
*************************************************************************/	
typedef enum
{
	I8H_REC_TRIG_NONE = 0,

	I8H_REC_TRIG_BY_REGULAR		= 0x01,		//常规录像
	I8H_REC_TRIG_BY_MD 			= 0x02,		//移动侦测录像
	I8H_REC_TRIG_BY_AI 			= 0x04,		//报警录像
	I8H_REC_TRIG_BY_COUNTER    = 0x08,
	I8H_REC_TRIG_BY_WIRE       = 0x10, 
	I8H_REC_TRIG_BY_REGION     = 0x20,
	I8H_REC_TRIG_BY_OBJECT     = 0x40,
	I8H_REC_TRIG_BY_SCENCE		= 0x80,		//场景突变录像
	I8H_REC_TRIG_BY_SOUND		= 0x100,	//声音告警录像
	I8H_REC_TRIG_BY_FIRE    	= 0x200,	//火灾检测录像
	I8H_REC_TRIG_BY_FACE    	= 0x400,	//人脸检测录像
	I8H_REC_TRIG_BY_PLATE    	= 0x800,	//车牌检测录像
	/*****如果新增加录像类型，记得同步增加到I8H_REC_TRIG_BY_ALL中去哦********/

	I8H_REC_TRIG_BY_PRE = I8H_REC_TRIG_NONE,	//预录
	//对于类型的全部，最好不要用0xFFFFFFFF来处理了，增加一种类型，就修改一下全部的定义，这样用户查询的时候，选择全部 + 同时满足 的时候才能查得到
	I8H_REC_TRIG_BY_ALL = I8H_REC_TRIG_BY_REGULAR\
	| I8H_REC_TRIG_BY_MD\
	| I8H_REC_TRIG_BY_AI\
	| I8H_REC_TRIG_BY_COUNTER\
	| I8H_REC_TRIG_BY_WIRE\
	| I8H_REC_TRIG_BY_REGION\
	| I8H_REC_TRIG_BY_OBJECT\
	| I8H_REC_TRIG_BY_SCENCE\
	| I8H_REC_TRIG_BY_SOUND\
	| I8H_REC_TRIG_BY_FIRE\
	| I8H_REC_TRIG_BY_FACE\
	| I8H_REC_TRIG_BY_PLATE,
}I8H_REC_TRIG_TYPE;


/************************************************************************
			   获取配置和设置配置的宏定义
*************************************************************************/

typedef enum
{
	I8H_SET_ENABLE_ALARM_CFG = 0x0001,
	
	I8H_SET_TIME_CFG = 0x1000,
	
	I8H_GET_TIME_CFG = 0x2000,
	
}I8H_CONFIG_CMD ;



/************************************************************************
			   SDK初始化参数
*************************************************************************/	
typedef struct
{
	BOOL bAsync ;
	BYTE byKeyPath[256] ;
	DWORD dwUnicastSTX ;
	DWORD dwUnicastETX ;
	BYTE  byEnableHeartBeat ;
	BYTE  byManageMem ; //是否自己管理并释放RTSP的内存,NVR2.0内部专用,外部对接(设置为0即可)请勿使用  0:否 1:是
	BYTE  byCaptureJPEGIntervalTime ;//!JPEG抓图间隔时间(单位:秒)
	BYTE byRes[117] ;	
}I8H_INIT_PARAM, *LPI8H_INIT_PARAM ;


/************************************************************************
			   设备相关参数结构定义
*************************************************************************/	

/************************************************************************
			   设备基本参数信息
*************************************************************************/	
typedef struct
{
	BYTE bySerialNumber[I8H_SERIALNO_LEN];					//!序列号
	WORD wAlarmInNum ;										//!报警输入总数
	WORD wAlarmOutNum ;										//!报警输出总数
	WORD wDiskNum ;											//!硬盘总数
	WORD wDVRType ;											//!设备类型 1-DVR 2-NVR 3-IPC 4-DEC 5-NVR2.0
	WORD wChanNum ;											//!视频通道总数
	WORD wStartChan ;										//!视频起始通道号
	WORD wAudioChanNum ;									//!语音通道总数
	WORD wZeroChanNum ;										//!零通道总数
	DWORD dwSupport ;										//!能力,位与结果0-表示不支持 1-表示支持
															//!dwSupport & 0x01 表示是否支持智能搜索
															//!dwSupport & 0x02 表示是否支持支持备份
															//!dwSupport & 0x04 表示是否支持压缩参数能力获取
															//!dwSupport & 0x08 表示是否支持多网卡
															//!dwSupport & 0x10 表示是否支持远程SADP															
	BYTE byVer; 											//!1:DVR_GO_AHEAD    2:NVR1.0_GO_AHEAD   3:IPC_GO_AHEAD   4:DEC_GO_AHEAD  5:NVR2.0_GO_AHEAD   6:DVR_NGINX    7:NVR1.0_NGINX   8:IPC_NGINX  9:DEC_NGINX 10:NVR2.0_NGINX 11:I8H_IPC_JULONG_NGINX 12:I8H_IPC_OVFS_NGINX 13:I8H_IPC_FISHEYE_NGINX 14:I8H_IPC_AI 15:
	BYTE byRes[63];											//!保留
}I8H_DEVICEINFO, *LPI8H_DEVICEINFO;


/************************************************************************
				预览参数信息
*************************************************************************/	
typedef struct
{
	LONG lChannel ; 		//!bit0~bit15:通道号  bit28~bit31:智能流类型 第一位:表示获取音视频流 第二位:表示获取智能流 第三位:保留 第四位:保留
	LONG lLinkMode ;		//!Bit0-Bit7   表示码流连接方式 0-TCP连接方式 1-UDP连接方式 2-组播方式
							//!Bit8-Bit15  表示码流类型 0-主码流 1-子码流 2-主子码流 
							//!Bit16-Bit31 表示Socket缓冲区,为0表示使用默认值(64kb),单位kb
	char* lpMultiCastIP ;	//!多播组地址
}I8H_CLIENTINFO, *LPI8H_CLIENTINFO;


/************************************************************************
				时间参数信息
*************************************************************************/	
typedef struct 
{
	WORD wYear ;		//!年
	WORD wMonth ;		//!月
	WORD wDay ;			//!日
	WORD wHour ;		//!时
	WORD wMinute ;		//!分
	WORD wSecond ;		//!秒
	WORD wZoneTime ;	//!时区 如:东八区 wZoneTime = 8 西八区 wZoneTime = -8  
	WORD wRes ;			//!保留
}I8H_TIME, *LPI8H_TIME;


/************************************************************************
				巡航点参数信息
*************************************************************************/	
typedef struct 
{
	BYTE byPresetNo;			//!预置点
	BYTE byDWell;				//!停留时间
	BYTE bySpeed;				//!速度
	BYTE byReserve;				//!保留
}I8H_CRUISE_POINT, *LPI8H_CRUISE_POINT;

typedef struct 
{
	I8H_CRUISE_POINT struCruisePoint[32];	//!最大支持32个巡航点
}I8H_CRUISE_RET, *LPI8H_CRUISE_RET;


/************************************************************************
				录象文件查找条件结构信息
*************************************************************************/	
//!非2.0的设备使用此结构体
typedef struct 
{
	WORD wChannel ;				//!通道号									
	WORD wFileType ;			//!录像文件类型 0xFF-全部 0-定时录像 1-移动侦测 2-报警触发 3-报警|移动侦测 4-报警&移动侦测 5-命令触发 6-手动录像
	I8H_TIME struStartTime ;	//!文件查询开始时间	
	I8H_TIME struStopTime ;		//!文件查询结束时间
	WORD wRes[16] ; 
}I8H_FILECOND, *LPI8H_FILECOND;



//!2.0的设备使用此结构体
typedef struct 
{
	WORD wChannel ;				//!通道号		
	WORD wIsAnd;				//0:任意满足, 1:同时满足;NVR2.0的设备需要填写
	DWORD wFileType ;			//!录像文件类型NVR2.0的设备需要填写,其他设备无需填写,具体的设备型号参见   设备基本参数信息,具体参见I8H_REC_TRIG_TYPE															
	I8H_TIME struStartTime ;	//!文件查询开始时间	
	I8H_TIME struStopTime ;		//!文件查询结束时间								
	WORD wRes[14] ; 
}I8H_FILECONDV2, *LPI8H_FILECONDV2;



/************************************************************************
				录象文件参数结构信息
*************************************************************************/	
typedef struct 
{
	char szFileName[128] ;  	//!文件名
	I8H_TIME struStartTime ;	//!文件开始时间
	I8H_TIME struStopTime ;		//!文件结束时间
	DWORD dwFileSize ;		//!文件大小
	WORD wFileType ;		//!文件类型
	WORD wRes[15] ;			//!保留		
	DWORD dwFileType ;		//!文件类型(wFileType无法正常表示其他类型,所以扩展四个字节来描述)
}I8H_FINDDATA,*LPI8H_FINDDATA;


/************************************************************************
				报警上传参数结构信息
*************************************************************************/	
//typedef struct _tagAlarmInfo
//{
//	DWORD dwAlarmType ;			//!报警类型
//	WORD wParam ;				//!报警关联参数
//	WORD wState ;				//!第15位表示报警开关状态,置1表示报警开状态,置0表示报警关状态;	
//	DWORD dwTimeStamp ;			//!报警时间戳(取设备本地时间(单位:秒))
//}I8H_ALARMINFO, *LPI8H_ALARMINFO ;


typedef struct _tagAlarmInfov2
{
	DWORD dwMainAlarmType ;			//!报警主类型
	DWORD dwSubAlarmType ;			//!报警子类型
	DWORD dwThirdAlarmType ;	    //!报警三级类型
	BYTE *lpBuffer ;			    //!报警描述
	WORD wSize ;				    //!描述的字符长度
	WORD wState ;				    //!第15位表示报警开关状态,置1表示报警开状态,置0表示报警关状态;	
	DWORD dwTimeStamp ;			    //!报警时间戳(取设备本地时间(单位:秒))
}I8H_ALARMINFO_V2, *LPI8H_ALARMINFO_V2 ;


/************************************************************************
				搜索设备参数结构信息
*************************************************************************/	
typedef struct
{
	char szIP[16];
	char szMask[16];
	char szGateWay[16];
	char szDns1[16];
	char szDns2[16];
	BYTE byMacAddr[I8H_MACADDR_LEN];
	BYTE byRes[14];
}I8H_DEV_NET_INFO,*LPI8H_DEV_NET_INFO ;

typedef struct
{
	I8H_DEV_NET_INFO struNetInfos[3];			//!设备网络参数信息 0-eth0 1-wifi 2-3G
	WORD wPorts[4];								//!0-私有监听端口 1-Http监听端口 2-Rtsp监听端口 3-保留
	BYTE bySerialNo[I8H_SERIALNO_LEN];			//!设备序列号	
	char szName[I8H_NAME_LEN];					//!设备用户登录名
	char szPwd[I8H_PASSWD_LEN];					//!设备用户登录密码
	char szDeviceType[32];						//!设备类型 如:DVR-04 DVR-08 DVR-16 NVR-04 NVR-08 NVR-16 IPC
	DWORD dwSoftwareVersion;					//!软件版本号,高16位是主版本,低16位是次版本
	DWORD dwSoftwareBuildDate;					//!软件生成日期,0xYYYYMMDD
	BYTE byOldPrograms ; 						//!针对解码器程序,
	BYTE byDeviceModel[16] ;					//!设备型号
 	BYTE byI8Valid:1;       					//!bit0:I8有效,服务状态未启用,则按老版本处理
	BYTE byI8Status:1;       					//!bit1:I8服务,状态启用时,服务状态有效,1-启用
	BYTE byOnvifValid:1;       					//!bit2:ONVIF 服务
	BYTE byOnvifStatus:1;    					//!bit3:ONVIF服务
	BYTE byRTSPValid:1;       					//!bit4:RTSP 服务
	BYTE byRTSPStatus:1;    					//!bit5:RTSP服务
	BYTE byRTMPValid:1;      					//!bit6:RTMP 服务
	BYTE byRTMPStatus:1;   						//!bit7:RTMP服务
	BYTE bI8S_ServerValid:1;       				//!bit8:I8S 服务
	BYTE bI8S_ServerStatus:1;       			//!bit9:I8S服务
	BYTE bGB28181_ServerValid:1;       			//!bit10:GB28181 服务
	BYTE bGB28181_ServerStatus:1;       		//!bit11:GB28181服务
	BYTE bWebApi_ServerValid:1;       			//!bit12:WebApi 服务
	BYTE bWebApi_ServerStatus:1;       			//!bit13:WebApi服务状态
	BYTE bWebNginx_ServerValid:1;       		//!bit14:WebApi Nginx服务
	BYTE bWebNginx_ServerStatus:1;       		//!bit15:WebApi Nginx服务状态
	BYTE bOvfs_IPC:1;       					//!bit16:是否为OVFS架构 
	BYTE bT8S_ServerValid:1;       				//!bit17:是否为T8S的OVFS架构 
	BYTE bT8S_ServerStatus:1;       			//!bit18:是否为T8S的OVFS架构 
	BYTE bFaceValid:1;							//!bit19:是否支持人脸识别
	BYTE bRes:4;       							//!bit3~bit7:保留
	BYTE byRes[4] ;	
}I8H_DEV_NODE,*LPI8H_DEV_NODE ;


/************************************************************************
				通道添加删除结构信息
*************************************************************************/	
typedef struct
{
	BYTE byStreamType ;
	BYTE byAudioFlag ;
	WORD wChannel ;
	BYTE byRes[8] ;
}I8H_CHANNEL_INFO,*LPI8H_CHANNEL_INFO ;


/************************************************************************
				录像回放参数
*************************************************************************/
typedef struct
{
	WORD wChannel ;					  //!通道号,默认起始通道为1
	WORD wStreamType ;				  //!码流类型 0-主码流  1-子码流
	WORD wLinkMode ;				  //!连接模式
	WORD wIsAnd;					  //!0:任意满足,1:同时满足;NVR2.0的设备需要填写
	DWORD dwFileType ;				  //!录像文件类型NVR2.0的设备需要填写,其他设备无需填写,具体的设备型号参见   设备基本参数信息,具体参见I8H_REC_TRIG_TYPE															
	DWORD dwSelfClean ;				  //!bit0:是否启用用户名和密码验证 bit1:是否手动清除内存
	DWORD dwBuffSize ;				  //!socket缓冲区大小,单位字节
	BYTE byUserName[I8H_NAME_LEN] ;	  //!用户名
	BYTE byPassWord[I8H_PASSWD_LEN] ; //!密码
	I8H_TIME struStartTime ;		  //!文件查询开始时间	
	I8H_TIME struStopTime ;			  //!文件查询结束时间	
	BYTE byReplayModel ;			  //!0:普通速度回放,1:最快速度回放
	BYTE byRes[27] ;				  //!预留
}I8H_PLAYBACK_COND,*LPI8H_PLAYBACK_COND ;


/************************************************************************
				回调函数定义
*************************************************************************/	
//!搜索回调函数
typedef void (CALLBACK *fDiscoveryCallBack)(LPI8H_DEV_NODE lpDev, LPVOID lpUser) ; 

//!异常消息回调函数
typedef void (CALLBACK *fExceptionCallBack)(DWORD dwType, HANDLE hUserId, HANDLE hHandle, LPVOID lpUser) ; 

//!报警信息回调函数 lCommand 第31位置1,则表示lpAlarmInfo需要调用I8H_SDK_FreeMemory释放内存;置0,则表示不需要调用I8H_SDK_FreeMemory释放内存
typedef void (CALLBACK *fAlarmDataCallBack)(HANDLE hUserId, HANDLE hAlarmHandle, LONG lCommand, LPVOID lpAlarmInfo, DWORD dwAlarmInfoLen, LPVOID lpUser) ; 

//!设备报警信息/状态信息回调函数(扩展回调 1.硬盘状态 2.报警信息 3.录像状态)  
typedef void (CALLBACK *fAlarmDataCallBackV2)(BYTE *lpBuffer, DWORD dwBufferSize, LPVOID lpUser) ; 

//!报警信息回调函数 lCommand 第31位置1,则表示lpAlarmInfo需要调用I8H_SDK_FreeMemory释放内存;置0,则表示不需要调用I8H_SDK_FreeAlarm释放内存
typedef void (CALLBACK *fAlarmDataCallBackV3)(HANDLE hUserId, HANDLE hAlarmHandle, LONG lCommand, LPVOID lpAlarmInfo, DWORD dwAlarmInfoLen, LPVOID lpUser) ; 

//!设备RTSP报警原始信息透传回调函数(Onvif格式的XML消息)  
typedef void (CALLBACK *fTransAlarmCallBack)(HANDLE hUserId, BYTE *lpBuffer, DWORD dwBufferSize, LPVOID lpUser) ; 

//!流数据回调函数  dwOption:Bit0~7:表示码流类型 0-主码流 1-子码流 Bit8~15:编码类型 Bit16~31:表示通道号
typedef void (CALLBACK *fStreamDataCallBack)(HANDLE hHandle, DWORD dwOption, DWORD dwDataType, BYTE *lpBuffer, DWORD dwBufferSize, LPVOID lpUser) ; 

//!标准H264数据回调函数  dwOption:Bit0~7:表示码流类型 0-主码流 1-子码流 Bit8~15:编码类型 Bit16~31:表示通道号  dwDataType:Bit16-31表示码率 Bit8-15表示帧率 Bit0-7表示帧类型
typedef void (CALLBACK *fStandardStreamDataCallBack)(HANDLE hHandle, DWORD dwOption, DWORD dwDataType, unsigned long long AbsTimeStamp, unsigned long long RelTimeStamp, BYTE *lpBuffer, DWORD dwBufferSize, LPVOID lpUser) ; 

//!标准H264数据回调函数V2  dwOption:Bit0~7:表示码流类型 0-主码流 1-子码流 Bit8~15:编码类型 Bit16~31:表示通道号  dwDataType:Bit16-31表示码率 Bit8-15表示帧率 Bit0-7表示帧类型
typedef void (CALLBACK *fStandardStreamDataCallBackV2)(HANDLE hHandle, DWORD dwOption, DWORD dwDataType, DWORD dwFrameTime, DWORD dwFrameTickCount, DWORD dwRelTimeStamp, BYTE *lpBuffer, DWORD dwBufferSize, LPVOID lpUser) ; 

//!语音对讲数据回调函数
typedef void (CALLBACK *fVoiceDataCallBack)(HANDLE hVoiceHandle, BYTE *lpBuffer, DWORD dwBufferSize, BYTE byAudioFlag, LPVOID lpUser) ; 

//!语音对讲数据回调函数(扩展回调)
typedef void (CALLBACK *fVoiceDataCallBackV2)(HANDLE hVoiceHandle, BYTE *lpBuffer, DWORD dwBufferSize, DWORD dwAudioFlag, LPVOID lpUser) ; 


//!SDK接口函数声明
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_Init(BOOL bAsync);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_Initv2(LPI8H_INIT_PARAM lpParam);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_Cleanup( );

I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_SetExceptionCallBack(fExceptionCallBack fpExceptionCallBack, LPVOID lpUser);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_SetAlarmDataCallBack(fAlarmDataCallBack fpMessageCallBack, LPVOID lpUser);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_SetAlarmDataCallBackv2(fAlarmDataCallBackV2 fpMessageCallBack, LPVOID lpUser);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_SetAlarmDataCallBackv3(fAlarmDataCallBackV3 fpMessageCallBack, LPVOID lpUser);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_SetTransAlarmCallBack(fTransAlarmCallBack fpTransAlarmCallBack, LPVOID lpUser);

I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_SetConnectTime(DWORD dwWaitTime, DWORD dwTryTimes);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_SetReconnect(DWORD dwInterval, BOOL bEnableRecon);
I8H_SDK_API DWORD I8H_SDK_CALL I8H_SDK_GetSDKVersion( );
I8H_SDK_API DWORD I8H_SDK_CALL I8H_SDK_GetSDKBuildVersion( );
I8H_SDK_API DWORD I8H_SDK_CALL I8H_SDK_IsSupport( );
I8H_SDK_API DWORD I8H_SDK_CALL I8H_SDK_GetLastError( );
I8H_SDK_API char* I8H_SDK_CALL I8H_SDK_GetErrorMsg(DWORD dwLastError);


//!搜索模块
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_StartDiscovery(char *lpIfName, fDiscoveryCallBack fpDiscoveryCallBack, LPVOID lpUser);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_StopDiscovery( );
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_ModifyDev(char *lpIfName, I8H_MODIFY_COMMAND eCmd, LPVOID lpBuffer, DWORD dwBufSize);


//!注册注销模块
I8H_SDK_API HANDLE I8H_SDK_CALL I8H_SDK_Login(char *lpDevIP, WORD wDevPort, char *lpUserName, char *lpPassword, LPI8H_DEVICEINFO lpDeviceInfo);
//内部对接东顺专用接口,外部人员对接请弄清楚之后决定是否使用,可以兼容普通的SLINK I8H以及T8S, nProtocolType: 0:普通的SLINK I8H   1:T8S协议
I8H_SDK_API HANDLE I8H_SDK_CALL I8H_SDK_Loginv2(char *lpDevIP, WORD wDevPort, char *lpUserName, char *lpPassword, int nProtocolType, LPI8H_DEVICEINFO lpDeviceInfo);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_Logout(HANDLE hUserId);


//!预览相关接口
I8H_SDK_API HANDLE I8H_SDK_CALL I8H_SDK_RealPlay(HANDLE hUserId, LPI8H_CLIENTINFO lpClientInfo, fStreamDataCallBack fpRealDataCallBack, LPVOID lpUser);
I8H_SDK_API HANDLE I8H_SDK_CALL I8H_SDK_RealPlayv2(HANDLE hUserId, char *lpUserName, char *lpPassword, BYTE bySelfClean, LPI8H_CLIENTINFO lpClientInfo, fStreamDataCallBack fpRealDataCallBack, LPVOID lpUser);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_StopRealPlay(HANDLE hRealHandle);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_ControlRealPlay(HANDLE hRealHandle, DWORD dwControl, LPVOID lpInBuffer, DWORD dwInLen);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_SetStandardCallBack4RealPlay(HANDLE hRealHandle, fStandardStreamDataCallBack fpStandardStreamCallBack, LPVOID lpUser);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_SetStandardCallBack4RealPlayV2(HANDLE hRealHandle, fStandardStreamDataCallBackV2 fpStandardStreamCallBackV2, LPVOID lpUser);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_StartRealPlayRecord(HANDLE hRealHandle, LPI8H_CHANNEL_INFO lpChannelInfo,  BYTE byFileType , char *lpSavedFileName) ;
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_StopRealPlayRecord(HANDLE hRealHandle, LPI8H_CHANNEL_INFO lpChannelInfo,   BYTE byFileType) ;


//!动态生成I帧
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_MakeKeyFrame(HANDLE hUserId, LONG lChannel);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_MakeKeyFrameSub(HANDLE hUserId, LONG lChannel);


//!云台控制相关接口
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_PTZControl(HANDLE hUserId, LONG lChannel, DWORD dwPtzCmd, DWORD dwStop, DWORD dwSpeed) ;
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_TransPTZ(HANDLE hUserId, LONG lChannel, BYTE *lpBuffer, DWORD dwSize) ;
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_PTZPreset(HANDLE hUserId, LONG lChannel, DWORD dwPtzPresetCmd, DWORD dwPresetIndex);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_PTZCruise(HANDLE hUserId, LONG lChannel, DWORD dwPtzCruiseCmd, BYTE byCruiseRoute, BYTE byCruisePoint, DWORD wInput);//byCruiseRoute:巡航序号 1~255;  byCruisePoint:巡航点 1~32; wInput:输入参数 bit0-bit15:dwell, bit16-bit23:speed, bit24-bit32:preset
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_PTZTrack(HANDLE hUserId, LONG lChannel, DWORD dwPtzTrackCmd, DWORD dwPtzTrackId);

I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_GetPTZCruise(HANDLE hUserId, LONG lChannel, LONG lCruiseRoute, LPI8H_CRUISE_RET lpCruiseRet);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_PTZSet3D(HANDLE hUserId, LONG lChannel, DWORD dwXTop, DWORD dwYTop, DWORD dwXBottom, DWORD dwYBottom);


//!文件查找  查询时间不能跨天   结果I8H_FINDDATA数组需要调用 I8H_SDK_FreeMemory 释放   I8H_FINDDATA[0]|I8H_FINDDATA[1]|I8H_FINDDATA[2]---
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_FindFile(HANDLE hUserId, LPI8H_FILECOND lpFindCond, BYTE **lpFileData, DWORD *lpOutSize);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_FindFilev2(HANDLE hUserId, LPI8H_FILECONDV2 lpFindCondv2, BYTE **lpFileData, DWORD *lpOutSize);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_FindFile4Monthly(HANDLE hUserId, LONG lChannel, LONG lStartYear, LONG lStartMonth, LONG lDaysOfMonth, DWORD *lpResult);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_FindFile4Monthlyv2(HANDLE hUserId, LONG lChannel, LONG lStartYear, LONG lStartMonth, LONG lStartDay, LONG lDaysOfMonth, DWORD *lpResult);


//!传入超时值和尝试次数dwTime = (second << 16) | (trycount ) 
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_FindFileByTime(HANDLE hUserId, LPI8H_FILECOND lpFindCond, BYTE **lpFileData, DWORD *lpOutSize, DWORD dwTime);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_FindFilev2ByTime(HANDLE hUserId, LPI8H_FILECONDV2 lpFindCondv2, BYTE **lpFileData, DWORD *lpOutSize, DWORD dwTime);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_FindFile4MonthlyByTime(HANDLE hUserId, LONG lChannel, LONG lStartYear, LONG lStartMonth, LONG lDaysOfMonth, DWORD *lpResult, DWORD dwTime);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_FindFile4Monthlyv2ByTime(HANDLE hUserId, LONG lChannel, LONG lStartYear, LONG lStartMonth, LONG lStartDay, LONG lDaysOfMonth, DWORD *lpResult, DWORD dwTime);


//!文件回放//dwOpt bit0 --bit7:stream type  0:main stream 1:sub stream   bit8--bit15:link mode  bit15--bit31:channel
I8H_SDK_API HANDLE I8H_SDK_CALL I8H_SDK_PlayBackByTime(HANDLE hUserId, DWORD dwOpt, LPI8H_TIME lpStartTime, LPI8H_TIME lpStopTime, fStreamDataCallBack fpPlayDataCallBack, LPVOID lpUser);
I8H_SDK_API HANDLE I8H_SDK_CALL I8H_SDK_PlayBackByTimev2(HANDLE hUserId, LPI8H_PLAYBACK_COND lpPalyBackCond, fStreamDataCallBack fpPlayDataCallBack, LPVOID lpUser);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_PlayBackControl(HANDLE hPlayHandle, DWORD dwControl, LPVOID lpInBuffer, DWORD dwInLen, LPVOID lpOutBuffer, DWORD *lpOutLen);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_StopPlayBack(HANDLE hPlayHandle);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_SetStandardCallBack4PlayBack(HANDLE hPlayHandle, fStandardStreamDataCallBack fpStandardStreamCallBack, LPVOID lpUser);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_SetStandardCallBack4PlayBackV2(HANDLE hPlayHandle, fStandardStreamDataCallBackV2 fpStandardStreamCallBackV2, LPVOID lpUser);



//!文件下载
I8H_SDK_API HANDLE I8H_SDK_CALL I8H_SDK_GetFileByTime(HANDLE hUserId, LONG lChannel, LPI8H_TIME lpStartTime, LPI8H_TIME lpStopTime, char *lpSavedFileName);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_StopGetFile(HANDLE hFileHandle);
I8H_SDK_API int I8H_SDK_CALL I8H_SDK_GetDownloadPos(HANDLE hFileHandle);


//!升级
I8H_SDK_API HANDLE I8H_SDK_CALL I8H_SDK_Upgrade(HANDLE hUserId, char *lpFileName);
I8H_SDK_API int I8H_SDK_CALL I8H_SDK_GetUpgradeState(HANDLE hUpgradeHandle);
I8H_SDK_API int I8H_SDK_CALL I8H_SDK_GetUpgradeProgress(HANDLE hUpgradeHandle);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_CloseUpgradeHandle(HANDLE hUpgradeHandle);


//!报警
I8H_SDK_API HANDLE I8H_SDK_CALL I8H_SDK_SetupAlarmChan(HANDLE hUserId);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_CloseAlarmChan(HANDLE hAlarmHandle);

I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_SubscribeNotify(HANDLE hUserId, char *lpRemoteIP, WORD wRemotePort, BOOL bSubscribe);

I8H_SDK_API HANDLE I8H_SDK_CALL I8H_SDK_SetupAlarmByRTSP(HANDLE hUserId);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_CloseAlarmByRTSP(HANDLE hAlarmHandle);


//!语音对讲(默认音频编码类型为G711-A dwAudioType是音频编码类型取值范围 0-OggVorbis;1-G711_U;2-G711_A 3-G726)
I8H_SDK_API HANDLE I8H_SDK_CALL I8H_SDK_StartVoiceCom(HANDLE hUserId, DWORD dwVoiceChan, fVoiceDataCallBack fpVoiceDataCallBack, LPVOID lpUser, DWORD dwAudioType);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_VoiceComSendData(HANDLE hVoiceComHandle, BYTE *lpBuffer, DWORD dwSize);

//!语音对讲(默认音频编码类型为G711-A dwAudioType是音频编码类型取值范围 0-OggVorbis;1-G711_U;2-G711_A 3-G726, 目前仅支持G711U和G711A类型，采样率8000，位率16，单声道的音频输入和输出数据)
I8H_SDK_API HANDLE I8H_SDK_CALL I8H_SDK_StartVoiceComv2(HANDLE hUserId, DWORD dwVoiceChan, fVoiceDataCallBackV2 fpVoiceDataCallBack, LPVOID lpUser, DWORD dwAudioType);
//!dwOpt bit0~bit7:音频编码类型, 0--OggVorbis 1--G711_U  2--G711_A 3--G726  bit8~bit15:采样率,0--8000;bit16~bit23:位率,0--16,1--32;bit24~bit32:声道,0-单声道,1-双声道
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_VoiceComSendDatav2(HANDLE hVoiceComHandle, DWORD dwVoiceOpt, BYTE *lpBuffer, DWORD dwSize);

I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_StopVoiceCom(HANDLE hVoiceComHandle);


//!设备抓图
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_CaptureJPEGPicture(HANDLE hUserId, LONG lChannel, BYTE *lpJpegBuffer, DWORD dwJpegSize, DWORD *lpOutJpegSize);

I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_CaptureJPEGPicturev2(HANDLE hUserId, LONG lChannel, char *lpFileName);

//!设备恢复默认值 保存参数 重启 关机操作
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_RestoreConfig(HANDLE hUserId);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_SaveConfig(HANDLE hUserId);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_RebootDVR(HANDLE hUserId);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_ShutDownDVR(HANDLE hUserId);

I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_TranData(HANDLE hUserId, BYTE *lpUrl, BYTE *lpInBuffer, DWORD dwInSize, BYTE *lpOutBuffer, DWORD dwOutBufSize, DWORD *lpOutSize);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_TranDatav2(HANDLE hUserId,  BYTE *lpUrl, BYTE *lpInBuffer, DWORD dwInSize, BYTE *lpOutBuffer, DWORD dwOutBufSize, DWORD *lpOutSize,DWORD dwTimeout);//!dwTimeout = (超时时间(秒)<< 16)|(尝试次数)
//!dwTimeout = (超时时间(秒)<< 16)|(尝试次数) dwBufSize需要多大的缓冲区(以字节为单位,默认为1 * 1024 * 1024)
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_TranDatav3(HANDLE hUserId, BYTE *lpUrl, BYTE *lpInBuffer, DWORD dwInSize, BYTE *lpOutBuffer, DWORD dwOutBufSize, DWORD *lpOutSize, DWORD dwTimeout, DWORD dwBufSize);//!dwTimeout = (超时时间(秒)<< 16)|(尝试次数)
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_FreeMemory(BYTE *lpBuffer);


//!参数获取与设置
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_GetConfig(HANDLE hUserId, DWORD dwCommand, BYTE *lpInBuffer, DWORD dwInSize, BYTE *lpOutBuffer, DWORD dwOutBufSize, DWORD *lpOutSize);
I8H_SDK_API BOOL I8H_SDK_CALL I8H_SDK_SetConfig(HANDLE hUserId, DWORD dwCommand, BYTE *lpInBuffer, DWORD dwInSize, BYTE *lpOutBuffer, DWORD dwOutBufSize, DWORD *lpOutSize);


#endif 

