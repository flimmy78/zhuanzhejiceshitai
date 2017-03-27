// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************
#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>
#include "S700K.h"
#include "..\include\driver.h"
#include "ADPCI1784.h"

//------------------------------------------------------------------------------------------------
// ���л����ݲɼ���PCI1784
// ����:
//    pDev        �豸ָ��
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADPCI1784_Open( LPT_DAQCard pDev )
{
   LRESULT     ErrCde;         // Return error code
   PT_QCounterConfig  ptQCounterConfig;
   PT_QCounterStart   ptQCounterStart;
   
   // ����豸�Ѿ����򿪣�����
   if ( pDev->hDevice != 0 )
      return TRUE;
   
   // �����������򣬴��豸
   ErrCde = DRV_DeviceOpen( pDev->dwIndex, ( LONG far* )&pDev->hDevice );
   // ������ɹ����ش���
   if ( ErrCde != SUCCESS )
   {
      return FALSE;
   }
   
   // ����λ�Ƽ���ͨ��
   ptQCounterConfig.counter       = PICH_Stroke;
   ptQCounterConfig.LatchSrc      = 0;
   ptQCounterConfig.LatchOverflow = 0;
   ptQCounterConfig.ResetOnLatch  = 0;
   ptQCounterConfig.ResetValue    = 1;   // 0x80000000

   // ����������������ͨ��
   ErrCde = DRV_QCounterConfig (( LONG )pDev->hDevice, &ptQCounterConfig );
   // ������ɹ����ش���
   if ( ErrCde != SUCCESS )
   {
      return FALSE;
   }

   // ����λ�Ƽ���ͨ��
   ptQCounterStart.counter   = PICH_Stroke;
   ptQCounterStart.InputMode = 1;
 
   // ����������������ͨ�� 
   ErrCde = DRV_QCounterStart ((LONG )pDev->hDevice, &ptQCounterStart);
   // ������ɹ����ش���
   if ( ErrCde != SUCCESS )
   {
//      return FALSE;
   }
   // ��ȷ����
   return TRUE;
}

//------------------------------------------------------------------------------------------------
// �ر��л����ݲɼ���PCI1784
// ����:
//    pDev        �豸ָ��
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADPCI1784_Close( LPT_DAQCard pDev )
{
   LRESULT     ErrCde;         // Return error code
   
   // ����豸û�д򿪣�����
   if ( pDev->hDevice == NULL )
      return TRUE;
   
   // �����������򣬸�λ����ͨ�� 
   ErrCde = DRV_CounterReset( ( LONG )pDev->hDevice, PICH_Stroke );
   // ������ɹ����ش���
   if ( ErrCde != SUCCESS )
   {
      return FALSE;
   }
   
   // �����������򣬹ر��豸 
   ErrCde = DRV_DeviceClose( ( LONG FAR* )&pDev->hDevice );
   // ������ɹ����ش���
   if ( ErrCde != SUCCESS )
   {
      return FALSE;
   }
   
   // ��λ����ָ��
   pDev->hDevice = (LONG)NULL;
   
   // ��ȷ����
   return TRUE;
}

//------------------------------------------------------------------------------------------------
// �����л����ݲɼ���PCI1784����ͨ��
// ����:
//    pDev        �豸ָ��
//    ushChannel  ͨ�����
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADPCI1784_PIConfig(LPT_DAQCard pDev, USHORT ushChannel)
{
   LRESULT     ErrCde;         // Return error code
   // ��ȷ����
   return TRUE;
}

//------------------------------------------------------------------------------------------------
// ��ȡ�л����ݲɼ���PCI1784����ͨ������ֵ
// ����:
//    pDev        �豸ָ��
//    ushChannel  ͨ�����
// ���:
//    pdfValue    λ��ֵ
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
DWORD g_PIStart = 0x80000000;
BOOL __stdcall ADPCI1784_PIValue( LPT_DAQCard pDev, double* pdfValue )
{
   LRESULT     ErrCde;         // Return error code
   USHORT      usOverflow;
   ULONG       ulLoCount;
   ULONG       ulHiCount;
   
   PT_QCounterRead    ptQCounterRead;
   
   // ׼������
   ptQCounterRead.counter = PICH_Stroke;
   ptQCounterRead.overflow = (USHORT far *)&usOverflow;
   ptQCounterRead.LoCount  = (ULONG  far *)&ulLoCount;
   ptQCounterRead.HiCount  = (ULONG  far *)&ulHiCount;
   
   // �����������򣬶�ȡ������
   ErrCde = DRV_QCounterRead( ( LONG )pDev->hDevice, &ptQCounterRead );
   // ������ɹ����ش���
   if ( ErrCde != SUCCESS )
   {
      return FALSE;
   }
   
   // ����λ��
   *pdfValue = labs( g_PIStart - ulLoCount ) * 20.0 / 1000.0;

   // ��ȷ����
   return TRUE;
}

//------------------------------------------------------------------------------------------------
// ��λ�л����ݲɼ���PCI1784����ͨ�������������ĵ�ǰֵ��Ϊ�������
// ����:
//    pDev        �豸ָ��
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADPCI1784_Reset( LPT_DAQCard pDev )
{
   LRESULT     ErrCde;         // Return error code
   USHORT      usOverflow;
   ULONG       ulLoCount;
   ULONG       ulHiCount;
   
   PT_QCounterRead    ptQCounterRead;
   
   // ׼������
   ptQCounterRead.counter = PICH_Stroke;
   ptQCounterRead.overflow = (USHORT far *)&usOverflow;
   ptQCounterRead.LoCount  = (ULONG  far *)&ulLoCount;
   ptQCounterRead.HiCount  = (ULONG  far *)&ulHiCount;
   
   // �����������򣬶�ȡ������
   ErrCde = DRV_QCounterRead( ( LONG )pDev->hDevice, &ptQCounterRead );
   // ������ɹ����ش���
   if ( ErrCde != SUCCESS )
   {
      return FALSE;
   }
   
   // �����ʼֵ
   g_PIStart = ulLoCount;

   // ��ȷ����
   return TRUE;
}

