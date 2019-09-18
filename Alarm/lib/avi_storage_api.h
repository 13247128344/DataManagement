#ifndef AVI_STORAGE_API_H
#define AVI_STORAGE_API_H


#ifdef WIN32
#ifdef __cplusplus
#if defined( AVI_STORAGE_EXPORTS)
#define AAS_API extern "C" __declspec(dllexport)
#else
#define AAS_API extern "C"
#endif
#else
#define AAS_API
#endif
#define AAS_CALL __stdcall
#else/*Linux*/
#ifdef __cplusplus
#define AAS_API extern "C"
#else
#define AAS_API
#endif
#define AAS_CALL
#endif

////////////////////////////////////////////////////////////////////////////////
// �궨��
////////////////////////////////////////////////////////////////////////////////

// �������
#define IN
// �������
#define OUT
// �����������
#define INOUT

// ������Ϊ�����
#define MAX_AVI_SAVEAS_HANDLE_CNT		(32)

// ���¼���ļ���ѯ�����
#define MAX_REC_FILE_QUERY_HANDLE_CNT	(8)


// ���¼���ļ�·������
#define MAX_REC_FILE_NAME_LEN	(256)


// ¼������
#define ANTS_RECORDTYPE_BEGIN			(0)
#define	ANTS_RECORDTYPE_TIMER			(1)
#define	ANTS_RECORDTYPE_MOTION			(2)
#define	ANTS_RECORDTYPE_ALARM			(3)
#define	ANTS_RECORDTYPE_MOTIONORALARM	(4)
#define	ANTS_RECORDTYPE_MOTIONANDALARM	(5)
#define	ANTS_RECORDTYPE_COMMAND			(6)
#define	ANTS_RECORDTYPE_MANUAL			(7)
#define	ANTS_RECORDTYPE_ALL				(8)
#define ANTS_RECORDTYPE_END				(9)

////////////////////////////////////////////////////////////////////////////////
// ö�ٶ���
////////////////////////////////////////////////////////////////////////////////

// �ӿڷ���ֵ����
typedef enum
{
	avis_ret_ok = 0,
	avis_ret_failed = -1000,
	avis_ret_sdk_no_init,
	avis_ret_no_mem,
	avis_ret_invalid_para,
	avis_ret_invalid_handle,
	avis_ret_invalid_file,
	avis_ret_buffer_too_small,
	avis_ret_no_handle,
	avis_ret_has_started,
	avis_ret_not_start,
	avis_ret_has_create,
	avis_ret_not_create,
	avis_ret_no_more_file,
	avis_ret_no_more_data,
}ants_avis_ret_code;

// ¼�����ȼ�
typedef enum
{
	eRecPriority_Lowest,
	eRecPriority_Low,
	eRecPriority_Normal,
	eRecPriority_High,
	eRecPriority_Highest,
}eRecPriority;

////////////////////////////////////////////////////////////////////////////////
// �ṹ�嶨��
////////////////////////////////////////////////////////////////////////////////

// ¼�������Ϣ
typedef struct tagRecPartitionInfo
{	
	char acPath[32];						// ����·��, ��"/dev/hda1/"��"c:/"...
	eRecPriority ePriority;					// ¼�����ȼ�, ��ֵԽ�����ȼ�Խ��
	unsigned long long nRecCanUseSpace;		// ¼���ʹ�õĿռ䣨�ֽڣ�
	unsigned long long nPartitionTotalSpace;// �����ܴ�С���ֽڣ�
	DWORD nRecMaxSaveHour;					// ¼����󱣴�ʱ�� 0xFFFFFFFF-������ֹͣ¼�� 0-���������ǣ� other-¼����󱣴�ʱ�䣨Сʱ��
}PartitionInfo;

// ¼���豸��ʶ
typedef struct tagRecDeviceId
{
	char acDeviceId[64];					// �豸id��ants���豸һ�㴫���豸���к�
}RecDeviceId;

// ¼���ļ���Ϣ
typedef struct tagRecFileInfo
{
	char acPath[MAX_REC_FILE_NAME_LEN];		// ¼���ļ����ƣ���������·����
	unsigned long lBeginTime;				// ��ʼʱ��
	unsigned long lEndtime;					// ����ʱ��
	unsigned int nFileSize;					// �ļ���С
	unsigned int nRecTypeMask;				// ¼���������루Ԥ����
}RecFileInfo;

/*¼��Ƭ����Ϣ�ṹ��*/
typedef struct _PSS_REGSEG
{
	time_t             tBeginTime; //��ʼʱ���
	time_t             tEndTime;   //����ʱ���
	int                iRecType;   //��ʱ��ε�¼������
	struct _PSS_REGSEG *ptNext;
} PSS_REGSEG, *pPPS_REGSEG;

////////////////////////////////////////////////////////////////////////////////
// �ص���������
////////////////////////////////////////////////////////////////////////////////

/*!
* \brief ���̷������ص�����
* \param ��
* \return �洢�ⲻ���ûص������ķ���ֵ
*/
#ifdef WIN32
typedef int (*ANTS_DATAINPUT_DISKFULL_CALLBACK)(DWORD dwUserData);
#else
typedef int (*ANTS_DATAINPUT_DISKFULL_CALLBACK)();
#endif


/*!
* \brief ���ݵ����ص�����
* \param hDataPopper ���ݵ��������
* \param iChannel ���ݶ�Ӧ��ͨ��
* \param bIndexFrame �Ƿ��ǽ���������֡���ؼ�֡��
* \param wFrameType ���ݶ�Ӧ������
* \param tFrameTime ����֡�ľ���ʱ��أ���ȷ��Ϊ��
* \param pBuf ���ݶ�Ӧ�Ļ�������ַ
* \param dwSize ���ݶ�Ӧ�Ĵ�С
* \param EventID �������¼����ͣ���������������ݵ�����EventIDΪDATAPOP_EVENT_NONE�������¼�ʱ��֡��صĲ�����Ч
* \param pContext ����������ʱ�����������
* \return �洢�ⲻ���ûص������ķ���ֵ
*/
typedef int (*ANTS_AVI_DATAPOP_CALLBACK)(HANDLE hDataPopper, int iChannel, BOOL bIndexFrame, unsigned short wFrameType, time_t tFrameTime, unsigned char *pBuf, unsigned long dwSize, unsigned long EventID, void *pContext);


////////////////////////////////////////////////////////////////////////////////
// �ӿڶ���
////////////////////////////////////////////////////////////////////////////////

/*!
* \brief
* �洢ϵͳ�ĳ�ʼ��.
* \param sDeviceSerial ��ǰδʹ�ã�������Ϊ��
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_Init(const char *sDeviceSerial);


/*!
* \brief
* �洢ϵͳ�ķ���ʼ��.
* \param sDeviceSerial ��ǰδʹ�ã�������Ϊ��
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_UnInit(const char *sDeviceSerial);



/*!
* \brief ���¼������������ͬ·����¼������Ѿ�������ˣ���ýӿڽ����·���¼�����
* \param pInfo ����ӵķ�����Ϣ
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_AddRecPartition(PartitionInfo *pInfo);



/*!
* \brief ɾ��¼�����
* \param pInfo ��ɾ���ķ�����Ϣ��ע�����·����������ʱ�ı���һ��
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_DelRecPartition(char *pPath);



/*!
* \brief ��ȡ����¼����ʹ�ÿռ�
* \param pInfo ����·������������ʱ�ı���һ��
* \param pRecUsedSpace ���������¼����ʹ�õĿռ䣨�ֽڣ�
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_GetRecUsedSpace(char *pPath, unsigned long long *pRecUsedSpace);


/*!
* \brief �����豸�������ͬ���豸����һ�θýӿھͿ����ˣ��������Ҫ�����豸��������ô˽ӿ�
* \param pRecDev �������������¼���豸�������ͬ��pDeviceIdֵ�᷵����ͬ���豸���ֵ
* \param pDeviceId ¼���豸��ʶ��һ�㲻��Ҫ�����豸ʱ������Ҫ���ô˲���������Ҫ�����豸ʱ���ô˲��������Ҹò����ܹ�Ψһ��ʶһ̨�豸
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
#ifdef WIN32
AAS_API int AAS_CALL ANTS_AviFile_CreateDevHandle(HANDLE *pRecDev, RecDeviceId *pDeviceId);
#endif


/*!
* \brief �����豸����������豸������Ҫʹ��avi_storage��api�ӿ�ʱ�������豸������������Ҫ�����豸��������ô˽ӿ�
* \param hRecDev ¼���豸�������ANTS_AviFile_RecStart�ӿڷ���
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
#ifdef WIN32
AAS_API int AAS_CALL ANTS_AviFile_ReleaseDevHandle(HANDLE hRecDev);
#endif


/*!
* \brief ��ָ����¼�����Ϳ�ʼ¼�������ͨ����¼���Ѿ������ˣ�����øýӿڱ�ʾ�����µ�¼������
* \param iChannel ¼��ͨ����
* \param iRecType ¼������
* \param hRecDev �豸�������ANTS_AviFile_CreateDevHandle�ӿڷ��أ�ȱʡʱ��ʾ����Ҫ�����豸
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
#ifdef WIN32
AAS_API int AAS_CALL ANTS_AviFile_RecStart(int iChannel, int iRecType, HANDLE hRecDev);
#else
AAS_API int AAS_CALL ANTS_AviFile_RecStart(int iChannel, int iRecType);
#endif


/*!
* \brief ������д��¼��ͨ����
* \param iChannel ¼��ͨ����
* \param pFrameHead ֡ͷ����ָ��
* \param nHeadLen ֡ͷ���ݳ���
* \param pFrameData ֡����ָ�룬������֡ͷ
* \param nDataLen ֡���ݳ��ȣ�������֡ͷ
* \param tFrameTime д��֡�ľ���ʱ��أ���ȷ��Ϊ��
* \param tFrameTimeInUs д��֡�ľ���ʱ��أ����ڵľ���(΢��)
* \param hRecDev �豸�������ANTS_AviFile_CreateDevHandle�ӿڷ��أ�ȱʡʱ��ʾ����Ҫ�����豸
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
#ifdef WIN32
AAS_API int AAS_CALL ANTS_AviFile_DataInput(int iChannel, char *pFrameHead, int nHeadLen, char *pFrameData, int nDataLen, DWORD dwCurTimeSec, DWORD dwCurTimeUsec, HANDLE hRecDev);
#else
AAS_API int AAS_CALL ANTS_AviFile_DataInput(int iChannel, char *pFrameHead, int nHeadLen, char *pFrameData, int nDataLen, DWORD dwCurTimeSec, DWORD dwCurTimeUsec);
#endif


/*!
* \brief ָֹͣ��¼��ͨ����¼��
* \param iChannel ¼��ͨ����
* \param hRecDev �豸�������ANTS_AviFile_CreateDevHandle�ӿڷ��أ�ȱʡʱ��ʾ����Ҫ�����豸
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
#ifdef WIN32
AAS_API int AAS_CALL ANTS_AviFile_RecStop(int iChannel, HANDLE hRecDev);
#else
AAS_API int AAS_CALL ANTS_AviFile_RecStop(int iChannel);
#endif



/*!
* \brief ���ָ��ͨ����ָ��ʱ�����ָ��¼�����͵�¼��Ƭ��
* \param iChannel ¼��ͨ����
* \param tBeginTime ��ʼʱ��
* \param tEndTime ����ʱ��, ע��: ��ʼʱ��ͽ���ʱ��֮���������, ������֮��ó���24Сʱ
* \param iRecType ¼������
* \param pRecSegHead ���¼��Ƭ�εĻ�����ͷָ��
* \param pRecSegCount ���淵�ػ�ȡƬ�ϵĸ���
* \param hRecDev �豸�������ANTS_AviFile_CreateDevHandle�ӿڷ��أ�ȱʡʱ��ʾ����Ҫ�����豸
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
#ifdef WIN32
AAS_API int AAS_CALL ANTS_AviFile_GetRecSegList(int iChannel, time_t tBeginTime, time_t tEndTime, int iRecType, PSS_REGSEG **pRecSegHead, int *pRecSegCount, HANDLE hRecDev);
#else
AAS_API int AAS_CALL ANTS_AviFile_GetRecSegList(int iChannel, time_t tBeginTime, time_t tEndTime, int iRecType, PSS_REGSEG **pRecSegHead, int *pRecSegCount);
#endif



/*!
* \brief �ͷ�¼��Ƭ����Ϣ�б���ռ�ڴ�
* \param pRecSegHead ���¼��Ƭ�εĻ�����ͷָ��
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_ReleaseRecSegList(PSS_REGSEG *pRecSegHead);



/*!
* \brief �������ݵ�����
* \param nRefChan �ο�ͨ��(���Բ����ã�ֵΪ-1��ʾ������)
* \param tStartSeekTime ��ʼ�������ݵ�ʱ��
* \param tEndSeekTime �������ݵĽ���ʱ�䡣����ʱ��Ϊ0ʱ�����ݽ��ж�̬�������������ʱ����һ��δ��ʱ�䣬�򵽴ﵱǰʱ��ʱ��ͨ���ص��ӿڸ�֮���¼���
					 ע��: ��ʼʱ��ͽ���ʱ��֮���������, ������֮��ó���24Сʱ
* \param cbReplayCallback �趨���ݵ����Ļص������ӿڣ����������ݰ������������ͨ����֡���͡�ʱ��ء��¼����ͣ������µ�ʱ��Ƭ/��ѯ����/��ǰ���ݲ�ѯ��ϵȣ��Ȳ�����ʽ�ͻط��߳�
* \param bDynPop �Ƿ�̬��λ��������������Ϻ��Ƿ��������¶�λ���������������ڻط�ʱ������ΪTRUE�����ڱ���ʱ������ΪFALSE
* \param pContext �����ģ��ϲ�������Դ���˲������ڵ����ص��л�����ò���
* \param hRecDev �豸�������ANTS_AviFile_CreateDevHandle�ӿڷ��أ�ȱʡʱ��ʾ����Ҫ�����豸
* \param bNeedSync �Ƿ���Ҫͬ�����ط�ʱһ������Ϊtrue, ���Ϊʱһ������Ϊfalse
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
#ifdef WIN32
AAS_API int AAS_CALL ANTS_AviFile_DataPopCreate(HANDLE *pDataPopper, int nRefChan, time_t tStartSeekTime, time_t tEndSeekTime, ANTS_AVI_DATAPOP_CALLBACK cbReplayCallback, BOOL bDynPop, void *pContext, HANDLE hRecDev, BOOL bNeedSync = true);
#else
AAS_API int AAS_CALL ANTS_AviFile_DataPopCreate(HANDLE *pDataPopper, int nRefChan, time_t tStartSeekTime, time_t tEndSeekTime, ANTS_AVI_DATAPOP_CALLBACK cbReplayCallback, BOOL bDynPop, void *pContext);
#endif



/*!
* \brief ��ӵ������ݵ�ͨ��
* \param hDataPopper ���ݵ������ľ��
* \param iChannel ͨ����
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_DataPopChanAdd(HANDLE hDataPopper, int iChannel);



/*!
* \brief �Ƴ��������ݵ�ͨ��
* \param hDataPopper ���ݵ������ľ��
* \param iChannel ͨ����
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_DataPopChanDel(HANDLE hDataPopper, int iChannel);



/*!
* \brief ��ӵ������ݵ�¼������
* \param hDataPopper ���ݵ������ľ��
* \param iRecType ¼������
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_DataPopRecTypeAdd(HANDLE hDataPopper, unsigned int iRecType);



/*!
* \brief �Ƴ��������ݵ�¼������
* \param hDataPopper ���ݵ������ľ��
* \param iRecType ¼������
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_DataPopRecTypeDel(HANDLE hDataPopper, unsigned int iRecType);



/*!
* \brief ���ݵ�������λ(�趨�˲ο�ͨ�������ο�ͨ����λ��δ��ο�ͨ������λΪʱ���ϵ�һ������������ͨ��)
* \param hDataPopper ���ݵ������ľ��
* \param SeekTime ���õĵ������ݵ�ʱ��
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_DataPopTimeSeek(HANDLE hDataPopper, time_t SeekTime);


/*!
* \brief �������ݵ�������
* \param hDataPopper ���ݵ������ľ��
* \param bKeyFrame ���ݵ����������ΪTRUE����󵯳������ΪFALSE����ǰ��������δʵ�֣�
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_DataPopSetDirect(HANDLE hDataPopper, BOOL bSequential);


/*!
* \brief ���ݵ���ʱ�Ƿ�ֻ�����ؼ�֡
* \param hDataPopper ���ݵ������ľ��
* \param bKeyFrame �Ƿ�ֻ�����ؼ�֡�����ΪTRUE��ֻ�����ؼ�֡�����ΪFALSE�򵯳�����֡��
* \param PopKeyInterval ��ֻ�����ؼ�֡ʱ���ò�����Ч����ʾͨ������ÿ�����ٹؼ�֡����һ������ֵ������0-3��0��ʾȫ������
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_DataPopSetKeyFrame(HANDLE hDataPopper, BOOL bKeyFrame, unsigned long PopKeyInterval);


/*!
* \brief ��ȡ�������������ݵ�������(��λ���ֽ�)
* \param hDataPopper ���ݵ������ľ��
* \param pSize ������
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_DataPopGetDataSize(HANDLE hDataPopper, unsigned long long *pSize);


/*!
* \brief ��ʼ���ݵ���
* \param hDataPopper ���ݵ������ľ��
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_DataPopStart(HANDLE hDataPopper);



/*!
* \brief ֹͣ���ݵ���
* \param hDataPopper ���ݵ������ľ��
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_DataPopStop(HANDLE hDataPopper);



/*!
* \brief �ͷ����ݵ�����
* \param hDataPopper ���ݵ������ľ��
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_DataPopRelease(HANDLE hDataPopper);



/*!
* \brief
* ���ô��̷�������ص�
* \param cbDiskGroupFullCallback �ص��������
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
#ifdef WIN32
AAS_API int AAS_CALL ANTS_AviFile_SetDiskGroupFullCallback(ANTS_DATAINPUT_DISKFULL_CALLBACK cbDiskGroupFullCallback, DWORD dwUserData);
#else
AAS_API int AAS_CALL ANTS_AviFile_SetDiskGroupFullCallback(ANTS_DATAINPUT_DISKFULL_CALLBACK cbDiskGroupFullCallback);
#endif


/*!
* \brief ��ȡ�Ƿ���ָ������(һ������һ����)��¼������
* \param tBeginTime ָ��ʱ��εĿ�ʼʱ��
* \param numOfdays ����ʼ�쿪ʼ������(24Сʱ)
* \param pResult ���ؽ��������λ�뷽ʽbit0-bit30�ֱ��Ӧ31��
* \param hRecDev �豸�������ANTS_AviFile_CreateDevHandle�ӿڷ��أ�ȱʡʱ��ʾ����Ҫ�����豸
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
#ifdef WIN32
AAS_API int AAS_CALL ANTS_AviFile_JudgeIFHaveDataByDays(time_t tBeginTime, unsigned int numOfdays, unsigned int *pResult, HANDLE hRecDev);
#else
AAS_API int AAS_CALL ANTS_AviFile_JudgeIFHaveDataByDays(time_t tBeginTime, unsigned int numOfdays, unsigned int *pResult);
#endif



/*!
* \brief ��֡���ݱ����avi�ļ�
* \param pSaveHandle ������������ر�����
* \param pFullName �������ļ�·��
��pFullName����".avi"��β�ĺϷ��ļ���ʱ���ӿ�ֻ����洢¼�����ݵ�ָ�����Ƶ�avi�ļ��У���ʱ�л�¼���ļ����ϲ������
����pFullName�ǺϷ���·����ʱ���ӿڻ��ڸ�·���´洢avi¼���ļ����Զ��л��ļ�
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_SaveStart(HANDLE *pSaveHandle, char *pFullName);


/*!
* \brief ��֡���ݱ����ָ�����Ƶ�avi�ļ�
* \param pSaveHandle ������������ر�����
* \param pFullName �������ļ�·������������ļ����Ƿ���".avi"��β��һ�ɽ�avi��ʽ�����ݴ洢��ָ�����Ƶ��ļ��У���ʱ�л�¼���ļ����ϲ����
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_SaveStart_ByName(HANDLE *pSaveHandle, char *pFullName);


/*!
* \brief ������д��avi�ļ���
* \param hSaveHandle ����������ANTS_AviFile_SaveStart�ӿڷ���
* \param pFrameHead ֡ͷ����ָ��
* \param nHeadLen ֡ͷ���ݳ���
* \param pFrameData ֡����ָ�룬������֡ͷ
* \param nDataLen ֡���ݳ��ȣ�������֡ͷ
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_SaveInput(HANDLE hSaveHandle, char *pFrameHead, int nHeadLen, char *pFrameData, int nDataLen);


/*!
* \brief ָֹͣ��¼��ͨ����¼��
* \param hSaveHandle ����������ANTS_AviFile_SaveStart�ӿڷ���
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_SaveStop(HANDLE hSaveHandle);



/*!
* \brief ��ʼ��ѯָ��ͨ����ָ�����ڵ�¼���ļ���ע�⣺����¼���avi�ļ����ᱻ����
* \param pQuery ��ѯ������������
* \param iChannel ¼��ͨ���ţ���0��ʼ��-1��ʾ��ѯ����ͨ����¼���ļ�
* \param tDate ¼���ѯ���ڣ�-1��ʾ��ѯ�������ڵ�¼���ļ�
* \param hRecDev �豸�������ANTS_AviFile_CreateDevHandle�ӿڷ���
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
#ifdef WIN32
AAS_API int AAS_CALL ANTS_AviFile_QueryRecFilesStart(OUT HANDLE *pQuery, IN int iChannel, IN time_t tDate, IN HANDLE hRecDev);
#else
AAS_API int AAS_CALL ANTS_AviFile_QueryRecFilesStart(OUT HANDLE *pQuery, IN int iChannel, IN time_t tDate);
#endif


/*!
* \brief ��ȡ��һ��¼���ļ���Ϣ
* \param hQuery ��ѯ�����ͨ��ANTS_AviFile_QueryRecFilesStart�ӿڷ���
* \param pInfo ��ѯ����¼���ļ���Ϣ
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_GetNextRecFile(IN HANDLE hQuery, OUT RecFileInfo *pInfo);


/*!
* \brief ֹͣ��ѯ¼���ļ�
* \param hQuery ��ѯ�����ͨ��ANTS_AviFile_QueryRecFilesStart�ӿڷ���
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_QueryRecFilesStop(IN HANDLE hQuery);



/*!
* \brief ɾ��ָ�����Ƶ�¼���ļ�
* \param pFullPath ¼���ļ�������·��
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
AAS_API int AAS_CALL ANTS_AviFile_DelAviFileByName(IN char *pFullPath);


/*!
* \brief ɾ��ָ������������¼���ļ�
* \param iChannel ¼��ͨ���ţ���0��ʼ��-1��ʾɾ������ͨ����¼���ļ�
* \param tDate ¼���ѯ���ڣ�-1��ʾɾ���������ڵ�¼���ļ�
* \param hRecDev �豸�������ANTS_AviFile_CreateDevHandle�ӿڷ���
* \return �ɹ�����0��ʧ�ܵĴ�������ο�ants_avis_ret_code
*/
#ifdef WIN32
AAS_API int AAS_CALL ANTS_AviFile_DelAviFiles(IN int iChannel, IN time_t tDate, IN HANDLE hRecDev);
#else
AAS_API int AAS_CALL ANTS_AviFile_DelAviFiles(IN int iChannel, IN time_t tDate);
#endif

#endif // end of AVI_STORAGE_API_H
