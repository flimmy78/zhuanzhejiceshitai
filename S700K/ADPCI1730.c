// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************
#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>
#include "S700K.h"
#include "ADPCI1730.h"

//------------------------------------------------------------------------------------------------
// 研华数据采集卡PCI1730的数字量输出
// 输入:
//    pDev        设备指针
//    ushChannel  通道编号
//    ushState    输出状态
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADCards_DOBit( LPT_DAQCard pDev, USHORT ushChannel, USHORT ushState )
{
   LRESULT     ErrCde;         // Return error code
   PT_DioWriteBit  ptDioWriteBit;

   // 如果设备没有打开，返回
   if ( pDev->hDevice == NULL )
   {
      return FALSE;
   }
   // 设置数据结构
   ptDioWriteBit.port  = ushChannel / 8;
   ptDioWriteBit.bit   = ushChannel % 8;
   ptDioWriteBit.state = ushState;
   
   // 调用驱动程序
   ErrCde = DRV_DioWriteBit( (LONG)pDev->hDevice, &ptDioWriteBit );
   // 如果不成功返回错误
   if ( ErrCde != 0)
   {
      return FALSE;
   }
   // 正确返回
   return TRUE;
}

//------------------------------------------------------------------------------------------------
// 研华数据采集卡PCI1730的数字量输出
// 输入:
//    pDev        设备指针
//    ushPort     端口编号
//    ushState    输出状态
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADCards_DOWord( LPT_DAQCard pDev, USHORT ushPort, USHORT ushState )
{
   LRESULT     ErrCde;         // Return error code
   PT_DioWritePortWord  ptDioWritePortWord;

   // 如果设备没有打开，返回
   if ( pDev->hDevice == NULL )
   {
      return FALSE;
   }
   // 设置数据结构
   ptDioWritePortWord.port  = ushPort;
   ptDioWritePortWord.mask  = 0xffff;
   ptDioWritePortWord.state = ushState;
   
   // 调用驱动程序
   ErrCde = DRV_DioWritePortWord( (LONG)pDev->hDevice, &ptDioWritePortWord );
   // 如果不成功返回错误
   if ( ErrCde != 0 )
   {
      return FALSE;
   }
   // 正确返回
   return TRUE;
}
//------------------------------------------------------------------------------------------------
// 研华数据采集卡PCI1730的数字量输入
// 输入:
//    pDev        设备指针
//    ushChannel  通道编号
// 输出:
//    pusState    输入通道状态
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADCards_DIBit(LPT_DAQCard pDev, USHORT ushChannel, USHORT* pusState)
{
   LRESULT     ErrCde;         // Return error code
   PT_DioReadBit  ptDioReadBit;

   // 如果设备没有打开，返回
   if ( pDev->hDevice == NULL )
   {
      return FALSE;
   }
   // 设置数据结构
   ptDioReadBit.port  = ushChannel / 8;
   ptDioReadBit.bit   = ushChannel % 8;
   ptDioReadBit.state = pusState;
   
   // 调用驱动程序
   ErrCde = DRV_DioReadBit ((LONG)pDev->hDevice, &ptDioReadBit );

   // 如果不成功返回错误
   if (ErrCde != 0)
   {
      return FALSE;
   }
   // 正确返回
   return TRUE;
}
//------------------------------------------------------------------------------------------------
