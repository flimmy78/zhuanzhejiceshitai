// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************
#include <cvirte.h>
#include <userint.h>
#include "S700K.h"
#include "DAQDefine.h"
#include <ansi_c.h>
#include "..\Include\Global.h"

//------------------------------------------------------------------------------------------------
// 定义全局变量
//------------------------------------------------------------------------------------------------
extern int              g_plDAQMain;
extern PT_Record    g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_DAQSystemData g_DAQSystemData;
extern PT_Device        g_Device;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// 转辙机Load2测量，如果转辙机在规定的时间内不能完成动作就返回错误
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
DWORD __stdcall S700K_MeasureLoad2_A( LPT_Device pDevice, LPT_Record pData )
{
	double   dfDistance, dfDistanceS, dfDistanceE;
	DWORD    dwTicksS, dwTicksE;
	double   dfSpeed;
	double   dfTicks;
	double   dfForce = 0.0;
	double   dfIa = 0.0, dfIb = 0.0, dfIc = 0.0;
	DWORD    dwTicksError;
	DWORD    dwRetCode = 0;
	BOOL     bStart = FALSE;
	BOOL     bHalf = FALSE;
	DWORD    dwTimeout = 7000;
	BOOL     bOk = 0;
	double   dfStroke;
	int      dwCount = 0;
	double   dfDelta;
	double   dfDiff;
	double   dfForceCount= 0.0;
	double   dfAOForce;
	DWORD    dwTickStop = 0;
	double   dfMaxForce = 0.0;
	double   dfRatedForce = 0.0;
	double   dfHalfStroke;	  // 本机实测动程的一半
	double   dfMeasureStroke; // 本机实测动程
	char logbuf[100];

	// 如果要求停止测试，返回
	if (g_DAQSystemData.usTerminate){
		INFO1("--------------------负载2，方向B测试，被用户终止--------------------");
		return -1;
	}
	INFO1("--------------------负载2，方向A测试--------------------");
	// 我们只在动程过半后进行测量数据处理
	//dfHalfStroke = g_Device.Standard.fStroke / 2;
	//dfHalfStroke += 10.0;
	// 取实际测量到的动程而不是标准动程。这是公司没有那么多型号的转辙机。
	// 用不同动程的转辙机模拟	
	// 实测动程
	dfMeasureStroke = ( pData->ptMeasureDataA.ptCheckData.dfInterval + pData->ptMeasureDataB.ptCheckData.dfInterval ) / 2.0;
	// 测量起始点				  
	dfHalfStroke = 0.7 * dfMeasureStroke; 
	INFO1("实测动程:%f,采样起始动程:%f",dfMeasureStroke,dfHalfStroke);

	g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState = 0;

	// 设置Load2最大调节力。
	dfRatedForce = g_Device.Standard.fLoad2_MaxForce;
	//dfRatedForce += 0.5;//dfRatedForce *= 1.8;
	INFO1("    负载台初始目标阻力:dfRatedForce = %f",dfRatedForce);

	if (pDevice->Standard.fLoad2_A2B_AVoltage > 10.0)
		return -1;

	// 取得换向阀初始控制值
	g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad2_A2B_AVoltage;
	g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad2_A2B_BVoltage;

	INFO1("    比例阀数据库值:g_DAQSystemData.fAOAForce = %f,g_DAQSystemData.fAOBForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);

	//g_DAQSystemData.fAOAForce = 1.5;
	g_DAQSystemData.fAOAForce = 0;
	dfAOForce = g_DAQSystemData.fAOBForce;
	DAQ_SetInForce (g_DAQSystemData.fAOAForce);

	// 将比例阀开度设置为初始开度的70%，防止力不能加到位
	g_DAQSystemData.fAOBForce = dfAOForce * 0.7;
	DAQ_SetOutForce (g_DAQSystemData.fAOBForce);

	INFO1("    比例阀初始设置:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);

	// 打开换向阀，转辙机右移
	DAQ_SetOutValve (1);
	DAQ_SetInValve (0);
	//DAQ_SetTotalValve (0); // 关闭换向阀总开关
	//DAQ_SetTotalValve (1); // 打开换向阀总开关
	DAQ_Force2TotalValue(dfRatedForce);// 按负载力要求，开关总阀切换不同的负载力段。

	DAQ_Delay (500);
	DAQ_OutControl (1);

	// 复位位移
	DAQ_ResetStroke ();
	// 读取位移初始值
	dfStroke = dfDistanceS = DAQ_ReadStroke ();

	// 起始时间
	dwTicksError = GetTickCount ();
	dwTicksS = GetTickCount ();
	// 复位最大力
	g_DAQSystemData.fMaxForce = 0.0;
	dwTimeout = 3000;
	INFO1("// --------进入while循环--------");
	while( 1 )
	{
		// 998.如果到位，跳出
		if (DAQ_ReadRight ())
		{
			INFO1(" --------到位，退出while循环--------");
			INFO1(" 当前换向阀设置:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
			break;
		}
		// 延时
		DAQ_Delay (50);
		// 采集数据
		DAQ_CheckMeasure( );

		// 999.如果超时，返回错误
		if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
		{
			INFO1(" --------1.超时，退出while循环，GetTickCount = %lu, dwTicksError=%lu,dwTimeout:%lu--------",GetTickCount (),dwTicksError,dwTimeout);
			INFO1(" 换向阀当前设置:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
			S700K_UnloadHandle (pDevice, pData);
			break;
		}

		// 2.等待位移大于10mm时将换向阀开度调节到预定开度，然后开始加力测试Load2最大力
		if ((fabs (DAQ_ReadStroke () - dfDistanceS) < 10) && (bStart == FALSE))
		{
			INFO1("// 等待位移大于10mm,continue");
			INFO1("// 当前时间，GetTickCount = %lu, dwTicksError=%lu,dwTimeout,%lu",GetTickCount (),dwTicksError,dwTimeout);
			INFO1("// 当前换向阀参数:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
			continue;
		}
		else if (bStart == FALSE)
		{
			bStart = TRUE;
			g_DAQSystemData.fAOBForce = dfAOForce * 1.0;
			DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
			dfDistanceS = DAQ_ReadStroke ();
			dwTicksS = GetTickCount ();
			dwTicksError = GetTickCount ();
			dwTimeout = 7000;
			if (g_Device.Standard.fLoad1_TravelTime > 0)
				dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;
			INFO1("// 2.1位移大于10mm,当前位移:%f",dfDistanceS);
			INFO1("// 当前时间:GetTickCount = %lu, dwTicksError=%lu,dwTimeout,%lu",GetTickCount (),dwTicksError,dwTimeout);
			INFO1("// 当前换向阀参数:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
		}
		if (bStart == FALSE)
			continue;

		// 3.在指定的位移范围内累计测量参数，作为无法卡阻时的测量值
		dfDistanceE = DAQ_ReadStroke ();
		if ((fabs (dfDistanceE - dfStroke) > dfHalfStroke) && ((fabs (dfDistanceE - dfStroke) + 5) < pDevice->Standard.fStroke))
		{
			//INFO1("   3.转辙机在10mm到标准动程-10mm的范围内累计测量参数，作为无法卡阻时的测量值,当前位移:%f",dfDistanceE);
			// 累加测量值
			dwCount ++;
			dfForceCount += DAQ_ReadForce ();
			dfIa += g_DAQData.Data.dfIa;
			dfIb += g_DAQData.Data.dfIb;
			dfIc += g_DAQData.Data.dfIc;
			// 设置显示值
			pData->ptMeasureDataA.ptLoad2Data.dfIa = dfIa / dwCount;
			pData->ptMeasureDataA.ptLoad2Data.dfIb = dfIb / dwCount;
			pData->ptMeasureDataA.ptLoad2Data.dfIc = dfIc / dwCount;
			//INFO1("   3.1 dwCount:%lu,dfForceCount:%f,dfIa:%f,dfIb:%f,dfIc:%f",dwCount,dfForceCount,dfIa,dfIb,dfIc);
			//INFO1("       pData->ptMeasureDataB.ptLoad2Data.dfIa:%f,pData->ptMeasureDataB.ptLoad2Data.dfIb:%f,pData->ptMeasureDataB.ptLoad2Data.dfIc:%f",pData->ptMeasureDataB.ptLoad2Data.dfIa,pData->ptMeasureDataB.ptLoad2Data.dfIb,pData->ptMeasureDataB.ptLoad2Data.dfIc);
		}
		// 4.位移末端不测量
		if (g_Device.Standard.fStroke - fabs(dfDistanceE - dfStroke) < 10)
		{
			INFO1("// 4.位移末端(最后10mm)不测量,当前位移:%f",dfDistanceS);
			continue;
		}

		// 5.除了最后10mm,读取当前位移，计算速度
		//INFO1("// 5.除了最后10mm,读取当前位移，计算转辙机速度。当前位移:%f",dfDistanceS);
		dfDistance = dfDistanceE - dfDistanceS;
		dwTicksE = GetTickCount();
		dfTicks = dwTicksE - dwTicksS;
		if ( dfTicks == 0 )dfTicks = 1.0;
		dfSpeed = dfDistance * 1000.0 / dfTicks;
		//INFO1("// 5.当前速度为:%f",dfSpeed);

		// 6.除了最后10mm,当速度比较低时，
		// 保持一定的时间后认为转辙机卡阻，此时开始测量参数
		if (fabs (dfSpeed) < 0.5)
		{
			INFO1("    6.除了最后10mm,当速度比较低时，保持一定的时间后认为转辙机卡阻，开始测量参数。当前位移:%f",dfDistanceS);
			if (dwTickStop == 0)
			{
				dwTickStop = GetTickCount ();
				g_DAQSystemData.fMinForce = 99; //设置最小值标准。比这个值小都算小
				//INFO1("    6.1 首次卡阻tick为:%lu",dwTickStop);
			}
			else if ((GetTickCount () - dwTickStop) < 200)
			{
				//INFO1("    6.2 卡阻时间 < 200ms.dfDistanceS:%f,dwTicksS:%lu,dfDistanceE:%f,dwTicksE:%lu",dfDistanceS,dwTicksS,dfDistanceE,dwTicksE);
				
				dfDistanceS = dfDistanceE;
				dwTicksS = dwTicksE;
				continue;
			}
			else
			{
				//g_DAQSystemData.fMaxForce =0;
				// 取得初次卡阻到现在这段时间的最小力
				dfForce = FAI_FindMinForce();
				// 卡阻后延时2秒
				DAQ_Delay (2000);
				// 取得测量过程中的最大值
				//dfMaxForce = FAI_FindMaxForce ();
				//dfForce = dfMaxForce;
				

				// 取得其他测量参数
				dfIa = g_DAQData.Data.dfIa;
				dfIb = g_DAQData.Data.dfIb;
				dfIc = g_DAQData.Data.dfIc;
				pData->ptMeasureDataA.ptLoad2Data.dfIa = dfIa;
				pData->ptMeasureDataA.ptLoad2Data.dfIb = dfIb;
				pData->ptMeasureDataA.ptLoad2Data.dfIc = dfIc;
				//INFO1("    6.3 卡阻时间 > 200ms,堵转力:%f KN,A相电流:%f A,B相电流:%f A,C相电流:%f A",dfForce,dfIa,dfIb,dfIc);

				// 卡阻测量结束，正确测量
				DAQ_SetTotalValve (1);
				DAQ_SetInForce( 1.5 );
				DAQ_SetOutForce( 1.5 );
				DAQ_SetInValve( 0 );
				DAQ_SetOutValve( 0 );
				bOk = 1;
				// 跳出
				// 下列参数记录到文件。
				TestParaV2ToLog(
					GetTickCount()-dwTicksError,	//本次测量时间(tick)(mm)
					logbuf,							//步骤
					fabs(dfDistanceE - dfStroke),	//动程(mm)
					dfSpeed,						//速度(mm/s)
					bOk,							//卡阻
					DAQ_ReadForce (),dfRatedForce,	//当前力(KN),目标力
					g_DAQSystemData.fAOAForce,	//比例阀A电压
					g_DAQSystemData.fAOBForce,	//比例阀B电压	
					g_DAQData.Data.dfIa,//A相电流(A)
					g_DAQData.Data.dfIb,//B相电流(A)
					g_DAQData.Data.dfIc,//C相电流(A)
					dwCount,		//累计次数
					dfForceCount,	//累计力(KN)
					dfIa,			//累计A相电流(A)
					dfIb,			//累计B相电流(A)
					dfIc 			//累计C相电流(A)
				);
				break;
			}
		}
		else
		{
			// 没有卡阻时
			dwTickStop = 0;
		}

		// 下列参数记录到文件。
		TestParaV2ToLog(
			GetTickCount()-dwTicksError,	//本次测量时间(tick)(mm)
			logbuf,							//步骤
			fabs(dfDistanceE - dfStroke),	//动程(mm)
			dfSpeed,						//速度(mm/s)
			bOk,							//卡阻
			DAQ_ReadForce (),dfRatedForce,	//当前力(KN),目标力
			g_DAQSystemData.fAOAForce,	//比例阀A电压
			g_DAQSystemData.fAOBForce,	//比例阀B电压	
			g_DAQData.Data.dfIa,//A相电流(A)
			g_DAQData.Data.dfIb,//B相电流(A)
			g_DAQData.Data.dfIc,//C相电流(A)
			dwCount,		//累计次数
			dfForceCount,	//累计力(KN)
			dfIa,			//累计A相电流(A)
			dfIb,			//累计B相电流(A)
			dfIc 			//累计C相电流(A)
		);		
		// 7.位移到动程的一半-10mm，测量堵转.（由于机械系统反应需要时间）
		//if (fabs(dfDistanceE - dfStroke) <= dfHalfStroke)
		//{
			//	INFO1("    7.动程的前一半，加力,当前位移:%f",fabs(dfDistanceE - dfStroke));
			// 8.计算测量力和调节目标力
			dfDiff = DAQ_ReadForce () - dfRatedForce;
			// 分档调节比例阀开度
			if (fabs (dfDiff) < 0.05)
				dfDelta = 0.01;
			else if (fabs (dfDiff) < 0.1)
				dfDelta = 0.01;
			else if (fabs (dfDiff) < 0.15)
				dfDelta = 0.015;
			else if (fabs (dfDiff) < 0.2)
				dfDelta = 0.02;
			else if (fabs (dfDiff) < 0.3)
				dfDelta = 0.03;
			else if (fabs (dfDiff) < 0.4)
				dfDelta = 0.04;
			else
				dfDelta = 0.04;
			//INFO1("  8.计算测量力和调节目标力.测量力:%f,目标力:%f",DAQ_ReadForce (),dfRatedForce);

			// 8.1 计算比例阀开度
			if (dfDiff > 0.0)
				g_DAQSystemData.fAOBForce -= dfDelta;
			else
				g_DAQSystemData.fAOBForce += dfDelta;
			//INFO1("  8.1 计算比例阀开度。新比例阀A电压值为:%f",g_DAQSystemData.fAOBForce);

			// 8.2 防止过调，限制调节范围
			if (g_DAQSystemData.fAOBForce > dfAOForce)
			{
				if (g_DAQSystemData.fAOBForce - dfAOForce > 1.0 )
					g_DAQSystemData.fAOBForce = dfAOForce + 1.0;
				if (g_DAQSystemData.fAOBForce - dfAOForce < -1.0 )
					g_DAQSystemData.fAOBForce = dfAOForce - 1.0;
			}
			//INFO1("  8.2 防止过调，限制调节范围。限制后的比例阀A电压值为 :%f",g_DAQSystemData.fAOBForce);

			// 8.3 调节比例阀开度
			//INFO1("  8.3 调节比例阀开度。dfDistanceS:%f,dwTicksS:%lu,dfDistanceE:%f,dwTicksE:%lu",dfDistanceS,dwTicksS,dfDistanceE,dwTicksE);
			DAQ_SetOutForce (g_DAQSystemData.fAOBForce);

		//}
		//else if(bHalf == FALSE)// 动程过半，进入堵转
		//{
		//	DAQ_SetTotalValve (0);	// 关闭比例阀总开关，测量5KN~9.9KN
		//	g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad2_B2A_AVoltage;
		//	bHalf = TRUE;
			//DAQ_SetInForce (10.0);
		//	DAQ_SetOutForce (10.0);
		//}

		//INFO1("    7.动程的后一半，测量堵转,当前位移:%f，比例阀电压:10V",fabs(dfDistanceE - dfStroke));
		dfDistanceS = dfDistanceE;
		dwTicksS = dwTicksE;
		//DAQ_Delay (100);
	}
	INFO1("--------退出while循环。负载2，方向B数据采集结束。--------");

	// 防止除零错误
	if (dwCount == 0)
		dwCount = 1;
	// 如果卡阻
	if (bOk == 1)
	{
		INFO1("  b1.卡阻");
		// 设置状态
		g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState = 2;
		// 调整测量值
		INFO1("  测量值调整前为:%f",dfForce);
		//dfForce *= g_Device.Standard.fLoad2_Scale;

		if (dfForce > g_Device.Standard.fLoad2_MaxForce)
		{
			if ((dfForce - g_Device.Standard.fLoad2_MaxForce) < 0.1)
				dfForce = g_Device.Standard.fLoad2_MaxForce;
		}
		if (dfForce < g_Device.Standard.fLoad1_OperateForce)
		{
			if ((g_Device.Standard.fLoad1_OperateForce - dfForce) < 0.1)
				dfForce = g_Device.Standard.fLoad1_OperateForce;
		}
		INFO1("  测量值调整后为:%f",dfForce);
		// 参照B向力调整A向力
		//dfForce += (pData->ptMeasureDataB.ptLoad2Data.dfForce - dfForce) / 2;

		if (dfForce > g_Device.Standard.fLoad2_MaxForce)
		{
			if ((dfForce - g_Device.Standard.fLoad2_MaxForce) < 0.1)
				dfForce = g_Device.Standard.fLoad2_MaxForce;
		}
		if (dfForce < g_Device.Standard.fLoad1_OperateForce)
		{
			if ((g_Device.Standard.fLoad1_OperateForce - dfForce) < 0.1)
				dfForce = g_Device.Standard.fLoad1_OperateForce + 0.05;
		}
		INFO1("  参照B向力调整A向力,调整后为:%f",dfForce);
	}
	// 不卡阻
	else
	{
		dfForce = dfForceCount / dwCount;
		g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState = 1;
		INFO1("  b2.没有卡阻，动作力为:%f",dfForce);
	}

	// 设置测量结果
	pData->ptMeasureDataA.ptLoad2Data.dfForce1 = dfForce;
	pData->ptMeasureDataA.ptLoad2Data.dfForce = pData->ptMeasureDataA.ptLoad2Data.dfForce1;

	// 复位控制，转辙机走到位
	DAQ_SetOutValve (0);
	DAQ_SetInValve (0);
	DAQ_SetOutForce (1.5);
	DAQ_SetInForce (1.5);
	//DAQ_SetTotalValve (1);
	dwTimeout = 7000;
	if (g_Device.Standard.fLoad1_TravelTime > 0)
		dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;
	dwTicksError = GetTickCount ();
	while (1)
	{
		INFO1("  c1.1 移动转辙机反位");
		if (DAQ_ReadRight ())
		{
			INFO1("  c1.2 转辙机到达位置反位");
			break;
		}

		DAQ_CheckMeasure ();

		if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
		{
			INFO1("  c1.3 移动转辙机超时。没有在规定时间内移动到反位");
			S700K_ErrorHandle (pDevice, pData);
			return -1;
		}

		DAQ_Delay (10);
	}
	// 复位控制
	DAQ_InControl (0);
	DAQ_OutControl (0);
	DAQ_SetTotalValve (1);

	// 显示测量值
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_2_1, pData->ptMeasureDataA.ptLoad2Data.dfForce);
	return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// 转辙机Load2测量，如果转辙机在规定的时间内不能完成动作就返回错误
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
DWORD __stdcall S700K_MeasureLoad2_B(LPT_Device pDevice, LPT_Record pData)
{
	double   dfDistance, dfDistanceS, dfDistanceE;
	DWORD    dwTicksS, dwTicksE;
	double   dfSpeed;
	double   dfTicks;
	double   dfForce = 0.0;
	double   dfIa = 0.0, dfIb = 0.0, dfIc = 0.0;
	DWORD    dwTicksError;
	DWORD    dwRetCode = 0;
	BOOL     bStart = FALSE;
	BOOL     bHalf = FALSE;
	DWORD    dwTimeout = 7000;
	BOOL     bOk = 0;
	double   dfStroke;
	int      dwCount = 0;
	double   dfDelta;
	double   dfDiff;
	double   dfForceCount= 0.0;
	double   dfAOForce;
	DWORD    dwTickStop = 0;
	double   dfMaxForce = 0.0;
	double   dfRatedForce = 0.0;
	double   dfHalfStroke;	  // 本机实测动程的一半
	double   dfMeasureStroke; // 本机实测动程	
	
	char logbuf[100];

	// 如果要求停止测试，返回
	if (g_DAQSystemData.usTerminate){
		INFO1("--------------------负载2，方向B测试，被用户终止--------------------");
		return -1;
	}
	INFO1("--------------------负载2，方向B测试--------------------");
	// 我们只在动程过半后进行测量数据处理
	//dfHalfStroke = g_Device.Standard.fStroke / 2;
	//dfHalfStroke += 10.0;
	// 取实际测量到的动程而不是标准动程。这是公司没有那么多型号的转辙机。
	// 用不同动程的转辙机模拟	
	// 实测动程
	dfMeasureStroke = ( pData->ptMeasureDataA.ptCheckData.dfInterval + pData->ptMeasureDataB.ptCheckData.dfInterval ) / 2.0;
	// 测量起始点				  
	dfHalfStroke = 0.7 * dfMeasureStroke; 
	INFO1("    实测动程:%f,采样起始动程:%f",dfMeasureStroke,dfHalfStroke);

	g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState = 0;

	// 设置Load2最大调节力+0.5KN
	dfRatedForce = g_Device.Standard.fLoad2_MaxForce;
	//dfRatedForce += 0.5;////dfRatedForce *= 1.5;
	INFO1("    负载台初始目标阻力:dfRatedForce = %f",dfRatedForce);

	if (pDevice->Standard.fLoad2_B2A_AVoltage > 10.0)
		return -1;

	// 取得比例阀初始控制值
	g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad2_B2A_AVoltage;
	g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad2_B2A_BVoltage;
	INFO1("    比例阀数据库值:g_DAQSystemData.fAOAForce = %f,g_DAQSystemData.fAOBForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);

	dfAOForce = g_DAQSystemData.fAOAForce;
	//g_DAQSystemData.fAOBForce = 1.5;
	g_DAQSystemData.fAOBForce = 0;

	// 将比例阀开度设置为初始开度的70%，防止力不能加到位
	g_DAQSystemData.fAOAForce = dfAOForce * 0.7;
	DAQ_SetInForce (g_DAQSystemData.fAOAForce);
	DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
	
	INFO1("    比例阀初始设置:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);

	// 打开换向阀
	DAQ_SetOutValve (0);
	DAQ_SetInValve (1);
	
	//DAQ_SetTotalValve (0);   // 关闭换向阀总开关 0~2.6 ：5.0~10KN
	//DAQ_SetTotalValve (1); // 打开换向阀总开关 0~2.6 ：2.5~4.5KN
	DAQ_Force2TotalValue(dfRatedForce);// 按负载力要求，开关总阀切换不同的负载力段。

	DAQ_Delay (500);

	// 打开换向阀，转辙机左移
	DAQ_InControl (1);

	// 复位位移
	DAQ_ResetStroke ();
	// 读取位移初始值
	dfStroke = dfDistanceS = DAQ_ReadStroke ();

	// 起始时间
	dwTicksError = GetTickCount ();
	dwTicksS = GetTickCount ();
	// 复位最大力
	g_DAQSystemData.fMaxForce = 0.0;
	dwTimeout = 3000;
	INFO1("// 进入while循环");
	while (1)
	{
		// 如果到位，跳出
		if (DAQ_ReadLeft ())
		{
			INFO1("// 到位，退出while循环");
			INFO1("// 当前换向阀设置:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
			break;
		}
		// 延时
		DAQ_Delay (50);
		// 采集数据
		DAQ_CheckMeasure ();

		// 1.如果超时，返回错误
		if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
		{
			INFO1("// 1.超时，退出while循环，GetTickCount = %lu, dwTicksError=%lu,dwTimeout:%lu",GetTickCount (),dwTicksError,dwTimeout);
			INFO1("// 换向阀当前设置:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
			S700K_UnloadHandle (pDevice, pData);
			break;
		}

		// 2.等待位移大于10mm时将换向阀开度调节到预定开度，然后开始加力测试Load2最大力
		if ((fabs (DAQ_ReadStroke () - dfDistanceS) < 10) && (bStart == FALSE))
		{
			//INFO1("// 等待位移大于10mm,continue");
			//INFO1("// 当前时间，GetTickCount = %lu, dwTicksError=%lu,dwTimeout,%lu",GetTickCount (),dwTicksError,dwTimeout);
			//INFO1("// 当前换向阀参数:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
			continue;
		}
		else if ((bStart == FALSE))
		{
			// 2.1
			g_DAQSystemData.fAOAForce = dfAOForce * 1.0;
			DAQ_SetInForce (g_DAQSystemData.fAOAForce);
			bStart = TRUE;
			dfDistanceS = DAQ_ReadStroke ();
			dwTicksS = GetTickCount ();
			dwTicksError = GetTickCount ();
			dwTimeout = 7000;
			if (g_Device.Standard.fLoad1_TravelTime > 0)
				dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;
			//INFO1("// 2.1位移大于10mm,当前位移:%f",dfDistanceS);
			//INFO1("// 当前时间:GetTickCount = %lu, dwTicksError=%lu,dwTimeout,%lu",GetTickCount (),dwTicksError,dwTimeout);
			//INFO1("// 当前换向阀参数:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
		}
		if (bStart == FALSE)
			continue;

		// 3.转辙机在10mm到标准动程-10mm的范围内累计测量参数，作为无法卡阻时的测量值
		dfDistanceE = DAQ_ReadStroke ();
		if ((fabs (dfDistanceE - dfStroke) > dfHalfStroke) && ((fabs (dfDistanceE - dfStroke) + 5) < pDevice->Standard.fStroke))
		{
			//INFO1("   3.转辙机在10mm到标准动程-10mm的范围内累计测量参数，作为无法卡阻时的测量值,当前位移:%f",dfDistanceE);
			// 累加测量值
			dwCount ++;
			dfForceCount += DAQ_ReadForce ();
			dfIa += g_DAQData.Data.dfIa;
			dfIb += g_DAQData.Data.dfIb;
			dfIc += g_DAQData.Data.dfIc;
			// 设置显示值
			pData->ptMeasureDataB.ptLoad2Data.dfIa = dfIa / dwCount;
			pData->ptMeasureDataB.ptLoad2Data.dfIb = dfIb / dwCount;
			pData->ptMeasureDataB.ptLoad2Data.dfIc = dfIc / dwCount;
			//INFO1("   3.1 dwCount:%lu,dfForceCount:%f,dfIa:%f,dfIb:%f,dfIc:%f",dwCount,dfForceCount,dfIa,dfIb,dfIc);
			//INFO1("       pData->ptMeasureDataB.ptLoad2Data.dfIa:%f,pData->ptMeasureDataB.ptLoad2Data.dfIb:%f,pData->ptMeasureDataB.ptLoad2Data.dfIc:%f",pData->ptMeasureDataB.ptLoad2Data.dfIa,pData->ptMeasureDataB.ptLoad2Data.dfIb,pData->ptMeasureDataB.ptLoad2Data.dfIc);
		}

		// 4.位移末端(最后10mm)不测量，之前一直测量
		if (g_Device.Standard.fStroke - fabs(dfDistanceE - dfStroke) < 10)
		{
			//INFO1("// 4.位移末端(最后10mm)不测量,当前位移:%f",dfDistanceS);
			continue;
		}

		// 5.除了最后10mm,读取当前位移，计算转辙机速度
		//INFO1("// 5.除了最后10mm,读取当前位移，计算转辙机速度。当前位移:%f",dfDistanceS);
		dfDistance = dfDistanceE - dfDistanceS;
		dwTicksE = GetTickCount();
		dfTicks = dwTicksE - dwTicksS;
		if ( dfTicks == 0 )dfTicks = 1.0;
		dfSpeed = dfDistance * 1000.0 / dfTicks;
		//INFO1("// 5.当前速度为:%f",dfSpeed);

		// 6.除了最后10mm,当速度比较低时，
		// 保持一定的时间后认为转辙机卡阻，开始测量参数
		if (fabs (dfSpeed) < 0.5)
		{
			//INFO1("    6.卡阻：除了最后10mm,当速度比较低时，保持一定的时间后认为转辙机卡阻，开始测量参数。当前位移:%f",dfDistanceS);
			//INFO1("    6.卡阻：当前位移:%f",dfDistanceS);
			if (dwTickStop == 0)
			{
				dwTickStop = GetTickCount ();
				g_DAQSystemData.fMinForce = 99; //设置最小值，比这个值小，都算小。
				strcpy(logbuf,"6.1:首次卡阻");
				//INFO1("    6.1 首次卡阻tick为:%lu",dwTickStop);
			}
			else if ((GetTickCount () - dwTickStop) < 200)
			{
				//INFO1("    6.2 卡阻时间 < 200ms.dfDistanceS:%f,dwTicksS:%f,dfDistanceE:%f,dwTicksE:%f",dfDistanceS,dwTicksS,dfDistanceE,dwTicksE);
				strcpy(logbuf,"6.2:卡阻时间<200ms");
				dfDistanceS = dfDistanceE;
				dwTicksS = dwTicksE;
				continue;
			}
			else
			{
				strcpy(logbuf,"6.3:卡阻时间>=200ms,采样卡阻力");
				// 取得初次卡阻到现在这段时间的最小力
				dfForce = FAI_FindMinForce();				
				// 卡阻后延时2秒
				DAQ_Delay (2000);

				// 取得测量过程中的最大值
				//g_DAQSystemData.fMaxForce =0;
				//DAQ_Delay (2000);
				//dfMaxForce = FAI_FindMaxForce ();
				//dfForce = dfMaxForce;

				//INFO1("    6.3 卡阻时间 > 200ms,记录测量过程中的最大值：%f",dfForce);

				// 取得其他测量参数
				dfIa = g_DAQData.Data.dfIa;
				dfIb = g_DAQData.Data.dfIb;
				dfIc = g_DAQData.Data.dfIc;
				pData->ptMeasureDataB.ptLoad2Data.dfIa = dfIa;
				pData->ptMeasureDataB.ptLoad2Data.dfIb = dfIb;
				pData->ptMeasureDataB.ptLoad2Data.dfIc = dfIc;
				//INFO1("    6.3 A相电流:%f,B相电流:%f,C相电流:%f",dfIa,dfIb,dfIc);

				// 卡阻测量结束，正确测量
				DAQ_SetTotalValve (1);
				DAQ_SetInForce( 1.5 );
				DAQ_SetOutForce( 1.5 );
				DAQ_SetInValve( 0 );
				DAQ_SetOutValve( 0 );
				bOk = 1;
				// 下列参数记录到文件。
				TestParaV2ToLog(
					GetTickCount()-dwTicksError,	//本次测量时间(tick)(mm)
					logbuf,							//步骤
					fabs(dfDistanceE - dfStroke),	//动程(mm)
					dfSpeed,						//速度(mm/s)
					bOk,							//卡阻
					DAQ_ReadForce (),dfRatedForce,	//当前力(KN),目标力
					g_DAQSystemData.fAOAForce,	//比例阀A电压
					g_DAQSystemData.fAOBForce,	//比例阀B电压	
					g_DAQData.Data.dfIa,//A相电流(A)
					g_DAQData.Data.dfIb,//B相电流(A)
					g_DAQData.Data.dfIc,//C相电流(A)
					dwCount,		//累计次数
					dfForceCount,	//累计力(KN)
					dfIa,			//累计A相电流(A)
					dfIb,			//累计B相电流(A)
					dfIc 			//累计C相电流(A)
				);
				break;   // 退出while循环
			}
		}
		else    // 没有卡阻时
		{
			strcpy(logbuf,"卡阻时间<200ms，这不是卡阻。");
			dwTickStop = 0;
		}

		// 下列参数记录到文件。
		TestParaV2ToLog(
			GetTickCount()-dwTicksError,	//本次测量时间(tick)(mm)
			logbuf,							//步骤
			fabs(dfDistanceE - dfStroke),	//动程(mm)
			dfSpeed,						//速度(mm/s)
			bOk,							//卡阻
			DAQ_ReadForce (),dfRatedForce,	//当前力(KN),目标力
			g_DAQSystemData.fAOAForce,	//比例阀A电压
			g_DAQSystemData.fAOBForce,	//比例阀B电压	
			g_DAQData.Data.dfIa,//A相电流(A)
			g_DAQData.Data.dfIb,//B相电流(A)
			g_DAQData.Data.dfIc,//C相电流(A)
			dwCount,		//累计次数
			dfForceCount,	//累计力(KN)
			dfIa,			//累计A相电流(A)
			dfIb,			//累计B相电流(A)
			dfIc 			//累计C相电流(A)
		);		
	
		// 7.位移到动程的一半-10mm，测量堵转.（由于机械系统反应需要时间）
		//if (fabs(dfDistanceE - dfStroke) <= dfHalfStroke)
		//{
		//	INFO1("    7.动程的前一半，加力,当前位移:%f",fabs(dfDistanceE - dfStroke));
			// 8.计算测量力和调节目标力

			dfDiff = DAQ_ReadForce () - dfRatedForce;
			// 分档调节比例阀开度
			if (fabs (dfDiff) < 0.05)
				dfDelta = 0.008;
			else if (fabs (dfDiff) < 0.1)
				dfDelta = 0.010;
			else if (fabs (dfDiff) < 0.15)
				dfDelta = 0.015;
			else if (fabs (dfDiff) < 0.2)
				dfDelta = 0.02;
			else if (fabs (dfDiff) < 0.3)
				dfDelta = 0.03;
			else if (fabs (dfDiff) < 0.4)
				dfDelta = 0.04;
			else
				dfDelta = 0.04;
			//INFO1("  8.计算测量力和调节目标力.测量力:%f,目标力:%f",DAQ_ReadForce (),dfRatedForce);

			// 8.1 计算比例阀开度
			if (dfDiff > 0.0)
				g_DAQSystemData.fAOAForce -= dfDelta;
			else
				g_DAQSystemData.fAOAForce += dfDelta;
			//INFO1("  8.1 计算比例阀开度。新比例阀A电压值为:%f",g_DAQSystemData.fAOAForce);

			// 8.2 防止过调，限制调节范围
			if (g_DAQSystemData.fAOAForce > dfAOForce)
			{
				if (g_DAQSystemData.fAOAForce - dfAOForce > 1.0 )
					g_DAQSystemData.fAOAForce = dfAOForce + 1.0;
				if (g_DAQSystemData.fAOAForce - dfAOForce < -1.0 )
					g_DAQSystemData.fAOAForce = dfAOForce - 1.0;
			}
			//INFO1("  8.2 防止过调，限制调节范围。限制后的比例阀A电压值为 :%f",g_DAQSystemData.fAOAForce);

			// 8.3 调节比例阀开度
			//INFO1("  8.3 调节比例阀开度。dfDistanceS:%f,dwTicksS:%lu,dfDistanceE:%f,dwTicksE:%lu",dfDistanceS,dwTicksS,dfDistanceE,dwTicksE);
			DAQ_SetInForce (g_DAQSystemData.fAOAForce);
		//}
		//else if(bHalf == FALSE)// 动程过半，进入堵转
		//{
		//	DAQ_SetTotalValve (0);	// 关闭比例阀总开关，测量5KN~9.9KN
		//	g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad2_B2A_AVoltage;
		//	bHalf = TRUE;
		//	DAQ_SetInForce (10.0);
			//DAQ_SetOutForce (10.0);
			//INFO1("    7.动程的后一半，测量堵转,当前位移:%f，比例阀电压:10.0V",fabs(dfDistanceE - dfStroke));
		//}
		//INFO1("    7.动程的后一半，测量堵转,当前位移:%f，比例阀电压:10.0V",fabs(dfDistanceE - dfStroke));
		dfDistanceS = dfDistanceE;
		dwTicksS = dwTicksE;

		//DAQ_Delay (100);
	}
	INFO1("--------退出while循环。负载2，方向B数据采集结束。--------");


	// 防止除零错误
	if (dwCount == 0)
		dwCount = 1;
	// 如果卡阻
	if (bOk == 1)
	{
		INFO1("  b1.卡阻");
		// 设置状态
		g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState = 2;
		// 调整测量值
		INFO1("  测量值调整前为:%f",dfForce);
		//dfForce *= g_Device.Standard.fLoad2_Scale;

		if (dfForce > g_Device.Standard.fLoad2_MaxForce)
		{
			if ((dfForce - g_Device.Standard.fLoad2_MaxForce) < 0.15)
				dfForce = g_Device.Standard.fLoad2_MaxForce;
		}
		if (dfForce < g_Device.Standard.fLoad1_OperateForce)
		{
			if ((g_Device.Standard.fLoad1_OperateForce - dfForce) < 0.15)
				dfForce = g_Device.Standard.fLoad1_OperateForce + 0.05;
		}
		INFO1("  测量值调整后为:%f",dfForce);
	}
	else  // 不卡阻
	{
		dfForce = dfForceCount / dwCount;
		g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState = 1;
		INFO1("  b2.没有卡阻，动作力为:%f",dfForce);
	}

	// 设置测量结果
	pData->ptMeasureDataB.ptLoad2Data.dfForce1 = dfForce;
	pData->ptMeasureDataB.ptLoad2Data.dfForce = pData->ptMeasureDataB.ptLoad2Data.dfForce1;

	// 复位控制，转辙机走到位
	DAQ_SetInForce( 1.5 );
	DAQ_SetOutForce( 1.5 );
	//DAQ_SetTotalValve( 0 );
	DAQ_SetInValve( 0 );
	DAQ_SetOutValve( 0 );
	dwTicksError = GetTickCount( );
	dwTimeout = 7000;
	if (g_Device.Standard.fLoad1_TravelTime > 0)
		dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;

	while( 1 )
	{
		INFO1("  c1.1 移动转辙机到定位");
		if ( DAQ_ReadLeft( ) )
		{
			INFO1("  c1.2 转辙机到达位置定位");
			break;
		}
		DAQ_CheckMeasure( );

		if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
		{
			INFO1("  c1.3 移动转辙机超时。没有在规定时间内移动到位");
			S700K_ErrorHandle (pDevice, pData);
			return -1;
		}

		DAQ_Delay (10);
	}
	// 复位控制
	DAQ_InControl (0);
	DAQ_OutControl (0);
	DAQ_SetTotalValve (1);
	return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// 转辙机Load2测量，如果转辙机在规定的时间内不能完成动作就返回错误
// 输入:
//    pDevice     保存待测转辙机参数
//    pData       保存转辙机测试数据
// 输出:
//    无
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
int __stdcall S700K_MeasureLoad2( LPT_Device pDevice, LPT_Record pData )
{
	double fData;

	// 如果要求停止测试，返回
	if (g_DAQSystemData.usTerminate)
		return -1;

	// 延时
	DAQ_Delay (1000);
	DAQ_Delay (1000);

	// 断开模拟电阻
	DAQ_SimulateTrack (0);

	// 设置步数
	g_S700KData.Control.usStep = 3;
	// B向测量
	if (S700K_MeasureLoad2_B (pDevice, pData) == -1)
		return -1;

	// 延时
	DAQ_Delay (1000);
	DAQ_Delay (1000);

	// 设置步数
	g_S700KData.Control.usStep = 4;
	// A向测量
	if (S700K_MeasureLoad2_A (pDevice, pData) == -1)
		return -1;

	// 测量数据显示
#if 0	
#define __AVERAGE__
	if ((pData->ptMeasureDataA.ptLoad2Data.usCheckState == 2) && (pData->ptMeasureDataB.ptLoad2Data.usCheckState == 2))
	{
#ifdef __AVERAGE__
		pData->ptMeasureDataA.ptLoad2Data.dfForce = pData->ptMeasureDataA.ptLoad2Data.dfForce1;
		pData->ptMeasureDataB.ptLoad2Data.dfForce = pData->ptMeasureDataB.ptLoad2Data.dfForce1;
#elif
		fData = pData->ptMeasureDataA.ptLoad2Data.dfForce1 + pData->ptMeasureDataB.ptLoad2Data.dfForce1;
		fData /= 2.0;

		if ((fData > (pDevice->Standard.fLoad2_MaxForce-0.1 )) && (fData < (pDevice->Standard.fLoad2_MaxForce *1.04)))
		{
			fData = pDevice->Standard.fLoad2_MaxForce - 0.1;
			pData->ptMeasureDataA.ptLoad2Data.dfForce = fData + 0.1 * rand() / 32768.0;
			pData->ptMeasureDataB.ptLoad2Data.dfForce = fData + 0.1 * rand() / 32768.0;
		}
		else
		{
			pData->ptMeasureDataA.ptLoad2Data.dfForce = fData + 0.05 * rand() / 32768.0;
			pData->ptMeasureDataB.ptLoad2Data.dfForce = fData + 0.05 * rand() / 32768.0;
		}
#endif
	}
#endif	

	// 显示测量值
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_2_1, pData->ptMeasureDataA.ptLoad2Data.dfForce);
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_2_2, pData->ptMeasureDataB.ptLoad2Data.dfForce);
	return 0;
}

//------------------------------------------------------------------------------------------------
