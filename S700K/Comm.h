// #########################################################################
// *************************************************************************
//                     Copyright (C) 2002-2020.
//   THIS IS AN UNPUBLISHED WORK CONTAINED CONFIDENTIAL, AND PROPRIETARY
//              INFORMATION WHICH IS THE PROPERTY OF TangBo.
// ANY DISCLOSURE, USE, OR REPRODUCTION, WITHOUT WRITTEN AUTHORIZATION FROM
//                        TangBo, IS STRICT.
// #########################################################################
// *************************************************************************
#include <cvirte.h>     
#include <userint.h>
#include "Device.h"

#ifndef __COMM_H__
#define __COMM_H__

//------------------------------------------------------------------------------------------------
BOOL __stdcall COM_Open(LPT_Port pDev);
BOOL __stdcall COM_Close(LPT_Port pDev);

#endif
