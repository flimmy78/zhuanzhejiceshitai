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
extern int              g_plDAQMain;
extern PT_Record        g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_DAQSystemData g_DAQSystemData;
extern PT_Device        g_Device;
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
int __stdcall ZDJ9_DeviceCheck( LPT_Device pDevice, LPT_Record pData )
{
   double   dfDistance, dfDistanceS, dfDistanceE;
   
   DWORD    dwTicksError;
   double   dfDiff;
   
   // ���ó�ʱΪ10��
   DWORD    dwTimeout = 10000;
  
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // ����ת�޻�����ʱ�������ʱֵ
   if (g_Device.Standard.fLoad1_TravelTime > 0)
      dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 2000;
   
   // ����ת�޻���������
   g_S700KData.Control.usStep = 0;
   
   // ת�޻��˻�A / Left λ
   DAQ_SimulateTrack(0);
   DAQ_OutControl(0);
   DAQ_InControl(1);
   DAQ_SetOutForce( 0.0 );
   DAQ_SetInForce( 0.0 );
   DAQ_SetTotalValve( 1 );
   
   // ������ʼʱ��
   dwTicksError = GetTickCount( );
   while( 1 )
   {
      // �����λ������
      if ( DAQ_ReadLeft())
         break;
      // ���ݲɼ�
      DAQ_CheckMeasure();
      
      // �����ʱ������״̬�����ش���
      if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      Sleep( 10 );
   }
   // �Ͽ����
   DAQ_InControl(0);

   // ��ʱ2��
   DAQ_Delay(2000);
   
   // ת�޻������˶�
   DAQ_OutControl(1);
   // ������ʼʱ��
   dwTicksError = GetTickCount( );
   while( 1 )
   {
      // �����λ������
      if ( DAQ_ReadRight( ) )
         break;
      // ���ݲɼ�
      DAQ_CheckMeasure( );
      
      // �����ʱ������״̬�����ش���
      if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      
      Sleep( 10 );
   }
   // �Ͽ����
   DAQ_OutControl( 0 );

   // ��ʱ2��
   DAQ_Delay( 2000 );

   // ����ת�޻���������
   g_S700KData.Control.usStep = 1;
   
   // ��λλ�Ʋ���������������ԭ��
   DAQ_ResetStroke();
   // ����λ����ʼֵ
   dfDistanceS = DAQ_ReadStroke ();
   // ת�޻�����
   DAQ_InControl( 1 );
   // ������ʼʱ��
   dwTicksError = GetTickCount();
   while( 1 )
   {
      // �����λ������
      if (DAQ_ReadLeft())
         break;
      // ���ݲɼ�
      DAQ_CheckMeasure();
      
      // �����ʱ������״̬�����ش���
      if (DAQ_CheckError(GetTickCount() - dwTicksError, dwTimeout))
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      
      Sleep(10);
   }
   // ����λ����ֵֹ
   dfDistanceE = DAQ_ReadStroke ();
   // ���㶯��
   dfDistance = fabs( dfDistanceE - dfDistanceS );
   
   // ��������ֵ
   dfDiff = pDevice->Standard.fStroke - dfDistance;
   if ((dfDiff > 0.0) && (dfDiff <= 1.0))
      dfDistance += 1.0;
   else if ((dfDiff > 1.0) && (dfDiff <= 2.0))
      dfDistance += 2.0;
   
   // �������ֵ������ʾ
   pData->ptMeasureDataB.ptCheckData.dfInterval = dfDistance;
   pData->ptMeasureDataB.ptCheckData.bCheckState = TRUE;
   SetCtrlVal( g_plDAQMain, DAQMAIN_NG_DISB_B, dfDistance );

   DAQ_InControl( 0 );
   
   // ��ʱ1��
   DAQ_Delay( 1000 );
   
   // ����ת�޻���������
   g_S700KData.Control.usStep = 2;
   
   // ��λλ�Ʋ���������������ԭ��
   DAQ_ResetStroke ();
   // ����λ����ʼֵ
   dfDistanceS = DAQ_ReadStroke ();
   // ת�޻�����
   DAQ_OutControl( 1 );
   // ������ʼʱ��
   dwTicksError = GetTickCount( );
   // ȡ���ص���
   while( 1 )
   {
      // �����λ������
      if ( DAQ_ReadRight( ) )
         break;
      // ���ݲɼ�
      DAQ_CheckMeasure( );
      
      // �����ʱ������״̬�����ش���
      if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
         ZDJ9_ErrorHandle (pDevice, pData);
         return -1;
      }
      Sleep( 10 );
   }
   // ����λ����ֵֹ
   dfDistanceE = DAQ_ReadStroke( );
   // ���㶯��
   dfDistance = fabs( dfDistanceE - dfDistanceS );

   // ��������ֵ
   dfDiff = pDevice->Standard.fStroke - dfDistance;
   if ((dfDiff > 0.0) && (dfDiff <= 1.0))
      dfDistance += 1.0;
   else if ((dfDiff > 1.0) && (dfDiff <= 2.0))
      dfDistance += 2.0;
   
   // �������ֵ������ʾ
   pData->ptMeasureDataA.ptCheckData.dfInterval = dfDistance;
   pData->ptMeasureDataA.ptCheckData.bCheckState = TRUE;
   SetCtrlVal(g_plDAQMain, DAQMAIN_NG_DISB_A, dfDistance);

   DAQ_OutControl(0);
   DAQ_SetTotalValve(0);
   
   return 0;
}

//------------------------------------------------------------------------------------------------
