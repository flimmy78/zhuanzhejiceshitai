// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************

#ifndef __ADPCI1711_H__
#define __ADPCI1711_H__

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
BOOL __stdcall ADCards_Open( LPT_DAQCard pDev );
BOOL __stdcall ADCards_Close( LPT_DAQCard pDev );
BOOL __stdcall ADCards_AIConfig( LPT_DAQCard pDev, USHORT ushChannel, USHORT ushGainCode );
//BOOL __stdcall ADCards_AOValue( LPT_DAQCard pDev, USHORT ushChannel, float fVoltage );
//BOOL __stdcall ADCards_AOConfig( LPT_DAQCard pDev, USHORT ushChannel );

#endif

