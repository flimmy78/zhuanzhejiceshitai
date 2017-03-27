// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************

#ifndef __USB2833_H__
#define __USB2833_H__

#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>
#include "S700K.h"
#include "DAQDefine.h"
#include "..\include\device.h"

//------------------------------------------------------------------------------------------------
// º¯Êý¶¨Òå
//------------------------------------------------------------------------------------------------
BOOL __stdcall USB2833_Open( LPT_DAQCard pDev );
BOOL __stdcall USB2833_Close( LPT_DAQCard pDev );
BOOL __stdcall USB2833_AOValue( LPT_DAQCard pDev, USHORT ushChannel, float fVoltage );
BOOL __stdcall USB2833_AOConfig( LPT_DAQCard pDev, USHORT ushChannel );

#endif

