// #########################################################################
// *************************************************************************
//           Copyright (C) 2002-2004, Xi'an KeXing M&C Ltd. Corp.
//   THIS IS AN UNPUBLISHED WORK CONTAINED CONFIDENTIAL, AND PROPRIETARY
//     INFORMATION WHICH IS THE PROPERTY OF Xi'an KeXing M&C Ltd. Corp.
// ANY DISCLOSURE, USE, OR REPRODUCTION, WITHOUT WRITTERN AUTHORIZATION FROM
//            Xi'an KeXing M&C Ltd. Corp., IS STRICT
// #########################################################################
// *************************************************************************

//------------------------------------------------------------------------------------------------
#include "global.h"
#include <cvirte.h>     
#include <userint.h>
#include "S700K.h"
#include "inifile.h"
#include "Device.h"
#include "DAQDefine.h"
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
//extern int              g_plDCTable;
extern int              g_plDAQMain;
//extern PT_Device        g_Device;
//extern PT_Record        g_S700KData;
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
int __stdcall ZD6S_DeviceCheck(LPT_Device pDevice, LPT_Record pData)
{
   double   dfStroke, dfStrokeS, dfStrokeE;
   
   DWORD    dwTicksError;
   double   dfDiff;
   
   // ���ó�ʱΪ10��
   DWORD    dwTimeout = 10000;
  
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // ����ת�޻�����ʱ�������ʱֵ
   //if (g_Device.Database.fLoad1_TravelTime > 0)
   //   dwTimeout = g_Device.Database.fLoad3_TravelTime * 1000 + 2000;
   
   // ����ת�޻���������
//   g_S700KData.Control.usStep = 0;
   
   // ת�޻��˻�A / Left λ
   DAQ_SimulateTrack (0);
   //DAQ_DCRightControl (0);
   //DAQ_DCLeftControl (1);
   DAQ_SetOutForce (0.0);
   DAQ_SetInForce (0.0);
   DAQ_SetTotalValve (0);
   
   // ������ʼʱ��
   dwTicksError = GetTickCount ();
   while (1)
   {
      // �����λ������
      if (DAQ_DCReadLeft ())
         break;
      // ���ݲɼ�
      DAQ_CheckMeasure ();
      
      // �����ʱ������״̬�����ش���
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         goto Error;
      }
      Sleep( 10 );
   }
   // �Ͽ����
   //DAQ_DCLeftControl(0);

   // ��ʱ2��
   DAQ_Delay(2000);
   
   // ת�޻������˶�
   //DAQ_DCRightControl(1);
   // ������ʼʱ��
   dwTicksError = GetTickCount( );
   while( 1 )
   {
      // �����λ������
      if (DAQ_DCReadRight( ) )
         break;
      // ���ݲɼ�
      DAQ_CheckMeasure( );
      
      // �����ʱ������״̬�����ش���
      if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
         goto Error;
      }
      
      Sleep( 10 );
   }
   // �Ͽ����
   //DAQ_DCRightControl( 0 );

   // ��ʱ2��
   DAQ_Delay( 2000 );

   // ����ת�޻���������
//   g_S700KData.Control.usStep = 1;
   
   // ��λλ�Ʋ���������������ԭ��
   DAQ_ResetStroke();
   // ����λ����ʼֵ
   dfStrokeS = DAQ_ReadStroke ();
   // ת�޻�����
   //DAQ_DCLeftControl( 1 );
   // ������ʼʱ��
   dwTicksError = GetTickCount();
   while( 1 )
   {
      // �����λ������
      if (DAQ_DCReadLeft())
         break;
      // ���ݲɼ�
      DAQ_CheckMeasure();
      
      // �����ʱ������״̬�����ش���
      if (DAQ_CheckError(GetTickCount() - dwTicksError, dwTimeout))
      {
         goto Error;
      }
      
      Sleep(10);
   }
   // ����λ����ֵֹ
   dfStrokeE = DAQ_ReadStroke ();
   // ���㶯��
   dfStroke = fabs (dfStrokeE - dfStrokeS);
   
   // ��������ֵ
   dfDiff = pDevice->ssRatedStroke.fData1 - dfStroke;
   if ((dfDiff > 0.0) && (dfDiff <= 1.0))
      dfStroke += 1.0;
   else if ((dfDiff > 1.0) && (dfDiff <= 2.0))
      dfStroke += 2.0;
   
   // �������ֵ������ʾ
   pData->ptMeasureDataF.dfStroke = dfStroke;
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_DISB_B, dfStroke);

   //DAQ_DCLeftControl( 0 );
   
   // ��ʱ1��
   DAQ_Delay( 1000 );
   
   // ����ת�޻���������
//   g_S700KData.Control.usStep = 2;
   
   // ��λλ�Ʋ���������������ԭ��
   DAQ_ResetStroke ();
   // ����λ����ʼֵ
   dfStrokeS = DAQ_ReadStroke ();
   // ת�޻�����
   //DAQ_DCRightControl( 1 );
   // ������ʼʱ��
   dwTicksError = GetTickCount( );
   // ȡ���ص���
   while( 1 )
   {
      // �����λ������
      if ( DAQ_DCReadRight( ) )
         break;
      // ���ݲɼ�
      DAQ_CheckMeasure( );
      
      // �����ʱ������״̬�����ش���
      if ( DAQ_CheckError( GetTickCount() - dwTicksError, dwTimeout ) )
      {
         goto Error;
      }
      Sleep( 10 );
   }
   // ����λ����ֵֹ
   dfStrokeE = DAQ_ReadStroke( );
   // ���㶯��
   dfStroke = fabs( dfStrokeE - dfStrokeS );

   // ��������ֵ
   dfDiff = pDevice->ssRatedStroke.fData1 - dfStroke;
   if ((dfDiff > 0.0) && (dfDiff <= 1.0))
      dfStroke += 1.0;
   else if ((dfDiff > 1.0) && (dfDiff <= 2.0))
      dfStroke += 2.0;
   
   // �������ֵ������ʾ
   pData->ptMeasureDataD.dfStroke = dfStroke;
   SetCtrlVal(g_plDAQMain, DAQMAIN_NG_DISB_A, dfStroke);

   //DAQ_DCRightControl(0);
   DAQ_SetTotalValve(0);
   
   return 0;
Error:
   // ��λ���
  // DAQ_SetDCVoltage (0);
   //DAQ_DCLineControl (0);
   //DAQ_DCLeftControl (0);                
   //DAQ_DCRightControl (0);
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
   
   return -1;
   
}

//------------------------------------------------------------------------------------------------
// ת�޻�Load3���������ת�޻��ڹ涨��ʱ���ڲ�����ɶ����ͷ��ش���
// ����:
//    pDevice     �������ת�޻�����
//    pData       ����ת�޻���������
// ���:
//    ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
DWORD __stdcall ZD6S_Measure_A( LPT_Device pDevice, LPT_Record pData )
{
   double   dfTicksS;
   double   dfActionTime;
   double   dfDistanceS;
   double   dfDistance;
   double   dfTicks;
   DWORD    dwTicksA;
   DWORD    dwTicksError;
   BOOL     bOk = FALSE;
   DWORD    dwRetCode = 0;
   double   dfIdc = 0.0, dfUdc = 0.0;
   DWORD    dwCount = 0;
   BOOL     bStart = 0;
   DWORD    dwTimeout = 10000;
   double   dfStroke;
   double   dfForceCount = 0.0;
   double   dfAOForce;
   double   dfDelta, dfDiff;
   double   dfSpeed;
   short    usSkiped = 0;
   short    usError = 0;
//   double   dfRatedForce = 0.0;
   double   dfHalfStroke;
//   double   dfMinLoad2Force;
   
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // ����ֻ�ڶ��̹������в������ݴ���
   dfHalfStroke = g_Device.ssRatedStroke.fData1 / 2;
   dfHalfStroke += 10.0;

   // ����ת�޻�����ʱ�������ʱֵ
//   if (g_Device.Database.fLoad3_TravelTime > 0)
//      dwTimeout = g_Device.Database.fLoad3_TravelTime * 1000 + 1000;

   // ��������̨����ʼ״̬
   DAQ_SetInForce (pDevice->ssAValveVoltage1.fData1);
   DAQ_SetOutForce (pDevice->ssBValveVoltage1.fData1); 
   
   // �رջ���
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (0);
   
   DAQ_Delay (1000);
   
   // �򿪻��򷧣�ת�޻�����
   DAQ_SetOutValve (1);
   //DAQ_DCRightControl (1);
   
   // ��λλ��
   DAQ_ResetStroke ();
   // ��ȡλ�Ƴ�ʼֵ
   dfStroke = DAQ_ReadStroke ();
   // ��ʼʱ��
   dwTicksError = GetTickCount ();
   dwTicksA = GetTickCount ();
   dfDistanceS = DAQ_ReadStroke ();
   dfTicksS = GetTickCount ();
   while( 1 )
   {
      // ��ʱ
      DAQ_Delay (50);
      // �����λ������
      if (DAQ_DCReadRight ())
         break;
      // �ɼ�����
      DAQ_CheckMeasure ();
      // �����ʱ�����ش���
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         if (usError == 1)
         {
         }
         else
         {
            usError = 1;
            dwTicksError = GetTickCount ();
            goto Error;
         }
      }
      
      // ���ض��Ķ��̷�Χ�ڼ��������ƽ��ֵ����Ϊ�޷�����ʱ�Ĳ������
      dfDistance = DAQ_ReadStroke ();
      if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->ssRatedStroke.fData1))
      {
         // �ۼӲ���ֵ
         dwCount ++;
         dfForceCount += DAQ_ReadForce ();
         dfUdc += g_DAQData.Data.dfUdc;
         dfIdc += g_DAQData.Data.dfIdc;
         
         // ������ʾֵ
         pData->ptMeasureDataD.dfForce = dfForceCount / dwCount;
         pData->ptMeasureDataD.dfU = dfUdc / dwCount;
         pData->ptMeasureDataD.dfI = dfIdc / dwCount;
      }
   }
   
   // ���㶯��ʱ��
   dfActionTime = GetTickCount( ) - dwTicksA;
   // ��ֹ�������
   if ( dwCount == 0 )
      dwCount = 1;
   // ����ƽ��ֵ
   dfForceCount /= dwCount;
   dfUdc /= dwCount;
   dfIdc /= dwCount;
   
   // ���ò������
   pData->ptMeasureDataD.dfU = dfUdc;
   pData->ptMeasureDataD.dfI = dfIdc;
   pData->ptMeasureDataD.dfForce = dfForceCount;
   pData->ptMeasureDataD.dfActionTime = (dfActionTime - 500) / 1000.0;
   
   DAQ_Delay (2000);
   // Ħ��
   dfIdc = 0.0;
   dwCount = 0;
   // ��ʼʱ��
   dwTicksError = GetTickCount ();
   
   while ((GetTickCount () - dwTicksError) < 5000)
   {
      DAQ_Delay (200);
      dfIdc += g_DAQData.Data.dfIdc;
      dwCount ++;
   }
   dfIdc /= dwCount;
   
   // ���ò������
   pData->ptMeasureDataD.dfI_F = dfIdc;
  
   // ��λ����
   //DAQ_DCLeftControl( 0 );
   //DAQ_DCRightControl( 0 );
   DAQ_SetTotalValve( 0 );
   DAQ_SetInForce( 1.0 );
   DAQ_SetOutForce( 1.0 );
   DAQ_SetOutValve( 0 );
   DAQ_SetInValve( 0 );
   
   // ��ʾ����ֵ
   SetCtrlVal( g_plDAQMain, DAQMAIN_NG_F_3_1, pData->ptMeasureDataD.dfForce );
   SetCtrlVal( g_plDAQMain, DAQMAIN_NG_T_3_1, pData->ptMeasureDataD.dfActionTime );
   return dwRetCode;
Error:
   // ��λ���
  // DAQ_SetDCVoltage (0);
  // DAQ_DCLineControl (0);
   //DAQ_DCLeftControl (0);                
   //DAQ_DCRightControl (0);
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
   
   return -1;
}

//------------------------------------------------------------------------------------------------
// ת�޻�Load3���������ת�޻��ڹ涨��ʱ���ڲ�����ɶ����ͷ��ش���
// ����:
//    pDevice     �������ת�޻�����
//    pData       ����ת�޻���������
// ���:
//    ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
DWORD __stdcall ZD6S_Measure_B(LPT_Device pDevice, LPT_Record pData)
{
   double   dfTicksS;
   double   dfActionTime;
   double   dfDistanceS;
   double   dfDistance;
   double   dfTicks;
   DWORD    dwTicksA;
   DWORD    dwTicksError;
   BOOL     bOk = FALSE;
   DWORD    dwRetCode = 0;
   double   dfIdc = 0.0;
   double   dfUdc = 0.0;
   DWORD    dwCount = 0;
   BOOL     bStart = 0;
   DWORD    dwTimeout = 10000;
   double   dfStroke;
   double   dfForceCount = 0.0;
   double   dfAOForce;
   double   dfDelta, dfDiff;
   double   dfSpeed;
   short    usSkiped = 0;
   short    usError = 0;
//   double   dfRatedForce = 0.0;
   double   dfHalfStroke;
   double   dfMinLoad2Force;
   
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // ����ֻ�ڶ��̹������в������ݴ���
   dfHalfStroke = g_Device.ssRatedStroke.fData1 / 2;
   dfHalfStroke += 10.0;
   
   // ����ת�޻�����ʱ�������ʱֵ
//   if (g_Device.Database.fLoad3_TravelTime > 0)
//      dwTimeout = g_Device.Database.fLoad3_TravelTime * 1000 + 1000;
   
   // ��������̨����ʼ״̬
   DAQ_SetInForce (pDevice->ssAValveVoltage2.fData1);
   DAQ_SetOutForce (pDevice->ssBValveVoltage2.fData1); 
   
   // �رջ���
   DAQ_SetTotalValve (0);
   DAQ_SetOutValve (0);
   
   DAQ_Delay (1000);
   
   // �򿪻��򷧣�ת�޻�����
   DAQ_SetInValve (1);
   //DAQ_DCLeftControl (1);
   
   // ��λλ��
   DAQ_ResetStroke ();
   // ��ȡλ�Ƴ�ʼֵ
   dfStroke = DAQ_ReadStroke ();
   // ��ʼʱ��
   dwTicksError = GetTickCount ();
   dwTicksA = GetTickCount ();
   dfDistanceS = DAQ_ReadStroke ();
   dfTicksS = GetTickCount ();
   while( 1 )
   {
      // ��ʱ
      DAQ_Delay (50);
      // �����λ������
      if (DAQ_DCReadLeft ())
         break;
      // �ɼ�����
      DAQ_CheckMeasure ();
      // �����ʱ�����ش���
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         if (usError == 1)
         {
            goto Error;
         }
         else
         {
            usError = 1;
            dwTicksError = GetTickCount ();
            goto Error;
         }
      }
      
      // ���ض��Ķ��̷�Χ�ڼ��������ƽ��ֵ����Ϊ�޷�����ʱ�Ĳ������
      dfDistance = DAQ_ReadStroke ();
      if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->ssRatedStroke.fData1))
      {
         // �ۼӲ���ֵ
         dwCount ++;
         dfForceCount += DAQ_ReadForce ();
         dfUdc += g_DAQData.Data.dfUdc;
         dfIdc += g_DAQData.Data.dfIdc;
         
         // ������ʾֵ
         pData->ptMeasureDataF.dfForce = dfForceCount / dwCount;
         pData->ptMeasureDataF.dfU = dfUdc / dwCount;
         pData->ptMeasureDataF.dfI = dfIdc / dwCount;
      }
   }
   
   // ���㶯��ʱ��
   dfActionTime = GetTickCount () - dwTicksA;
   if (dwCount == 0)
      dwCount = 1;
   dfForceCount /= dwCount;
   dfUdc /= dwCount;
   dfIdc /= dwCount;

   // ���ò������
   pData->ptMeasureDataF.dfU = dfUdc;
   pData->ptMeasureDataF.dfI = dfIdc;
   pData->ptMeasureDataF.dfForce = dfForceCount;
   pData->ptMeasureDataF.dfActionTime = (dfActionTime-500)/ 1000.0;
   
   DAQ_Delay (2000);
   // Ħ��
   dfIdc = 0.0;
   dwCount = 0;
   // ��ʼʱ��
   dwTicksError = GetTickCount ();
   
   while ((GetTickCount () - dwTicksError) < 5000)
   {
      DAQ_Delay (200);
      dfIdc += g_DAQData.Data.dfIdc;
      dwCount ++;
   }
   dfIdc /= dwCount;
   
   // ���ò������
   pData->ptMeasureDataF.dfI_F = dfIdc;

   // ��λ����
   DAQ_SetTotalValve (0);
   DAQ_SetInForce (1.0);
   DAQ_SetOutForce (1.0);
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);
   //DAQ_DCLeftControl (0);
   //DAQ_DCRightControl (0);

   // ��ʾ����ֵ
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_3_2, pData->ptMeasureDataF.dfForce);
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_T_3_2, pData->ptMeasureDataF.dfActionTime);
   return dwRetCode;
Error:
   // ��λ���
   //DAQ_SetDCVoltage (0);
   //DAQ_DCLineControl (0);
   //DAQ_DCLeftControl (0);                
   //DAQ_DCRightControl (0);
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
   
   return -1;
}

//------------------------------------------------------------------------------------------------
DWORD WINAPI ZD6S_ThreadRoutine_Normal (LPT_Device pDevice, LPT_Record pData)
{
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_DAQSystemData.usTerminate)
      return -1;

   // ��ʱ
   DAQ_Delay (1000);
   DAQ_Delay (1000);
   
   // ���ò���
//   g_S700KData.Control.usStep = 207;
   // B�����
   if (ZD6S_Measure_B (pDevice, pData) == -1)
      return -1;
   
   // ��ʱ
   DAQ_Delay (1000);
   DAQ_Delay (1000);

   // ���ò���
//   g_S700KData.Control.usStep = 208;
   // A�����
   if (ZD6S_Measure_A (pDevice, pData) == -1)
      return -1;
   
  // DAQ_SetDCVoltage (0);

   return 0;
}

//------------------------------------------------------------------------------------------------
int __stdcall ZD6S_ThreadRoutine( LPT_Device pDevice, LPT_Record pData )
{
   DAQ_ACSelect (0);
   //DAQ_DCSelect (1);
   
   //DAQ_DCLineControl (1);
   
   // DC Voltage, 160V
  // if (pDevice->ssDCVoltageSet.fData1 > 0)
 //     DAQ_SetDCVoltage (pDevice->ssDCVoltageSet.fData1);
 //  else
 //     DAQ_SetDCVoltage (3.02);
   
   if (ZD6S_DeviceCheck (pDevice, pData))
      goto Exit;
   if (g_DAQSystemData.usTerminate)
      goto Exit;

   DAQ_Delay (2000);
   DAQ_OilBumpControl (1);
   
   ZD6S_ThreadRoutine_Normal (pDevice, pData);
   if (g_DAQSystemData.usTerminate)
      goto Exit;
   
Exit:
//   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_Time, g_S700KData.Control.ulMeasTime);
   
   // ��λ���
  // DAQ_SetDCVoltage (0);
  // DAQ_DCLineControl (0);
   //DAQ_DCLeftControl (0);                
   //DAQ_DCRightControl (0);
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

