// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************
#include <cvirte.h>     
#include <userint.h>
#include "S700K.h"
#include "DAQDefine.h"
#include <ansi_c.h>
#include "..\Include\Global.h"

//------------------------------------------------------------------------------------------------
// 定义全局变量
//------------------------------------------------------------------------------------------------
extern int              g_plDAQMain;
extern PT_Record        g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_DAQSystemData g_DAQSystemData;
extern PT_Device        g_Device;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// 转辙机挤岔力测量，如果转辙机在规定的时间内不能完成动作就返回错误
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
DWORD __stdcall ZDJ9_MeasureTrailling_A( LPT_Device pDevice, LPT_Record pData )
{
   double   dfTicks;
   DWORD    dwTicksError;
   DWORD    dwRetCode = 0;
   DWORD    dwTimeout = 10000;
   double   dfStrokeS;
   double   dfMaxForce = 0.0;
   double   dfStroke;
   
   // 如果要求停止测试，返回
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // 根据转辙机动作时间调整超时值
   if (g_Device.Standard.fLoad1_TravelTime > 0)
      dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 4000;

   // 设置比例阀初始控制值
   g_DAQSystemData.fAOAForce = 5.5;
   g_DAQSystemData.fAOBForce = 1.0;
   
   // 打开比例阀到初始开度
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   
   // 打开换向阀
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (1);
   DAQ_SetOutValve (0);
   
   DAQ_Delay (1000);
   
   // 转辙机左移
   DAQ_InControl (0);
   
   // 复位位移
   DAQ_ResetStroke ();
   // 读取位移初始值
   dfStrokeS = DAQ_ReadStroke ();
   while (1)
   {
      // 采集数据
      DAQ_CheckMeasure ();
      
      // 延时
      DAQ_Delay (50);
      
      // 比较采集力和之前的最大力，并记录最大力
      if (dfMaxForce < DAQ_ReadForce ())
         dfMaxForce = DAQ_ReadForce ();
      
      // 如果采集力大于30KN停止测试
      if (DAQ_ReadForce () > 30.0)
         break;
      
      // 读入位移计数器
      dfStroke = DAQ_ReadStroke ();
      // 如果转辙机已经走出50mm，认为测试不成功退出
      if (fabs (dfStroke - dfStrokeS) > 50.0)
      {
         break;
      }
      DAQ_Delay (50);
      
      // 调节比例阀
      g_DAQSystemData.fAOAForce += 0.05;
      // 限制比例阀开度
      if (g_DAQSystemData.fAOAForce > 9.0)
         break;
      
      // 设置比例阀开度
      DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   }
   
   // 记录最大的力作为挤岔力
   pData->ptMeasureDataA.ptTraillingData.dfForce = dfMaxForce;
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_4_1, dfMaxForce);
   
   // 卸载，复位控制
   g_DAQSystemData.fAOAForce = 1.0;
   g_DAQSystemData.fAOBForce = 1.0;
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (1);
   
   // 延时2秒
   DAQ_Delay (2000);
   
   // 计算位移
   dfStroke = fabs (DAQ_ReadStroke () - dfStrokeS);

   // 调整比例阀开度
   g_DAQSystemData.fAOAForce = 1.0;
   g_DAQSystemData.fAOBForce = 5.0;
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   
   // 打开换向阀
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (1);

   // 复位位移
   DAQ_ResetStroke ();
   // 读取位移初始值
   dfStrokeS = DAQ_ReadStroke ();
   dwTicksError = GetTickCount ();
   while (1)
   {
      // 采集数据
      DAQ_CheckMeasure ();
      
      DAQ_Delay (10);
      
      // 如果超时，返回错误
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      
      // 转辙机继续前进，说明转辙机已经挤脱
      if (fabs (DAQ_ReadStroke () - dfStrokeS) >= dfStroke)
      {
         break;
      }
   }

   // 复位控制
   DAQ_SetInForce (0.0);
   DAQ_SetOutForce (0.0);
   DAQ_SetTotalValve (1);
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);
   
   // 转辙机移动回右位
   DAQ_InControl (0);
   DAQ_OutControl (1);
   
   // 设置超时值
   dwTimeout = 7000;
   if (g_Device.Standard.fLoad1_TravelTime > 0)
      dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;
   dwTicksError = GetTickCount ();
   while (1)
   {
      // 如果到位，跳出
      if (DAQ_ReadRight ())
         break;
      // 采集数据
      DAQ_CheckMeasure ();
      // 如果超时，返回错误
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      DAQ_Delay (50);
   }
   
   // 复位控制
   DAQ_InControl (0);
   DAQ_SetTotalValve (0);
   DAQ_SetInForce (0.0);
   DAQ_SetOutForce (0.0);
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);
   DAQ_OutControl (0);

   return dwRetCode;
}

//------------------------------------------------------------------------------------------------
DWORD __stdcall ZDJ9_MeasureTrailling_B( LPT_Device pDevice, LPT_Record pData )
{
   double   dfTicks;
   DWORD    dwTicksError;
   DWORD    dwRetCode = 0;
   DWORD    dwTimeout = 10000;
   double   dfStrokeS;
   double   dfMaxForce = 0.0;
   double   dfStroke;
   
   // 如果要求停止测试，返回
   if (g_DAQSystemData.usTerminate)
      return -1;

   // 根据转辙机动作时间调整超时值
   if (g_Device.Standard.fLoad1_TravelTime > 0)
     dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 4000;
   
   // 设置比例阀初始控制值
   g_DAQSystemData.fAOAForce = 1.0;
   g_DAQSystemData.fAOBForce = 5.5;
   
   // 打开比例阀到初始开度
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   
   // 打开换向阀
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (1);
   
   DAQ_Delay (1000);
   
   // 转辙机左移
   DAQ_InControl (0);
   
   // 复位位移
   DAQ_ResetStroke ();
   // 读取位移初始值
   dfStrokeS = DAQ_ReadStroke ();
   while (1)
   {
      // 采集数据
      DAQ_CheckMeasure ();
      
      DAQ_Delay (50);
      
      // 比较采集力和之前的最大力，并记录最大力
      if (dfMaxForce < DAQ_ReadForce ())
         dfMaxForce = DAQ_ReadForce ();
      // Check force
      
      // 如果采集力大于30KN停止测试
      if (DAQ_ReadForce () > 30.0)
         break;
      
      // 读入位移计数器
      dfStroke = DAQ_ReadStroke ();
      // 如果转辙机已经走出50mm，认为测试不成功退出
      if (fabs (dfStroke - dfStrokeS) > 30.0)
      {
         break;
      }
      DAQ_Delay (50);
      
      // 调节比例阀
      g_DAQSystemData.fAOBForce += 0.05;
      // 限制比例阀开度
      if (g_DAQSystemData.fAOBForce > 9.0)
         break;
      
      // 设置比例阀开度
      DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   }
   
   // 记录最大的力作为挤岔力
   pData->ptMeasureDataB.ptTraillingData.dfForce = dfMaxForce;
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_4_2, dfMaxForce);
   
   // 卸载，复位控制
   g_DAQSystemData.fAOAForce = 1.0;
   g_DAQSystemData.fAOBForce = 1.0;
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (1);
   DAQ_SetOutValve (0);
   
   DAQ_Delay (2000);
   
   // 计算当前位移，用于比较是否挤脱 
   dfStroke = fabs (DAQ_ReadStroke () - dfStrokeS);

   // 调整比例阀开度
   g_DAQSystemData.fAOAForce = 5.0;
   g_DAQSystemData.fAOBForce = 1.0;
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   
   // 打开换向阀
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (1);
   DAQ_SetOutValve (0);

   // 复位位移
   DAQ_ResetStroke ();
   // 读取位移初始值
   dfStrokeS = DAQ_ReadStroke ();
   dwTicksError = GetTickCount ();
   while (1)
   {
      // 采集数据
      DAQ_CheckMeasure ();
      
      DAQ_Delay (10);
      
      // 如果超时，返回错误
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      
      // 转辙机继续前进，说明转辙机已经挤脱
      if (fabs (DAQ_ReadStroke () - dfStrokeS) >= dfStroke)
      {
         break;
      }
   }

   // 复位控制
   DAQ_SetInForce (0.0);
   DAQ_SetOutForce (0.0);
   DAQ_SetTotalValve (1);
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);
   
   // 转辙机移动回左位
   DAQ_InControl (1);
   DAQ_OutControl (0);
   
   // 设置超时值
   dwTimeout = 7000;
   if (g_Device.Standard.fLoad1_TravelTime > 0)
      dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;
   dwTicksError = GetTickCount ();
   while (1)
   {
      // 如果到位，退出
      if (DAQ_ReadLeft ())
         break;
      // 采集数据
      DAQ_CheckMeasure ();
      // 如果超时，返回错误
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      DAQ_Delay (50);
   }
   
   // 复位控制
   DAQ_InControl (0);
   DAQ_SetTotalValve (0);
   DAQ_SetInForce (0.0);
   DAQ_SetOutForce (0.0);
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);
   DAQ_OutControl (0);

   return dwRetCode;
}

//------------------------------------------------------------------------------------------------
int __stdcall ZDJ9_MeasureTrailling( LPT_Device pDevice, LPT_Record pData )
{
   
   if (g_DAQSystemData.usTerminate)
      return -1;

   DAQ_Delay (2000);
   
   // Start...........
   DAQ_SimulateTrack (1);
   
   g_S700KData.Control.usStep = 11;
   if (ZDJ9_MeasureTrailling_B (pDevice, pData) == -1)
      return -1;

   DAQ_Delay( 2000 );

   g_S700KData.Control.usStep = 12;
   if (ZDJ9_MeasureTrailling_A (pDevice, pData) == -1)
      return -1;

   DAQ_SimulateTrack( 0 );
   
   return 0;
}

//------------------------------------------------------------------------------------------------
