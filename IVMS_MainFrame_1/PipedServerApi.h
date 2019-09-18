#ifndef __ANTS_NAMED_PIPE_SERVER__
#define __ANTS_NAMED_PIPE_SERVER__

#include <windows.h>


/*
//�ӽ��̷��������JSON���ݸ�ʽ
{
	"msgType":"",					//��Ϣ����
	"from": "",						//��Ϣ��Դ
	"target": "ivms_clientMain",  //����          
	"msgData":{}					//��Ϣ���� ������Ϣ���������� ���� "msgData":{"data":"msgContext"}
}

	msgType
		0	�ӽ�����������ҪǶ�׵Ľ�����(WId)������������    
			msgData : { "data":[{"widget1":"1321"},{"widget2":"122331"}... ] }  "��������":"����WId" 
		1   ��Ϣ����

	target  (msgTypeΪ1ʱ��Ч)
		"ivms_clientMain"   //�ͻ�������� msgData : { "data" : ""}
		"ivms_serverMain"   //���������� msgData : { "topic":"","cmd":"","token":"","connectTime":12,"data":"ʵ����Ҫ���������" }
		"...."              //�ͻ�����������    //��ʱ��ʹ��

//�������ݸ�ʽ
{
	"result" : "",              //��������
	"data":{}					//��������  
}

	result   0      �ɹ�
			 ��0    ʧ��      
*/

/******************************************************************
					����ֵ�궨��
*******************************************************************/
#define NAMED_PIPE_NO_ERROR					0			//û�д���
#define NAMED_PIPE_FAILED					1			//ʧ��		
#define NAMED_PIPE_WRONG_PARAMETER			2			//��������
#define NAMED_PIPE_OUTBUFFERSIZE_SMALL		3			//����������ڴ�̫С
#define NAMED_PIPE_TIMEOUT					4			//��ʱ
#define NAMED_PIPE_WRONG_JSON_FORMAT		5			//JSON��������
#define NAMED_PIPE_WRONG_PIPE_NAME			6			//�����ܵ����ƴ���
#define NAMED_PIPE_CONNECT_FAILED			7			//���������ܵ�����ʧ��

/********************************************************************************
					�ص���������	
*********************************************************************************/
//�����ܵ�������յ��ͻ������ݺ���øûص�����
typedef void(__stdcall *NamedPipeMsgCallback)(char* inBuffer /*������������ͷ�*/, int inBufferSize, char* outBuffer /*������������ͷ�*/, int outBufferSize, int* outSize);

#define NAMEDPIPE_API extern "C" __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif
	NAMEDPIPE_API bool	ants_named_pipe_init();
	NAMEDPIPE_API bool	ants_named_pipe_setup(char* pipeServerName);
	NAMEDPIPE_API void	ants_named_pipe_setCallback(NamedPipeMsgCallback pFunc);
	NAMEDPIPE_API DWORD  ants_named_pipe_sendMsgToServer(char* serverName, char* inBuffer/*������������ͷ�*/, int inBufferSize, char* outBuffer/*������������ͷ�*/, int outBufferSize, int *outSize);
	NAMEDPIPE_API DWORD  ants_named_pipe_sendMsgToServerNotNeedReply(char* serverName, char* inBuffer/*������������ͷ�*/, int inBufferSize);
#ifdef __cplusplus
	}
#endif

#endif