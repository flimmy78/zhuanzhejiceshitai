// #########################################################################
// *************************************************************************
//                     Copyright (C) 2002-2020.
//   THIS IS AN UNPUBLISHED WORK CONTAINED CONFIDENTIAL, AND PROPRIETARY
//              INFORMATION WHICH IS THE PROPERTY OF TangBo.
// ANY DISCLOSURE, USE, OR REPRODUCTION, WITHOUT WRITTEN AUTHORIZATION FROM
//                        TangBo, IS STRICT.
// #########################################################################
// *************************************************************************

#ifndef __Database_H__
#define __Database_H__

#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>
#include <device.h>

#include <SQLExt.h>

#include "cvidef.h"
#include "..\include\global.h"

//#ifdef __cplusplus
//    extern "C" {
//#endif

//==============================================================================
// Constants
#define PASS            0
#define FAIL            -1
#define EXCEPTION       -2
#define PRIMARYKEY      -1605
//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

//------------------------------------------------------------------------------------------------
typedef struct tagPT_Database
{
   char           cDSNName[32];
   char           cUserName[32];
   char           cPassword[32];
   char           cDatabase[32];
   HENV           hEnvHandle;
   HDBC           hDbcHandle;
   BOOL           bUsed;
}PT_Database, far* LPT_Database;

//------------------------------------------------------------------------------------------------
//数据库连接
long __stdcall DB_Connect(LPT_Database db);
long __stdcall DB_Initialize(LPT_Database db);
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
//数据库断开
long __stdcall DB_Disconnect(LPT_Database db);
long __stdcall DB_Deinitialize(LPT_Database db);
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
SQLHANDLE DB_ActivateSQL(LPT_Database db, char* SQLText);
long DB_DeactivateSQL(SQLHANDLE StateHandle);
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
int __stdcall Database_ReadStandard(LPT_Database db, LPT_Device std, char model[]);
void __stdcall Database_ReadModel(LPT_Database db, int panel, int control);
void __stdcall DataClear(void);
void __stdcall TableSetReportValue(LPT_Record pData);
void __stdcall TableSetRatedValue(LPT_Record pData);
int __stdcall Record2ReportValue(LPT_Device pStd, LPT_Record pData);
//------------------------------------------------------------------------------------------------

//#ifdef __cplusplus
//    }
//#endif

#endif  /* ndef __Database_H__ */
