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
// 打开研华数据采集卡PCI1711
// 输入:
//    pDev        设备指针
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADCards_Open(LPT_DAQCard pDev)
{
	LRESULT     ErrCde;         // Return error code
	char		lpszErrMsg[256];// 返回的错误描述

	// 如果设备已经被打开，返回
	if ( pDev->hDevice != 0 )
		return TRUE;

	// 调用驱动程序，打开设备
#if 0
	ErrCde = DRV_DeviceOpen( pDev->dwIndex, ( LONG far* )&pDev->hDevice );
#else
	ErrCde = DRV_DeviceOpen( pDev->dwIndex, ( LONG far* )&pDev->hDevice );
	if (ErrCde != SUCCESS)
	{
		DRV_GetErrorMessage(ErrCde,lpszErrMsg);
		ERR1("打开数据采集卡PCI1713失败.从驱动程序返回的故障描述:%s",lpszErrMsg);
		MessageBox(NULL,lpszErrMsg,"错误",MB_OK);
		return FALSE;
	}
#endif
	// 如果不成功返回错误
	if ( ErrCde != SUCCESS )
	{
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
BOOL __stdcall ADCards_Close( LPT_DAQCard pDev )
{
	LRESULT     ErrCde;         // Return error code

	// 如果设备已经被关闭，返回
	if ( pDev->hDevice == NULL )
		return TRUE;

	// 调用驱动程序，关闭设备
	ErrCde = DRV_DeviceClose( ( LONG far* )&pDev->hDevice );
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
// 配置研华数据采集卡PCI1711的输入通道
// 输入:
//    pDev        设备指针
//    ushChannel  通道编号
//    ushGainCode 增益代码
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADCards_AIConfig( LPT_DAQCard pDev, USHORT ushChannel, USHORT ushGainCode )
{
	LRESULT     ErrCde;         // Return error code
	PT_AIConfig ptAIConfig;     // structure for AIConfig table

	// 如果设备没有打开，返回
	if ( pDev->hDevice == NULL )
	{
		return FALSE;
	}

	// 对指定的通道设置增益
	ptAIConfig.DasGain = ushGainCode;
	ptAIConfig.DasChan = ushChannel;

	// 调用驱动程序
	ErrCde = DRV_AIConfig( (LONG)pDev->hDevice, &ptAIConfig );
	// 如果不成功返回错误
	if ( ErrCde != 0 )
	{
		return FALSE;
	}
	// 正确返回
	return TRUE;
}

//------------------------------------------------------------------------------------------------
