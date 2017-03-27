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
// ����ȫ�ֱ���
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
// ��ʾϵͳʱ��
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
// ������
//------------------------------------------------------------------------------------------------
int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
					   LPSTR lpszCmdLine, int nCmdShow)
{
	INFO1("----------------����----------------");
	// �������Ƿ��Ѿ���������Ѿ��������˳�
	g_CheckEvent = CreateEvent( NULL, TRUE, FALSE, CHECKEVENT_NAME );
	if ( GetLastError( ) == ERROR_ALREADY_EXISTS )
		return -1;

	// ��ʼ�����л���
	if (InitCVIRTE (hInstance, 0, 0) == 0)
		return -1;  /* out of memory */

	// ��ʼ��ȫ�ֱ���
	memset (&g_HMISystemData, 0, sizeof (g_HMISystemData) );
	g_HMISystemData.usHMIThreadLoop = 1;
	g_HMISystemData.ulPeriods = 16;
	g_HMISystemData.ulDisplayPointer = FAI_DataBufferSize - g_HMISystemData.ulPeriods;

	memset (&g_DBStandard, 0, sizeof(PT_Database));
	strcpy (g_DBStandard.cDSNName, "Standard");
	strcpy (g_DBStandard.cPassword, "qldq");
	strcpy (g_DBStandard.cDatabase, "Data\\Standard.mdb");

	//�������ݿ�
	if (DB_Initialize(&g_DBStandard) != PASS)
	{
		MessageBox(NULL, "��׼���ݿ��ļ���ʧ��", "����", MB_OK | MB_ICONERROR);

		goto ExitSystem;
	}

	// ���������������
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


	// ��ʾϵͳʱ��
	TBDisplayTime ();

	g_S700KData.Control.usStep = -1;

	// ����UDPͨѶ�߳�
//   HMI_InitializeUDPCom ();

	// ��ʾ���
	DisplayPanel(g_plTable);

	DisplayPanel(g_plTrend);
	HidePanel(g_plTrend);
	DisplayPanel (g_plMain);
	// �����ɼ�,PLC���Ǳ�ͨ�ţ����߳�
	DAQ_Initialize ();
	// ����������ʾ�߳�
	HMI_CreateThread ();

	// ����������
	RunUserInterface ();

	// ������ʾ�̣߳�������ڡ��ر�����Ļ��桱֮ǰ
	HMI_TerminateThread ();
	DAQ_Uninitialize ();

	// �ر�����Ļ���
	DiscardPanel (g_plMain);
	DiscardPanel (g_plTable);
	DiscardPanel (g_plPosition);
	DiscardPanel (g_plCurrent);
	DiscardPanel (g_plPower);
	DiscardPanel (g_plTrend);

	// ֹͣUDPͨѶ�߳�
//   HMI_UninitializeUDPCom ();


ExitSystem:
	DB_Deinitialize (&g_DBStandard);

	// �رռ���¼�
	CloseHandle (g_CheckEvent);

	return 0;
}

//------------------------------------------------------------------------------------------------
// �ص�����
// ��ʾʱ�䶨ʱ���¼�
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
// �ص�����
// �˳���ť�¼�
//------------------------------------------------------------------------------------------------
int CVICALLBACK quitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	int nRetCode;
	if (event != EVENT_COMMIT)
		return 0;

	// ѯ���Ƿ��˳�
	nRetCode = MessageBox (NULL, "�Ƿ��˳�����?", "��ʾ", MB_YESNO | MB_ICONQUESTION | MB_SYSTEMMODAL);

	// ���ͬ���˳�
	if (nRetCode == IDYES)
		QuitUserInterface (0);

	return 0;
}

//------------------------------------------------------------------------------------------------
// �ص�����
// ������ʾ���ť�¼�
//------------------------------------------------------------------------------------------------
int CVICALLBACK HideTableCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	int nValue;
	if (event != EVENT_COMMIT)
		return 0;

	// ����������ʾ�����أ���֮����ʾ
	GetPanelAttribute( g_plTable, ATTR_VISIBLE, &nValue );
	if ( nValue == 0 )
		DisplayPanel( g_plTable );
	else
		HidePanel( g_plTable );
	return 0;
}

//------------------------------------------------------------------------------------------------
// �ص�����
// ������ʾλ�ƻ�����ť�¼�
//------------------------------------------------------------------------------------------------
int CVICALLBACK positionCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	int nValue;
	if (event != EVENT_COMMIT)
		return 0;

	// ��������Ѿ���ʾ�����أ���֮����ʾ
	GetPanelAttribute( g_plPosition, ATTR_VISIBLE, &nValue );
	if ( nValue == 0 )
		DisplayPanel( g_plPosition );
	else
		HidePanel( g_plPosition );
	return 0;
}

//------------------------------------------------------------------------------------------------
// �ص�����
// ������ʾ����������ť�¼�
//------------------------------------------------------------------------------------------------
int CVICALLBACK currentCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int nValue;
	if (event != EVENT_COMMIT)
		return 0;

	// ��������Ѿ���ʾ�����أ���֮����ʾ
	GetPanelAttribute( g_plCurrent, ATTR_VISIBLE, &nValue );
	if ( nValue == 0 )
		DisplayPanel( g_plCurrent );
	else
		HidePanel( g_plCurrent );
	return 0;
}

//------------------------------------------------------------------------------------------------
// �ص�����
// ������ʾ�����߻�����ť�¼�
//------------------------------------------------------------------------------------------------
int CVICALLBACK powerCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	int nValue;
	if (event != EVENT_COMMIT)
		return 0;

	// ��������Ѿ���ʾ�����أ���֮����ʾ
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
// �ص�����
// ת�޻��ͺŰ�ť�¼�/��λ���ػ�
//------------------------------------------------------------------------------------------------
BOOL WINAPI QLTableSetInputValue( LPT_Device pDevice );
int CVICALLBACK typeNumberCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	if (event != EVENT_COMMIT)
		return 0;

	g_HMISystemData.usShutdown = 1;

	// ¼������
	if (TBTypeNumber (g_Device.Standard.acSpecification, 0) != 0)
		return 0;

	// ��ʾ����
	QLTableSetInputValue (&g_Device);
	return 0;
}

//------------------------------------------------------------------------------------------------
// �ص�����
// ת�޻�����¼�밴ť�¼�
//------------------------------------------------------------------------------------------------
int CVICALLBACK serialNumberCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// ¼������
			if (TBSerialNumber (g_Device.Config.acSerialNumber, 0) != 0)
				break;
			// ��ʾ����
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// �ص�����
// ת�޻�������¼�밴ť�¼�
//------------------------------------------------------------------------------------------------
int CVICALLBACK testerNameCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// ¼������
			if (TBTesterName (g_Device.Config.acTesterName, 0) != 0)
				break;
			// ��ʾ����
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// �ص�����
// ת�޻��������¼�밴ť�¼�
//------------------------------------------------------------------------------------------------
int CVICALLBACK resultCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// ¼������
			if (TBTestResult (g_Device.Config.acTestResult, 0) != 0)
				break;
			// ��ʾ����
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// �ص�����
// ������Ϣ�´���ť�¼�
//------------------------------------------------------------------------------------------------
int CVICALLBACK transmitCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	HRESULT error = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			// ������Խ��
			strcpy (g_Device.Config.acTestResult, "");
			QLTableSetInputValue (&g_Device);
			// ���
			if (strlen (g_Device.Standard.acModelName) == 0)
			{
				MessageBox (NULL, "��Ч������!", "Error", MB_OK | MB_TOPMOST);
				break;
			}
			// ���
			if (strlen (g_Device.Standard.acSpecification) == 0)
			{
				MessageBox (NULL, "��Ʒ�����Ϊ��!", "����", MB_OK | MB_TOPMOST);
				break;
			}
			// ���
			if (((g_Device.Standard.fMaxTraillingForce <= 0.0)
					|| (g_Device.Standard.fMinTraillingForce <= 0.0))
					&& (g_Device.Config.usTraillingTest == 1))
			{
				MessageBox (NULL, "ת�޻����ܲ��Լ�����!", "����", MB_OK | MB_TOPMOST);
				break;
			}
			// ���
			if (strlen (g_Device.Config.acSerialNumber) == 0)
			{
				MessageBox (NULL, "������Ų���Ϊ��!", "Error", MB_OK | MB_TOPMOST);
				break;
			}
			// ���������/������ g_S700KData.Control.usType
			if (g_S700KData.Control.usWireType == 0)
			{
				MessageBox(NULL,"��ѡ�������ƻ��������ƣ�","Error",MB_OK | MB_TOPMOST);
				break;
			}
			// ���ת�޻���װ��ʽ.δѡ��:0,��װ:1,��װ��2
			if(g_S700KData.Control.usMount == 0)
			{
				MessageBox(NULL,"��ѡ����װ������װ��","Error",MB_OK | MB_TOPMOST);
			}

			// �����´�����
			g_DAQSystemData.usTerminate = FALSE;
			g_DAQSystemData.usRunStatus = RUNSTATUS_RUNING;
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// �ص�����
// ת�޻��豸ѡ��ť�¼�
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
			//g_S700KData.Control.usMount = 0;  // �����װ/��װ����
			SetMount(0);                      // 0:δ���á�1����װ��2����װ
			//g_S700KData.Control.usType = 0;   // ���������/����������
			SetWireType(0);  // �趨ת�޻�������/������  0:δ���á�1�������ơ�2��������			
			// ���붯̬��
			hInstance = LoadLibrary("S700K.dll");
			if (!hInstance)
				break;
			// ��ȡ������ַ
			pFunction = (DLL_DeviceSelect)GetProcAddress(hInstance, "DLL_DeviceSelect");
			// ���
			if (!pFunction)
				break;
			// ��������
			if (pFunction(&g_Device) != 0)
				break;

			// ��ʾ����
			SetCtrlVal (g_plMain, MAIN_TYPENAME, g_Device.Standard.acSpecification);
			QLTableSetRatedValue (&g_Device);
			break;
	}
	// �ͷŶ�̬��
	if (!hInstance)
		FreeLibrary(hInstance);
	return 0;
}

//------------------------------------------------------------------------------------------------
// �ص�����
// �����水ť�¼�
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
// �ص�����
// Excel���Ա����ӡ��ť�¼�
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
// �ص�����
// ѡ��Load2���԰�ť�¼�
//------------------------------------------------------------------------------------------------
int CVICALLBACK load2Callback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// ����Ѿ�ѡ����ȡ������֮��ѡ��
			if (g_Device.Config.usLoad2Test == 1)
				g_Device.Config.usLoad2Test = 0;
			else
				g_Device.Config.usLoad2Test = 1;

			// ��ʾ����
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// �ص�����
// ѡ��Load1���԰�ť�¼�
//------------------------------------------------------------------------------------------------
int CVICALLBACK load1Callback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// ����Ѿ�ѡ����ȡ������֮��ѡ��
			if (g_Device.Config.usLoad1Test == 1)
				g_Device.Config.usLoad1Test = 0;
			else
				g_Device.Config.usLoad1Test = 1;

			// ��ʾ����
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// �ص�����
// ѡ��Load3���԰�ť�¼�
//------------------------------------------------------------------------------------------------
int CVICALLBACK load3Callback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// ����Ѿ�ѡ����ȡ������֮��ѡ��
			if (g_Device.Config.usLoad3Test == 1)
				g_Device.Config.usLoad3Test = 0;
			else
				g_Device.Config.usLoad3Test = 1;

			// ��ʾ����
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// �ص�����
// ѡ�񱣳������԰�ť�¼�
//------------------------------------------------------------------------------------------------
int CVICALLBACK revisionCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// ����Ѿ�ѡ����ȡ������֮��ѡ��
			if (g_Device.Config.usRevisionTest == 1)
				g_Device.Config.usRevisionTest = 0;
			else
				g_Device.Config.usRevisionTest = 1;

			// ��ʾ����
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// �ص�����
// ѡ�񼷲������԰�ť�¼�
//------------------------------------------------------------------------------------------------
int CVICALLBACK traillingCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			// ����Ѿ�ѡ����ȡ������֮��ѡ��
			if (g_Device.Config.usTraillingTest == 1)
				g_Device.Config.usTraillingTest = 0;
			else
				g_Device.Config.usTraillingTest = 1;

			// ��ʾ����
			QLTableSetInputValue (&g_Device);
			break;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------
// ������������ʾ
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
// ���������߻ط���ʾ
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
// �ص�����
// ���ߺ󷭰�ť�¼�
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
// �ص�����
// ����ǰ����ť�¼�
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
// �ص�����
// �������ذ�ť�¼�
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
// �ص�����
// ���ߴ�ӡ��ť�¼�
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
// �ص�����
// ������ʾ��ʱ���¼�
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
// �ص�����
// ���߼�¼ֹͣ��ť�¼�
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
// �ص�����
// ���߼�¼��ʼ��ť�¼�
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
// �ص�����
// ��������Ŵ�ť�¼�
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
// �ص�����
// ����������С��ť�¼�
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
// �ص�����
// ����ʱ����Ŵ�ť�¼�
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
// �ص�����
// ����ʱ������С��ť�¼�
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
// �ص�����
// ����һ��������ʾ��ť�¼�
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
// �ص�����
// ����ȫ��������ʾ��ť�¼�
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
// �ص�����
// ���߱���Ϊλͼ��ʾ��ť�¼�
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
			strcpy (chTitle, "����ͼ��");
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
			system("shutdown -p");  // ֱ�ӹػ�����ϵͳ��ʾ��
			//system("shutdown -s");  // 30s��ػ�����ϵͳ��ʾ��
			//system("shutdown -s -t 360);  ��t ָ����ʱ�䣩 ���ͣ�360���ػ� ����ֹػ�����ʱ����
			//system("shutdown -h");����
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
			//��ܼ�,��ֻҪ����SetPanelAttribute(panelHandle,ATTR_TITLEBAR_VISIBLE,0)�Ѵ��ڵı�������Ϊ����(�����ɼ�),Ȼ����ʹ��SetPanelAttribute (panelHandle, ATTR_WINDOW_ZOOM, VAL_MAXIMIZE);����ʵ��ȫ��,��������Ҳ������,����,����,������.
			SetPanelAttribute(panel,ATTR_TITLEBAR_VISIBLE,0);// ���ڵı�������Ϊ����(�����ɼ�)
			// Ȼ����ʹ�ü���ʵ��ȫ��,��������Ҳ������,����,����,������.
			SetPanelAttribute (panel, ATTR_WINDOW_ZOOM, VAL_MAXIMIZE);
			break;
	}
	return 0;
}
