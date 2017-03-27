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
#include "toolbox.h"

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
DWORD __stdcall ZDJ9_MeasureLoad3_A( LPT_Device pDevice, LPT_Record pData )
{
   double   dfTicksS = 0;
   double   dfActionTime;
   double   dfDistanceS = 0;
   double   dfDistance;
   double   dfTicks;
   DWORD    dwTicksA;
   DWORD    dwTicksError;
   BOOL     bOk = FALSE;
   DWORD    dwRetCode = 0;
   double   dfIa = 0.0, dfIb = 0.0, dfIc = 0.0;
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
   double   dfRatedForce = 0.0;
   double   dfHalfStroke;
   double   dfMinLoad2Force;
   
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // ����ֻ�ڶ��̹������в������ݴ���
   dfHalfStroke = g_Device.Standard.fStroke / 2;
   dfHalfStroke += 10.0;

   // ����ת�޻�����ʱ�������ʱֵ
   if (g_Device.Standard.fLoad3_TravelTime > 0)
      dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;

   // ѡȡA���B��Load2���е���Сֵ
   dfMinLoad2Force = (g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce < g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce)
      ? g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce : g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce;
   
   // �趨Ϊ����Ŀ����
   dfRatedForce = dfMinLoad2Force;
   
   // ��������Ŀ����
   if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 0.6)
      dfRatedForce -= 0.5;
   else if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 1.0)
      dfRatedForce -= 0.75;
   else
      dfRatedForce -= 0.8;
   
   // ��������Ŀ���������ܱ�Load3���С
   if (dfRatedForce < (g_Device.Standard.fLoad3_OperateForce + 0.05))
      dfRatedForce = g_Device.Standard.fLoad3_OperateForce + 0.05;
   
   // ȡ�û��򷧳�ʼ����ֵ
   g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad3_A2B_AVoltage;
   g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad3_A2B_BVoltage;
   
   // ��������̨����ʼ״̬
   g_DAQSystemData.fAOAForce = 1.0;
   dfAOForce = g_DAQSystemData.fAOBForce; 
   DAQ_SetInForce (1.0);
   DAQ_SetOutForce (1.0); 
   g_DAQSystemData.fAOBForce = 1.0;
   
   // �رջ���
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (0);
   
   DAQ_Delay (1000);
   
   // �򿪻��򷧣�ת�޻�����
   DAQ_SetOutValve (1);
   DAQ_OutControl (1);
   
   // ��λλ��
   DAQ_ResetStroke ();
   // ��ȡλ�Ƴ�ʼֵ
   dfStroke = DAQ_ReadStroke ();
   // ��ʼʱ��
   dwTicksError = GetTickCount ();
   dwTicksA = GetTickCount ();
   // ��λ�����
   g_DAQSystemData.fMaxForce = 0.0;
   while( 1 )
   {
      // ��ʱ
      DAQ_Delay (50);
      // �����λ������
      if (DAQ_ReadRight ())
         break;
      // �ɼ�����
      DAQ_CheckMeasure ();
      // �����ʱ�����ش���
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         break;
      }
      
      // ת�޻�����ʱ������߻��򷧿��ȣ���ֹת�޻�����
      if ((fabs (DAQ_ReadStroke () - dfStroke) < 10) && (bStart == FALSE))
      {
         g_DAQSystemData.fAOBForce += (dfAOForce * 0.7 - 1.0) / 5.0;
         if ( g_DAQSystemData.fAOBForce > dfAOForce * 0.7)
            g_DAQSystemData.fAOBForce = dfAOForce * 0.7;
         DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
         continue;
      }
      else if (bStart == FALSE)
      {
         g_DAQSystemData.fAOBForce = dfAOForce;
         DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
         bStart = TRUE;
         dfDistanceS = DAQ_ReadStroke ();
         dfTicksS = GetTickCount ();
         continue;
      }
      if (usSkiped == 1)
         continue;
      
      // ���뵱ǰλ�ƣ������ٶ�
      dfDistance = DAQ_ReadStroke ();
      dfTicks = GetTickCount ();
      if ((dfTicks - dfTicksS) == 0)
      {
         dfSpeed = fabs (dfDistance - dfDistanceS) * 1000.0;
      }
      else
      {
         dfSpeed = fabs (dfDistance - dfDistanceS) * 1000.0 / (dfTicks - dfTicksS);
      }
      dfTicks = dfTicks;
      dfDistanceS = dfDistance;
      
      // ���ٶȱȽϵ�ʱ��������һ����ʱ�����Ϊת�޻����裬����ʼ��������
      // ��ɲ���������
      if ((dfSpeed < 0.5) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->Standard.fStroke))
      {
         // ���û��ƽ��ֵ���������ֵ����֤�в�������
         if (dfForceCount == 0.0)
         {
            dfForceCount += FAI_FindMaxForce();
            dfIa += g_DAQData.Data.dfIa;
            dfIb += g_DAQData.Data.dfIb;
            dfIc += g_DAQData.Data.dfIc;
            dwCount ++;
            // ������ʾֵ
            pData->ptMeasureDataA.ptLoad3Data.dfForce = dfForceCount / dwCount;
            pData->ptMeasureDataA.ptLoad3Data.dfIa = dfIa / dwCount;
            pData->ptMeasureDataA.ptLoad3Data.dfIb = dfIb / dwCount;
            pData->ptMeasureDataA.ptLoad3Data.dfIc = dfIc / dwCount;
         }
         // �����������
         DAQ_Delay(1000);
         DAQ_SetOutForce (1.0);
         DAQ_SetInForce (1.0);
         DAQ_SetTotalValve (0);
         DAQ_SetOutValve (0);
         DAQ_SetInValve (0);
         usSkiped = 1;
      }

      // ���ض��Ķ��̷�Χ�ڼ��������ƽ��ֵ����Ϊ�޷�����ʱ�Ĳ������
      dfDistance = DAQ_ReadStroke ();
      if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->Standard.fStroke))
      {
         // �ۼӲ���ֵ
         dwCount ++;
         dfForceCount += DAQ_ReadForce ();
         dfIa += g_DAQData.Data.dfIa;
         dfIb += g_DAQData.Data.dfIb;
         dfIc += g_DAQData.Data.dfIc;
         
         // ������ʾֵ
         pData->ptMeasureDataA.ptLoad3Data.dfForce = dfForceCount / dwCount;
         pData->ptMeasureDataA.ptLoad3Data.dfIa = dfIa / dwCount;
         pData->ptMeasureDataA.ptLoad3Data.dfIb = dfIb / dwCount;
         pData->ptMeasureDataA.ptLoad3Data.dfIc = dfIc / dwCount;
      }

      // ����������͵���Ŀ����
      dfDiff = DAQ_ReadForce () - dfRatedForce;
      // �ֵ����ڱ���������
      if (fabs (dfDiff) < 0.08)
         dfDelta = 0.005;
      else if (fabs (dfDiff) < 0.1)
         dfDelta = 0.01;
      else if (fabs (dfDiff) < 0.15)
         dfDelta = 0.02;
      else if (fabs (dfDiff) < 0.2)
         dfDelta = 0.025;
      else if (fabs (dfDiff) < 0.3)
         dfDelta = 0.03;
      else if (fabs (dfDiff) < 0.4) 
         dfDelta = 0.04;
      else
         dfDelta = 0.04;
      
      // �������������
      if (dfDiff > 0.0)
         g_DAQSystemData.fAOBForce -= dfDelta;
      else
         g_DAQSystemData.fAOBForce += dfDelta;
      
      // ��ֹ���������Ƶ��ڷ�Χ
      if (g_DAQSystemData.fAOBForce - dfAOForce > 1.6 )
         g_DAQSystemData.fAOBForce = dfAOForce + 1.6;
      if (g_DAQSystemData.fAOBForce - dfAOForce < -1.6 )
         g_DAQSystemData.fAOBForce = dfAOForce - 1.6;
      
      // ���ڱ���������
      DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   }
   
   // ���㶯��ʱ��
   dfActionTime = GetTickCount( ) - dwTicksA;
   // ��ֹ�������
   if ( dwCount == 0 )dwCount = 1;
   // ����ƽ��ֵ
   dfForceCount /= dwCount;
   dfIa /= dwCount;
   dfIb /= dwCount;
   dfIc /= dwCount;
   
   // �����������ܴ��������
   if ((g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState == 2) && (usSkiped != 1))
   {
   // ��������������ܴ��������
      if (dfForceCount > g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce)
         dfForceCount = g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce;
      
   // ������������Load1���ͬʱLoad1������С��Load1���ʱ
      if ((g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce > g_Device.Standard.fLoad3_OperateForce)
         && (dfForceCount < g_Device.Standard.fLoad3_OperateForce))
      {
      // �����ֵС��0.1KNʱ����Ϊ����ֵ
         if ((g_Device.Standard.fLoad3_OperateForce - dfForceCount) <= 0.1)
            dfForceCount = g_Device.Standard.fLoad3_OperateForce + Random(0.0, 0.05);
      }
   }
   
   // ���ò������
   pData->ptMeasureDataA.ptLoad3Data.dfIa = dfIa;
   pData->ptMeasureDataA.ptLoad3Data.dfIb = dfIb;
   pData->ptMeasureDataA.ptLoad3Data.dfIc = dfIc;
   pData->ptMeasureDataA.ptLoad3Data.dfForce = dfForceCount;
//   pData->ptMeasureDataA.ptLoad3Data.dfActionTime = (dfActionTime-500)/ 1000.0;
   
   // ��λ����
   DAQ_InControl( 0 );
   DAQ_OutControl( 0 );
   DAQ_SetTotalValve( 0 );
   DAQ_SetInForce( 1.0 );
   DAQ_SetOutForce( 1.0 );
   DAQ_SetOutValve( 0 );
   DAQ_SetInValve( 0 );
   
   // ��ʾ����ֵ
   SetCtrlVal( g_plDAQMain, DAQMAIN_NG_F_3_1, pData->ptMeasureDataA.ptLoad3Data.dfForce );
//   SetCtrlVal( g_plDAQMain, DAQMAIN_NG_T_3_1, pData->ptMeasureDataA.ptLoad3Data.dfActionTime );
   return dwRetCode;
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
DWORD __stdcall ZDJ9_MeasureLoad3_B( LPT_Device pDevice, LPT_Record pData )
{
   double   dfTicksS = 0;
   double   dfActionTime;
   double   dfDistanceS = 0;
   double   dfDistance;
   double   dfTicks;
   DWORD    dwTicksA;
   DWORD    dwTicksError;
   BOOL     bOk = FALSE;
   DWORD    dwRetCode = 0;
   double   dfIa = 0.0, dfIb = 0.0, dfIc = 0.0;
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
   double   dfRatedForce = 0.0;
   double   dfHalfStroke;
   double   dfMinLoad2Force;
   
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // ����ֻ�ڶ��̹������в������ݴ���
   dfHalfStroke = g_Device.Standard.fStroke / 2;
   dfHalfStroke += 10.0;
   
   // ����ת�޻�����ʱ�������ʱֵ
   if (g_Device.Standard.fLoad3_TravelTime > 0)
      dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;
   
   // ѡȡA���B��Load2���е���Сֵ
   dfMinLoad2Force = (g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce < g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce)
      ? g_S700KData.ptMeasureDataA.ptLoad2Data.dfForce : g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce;
   
   // �趨Ϊ����Ŀ����
   dfRatedForce = dfMinLoad2Force;

   // ��������Ŀ����
   if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 0.6)
      dfRatedForce -= 0.5;
   else if ((g_Device.Standard.fLoad2_MaxForce - g_Device.Standard.fLoad1_OperateForce) <= 1.0)
      dfRatedForce -= 0.75;
   else
      dfRatedForce -= 0.8;
   
   // ��������Ŀ���������ܱ�Load1���С
   if (dfRatedForce < (g_Device.Standard.fLoad3_OperateForce + 0.05))
      dfRatedForce = g_Device.Standard.fLoad3_OperateForce + 0.05;
   
   // ȡ�û��򷧳�ʼ����ֵ
   g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad3_B2A_AVoltage;
   g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad3_B2A_BVoltage;

   // ��������̨����ʼ״̬
   g_DAQSystemData.fAOBForce = 1.0;
   dfAOForce = g_DAQSystemData.fAOAForce;  
   DAQ_SetOutForce (1.0);
   DAQ_SetInForce (1.0);
   g_DAQSystemData.fAOAForce = 1.0;
   
   // �رջ���
   DAQ_SetTotalValve (0);
   DAQ_SetOutValve (0);
   
   DAQ_Delay (1000);
   
   // �򿪻��򷧣�ת�޻�����
   DAQ_SetInValve (1);
   DAQ_InControl( 1 );
   
   // ��λλ��
   DAQ_ResetStroke ();
   // ��ȡλ�Ƴ�ʼֵ
   dfStroke = DAQ_ReadStroke ();
   // ��ʼʱ��
   dwTicksError = GetTickCount ();
   dwTicksA = GetTickCount ();
   // ��λ�����
   g_DAQSystemData.fMaxForce = 0.0;
   while( 1 )
   {
      // ��ʱ
      DAQ_Delay (50);
      // �����λ������
      if (DAQ_ReadLeft ())
         break;
      // �ɼ�����
      DAQ_CheckMeasure ();
      // �����ʱ�����ش���
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         break;
      }
      
      // ת�޻�����ʱ������߻��򷧿��ȣ���ֹת�޻�����
      if ((fabs (DAQ_ReadStroke () - dfStroke) < 10) && (bStart == FALSE))
      {
         g_DAQSystemData.fAOAForce += (dfAOForce * 0.7 - 1.0) / 5.0;
         if ( g_DAQSystemData.fAOAForce > dfAOForce * 0.7)
            g_DAQSystemData.fAOAForce = dfAOForce * 0.7;
         DAQ_SetInForce (g_DAQSystemData.fAOAForce);
         continue;
      }
      else if (bStart == FALSE)
      {
         g_DAQSystemData.fAOAForce = dfAOForce;
         DAQ_SetInForce (g_DAQSystemData.fAOAForce);
         bStart = TRUE;
         dfDistanceS = DAQ_ReadStroke ();
         dfTicksS = GetTickCount ();
         continue;
      }
      if (usSkiped == 1)
         continue;
      
      // ���뵱ǰλ�ƣ������ٶ�
      dfDistance = DAQ_ReadStroke ();
      dfTicks = GetTickCount ();
      if ((dfTicks - dfTicksS) == 0)
      {
         dfSpeed = fabs (dfDistance - dfDistanceS) * 1000.0;
      }
      else
      {
         dfSpeed = fabs (dfDistance - dfDistanceS) * 1000.0 / (dfTicks - dfTicksS);
      }
      dfTicks = dfTicks;
      dfDistanceS = dfDistance;

      // ���ٶȱȽϵ�ʱ��������һ����ʱ�����Ϊת�޻����裬����ʼ��������
      // ��ɲ���������
      if ((dfSpeed < 0.5) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->Standard.fStroke))
      {
         // ���û��ƽ��ֵ���������ֵ����֤�в�������
         if (dfForceCount == 0.0)
         {
            dfForceCount += FAI_FindMaxForce();
            dfIa += g_DAQData.Data.dfIa;
            dfIb += g_DAQData.Data.dfIb;
            dfIc += g_DAQData.Data.dfIc;
            dwCount ++;
            // ������ʾֵ
            pData->ptMeasureDataB.ptLoad3Data.dfForce = dfForceCount / dwCount;
            pData->ptMeasureDataB.ptLoad3Data.dfIa = dfIa / dwCount;
            pData->ptMeasureDataB.ptLoad3Data.dfIb = dfIb / dwCount;
            pData->ptMeasureDataB.ptLoad3Data.dfIc = dfIc / dwCount;
         }
         DAQ_Delay(1000);
         // �����������
         DAQ_SetOutForce( 1.0 );
         DAQ_SetInForce( 1.0 );
         DAQ_SetTotalValve( 0 );
         DAQ_SetOutValve( 0 );
         DAQ_SetInValve( 0 );
         usSkiped = 1;
      }

      // ���ض��Ķ��̷�Χ�ڼ��������ƽ��ֵ����Ϊ�޷�����ʱ�Ĳ������
      dfDistance = DAQ_ReadStroke ();
      if ((fabs (dfDistance - dfStroke) > dfHalfStroke) && ((fabs (dfDistance - dfStroke) + 20) < pDevice->Standard.fStroke))
      {
         // �ۼӲ���ֵ
         dwCount ++;
         dfForceCount += DAQ_ReadForce ();
         dfIa += g_DAQData.Data.dfIa;
         dfIb += g_DAQData.Data.dfIb;
         dfIc += g_DAQData.Data.dfIc;
         
         // ������ʾֵ
         pData->ptMeasureDataB.ptLoad3Data.dfForce = dfForceCount / dwCount;
         pData->ptMeasureDataB.ptLoad3Data.dfIa = dfIa / dwCount;
         pData->ptMeasureDataB.ptLoad3Data.dfIb = dfIb / dwCount;
         pData->ptMeasureDataB.ptLoad3Data.dfIc = dfIc / dwCount;
      }

      // ����������͵���Ŀ����
      dfDiff = DAQ_ReadForce () - dfRatedForce;
      // �ֵ����ڱ���������
      if (fabs (dfDiff) < 0.08)
         dfDelta = 0.005;
      else if (fabs (dfDiff) < 0.1)
         dfDelta = 0.01;
      else if (fabs (dfDiff) < 0.15)
         dfDelta = 0.02;
      else if (fabs (dfDiff) < 0.2)
         dfDelta = 0.025;
      else if (fabs (dfDiff) < 0.3)
         dfDelta = 0.03;
      else if (fabs (dfDiff) < 0.4) 
         dfDelta = 0.04;
      else
         dfDelta = 0.04;
      
      // �������������
      if (dfDiff > 0.0)
         g_DAQSystemData.fAOAForce -= dfDelta;
      else
         g_DAQSystemData.fAOAForce += dfDelta;
      
      // ��ֹ���������Ƶ��ڷ�Χ
      if (g_DAQSystemData.fAOAForce - dfAOForce > 1.6 )
         g_DAQSystemData.fAOAForce = dfAOForce + 1.6;
      if (g_DAQSystemData.fAOAForce - dfAOForce < -1.6 )
         g_DAQSystemData.fAOAForce = dfAOForce - 1.6;
      
      // ���ڱ���������
      DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   }
   
   // ���㶯��ʱ��
   dfActionTime = GetTickCount () - dwTicksA;
   if (dwCount == 0)
      dwCount = 1;
   dfForceCount /= dwCount;
   dfIa /= dwCount;
   dfIb /= dwCount;
   dfIc /= dwCount;
      
   // ��������ֵ
   if ((g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState == 2) && (usSkiped != 1))
   {
   // ��������������ܴ��������
      if (dfForceCount > g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce)
         dfForceCount = g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce;
      
   // ������������Load1���ͬʱLoad1������С��Load1���ʱ
      if ((g_S700KData.ptMeasureDataB.ptLoad2Data.dfForce > g_Device.Standard.fLoad3_OperateForce)
         && (dfForceCount < g_Device.Standard.fLoad3_OperateForce))
      {
      // �����ֵС��0.1KNʱ����Ϊ����ֵ
         if ((g_Device.Standard.fLoad3_OperateForce - dfForceCount) <= 0.1)
            dfForceCount = g_Device.Standard.fLoad3_OperateForce + Random(0.0, 0.05);
      }
   }

   // ���ò������
   pData->ptMeasureDataB.ptLoad3Data.dfIa = dfIa;
   pData->ptMeasureDataB.ptLoad3Data.dfIb = dfIb;
   pData->ptMeasureDataB.ptLoad3Data.dfIc = dfIc;
   pData->ptMeasureDataB.ptLoad3Data.dfForce = dfForceCount;
//   pData->ptMeasureDataB.ptLoad3Data.dfActionTime = (dfActionTime-500)/ 1000.0;
   
   // ��λ����
   DAQ_SetTotalValve (0);
   DAQ_SetInForce (1.0);
   DAQ_SetOutForce (1.0);
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);
   DAQ_InControl (0);
   DAQ_OutControl (0);

   // ��ʾ����ֵ
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_3_2, pData->ptMeasureDataB.ptLoad3Data.dfForce);
//   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_T_3_2, pData->ptMeasureDataB.ptLoad3Data.dfActionTime);
   return dwRetCode;
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
int __stdcall ZDJ9_MeasureLoad3( LPT_Device pDevice, LPT_Record pData )
{
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_DAQSystemData.usTerminate)
      return -1;

   // ��ʱ
   DAQ_Delay (1000);
   DAQ_Delay (1000);
   
   // ����ģ�����
   DAQ_SimulateTrack (1);
   
   // ���ò���
   g_S700KData.Control.usStep = 7;
   // B�����
   if (ZDJ9_MeasureLoad3_B (pDevice, pData) == -1)
      return -1;
   
   // ��ʱ
   DAQ_Delay (1000);
   DAQ_Delay (1000);

   // ���ò���
   g_S700KData.Control.usStep = 8;
   // A�����
   if (ZDJ9_MeasureLoad3_A (pDevice, pData) == -1)
      return -1;

   // �Ͽ�ģ�����
   DAQ_SimulateTrack( 0 );
   
   return 0;
}

//------------------------------------------------------------------------------------------------
