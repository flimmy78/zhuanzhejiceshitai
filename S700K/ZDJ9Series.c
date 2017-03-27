// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************
#include <cvirte.h>     
#include <userint.h>
#include "S700k.h"
#include "DAQDefine.h"
//#include "MyFile.h"
#include <ansi_c.h>
#include "..\Include\Global.h"

//------------------------------------------------------------------------------------------------
// ����ȫ�ֱ���
//------------------------------------------------------------------------------------------------
extern int              plMain;
extern PT_Record        g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_DAQSystemData g_DAQSystemData;
extern PT_Device        g_Device;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// ���ݲ���������ȡB����������Ƶ�ѹ
// ����:
//    fForce      ������
// ���:
//    ��
// ����:
//                ���Ƶ�ѹ
//------------------------------------------------------------------------------------------------
float __stdcall ZDJ9_GetControlVoltageB(float fForce)
{
   float fData;
   
   if (fForce <= 2.50)
      fData = 1.0;
   else if ((fForce <= 2.75) && (fForce > 2.50))
      fData = 1.2;
   else if ((fForce <= 3.00) && (fForce > 2.75))
      fData = 1.3;
   else if ((fForce <= 3.25) && (fForce > 3.00))
      fData = 1.5;
   else if ((fForce <= 3.50) && (fForce > 3.25))
      fData = 1.7;
   else if ((fForce <= 3.75) && (fForce > 3.50))
      fData = 1.95;
   else if ((fForce <= 4.00) && (fForce > 3.75))
      fData = 2.10;
   else if ((fForce <= 4.25) && (fForce > 4.00))
      fData = 2.25;
   else if ((fForce <= 4.50) && (fForce > 4.25))
      fData = 2.40;
   else if ((fForce <= 4.75) && (fForce > 4.50))
      fData = 2.50;
   else if ((fForce <= 5.00) && (fForce > 4.75))
      fData = 2.65;
   else if ((fForce <= 5.25) && (fForce > 5.00))
      fData = 2.75;
   else if ((fForce <= 5.50) && (fForce > 5.25))
      fData = 2.85;
   else if ((fForce <= 5.75) && (fForce > 5.50))
      fData = 2.95;
   else if ((fForce <= 6.00) && (fForce > 5.75))
      fData = 3.05;
   else if ((fForce <= 6.25) && (fForce > 6.00))
      fData = 3.15;
   else if ((fForce <= 6.50) && (fForce > 6.25))
      fData = 3.20;
   else if ((fForce <= 6.75) && (fForce > 6.50))
      fData = 3.25;
   else if ((fForce <= 7.00) && (fForce > 6.75))
      fData = 3.35;
   else if ((fForce <= 7.25) && (fForce > 7.00))
      fData = 3.45;
   else if ((fForce <= 7.50) && (fForce > 7.25))
      fData = 3.50;
   else if ((fForce <= 7.75) && (fForce > 7.50))
      fData = 3.60;
   else if ((fForce <= 8.00) && (fForce > 7.75))
      fData = 3.68;
   else if ((fForce <= 8.25) && (fForce > 8.00))
      fData = 3.75;
   else if ((fForce <= 8.50) && (fForce > 8.25))
      fData = 3.80;
   else if ((fForce <= 8.75) && (fForce > 8.50))
      fData = 3.85;
   else if ((fForce <= 9.00) && (fForce > 8.75))
      fData = 3.92;
   else if ((fForce <= 9.25) && (fForce > 9.00))
      fData = 4.00;
   else if ((fForce <= 9.50) && (fForce > 9.25))
      fData = 4.04;
   else if ((fForce <= 9.75) && (fForce > 9.50))
      fData = 4.12;
   else if ((fForce <= 10.00) && (fForce > 9.75))
      fData = 4.18;
   else
      fData = 4.18;

   return fData;
}

//------------------------------------------------------------------------------------------------
// ���ݲ���������ȡA����������Ƶ�ѹ
// ����:
//    fForce      ������
// ���:
//    ��
// ����:
//                ���Ƶ�ѹ
//------------------------------------------------------------------------------------------------
float __stdcall ZDJ9_GetControlVoltageA(float fForce)
{
   float fData;
   
   if (fForce <= 2.50)
      fData = 1.4;
   else if ((fForce <= 2.75) && (fForce > 2.50))
      fData = 1.7;
   else if ((fForce <= 3.00) && (fForce > 2.75))
      fData = 2.0;
   else if ((fForce <= 3.25) && (fForce > 3.00))
      fData = 2.3;
   
   else if ((fForce <= 3.50) && (fForce > 3.25))
      fData = 2.5;
   else if ((fForce <= 3.75) && (fForce > 3.50))
      fData = 2.65;
   else if ((fForce <= 4.00) && (fForce > 3.75))
      fData = 2.80;
   else if ((fForce <= 4.25) && (fForce > 4.00))
      fData = 2.95;
   
   else if ((fForce <= 4.50) && (fForce > 4.25))
      fData = 3.10;
   else if ((fForce <= 4.75) && (fForce > 4.50))
      fData = 3.20;
   else if ((fForce <= 5.00) && (fForce > 4.75))
      fData = 3.30;
   else if ((fForce <= 5.25) && (fForce > 5.00))
      fData = 3.40;
   
   else if ((fForce <= 5.50) && (fForce > 5.25))
      fData = 3.50;
   else if ((fForce <= 5.75) && (fForce > 5.50))
      fData = 3.60;
   else if ((fForce <= 6.00) && (fForce > 5.75))
      fData = 3.70;
   else if ((fForce <= 6.25) && (fForce > 6.00))
      fData = 3.75;
   
   else if ((fForce <= 6.50) && (fForce > 6.25))
      fData = 3.82;
   else if ((fForce <= 6.75) && (fForce > 6.50))
      fData = 3.88;
   else if ((fForce <= 7.00) && (fForce > 6.75))
      fData = 3.95;
   else if ((fForce <= 7.25) && (fForce > 7.00))
      fData = 4.02;
   
   else if ((fForce <= 7.50) && (fForce > 7.25))
      fData = 4.08;
   else if ((fForce <= 7.75) && (fForce > 7.50))
      fData = 4.15;
   else if ((fForce <= 8.00) && (fForce > 7.75))
      fData = 4.22;
   else if ((fForce <= 8.25) && (fForce > 8.00))
      fData = 4.28;
   
   else if ((fForce <= 8.50) && (fForce > 8.25))
      fData = 4.33;
   else if ((fForce <= 8.75) && (fForce > 8.50))
      fData = 4.40;
   else if ((fForce <= 9.00) && (fForce > 8.75))
      fData = 4.46;
   else if ((fForce <= 9.25) && (fForce > 9.00))
      fData = 4.52;
   
   else if ((fForce <= 9.50) && (fForce > 9.25))
      fData = 4.58;
   else if ((fForce <= 9.75) && (fForce > 9.50))
      fData = 4.65;
   else if ((fForce <= 10.00) && (fForce > 9.75))
      fData = 4.70;
   else
      fData = 4.70;

   return fData;
}

//------------------------------------------------------------------------------------------------
// ת�޻����Ͽ��ƣ��رձ�������ֹͣת�޻�
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//------------------------------------------------------------------------------------------------
void __stdcall ZDJ9_ErrorHandle(LPT_Device pDevice, LPT_Record pData)
{
   // Clear all output
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_SetOutForce (0.0);
   DAQ_SetInForce (0.0);
   DAQ_SetTotalValve (1);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (0);

   // Set Error status
   pData->Control.usError = 1;
}

//------------------------------------------------------------------------------------------------
// ת�޻�ж�ؿ��ƣ��رձ�����
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//------------------------------------------------------------------------------------------------
void __stdcall ZDJ9_UnloadHandle(LPT_Device pDevice, LPT_Record pData)
{
   // Clear all output
   DAQ_SetOutForce (0.0);
   DAQ_SetInForce (0.0);
   DAQ_SetTotalValve (1);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (0);
}

//------------------------------------------------------------------------------------------------
// ����������
// ����:
//    pDevice     �������ת�޻�����
//    pData       ����ת�޻���������
// ���:
//    ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
DWORD WINAPI ZDJ9_MeasureRevision(LPT_Device pDevice, LPT_Record pData)
{
   double   dfDistance;
   DWORD    dwTicksError;
   DWORD    dwRetCode = 0;
   double   fStroke;
   DWORD    dwTimeout = 7000;
   
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_S700KData.Control.usTerminate)
      return -1;
   
   // ����ת�޻�����ʱ�������ʱֵ
   if (g_Device.Standard.fLoad1_TravelTime > 0)
      dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;
   DAQ_Delay (2000);
   
   // ���
   fStroke = pDevice->Standard.fStroke;
   if (fStroke <= 100.0)
      return -1;
   if (fStroke >= 300.0)
      return -1;
   fStroke = fStroke / 2.0 - 30.0;

   // �򿪱�����
   DAQ_SetTotalValve( 0 );
   DAQ_SetInForce( 1.0 );
   DAQ_SetOutForce( 1.0 );
   DAQ_SetOutValve( 0 );
   DAQ_SetInValve( 1 );
   
   DAQ_Delay( 1000 );
   // ���ò���
   g_S700KData.Control.usStep = 9;
   
   // ��λλ�Ƽ�����
   DAQ_ResetStroke( );
   // ���ó�ʱ��ʼʱ��
   dwTicksError = GetTickCount( );
   // ת�޻�����
   DAQ_InControl( 1 );
   DAQ_OutControl( 0 );
   
   // ����λ�Ƴ�ʼֵ
   dfDistance = fabs (DAQ_ReadStroke ());
   DAQ_Delay( 300 );
   while( 1 )
   {
      // ��ʱ
      DAQ_Delay (10);
      // �����λ����
      if (DAQ_ReadLeft ())
         break;
      // �ɼ�����
      DAQ_CheckMeasure ();
      
      // �����飬�����ʱ�˳�
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }

      // ���û���ߵ�ָ��λ�ã�����
      if (fabs (DAQ_ReadStroke () - dfDistance) < fStroke)
         continue;
     
      // ͬʱ�Ӵ��򷧿�������ʹת�޻�����
      DAQ_SetInForce( 8.0 );
      DAQ_SetOutForce( 8.0 );
      DAQ_SetTotalValve( 0 );
      DAQ_SetOutValve( 0 );
      DAQ_SetInValve( 0 );
     
      // �˳�
      break;
   }
   
   // ����5��
   DAQ_InControl( 1 );
   DAQ_OutControl( 0 );
   DAQ_Delay (5000);
   
   // �Ͽ����ƣ���ʱ3��
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_Delay (3000);
   
   // ���ò���
   g_S700KData.Control.usStep = 10;
   
   // ת�޻�����
   DAQ_InControl (0);
   DAQ_OutControl (1);
   // ����5��
   DAQ_Delay (5000);
   DAQ_InControl (0);
   DAQ_OutControl (0);
   // �Ͽ����ƣ���ʱ3��
   DAQ_Delay (3000);

   // ���ò���
   g_S700KData.Control.usStep = 9;
   DAQ_InControl( 1 );
   DAQ_OutControl( 0 );
   DAQ_Delay (5000);
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_Delay (3000);
   
   // ���ò���
   g_S700KData.Control.usStep = 10;
   DAQ_InControl (0);
   DAQ_OutControl (1);
   DAQ_Delay (5000);
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_Delay (3000);

   // ���ò���
   g_S700KData.Control.usStep = 9;
   DAQ_InControl( 1 );
   DAQ_OutControl( 0 );
   DAQ_Delay (5000);
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_Delay (3000);
   
   // ���ò���
   g_S700KData.Control.usStep = 10;
   DAQ_InControl (0);
   DAQ_OutControl (1);
   DAQ_Delay (5000);
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_Delay (3000);

   // ���ò���
   g_S700KData.Control.usStep = 9;
   
   // ��λ����
   DAQ_SetTotalValve (0);
   DAQ_SetInForce (1.0);
   DAQ_SetOutForce (1.0);
   DAQ_SetOutValve (0);
   DAQ_Delay (1000);
   DAQ_InControl (1);
   DAQ_OutControl (0);
   DAQ_SetInValve (1);
   
   // ��ת�޻�����ͣ��Aλ
   dwTicksError = GetTickCount( );
   while( 1 )
   {
      if (DAQ_ReadLeft ())
         break;
      DAQ_CheckMeasure ();
     
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }

      DAQ_Delay (120);
   }
   DAQ_Delay (3000);
   DAQ_InControl (0);
   DAQ_OutControl (1);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (1);
   
   // ��ת�޻�����ͣ��Bλ
   dwTicksError = GetTickCount( );
   while( 1 )
   {
      if (DAQ_ReadRight ())
         break;
      DAQ_CheckMeasure ();
     
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }

      DAQ_Delay (120);
   }
   
   // ���Խ���
   DAQ_SetOutForce (0.0);
   DAQ_SetInForce (0.0);
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_SetTotalValve (0);
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);

   return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// S700Kת�޻�����
// ����:
//    pDevice     �������ת�޻�����
//    pData       ����ת�޻���������
// ���:
//    ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
int WINAPI ZDJ9_ThreadRoutine( LPT_Device pDevice, LPT_Record pData )
{
   // ��ʱ��ʼ
   g_DAQSystemData.dwMeasureTicks = GetTickCount ();
   g_S700KData.Control.usStep = 0;

//   DAQ_ACSelect (1);
   // ���ͱ�
   DAQ_OilBumpControl (1);
   // ��ʱ2��
   DAQ_Delay (2000);

   // ת�޻��������̼�飬������ɹ��˳�
   // if (ZDJ9_DeviceCheck (pDevice, pData) == -1)
   //    goto Exit;
   
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_S700KData.Control.usTerminate)
      goto Exit;

   // ���Ҫ�����Load2
   if (g_Device.Config.usLoad2Test == 1)
   {
   // ����Load2��������ɹ��˳� 
      if (ZDJ9_MeasureLoad2 (pDevice, pData) == -1)
         goto Exit;
   // ���Ҫ��ֹͣ���ԣ�����
      if (g_S700KData.Control.usTerminate)
         goto Exit;
   }

   // ���Ҫ�����Load1
   if (g_Device.Config.usLoad1Test == 1)
   {
   // ����Load1��������ɹ��˳� 
      if (ZDJ9_MeasureLoad1 (pDevice, pData) == -1)
         goto Exit;
   // ���Ҫ��ֹͣ���ԣ�����
      if (g_S700KData.Control.usTerminate)
         goto Exit;
   }

   // ���Ҫ�����Load3
   if (g_Device.Config.usLoad3Test == 1)
   {
   // ����Load3��������ɹ��˳� 
      if (ZDJ9_MeasureLoad3 (pDevice, pData) == -1)
         goto Exit;
   // ���Ҫ��ֹͣ���ԣ�����
      if (g_S700KData.Control.usTerminate)
         goto Exit;
   }
   
   // ���Ҫ����Ա�����
   // if (g_Device.Config.usRevisionTest == 1)
   // {
   // ���Ա�������������ɹ��˳� 
      // if (ZDJ9_MeasureRevision (pDevice, pData) == -1)
      //    goto Exit;
   // ���Ҫ��ֹͣ���ԣ�����
      // if (g_S700KData.Control.usTerminate)
      //    goto Exit;
   // }
   
   // ���Ҫ����Լ�����
   // if (g_Device.Config.usTraillingTest == 1)
   // {
   // ���Լ�������������ɹ��˳� 
      // if (ZDJ9_MeasureTrailling (pDevice, pData) == -1)
      //    goto Exit;
   // ���Ҫ��ֹͣ���ԣ�����
      // if (g_S700KData.Control.usTerminate)
      //    goto Exit;
   // }

   // ��ʱ
   DAQ_Delay (2000);
   
   // �����˳�
Exit:
//   SetCtrlVal (plMain, PANELMAIN_NG_Time, g_S700KData.Control.ulMeasTime);
   
   // ��λ���
   DAQ_InControl (0);                
   DAQ_OutControl (0);
   DAQ_SimulateTrack (0);
   DAQ_SetInForce (0.0);
   DAQ_SetOutForce (0.0);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (0);
   DAQ_SetTotalValve (0);
   Sleep (100);
   DAQ_OilBumpControl (0);
   Sleep (100);
   DAQ_OilBumpControl (0);
   return 0;
}
//------------------------------------------------------------------------------------------------

