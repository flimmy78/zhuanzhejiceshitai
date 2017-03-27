// #########################################################################
// *************************************************************************
// 检查转辙机和测量动程
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
int __stdcall ZDJ9_DeviceCheck( LPT_Device pDevice, LPT_Record pData )
{
   double   dfDistance, dfDistanceS, dfDistanceE;
   
   DWORD    dwTicksError;
   double   dfDiff;
   
   // 设置超时为10秒
   DWORD    dwTimeout = 10000;
  
   // 如果要求停止测试，返回
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // 根据转辙机动作时间调整超时值
   if (g_Device.Standard.fLoad1_TravelTime > 0)
      dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 2000;
   
   // 设置转辙机动作步数
   g_S700KData.Control.usStep = 0;
   
   // 转辙机退回A / Left 位
   DAQ_SimulateTrack(0);
   DAQ_OutControl(0);
   DAQ_InControl(1);
   DAQ_SetOutForce( 0.0 );
   DAQ_SetInForce( 0.0 );
   DAQ_SetTotalValve( 1 );
   
   // 设置起始时间
   dwTicksError = GetTickCount( );
   while( 1 )
   {
      // 如果到位，跳出
      if ( DAQ_ReadLeft())
         break;
      // 数据采集
      DAQ_CheckMeasure();
      
      // 如果超时，设置状态，返回错误
      if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      Sleep( 10 );
   }
   // 断开输出
   DAQ_InControl(0);

   // 延时2秒
   DAQ_Delay(2000);
   
   // 转辙机向右运动
   DAQ_OutControl(1);
   // 设置起始时间
   dwTicksError = GetTickCount( );
   while( 1 )
   {
      // 如果到位，跳出
      if ( DAQ_ReadRight( ) )
         break;
      // 数据采集
      DAQ_CheckMeasure( );
      
      // 如果超时，设置状态，返回错误
      if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      
      Sleep( 10 );
   }
   // 断开输出
   DAQ_OutControl( 0 );

   // 延时2秒
   DAQ_Delay( 2000 );

   // 设置转辙机动作步数
   g_S700KData.Control.usStep = 1;
   
   // 复位位移测量计数器，设置原点
   DAQ_ResetStroke();
   // 读入位移起始值
   dfDistanceS = DAQ_ReadStroke ();
   // 转辙机左移
   DAQ_InControl( 1 );
   // 设置起始时间
   dwTicksError = GetTickCount();
   while( 1 )
   {
      // 如果到位，跳出
      if (DAQ_ReadLeft())
         break;
      // 数据采集
      DAQ_CheckMeasure();
      
      // 如果超时，设置状态，返回错误
      if (DAQ_CheckError(GetTickCount() - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      
      Sleep(10);
   }
   // 读入位移终止值
   dfDistanceE = DAQ_ReadStroke ();
   // 计算动程
   dfDistance = fabs( dfDistanceE - dfDistanceS );
   
   // 修正测量值
   dfDiff = pDevice->Standard.fStroke - dfDistance;
   if ((dfDiff > 0.0) && (dfDiff <= 1.0))
      dfDistance += 1.0;
   else if ((dfDiff > 1.0) && (dfDiff <= 2.0))
      dfDistance += 2.0;
   
   // 保存测量值，并显示
   pData->ptMeasureDataB.ptCheckData.dfInterval = dfDistance;
   pData->ptMeasureDataB.ptCheckData.bCheckState = TRUE;
   SetCtrlVal( g_plDAQMain, DAQMAIN_NG_DISB_B, dfDistance );

   DAQ_InControl( 0 );
   
   // 延时1秒
   DAQ_Delay( 1000 );
   
   // 设置转辙机动作步数
   g_S700KData.Control.usStep = 2;
   
   // 复位位移测量计数器，设置原点
   DAQ_ResetStroke ();
   // 读入位移起始值
   dfDistanceS = DAQ_ReadStroke ();
   // 转辙机右移
   DAQ_OutControl( 1 );
   // 设置起始时间
   dwTicksError = GetTickCount( );
   // 取空载电流
   while( 1 )
   {
      // 如果到位，跳出
      if ( DAQ_ReadRight( ) )
         break;
      // 数据采集
      DAQ_CheckMeasure( );
      
      // 如果超时，设置状态，返回错误
      if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      Sleep( 10 );
   }
   // 读入位移终止值
   dfDistanceE = DAQ_ReadStroke( );
   // 计算动程
   dfDistance = fabs( dfDistanceE - dfDistanceS );

   // 修正测量值
   dfDiff = pDevice->Standard.fStroke - dfDistance;
   if ((dfDiff > 0.0) && (dfDiff <= 1.0))
      dfDistance += 1.0;
   else if ((dfDiff > 1.0) && (dfDiff <= 2.0))
      dfDistance += 2.0;
   
   // 保存测量值，并显示
   pData->ptMeasureDataA.ptCheckData.dfInterval = dfDistance;
   pData->ptMeasureDataA.ptCheckData.bCheckState = TRUE;
   SetCtrlVal(g_plDAQMain, DAQMAIN_NG_DISB_A, dfDistance);

   DAQ_OutControl(0);
   DAQ_SetTotalValve(0);
   
   return 0;
}

//------------------------------------------------------------------------------------------------
