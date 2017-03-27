// #########################################################################
// *************************************************************************

#include <cvirte.h>     
#include "..\include\global.h"
#include <userint.h>
#include "S700K.h"
#include "inifile.h"
#include "HMIDefine.h"
#include "DAQDefine.h"
#include "Device.h"

//------------------------------------------------------------------------------------------------
// ����ȫ�ֱ���
//------------------------------------------------------------------------------------------------
extern int              g_plMain;
extern int              g_plMain;
extern PT_Record        g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_Device        g_Device;
extern PT_HMISystemData g_HMISystemData;
extern PT_DAQSystemData g_DAQSystemData;
extern PT_InitStatus    g_InitStatus;
//------------------------------------------------------------------------------------------------
extern int              g_plPosition;
extern int              g_plCurrent;
extern int              g_plPower;
//------------------------------------------------------------------------------------------------
extern PT_Meter         g_Meters[MAX_METERS];
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void WINAPI TBDisplayValue( LPT_Device pDevice, LPT_DAQData pData )
{
   char  chData[ 128 ];
   // ��ʾָ�������
   SetCtrlVal( g_plPosition, PLPosition_NUMERICGAUGE, pData->Data.dfStroke );
   SetCtrlVal( g_plCurrent, PLCurrent_NUMERICGAUGE, pData->Data.dfIa );
   SetCtrlVal( g_plPower, PLPower_NUMERICGAUGE, pData->Data.dfPower );
   
   // ��ʾָʾ��
   SetCtrlVal( g_plMain, MAIN_LED_AUTO, pData->Data.usAutoMode );
   
   SetCtrlVal( g_plMain, MAIN_LED_CONFIG, g_S700KData.Control.usConfig );
   SetCtrlVal( g_plMain, MAIN_LED_LOAD2, g_Device.Config.usLoad2Test );
   SetCtrlVal( g_plMain, MAIN_LED_LOAD1, g_Device.Config.usLoad1Test );
   SetCtrlVal( g_plMain, MAIN_LED_LOAD3, g_Device.Config.usLoad3Test );
   SetCtrlVal( g_plMain, MAIN_LED_TRAIL, g_Device.Config.usTraillingTest );
   SetCtrlVal( g_plMain, MAIN_LED_REVISION, g_Device.Config.usRevisionTest );
   
   if (g_S700KData.Control.usRunStatus == RUNSTATUS_RUNING)
      SetCtrlVal(g_plMain, MAIN_LED_RUNING, 1);
   else
      SetCtrlVal(g_plMain, MAIN_LED_RUNING, 0);
   
   SetCtrlVal (g_plMain, MAIN_LED_FR1, pData->Data.usFR1);
   SetCtrlVal (g_plMain, MAIN_LED_FR2, pData->Data.usFR2);
   SetCtrlVal (g_plMain, MAIN_LED_JWXC, pData->Data.usJWXC);
   
   SetCtrlVal (g_plMain, MAIN_LED_ERROR, g_S700KData.Control.usError);
  
   // ��ʾ����
   sprintf (chData, "%d", g_S700KData.Control.usStep);
   SetCtrlVal (g_plMain, MAIN_STEP, chData);
   
   // ��ʾ����ʱ��
   sprintf (chData, "%.1f s", g_S700KData.Control.ulMeasTime / 1000.0);
   SetCtrlVal (g_plMain, MAIN_MEASTIME, chData);
     
   return;
}

//------------------------------------------------------------------------------------------------
// ��ʾ��������
// ����:
//    pData       ���Խ������
// ���:
//    ��
// ����:
//    ��
//------------------------------------------------------------------------------------------------
void __stdcall HMI_DataDisplay( LPT_DAQData pData )
{
   char  chData[ 128 ];

   SetCtrlVal(g_plMain, MAIN_NG_UAB, pData->Data.dfUab);
   SetCtrlVal(g_plMain, MAIN_NG_UBC, pData->Data.dfUbc);
   SetCtrlVal(g_plMain, MAIN_NG_UCA, pData->Data.dfUca);
   SetCtrlVal(g_plMain, MAIN_NG_IA, pData->Data.dfIa);
   SetCtrlVal(g_plMain, MAIN_NG_IB, pData->Data.dfIb);
   SetCtrlVal(g_plMain, MAIN_NG_IC, pData->Data.dfIc);
  // SetCtrlVal(g_plMain, MAIN_NG_UDC, pData->Data.dfUdc);
  // SetCtrlVal(g_plMain, MAIN_NG_IDC, pData->Data.dfIdc);
   SetCtrlVal(g_plMain, MAIN_NG_S, pData->Data.dfStroke);	 // ����
   SetCtrlVal(g_plMain, MAIN_NG_FORCE, pData->Data.dfForce);

   //SetCtrlVal(g_plMain, MAIN_LED_RUNING, g_DAQSystemData.usRunStatus == RUNSTATUS_RUNING);
   
   //SetCtrlVal (g_plMain, MAIN_LED_FR1, pData->Data.usFR2 == 0);
   //SetCtrlVal (g_plMain, MAIN_LED_FR2, pData->Data.usFR1 == 0);
   //SetCtrlVal (g_plMain, MAIN_LED_JWXC, pData->Data.usJWXC);
   //SetCtrlVal (g_plMain, MAIN_LED_ERROR, g_DAQSystemData.usError);
#if 0   
   SetCtrlVal (g_plMain, MAIN_LED_D, pData->Data.usLeft == 1);
   SetCtrlVal (g_plMain, MAIN_LED_F, pData->Data.usRight == 1);
#else
   if((pData->Data.usLeft == 1) && (pData->Data.usRight == 1)){
	   // ת�޻�ͣ���м䣬�Ȳ��ڶ�λ�ֲ��ڷ�λ��
	  SetCtrlVal (g_plMain, MAIN_LED_D, 0);
      SetCtrlVal (g_plMain, MAIN_LED_F, 0);   	   
   }else{
	  SetCtrlVal (g_plMain, MAIN_LED_D, pData->Data.usLeft == 1);
      SetCtrlVal (g_plMain, MAIN_LED_F, pData->Data.usRight == 1);   
   }
#endif
   // ��ʾָ�������
   SetCtrlVal( g_plPosition, PLPosition_NUMERICGAUGE, pData->Data.dfStroke );
   SetCtrlVal( g_plCurrent, PLCurrent_NUMERICGAUGE, pData->Data.dfIa );
   SetCtrlVal( g_plPower, PLPower_NUMERICGAUGE, pData->Data.dfPower );
   
   // ��ʾָʾ��
   SetCtrlVal( g_plMain, MAIN_LED_AUTO, pData->Data.usAutoMode );
   
   SetCtrlVal( g_plMain, MAIN_LED_CONFIG, g_S700KData.Control.usConfig );
   SetCtrlVal( g_plMain, MAIN_LED_LOAD1, g_Device.Config.usLoad1Test );
   SetCtrlVal( g_plMain, MAIN_LED_LOAD2, g_Device.Config.usLoad2Test );
   SetCtrlVal( g_plMain, MAIN_LED_LOAD3, g_Device.Config.usLoad3Test );
   SetCtrlVal( g_plMain, MAIN_LED_TRAIL, g_Device.Config.usTraillingTest );
   SetCtrlVal( g_plMain, MAIN_LED_REVISION, g_Device.Config.usRevisionTest );
   
   if (g_S700KData.Control.usRunStatus == RUNSTATUS_RUNING)
      SetCtrlVal(g_plMain, MAIN_LED_RUNING, 1);
   else
      SetCtrlVal(g_plMain, MAIN_LED_RUNING, 0);
   
   SetCtrlVal (g_plMain, MAIN_LED_FR1, pData->Data.usFR1);
   SetCtrlVal (g_plMain, MAIN_LED_FR2, pData->Data.usFR2);
   SetCtrlVal (g_plMain, MAIN_LED_JWXC, pData->Data.usJWXC);
   
   SetCtrlVal (g_plMain, MAIN_LED_ERROR, g_S700KData.Control.usError);
  
   // ��ʾ����
   sprintf( chData, "%d", g_S700KData.Control.usStep );
   SetCtrlVal( g_plMain, MAIN_STEP, chData );
   
   // ��ʾ����ʱ��
   sprintf (chData, "%.1f s", g_S700KData.Control.ulMeasTime / 1000.0);
   SetCtrlVal (g_plMain, MAIN_MEASTIME, chData);
     
   return;
}

//------------------------------------------------------------------------------------------------
// ��ʾ����������������ʾ
// ����:
//    pData       ���Խ������
// ���:
//    ��
// ����:
//    ��
//------------------------------------------------------------------------------------------------
void __stdcall HMI_StepDisplay(LPT_Record pData)
{
   char  chData[128];
   switch (pData->Control.usStep)
   {
   case -1:
      strcpy (chData, "׼������.");
      break;
   case 0:
      strcpy (chData, "�ƶ�ת�޻�����λ.");
      break;
   case 1:
      strcpy (chData, "������λ����λ�Ķ���.");
      break;
   case 2:
      strcpy (chData, "������λ����λ�Ķ���.");
      break;
   case 3:
      strcpy (chData, "������λ����λ�������.");
      break;
   case 4:
      strcpy (chData, "������λ����λ�������.");
      break;
   case 5:
      strcpy (chData, "������λ����λ����С��(��ģ�����).");
      break;
   case 6:
      strcpy (chData, "������λ����λ����С��(��ģ�����).");
      break;
   case 7:
      strcpy (chData, "������λ����λ����С��(��ģ�����).");
      break;
   case 8:
      strcpy (chData, "������λ����λ����С��(��ģ�����).");
      break;
   case 9:
      strcpy (chData, "��ⷴλ����λ�ı�����.");
      break;
   case 10:
      strcpy (chData, "��ⶨλ����λ�ı�����.");
      break;
   case 11:
      strcpy (chData, "�����ն˶�λ�ļ�����.");
      break;
   case 12:
      strcpy (chData, "�����ն˷�λ�ļ�����.");
      break;
   default:
      break;
   }
   SetCtrlVal (g_plMain,MAIN_STEPMSG, chData);
}

//------------------------------------------------------------------------------------------------
// ������ʾ���߳�
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//------------------------------------------------------------------------------------------------
DWORD WINAPI HMI_ThreadRoutine(DWORD arg)
{
   MSG Msg;
   // �����Ҫ���˳�
   while (g_HMISystemData.usHMIThreadLoop)
   {
      if (PeekMessage (&Msg, 0, 0, 0, PM_REMOVE))
      {
         TranslateMessage (&Msg);
         DispatchMessage (&Msg);
      }
      
      // ��ʾʵʱ����
      HMI_DataDisplay (&g_DAQData);   // �Ǳ��ָʾ��
      // ��ʾ�����ַ���
      HMI_StepDisplay (&g_S700KData);

      // ��ʾ���Ա�����
      HMI_TableRefresh (&g_S700KData);	  		// ���Ա���е�����
      HMI_TableSetReportResult (&g_S700KData);  // ���Ա���еĽ����' ':û�в���ֵ��-���ϸ�+�����ϸ�
	  
	  // �����ֶ���������
	  DAQ_DataDisplay( &g_DAQData );
      
      Sleep( 200 );		// 200msˢ��һ�Ρ�
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
// ����������ʾ�߳�
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//---------------------------------------------------------------------------
int __stdcall HMI_CreateThread(void)
{
   // �����߳�ѭ����־
   g_HMISystemData.usHMIThreadLoop = 1;
   
   // �����߳�
   g_HMISystemData.uhHMIThread = CreateThread (NULL, 0,
      (LPTHREAD_START_ROUTINE)&HMI_ThreadRoutine, NULL, 0, NULL);
   
   // ���
   if (g_HMISystemData.uhHMIThread == NULL)
      return FALSE;
   
   return TRUE;
}

//------------------------------------------------------------------------------------------------
// ֹͣ������ʾ�߳�
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//---------------------------------------------------------------------------
int __stdcall HMI_TerminateThread( void )
{
   // Ҫ���߳�ֹͣ
   g_HMISystemData.usHMIThreadLoop = FALSE;

   // �ȴ��߳�ֹͣ
   WaitForSingleObject (g_HMISystemData.uhHMIThread, 5000);
   CloseHandle (g_HMISystemData.uhHMIThread);
   g_HMISystemData.uhHMIThread = NULL;
   
   return TRUE;
}
//------------------------------------------------------------------------------------------------
