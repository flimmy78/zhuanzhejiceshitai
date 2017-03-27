// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************
#include <cvirte.h>     
#include <userint.h>
#include "S700k.h"
#include "DAQDefine.h"
//#include "MyFile.h"
#include <ansi_c.h>
#include "..\Include\Global.h"

//------------------------------------------------------------------------------------------------
// 定义全局变量
//------------------------------------------------------------------------------------------------
extern int              plMain;
extern PT_Record        g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_DAQSystemData g_DAQSystemData;
extern PT_Device        g_Device;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// 根据测量力，获取B向比例阀控制电压
// 输入:
//    fForce      测量力
// 输出:
//    无
// 返回:
//                控制电压
//------------------------------------------------------------------------------------------------
float __stdcall ZDJ9_GetControlVoltageB(float fForce)
{
   float fData;
   
   if (fForce <= 2.50)
      fData = 1.0;
   else if ((fForce <= 2.75) && (fForce > 2.50))
      fData = 1.2;
   else if ((fForce <= 3.00) && (fForce > 2.75))
      fData = 1.3;
   else if ((fForce <= 3.25) && (fForce > 3.00))
      fData = 1.5;
   else if ((fForce <= 3.50) && (fForce > 3.25))
      fData = 1.7;
   else if ((fForce <= 3.75) && (fForce > 3.50))
      fData = 1.95;
   else if ((fForce <= 4.00) && (fForce > 3.75))
      fData = 2.10;
   else if ((fForce <= 4.25) && (fForce > 4.00))
      fData = 2.25;
   else if ((fForce <= 4.50) && (fForce > 4.25))
      fData = 2.40;
   else if ((fForce <= 4.75) && (fForce > 4.50))
      fData = 2.50;
   else if ((fForce <= 5.00) && (fForce > 4.75))
      fData = 2.65;
   else if ((fForce <= 5.25) && (fForce > 5.00))
      fData = 2.75;
   else if ((fForce <= 5.50) && (fForce > 5.25))
      fData = 2.85;
   else if ((fForce <= 5.75) && (fForce > 5.50))
      fData = 2.95;
   else if ((fForce <= 6.00) && (fForce > 5.75))
      fData = 3.05;
   else if ((fForce <= 6.25) && (fForce > 6.00))
      fData = 3.15;
   else if ((fForce <= 6.50) && (fForce > 6.25))
      fData = 3.20;
   else if ((fForce <= 6.75) && (fForce > 6.50))
      fData = 3.25;
   else if ((fForce <= 7.00) && (fForce > 6.75))
      fData = 3.35;
   else if ((fForce <= 7.25) && (fForce > 7.00))
      fData = 3.45;
   else if ((fForce <= 7.50) && (fForce > 7.25))
      fData = 3.50;
   else if ((fForce <= 7.75) && (fForce > 7.50))
      fData = 3.60;
   else if ((fForce <= 8.00) && (fForce > 7.75))
      fData = 3.68;
   else if ((fForce <= 8.25) && (fForce > 8.00))
      fData = 3.75;
   else if ((fForce <= 8.50) && (fForce > 8.25))
      fData = 3.80;
   else if ((fForce <= 8.75) && (fForce > 8.50))
      fData = 3.85;
   else if ((fForce <= 9.00) && (fForce > 8.75))
      fData = 3.92;
   else if ((fForce <= 9.25) && (fForce > 9.00))
      fData = 4.00;
   else if ((fForce <= 9.50) && (fForce > 9.25))
      fData = 4.04;
   else if ((fForce <= 9.75) && (fForce > 9.50))
      fData = 4.12;
   else if ((fForce <= 10.00) && (fForce > 9.75))
      fData = 4.18;
   else
      fData = 4.18;

   return fData;
}

//------------------------------------------------------------------------------------------------
// 根据测量力，获取A向比例阀控制电压
// 输入:
//    fForce      测量力
// 输出:
//    无
// 返回:
//                控制电压
//------------------------------------------------------------------------------------------------
float __stdcall ZDJ9_GetControlVoltageA(float fForce)
{
   float fData;
   
   if (fForce <= 2.50)
      fData = 1.4;
   else if ((fForce <= 2.75) && (fForce > 2.50))
      fData = 1.7;
   else if ((fForce <= 3.00) && (fForce > 2.75))
      fData = 2.0;
   else if ((fForce <= 3.25) && (fForce > 3.00))
      fData = 2.3;
   
   else if ((fForce <= 3.50) && (fForce > 3.25))
      fData = 2.5;
   else if ((fForce <= 3.75) && (fForce > 3.50))
      fData = 2.65;
   else if ((fForce <= 4.00) && (fForce > 3.75))
      fData = 2.80;
   else if ((fForce <= 4.25) && (fForce > 4.00))
      fData = 2.95;
   
   else if ((fForce <= 4.50) && (fForce > 4.25))
      fData = 3.10;
   else if ((fForce <= 4.75) && (fForce > 4.50))
      fData = 3.20;
   else if ((fForce <= 5.00) && (fForce > 4.75))
      fData = 3.30;
   else if ((fForce <= 5.25) && (fForce > 5.00))
      fData = 3.40;
   
   else if ((fForce <= 5.50) && (fForce > 5.25))
      fData = 3.50;
   else if ((fForce <= 5.75) && (fForce > 5.50))
      fData = 3.60;
   else if ((fForce <= 6.00) && (fForce > 5.75))
      fData = 3.70;
   else if ((fForce <= 6.25) && (fForce > 6.00))
      fData = 3.75;
   
   else if ((fForce <= 6.50) && (fForce > 6.25))
      fData = 3.82;
   else if ((fForce <= 6.75) && (fForce > 6.50))
      fData = 3.88;
   else if ((fForce <= 7.00) && (fForce > 6.75))
      fData = 3.95;
   else if ((fForce <= 7.25) && (fForce > 7.00))
      fData = 4.02;
   
   else if ((fForce <= 7.50) && (fForce > 7.25))
      fData = 4.08;
   else if ((fForce <= 7.75) && (fForce > 7.50))
      fData = 4.15;
   else if ((fForce <= 8.00) && (fForce > 7.75))
      fData = 4.22;
   else if ((fForce <= 8.25) && (fForce > 8.00))
      fData = 4.28;
   
   else if ((fForce <= 8.50) && (fForce > 8.25))
      fData = 4.33;
   else if ((fForce <= 8.75) && (fForce > 8.50))
      fData = 4.40;
   else if ((fForce <= 9.00) && (fForce > 8.75))
      fData = 4.46;
   else if ((fForce <= 9.25) && (fForce > 9.00))
      fData = 4.52;
   
   else if ((fForce <= 9.50) && (fForce > 9.25))
      fData = 4.58;
   else if ((fForce <= 9.75) && (fForce > 9.50))
      fData = 4.65;
   else if ((fForce <= 10.00) && (fForce > 9.75))
      fData = 4.70;
   else
      fData = 4.70;

   return fData;
}

//------------------------------------------------------------------------------------------------
// 转辙机故障控制，关闭比例阀，停止转辙机
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ZDJ9_ErrorHandle(LPT_Device pDevice, LPT_Record pData)
{
   // Clear all output
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_SetOutForce (0.0);
   DAQ_SetInForce (0.0);
   DAQ_SetTotalValve (1);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (0);

   // Set Error status
   pData->Control.usError = 1;
}

//------------------------------------------------------------------------------------------------
// 转辙机卸载控制，关闭比例阀
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ZDJ9_UnloadHandle(LPT_Device pDevice, LPT_Record pData)
{
   // Clear all output
   DAQ_SetOutForce (0.0);
   DAQ_SetInForce (0.0);
   DAQ_SetTotalValve (1);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (0);
}

//------------------------------------------------------------------------------------------------
// 保持力测试
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
DWORD WINAPI ZDJ9_MeasureRevision(LPT_Device pDevice, LPT_Record pData)
{
   double   dfDistance;
   DWORD    dwTicksError;
   DWORD    dwRetCode = 0;
   double   fStroke;
   DWORD    dwTimeout = 7000;
   
   // 如果要求停止测试，返回
   if (g_S700KData.Control.usTerminate)
      return -1;
   
   // 根据转辙机动作时间调整超时值
   if (g_Device.Standard.fLoad1_TravelTime > 0)
      dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;
   DAQ_Delay (2000);
   
   // 检查
   fStroke = pDevice->Standard.fStroke;
   if (fStroke <= 100.0)
      return -1;
   if (fStroke >= 300.0)
      return -1;
   fStroke = fStroke / 2.0 - 30.0;

   // 打开比例阀
   DAQ_SetTotalValve( 0 );
   DAQ_SetInForce( 1.0 );
   DAQ_SetOutForce( 1.0 );
   DAQ_SetOutValve( 0 );
   DAQ_SetInValve( 1 );
   
   DAQ_Delay( 1000 );
   // 设置步数
   g_S700KData.Control.usStep = 9;
   
   // 复位位移计数器
   DAQ_ResetStroke( );
   // 设置超时起始时间
   dwTicksError = GetTickCount( );
   // 转辙机左移
   DAQ_InControl( 1 );
   DAQ_OutControl( 0 );
   
   // 读入位移初始值
   dfDistance = fabs (DAQ_ReadStroke ());
   DAQ_Delay( 300 );
   while( 1 )
   {
      // 延时
      DAQ_Delay (10);
      // 如果到位跳出
      if (DAQ_ReadLeft ())
         break;
      // 采集数据
      DAQ_CheckMeasure ();
      
      // 错误检查，如果超时退出
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }

      // 如果没有走到指定位置，继续
      if (fabs (DAQ_ReadStroke () - dfDistance) < fStroke)
         continue;
     
      // 同时加大换向阀开单独，使转辙机保持
      DAQ_SetInForce( 8.0 );
      DAQ_SetOutForce( 8.0 );
      DAQ_SetTotalValve( 0 );
      DAQ_SetOutValve( 0 );
      DAQ_SetInValve( 0 );
     
      // 退出
      break;
   }
   
   // 保持5秒
   DAQ_InControl( 1 );
   DAQ_OutControl( 0 );
   DAQ_Delay (5000);
   
   // 断开控制，延时3秒
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_Delay (3000);
   
   // 设置步数
   g_S700KData.Control.usStep = 10;
   
   // 转辙机右移
   DAQ_InControl (0);
   DAQ_OutControl (1);
   // 保持5秒
   DAQ_Delay (5000);
   DAQ_InControl (0);
   DAQ_OutControl (0);
   // 断开控制，延时3秒
   DAQ_Delay (3000);

   // 设置步数
   g_S700KData.Control.usStep = 9;
   DAQ_InControl( 1 );
   DAQ_OutControl( 0 );
   DAQ_Delay (5000);
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_Delay (3000);
   
   // 设置步数
   g_S700KData.Control.usStep = 10;
   DAQ_InControl (0);
   DAQ_OutControl (1);
   DAQ_Delay (5000);
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_Delay (3000);

   // 设置步数
   g_S700KData.Control.usStep = 9;
   DAQ_InControl( 1 );
   DAQ_OutControl( 0 );
   DAQ_Delay (5000);
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_Delay (3000);
   
   // 设置步数
   g_S700KData.Control.usStep = 10;
   DAQ_InControl (0);
   DAQ_OutControl (1);
   DAQ_Delay (5000);
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_Delay (3000);

   // 设置步数
   g_S700KData.Control.usStep = 9;
   
   // 复位控制
   DAQ_SetTotalValve (0);
   DAQ_SetInForce (1.0);
   DAQ_SetOutForce (1.0);
   DAQ_SetOutValve (0);
   DAQ_Delay (1000);
   DAQ_InControl (1);
   DAQ_OutControl (0);
   DAQ_SetInValve (1);
   
   // 将转辙机最终停在A位
   dwTicksError = GetTickCount( );
   while( 1 )
   {
      if (DAQ_ReadLeft ())
         break;
      DAQ_CheckMeasure ();
     
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }

      DAQ_Delay (120);
   }
   DAQ_Delay (3000);
   DAQ_InControl (0);
   DAQ_OutControl (1);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (1);
   
   // 将转辙机最终停在B位
   dwTicksError = GetTickCount( );
   while( 1 )
   {
      if (DAQ_ReadRight ())
         break;
      DAQ_CheckMeasure ();
     
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }

      DAQ_Delay (120);
   }
   
   // 测试结束
   DAQ_SetOutForce (0.0);
   DAQ_SetInForce (0.0);
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_SetTotalValve (0);
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);

   return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// S700K转辙机测试
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
int WINAPI ZDJ9_ThreadRoutine( LPT_Device pDevice, LPT_Record pData )
{
   // 计时开始
   g_DAQSystemData.dwMeasureTicks = GetTickCount ();
   g_S700KData.Control.usStep = 0;

//   DAQ_ACSelect (1);
   // 开油泵
   DAQ_OilBumpControl (1);
   // 延时2秒
   DAQ_Delay (2000);

   // 转辙机动作过程检查，如果不成功退出
   // if (ZDJ9_DeviceCheck (pDevice, pData) == -1)
   //    goto Exit;
   
   // 如果要求停止测试，返回
   if (g_S700KData.Control.usTerminate)
      goto Exit;

   // 如果要求测试Load2
   if (g_Device.Config.usLoad2Test == 1)
   {
   // 测试Load2，如果不成功退出 
      if (ZDJ9_MeasureLoad2 (pDevice, pData) == -1)
         goto Exit;
   // 如果要求停止测试，返回
      if (g_S700KData.Control.usTerminate)
         goto Exit;
   }

   // 如果要求测试Load1
   if (g_Device.Config.usLoad1Test == 1)
   {
   // 测试Load1，如果不成功退出 
      if (ZDJ9_MeasureLoad1 (pDevice, pData) == -1)
         goto Exit;
   // 如果要求停止测试，返回
      if (g_S700KData.Control.usTerminate)
         goto Exit;
   }

   // 如果要求测试Load3
   if (g_Device.Config.usLoad3Test == 1)
   {
   // 测试Load3，如果不成功退出 
      if (ZDJ9_MeasureLoad3 (pDevice, pData) == -1)
         goto Exit;
   // 如果要求停止测试，返回
      if (g_S700KData.Control.usTerminate)
         goto Exit;
   }
   
   // 如果要求测试保持力
   // if (g_Device.Config.usRevisionTest == 1)
   // {
   // 测试保持力，如果不成功退出 
      // if (ZDJ9_MeasureRevision (pDevice, pData) == -1)
      //    goto Exit;
   // 如果要求停止测试，返回
      // if (g_S700KData.Control.usTerminate)
      //    goto Exit;
   // }
   
   // 如果要求测试挤岔力
   // if (g_Device.Config.usTraillingTest == 1)
   // {
   // 测试挤岔力，如果不成功退出 
      // if (ZDJ9_MeasureTrailling (pDevice, pData) == -1)
      //    goto Exit;
   // 如果要求停止测试，返回
      // if (g_S700KData.Control.usTerminate)
      //    goto Exit;
   // }

   // 延时
   DAQ_Delay (2000);
   
   // 正常退出
Exit:
//   SetCtrlVal (plMain, PANELMAIN_NG_Time, g_S700KData.Control.ulMeasTime);
   
   // 复位输出
   DAQ_InControl (0);                
   DAQ_OutControl (0);
   DAQ_SimulateTrack (0);
   DAQ_SetInForce (0.0);
   DAQ_SetOutForce (0.0);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (0);
   DAQ_SetTotalValve (0);
   Sleep (100);
   DAQ_OilBumpControl (0);
   Sleep (100);
   DAQ_OilBumpControl (0);
   return 0;
}
//------------------------------------------------------------------------------------------------

