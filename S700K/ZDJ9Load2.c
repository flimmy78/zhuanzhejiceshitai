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
extern PT_Record    g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_DAQSystemData g_DAQSystemData;
extern PT_Device        g_Device;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// 转辙机Load2测量，如果转辙机在规定的时间内不能完成动作就返回错误
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
DWORD __stdcall ZDJ9_MeasureLoad2_A( LPT_Device pDevice, LPT_Record pData)
{
   double   dfDistance, dfDistanceS, dfDistanceE;
   double   dfStrokeS;
   DWORD    dwTicksS, dwTicksE;
   double   dfSpeed;
   double   dfTicks;
   double   dfForce = 0.0;
   double   dfIa = 0.0, dfIb = 0.0, dfIc = 0.0;
   DWORD    dwTicksError;
   DWORD    dwRetCode = 0;
   BOOL     bStart = FALSE;
   DWORD    dwTimeout = 7000;
   BOOL     bOk = 0;
   double   dfStroke;
   int      dwCount = 0;
   double   dfDelta;
   double   dfDiff;
   double   dfForceCount= 0.0;
   double   dfAOForce;
   DWORD    dwTickStop = 0;
   double   dfMaxForce = 0.0;
   double   dfRatedForce = 0.0;
   double   dfHalfStroke;
   
   // 如果要求停止测试，返回
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // 我们只在动程过半后进行测量数据处理
   dfHalfStroke = g_Device.Standard.fStroke / 2;
   dfHalfStroke += 10.0;
   
   g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState = 0;
   
   // 设置Load2最大调节力为最大力的1.8倍
   dfRatedForce = g_Device.Standard.fLoad2_MaxForce;
//   dfRatedForce *= 1.8;
   
   if (pDevice->Standard.fLoad2_A2B_AVoltage > 10.0)
      return -1;

   // 取得换向阀初始控制值
   g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad2_A2B_AVoltage;
   g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad2_A2B_BVoltage;
   
   g_DAQSystemData.fAOAForce = 1.0;
   dfAOForce = g_DAQSystemData.fAOBForce;
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);

   // 将换向阀开度设置为初始开度的70%，防止力不能加到位
   g_DAQSystemData.fAOBForce = dfAOForce * 0.7;
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   
   // 打开换向阀，转辙机右移
   DAQ_SetOutValve (1);
   DAQ_SetInValve (0);
   DAQ_SetTotalValve (0);
   
   DAQ_Delay (500);
   DAQ_OutControl (1);
   
   // 复位位移
   DAQ_ResetStroke ();
   // 读取位移初始值
   dfStrokeS = dfStroke = dfDistanceS = DAQ_ReadStroke ();
   
   // 起始时间
   dwTicksError = GetTickCount ();
   dwTicksS = GetTickCount ();
   // 复位最大力
   g_DAQSystemData.fMaxForce = 0.0;
   dwTimeout = 10000;
   while( 1)
   {
      // 如果到位，跳出
      if (DAQ_ReadRight ())
         break;
      // 延时
      DAQ_Delay (50);
      // 采集数据
      DAQ_CheckMeasure();
      
      // 如果超时，返回错误
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
//         ZDJ9_UnloadHandle (pDevice, pData);
         break;
      }
      
      // 等待位移大于10mm时将换向阀开度调节到预定开度，然后开始加力测试Load2最大力
      if ((fabs (DAQ_ReadStroke () - dfDistanceS) < 10) && (bStart == FALSE))
         continue;
      else if (bStart == FALSE)
      {
         g_DAQSystemData.fAOBForce = dfAOForce * 1.0;
         DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
         bStart = TRUE;
         dfDistanceS = DAQ_ReadStroke ();
         dwTicksS = GetTickCount ();
         dwTicksError = GetTickCount ();
         dwTimeout = 7000;
         if (g_Device.Standard.fLoad1_TravelTime > 0)
            dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;
      }
      
      // 在指定的位移范围内累计测量参数，作为无法卡阻时的测量值
      dfDistanceE = DAQ_ReadStroke ();
      if ((fabs (dfDistanceE - dfStroke) > dfHalfStroke) && ((fabs (dfDistanceE - dfStroke) + 5) < pDevice->Standard.fStroke))
      {
         // 累加测量值
         dwCount ++;
         dfForceCount += DAQ_ReadForce ();
         dfIa += g_DAQData.Data.dfIa;
         dfIb += g_DAQData.Data.dfIb;
         dfIc += g_DAQData.Data.dfIc;
         // 设置显示值
         pData->ptMeasureDataA.ptLoad2Data.dfIa = dfIa / dwCount;
         pData->ptMeasureDataA.ptLoad2Data.dfIb = dfIb / dwCount;
         pData->ptMeasureDataA.ptLoad2Data.dfIc = dfIc / dwCount;
      }
      // 位移末端不测量
      if (g_Device.Standard.fStroke - fabs(dfDistanceE - dfStroke) < 10)
      {
         continue;
      }
   }
   // 读入位移终止值
   dfDistanceE = DAQ_ReadStroke ();
   // 计算动程
   dfDistance = fabs (dfDistanceE - dfStrokeS);
   
   // 保存测量值，并显示
   pData->ptMeasureDataA.ptCheckData.dfInterval = dfDistance;
   pData->ptMeasureDataA.ptCheckData.bCheckState = TRUE;
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_DISB_A, dfDistance);
   
   // 防止除零错误
   if (dwCount == 0)
      dwCount = 1;
   // 如果卡阻
   if (bOk == 1)
   {
      // 设置状态
      g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState = 2;
      // 调整测量值
      dfForce *= g_Device.Standard.fLoad2_Scale;
      
      if (dfForce > g_Device.Standard.fLoad2_MaxForce)
      {
         if ((dfForce - g_Device.Standard.fLoad2_MaxForce) < 0.1)
            dfForce = g_Device.Standard.fLoad2_MaxForce;
      }
      if (dfForce < g_Device.Standard.fLoad1_OperateForce)
      {
         if ((g_Device.Standard.fLoad1_OperateForce - dfForce) < 0.1)
            dfForce = g_Device.Standard.fLoad1_OperateForce;
      }
      
      // 参照B向力调整A向力
      dfForce += (pData->ptMeasureDataB.ptLoad2Data.dfForce - dfForce) / 2;
      
      if (dfForce > g_Device.Standard.fLoad2_MaxForce)
      {
         if ((dfForce - g_Device.Standard.fLoad2_MaxForce) < 0.1)
            dfForce = g_Device.Standard.fLoad2_MaxForce;
      }
      if (dfForce < g_Device.Standard.fLoad1_OperateForce)
      {
         if ((g_Device.Standard.fLoad1_OperateForce - dfForce) < 0.1)
            dfForce = g_Device.Standard.fLoad1_OperateForce + 0.05;
      }
   }
   // 不卡阻
   else
   {
      dfForce = dfForceCount / dwCount;
      g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState = 0;
   }
   
   // 设置测量结果
   pData->ptMeasureDataA.ptLoad2Data.dfForce1 = dfForce;
   pData->ptMeasureDataA.ptLoad2Data.dfForce = pData->ptMeasureDataA.ptLoad2Data.dfForce1;
   
   // 复位控制，转辙机走到位
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);
   DAQ_SetOutForce (0.0);
   DAQ_SetTotalValve (1);
   // 复位控制
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_SetTotalValve (0);
   
   // 显示测量值
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_2_1, pData->ptMeasureDataA.ptLoad2Data.dfForce);
   return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// 转辙机Load2测量，如果转辙机在规定的时间内不能完成动作就返回错误
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
DWORD __stdcall ZDJ9_MeasureLoad2_B(LPT_Device pDevice, LPT_Record pData)
{
   double   dfStrokeS, dfDistance, dfDistanceS, dfDistanceE;
   DWORD    dwTicksS, dwTicksE;
   double   dfSpeed;
   double   dfTicks;
   double   dfForce = 0.0;
   double   dfIa = 0.0, dfIb = 0.0, dfIc = 0.0;
   DWORD    dwTicksError;
   DWORD    dwRetCode = 0;
   BOOL     bStart = FALSE;
   DWORD    dwTimeout = 7000;
   BOOL     bOk = 0;
   double   dfStroke;
   int      dwCount = 0;
   double   dfDelta;
   double   dfDiff;
   double   dfForceCount= 0.0;
   double   dfAOForce;
   DWORD    dwTickStop = 0;
   double   dfMaxForce = 0.0;
   double   dfRatedForce = 0.0;
   double   dfHalfStroke;
   
   // 如果要求停止测试，返回
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // 我们只在动程过半后进行测量数据处理
   dfHalfStroke = g_Device.Standard.fStroke / 2;
   dfHalfStroke += 10.0;
   
   g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState = 0;
   
   // 设置Load2最大调节力为最大力的1.5倍
   dfRatedForce = g_Device.Standard.fLoad2_MaxForce;
   
   if (pDevice->Standard.fLoad2_B2A_AVoltage > 10.0)
      return -1;  

   // 取得换向阀初始控制值
   g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad2_B2A_AVoltage;
   g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad2_B2A_BVoltage;
   
   dfAOForce = g_DAQSystemData.fAOAForce;
   g_DAQSystemData.fAOBForce = 1.0;
   
   // 将换向阀开度设置为初始开度的70%，防止力不能加到位
   g_DAQSystemData.fAOAForce = dfAOForce * 0.7;
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   
   // 打开换向阀
   DAQ_SetOutValve (0);
   DAQ_SetInValve (1);
   DAQ_SetTotalValve (0);
   
   DAQ_Delay (500);
   
   // 打开换向阀，转辙机左移
   DAQ_InControl (1);
   
   // 复位位移
   DAQ_ResetStroke ();
   // 读取位移初始值
   dfStrokeS = dfStroke = dfDistanceS = DAQ_ReadStroke ();
   
   // 起始时间
   dwTicksError = GetTickCount ();
   dwTicksS = GetTickCount ();
   // 复位最大力
   g_DAQSystemData.fMaxForce = 0.0;
   dwTimeout = 10000;
   while (1)
   {
      // 如果到位，跳出
      if (DAQ_ReadLeft ())
         break;
      // 延时
      DAQ_Delay (50);
      // 采集数据
      DAQ_CheckMeasure ();
      
      // 如果超时，返回错误
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_UnloadHandle (pDevice, pData);
         break;
      }
      
      // 等待位移大于10mm时将换向阀开度调节到预定开度，然后开始加力测试Load2最大力
      if ((fabs (DAQ_ReadStroke () - dfDistanceS) < 10) && (bStart == FALSE))
         continue;
      else if ((bStart == FALSE))
      {
         g_DAQSystemData.fAOAForce = dfAOForce * 1.0;
         DAQ_SetInForce (g_DAQSystemData.fAOAForce);
         bStart = TRUE;
         dfDistanceS = DAQ_ReadStroke ();
         dwTicksS = GetTickCount ();
         dwTicksError = GetTickCount ();
         dwTimeout = 7000;
         if (g_Device.Standard.fLoad1_TravelTime > 0)
            dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;
      }
      if (bStart == FALSE)
         continue;
      
      // 在指定的位移范围内累计测量参数，作为无法卡阻时的测量值
      dfDistanceE = DAQ_ReadStroke ();
      if ((fabs (dfDistanceE - dfStroke) > dfHalfStroke) && ((fabs (dfDistanceE - dfStroke) + 5) < pDevice->Standard.fStroke))
      {
         // 累加测量值
         dwCount ++;
         dfForceCount += DAQ_ReadForce ();
         dfIa += g_DAQData.Data.dfIa;
         dfIb += g_DAQData.Data.dfIb;
         dfIc += g_DAQData.Data.dfIc;
         // 设置显示值
         pData->ptMeasureDataB.ptLoad2Data.dfIa = dfIa / dwCount;
         pData->ptMeasureDataB.ptLoad2Data.dfIb = dfIb / dwCount;
         pData->ptMeasureDataB.ptLoad2Data.dfIc = dfIc / dwCount;
      }
      
      // 位移末端不测量
      if (g_Device.Standard.fStroke - fabs(dfDistanceE - dfStroke) < 10)
      {
         continue;
      }
      
   }
   // 读入位移终止值
   dfDistanceE = DAQ_ReadStroke ();
   // 计算动程
   dfDistance = fabs( dfDistanceE - dfStrokeS);
   
   // 保存测量值，并显示
   pData->ptMeasureDataB.ptCheckData.dfInterval = dfDistance;
   pData->ptMeasureDataB.ptCheckData.bCheckState = TRUE;
   SetCtrlVal( g_plDAQMain, DAQMAIN_NG_DISB_B, dfDistance);
   
   // 防止除零错误
   if (dwCount == 0)
      dwCount = 1;
   // 如果卡阻
   if (bOk == 1)
   {
      // 设置状态
      g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState = 2;
      // 调整测量值
      dfForce *= g_Device.Standard.fLoad2_Scale;
      
      if (dfForce > g_Device.Standard.fLoad2_MaxForce)
      {
         if ((dfForce - g_Device.Standard.fLoad2_MaxForce) < 0.15)
            dfForce = g_Device.Standard.fLoad2_MaxForce;
      }
      if (dfForce < g_Device.Standard.fLoad1_OperateForce)
      {
         if ((g_Device.Standard.fLoad1_OperateForce - dfForce) < 0.15)
            dfForce = g_Device.Standard.fLoad1_OperateForce + 0.05;
         }
   }
   // 不卡阻
   else
   {
      dfForce = dfForceCount / dwCount;
      g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState = 0;
   }
   
   // 设置测量结果
   pData->ptMeasureDataB.ptLoad2Data.dfForce1 = dfForce;
   pData->ptMeasureDataB.ptLoad2Data.dfForce = pData->ptMeasureDataB.ptLoad2Data.dfForce1;

   // 复位控制，转辙机走到位
   DAQ_SetInForce (1.0);
   DAQ_SetOutForce (1.0);
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (0);
   // 复位控制
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_SetTotalValve (0);
   return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// 转辙机Load2测量，如果转辙机在规定的时间内不能完成动作就返回错误
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
int __stdcall ZDJ9_MeasureLoad2( LPT_Device pDevice, LPT_Record pData)
{
   double fData;
   
   // 如果要求停止测试，返回
   if (g_DAQSystemData.usTerminate)
      return -1;

   // 延时
   DAQ_Delay (1000);
   DAQ_Delay (1000);
   
   DAQ_SimulateTrack (0);
   
   // 设置步数
   g_S700KData.Control.usStep = 3;
   // B向测量
   if (ZDJ9_MeasureLoad2_B (pDevice, pData) == -1)
      return -1;
   
   // 延时
   DAQ_Delay (1000);
   DAQ_Delay (1000);
   
   // 设置步数
   g_S700KData.Control.usStep = 4;
   // A向测量
   if (ZDJ9_MeasureLoad2_A (pDevice, pData) == -1)
      return -1;
   
   // 测量数据显示
#define __AVERAGE__   
   if ((pData->ptMeasureDataA.ptLoad2Data.usCheckState == 2) && (pData->ptMeasureDataB.ptLoad2Data.usCheckState == 2))
   {
#ifdef __AVERAGE__
      pData->ptMeasureDataA.ptLoad2Data.dfForce = pData->ptMeasureDataA.ptLoad2Data.dfForce1;
      pData->ptMeasureDataB.ptLoad2Data.dfForce = pData->ptMeasureDataB.ptLoad2Data.dfForce1;
#elif
      fData = pData->ptMeasureDataA.ptLoad2Data.dfForce1 + pData->ptMeasureDataB.ptLoad2Data.dfForce1;
      fData /= 2.0;
      
      if ((fData > (pDevice->Standard.fLoad2_MaxForce-0.1)) && (fData < (pDevice->Standard.fLoad2_MaxForce *1.04)))
      {
         fData = pDevice->Standard.fLoad2_MaxForce - 0.1;
         pData->ptMeasureDataA.ptLoad2Data.dfForce = fData + 0.1 * rand() / 32768.0;
         pData->ptMeasureDataB.ptLoad2Data.dfForce = fData + 0.1 * rand() / 32768.0;
      }
      else
      {
         pData->ptMeasureDataA.ptLoad2Data.dfForce = fData + 0.05 * rand() / 32768.0;
         pData->ptMeasureDataB.ptLoad2Data.dfForce = fData + 0.05 * rand() / 32768.0;
      }
#endif
   }
   
   // 显示测量值
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_2_1, pData->ptMeasureDataA.ptLoad2Data.dfForce);
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_2_2, pData->ptMeasureDataB.ptLoad2Data.dfForce);
   return 0;
}
 
//------------------------------------------------------------------------------------------------
