// #########################################################################
// *************************************************************************

#include <windows.h>
#include <cvirte.h>
#include <ansi_c.h>
#include <userint.h>
#include "S700K.h"
//#include "HMIUDP.h"
#include "..\include\global.h"
#include "DAQDefine.h"
#include "HMIDefine.h"
#include "toolbox.h"

#include "Database.h"
//#include "log.h"

//------------------------------------------------------------------------------------------------
// 定义全局变量
//------------------------------------------------------------------------------------------------
int         g_plMain;
int         g_plTable;
int         g_plPosition;
int         g_plCurrent;
int         g_plPower;
int         g_plTrend;
//------------------------------------------------------------------------------------------------
int         g_plModel;
//------------------------------------------------------------------------------------------------
// Global variables
PT_Device               g_Device;
PT_DAQData              g_DAQData;
PT_Record               g_S700KData;
PT_HMISystemData        g_HMISystemData;
PT_DAQSystemData        g_DAQSystemData;
PT_Database             g_DBStandard;
//------------------------------------------------------------------------------------------------
// Marco
#define CHECKEVENT_NAME       "TB_SERVER_CHECK"
HANDLE                        g_CheckEvent;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// 显示系统时间
//------------------------------------------------------------------------------------------------
int TBDisplayTime( void )
{
	SYSTEMTIME st;
	char  acData[ 32 ];
	GetLocalTime (&st);
	sprintf (acData, "%04d.%02d.%02d", st.wYear, st.wMonth, st.wDay);
	SetCtrlVal (g_plMain, MAIN_TM_DATE, acData);

	sprintf (acData, "%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond );
	SetCtrlVal (g_plMain, MAIN_TM_TIME, acData);
	return 0;
}

//------------------------------------------------------------------------------------------------
// 主程序
//------------------------------------------------------------------------------------------------
int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
					   LPSTR lpszCmdLine, int nCmdShow)
{
	INFO1("----------------启动----------------");
	// 检测程序是否已经允许，如果已经允许则退出
	g_CheckEvent = CreateEvent( NULL, TRUE, FALSE, CHECKEVENT_NAME );
	if ( GetLastError( ) == ERROR_ALREADY_EXISTS )
		return -1;

	// 初始化运行环境
	if (InitCVIRTE (hInstance, 0, 0) == 0)
		return -1;  /* out of memory */

	// 初始化全局变量
	memset (&g_HMISystemData, 0, sizeof (g_HMISystemData) );
	g_HMISystemData.usHMIThreadLoop = 1;
	g_HMISystemData.ulPeriods = 16;
	g_HMISystemData.ulDisplayPointer = FAI_DataBufferSize - g_HMISystemData.ulPeriods;

	memset (&g_DBStandard, 0, sizeof(PT_Database));
	strcpy (g_DBStandard.cDSNName, "Standard");
	strcpy (g_DBStandard.cPassword, "qldq");
	strcpy (g_DBStandard.cDatabase, "Data\\Standard.mdb");

	//连接数据库
	if (DB_Initialize(&g_DBStandard) != PASS)
	{
		MessageBox(NULL, "标准数据库文件打开失败", "错误", MB_OK | MB_ICONERROR);

		goto ExitSystem;
	}

	// 载入各个操作画面
	if ((g_plTable = LoadPanel (0, "S700K.uir", PLTABLE)) < 0)
		return -1;
	if ((g_plPosition = LoadPanel (0, "S700K.uir", PLPosition)) < 0)
		return -1;
	if ((g_plCurrent = LoadPanel (0, "S700K.uir", PLCurrent)) < 0)
		return -1;
	if ((g_plPower = LoadPanel (0, "S700K.uir", PLPower)) < 0)
		return -1;

	if ((g_plTrend = LoadPanel (0, "S700K.uir", PLTrend)) < 0)
		return -1;

	if ((g_plMain = LoadPanel (0, "S700K.uir", MAIN)) < 0)
		goto ExitSystem;


	// 显示系统时间
	TBDisplayTime ();

	g_S700KData.Control.usStep = -1;

	// 建立UDP通讯线程
//   HMI_InitializeUDPCom ();

	// 显示面板
	DisplayPanel(g_plTable);

	DisplayPanel(g_plTrend);
	HidePanel(g_plTrend);
	DisplayPanel (g_plMain);
	// 建立采集,PLC，仪表通信，等线程
	DAQ_Initialize ();
	// 建立数据显示线程
	HMI_CreateThread ();

	// 主程序允许
	RunUserInterface ();

	// 结束显示线程，必须放在“关闭载入的画面”之前
	HMI_TerminateThread ();
	DAQ_Uninitialize ();

	// 关闭载入的画面
	DiscardPanel (g_plMain);
	DiscardPanel (g_plTable);
	DiscardPanel (g_plPosition);
	DiscardPanel (g_plCurrent);
	DiscardPanel (g_plPower);
	DiscardPanel (g_plTrend);

	// 停止UDP通讯线程
//   HMI_UninitializeUDPCom ();


ExitSystem:
	DB_Deinitialize (&g_DBStandard);

	// 关闭检查事件
	CloseHandle (g_CheckEvent);

	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 显示时间定时器事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK datetimeCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	if (event != EVENT_TIMER_TICK)
		return 0;
	TBDisplayTime( );
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 退出按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK quitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	int nRetCode;
	if (event != EVENT_COMMIT)
		return 0;

	// 询问是否退出
	nRetCode = MessageBox (NULL, "是否退出运行?", "提示", MB_YESNO | MB_ICONQUESTION | MB_SYSTEMMODAL);

	// 如果同意退出
	if (nRetCode == IDYES)
		QuitUserInterface (0);

	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 隐藏显示表格按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK HideTableCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	int nValue;
	if (event != EVENT_COMMIT)
		return 0;

	// 表格画面如果显示则隐藏，反之则显示
	GetPanelAttribute( g_plTable, ATTR_VISIBLE, &nValue );
	if ( nValue == 0 )
		DisplayPanel( g_plTable );
	else
		HidePanel( g_plTable );
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 隐藏显示位移画面表格按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK positionCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	int nValue;
	if (event != EVENT_COMMIT)
		return 0;

	// 画面如果已经显示则隐藏，反之则显示
	GetPanelAttribute( g_plPosition, ATTR_VISIBLE, &nValue );
	if ( nValue == 0 )
		DisplayPanel( g_plPosition );
	else
		HidePanel( g_plPosition );
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 隐藏显示电流画面表格按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK currentCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int nValue;
	if (event != EVENT_COMMIT)
		return 0;

	// 画面如果已经显示则隐藏，反之则显示
	GetPanelAttribute( g_plCurrent, ATTR_VISIBLE, &nValue );
	if ( nValue == 0 )
		DisplayPanel( g_plCurrent );
	else
		HidePanel( g_plCurrent );
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 隐藏显示力曲线画面表格按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK powerCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	int nValue;
	if (event != EVENT_COMMIT)
		return 0;

	// 画面如果已经显示则隐藏，反之则显示
	GetPanelAttribute( g_plTrend, ATTR_VISIBLE, &nValue );
	if ( nValue == 0 )
	{
		DisplayPanel (g_plTrend);
	}
	else
	{
		HidePanel (g_plTrend);
	}
	Sleep (100);

	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 转辙机型号按钮事件/下位机关机
//------------------------------------------------------------------------------------------------
BOOL WINAPI QLTableSetInputValue( LPT_Device pDevice );
int CVICALLBACK typeNumberCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	if (event != EVENT_COMMIT)
		return 0;

	g_HMISystemData.usShutdown = 1;

	// 录入数据
	if (TBTypeNumber (g_Device.Standard.acSpecification, 0) != 0)
		return 0;

	// 显示数据
	QLTableSetInputValue (&g_Device);
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 转辙机串号录入按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK serialNumberCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// 录入数据
			if (TBSerialNumber (g_Device.Config.acSerialNumber, 0) != 0)
				break;
			// 显示数据
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 转辙机测试人录入按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK testerNameCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// 录入数据
			if (TBTesterName (g_Device.Config.acTesterName, 0) != 0)
				break;
			// 显示数据
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 转辙机测量结果录入按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK resultCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// 录入数据
			if (TBTestResult (g_Device.Config.acTestResult, 0) != 0)
				break;
			// 显示数据
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 配置信息下传按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK transmitCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	HRESULT error = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			// 清除测试结果
			strcpy (g_Device.Config.acTestResult, "");
			QLTableSetInputValue (&g_Device);
			// 检查
			if (strlen (g_Device.Standard.acModelName) == 0)
			{
				MessageBox (NULL, "无效的设置!", "Error", MB_OK | MB_TOPMOST);
				break;
			}
			// 检查
			if (strlen (g_Device.Standard.acSpecification) == 0)
			{
				MessageBox (NULL, "产品规格不能为空!", "错误", MB_OK | MB_TOPMOST);
				break;
			}
			// 检查
			if (((g_Device.Standard.fMaxTraillingForce <= 0.0)
					|| (g_Device.Standard.fMinTraillingForce <= 0.0))
					&& (g_Device.Config.usTraillingTest == 1))
			{
				MessageBox (NULL, "转辙机不能测试挤岔力!", "错误", MB_OK | MB_TOPMOST);
				break;
			}
			// 检查
			if (strlen (g_Device.Config.acSerialNumber) == 0)
			{
				MessageBox (NULL, "出厂编号不能为空!", "Error", MB_OK | MB_TOPMOST);
				break;
			}
			// 检查四线制/五线制 g_S700KData.Control.usType
			if (g_S700KData.Control.usWireType == 0)
			{
				MessageBox(NULL,"请选择四线制或者五线制！","Error",MB_OK | MB_TOPMOST);
				break;
			}
			// 检查转辙机安装方式.未选择:0,左装:1,右装：2
			if(g_S700KData.Control.usMount == 0)
			{
				MessageBox(NULL,"请选择左装或者右装！","Error",MB_OK | MB_TOPMOST);
			}

			// 请求下传数据
			g_DAQSystemData.usTerminate = FALSE;
			g_DAQSystemData.usRunStatus = RUNSTATUS_RUNING;
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 转辙机设备选择按钮事件
//------------------------------------------------------------------------------------------------
BOOL WINAPI QLTableSetRatedValue( LPT_Device pDevice );
typedef int __stdcall (*DLL_DeviceSelect)(LPT_Device pDevice);
int CVICALLBACK typeCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	HINSTANCE   hInstance = NULL;
	DLL_DeviceSelect pFunction;
	switch (event)
	{
		case EVENT_COMMIT:
			//g_S700KData.Control.usMount = 0;  // 清除左装/右装设置
			SetMount(0);                      // 0:未设置。1：左装。2：右装
			//g_S700KData.Control.usType = 0;   // 清除四线制/五线制设置
			SetWireType(0);  // 设定转辙机四线制/五线制  0:未设置。1：四线制。2：五线制			
			// 载入动态库
			hInstance = LoadLibrary("S700K.dll");
			if (!hInstance)
				break;
			// 获取函数地址
			pFunction = (DLL_DeviceSelect)GetProcAddress(hInstance, "DLL_DeviceSelect");
			// 检查
			if (!pFunction)
				break;
			// 函数调用
			if (pFunction(&g_Device) != 0)
				break;

			// 显示数据
			SetCtrlVal (g_plMain, MAIN_TYPENAME, g_Device.Standard.acSpecification);
			QLTableSetRatedValue (&g_Device);
			break;
	}
	// 释放动态库
	if (!hInstance)
		FreeLibrary(hInstance);
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 报表保存按钮事件
//------------------------------------------------------------------------------------------------
int __stdcall QLReportSave(void);
int CVICALLBACK saveCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QLReportSave( );
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// Excel测试报表打印按钮事件
//------------------------------------------------------------------------------------------------
int __stdcall QLReportPrint(void);
int CVICALLBACK tableCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QLReportPrint ();
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 选择Load2测试按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK load2Callback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// 如果已经选择则取消，反之责选择
			if (g_Device.Config.usLoad2Test == 1)
				g_Device.Config.usLoad2Test = 0;
			else
				g_Device.Config.usLoad2Test = 1;

			// 显示数据
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 选择Load1测试按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK load1Callback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// 如果已经选择则取消，反之责选择
			if (g_Device.Config.usLoad1Test == 1)
				g_Device.Config.usLoad1Test = 0;
			else
				g_Device.Config.usLoad1Test = 1;

			// 显示数据
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 选择Load3测试按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK load3Callback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// 如果已经选择则取消，反之责选择
			if (g_Device.Config.usLoad3Test == 1)
				g_Device.Config.usLoad3Test = 0;
			else
				g_Device.Config.usLoad3Test = 1;

			// 显示数据
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 选择保持力测试按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK revisionCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// 如果已经选择则取消，反之责选择
			if (g_Device.Config.usRevisionTest == 1)
				g_Device.Config.usRevisionTest = 0;
			else
				g_Device.Config.usRevisionTest = 1;

			// 显示数据
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 选择挤岔力测试按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK traillingCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// 如果已经选择则取消，反之责选择
			if (g_Device.Config.usTraillingTest == 1)
				g_Device.Config.usTraillingTest = 0;
			else
				g_Device.Config.usTraillingTest = 1;

			// 显示数据
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 力趋势曲线显示
//------------------------------------------------------------------------------------------------
void __stdcall DisplayTrend(void)
{
	long  ulOffset;
	float *pfDataBuffer;
	long  ulPeriods = 16;
	ulOffset = g_HMISystemData.ulPointer - g_HMISystemData.ulStartPointer;

	// Check offset
	if (ulOffset > FAI_DataBufferSize * 2)
		return;
	if (ulOffset < 0)
		return;

	// Adjust pointer
	ulOffset = ulOffset / 2;

	ulOffset -= ulPeriods;
	if (ulOffset < 0)
		ulOffset = 0;

	pfDataBuffer = g_HMISystemData.ufDataBuffer + ulOffset * FAI_PacerRate;

	SetAxisScalingMode (g_plTrend, PLTrend_FORCETREND, VAL_BOTTOM_XAXIS, VAL_MANUAL,
						ulOffset * 1000, (ulOffset + ulPeriods) * 1000);

	DeleteGraphPlot (g_plTrend, PLTrend_FORCETREND, -1, VAL_IMMEDIATE_DRAW);
	PlotWaveform (g_plTrend, PLTrend_FORCETREND, pfDataBuffer, ulPeriods * FAI_PacerRate, VAL_FLOAT, 1.0, 0.0, ulOffset * 1000, 1.0, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
}

//------------------------------------------------------------------------------------------------
// 力趋势曲线回放显示
//------------------------------------------------------------------------------------------------
void __stdcall DisplayHistroyTrend(void)
{
	long  ulOffset;
	float *pfDataBuffer;
	ulOffset = g_HMISystemData.ulDisplayPointer;

	pfDataBuffer = g_HMISystemData.ufDataBuffer + ulOffset * FAI_PacerRate;

	SetAxisScalingMode (g_plTrend, PLTrend_FORCETREND, VAL_BOTTOM_XAXIS, VAL_MANUAL,
						ulOffset * 1000,
						(ulOffset + g_HMISystemData.ulPeriods) * 1000);

	DeleteGraphPlot (g_plTrend, PLTrend_FORCETREND, -1, VAL_IMMEDIATE_DRAW);
	PlotWaveform (g_plTrend, PLTrend_FORCETREND, pfDataBuffer, g_HMISystemData.ulPeriods * FAI_PacerRate, VAL_FLOAT, 1.0, 0.0, ulOffset * 1000, 1.0, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID,
				  1, VAL_RED);
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 曲线后翻按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK previousCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			g_HMISystemData.ulDisplayPointer -= g_HMISystemData.ulPeriods;
			if (g_HMISystemData.ulDisplayPointer <= 0)
				g_HMISystemData.ulDisplayPointer = 0;
			DisplayHistroyTrend ();

			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 曲线前翻按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK nextCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			g_HMISystemData.ulDisplayPointer += g_HMISystemData.ulPeriods;
			if (g_HMISystemData.ulDisplayPointer >= (FAI_DataBufferSize - g_HMISystemData.ulPeriods))
				g_HMISystemData.ulDisplayPointer = FAI_DataBufferSize - g_HMISystemData.ulPeriods;
			DisplayHistroyTrend ();

			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 曲线隐藏按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK HideCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (g_plTrend, PLTrend_TRENDTIMER, ATTR_ENABLED, 0);
			HidePanel (g_plTrend);

			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 曲线打印按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK printtrendCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetPrintAttribute (ATTR_PRINT_AREA_WIDTH,VAL_USE_ENTIRE_PAPER);
			SetPrintAttribute (ATTR_PRINT_AREA_HEIGHT,VAL_USE_ENTIRE_PAPER);
			PrintCtrl (g_plTrend, PLTrend_FORCETREND, NULL, 1, 0);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 曲线显示定时器事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK trendtimeCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			DisplayTrend ();
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 曲线记录停止按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK stopCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (g_plTrend, PLTrend_TRENDTIMER, ATTR_ENABLED, 0);
			//g_HMISystemData.UDPTrend.usThreadLoop = 0;

			g_HMISystemData.ulDisplayPointer = 0;

			SetCtrlAttribute (g_plTrend, PLTrend_STOP, ATTR_DIMMED, 1);
			SetCtrlAttribute (g_plTrend, PLTrend_RESUME, ATTR_DIMMED, 0);
			SetCtrlAttribute (g_plTrend, PLTrend_PREVIOUS, ATTR_DIMMED, 0);
			SetCtrlAttribute (g_plTrend, PLTrend_NEXT, ATTR_DIMMED, 0);

			SetCtrlAttribute (g_plTrend, PLTrend_TAXISSCALEUP, ATTR_DIMMED, 0);
			SetCtrlAttribute (g_plTrend, PLTrend_TAXISSCALEDOWN, ATTR_DIMMED, 0);
			SetCtrlAttribute (g_plTrend, PLTrend_TAXISSCALEHALF, ATTR_DIMMED, 0);
			SetCtrlAttribute (g_plTrend, PLTrend_TAXISSCALETOTAL, ATTR_DIMMED, 0);

			DisplayHistroyTrend ();
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 曲线记录开始按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK resumeCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			g_HMISystemData.ulStartPointer = 0;
			//g_HMISystemData.UDPTrend.usThreadLoop = 1;

			SetCtrlAttribute (g_plTrend, PLTrend_STOP, ATTR_DIMMED, 0);
			SetCtrlAttribute (g_plTrend, PLTrend_RESUME, ATTR_DIMMED, 1);
			SetCtrlAttribute (g_plTrend, PLTrend_PREVIOUS, ATTR_DIMMED, 1);
			SetCtrlAttribute (g_plTrend, PLTrend_NEXT, ATTR_DIMMED, 1);

			SetCtrlAttribute (g_plTrend, PLTrend_TAXISSCALEUP, ATTR_DIMMED, 1);
			SetCtrlAttribute (g_plTrend, PLTrend_TAXISSCALEDOWN, ATTR_DIMMED, 1);
			SetCtrlAttribute (g_plTrend, PLTrend_TAXISSCALEHALF, ATTR_DIMMED, 1);
			SetCtrlAttribute (g_plTrend, PLTrend_TAXISSCALETOTAL, ATTR_DIMMED, 1);

			SetCtrlAttribute (g_plTrend, PLTrend_TRENDTIMER, ATTR_ENABLED, 1);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 曲线力轴放大按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK faxisscaleupCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	int axisScaling;
	double min, max;
	switch (event)
	{
		case EVENT_COMMIT:
			GetAxisScalingMode (g_plTrend, PLTrend_FORCETREND, VAL_LEFT_YAXIS, &axisScaling, &min, &max);
			if (max > 2)
				max -= 2.0;
			min = -max;
			SetAxisScalingMode (g_plTrend, PLTrend_FORCETREND, VAL_LEFT_YAXIS, VAL_MANUAL, min, max);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 曲线力轴缩小按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK faxisscaledownCallback (int panel, int control, int event,
										void *callbackData, int eventData1, int eventData2)
{
	int axisScaling;
	double min, max;
	switch (event)
	{
		case EVENT_COMMIT:
			GetAxisScalingMode (g_plTrend, PLTrend_FORCETREND, VAL_LEFT_YAXIS, &axisScaling, &min, &max);
			max += 2.0;
			if (max > 50)
				max = 50.0;
			min = -max;
			SetAxisScalingMode (g_plTrend, PLTrend_FORCETREND, VAL_LEFT_YAXIS, VAL_MANUAL, min, max);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 曲线时间轴放大按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK taxisscaleupCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			g_HMISystemData.ulPeriods -= 8;
			if (g_HMISystemData.ulPeriods <= 8)
				g_HMISystemData.ulPeriods = 8;

			if ((g_HMISystemData.ulDisplayPointer + g_HMISystemData.ulPeriods) > FAI_DataBufferSize)
				g_HMISystemData.ulDisplayPointer = FAI_DataBufferSize - g_HMISystemData.ulPeriods;

			DisplayHistroyTrend ();
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 曲线时间轴缩小按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK taxisscaledownCallback (int panel, int control, int event,
										void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			g_HMISystemData.ulPeriods += 8;
			if (g_HMISystemData.ulPeriods >= (FAI_DataBufferSize))
				g_HMISystemData.ulPeriods = FAI_DataBufferSize;

			if ((g_HMISystemData.ulDisplayPointer + g_HMISystemData.ulPeriods) > FAI_DataBufferSize)
				g_HMISystemData.ulDisplayPointer = FAI_DataBufferSize - g_HMISystemData.ulPeriods;

			DisplayHistroyTrend ();

			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 曲线一半数据显示按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK taxisscalehalfCallback (int panel, int control, int event,
										void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			g_HMISystemData.ulPeriods = FAI_DataBufferSize / 2;

			if ((g_HMISystemData.ulDisplayPointer + g_HMISystemData.ulPeriods) > FAI_DataBufferSize)
				g_HMISystemData.ulDisplayPointer = FAI_DataBufferSize - g_HMISystemData.ulPeriods;

			DisplayHistroyTrend ();
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 曲线全部数据显示按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK taxisscaletotalCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			g_HMISystemData.ulPeriods = FAI_DataBufferSize;

			if ((g_HMISystemData.ulDisplayPointer + g_HMISystemData.ulPeriods) > FAI_DataBufferSize)
				g_HMISystemData.ulDisplayPointer = FAI_DataBufferSize - g_HMISystemData.ulPeriods;

			DisplayHistroyTrend ();
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 曲线保存为位图显示按钮事件
//------------------------------------------------------------------------------------------------
int CVICALLBACK savebitmapCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	Rect rc;
	int nBitmapID;
	char chFileName[512];
	char chTitle[128];
	switch (event)
	{
		case EVENT_COMMIT:
			strcpy (chTitle, "保存图像");
			rc.left = 4;
			rc.top = 6;
			rc.width = 860;
			rc.height = 504;
			GetPanelDisplayBitmap (g_plTrend, VAL_FULL_PANEL, rc, &nBitmapID);
			if (FileSelectPopup ("E:\\Picture\\", "Picture.jpg", "*.jpg", chTitle, VAL_SAVE_BUTTON, 0, 1, 1, 1, chFileName) > 0)
			{
				SaveBitmapToJPEGFile (nBitmapID, chFileName, JPEG_INTERLACE, 100);
			}
			DiscardBitmap (nBitmapID);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------

int CVICALLBACK OnExit (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			system("shutdown -p");  // 直接关机，无系统提示。
			//system("shutdown -s");  // 30s后关机，有系统提示。
			//system("shutdown -s -t 360);  （t 指的是时间） 解释：360秒后关机 会出现关机倒计时界面
			//system("shutdown -h");休眠
			break;
	}
	return 0;
}

int CVICALLBACK OnXiuMian (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			system("shutdown -h");
			break;
	}
	return 0;
}

int CVICALLBACK OnQuanPing (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//这很简单,你只要先用SetPanelAttribute(panelHandle,ATTR_TITLEBAR_VISIBLE,0)把窗口的标题栏设为隐藏(即不可见),然后再使用SetPanelAttribute (panelHandle, ATTR_WINDOW_ZOOM, VAL_MAXIMIZE);即可实现全屏,连任务栏也看不到,包好,包好,哈哈哈.
			SetPanelAttribute(panel,ATTR_TITLEBAR_VISIBLE,0);// 窗口的标题栏设为隐藏(即不可见)
			// 然后再使用即可实现全屏,连任务栏也看不到,包好,包好,哈哈哈.
			SetPanelAttribute (panel, ATTR_WINDOW_ZOOM, VAL_MAXIMIZE);
			break;
	}
	return 0;
}
