// #########################################################################
// *************************************************************************
//                     Copyright (C) 2002-2020.
//   THIS IS AN UNPUBLISHED WORK CONTAINED CONFIDENTIAL, AND PROPRIETARY
//              INFORMATION WHICH IS THE PROPERTY OF TangBo.
// ANY DISCLOSURE, USE, OR REPRODUCTION, WITHOUT WRITTEN AUTHORIZATION FROM
//                        TangBo, IS STRICT.
// #########################################################################
// *************************************************************************

#include "COMM.h"
#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>
#include <cvirte.h>
#include "S700K.h"
#include <cviauto.h>
#include "excel.h"
#include "inifile.h"
#include "..\include\global.h"
#include "Device.h"
#include <formatio.h>
//#include "Database.h"
#include "HMIDefine.h"
#include "DAQDefine.h"

//------------------------------------------------------------------------------------------------
// 定义全局变量
//------------------------------------------------------------------------------------------------
extern PT_HMISystemData g_HMISystemData;
//------------------------------------------------------------------------------------------------
extern PT_Record        g_S700KData;
extern PT_Device        g_Device;
//------------------------------------------------------------------------------------------------
extern int              g_plTable;
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// Excel Report Variables / Print & Save
//------------------------------------------------------------------------------------------------
static ExcelObj_App               ExcelAppHandle = 0;
static ExcelObj_Workbooks         ExcelWorkbooksHandle = 0;
static ExcelObj_Workbook          ExcelWorkbookHandle = 0;
static ExcelObj_Sheets            ExcelSheetsHandle = 0;
static ExcelObj_Worksheet         ExcelWorksheetHandle = 0;

static VARIANT MyVariant;
//------------------------------------------------------------------------------------------------
#define APP_AUTOMATION_ERR       "Error:  Microsoft Excel Automation"
#define EXCEL_ARRAY_OF_CELLS     "A1:I40"
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// Excel Report Functions
//------------------------------------------------------------------------------------------------
long __stdcall TBExcelOpen( void );
long __stdcall TBExcelClose( void );
long __stdcall TBExcelShow( void );
long __stdcall TBExcelHide( void );
long __stdcall TBExcelCellSetValue( int nLine, int nColumn, char* pchValue );
long __stdcall TBExcelSave( void );
long __stdcall TBExcelCreate( char* pchTemp, char* pchName );
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// 刷新测试结果表中的测量数据
// 输入:
//    pData       测试结果数据
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL WINAPI HMI_TableRefresh( LPT_Record pData )
{
	HRESULT     hrStatus;
	char        chData[ 128 ];

	// 设置测量时间
	if (pData->ptStart.wYear < 2007)
		strcpy (chData, "");
	else
		sprintf (chData, "%04d/%02d/%02d %02d:%02d:%02d", pData->ptStart.wYear, pData->ptStart.wMonth, pData->ptStart.wDay, pData->ptStart.wHour, pData->ptStart.wMinute, pData->ptStart.wSecond);
	SetCtrlVal (g_plTable, PLTABLE_DATE, chData);

	// 设置动程
	if ( ( pData->ptMeasureDataA.ptCheckData.dfInterval == 0.0 ) || ( pData->ptMeasureDataB.ptCheckData.dfInterval == 0.0 ) )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", ( pData->ptMeasureDataA.ptCheckData.dfInterval + pData->ptMeasureDataB.ptCheckData.dfInterval ) / 2.0 );
	SetCtrlVal (g_plTable, PLTABLE_STROKE, chData);

	// 设置B向最大力
	if ( pData->ptMeasureDataB.ptLoad2Data.dfForce == 0.0 )
		strcpy( chData, "" );
	//else if (pData->ptMeasureDataB.ptLoad2Data.usCheckState == 1)
	//   sprintf( chData, ">%.2f", g_Device.Standard.fLoad2_MaxForce );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataB.ptLoad2Data.dfForce );
	SetCtrlVal (g_plTable, PLTABLE_LOAD2B_F, chData);

	// 设置B向动作电流
	if ( ( pData->ptMeasureDataB.ptLoad2Data.dfIa == 0.0 )
			&& ( pData->ptMeasureDataB.ptLoad2Data.dfIb == 0.0 )
			&& ( pData->ptMeasureDataB.ptLoad2Data.dfIc == 0.0 ) )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", ( pData->ptMeasureDataB.ptLoad2Data.dfIa + pData->ptMeasureDataB.ptLoad2Data.dfIb + pData->ptMeasureDataB.ptLoad2Data.dfIc ) / 3 );
	SetCtrlVal (g_plTable, PLTABLE_LOAD2B_I, chData);

	// 设置A向最大力
	if ( pData->ptMeasureDataA.ptLoad2Data.dfForce == 0.0 )
		strcpy( chData, "" );
	//else if (pData->ptMeasureDataA.ptLoad2Data.usCheckState == 1)
	//  sprintf( chData, ">%.2f", g_Device.Standard.fLoad2_MaxForce );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataA.ptLoad2Data.dfForce );
	SetCtrlVal (g_plTable, PLTABLE_LOAD2A_F, chData);

	// 设置A向动作电流
	if ( ( pData->ptMeasureDataA.ptLoad2Data.dfIa == 0.0 ) && ( pData->ptMeasureDataA.ptLoad2Data.dfIb == 0.0 ) && ( pData->ptMeasureDataA.ptLoad2Data.dfIc == 0.0 ) )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", ( pData->ptMeasureDataA.ptLoad2Data.dfIa + pData->ptMeasureDataA.ptLoad2Data.dfIb + pData->ptMeasureDataA.ptLoad2Data.dfIc ) / 3 );
	SetCtrlVal (g_plTable, PLTABLE_LOAD2A_I, chData);

	// 设置Load1动作力
	if ( pData->ptMeasureDataB.ptLoad1Data.dfForce == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataB.ptLoad1Data.dfForce );
	SetCtrlVal (g_plTable, PLTABLE_LOAD1B_F, chData);

	// 设置Load1动作时间
	if ( pData->ptMeasureDataB.ptLoad1Data.dfActionTime == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataB.ptLoad1Data.dfActionTime );
	SetCtrlVal (g_plTable, PLTABLE_LOAD1B_T, chData);

	// 指针Load1动作电流
	if ( ( pData->ptMeasureDataB.ptLoad1Data.dfIa == 0.0 ) && ( pData->ptMeasureDataB.ptLoad1Data.dfIb == 0.0 ) && ( pData->ptMeasureDataB.ptLoad1Data.dfIc == 0.0 ) )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", ( pData->ptMeasureDataB.ptLoad1Data.dfIa + pData->ptMeasureDataB.ptLoad1Data.dfIb + pData->ptMeasureDataB.ptLoad1Data.dfIc ) / 3 );
	SetCtrlVal (g_plTable, PLTABLE_LOAD1B_I, chData);

	// 设置Load1动作力
	if ( pData->ptMeasureDataA.ptLoad1Data.dfForce == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataA.ptLoad1Data.dfForce );
	SetCtrlVal (g_plTable, PLTABLE_LOAD1A_F, chData);

	// 设置Load1动作时间
	if ( pData->ptMeasureDataA.ptLoad1Data.dfActionTime == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataA.ptLoad1Data.dfActionTime );
	SetCtrlVal (g_plTable, PLTABLE_LOAD1A_T, chData);

	// 指针Load1动作电流
	if ( ( pData->ptMeasureDataA.ptLoad1Data.dfIa == 0.0 ) && ( pData->ptMeasureDataA.ptLoad1Data.dfIb == 0.0 ) && ( pData->ptMeasureDataA.ptLoad1Data.dfIc == 0.0 ) )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", ( pData->ptMeasureDataA.ptLoad1Data.dfIa + pData->ptMeasureDataA.ptLoad1Data.dfIb + pData->ptMeasureDataA.ptLoad1Data.dfIc ) / 3 );
	SetCtrlVal (g_plTable, PLTABLE_LOAD1A_I, chData);

	// 设置Load3动作力
	if ( pData->ptMeasureDataB.ptLoad3Data.dfForce == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataB.ptLoad3Data.dfForce );
	SetCtrlVal (g_plTable, PLTABLE_LOAD3B_F, chData);

	// 设置Load3动作时间
	if ( pData->ptMeasureDataB.ptLoad3Data.dfActionTime == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataB.ptLoad3Data.dfActionTime );
	SetCtrlVal (g_plTable, PLTABLE_LOAD3B_T, chData);

	// 指针Load3动作电流
	if ( ( pData->ptMeasureDataB.ptLoad3Data.dfIa == 0.0 ) && ( pData->ptMeasureDataB.ptLoad3Data.dfIb == 0.0 ) && ( pData->ptMeasureDataB.ptLoad3Data.dfIc == 0.0 ) )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", ( pData->ptMeasureDataB.ptLoad3Data.dfIa + pData->ptMeasureDataB.ptLoad3Data.dfIb + pData->ptMeasureDataB.ptLoad3Data.dfIc ) / 3 );
	SetCtrlVal (g_plTable, PLTABLE_LOAD3B_I, chData);

	// 设置Load3动作力
	if ( pData->ptMeasureDataA.ptLoad3Data.dfForce == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataA.ptLoad3Data.dfForce );
	SetCtrlVal (g_plTable, PLTABLE_LOAD3A_F, chData);

	// 设置Load3动作时间
	if ( pData->ptMeasureDataA.ptLoad3Data.dfActionTime == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataA.ptLoad3Data.dfActionTime );
	SetCtrlVal (g_plTable, PLTABLE_LOAD3A_T, chData);

	// 指针Load3动作电流
	if ( ( pData->ptMeasureDataA.ptLoad3Data.dfIa == 0.0 ) && ( pData->ptMeasureDataA.ptLoad3Data.dfIb == 0.0 ) && ( pData->ptMeasureDataA.ptLoad3Data.dfIc == 0.0 ) )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", ( pData->ptMeasureDataA.ptLoad3Data.dfIa + pData->ptMeasureDataA.ptLoad3Data.dfIb + pData->ptMeasureDataA.ptLoad3Data.dfIc ) / 3 );
	SetCtrlVal (g_plTable, PLTABLE_LOAD3A_I, chData);

	// 指针挤岔力
	if (pData->ptMeasureDataB.ptTraillingData.dfForce == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataB.ptTraillingData.dfForce);
	SetCtrlVal (g_plTable, PLTABLE_TRAILLINGB_F, chData);

	// 指针挤岔力
	if (pData->ptMeasureDataA.ptTraillingData.dfForce == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataA.ptTraillingData.dfForce);
	SetCtrlVal (g_plTable, PLTABLE_TRAILLINGA_F, chData);

	// 绝缘电阻
	if (pData->fIR > 199.9)
		sprintf( chData, "∞");
	else
		sprintf( chData, "%.0f", pData->fIR);
	SetCtrlVal (g_plTable, PLTABLE_IR, chData);

	return TRUE;
}
//------------------------------------------------------------------------------------------------
// 方向A接线测试结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_ConnectionA(LPT_Record pData, char* pchData)
{
	short val = pData->Control.usAConnection;
	if (val == 0)
		strcpy (pchData, "");
	else
	{
		if (val == 1)
			strcpy (pchData, "+");
		else
			strcpy (pchData, "-");
	}
}
//------------------------------------------------------------------------------------------------
// 方向B接线测试结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------

void __stdcall ReportResult_ConnectionB(LPT_Record pData, char* pchData)
{
	short val = pData->Control.usBConnection;
	if (val == 0)
		strcpy (pchData, "");
	else
	{
		if (val == 1)
			strcpy (pchData, "+");
		else
			strcpy (pchData, "-");
	}
}
//------------------------------------------------------------------------------------------------
// 计算动程比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Stroke(LPT_Record pData, char* pchData)
{
	double   dfValue;
	if ((pData->ptMeasureDataA.ptCheckData.dfInterval == 0.0) ||
			(pData->ptMeasureDataB.ptCheckData.dfInterval == 0.0))
		strcpy (pchData, "");
	else
	{
		dfValue = (pData->ptMeasureDataA.ptCheckData.dfInterval +
				   pData->ptMeasureDataB.ptCheckData.dfInterval) / 2.0;
		if ((dfValue > g_Device.Standard.fStroke + 2) ||
				(dfValue < g_Device.Standard.fStroke - 2))
			strcpy (pchData, "-");
		else
			strcpy (pchData, "+");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load2最大力比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load2B_F(LPT_Record pData, char* pchData)
{
	if ( pData->ptMeasureDataB.ptLoad2Data.dfForce == 0.0 )
		strcpy (pchData, "");
	else
	{
#if 1
		if (pData->ptMeasureDataB.ptLoad2Data.usCheckState == 1)
		{
			strcpy (pchData, "未卡阻");
		}
		else 
#endif			
		if ((pData->ptMeasureDataB.ptLoad2Data.dfForce
				  < g_Device.Standard.fLoad2_MaxForce)
				 /*&& (pData->ptMeasureDataB.ptLoad2Data.dfForce
				 < g_Device.Standard.fLoad1_OperateForce))*/)
			strcpy (pchData, "+");
		else
			strcpy (pchData, "-");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load2动作电流比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load2B_I(LPT_Record pData, char* chData)
{
	double   dfValue;
	dfValue = (pData->ptMeasureDataB.ptLoad2Data.dfIa
			   + pData->ptMeasureDataB.ptLoad2Data.dfIb
			   + pData->ptMeasureDataB.ptLoad2Data.dfIc) / 3;
	if (dfValue == 0.0)
		strcpy( chData, "" );
	else
	{
		if (dfValue > g_Device.Standard.fLoad2_Current)
			strcpy (chData, "-");
		else
			strcpy (chData, "+");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load2最大力比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load2A_F(LPT_Record pData, char* chData)
{
	if (pData == NULL)
		return;
	if ( pData->ptMeasureDataA.ptLoad2Data.dfForce == 0.0 )
		strcpy (chData, "");
	else
	{
#if 1		
		if (pData->ptMeasureDataA.ptLoad2Data.usCheckState == 1)
		{
			strcpy (chData, "未卡阻");
		}
		else 
#endif			
		if ((pData->ptMeasureDataA.ptLoad2Data.dfForce
				  < g_Device.Standard.fLoad2_MaxForce)
				 /*|| (pData->ptMeasureDataA.ptLoad2Data.dfForce < g_Device.Standard.fLoad1_OperateForce)*/
				)
			strcpy (chData, "+");
		else
			strcpy (chData, "-");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load2动作电流比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load2A_I(LPT_Record pData, char* chData)
{
	double   dfValue;
	dfValue = (pData->ptMeasureDataA.ptLoad2Data.dfIa + pData->ptMeasureDataA.ptLoad2Data.dfIb + pData->ptMeasureDataA.ptLoad2Data.dfIc) / 3;
	if (dfValue == 0.0)
		strcpy( chData, "" );
	else
	{
		if (dfValue > g_Device.Standard.fLoad2_Current)
			strcpy (chData, "-");
		else
			strcpy (chData, "+");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load3动作力比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load3B_F(LPT_Record pData, char* pchData)
{
	if ( pData->ptMeasureDataB.ptLoad3Data.dfForce == 0.0 )
		strcpy (pchData, "");
	else
	{
		if ((pData->ptMeasureDataB.ptLoad3Data.dfForce
				> g_Device.Standard.fLoad3_OperateForce)
				//|| (pData->ptMeasureDataB.ptLoad3Data.dfForce > g_Device.Standard.fLoad2_MaxForce)
		   )
			strcpy (pchData, "+");
		else
			strcpy (pchData, "-");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load3动作电流比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load3B_I(LPT_Record pData, char* chData)
{
	double   dfValue;
	dfValue = (pData->ptMeasureDataB.ptLoad3Data.dfIa + pData->ptMeasureDataB.ptLoad3Data.dfIb + pData->ptMeasureDataB.ptLoad3Data.dfIc) / 3;
	if (dfValue == 0.0)
		strcpy( chData, "" );
	else
	{
		if (dfValue > g_Device.Standard.fLoad3_Current)
			strcpy (chData, "-");
		else
			strcpy (chData, "+");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load1动作时间比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load3B_T(LPT_Record pData, char* chData)
{
	if ( pData->ptMeasureDataB.ptLoad3Data.dfActionTime == 0.0 )
		strcpy (chData, "");
	else
	{
		if (pData->ptMeasureDataB.ptLoad3Data.dfActionTime > g_Device.Standard.fLoad3_TravelTime)
			strcpy (chData, "-");
		else
			strcpy (chData, "+");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load3动作力比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load3A_F(LPT_Record pData, char* pchData)
{
	if ( pData->ptMeasureDataA.ptLoad3Data.dfForce == 0.0 )
		strcpy (pchData, "");
	else
	{
		if ((pData->ptMeasureDataA.ptLoad3Data.dfForce
				> g_Device.Standard.fLoad3_OperateForce)
				//|| (pData->ptMeasureDataA.ptLoad3Data.dfForce > g_Device.Standard.fLoad2_MaxForce)
		   )
			strcpy (pchData, "+");
		else
			strcpy (pchData, "-");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load3动作电流比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load3A_I(LPT_Record pData, char* chData)
{
	double   dfValue;
	dfValue = (pData->ptMeasureDataA.ptLoad3Data.dfIa + pData->ptMeasureDataA.ptLoad3Data.dfIb + pData->ptMeasureDataA.ptLoad3Data.dfIc) / 3;
	if (dfValue == 0.0)
		strcpy( chData, "" );
	else
	{
		if (dfValue > g_Device.Standard.fLoad3_Current)
			strcpy (chData, "-");
		else
			strcpy (chData, "+");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load3动作时间比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load3A_T(LPT_Record pData, char* chData)
{
	if ( pData->ptMeasureDataA.ptLoad3Data.dfActionTime == 0.0 )
		strcpy (chData, "");
	else
	{
		if (pData->ptMeasureDataA.ptLoad3Data.dfActionTime > g_Device.Standard.fLoad3_TravelTime)
			strcpy (chData, "-");
		else
			strcpy (chData, "+");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load1动作力比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load1B_F(LPT_Record pData, char* pchData)
{
	if ( pData->ptMeasureDataB.ptLoad1Data.dfForce == 0.0 )
		strcpy (pchData, "");
	else
	{
		if ((pData->ptMeasureDataB.ptLoad1Data.dfForce
				> g_Device.Standard.fLoad1_OperateForce)
				//|| (pData->ptMeasureDataB.ptLoad1Data.dfForce
				//> g_Device.Standard.fLoad2_MaxForce)
		   )
			strcpy (pchData, "+");
		else
			strcpy (pchData, "-");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load1动作电流比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load1B_I(LPT_Record pData, char* chData)
{
	double   dfValue;
	dfValue = (pData->ptMeasureDataB.ptLoad1Data.dfIa + pData->ptMeasureDataB.ptLoad1Data.dfIb + pData->ptMeasureDataB.ptLoad1Data.dfIc) / 3;
	if (dfValue == 0.0)
		strcpy( chData, "" );
	else
	{
		if (dfValue > g_Device.Standard.fLoad1_Current)
			strcpy (chData, "-");
		else
			strcpy (chData, "+");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load1动作时间比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load1B_T(LPT_Record pData, char* chData)
{
	if ( pData->ptMeasureDataB.ptLoad1Data.dfActionTime == 0.0 )
		strcpy (chData, "");
	else
	{
		if (pData->ptMeasureDataB.ptLoad1Data.dfActionTime > g_Device.Standard.fLoad1_TravelTime)
			strcpy (chData, "-");
		else
			strcpy (chData, "+");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load1动作力比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load1A_F(LPT_Record pData, char* pchData)
{
	if ( pData->ptMeasureDataA.ptLoad1Data.dfForce == 0.0 )
		strcpy (pchData, "");
	else
	{
		if ((pData->ptMeasureDataA.ptLoad1Data.dfForce
				> g_Device.Standard.fLoad1_OperateForce)
				//|| (pData->ptMeasureDataA.ptLoad1Data.dfForce > g_Device.Standard.fLoad2_MaxForce)
		   )
			strcpy (pchData, "+");
		else
			strcpy (pchData, "-");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load1动作电流比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load1A_I(LPT_Record pData, char* chData)
{
	double   dfValue;
	dfValue = (pData->ptMeasureDataA.ptLoad1Data.dfIa + pData->ptMeasureDataA.ptLoad1Data.dfIb + pData->ptMeasureDataA.ptLoad1Data.dfIc) / 3;
	if (dfValue == 0.0)
		strcpy( chData, "" );
	else
	{
		if (dfValue > g_Device.Standard.fLoad1_Current)
			strcpy (chData, "-");
		else
			strcpy (chData, "+");
	}
}

//------------------------------------------------------------------------------------------------
// 计算Load1动作时间比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_Load1A_T(LPT_Record pData, char* chData)
{
	if ( pData->ptMeasureDataA.ptLoad1Data.dfActionTime == 0.0 )
		strcpy (chData, "");
	else
	{
		if (pData->ptMeasureDataA.ptLoad1Data.dfActionTime > g_Device.Standard.fLoad1_TravelTime)
			strcpy (chData, "-");
		else
			strcpy (chData, "+");
	}
}

//------------------------------------------------------------------------------------------------
// 计算挤岔力比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_TraillingA_F(LPT_Record pData, char* chData)
{
	if (pData->ptMeasureDataA.ptTraillingData.dfForce == 0.0 )
		strcpy (chData, "");
	else
	{
		if ((pData->ptMeasureDataA.ptTraillingData.dfForce > g_Device.Standard.fMaxTraillingForce)
				|| (pData->ptMeasureDataA.ptTraillingData.dfForce < g_Device.Standard.fMinTraillingForce))
			strcpy (chData, "-");
		else
			strcpy (chData, "+");
	}
}

//------------------------------------------------------------------------------------------------
// 计算挤岔力比较结果
// 输入:
//    pData       测试结果数据
//    pchData     比较结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall ReportResult_TraillingB_F(LPT_Record pData, char* chData)
{
	if (pData->ptMeasureDataB.ptTraillingData.dfForce == 0.0 )
		strcpy (chData, "");
	else
	{
		if ((pData->ptMeasureDataB.ptTraillingData.dfForce > g_Device.Standard.fMaxTraillingForce)
				|| (pData->ptMeasureDataB.ptTraillingData.dfForce < g_Device.Standard.fMinTraillingForce))
			strcpy (chData, "-");
		else
			strcpy (chData, "+");
	}
}

//------------------------------------------------------------------------------------------------
// 测试结果表显示比较结果
// 输入:
//    pData       测试结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
int __stdcall HMI_TableSetReportResult(LPT_Record pData)
{
	char        chData[ 128 ];
	double      dfValue;
	// 接线测试
	ReportResult_ConnectionA (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_CONA, chData);
	ReportResult_ConnectionB (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_CONB, chData);


	// 动程比较
	ReportResult_Stroke (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_STROKE, chData);

	// Load2,方向B,最大力比较
	ReportResult_Load2B_F (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD2B_F, chData);

	// Load2动作电流比较
	ReportResult_Load2B_I (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD2B_I, chData);

	// Load2,方向A,最大力比较
	ReportResult_Load2A_F (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD2A_F, chData);

	// Load2动作电流比较
	ReportResult_Load2A_I (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD2A_I, chData);

	// Load1,方向B,动作力比较
	ReportResult_Load1B_F (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD1B_F, chData);

	// Load1动作时间比较
	ReportResult_Load1B_T (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD1B_T, chData);

	// Load1动作电流比较
	ReportResult_Load1B_I (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD1B_I, chData);

	// Load1,方向A,动作力比较
	ReportResult_Load1A_F (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD1A_F, chData);

	// Load1动作时间比较
	ReportResult_Load1A_T (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD1A_T, chData);

	// Load1动作电流比较
	ReportResult_Load1A_I (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD1A_I, chData);

	// Load3动作力比较
	ReportResult_Load3B_F (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD3B_F, chData);

	// Load3动作时间比较
	ReportResult_Load3B_T (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD3B_T, chData);

	// Load3动作电流比较
	ReportResult_Load3B_I (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD3B_I, chData);

	// Load3动作力比较
	ReportResult_Load3A_F (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD3A_F, chData);

	// Load3动作时间比较
	ReportResult_Load3A_T (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD3A_T, chData);

	// Load3动作电流比较
	ReportResult_Load3A_I (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_LOAD3A_I, chData);

	// 挤岔力比较
	ReportResult_TraillingA_F (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_TRAILLINGA_F, chData);

	// 挤岔力比较
	ReportResult_TraillingB_F (pData, chData);
	SetCtrlVal (g_plTable, PLTABLE_R_TRAILLINGB_F, chData);
	return 0;
}

//------------------------------------------------------------------------------------------------
// 测试结果表显示转辙机基本信息
// 输入:
//    pData       测试结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
BOOL WINAPI QLTableSetInputValue( LPT_Device pDevice )
{
	HRESULT     hrStatus;
	char        chData[ 128 ];
	BSTR        bStr;
	double      dfValue;

	// 转辙机测试基本信息
	SetCtrlVal (g_plTable, PLTABLE_TYPENUMBER, pDevice->Standard.acSpecification);
	SetCtrlVal (g_plTable, PLTABLE_SERIALNUMBER, pDevice->Config.acSerialNumber);
	SetCtrlVal (g_plTable, PLTABLE_TESTERNAME, pDevice->Config.acTesterName);
	SetCtrlVal (g_plTable, PLTABLE_RESULT, g_Device.Config.acTestResult);

	// 测试模式
	if (pDevice->Config.usLoad2Test == 1)
		strcpy (chData, "√");
	else
		strcpy (chData, "");
	SetCtrlVal (g_plTable, PLTABLE_TEST_LOAD2, chData);

	if (pDevice->Config.usLoad1Test == 1)
		strcpy (chData, "√");
	else
		strcpy (chData, "");
	SetCtrlVal (g_plTable, PLTABLE_TEST_LOAD1, chData);

	if (pDevice->Config.usLoad3Test == 1)
		strcpy (chData, "√");
	else
		strcpy (chData, "");
	SetCtrlVal (g_plTable, PLTABLE_TEST_LOAD3, chData);

	if (pDevice->Config.usTraillingTest == 1)
		strcpy (chData, "√");
	else
		strcpy (chData, "");
	SetCtrlVal (g_plTable, PLTABLE_TEST_TRAILLING, chData);

	if (pDevice->Config.usRevisionTest == 1)
		strcpy (chData, "√");
	else
		strcpy (chData, "");
	SetCtrlVal (g_plTable, PLTABLE_TEST_REVISION, chData);

	return TRUE;
}

//------------------------------------------------------------------------------------------------
// 测试结果表显示转辙机额定信息
// 输入:
//    pData       测试结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
BOOL WINAPI QLTableSetRatedValue( LPT_Device pDevice )
{
	HRESULT     hrStatus;
	char        chData[ 128 ];
	BSTR        bStr;
	double      dfValue;

	// 转辙机型号
	SetCtrlVal (g_plTable, PLTABLE_TYPENAME, pDevice->Standard.acModelName);

	// 动程
	sprintf (chData, "%.2f", pDevice->Standard.fStroke - 2.0);
	SetCtrlVal (g_plTable, PLTABLE_MIN_STROKE, chData);
	sprintf( chData, "%.2f", pDevice->Standard.fStroke + 2.0 );
	SetCtrlVal (g_plTable, PLTABLE_MAX_STROKE, chData);

	// Load2最大力
	sprintf( chData, "%.2f", pDevice->Standard.fLoad2_MaxForce );
	SetCtrlVal (g_plTable, PLTABLE_MAX_LOAD2B_F, chData);
	SetCtrlVal (g_plTable, PLTABLE_MAX_LOAD2A_F, chData);

	// Load2电流
	sprintf( chData, "%.2f", pDevice->Standard.fLoad2_Current );
	SetCtrlVal (g_plTable, PLTABLE_MAX_LOAD2B_I, chData);
	SetCtrlVal (g_plTable, PLTABLE_MAX_LOAD2A_I, chData);

	// Load1动作力
	sprintf( chData, "%.2f", pDevice->Standard.fLoad1_OperateForce );
	SetCtrlVal (g_plTable, PLTABLE_MIN_LOAD1B_F, chData);
	SetCtrlVal (g_plTable, PLTABLE_MIN_LOAD1A_F, chData);

	// Load1动作时间
	sprintf( chData, "%.2f", pDevice->Standard.fLoad1_TravelTime );
	SetCtrlVal (g_plTable, PLTABLE_MAX_LOAD1B_T, chData);
	SetCtrlVal (g_plTable, PLTABLE_MAX_LOAD1A_T, chData);

	// Load1动作电流
	sprintf( chData, "%.2f", pDevice->Standard.fLoad1_Current );
	SetCtrlVal (g_plTable, PLTABLE_MAX_LOAD1B_I, chData);
	SetCtrlVal (g_plTable, PLTABLE_MAX_LOAD1A_I, chData);

	// Load3动作力
	sprintf( chData, "%.2f", pDevice->Standard.fLoad3_OperateForce );
	SetCtrlVal (g_plTable, PLTABLE_MIN_LOAD3B_F, chData);
	SetCtrlVal (g_plTable, PLTABLE_MIN_LOAD3A_F, chData);

	// Load3动作时间
	sprintf( chData, "%.2f", pDevice->Standard.fLoad3_TravelTime );
	SetCtrlVal (g_plTable, PLTABLE_MAX_LOAD3B_T, chData);
	SetCtrlVal (g_plTable, PLTABLE_MAX_LOAD3A_T, chData);

	// Load3动作电流
	sprintf( chData, "%.2f", pDevice->Standard.fLoad3_Current );
	SetCtrlVal (g_plTable, PLTABLE_MAX_LOAD3B_I, chData);
	SetCtrlVal (g_plTable, PLTABLE_MAX_LOAD3A_I, chData);

	// 挤岔力
	if ((pDevice->Standard.fMinTraillingForce <= 0) || (pDevice->Standard.fMaxTraillingForce <= 0))
		strcpy (chData, "");
	else
		sprintf(chData, "%.2f", pDevice->Standard.fMinTraillingForce);
	SetCtrlVal (g_plTable, PLTABLE_MIN_TRAILLING, chData);

	// 挤岔力
	if ((pDevice->Standard.fMinTraillingForce <= 0) || (pDevice->Standard.fMaxTraillingForce <= 0))
		strcpy (chData, "");
	else
		sprintf(chData, "%.2f", pDevice->Standard.fMaxTraillingForce);
	SetCtrlVal (g_plTable, PLTABLE_MAX_TRAILLING, chData);

	return TRUE;
}

//----------------------------------------------------------------------------
// ClearObjHandle
HRESULT ClearObjHandle(CAObjHandle *objHandle)
{
	HRESULT error = 0;
	if ((objHandle) && (*objHandle))
	{
		error = CA_DiscardObjHandle (*objHandle);
		*objHandle = 0;
	}
	return error;
}

//----------------------------------------------------------------------------
// ReportWordAutomationError
static void ReportAppAutomationError( HRESULT hrStatus )
{
	char errorBuf[256];

	if (hrStatus < 0)
	{
		CA_GetAutomationErrorString (hrStatus, errorBuf, sizeof (errorBuf));
		MessagePopup (APP_AUTOMATION_ERR, errorBuf);
	}
	return;
}

//------------------------------------------------------------------------------------------------
//
long __stdcall ExcelOpen( void )
{
	HRESULT hrStatus = 0;

	// Launch App
	hrStatus = Excel_NewApp (NULL, 1, LOCALE_NEUTRAL, 0, &ExcelAppHandle);
	if ( hrStatus < 0 )
		goto Error;

	return 0;

Error:
	ReportAppAutomationError (hrStatus);
	return hrStatus;
}

//------------------------------------------------------------------------------------------------
//
long __stdcall ExcelClose( void )
{
	HRESULT hrStatus = 0;

	ClearObjHandle (&ExcelWorksheetHandle);
	ClearObjHandle (&ExcelSheetsHandle);

	if (ExcelWorkbookHandle)
	{
		// Close workbook without saving
		hrStatus = Excel_WorkbookClose (ExcelWorkbookHandle, NULL, CA_VariantBool (VFALSE),
										CA_DEFAULT_VAL, CA_VariantBool (VFALSE));
		if (hrStatus < 0)
			goto Error;

		ClearObjHandle (&ExcelWorkbookHandle);
	}

	ClearObjHandle (&ExcelWorkbooksHandle);

	if (ExcelAppHandle)
	{
		// Quit the Application
		hrStatus = Excel_AppQuit (ExcelAppHandle, NULL);
		if (hrStatus < 0) goto Error;

		ClearObjHandle (&ExcelAppHandle);
	}

	return 0;
Error:
	ReportAppAutomationError (hrStatus);

	return hrStatus;
}

//------------------------------------------------------------------------------------------------
//
long __stdcall ExcelShow( void )
{
	HRESULT hrStatus = 0;
	// Launch App
	// Connect to existing application if available
	hrStatus = Excel_ActiveApp (NULL, 1, LOCALE_NEUTRAL, 0, &ExcelAppHandle);
	if (hrStatus < 0)
		goto Error;

	// Make App Visible
//    hrStatus = Excel_Set_ApplicationProperty (ExcelAppHandle, NULL, Excel_AppVisible, CAVT_BOOL, VTRUE);
	if (hrStatus < 0)
		goto Error;

	MakeApplicationActive ();
	return 0;
Error:
	ReportAppAutomationError (hrStatus);

	return 0;
}

//------------------------------------------------------------------------------------------------
//
long __stdcall ExcelHide( void )
{
	HRESULT hrStatus = 0;
	// Launch App
	// Connect to existing application if available
	hrStatus = Excel_ActiveApp (NULL, 1, LOCALE_NEUTRAL, 0, &ExcelAppHandle);
	if (hrStatus < 0)
		goto Error;

	// Make App Visible
	hrStatus = Excel_Set_ApplicationProperty (ExcelAppHandle, NULL, Excel_AppVisible, CAVT_BOOL, VFALSE);
	if (hrStatus < 0)
		goto Error;

	MakeApplicationActive ();
	return 0;
Error:
	ReportAppAutomationError (hrStatus);

	return 0;
}

//------------------------------------------------------------------------------------------------
ExcelObj_Range __stdcall ExcelCreateRange(int nLine, int nColumn)
{
	HRESULT error = 0;
	char addr_range[32];
	ExcelObj_Range ExcelRangeHandle = 0;
	VARIANT vr_addr_range;

	sprintf (addr_range, "%c%d:%c%d", nColumn+'A'-1, nLine, nColumn+'A'-1, nLine);
	// Open new Range for Worksheet
	error = CA_VariantSetCString (&vr_addr_range, addr_range);
	error = Excel_WorksheetRange (ExcelWorksheetHandle, NULL, vr_addr_range, CA_DEFAULT_VAL, &ExcelRangeHandle);
	CA_VariantClear (&vr_addr_range);

	if (error < 0)
		return 0;
	// Make range Active
	//error = Excel_RangeActivate (ExcelRangeHandle, NULL, NULL);
	//if (error<0)
	//   goto Error;

	return ExcelRangeHandle;
}

//------------------------------------------------------------------------------------------------
long __stdcall ExcelCellSetCorlor(ExcelObj_Range ExcelRangeHandle, int corlor)
{
	HRESULT error = 0;
	ExcelObj_Font ExcelFontHandle = 0;

	//----------------------------------------------------------------
	// 1) Set cell in Range one at a time using an offset from
	//    range's top left cell
	//----------------------------------------------------------------
	error = Excel_GetRangeProperty (ExcelRangeHandle, NULL, Excel_RangeFont, CAVT_OBJHANDLE, &ExcelFontHandle);
	if (error < 0)
		goto Error;

	error = Excel_SetFontProperty (ExcelFontHandle, NULL, Excel_FontColor, CAVT_INT, corlor);
	if (error < 0)
		goto Error;

	ClearObjHandle (&ExcelFontHandle);
	return 0;

Error:
	ClearObjHandle (&ExcelFontHandle);

	ReportAppAutomationError (error);
	return error;
}

//------------------------------------------------------------------------------------------------
long __stdcall ExcelCellSetValue(int nLine, int nColumn, char* pchValue, int status)
{
	HRESULT error = -1;
	VARIANT CellData;
	ExcelObj_Range ExcelRangeHandle = 0;

	//----------------------------------------------------------------
	// 1) Set cell in Range one at a time using an offset from
	//    range's top left cell
	//----------------------------------------------------------------
	ExcelRangeHandle = ExcelCreateRange (nLine, nColumn);
	if (ExcelRangeHandle == 0)
		goto Error;

	CA_VariantSetCString (&CellData, pchValue);
	error = Excel_RangeSetValue (ExcelRangeHandle, NULL, CA_DEFAULT_VAL, CellData);
	if (error < 0)
		goto Error;

	if (status)
		error = ExcelCellSetCorlor (ExcelRangeHandle, MakeColor (0, 0, 255));
	if (error < 0)
		goto Error;

	CA_VariantClear (&CellData);
	ClearObjHandle (&ExcelRangeHandle);
	return 0;

Error:
	ClearObjHandle (&ExcelRangeHandle);
	CA_VariantClear (&CellData);
	ReportAppAutomationError (error);

	return error;
}

/*
HRESULT CVIFUNC Excel_Worksheet_Protect (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT password,
                                         VARIANT drawingObjects,
                                         VARIANT contents, VARIANT scenarios,
                                         VARIANT userInterfaceOnly);
*/
// 调用excel的保护工作表函数，保护测试记录为只读
// 密码：qili12345
long __stdcall ExcelSetWorkbookReadOnly(void)
{
	HRESULT error = 0; 	
	HRESULT status;
	VARIANT MyVariant;
	
    status = CA_VariantSetCString (&MyVariant, "qili12345");
	error = Excel_Worksheet_Protect(ExcelWorksheetHandle,NULL,
				MyVariant,CA_VariantBool(VTRUE),CA_VariantBool(VTRUE),CA_VariantBool(VTRUE),CA_VariantBool(VTRUE));
    CA_VariantClear(&MyVariant);
    if (status<0) goto Error;
              
Error:    
    if (error < 0) 
        ReportAppAutomationError (error);

    return 0;
}
// 密码为qili12345
// 以宏的方式保护工作表
long __stdcall ExcelSetReadOnlyFile(void)
{
	HRESULT error = 0; 	
	HRESULT status;	
    // Application.Run "exceldem.xls!NewDataFromMacro"
    status = CA_VariantSetCString (&MyVariant, "SetReadOnlyFile");
    error = Excel_AppRun (ExcelAppHandle, NULL, MyVariant, CA_DEFAULT_VAL,
                          CA_DEFAULT_VAL, CA_DEFAULT_VAL, CA_DEFAULT_VAL,
                          CA_DEFAULT_VAL, CA_DEFAULT_VAL, CA_DEFAULT_VAL,
                          CA_DEFAULT_VAL, CA_DEFAULT_VAL, CA_DEFAULT_VAL,
                          CA_DEFAULT_VAL, CA_DEFAULT_VAL, CA_DEFAULT_VAL,
                          CA_DEFAULT_VAL, CA_DEFAULT_VAL, CA_DEFAULT_VAL,
                          CA_DEFAULT_VAL, CA_DEFAULT_VAL, CA_DEFAULT_VAL,
                          CA_DEFAULT_VAL, CA_DEFAULT_VAL, CA_DEFAULT_VAL,
                          CA_DEFAULT_VAL, CA_DEFAULT_VAL, CA_DEFAULT_VAL,
                          CA_DEFAULT_VAL, CA_DEFAULT_VAL, CA_DEFAULT_VAL,
                          CA_DEFAULT_VAL, CA_DEFAULT_VAL, NULL);
    CA_VariantClear(&MyVariant);
    if (status<0) goto Error;
              
Error:    
    if (error < 0) 
        ReportAppAutomationError (error);

    return 0;	
}

//------------------------------------------------------------------------------------------------
//
long __stdcall ExcelSave( void )
{
	HRESULT error = 0;

	// 保护输出的excel文件为只读。方法为：密码保护工作表，禁止用户编辑修改，复制
	// ExcelSetWorkbookReadOnly();
	
	if (ExcelWorkbookHandle)
	{
		error = Excel_WorkbookSave (ExcelWorkbookHandle, NULL);

		if (error < 0)
			goto Error;
	}
	return 0;
Error:
	if (error < 0)
		ReportAppAutomationError (error);
	return error;
}

//------------------------------------------------------------------------------------------------
//
long __stdcall ExcelPrint( void )
{
	HRESULT error = 0;

	if (ExcelWorkbookHandle)
	{
		error = Excel_WorkbookPrintOut (ExcelWorkbookHandle, NULL, CA_DEFAULT_VAL,
										CA_DEFAULT_VAL, CA_DEFAULT_VAL, CA_DEFAULT_VAL, CA_DEFAULT_VAL, CA_DEFAULT_VAL,
										CA_DEFAULT_VAL, CA_DEFAULT_VAL);

		if (error < 0)
			goto Error;
	}
	return 0;
Error:
	if (error < 0)
		ReportAppAutomationError (error);
	return error;
}

//------------------------------------------------------------------------------------------------
//
long __stdcall ExcelPreview( void )
{
	HRESULT error = 0;

	if (ExcelWorkbookHandle)
	{
		error = Excel_WorkbookPrintOut (ExcelWorkbookHandle, NULL, CA_DEFAULT_VAL,
										CA_DEFAULT_VAL, CA_DEFAULT_VAL, CA_VariantBool(TRUE), CA_DEFAULT_VAL, CA_DEFAULT_VAL,
										CA_DEFAULT_VAL, CA_DEFAULT_VAL);

		if (error < 0)
			goto Error;
	}
	return 0;
Error:
	if (error < 0)
		ReportAppAutomationError (error);
	return error;
}

//------------------------------------------------------------------------------------------------
long __stdcall ExcelCreate( char* pchTemp, char* pchName )
{
	HRESULT error = 0;
	VARIANT FileName;
	VARIANT CellRange;

	error = Excel_Get_ApplicationProperty (ExcelAppHandle, NULL, Excel_AppWorkbooks, CAVT_OBJHANDLE, &ExcelWorkbooksHandle);
	if (error < 0)
		goto Error;
	error = CA_VariantSetCString(&FileName, pchTemp);
	error = Excel_WorkbooksAdd (ExcelWorkbooksHandle, NULL, FileName, &ExcelWorkbookHandle);
	if (error < 0)
		goto Error;
	CA_VariantClear(&FileName);
	error = CA_VariantSetCString(&FileName, pchName);

	if (error < 0)
		goto Error;
	// if file exists then delete it
	if (FileExists (pchName, 0))
	{
		error = DeleteFile (pchName);
		if (error < 0)
			return error;
	}
	error = Excel_Workbook_SaveAs (ExcelWorkbookHandle, NULL, FileName,
								   CA_DEFAULT_VAL, CA_DEFAULT_VAL,
								   CA_DEFAULT_VAL, CA_DEFAULT_VAL,
								   CA_DEFAULT_VAL, ExcelConst_xlNoChange,
								   CA_DEFAULT_VAL, CA_DEFAULT_VAL,
								   CA_DEFAULT_VAL, CA_DEFAULT_VAL);
	CA_VariantClear(&FileName);

	if (error < 0)
		goto Error;

	error = Excel_Get_WorkbookProperty (ExcelWorkbookHandle, NULL, Excel_WorkbookActiveSheet, CAVT_OBJHANDLE, &ExcelWorksheetHandle);
	if (error < 0)goto Error;

	// Open new Range for Worksheet
//   error = CA_VariantSetCString (&CellRange, EXCEL_ARRAY_OF_CELLS);
//   error = Excel_WorksheetRange (ExcelWorksheetHandle, NULL, CellRange, CA_DEFAULT_VAL, &ExcelRangeHandle);
//   CA_VariantClear (&CellRange);
//   if (error < 0)
//      goto Error;
	// Make range Active
//   error = Excel_RangeActivate (ExcelRangeHandle, NULL, NULL);
//   if (error<0) goto Error;

	return 0;
Error:
	if (error < 0)
		ReportAppAutomationError (error);
	return error;
}

//------------------------------------------------------------------------------------------------
// 测试报表显示转辙机额定信息
// 输入:
//    pData       测试结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
int __stdcall ExcelSetRatedValue( void )
{
	HRESULT     hrStatus;
	char        chData[ 128 ];
	LPT_Device  pDevice;
	pDevice = &g_Device;

	// 基本信息
	ExcelCellSetValue (2, 3, pDevice->Standard.acModelName, 0);
	ExcelCellSetValue (1, 3, pDevice->Standard.acSpecification, 0);
	ExcelCellSetValue (3, 3, pDevice->Config.acSerialNumber, 0);
	ExcelCellSetValue (4, 3, pDevice->Config.acTesterName, 0);
	ExcelCellSetValue (34, 3, g_Device.Config.acTestResult, 0);

	// 动程
	sprintf( chData, "%.2f", pDevice->Standard.fStroke - 2.0 );
	ExcelCellSetValue (12, 5, chData, 0);
	sprintf( chData, "%.2f", pDevice->Standard.fStroke + 2.0 );
	ExcelCellSetValue (12, 7, chData, 0);

	// Load2最大力
	sprintf( chData, "%.2f", pDevice->Standard.fLoad2_MaxForce );
	ExcelCellSetValue( 13, 7, chData, 0);
	ExcelCellSetValue( 15, 7, chData, 0);

	// Load2动作力
	sprintf( chData, "%.2f", pDevice->Standard.fLoad2_Current );
	ExcelCellSetValue( 14, 7, chData, 0 );
	ExcelCellSetValue( 16, 7, chData, 0 );

	// Load1动作力
	sprintf( chData, "%.2f", pDevice->Standard.fLoad1_OperateForce );
	ExcelCellSetValue( 17, 5, chData, 0 );
	ExcelCellSetValue( 20, 5, chData, 0 );

	// Load1动作时间
	sprintf( chData, "%.2f", pDevice->Standard.fLoad1_TravelTime );
	ExcelCellSetValue( 18, 7, chData, 0 );
	ExcelCellSetValue( 21, 7, chData, 0 );

	// Load1动作电流
	sprintf( chData, "%.2f", pDevice->Standard.fLoad1_Current );
	ExcelCellSetValue( 19, 7, chData, 0 );
	ExcelCellSetValue( 22, 7, chData, 0 );

	// Load3动作力
	sprintf( chData, "%.2f", pDevice->Standard.fLoad3_OperateForce );
	ExcelCellSetValue( 23, 5, chData, 0 );
	ExcelCellSetValue( 26, 5, chData, 0 );

	// Load3动作时间
	sprintf( chData, "%.2f", pDevice->Standard.fLoad3_TravelTime );
	ExcelCellSetValue( 24, 7, chData, 0 );
	ExcelCellSetValue( 27, 7, chData, 0 );

	// Load3动作电流
	sprintf( chData, "%.2f", pDevice->Standard.fLoad3_Current );
	ExcelCellSetValue (25, 7, chData, 0);
	ExcelCellSetValue (28, 7, chData, 0);

	// 挤岔力
	if ((pDevice->Standard.fMinTraillingForce <= 0) || (pDevice->Standard.fMaxTraillingForce <= 0))
		strcpy (chData, "");
	else
		sprintf(chData, "%.2f", pDevice->Standard.fMinTraillingForce);
	ExcelCellSetValue (29, 5, chData, 0);

	// 挤岔力
	if ((pDevice->Standard.fMinTraillingForce <= 0) || (pDevice->Standard.fMaxTraillingForce <= 0))
		strcpy (chData, "");
	else
		sprintf(chData, "%.2f", pDevice->Standard.fMaxTraillingForce);
	ExcelCellSetValue (29, 7, chData, 0);

	// 测试过程选择
	if (pDevice->Config.usLoad2Test == 1)
		ExcelCellSetValue ( 13, 2, "√", 0);
	else
		ExcelCellSetValue ( 13, 2, "", 0);

	if (pDevice->Config.usLoad1Test == 1)
		ExcelCellSetValue ( 17, 2, "√", 0);
	else
		ExcelCellSetValue ( 17, 2, "", 0);

	if (pDevice->Config.usLoad3Test == 1)
		ExcelCellSetValue ( 23, 2, "√", 0);
	else
		ExcelCellSetValue ( 23, 2, "", 0);

	if (pDevice->Config.usTraillingTest == 1)
		ExcelCellSetValue ( 29, 2, "√", 0);
	else
		ExcelCellSetValue ( 29, 2, "", 0);

	if (pDevice->Config.usRevisionTest == 1)
		ExcelCellSetValue ( 31, 2, "√", 0);
	else
		ExcelCellSetValue ( 31, 2, "", 0);

	return 0;
}

//------------------------------------------------------------------------------------------------
// 测试报表显示转辙机测量数据
// 输入:
//    pData       测试结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
int __stdcall ExcelSetReportValue( void )
{
	HRESULT     hrStatus;
	char        chData[ 128 ];
	BSTR        bStr;
	double      dfValue;
	LPT_Record  pData;
	pData = &g_S700KData;

	// 设置测试时间
	sprintf( chData, "%04d/%02d/%02d %02d:%02d:%02d", pData->ptStart.wYear, pData->ptStart.wMonth, pData->ptStart.wDay, pData->ptStart.wHour, pData->ptStart.wMinute, pData->ptStart.wSecond );
	ExcelCellSetValue( 5, 3, chData, 0 );

	// 设置动程
	if ( ( pData->ptMeasureDataA.ptCheckData.dfInterval == 0.0 ) || ( pData->ptMeasureDataB.ptCheckData.dfInterval == 0.0 ) )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", ( pData->ptMeasureDataA.ptCheckData.dfInterval + pData->ptMeasureDataB.ptCheckData.dfInterval ) / 2.0 );
	ExcelCellSetValue( 12, 6, chData, 0 );

	// 设置Load2最大力
	if ( pData->ptMeasureDataB.ptLoad2Data.dfForce == 0.0 )
		strcpy( chData, "" );
#if 0	// 现场要求，不显示">"号,直接显示值超量程的值。
	else if (pData->ptMeasureDataB.ptLoad2Data.usCheckState == 1)
		sprintf( chData, ">%.2f", g_Device.Standard.fLoad2_MaxForce );
#endif	
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataB.ptLoad2Data.dfForce );
	ExcelCellSetValue( 13, 6, chData, 0 );

	// 设置Load2动作电流
	if ((pData->ptMeasureDataB.ptLoad2Data.dfIa == 0.0) && (pData->ptMeasureDataB.ptLoad2Data.dfIb == 0.0) && (pData->ptMeasureDataB.ptLoad2Data.dfIc == 0.0))
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", ( pData->ptMeasureDataB.ptLoad2Data.dfIa + pData->ptMeasureDataB.ptLoad2Data.dfIb + pData->ptMeasureDataB.ptLoad2Data.dfIc ) / 3 );
	ExcelCellSetValue( 14, 6, chData, 0 );

	// 设置Load2最大力
	if ( pData->ptMeasureDataA.ptLoad2Data.dfForce == 0.0 )
		strcpy( chData, "" );
#if 0	// 现场要求，不显示">"号,直接显示值超量程的值。    	
	else if (pData->ptMeasureDataA.ptLoad2Data.usCheckState == 1)
		sprintf( chData, ">%.2f", g_Device.Standard.fLoad2_MaxForce );
#endif	
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataA.ptLoad2Data.dfForce );
	ExcelCellSetValue( 15, 6, chData, 0 );

	// 设置Load2动作电流
	if ((pData->ptMeasureDataA.ptLoad2Data.dfIa == 0.0) && (pData->ptMeasureDataA.ptLoad2Data.dfIb == 0.0) && (pData->ptMeasureDataA.ptLoad2Data.dfIc == 0.0))
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", ( pData->ptMeasureDataA.ptLoad2Data.dfIa + pData->ptMeasureDataA.ptLoad2Data.dfIb + pData->ptMeasureDataA.ptLoad2Data.dfIc ) / 3 );
	ExcelCellSetValue( 16, 6, chData, 0 );

	// 设置Load1动作力
	if ( pData->ptMeasureDataB.ptLoad1Data.dfForce == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataB.ptLoad1Data.dfForce );
	ExcelCellSetValue( 17, 6, chData, 0 );

	// Interval Force 12:12
	if ( pData->ptMeasureDataB.ptLoad1Data.dfActionTime == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataB.ptLoad1Data.dfActionTime );
	ExcelCellSetValue( 18, 6, chData, 0 );

	// 设置Load2动作电流
	if ((pData->ptMeasureDataB.ptLoad1Data.dfIa == 0.0) && (pData->ptMeasureDataB.ptLoad1Data.dfIb == 0.0) && (pData->ptMeasureDataB.ptLoad1Data.dfIc == 0.0))
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", ( pData->ptMeasureDataB.ptLoad1Data.dfIa + pData->ptMeasureDataB.ptLoad1Data.dfIb + pData->ptMeasureDataB.ptLoad1Data.dfIc ) / 3 );
	ExcelCellSetValue( 19, 6, chData, 0 );

	// 设置Load1动作力
	if ( pData->ptMeasureDataA.ptLoad1Data.dfForce == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataA.ptLoad1Data.dfForce );
	ExcelCellSetValue( 20, 6, chData, 0 );

	// 设置Load1动作时间
	if ( pData->ptMeasureDataA.ptLoad1Data.dfActionTime == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataA.ptLoad1Data.dfActionTime );
	ExcelCellSetValue( 21, 6, chData, 0 );

	// 设置Load1动作电流
	if ((pData->ptMeasureDataA.ptLoad1Data.dfIa == 0.0) && (pData->ptMeasureDataA.ptLoad1Data.dfIb == 0.0) && (pData->ptMeasureDataA.ptLoad1Data.dfIc == 0.0))
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", ( pData->ptMeasureDataA.ptLoad1Data.dfIa + pData->ptMeasureDataA.ptLoad1Data.dfIb + pData->ptMeasureDataA.ptLoad1Data.dfIc ) / 3 );
	ExcelCellSetValue( 22, 6, chData, 0 );

	// 设置Load1动作力
	if ( pData->ptMeasureDataB.ptLoad3Data.dfForce == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataB.ptLoad3Data.dfForce );
	ExcelCellSetValue( 23, 6, chData, 0 );

	// 设置Load1动作时间
	if ( pData->ptMeasureDataB.ptLoad3Data.dfActionTime == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataB.ptLoad3Data.dfActionTime );
	ExcelCellSetValue( 24, 6, chData, 0 );

	// 设置Load1动作电流
	if ((pData->ptMeasureDataB.ptLoad3Data.dfIa == 0.0) && (pData->ptMeasureDataB.ptLoad3Data.dfIb == 0.0) && (pData->ptMeasureDataB.ptLoad3Data.dfIc == 0.0))
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", ( pData->ptMeasureDataB.ptLoad3Data.dfIa + pData->ptMeasureDataB.ptLoad3Data.dfIb + pData->ptMeasureDataB.ptLoad3Data.dfIc ) / 3 );
	ExcelCellSetValue( 25, 6, chData, 0 );

	// 设置Load3动作力
	if ( pData->ptMeasureDataA.ptLoad3Data.dfForce == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataA.ptLoad3Data.dfForce );
	ExcelCellSetValue( 26, 6, chData, 0 );

	// 设置Load3动作时间
	if ( pData->ptMeasureDataA.ptLoad3Data.dfActionTime == 0.0 )
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", pData->ptMeasureDataA.ptLoad3Data.dfActionTime );
	ExcelCellSetValue( 27, 6, chData, 0 );

	// 设置Load3动作电流
	if ((pData->ptMeasureDataA.ptLoad3Data.dfIa == 0.0) && (pData->ptMeasureDataA.ptLoad3Data.dfIb == 0.0) && (pData->ptMeasureDataA.ptLoad3Data.dfIc == 0.0))
		strcpy( chData, "" );
	else
		sprintf( chData, "%.2f", ( pData->ptMeasureDataA.ptLoad3Data.dfIa + pData->ptMeasureDataA.ptLoad3Data.dfIb + pData->ptMeasureDataA.ptLoad3Data.dfIc ) / 3 );
	ExcelCellSetValue( 28, 6, chData, 0 );

	// 挤岔力
	if (pData->ptMeasureDataB.ptTraillingData.dfForce == 0.0)
		strcpy (chData, "");
	else
		sprintf (chData, "%.2f", pData->ptMeasureDataB.ptTraillingData.dfForce);
	ExcelCellSetValue( 29, 6, chData, 0 );

	// 挤岔力
	if (pData->ptMeasureDataA.ptTraillingData.dfForce == 0.0)
		strcpy (chData, "");
	else
		sprintf (chData, "%.2f", pData->ptMeasureDataA.ptTraillingData.dfForce);
	ExcelCellSetValue( 30, 6, chData, 0 );

	// 绝缘电阻
	if (pData->fIR > 199.9)
		sprintf(chData, "∞");
	else
		sprintf( chData, "%.0f", pData->fIR);
	ExcelCellSetValue( 32, 6, chData, 0 );

	return 0;
}

//------------------------------------------------------------------------------------------------
// 测试报表显示转辙机测量数据比较结果
// 输入:
//    pData       测试结果数据
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
int __stdcall ExcelSetReportResult(void)
{
	HRESULT     hrStatus;
	char        chData[ 128 ];
	BSTR        bStr;
	double      dfValue;
	LPT_Record  pData;
	pData = &g_S700KData;
	
#if 1
// 接线测试方向A
	ReportResult_ConnectionA (pData, chData);
	ExcelCellSetValue (8, 9, chData, 0);	
	
// 接线测试方向B
	ReportResult_ConnectionB (pData, chData);
	ExcelCellSetValue (9, 9, chData, 0);
#endif	
	
	// 动程比较结果
	ReportResult_Stroke (pData, chData);
	ExcelCellSetValue (12, 9, chData, 0);

	// Load2最大力比较结果
	ReportResult_Load2B_F (pData, chData);
	ExcelCellSetValue( 13, 9, chData, 0 );

	// Load2动作电流比较结果
	ReportResult_Load2B_I (pData, chData);
	ExcelCellSetValue( 14, 9, chData, 0 );

	// Load2最大力比较结果
	ReportResult_Load2A_F (pData, chData);
	ExcelCellSetValue( 15, 9, chData, 0 );

	// Load2动作电流比较结果
	ReportResult_Load2A_I (pData, chData);
	ExcelCellSetValue( 16, 9, chData, 0 );

	// Load1动作力比较结果
	ReportResult_Load1B_F (pData, chData);
	ExcelCellSetValue( 17, 9, chData, 0 );

	// Load1动作时间比较结果
	ReportResult_Load1B_T (pData, chData);
	ExcelCellSetValue( 18, 9, chData, 0 );

	// Load1动作电流比较结果
	ReportResult_Load1B_I (pData, chData);
	ExcelCellSetValue( 19, 9, chData, 0 );

	// Load1动作力比较结果
	ReportResult_Load1A_F (pData, chData);
	ExcelCellSetValue( 20, 9, chData, 0 );

	// Load1动作时间比较结果
	ReportResult_Load1A_T (pData, chData);
	ExcelCellSetValue( 21, 9, chData, 0 );

	// Load1动作电流比较结果
	ReportResult_Load1A_I (pData, chData);
	ExcelCellSetValue( 22, 9, chData, 0 );

	// Load3动作力比较结果
	ReportResult_Load3B_F (pData, chData);
	ExcelCellSetValue( 23, 9, chData, 0 );

	// Load3动作时间比较结果
	ReportResult_Load3B_T (pData, chData);
	ExcelCellSetValue( 24, 9, chData, 0 );

	// Load3动作电流比较结果
	ReportResult_Load3B_I (pData, chData);
	ExcelCellSetValue( 25, 9, chData, 0 );

	// Load3动作力比较结果
	ReportResult_Load3A_F (pData, chData);
	ExcelCellSetValue( 26, 9, chData, 0 );

	// Load3动作时间比较结果
	ReportResult_Load3A_T (pData, chData);
	ExcelCellSetValue( 27, 9, chData, 0 );

	// Load3动作电流比较结果
	ReportResult_Load3A_I (pData, chData);
	ExcelCellSetValue( 28, 9, chData, 0 );

	// 挤岔力
	ReportResult_TraillingA_F (pData, chData);
	ExcelCellSetValue( 29, 9, chData, 0 );

	// 挤岔力
	ReportResult_TraillingB_F (pData, chData);
	ExcelCellSetValue( 30, 9, chData, 0 );

	return 0;
}

//------------------------------------------------------------------------------------------------
// 检查是否允许生成报表
// 输入:
//    无
// 输出:
//    无
// 返回:
//    0        正确
//    <0       错误
//------------------------------------------------------------------------------------------------
int __stdcall QLReportCheck(void)
{
	// 时间检查
	if (g_S700KData.ptStart.wYear == 0)
	{
		MessageBox (NULL, "测试数据无效!", "错误", MB_OK | MB_ICONERROR | MB_TOPMOST );
		return -1;
	}

	// 基本信息检查
	if (strlen (g_Device.Config.acSerialNumber) <= 0)
	{
		MessageBox (NULL, "测试数据无效!", "错误", MB_OK | MB_ICONERROR | MB_TOPMOST );
		return -1;
	}

	// 测试结果检查
	if (strlen (g_Device.Config.acTestResult) <= 0)
	{
		MessageBox (NULL, "未输入测试结果!", "错误", MB_OK | MB_ICONERROR | MB_TOPMOST );
		return -1;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------
// 建立测试报表
// 输入:
//    nPrint      创建方式
// 输出:
//    无
// 返回:
//    0        正确
//    <0       错误
//------------------------------------------------------------------------------------------------
int __stdcall QLReportCreate(int nPrint)
{
	HRESULT     hrStatus;
	char chData[ 256 ];
	char chFileName[512];
	char chTitle[128];
	char chTpl[1024];//模板路径
	char chDir[512];//当前程序路径

	// 检查能否生成报表
#if 0 // 调试打印程序，暂时关闭检查   
	if (QLReportCheck () < 0)
		return -1;
#endif

	// 如果是直接打印
	if (nPrint == 1)
	{
		sprintf (chFileName, "E:\\Report\\Print.xls");
	}
	// 否则创建Excel报表名称
	else
	{
		strcpy (chTitle, "保存报表");
		sprintf (chData, "%04d%02d%02d-%s.xls", g_S700KData.ptStart.wYear,
				 g_S700KData.ptStart.wMonth, g_S700KData.ptStart.wDay,
				 g_Device.Config.acSerialNumber);

		if (FileSelectPopup ("E:\\Report\\", chData, "*.xls", chTitle, VAL_SAVE_BUTTON, 0, 1, 1, 1, chFileName) <= 0)
			return -1;
	}
	// 设置模板文件路径
	GetProjectDir(chDir);
#if 1	
	MakePathname(chDir,"Data\\CS700K.xlt",chTpl);
#else	
	MakePathname(chDir,"Data\\CS700K.xls",chTpl);
#endif	
	// 启动Excel
	if (ExcelOpen ())
		return -1;

	// 检测Excel报表
#if 0
	if (ExcelCreate ("E:\\S700K\\working\\S700K\\Data\\CS700K.xlt", chFileName))
		return -1;
#else
	if (ExcelCreate (chTpl, chFileName))
		goto Exit;
#endif
	// 设置额定值
	if (ExcelSetRatedValue ())
		goto Exit;
	// 设置测量值
	if (ExcelSetReportValue ())
		goto Exit;
	// 设置比较结果
	if (ExcelSetReportResult ())
		goto Exit;

	return 0;
Exit:
	ExcelClose();
	return -1;
}

//------------------------------------------------------------------------------------------------
// 关闭报表
// 输入:
//    无
// 输出:
//    无
// 返回:
//    0        正确
//    <0       错误
//------------------------------------------------------------------------------------------------
int __stdcall QLReportClose(void)
{
	if (ExcelClose ())
		return 0;
	return 0;
}

//------------------------------------------------------------------------------------------------
// 保存报表
// 输入:
//    无
// 输出:
//    无
// 返回:
//    0        正确
//    <0       错误
//------------------------------------------------------------------------------------------------
int __stdcall QLReportSave(void)
{
	if (QLReportCreate (0) == -1)
		return -1;

	if (ExcelSave ())
		return -1;

	if (QLReportClose () == -1)
		return -1;

	return 0;
}

//------------------------------------------------------------------------------------------------
// 打印报表
// 输入:
//    无
// 输出:
//    无
// 返回:
//    0        正确
//    <0       错误
//------------------------------------------------------------------------------------------------
int __stdcall QLReportPrint( void )
{
	if (QLReportCreate (1) == -1)
		goto Exit;

	if (ExcelPrint ())
		goto Exit;

	if (QLReportClose () == -1)
		return -1;

	return 0;
Exit:
	ExcelClose();
	return -1;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 报表打印按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK printCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QLReportPrint( );
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
