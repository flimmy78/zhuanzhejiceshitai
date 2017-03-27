// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************

#include <windows.h>
#include <cvirte.h>     
#include <userint.h>
#include "..\include\Global.h"

#ifndef __MYFILE_H__
#define __MYFILE_H__

//------------------------------------------------------------------------------------------------
typedef struct tagPT_SystemData
{
   short          usThreadLoop;
   HANDLE         uhDAQThread;
   short          usDownloadConfig;
   short          usReboot;         // ÖØÆô
   short          usShutdown;       // ¹Ø»ú
   short          usDisplayResult;
   short          usLanguage;
   PT_UDPSocket   UDPRealtime;
   PT_UDPSocket   UDPTrend;
   long           ulPointer;
   long           ulStartPointer;
   long           ulDisplayPointer;
   short          ulPeriods;
   float          ufDataBuffer[(FAI_DataBufferSize + 16) * FAI_PacerRate];
}PT_SystemData, far* LPT_SystemData;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
int __stdcall UDPRealtimeTrend(void);
int __stdcall UDPHistroyTrend(void);
int __stdcall TCPTransmitTable(void);
int __stdcall DAQCreateThread(void);
int __stdcall DAQTerminateThread(void);

int __stdcall QLTableRefresh( LPT_ReportData pData );
int __stdcall QLTableSetReportResult(LPT_ReportData pData);
int __stdcall QLTableSetRatedValue( LPT_Device pDevice );
int __stdcall QLTableSetInputValue( LPT_Device pDevice );
int __stdcall QLReportSave(void);
int __stdcall QLReportPrint(void);

int __stdcall TBTypeNumber( char* pData, int nLanguage );
int __stdcall TBTestResult( char* pData, int nLanguage );
int __stdcall TBTesterName( char* pData, int nLanguage );
int __stdcall TBSerialNumber( char* pData, int nLanguage );
int __stdcall TBDeviceSelect( LPT_Device pDevice, int nLanguage );

int __stdcall S700K_GetSetting(char* pszFileName);
int __stdcall S700K_PutSetting(char* pszFileName);
int __stdcall S700K_Language(void);

int __stdcall InitializeForceTrend(void);
int __stdcall UninitializeForceTrend(void);

#endif // __MYFILE_H__
