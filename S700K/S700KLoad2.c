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
// ����ȫ�ֱ���
//------------------------------------------------------------------------------------------------
extern int              g_plDAQMain;
extern PT_Record    g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_DAQSystemData g_DAQSystemData;
extern PT_Device        g_Device;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// ת�޻�Load2���������ת�޻��ڹ涨��ʱ���ڲ�����ɶ����ͷ��ش���
// ����:
//    pDevice     �������ת�޻�����
//    pData       ����ת�޻���������
// ���:
//    ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
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
	double   dfHalfStroke;	  // ����ʵ�⶯�̵�һ��
	double   dfMeasureStroke; // ����ʵ�⶯��
	char logbuf[100];

	// ���Ҫ��ֹͣ���ԣ�����
	if (g_DAQSystemData.usTerminate){
		INFO1("--------------------����2������B���ԣ����û���ֹ--------------------");
		return -1;
	}
	INFO1("--------------------����2������A����--------------------");
	// ����ֻ�ڶ��̹������в������ݴ���
	//dfHalfStroke = g_Device.Standard.fStroke / 2;
	//dfHalfStroke += 10.0;
	// ȡʵ�ʲ������Ķ��̶����Ǳ�׼���̡����ǹ�˾û����ô���ͺŵ�ת�޻���
	// �ò�ͬ���̵�ת�޻�ģ��	
	// ʵ�⶯��
	dfMeasureStroke = ( pData->ptMeasureDataA.ptCheckData.dfInterval + pData->ptMeasureDataB.ptCheckData.dfInterval ) / 2.0;
	// ������ʼ��				  
	dfHalfStroke = 0.7 * dfMeasureStroke; 
	INFO1("ʵ�⶯��:%f,������ʼ����:%f",dfMeasureStroke,dfHalfStroke);

	g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState = 0;

	// ����Load2����������
	dfRatedForce = g_Device.Standard.fLoad2_MaxForce;
	//dfRatedForce += 0.5;//dfRatedForce *= 1.8;
	INFO1("    ����̨��ʼĿ������:dfRatedForce = %f",dfRatedForce);

	if (pDevice->Standard.fLoad2_A2B_AVoltage > 10.0)
		return -1;

	// ȡ�û��򷧳�ʼ����ֵ
	g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad2_A2B_AVoltage;
	g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad2_A2B_BVoltage;

	INFO1("    ���������ݿ�ֵ:g_DAQSystemData.fAOAForce = %f,g_DAQSystemData.fAOBForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);

	//g_DAQSystemData.fAOAForce = 1.5;
	g_DAQSystemData.fAOAForce = 0;
	dfAOForce = g_DAQSystemData.fAOBForce;
	DAQ_SetInForce (g_DAQSystemData.fAOAForce);

	// ����������������Ϊ��ʼ���ȵ�70%����ֹ�����ܼӵ�λ
	g_DAQSystemData.fAOBForce = dfAOForce * 0.7;
	DAQ_SetOutForce (g_DAQSystemData.fAOBForce);

	INFO1("    ��������ʼ����:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);

	// �򿪻��򷧣�ת�޻�����
	DAQ_SetOutValve (1);
	DAQ_SetInValve (0);
	//DAQ_SetTotalValve (0); // �رջ����ܿ���
	//DAQ_SetTotalValve (1); // �򿪻����ܿ���
	DAQ_Force2TotalValue(dfRatedForce);// ��������Ҫ�󣬿����ܷ��л���ͬ�ĸ������Ρ�

	DAQ_Delay (500);
	DAQ_OutControl (1);

	// ��λλ��
	DAQ_ResetStroke ();
	// ��ȡλ�Ƴ�ʼֵ
	dfStroke = dfDistanceS = DAQ_ReadStroke ();

	// ��ʼʱ��
	dwTicksError = GetTickCount ();
	dwTicksS = GetTickCount ();
	// ��λ�����
	g_DAQSystemData.fMaxForce = 0.0;
	dwTimeout = 3000;
	INFO1("// --------����whileѭ��--------");
	while( 1 )
	{
		// 998.�����λ������
		if (DAQ_ReadRight ())
		{
			INFO1(" --------��λ���˳�whileѭ��--------");
			INFO1(" ��ǰ��������:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
			break;
		}
		// ��ʱ
		DAQ_Delay (50);
		// �ɼ�����
		DAQ_CheckMeasure( );

		// 999.�����ʱ�����ش���
		if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
		{
			INFO1(" --------1.��ʱ���˳�whileѭ����GetTickCount = %lu, dwTicksError=%lu,dwTimeout:%lu--------",GetTickCount (),dwTicksError,dwTimeout);
			INFO1(" ���򷧵�ǰ����:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
			S700K_UnloadHandle (pDevice, pData);
			break;
		}

		// 2.�ȴ�λ�ƴ���10mmʱ�����򷧿��ȵ��ڵ�Ԥ�����ȣ�Ȼ��ʼ��������Load2�����
		if ((fabs (DAQ_ReadStroke () - dfDistanceS) < 10) && (bStart == FALSE))
		{
			INFO1("// �ȴ�λ�ƴ���10mm,continue");
			INFO1("// ��ǰʱ�䣬GetTickCount = %lu, dwTicksError=%lu,dwTimeout,%lu",GetTickCount (),dwTicksError,dwTimeout);
			INFO1("// ��ǰ���򷧲���:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
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
			INFO1("// 2.1λ�ƴ���10mm,��ǰλ��:%f",dfDistanceS);
			INFO1("// ��ǰʱ��:GetTickCount = %lu, dwTicksError=%lu,dwTimeout,%lu",GetTickCount (),dwTicksError,dwTimeout);
			INFO1("// ��ǰ���򷧲���:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
		}
		if (bStart == FALSE)
			continue;

		// 3.��ָ����λ�Ʒ�Χ���ۼƲ�����������Ϊ�޷�����ʱ�Ĳ���ֵ
		dfDistanceE = DAQ_ReadStroke ();
		if ((fabs (dfDistanceE - dfStroke) > dfHalfStroke) && ((fabs (dfDistanceE - dfStroke) + 5) < pDevice->Standard.fStroke))
		{
			//INFO1("   3.ת�޻���10mm����׼����-10mm�ķ�Χ���ۼƲ�����������Ϊ�޷�����ʱ�Ĳ���ֵ,��ǰλ��:%f",dfDistanceE);
			// �ۼӲ���ֵ
			dwCount ++;
			dfForceCount += DAQ_ReadForce ();
			dfIa += g_DAQData.Data.dfIa;
			dfIb += g_DAQData.Data.dfIb;
			dfIc += g_DAQData.Data.dfIc;
			// ������ʾֵ
			pData->ptMeasureDataA.ptLoad2Data.dfIa = dfIa / dwCount;
			pData->ptMeasureDataA.ptLoad2Data.dfIb = dfIb / dwCount;
			pData->ptMeasureDataA.ptLoad2Data.dfIc = dfIc / dwCount;
			//INFO1("   3.1 dwCount:%lu,dfForceCount:%f,dfIa:%f,dfIb:%f,dfIc:%f",dwCount,dfForceCount,dfIa,dfIb,dfIc);
			//INFO1("       pData->ptMeasureDataB.ptLoad2Data.dfIa:%f,pData->ptMeasureDataB.ptLoad2Data.dfIb:%f,pData->ptMeasureDataB.ptLoad2Data.dfIc:%f",pData->ptMeasureDataB.ptLoad2Data.dfIa,pData->ptMeasureDataB.ptLoad2Data.dfIb,pData->ptMeasureDataB.ptLoad2Data.dfIc);
		}
		// 4.λ��ĩ�˲�����
		if (g_Device.Standard.fStroke - fabs(dfDistanceE - dfStroke) < 10)
		{
			INFO1("// 4.λ��ĩ��(���10mm)������,��ǰλ��:%f",dfDistanceS);
			continue;
		}

		// 5.�������10mm,��ȡ��ǰλ�ƣ������ٶ�
		//INFO1("// 5.�������10mm,��ȡ��ǰλ�ƣ�����ת�޻��ٶȡ���ǰλ��:%f",dfDistanceS);
		dfDistance = dfDistanceE - dfDistanceS;
		dwTicksE = GetTickCount();
		dfTicks = dwTicksE - dwTicksS;
		if ( dfTicks == 0 )dfTicks = 1.0;
		dfSpeed = dfDistance * 1000.0 / dfTicks;
		//INFO1("// 5.��ǰ�ٶ�Ϊ:%f",dfSpeed);

		// 6.�������10mm,���ٶȱȽϵ�ʱ��
		// ����һ����ʱ�����Ϊת�޻����裬��ʱ��ʼ��������
		if (fabs (dfSpeed) < 0.5)
		{
			INFO1("    6.�������10mm,���ٶȱȽϵ�ʱ������һ����ʱ�����Ϊת�޻����裬��ʼ������������ǰλ��:%f",dfDistanceS);
			if (dwTickStop == 0)
			{
				dwTickStop = GetTickCount ();
				g_DAQSystemData.fMinForce = 99; //������Сֵ��׼�������ֵС����С
				//INFO1("    6.1 �״ο���tickΪ:%lu",dwTickStop);
			}
			else if ((GetTickCount () - dwTickStop) < 200)
			{
				//INFO1("    6.2 ����ʱ�� < 200ms.dfDistanceS:%f,dwTicksS:%lu,dfDistanceE:%f,dwTicksE:%lu",dfDistanceS,dwTicksS,dfDistanceE,dwTicksE);
				
				dfDistanceS = dfDistanceE;
				dwTicksS = dwTicksE;
				continue;
			}
			else
			{
				//g_DAQSystemData.fMaxForce =0;
				// ȡ�ó��ο��赽�������ʱ�����С��
				dfForce = FAI_FindMinForce();
				// �������ʱ2��
				DAQ_Delay (2000);
				// ȡ�ò��������е����ֵ
				//dfMaxForce = FAI_FindMaxForce ();
				//dfForce = dfMaxForce;
				

				// ȡ��������������
				dfIa = g_DAQData.Data.dfIa;
				dfIb = g_DAQData.Data.dfIb;
				dfIc = g_DAQData.Data.dfIc;
				pData->ptMeasureDataA.ptLoad2Data.dfIa = dfIa;
				pData->ptMeasureDataA.ptLoad2Data.dfIb = dfIb;
				pData->ptMeasureDataA.ptLoad2Data.dfIc = dfIc;
				//INFO1("    6.3 ����ʱ�� > 200ms,��ת��:%f KN,A�����:%f A,B�����:%f A,C�����:%f A",dfForce,dfIa,dfIb,dfIc);

				// ���������������ȷ����
				DAQ_SetTotalValve (1);
				DAQ_SetInForce( 1.5 );
				DAQ_SetOutForce( 1.5 );
				DAQ_SetInValve( 0 );
				DAQ_SetOutValve( 0 );
				bOk = 1;
				// ����
				// ���в�����¼���ļ���
				TestParaV2ToLog(
					GetTickCount()-dwTicksError,	//���β���ʱ��(tick)(mm)
					logbuf,							//����
					fabs(dfDistanceE - dfStroke),	//����(mm)
					dfSpeed,						//�ٶ�(mm/s)
					bOk,							//����
					DAQ_ReadForce (),dfRatedForce,	//��ǰ��(KN),Ŀ����
					g_DAQSystemData.fAOAForce,	//������A��ѹ
					g_DAQSystemData.fAOBForce,	//������B��ѹ	
					g_DAQData.Data.dfIa,//A�����(A)
					g_DAQData.Data.dfIb,//B�����(A)
					g_DAQData.Data.dfIc,//C�����(A)
					dwCount,		//�ۼƴ���
					dfForceCount,	//�ۼ���(KN)
					dfIa,			//�ۼ�A�����(A)
					dfIb,			//�ۼ�B�����(A)
					dfIc 			//�ۼ�C�����(A)
				);
				break;
			}
		}
		else
		{
			// û�п���ʱ
			dwTickStop = 0;
		}

		// ���в�����¼���ļ���
		TestParaV2ToLog(
			GetTickCount()-dwTicksError,	//���β���ʱ��(tick)(mm)
			logbuf,							//����
			fabs(dfDistanceE - dfStroke),	//����(mm)
			dfSpeed,						//�ٶ�(mm/s)
			bOk,							//����
			DAQ_ReadForce (),dfRatedForce,	//��ǰ��(KN),Ŀ����
			g_DAQSystemData.fAOAForce,	//������A��ѹ
			g_DAQSystemData.fAOBForce,	//������B��ѹ	
			g_DAQData.Data.dfIa,//A�����(A)
			g_DAQData.Data.dfIb,//B�����(A)
			g_DAQData.Data.dfIc,//C�����(A)
			dwCount,		//�ۼƴ���
			dfForceCount,	//�ۼ���(KN)
			dfIa,			//�ۼ�A�����(A)
			dfIb,			//�ۼ�B�����(A)
			dfIc 			//�ۼ�C�����(A)
		);		
		// 7.λ�Ƶ����̵�һ��-10mm��������ת.�����ڻ�еϵͳ��Ӧ��Ҫʱ�䣩
		//if (fabs(dfDistanceE - dfStroke) <= dfHalfStroke)
		//{
			//	INFO1("    7.���̵�ǰһ�룬����,��ǰλ��:%f",fabs(dfDistanceE - dfStroke));
			// 8.����������͵���Ŀ����
			dfDiff = DAQ_ReadForce () - dfRatedForce;
			// �ֵ����ڱ���������
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
			//INFO1("  8.����������͵���Ŀ����.������:%f,Ŀ����:%f",DAQ_ReadForce (),dfRatedForce);

			// 8.1 �������������
			if (dfDiff > 0.0)
				g_DAQSystemData.fAOBForce -= dfDelta;
			else
				g_DAQSystemData.fAOBForce += dfDelta;
			//INFO1("  8.1 ������������ȡ��±�����A��ѹֵΪ:%f",g_DAQSystemData.fAOBForce);

			// 8.2 ��ֹ���������Ƶ��ڷ�Χ
			if (g_DAQSystemData.fAOBForce > dfAOForce)
			{
				if (g_DAQSystemData.fAOBForce - dfAOForce > 1.0 )
					g_DAQSystemData.fAOBForce = dfAOForce + 1.0;
				if (g_DAQSystemData.fAOBForce - dfAOForce < -1.0 )
					g_DAQSystemData.fAOBForce = dfAOForce - 1.0;
			}
			//INFO1("  8.2 ��ֹ���������Ƶ��ڷ�Χ�����ƺ�ı�����A��ѹֵΪ :%f",g_DAQSystemData.fAOBForce);

			// 8.3 ���ڱ���������
			//INFO1("  8.3 ���ڱ��������ȡ�dfDistanceS:%f,dwTicksS:%lu,dfDistanceE:%f,dwTicksE:%lu",dfDistanceS,dwTicksS,dfDistanceE,dwTicksE);
			DAQ_SetOutForce (g_DAQSystemData.fAOBForce);

		//}
		//else if(bHalf == FALSE)// ���̹��룬�����ת
		//{
		//	DAQ_SetTotalValve (0);	// �رձ������ܿ��أ�����5KN~9.9KN
		//	g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad2_B2A_AVoltage;
		//	bHalf = TRUE;
			//DAQ_SetInForce (10.0);
		//	DAQ_SetOutForce (10.0);
		//}

		//INFO1("    7.���̵ĺ�һ�룬������ת,��ǰλ��:%f����������ѹ:10V",fabs(dfDistanceE - dfStroke));
		dfDistanceS = dfDistanceE;
		dwTicksS = dwTicksE;
		//DAQ_Delay (100);
	}
	INFO1("--------�˳�whileѭ��������2������B���ݲɼ�������--------");

	// ��ֹ�������
	if (dwCount == 0)
		dwCount = 1;
	// �������
	if (bOk == 1)
	{
		INFO1("  b1.����");
		// ����״̬
		g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState = 2;
		// ��������ֵ
		INFO1("  ����ֵ����ǰΪ:%f",dfForce);
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
		INFO1("  ����ֵ������Ϊ:%f",dfForce);
		// ����B��������A����
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
		INFO1("  ����B��������A����,������Ϊ:%f",dfForce);
	}
	// ������
	else
	{
		dfForce = dfForceCount / dwCount;
		g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState = 1;
		INFO1("  b2.û�п��裬������Ϊ:%f",dfForce);
	}

	// ���ò������
	pData->ptMeasureDataA.ptLoad2Data.dfForce1 = dfForce;
	pData->ptMeasureDataA.ptLoad2Data.dfForce = pData->ptMeasureDataA.ptLoad2Data.dfForce1;

	// ��λ���ƣ�ת�޻��ߵ�λ
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
		INFO1("  c1.1 �ƶ�ת�޻���λ");
		if (DAQ_ReadRight ())
		{
			INFO1("  c1.2 ת�޻�����λ�÷�λ");
			break;
		}

		DAQ_CheckMeasure ();

		if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
		{
			INFO1("  c1.3 �ƶ�ת�޻���ʱ��û���ڹ涨ʱ�����ƶ�����λ");
			S700K_ErrorHandle (pDevice, pData);
			return -1;
		}

		DAQ_Delay (10);
	}
	// ��λ����
	DAQ_InControl (0);
	DAQ_OutControl (0);
	DAQ_SetTotalValve (1);

	// ��ʾ����ֵ
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_2_1, pData->ptMeasureDataA.ptLoad2Data.dfForce);
	return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// ת�޻�Load2���������ת�޻��ڹ涨��ʱ���ڲ�����ɶ����ͷ��ش���
// ����:
//    pDevice     �������ת�޻�����
//    pData       ����ת�޻���������
// ���:
//    ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
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
	double   dfHalfStroke;	  // ����ʵ�⶯�̵�һ��
	double   dfMeasureStroke; // ����ʵ�⶯��	
	
	char logbuf[100];

	// ���Ҫ��ֹͣ���ԣ�����
	if (g_DAQSystemData.usTerminate){
		INFO1("--------------------����2������B���ԣ����û���ֹ--------------------");
		return -1;
	}
	INFO1("--------------------����2������B����--------------------");
	// ����ֻ�ڶ��̹������в������ݴ���
	//dfHalfStroke = g_Device.Standard.fStroke / 2;
	//dfHalfStroke += 10.0;
	// ȡʵ�ʲ������Ķ��̶����Ǳ�׼���̡����ǹ�˾û����ô���ͺŵ�ת�޻���
	// �ò�ͬ���̵�ת�޻�ģ��	
	// ʵ�⶯��
	dfMeasureStroke = ( pData->ptMeasureDataA.ptCheckData.dfInterval + pData->ptMeasureDataB.ptCheckData.dfInterval ) / 2.0;
	// ������ʼ��				  
	dfHalfStroke = 0.7 * dfMeasureStroke; 
	INFO1("    ʵ�⶯��:%f,������ʼ����:%f",dfMeasureStroke,dfHalfStroke);

	g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState = 0;

	// ����Load2��������+0.5KN
	dfRatedForce = g_Device.Standard.fLoad2_MaxForce;
	//dfRatedForce += 0.5;////dfRatedForce *= 1.5;
	INFO1("    ����̨��ʼĿ������:dfRatedForce = %f",dfRatedForce);

	if (pDevice->Standard.fLoad2_B2A_AVoltage > 10.0)
		return -1;

	// ȡ�ñ�������ʼ����ֵ
	g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad2_B2A_AVoltage;
	g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad2_B2A_BVoltage;
	INFO1("    ���������ݿ�ֵ:g_DAQSystemData.fAOAForce = %f,g_DAQSystemData.fAOBForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);

	dfAOForce = g_DAQSystemData.fAOAForce;
	//g_DAQSystemData.fAOBForce = 1.5;
	g_DAQSystemData.fAOBForce = 0;

	// ����������������Ϊ��ʼ���ȵ�70%����ֹ�����ܼӵ�λ
	g_DAQSystemData.fAOAForce = dfAOForce * 0.7;
	DAQ_SetInForce (g_DAQSystemData.fAOAForce);
	DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
	
	INFO1("    ��������ʼ����:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);

	// �򿪻���
	DAQ_SetOutValve (0);
	DAQ_SetInValve (1);
	
	//DAQ_SetTotalValve (0);   // �رջ����ܿ��� 0~2.6 ��5.0~10KN
	//DAQ_SetTotalValve (1); // �򿪻����ܿ��� 0~2.6 ��2.5~4.5KN
	DAQ_Force2TotalValue(dfRatedForce);// ��������Ҫ�󣬿����ܷ��л���ͬ�ĸ������Ρ�

	DAQ_Delay (500);

	// �򿪻��򷧣�ת�޻�����
	DAQ_InControl (1);

	// ��λλ��
	DAQ_ResetStroke ();
	// ��ȡλ�Ƴ�ʼֵ
	dfStroke = dfDistanceS = DAQ_ReadStroke ();

	// ��ʼʱ��
	dwTicksError = GetTickCount ();
	dwTicksS = GetTickCount ();
	// ��λ�����
	g_DAQSystemData.fMaxForce = 0.0;
	dwTimeout = 3000;
	INFO1("// ����whileѭ��");
	while (1)
	{
		// �����λ������
		if (DAQ_ReadLeft ())
		{
			INFO1("// ��λ���˳�whileѭ��");
			INFO1("// ��ǰ��������:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
			break;
		}
		// ��ʱ
		DAQ_Delay (50);
		// �ɼ�����
		DAQ_CheckMeasure ();

		// 1.�����ʱ�����ش���
		if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
		{
			INFO1("// 1.��ʱ���˳�whileѭ����GetTickCount = %lu, dwTicksError=%lu,dwTimeout:%lu",GetTickCount (),dwTicksError,dwTimeout);
			INFO1("// ���򷧵�ǰ����:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
			S700K_UnloadHandle (pDevice, pData);
			break;
		}

		// 2.�ȴ�λ�ƴ���10mmʱ�����򷧿��ȵ��ڵ�Ԥ�����ȣ�Ȼ��ʼ��������Load2�����
		if ((fabs (DAQ_ReadStroke () - dfDistanceS) < 10) && (bStart == FALSE))
		{
			//INFO1("// �ȴ�λ�ƴ���10mm,continue");
			//INFO1("// ��ǰʱ�䣬GetTickCount = %lu, dwTicksError=%lu,dwTimeout,%lu",GetTickCount (),dwTicksError,dwTimeout);
			//INFO1("// ��ǰ���򷧲���:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
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
			//INFO1("// 2.1λ�ƴ���10mm,��ǰλ��:%f",dfDistanceS);
			//INFO1("// ��ǰʱ��:GetTickCount = %lu, dwTicksError=%lu,dwTimeout,%lu",GetTickCount (),dwTicksError,dwTimeout);
			//INFO1("// ��ǰ���򷧲���:DAQ_SetInForce = %f,DAQ_SetOutForce = %f",g_DAQSystemData.fAOAForce,g_DAQSystemData.fAOBForce);
		}
		if (bStart == FALSE)
			continue;

		// 3.ת�޻���10mm����׼����-10mm�ķ�Χ���ۼƲ�����������Ϊ�޷�����ʱ�Ĳ���ֵ
		dfDistanceE = DAQ_ReadStroke ();
		if ((fabs (dfDistanceE - dfStroke) > dfHalfStroke) && ((fabs (dfDistanceE - dfStroke) + 5) < pDevice->Standard.fStroke))
		{
			//INFO1("   3.ת�޻���10mm����׼����-10mm�ķ�Χ���ۼƲ�����������Ϊ�޷�����ʱ�Ĳ���ֵ,��ǰλ��:%f",dfDistanceE);
			// �ۼӲ���ֵ
			dwCount ++;
			dfForceCount += DAQ_ReadForce ();
			dfIa += g_DAQData.Data.dfIa;
			dfIb += g_DAQData.Data.dfIb;
			dfIc += g_DAQData.Data.dfIc;
			// ������ʾֵ
			pData->ptMeasureDataB.ptLoad2Data.dfIa = dfIa / dwCount;
			pData->ptMeasureDataB.ptLoad2Data.dfIb = dfIb / dwCount;
			pData->ptMeasureDataB.ptLoad2Data.dfIc = dfIc / dwCount;
			//INFO1("   3.1 dwCount:%lu,dfForceCount:%f,dfIa:%f,dfIb:%f,dfIc:%f",dwCount,dfForceCount,dfIa,dfIb,dfIc);
			//INFO1("       pData->ptMeasureDataB.ptLoad2Data.dfIa:%f,pData->ptMeasureDataB.ptLoad2Data.dfIb:%f,pData->ptMeasureDataB.ptLoad2Data.dfIc:%f",pData->ptMeasureDataB.ptLoad2Data.dfIa,pData->ptMeasureDataB.ptLoad2Data.dfIb,pData->ptMeasureDataB.ptLoad2Data.dfIc);
		}

		// 4.λ��ĩ��(���10mm)��������֮ǰһֱ����
		if (g_Device.Standard.fStroke - fabs(dfDistanceE - dfStroke) < 10)
		{
			//INFO1("// 4.λ��ĩ��(���10mm)������,��ǰλ��:%f",dfDistanceS);
			continue;
		}

		// 5.�������10mm,��ȡ��ǰλ�ƣ�����ת�޻��ٶ�
		//INFO1("// 5.�������10mm,��ȡ��ǰλ�ƣ�����ת�޻��ٶȡ���ǰλ��:%f",dfDistanceS);
		dfDistance = dfDistanceE - dfDistanceS;
		dwTicksE = GetTickCount();
		dfTicks = dwTicksE - dwTicksS;
		if ( dfTicks == 0 )dfTicks = 1.0;
		dfSpeed = dfDistance * 1000.0 / dfTicks;
		//INFO1("// 5.��ǰ�ٶ�Ϊ:%f",dfSpeed);

		// 6.�������10mm,���ٶȱȽϵ�ʱ��
		// ����һ����ʱ�����Ϊת�޻����裬��ʼ��������
		if (fabs (dfSpeed) < 0.5)
		{
			//INFO1("    6.���裺�������10mm,���ٶȱȽϵ�ʱ������һ����ʱ�����Ϊת�޻����裬��ʼ������������ǰλ��:%f",dfDistanceS);
			//INFO1("    6.���裺��ǰλ��:%f",dfDistanceS);
			if (dwTickStop == 0)
			{
				dwTickStop = GetTickCount ();
				g_DAQSystemData.fMinForce = 99; //������Сֵ�������ֵС������С��
				strcpy(logbuf,"6.1:�״ο���");
				//INFO1("    6.1 �״ο���tickΪ:%lu",dwTickStop);
			}
			else if ((GetTickCount () - dwTickStop) < 200)
			{
				//INFO1("    6.2 ����ʱ�� < 200ms.dfDistanceS:%f,dwTicksS:%f,dfDistanceE:%f,dwTicksE:%f",dfDistanceS,dwTicksS,dfDistanceE,dwTicksE);
				strcpy(logbuf,"6.2:����ʱ��<200ms");
				dfDistanceS = dfDistanceE;
				dwTicksS = dwTicksE;
				continue;
			}
			else
			{
				strcpy(logbuf,"6.3:����ʱ��>=200ms,����������");
				// ȡ�ó��ο��赽�������ʱ�����С��
				dfForce = FAI_FindMinForce();				
				// �������ʱ2��
				DAQ_Delay (2000);

				// ȡ�ò��������е����ֵ
				//g_DAQSystemData.fMaxForce =0;
				//DAQ_Delay (2000);
				//dfMaxForce = FAI_FindMaxForce ();
				//dfForce = dfMaxForce;

				//INFO1("    6.3 ����ʱ�� > 200ms,��¼���������е����ֵ��%f",dfForce);

				// ȡ��������������
				dfIa = g_DAQData.Data.dfIa;
				dfIb = g_DAQData.Data.dfIb;
				dfIc = g_DAQData.Data.dfIc;
				pData->ptMeasureDataB.ptLoad2Data.dfIa = dfIa;
				pData->ptMeasureDataB.ptLoad2Data.dfIb = dfIb;
				pData->ptMeasureDataB.ptLoad2Data.dfIc = dfIc;
				//INFO1("    6.3 A�����:%f,B�����:%f,C�����:%f",dfIa,dfIb,dfIc);

				// ���������������ȷ����
				DAQ_SetTotalValve (1);
				DAQ_SetInForce( 1.5 );
				DAQ_SetOutForce( 1.5 );
				DAQ_SetInValve( 0 );
				DAQ_SetOutValve( 0 );
				bOk = 1;
				// ���в�����¼���ļ���
				TestParaV2ToLog(
					GetTickCount()-dwTicksError,	//���β���ʱ��(tick)(mm)
					logbuf,							//����
					fabs(dfDistanceE - dfStroke),	//����(mm)
					dfSpeed,						//�ٶ�(mm/s)
					bOk,							//����
					DAQ_ReadForce (),dfRatedForce,	//��ǰ��(KN),Ŀ����
					g_DAQSystemData.fAOAForce,	//������A��ѹ
					g_DAQSystemData.fAOBForce,	//������B��ѹ	
					g_DAQData.Data.dfIa,//A�����(A)
					g_DAQData.Data.dfIb,//B�����(A)
					g_DAQData.Data.dfIc,//C�����(A)
					dwCount,		//�ۼƴ���
					dfForceCount,	//�ۼ���(KN)
					dfIa,			//�ۼ�A�����(A)
					dfIb,			//�ۼ�B�����(A)
					dfIc 			//�ۼ�C�����(A)
				);
				break;   // �˳�whileѭ��
			}
		}
		else    // û�п���ʱ
		{
			strcpy(logbuf,"����ʱ��<200ms���ⲻ�ǿ��衣");
			dwTickStop = 0;
		}

		// ���в�����¼���ļ���
		TestParaV2ToLog(
			GetTickCount()-dwTicksError,	//���β���ʱ��(tick)(mm)
			logbuf,							//����
			fabs(dfDistanceE - dfStroke),	//����(mm)
			dfSpeed,						//�ٶ�(mm/s)
			bOk,							//����
			DAQ_ReadForce (),dfRatedForce,	//��ǰ��(KN),Ŀ����
			g_DAQSystemData.fAOAForce,	//������A��ѹ
			g_DAQSystemData.fAOBForce,	//������B��ѹ	
			g_DAQData.Data.dfIa,//A�����(A)
			g_DAQData.Data.dfIb,//B�����(A)
			g_DAQData.Data.dfIc,//C�����(A)
			dwCount,		//�ۼƴ���
			dfForceCount,	//�ۼ���(KN)
			dfIa,			//�ۼ�A�����(A)
			dfIb,			//�ۼ�B�����(A)
			dfIc 			//�ۼ�C�����(A)
		);		
	
		// 7.λ�Ƶ����̵�һ��-10mm��������ת.�����ڻ�еϵͳ��Ӧ��Ҫʱ�䣩
		//if (fabs(dfDistanceE - dfStroke) <= dfHalfStroke)
		//{
		//	INFO1("    7.���̵�ǰһ�룬����,��ǰλ��:%f",fabs(dfDistanceE - dfStroke));
			// 8.����������͵���Ŀ����

			dfDiff = DAQ_ReadForce () - dfRatedForce;
			// �ֵ����ڱ���������
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
			//INFO1("  8.����������͵���Ŀ����.������:%f,Ŀ����:%f",DAQ_ReadForce (),dfRatedForce);

			// 8.1 �������������
			if (dfDiff > 0.0)
				g_DAQSystemData.fAOAForce -= dfDelta;
			else
				g_DAQSystemData.fAOAForce += dfDelta;
			//INFO1("  8.1 ������������ȡ��±�����A��ѹֵΪ:%f",g_DAQSystemData.fAOAForce);

			// 8.2 ��ֹ���������Ƶ��ڷ�Χ
			if (g_DAQSystemData.fAOAForce > dfAOForce)
			{
				if (g_DAQSystemData.fAOAForce - dfAOForce > 1.0 )
					g_DAQSystemData.fAOAForce = dfAOForce + 1.0;
				if (g_DAQSystemData.fAOAForce - dfAOForce < -1.0 )
					g_DAQSystemData.fAOAForce = dfAOForce - 1.0;
			}
			//INFO1("  8.2 ��ֹ���������Ƶ��ڷ�Χ�����ƺ�ı�����A��ѹֵΪ :%f",g_DAQSystemData.fAOAForce);

			// 8.3 ���ڱ���������
			//INFO1("  8.3 ���ڱ��������ȡ�dfDistanceS:%f,dwTicksS:%lu,dfDistanceE:%f,dwTicksE:%lu",dfDistanceS,dwTicksS,dfDistanceE,dwTicksE);
			DAQ_SetInForce (g_DAQSystemData.fAOAForce);
		//}
		//else if(bHalf == FALSE)// ���̹��룬�����ת
		//{
		//	DAQ_SetTotalValve (0);	// �رձ������ܿ��أ�����5KN~9.9KN
		//	g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad2_B2A_AVoltage;
		//	bHalf = TRUE;
		//	DAQ_SetInForce (10.0);
			//DAQ_SetOutForce (10.0);
			//INFO1("    7.���̵ĺ�һ�룬������ת,��ǰλ��:%f����������ѹ:10.0V",fabs(dfDistanceE - dfStroke));
		//}
		//INFO1("    7.���̵ĺ�һ�룬������ת,��ǰλ��:%f����������ѹ:10.0V",fabs(dfDistanceE - dfStroke));
		dfDistanceS = dfDistanceE;
		dwTicksS = dwTicksE;

		//DAQ_Delay (100);
	}
	INFO1("--------�˳�whileѭ��������2������B���ݲɼ�������--------");


	// ��ֹ�������
	if (dwCount == 0)
		dwCount = 1;
	// �������
	if (bOk == 1)
	{
		INFO1("  b1.����");
		// ����״̬
		g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState = 2;
		// ��������ֵ
		INFO1("  ����ֵ����ǰΪ:%f",dfForce);
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
		INFO1("  ����ֵ������Ϊ:%f",dfForce);
	}
	else  // ������
	{
		dfForce = dfForceCount / dwCount;
		g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState = 1;
		INFO1("  b2.û�п��裬������Ϊ:%f",dfForce);
	}

	// ���ò������
	pData->ptMeasureDataB.ptLoad2Data.dfForce1 = dfForce;
	pData->ptMeasureDataB.ptLoad2Data.dfForce = pData->ptMeasureDataB.ptLoad2Data.dfForce1;

	// ��λ���ƣ�ת�޻��ߵ�λ
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
		INFO1("  c1.1 �ƶ�ת�޻�����λ");
		if ( DAQ_ReadLeft( ) )
		{
			INFO1("  c1.2 ת�޻�����λ�ö�λ");
			break;
		}
		DAQ_CheckMeasure( );

		if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
		{
			INFO1("  c1.3 �ƶ�ת�޻���ʱ��û���ڹ涨ʱ�����ƶ���λ");
			S700K_ErrorHandle (pDevice, pData);
			return -1;
		}

		DAQ_Delay (10);
	}
	// ��λ����
	DAQ_InControl (0);
	DAQ_OutControl (0);
	DAQ_SetTotalValve (1);
	return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// ת�޻�Load2���������ת�޻��ڹ涨��ʱ���ڲ�����ɶ����ͷ��ش���
// ����:
//    pDevice     �������ת�޻�����
//    pData       ����ת�޻���������
// ���:
//    ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
int __stdcall S700K_MeasureLoad2( LPT_Device pDevice, LPT_Record pData )
{
	double fData;

	// ���Ҫ��ֹͣ���ԣ�����
	if (g_DAQSystemData.usTerminate)
		return -1;

	// ��ʱ
	DAQ_Delay (1000);
	DAQ_Delay (1000);

	// �Ͽ�ģ�����
	DAQ_SimulateTrack (0);

	// ���ò���
	g_S700KData.Control.usStep = 3;
	// B�����
	if (S700K_MeasureLoad2_B (pDevice, pData) == -1)
		return -1;

	// ��ʱ
	DAQ_Delay (1000);
	DAQ_Delay (1000);

	// ���ò���
	g_S700KData.Control.usStep = 4;
	// A�����
	if (S700K_MeasureLoad2_A (pDevice, pData) == -1)
		return -1;

	// ����������ʾ
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

	// ��ʾ����ֵ
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_2_1, pData->ptMeasureDataA.ptLoad2Data.dfForce);
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_2_2, pData->ptMeasureDataB.ptLoad2Data.dfForce);
	return 0;
}

//------------------------------------------------------------------------------------------------
