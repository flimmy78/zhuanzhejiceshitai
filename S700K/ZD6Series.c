// #########################################################################
// *************************************************************************
//           Copyright (C) 2002-2004, Xi'an KeXing M&C Ltd. Corp.
//   THIS IS AN UNPUBLISHED WORK CONTAINED CONFIDENTIAL, AND PROPRIETARY
//     INFORMATION WHICH IS THE PROPERTY OF Xi'an KeXing M&C Ltd. Corp.
// ANY DISCLOSURE, USE, OR REPRODUCTION, WITHOUT WRITTERN AUTHORIZATION FROM
//            Xi'an KeXing M&C Ltd. Corp., IS STRICT
// #########################################################################
// *************************************************************************

//------------------------------------------------------------------------------------------------
#include "global.h"
#include <cvirte.h>     
#include <userint.h>
#include "S700K.h"
#include "inifile.h"
#include "Device.h"
#include "DAQDefine.h"
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
//extern int              g_plDCTable;
extern int              g_plDAQMain;
//extern PT_Device        g_Device;
//extern PT_Record        g_S700KData;
extern PT_Record        g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_DAQSystemData g_DAQSystemData;
extern PT_Device        g_Device;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// 检查转辙机和测量动程，如果转辙机在规定的时间内不能完成动作就返回错误
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
int __stdcall ZD6S_DeviceCheck(LPT_Device pDevice, LPT_Record pData)
{
   double   dfStroke, dfStrokeS, dfStrokeE;
   
   DWORD    dwTicksError;
   double   dfDiff;
   
   // 设置超时为10秒
   DWORD    dwTimeout = 10000;
  
   // 如果要求停止测试，返回
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // 根据转辙机动作时间调整超时值
   //if (g_Device.Database.fLoad1_TravelTime > 0)
   //   dwTimeout = g_Device.Database.fLoad3_TravelTime * 1000 + 2000;
   
   // 设置转辙机动作步数
//   g_S700KData.Control.usStep = 0;
   
   // 转辙机退回A / Left 位
   DAQ_SimulateTrack (0);
   //DAQ_DCRightControl (0);
   //DAQ_DCLeftControl (1);
   DAQ_SetOutForce (0.0);
   DAQ_SetInForce (0.0);
   DAQ_SetTotalValve (0);
   
   // 设置起始时间
   dwTicksError = GetTickCount ();
   while (1)
   {
      // 如果到位，跳出
      if (DAQ_DCReadLeft ())
         break;
      // 数据采集
      DAQ_CheckMeasure ();
      
      // 如果超时，设置状态，返回错误
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         goto Error;
      }
      Sleep( 10 );
   }
   // 断开输出
   //DAQ_DCLeftControl(0);

   // 延时2秒
   DAQ_Delay(2000);
   
   // 转辙机向右运动
   //DAQ_DCRightControl(1);
   // 设置起始时间
   dwTicksError = GetTickCount( );
   while( 1 )
   {
      // 如果到位，跳出
      if (DAQ_DCReadRight( ) )
         break;
      // 数据采集
      DAQ_CheckMeasure( );
      
      // 如果超时，设置状态，返回错误
      if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
         goto Error;
      }
      
      Sleep( 10 );
   }
   // 断开输出
   //DAQ_DCRightControl( 0 );

   // 延时2秒
   DAQ_Delay( 2000 );

   // 设置转辙机动作步数
//   g_S700KData.Control.usStep = 1;
   
   // 复位位移测量计数器，设置原点
   DAQ_ResetStroke();
   // 读入位移起始值
   dfStrokeS = DAQ_ReadStroke ();
   // 转辙机左移
   //DAQ_DCLeftControl( 1 );
   // 设置起始时间
   dwTicksError = GetTickCount();
   while( 1 )
   {
      // 如果到位，跳出
      if (DAQ_DCReadLeft())
         break;
      // 数据采集
      DAQ_CheckMeasure();
      
      // 如果超时，设置状态，返回错误
      if (DAQ_CheckError(GetTickCount() - dwTicksError, dwTimeout))
      {
         goto Error;
      }
      
      Sleep(10);
   }
   // 读入位移终止值
   dfStrokeE = DAQ_ReadStroke ();
   // 计算动程
   dfStroke = fabs (dfStrokeE - dfStrokeS);
   
   // 修正测量值
   dfDiff = pDevice->ssRatedStroke.fData1 - dfStroke;
   if ((dfDiff > 0.0) && (dfDiff <= 1.0))
      dfStroke += 1.0;
   else if ((dfDiff > 1.0) && (dfDiff <= 2.0))
      dfStroke += 2.0;
   
   // 保存测量值，并显示
   pData->ptMeasureDataF.dfStroke = dfStroke;
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_DISB_B, dfStroke);

   //DAQ_DCLeftControl( 0 );
   
   // 延时1秒
   DAQ_Delay( 1000 );
   
   // 设置转辙机动作步数
//   g_S700KData.Control.usStep = 2;
   
   // 复位位移测量计数器，设置原点
   DAQ_ResetStroke ();
   // 读入位移起始值
   dfStrokeS = DAQ_ReadStroke ();
   // 转辙机右移
   //DAQ_DCRightControl( 1 );
   // 设置起始时间
   dwTicksError = GetTickCount( );
   // 取空载电流
   while( 1 )
   {
      // 如果到位，跳出
      if ( DAQ_DCReadRight( ) )
         break;
      // 数据采集
      DAQ_CheckMeasure( );
      
      // 如果超时，设置状态，返回错误
      if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
         goto Error;
      }
      Sleep( 10 );
   }
   // 读入位移终止值
   dfStrokeE = DAQ_ReadStroke( );
   // 计算动程
   dfStroke = fabs( dfStrokeE - dfStrokeS );

   // 修正测量值
   dfDiff = pDevice->ssRatedStroke.fData1 - dfStroke;
   if ((dfDiff > 0.0) && (dfDiff <= 1.0))
      dfStroke += 1.0;
   else if ((dfDiff > 1.0) && (dfDiff <= 2.0))
      dfStroke += 2.0;
   
   // 保存测量值，并显示
   pData->ptMeasureDataD.dfStroke = dfStroke;
   SetCtrlVal(g_plDAQMain, DAQMAIN_NG_DISB_A, dfStroke);

   //DAQ_DCRightControl(0);
   DAQ_SetTotalValve(0);
   
   return 0;
Error:
   // 复位输出
  // DAQ_SetDCVoltage (0);
   //DAQ_DCLineControl (0);
   //DAQ_DCLeftControl (0);                
   //DAQ_DCRightControl (0);
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
   
   return -1;
   
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
DWORD __stdcall ZD6S_Measure_A( LPT_Device pDevice, LPT_Record pData )
{
   double   dfTicksS;
   double   dfActionTime;
   double   dfDistanceS;
   double   dfDistance;
   double   dfTicks;
   DWORD    dwTicksA;
   DWORD    dwTicksError;
   BOOL     bOk = FALSE;
   DWORD    dwRetCode = 0;
   double   dfIdc = 0.0, dfUdc = 0.0;
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
//   double   dfRatedForce = 0.0;
   double   dfHalfStroke;
//   double   dfMinLoad2Force;
   
   // 如果要求停止测试，返回
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // 我们只在动程过半后进行测量数据处理
   dfHalfStroke = g_Device.ssRatedStroke.fData1 / 2;
   dfHalfStroke += 10.0;

   // 根据转辙机动作时间调整超时值
//   if (g_Device.Database.fLoad3_TravelTime > 0)
//      dwTimeout = g_Device.Database.fLoad3_TravelTime * 1000 + 1000;

   // 调整测试台到初始状态
   DAQ_SetInForce (pDevice->ssAValveVoltage1.fData1);
   DAQ_SetOutForce (pDevice->ssBValveVoltage1.fData1); 
   
   // 关闭换向阀
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (0);
   
   DAQ_Delay (1000);
   
   // 打开换向阀，转辙机右移
   DAQ_SetOutValve (1);
   //DAQ_DCRightControl (1);
   
   // 复位位移
   DAQ_ResetStroke ();
   // 读取位移初始值
   dfStroke = DAQ_ReadStroke ();
   // 起始时间
   dwTicksError = GetTickCount ();
   dwTicksA = GetTickCount ();
   dfDistanceS = DAQ_ReadStroke ();
   dfTicksS = GetTickCount ();
   while( 1 )
   {
      // 延时
      DAQ_Delay (50);
      // 如果到位，跳出
      if (DAQ_DCReadRight ())
         break;
      // 采集数据
      DAQ_CheckMeasure ();
      // 如果超时，返回错误
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         if (usError == 1)
         {
         }
         else
         {
            usError = 1;
            dwTicksError = GetTickCount ();
            goto Error;
         }
      }
      
      // 在特定的动程范围内计算参数的平均值，作为无法卡阻时的测量结果
      dfDistance = DAQ_ReadStroke ();
      if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->ssRatedStroke.fData1))
      {
         // 累加测量值
         dwCount ++;
         dfForceCount += DAQ_ReadForce ();
         dfUdc += g_DAQData.Data.dfUdc;
         dfIdc += g_DAQData.Data.dfIdc;
         
         // 设置显示值
         pData->ptMeasureDataD.dfForce = dfForceCount / dwCount;
         pData->ptMeasureDataD.dfU = dfUdc / dwCount;
         pData->ptMeasureDataD.dfI = dfIdc / dwCount;
      }
   }
   
   // 计算动作时间
   dfActionTime = GetTickCount( ) - dwTicksA;
   // 防止除零错误
   if ( dwCount == 0 )
      dwCount = 1;
   // 计算平均值
   dfForceCount /= dwCount;
   dfUdc /= dwCount;
   dfIdc /= dwCount;
   
   // 设置测量结果
   pData->ptMeasureDataD.dfU = dfUdc;
   pData->ptMeasureDataD.dfI = dfIdc;
   pData->ptMeasureDataD.dfForce = dfForceCount;
   pData->ptMeasureDataD.dfActionTime = (dfActionTime - 500) / 1000.0;
   
   DAQ_Delay (2000);
   // 摩擦
   dfIdc = 0.0;
   dwCount = 0;
   // 起始时间
   dwTicksError = GetTickCount ();
   
   while ((GetTickCount () - dwTicksError) < 5000)
   {
      DAQ_Delay (200);
      dfIdc += g_DAQData.Data.dfIdc;
      dwCount ++;
   }
   dfIdc /= dwCount;
   
   // 设置测量结果
   pData->ptMeasureDataD.dfI_F = dfIdc;
  
   // 复位控制
   //DAQ_DCLeftControl( 0 );
   //DAQ_DCRightControl( 0 );
   DAQ_SetTotalValve( 0 );
   DAQ_SetInForce( 1.0 );
   DAQ_SetOutForce( 1.0 );
   DAQ_SetOutValve( 0 );
   DAQ_SetInValve( 0 );
   
   // 显示测量值
   SetCtrlVal( g_plDAQMain, DAQMAIN_NG_F_3_1, pData->ptMeasureDataD.dfForce );
   SetCtrlVal( g_plDAQMain, DAQMAIN_NG_T_3_1, pData->ptMeasureDataD.dfActionTime );
   return dwRetCode;
Error:
   // 复位输出
  // DAQ_SetDCVoltage (0);
  // DAQ_DCLineControl (0);
   //DAQ_DCLeftControl (0);                
   //DAQ_DCRightControl (0);
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
   
   return -1;
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
DWORD __stdcall ZD6S_Measure_B(LPT_Device pDevice, LPT_Record pData)
{
   double   dfTicksS;
   double   dfActionTime;
   double   dfDistanceS;
   double   dfDistance;
   double   dfTicks;
   DWORD    dwTicksA;
   DWORD    dwTicksError;
   BOOL     bOk = FALSE;
   DWORD    dwRetCode = 0;
   double   dfIdc = 0.0;
   double   dfUdc = 0.0;
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
//   double   dfRatedForce = 0.0;
   double   dfHalfStroke;
   double   dfMinLoad2Force;
   
   // 如果要求停止测试，返回
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // 我们只在动程过半后进行测量数据处理
   dfHalfStroke = g_Device.ssRatedStroke.fData1 / 2;
   dfHalfStroke += 10.0;
   
   // 根据转辙机动作时间调整超时值
//   if (g_Device.Database.fLoad3_TravelTime > 0)
//      dwTimeout = g_Device.Database.fLoad3_TravelTime * 1000 + 1000;
   
   // 调整测试台到初始状态
   DAQ_SetInForce (pDevice->ssAValveVoltage2.fData1);
   DAQ_SetOutForce (pDevice->ssBValveVoltage2.fData1); 
   
   // 关闭换向阀
   DAQ_SetTotalValve (0);
   DAQ_SetOutValve (0);
   
   DAQ_Delay (1000);
   
   // 打开换向阀，转辙机左移
   DAQ_SetInValve (1);
   //DAQ_DCLeftControl (1);
   
   // 复位位移
   DAQ_ResetStroke ();
   // 读取位移初始值
   dfStroke = DAQ_ReadStroke ();
   // 起始时间
   dwTicksError = GetTickCount ();
   dwTicksA = GetTickCount ();
   dfDistanceS = DAQ_ReadStroke ();
   dfTicksS = GetTickCount ();
   while( 1 )
   {
      // 延时
      DAQ_Delay (50);
      // 如果到位，跳出
      if (DAQ_DCReadLeft ())
         break;
      // 采集数据
      DAQ_CheckMeasure ();
      // 如果超时，返回错误
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         if (usError == 1)
         {
            goto Error;
         }
         else
         {
            usError = 1;
            dwTicksError = GetTickCount ();
            goto Error;
         }
      }
      
      // 在特定的动程范围内计算参数的平均值，作为无法卡阻时的测量结果
      dfDistance = DAQ_ReadStroke ();
      if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->ssRatedStroke.fData1))
      {
         // 累加测量值
         dwCount ++;
         dfForceCount += DAQ_ReadForce ();
         dfUdc += g_DAQData.Data.dfUdc;
         dfIdc += g_DAQData.Data.dfIdc;
         
         // 设置显示值
         pData->ptMeasureDataF.dfForce = dfForceCount / dwCount;
         pData->ptMeasureDataF.dfU = dfUdc / dwCount;
         pData->ptMeasureDataF.dfI = dfIdc / dwCount;
      }
   }
   
   // 计算动作时间
   dfActionTime = GetTickCount () - dwTicksA;
   if (dwCount == 0)
      dwCount = 1;
   dfForceCount /= dwCount;
   dfUdc /= dwCount;
   dfIdc /= dwCount;

   // 设置测量结果
   pData->ptMeasureDataF.dfU = dfUdc;
   pData->ptMeasureDataF.dfI = dfIdc;
   pData->ptMeasureDataF.dfForce = dfForceCount;
   pData->ptMeasureDataF.dfActionTime = (dfActionTime-500)/ 1000.0;
   
   DAQ_Delay (2000);
   // 摩擦
   dfIdc = 0.0;
   dwCount = 0;
   // 起始时间
   dwTicksError = GetTickCount ();
   
   while ((GetTickCount () - dwTicksError) < 5000)
   {
      DAQ_Delay (200);
      dfIdc += g_DAQData.Data.dfIdc;
      dwCount ++;
   }
   dfIdc /= dwCount;
   
   // 设置测量结果
   pData->ptMeasureDataF.dfI_F = dfIdc;

   // 复位控制
   DAQ_SetTotalValve (0);
   DAQ_SetInForce (1.0);
   DAQ_SetOutForce (1.0);
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);
   //DAQ_DCLeftControl (0);
   //DAQ_DCRightControl (0);

   // 显示测量值
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_3_2, pData->ptMeasureDataF.dfForce);
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_T_3_2, pData->ptMeasureDataF.dfActionTime);
   return dwRetCode;
Error:
   // 复位输出
   //DAQ_SetDCVoltage (0);
   //DAQ_DCLineControl (0);
   //DAQ_DCLeftControl (0);                
   //DAQ_DCRightControl (0);
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
   
   return -1;
}

//------------------------------------------------------------------------------------------------
DWORD WINAPI ZD6S_ThreadRoutine_Normal (LPT_Device pDevice, LPT_Record pData)
{
   // 如果要求停止测试，返回
   if (g_DAQSystemData.usTerminate)
      return -1;

   // 延时
   DAQ_Delay (1000);
   DAQ_Delay (1000);
   
   // 设置步数
//   g_S700KData.Control.usStep = 207;
   // B向测量
   if (ZD6S_Measure_B (pDevice, pData) == -1)
      return -1;
   
   // 延时
   DAQ_Delay (1000);
   DAQ_Delay (1000);

   // 设置步数
//   g_S700KData.Control.usStep = 208;
   // A向测量
   if (ZD6S_Measure_A (pDevice, pData) == -1)
      return -1;
   
  // DAQ_SetDCVoltage (0);

   return 0;
}

//------------------------------------------------------------------------------------------------
int __stdcall ZD6S_ThreadRoutine( LPT_Device pDevice, LPT_Record pData )
{
   DAQ_ACSelect (0);
   //DAQ_DCSelect (1);
   
   //DAQ_DCLineControl (1);
   
   // DC Voltage, 160V
  // if (pDevice->ssDCVoltageSet.fData1 > 0)
 //     DAQ_SetDCVoltage (pDevice->ssDCVoltageSet.fData1);
 //  else
 //     DAQ_SetDCVoltage (3.02);
   
   if (ZD6S_DeviceCheck (pDevice, pData))
      goto Exit;
   if (g_DAQSystemData.usTerminate)
      goto Exit;

   DAQ_Delay (2000);
   DAQ_OilBumpControl (1);
   
   ZD6S_ThreadRoutine_Normal (pDevice, pData);
   if (g_DAQSystemData.usTerminate)
      goto Exit;
   
Exit:
//   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_Time, g_S700KData.Control.ulMeasTime);
   
   // 复位输出
  // DAQ_SetDCVoltage (0);
  // DAQ_DCLineControl (0);
   //DAQ_DCLeftControl (0);                
   //DAQ_DCRightControl (0);
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

