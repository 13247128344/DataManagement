#ifndef __ANTS_NAMED_PIPE_SERVER__
#define __ANTS_NAMED_PIPE_SERVER__

#include <windows.h>


/*
//子进程发往主框架JSON数据格式
{
"msgType":"",					//消息类型
"from": "",						//消息来源
"target": "/api/v1/adddevice",  //发往
"msgData":{}					//消息内容 根据消息类型来解析 比如 "msgData":{"data":"msgContext"}
}

	msgType
		0	子进程启动将需要嵌套界面句柄(WId)发往宿主程序    
			msgData : { "data":[{"name":"application","WId","1233434"}... ] }  name窗口名称  窗口WId
		1


//返回数据格式
{
	"result" : "",              //返回类型
	"responseContent": ""
}
*/

/******************************************************************
					返回值宏定义
*******************************************************************/
#define NAMED_PIPE_NO_ERROR					0			//没有错误
#define NAMED_PIPE_FAILED					1			//失败		
#define NAMED_PIPE_WRONG_PARAMETER			2			//参数错误
#define NAMED_PIPE_OUTBUFFERSIZE_SMALL		3			//输出缓冲区内存太小
#define NAMED_PIPE_TIMEOUT					4			//超时
#define NAMED_PIPE_WRONG_JSON_FORMAT		5			//JSON解析错误
#define NAMED_PIPE_WRONG_PIPE_NAME			6			//命名管道名称错误
#define NAMED_PIPE_CONNECT_FAILED			7			//连接命名管道服务失败

/********************************************************************************
					回调函数定义	
*********************************************************************************/
//命名管道服务接收到客户端数据后调用该回调函数
typedef void(__stdcall *NamedPipeMsgCallback)(char* inBuffer /*调用者申请和释放*/, int inBufferSize, char* outBuffer /*调用者申请和释放*/, int outBufferSize, int* outSize);

#define NAMEDPIPE_API extern "C" __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif
	NAMEDPIPE_API bool	ants_named_pipe_init();
	NAMEDPIPE_API bool	ants_named_pipe_setup(char* pipeServerName);
	NAMEDPIPE_API void	ants_named_pipe_setCallback(NamedPipeMsgCallback pFunc);
	NAMEDPIPE_API DWORD  ants_named_pipe_sendMsgToServer(char* serverName, char* inBuffer/*调用者申请和释放*/, int inBufferSize, char* outBuffer/*调用者申请和释放*/, int outBufferSize, int *outSize);
	NAMEDPIPE_API DWORD  ants_named_pipe_sendMsgToServerNotNeedReply(char* serverName, char* inBuffer/*调用者申请和释放*/, int inBufferSize);
#ifdef __cplusplus
	}
#endif

#endif