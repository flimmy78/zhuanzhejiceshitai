// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************

#ifndef __ADPCI1724_H__
#define __ADPCI1724_H__

#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>
#include "S700K.h"
#include "DAQDefine.h"
#include "..\include\device.h"

//------------------------------------------------------------------------------------------------
// ��������
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADCards_AOValue( LPT_DAQCard pDev, USHORT ushChannel, float fVoltage );
BOOL __stdcall ADCards_AOConfig( LPT_DAQCard pDev, USHORT ushChannel );

#endif

