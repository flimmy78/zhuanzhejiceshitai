// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************
#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>
#include "S700K.h"
#include "..\include\driver.h"
#include "ADPCI1784.h"

//------------------------------------------------------------------------------------------------
// 打开研华数据采集卡PCI1784
// 输入:
//    pDev        设备指针
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADPCI1784_Open( LPT_DAQCard pDev )
{
   LRESULT     ErrCde;         // Return error code
   PT_QCounterConfig  ptQCounterConfig;
   PT_QCounterStart   ptQCounterStart;
   
   // 如果设备已经被打开，返回
   if ( pDev->hDevice != 0 )
      return TRUE;
   
   // 调用驱动程序，打开设备
   ErrCde = DRV_DeviceOpen( pDev->dwIndex, ( LONG far* )&pDev->hDevice );
   // 如果不成功返回错误
   if ( ErrCde != SUCCESS )
   {
      return FALSE;
   }
   
   // 配置位移计数通道
   ptQCounterConfig.counter       = PICH_Stroke;
   ptQCounterConfig.LatchSrc      = 0;
   ptQCounterConfig.LatchOverflow = 0;
   ptQCounterConfig.ResetOnLatch  = 0;
   ptQCounterConfig.ResetValue    = 1;   // 0x80000000

   // 调用驱动程序，配置通道
   ErrCde = DRV_QCounterConfig (( LONG )pDev->hDevice, &ptQCounterConfig );
   // 如果不成功返回错误
   if ( ErrCde != SUCCESS )
   {
      return FALSE;
   }

   // 启动位移计数通道
   ptQCounterStart.counter   = PICH_Stroke;
   ptQCounterStart.InputMode = 1;
 
   // 调用驱动程序，启动通道 
   ErrCde = DRV_QCounterStart ((LONG )pDev->hDevice, &ptQCounterStart);
   // 如果不成功返回错误
   if ( ErrCde != SUCCESS )
   {
//      return FALSE;
   }
   // 正确返回
   return TRUE;
}

//------------------------------------------------------------------------------------------------
// 关闭研华数据采集卡PCI1784
// 输入:
//    pDev        设备指针
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADPCI1784_Close( LPT_DAQCard pDev )
{
   LRESULT     ErrCde;         // Return error code
   
   // 如果设备没有打开，返回
   if ( pDev->hDevice == NULL )
      return TRUE;
   
   // 调用驱动程序，复位计数通道 
   ErrCde = DRV_CounterReset( ( LONG )pDev->hDevice, PICH_Stroke );
   // 如果不成功返回错误
   if ( ErrCde != SUCCESS )
   {
      return FALSE;
   }
   
   // 调用驱动程序，关闭设备 
   ErrCde = DRV_DeviceClose( ( LONG FAR* )&pDev->hDevice );
   // 如果不成功返回错误
   if ( ErrCde != SUCCESS )
   {
      return FALSE;
   }
   
   // 复位数据指针
   pDev->hDevice = (LONG)NULL;
   
   // 正确返回
   return TRUE;
}

//------------------------------------------------------------------------------------------------
// 配置研华数据采集卡PCI1784计数通道
// 输入:
//    pDev        设备指针
//    ushChannel  通道编号
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADPCI1784_PIConfig(LPT_DAQCard pDev, USHORT ushChannel)
{
   LRESULT     ErrCde;         // Return error code
   // 正确返回
   return TRUE;
}

//------------------------------------------------------------------------------------------------
// 读取研华数据采集卡PCI1784计数通道计数值
// 输入:
//    pDev        设备指针
//    ushChannel  通道编号
// 输出:
//    pdfValue    位移值
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
DWORD g_PIStart = 0x80000000;
BOOL __stdcall ADPCI1784_PIValue( LPT_DAQCard pDev, double* pdfValue )
{
   LRESULT     ErrCde;         // Return error code
   USHORT      usOverflow;
   ULONG       ulLoCount;
   ULONG       ulHiCount;
   
   PT_QCounterRead    ptQCounterRead;
   
   // 准备数据
   ptQCounterRead.counter = PICH_Stroke;
   ptQCounterRead.overflow = (USHORT far *)&usOverflow;
   ptQCounterRead.LoCount  = (ULONG  far *)&ulLoCount;
   ptQCounterRead.HiCount  = (ULONG  far *)&ulHiCount;
   
   // 调用驱动程序，读取计数器
   ErrCde = DRV_QCounterRead( ( LONG )pDev->hDevice, &ptQCounterRead );
   // 如果不成功返回错误
   if ( ErrCde != SUCCESS )
   {
      return FALSE;
   }
   
   // 计算位移
   *pdfValue = labs( g_PIStart - ulLoCount ) * 20.0 / 1000.0;

   // 正确返回
   return TRUE;
}

//------------------------------------------------------------------------------------------------
// 复位研华数据采集卡PCI1784计数通道，将计数机的当前值作为计数起点
// 输入:
//    pDev        设备指针
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADPCI1784_Reset( LPT_DAQCard pDev )
{
   LRESULT     ErrCde;         // Return error code
   USHORT      usOverflow;
   ULONG       ulLoCount;
   ULONG       ulHiCount;
   
   PT_QCounterRead    ptQCounterRead;
   
   // 准备数据
   ptQCounterRead.counter = PICH_Stroke;
   ptQCounterRead.overflow = (USHORT far *)&usOverflow;
   ptQCounterRead.LoCount  = (ULONG  far *)&ulLoCount;
   ptQCounterRead.HiCount  = (ULONG  far *)&ulHiCount;
   
   // 调用驱动程序，读取计数器
   ErrCde = DRV_QCounterRead( ( LONG )pDev->hDevice, &ptQCounterRead );
   // 如果不成功返回错误
   if ( ErrCde != SUCCESS )
   {
      return FALSE;
   }
   
   // 保存初始值
   g_PIStart = ulLoCount;

   // 正确返回
   return TRUE;
}

