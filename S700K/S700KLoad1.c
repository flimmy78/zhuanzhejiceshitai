// #########################################################################
// *************************************************************************
// ת�޻�Load1����
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
// ����ȫ�ֱ���
//------------------------------------------------------------------------------------------------
extern int              g_plDAQMain;
extern PT_Record        g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_DAQSystemData g_DAQSystemData;
extern PT_Device        g_Device;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// ת�޻�Load1���������ת�޻��ڹ涨��ʱ���ڲ�����ɶ����ͷ��ش���
// ����:
//    pDevice     �������ת�޻�����
//    pData       ����ת�޻���������
// ���:
//    ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
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
	double   dfStroke;  // ��ǰλ�ƣ���ȥ��ʼ����Ƕ��̡�
	double   dfMeasureStroke; // ����ʵ�⶯�̡�
	double   dfForceCount = 0.0;
	double   dfAOForce;
	double   dfDelta, dfDiff;
	double   dfSpeed;
	short    usSkiped = 0;
	short    usError = 0;
	double   dfRatedForce = 0.0;
	double   dfHalfStroke;
	double   dfMinLoad2Force;

	// ���Ҫ��ֹͣ���ԣ�����
	if (g_DAQSystemData.usTerminate){
		INFO1("--------------------����1������A���ԣ����û���ֹ--------------------");
		return -1;
	}
	INFO1("--------------------����1������A����--------------------");
	// ����ֻ�ڶ��̹������в������ݴ���
	// dfHalfStroke = g_Device.Standard.fStroke / 2;
	// dfHalfStroke = g_Device.Standard.fStroke * 0.7; // 
	// dfHalfStroke += 10.0;
	// ȡʵ�ʲ������Ķ��̶����Ǳ�׼���̡����ǹ�˾û����ô���ͺŵ�ת�޻���
	// �ò�ͬ���̵�ת�޻�ģ��	
	// ʵ�⶯��
	dfMeasureStroke = ( pData->ptMeasureDataA.ptCheckData.dfInterval + pData->ptMeasureDataB.ptCheckData.dfInterval ) / 2.0;
	// ������ʼ��				  
	dfHalfStroke = 0.7 * dfMeasureStroke; 
	INFO1("ʵ�⶯��:%f,������ʼ����:%f",dfMeasureStroke,dfHalfStroke);


	// ����ת�޻�����ʱ�������ʱֵ
	if (g_Device.Standard.fLoad1_TravelTime > 0)
		dwTimeout = g_Device.Standard.fLoad1_TravelTime * 1000 + 1000;
	INFO1("0 ����ʱ�������ʱֵ:%lu(s)",dwTimeout);

#if 0	
	// ѡȡA���B��Load2���е���Сֵ
	dfMinLoad2Force = (g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce < g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce)
					  ? g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce : g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce;

	// �趨Ϊ����Ŀ����
	dfRatedForce = dfMinLoad2Force;
	INFO1("0.1 �趨����Ŀ������(����ǰ):%f(KN)",dfRatedForce);

	// ��������Ŀ����
	if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 0.6)
		dfRatedForce -= 0.4;
	else if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 1.0)
		dfRatedForce -= 0.6;
	else
		dfRatedForce -= 0.6;
	INFO1("0.1 �趨����Ŀ������(����1��):%f(KN)",dfRatedForce);

	// ��������Ŀ���������ܱ�Load1���С
	if (dfRatedForce < g_Device.Standard.fLoad1_OperateForce + 0.05)
		dfRatedForce = g_Device.Standard.fLoad1_OperateForce;

	INFO1("0.1 �趨����Ŀ������(����2��):%f(KN)",dfRatedForce);
#else
	dfRatedForce = g_Device.Standard.fLoad1_OperateForce + 0.25;
	INFO1("0.1 �趨Ŀ������Ϊ��׼������+0.25:%f(KN)",dfRatedForce);	
#endif
	// ȡ�û��򷧳�ʼ����ֵ
	g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad1_A2B_AVoltage;
	g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad1_A2B_BVoltage;
	
	// ��������̨����ʼ״̬
	//g_DAQSystemData.fAOAForce = 1.0;
	dfAOForce = g_DAQSystemData.fAOBForce;
	DAQ_SetInForce (1.0);
	DAQ_SetOutForce (1.0);

	//g_DAQSystemData.fAOBForce = 1.0;

	// �رջ���
	//DAQ_SetTotalValve (0);
	DAQ_SetInValve (0);

	DAQ_Delay (1000);

	// �򿪻��򷧣�ת�޻�����.(����)
	//DAQ_SetTotalValve (1);
	DAQ_Force2TotalValue(dfRatedForce);// ��������Ҫ�󣬿����ܷ��л���ͬ�ĸ������Ρ�	
	DAQ_OutControl (1);
	DAQ_SetOutValve (1);

	// ��λλ��
	DAQ_ResetStroke ();
	// ��ȡλ�Ƴ�ʼֵ
	dfStroke = DAQ_ReadStroke ();
	// ��ʼʱ��
	dwTicksError = GetTickCount ();
	dwTicksA = GetTickCount ();
	// ��λ�����
	g_DAQSystemData.fMaxForce = 0.0;

	int delayCnt = 0;
	while( 1 )
	{
		// ��ʱ
		DAQ_Delay(50);
		delayCnt ++;

		// �����λ������
		if (DAQ_ReadRight ())
		{
			INFO1("--------��λ���˳�whileѭ��--------");			
			break;
		}
		// �ɼ�����
		DAQ_CheckMeasure ();
		// �����ʱ�����ش���
		if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
		{
			if (usError == 1)
			{
				S700K_ErrorHandle (pDevice, pData);
				INFO1("--------��ʱ���˳�whileѭ��--------");
				return -1;
			}
			else
			{
				S700K_UnloadHandle (pDevice, pData);
				usError = 1;
				dwTicksError = GetTickCount ();
			}
		}

		// ת�޻�����ʱ������߻��򷧿��ȣ���ֹת�޻�����
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
		// ���뵱ǰλ�ƣ������ٶ�
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
		/* û����ʱ��ֱ���ж��ٶ�<2.5mm/sΪ���裬�ֳ������ڶ���Ϊ20mm���ҵ�ʱ�򣬻����п��衣
			ʵ���ϲ���ת�޻��ܾ޴��������衣����ȥ����δ��롣
		 	��δ���������ʹ�ã�1�������ٶ��жϱ�׼Ϊ<0.5mm,2:�����ʱ��
		*/		
		// ���ٶȱȽϵ�ʱ��������һ����ʱ�����Ϊת�޻����裬����ʼ��������
		// ��ɲ������������
		if ((dfSpeed < 2.5) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->Standard.fStroke))
		{
			// ���û��ƽ��ֵ���������ֵ����֤�в�������
			if (dfForceCount == 0.0)
			{
				dfForceCount += FAI_FindMaxForce();
				dfIa += g_DAQData.Data.dfIa;
				dfIb += g_DAQData.Data.dfIb;
				dfIc += g_DAQData.Data.dfIc;
				dwCount ++;
				// ������ʾֵ
				pData->ptMeasureDataA.ptLoad1Data.dfForce = dfForceCount / dwCount;
				pData->ptMeasureDataA.ptLoad1Data.dfIa = dfIa / dwCount;
				pData->ptMeasureDataA.ptLoad1Data.dfIb = dfIb / dwCount;
				pData->ptMeasureDataA.ptLoad1Data.dfIc = dfIc / dwCount;
			}
			INFO1("6.3 ����,������%lu,�ۼƶ�ת��:%f KN,A�����:%f A,B�����:%f A,C�����:%f A",dwCount,dfForceCount,dfIa,dfIb,dfIc);
			INFO1("6.3 ����,ƽ��ֵ        ��ת��:%f KN,A�����:%f A,B�����:%f A,C�����:%f A",
				  pData->ptMeasureDataA.ptLoad1Data.dfForce,
				  pData->ptMeasureDataA.ptLoad1Data.dfIa,
				  pData->ptMeasureDataA.ptLoad1Data.dfIb,
				  pData->ptMeasureDataA.ptLoad1Data.dfIc);
			// �����������
			DAQ_Delay(1000);
			DAQ_SetOutForce (1.0);
			DAQ_SetInForce (1.0);
			//DAQ_SetTotalValve (0);
			DAQ_SetOutValve (0);
			DAQ_SetInValve (0);
			usSkiped = 1;
		}
#endif		

		// ���ض��Ķ��̷�Χ�ڼ��������ƽ��ֵ����Ϊ�޷�����ʱ�Ĳ������
		dfDistance = DAQ_ReadStroke ();
		//if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 10) < pDevice->Standard.fStroke))
		if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 10) < dfMeasureStroke))
		{
			// �ۼӲ���ֵ
			dwCount ++;
			dfForceCount += DAQ_ReadForce ();
			dfIa += g_DAQData.Data.dfIa;
			dfIb += g_DAQData.Data.dfIb;
			dfIc += g_DAQData.Data.dfIc;

			// ������ʾֵ
			pData->ptMeasureDataA.ptLoad1Data.dfForce = dfForceCount / dwCount;
			pData->ptMeasureDataA.ptLoad1Data.dfIa = dfIa / dwCount;
			pData->ptMeasureDataA.ptLoad1Data.dfIb = dfIb / dwCount;
			pData->ptMeasureDataA.ptLoad1Data.dfIc = dfIc / dwCount;
		}
		//INFO1(" ��ǰ����:%f(mm)",fabs (dfDistance - dfStroke));
		// ���в�����¼���ļ������̣���ǰ����Ŀ������������A��ѹ��������B��ѹ��
		TestPara2Log( fabs (dfDistance - dfStroke),// ����
			  DAQ_ReadForce (),dfRatedForce,// ��ǰ��,Ŀ����
			  g_DAQSystemData.fAOAForce,//������A��ѹ
			  g_DAQSystemData.fAOBForce //������B��ѹ
		);		
		// ����������͵���Ŀ����
		if (fabs (DAQ_ReadStroke () - dfStroke) < dfHalfStroke){ // ���̵�ǰ����̫С��������Ϊ���������ڵ����ݡ�
			//INFO1("����ǰ��Σ������ڱ��������ȡ�������A��ѹ:%f(V),������B��ѹ:%f(V)",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
			continue;
		}		
		dfDiff = DAQ_ReadForce () - dfRatedForce;
		//INFO1(" ��ǰ��:%f(KN)��Ŀ����%f:(KN)",DAQ_ReadForce (),dfRatedForce);
		// �ֵ����ڱ���������
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
		//INFO1(" ������:%f(V),���������֮ǰ����������:%f(V)",dfDelta,g_DAQSystemData.fAOBForce);

		// �������������
		if (dfDiff > 0.0){
			g_DAQSystemData.fAOBForce -= dfDelta;
			g_DAQSystemData.fAOAForce -= dfDelta;
		}else{
			g_DAQSystemData.fAOBForce += dfDelta;
			g_DAQSystemData.fAOAForce += dfDelta;			
		}

		//INFO1("  ���������֮�����������:%f(V)",g_DAQSystemData.fAOBForce);

		// ��ֹ���������Ƶ��ڷ�Χ
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

		//INFO1("----end---- ���Ƶ��ڷ�Χ�����������:%f(V)",g_DAQSystemData.fAOBForce);
		// ���ڱ���������
		if(DAQ_GetTotalValue()){ // �ܷ��򿪣�ʹ������������
		}else{// �ܷ��ر�,һ��Ϊ0V��ֻ������һ����������
			g_DAQSystemData.fAOAForce = 0;
		}
		DAQ_SetInForce (g_DAQSystemData.fAOAForce);	//������A��ѹ	
		DAQ_SetOutForce (g_DAQSystemData.fAOBForce);//������B��ѹ				
	}

	// ���㶯��ʱ��
	
#if 0	
	dfActionTime = GetTickCount( ) - dwTicksA;
#else
	dfActionTime = DAQAIReadTravelTime(DIRECTION_A);// ����A
#endif	
	// ��ֹ�������
	if ( dwCount == 0 )dwCount = 1;
	// ����ƽ��ֵ
	dfForceCount /= dwCount;
	dfIa /= dwCount;
	dfIb /= dwCount;
	dfIc /= dwCount;

	// ��������ֵ
#if 0
	if ((g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState == 2) && (usSkiped != 1))
	{

		// �����������ܴ��������
		if (dfForceCount > g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce)
			dfForceCount = g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce;

		// ������������Load1���ͬʱLoad1������С��Load1���ʱ
		if ((g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce > g_Device.Standard.fLoad1_OperateForce)
				&& (dfForceCount < g_Device.Standard.fLoad1_OperateForce))
		{
			// �����ֵС��0.1KNʱ����Ϊ����ֵ
			if ((g_Device.Standard.fLoad1_OperateForce - dfForceCount) < 0.1)
				dfForceCount = g_Device.Standard.fLoad1_OperateForce + Random(0.0, 0.05);
		}
	}
#endif
	// ���ò������
	pData->ptMeasureDataA.ptLoad1Data.dfIa = dfIa;
	pData->ptMeasureDataA.ptLoad1Data.dfIb = dfIb;
	pData->ptMeasureDataA.ptLoad1Data.dfIc = dfIc;
	pData->ptMeasureDataA.ptLoad1Data.dfForce = dfForceCount;
	pData->ptMeasureDataA.ptLoad1Data.dfActionTime = dfActionTime/ 1000.0;
	INFO1("  A�����:%f(A),B�����:%f(A),C�����:%f(A),������:%f(KN),����ʱ��:%f(s)",
		  dfIa,dfIb,dfIc,dfForceCount,
		  pData->ptMeasureDataA.ptLoad1Data.dfActionTime
		 );
#if 0
	if (usSkiped == 1)
		pData->ptMeasureDataA.ptLoad1Data.dfActionTime = (dfActionTime-50*delayCnt-1000) / 1000.0;
	else
		pData->ptMeasureDataA.ptLoad1Data.dfActionTime = (dfActionTime-50*delayCnt) / 1000.0;
#endif
	// ��λ����
	DAQ_SetOutForce( 1.0 );
	DAQ_SetInForce( 1.0 );
	DAQ_InControl( 0 );
	DAQ_OutControl( 0 );
	DAQ_SetTotalValve( 1 );
	DAQ_SetOutValve( 0 );
	DAQ_SetInValve( 0 );

	// ��ʾ����ֵ
	SetCtrlVal( g_plDAQMain, DAQMAIN_NG_F_1_1, pData->ptMeasureDataA.ptLoad1Data.dfForce );
	SetCtrlVal( g_plDAQMain, DAQMAIN_NG_T_1_1, pData->ptMeasureDataA.ptLoad1Data.dfActionTime );

	return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// ת�޻�Load1���������ת�޻��ڹ涨��ʱ���ڲ�����ɶ����ͷ��ش���
// ����:
//    pDevice     �������ת�޻�����
//    pData       ����ת�޻���������
// ���:
//    ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
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
	double   dfStroke;  // ��ǰλ�ƣ���ȥ��ʼ����Ƕ��̡�
	double   dfMeasureStroke; // ����ʵ�⶯�̡�
	double   dfForceCount = 0.0;
	double   dfAOForce;
	double   dfDelta, dfDiff;
	double   dfSpeed;
	short    usSkiped = 0;
	short    usError = 0;
	double   dfRatedForce = 0.0;
	double   dfHalfStroke;
	double   dfMinLoad2Force;

	// ���Ҫ��ֹͣ���ԣ�����
	if (g_DAQSystemData.usTerminate)
	{
		INFO1("--------------------����1������B���ԣ����û���ֹ--------------------");
		return -1;
	}
	INFO1("--------------------����1������B����--------------------");
	// ����ֻ�ڶ��̹������в������ݴ���
	// dfHalfStroke = g_Device.Standard.fStroke / 2;
	// dfHalfStroke = g_Device.Standard.fStroke * 0.7;
	// dfHalfStroke += 10.0;
	// ʵ�⶯��
	dfMeasureStroke = ( pData->ptMeasureDataA.ptCheckData.dfInterval + pData->ptMeasureDataB.ptCheckData.dfInterval ) / 2.0;
	// ������ʼ��				  
	dfHalfStroke = 0.7 * dfMeasureStroke; 
	INFO1("ʵ�⶯��:%f,������ʼ����:%f",dfMeasureStroke,dfHalfStroke);
	
	// ����ת�޻�����ʱ�������ʱֵ
	if (g_Device.Standard.fLoad1_TravelTime > 0)
		dwTimeout = g_Device.Standard.fLoad1_TravelTime * 1000 + 1000;
	INFO1("0 ����ʱ�������ʱֵ:%lu(s)",dwTimeout);
#if 0
	// ѡȡA���B��Load2���е���Сֵ
	dfMinLoad2Force = (g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce < g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce)
					  ? g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce : g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce;

	// �趨Ϊ����Ŀ����
	dfRatedForce = dfMinLoad2Force;
	INFO1("0.1 �趨����Ŀ������(����ǰ):%f(KN)",dfRatedForce);

	// ��������Ŀ����
	if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 0.6)
		dfRatedForce -= 0.4;
	else if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 1.0)
		dfRatedForce -= 0.6;
	else
		dfRatedForce -= 0.6;
	INFO1("0.1 �趨����Ŀ������(����1��):%f(KN)",dfRatedForce);

	// ��������Ŀ���������ܱ�Load1���С
	if (dfRatedForce < g_Device.Standard.fLoad1_OperateForce + 0.05)
		dfRatedForce = g_Device.Standard.fLoad1_OperateForce ;
	INFO1("0.1 �趨����Ŀ������(����2��):%f(KN)",dfRatedForce);
	
#else
	dfRatedForce = g_Device.Standard.fLoad1_OperateForce + 0.25 ;
	INFO1("0.1 �趨Ŀ������Ϊ��׼������+0.25:%f(KN)",dfRatedForce);
#endif
	// ȡ�û��򷧳�ʼ����ֵ
	g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad1_B2A_AVoltage;
	g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad1_B2A_BVoltage;

	// ��������̨����ʼ״̬
	//g_DAQSystemData.fAOBForce = 1.0;
	dfAOForce = g_DAQSystemData.fAOAForce;
	DAQ_SetOutForce (1.0);
	DAQ_SetInForce (1.0);

	// �رջ���
	DAQ_SetOutValve (0);

	DAQ_Delay (1000);

	//g_DAQSystemData.fAOAForce = 1.0;
	// �򿪻��򷧣�ת�޻�����
	//DAQ_SetTotalValve (1);
	DAQ_Force2TotalValue(dfRatedForce);// ��������Ҫ�󣬿����ܷ��л���ͬ�ĸ������Ρ�
	
	DAQ_InControl( 1 );  // ת�޻�����
	DAQ_SetInValve (1);

	// ��λλ��
	DAQ_ResetStroke ();
	// ��ȡλ�Ƴ�ʼֵ
	dfStroke = DAQ_ReadStroke ();
	// ��ʼʱ��
	dwTicksError = GetTickCount ();
	dwTicksA = GetTickCount ();
	// ��λ�����
	g_DAQSystemData.fMaxForce = 0.0;

	int delayCnt = 0;
	while( 1 )
	{
		// ��ʱ
		DAQ_Delay(50);
		delayCnt ++;

		// �����λ������
		if (DAQ_ReadLeft ())
		{
			INFO1("--------��λ���˳�whileѭ��--------");
			break;
		}
		// �ɼ�����
		DAQ_CheckMeasure ();
		// �����ʱ�����ش���
		if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
		{
			if (usError == 1)
			{
				S700K_ErrorHandle (pDevice, pData);
				INFO1("--------��ʱ���˳�whileѭ��--------");
				return -1;
			}
			else
			{
				S700K_UnloadHandle (pDevice, pData);
				usError = 1;
				dwTicksError = GetTickCount ();
			}
		}

		// ת�޻�����ʱ������߻��򷧿��ȣ���ֹת�޻�����
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
		// ���뵱ǰλ�ƣ������ٶ�
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
		/* û����ʱ��ֱ���ж��ٶ�<2.5mm/sΪ���裬�ֳ������ڶ���Ϊ20mm���ҵ�ʱ�򣬻����п��衣
			ʵ���ϲ���ת�޻��ܾ޴��������衣����ȥ����δ��롣
		 	��δ���������ʹ�ã�1�������ٶ��жϱ�׼Ϊ<0.5mm,2:�����ʱ��
		*/
		
		// ���ٶȱȽϵ�ʱ��������һ����ʱ�����Ϊת�޻����裬����ʼ��������
		// ��ɲ���������
		if ((dfSpeed < 2.5) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->Standard.fStroke))
		{
			// ���û��ƽ��ֵ���������ֵ����֤�в�������
			if (dfForceCount == 0.0)
			{
				dfForceCount += FAI_FindMaxForce();
				dfIa += g_DAQData.Data.dfIa;
				dfIb += g_DAQData.Data.dfIb;
				dfIc += g_DAQData.Data.dfIc;
				dwCount ++;
				// ������ʾֵ
				pData->ptMeasureDataB.ptLoad1Data.dfForce = dfForceCount / dwCount;
				pData->ptMeasureDataB.ptLoad1Data.dfIa = dfIa / dwCount;
				pData->ptMeasureDataB.ptLoad1Data.dfIb = dfIb / dwCount;
				pData->ptMeasureDataB.ptLoad1Data.dfIc = dfIc / dwCount;
			}
			INFO1("6.3 ����,������%lu,�ۼƶ�ת��:%f KN,A�����:%f A,B�����:%f A,C�����:%f A",dwCount,dfForceCount,dfIa,dfIb,dfIc);
			INFO1("6.3 ����,ƽ��ֵ        ��ת��:%f KN,A�����:%f A,B�����:%f A,C�����:%f A",
				  pData->ptMeasureDataB.ptLoad1Data.dfForce,
				  pData->ptMeasureDataB.ptLoad1Data.dfIa,
				  pData->ptMeasureDataB.ptLoad1Data.dfIb,
				  pData->ptMeasureDataB.ptLoad1Data.dfIc);
			// �����������
			DAQ_Delay(1000);
			DAQ_SetOutForce( 1.0 );
			DAQ_SetInForce( 1.0 );
			//DAQ_SetTotalValve( 0 );
			DAQ_SetOutValve( 0 );
			DAQ_SetInValve( 0 );
			usSkiped = 1;
		}
#endif
		// ���ض��Ķ��̷�Χ�ڼ��������ƽ��ֵ����Ϊ�޷�����ʱ�Ĳ������
		dfDistance = DAQ_ReadStroke ();
		//if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 10) < pDevice->Standard.fStroke))
		if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 10) < dfMeasureStroke))
		{
			// �ۼӲ���ֵ
			dwCount ++;
			dfForceCount += DAQ_ReadForce ();
			dfIa += g_DAQData.Data.dfIa;
			dfIb += g_DAQData.Data.dfIb;
			dfIc += g_DAQData.Data.dfIc;

			// ������ʾֵ
			pData->ptMeasureDataB.ptLoad1Data.dfForce = dfForceCount / dwCount;
			pData->ptMeasureDataB.ptLoad1Data.dfIa = dfIa / dwCount;
			pData->ptMeasureDataB.ptLoad1Data.dfIb = dfIb / dwCount;
			pData->ptMeasureDataB.ptLoad1Data.dfIc = dfIc / dwCount;
		}
		//INFO1(" ��ǰ����:%f(mm)",fabs (dfDistance - dfStroke));
		// ���в�����¼���ļ������̣���ǰ����Ŀ������������A��ѹ��������B��ѹ��
		TestPara2Log( fabs (dfDistance - dfStroke),// ����
			  DAQ_ReadForce (),dfRatedForce,// ��ǰ��,Ŀ����
			  g_DAQSystemData.fAOAForce,//������A��ѹ
			  g_DAQSystemData.fAOBForce //������B��ѹ
		);		
		// ����������͵���Ŀ����
		if (fabs (DAQ_ReadStroke () - dfStroke) < dfHalfStroke){ // ���̵�ǰ����̫С��������Ϊ���������ڵ����ݡ�
			//INFO1("    ����ǰ��Σ������ڱ��������ȡ�������A��ѹ:%f(V),������B��ѹ:%f(V)",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
			continue;
		}
		dfDiff = DAQ_ReadForce () - dfRatedForce;
		//INFO1(" ��ǰ��:%f(KN)��Ŀ����:%f(KN)",DAQ_ReadForce (),dfRatedForce);
		// �ֵ����ڱ���������
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
		//INFO1(" ������:%f(V),���������֮ǰ����������:%f(V)",dfDelta,g_DAQSystemData.fAOAForce);

		// �������������
		if (dfDiff > 0.0){
			g_DAQSystemData.fAOAForce -= dfDelta;
			g_DAQSystemData.fAOBForce -= dfDelta;
		}else{
			g_DAQSystemData.fAOAForce += dfDelta;
			g_DAQSystemData.fAOBForce += dfDelta;
		}

		// ��ֹ���������Ƶ��ڷ�Χ
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
		//INFO1("----end---- ���Ƶ��ڷ�Χ�����������:%f(V)",g_DAQSystemData.fAOAForce);

		// ���ڱ���������
		if(DAQ_GetTotalValue()){ // �ܷ��򿪣�ʹ������������
		}else{// �ܷ��ر�,һ��Ϊ0V��ֻ������һ����������
			g_DAQSystemData.fAOBForce = 0;
		}
		DAQ_SetInForce (g_DAQSystemData.fAOAForce);	//������A��ѹ	
		DAQ_SetOutForce (g_DAQSystemData.fAOBForce);//������B��ѹ				
		//DAQ_Delay (50);
	}

	// ���㶯��ʱ��
#if 0	
	dfActionTime = GetTickCount( ) - dwTicksA;
#else
	dfActionTime = DAQAIReadTravelTime(DIRECTION_B);// ����B
#endif
	// ��ֹ�������
	if ( dwCount == 0 )dwCount = 1;
	// ����ƽ��ֵ
	dfForceCount /= dwCount;
	dfIa /= dwCount;
	dfIb /= dwCount;
	dfIc /= dwCount;

	// ��������ֵ
#if 0
	if ((g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState == 2) && (usSkiped != 1))
	{
		// ��������������ܴ��������
		if (dfForceCount > g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce)
			dfForceCount = g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce;

		// ������������Load1���ͬʱLoad1������С��Load1���ʱ
		if ((g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce > g_Device.Standard.fLoad1_OperateForce)
				&& (dfForceCount < g_Device.Standard.fLoad1_OperateForce))
		{
			// �����ֵС��0.1KNʱ����Ϊ����ֵ
			if ((g_Device.Standard.fLoad1_OperateForce - dfForceCount) < 0.1)
				dfForceCount = g_Device.Standard.fLoad1_OperateForce + Random(0.0, 0.05);
		}
	}
#endif
	// ���ò������
	pData->ptMeasureDataB.ptLoad1Data.dfIa = dfIa;
	pData->ptMeasureDataB.ptLoad1Data.dfIb = dfIb;
	pData->ptMeasureDataB.ptLoad1Data.dfIc = dfIc;
	pData->ptMeasureDataB.ptLoad1Data.dfForce = dfForceCount;
	pData->ptMeasureDataB.ptLoad1Data.dfActionTime = dfActionTime/ 1000.0;

	INFO1("  A�����:%f(A),B�����:%f(A),C�����:%f(A),������:%f(KN),����ʱ��:%f(s)",
		  dfIa,dfIb,dfIc,dfForceCount,
		  pData->ptMeasureDataB.ptLoad1Data.dfActionTime
		 );

#if 0
	if (usSkiped == 1)
		pData->ptMeasureDataB.ptLoad1Data.dfActionTime = (dfActionTime-50*delayCnt-1000) / 1000.0;
	else
		pData->ptMeasureDataB.ptLoad1Data.dfActionTime = (dfActionTime-50*delayCnt) / 1000.0;
#endif
	// ��λ����
	DAQ_SetOutForce( 1.0 );
	DAQ_SetInForce( 1.0 );
	DAQ_InControl( 0 );
	DAQ_OutControl( 0 );
	DAQ_SetTotalValve( 1 );
	DAQ_SetOutValve( 0 );
	DAQ_SetInValve( 0 );

	// ��ʾ����ֵ
	SetCtrlVal( g_plDAQMain, DAQMAIN_NG_F_1_2, pData->ptMeasureDataB.ptLoad1Data.dfForce );
	SetCtrlVal( g_plDAQMain, DAQMAIN_NG_T_1_2, pData->ptMeasureDataB.ptLoad1Data.dfActionTime );

	return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// ת�޻�Load1���������ת�޻��ڹ涨��ʱ���ڲ�����ɶ����ͷ��ش���
// ����:
//    pDevice     �������ת�޻�����
//    pData       ����ת�޻���������
// ���:
//    ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
int __stdcall S700K_MeasureLoad1( LPT_Device pDevice, LPT_Record pData )
{
	// ���Ҫ��ֹͣ���ԣ�����
	if (g_DAQSystemData.usTerminate)
		return -1;

	// ��ʱ
	DAQ_Delay (1000);
	DAQ_Delay (1000);

	// �Ͽ�ģ�����
	DAQ_SimulateTrack (0);

	// ���ò���
	g_S700KData.Control.usStep = 5;
	// B�����
	if (S700K_MeasureLoad1_B (pDevice, pData) == -1)
		return -1;

	// ��ʱ
	DAQ_Delay (1000);
	DAQ_Delay (1000);

	// ���ò���
	g_S700KData.Control.usStep = 6;
	// A�����
	if (S700K_MeasureLoad1_A (pDevice, pData) == -1)
		return -1;

	return 0;
}

//------------------------------------------------------------------------------------------------

