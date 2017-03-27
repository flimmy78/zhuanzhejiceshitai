// #########################################################################
// *************************************************************************

#include <cvirte.h>     
#include "..\include\global.h"
#include <userint.h>
#include "S700K.h"
#include "inifile.h"
#include "HMIDefine.h"
#include "DAQDefine.h"
#include "Device.h"

//------------------------------------------------------------------------------------------------
// 定义全局变量
//------------------------------------------------------------------------------------------------
extern int              g_plMain;
extern int              g_plMain;
extern PT_Record        g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_Device        g_Device;
extern PT_HMISystemData g_HMISystemData;
extern PT_DAQSystemData g_DAQSystemData;
extern PT_InitStatus    g_InitStatus;
//------------------------------------------------------------------------------------------------
extern int              g_plPosition;
extern int              g_plCurrent;
extern int              g_plPower;
//------------------------------------------------------------------------------------------------
extern PT_Meter         g_Meters[MAX_METERS];
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void WINAPI TBDisplayValue( LPT_Device pDevice, LPT_DAQData pData )
{
   char  chData[ 128 ];
   // 显示指针表数据
   SetCtrlVal( g_plPosition, PLPosition_NUMERICGAUGE, pData->Data.dfStroke );
   SetCtrlVal( g_plCurrent, PLCurrent_NUMERICGAUGE, pData->Data.dfIa );
   SetCtrlVal( g_plPower, PLPower_NUMERICGAUGE, pData->Data.dfPower );
   
   // 显示指示灯
   SetCtrlVal( g_plMain, MAIN_LED_AUTO, pData->Data.usAutoMode );
   
   SetCtrlVal( g_plMain, MAIN_LED_CONFIG, g_S700KData.Control.usConfig );
   SetCtrlVal( g_plMain, MAIN_LED_LOAD2, g_Device.Config.usLoad2Test );
   SetCtrlVal( g_plMain, MAIN_LED_LOAD1, g_Device.Config.usLoad1Test );
   SetCtrlVal( g_plMain, MAIN_LED_LOAD3, g_Device.Config.usLoad3Test );
   SetCtrlVal( g_plMain, MAIN_LED_TRAIL, g_Device.Config.usTraillingTest );
   SetCtrlVal( g_plMain, MAIN_LED_REVISION, g_Device.Config.usRevisionTest );
   
   if (g_S700KData.Control.usRunStatus == RUNSTATUS_RUNING)
      SetCtrlVal(g_plMain, MAIN_LED_RUNING, 1);
   else
      SetCtrlVal(g_plMain, MAIN_LED_RUNING, 0);
   
   SetCtrlVal (g_plMain, MAIN_LED_FR1, pData->Data.usFR1);
   SetCtrlVal (g_plMain, MAIN_LED_FR2, pData->Data.usFR2);
   SetCtrlVal (g_plMain, MAIN_LED_JWXC, pData->Data.usJWXC);
   
   SetCtrlVal (g_plMain, MAIN_LED_ERROR, g_S700KData.Control.usError);
  
   // 显示步数
   sprintf (chData, "%d", g_S700KData.Control.usStep);
   SetCtrlVal (g_plMain, MAIN_STEP, chData);
   
   // 显示测量时间
   sprintf (chData, "%.1f s", g_S700KData.Control.ulMeasTime / 1000.0);
   SetCtrlVal (g_plMain, MAIN_MEASTIME, chData);
     
   return;
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
void __stdcall HMI_DataDisplay( LPT_DAQData pData )
{
   char  chData[ 128 ];

   SetCtrlVal(g_plMain, MAIN_NG_UAB, pData->Data.dfUab);
   SetCtrlVal(g_plMain, MAIN_NG_UBC, pData->Data.dfUbc);
   SetCtrlVal(g_plMain, MAIN_NG_UCA, pData->Data.dfUca);
   SetCtrlVal(g_plMain, MAIN_NG_IA, pData->Data.dfIa);
   SetCtrlVal(g_plMain, MAIN_NG_IB, pData->Data.dfIb);
   SetCtrlVal(g_plMain, MAIN_NG_IC, pData->Data.dfIc);
  // SetCtrlVal(g_plMain, MAIN_NG_UDC, pData->Data.dfUdc);
  // SetCtrlVal(g_plMain, MAIN_NG_IDC, pData->Data.dfIdc);
   SetCtrlVal(g_plMain, MAIN_NG_S, pData->Data.dfStroke);	 // 动程
   SetCtrlVal(g_plMain, MAIN_NG_FORCE, pData->Data.dfForce);

   //SetCtrlVal(g_plMain, MAIN_LED_RUNING, g_DAQSystemData.usRunStatus == RUNSTATUS_RUNING);
   
   //SetCtrlVal (g_plMain, MAIN_LED_FR1, pData->Data.usFR2 == 0);
   //SetCtrlVal (g_plMain, MAIN_LED_FR2, pData->Data.usFR1 == 0);
   //SetCtrlVal (g_plMain, MAIN_LED_JWXC, pData->Data.usJWXC);
   //SetCtrlVal (g_plMain, MAIN_LED_ERROR, g_DAQSystemData.usError);
#if 0   
   SetCtrlVal (g_plMain, MAIN_LED_D, pData->Data.usLeft == 1);
   SetCtrlVal (g_plMain, MAIN_LED_F, pData->Data.usRight == 1);
#else
   if((pData->Data.usLeft == 1) && (pData->Data.usRight == 1)){
	   // 转辙机停在中间，既不在定位又不在反位。
	  SetCtrlVal (g_plMain, MAIN_LED_D, 0);
      SetCtrlVal (g_plMain, MAIN_LED_F, 0);   	   
   }else{
	  SetCtrlVal (g_plMain, MAIN_LED_D, pData->Data.usLeft == 1);
      SetCtrlVal (g_plMain, MAIN_LED_F, pData->Data.usRight == 1);   
   }
#endif
   // 显示指针表数据
   SetCtrlVal( g_plPosition, PLPosition_NUMERICGAUGE, pData->Data.dfStroke );
   SetCtrlVal( g_plCurrent, PLCurrent_NUMERICGAUGE, pData->Data.dfIa );
   SetCtrlVal( g_plPower, PLPower_NUMERICGAUGE, pData->Data.dfPower );
   
   // 显示指示灯
   SetCtrlVal( g_plMain, MAIN_LED_AUTO, pData->Data.usAutoMode );
   
   SetCtrlVal( g_plMain, MAIN_LED_CONFIG, g_S700KData.Control.usConfig );
   SetCtrlVal( g_plMain, MAIN_LED_LOAD1, g_Device.Config.usLoad1Test );
   SetCtrlVal( g_plMain, MAIN_LED_LOAD2, g_Device.Config.usLoad2Test );
   SetCtrlVal( g_plMain, MAIN_LED_LOAD3, g_Device.Config.usLoad3Test );
   SetCtrlVal( g_plMain, MAIN_LED_TRAIL, g_Device.Config.usTraillingTest );
   SetCtrlVal( g_plMain, MAIN_LED_REVISION, g_Device.Config.usRevisionTest );
   
   if (g_S700KData.Control.usRunStatus == RUNSTATUS_RUNING)
      SetCtrlVal(g_plMain, MAIN_LED_RUNING, 1);
   else
      SetCtrlVal(g_plMain, MAIN_LED_RUNING, 0);
   
   SetCtrlVal (g_plMain, MAIN_LED_FR1, pData->Data.usFR1);
   SetCtrlVal (g_plMain, MAIN_LED_FR2, pData->Data.usFR2);
   SetCtrlVal (g_plMain, MAIN_LED_JWXC, pData->Data.usJWXC);
   
   SetCtrlVal (g_plMain, MAIN_LED_ERROR, g_S700KData.Control.usError);
  
   // 显示步数
   sprintf( chData, "%d", g_S700KData.Control.usStep );
   SetCtrlVal( g_plMain, MAIN_STEP, chData );
   
   // 显示测量时间
   sprintf (chData, "%.1f s", g_S700KData.Control.ulMeasTime / 1000.0);
   SetCtrlVal (g_plMain, MAIN_MEASTIME, chData);
     
   return;
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
void __stdcall HMI_StepDisplay(LPT_Record pData)
{
   char  chData[128];
   switch (pData->Control.usStep)
   {
   case -1:
      strcpy (chData, "准备就绪.");
      break;
   case 0:
      strcpy (chData, "移动转辙机到反位.");
      break;
   case 1:
      strcpy (chData, "测量反位到定位的动程.");
      break;
   case 2:
      strcpy (chData, "测量定位到反位的动程.");
      break;
   case 3:
      strcpy (chData, "测量反位到定位的最大力.");
      break;
   case 4:
      strcpy (chData, "测量定位到反位的最大力.");
      break;
   case 5:
      strcpy (chData, "测量反位到定位的最小力(无模拟电阻).");
      break;
   case 6:
      strcpy (chData, "测量定位到反位的最小力(无模拟电阻).");
      break;
   case 7:
      strcpy (chData, "测量反位到定位的最小力(有模拟电阻).");
      break;
   case 8:
      strcpy (chData, "测量定位到反位的最小力(有模拟电阻).");
      break;
   case 9:
      strcpy (chData, "检测反位到定位的保持力.");
      break;
   case 10:
      strcpy (chData, "检测定位到反位的保持力.");
      break;
   case 11:
      strcpy (chData, "测量终端定位的挤岔力.");
      break;
   case 12:
      strcpy (chData, "测量终端反位的挤岔力.");
      break;
   default:
      break;
   }
   SetCtrlVal (g_plMain,MAIN_STEPMSG, chData);
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
DWORD WINAPI HMI_ThreadRoutine(DWORD arg)
{
   MSG Msg;
   // 如果不要求退出
   while (g_HMISystemData.usHMIThreadLoop)
   {
      if (PeekMessage (&Msg, 0, 0, 0, PM_REMOVE))
      {
         TranslateMessage (&Msg);
         DispatchMessage (&Msg);
      }
      
      // 显示实时数据
      HMI_DataDisplay (&g_DAQData);   // 仪表和指示灯
      // 显示步数字符串
      HMI_StepDisplay (&g_S700KData);

      // 显示测试表数据
      HMI_TableRefresh (&g_S700KData);	  		// 测试表格中的数据
      HMI_TableSetReportResult (&g_S700KData);  // 测试表格中的结果。' ':没有测量值，-：合格，+：不合格
	  
	  // 更新手动界面数据
	  DAQ_DataDisplay( &g_DAQData );
      
      Sleep( 200 );		// 200ms刷新一次。
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
int __stdcall HMI_CreateThread(void)
{
   // 设置线程循环标志
   g_HMISystemData.usHMIThreadLoop = 1;
   
   // 建立线程
   g_HMISystemData.uhHMIThread = CreateThread (NULL, 0,
      (LPTHREAD_START_ROUTINE)&HMI_ThreadRoutine, NULL, 0, NULL);
   
   // 检查
   if (g_HMISystemData.uhHMIThread == NULL)
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
int __stdcall HMI_TerminateThread( void )
{
   // 要求线程停止
   g_HMISystemData.usHMIThreadLoop = FALSE;

   // 等待线程停止
   WaitForSingleObject (g_HMISystemData.uhHMIThread, 5000);
   CloseHandle (g_HMISystemData.uhHMIThread);
   g_HMISystemData.uhHMIThread = NULL;
   
   return TRUE;
}
//------------------------------------------------------------------------------------------------
