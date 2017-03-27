// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************

#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>
#include "DAQDefine.h"
#include "S700K.h"
#include "..\include\device.h"
#include "..\include\driver.h"

#ifndef __ADPCI1784_H__
#define __ADPCI1784_H__

//------------------------------------------------------------------------------------------------
// º¯Êý¶¨Òå
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADPCI1784_Open( LPT_DAQCard pDev );
BOOL __stdcall ADPCI1784_Close( LPT_DAQCard pDev );
BOOL __stdcall ADPCI1784_PIConfig( LPT_DAQCard pDev, USHORT ushChannel);
BOOL __stdcall ADPCI1784_PIValue( LPT_DAQCard pDev, double* pdfValue );
BOOL __stdcall ADPCI1784_Reset( LPT_DAQCard pDev );

#endif
