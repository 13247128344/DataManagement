#ifndef __SMART_FRAME_RENDER_H__
#define __SMART_FRAME_RENDER_H__


//�����κ�����֡��ʼ��Ⱦǰִ�У������ʼ��ʱִ��
extern "C" _declspec(dllexport) void SFR_initSmartRenderSDK();

///�����κ�����֡������Ⱦ��ִ�У�����˳�ʱִ��
extern "C" _declspec(dllexport) void SFR_cleanSmartRenderSDK();

//��һ��ͨ����Ԥ����ط�ʱִ�У�lPortΪ�ôβ��ŵĻطſⲥ�Ŷ˿ڣ�����ͬ������ӿڷ��ڻطſ��I8_MP4Play_Play(LONG nPort, HWND hWnd)֮ǰִ��
extern "C" _declspec(dllexport) void SFR_initOnceSmartRender(long lPort);

//�ر�һ��ͨ����Ԥ����ط�ʱִ�У�����ӿڷ��ڻطſ��I8_MP4Play_Stop(LONG nPort)֮ǰִ��
extern "C" _declspec(dllexport) void SFR_cleanOnceSmartRender(long lPort);

//�ϲ�Ӧ�ڡ�����Ƶ�����ص�������øýӿں������Żطſ��I8_MP4Play_InputData�ӿں���ִ��  lpBuffer������ָ֡��   dwBufSize������֡����
//ע����Ȼ�˽ӿ��ڲ�ֻ��������֡���ϲ������֡ʱ���������жϣ�ֻ��������֡������֡�ͽ��֡��
extern "C" _declspec(dllexport) void SFR_inputSmartData(long lPort,unsigned char *lpBuffer,int dwBufSize);

//�ϲ�Ӧ�ڡ����ſ�Ļ�ͼ�ص�������øýӿں���  hDC�����ſھ��  iVideoWidth*iVideoHeigth����Ƶ�ֱ���  iWindowWidth*iWindowHeight�����Ŵ��ڷֱ���  ��ػطſ�ӿڣ�I8_MP4Play_RigisterDrawFunEx
extern "C" _declspec(dllexport) void SFR_drawSmartData(long lPort, HDC hDC,unsigned int iVideoWidth , unsigned int iVideoHeigth, unsigned int iWindowWidth, unsigned int iWindowHeight);

//�Ƿ���ʾ���ܹ���֡����֡����Ե��β��ţ�Ĭ�������õ�
enum SmartDataType {SmartRule,SmartResult,SmartBoth};
extern "C" _declspec(dllexport) void SFR_enableOnceRender(long lPort,bool isEnable,SmartDataType smartDataType);

//�Ƿ���ʾ���ܹ���֡����֡��������в���
extern "C" _declspec(dllexport) void SFR_enableRender(bool isEnable,SmartDataType smartDataType);

//���ʽ���
//���ܹ���֡���趨�����ܼ��������ݣ������㷨����ʱ��ʹ�ã�ͬʱҲ��Ҫ���ָ��û����������û��޸ģ������ǲ���ġ����ڶ���֡ͷ�����ͺ�Ϊ0x1b��ö��ֵAntsPktSmartIFrames��

//���ܽ��֡�������㷨����󵯳��Ľ�����ݣ���Ƶ֡+����֡-->���֡����ſ�����ô��⣩����Ҫ���ָ��û�����������Ƶ֡�ж�Ӧ�Ĺ�ϵ����Ⱦ��Ƶ֡��ͬʱȥ��Ⱦ���֡��
//���ڶ���֡ͷ�����ͺ�Ϊ0x1c��ö��ֵAntsPktSmartPFrames��
#endif