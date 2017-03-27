// #########################################################################
// *************************************************************************
// 转辙机Load1测量
// #########################################################################
// *************************************************************************
#include <cvirte.h>
#include <userint.h>
#include "S700K.h"
#include "DAQDefine.h"
#include <ansi_c.h>
#include "..\Include\Global.h"
#include "toolbox.h"

//------------------------------------------------------------------------------------------------
// 定义全局变量
//------------------------------------------------------------------------------------------------
extern int              g_plDAQMain;
extern PT_Record        g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_DAQSystemData g_DAQSystemData;
extern PT_Device        g_Device;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// 转辙机Load1测量，如果转辙机在规定的时间内不能完成动作就返回错误
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
DWORD __stdcall S700K_MeasureLoad1_A( LPT_Device pDevice, LPT_Record pData )
{
	double   dfTicksS = 0;
	double   dfActionTime;
	double   dfDistanceS = 0;
	double   dfDistance;
	double   dfTicks;
	DWORD    dwTicksA;
	DWORD    dwTicksError;
	BOOL     bOk = FALSE;
	DWORD    dwRetCode = 0;
	double   dfIa = 0.0, dfIb = 0.0, dfIc = 0.0;
	DWORD    dwCount = 0;
	BOOL     bStart = 0;
	DWORD    dwTimeout = 7000;
	double   dfStroke;  // 当前位移，减去起始点才是动程。
	double   dfMeasureStroke; // 本机实测动程。
	double   dfForceCount = 0.0;
	double   dfAOForce;
	double   dfDelta, dfDiff;
	double   dfSpeed;
	short    usSkiped = 0;
	short    usError = 0;
	double   dfRatedForce = 0.0;
	double   dfHalfStroke;
	double   dfMinLoad2Force;

	// 如果要求停止测试，返回
	if (g_DAQSystemData.usTerminate){
		INFO1("--------------------负载1，方向A测试，被用户终止--------------------");
		return -1;
	}
	INFO1("--------------------负载1，方向A测试--------------------");
	// 我们只在动程过半后进行测量数据处理
	// dfHalfStroke = g_Device.Standard.fStroke / 2;
	// dfHalfStroke = g_Device.Standard.fStroke * 0.7; // 
	// dfHalfStroke += 10.0;
	// 取实际测量到的动程而不是标准动程。这是公司没有那么多型号的转辙机。
	// 用不同动程的转辙机模拟	
	// 实测动程
	dfMeasureStroke = ( pData->ptMeasureDataA.ptCheckData.dfInterval + pData->ptMeasureDataB.ptCheckData.dfInterval ) / 2.0;
	// 测量起始点				  
	dfHalfStroke = 0.7 * dfMeasureStroke; 
	INFO1("实测动程:%f,采样起始动程:%f",dfMeasureStroke,dfHalfStroke);


	// 根据转辙机动作时间调整超时值
	if (g_Device.Standard.fLoad1_TravelTime > 0)
		dwTimeout = g_Device.Standard.fLoad1_TravelTime * 1000 + 1000;
	INFO1("0 动作时间调整超时值:%lu(s)",dwTimeout);

#if 0	
	// 选取A向和B向Load2力中的最小值
	dfMinLoad2Force = (g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce < g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce)
					  ? g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce : g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce;

	// 设定为调整目标力
	dfRatedForce = dfMinLoad2Force;
	INFO1("0.1 设定调整目标阻力(修正前):%f(KN)",dfRatedForce);

	// 修正调整目标力
	if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 0.6)
		dfRatedForce -= 0.4;
	else if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 1.0)
		dfRatedForce -= 0.6;
	else
		dfRatedForce -= 0.6;
	INFO1("0.1 设定调整目标阻力(修正1后):%f(KN)",dfRatedForce);

	// 修正调整目标力，不能比Load1额定力小
	if (dfRatedForce < g_Device.Standard.fLoad1_OperateForce + 0.05)
		dfRatedForce = g_Device.Standard.fLoad1_OperateForce;

	INFO1("0.1 设定调整目标阻力(修正2后):%f(KN)",dfRatedForce);
#else
	dfRatedForce = g_Device.Standard.fLoad1_OperateForce + 0.25;
	INFO1("0.1 设定目标阻力为标准动作力+0.25:%f(KN)",dfRatedForce);	
#endif
	// 取得换向阀初始控制值
	g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad1_A2B_AVoltage;
	g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad1_A2B_BVoltage;
	
	// 调整测试台到初始状态
	//g_DAQSystemData.fAOAForce = 1.0;
	dfAOForce = g_DAQSystemData.fAOBForce;
	DAQ_SetInForce (1.0);
	DAQ_SetOutForce (1.0);

	//g_DAQSystemData.fAOBForce = 1.0;

	// 关闭换向阀
	//DAQ_SetTotalValve (0);
	DAQ_SetInValve (0);

	DAQ_Delay (1000);

	// 打开换向阀，转辙机右移.(缩回)
	//DAQ_SetTotalValve (1);
	DAQ_Force2TotalValue(dfRatedForce);// 按负载力要求，开关总阀切换不同的负载力段。	
	DAQ_OutControl (1);
	DAQ_SetOutValve (1);

	// 复位位移
	DAQ_ResetStroke ();
	// 读取位移初始值
	dfStroke = DAQ_ReadStroke ();
	// 起始时间
	dwTicksError = GetTickCount ();
	dwTicksA = GetTickCount ();
	// 复位最大力
	g_DAQSystemData.fMaxForce = 0.0;

	int delayCnt = 0;
	while( 1 )
	{
		// 延时
		DAQ_Delay(50);
		delayCnt ++;

		// 如果到位，跳出
		if (DAQ_ReadRight ())
		{
			INFO1("--------到位，退出while循环--------");			
			break;
		}
		// 采集数据
		DAQ_CheckMeasure ();
		// 如果超时，返回错误
		if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
		{
			if (usError == 1)
			{
				S700K_ErrorHandle (pDevice, pData);
				INFO1("--------超时，退出while循环--------");
				return -1;
			}
			else
			{
				S700K_UnloadHandle (pDevice, pData);
				usError = 1;
				dwTicksError = GetTickCount ();
			}
		}

		// 转辙机启动时，逐步提高换向阀开度，防止转辙机卡死
		if ((fabs (DAQ_ReadStroke () - dfStroke) < 10) && (bStart == FALSE))
		{
#if 0			
			g_DAQSystemData.fAOBForce += (dfAOForce * 0.7 - 1.0) / 5.0;
			if ( g_DAQSystemData.fAOBForce > dfAOForce * 0.7)
				g_DAQSystemData.fAOBForce = dfAOForce * 0.7;
			DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
#endif			
			continue;
		}
		else if (bStart == FALSE)
		{
			g_DAQSystemData.fAOBForce = dfAOForce;
			DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
			bStart = TRUE;
			dfDistanceS = DAQ_ReadStroke ();
			dfTicksS = GetTickCount ();
			continue;
		}
#if defined(KaZu)		
		if (usSkiped == 1)
			continue;
#endif
		// 读入当前位移，计算速度
		dfDistance = DAQ_ReadStroke ();
		dfTicks = GetTickCount ();
		if ((dfTicks - dfTicksS) == 0)
		{
			dfSpeed = fabs (dfDistance - dfDistanceS) * 1000.0;
		}
		else
		{
			dfSpeed = fabs (dfDistance - dfDistanceS) * 1000.0 / (dfTicks - dfTicksS);
		}
		dfTicksS = dfTicks;
		dfDistanceS = dfDistance;
#if defined(KaZu)
		/* 没有延时，直接判断速度<2.5mm/s为卡阻，现场发现在动程为20mm左右的时候，会误判卡阻。
			实际上并非转辙机受巨大阻力卡阻。所以去掉这段代码。
		 	这段代码想真正使用，1：降低速度判断标准为<0.5mm,2:添加延时。
		*/		
		// 当速度比较低时，并保持一定的时间后认为转辙机卡阻，并开始测量参数
		// 完成测量后故障跳出
		if ((dfSpeed < 2.5) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->Standard.fStroke))
		{
			// 如果没有平均值，读入最大值，保证有测量数据
			if (dfForceCount == 0.0)
			{
				dfForceCount += FAI_FindMaxForce();
				dfIa += g_DAQData.Data.dfIa;
				dfIb += g_DAQData.Data.dfIb;
				dfIc += g_DAQData.Data.dfIc;
				dwCount ++;
				// 设置显示值
				pData->ptMeasureDataA.ptLoad1Data.dfForce = dfForceCount / dwCount;
				pData->ptMeasureDataA.ptLoad1Data.dfIa = dfIa / dwCount;
				pData->ptMeasureDataA.ptLoad1Data.dfIb = dfIb / dwCount;
				pData->ptMeasureDataA.ptLoad1Data.dfIc = dfIc / dwCount;
			}
			INFO1("6.3 卡阻,次数：%lu,累计堵转力:%f KN,A相电流:%f A,B相电流:%f A,C相电流:%f A",dwCount,dfForceCount,dfIa,dfIb,dfIc);
			INFO1("6.3 卡阻,平均值        堵转力:%f KN,A相电流:%f A,B相电流:%f A,C相电流:%f A",
				  pData->ptMeasureDataA.ptLoad1Data.dfForce,
				  pData->ptMeasureDataA.ptLoad1Data.dfIa,
				  pData->ptMeasureDataA.ptLoad1Data.dfIb,
				  pData->ptMeasureDataA.ptLoad1Data.dfIc);
			// 卡阻测量结束
			DAQ_Delay(1000);
			DAQ_SetOutForce (1.0);
			DAQ_SetInForce (1.0);
			//DAQ_SetTotalValve (0);
			DAQ_SetOutValve (0);
			DAQ_SetInValve (0);
			usSkiped = 1;
		}
#endif		

		// 在特定的动程范围内计算参数的平均值，作为无法卡阻时的测量结果
		dfDistance = DAQ_ReadStroke ();
		//if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 10) < pDevice->Standard.fStroke))
		if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 10) < dfMeasureStroke))
		{
			// 累加测量值
			dwCount ++;
			dfForceCount += DAQ_ReadForce ();
			dfIa += g_DAQData.Data.dfIa;
			dfIb += g_DAQData.Data.dfIb;
			dfIc += g_DAQData.Data.dfIc;

			// 设置显示值
			pData->ptMeasureDataA.ptLoad1Data.dfForce = dfForceCount / dwCount;
			pData->ptMeasureDataA.ptLoad1Data.dfIa = dfIa / dwCount;
			pData->ptMeasureDataA.ptLoad1Data.dfIb = dfIb / dwCount;
			pData->ptMeasureDataA.ptLoad1Data.dfIc = dfIc / dwCount;
		}
		//INFO1(" 当前动程:%f(mm)",fabs (dfDistance - dfStroke));
		// 下列参数记录到文件。动程，当前力，目标力，比例阀A电压，比例阀B电压。
		TestPara2Log( fabs (dfDistance - dfStroke),// 动程
			  DAQ_ReadForce (),dfRatedForce,// 当前力,目标力
			  g_DAQSystemData.fAOAForce,//比例阀A电压
			  g_DAQSystemData.fAOBForce //比例阀B电压
		);		
		// 计算测量力和调节目标力
		if (fabs (DAQ_ReadStroke () - dfStroke) < dfHalfStroke){ // 动程的前半力太小，不能作为比例阀调节的依据。
			//INFO1("动程前半段，不调节比例阀开度。比例阀A电压:%f(V),比例阀B电压:%f(V)",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
			continue;
		}		
		dfDiff = DAQ_ReadForce () - dfRatedForce;
		//INFO1(" 当前力:%f(KN)，目标力%f:(KN)",DAQ_ReadForce (),dfRatedForce);
		// 分档调节比例阀开度
		if (fabs (dfDiff) < 0.08)
			dfDelta = 0.005;
		else if (fabs (dfDiff) < 0.1)
			dfDelta = 0.01;
		else if (fabs (dfDiff) < 0.15)
			dfDelta = 0.02;
		else if (fabs (dfDiff) < 0.2)
			dfDelta = 0.025;
		else if (fabs (dfDiff) < 0.3)
			dfDelta = 0.03;
		else if (fabs (dfDiff) < 0.4)
			dfDelta = 0.04;
		else
			dfDelta = 0.04;
		//INFO1(" 调节量:%f(V),加入调节量之前比例阀开度:%f(V)",dfDelta,g_DAQSystemData.fAOBForce);

		// 计算比例阀开度
		if (dfDiff > 0.0){
			g_DAQSystemData.fAOBForce -= dfDelta;
			g_DAQSystemData.fAOAForce -= dfDelta;
		}else{
			g_DAQSystemData.fAOBForce += dfDelta;
			g_DAQSystemData.fAOAForce += dfDelta;			
		}

		//INFO1("  加入调节量之后比例阀开度:%f(V)",g_DAQSystemData.fAOBForce);

		// 防止过调，限制调节范围
		if (g_DAQSystemData.fAOBForce - dfAOForce > 1.0 )
			g_DAQSystemData.fAOBForce = dfAOForce + 1.0;
		if (g_DAQSystemData.fAOBForce - dfAOForce < -1.0 )
			g_DAQSystemData.fAOBForce = dfAOForce - 1.0;
		if (g_DAQSystemData.fAOBForce < 0.0 )
			g_DAQSystemData.fAOBForce = 0;

		if (g_DAQSystemData.fAOAForce - dfAOForce > 1.0 )
			g_DAQSystemData.fAOAForce = dfAOForce + 1.0;
		if (g_DAQSystemData.fAOAForce - dfAOForce < -1.0 )
			g_DAQSystemData.fAOAForce = dfAOForce - 1.0;
		if (g_DAQSystemData.fAOAForce < 0.0 )
			g_DAQSystemData.fAOAForce = 0;		

		//INFO1("----end---- 限制调节范围后比例阀开度:%f(V)",g_DAQSystemData.fAOBForce);
		// 调节比例阀开度
		if(DAQ_GetTotalValue()){ // 总阀打开，使用两个比例阀
		}else{// 总阀关闭,一个为0V，只用另外一个比例阀。
			g_DAQSystemData.fAOAForce = 0;
		}
		DAQ_SetInForce (g_DAQSystemData.fAOAForce);	//比例阀A电压	
		DAQ_SetOutForce (g_DAQSystemData.fAOBForce);//比例阀B电压				
	}

	// 计算动作时间
	
#if 0	
	dfActionTime = GetTickCount( ) - dwTicksA;
#else
	dfActionTime = DAQAIReadTravelTime(DIRECTION_A);// 方向A
#endif	
	// 防止除零错误
	if ( dwCount == 0 )dwCount = 1;
	// 计算平均值
	dfForceCount /= dwCount;
	dfIa /= dwCount;
	dfIb /= dwCount;
	dfIc /= dwCount;

	// 修正测量值
#if 0
	if ((g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState == 2) && (usSkiped != 1))
	{

		// 调整力，不能大于最大力
		if (dfForceCount > g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce)
			dfForceCount = g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce;

		// 如果最大力大于Load1额定力同时Load1测量力小于Load1额定力时
		if ((g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce > g_Device.Standard.fLoad1_OperateForce)
				&& (dfForceCount < g_Device.Standard.fLoad1_OperateForce))
		{
			// 如果差值小于0.1KN时调节为正常值
			if ((g_Device.Standard.fLoad1_OperateForce - dfForceCount) < 0.1)
				dfForceCount = g_Device.Standard.fLoad1_OperateForce + Random(0.0, 0.05);
		}
	}
#endif
	// 设置测量结果
	pData->ptMeasureDataA.ptLoad1Data.dfIa = dfIa;
	pData->ptMeasureDataA.ptLoad1Data.dfIb = dfIb;
	pData->ptMeasureDataA.ptLoad1Data.dfIc = dfIc;
	pData->ptMeasureDataA.ptLoad1Data.dfForce = dfForceCount;
	pData->ptMeasureDataA.ptLoad1Data.dfActionTime = dfActionTime/ 1000.0;
	INFO1("  A相电流:%f(A),B相电流:%f(A),C相电流:%f(A),动作力:%f(KN),动作时间:%f(s)",
		  dfIa,dfIb,dfIc,dfForceCount,
		  pData->ptMeasureDataA.ptLoad1Data.dfActionTime
		 );
#if 0
	if (usSkiped == 1)
		pData->ptMeasureDataA.ptLoad1Data.dfActionTime = (dfActionTime-50*delayCnt-1000) / 1000.0;
	else
		pData->ptMeasureDataA.ptLoad1Data.dfActionTime = (dfActionTime-50*delayCnt) / 1000.0;
#endif
	// 复位控制
	DAQ_SetOutForce( 1.0 );
	DAQ_SetInForce( 1.0 );
	DAQ_InControl( 0 );
	DAQ_OutControl( 0 );
	DAQ_SetTotalValve( 1 );
	DAQ_SetOutValve( 0 );
	DAQ_SetInValve( 0 );

	// 显示测量值
	SetCtrlVal( g_plDAQMain, DAQMAIN_NG_F_1_1, pData->ptMeasureDataA.ptLoad1Data.dfForce );
	SetCtrlVal( g_plDAQMain, DAQMAIN_NG_T_1_1, pData->ptMeasureDataA.ptLoad1Data.dfActionTime );

	return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// 转辙机Load1测量，如果转辙机在规定的时间内不能完成动作就返回错误
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
DWORD __stdcall S700K_MeasureLoad1_B( LPT_Device pDevice, LPT_Record pData )
{
	double   dfTicksS = 0;
	double   dfActionTime;
	double   dfDistanceS = 0;
	double   dfDistance;
	double   dfTicks;
	DWORD    dwTicksA;
	DWORD    dwTicksError;
	BOOL     bOk = FALSE;
	DWORD    dwRetCode = 0;
	double   dfIa = 0.0, dfIb = 0.0, dfIc = 0.0;
	DWORD    dwCount = 0;
	BOOL     bStart = 0;
	DWORD    dwTimeout = 7000;
	double   dfStroke;  // 当前位移，减去起始点才是动程。
	double   dfMeasureStroke; // 本机实测动程。
	double   dfForceCount = 0.0;
	double   dfAOForce;
	double   dfDelta, dfDiff;
	double   dfSpeed;
	short    usSkiped = 0;
	short    usError = 0;
	double   dfRatedForce = 0.0;
	double   dfHalfStroke;
	double   dfMinLoad2Force;

	// 如果要求停止测试，返回
	if (g_DAQSystemData.usTerminate)
	{
		INFO1("--------------------负载1，方向B测试，被用户终止--------------------");
		return -1;
	}
	INFO1("--------------------负载1，方向B测试--------------------");
	// 我们只在动程过半后进行测量数据处理
	// dfHalfStroke = g_Device.Standard.fStroke / 2;
	// dfHalfStroke = g_Device.Standard.fStroke * 0.7;
	// dfHalfStroke += 10.0;
	// 实测动程
	dfMeasureStroke = ( pData->ptMeasureDataA.ptCheckData.dfInterval + pData->ptMeasureDataB.ptCheckData.dfInterval ) / 2.0;
	// 测量起始点				  
	dfHalfStroke = 0.7 * dfMeasureStroke; 
	INFO1("实测动程:%f,采样起始动程:%f",dfMeasureStroke,dfHalfStroke);
	
	// 根据转辙机动作时间调整超时值
	if (g_Device.Standard.fLoad1_TravelTime > 0)
		dwTimeout = g_Device.Standard.fLoad1_TravelTime * 1000 + 1000;
	INFO1("0 动作时间调整超时值:%lu(s)",dwTimeout);
#if 0
	// 选取A向和B向Load2力中的最小值
	dfMinLoad2Force = (g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce < g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce)
					  ? g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce : g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce;

	// 设定为调整目标力
	dfRatedForce = dfMinLoad2Force;
	INFO1("0.1 设定调整目标阻力(修正前):%f(KN)",dfRatedForce);

	// 修正调整目标力
	if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 0.6)
		dfRatedForce -= 0.4;
	else if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 1.0)
		dfRatedForce -= 0.6;
	else
		dfRatedForce -= 0.6;
	INFO1("0.1 设定调整目标阻力(修正1后):%f(KN)",dfRatedForce);

	// 修正调整目标力，不能比Load1额定力小
	if (dfRatedForce < g_Device.Standard.fLoad1_OperateForce + 0.05)
		dfRatedForce = g_Device.Standard.fLoad1_OperateForce ;
	INFO1("0.1 设定调整目标阻力(修正2后):%f(KN)",dfRatedForce);
	
#else
	dfRatedForce = g_Device.Standard.fLoad1_OperateForce + 0.25 ;
	INFO1("0.1 设定目标阻力为标准动作力+0.25:%f(KN)",dfRatedForce);
#endif
	// 取得换向阀初始控制值
	g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad1_B2A_AVoltage;
	g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad1_B2A_BVoltage;

	// 调整测试台到初始状态
	//g_DAQSystemData.fAOBForce = 1.0;
	dfAOForce = g_DAQSystemData.fAOAForce;
	DAQ_SetOutForce (1.0);
	DAQ_SetInForce (1.0);

	// 关闭换向阀
	DAQ_SetOutValve (0);

	DAQ_Delay (1000);

	//g_DAQSystemData.fAOAForce = 1.0;
	// 打开换向阀，转辙机左移
	//DAQ_SetTotalValve (1);
	DAQ_Force2TotalValue(dfRatedForce);// 按负载力要求，开关总阀切换不同的负载力段。
	
	DAQ_InControl( 1 );  // 转辙机缩回
	DAQ_SetInValve (1);

	// 复位位移
	DAQ_ResetStroke ();
	// 读取位移初始值
	dfStroke = DAQ_ReadStroke ();
	// 起始时间
	dwTicksError = GetTickCount ();
	dwTicksA = GetTickCount ();
	// 复位最大力
	g_DAQSystemData.fMaxForce = 0.0;

	int delayCnt = 0;
	while( 1 )
	{
		// 延时
		DAQ_Delay(50);
		delayCnt ++;

		// 如果到位，跳出
		if (DAQ_ReadLeft ())
		{
			INFO1("--------到位，退出while循环--------");
			break;
		}
		// 采集数据
		DAQ_CheckMeasure ();
		// 如果超时，返回错误
		if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
		{
			if (usError == 1)
			{
				S700K_ErrorHandle (pDevice, pData);
				INFO1("--------超时，退出while循环--------");
				return -1;
			}
			else
			{
				S700K_UnloadHandle (pDevice, pData);
				usError = 1;
				dwTicksError = GetTickCount ();
			}
		}

		// 转辙机启动时，逐步提高换向阀开度，防止转辙机卡死
		if ((fabs (DAQ_ReadStroke () - dfStroke) < 10) && (bStart == FALSE))
		{
#if 0			
			g_DAQSystemData.fAOAForce += (dfAOForce * 0.7 - 1.0) / 10.0;
			if ( g_DAQSystemData.fAOAForce > dfAOForce * 0.7)
				g_DAQSystemData.fAOAForce = dfAOForce * 0.7;
#endif			
			DAQ_SetInForce (g_DAQSystemData.fAOAForce);
			continue;
		}
		else if (bStart == FALSE)
		{
			g_DAQSystemData.fAOAForce = dfAOForce;
			DAQ_SetInForce (g_DAQSystemData.fAOAForce);
			bStart = TRUE;
			dfDistanceS = DAQ_ReadStroke ();
			dfTicksS = GetTickCount ();
			continue;
		}
#if defined(KaZu)		
		if (usSkiped == 1)
			continue;
#endif
		// 读入当前位移，计算速度
		dfDistance = DAQ_ReadStroke ();
		dfTicks = GetTickCount ();
		if ((dfTicks - dfTicksS) == 0)
		{
			dfSpeed = fabs (dfDistance - dfDistanceS) * 1000.0;
		}
		else
		{
			dfSpeed = fabs (dfDistance - dfDistanceS) * 1000.0 / (dfTicks - dfTicksS);
		}
		dfTicksS = dfTicks;
		dfDistanceS = dfDistance;
#if defined(KaZu)  
		/* 没有延时，直接判断速度<2.5mm/s为卡阻，现场发现在动程为20mm左右的时候，会误判卡阻。
			实际上并非转辙机受巨大阻力卡阻。所以去掉这段代码。
		 	这段代码想真正使用，1：降低速度判断标准为<0.5mm,2:添加延时。
		*/
		
		// 当速度比较低时，并保持一定的时间后认为转辙机卡阻，并开始测量参数
		// 完成测量后跳出
		if ((dfSpeed < 2.5) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->Standard.fStroke))
		{
			// 如果没有平均值，读入最大值，保证有测量数据
			if (dfForceCount == 0.0)
			{
				dfForceCount += FAI_FindMaxForce();
				dfIa += g_DAQData.Data.dfIa;
				dfIb += g_DAQData.Data.dfIb;
				dfIc += g_DAQData.Data.dfIc;
				dwCount ++;
				// 设置显示值
				pData->ptMeasureDataB.ptLoad1Data.dfForce = dfForceCount / dwCount;
				pData->ptMeasureDataB.ptLoad1Data.dfIa = dfIa / dwCount;
				pData->ptMeasureDataB.ptLoad1Data.dfIb = dfIb / dwCount;
				pData->ptMeasureDataB.ptLoad1Data.dfIc = dfIc / dwCount;
			}
			INFO1("6.3 卡阻,次数：%lu,累计堵转力:%f KN,A相电流:%f A,B相电流:%f A,C相电流:%f A",dwCount,dfForceCount,dfIa,dfIb,dfIc);
			INFO1("6.3 卡阻,平均值        堵转力:%f KN,A相电流:%f A,B相电流:%f A,C相电流:%f A",
				  pData->ptMeasureDataB.ptLoad1Data.dfForce,
				  pData->ptMeasureDataB.ptLoad1Data.dfIa,
				  pData->ptMeasureDataB.ptLoad1Data.dfIb,
				  pData->ptMeasureDataB.ptLoad1Data.dfIc);
			// 卡阻测量结束
			DAQ_Delay(1000);
			DAQ_SetOutForce( 1.0 );
			DAQ_SetInForce( 1.0 );
			//DAQ_SetTotalValve( 0 );
			DAQ_SetOutValve( 0 );
			DAQ_SetInValve( 0 );
			usSkiped = 1;
		}
#endif
		// 在特定的动程范围内计算参数的平均值，作为无法卡阻时的测量结果
		dfDistance = DAQ_ReadStroke ();
		//if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 10) < pDevice->Standard.fStroke))
		if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 10) < dfMeasureStroke))
		{
			// 累加测量值
			dwCount ++;
			dfForceCount += DAQ_ReadForce ();
			dfIa += g_DAQData.Data.dfIa;
			dfIb += g_DAQData.Data.dfIb;
			dfIc += g_DAQData.Data.dfIc;

			// 设置显示值
			pData->ptMeasureDataB.ptLoad1Data.dfForce = dfForceCount / dwCount;
			pData->ptMeasureDataB.ptLoad1Data.dfIa = dfIa / dwCount;
			pData->ptMeasureDataB.ptLoad1Data.dfIb = dfIb / dwCount;
			pData->ptMeasureDataB.ptLoad1Data.dfIc = dfIc / dwCount;
		}
		//INFO1(" 当前动程:%f(mm)",fabs (dfDistance - dfStroke));
		// 下列参数记录到文件。动程，当前力，目标力，比例阀A电压，比例阀B电压。
		TestPara2Log( fabs (dfDistance - dfStroke),// 动程
			  DAQ_ReadForce (),dfRatedForce,// 当前力,目标力
			  g_DAQSystemData.fAOAForce,//比例阀A电压
			  g_DAQSystemData.fAOBForce //比例阀B电压
		);		
		// 计算测量力和调节目标力
		if (fabs (DAQ_ReadStroke () - dfStroke) < dfHalfStroke){ // 动程的前半力太小，不能作为比例阀调节的依据。
			//INFO1("    动程前半段，不调节比例阀开度。比例阀A电压:%f(V),比例阀B电压:%f(V)",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
			continue;
		}
		dfDiff = DAQ_ReadForce () - dfRatedForce;
		//INFO1(" 当前力:%f(KN)，目标力:%f(KN)",DAQ_ReadForce (),dfRatedForce);
		// 分档调节比例阀开度
		if (fabs (dfDiff) < 0.08)
			dfDelta = 0.005;
		else if (fabs (dfDiff) < 0.1)
			dfDelta = 0.01;
		else if (fabs (dfDiff) < 0.15)
			dfDelta = 0.02;
		else if (fabs (dfDiff) < 0.2)
			dfDelta = 0.025;
		else if (fabs (dfDiff) < 0.3)
			dfDelta = 0.03;
		else if (fabs (dfDiff) < 0.4)
			dfDelta = 0.04;
		else
			dfDelta = 0.04;
		//INFO1(" 调节量:%f(V),加入调节量之前比例阀开度:%f(V)",dfDelta,g_DAQSystemData.fAOAForce);

		// 计算比例阀开度
		if (dfDiff > 0.0){
			g_DAQSystemData.fAOAForce -= dfDelta;
			g_DAQSystemData.fAOBForce -= dfDelta;
		}else{
			g_DAQSystemData.fAOAForce += dfDelta;
			g_DAQSystemData.fAOBForce += dfDelta;
		}

		// 防止过调，限制调节范围
		if (g_DAQSystemData.fAOAForce - dfAOForce > 1.6 )
			g_DAQSystemData.fAOAForce = dfAOForce + 1.6;
		if (g_DAQSystemData.fAOAForce - dfAOForce < -1.6  )
			g_DAQSystemData.fAOAForce = dfAOForce - 1.6;
		if(g_DAQSystemData.fAOAForce < 0)
			g_DAQSystemData.fAOAForce = 0;
		
		if (g_DAQSystemData.fAOBForce - dfAOForce > 1.6 )
			g_DAQSystemData.fAOBForce = dfAOForce + 1.6;
		if (g_DAQSystemData.fAOBForce - dfAOForce < -1.6  )
			g_DAQSystemData.fAOBForce = dfAOForce - 1.6;
		if(g_DAQSystemData.fAOBForce < 0)
			g_DAQSystemData.fAOBForce = 0;		
		//INFO1("----end---- 限制调节范围后比例阀开度:%f(V)",g_DAQSystemData.fAOAForce);

		// 调节比例阀开度
		if(DAQ_GetTotalValue()){ // 总阀打开，使用两个比例阀
		}else{// 总阀关闭,一个为0V，只用另外一个比例阀。
			g_DAQSystemData.fAOBForce = 0;
		}
		DAQ_SetInForce (g_DAQSystemData.fAOAForce);	//比例阀A电压	
		DAQ_SetOutForce (g_DAQSystemData.fAOBForce);//比例阀B电压				
		//DAQ_Delay (50);
	}

	// 计算动作时间
#if 0	
	dfActionTime = GetTickCount( ) - dwTicksA;
#else
	dfActionTime = DAQAIReadTravelTime(DIRECTION_B);// 方向B
#endif
	// 防止除零错误
	if ( dwCount == 0 )dwCount = 1;
	// 计算平均值
	dfForceCount /= dwCount;
	dfIa /= dwCount;
	dfIb /= dwCount;
	dfIc /= dwCount;

	// 修正测量值
#if 0
	if ((g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState == 2) && (usSkiped != 1))
	{
		// 调整最大力，不能大于最大力
		if (dfForceCount > g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce)
			dfForceCount = g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce;

		// 如果最大力大于Load1额定力同时Load1测量力小于Load1额定力时
		if ((g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce > g_Device.Standard.fLoad1_OperateForce)
				&& (dfForceCount < g_Device.Standard.fLoad1_OperateForce))
		{
			// 如果差值小于0.1KN时调节为正常值
			if ((g_Device.Standard.fLoad1_OperateForce - dfForceCount) < 0.1)
				dfForceCount = g_Device.Standard.fLoad1_OperateForce + Random(0.0, 0.05);
		}
	}
#endif
	// 设置测量结果
	pData->ptMeasureDataB.ptLoad1Data.dfIa = dfIa;
	pData->ptMeasureDataB.ptLoad1Data.dfIb = dfIb;
	pData->ptMeasureDataB.ptLoad1Data.dfIc = dfIc;
	pData->ptMeasureDataB.ptLoad1Data.dfForce = dfForceCount;
	pData->ptMeasureDataB.ptLoad1Data.dfActionTime = dfActionTime/ 1000.0;

	INFO1("  A相电流:%f(A),B相电流:%f(A),C相电流:%f(A),动作力:%f(KN),动作时间:%f(s)",
		  dfIa,dfIb,dfIc,dfForceCount,
		  pData->ptMeasureDataB.ptLoad1Data.dfActionTime
		 );

#if 0
	if (usSkiped == 1)
		pData->ptMeasureDataB.ptLoad1Data.dfActionTime = (dfActionTime-50*delayCnt-1000) / 1000.0;
	else
		pData->ptMeasureDataB.ptLoad1Data.dfActionTime = (dfActionTime-50*delayCnt) / 1000.0;
#endif
	// 复位控制
	DAQ_SetOutForce( 1.0 );
	DAQ_SetInForce( 1.0 );
	DAQ_InControl( 0 );
	DAQ_OutControl( 0 );
	DAQ_SetTotalValve( 1 );
	DAQ_SetOutValve( 0 );
	DAQ_SetInValve( 0 );

	// 显示测量值
	SetCtrlVal( g_plDAQMain, DAQMAIN_NG_F_1_2, pData->ptMeasureDataB.ptLoad1Data.dfForce );
	SetCtrlVal( g_plDAQMain, DAQMAIN_NG_T_1_2, pData->ptMeasureDataB.ptLoad1Data.dfActionTime );

	return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// 转辙机Load1测量，如果转辙机在规定的时间内不能完成动作就返回错误
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
int __stdcall S700K_MeasureLoad1( LPT_Device pDevice, LPT_Record pData )
{
	// 如果要求停止测试，返回
	if (g_DAQSystemData.usTerminate)
		return -1;

	// 延时
	DAQ_Delay (1000);
	DAQ_Delay (1000);

	// 断开模拟电阻
	DAQ_SimulateTrack (0);

	// 设置步数
	g_S700KData.Control.usStep = 5;
	// B向测量
	if (S700K_MeasureLoad1_B (pDevice, pData) == -1)
		return -1;

	// 延时
	DAQ_Delay (1000);
	DAQ_Delay (1000);

	// 设置步数
	g_S700KData.Control.usStep = 6;
	// A向测量
	if (S700K_MeasureLoad1_A (pDevice, pData) == -1)
		return -1;

	return 0;
}

//------------------------------------------------------------------------------------------------

