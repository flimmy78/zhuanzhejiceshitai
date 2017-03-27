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
extern PT_Record        g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_DAQSystemData g_DAQSystemData;
extern PT_Device        g_Device;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// ת�޻����������������ת�޻��ڹ涨��ʱ���ڲ�����ɶ����ͷ��ش���
// ����:
//    pDevice     �������ת�޻�����
//    pData       ����ת�޻���������
// ���:
//    ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
DWORD __stdcall ZDJ9_MeasureTrailling_A( LPT_Device pDevice, LPT_Record pData )
{
   double   dfTicks;
   DWORD    dwTicksError;
   DWORD    dwRetCode = 0;
   DWORD    dwTimeout = 10000;
   double   dfStrokeS;
   double   dfMaxForce = 0.0;
   double   dfStroke;
   
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // ����ת�޻�����ʱ�������ʱֵ
   if (g_Device.Standard.fLoad1_TravelTime > 0)
      dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 4000;

   // ���ñ�������ʼ����ֵ
   g_DAQSystemData.fAOAForce = 5.5;
   g_DAQSystemData.fAOBForce = 1.0;
   
   // �򿪱���������ʼ����
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   
   // �򿪻���
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (1);
   DAQ_SetOutValve (0);
   
   DAQ_Delay (1000);
   
   // ת�޻�����
   DAQ_InControl (0);
   
   // ��λλ��
   DAQ_ResetStroke ();
   // ��ȡλ�Ƴ�ʼֵ
   dfStrokeS = DAQ_ReadStroke ();
   while (1)
   {
      // �ɼ�����
      DAQ_CheckMeasure ();
      
      // ��ʱ
      DAQ_Delay (50);
      
      // �Ƚϲɼ�����֮ǰ�������������¼�����
      if (dfMaxForce < DAQ_ReadForce ())
         dfMaxForce = DAQ_ReadForce ();
      
      // ����ɼ�������30KNֹͣ����
      if (DAQ_ReadForce () > 30.0)
         break;
      
      // ����λ�Ƽ�����
      dfStroke = DAQ_ReadStroke ();
      // ���ת�޻��Ѿ��߳�50mm����Ϊ���Բ��ɹ��˳�
      if (fabs (dfStroke - dfStrokeS) > 50.0)
      {
         break;
      }
      DAQ_Delay (50);
      
      // ���ڱ�����
      g_DAQSystemData.fAOAForce += 0.05;
      // ���Ʊ���������
      if (g_DAQSystemData.fAOAForce > 9.0)
         break;
      
      // ���ñ���������
      DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   }
   
   // ��¼��������Ϊ������
   pData->ptMeasureDataA.ptTraillingData.dfForce = dfMaxForce;
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_4_1, dfMaxForce);
   
   // ж�أ���λ����
   g_DAQSystemData.fAOAForce = 1.0;
   g_DAQSystemData.fAOBForce = 1.0;
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (1);
   
   // ��ʱ2��
   DAQ_Delay (2000);
   
   // ����λ��
   dfStroke = fabs (DAQ_ReadStroke () - dfStrokeS);

   // ��������������
   g_DAQSystemData.fAOAForce = 1.0;
   g_DAQSystemData.fAOBForce = 5.0;
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   
   // �򿪻���
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (1);

   // ��λλ��
   DAQ_ResetStroke ();
   // ��ȡλ�Ƴ�ʼֵ
   dfStrokeS = DAQ_ReadStroke ();
   dwTicksError = GetTickCount ();
   while (1)
   {
      // �ɼ�����
      DAQ_CheckMeasure ();
      
      DAQ_Delay (10);
      
      // �����ʱ�����ش���
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      
      // ת�޻�����ǰ����˵��ת�޻��Ѿ�����
      if (fabs (DAQ_ReadStroke () - dfStrokeS) >= dfStroke)
      {
         break;
      }
   }

   // ��λ����
   DAQ_SetInForce (0.0);
   DAQ_SetOutForce (0.0);
   DAQ_SetTotalValve (1);
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);
   
   // ת�޻��ƶ�����λ
   DAQ_InControl (0);
   DAQ_OutControl (1);
   
   // ���ó�ʱֵ
   dwTimeout = 7000;
   if (g_Device.Standard.fLoad1_TravelTime > 0)
      dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;
   dwTicksError = GetTickCount ();
   while (1)
   {
      // �����λ������
      if (DAQ_ReadRight ())
         break;
      // �ɼ�����
      DAQ_CheckMeasure ();
      // �����ʱ�����ش���
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      DAQ_Delay (50);
   }
   
   // ��λ����
   DAQ_InControl (0);
   DAQ_SetTotalValve (0);
   DAQ_SetInForce (0.0);
   DAQ_SetOutForce (0.0);
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);
   DAQ_OutControl (0);

   return dwRetCode;
}

//------------------------------------------------------------------------------------------------
DWORD __stdcall ZDJ9_MeasureTrailling_B( LPT_Device pDevice, LPT_Record pData )
{
   double   dfTicks;
   DWORD    dwTicksError;
   DWORD    dwRetCode = 0;
   DWORD    dwTimeout = 10000;
   double   dfStrokeS;
   double   dfMaxForce = 0.0;
   double   dfStroke;
   
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_DAQSystemData.usTerminate)
      return -1;

   // ����ת�޻�����ʱ�������ʱֵ
   if (g_Device.Standard.fLoad1_TravelTime > 0)
     dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 4000;
   
   // ���ñ�������ʼ����ֵ
   g_DAQSystemData.fAOAForce = 1.0;
   g_DAQSystemData.fAOBForce = 5.5;
   
   // �򿪱���������ʼ����
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   
   // �򿪻���
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (1);
   
   DAQ_Delay (1000);
   
   // ת�޻�����
   DAQ_InControl (0);
   
   // ��λλ��
   DAQ_ResetStroke ();
   // ��ȡλ�Ƴ�ʼֵ
   dfStrokeS = DAQ_ReadStroke ();
   while (1)
   {
      // �ɼ�����
      DAQ_CheckMeasure ();
      
      DAQ_Delay (50);
      
      // �Ƚϲɼ�����֮ǰ�������������¼�����
      if (dfMaxForce < DAQ_ReadForce ())
         dfMaxForce = DAQ_ReadForce ();
      // Check force
      
      // ����ɼ�������30KNֹͣ����
      if (DAQ_ReadForce () > 30.0)
         break;
      
      // ����λ�Ƽ�����
      dfStroke = DAQ_ReadStroke ();
      // ���ת�޻��Ѿ��߳�50mm����Ϊ���Բ��ɹ��˳�
      if (fabs (dfStroke - dfStrokeS) > 30.0)
      {
         break;
      }
      DAQ_Delay (50);
      
      // ���ڱ�����
      g_DAQSystemData.fAOBForce += 0.05;
      // ���Ʊ���������
      if (g_DAQSystemData.fAOBForce > 9.0)
         break;
      
      // ���ñ���������
      DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   }
   
   // ��¼��������Ϊ������
   pData->ptMeasureDataB.ptTraillingData.dfForce = dfMaxForce;
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_4_2, dfMaxForce);
   
   // ж�أ���λ����
   g_DAQSystemData.fAOAForce = 1.0;
   g_DAQSystemData.fAOBForce = 1.0;
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (1);
   DAQ_SetOutValve (0);
   
   DAQ_Delay (2000);
   
   // ���㵱ǰλ�ƣ����ڱȽ��Ƿ��� 
   dfStroke = fabs (DAQ_ReadStroke () - dfStrokeS);

   // ��������������
   g_DAQSystemData.fAOAForce = 5.0;
   g_DAQSystemData.fAOBForce = 1.0;
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   
   // �򿪻���
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (1);
   DAQ_SetOutValve (0);

   // ��λλ��
   DAQ_ResetStroke ();
   // ��ȡλ�Ƴ�ʼֵ
   dfStrokeS = DAQ_ReadStroke ();
   dwTicksError = GetTickCount ();
   while (1)
   {
      // �ɼ�����
      DAQ_CheckMeasure ();
      
      DAQ_Delay (10);
      
      // �����ʱ�����ش���
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      
      // ת�޻�����ǰ����˵��ת�޻��Ѿ�����
      if (fabs (DAQ_ReadStroke () - dfStrokeS) >= dfStroke)
      {
         break;
      }
   }

   // ��λ����
   DAQ_SetInForce (0.0);
   DAQ_SetOutForce (0.0);
   DAQ_SetTotalValve (1);
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);
   
   // ת�޻��ƶ�����λ
   DAQ_InControl (1);
   DAQ_OutControl (0);
   
   // ���ó�ʱֵ
   dwTimeout = 7000;
   if (g_Device.Standard.fLoad1_TravelTime > 0)
      dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;
   dwTicksError = GetTickCount ();
   while (1)
   {
      // �����λ���˳�
      if (DAQ_ReadLeft ())
         break;
      // �ɼ�����
      DAQ_CheckMeasure ();
      // �����ʱ�����ش���
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      DAQ_Delay (50);
   }
   
   // ��λ����
   DAQ_InControl (0);
   DAQ_SetTotalValve (0);
   DAQ_SetInForce (0.0);
   DAQ_SetOutForce (0.0);
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);
   DAQ_OutControl (0);

   return dwRetCode;
}

//------------------------------------------------------------------------------------------------
int __stdcall ZDJ9_MeasureTrailling( LPT_Device pDevice, LPT_Record pData )
{
   
   if (g_DAQSystemData.usTerminate)
      return -1;

   DAQ_Delay (2000);
   
   // Start...........
   DAQ_SimulateTrack (1);
   
   g_S700KData.Control.usStep = 11;
   if (ZDJ9_MeasureTrailling_B (pDevice, pData) == -1)
      return -1;

   DAQ_Delay( 2000 );

   g_S700KData.Control.usStep = 12;
   if (ZDJ9_MeasureTrailling_A (pDevice, pData) == -1)
      return -1;

   DAQ_SimulateTrack( 0 );
   
   return 0;
}

//------------------------------------------------------------------------------------------------
