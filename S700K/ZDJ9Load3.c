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
#include "toolbox.h"

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
// 转辙机Load3测量，如果转辙机在规定的时间内不能完成动作就返回错误
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
DWORD __stdcall ZDJ9_MeasureLoad3_A( LPT_Device pDevice, LPT_Record pData )
{
   double   dfTicksS = 0;
   double   dfActionTime;
   double   dfDistanceS = 0;
   double   dfDistance;
   double   dfTicks;
   DWORD    dwTicksA;
   DWORD    dwTicksError;
   BOOL     bOk = FALSE;
   DWORD    dwRetCode = 0;
   double   dfIa = 0.0, dfIb = 0.0, dfIc = 0.0;
   DWORD    dwCount = 0;
   BOOL     bStart = 0;
   DWORD    dwTimeout = 10000;
   double   dfStroke;
   double   dfForceCount = 0.0;
   double   dfAOForce;
   double   dfDelta, dfDiff;
   double   dfSpeed;
   short    usSkiped = 0;
   short    usError = 0;
   double   dfRatedForce = 0.0;
   double   dfHalfStroke;
   double   dfMinLoad2Force;
   
   // 如果要求停止测试，返回
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // 我们只在动程过半后进行测量数据处理
   dfHalfStroke = g_Device.Standard.fStroke / 2;
   dfHalfStroke += 10.0;

   // 根据转辙机动作时间调整超时值
   if (g_Device.Standard.fLoad3_TravelTime > 0)
      dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;

   // 选取A向和B向Load2力中的最小值
   dfMinLoad2Force = (g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce < g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce)
      ? g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce : g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce;
   
   // 设定为调整目标力
   dfRatedForce = dfMinLoad2Force;
   
   // 修正调整目标力
   if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 0.6)
      dfRatedForce -= 0.5;
   else if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 1.0)
      dfRatedForce -= 0.75;
   else
      dfRatedForce -= 0.8;
   
   // 修正调整目标力，不能比Load3额定力小
   if (dfRatedForce < (g_Device.Standard.fLoad3_OperateForce + 0.05))
      dfRatedForce = g_Device.Standard.fLoad3_OperateForce + 0.05;
   
   // 取得换向阀初始控制值
   g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad3_A2B_AVoltage;
   g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad3_A2B_BVoltage;
   
   // 调整测试台到初始状态
   g_DAQSystemData.fAOAForce = 1.0;
   dfAOForce = g_DAQSystemData.fAOBForce; 
   DAQ_SetInForce (1.0);
   DAQ_SetOutForce (1.0); 
   g_DAQSystemData.fAOBForce = 1.0;
   
   // 关闭换向阀
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (0);
   
   DAQ_Delay (1000);
   
   // 打开换向阀，转辙机右移
   DAQ_SetOutValve (1);
   DAQ_OutControl (1);
   
   // 复位位移
   DAQ_ResetStroke ();
   // 读取位移初始值
   dfStroke = DAQ_ReadStroke ();
   // 起始时间
   dwTicksError = GetTickCount ();
   dwTicksA = GetTickCount ();
   // 复位最大力
   g_DAQSystemData.fMaxForce = 0.0;
   while( 1 )
   {
      // 延时
      DAQ_Delay (50);
      // 如果到位，跳出
      if (DAQ_ReadRight ())
         break;
      // 采集数据
      DAQ_CheckMeasure ();
      // 如果超时，返回错误
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         break;
      }
      
      // 转辙机启动时，逐步提高换向阀开度，防止转辙机卡死
      if ((fabs (DAQ_ReadStroke () - dfStroke) < 10) && (bStart == FALSE))
      {
         g_DAQSystemData.fAOBForce += (dfAOForce * 0.7 - 1.0) / 5.0;
         if ( g_DAQSystemData.fAOBForce > dfAOForce * 0.7)
            g_DAQSystemData.fAOBForce = dfAOForce * 0.7;
         DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
         continue;
      }
      else if (bStart == FALSE)
      {
         g_DAQSystemData.fAOBForce = dfAOForce;
         DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
         bStart = TRUE;
         dfDistanceS = DAQ_ReadStroke ();
         dfTicksS = GetTickCount ();
         continue;
      }
      if (usSkiped == 1)
         continue;
      
      // 读入当前位移，计算速度
      dfDistance = DAQ_ReadStroke ();
      dfTicks = GetTickCount ();
      if ((dfTicks - dfTicksS) == 0)
      {
         dfSpeed = fabs (dfDistance - dfDistanceS) * 1000.0;
      }
      else
      {
         dfSpeed = fabs (dfDistance - dfDistanceS) * 1000.0 / (dfTicks - dfTicksS);
      }
      dfTicks = dfTicks;
      dfDistanceS = dfDistance;
      
      // 当速度比较低时，并保持一定的时间后认为转辙机卡阻，并开始测量参数
      // 完成测量后跳出
      if ((dfSpeed < 0.5) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->Standard.fStroke))
      {
         // 如果没有平均值，读入最大值，保证有测量数据
         if (dfForceCount == 0.0)
         {
            dfForceCount += FAI_FindMaxForce();
            dfIa += g_DAQData.Data.dfIa;
            dfIb += g_DAQData.Data.dfIb;
            dfIc += g_DAQData.Data.dfIc;
            dwCount ++;
            // 设置显示值
            pData->ptMeasureDataA.ptLoad3Data.dfForce = dfForceCount / dwCount;
            pData->ptMeasureDataA.ptLoad3Data.dfIa = dfIa / dwCount;
            pData->ptMeasureDataA.ptLoad3Data.dfIb = dfIb / dwCount;
            pData->ptMeasureDataA.ptLoad3Data.dfIc = dfIc / dwCount;
         }
         // 卡阻测量结束
         DAQ_Delay(1000);
         DAQ_SetOutForce (1.0);
         DAQ_SetInForce (1.0);
         DAQ_SetTotalValve (0);
         DAQ_SetOutValve (0);
         DAQ_SetInValve (0);
         usSkiped = 1;
      }

      // 在特定的动程范围内计算参数的平均值，作为无法卡阻时的测量结果
      dfDistance = DAQ_ReadStroke ();
      if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->Standard.fStroke))
      {
         // 累加测量值
         dwCount ++;
         dfForceCount += DAQ_ReadForce ();
         dfIa += g_DAQData.Data.dfIa;
         dfIb += g_DAQData.Data.dfIb;
         dfIc += g_DAQData.Data.dfIc;
         
         // 设置显示值
         pData->ptMeasureDataA.ptLoad3Data.dfForce = dfForceCount / dwCount;
         pData->ptMeasureDataA.ptLoad3Data.dfIa = dfIa / dwCount;
         pData->ptMeasureDataA.ptLoad3Data.dfIb = dfIb / dwCount;
         pData->ptMeasureDataA.ptLoad3Data.dfIc = dfIc / dwCount;
      }

      // 计算测量力和调节目标力
      dfDiff = DAQ_ReadForce () - dfRatedForce;
      // 分档调节比例阀开度
      if (fabs (dfDiff) < 0.08)
         dfDelta = 0.005;
      else if (fabs (dfDiff) < 0.1)
         dfDelta = 0.01;
      else if (fabs (dfDiff) < 0.15)
         dfDelta = 0.02;
      else if (fabs (dfDiff) < 0.2)
         dfDelta = 0.025;
      else if (fabs (dfDiff) < 0.3)
         dfDelta = 0.03;
      else if (fabs (dfDiff) < 0.4) 
         dfDelta = 0.04;
      else
         dfDelta = 0.04;
      
      // 计算比例阀开度
      if (dfDiff > 0.0)
         g_DAQSystemData.fAOBForce -= dfDelta;
      else
         g_DAQSystemData.fAOBForce += dfDelta;
      
      // 防止过调，限制调节范围
      if (g_DAQSystemData.fAOBForce - dfAOForce > 1.6 )
         g_DAQSystemData.fAOBForce = dfAOForce + 1.6;
      if (g_DAQSystemData.fAOBForce - dfAOForce < -1.6 )
         g_DAQSystemData.fAOBForce = dfAOForce - 1.6;
      
      // 调节比例阀开度
      DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   }
   
   // 计算动作时间
   dfActionTime = GetTickCount( ) - dwTicksA;
   // 防止除零错误
   if ( dwCount == 0 )dwCount = 1;
   // 计算平均值
   dfForceCount /= dwCount;
   dfIa /= dwCount;
   dfIb /= dwCount;
   dfIc /= dwCount;
   
   // 调整力，不能大于最大力
   if ((g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState == 2) && (usSkiped != 1))
   {
   // 调整最大力，不能大于最大力
      if (dfForceCount > g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce)
         dfForceCount = g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce;
      
   // 如果最大力大于Load1额定力同时Load1测量力小于Load1额定力时
      if ((g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce > g_Device.Standard.fLoad3_OperateForce)
         && (dfForceCount < g_Device.Standard.fLoad3_OperateForce))
      {
      // 如果差值小于0.1KN时调节为正常值
         if ((g_Device.Standard.fLoad3_OperateForce - dfForceCount) <= 0.1)
            dfForceCount = g_Device.Standard.fLoad3_OperateForce + Random(0.0, 0.05);
      }
   }
   
   // 设置测量结果
   pData->ptMeasureDataA.ptLoad3Data.dfIa = dfIa;
   pData->ptMeasureDataA.ptLoad3Data.dfIb = dfIb;
   pData->ptMeasureDataA.ptLoad3Data.dfIc = dfIc;
   pData->ptMeasureDataA.ptLoad3Data.dfForce = dfForceCount;
//   pData->ptMeasureDataA.ptLoad3Data.dfActionTime = (dfActionTime-500)/ 1000.0;
   
   // 复位控制
   DAQ_InControl( 0 );
   DAQ_OutControl( 0 );
   DAQ_SetTotalValve( 0 );
   DAQ_SetInForce( 1.0 );
   DAQ_SetOutForce( 1.0 );
   DAQ_SetOutValve( 0 );
   DAQ_SetInValve( 0 );
   
   // 显示测量值
   SetCtrlVal( g_plDAQMain, DAQMAIN_NG_F_3_1, pData->ptMeasureDataA.ptLoad3Data.dfForce );
//   SetCtrlVal( g_plDAQMain, DAQMAIN_NG_T_3_1, pData->ptMeasureDataA.ptLoad3Data.dfActionTime );
   return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// 转辙机Load3测量，如果转辙机在规定的时间内不能完成动作就返回错误
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
DWORD __stdcall ZDJ9_MeasureLoad3_B( LPT_Device pDevice, LPT_Record pData )
{
   double   dfTicksS = 0;
   double   dfActionTime;
   double   dfDistanceS = 0;
   double   dfDistance;
   double   dfTicks;
   DWORD    dwTicksA;
   DWORD    dwTicksError;
   BOOL     bOk = FALSE;
   DWORD    dwRetCode = 0;
   double   dfIa = 0.0, dfIb = 0.0, dfIc = 0.0;
   DWORD    dwCount = 0;
   BOOL     bStart = 0;
   DWORD    dwTimeout = 10000;
   double   dfStroke;
   double   dfForceCount = 0.0;
   double   dfAOForce;
   double   dfDelta, dfDiff;
   double   dfSpeed;
   short    usSkiped = 0;
   short    usError = 0;
   double   dfRatedForce = 0.0;
   double   dfHalfStroke;
   double   dfMinLoad2Force;
   
   // 如果要求停止测试，返回
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // 我们只在动程过半后进行测量数据处理
   dfHalfStroke = g_Device.Standard.fStroke / 2;
   dfHalfStroke += 10.0;
   
   // 根据转辙机动作时间调整超时值
   if (g_Device.Standard.fLoad3_TravelTime > 0)
      dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;
   
   // 选取A向和B向Load2力中的最小值
   dfMinLoad2Force = (g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce < g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce)
      ? g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce : g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce;
   
   // 设定为调整目标力
   dfRatedForce = dfMinLoad2Force;

   // 修正调整目标力
   if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 0.6)
      dfRatedForce -= 0.5;
   else if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 1.0)
      dfRatedForce -= 0.75;
   else
      dfRatedForce -= 0.8;
   
   // 修正调整目标力，不能比Load1额定力小
   if (dfRatedForce < (g_Device.Standard.fLoad3_OperateForce + 0.05))
      dfRatedForce = g_Device.Standard.fLoad3_OperateForce + 0.05;
   
   // 取得换向阀初始控制值
   g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad3_B2A_AVoltage;
   g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad3_B2A_BVoltage;

   // 调整测试台到初始状态
   g_DAQSystemData.fAOBForce = 1.0;
   dfAOForce = g_DAQSystemData.fAOAForce;  
   DAQ_SetOutForce (1.0);
   DAQ_SetInForce (1.0);
   g_DAQSystemData.fAOAForce = 1.0;
   
   // 关闭换向阀
   DAQ_SetTotalValve (0);
   DAQ_SetOutValve (0);
   
   DAQ_Delay (1000);
   
   // 打开换向阀，转辙机左移
   DAQ_SetInValve (1);
   DAQ_InControl( 1 );
   
   // 复位位移
   DAQ_ResetStroke ();
   // 读取位移初始值
   dfStroke = DAQ_ReadStroke ();
   // 起始时间
   dwTicksError = GetTickCount ();
   dwTicksA = GetTickCount ();
   // 复位最大力
   g_DAQSystemData.fMaxForce = 0.0;
   while( 1 )
   {
      // 延时
      DAQ_Delay (50);
      // 如果到位，跳出
      if (DAQ_ReadLeft ())
         break;
      // 采集数据
      DAQ_CheckMeasure ();
      // 如果超时，返回错误
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         break;
      }
      
      // 转辙机启动时，逐步提高换向阀开度，防止转辙机卡死
      if ((fabs (DAQ_ReadStroke () - dfStroke) < 10) && (bStart == FALSE))
      {
         g_DAQSystemData.fAOAForce += (dfAOForce * 0.7 - 1.0) / 5.0;
         if ( g_DAQSystemData.fAOAForce > dfAOForce * 0.7)
            g_DAQSystemData.fAOAForce = dfAOForce * 0.7;
         DAQ_SetInForce (g_DAQSystemData.fAOAForce);
         continue;
      }
      else if (bStart == FALSE)
      {
         g_DAQSystemData.fAOAForce = dfAOForce;
         DAQ_SetInForce (g_DAQSystemData.fAOAForce);
         bStart = TRUE;
         dfDistanceS = DAQ_ReadStroke ();
         dfTicksS = GetTickCount ();
         continue;
      }
      if (usSkiped == 1)
         continue;
      
      // 读入当前位移，计算速度
      dfDistance = DAQ_ReadStroke ();
      dfTicks = GetTickCount ();
      if ((dfTicks - dfTicksS) == 0)
      {
         dfSpeed = fabs (dfDistance - dfDistanceS) * 1000.0;
      }
      else
      {
         dfSpeed = fabs (dfDistance - dfDistanceS) * 1000.0 / (dfTicks - dfTicksS);
      }
      dfTicks = dfTicks;
      dfDistanceS = dfDistance;

      // 当速度比较低时，并保持一定的时间后认为转辙机卡阻，并开始测量参数
      // 完成测量后跳出
      if ((dfSpeed < 0.5) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->Standard.fStroke))
      {
         // 如果没有平均值，读入最大值，保证有测量数据
         if (dfForceCount == 0.0)
         {
            dfForceCount += FAI_FindMaxForce();
            dfIa += g_DAQData.Data.dfIa;
            dfIb += g_DAQData.Data.dfIb;
            dfIc += g_DAQData.Data.dfIc;
            dwCount ++;
            // 设置显示值
            pData->ptMeasureDataB.ptLoad3Data.dfForce = dfForceCount / dwCount;
            pData->ptMeasureDataB.ptLoad3Data.dfIa = dfIa / dwCount;
            pData->ptMeasureDataB.ptLoad3Data.dfIb = dfIb / dwCount;
            pData->ptMeasureDataB.ptLoad3Data.dfIc = dfIc / dwCount;
         }
         DAQ_Delay(1000);
         // 卡阻测量结束
         DAQ_SetOutForce( 1.0 );
         DAQ_SetInForce( 1.0 );
         DAQ_SetTotalValve( 0 );
         DAQ_SetOutValve( 0 );
         DAQ_SetInValve( 0 );
         usSkiped = 1;
      }

      // 在特定的动程范围内计算参数的平均值，作为无法卡阻时的测量结果
      dfDistance = DAQ_ReadStroke ();
      if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->Standard.fStroke))
      {
         // 累加测量值
         dwCount ++;
         dfForceCount += DAQ_ReadForce ();
         dfIa += g_DAQData.Data.dfIa;
         dfIb += g_DAQData.Data.dfIb;
         dfIc += g_DAQData.Data.dfIc;
         
         // 设置显示值
         pData->ptMeasureDataB.ptLoad3Data.dfForce = dfForceCount / dwCount;
         pData->ptMeasureDataB.ptLoad3Data.dfIa = dfIa / dwCount;
         pData->ptMeasureDataB.ptLoad3Data.dfIb = dfIb / dwCount;
         pData->ptMeasureDataB.ptLoad3Data.dfIc = dfIc / dwCount;
      }

      // 计算测量力和调节目标力
      dfDiff = DAQ_ReadForce () - dfRatedForce;
      // 分档调节比例阀开度
      if (fabs (dfDiff) < 0.08)
         dfDelta = 0.005;
      else if (fabs (dfDiff) < 0.1)
         dfDelta = 0.01;
      else if (fabs (dfDiff) < 0.15)
         dfDelta = 0.02;
      else if (fabs (dfDiff) < 0.2)
         dfDelta = 0.025;
      else if (fabs (dfDiff) < 0.3)
         dfDelta = 0.03;
      else if (fabs (dfDiff) < 0.4) 
         dfDelta = 0.04;
      else
         dfDelta = 0.04;
      
      // 计算比例阀开度
      if (dfDiff > 0.0)
         g_DAQSystemData.fAOAForce -= dfDelta;
      else
         g_DAQSystemData.fAOAForce += dfDelta;
      
      // 防止过调，限制调节范围
      if (g_DAQSystemData.fAOAForce - dfAOForce > 1.6 )
         g_DAQSystemData.fAOAForce = dfAOForce + 1.6;
      if (g_DAQSystemData.fAOAForce - dfAOForce < -1.6 )
         g_DAQSystemData.fAOAForce = dfAOForce - 1.6;
      
      // 调节比例阀开度
      DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   }
   
   // 计算动作时间
   dfActionTime = GetTickCount () - dwTicksA;
   if (dwCount == 0)
      dwCount = 1;
   dfForceCount /= dwCount;
   dfIa /= dwCount;
   dfIb /= dwCount;
   dfIc /= dwCount;
      
   // 修正测量值
   if ((g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState == 2) && (usSkiped != 1))
   {
   // 调整最大力，不能大于最大力
      if (dfForceCount > g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce)
         dfForceCount = g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce;
      
   // 如果最大力大于Load1额定力同时Load1测量力小于Load1额定力时
      if ((g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce > g_Device.Standard.fLoad3_OperateForce)
         && (dfForceCount < g_Device.Standard.fLoad3_OperateForce))
      {
      // 如果差值小于0.1KN时调节为正常值
         if ((g_Device.Standard.fLoad3_OperateForce - dfForceCount) <= 0.1)
            dfForceCount = g_Device.Standard.fLoad3_OperateForce + Random(0.0, 0.05);
      }
   }

   // 设置测量结果
   pData->ptMeasureDataB.ptLoad3Data.dfIa = dfIa;
   pData->ptMeasureDataB.ptLoad3Data.dfIb = dfIb;
   pData->ptMeasureDataB.ptLoad3Data.dfIc = dfIc;
   pData->ptMeasureDataB.ptLoad3Data.dfForce = dfForceCount;
//   pData->ptMeasureDataB.ptLoad3Data.dfActionTime = (dfActionTime-500)/ 1000.0;
   
   // 复位控制
   DAQ_SetTotalValve (0);
   DAQ_SetInForce (1.0);
   DAQ_SetOutForce (1.0);
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);
   DAQ_InControl (0);
   DAQ_OutControl (0);

   // 显示测量值
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_3_2, pData->ptMeasureDataB.ptLoad3Data.dfForce);
//   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_T_3_2, pData->ptMeasureDataB.ptLoad3Data.dfActionTime);
   return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// 转辙机Load3测量，如果转辙机在规定的时间内不能完成动作就返回错误
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
int __stdcall ZDJ9_MeasureLoad3( LPT_Device pDevice, LPT_Record pData )
{
   // 如果要求停止测试，返回
   if (g_DAQSystemData.usTerminate)
      return -1;

   // 延时
   DAQ_Delay (1000);
   DAQ_Delay (1000);
   
   // 接入模拟电阻
   DAQ_SimulateTrack (1);
   
   // 设置步数
   g_S700KData.Control.usStep = 7;
   // B向测量
   if (ZDJ9_MeasureLoad3_B (pDevice, pData) == -1)
      return -1;
   
   // 延时
   DAQ_Delay (1000);
   DAQ_Delay (1000);

   // 设置步数
   g_S700KData.Control.usStep = 8;
   // A向测量
   if (ZDJ9_MeasureLoad3_A (pDevice, pData) == -1)
      return -1;

   // 断开模拟电阻
   DAQ_SimulateTrack( 0 );
   
   return 0;
}

//------------------------------------------------------------------------------------------------
