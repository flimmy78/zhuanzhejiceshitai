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
int __stdcall S700K_DeviceCheck( LPT_Device pDevice, LPT_Record pData )
{
   double   dfDistance, dfDistanceS, dfDistanceE;
   
   DWORD    dwTicksError;
   double   dfDiff;
   int retValue = 0;
   
   // ���ó�ʱΪ10��
   DWORD    dwTimeout = 10000;
  
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // ����ת�޻�����ʱ�������ʱֵ
   if (g_Device.Standard.fLoad3_TravelTime > 0)
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
   // ����Bת�޻���ת
   while( 1 )
   {
	  // ���ݲɼ�
      DAQ_CheckMeasure();
      
      // �����λ������
      if ( DAQ_ReadLeft())
         break;

      // �����ʱ������״̬�����ش���
      if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
		 pData->Control.usBConnection = 2; // ����B���ߴ���		  		  
         S700K_ErrorHandle (pDevice, pData);
         return -1;
      }
      Sleep( 10 );
   }
   // �Ͽ����
   DAQ_InControl(0);

   // ��ʱ2��
   DAQ_Delay(2000);
   
   // �ƶ�ת�޻�����λ�������˶�
   DAQ_OutControl(1);
   // ������ʼʱ��
   dwTicksError = GetTickCount( );
   
   // ����Aת�޻���ת    
   while( 1 )
   {
	  // ���ݲɼ�
      DAQ_CheckMeasure( );
      // �����λ������
      if ( DAQ_ReadRight( ) )
         break;

      // �����ʱ������״̬�����ش���
      if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
		 pData->Control.usAConnection = 2; // ����A���ߴ���		  		  
         S700K_ErrorHandle (pDevice, pData);
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
   // �ƶ�ת�޻�����λ
   DAQ_InControl( 1 );
   // ������ʼʱ��
   dwTicksError = GetTickCount();
   // ���Է���B����
   while( 1 )
   {
      // �����λ������
      if (DAQ_ReadLeft()){
		 pData->Control.usBConnection = 1; // ����B��������
         break;
	  }
      // ���ݲɼ�
      DAQ_CheckMeasure();
      
      // �����ʱ������״̬�����ش���
      if (DAQ_CheckError(GetTickCount() - dwTicksError, dwTimeout))
      {
		 pData->Control.usBConnection = 2; // ����B���ߴ���		  
         S700K_ErrorHandle (pDevice, pData);
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
   // �˶�ת�޻�����λ������
   DAQ_OutControl( 1 );
   // ������ʼʱ��
   dwTicksError = GetTickCount( );
   // ȡ���ص���
   // ����A���̲���
   while( 1 )
   {
      // �����λ������
      if ( DAQ_ReadRight( ) ){
	  	 pData->Control.usAConnection = 1;  // ����A��������
		 break;
	  }

      // ���ݲɼ�
      DAQ_CheckMeasure( );
      
      // �����ʱ������״̬�����ش���
      if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
	  	 pData->Control.usAConnection = 2; // ����A���ߴ���
         S700K_ErrorHandle (pDevice, pData);
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
   if(dfDiff > 10.0 || dfDiff < -10.0){ // >10mm
   		int ret = MessageBox (NULL, "ת�޻����̲�ƥ��! ����ѡ���˴����ת�޻��ͺš�������������", "����", MB_YESNO | MB_TOPMOST);
		if(IDYES == ret){ // ��������
			retValue = 0;
		}else{
			retValue = -1;// ����
			goto ERR;
		}
   }
ERR:   
   // �������ֵ������ʾ
   pData->ptMeasureDataA.ptCheckData.dfInterval = dfDistance;
   pData->ptMeasureDataA.ptCheckData.bCheckState = TRUE;
   SetCtrlVal(g_plDAQMain, DAQMAIN_NG_DISB_A, dfDistance);

   DAQ_OutControl(0);
   DAQ_SetTotalValve(1);
   
   return retValue;
}

//------------------------------------------------------------------------------------------------
