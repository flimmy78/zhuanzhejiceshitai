// #########################################################################
// *************************************************************************

#include <cvirte.h>     
#include "..\include\Global.h"
#include <userint.h>
#include "S700K.h"
#include "inifile.h"
#include "Myfile.h"

//------------------------------------------------------------------------------------------------
// 定义全局变量
//------------------------------------------------------------------------------------------------
extern int              plMain;
extern PT_ReportData    g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_Device        g_Device;
extern PT_SystemData    g_SystemData;
//------------------------------------------------------------------------------------------------
extern int              plPosition;
extern int              plCurrent;
extern int              plPower;
extern PT_InitStatus    g_InitStatus;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// 显示测量步数，英语显示
// 输入:
//    pData       测试结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall DAQStepDisplayEnglish(LPT_ReportData pData)
{
   char  chData[128];
   switch (pData->Control.usStep)
   {
   case -1:
      strcpy (chData, "Ready.");
      break;
   case 0:
      strcpy (chData, "Move point machine to position B.");
      break;
   case 1:
      strcpy (chData, "Measure storke from position B to A.");
      break;
   case 2:
      strcpy (chData, "Measure storke from position A to B.");
      break;
   case 3:
      strcpy (chData, "Measure maximum force from position B to A.");
      break;
   case 4:
      strcpy (chData, "Measure maximum force from position A to B.");
      break;
   case 5:
      strcpy (chData, "Measure operating force (without R.V) from position B to A.");
      break;
   case 6:
      strcpy (chData, "Measure operating force (without R.V) from position A to B.");
      break;
   case 7:
      strcpy (chData, "Measure operating force (with R.V) from position B to A.");
      break;
   case 8:
      strcpy (chData, "Measure operating force (with R.V) from position A to B.");
      break;
   case 9:
      strcpy (chData, "Check revision from position B to A.");
      break;
   case 10:
      strcpy (chData, "Check revision from position A to B.");
      break;
   case 11:
      strcpy (chData, "Measure trailling force at endposition direction A.");
      break;
   case 12:
      strcpy (chData, "Measure trailling force at endposition direction B.");
      break;
   default:
      break;
   }
   SetCtrlVal (plMain,PANELMAIN_STEPMSG, chData);
}

//------------------------------------------------------------------------------------------------
// 显示测量步数，中文显示
// 输入:
//    pData       测试结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall DAQStepDisplayChinese(LPT_ReportData pData)
{
   char  chData[128];
   switch (pData->Control.usStep)
   {
   case -1:
      strcpy (chData, "准备就绪.");
      break;
   case 0:
      strcpy (chData, "移动转辙机到位置B.");
      break;
   case 1:
      strcpy (chData, "测量位置B到A的动程.");
      break;
   case 2:
      strcpy (chData, "测量位置A到B的动程.");
      break;
   case 3:
      strcpy (chData, "测量位置B到A的最大力.");
      break;
   case 4:
      strcpy (chData, "测量位置A到B的最大力.");
      break;
   case 5:
      strcpy (chData, "测量位置B到A的最小力(无模拟电阻).");
      break;
   case 6:
      strcpy (chData, "测量位置A到B的最小力(无模拟电阻).");
      break;
   case 7:
      strcpy (chData, "测量位置B到A的最小力(有模拟电阻).");
      break;
   case 8:
      strcpy (chData, "测量位置A到B的最小力(有模拟电阻).");
      break;
   case 9:
      strcpy (chData, "检测位置B到A的保持力.");
      break;
   case 10:
      strcpy (chData, "检测位置A到B的保持力.");
      break;
   case 11:
      strcpy (chData, "测量终端位置A的挤岔力.");
      break;
   case 12:
      strcpy (chData, "测量终端位置B的挤岔力.");
      break;
   default:
      break;
   }
   SetCtrlVal (plMain,PANELMAIN_STEPMSG, chData);
}

//------------------------------------------------------------------------------------------------
// 显示测量步数
// 输入:
//    pData       测试结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall DAQStepDisplay(LPT_ReportData pData)
{
   // 英语显示
   if (g_SystemData.usLanguage == 0)
      DAQStepDisplayEnglish (pData);
   // 中文显示
   else
      DAQStepDisplayChinese (pData);
}

//------------------------------------------------------------------------------------------------
// 显示测量数据
// 输入:
//    pData       测试结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall DAQDataDisplay( LPT_DAQData pData )
{
   char  chData[ 128 ];
   // 显示指针表数据
   SetCtrlVal( plPosition, PLPosition_NUMERICGAUGE, pData->Data.dfDistance );
   SetCtrlVal( plCurrent, PLCurrent_NUMERICGAUGE, pData->Data.dfIa );
   SetCtrlVal( plPower, PLPower_NUMERICGAUGE, pData->Data.dfPower );
   
   // 显示指示灯
   SetCtrlVal( plMain, PANELMAIN_LED_AUTO, pData->Data.usAutoMode );
   SetCtrlVal( plMain, PANELMAIN_LED_Connect, g_InitStatus.chInitNetwork );
   
   SetCtrlVal( plMain, PANELMAIN_LED_CONFIG, g_S700KData.Control.usConfig );
   SetCtrlVal( plMain, PANELMAIN_LED_LOAD2, g_S700KData.ptDevice.Config.usLoad2Test );
   SetCtrlVal( plMain, PANELMAIN_LED_LOAD1, g_S700KData.ptDevice.Config.usLoad1Test );
   SetCtrlVal( plMain, PANELMAIN_LED_LOAD3, g_S700KData.ptDevice.Config.usLoad3Test );
   SetCtrlVal( plMain, PANELMAIN_LED_TRAIL, g_S700KData.ptDevice.Config.usTraillingTest );
   SetCtrlVal( plMain, PANELMAIN_LED_REVISION, g_S700KData.ptDevice.Config.usRevisionTest );
   
   if (g_S700KData.Control.usRunStatus == RUNSTATUS_RUNING)
      SetCtrlVal(plMain, PANELMAIN_LED_RUNING, 1);
   else
      SetCtrlVal(plMain, PANELMAIN_LED_RUNING, 0);
   
   SetCtrlVal (plMain, PANELMAIN_LED_FR1, pData->Data.usFR1);
   SetCtrlVal (plMain, PANELMAIN_LED_FR2, pData->Data.usFR2);
   SetCtrlVal (plMain, PANELMAIN_LED_JWXC, pData->Data.usJWXC);
   
   SetCtrlVal (plMain, PANELMAIN_LED_ERROR, g_S700KData.Control.usError);
  
   // 显示步数
   sprintf( chData, "%d", g_S700KData.Control.usStep );
   SetCtrlVal( plMain, PANELMAIN_STEP, chData );
   
   // 显示测量时间
   sprintf (chData, "%.1f s", g_S700KData.Control.ulMeasTime / 1000.0);
   SetCtrlVal (plMain, PANELMAIN_MEASTIME, chData);
     
   return;
}

//------------------------------------------------------------------------------------------------
// 数据显示主线程
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
DWORD WINAPI DAQThreadRoutine(DWORD arg)
{
   DWORD dwTicks;
   // 如果不要求退出
   while (g_SystemData.usThreadLoop)
   {
      // 显示实时数据
      DAQDataDisplay (&g_DAQData);
      // 显示步数
      DAQStepDisplay (&g_S700KData);

      // 显示测试表数据
      QLTableRefresh (&g_S700KData);
      QLTableSetReportResult (&g_S700KData);
      
      Sleep( 200 );
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
// 启动数据显示线程
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//---------------------------------------------------------------------------
int __stdcall DAQCreateThread(void)
{
   // 设置线程循环标志
   g_SystemData.usThreadLoop = 1;
   
   // 建立线程
   g_SystemData.uhDAQThread = CreateThread (NULL, 0,
      (LPTHREAD_START_ROUTINE)&DAQThreadRoutine, NULL, 0, NULL);
   
   // 检查
   if (g_SystemData.uhDAQThread == NULL)
      return FALSE;
   
   return TRUE;
}

//------------------------------------------------------------------------------------------------
// 停止数据显示线程
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//---------------------------------------------------------------------------
int __stdcall DAQTerminateThread( void )
{
   // 要求线程停止
   g_SystemData.usThreadLoop = FALSE;

   // 等待线程停止
   WaitForSingleObject (g_SystemData.uhDAQThread, 5000);
   CloseHandle (g_SystemData.uhDAQThread);
   g_SystemData.uhDAQThread = NULL;
   
   return TRUE;
}
//------------------------------------------------------------------------------------------------
