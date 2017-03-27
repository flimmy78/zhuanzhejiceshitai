// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************
#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>
#include "S700K.h"
//#include "..\include\USB2833.h"
//#include "DAUSB2833.h"

//------------------------------------------------------------------------------------------------
// 打开研华数据采集卡PCI1711
// 输入:
//    pDev        设备指针
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall USB2833_Open(LPT_DAQCard pDev)
{
   LRESULT     ErrCde;         // Return error code
   
   // 如果设备已经被打开，返回
   if ( pDev->hDevice != 0 )
      return TRUE;
   
   // 调用驱动程序，打开设备
   pDev->hDevice = (LONG)USB2833_CreateDevice (0);
   
   // 如果不成功返回错误
   if ( pDev->hDevice == 0 )
   {
      MessagePopup ("错误", "不能连接到USB2833!");
      return FALSE;
   }
   
   // 正确返回
   return TRUE;
   
}

//------------------------------------------------------------------------------------------------
// 关闭研华数据采集卡PCI1711  
// 输入:
//    pDev        设备指针
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall USB2833_Close( LPT_DAQCard pDev )
{
   LRESULT     ErrCde;         // Return error code
   
   // 如果设备已经被关闭，返回
   if ( pDev->hDevice == NULL )
      return TRUE;
   
   // 调用驱动程序，关闭设备
   USB2833_ReleaseDevice ((HANDLE)pDev->hDevice); // 释放设备对象
   
   // 复位数据指针
   pDev->hDevice = (LONG)NULL;
   
   // 正确返回
   return TRUE;
}

//------------------------------------------------------------------------------------------------
// 研华数据采集卡PCI1711的模拟量输出
// 输入:
//    pDev        设备指针
//    ushChannel  通道编号
//    fVoltage    输出电压值
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall USB2833_AOValue( LPT_DAQCard pDev, USHORT ushChannel, float fVoltage )
{
   BOOL     ErrCde;         // Return error code
   USHORT     usRaw;
   
   // 如果设备没有打开，返回
   if ( pDev->hDevice == NULL )
   {
      return FALSE;
   }
   
   usRaw = (WORD)(fVoltage/(10000.00/4096));
   
   ErrCde = USB2833_WriteDeviceDA((HANDLE)pDev->hDevice, USB2833_OUTPUT_0_P10000mV, usRaw, ushChannel);
   if (!ErrCde)
   {
      return FALSE;
   }
   
   // 正确返回
   return TRUE;
}

//------------------------------------------------------------------------------------------------
