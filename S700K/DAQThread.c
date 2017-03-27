// #########################################################################
// *************************************************************************
// ת�޻������߳�
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
// ����ȫ�ֱ���
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

	// ���
	if (strlen (g_Device.Standard.acModelName) == 0)
	{
		MessageBox (NULL, "��Ч������!", "Error", MB_OK | MB_TOPMOST);
		return 0;
	}
	if (!g_DAQData.Data.usAutoMode)
	{
		MessagePopup ("��ʾ", "�ֶ�ģʽ�²��������!");
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
// ��ȡAλ��λ״̬
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//
//------------------------------------------------------------------------------------------------
void __stdcall DAQDIReadLeft(void)
{

	// ����ϵͳ����
//   FX2N_Read_DIO ();

	g_DAQData.Data.usLeft = FX2N_GetStatus (DICH_JA1) == 1;
}

//------------------------------------------------------------------------------------------------
// ��ȡBλ��λ״̬
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//
//------------------------------------------------------------------------------------------------
void __stdcall DAQDIReadRight(void)
{
	// ����ϵͳ����
//   FX2N_Read_DIO ();

	g_DAQData.Data.usRight = FX2N_GetStatus (DICH_JA2) == 1;
}

//------------------------------------------------------------------------------------------------
// ��ȡ����ģʽ״̬
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//
//------------------------------------------------------------------------------------------------
void __stdcall DAQDIReadMode(void)
{
	// ����ϵͳ����
//   FX2N_Read_DIO ();

	g_DAQData.Data.usAutoMode = FX2N_GetStatus (DICH_SB7) == 1;
}

//------------------------------------------------------------------------------------------------
// �����ݲɼ�����ȡ������״̬
// ����:
//    pData       �洢�ɼ����ݵĽṹ��
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall DAQ_ReadDIStatus( LPT_DAQData pData )
{
	USHORT   ushValue;

	FX2N_Read_DIO ();
	// ��ȡAλָʾ
	DAQDIReadLeft ();
	// ��ȡBλָʾ
	DAQDIReadRight ();
	// ��ȡ����ģʽ
	DAQDIReadMode ();
	
	

	// �ȼ�״̬
	g_DAQData.Data.usFR1 = FX2N_GetStatus (DICH_FR3) == 0;
	// �ȼ�״̬
	g_DAQData.Data.usFR2 = FX2N_GetStatus (DICH_FR1) == 1;
	// ȱ�ౣ��״̬
	g_DAQData.Data.usJWXC = 0;//FX2N_GetStatus (DICH_FR2) == 0;

	return TRUE;
}
//------------------------------------------------------------------------------------------------
// ��ȡת�޻�����ʱ��
// ����:
//    dir       ����0��A����1��B����
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
double WINAPI DAQAIReadTravelTime (Direction dir)
{
	double travelTime = 0.0;
	FX2N_Read_AIO();// ��ȡD����Ԫ�� 	
	if(dir == DIRECTION_A)
		travelTime = FX2N_GetData (AI_TRAVEL_TIME_A);
	else
		travelTime = FX2N_GetData (AI_TRAVEL_TIME_B);
	return travelTime;
}
//------------------------------------------------------------------------------------------------
// ������ʾ
// ����:
//    pData       �洢�ɼ����ݵĽṹ��
// ���:
//    ��
// ����:
//    ��
//------------------------------------------------------------------------------------------------
void __stdcall DAQ_DataDisplay( LPT_DAQData pData )
{
	// ��ʾ��ѹ
//   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_UDC, pData->Data.dfUdc);
	// ��ʾ����
//   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_IDC, pData->Data.dfIdc);
	// ��ʾ��ѹ
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_UAB, pData->Data.dfUab);
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_UBC, pData->Data.dfUbc);
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_UCA, pData->Data.dfUca);
	// ��ʾ����
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_IA, pData->Data.dfIa);
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_IB, pData->Data.dfIb);
	SetCtrlVal (g_plDAQMain, DAQMAIN_NG_IC, pData->Data.dfIc);
	// ��ʾ��
	SetCtrlVal( g_plDAQMain, DAQMAIN_NG_FORCE, pData->Data.dfForce );

	// ��ʾ����
	SetCtrlVal( g_plDAQMain, DAQMAIN_NG_POWER, pData->Data.dfPower );

	// ��ʾλ��
	SetCtrlVal( g_plDAQMain, DAQMAIN_NG_DISTANCE, pData->Data.dfStroke );

	// ��ʾ״̬
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
// ��ȡλ��
// ����:
//    ��
// ���:
//    ��
// ����:
//    ʵ��λ��
//------------------------------------------------------------------------------------------------
#if 1  // �ɼ���ӹ�դ������
double WINAPI DAQ_ReadStroke( void )
{
	double   dfValue;
	// ��ȡλ��
	ADPCI1784_PIValue( &g_PCI1784, &dfValue );
	if (dfValue < 0.0)dfValue = 0.0;
	if (dfValue > 3500.0)dfValue = 3500.0;

	return dfValue;
}
#else  // �����ã�ģ���դ������
double WINAPI DAQ_ReadStroke( void )
{
	static double   dfValue = 0.0;
	// ��ȡλ��
	// ADPCI1784_PIValue( &g_PCI1784, &dfValue );
	dfValue += 0.0005;
	if(dfValue>0.24)dfValue = 0.0;

	if (dfValue < 0.0)dfValue = 0.0;
	if (dfValue > 3500.0)dfValue = 3500.0;

	return dfValue;
}
#endif

//------------------------------------------------------------------------------------------------
// ��λλ��
// ����:
//    ��
// ���:
//    ��
// ����:
//
//------------------------------------------------------------------------------------------------
double WINAPI DAQ_ResetStroke( void )
{
	ADPCI1784_Reset( &g_PCI1784 );
	return 0;
}

//------------------------------------------------------------------------------------------------
// ��ȡ������
// ����:
//    ��
// ���:
//    ��
// ����:
//    ������
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
// ��ȡAλ״̬
// ����:
//    ��
// ���:
//    ��
// ����:
//    ״̬
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
// ��ȡBλ״̬
// ����:
//    ��
// ���:
//    ��
// ����:
//    ״̬
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
// ������ģʽ״̬
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//------------------------------------------------------------------------------------------------
void WINAPI DAQCheckMode( void )
{
	static short usAutoModeOld = 0;

	// �����Զ�״̬ת��������״̬ʱ��ֹͣ�������
	if ((g_DAQData.Data.usAutoMode == 0) && (usAutoModeOld == 1))
	{
		INFO1("--------�����Զ�״̬ת��������״̬ʱ��ֹͣ�������--------");
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
// ��ȡ����ģʽ״̬
// ����:
//    ��
// ���:
//    ��
// ����:
//    ״̬
//------------------------------------------------------------------------------------------------
USHORT WINAPI DAQ_ReadMode(void)
{
	return g_DAQData.Data.usAutoMode;
}

//------------------------------------------------------------------------------------------------
// ��ʱ�ɼ�ģ������������״̬״̬
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_CheckMeasure( void )
{
	FAI_ReadAIData (&g_DAQData);
	DAQ_ReadDIStatus (&g_DAQData); // ��·�źź�ת�޻�����ʱ��
	DAQCheckMode ();
	if (g_DAQSystemData.usRunStatus == RUNSTATUS_COMPLETE)
		;
	else if (g_DAQSystemData.usRunStatus == RUNSTATUS_RUNING)
		g_S700KData.Control.ulMeasTime = GetTickCount () - g_DAQSystemData.dwMeasureTicks;
	else
		g_S700KData.Control.ulMeasTime = 0;
}

//------------------------------------------------------------------------------------------------
// ��ʱ�������Զ��������ݲɼ�
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
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
// ��鳬ʱ
// ����:
//    dwActionTime   ʵ��ʱ��
//    dwTimeout      ��ʱʱ��
// ���:
//    ��
// ����:
//    TRUE        ��ʱ
//    FALSE       ����
//------------------------------------------------------------------------------------------------
BOOL WINAPI DAQ_CheckError( DWORD dwActionTime, DWORD dwTimeout )
{
	if ( g_DAQSystemData.usTerminate == TRUE )
	{
		INFO1("--------------------����3������B���ԣ����û���ֹ--------------------");
		return TRUE;
	}
	if ( dwActionTime <= dwTimeout )
	{
		return FALSE;
	}
	return TRUE;
}

//------------------------------------------------------------------------------------------------
// �ͱÿ���
// ����:
//    bAction     TRUEʱ������FALSEʱֹͣ
// ���:
//    ��
// ����:
//    ��
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_OilBumpControl( BOOL bAction )
{
	FX2N_DOControl (DOCH_OilBumpStart, (USHORT)bAction);
}

//------------------------------------------------------------------------------------------------
// ���ؿ���
// ����:
//    bAction     TRUEʱ������FALSEʱֹͣ
// ���:
//    ��
// ����:
//    ��
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_InControl( BOOL bAction )
{
	FX2N_DOControl (DOCH_ACBack, (USHORT)bAction);
}

//------------------------------------------------------------------------------------------------
// �������
// ����:
//    bAction     TRUEʱ������FALSEʱֹͣ
// ���:
//    ��
// ����:
//    ��
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_OutControl( BOOL bAction )
{
	FX2N_DOControl (DOCH_ACForward, (USHORT)bAction );
}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
// ����Һѹ����̨���������䡣
// ����:
//    dfRatedForce     Ŀ����
// ���:
//    ��
// ����:
//               
//              
//------------------------------------------------------------------------------------------------
static BOOL gTotalValue;
void DAQ_Force2TotalValue(double dfRatedForce)
{// ��������Ҫ�󣬿����ܷ��л���ͬ�ĸ������Ρ�
	if(dfRatedForce < 3.5){
		gTotalValue = 1; // ���ܷ� 3.0~3.5KN
	}else{
		gTotalValue = 0; // �ر��ܷ� >3.7KN
	}
	DAQ_SetTotalValve (gTotalValue);
	INFO1("    Ŀ�긺����: %f(KN)���ܷ�: %d��",dfRatedForce,gTotalValue);
}

//------------------------------------------------------------------------------------------------
// ��ȡҺѹ����̨�ܷ�״̬��
// ����:
//    ��
// ���:
//    �� 
// ����:
//    1���ܷ��򿪣�0�ܷ��رա�           
//              
//------------------------------------------------------------------------------------------------
BOOL DAQ_GetTotalValue(void)
{
	return gTotalValue;
}
//------------------------------------------------------------------------------------------------
// �ܻ��򷧿���
// ����:
//    bAction     TRUEʱ������FALSEʱֹͣ
// ���:
//    ��
// ����:
//    ��
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_SetTotalValve( BOOL bAction )
{
	FX2N_DOControl (DOCH_TotalValve, (USHORT)bAction );
}

//------------------------------------------------------------------------------------------------
// ������򷧿���
// ����:
//    bAction     TRUEʱ������FALSEʱֹͣ
// ���:
//    ��
// ����:
//    ��
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_SetOutValve( BOOL bAction )
{
	//FX2N_DOControl (DOCH_BackValve, (USHORT)bAction );
	//FX2N_DOControl (DOCH_ForwardValve, (USHORT)bAction );
	if(g_S700KData.Control.usMount == 1) // ת�޻���װ��ʽ����Ϊ��װ
	{
		FX2N_DOControl (DOCH_BackValve, (USHORT)bAction );
	}
	else if(g_S700KData.Control.usMount == 2)   // ��װ
	{
		FX2N_DOControl (DOCH_ForwardValve, (USHORT)bAction );				
	}
}

//------------------------------------------------------------------------------------------------
// ���ػ��򷧿���
// ����:
//    bAction     TRUEʱ������FALSEʱֹͣ
// ���:
//    ��
// ����:
//    ��
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_SetInValve( BOOL bAction )
{
	if(g_S700KData.Control.usMount == 1) // ת�޻���װ��ʽ����Ϊ��װ
	{
		FX2N_DOControl (DOCH_ForwardValve, (USHORT)bAction );				
	}
	else if(g_S700KData.Control.usMount == 2)   // ��װ
	{
		FX2N_DOControl (DOCH_BackValve, (USHORT)bAction );
	}
}

//------------------------------------------------------------------------------------------------
// ģ��������������
// ����:
//    bAction     TRUEʱ���룬FALSEʱ�Ͽ�
// ���:
//    ��
// ����:
//    ��
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_SimulateTrack( BOOL bAction )
{
	// bActionΪTRUE ʱ������������ -- ����·������裬isShortΪFALSE
	// bActionΪFALSEʱ���Ͽ�������� --   ��·������裬isShortΪTRUE
	USHORT isShort = !bAction;
	FX2N_DOControl (DOCH_SimulateTrack, isShort);
}

//------------------------------------------------------------------------------------------------
// ������򷧿��ȿ���
// ����:
//    fValue      ������
// ���:
//    ��
// ����:
//    ��
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_SetOutForce( float fValue )
{
//   ADCards_AOValue (&g_PCI1724, AOCH_BackForce, fValue);
//   USB2833_AOValue (&g_PCI1711, AOCH_BackForce, fValue);
	if(g_S700KData.Control.usMount == 1) // ת�޻���װ��ʽ����Ϊ��װ
	{
		ADCards_AOValue (&g_PCI1724, AOCH_BackForce, fValue);
	}
	else if(g_S700KData.Control.usMount == 2)   // ��װ
	{
		ADCards_AOValue (&g_PCI1724, AOCH_ForwardForce, fValue);		
	}
}

//------------------------------------------------------------------------------------------------
// ���ػ��򷧿��ȿ���
// ����:
//    fValue      ������
// ���:
//    ��
// ����:
//    ��
//
//------------------------------------------------------------------------------------------------
void WINAPI DAQ_SetInForce( float fValue )
{
	// ADCards_AOValue (&g_PCI1724, AOCH_ForwardForce, fValue);
//   USB2833_AOValue (&g_PCI1711, AOCH_ForwardForce, fValue);

	if(g_S700KData.Control.usMount == 1) // ת�޻���װ��ʽ����Ϊ��װ
	{
		ADCards_AOValue (&g_PCI1724, AOCH_ForwardForce, fValue);
	}
	else if(g_S700KData.Control.usMount == 2)   // ��װ
	{
		ADCards_AOValue (&g_PCI1724, AOCH_BackForce, fValue);
	}
}

//------------------------------------------------------------------------------------------------
// ֱ����ѹ����
// ����:
//    fValue      ������
// ���:
//    ��
// ����:
//    ��
//
//------------------------------------------------------------------------------------------------
//void WINAPI DAQ_SetDCVoltage( float fValue )
//{
//   ADCards_AOValue (&g_PCI1724, AOCH_DCVoltage, fValue);
//}

//------------------------------------------------------------------------------------------------
// ת�޻������߳�
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//
//------------------------------------------------------------------------------------------------
DWORD WINAPI DAQThreadRoutine( DWORD arg )
{
	//DAQ_DCSelect (0);
//   DAQ_ACSelect (1);

	// ������б�־�����ڣ����˳��߳�ѭ��
	while (g_DAQSystemData.usDAQThreadLoop)
	{
		// ��������״̬ʱ���������
		if ((g_DAQSystemData.usRunStatus != RUNSTATUS_RUNING) ||
				(g_DAQSystemData.usRunStatus == RUNSTATUS_COMPLETE))
		{
			// �������ݲɼ�
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

			// ���û���µ����������´������ص�ѭ����ʼ��
			if (strlen (g_Device.Standard.acModelName) == 0)
				continue;

			// �������ģʽ����״̬
			if (!DAQ_ReadMode ())
			{
				g_DAQSystemData.usRunStatus = RUNSTATUS_TERMINATE;
				continue;
			}

			continue;
		}

		// �����������
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

		// ������������
		g_S700KData.Control.usError = 0;
		g_S700KData.Control.usTerminate = 0;
		g_S700KData.Control.usRunStatus = RUNSTATUS_RUNING;
		GetLocalTime (&g_S700KData.ptStart);
		DAQ_Delay (1000);


		// ����S700K���Թ�����
		if (g_Device.Standard.dwModelID < 300)
			S700K_ThreadRoutine( &g_Device, &g_S700KData );

		// ����ZDJ9���Թ�����
		if (g_Device.Standard.dwModelID > 300)
			ZDJ9_ThreadRoutine( &g_Device, &g_S700KData );

		// ������������������״̬
		g_S700KData.Control.usStep = -1;
		g_S700KData.Control.usConfig = 0;
		g_Device.Config.usTraillingTest = 0;
		g_S700KData.Control.usRunStatus = RUNSTATUS_COMPLETE;
		g_DAQSystemData.usRunStatus = RUNSTATUS_COMPLETE;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// ת�޻������߳�
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//
//------------------------------------------------------------------------------------------------
DWORD WINAPI DisplayThreadRoutine( DWORD arg )
{
	DWORD dwTicks;
	while ( g_DAQSystemData.usDisplayThreadLoop )
	{
		// ��ʱ������ʾ
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
// ����ת�޻������߳�
// ����:
//    ��
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall DAQ_CreateThread( void )
{
	// �����߳�ѭ��
	g_DAQSystemData.usDAQThreadLoop = TRUE;

	// �����߳�
	g_DAQSystemData.uhDAQThread = CreateThread( NULL, 0, ( LPTHREAD_START_ROUTINE )&DAQThreadRoutine, NULL, 0, NULL );
	if ( g_DAQSystemData.uhDAQThread == NULL )
		return FALSE;

	// ������ʾ�߳�ѭ��
	g_DAQSystemData.usDisplayThreadLoop = TRUE;

	//
	g_DAQSystemData.dwDAQTicks = GetTickCount( );

	// �����߳�
	g_DAQSystemData.uhDisplayThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&DisplayThreadRoutine, NULL, 0, NULL);
	if (g_DAQSystemData.uhDisplayThread == NULL)
		return FALSE;
	return TRUE;
}

//------------------------------------------------------------------------------------------------
// ֹͣת�޻������߳�
// ����:
//    ��
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall DAQ_TerminateThread( void )
{
	// ֪ͨ�߳̽���
	g_DAQSystemData.usDAQThreadLoop = FALSE;
	g_DAQSystemData.usDisplayThreadLoop = FALSE;

	// �ȴ������߳̽���
	WaitForSingleObject (g_DAQSystemData.uhDAQThread, 5000);
	CloseHandle (g_DAQSystemData.uhDAQThread);
	g_DAQSystemData.uhDAQThread = NULL;

	//
	g_DAQSystemData.usDisplayThreadLoop = FALSE;
	// �ȴ���ʾ�߳̽���
	WaitForSingleObject( g_DAQSystemData.uhDisplayThread, 5000 );
	CloseHandle (g_DAQSystemData.uhDisplayThread);
	g_DAQSystemData.uhDisplayThread = NULL;
	return TRUE;
}
//------------------------------------------------------------------------------------------------
// �趨ת�޻���װ��ʽ
// mount:  0:δ���á�1����װ��2����װ
//
void SetMount(short mount)
{
	unsigned int yesColor  = 0xFF0000;
	unsigned int noColor = 0xECE9D8;
		
	unsigned int leftButtonColor,rightButtonColor;
	switch(mount){
		case 0:// δ����
			leftButtonColor  = noColor;
			rightButtonColor = noColor;
			break;
		case 1:// ����Ϊ��װ
			leftButtonColor  = yesColor;
			rightButtonColor = noColor;			
			break;
		case 2:// ����Ϊ��װ
			leftButtonColor  = noColor;
			rightButtonColor = yesColor;						
			break;
		default:
			leftButtonColor  = noColor;
			rightButtonColor = noColor;
	}
	
	g_S700KData.Control.usMount = mount;  // ת�޻���װ��ʽ����Ϊ��װ
	SetCtrlAttribute(g_plMain, MAIN_LEFTTYPE, ATTR_CMD_BUTTON_COLOR, leftButtonColor);
	SetCtrlAttribute(g_plMain, MAIN_RIGHTTYPE, ATTR_CMD_BUTTON_COLOR, rightButtonColor);
}

//------------------------------------------------------------------------------------------------
// ��װ��ť
int CVICALLBACK CallBack_Left (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
#if 0			
			// FX2N_DOControl(DOCH_LEFT, TRUE);
			// FX2N_DOControl(DOCH_RIGHT, FALSE);
			
			g_S700KData.Control.usMount = 1;  // ת�޻���װ��ʽ����Ϊ��װ

			SetCtrlAttribute(g_plMain, MAIN_LEFTTYPE, ATTR_CMD_BUTTON_COLOR, 0xFF0000);
			SetCtrlAttribute(g_plMain, MAIN_RIGHTTYPE, ATTR_CMD_BUTTON_COLOR, 0xECE9D8);
#else
			SetMount(1);                      // 0:δ���á�1����װ��2����װ
#endif
			break;
	}
	return 0;
}
//------------------------------------------------------------------------------------------------
// ��װ��ť
int CVICALLBACK CallBack_Right (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
#if 0			
			// FX2N_DOControl(DOCH_LEFT, FALSE);
			// FX2N_DOControl(DOCH_RIGHT, TRUE);
			g_S700KData.Control.usMount = 2;   // ת�޻���װ��ʽ����Ϊ��װ

			SetCtrlAttribute(g_plMain, MAIN_LEFTTYPE, ATTR_CMD_BUTTON_COLOR, 0xECE9D8);
			SetCtrlAttribute(g_plMain, MAIN_RIGHTTYPE, ATTR_CMD_BUTTON_COLOR, 0xFF0000);
#else
			SetMount(2);                      // 0:δ���á�1����װ��2����װ
#endif
			break;
	}
	return 0;
}
//------------------------------------------------------------------------------------------------
// �趨ת�޻�������/������
// wireType:  0:δ���á�1�������ơ�2��������
//
void SetWireType(short wireType)
{
	unsigned int yesColor  = 0xFF0000;
	unsigned int noColor = 0xECE9D8;
		
	unsigned int leftButtonColor,rightButtonColor;
	switch(wireType){
		case 0:// δ����
			leftButtonColor  = noColor;
			rightButtonColor = noColor;
			FX2N_DOControl(DOCH_FOUR, FALSE);							
			FX2N_DOControl(DOCH_FIVE, FALSE);						
			break;
		case 1:// ����Ϊ������
			leftButtonColor  = yesColor;
			rightButtonColor = noColor;			
			FX2N_DOControl(DOCH_FOUR, TRUE);							
			FX2N_DOControl(DOCH_FIVE, FALSE);
			break;
		case 2:// ����Ϊ������
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
			INFO1("�趨ת�޻�������/�����ƴ���SetWireType(wireType)����wireType = %d",wireType);
	}
	g_S700KData.Control.usWireType = wireType;// ����ת�޻����߷�ʽ 
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
			g_S700KData.Control.usType = 1;// ������
			//FX2N_DOControl(DOCH_FIVE, FALSE);
			//FX2N_DOControl(DOCH_FOUR, TRUE);
			SetCtrlAttribute(g_plMain, MAIN_FIVEXZ, ATTR_CMD_BUTTON_COLOR, 0xECE9D8);
			SetCtrlAttribute(g_plMain, MAIN_Fourxz, ATTR_CMD_BUTTON_COLOR, 0xFF0000);
#else
			SetWireType(1);  // �趨ת�޻�������/������  0:δ���á�1�������ơ�2��������
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
			g_S700KData.Control.usType = 2;// ������
			FX2N_DOControl(DOCH_FOUR, FALSE);
			FX2N_DOControl(DOCH_FIVE, TRUE);
			SetCtrlAttribute(g_plMain, MAIN_FIVEXZ, ATTR_CMD_BUTTON_COLOR, 0xFF0000);
			SetCtrlAttribute(g_plMain, MAIN_Fourxz, ATTR_CMD_BUTTON_COLOR, 0xECE9D8);
#else
			SetWireType(2);  // �趨ת�޻�������/������  0:δ���á�1�������ơ�2��������
#endif			
			break;
	}
	return 0;
}
