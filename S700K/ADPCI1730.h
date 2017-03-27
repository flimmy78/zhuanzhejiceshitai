// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************

#ifndef __ADPCI1730_H__
#define __ADPCI1730_H__

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
BOOL __stdcall ADCards_DOBit( LPT_DAQCard pDev, USHORT ushChannel, USHORT ushState );
BOOL __stdcall ADCards_DOByte( LPT_DAQCard pDev, USHORT ushPort, USHORT ushMask, USHORT ushState );
BOOL __stdcall ADCards_DOWord( LPT_DAQCard pDev, USHORT ushPort, USHORT ushState );
BOOL __stdcall ADCards_DIBit( LPT_DAQCard pDev, USHORT ushChannel, USHORT* pusState );
BOOL __stdcall ADCards_DIByte( LPT_DAQCard pDev, USHORT ushPort, USHORT* pusState );
BOOL __stdcall ADCards_DIWord( LPT_DAQCard pDev, USHORT ushPort, USHORT* pusState );

#endif

