// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************
#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>
#include "S700K.h"
#include "ADPCI1711.h"

//------------------------------------------------------------------------------------------------
// 配置研华数据采集卡PCI1711的输出通道
// 输入:
//    pDev        设备指针
//    ushChannel  通道编号
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADCards_AOConfig( LPT_DAQCard pDev, USHORT ushChannel )
{
/*   
   LRESULT     ErrCde;         // Return error code
   PT_AOConfig ptAOConfig;     // structure for AIConfig table

   // 如果设备没有打开，返回
   if ( pDev->hDevice == NULL )
   {
      return FALSE;
   }
   
   // 对指定的通道设置增益
   ptAOConfig.chan = ushChannel;
   ptAOConfig.RefSrc = 0;
   ptAOConfig.MaxValue = 10;
   ptAOConfig.MinValue = 0;
   
   // 调用驱动程序
   ErrCde = DRV_AOConfig( (LONG)pDev->hDevice, &ptAOConfig );
   // 如果不成功返回错误
   if ( ErrCde != 0 )
   {
      return FALSE;
   }
   // 正确返回
*/
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
BOOL __stdcall ADCards_AOValue( LPT_DAQCard pDev, USHORT ushChannel, float fVoltage )
{
   LRESULT     ErrCde;         // Return error code
   PT_AOVoltageOut ptAOVoltageOut;  // structure for AIVoltageIn table
   
   PT_AOScale ptAOScale;
   USHORT     usRaw;
   
   // 如果设备没有打开，返回
   if ( pDev->hDevice == NULL )
   {
      return FALSE;
   }
   
   // 设置数据结构
   ptAOVoltageOut.chan = ushChannel;
   ptAOVoltageOut.OutputValue = fVoltage;
   
   // 调用驱动程序
   ErrCde = DRV_AOVoltageOut( (LONG)pDev->hDevice, &ptAOVoltageOut );
//   ErrCde = DRV_AOBinaryOut ((LONG)pDev->hDevice, &ptAOBinaryOut);
   // 如果不成功返回错误
   if ( ErrCde != 0 )
   {
      return FALSE;
   }
   
   // 正确返回
   return TRUE;
}

//------------------------------------------------------------------------------------------------
