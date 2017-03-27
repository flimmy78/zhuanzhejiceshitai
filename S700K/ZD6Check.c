// #########################################################################
// *************************************************************************
// ���ת�޻��Ͳ�������
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
extern int              plMain;
extern PT_ReportData    g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_SystemData    g_SystemData;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// ���ת�޻��Ͳ������̣����ת�޻��ڹ涨��ʱ���ڲ�����ɶ����ͷ��ش���
// ����:
//    pDevice     �������ת�޻�����
//    pData       ����ת�޻���������
// ���:
//    ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
int __stdcall ZDS_DeviceCheck( LPT_Device pDevice, LPT_ReportData pData )
{
   double   dfDistance, dfDistanceS, dfDistanceE;
   
   DWORD    dwTicksError;
   double   dfDiff;
   
   // ���ó�ʱΪ10��
   DWORD    dwTimeout = 10000;
  
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_S700KData.Control.usTerminate)
      return -1;
   
   // ����ת�޻�����ʱ�������ʱֵ
   if (g_S700KData.ptDevice.Database.fLoad1_TravelTime > 0)
      dwTimeout = g_S700KData.ptDevice.Database.fLoad3_TravelTime * 1000 + 2000;
   
   // ����ת�޻���������
   g_S700KData.Control.usStep = 0;
   
   // ת�޻��˻�A / Left λ
   DAQ_SimulateTrack(0);
   DAQ_ACRightControl(0);
   DAQ_ACLeftControl(1);
   DAQ_SetOutForce( 0.0 );
   DAQ_SetInForce( 0.0 );
   DAQ_SetTotalValve( 0 );
   
   // ������ʼʱ��
   dwTicksError = GetTickCount( );
   while( 1 )
   {
      // �����λ������
      if ( DAQ_ACReadLeft())
         break;
      // ���ݲɼ�
      DAQ_CheckMeasure();
      
      // �����ʱ������״̬�����ش���
      if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
         ZDS_ErrorHandle (pDevice, pData);
         return -1;
      }
      Sleep( 10 );
   }
   // �Ͽ����
   DAQ_ACLeftControl(0);

   // ��ʱ2��
   DAQ_Delay(2000);
   
   // ת�޻������˶�
   DAQ_ACRightControl(1);
   // ������ʼʱ��
   dwTicksError = GetTickCount( );
   while( 1 )
   {
      // �����λ������
      if ( DAQ_ACReadRight( ) )
         break;
      // ���ݲɼ�
      DAQ_CheckMeasure( );
      
      // �����ʱ������״̬�����ش���
      if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
         ZDS_ErrorHandle (pDevice, pData);
         return -1;
      }
      
      Sleep( 10 );
   }
   // �Ͽ����
   DAQ_ACRightControl( 0 );

   // ��ʱ2��
   DAQ_Delay( 2000 );

   // ����ת�޻���������
   g_S700KData.Control.usStep = 1;
   
   // ��λλ�Ʋ���������������ԭ��
   DAQ_ResetStroke();
   // ����λ����ʼֵ
   dfDistanceS = DAQ_ReadStroke ();
   // ת�޻�����
   DAQ_ACLeftControl( 1 );
   // ������ʼʱ��
   dwTicksError = GetTickCount();
   while( 1 )
   {
      // �����λ������
      if (DAQ_ACReadLeft())
         break;
      // ���ݲɼ�
      DAQ_CheckMeasure();
      
      // �����ʱ������״̬�����ش���
      if (DAQ_CheckError(GetTickCount() - dwTicksError, dwTimeout))
      {
         ZDS_ErrorHandle (pDevice, pData);
         return -1;
      }
      
      Sleep(10);
   }
   // ����λ����ֵֹ
   dfDistanceE = DAQ_ReadStroke ();
   // ���㶯��
   dfDistance = fabs( dfDistanceE - dfDistanceS );
   
   // ��������ֵ
   dfDiff = pDevice->Database.fStroke - dfDistance;
   if ((dfDiff > 0.0) && (dfDiff <= 1.0))
      dfDistance += 1.0;
   else if ((dfDiff > 1.0) && (dfDiff <= 2.0))
      dfDistance += 2.0;
   
   // �������ֵ������ʾ
   pData->ptMeasureDataB.ptCheckData.dfInterval = dfDistance;
   pData->ptMeasureDataB.ptCheckData.bCheckState = TRUE;
   SetCtrlVal( plMain, PANELMAIN_NG_DISB_B, dfDistance );

   DAQLeftControl( 0 );
   
   // ��ʱ1��
   DAQDelay( 1000 );
   
   // ����ת�޻���������
   g_S700KData.Control.usStep = 2;
   
   // ��λλ�Ʋ���������������ԭ��
   DAQ_ResetStroke ();
   // ����λ����ʼֵ
   dfDistanceS = DAQ_ReadStroke ();
   // ת�޻�����
   DAQRightControl( 1 );
   // ������ʼʱ��
   dwTicksError = GetTickCount( );
   // ȡ���ص���
   while( 1 )
   {
      // �����λ������
      if ( DAQ_ACReadRight( ) )
         break;
      // ���ݲɼ�
      DAQCheckMeasure( );
      
      // �����ʱ������״̬�����ش���
      if ( DAQCheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
         ZDS_ErrorHandle (pDevice, pData);
         return -1;
      }
      Sleep( 10 );
   }
   // ����λ����ֵֹ
   dfDistanceE = DAQ_ReadStroke( );
   // ���㶯��
   dfDistance = fabs( dfDistanceE - dfDistanceS );

   // ��������ֵ
   dfDiff = pDevice->Database.fStroke - dfDistance;
   if ((dfDiff > 0.0) && (dfDiff <= 1.0))
      dfDistance += 1.0;
   else if ((dfDiff > 1.0) && (dfDiff <= 2.0))
      dfDistance += 2.0;
   
   // �������ֵ������ʾ
   pData->ptMeasureDataA.ptCheckData.dfInterval = dfDistance;
   pData->ptMeasureDataA.ptCheckData.bCheckState = TRUE;
   SetCtrlVal(plMain, PANELMAIN_NG_DISB_A, dfDistance);

   DAQRightControl(0);
   DAQSetTotalValve(0);
   
   return 0;
}

//------------------------------------------------------------------------------------------------
