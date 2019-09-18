#ifndef __SMART_FRAME_RENDER_H__
#define __SMART_FRAME_RENDER_H__


//放在任何智能帧开始渲染前执行，软件初始化时执行
extern "C" _declspec(dllexport) void SFR_initSmartRenderSDK();

///放在任何智能帧结束渲染后执行，软件退出时执行
extern "C" _declspec(dllexport) void SFR_cleanSmartRenderSDK();

//打开一个通道的预览或回放时执行，lPort为该次播放的回放库播放端口，以下同；这个接口放在回放库的I8_MP4Play_Play(LONG nPort, HWND hWnd)之前执行
extern "C" _declspec(dllexport) void SFR_initOnceSmartRender(long lPort);

//关闭一个通道的预览或回放时执行；这个接口放在回放库的I8_MP4Play_Stop(LONG nPort)之前执行
extern "C" _declspec(dllexport) void SFR_cleanOnceSmartRender(long lPort);

//上层应在“视音频码流回调”里调用该接口函数，放回放库的I8_MP4Play_InputData接口后面执行  lpBuffer：数据帧指针   dwBufSize：数据帧长度
//注：虽然此接口内部只处理智能帧，上层最好塞帧时还是做个判断，只需塞智能帧（规则帧和结果帧）
extern "C" _declspec(dllexport) void SFR_inputSmartData(long lPort,unsigned char *lpBuffer,int dwBufSize);

//上层应在“播放库的画图回调”里调用该接口函数  hDC：播放口句柄  iVideoWidth*iVideoHeigth：视频分辨率  iWindowWidth*iWindowHeight：播放窗口分辨率  相关回放库接口：I8_MP4Play_RigisterDrawFunEx
extern "C" _declspec(dllexport) void SFR_drawSmartData(long lPort, HDC hDC,unsigned int iVideoWidth , unsigned int iVideoHeigth, unsigned int iWindowWidth, unsigned int iWindowHeight);

//是否显示智能规则帧或结果帧，针对单次播放，默认是启用的
enum SmartDataType {SmartRule,SmartResult,SmartBoth};
extern "C" _declspec(dllexport) void SFR_enableOnceRender(long lPort,bool isEnable,SmartDataType smartDataType);

//是否显示智能规则帧或结果帧，针对所有播放
extern "C" _declspec(dllexport) void SFR_enableRender(bool isEnable,SmartDataType smartDataType);

//名词解释
//智能规则帧：设定的智能检测规则数据，智能算法运算时需使用，同时也需要呈现给用户看。除非用户修改，否则是不变的。它在恩智帧头中类型号为0x1b（枚举值AntsPktSmartIFrames）

//智能结果帧：智能算法运算后弹出的结果数据（视频帧+规则帧-->结果帧，大概可以这么理解），需要呈现给用户看。它与视频帧有对应的关系，渲染视频帧的同时去渲染结果帧。
//它在恩智帧头中类型号为0x1c（枚举值AntsPktSmartPFrames）
#endif