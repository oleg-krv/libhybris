/*
 * Copyright (C) 2013 Siarhei Siamashka <siarhei.siamashka@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <dlfcn.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>

#include <hybris/common/binding.h>
#include <libmxmnetsdk/mxmnetsdk.h>

HYBRIS_LIBRARY_INITIALIZE (mxmnetsdk_so,         "/system/lib/libmxmnetsdk.so");


//*** */SDK初始化
//H264_DVR_API long CALL_METHOD H264_DVR_Init(fDisConnect cbDisConnect, unsigned long dwUser);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, long,    H264_DVR_Init, fDisConnect, unsigned long);

//*** */SDK退出清理
//H264_DVR_API bool CALL_METHOD H264_DVR_Cleanup();
HYBRIS_IMPLEMENT_FUNCTION0(mxmnetsdk_so, bool,    H264_DVR_Cleanup);

//获取错误信息
//H264_DVR_API long CALL_METHOD H264_DVR_GetLastError();
HYBRIS_IMPLEMENT_FUNCTION0(mxmnetsdk_so, long,    H264_DVR_GetLastError);

// 设置连接设备超时时间和尝试次数
/*
	nWaitTime:单位ms不设置时默认5000ms,
	nTryTimes:次数,不设置时默认3次
*/
//H264_DVR_API bool CALL_METHOD H264_DVR_SetConnectTime(long nWaitTime, long nTryTimes);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_SetConnectTime, long, long);

//登陆设备
/*
	socketType 参考类型 SocketStyle，默认是0
*/
//H264_DVR_API long CALL_METHOD H264_DVR_Login(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
//                                             LPH264_DVR_DEVICEINFO lpDeviceInfo, int *error,int socketType DEF_PARAM(0));
HYBRIS_IMPLEMENT_FUNCTION7(mxmnetsdk_so, long,    H264_DVR_Login, char*, unsigned short, char*, char*, LPH264_DVR_DEVICEINFO, int*, int);

//向设备注册扩展接口
/*
	增加登陆类型 0==web 1 ==升级工具 2 == 搜索工具  102 == 外部加密，内部就不用加密了
*/
//H264_DVR_API long CALL_METHOD H264_DVR_LoginEx(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
//                                               LPH264_DVR_DEVICEINFO lpDeviceInfo, int nType, int *error);

HYBRIS_IMPLEMENT_FUNCTION7(mxmnetsdk_so, long,    H264_DVR_LoginEx, char*, unsigned short, char*, char*, LPH264_DVR_DEVICEINFO, int, int*);

//登陆接口V2版本
//H264_DVR_API long CALL_METHOD H264_DVR_LoginEx_V2(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
//                                                  LPH264_DVR_DEVICEINFO lpDeviceInfo, int nType, int *error,int socketType);
HYBRIS_IMPLEMENT_FUNCTION8(mxmnetsdk_so, long,    H264_DVR_LoginEx_V2, char*, unsigned short, char*, char*, LPH264_DVR_DEVICEINFO, int, int*, int);

//客户云登陆接口
//H264_DVR_API long CALL_METHOD H264_DVR_Login_Cloud(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
//                                                   LPH264_DVR_DEVICEINFO lpDeviceInfo, int *error,char* uuid);
HYBRIS_IMPLEMENT_FUNCTION7(mxmnetsdk_so, long,    H264_DVR_Login_Cloud, char*, unsigned short, char*, char*, LPH264_DVR_DEVICEINFO, int*, int*);

//向设备注销
//H264_DVR_API long CALL_METHOD H264_DVR_Logout(long lLoginID);
HYBRIS_IMPLEMENT_FUNCTION1(mxmnetsdk_so, long,    H264_DVR_Logout, long);

//设置接收DVR信息回调, 例如报警信息,以ID号区分
//H264_DVR_API bool CALL_METHOD H264_DVR_SetDVRMessCallBack(fMessCallBack cbAlarmcallback, unsigned long lUser);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_SetDVRMessCallBack, fMessCallBack, unsigned long);

//建立报警上传通道
//H264_DVR_API long CALL_METHOD H264_DVR_SetupAlarmChan(long lLoginID);
HYBRIS_IMPLEMENT_FUNCTION1(mxmnetsdk_so, long,    H264_DVR_SetupAlarmChan, long);

//关闭报警上报
//H264_DVR_API bool CALL_METHOD H264_DVR_CloseAlarmChan(long lLoginID);
HYBRIS_IMPLEMENT_FUNCTION1(mxmnetsdk_so, bool,    H264_DVR_CloseAlarmChan, long);

//远程配置设备接口 配置类型见SDK_CONFIG_TYPE
//H264_DVR_API long  CALL_METHOD H264_DVR_GetDevConfig(long lLoginID, unsigned long dwCommand, int nChannelNO, char * lpOutBuffer, unsigned long dwOutBufferSize, unsigned long* lpBytesReturned,int waittime DEF_PARAM(1000));
HYBRIS_IMPLEMENT_FUNCTION7(mxmnetsdk_so, long,    H264_DVR_GetDevConfig, long, unsigned long, int, char*, unsigned long, unsigned long*, int);
//H264_DVR_API long  CALL_METHOD H264_DVR_SetDevConfig(long lLoginID, unsigned long dwCommand, int nChannelNO, char * lpInBuffer, unsigned long dwInBufferSize, int waittime DEF_PARAM(1000));
HYBRIS_IMPLEMENT_FUNCTION6(mxmnetsdk_so, long,    H264_DVR_SetDevConfig, long, unsigned long, int, char*, unsigned long, int);

//跨网段设置设备配置，目前只支持对网络配置进行设置    SDK_CONFIG_NET_COMMON_V3,nChannelNO:1临时保存,其他为永久保存
//H264_DVR_API long CALL_METHOD H264_DVR_SetConfigOverNet(unsigned long dwCommand, int nChannelNO, char * lpInBuffer, unsigned long dwInBufferSize, int waittime DEF_PARAM(1000));
HYBRIS_IMPLEMENT_FUNCTION5(mxmnetsdk_so, long,    H264_DVR_SetConfigOverNet, unsigned long, int, char*, unsigned long, int);

//日志查询
//H264_DVR_API bool CALL_METHOD H264_DVR_FindDVRLog(long lLoginID, SDK_LogSearchCondition *pFindParam, SDK_LogList *pRetBuffer, long lBufSize, int waittime DEF_PARAM(2000));
HYBRIS_IMPLEMENT_FUNCTION5(mxmnetsdk_so, bool,    H264_DVR_FindDVRLog, long, SDK_LogSearchCondition*, SDK_LogList*, long, int);

//打开实时预览
//H264_DVR_API long CALL_METHOD H264_DVR_RealPlay(long lLoginID, LPH264_DVR_CLIENTINFO lpClientInfo);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, long,    H264_DVR_RealPlay, long, LPH264_DVR_CLIENTINFO);
//H264_DVR_API bool CALL_METHOD H264_DVR_StopRealPlay(long lRealHandle,void*hWnd DEF_PARAM(0));
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_StopRealPlay, long, void*);
//H264_DVR_API long CALL_METHOD H264_DVR_PauseRealPlay(long lRealHandle, bool bPause);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, long,    H264_DVR_PauseRealPlay, long, bool);

//设置回调函数，用户自己处理客户端收到的数据
//H264_DVR_API bool CALL_METHOD H264_DVR_SetRealDataCallBack(long lRealHandle,fRealDataCallBack cbRealData, long dwUser);
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_SetRealDataCallBack, long, fRealDataCallBack, long);

/*
	数据经过码流分析过，带有帧的具体信息
*/
//H264_DVR_API bool CALL_METHOD H264_DVR_SetRealDataCallBack_V2(long lRealHandle,fRealDataCallBack_V2 cbRealData, long dwUser);
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_SetRealDataCallBack_V2, long, fRealDataCallBack_V2, long);

//清除回调函数,该函数需要在H264_DVR_StopRealPlay前调用
//H264_DVR_API bool CALL_METHOD H264_DVR_DelRealDataCallBack(long lRealHandle,fRealDataCallBack cbRealData, long dwUser);
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_DelRealDataCallBack, long, fRealDataCallBack, long);
//H264_DVR_API bool CALL_METHOD H264_DVR_DelRealDataCallBack_V2(long lRealHandle,fRealDataCallBack_V2 cbRealData, long dwUser);
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_DelRealDataCallBack_V2, long, fRealDataCallBack_V2, long);

//录像查询
/*
	lLoginID	登陆句柄
	lpFindInfo	查询条件
	lpFileData	查找到的录像数据，外部开内存
	lMaxCount	最大录像数目
	findcount	查找到的录像数目
	waittime	查询超时时间
*/
//H264_DVR_API long CALL_METHOD H264_DVR_FindFile(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, H264_DVR_FILE_DATA *lpFileData, int lMaxCount, int *findcount, int waittime DEF_PARAM(5000));
HYBRIS_IMPLEMENT_FUNCTION6(mxmnetsdk_so, long,    H264_DVR_FindFile, long, H264_DVR_FINDINFO*, H264_DVR_FILE_DATA *, int, int*, int);

//录像查询
/*
	lLoginID		登陆句柄
	lpFindInfo	查询条件
	lpFileData	查找到的录像数据，外部开内存
	waittime		查询超时时间
*/
//H264_DVR_API long CALL_METHOD H264_DVR_FindFileByTime(long lLoginID, SDK_SearchByTime* lpFindInfo, SDK_SearchByTimeResult *lpFileData, int waittime DEF_PARAM(10000));
HYBRIS_IMPLEMENT_FUNCTION4(mxmnetsdk_so, long,    H264_DVR_FindFileByTime, long, SDK_SearchByTime*, SDK_SearchByTimeResult *, int);

//录像回放
/*
	lLoginID		登陆句柄
	sPlayBackFileName	回放的录像名称
	cbDownLoadPos 进度回调，用户通知用户设备是否已经将数据发送完毕，回调中的lDownLoadSize=-1代表数据发送完毕
	客户如果想实时显示进度，应该从码流里面获取时间来计算
	网络部分不分析码流，如果以当前接收数据大小/总大小来计算进度的话不是很准，应该以当前时间，根据开始时间和结束时间来计算进度
	fDownLoadDataCallBack 数据回调
	dwDataUser	回调参数
*/
//H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByName(long lLoginID, H264_DVR_FILE_DATA *sPlayBackFile, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack fDownLoadDataCallBack, long dwDataUser);
HYBRIS_IMPLEMENT_FUNCTION5(mxmnetsdk_so, long,    H264_DVR_PlayBackByName, long, H264_DVR_FILE_DATA *, fDownLoadPosCallBack, fRealDataCallBack, long);
//H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByName_V2(long lLoginID, H264_DVR_FILE_DATA *sPlayBackFile, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack_V2 fDownLoadDataCallBack, long dwDataUser);
HYBRIS_IMPLEMENT_FUNCTION5(mxmnetsdk_so, long,    H264_DVR_PlayBackByName_V2, long, H264_DVR_FILE_DATA *, fDownLoadPosCallBack, fRealDataCallBack_V2, long);

//按时间进行录像回放
/*
	1、进度回调和数据回调用的同一个回调参数
	2、fDownLoadDataCallBack数据回调出来的数据的没有经过码流分析
*/
//H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByTime(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack fDownLoadDataCallBack, long dwDataUser);
HYBRIS_IMPLEMENT_FUNCTION5(mxmnetsdk_so, long,    H264_DVR_PlayBackByTime, long, H264_DVR_FINDINFO*, fDownLoadPosCallBack, fRealDataCallBack, long);

/*
	1、进度回调和数据回调用不同的回调参数
	2、fDownLoadDataCallBack数据回调出来的数据的没有经过码流分析
*/
//H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByTimeEx(long lLoginID, H264_DVR_FINDINFO* lpFindInfo,fRealDataCallBack fDownLoadDataCallBack, long dwDataUser, fDownLoadPosCallBack cbDownLoadPos, long dwPosUser);
HYBRIS_IMPLEMENT_FUNCTION6(mxmnetsdk_so, long,    H264_DVR_PlayBackByTimeEx, long, H264_DVR_FINDINFO*,fRealDataCallBack, long, fDownLoadPosCallBack, long);

/*
	1、进度回调和数据回调用不同的回调参数
	2、fDownLoadDataCallBack数据回调出来的数据的码流分析过
*/
//H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByTime_V2(long lLoginID, H264_DVR_FINDINFO* lpFindInfo,fRealDataCallBack_V2 fDownLoadDataCallBack, long dwDataUser, fDownLoadPosCallBack cbDownLoadPos, long dwPosUser);
HYBRIS_IMPLEMENT_FUNCTION6(mxmnetsdk_so, long,    H264_DVR_PlayBackByTime_V2, long, H264_DVR_FINDINFO*,fRealDataCallBack_V2, long, fDownLoadPosCallBack, long);

//停止回放
//H264_DVR_API bool CALL_METHOD H264_DVR_StopPlayBack(long lPlayHandle);
HYBRIS_IMPLEMENT_FUNCTION1(mxmnetsdk_so, bool,    H264_DVR_StopPlayBack, long);

//回放控制分暂停/继续/定位/快放/慢放等等 lControlCode: SDK_PlayBackAction
//H264_DVR_API bool CALL_METHOD H264_DVR_PlayBackControl(long lPlayHandle, long lControlCode,long lCtrlValue);
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_PlayBackControl, long, long, long);

//录像下载,用户可以不使用回调，自己通过H264_DVR_GetDownloadPos获取进度
//H264_DVR_API long CALL_METHOD H264_DVR_GetFileByName(long lLoginID,H264_DVR_FILE_DATA *sPlayBackFile,char *sSavedFileName, fDownLoadPosCallBack cbDownLoadPos DEF_0_PARAM, long dwDataUser DEF_0_PARAM,fRealDataCallBack fDownLoadDataCallBack DEF_0_PARAM);
HYBRIS_IMPLEMENT_FUNCTION6(mxmnetsdk_so, long,    H264_DVR_GetFileByName, long, H264_DVR_FILE_DATA *,char *, fDownLoadPosCallBack, long, fRealDataCallBack);

//录像下载,用户可以不使用回调，自己通过H264_DVR_GetDownloadPos获取进度
//H264_DVR_API long CALL_METHOD H264_DVR_GetFileByName_V2(long lLoginID,H264_DVR_FILE_DATA *sPlayBackFile,char *sSavedFileName, fDownLoadPosCallBack cbDownLoadPos DEF_0_PARAM, long dwDataUser DEF_0_PARAM,fRealDataCallBack_V2 fDownLoadDataCallBack_V2 DEF_0_PARAM);
HYBRIS_IMPLEMENT_FUNCTION6(mxmnetsdk_so, long,    H264_DVR_GetFileByName_V2, long, H264_DVR_FILE_DATA *, char *, fDownLoadPosCallBack, long,fRealDataCallBack_V2);

//H264_DVR_API long CALL_METHOD H264_DVR_GetFileByTime(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, char *sSavedFileDIR, bool bMerge DEF_PARAM(0), fDownLoadPosCallBack cbDownLoadPos DEF_0_PARAM, long dwDataUser DEF_0_PARAM,fRealDataCallBack fDownLoadDataCallBack DEF_0_PARAM);
HYBRIS_IMPLEMENT_FUNCTION7(mxmnetsdk_so, long,    H264_DVR_GetFileByTime, long, H264_DVR_FINDINFO*, char *, bool, fDownLoadPosCallBack, long,fRealDataCallBack);

/*
	1.sSavedFileDIR=NULL,只回调不下载
	2.fDownLoadDataCallBack_V2 数据回调出来的数据的码流分析过
*/
//H264_DVR_API long CALL_METHOD H264_DVR_GetFileByTime_V2(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, char *sSavedFileDIR, bool bMerge, fDownLoadPosCallBack cbDownLoadPos DEF_0_PARAM,long dwDataUser DEF_0_PARAM,fRealDataCallBack_V2 fDownLoadDataCallBack_V2 DEF_0_PARAM);
HYBRIS_IMPLEMENT_FUNCTION7(mxmnetsdk_so, long,    H264_DVR_GetFileByTime_V2, long, H264_DVR_FINDINFO*, char *, bool, fDownLoadPosCallBack,long,fRealDataCallBack_V2);

//H264_DVR_API bool CALL_METHOD H264_DVR_StopGetFile(long lFileHandle);
HYBRIS_IMPLEMENT_FUNCTION1(mxmnetsdk_so, bool,    H264_DVR_StopGetFile, long);

//下载控制分,暂停,继续 lControlCode: SDK_PlayBackAction
//H264_DVR_API bool CALL_METHOD H264_DVR_GetFileControl(long lPlayHandle, long lControlCode, bool bDown DEF_PARAM(1));
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_GetFileControl, long, long, bool);

//获取下载进度
//H264_DVR_API int CALL_METHOD H264_DVR_GetDownloadPos(long lFileHandle);
HYBRIS_IMPLEMENT_FUNCTION1(mxmnetsdk_so, int,    H264_DVR_GetDownloadPos, long);

//升级
/*
	==UpgradeTypes
 */
//H264_DVR_API long CALL_METHOD H264_DVR_Upgrade(long lLoginID, char *sFileName, int nType DEF_0_PARAM, fUpgradeCallBack cbUpgrade DEF_0_PARAM, long dwUser DEF_0_PARAM);
HYBRIS_IMPLEMENT_FUNCTION5(mxmnetsdk_so, long,    H264_DVR_Upgrade, long, char *, int, fUpgradeCallBack, long);

//升级状态 1 成功， 2 正在升级 3 失败
//H264_DVR_API int CALL_METHOD H264_DVR_GetUpgradeState(long lUpgradeHandle);
HYBRIS_IMPLEMENT_FUNCTION1(mxmnetsdk_so, int,    H264_DVR_GetUpgradeState, long);
//H264_DVR_API long CALL_METHOD H264_DVR_CloseUpgradeHandle(long lUpgradeHandle);
HYBRIS_IMPLEMENT_FUNCTION1(mxmnetsdk_so, long,    H264_DVR_CloseUpgradeHandle, long);

//云台控制，默认是开启云台，速度4，用户也可以自行设置速度
/*
	lPTZCommand:见PTZ_ControlType
*/
//H264_DVR_API bool CALL_METHOD H264_DVR_PTZControl(long lLoginID,int nChannelNo, long lPTZCommand, bool bStop  DEF_PARAM(0), long lSpeed DEF_PARAM(4));
HYBRIS_IMPLEMENT_FUNCTION5(mxmnetsdk_so, bool,    H264_DVR_PTZControl, long, int, long, bool, long);

//扩展云台控制，包括预置点设置，巡航路线，快速定位等等
/*
	设置，删除，转到预置点时：lParam1为预置点值
	加入预置点到巡航，删除巡航中预置点时：lParam1为巡航线路值，
	lParam2为预置点值,lParam3为时间间隔
	开始巡航，停止巡航，清除巡航线路时：lParam1为巡航线路值
	云台方向设置时：lParam1为水平步长，lParam2为垂直步长
	lPTZCommand:PTZ_ControlType
 */
//H264_DVR_API bool CALL_METHOD H264_DVR_PTZControlEx(long lLoginID,int nChannelNo, long lPTZCommand, long lParam1, long lParam2, long lParam3, bool bStop DEF_0_PARAM);
HYBRIS_IMPLEMENT_FUNCTION7(mxmnetsdk_so, bool,    H264_DVR_PTZControlEx, long, int, long, long, long, long, bool);

//设备控制：返回值 true 成功， false 失败
/*
	type==0 重启设备，1 清除日志 2 关机 3.恢复记录日志 4.停止记录日志 5.手机对讲恢复关闭之前临时打开过的音频
*/
//H264_DVR_API bool CALL_METHOD H264_DVR_ControlDVR(long lLoginID, int type, int waittime DEF_PARAM(2000));
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_ControlDVR, long, int, int);

//搜索局域网内的设备 SDK_CONFIG_NET_COMMON_V2
//H264_DVR_API bool CALL_METHOD H264_DVR_SearchDevice(char* szBuf, int nBufLen, int* pRetLen, int nSearchTime);
HYBRIS_IMPLEMENT_FUNCTION4(mxmnetsdk_so, bool,    H264_DVR_SearchDevice, char*, int, int*, int);

//语音对讲，负责数据传发接口
//H264_DVR_API long CALL_METHOD H264_DVR_StartVoiceCom_MR(long lLoginID, pfAudioDataCallBack pVcb, long dwDataUser);
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, long,    H264_DVR_StartVoiceCom_MR, long, pfAudioDataCallBack, long);
//H264_DVR_API bool CALL_METHOD H264_DVR_VoiceComSendData(long lVoiceHandle, char *pSendBuf, long lBufSize);
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_VoiceComSendData, long, char *, long);
//H264_DVR_API bool CALL_METHOD H264_DVR_StopVoiceCom(long lVoiceHandle);
HYBRIS_IMPLEMENT_FUNCTION1(mxmnetsdk_so, bool,    H264_DVR_StopVoiceCom, long);

//设置对讲音频编码方式，用户可以不设置，默认为G711A编码
//H264_DVR_API bool CALL_METHOD H264_DVR_SetTalkMode(long lLoginID, SDK_AudioInFormatConfig* pTalkMode);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_SetTalkMode, long, SDK_AudioInFormatConfig*);

// lRecordType录像模式, 见SDK_RecordModeTypes
//H264_DVR_API bool CALL_METHOD H264_DVR_StartDVRRecord(long lLoginID, int nChannelNo ,long lRecordType);
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_StartDVRRecord, long, int, long);
//H264_DVR_API bool CALL_METHOD H264_DVR_StopDVRRecord(long lLoginID, int nChannelNo);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_StopDVRRecord, long, int);

//设置设备系统时间
//H264_DVR_API bool CALL_METHOD H264_DVR_SetSystemDateTime(long lLoginID, SDK_SYSTEM_TIME *pSysTime);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_SetSystemDateTime, long, SDK_SYSTEM_TIME*);
//得到设备的工作状态
//H264_DVR_API bool CALL_METHOD H264_DVR_GetDVRWorkState(long lLoginID, SDK_DVR_WORKSTATE *pWorkState);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_GetDVRWorkState, long, SDK_DVR_WORKSTATE*);

//网络键盘，具体使用方法见ClientDemo
//H264_DVR_API bool CALL_METHOD H264_DVR_ClickKey(long lLoginID, SDK_NetKeyBoardData *pKeyBoardData);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_ClickKey, long, SDK_NetKeyBoardData*);

// 磁盘管理
/*
	对硬盘进行分区,格式化等等操作
*/
//H264_DVR_API int CALL_METHOD H264_DVR_StorageManage(long lLoginID, SDK_StorageDeviceControl *pStorageCtl);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, int,    H264_DVR_StorageManage, long, SDK_StorageDeviceControl*);

//H264_DVR_API bool CALL_METHOD H264_DVR_SendNetAlarmMsg(long lLoginID, SDK_NetAlarmInfo *pAlarmInfo);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_SendNetAlarmMsg, long, SDK_NetAlarmInfo*);

//设备端抓图,即抓设备端发过来的即时的一张图片sdk内部生成文件
/*
	说明:设备端抓图,即抓设备端发过来的即时的一张图片的内存buf
	1.需要设备配置里面有抓图配置选项该接口才有效
	2.如果满足1，默认抓出来的分辨率是D1，如果想抓跟视频分辨率一样的图片，就需要修改编码设置里的抓图分辨率，
	  如果编码设置没有抓图分辨率选项，则需要定制支持该项的程序
*/
//H264_DVR_API bool CALL_METHOD H264_DVR_CatchPic(long lLoginID, int nChannel, char *sFileName);
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_CatchPic, long, int, char*);

//设备端抓图,即抓设备端发过来的即时的一张图片的内存buf，外部生成文件
/*
	说明:同H264_DVR_CatchPic
*/
//H264_DVR_API bool CALL_METHOD H264_DVR_CatchPicInBuffer(long lLoginID, int nChannel, char *pBuffer, int nBufLen, int *pPicLen);
HYBRIS_IMPLEMENT_FUNCTION5(mxmnetsdk_so, bool,    H264_DVR_CatchPicInBuffer, long, int, char*, int, int);

//启动报警中心监听(具体用法见AlarmCenter demo)
//H264_DVR_API bool CALL_METHOD H264_DVR_StartAlarmCenterListen(int nPort, fMessCallBack cbAlarmCenter, unsigned long dwDataUser);
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_StartAlarmCenterListen, int, fMessCallBack, unsigned long);

//关闭报警中心监听
//H264_DVR_API bool CALL_METHOD H264_DVR_StopAlarmCenterListen();
HYBRIS_IMPLEMENT_FUNCTION0(mxmnetsdk_so, bool,    H264_DVR_StopAlarmCenterListen);

//透明232,485
//H264_DVR_API bool CALL_METHOD H264_DVR_SerialWrite(long lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen);
HYBRIS_IMPLEMENT_FUNCTION4(mxmnetsdk_so, bool,    H264_DVR_SerialWrite, long, SERIAL_TYPE, char *, int);
//H264_DVR_API bool CALL_METHOD H264_DVR_SerialRead(long lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen, int *pReadLen);
HYBRIS_IMPLEMENT_FUNCTION5(mxmnetsdk_so, bool,    H264_DVR_SerialRead, long, SERIAL_TYPE, char *, int, int *);

//获取DDNS信息，具体用法见ClientDemo
//H264_DVR_API int CALL_METHOD H264_DVR_GetDDNSInfo(SearchMode &searchmode, DDNS_INFO *pDevicInfo, int maxDeviceNum, int &nretNum);
HYBRIS_IMPLEMENT_FUNCTION4(mxmnetsdk_so, int,    H264_DVR_GetDDNSInfo, SearchMode, DDNS_INFO *, int, int);

//nStream: 0表示主码流，为1表示子码流
//H264_DVR_API bool CALL_METHOD H264_DVR_MakeKeyFrame(long lLoginID, int nChannel, int nStream);
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_MakeKeyFrame, long, int, int);

//nStream: 0表示主码流，为1表示子码流
//H264_DVR_API bool CALL_METHOD H264_DVR_GetOEMInfo(long lLoginID, SDK_OEMInfo *pOEMInfo);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_GetOEMInfo, long, SDK_OEMInfo*);
// 创建透明串口通道
//H264_DVR_API bool CALL_METHOD H264_DVR_OpenTransComChannel(long lLoginID, TransComChannel *TransInfo, fTransComCallBack cbTransCom, unsigned long lUser);
HYBRIS_IMPLEMENT_FUNCTION4(mxmnetsdk_so, bool,    H264_DVR_OpenTransComChannel, long, TransComChannel *, fTransComCallBack, unsigned long);

//关闭透明串口通道
//H264_DVR_API bool CALL_METHOD H264_DVR_CloseTransComChannel(long lLoginID, SERIAL_TYPE nType);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_CloseTransComChannel, long, SERIAL_TYPE);

//获取ui图片:type 1:为全图片 2:活动区域图片
//H264_DVR_API bool CALL_METHOD H264_DVR_CatchPicUI(long lLoginID,char *saveFileName,int type DEF_PARAM(1));
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_CatchPicUI, long, char *, int);

#ifdef WIN32
//打开通道音频 //预览，回放，本地播放 一个函数
H264_DVR_API bool CALL_METHOD H264_DVR_OpenSound(long lHandle);
//关闭通道音频 //预览，回放，本地播放 一个函数
H264_DVR_API bool CALL_METHOD H264_DVR_CloseSound(long lHandle);
//抓本地图片 //预览，回放，本地播放 一个函数
H264_DVR_API bool CALL_METHOD H264_DVR_LocalCatchPic(long lHandle,char*szSaveFileName);
//打开对讲
H264_DVR_API long CALL_METHOD H264_DVR_StartLocalVoiceCom(long lLoginID);
//开始本地录像
H264_DVR_API bool CALL_METHOD H264_DVR_StartLocalRecord(long lRealHandle,char*szSaveFileName,long type=0);
//关闭本地录像
H264_DVR_API bool CALL_METHOD H264_DVR_StopLocalRecord(long lRealHandle);

//播放本地文件
H264_DVR_API long CALL_METHOD H264_DVR_StartLocalPlay(char*pFileName,void* hWnd,fPlayDrawCallBack drawCallBack=0,long user=0);
//关闭本地播放
H264_DVR_API bool CALL_METHOD H264_DVR_StopLocalPlay(long lPlayHandle);
//获取播放位置用于回放，和本地播放
H264_DVR_API float CALL_METHOD H264_DVR_GetPlayPos(long lPlayHandle);
//设置播放位置（百分比）用于回放，和本地播放
H264_DVR_API bool CALL_METHOD H264_DVR_SetPlayPos(long lPlayHandle,float fRelativPos);
//播放控制（播放，停止，恢复，快发，慢放）
H264_DVR_API bool CALL_METHOD H264_DVR_LocalPlayCtrl(long lPlayHandle,SDK_LoalPlayAction action,long lCtrlValue);
//设置播放结束回调
H264_DVR_API bool CALL_METHOD H264_DVR_SetFileEndCallBack(long lPlayHandle,fLocalPlayFileCallBack callBack,long user);
//设置信息帧回调
H264_DVR_API bool CALL_METHOD H264_DVR_SetInfoFrameCallBack(long lPlayHandle,InfoFramCallBack callback,long user);

//本地颜色控制 //预览，回放，本地播放 一个函数
H264_DVR_API bool CALL_METHOD H264_DVR_LocalGetColor(long lHandle, DWORD nRegionNum, LONG *pBrightness, LONG *pContrast, LONG *pSaturation, LONG *pHue);
H264_DVR_API bool CALL_METHOD H264_DVR_LocalSetColor(long lHandle, DWORD nRegionNum, LONG nBrightness, LONG nContrast, LONG nSaturation, LONG nHue);
#endif

//设置本地ip
//H264_DVR_API bool CALL_METHOD H264_DVR_SetLocalBindAddress(char*szIP);
HYBRIS_IMPLEMENT_FUNCTION1(mxmnetsdk_so, bool,    H264_DVR_SetLocalBindAddress, char*);

//上报数据
//H264_DVR_API bool CALL_METHOD H264_DVR_StartUploadData(long lLoginID,UploadDataType upLoadType,fUploadDataCallBack callBack,long lUser);
HYBRIS_IMPLEMENT_FUNCTION4(mxmnetsdk_so, bool,    H264_DVR_StartUploadData, long, UploadDataType, fUploadDataCallBack, long);

//H264_DVR_API bool CALL_METHOD H264_DVR_StopUploadData(long lLoginID,UploadDataType upLoadType);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_StopUploadData, long, UploadDataType);

//主动注册
//H264_DVR_API bool CALL_METHOD H264_DVR_StartActiveRigister(int nPort, fMessCallBack cbFunc, unsigned long dwDataUser);
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_StartActiveRigister, int, fMessCallBack, unsigned long);
//H264_DVR_API bool CALL_METHOD H264_DVR_StopActiveRigister();
HYBRIS_IMPLEMENT_FUNCTION0(mxmnetsdk_so, bool,    H264_DVR_StopActiveRigister);

//子连接异常断开
//H264_DVR_API long CALL_METHOD H264_DVR_SetSubDisconnectCallBack(fSubDisConnectCallBack callBack,DWORD userData);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, long,    H264_DVR_SetSubDisconnectCallBack, fSubDisConnectCallBack, DWORD);

//设置保活时间,perKeeplifeTime(心跳间隔):单位秒,detectDisconTime(断线检测时间):单位秒
//H264_DVR_API long CALL_METHOD H264_DVR_SetKeepLifeTime(long lLoginID,unsigned int perKeeplifeTime,unsigned int detectDisconTime);
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, long,    H264_DVR_SetKeepLifeTime, long, unsigned int, unsigned int);

//MAC 得到加密
//H264_DVR_API bool CALL_METHOD H264_DVR_CheckEncrypt(char *pMac);
HYBRIS_IMPLEMENT_FUNCTION1(mxmnetsdk_so, bool,    H264_DVR_CheckEncrypt, char*);

//设备搜索到的设备，与设备在同一个局域网的设备
//H264_DVR_API bool CALL_METHOD H264_DVR_SearchDeviceEX(long lLoginID,SDK_NetDevList *pDevlist,SDK_TransferProtocol_V2 transferProtocol DEF_PARAM(SDK_TRANSFER_PROTOCOL_NETIP),int waittime DEF_PARAM(15000));
HYBRIS_IMPLEMENT_FUNCTION4(mxmnetsdk_so, bool,    H264_DVR_SearchDeviceEX, long, SDK_NetDevList *, SDK_TransferProtocol_V2, int);

//云台快速定位
//使用前 判断是否支持
//H264_DVR_API bool CALL_METHOD H264_DVR_PTZPostion(long lLoginID,int nChannel,SDK_PositionPoint *pPositionPoint);
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_PTZPostion, long, int, SDK_PositionPoint *);

///< NVR和其连接的前端对讲
//H264_DVR_API bool CALL_METHOD H264_DVR_StartDevTalk(long lLoginID,int nChannel,int waittime DEF_PARAM(2000));
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_StartDevTalk, long, int, int);

//H264_DVR_API bool CALL_METHOD H264_DVR_StopDevTalk(long lLoginID,int nChannel,int waittime DEF_PARAM(2000));
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_StopDevTalk, long, int, int);

///<硬盘录像信息
//录像查询
//lLoginID		登陆句柄
//lpFindInfo	查询条件
//lpFileData	查找到的录像数据，外部开内存
//waittime		查询超时时间
//H264_DVR_API long CALL_METHOD H264_DVR_RecordInfo(long lLoginID, SDK_SearchByTime* lpFindInfo, SDK_RecordStorageInfo *lpRecordData, int waittime DEF_PARAM(15000));
HYBRIS_IMPLEMENT_FUNCTION4(mxmnetsdk_so, long,    H264_DVR_RecordInfo, long, SDK_SearchByTime*, SDK_RecordStorageInfo *, int);

//H264_DVR_API bool CALL_METHOD H264_DVR_ControlFile(long lLoginID,SDK_NetFileControl *lpFileControl,int waittime DEF_PARAM(15000));
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_ControlFile, long,SDK_NetFileControl *, int);

//录像设备里面有多少音频文件，最大8个
//lLoginID		登陆句柄
//lpFindInfo	查询条件
//lpFileData	查找到的音频数据，外部开内存
//waittime		查询超时时间
//H264_DVR_API bool CALL_METHOD H264_DVR_FindAudioFile(long lLoginID, SDK_MusicFileList* lpFileList, int waittime DEF_PARAM(5000));
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_FindAudioFile, long, SDK_MusicFileList*, int);

/*
	==播放音频文件需要文件名，其他的不需要，ACTION一定要赋值
	== Action  参考 SDK_Music_Play_Action
 */
//H264_DVR_API bool CALL_METHOD H264_DVR_ControlAudio(long lLoginID, SDK_LocalMusicControl *lpMusicControl, int waittime DEF_PARAM(2000));
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_ControlAudio, long, SDK_LocalMusicControl *, int);

//H264_DVR_API bool CALL_METHOD H264_DVR_UserData(int ntype,char *pUserData, long nlen);
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_UserData, int, char *, long);

//H264_DVR_API long CALL_METHOD H264_DVR_Upgrade_Cloud(long lLoginID, SDK_CloudUpgradeVersion *sUpgradeVer, int nType DEF_0_PARAM, fUpgradeCallBack cbUpgrade DEF_0_PARAM, long dwUser DEF_0_PARAM);
HYBRIS_IMPLEMENT_FUNCTION5(mxmnetsdk_so, long,    H264_DVR_Upgrade_Cloud, long, SDK_CloudUpgradeVersion *, int, fUpgradeCallBack, long);

//H264_DVR_API long CALL_METHOD H264_DVR_StopUpgrade_Cloud(long lHandle);
HYBRIS_IMPLEMENT_FUNCTION1(mxmnetsdk_so, long,    H264_DVR_StopUpgrade_Cloud, long);

//H264_DVR_API bool CALL_METHOD H264_DVR_Get_OutNet_IP(const char *uuid, char* ip);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_Get_OutNet_IP, const char*, char*);

#ifndef WIN32

typedef void (*IDownProcess)(int nProcess,int userData);
typedef void (*IDownData)(unsigned char* data, unsigned int length, int nUserData);

H264_DVR_API int  CALL_METHOD H264_DVR_SetServerAddr(const char *ip, int port);
////start********手机用**********/
H264_DVR_API int  CALL_METHOD H264_DVR_GetUpgradeFileList(const char *id, char *VersionList,int &num);
H264_DVR_API int CALL_METHOD H264_DVR_StartDownload(const char* strSaveFilePath, const char *id, const char *date,const char *name,unsigned int length,IDownProcess ProgressCallback,IDownData DataCallback,int userData);
H264_DVR_API int CALL_METHOD H264_DVR_CancelDownload();
////**************end/

H264_DVR_API bool CALL_METHOD H264_DVR_ControlFBExtraState(long lLoginID, bool bOn, int waittime);
//获取服务器ip(测试用)
H264_DVR_API bool CALL_METHOD H264_DVR_GetServerIp(char* _serverip);


H264_DVR_API int CALL_METHOD H264_DVR_AuthDevice_Init(char *uuid,char *ip,int port);
H264_DVR_API int CALL_METHOD H264_DVR_AuthDevice_Register();
H264_DVR_API int CALL_METHOD H264_DVR_AuthDevice_UnRegister();

H264_DVR_API int CALL_METHOD H264_DVR_AuthDevice_GetUpdateServer(char *ip,int size);


H264_DVR_API int CALL_METHOD H264_DVR_AlarmInit(char* uuid,char*ip,char* serIP);

typedef int (*MpsDevAuth)(char *buffer,int size);	//鉴权
typedef int (*MpsDevDataRecv)(char *buffer,int size,int clientID);	//数据由客户端发给设备

H264_DVR_API int CALL_METHOD H264_DVR_AlarmPush(char* buffer,int size);
H264_DVR_API int CALL_METHOD H264_DVR_AlarmStart(char* uuid,char* serIP,MpsDevAuth  AuthCb, MpsDevDataRecv DataRecvCb);

H264_DVR_API int CALL_METHOD H264_DVR_IMpsClient(char* uuid,SDK_CONFIG_TYPE configType,char* buffer,int size);

H264_DVR_API int CALL_METHOD H264_DVR_IMpsGetClient(char* uuid,SDK_CONFIG_TYPE configType,char* buffer,int size);
H264_DVR_API int CALL_METHOD H264_DVR_IMpsInbuffer(char* uuid,SDK_CONFIG_TYPE configType,char* buffer,int *size);
H264_DVR_API long CALL_METHOD H264_DVR_Upgrade_Cloud_V2(char* uuid, SDK_CloudUpgradeVersion *sUpgradeVer, int nType,fUpgradeCallBack cbUpgrade, long dwUser);

H264_DVR_API int H264_DVR_SearchAlarmInfo(char *ip, int port, SDK_XPMS_SEARCH_ALARMINFO_REQ &AlarmInfoReq);
H264_DVR_API int H264_DVR_SearchAlarmPic(char *ip, int port, SDK_XPMS_SEARCH_ALARMPIC_REQ &AlarmPicReq);
//获取穿透库的版本信息
H264_DVR_API void CALL_METHOD H264_VV_NAT_GetVersion(char *version, int size);
////增加强制走转发的接口；skipP2P=1  强制转发。skipP2P=0 按正常检测机制流程。
H264_DVR_API void CALL_METHOD H264_Direct_Proxy(int skipP2P);
//1雄迈精品  0普通的
H264_DVR_API int CALL_METHOD H264_XM_Unique();
H264_DVR_API void* get_MpsAlarmClient_Instance();
H264_DVR_API long CALL_METHOD H264_DVR_GetDevConfig_Json(long lLoginID, const char* dwCommand, int nChannelNO,char * lpOutBuffer,unsigned long dwOutBufferSize,unsigned long* lpBytesReturned,int waittime DEF_PARAM(1000));

H264_DVR_API long CALL_METHOD H264_DVR_SetDevConfig_Json(long lLoginID,const char* dwCommand, int nChannelNO, char * lpInBuffer,int waittime DEF_PARAM(1000));
typedef int (*OnFoundDevCB)(char * uuid,int state,int userData);
H264_DVR_API int CALL_METHOD H264_DVR_Check_Device_Exist(SDK_SDevicesState *pStates, int nTimeout,OnFoundDevCB decCb,int userData);
H264_DVR_API int CALL_METHOD H264_DVR_Check_Device_Exist_V2(SDK_SDevicesState *pStates, int nTimeout,OnFoundDevCB decCb,int userData);
typedef void (*PFunOnWifiConfigResult)(int nResult, SDK_CONFIG_NET_COMMON_V2 *pConfig);
H264_DVR_API int CALL_METHOD H264_DVR_StartWifiConfig(SDK_SWifiInfo *pInfo, PFunOnWifiConfigResult pOnResult);
H264_DVR_API void CALL_METHOD H264_DVR_StopWifiConfig();
H264_DVR_API int CALL_METHOD H264_DVR_SetAuthUserInfo(const char *userName, const char *password);
H264_DVR_API long CALL_METHOD H264_DVR_CmdGeneral(long lLoginID, int nCmdReq, const char *szCmd, void *lpOutBuffer, unsigned long dwOutBufferSize, unsigned long* lpBytesReturned, int nTimeout, char *pInParam DEF_PARAM(0), int nInParamLen DEF_PARAM(0), int nCmdRes DEF_PARAM(-1));
#endif
