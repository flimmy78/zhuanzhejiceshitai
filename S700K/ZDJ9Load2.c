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
extern PT_Record    g_S700KData;
extern PT_DAQData       g_DAQData;
extern PT_DAQSystemData g_DAQSystemData;
extern PT_Device        g_Device;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// ת�޻�Load2���������ת�޻��ڹ涨��ʱ���ڲ�����ɶ����ͷ��ش���
// ����:
//    pDevice     �������ת�޻�����
//    pData       ����ת�޻���������
// ���:
//    ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
DWORD __stdcall ZDJ9_MeasureLoad2_A( LPT_Device pDevice, LPT_Record pData)
{
   double   dfDistance, dfDistanceS, dfDistanceE;
   double   dfStrokeS;
   DWORD    dwTicksS, dwTicksE;
   double   dfSpeed;
   double   dfTicks;
   double   dfForce = 0.0;
   double   dfIa = 0.0, dfIb = 0.0, dfIc = 0.0;
   DWORD    dwTicksError;
   DWORD    dwRetCode = 0;
   BOOL     bStart = FALSE;
   DWORD    dwTimeout = 7000;
   BOOL     bOk = 0;
   double   dfStroke;
   int      dwCount = 0;
   double   dfDelta;
   double   dfDiff;
   double   dfForceCount= 0.0;
   double   dfAOForce;
   DWORD    dwTickStop = 0;
   double   dfMaxForce = 0.0;
   double   dfRatedForce = 0.0;
   double   dfHalfStroke;
   
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // ����ֻ�ڶ��̹������в������ݴ���
   dfHalfStroke = g_Device.Standard.fStroke / 2;
   dfHalfStroke += 10.0;
   
   g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState = 0;
   
   // ����Load2��������Ϊ�������1.8��
   dfRatedForce = g_Device.Standard.fLoad2_MaxForce;
//   dfRatedForce *= 1.8;
   
   if (pDevice->Standard.fLoad2_A2B_AVoltage > 10.0)
      return -1;

   // ȡ�û��򷧳�ʼ����ֵ
   g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad2_A2B_AVoltage;
   g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad2_A2B_BVoltage;
   
   g_DAQSystemData.fAOAForce = 1.0;
   dfAOForce = g_DAQSystemData.fAOBForce;
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);

   // �����򷧿�������Ϊ��ʼ���ȵ�70%����ֹ�����ܼӵ�λ
   g_DAQSystemData.fAOBForce = dfAOForce * 0.7;
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   
   // �򿪻��򷧣�ת�޻�����
   DAQ_SetOutValve (1);
   DAQ_SetInValve (0);
   DAQ_SetTotalValve (0);
   
   DAQ_Delay (500);
   DAQ_OutControl (1);
   
   // ��λλ��
   DAQ_ResetStroke ();
   // ��ȡλ�Ƴ�ʼֵ
   dfStrokeS = dfStroke = dfDistanceS = DAQ_ReadStroke ();
   
   // ��ʼʱ��
   dwTicksError = GetTickCount ();
   dwTicksS = GetTickCount ();
   // ��λ�����
   g_DAQSystemData.fMaxForce = 0.0;
   dwTimeout = 10000;
   while( 1)
   {
      // �����λ������
      if (DAQ_ReadRight ())
         break;
      // ��ʱ
      DAQ_Delay (50);
      // �ɼ�����
      DAQ_CheckMeasure();
      
      // �����ʱ�����ش���
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
//         ZDJ9_UnloadHandle (pDevice, pData);
         break;
      }
      
      // �ȴ�λ�ƴ���10mmʱ�����򷧿��ȵ��ڵ�Ԥ�����ȣ�Ȼ��ʼ��������Load2�����
      if ((fabs (DAQ_ReadStroke () - dfDistanceS) < 10) && (bStart == FALSE))
         continue;
      else if (bStart == FALSE)
      {
         g_DAQSystemData.fAOBForce = dfAOForce * 1.0;
         DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
         bStart = TRUE;
         dfDistanceS = DAQ_ReadStroke ();
         dwTicksS = GetTickCount ();
         dwTicksError = GetTickCount ();
         dwTimeout = 7000;
         if (g_Device.Standard.fLoad1_TravelTime > 0)
            dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;
      }
      
      // ��ָ����λ�Ʒ�Χ���ۼƲ�����������Ϊ�޷�����ʱ�Ĳ���ֵ
      dfDistanceE = DAQ_ReadStroke ();
      if ((fabs (dfDistanceE - dfStroke) > dfHalfStroke) && ((fabs (dfDistanceE - dfStroke) + 5) < pDevice->Standard.fStroke))
      {
         // �ۼӲ���ֵ
         dwCount ++;
         dfForceCount += DAQ_ReadForce ();
         dfIa += g_DAQData.Data.dfIa;
         dfIb += g_DAQData.Data.dfIb;
         dfIc += g_DAQData.Data.dfIc;
         // ������ʾֵ
         pData->ptMeasureDataA.ptLoad2Data.dfIa = dfIa / dwCount;
         pData->ptMeasureDataA.ptLoad2Data.dfIb = dfIb / dwCount;
         pData->ptMeasureDataA.ptLoad2Data.dfIc = dfIc / dwCount;
      }
      // λ��ĩ�˲�����
      if (g_Device.Standard.fStroke - fabs(dfDistanceE - dfStroke) < 10)
      {
         continue;
      }
   }
   // ����λ����ֵֹ
   dfDistanceE = DAQ_ReadStroke ();
   // ���㶯��
   dfDistance = fabs (dfDistanceE - dfStrokeS);
   
   // �������ֵ������ʾ
   pData->ptMeasureDataA.ptCheckData.dfInterval = dfDistance;
   pData->ptMeasureDataA.ptCheckData.bCheckState = TRUE;
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_DISB_A, dfDistance);
   
   // ��ֹ�������
   if (dwCount == 0)
      dwCount = 1;
   // �������
   if (bOk == 1)
   {
      // ����״̬
      g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState = 2;
      // ��������ֵ
      dfForce *= g_Device.Standard.fLoad2_Scale;
      
      if (dfForce > g_Device.Standard.fLoad2_MaxForce)
      {
         if ((dfForce - g_Device.Standard.fLoad2_MaxForce) < 0.1)
            dfForce = g_Device.Standard.fLoad2_MaxForce;
      }
      if (dfForce < g_Device.Standard.fLoad1_OperateForce)
      {
         if ((g_Device.Standard.fLoad1_OperateForce - dfForce) < 0.1)
            dfForce = g_Device.Standard.fLoad1_OperateForce;
      }
      
      // ����B��������A����
      dfForce += (pData->ptMeasureDataB.ptLoad2Data.dfForce - dfForce) / 2;
      
      if (dfForce > g_Device.Standard.fLoad2_MaxForce)
      {
         if ((dfForce - g_Device.Standard.fLoad2_MaxForce) < 0.1)
            dfForce = g_Device.Standard.fLoad2_MaxForce;
      }
      if (dfForce < g_Device.Standard.fLoad1_OperateForce)
      {
         if ((g_Device.Standard.fLoad1_OperateForce - dfForce) < 0.1)
            dfForce = g_Device.Standard.fLoad1_OperateForce + 0.05;
      }
   }
   // ������
   else
   {
      dfForce = dfForceCount / dwCount;
      g_S700KData.ptMeasureDataA.ptLoad2Data.usCheckState = 0;
   }
   
   // ���ò������
   pData->ptMeasureDataA.ptLoad2Data.dfForce1 = dfForce;
   pData->ptMeasureDataA.ptLoad2Data.dfForce = pData->ptMeasureDataA.ptLoad2Data.dfForce1;
   
   // ��λ���ƣ�ת�޻��ߵ�λ
   DAQ_SetOutValve (0);
   DAQ_SetInValve (0);
   DAQ_SetOutForce (0.0);
   DAQ_SetTotalValve (1);
   // ��λ����
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_SetTotalValve (0);
   
   // ��ʾ����ֵ
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_2_1, pData->ptMeasureDataA.ptLoad2Data.dfForce);
   return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// ת�޻�Load2���������ת�޻��ڹ涨��ʱ���ڲ�����ɶ����ͷ��ش���
// ����:
//    pDevice     �������ת�޻�����
//    pData       ����ת�޻���������
// ���:
//    ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
DWORD __stdcall ZDJ9_MeasureLoad2_B(LPT_Device pDevice, LPT_Record pData)
{
   double   dfStrokeS, dfDistance, dfDistanceS, dfDistanceE;
   DWORD    dwTicksS, dwTicksE;
   double   dfSpeed;
   double   dfTicks;
   double   dfForce = 0.0;
   double   dfIa = 0.0, dfIb = 0.0, dfIc = 0.0;
   DWORD    dwTicksError;
   DWORD    dwRetCode = 0;
   BOOL     bStart = FALSE;
   DWORD    dwTimeout = 7000;
   BOOL     bOk = 0;
   double   dfStroke;
   int      dwCount = 0;
   double   dfDelta;
   double   dfDiff;
   double   dfForceCount= 0.0;
   double   dfAOForce;
   DWORD    dwTickStop = 0;
   double   dfMaxForce = 0.0;
   double   dfRatedForce = 0.0;
   double   dfHalfStroke;
   
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_DAQSystemData.usTerminate)
      return -1;
   
   // ����ֻ�ڶ��̹������в������ݴ���
   dfHalfStroke = g_Device.Standard.fStroke / 2;
   dfHalfStroke += 10.0;
   
   g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState = 0;
   
   // ����Load2��������Ϊ�������1.5��
   dfRatedForce = g_Device.Standard.fLoad2_MaxForce;
   
   if (pDevice->Standard.fLoad2_B2A_AVoltage > 10.0)
      return -1;  

   // ȡ�û��򷧳�ʼ����ֵ
   g_DAQSystemData.fAOAForce = pDevice->Standard.fLoad2_B2A_AVoltage;
   g_DAQSystemData.fAOBForce = pDevice->Standard.fLoad2_B2A_BVoltage;
   
   dfAOForce = g_DAQSystemData.fAOAForce;
   g_DAQSystemData.fAOBForce = 1.0;
   
   // �����򷧿�������Ϊ��ʼ���ȵ�70%����ֹ�����ܼӵ�λ
   g_DAQSystemData.fAOAForce = dfAOForce * 0.7;
   DAQ_SetInForce (g_DAQSystemData.fAOAForce);
   DAQ_SetOutForce (g_DAQSystemData.fAOBForce);
   
   // �򿪻���
   DAQ_SetOutValve (0);
   DAQ_SetInValve (1);
   DAQ_SetTotalValve (0);
   
   DAQ_Delay (500);
   
   // �򿪻��򷧣�ת�޻�����
   DAQ_InControl (1);
   
   // ��λλ��
   DAQ_ResetStroke ();
   // ��ȡλ�Ƴ�ʼֵ
   dfStrokeS = dfStroke = dfDistanceS = DAQ_ReadStroke ();
   
   // ��ʼʱ��
   dwTicksError = GetTickCount ();
   dwTicksS = GetTickCount ();
   // ��λ�����
   g_DAQSystemData.fMaxForce = 0.0;
   dwTimeout = 10000;
   while (1)
   {
      // �����λ������
      if (DAQ_ReadLeft ())
         break;
      // ��ʱ
      DAQ_Delay (50);
      // �ɼ�����
      DAQ_CheckMeasure ();
      
      // �����ʱ�����ش���
      if (DAQ_CheckError (GetTickCount () - dwTicksError, dwTimeout))
      {
         ZDJ9_UnloadHandle (pDevice, pData);
         break;
      }
      
      // �ȴ�λ�ƴ���10mmʱ�����򷧿��ȵ��ڵ�Ԥ�����ȣ�Ȼ��ʼ��������Load2�����
      if ((fabs (DAQ_ReadStroke () - dfDistanceS) < 10) && (bStart == FALSE))
         continue;
      else if ((bStart == FALSE))
      {
         g_DAQSystemData.fAOAForce = dfAOForce * 1.0;
         DAQ_SetInForce (g_DAQSystemData.fAOAForce);
         bStart = TRUE;
         dfDistanceS = DAQ_ReadStroke ();
         dwTicksS = GetTickCount ();
         dwTicksError = GetTickCount ();
         dwTimeout = 7000;
         if (g_Device.Standard.fLoad1_TravelTime > 0)
            dwTimeout = g_Device.Standard.fLoad3_TravelTime * 1000 + 1000;
      }
      if (bStart == FALSE)
         continue;
      
      // ��ָ����λ�Ʒ�Χ���ۼƲ�����������Ϊ�޷�����ʱ�Ĳ���ֵ
      dfDistanceE = DAQ_ReadStroke ();
      if ((fabs (dfDistanceE - dfStroke) > dfHalfStroke) && ((fabs (dfDistanceE - dfStroke) + 5) < pDevice->Standard.fStroke))
      {
         // �ۼӲ���ֵ
         dwCount ++;
         dfForceCount += DAQ_ReadForce ();
         dfIa += g_DAQData.Data.dfIa;
         dfIb += g_DAQData.Data.dfIb;
         dfIc += g_DAQData.Data.dfIc;
         // ������ʾֵ
         pData->ptMeasureDataB.ptLoad2Data.dfIa = dfIa / dwCount;
         pData->ptMeasureDataB.ptLoad2Data.dfIb = dfIb / dwCount;
         pData->ptMeasureDataB.ptLoad2Data.dfIc = dfIc / dwCount;
      }
      
      // λ��ĩ�˲�����
      if (g_Device.Standard.fStroke - fabs(dfDistanceE - dfStroke) < 10)
      {
         continue;
      }
      
   }
   // ����λ����ֵֹ
   dfDistanceE = DAQ_ReadStroke ();
   // ���㶯��
   dfDistance = fabs( dfDistanceE - dfStrokeS);
   
   // �������ֵ������ʾ
   pData->ptMeasureDataB.ptCheckData.dfInterval = dfDistance;
   pData->ptMeasureDataB.ptCheckData.bCheckState = TRUE;
   SetCtrlVal( g_plDAQMain, DAQMAIN_NG_DISB_B, dfDistance);
   
   // ��ֹ�������
   if (dwCount == 0)
      dwCount = 1;
   // �������
   if (bOk == 1)
   {
      // ����״̬
      g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState = 2;
      // ��������ֵ
      dfForce *= g_Device.Standard.fLoad2_Scale;
      
      if (dfForce > g_Device.Standard.fLoad2_MaxForce)
      {
         if ((dfForce - g_Device.Standard.fLoad2_MaxForce) < 0.15)
            dfForce = g_Device.Standard.fLoad2_MaxForce;
      }
      if (dfForce < g_Device.Standard.fLoad1_OperateForce)
      {
         if ((g_Device.Standard.fLoad1_OperateForce - dfForce) < 0.15)
            dfForce = g_Device.Standard.fLoad1_OperateForce + 0.05;
         }
   }
   // ������
   else
   {
      dfForce = dfForceCount / dwCount;
      g_S700KData.ptMeasureDataB.ptLoad2Data.usCheckState = 0;
   }
   
   // ���ò������
   pData->ptMeasureDataB.ptLoad2Data.dfForce1 = dfForce;
   pData->ptMeasureDataB.ptLoad2Data.dfForce = pData->ptMeasureDataB.ptLoad2Data.dfForce1;

   // ��λ���ƣ�ת�޻��ߵ�λ
   DAQ_SetInForce (1.0);
   DAQ_SetOutForce (1.0);
   DAQ_SetTotalValve (0);
   DAQ_SetInValve (0);
   DAQ_SetOutValve (0);
   // ��λ����
   DAQ_InControl (0);
   DAQ_OutControl (0);
   DAQ_SetTotalValve (0);
   return dwRetCode;
}

//------------------------------------------------------------------------------------------------
// ת�޻�Load2���������ת�޻��ڹ涨��ʱ���ڲ�����ɶ����ͷ��ش���
// ����:
//    pDevice     �������ת�޻�����
//    pData       ����ת�޻���������
// ���:
//    ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
int __stdcall ZDJ9_MeasureLoad2( LPT_Device pDevice, LPT_Record pData)
{
   double fData;
   
   // ���Ҫ��ֹͣ���ԣ�����
   if (g_DAQSystemData.usTerminate)
      return -1;

   // ��ʱ
   DAQ_Delay (1000);
   DAQ_Delay (1000);
   
   DAQ_SimulateTrack (0);
   
   // ���ò���
   g_S700KData.Control.usStep = 3;
   // B�����
   if (ZDJ9_MeasureLoad2_B (pDevice, pData) == -1)
      return -1;
   
   // ��ʱ
   DAQ_Delay (1000);
   DAQ_Delay (1000);
   
   // ���ò���
   g_S700KData.Control.usStep = 4;
   // A�����
   if (ZDJ9_MeasureLoad2_A (pDevice, pData) == -1)
      return -1;
   
   // ����������ʾ
#define __AVERAGE__   
   if ((pData->ptMeasureDataA.ptLoad2Data.usCheckState == 2) && (pData->ptMeasureDataB.ptLoad2Data.usCheckState == 2))
   {
#ifdef __AVERAGE__
      pData->ptMeasureDataA.ptLoad2Data.dfForce = pData->ptMeasureDataA.ptLoad2Data.dfForce1;
      pData->ptMeasureDataB.ptLoad2Data.dfForce = pData->ptMeasureDataB.ptLoad2Data.dfForce1;
#elif
      fData = pData->ptMeasureDataA.ptLoad2Data.dfForce1 + pData->ptMeasureDataB.ptLoad2Data.dfForce1;
      fData /= 2.0;
      
      if ((fData > (pDevice->Standard.fLoad2_MaxForce-0.1)) && (fData < (pDevice->Standard.fLoad2_MaxForce *1.04)))
      {
         fData = pDevice->Standard.fLoad2_MaxForce - 0.1;
         pData->ptMeasureDataA.ptLoad2Data.dfForce = fData + 0.1 * rand() / 32768.0;
         pData->ptMeasureDataB.ptLoad2Data.dfForce = fData + 0.1 * rand() / 32768.0;
      }
      else
      {
         pData->ptMeasureDataA.ptLoad2Data.dfForce = fData + 0.05 * rand() / 32768.0;
         pData->ptMeasureDataB.ptLoad2Data.dfForce = fData + 0.05 * rand() / 32768.0;
      }
#endif
   }
   
   // ��ʾ����ֵ
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_2_1, pData->ptMeasureDataA.ptLoad2Data.dfForce);
   SetCtrlVal (g_plDAQMain, DAQMAIN_NG_F_2_2, pData->ptMeasureDataB.ptLoad2Data.dfForce);
   return 0;
}
 
//------------------------------------------------------------------------------------------------
