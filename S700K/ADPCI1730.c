// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************
#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>
#include "S700K.h"
#include "ADPCI1730.h"

//------------------------------------------------------------------------------------------------
// �л����ݲɼ���PCI1730�����������
// ����:
//    pDev        �豸ָ��
//    ushChannel  ͨ�����
//    ushState    ���״̬
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADCards_DOBit( LPT_DAQCard pDev, USHORT ushChannel, USHORT ushState )
{
   LRESULT     ErrCde;         // Return error code
   PT_DioWriteBit  ptDioWriteBit;

   // ����豸û�д򿪣�����
   if ( pDev->hDevice == NULL )
   {
      return FALSE;
   }
   // �������ݽṹ
   ptDioWriteBit.port  = ushChannel / 8;
   ptDioWriteBit.bit   = ushChannel % 8;
   ptDioWriteBit.state = ushState;
   
   // ������������
   ErrCde = DRV_DioWriteBit( (LONG)pDev->hDevice, &ptDioWriteBit );
   // ������ɹ����ش���
   if ( ErrCde != 0)
   {
      return FALSE;
   }
   // ��ȷ����
   return TRUE;
}

//------------------------------------------------------------------------------------------------
// �л����ݲɼ���PCI1730�����������
// ����:
//    pDev        �豸ָ��
//    ushPort     �˿ڱ��
//    ushState    ���״̬
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADCards_DOWord( LPT_DAQCard pDev, USHORT ushPort, USHORT ushState )
{
   LRESULT     ErrCde;         // Return error code
   PT_DioWritePortWord  ptDioWritePortWord;

   // ����豸û�д򿪣�����
   if ( pDev->hDevice == NULL )
   {
      return FALSE;
   }
   // �������ݽṹ
   ptDioWritePortWord.port  = ushPort;
   ptDioWritePortWord.mask  = 0xffff;
   ptDioWritePortWord.state = ushState;
   
   // ������������
   ErrCde = DRV_DioWritePortWord( (LONG)pDev->hDevice, &ptDioWritePortWord );
   // ������ɹ����ش���
   if ( ErrCde != 0 )
   {
      return FALSE;
   }
   // ��ȷ����
   return TRUE;
}
//------------------------------------------------------------------------------------------------
// �л����ݲɼ���PCI1730������������
// ����:
//    pDev        �豸ָ��
//    ushChannel  ͨ�����
// ���:
//    pusState    ����ͨ��״̬
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADCards_DIBit(LPT_DAQCard pDev, USHORT ushChannel, USHORT* pusState)
{
   LRESULT     ErrCde;         // Return error code
   PT_DioReadBit  ptDioReadBit;

   // ����豸û�д򿪣�����
   if ( pDev->hDevice == NULL )
   {
      return FALSE;
   }
   // �������ݽṹ
   ptDioReadBit.port  = ushChannel / 8;
   ptDioReadBit.bit   = ushChannel % 8;
   ptDioReadBit.state = pusState;
   
   // ������������
   ErrCde = DRV_DioReadBit ((LONG)pDev->hDevice, &ptDioReadBit );

   // ������ɹ����ش���
   if (ErrCde != 0)
   {
      return FALSE;
   }
   // ��ȷ����
   return TRUE;
}
//------------------------------------------------------------------------------------------------
