// #########################################################################
// *************************************************************************
// 转辙机测试线程
// #########################################################################
// *************************************************************************
#include <cvirte.h>
#include <userint.h>
#include "S700K.h"
#include "ADPCI1724.h"
#include "ADPCI1730.h"
#include "ADPCI1784.h"
//#include "DAUSB2833.h"
#include "inifile.h"
#include "..\include\global.h"
#include "Device.h"

//------------------------------------------------------------------------------------------------
// 定义全局变量
//------------------------------------------------------------------------------------------------
extern int              g_plDAQMain;
extern PT_DAQCard       g_PCI1711;
extern PT_DAQCard       g_PCI1724;
//extern PT_DAQCard       g_PCI1730;
extern PT_DAQCard       g_PCI1784;
extern PT_Record        g_S700KData;
extern PT_DAQSystemData g_DAQSystemData;
extern PT_DAQData       g_DAQData;
extern PT_Device        g_Device;
extern PT_PLC           g_Fx2n;
extern int                     g_plMain;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
int CVICALLBACK Callback_Main_IR (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	float fIR;
	if (event != EVENT_COMMIT)
		return 0;

	// 检查
	if (strlen (g_Device.Standard.acModelName) == 0)
	{
		MessageBox (NULL, "无效的设置!", "Error", MB_OK | MB_TOPMOST);
		return 0;
	}
	if (!g_DAQData.Data.usAutoMode)
	{
		MessagePopup ("提示", "手动模式下不允许测试!");
		return 0;
	}

	FX2N_DOControl (DOCH_OilBumpStart, 0);
///   FX2N_DOControl (DOCH_ACSelect, 0);
	FX2N_DOControl (DOCH_SimulateTrack, 0);
	FX2N_DOControl (DOCH_ACForward, 0);
	FX2N_DOControl (DOCH_ACBack, 0);
///   FX2N_DOControl (DOCH_OilCool, 0);
	FX2N_DOControl (DOCH_ForwardValve, 0);
	FX2N_DOControl (DOCH_BackValve, 0);
	FX2N_DOControl (DOCH_TotalValve, 0);
///   FX2N_DOControl (DOCH_MForward, 0);
///   FX2N_DOControl (DOCH_MBack, 0);

	Sleep (2000);
	FX2N_DOControl (DOCH_InsulateTest, 1);
	Sleep (10000);

	if (Meter_Read_IR (&fIR))
		goto Exit;

	g_S700KData.fIR = fIR / 1000000.0;

Exit:
	FX2N_DOControl (DOCH_InsulateTest, 0);
	Sleep (2000);
///   FX2N_DOControl (DOCH_ACSelect, 1);
	return 0;
}

//------------------------------------------------------------------------------------------------
// 获取A位到位状态
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//
//------------------------------------------------------------------------------------------------
void __stdcall DAQDIReadLeft(void)
{

	// 调用系统函数
//   FX2N_Read_DIO ();

	g_DAQData.Data.usLeft = FX2N_GetStatus (DICH_JA1) == 1;
}

//------------------------------------------------------------------------------------------------
// 获取B位到位状态
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//
//------------------------------------------------------------------------------------------------
void __stdcall DAQDIReadRight(void)
{
	// 调用系统函数
//   FX2N_Read_DIO ();

	g_DAQData.Data.usRight = FX2N_GetStatus (DICH_JA2) == 1;
}

//------------------------------------------------------------------------------------------------
// 获取测试模式状态
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//
//------------------------------------------------------------------------------------------------
void __stdcall DAQDIReadMode(void)
{
	// 调用系统函数
//   FX2N_Read_DIO ();

	g_DAQData.Data.usAutoMode = FX2N_GetStatus (DICH_SB7) == 1;
}

//------------------------------------------------------------------------------------------------
// 从数据采集卡读取数字量状态
// 输入:
//    pData       存储采集数据的结构体
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall DAQ_ReadDIStatus( LPT_DAQData pData )
{
	USHORT   ushValue;

	FX2N_Read_DIO ();
	// 读取A位指示
	DAQDIReadLeft ();
	// 读取B位指示
	DAQDIReadRight ();
	// 读取测试模式
	DAQDIReadMode ();
	
	

	// 热继状态
	g_DAQData.Data.usFR1 = FX2N_GetStatus (DICH_FR3) == 0;
	// 热继状态
	g_DAQData.Data.usFR2 = FX2N_GetStatus (DICH_FR1) == 1;
	// 缺相保护状态
	g_DAQData.Data.usJWXC = 0;//FX2N_GetStatus (DICH_FR2) == 0;

	return TRUE;
}
//------------------------------------------------------------------------------------------------
// 读取转辙机动作时间
// 输入:
//    dir       方向。0：A方向，1：B方向
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
double WINAPI DAQAIReadTravelTime (Direction dir)
{
	double travelTime = 0.0;
	FX2N_Read_AIO();// 读取D，字元件 	
	if(dir == DIRECTION_A)
		travelTime = FX2N_GetData (AI_TRAVEL_TIME_A);
	else
		travelTime = FX2N_GetData (AI_TRAVEL_TIME_B);
	return travelTime;
}
//------------------------------------------------------------------------------------------------
// 数据显示
// 输入:
//    pData       存储采集数据的结构体
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void __stdcall DAQ_DataDisplay( LPT_DAQData pData )
{
	// 显示电压
//   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_UDC, pData->Data.dfUdc);
	// 显示电流
//   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_IDC, pData->Data.dfIdc);
	// 显示电压
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_UAB, pData->Data.dfUab);
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_UBC, pData->Data.dfUbc);
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_UCA, pData->Data.dfUca);
	// 显示电流
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_IA, pData->Data.dfIa);
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_IB, pData->Data.dfIb);
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_IC, pData->Data.dfIc);
	// 显示力
	SetCtrlVal( g_plDAQMain, DAQMAIN_NG_FORCE, pData->Data.dfForce );

	// 显示功率
	SetCtrlVal( g_plDAQMain, DAQMAIN_NG_POWER, pData->Data.dfPower );

	// 显示位移
	SetCtrlVal( g_plDAQMain, DAQMAIN_NG_DISTANCE, pData->Data.dfStroke );

	// 显示状态
	SetCtrlVal( g_plDAQMain, DAQMAIN_LED_LEFT, pData->Data.usLeft );
	SetCtrlVal( g_plDAQMain, DAQMAIN_LED_RIGHT, pData->Data.usRight );

	SetCtrlVal( g_plDAQMain, DAQMAIN_LED_AUTO, pData->Data.usAutoMode );

//   SetCtrlVal(g_plDAQMain, DAQMAIN_LED_CONFIG, g_S700KData.Control.usConfig);
//   SetCtrlVal(g_plDAQMain, DAQMAIN_LED_LOAD2, g_Device.Config.usLoad2Test);
//   SetCtrlVal(g_plDAQMain, DAQMAIN_LED_LOAD1, g_Device.Config.usLoad1Test);
//   SetCtrlVal(g_plDAQMain, DAQMAIN_LED_LOAD3, g_Device.Config.usLoad3Test);
//   SetCtrlVal(g_plDAQMain, DAQMAIN_LED_TRAIL, g_Device.Config.usTraillingTest);
//   SetCtrlVal(g_plDAQMain, DAQMAIN_LED_REVISION, g_Device.Config.usRevisionTest);

//   SetCtrlVal(g_plDAQMain, DAQMAIN_NG_AOA, g_DAQSystemData.fAOAForce);
//   SetCtrlVal(g_plDAQMain, DAQMAIN_NG_AOB, g_DAQSystemData.fAOBForce);
	return;
}

//------------------------------------------------------------------------------------------------
// 读取位移
// 输入:
//    无
// 输出:
//    无
// 返回:
//    实测位移
//------------------------------------------------------------------------------------------------
#if 1  // 采集外接光栅尺数据
double WINAPI DAQ_ReadStroke( void )
{
	double   dfValue;
	// 读取位移
	ADPCI1784_PIValue( &g_PCI1784, &dfValue );
	if (dfValue < 0.0)dfValue = 0.0;
	if (dfValue > 3500.0)dfValue = 3500.0;

	return dfValue;
}
#else  // 调试用，模拟光栅尺数据
double WINAPI DAQ_ReadStroke( void )
{
	static double   dfValue = 0.0;
	// 读取位移
	// ADPCI1784_PIValue( &g_PCI1784, &dfValue );
	dfValue += 0.0005;
	if(dfValue>0.24)dfValue = 0.0;

	if (dfValue < 0.0)dfValue = 0.0;
	if (dfValue > 3500.0)dfValue = 3500.0;

	return dfValue;
}
#endif

//------------------------------------------------------------------------------------------------
// 复位位移
// 输入:
//    无
// 输出:
//    无
// 返回:
//
//------------------------------------------------------------------------------------------------
double WINAPI DAQ_ResetStroke( void )
{
	ADPCI1784_Reset( &g_PCI1784 );
	return 0;
}

//------------------------------------------------------------------------------------------------
// 读取测量力
// 输入:
//    无
// 输出:
//    无
// 返回:
//    测量力
//------------------------------------------------------------------------------------------------
double WINAPI DAQ_ReadForce( void )
{
	return fabs (g_DAQData.Data.dfForce);
}
double WINAPI DAQ_ACReadVoltage( void )
{
	return fabs (g_DAQData.Data.dfUdc);
}

double WINAPI DAQ_ACReadCurrent( void )
{
	return fabs (g_DAQData.Data.dfIdc);
}
//------------------------------------------------------------------------------------------------
// 读取A位状态
// 输入:
//    无
// 输出:
//    无
// 返回:
//    状态
//------------------------------------------------------------------------------------------------
USHORT WINAPI DAQ_ReadLeft(void)
{
	USHORT retVal = 0;
	if((g_DAQData.Data.usLeft==1) && (g_DAQData.Data.usRight==0))
	{
		retVal = 1;
	}
	else {}

	return retVal;
	//return g_DAQData.Data.usLeft;
}

//------------------------------------------------------------------------------------------------
// 读取B位状态
// 输入:
//    无
// 输出:
//    无
// 返回:
//    状态
//------------------------------------------------------------------------------------------------
USHORT WINAPI DAQ_ReadRight( void )
{
	USHORT retVal = 0;
	if((g_DAQData.Data.usRight==1) && (g_DAQData.Data.usLeft==0))
	{
		retVal = 1;
	}
	else {}

	return retVal;
	//return g_DAQData.Data.usRight;
}

//------------------------------------------------------------------------------------------------
// 检查测量模式状态
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void WINAPI DAQCheckMode( void )
{
	static short usAutoModeOld = 0;

	// 当从自动状态转换到其他状态时，停止所有输出
	if ((g_DAQData.Data.usAutoMode == 0) && (usAutoModeOld == 1))
	{
		INFO1("--------当从自动状态转换到其他状态时，停止所有输出--------");
		//DAQ_DCLineControl( 0 );
		DAQ_InControl( 0 );
		DAQ_OutControl( 0 );
		//    DAQ_DCLeftControl( 0 );
		//    DAQ_DCRightControl( 0 );
		DAQ_SimulateTrack( 0 );
		DAQ_SetInForce( 0.0 );
		DAQ_SetOutForce( 0.0 );
		DAQ_SetInValve( 0 );
		DAQ_SetOutValve( 0 );
		DAQ_SetTotalValve( 0 );
		DAQ_OilBumpControl( 0 );

		g_DAQSystemData.usTerminate = 1;
	}
	usAutoModeOld = g_DAQData.Data.usAutoMode;
}

//------------------------------------------------------------------------------------------------
// 读取测量模式状态
// 输入:
//    无
// 输出:
//    无
// 返回:
//    状态
//------------------------------------------------------------------------------------------------
USHORT WINAPI DAQ_ReadMode(void)
{
	return g_DAQData.Data.usAutoMode;
}

//------------------------------------------------------------------------------------------------
// 延时采集模拟量和数字量状态状态
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_CheckMeasure( void )
{
	FAI_ReadAIData (&g_DAQData);
	DAQ_ReadDIStatus (&g_DAQData); // 各路信号和转辙机动作时间
	DAQCheckMode ();
	if (g_DAQSystemData.usRunStatus == RUNSTATUS_COMPLETE)
		;
	else if (g_DAQSystemData.usRunStatus == RUNSTATUS_RUNING)
		g_S700KData.Control.ulMeasTime = GetTickCount () - g_DAQSystemData.dwMeasureTicks;
	else
		g_S700KData.Control.ulMeasTime = 0;
}

//------------------------------------------------------------------------------------------------
// 延时函数，自动进行数据采集
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_Delay( DWORD dwDelay )
{
	DWORD dwTicks;
	dwTicks = GetTickCount();
	while ( ( GetTickCount() - dwTicks ) < dwDelay )
	{
		DAQ_CheckMeasure( );
		Sleep( 10 );
	}
}

//------------------------------------------------------------------------------------------------
// 检查超时
// 输入:
//    dwActionTime   实际时间
//    dwTimeout      超时时间
// 输出:
//    无
// 返回:
//    TRUE        超时
//    FALSE       正常
//------------------------------------------------------------------------------------------------
BOOL WINAPI DAQ_CheckError( DWORD dwActionTime, DWORD dwTimeout )
{
	if ( g_DAQSystemData.usTerminate == TRUE )
	{
		INFO1("--------------------负载3，方向B测试，被用户终止--------------------");
		return TRUE;
	}
	if ( dwActionTime <= dwTimeout )
	{
		return FALSE;
	}
	return TRUE;
}

//------------------------------------------------------------------------------------------------
// 油泵控制
// 输入:
//    bAction     TRUE时启动，FALSE时停止
// 输出:
//    无
// 返回:
//    无
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_OilBumpControl( BOOL bAction )
{
	FX2N_DOControl (DOCH_OilBumpStart, (USHORT)bAction);
}

//------------------------------------------------------------------------------------------------
// 缩回控制
// 输入:
//    bAction     TRUE时启动，FALSE时停止
// 输出:
//    无
// 返回:
//    无
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_InControl( BOOL bAction )
{
	FX2N_DOControl (DOCH_ACBack, (USHORT)bAction);
}

//------------------------------------------------------------------------------------------------
// 伸出控制
// 输入:
//    bAction     TRUE时启动，FALSE时停止
// 输出:
//    无
// 返回:
//    无
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_OutControl( BOOL bAction )
{
	FX2N_DOControl (DOCH_ACForward, (USHORT)bAction );
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
// 设置液压负载台负载力区间。
// 输入:
//    dfRatedForce     目标力
// 输出:
//    无
// 返回:
//               
//              
//------------------------------------------------------------------------------------------------
static BOOL gTotalValue;
void DAQ_Force2TotalValue(double dfRatedForce)
{// 按负载力要求，开关总阀切换不同的负载力段。
	if(dfRatedForce < 3.5){
		gTotalValue = 1; // 打开总阀 3.0~3.5KN
	}else{
		gTotalValue = 0; // 关闭总阀 >3.7KN
	}
	DAQ_SetTotalValve (gTotalValue);
	INFO1("    目标负载力: %f(KN)。总阀: %d。",dfRatedForce,gTotalValue);
}

//------------------------------------------------------------------------------------------------
// 读取液压负载台总阀状态。
// 输入:
//    无
// 输出:
//    无 
// 返回:
//    1：总阀打开，0总阀关闭。           
//              
//------------------------------------------------------------------------------------------------
BOOL DAQ_GetTotalValue(void)
{
	return gTotalValue;
}
//------------------------------------------------------------------------------------------------
// 总换向阀控制
// 输入:
//    bAction     TRUE时启动，FALSE时停止
// 输出:
//    无
// 返回:
//    无
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_SetTotalValve( BOOL bAction )
{
	FX2N_DOControl (DOCH_TotalValve, (USHORT)bAction );
}

//------------------------------------------------------------------------------------------------
// 伸出换向阀控制
// 输入:
//    bAction     TRUE时启动，FALSE时停止
// 输出:
//    无
// 返回:
//    无
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_SetOutValve( BOOL bAction )
{
	//FX2N_DOControl (DOCH_BackValve, (USHORT)bAction );
	//FX2N_DOControl (DOCH_ForwardValve, (USHORT)bAction );
	if(g_S700KData.Control.usMount == 1) // 转辙机安装方式设置为左装
	{
		FX2N_DOControl (DOCH_BackValve, (USHORT)bAction );
	}
	else if(g_S700KData.Control.usMount == 2)   // 右装
	{
		FX2N_DOControl (DOCH_ForwardValve, (USHORT)bAction );				
	}
}

//------------------------------------------------------------------------------------------------
// 缩回换向阀控制
// 输入:
//    bAction     TRUE时启动，FALSE时停止
// 输出:
//    无
// 返回:
//    无
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_SetInValve( BOOL bAction )
{
	if(g_S700KData.Control.usMount == 1) // 转辙机安装方式设置为左装
	{
		FX2N_DOControl (DOCH_ForwardValve, (USHORT)bAction );				
	}
	else if(g_S700KData.Control.usMount == 2)   // 右装
	{
		FX2N_DOControl (DOCH_BackValve, (USHORT)bAction );
	}
}

//------------------------------------------------------------------------------------------------
// 模拟轨道电阻接入控制
// 输入:
//    bAction     TRUE时接入，FALSE时断开
// 输出:
//    无
// 返回:
//    无
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_SimulateTrack( BOOL bAction )
{
	// bAction为TRUE 时，接入轨道电阻 -- 不短路轨道电阻，isShort为FALSE
	// bAction为FALSE时，断开轨道电阻 --   短路轨道电阻，isShort为TRUE
	USHORT isShort = !bAction;
	FX2N_DOControl (DOCH_SimulateTrack, isShort);
}

//------------------------------------------------------------------------------------------------
// 伸出换向阀开度控制
// 输入:
//    fValue      阀开度
// 输出:
//    无
// 返回:
//    无
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_SetOutForce( float fValue )
{
//   ADCards_AOValue (&g_PCI1724, AOCH_BackForce, fValue);
//   USB2833_AOValue (&g_PCI1711, AOCH_BackForce, fValue);
	if(g_S700KData.Control.usMount == 1) // 转辙机安装方式设置为左装
	{
		ADCards_AOValue (&g_PCI1724, AOCH_BackForce, fValue);
	}
	else if(g_S700KData.Control.usMount == 2)   // 右装
	{
		ADCards_AOValue (&g_PCI1724, AOCH_ForwardForce, fValue);		
	}
}

//------------------------------------------------------------------------------------------------
// 缩回换向阀开度控制
// 输入:
//    fValue      阀开度
// 输出:
//    无
// 返回:
//    无
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_SetInForce( float fValue )
{
	// ADCards_AOValue (&g_PCI1724, AOCH_ForwardForce, fValue);
//   USB2833_AOValue (&g_PCI1711, AOCH_ForwardForce, fValue);

	if(g_S700KData.Control.usMount == 1) // 转辙机安装方式设置为左装
	{
		ADCards_AOValue (&g_PCI1724, AOCH_ForwardForce, fValue);
	}
	else if(g_S700KData.Control.usMount == 2)   // 右装
	{
		ADCards_AOValue (&g_PCI1724, AOCH_BackForce, fValue);
	}
}

//------------------------------------------------------------------------------------------------
// 直流电压控制
// 输入:
//    fValue      阀开度
// 输出:
//    无
// 返回:
//    无
//
//------------------------------------------------------------------------------------------------
//void WINAPI DAQ_SetDCVoltage( float fValue )
//{
//   ADCards_AOValue (&g_PCI1724, AOCH_DCVoltage, fValue);
//}

//------------------------------------------------------------------------------------------------
// 转辙机测试线程
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//
//------------------------------------------------------------------------------------------------
DWORD WINAPI DAQThreadRoutine( DWORD arg )
{
	//DAQ_DCSelect (0);
//   DAQ_ACSelect (1);

	// 如果运行标志不存在，则退出线程循环
	while (g_DAQSystemData.usDAQThreadLoop)
	{
		// 不在运行状态时，检查启动
		if ((g_DAQSystemData.usRunStatus != RUNSTATUS_RUNING) ||
				(g_DAQSystemData.usRunStatus == RUNSTATUS_COMPLETE))
		{
			// 输入数据采集
			DAQ_CheckMeasure ();

			Sleep (100);

			if (!g_DAQData.Data.usAutoMode)
			{
//            DAQ_ACSelect (1);
				if (g_DAQData.Data.usManualForward)
				{
					DAQ_OutControl (1);
				}
				else
					DAQ_OutControl (0);
				if (g_DAQData.Data.usManualBack)
				{
					DAQ_InControl (1);
				}
				else
					DAQ_InControl (0);
				if (g_DAQData.Data.usManualBumpForward)
				{
					DAQ_SetTotalValve (1);
					DAQ_SetInValve (1);
					DAQ_SetOutValve (0);
				}
				else
				{
					DAQ_SetInValve (0);
				}
				if (g_DAQData.Data.usManualBumpBack)
				{
					DAQ_SetTotalValve (1);
					DAQ_SetInValve (0);
					DAQ_SetOutValve (1);
				}
				else
				{
					DAQ_SetOutValve (0);
				}
			}

			// 如果没有新的配置数据下传，返回到循环开始处
			if (strlen (g_Device.Standard.acModelName) == 0)
				continue;

			// 读入测量模式开关状态
			if (!DAQ_ReadMode ())
			{
				g_DAQSystemData.usRunStatus = RUNSTATUS_TERMINATE;
				continue;
			}

			continue;
		}

		// 清除测试数据
		memset (&g_S700KData.ptMeasureDataA.ptCheckData, 0, sizeof (PT_CheckData));
		memset (&g_S700KData.ptMeasureDataB.ptCheckData, 0, sizeof (PT_CheckData));
		memset (&g_S700KData.ptMeasureDataA.ptLoad2Data, 0, sizeof (PT_Load2Data));
		memset (&g_S700KData.ptMeasureDataB.ptLoad2Data, 0, sizeof (PT_Load2Data));
		memset (&g_S700KData.ptMeasureDataA.ptLoad1Data, 0, sizeof (PT_Load1Data));
		memset (&g_S700KData.ptMeasureDataB.ptLoad1Data, 0, sizeof (PT_Load1Data));
		memset (&g_S700KData.ptMeasureDataA.ptLoad3Data, 0, sizeof (PT_Load3Data));
		memset (&g_S700KData.ptMeasureDataB.ptLoad3Data, 0, sizeof (PT_Load3Data));
		g_S700KData.Control.usAConnection = 0;
		g_S700KData.Control.usBConnection = 0;

		// 设置运行数据
		g_S700KData.Control.usError = 0;
		g_S700KData.Control.usTerminate = 0;
		g_S700KData.Control.usRunStatus = RUNSTATUS_RUNING;
		GetLocalTime (&g_S700KData.ptStart);
		DAQ_Delay (1000);


		// 调用S700K测试管理函数
		if (g_Device.Standard.dwModelID < 300)
			S700K_ThreadRoutine( &g_Device, &g_S700KData );

		// 调用ZDJ9测试管理函数
		if (g_Device.Standard.dwModelID > 300)
			ZDJ9_ThreadRoutine( &g_Device, &g_S700KData );

		// 测量结束后设置运行状态
		g_S700KData.Control.usStep = -1;
		g_S700KData.Control.usConfig = 0;
		g_Device.Config.usTraillingTest = 0;
		g_S700KData.Control.usRunStatus = RUNSTATUS_COMPLETE;
		g_DAQSystemData.usRunStatus = RUNSTATUS_COMPLETE;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 转辙机测试线程
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//
//------------------------------------------------------------------------------------------------
DWORD WINAPI DisplayThreadRoutine( DWORD arg )
{
	DWORD dwTicks;
	while ( g_DAQSystemData.usDisplayThreadLoop )
	{
		// 延时数据显示
		dwTicks = GetTickCount ();
		if ((dwTicks - g_DAQSystemData.dwDAQTicks) > 500)
		{
			g_DAQSystemData.dwDAQTicks = dwTicks;
			//DAQ_DataDisplay( &g_DAQData );
		}
		Sleep(50);
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// 启动转辙机测试线程
// 输入:
//    无
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall DAQ_CreateThread( void )
{
	// 允许线程循环
	g_DAQSystemData.usDAQThreadLoop = TRUE;

	// 建立线程
	g_DAQSystemData.uhDAQThread = CreateThread( NULL, 0, ( LPTHREAD_START_ROUTINE )&DAQThreadRoutine, NULL, 0, NULL );
	if ( g_DAQSystemData.uhDAQThread == NULL )
		return FALSE;

	// 允许显示线程循环
	g_DAQSystemData.usDisplayThreadLoop = TRUE;

	//
	g_DAQSystemData.dwDAQTicks = GetTickCount( );

	// 建立线程
	g_DAQSystemData.uhDisplayThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&DisplayThreadRoutine, NULL, 0, NULL);
	if (g_DAQSystemData.uhDisplayThread == NULL)
		return FALSE;
	return TRUE;
}

//------------------------------------------------------------------------------------------------
// 停止转辙机测试线程
// 输入:
//    无
// 输出:
//    无
// 返回:
//    TRUE        成功
//    FALSE       失败
//------------------------------------------------------------------------------------------------
BOOL __stdcall DAQ_TerminateThread( void )
{
	// 通知线程结束
	g_DAQSystemData.usDAQThreadLoop = FALSE;
	g_DAQSystemData.usDisplayThreadLoop = FALSE;

	// 等待测试线程结束
	WaitForSingleObject (g_DAQSystemData.uhDAQThread, 5000);
	CloseHandle (g_DAQSystemData.uhDAQThread);
	g_DAQSystemData.uhDAQThread = NULL;

	//
	g_DAQSystemData.usDisplayThreadLoop = FALSE;
	// 等待显示线程结束
	WaitForSingleObject( g_DAQSystemData.uhDisplayThread, 5000 );
	CloseHandle (g_DAQSystemData.uhDisplayThread);
	g_DAQSystemData.uhDisplayThread = NULL;
	return TRUE;
}
//------------------------------------------------------------------------------------------------
// 设定转辙机安装方式
// mount:  0:未设置。1：左装。2：右装
//
void SetMount(short mount)
{
	unsigned int yesColor  = 0xFF0000;
	unsigned int noColor = 0xECE9D8;
		
	unsigned int leftButtonColor,rightButtonColor;
	switch(mount){
		case 0:// 未设置
			leftButtonColor  = noColor;
			rightButtonColor = noColor;
			break;
		case 1:// 设置为左装
			leftButtonColor  = yesColor;
			rightButtonColor = noColor;			
			break;
		case 2:// 设置为右装
			leftButtonColor  = noColor;
			rightButtonColor = yesColor;						
			break;
		default:
			leftButtonColor  = noColor;
			rightButtonColor = noColor;
	}
	
	g_S700KData.Control.usMount = mount;  // 转辙机安装方式设置为左装
	SetCtrlAttribute(g_plMain, MAIN_LEFTTYPE, ATTR_CMD_BUTTON_COLOR, leftButtonColor);
	SetCtrlAttribute(g_plMain, MAIN_RIGHTTYPE, ATTR_CMD_BUTTON_COLOR, rightButtonColor);
}

//------------------------------------------------------------------------------------------------
// 左装按钮
int CVICALLBACK CallBack_Left (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
#if 0			
			// FX2N_DOControl(DOCH_LEFT, TRUE);
			// FX2N_DOControl(DOCH_RIGHT, FALSE);
			
			g_S700KData.Control.usMount = 1;  // 转辙机安装方式设置为左装

			SetCtrlAttribute(g_plMain, MAIN_LEFTTYPE, ATTR_CMD_BUTTON_COLOR, 0xFF0000);
			SetCtrlAttribute(g_plMain, MAIN_RIGHTTYPE, ATTR_CMD_BUTTON_COLOR, 0xECE9D8);
#else
			SetMount(1);                      // 0:未设置。1：左装。2：右装
#endif
			break;
	}
	return 0;
}
//------------------------------------------------------------------------------------------------
// 右装按钮
int CVICALLBACK CallBack_Right (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
#if 0			
			// FX2N_DOControl(DOCH_LEFT, FALSE);
			// FX2N_DOControl(DOCH_RIGHT, TRUE);
			g_S700KData.Control.usMount = 2;   // 转辙机安装方式设置为右装

			SetCtrlAttribute(g_plMain, MAIN_LEFTTYPE, ATTR_CMD_BUTTON_COLOR, 0xECE9D8);
			SetCtrlAttribute(g_plMain, MAIN_RIGHTTYPE, ATTR_CMD_BUTTON_COLOR, 0xFF0000);
#else
			SetMount(2);                      // 0:未设置。1：左装。2：右装
#endif
			break;
	}
	return 0;
}
//------------------------------------------------------------------------------------------------
// 设定转辙机四线制/五线制
// wireType:  0:未设置。1：四线制。2：五线制
//
void SetWireType(short wireType)
{
	unsigned int yesColor  = 0xFF0000;
	unsigned int noColor = 0xECE9D8;
		
	unsigned int leftButtonColor,rightButtonColor;
	switch(wireType){
		case 0:// 未设置
			leftButtonColor  = noColor;
			rightButtonColor = noColor;
			FX2N_DOControl(DOCH_FOUR, FALSE);							
			FX2N_DOControl(DOCH_FIVE, FALSE);						
			break;
		case 1:// 设置为四线制
			leftButtonColor  = yesColor;
			rightButtonColor = noColor;			
			FX2N_DOControl(DOCH_FOUR, TRUE);							
			FX2N_DOControl(DOCH_FIVE, FALSE);
			break;
		case 2:// 设置为五线制
			leftButtonColor  = noColor;
			rightButtonColor = yesColor;						
			FX2N_DOControl(DOCH_FOUR, FALSE);							
			FX2N_DOControl(DOCH_FIVE, TRUE);			
			break;
		default:
			leftButtonColor  = noColor;
			rightButtonColor = noColor;
			FX2N_DOControl(DOCH_FOUR, FALSE);							
			FX2N_DOControl(DOCH_FIVE, FALSE);
			INFO1("设定转辙机四线制/五线制错误。SetWireType(wireType)参数wireType = %d",wireType);
	}
	g_S700KData.Control.usWireType = wireType;// 保存转辙机配线方式 
	SetCtrlAttribute(g_plMain, MAIN_Fourxz, ATTR_CMD_BUTTON_COLOR, leftButtonColor);
	SetCtrlAttribute(g_plMain, MAIN_FIVEXZ, ATTR_CMD_BUTTON_COLOR, rightButtonColor);
}
int CVICALLBACK CallBack_Four (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
#if 0			
			//FX2N_DOControl(DOCH_FOUR, FALSE);

			//SetCtrlAttribute(g_plMain, MAIN_Fourxz, ATTR_CMD_BUTTON_COLOR, 0xECE9D8);
			//SetCtrlAttribute(g_plMain, MAIN_FIVEXZ, ATTR_CMD_BUTTON_COLOR, 0xFF0000);
			g_S700KData.Control.usType = 1;// 四线制
			//FX2N_DOControl(DOCH_FIVE, FALSE);
			//FX2N_DOControl(DOCH_FOUR, TRUE);
			SetCtrlAttribute(g_plMain, MAIN_FIVEXZ, ATTR_CMD_BUTTON_COLOR, 0xECE9D8);
			SetCtrlAttribute(g_plMain, MAIN_Fourxz, ATTR_CMD_BUTTON_COLOR, 0xFF0000);
#else
			SetWireType(1);  // 设定转辙机四线制/五线制  0:未设置。1：四线制。2：五线制
#endif
			

			break;
	}
	return 0;
}

int CVICALLBACK CallBack_Five (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
#if 0			
			//FX2N_DOControl(DOCH_FOUR, TRUE);DOCH_FOUR
			g_S700KData.Control.usType = 2;// 五线制
			FX2N_DOControl(DOCH_FOUR, FALSE);
			FX2N_DOControl(DOCH_FIVE, TRUE);
			SetCtrlAttribute(g_plMain, MAIN_FIVEXZ, ATTR_CMD_BUTTON_COLOR, 0xFF0000);
			SetCtrlAttribute(g_plMain, MAIN_Fourxz, ATTR_CMD_BUTTON_COLOR, 0xECE9D8);
#else
			SetWireType(2);  // 设定转辙机四线制/五线制  0:未设置。1：四线制。2：五线制
#endif			
			break;
	}
	return 0;
}
