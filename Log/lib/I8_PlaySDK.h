#ifndef _I8_PLAYSDK_
#define _I8_PLAYSDK_

#include "windows.h"

#define  I8_MP4Play_NOERROR						0	//!没有错误；
#define  I8_MP4Play_PARA_OVER				    	1	//!输入参数非法；
#define  I8_MP4Play_ORDER_ERROR					2	//!调用顺序不对；
#define  I8_MP4Play_DEC_VIDEO_ERROR				4	//!视频解码失败；
#define  I8_MP4Play_DEC_AUDIO_ERROR				5	//!音频解码失败；
#define  I8_MP4Play_SUPPORT_OPEN_ONLY	       		6	//!只能在播放流或播放文件时才能使用此接口
#define  I8_MP4Play_OPEN_FILE_ERROR				7	//!文件操作失败；
#define  I8_MP4Play_CREATE_OBJ_ERROR		 	8	//!创建线程事件等失败；
#define  I8_MP4Play_CREATE_DDRAW_ERROR			9	//!创建directDraw失败；
#define  I8_MP4Play_CREATE_OFFSCREEN_ERROR    	10	//!创建后端缓存失败；
#define  I8_MP4Play_BUF_OVER			       		11	//!缓冲区满，输入流失败；
#define  I8_MP4Play_CREATE_SOUND_ERROR	       		12	//!创建音频设备失败；
#define  I8_MP4Play_SET_VOLUME_ERROR	       		13	//!设置音量失败；
#define  I8_MP4Play_SUPPORT_FILE_ONLY	       		14	//!只能在播放文件时才能使用此接口；
#define  I8_MP4Play_SUPPORT_STREAM_ONLY	   	15	//!只能在播放流时才能使用此接口；
#define  I8_MP4Play_SYS_NOT_SUPPORT		   		16	//!系统不支持，解码器只能工作在Pentium 3以上；
#define  I8_MP4Play_FILEHEADER_UNKNOWN        		17	//!没有文件头；
#define  I8_MP4Play_VERSION_INCORRECT	       		18	//!解码器和编码器版本不对应；
#define  I8_MP4Play_INIT_DECODER_ERROR        		19	//!初始化解码器失败；
#define  I8_MP4Play_CHECK_FILE_ERROR	       		20	//!测试文件头尾数据时没有找到有效数据；文件太短或码流无法识别；
#define  I8_MP4Play_BLT_ERROR			       		22	//!位拷贝失败；
#define  I8_MP4Play_UPDATE_ERROR		       		23	//!显示overlay失败；

#define I8_STREAM_NO		 					0x0	//!文件方式
#define I8_STREAME_FILE	 					0x1	//!缓冲解码，适合文件流输入	
#define I8_STREAME_REALTIME 					0x2	//!实时解码，适合板卡生成的实时数据流，默认值

//!索引帧信息
typedef struct {
	DWORD nFrameNum;           	//!帧号
	unsigned	long	nTime;          
	unsigned	long	nFilePos;    	//!帧在文件中的位置
}I8_FRAME_POS ,*LPI8_FRAME_POS;

//!索引帧信息
typedef struct {
	DWORD nFrameNum;           		//!帧号
	unsigned	long	nTime;          
	unsigned	long	nFilePos;    		//!帧在文件中的位置 
}I8_FRAME_POSEX ,*LPI8_FRAME_POSEX;

//!帧信息
typedef struct{
	long nWidth;
	long nHeight;
	long nStamp;
	long nType;
	long nFrameRate;
}I8_FRAME_INFO,*LPI8_FRAME_INFO;


typedef int (CALLBACK *I8FASTBACKCALLBACK )(ULONG channelNumber);

//pBuf是原始视频的Y地址，nReserved1是U的地址， nReserved2是V的地址 ， nWidth和nHeight是宽和高，图像的nPitch=(nSize/nHeight)*2/3;nType为0的时候，是yuv 4:2:0，1时是yuv 4:2:2；
typedef void (CALLBACK *I8DISPLAYCBFUN)(long nPort,char *pBuf,long nSize,long nWidth,long nHeight,long nType,long nReserved1,long nReserved2);
typedef void (CALLBACK *I8FILEREFDONE)(DWORD nPort,DWORD nUser);
typedef void (CALLBACK *I8DECCBFUN)(long nPort,char *pBuf,long nSize,I8_FRAME_INFO *pFrameInfo,long nReserved1,long nReserved2); 
typedef long (CALLBACK *I8DECCBFUNEx)(long nPort,const char *pBuf,long nSize,I8_FRAME_INFO *pFrameInfo,long lParam);
typedef void (CALLBACK *I8SOURCEBUFFUN)(long nPort,DWORD nBufSize,DWORD dwUser,void *pResvered);
typedef void (CALLBACK *I8DRAWFUN)(long nPort,HDC hDC,LONG nUser);
typedef long (CALLBACK *I8DRAWFUNEx)(long nPort,HDC hDC,unsigned int width , unsigned int heigth ,LONG nUser);
typedef void (CALLBACK *I8DRAWFUNFAST)(long nPort,HDC hDC,unsigned int StartX,unsigned int StartY ,unsigned int width , unsigned int heigth ,LONG nUser);

typedef void (CALLBACK *I8TIMECTRLFUN)(long nPort,unsigned char *pFrameHead ,unsigned char *buffer , int size , void *pUser);


#ifndef I8_T_YV420 
#define I8_T_YV420 0
#endif

#ifndef I8_T_YV422 
#define I8_T_YV422 1
#endif

#ifndef I8_T_YV444 
#define I8_T_YV444 2
#endif

#ifndef I8_T_AUDIO16
#define I8_T_AUDIO16 101
#endif

#ifndef I8_T_AUDIO16EX
#define I8_T_AUDIO16EX 102
#endif

// 鱼眼结构
#define I8_FISHEYE_MAX_REGION_NUM 	8

typedef enum I8_FISHEYE_MOUNT_MODE_E
{		

	I8_FISHEYE_MOUNT_DESKTOP 	= 0,		/* desktop mount mode */
	I8_FISHEYE_MOUNT_CEILING	= 1,		/* ceiling mount mode */
	I8_FISHEYE_MOUNT_WALL   	= 2,		/* wall mount mode */

	I8_FISHEYE_MOUNT_MODE_BUTT
}I8_FISHEYE_MOUNT_MODE_E;


typedef enum I8_FISHEYE_VIEW_MODE_E
{
	I8_FISHEYE_VIEW_NO_TRANSFORMATION 	= 0, 	/* no fisheye correction */
	I8_FISHEYE_VIEW_NORMAL   		= 1, 	/* normal mode of fisheye correction */
	I8_FISHEYE_VIEW_360_PANORAMA   = 2, 	/* 360 panorama mode of fisheye correction */
	I8_FISHEYE_VIEW_180_PANORAMA	= 3,	/* 180 panorama mode of fisheye correction */	
	I8_FISHEYE_VIEW_CYLINDER      = 4,  // 圆柱体


	I8_FISHEYE_VIEW_MODE_BUTT
}I8_FISHEYE_VIEW_MODE_E;

typedef enum I8_FISHEYE_FILTER_MODE_E
{
	I8_FISHEYE_FILTER_BILINEAR 	= 0,	/* bilinear filter */
	I8_FISHEYE_FILTER_LINEAR		= 1,	/* linear filter */
	I8_FISHEYE_FILTER_NEAREST		= 2,	/* nearest filter */
	I8_FISHEYE_FILTER_MODE_BUTT
}I8_FISHEYE_FILTER_MODE_E;

typedef struct I8_FISHEYE_GPU_PRI_S
{
	I8_FISHEYE_FILTER_MODE_E	enYFilter;		/* Fiter mode for Luma */
	I8_FISHEYE_FILTER_MODE_E	enCbCrFilter;	/* Fiter mode for chroma */
	unsigned int 				u32CCMPhyAddr;	/* Physical address of correction coordinate memory , the size is region's width x height x sizeof(float) x 2. */										   	
}I8_FISHEYE_GPU_PRI_S;

typedef struct I8_FISHEYE_RECT_S
{
	int x;
	int y;
	int width;
	int height;
}I8_FISHEYE_RECT_S;


typedef struct I8_FISHEYE_REGION_ATTR_S
{
	I8_FISHEYE_VIEW_MODE_E 	enViewMode;		/* fisheye view mode */
	// 360 度展开时为内圆半径
	unsigned int 				u32InRadius;    /* inner radius of fisheye correction region [0, u32OutRadius) */
	// 360 度展开时为外圆半径  
	unsigned int 				u32OutRadius;   /* out radius of fisheye correction region [1, max(width/2 of input picture, height/2 of input picture)] */
	// 360 度展开时,
	unsigned int 				u32Pan;// 左右	,180		/* [0, 360] */
	unsigned int 				u32Tilt;// 上下	,180	/* [0, 360] */
	unsigned int 				u32HorZoom;// 放大、缩小,2048中间值		/* [1, 4095] */
	unsigned int 				u32VerZoom;		/* [1, 4095] */
	unsigned int                u32Ratio;// 0 - 拉伸，1-按比例
	I8_FISHEYE_RECT_S         stOutRect; // 输出区域		/* output image info after fisheye correction range of width [960, 4608],  rang of height [360, 3456], rang of x [0, 4608), rang of y [0, 3456) */
	I8_FISHEYE_GPU_PRI_S		stGPUPrivate; // GPU操作相关私有信息	/* GPU related attribute. Only for GPU use */
}I8_FISHEYE_REGION_ATTR_S;


typedef struct I8_FISHEYE_ATTR_S
{
	int  				bEnable;			/* whether enable fisheye correction or not */
	int 				bLMF; 				/* whether fisheye len's LMF coefficient is from user config 
											or from default linear config */
	int                 bBgColor;       	/* whether use background color or not */
	unsigned int                  u32BgColor;			/* the background color ARGB8888 */

	int                  s32OutWidth;// 输出宽
	int                  s32OutHeight;// 输出高
	int                  s32ValidWidth; // 鱼眼有效区域大小
	int                  s32ValidHeight;
	int 				 s32HorOffset; // 中心点 水平偏移,有效区域相对原始图像的位置   	/* the horizontal offset between image center and physical center of len */
	int 				 s32VerOffset;		/* the vertical offset between image center and physical center of len */

	unsigned int                  u32TrapezoidCoef;	/* strength coefficient of trapezoid correction */

	I8_FISHEYE_MOUNT_MODE_E    enMountMode;// 安装方式		/* fisheye mount mode */	

	unsigned int               	u32RegionNum; // 校正区域个数      /* fisheye correction region number */
	I8_FISHEYE_REGION_ATTR_S 	astFisheyeRegionAttr[I8_FISHEYE_MAX_REGION_NUM];/* attribution of fisheye correction region */	 
}I8_FISHEYE_ATTR_S;

//////////////////////////////

BOOL __stdcall I8_MP4Play_InitDDraw(HWND hWnd);
BOOL __stdcall I8_MP4Play_RealeseDDraw();

BOOL __stdcall I8_MP4Play_OpenFile(LONG nPort,LPSTR sFileName);
BOOL __stdcall I8_MP4Play_CloseFile(LONG nPort);
BOOL __stdcall I8_MP4Play_Play(LONG nPort, HWND hWnd);
BOOL __stdcall I8_MP4Play_Stop(LONG nPort);
BOOL __stdcall I8_MP4Play_Pause(LONG nPort,DWORD nPause);
BOOL __stdcall I8_MP4Play_Fast(LONG nPort);
BOOL __stdcall I8_MP4Play_Slow(LONG nPort);
BOOL __stdcall I8_MP4Play_OneByOne(LONG nPort);

BOOL __stdcall I8_MP4Play_SetFileEndMsg(LONG nPort,HWND hWnd,UINT nMsg);
BOOL __stdcall I8_MP4Play_SetVolume(LONG nPort,WORD nVolume);
BOOL __stdcall I8_MP4Play_StopSound();
BOOL __stdcall I8_MP4Play_PlaySound(LONG nPort);
BOOL __stdcall I8_MP4Play_OpenStream(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);
BOOL __stdcall I8_MP4Play_InputData(LONG nPort,PBYTE pBuf,DWORD nSize);
BOOL __stdcall I8_MP4Play_InputDataEx(LONG nPort,PBYTE pBuf,DWORD nSize);//接收一完整帧数据
BOOL __stdcall I8_MP4Play_CloseStream(LONG nPort);
int  __stdcall I8_MP4Play_GetCaps();
DWORD __stdcall I8_MP4Play_GetFileTime(LONG nPort);
DWORD __stdcall I8_MP4Play_GetPlayedTimeEx(LONG nPort);

DWORD __stdcall I8_MP4Play_GetCurrentFrameNum(LONG nPort);
BOOL __stdcall I8_MP4Play_SetPlayPos(LONG nPort,float fRelativePos);
float __stdcall I8_MP4Play_GetPlayPos(LONG nPort);
LONG __stdcall I8_MP4Play_GetStreamOpenMode(LONG nPort);
BOOL __stdcall I8_MP4Play_SetOverlayMode(LONG nPort,BOOL bOverlay,COLORREF colorKey);
LONG __stdcall I8_MP4Play_GetOverlayMode(LONG nPort);
COLORREF __stdcall I8_MP4Play_GetColorKey(LONG nPort);
WORD __stdcall I8_MP4Play_GetVolume(LONG nPort);
BOOL __stdcall I8_MP4Play_GetPictureQuality(LONG nPort,BOOL *bHighQuality);
BOOL __stdcall I8_MP4Play_OneByOneBack(LONG nPort);

BOOL __stdcall I8_MP4Play_SetCurrentFrameNum(LONG nPort,DWORD nFrameNum);
BOOL __stdcall I8_MP4Play_GetKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, LPI8_FRAME_POS pFramePos);
BOOL __stdcall I8_MP4Play_GetNextKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, LPI8_FRAME_POS pFramePos);
BOOL __stdcall I8_MP4Play_SetDisplayCallBack(LONG nPort,I8DISPLAYCBFUN DisplayCBFun);
BOOL __stdcall I8_MP4Play_SetFileRefCallBack(LONG nPort,I8FILEREFDONE FileRefDone,DWORD nUser);
BOOL __stdcall I8_MP4Play_ConvertToBmpFile(char * pBuf,long nSize,long nWidth,long nHeight,long nReserved1,long nReserved2,char *sFileName);
BOOL __stdcall I8_MP4Play_ConvertToBmpFileEx(char * pBuf,long nSize,long nWidth,long nHeight,long nType,long nReserved1,long nReserved2,char *sFileName);
BOOL __stdcall I8_MP4Play_ChangeContrast(LONG nPort,int degree);
BOOL __stdcall I8_MP4Play_ChangeBright(LONG nPort,int degree);
DWORD __stdcall I8_MP4Play_GetSdkVersion();
DWORD __stdcall I8_MP4Play_GetLastError(LONG nPort);

BOOL __stdcall I8_MP4Play_GetPictureSize(LONG nPort,LONG *pWidth,LONG *pHeight);
BOOL __stdcall I8_MP4Play_RefreshPlay(LONG nPort);
DWORD __stdcall I8_MP4Play_GetFileHeadLength();
DWORD __stdcall I8_MP4Play_GetPlayedTime(LONG nPort);
BOOL __stdcall I8_MP4Play_LocalZoom(LONG nPort,BOOL bLocalZoom,int Left,int Top,int Width,int Height);
BOOL __stdcall I8_MP4Play_SetDecCallBack(LONG nPort,I8DECCBFUN DecCBFun);
BOOL __stdcall I8_MP4Play_SetDecCallBackEx(LONG nPort,I8DECCBFUNEx DecCBFun);
DWORD __stdcall I8_MP4Play_GetSourceBufferRemain(LONG nPort);
BOOL __stdcall I8_MP4Play_ResetSourceBuffer(LONG nPort);
BOOL __stdcall I8_MP4Play_SetSourceBufCallBack(LONG nPort,DWORD nThreShold,I8SOURCEBUFFUN SourceBufFun,DWORD dwUser,void *pReserved);
BOOL __stdcall I8_MP4Play_ResetSourceBufFlag(LONG nPort);

BOOL __stdcall I8_MP4Play_SetStreamOpenMode(LONG nPort,DWORD nMode);
DWORD __stdcall I8_MP4Play_GetDisplayBuf(LONG nPort);
BOOL __stdcall I8_MP4Play_SetPlayedTimeEx(LONG nPort,DWORD nTime);
DWORD __stdcall I8_MP4Play_GetCurrentFrameRate(LONG nPort);
BOOL __stdcall I8_MP4Play_SetDisplayBuf(LONG nPort,DWORD nNum);
BOOL __stdcall I8_MP4Play_ThrowBFrameNum(LONG nPort,DWORD nNum);
BOOL __stdcall I8_MP4Play_PlaySoundShare(LONG nPort);
BOOL __stdcall I8_MP4Play_StopSoundShare(LONG nPort);
DWORD __stdcall I8_MP4Play_GetFileTotalFrames(LONG nPort);
BOOL __stdcall I8_MP4Play_SetPicQuality(LONG nPort,BOOL bHighQuality);

BOOL __stdcall I8_MP4Play_SetPlaySpeed(LONG nPort,int nSpeed);
void __stdcall I8_MP4Play_AutoSync(BOOL bSync);
BOOL __stdcall I8_MP4Play_RigisterDrawFun(LONG nPort,I8DRAWFUN DrawFun,LONG nUser);
BOOL __stdcall I8_MP4Play_RigisterDrawFunEx(LONG nPort,I8DRAWFUNEx DrawFun,LONG nUser);
BOOL __stdcall I8_MP4Play_GetKeyFramePosEx(LONG nPort,DWORD nValue, DWORD nType,RECT *rc, LPI8_FRAME_POS pFramePos);
BOOL __stdcall I8_MP4Play_SetDisplayRegion(LONG nPort,DWORD nRegionNum, RECT *pSrcRect, HWND hDestWnd, BOOL bEnable);
BOOL __stdcall I8_MP4Play_FastBack(LONG nPort,HWND hWnd,int nSpeed, I8FASTBACKCALLBACK pFastBackCallBack);

//!added by itman for HuXinHuTong 07-11-19
BOOL __stdcall I8_MP4Play_OpenStreamEx(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize,long lSpeedControl); 
BOOL __stdcall I8_MP4Play_GetPlaySpeed(LONG nPort,long *pSpeed);
BOOL __stdcall I8_MP4Play_Refresh(LONG nPort);
BOOL __stdcall I8_MP4Play_GetSysHead(LONG nPort,unsigned char *pSysHead,int *pSysLen);
BOOL __stdcall I8_MP4Play_StartRecord(LONG nPort,const char *sFileName);
BOOL __stdcall I8_MP4Play_StopRecord(LONG nPort);

//!added by itman for VideoAnalysis 2008-05-30
BOOL __stdcall I8_MP4Play_StopVideoAnalysis(LONG nPort, DWORD nStopVideoAnalysis );

//!add by sqy 2011-5-12
BOOL __stdcall I8_MP4Play_SetPlayerBufNumber(LONG nPort,DWORD dwBufNum);
BOOL __stdcall I8_MP4Play_SetAudioMode(DWORD dwMode);
DWORD __stdcall I8_MP4Play_GetPlayedOSDTime(LONG nPort);

BOOL __stdcall I8_MP4Play_SetColor(LONG nPort, DWORD nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);
BOOL __stdcall I8_MP4Play_GetColor(LONG nPort, DWORD nRegionNum, int *pBrightness, int *pContrast, int *pSaturation, int *pHue);
int __stdcall I8_MP4Play_GetFreePort();
BOOL  __stdcall I8_MP4Play_IsFreePort(int nPort);

BOOL  __stdcall I8_MP4Play_SetOverlayMode();

BOOL __stdcall I8_MP4Play_PlaySoundEX();

BOOL __stdcall I8_MP4Play_StopSoundEX();

BOOL __stdcall I8_MP4Play_InputAudioEX(unsigned char *pbuffer , int nLen ,int ntype);

BOOL __stdcall I8_MP4Play_SetVolumeEX(WORD nVolume);

WORD __stdcall I8_MP4Play_GetVolumeEX();

BOOL __stdcall I8_MP4Play_SetRealPlayDelay(unsigned int MinDelayCount , unsigned int NormalDelayCount,unsigned int MaxDelayCount );

void  __stdcall I8_MP4Play_SetDecoderMode(int bfastdecoder);

BOOL  __stdcall I8_MP4Play_StartDefog(LONG nPort);

BOOL  __stdcall I8_MP4Play_SetDefogLevel(LONG nPort, int nlevel) ;

BOOL  __stdcall I8_MP4Play_StoptDefog(LONG nPort);

BOOL  __stdcall I8_MP4Play_StartVideoStab(LONG nPort);

BOOL  __stdcall I8_MP4Play_SetVideoStabLevel(LONG nPort, int nlevel);

BOOL  __stdcall I8_MP4Play_StopVideoStab(LONG nPort);

BOOL  __stdcall I8_MP4Play_StartHDReady(LONG nPort);

BOOL  __stdcall I8_MP4Play_SetHDReadyLevel(LONG nPort, int nlevel);

BOOL  __stdcall I8_MP4Play_StopHDReady(LONG nPort);

BOOL __stdcall I8_MP4Play_GetFileStartTime(LONG nPort , DWORD *pStartTime);

BOOL __stdcall I8_MP4Play_ConverRTPtoH264(unsigned char *InBuffer , int InSize , unsigned char *OutBuffer , int *OutSize) ;

BOOL __stdcall I8_MP4Play_SetTimeCtrlCallBack(LONG nPort,I8TIMECTRLFUN TimeCtrlCBFun,void *pUser);

//转换YUV数据成JPG文件
BOOL __stdcall I8_MP4Play_ConvertToJpgFileEx(char * pBuf,long nSize,long nWidth,long nHeight,long nType,long nReserved1,long nReserved2,char *sFileName);

BOOL __stdcall I8_MP4Play_StartOSD(LONG nPort,char *pBuffer, int nLen);

BOOL __stdcall I8_MP4Play_StopOSD(LONG nPort);

BOOL __stdcall I8_MP4Play_GetPlayedOSDTimeEx(LONG nPort,unsigned int *uiFrameTime , unsigned int *uiFrameTickCount);


//增加一个高效画线函数，这个函数的DC是整个屏幕，在视频上画图的时候，必须要自己计算偏移量，以便图形能够画在视频的上面，效率比以前的画图函数提高很多
BOOL __stdcall I8_MP4Play_RigisterDrawFunFast(LONG nPort,I8DRAWFUNFAST DrawFunFast,LONG nUser);

//往流中输入原始数据
//uiFrameTyp的含义 IFrames=0x01,AudioFrames=0x08,PFrames=0x09
//TimeStamp是相对时间戳，前后两帧的相对时间戳之差/90就是两帧之间的毫秒数
//uiFrameNo为帧好，注意视频帧的帧号必须连续，音频帧号无所谓
//uiFrameTime为帧的秒级时间戳，也就是事件发生时候的当前时间
//unsigned short usWidth
//unsigned short usHeight
//char cCodecId 视频帧的时候H264=8,H265=16,	音频帧的时候AntsG711_ALAW=1,AntsG711_ULAW=2,
BOOL __stdcall I8_MP4Play_InputDataRaw(LONG nPort, PBYTE pBuf, DWORD nSize,unsigned int uiFrameType ,unsigned int uiFrameNo,unsigned int uiFrameTime ,unsigned int TimeStamp,unsigned short usWidth,unsigned short usHeight,char cCodecId);

// 鱼眼接口
// 开启并设置鱼眼参数，
BOOL __stdcall I8_MP4Play_FishEye_SetAttr(LONG nPort, I8_FISHEYE_ATTR_S *pAttr);
//获取当前应用配置状态
BOOL __stdcall I8_MP4Play_FishEye_GetAttr(LONG nPort, I8_FISHEYE_ATTR_S *pAttr);

#endif

