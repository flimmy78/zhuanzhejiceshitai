// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************

#ifndef __HMIDEFINE_H__
#define __HMIDEFINE_H__

#include <windows.h>
#include <cvirte.h>     
#include <userint.h>
#include "..\include\global.h"

//------------------------------------------------------------------------------------------------
typedef struct tagPT_HMISystemData
{
   short          usStep;   
   short          usHMIThreadLoop;
   HANDLE         uhHMIThread;
   short          usDisplayResult;
//   short          usLanguage;
   short          usForceThreadLoop;
   HANDLE         uhForceThread;
   long           ulPointer;
   long           ulStartPointer;
   long           ulDisplayPointer;
   short          ulPeriods;
   short          usShutdown;
   short          usDownloadConfig;
   float          ufDataBuffer[(FAI_DataBufferSize + 16) * FAI_PacerRate];
}PT_HMISystemData, far* LPT_HMISystemData;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
int __stdcall HMI_UDPRealtimeTrend(void);
int __stdcall HMI_UDPHistroyTrend(void);
int __stdcall HMI_TCPTransmitTable(void);
int __stdcall HMI_CreateThread(void);
int __stdcall HMI_TerminateThread(void);

int __stdcall HMI_TableRefresh( LPT_Record pData );
int __stdcall HMI_TableSetReportResult(LPT_Record pData);
int __stdcall HMI_TableSetRatedValue( LPT_Device pDevice );
int __stdcall HMI_TableSetInputValue( LPT_Device pDevice );
int __stdcall HMI_ACDevice_ReportSave(void);
int __stdcall HMI_ACDevice_ReportPrint(void);

int __stdcall HMI_DCDevice_ReportSave(void);
int __stdcall HMI_DCDevice_ReportPrint(void);

int __stdcall TBTypeNumber( char* pData, int nLanguage );
int __stdcall TBTestResult( char* pData, int nLanguage );
int __stdcall TBTesterName( char* pData, int nLanguage );
int __stdcall TBSerialNumber( char* pData, int nLanguage );
int __stdcall TBDeviceSelect( LPT_Device pDevice, int nLanguage );

int __stdcall S700K_GetSetting(char* pszFileName);
int __stdcall S700K_PutSetting(char* pszFileName);
int __stdcall S700K_Language(void);

int __stdcall HMI_InitializeForceTrend(void);
int __stdcall HMI_UninitializeForceTrend(void);

#endif // __MYFILE_H__
