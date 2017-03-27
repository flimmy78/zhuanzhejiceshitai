// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************
#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>
#include "S700K.h"
#include "ADPCI1711.h"

//------------------------------------------------------------------------------------------------
// �����л����ݲɼ���PCI1711�����ͨ��
// ����:
//    pDev        �豸ָ��
//    ushChannel  ͨ�����
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADCards_AOConfig( LPT_DAQCard pDev, USHORT ushChannel )
{
/*   
   LRESULT     ErrCde;         // Return error code
   PT_AOConfig ptAOConfig;     // structure for AIConfig table

   // ����豸û�д򿪣�����
   if ( pDev->hDevice == NULL )
   {
      return FALSE;
   }
   
   // ��ָ����ͨ����������
   ptAOConfig.chan = ushChannel;
   ptAOConfig.RefSrc = 0;
   ptAOConfig.MaxValue = 10;
   ptAOConfig.MinValue = 0;
   
   // ������������
   ErrCde = DRV_AOConfig( (LONG)pDev->hDevice, &ptAOConfig );
   // ������ɹ����ش���
   if ( ErrCde != 0 )
   {
      return FALSE;
   }
   // ��ȷ����
*/
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
BOOL __stdcall ADCards_AOValue( LPT_DAQCard pDev, USHORT ushChannel, float fVoltage )
{
   LRESULT     ErrCde;         // Return error code
   PT_AOVoltageOut ptAOVoltageOut;  // structure for AIVoltageIn table
   
   PT_AOScale ptAOScale;
   USHORT     usRaw;
   
   // ����豸û�д򿪣�����
   if ( pDev->hDevice == NULL )
   {
      return FALSE;
   }
   
   // �������ݽṹ
   ptAOVoltageOut.chan = ushChannel;
   ptAOVoltageOut.OutputValue = fVoltage;
   
   // ������������
   ErrCde = DRV_AOVoltageOut( (LONG)pDev->hDevice, &ptAOVoltageOut );
//   ErrCde = DRV_AOBinaryOut ((LONG)pDev->hDevice, &ptAOBinaryOut);
   // ������ɹ����ش���
   if ( ErrCde != 0 )
   {
      return FALSE;
   }
   
   // ��ȷ����
   return TRUE;
}

//------------------------------------------------------------------------------------------------
