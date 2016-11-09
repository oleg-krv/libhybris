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

/*
//SDK初始化
H264_DVR_API long CALL_METHOD H264_DVR_Init(fDisConnect cbDisConnect, void* dwUser);
*/
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, long,    H264_DVR_Init, fDisConnect, unsigned long);

/*
//SDK退出清理
H264_DVR_API bool CALL_METHOD H264_DVR_Cleanup();
*/
HYBRIS_IMPLEMENT_FUNCTION0(mxmnetsdk_so, bool,    H264_DVR_Cleanup);

/*
//获取错误信息
H264_DVR_API long CALL_METHOD H264_DVR_GetLastError();
*/
HYBRIS_IMPLEMENT_FUNCTION0(mxmnetsdk_so, long,    H264_DVR_GetLastError);

/*
// 设置连接设备超时时间和尝试次数
//nWaitTime:单位ms不设置时默认5000ms,
//nTryTimes:次数,不设置时默认3次
H264_DVR_API bool CALL_METHOD H264_DVR_SetConnectTime(long nWaitTime, long nTryTimes);
*/
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_SetConnectTime, long, long);

/*
//socketType 参考类型 SocketStyle，默认是0
H264_DVR_API long CALL_METHOD H264_DVR_Login(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
							   LPH264_DVR_DEVICEINFO lpDeviceInfo, int *error,int socketType = 0);
*/
HYBRIS_IMPLEMENT_FUNCTION7(mxmnetsdk_so, long,    H264_DVR_Login, char, unsigned short, char*, char*, LPH264_DVR_DEVICEINFO, int*, int);

/*
//向设备注册扩展接口
//增加登陆类型 0==web 1 ==升级工具 2 == 搜索工具  102 == 外部加密，内部就不用加密了
H264_DVR_API long CALL_METHOD H264_DVR_LoginEx(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
							   LPH264_DVR_DEVICEINFO lpDeviceInfo, int nType, int *error);

//向设备注销
H264_DVR_API long CALL_METHOD H264_DVR_Logout(long lLoginID);
*/
HYBRIS_IMPLEMENT_FUNCTION1(mxmnetsdk_so, long,    H264_DVR_Logout, long);

/*
//设置接收DVR信息回调, 例如报警信息,以ID号区分
H264_DVR_API bool CALL_METHOD H264_DVR_SetDVRMessCallBack(fMessCallBack cbAlarmcallback, void* lUser);
*/
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_SetDVRMessCallBack, fMessCallBack, unsigned long);

/*
//建立报警上传通道
H264_DVR_API long CALL_METHOD H264_DVR_SetupAlarmChan(long lLoginID);
H264_DVR_API bool CALL_METHOD H264_DVR_CloseAlarmChan(long lLoginID);
*/
HYBRIS_IMPLEMENT_FUNCTION1(mxmnetsdk_so, long,    H264_DVR_SetupAlarmChan, long);

/*
//远程配置设备接口 配置类型见SDK_CONFIG_TYPE
H264_DVR_API long  CALL_METHOD H264_DVR_GetDevConfig(long lLoginID, unsigned long dwCommand, int nChannelNO,
							char * lpOutBuffer, unsigned long dwOutBufferSize, unsigned long* lpBytesReturned,int waittime = 1000);
H264_DVR_API long  CALL_METHOD H264_DVR_SetDevConfig(long lLoginID, unsigned long dwCommand, int nChannelNO, char * lpInBuffer, unsigned long dwInBufferSize, int waittime = 1000);
*/
HYBRIS_IMPLEMENT_FUNCTION7(mxmnetsdk_so, long,    H264_DVR_GetDevConfig, long, unsigned long, int, char*, unsigned long, unsigned long*, int);
HYBRIS_IMPLEMENT_FUNCTION6(mxmnetsdk_so, long,    H264_DVR_SetDevConfig, long, unsigned long, int, char*, unsigned long, int);

/*
//跨网段设置设备配置，目前只支持对网络配置进行设置
H264_DVR_API long CALL_METHOD H264_DVR_SetConfigOverNet(unsigned long dwCommand, int nChannelNO, char * lpInBuffer, unsigned long dwInBufferSize, int waittime = 1000);

//日志查询
H264_DVR_API bool CALL_METHOD H264_DVR_FindDVRLog(long lLoginID, SDK_LogSearchCondition *pFindParam, SDK_LogList *pRetBuffer, long lBufSize, int waittime = 2000);

//打开实时预览
H264_DVR_API long CALL_METHOD H264_DVR_RealPlay(long lLoginID, LPH264_DVR_CLIENTINFO lpClientInfo);
H264_DVR_API bool CALL_METHOD H264_DVR_StopRealPlay(long lRealHandle,void*hWnd=NULL);
H264_DVR_API long CALL_METHOD H264_DVR_PauseRealPlay(long lRealHandle, bool bPause);
*/
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, long,    H264_DVR_RealPlay, long, LPH264_DVR_CLIENTINFO);
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, bool,    H264_DVR_StopRealPlay, long, void*);

/*
//设置回调函数，用户自己处理客户端收到的数据
H264_DVR_API bool CALL_METHOD H264_DVR_SetRealDataCallBack(long lRealHandle,fRealDataCallBack cbRealData, void* dwUser);
H264_DVR_API bool CALL_METHOD H264_DVR_SetRealDataCallBack_V2(long lRealHandle,fRealDataCallBack_V2 cbRealData, void* dwUser);
*/
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, bool,    H264_DVR_SetRealDataCallBack_V2, long, fRealDataCallBack_V2, unsigned int);

/*
//清除回调函数,该函数需要在H264_DVR_StopRealPlay前调用
H264_DVR_API bool CALL_METHOD H264_DVR_DelRealDataCallBack(long lRealHandle,fRealDataCallBack cbRealData, void* dwUser);
H264_DVR_API bool CALL_METHOD H264_DVR_DelRealDataCallBack_V2(long lRealHandle,fRealDataCallBack_V2 cbRealData, void* dwUser);

//录像查询
//lLoginID		登陆句柄
//lpFindInfo	查询条件
//lpFileData	查找到的录像数据，外部开内存
//lMaxCount		最大录像数目
//findcount		查找到的录像数目
//waittime		查询超时时间
H264_DVR_API long CALL_METHOD H264_DVR_FindFile(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, H264_DVR_FILE_DATA *lpFileData, int lMaxCount, int *findcount, int waittime = 5000);
*/
HYBRIS_IMPLEMENT_FUNCTION6(mxmnetsdk_so, long,    H264_DVR_FindFile, long, H264_DVR_FINDINFO*, H264_DVR_FILE_DATA *, int, int*, int);

/*
//录像查询
//lLoginID		登陆句柄
//lpFindInfo	查询条件
//lpFileData	查找到的录像数据，外部开内存
//waittime		查询超时时间
H264_DVR_API long CALL_METHOD H264_DVR_FindFileByTime(long lLoginID, SDK_SearchByTime* lpFindInfo, SDK_SearchByTimeResult *lpFileData, int waittime = 10000);

//录像回放
//lLoginID		登陆句柄
//sPlayBackFileName	回放的录像名称
//cbDownLoadPos 进度回调		用户通知用户设备是否已经将数据发送完毕
								//客户如果想实时显示进度，应该从码流里面获取时间来计算
								//网络部分不分析码流，如果以当前接收数据大小/总大小来计算进度的话不是很准，应该以当前时间，根据开始时间和结束时间来计算进度
//fDownLoadDataCallBack 数据回调
//dwDataUser	回调参数
H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByName(long lLoginID, H264_DVR_FILE_DATA *sPlayBackFile, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack fDownLoadDataCallBack, void* dwDataUser);
H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByName_V2(long lLoginID, H264_DVR_FILE_DATA *sPlayBackFile, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack_V2 fDownLoadDataCallBack, void* dwDataUser);

//按时间进行录像回放
H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByTime(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack fDownLoadDataCallBack, void* dwDataUser);
//H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByTimeEx(long lLoginID, int nChannelID, LPH264_DVR_TIME lpStartTime,
//											LPH264_DVR_TIME lpStopTime, fRealDataCallBack fDownLoadDataCallBack, long dwDataUser,
//											fDownLoadPosCallBack cbDownLoadPos, long dwPosUser);

H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByTimeEx(long lLoginID, H264_DVR_FINDINFO* lpFindInfo,fRealDataCallBack fDownLoadDataCallBack, void* dwDataUser,
											fDownLoadPosCallBack cbDownLoadPos, void* dwPosUser);

H264_DVR_API bool CALL_METHOD H264_DVR_StopPlayBack(long lPlayHandle);

//回放控制分,暂停,定位等等
H264_DVR_API bool CALL_METHOD H264_DVR_PlayBackControl(long lPlayHandle, long lControlCode,long lCtrlValue);

//录像下载,用户可以不使用回调，自己通过H264_DVR_GetDownloadPos获取进度
H264_DVR_API long CALL_METHOD H264_DVR_GetFileByName(long lLoginID,H264_DVR_FILE_DATA *sPlayBackFile,char *sSavedFileName, 
											fDownLoadPosCallBack cbDownLoadPos = NULL, void* dwDataUser = NULL,fRealDataCallBack fDownLoadDataCallBack = NULL);
H264_DVR_API long CALL_METHOD H264_DVR_GetFileByTime(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, char *sSavedFileDIR, bool bMerge = false,
											fDownLoadPosCallBack cbDownLoadPos = NULL, void* dwDataUser = NULL ,fRealDataCallBack fDownLoadDataCallBack =NULL );

H264_DVR_API bool CALL_METHOD H264_DVR_StopGetFile(long lFileHandle);
//获取下载进度
H264_DVR_API int CALL_METHOD H264_DVR_GetDownloadPos(long lFileHandle);

//升级
H264_DVR_API long CALL_METHOD H264_DVR_Upgrade(long lLoginID, char *sFileName, int nType = 0, fUpgradeCallBack cbUpgrade = NULL, void* dwUser = 0);
//升级状态 1 成功， 2 正在升级 3 失败
H264_DVR_API int CALL_METHOD H264_DVR_GetUpgradeState(long lUpgradeHandle);
H264_DVR_API long CALL_METHOD H264_DVR_CloseUpgradeHandle(long lUpgradeHandle);


//云台控制，默认是开启云台，速度4，用户也可以自行设置速度
H264_DVR_API bool CALL_METHOD H264_DVR_PTZControl(long lLoginID,int nChannelNo, long lPTZCommand, bool bStop = false, long lSpeed = 4);

//扩展云台控制，包括预置点设置，巡航路线，快速定位等等
H264_DVR_API bool CALL_METHOD H264_DVR_PTZControlEx(long lLoginID,int nChannelNo, long lPTZCommand, 
									long lParam1, long lParam2, long lParam3, bool bStop = false);

//设备控制：返回值 true 成功， false 失败
H264_DVR_API bool CALL_METHOD H264_DVR_ControlDVR(long lLoginID, int type, int waittime = 2000);

//搜索局域网内的设备
H264_DVR_API bool CALL_METHOD H264_DVR_SearchDevice(char* szBuf, int nBufLen, int* pRetLen, int nSearchTime);
*/
HYBRIS_IMPLEMENT_FUNCTION4(mxmnetsdk_so, bool,    H264_DVR_SearchDevice, char*, int, int*, int);

/*
//语音对讲，负责数据传发接口
H264_DVR_API long CALL_METHOD H264_DVR_StartVoiceCom_MR(long lLoginID, pfAudioDataCallBack pVcb, void* dwDataUser);
H264_DVR_API bool CALL_METHOD H264_DVR_VoiceComSendData(long lVoiceHandle, char *pSendBuf, long lBufSize);
H264_DVR_API bool CALL_METHOD H264_DVR_StopVoiceCom(long lVoiceHandle);

//设置对讲音频编码方式，用户可以不设置，默认为G711A编码
H264_DVR_API bool CALL_METHOD H264_DVR_SetTalkMode(long lLoginID, SDK_AudioInFormatConfig* pTalkMode);

// lRecordType录像模式, 见SDK_RecordModeTypes
H264_DVR_API bool CALL_METHOD H264_DVR_StartDVRRecord(long lLoginID, int nChannelNo ,long lRecordType);
H264_DVR_API bool CALL_METHOD H264_DVR_StopDVRRecord(long lLoginID, int nChannelNo);

H264_DVR_API bool CALL_METHOD H264_DVR_SetSystemDateTime(long lLoginID, SDK_SYSTEM_TIME *pSysTime);
H264_DVR_API bool CALL_METHOD H264_DVR_GetDVRWorkState(long lLoginID, SDK_DVR_WORKSTATE *pWorkState);

H264_DVR_API bool CALL_METHOD H264_DVR_ClickKey(long lLoginID, SDK_NetKeyBoardData *pKeyBoardData);

// 磁盘管理
H264_DVR_API int CALL_METHOD H264_DVR_StorageManage(long lLoginID, SDK_StorageDeviceControl *pStorageCtl);

H264_DVR_API bool CALL_METHOD H264_DVR_SendNetAlarmMsg(long lLoginID, SDK_NetAlarmInfo *pAlarmInfo);

// 抓图
H264_DVR_API bool CALL_METHOD H264_DVR_CatchPic(long lLoginID, int nChannel, char *sFileName);
H264_DVR_API bool CALL_METHOD H264_DVR_CatchPicInBuffer(long lLoginID, int nChannel, char *pBuffer, int nBufLen, int *pPicLen);

H264_DVR_API bool CALL_METHOD H264_DVR_StartAlarmCenterListen(int nPort, fMessCallBack cbAlarmCenter, void* dwDataUser);
H264_DVR_API bool CALL_METHOD H264_DVR_StopAlarmCenterListen();

//透明232,485
H264_DVR_API bool CALL_METHOD H264_DVR_SerialWrite(long lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen);
H264_DVR_API bool CALL_METHOD H264_DVR_SerialRead(long lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen, int *pReadLen);

H264_DVR_API int CALL_METHOD H264_DVR_GetDDNSInfo(SearchMode &searchmode, DDNS_INFO *pDevicInfo, int maxDeviceNum, int &nretNum);

//nStream: 0表示主码流，为1表示子码流
H264_DVR_API bool CALL_METHOD H264_DVR_MakeKeyFrame(long lLoginID, int nChannel, int nStream);

//nStream: 0表示主码流，为1表示子码流
H264_DVR_API bool CALL_METHOD H264_DVR_GetOEMInfo(long lLoginID, SDK_OEMInfo *pOEMInfo);
// 创建透明串口通道
H264_DVR_API bool CALL_METHOD H264_DVR_OpenTransComChannel(long lLoginID, TransComChannel *TransInfo, fTransComCallBack cbTransCom, void* lUser);
//关闭透明串口通道
H264_DVR_API bool CALL_METHOD H264_DVR_CloseTransComChannel(long lLoginID, SERIAL_TYPE nType);
//获取状态信息
H264_DVR_API bool CALL_METHOD H264_DVR_GetDeviceState(long lLoginID, SDK_State_Type type, char *pState);
//获取ui图片:type 1:为全图片 2:活动区域图片
H264_DVR_API bool CALL_METHOD H264_DVR_CatchPicUI(long lLoginID,char *saveFileName,int type=1);

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
H264_DVR_API long CALL_METHOD H264_DVR_StartLocalPlay(char*pFileName,void* hWnd,fPlayDrawCallBack drawCallBack=NULL,void* user=NULL);
//关闭本地播放
H264_DVR_API bool CALL_METHOD H264_DVR_StopLocalPlay(long lPlayHandle);
//获取播放位置用于回放，和本地播放
H264_DVR_API float CALL_METHOD H264_DVR_GetPlayPos(long lPlayHandle);
//设置播放位置（百分比）用于回放，和本地播放
H264_DVR_API bool CALL_METHOD H264_DVR_SetPlayPos(long lPlayHandle,float fRelativPos);
//播放控制（播放，停止，恢复，快发，慢放）
H264_DVR_API bool CALL_METHOD H264_DVR_LocalPlayCtrl(long lPlayHandle,SDK_LoalPlayAction action,long lCtrlValue);
//设置播放结束回调
H264_DVR_API bool CALL_METHOD H264_DVR_SetFileEndCallBack(long lPlayHandle,fLocalPlayFileCallBack callBack,void* user);
//设置信息帧回调
H264_DVR_API bool CALL_METHOD H264_DVR_SetInfoFrameCallBack(long lPlayHandle,InfoFramCallBack callback,void* user);

//本地颜色控制 //预览，回放，本地播放 一个函数
H264_DVR_API bool CALL_METHOD H264_DVR_LocalGetColor(long lHandle, DWORD nRegionNum, LONG *pBrightness, LONG *pContrast, LONG *pSaturation, LONG *pHue);
H264_DVR_API bool CALL_METHOD H264_DVR_LocalSetColor(long lHandle, DWORD nRegionNum, LONG nBrightness, LONG nContrast, LONG nSaturation, LONG nHue);
#endif
//设置本地ip
H264_DVR_API bool CALL_METHOD H264_DVR_SetLocalBindAddress(char*szIP);

//上报数据
H264_DVR_API bool CALL_METHOD H264_DVR_StartUploadData(long lLoginID,UploadDataType upLoadType,fUploadDataCallBack callBack,void* lUser);

H264_DVR_API bool CALL_METHOD H264_DVR_StopUploadData(long lLoginID,UploadDataType upLoadType);

//主动注册
H264_DVR_API bool CALL_METHOD H264_DVR_StartActiveRigister(int nPort, fMessCallBack cbFunc, void* dwDataUser);
H264_DVR_API bool CALL_METHOD H264_DVR_StopActiveRigister();

//子连接异常断开
H264_DVR_API long CALL_METHOD H264_DVR_SetSubDisconnectCallBack(fSubDisConnectCallBack callBack,DWORD userData)*/
HYBRIS_IMPLEMENT_FUNCTION2(mxmnetsdk_so, long,    H264_DVR_SetSubDisconnectCallBack, fSubDisConnectCallBack, DWORD);

/*
//设置保活时间
H264_DVR_API long CALL_METHOD H264_DVR_SetKeepLifeTime(long lLoginID,unsigned int perKeeplifeTime,unsigned int detectDisconTime);*/
HYBRIS_IMPLEMENT_FUNCTION3(mxmnetsdk_so, long,    H264_DVR_SetKeepLifeTime, long, unsigned int, unsigned int);

/*
//MAC 得到加密
H264_DVR_API bool CALL_METHOD H264_DVR_CheckEncrypt(char *pMac);

//设备搜索到的设备，与设备在同一个局域网的设备
H264_DVR_API bool CALL_METHOD H264_DVR_SearchDeviceEX(long lLoginID,SDK_NetDevList *pDevlist,SDK_TransferProtocol_V2 transferProtocol = SDK_TRANSFER_PROTOCOL_NETIP,int waittime = 15000);

//云台快速定位
//使用前 判断是否支持
H264_DVR_API bool CALL_METHOD H264_DVR_PTZPostion(long lLoginID,int nChannel,SDK_PositionPoint *pPositionPoint);

///< NVR和其连接的前端对讲
H264_DVR_API bool CALL_METHOD H264_DVR_StartDevTalk(long lLoginID,int nChannel,int waittime = 2000);
H264_DVR_API bool CALL_METHOD H264_DVR_StopDevTalk(long lLoginID,int nChannel,int waittime = 2000);
///<硬盘录像信息
//录像查询
//lLoginID		登陆句柄
//lpFindInfo	查询条件
//lpFileData	查找到的录像数据，外部开内存
//waittime		查询超时时间
H264_DVR_API long CALL_METHOD H264_DVR_RecordInfo(long lLoginID, SDK_SearchByTime* lpFindInfo, SDK_RecordStorageInfo *lpRecordData, int waittime = 15000);

H264_DVR_API bool CALL_METHOD H264_DVR_ControlFile(long lLoginID,SDK_NetFileControl *lpFileControl,int waittime = 15000);

//录像设备里面有多少音频文件，最大8个
//lLoginID		登陆句柄
//lpFindInfo	查询条件
//lpFileData	查找到的音频数据，外部开内存
//waittime		查询超时时间
H264_DVR_API bool CALL_METHOD H264_DVR_FindAudioFile(long lLoginID, SDK_MusicFileList* lpFileList, int waittime = 5000);

//	==播放音频文件需要文件名，其他的不需要，ACTION一定要赋值
//	== Action  参考 SDK_Music_Play_Action
H264_DVR_API bool CALL_METHOD H264_DVR_ControlAudio(long lLoginID, SDK_LocalMusicControl *lpMusicControl, int waittime = 2000);

H264_DVR_API bool CALL_METHOD H264_DVR_UserData(int ntype,char *pUserData, long nlen);
*/
