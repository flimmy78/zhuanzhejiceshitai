// #########################################################################
// *************************************************************************

#include <cvirte.h>     
#include "..\include\Global.h"
#include <userint.h>
#include "S700K.h"
#include "inifile.h"
#include "Myfile.h"

//------------------------------------------------------------------------------------------------
// ����ȫ�ֱ���
//------------------------------------------------------------------------------------------------
extern int              plMain;
extern PT_ReportData    g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_Device        g_Device;
extern PT_SystemData    g_SystemData;
//------------------------------------------------------------------------------------------------
extern int              plPosition;
extern int              plCurrent;
extern int              plPower;
extern PT_InitStatus    g_InitStatus;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// ��ʾ����������Ӣ����ʾ
// ����:
//    pData       ���Խ������
// ���:
//    ��
// ����:
//    ��
//------------------------------------------------------------------------------------------------
void __stdcall DAQStepDisplayEnglish(LPT_ReportData pData)
{
   char  chData[128];
   switch (pData->Control.usStep)
   {
   case -1:
      strcpy (chData, "Ready.");
      break;
   case 0:
      strcpy (chData, "Move point machine to position B.");
      break;
   case 1:
      strcpy (chData, "Measure storke from position B to A.");
      break;
   case 2:
      strcpy (chData, "Measure storke from position A to B.");
      break;
   case 3:
      strcpy (chData, "Measure maximum force from position B to A.");
      break;
   case 4:
      strcpy (chData, "Measure maximum force from position A to B.");
      break;
   case 5:
      strcpy (chData, "Measure operating force (without R.V) from position B to A.");
      break;
   case 6:
      strcpy (chData, "Measure operating force (without R.V) from position A to B.");
      break;
   case 7:
      strcpy (chData, "Measure operating force (with R.V) from position B to A.");
      break;
   case 8:
      strcpy (chData, "Measure operating force (with R.V) from position A to B.");
      break;
   case 9:
      strcpy (chData, "Check revision from position B to A.");
      break;
   case 10:
      strcpy (chData, "Check revision from position A to B.");
      break;
   case 11:
      strcpy (chData, "Measure trailling force at endposition direction A.");
      break;
   case 12:
      strcpy (chData, "Measure trailling force at endposition direction B.");
      break;
   default:
      break;
   }
   SetCtrlVal (plMain,PANELMAIN_STEPMSG, chData);
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
void __stdcall DAQStepDisplayChinese(LPT_ReportData pData)
{
   char  chData[128];
   switch (pData->Control.usStep)
   {
   case -1:
      strcpy (chData, "׼������.");
      break;
   case 0:
      strcpy (chData, "�ƶ�ת�޻���λ��B.");
      break;
   case 1:
      strcpy (chData, "����λ��B��A�Ķ���.");
      break;
   case 2:
      strcpy (chData, "����λ��A��B�Ķ���.");
      break;
   case 3:
      strcpy (chData, "����λ��B��A�������.");
      break;
   case 4:
      strcpy (chData, "����λ��A��B�������.");
      break;
   case 5:
      strcpy (chData, "����λ��B��A����С��(��ģ�����).");
      break;
   case 6:
      strcpy (chData, "����λ��A��B����С��(��ģ�����).");
      break;
   case 7:
      strcpy (chData, "����λ��B��A����С��(��ģ�����).");
      break;
   case 8:
      strcpy (chData, "����λ��A��B����С��(��ģ�����).");
      break;
   case 9:
      strcpy (chData, "���λ��B��A�ı�����.");
      break;
   case 10:
      strcpy (chData, "���λ��A��B�ı�����.");
      break;
   case 11:
      strcpy (chData, "�����ն�λ��A�ļ�����.");
      break;
   case 12:
      strcpy (chData, "�����ն�λ��B�ļ�����.");
      break;
   default:
      break;
   }
   SetCtrlVal (plMain,PANELMAIN_STEPMSG, chData);
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
void __stdcall DAQStepDisplay(LPT_ReportData pData)
{
   // Ӣ����ʾ
   if (g_SystemData.usLanguage == 0)
      DAQStepDisplayEnglish (pData);
   // ������ʾ
   else
      DAQStepDisplayChinese (pData);
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
void __stdcall DAQDataDisplay( LPT_DAQData pData )
{
   char  chData[ 128 ];
   // ��ʾָ�������
   SetCtrlVal( plPosition, PLPosition_NUMERICGAUGE, pData->Data.dfDistance );
   SetCtrlVal( plCurrent, PLCurrent_NUMERICGAUGE, pData->Data.dfIa );
   SetCtrlVal( plPower, PLPower_NUMERICGAUGE, pData->Data.dfPower );
   
   // ��ʾָʾ��
   SetCtrlVal( plMain, PANELMAIN_LED_AUTO, pData->Data.usAutoMode );
   SetCtrlVal( plMain, PANELMAIN_LED_Connect, g_InitStatus.chInitNetwork );
   
   SetCtrlVal( plMain, PANELMAIN_LED_CONFIG, g_S700KData.Control.usConfig );
   SetCtrlVal( plMain, PANELMAIN_LED_LOAD2, g_S700KData.ptDevice.Config.usLoad2Test );
   SetCtrlVal( plMain, PANELMAIN_LED_LOAD1, g_S700KData.ptDevice.Config.usLoad1Test );
   SetCtrlVal( plMain, PANELMAIN_LED_LOAD3, g_S700KData.ptDevice.Config.usLoad3Test );
   SetCtrlVal( plMain, PANELMAIN_LED_TRAIL, g_S700KData.ptDevice.Config.usTraillingTest );
   SetCtrlVal( plMain, PANELMAIN_LED_REVISION, g_S700KData.ptDevice.Config.usRevisionTest );
   
   if (g_S700KData.Control.usRunStatus == RUNSTATUS_RUNING)
      SetCtrlVal(plMain, PANELMAIN_LED_RUNING, 1);
   else
      SetCtrlVal(plMain, PANELMAIN_LED_RUNING, 0);
   
   SetCtrlVal (plMain, PANELMAIN_LED_FR1, pData->Data.usFR1);
   SetCtrlVal (plMain, PANELMAIN_LED_FR2, pData->Data.usFR2);
   SetCtrlVal (plMain, PANELMAIN_LED_JWXC, pData->Data.usJWXC);
   
   SetCtrlVal (plMain, PANELMAIN_LED_ERROR, g_S700KData.Control.usError);
  
   // ��ʾ����
   sprintf( chData, "%d", g_S700KData.Control.usStep );
   SetCtrlVal( plMain, PANELMAIN_STEP, chData );
   
   // ��ʾ����ʱ��
   sprintf (chData, "%.1f s", g_S700KData.Control.ulMeasTime / 1000.0);
   SetCtrlVal (plMain, PANELMAIN_MEASTIME, chData);
     
   return;
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
DWORD WINAPI DAQThreadRoutine(DWORD arg)
{
   DWORD dwTicks;
   // �����Ҫ���˳�
   while (g_SystemData.usThreadLoop)
   {
      // ��ʾʵʱ����
      DAQDataDisplay (&g_DAQData);
      // ��ʾ����
      DAQStepDisplay (&g_S700KData);

      // ��ʾ���Ա�����
      QLTableRefresh (&g_S700KData);
      QLTableSetReportResult (&g_S700KData);
      
      Sleep( 200 );
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
int __stdcall DAQCreateThread(void)
{
   // �����߳�ѭ����־
   g_SystemData.usThreadLoop = 1;
   
   // �����߳�
   g_SystemData.uhDAQThread = CreateThread (NULL, 0,
      (LPTHREAD_START_ROUTINE)&DAQThreadRoutine, NULL, 0, NULL);
   
   // ���
   if (g_SystemData.uhDAQThread == NULL)
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
int __stdcall DAQTerminateThread( void )
{
   // Ҫ���߳�ֹͣ
   g_SystemData.usThreadLoop = FALSE;

   // �ȴ��߳�ֹͣ
   WaitForSingleObject (g_SystemData.uhDAQThread, 5000);
   CloseHandle (g_SystemData.uhDAQThread);
   g_SystemData.uhDAQThread = NULL;
   
   return TRUE;
}
//------------------------------------------------------------------------------------------------
