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
// ���л����ݲɼ���PCI1711
// ����:
//    pDev        �豸ָ��
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADCards_Open(LPT_DAQCard pDev)
{
	LRESULT     ErrCde;         // Return error code
	char		lpszErrMsg[256];// ���صĴ�������

	// ����豸�Ѿ����򿪣�����
	if ( pDev->hDevice != 0 )
		return TRUE;

	// �����������򣬴��豸
#if 0
	ErrCde = DRV_DeviceOpen( pDev->dwIndex, ( LONG far* )&pDev->hDevice );
#else
	ErrCde = DRV_DeviceOpen( pDev->dwIndex, ( LONG far* )&pDev->hDevice );
	if (ErrCde != SUCCESS)
	{
		DRV_GetErrorMessage(ErrCde,lpszErrMsg);
		ERR1("�����ݲɼ���PCI1713ʧ��.���������򷵻صĹ�������:%s",lpszErrMsg);
		MessageBox(NULL,lpszErrMsg,"����",MB_OK);
		return FALSE;
	}
#endif
	// ������ɹ����ش���
	if ( ErrCde != SUCCESS )
	{
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
BOOL __stdcall ADCards_Close( LPT_DAQCard pDev )
{
	LRESULT     ErrCde;         // Return error code

	// ����豸�Ѿ����رգ�����
	if ( pDev->hDevice == NULL )
		return TRUE;

	// �����������򣬹ر��豸
	ErrCde = DRV_DeviceClose( ( LONG far* )&pDev->hDevice );
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
// �����л����ݲɼ���PCI1711������ͨ��
// ����:
//    pDev        �豸ָ��
//    ushChannel  ͨ�����
//    ushGainCode �������
// ���:
//    ��
// ����:
//    TRUE        �ɹ�
//    FALSE       ʧ��
//------------------------------------------------------------------------------------------------
BOOL __stdcall ADCards_AIConfig( LPT_DAQCard pDev, USHORT ushChannel, USHORT ushGainCode )
{
	LRESULT     ErrCde;         // Return error code
	PT_AIConfig ptAIConfig;     // structure for AIConfig table

	// ����豸û�д򿪣�����
	if ( pDev->hDevice == NULL )
	{
		return FALSE;
	}

	// ��ָ����ͨ����������
	ptAIConfig.DasGain = ushGainCode;
	ptAIConfig.DasChan = ushChannel;

	// ������������
	ErrCde = DRV_AIConfig( (LONG)pDev->hDevice, &ptAIConfig );
	// ������ɹ����ش���
	if ( ErrCde != 0 )
	{
		return FALSE;
	}
	// ��ȷ����
	return TRUE;
}

//------------------------------------------------------------------------------------------------
