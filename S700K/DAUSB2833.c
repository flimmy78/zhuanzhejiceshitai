// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************
#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>
#include "S700K.h"
//#include "..\include\USB2833.h"
//#include "DAUSB2833.h"

//------------------------------------------------------------------------------------------------
// ���л����ݲɼ���PCI1711
// ����:
//    pDev        �豸ָ��
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall USB2833_Open(LPT_DAQCard pDev)
{
   LRESULT     ErrCde;         // Return error code
   
   // ����豸�Ѿ����򿪣�����
   if ( pDev->hDevice != 0 )
      return TRUE;
   
   // �����������򣬴��豸
   pDev->hDevice = (LONG)USB2833_CreateDevice (0);
   
   // ������ɹ����ش���
   if ( pDev->hDevice == 0 )
   {
      MessagePopup ("����", "�������ӵ�USB2833!");
      return FALSE;
   }
   
   // ��ȷ����
   return TRUE;
   
}

//------------------------------------------------------------------------------------------------
// �ر��л����ݲɼ���PCI1711  
// ����:
//    pDev        �豸ָ��
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall USB2833_Close( LPT_DAQCard pDev )
{
   LRESULT     ErrCde;         // Return error code
   
   // ����豸�Ѿ����رգ�����
   if ( pDev->hDevice == NULL )
      return TRUE;
   
   // �����������򣬹ر��豸
   USB2833_ReleaseDevice ((HANDLE)pDev->hDevice); // �ͷ��豸����
   
   // ��λ����ָ��
   pDev->hDevice = (LONG)NULL;
   
   // ��ȷ����
   return TRUE;
}

//------------------------------------------------------------------------------------------------
// �л����ݲɼ���PCI1711��ģ�������
// ����:
//    pDev        �豸ָ��
//    ushChannel  ͨ�����
//    fVoltage    �����ѹֵ
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall USB2833_AOValue( LPT_DAQCard pDev, USHORT ushChannel, float fVoltage )
{
   BOOL     ErrCde;         // Return error code
   USHORT     usRaw;
   
   // ����豸û�д򿪣�����
   if ( pDev->hDevice == NULL )
   {
      return FALSE;
   }
   
   usRaw = (WORD)(fVoltage/(10000.00/4096));
   
   ErrCde = USB2833_WriteDeviceDA((HANDLE)pDev->hDevice, USB2833_OUTPUT_0_P10000mV, usRaw, ushChannel);
   if (!ErrCde)
   {
      return FALSE;
   }
   
   // ��ȷ����
   return TRUE;
}

//------------------------------------------------------------------------------------------------
