// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************

#ifndef __DAQDEFINE_H__
#define __DAQDEFINE_H__

#include <windows.h>
#include <cvirte.h>     
#include <userint.h>
#include "..\include\global.h"

//------------------------------------------------------------------------------------------------
typedef struct tagPT_DAQCard
{
   LONG        hDevice;             // Device handle of Advantech DAQ card, returned by function "DRV_DeviceOpen".
   DWORD       dwIndex;             // Index of Advantech DAQ Card, used by function "DRV_DeviceOpen".
   USHORT      usGainCode;          // Must be 0, means range of input singal is +/- 10V. PCI-1713:-5~+5V
   short       usStart;             // Start channel index
   short       usNumber;            // AD channel number
   long        ulPacerRate;         // AD pacer rate
   long        ulBufferSize;        // AD buffer size
   HGLOBAL     AcquisitionBuffer;   // "Interrupt scan" Data Buffer Used in DRV_FAIIntScanStart
   HGLOBAL     CopyBuffer;          // 
   long        ulBufferChanged;     //
   long        ulOverruned;         //
}PT_DAQCard, far* LPT_DAQCard;

//------------------------------------------------------------------------------------------------
typedef struct tagPT_DAQSystemData
{
   DWORD          dwMeasureMode;
   short          usError;
   short          usRunStatus;
   short          usTerminate;
   short          ThreadLoop_Meter;
   HANDLE         ThreadHandle_Meter;     //
   short          ThreadLoop_PLC;
   HANDLE         ThreadHandle_PLC;     //
   
   short          usDAQThreadLoop;
   unsigned       uhTCPInitialize;
   short          usDisplayRatedValue;
   short          usDisplayResult;
   HANDLE         uhDAQThread;
   short          usDisplayThreadLoop;
   HANDLE         uhDisplayThread;
   DWORD          dwMeasureTicks;      // Ticks when Measurement starts, Used by get measure time
   DWORD          dwDAQTicks;
   HANDLE         uhFAIThread;
   float          fAOAForce;           //
   float          fAOBForce;           //
   float          DataBuffer[FAI_PacerRate];    // Buffer size is 2048 * sizeof (float)
   float          fMaxForce; //单次采样最大值
   float          fMinForce; //单次采样最小值
   float          fIa;
   float          fIb;
   float          fIc;
   DWORD          dwSystemOperation;
}PT_DAQSystemData, far* LPT_DAQSystemData;
//------------------------------------------------------------------------------------------------
typedef enum{
	DIRECTION_A,
	DIRECTION_B
}Direction;
//------------------------------------------------------------------------------------------------
BOOL __stdcall DAQ_TerminateThread(void);
BOOL __stdcall DAQ_CreateThread(void);
//------------------------------------------------------------------------------------------------
double __stdcall DAQ_ReadStroke(void);
double __stdcall DAQ_ResetStroke(void);
double __stdcall DAQ_ReadForce(void);
double __stdcall FAI_FindMaxForce(void);
double __stdcall FAI_FindMinForce(void);
double __stdcall FAI_ReadForce(int nTime);

int __stdcall FAI_ScanStart(void);
int __stdcall FAI_ScanStop(void);

BOOL __stdcall FAI_ReadAIData(LPT_DAQData pData);
BOOL __stdcall DAQ_ReadDIStatus(LPT_DAQData pData);
void __stdcall DAQ_DataDisplay(LPT_DAQData pData);

double WINAPI DAQ_ReadForce(void);
double WINAPI DAQ_ReadForceTime(int nTime);
double WINAPI DAQAIReadTravelTime (Direction dir);
USHORT WINAPI DAQ_ReadLeft(void);
USHORT WINAPI DAQ_ReadRight(void);
//USHORT WINAPI DAQ_ReadTwoHandControl(void);
USHORT WINAPI DAQ_ReadMode(void);

void WINAPI DAQ_Delay(DWORD dwDelay);
void WINAPI DAQ_CheckMeasure(void);
BOOL WINAPI DAQ_CheckError(DWORD dwActionTime, DWORD dwTimeout);

//------------------------------------------------------------------------------------------------
void WINAPI DAQ_SimulateTrack(BOOL bAction);
void WINAPI DAQ_InControl(BOOL bAction);
void WINAPI DAQ_OutControl(BOOL bAction);
//void WINAPI DAQ_DCLeftControl(BOOL bAction);
//void WINAPI DAQ_DCRightControl(BOOL bAction);
//void WINAPI DAQ_DCLineControl(BOOL bAction);
void WINAPI DAQ_OilBumpControl(BOOL bAction);
void WINAPI DAQ_SocketSelect(BOOL bAction);
void WINAPI DAQ_SetTotalValve(BOOL bAction);
void WINAPI DAQ_SetOutValve(BOOL bAction);
void WINAPI DAQ_SetInValve(BOOL bAction);
//------------------------------------------------------------------------------------------------

int __stdcall S700K_ThreadRoutine(LPT_Device pDevice, LPT_Record pData);
void __stdcall S700K_ErrorHandle(LPT_Device pDevice, LPT_Record pData);
void __stdcall S700K_UnloadHandle(LPT_Device pDevice, LPT_Record pData);
int __stdcall S700K_MeasureLoad1(LPT_Device pDevice, LPT_Record pData);
int __stdcall S700K_MeasureLoad2(LPT_Device pDevice, LPT_Record pData);
int __stdcall S700K_MeasureLoad3(LPT_Device pDevice, LPT_Record pData);
int __stdcall S700K_DeviceCheck(LPT_Device pDevice, LPT_Record pData);
int __stdcall S700K_MeasureTrailling(LPT_Device pDevice, LPT_Record pData);
//------------------------------------------------------------------------------------------------
int __stdcall ZDJ9_ThreadRoutine(LPT_Device pDevice, LPT_Record pData);
void __stdcall ZDJ9_ErrorHandle(LPT_Device pDevice, LPT_Record pData);
void __stdcall ZDJ9_UnloadHandle(LPT_Device pDevice, LPT_Record pData);
int __stdcall ZDJ9_MeasureLoad1(LPT_Device pDevice, LPT_Record pData);
int __stdcall ZDJ9_MeasureLoad2(LPT_Device pDevice, LPT_Record pData);
int __stdcall ZDJ9_MeasureLoad3(LPT_Device pDevice, LPT_Record pData);
//int __stdcall ZDJ9_DeviceCheck(LPT_Device pDevice, LPT_Record pData);
//int __stdcall ZDJ9_MeasureTrailling(LPT_Device pDevice, LPT_Record pData);
//------------------------------------------------------------------------------------------------

void WINAPI DAQ_SetOutForce(float fValue);
void WINAPI DAQ_SetInForce(float fValue);
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void DAQ_Force2TotalValue(double dfRatedForce);// 设置液压负载台负载力区间。dfRatedForce     目标力
BOOL DAQ_GetTotalValue(void);                  // 读取液压负载台总阀当前状态。1:打开，0:关闭
void WINAPI DAQ_SetDCVoltage( float fValue );
void WINAPI DAQ_ACSelect(BOOL bAction);
//void WINAPI DAQ_DCSelect(BOOL bAction);

void WINAPI S700K_DisplayValue(LPT_Device pDevice, LPT_Record pData);
float __stdcall S700K_GetControlVoltageA(float fForce);
float __stdcall S700K_GetControlVoltageB(float fForce);

//------------------------------------------------------------------------------------------------
int __stdcall DAQ_Initialize(void);
int __stdcall DAQ_Uninitialize(void);

//------------------------------------------------------------------------------------------------
//PCI-1711 input
#define AICH_Uab              0     //     
#define AICH_Ubc              1     //
#define AICH_Uca              2     //
#define AICH_Ia               3     //     
#define AICH_Ib               4     //
#define AICH_Ic               5     //
#define AICH_Force            7     //
//OUPUT
#define AOCH_ForwardForce     0     //
#define AOCH_BackForce        1     //

//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// PCI-1784
#define PICH_Stroke           1     // 标尺

//------------------------------------------------------------------------------------------------
// PCI-1730


#endif // __MYFILE_H__
