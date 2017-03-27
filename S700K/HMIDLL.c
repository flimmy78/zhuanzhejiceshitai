// #########################################################################
// *************************************************************************

#include <cvirte.h>     
#include "Global.h"
#include <userint.h>
#include "S700K.h"
#include "inifile.h"

//------------------------------------------------------------------------------------------------
// ����ȫ�ֱ���
//------------------------------------------------------------------------------------------------
extern PT_Device  g_Device;

//------------------------------------------------------------------------------------------------
// ����ת�޻��ͺ�ѡ����
// ����:
//    pDevice     �豸ָ��
//    nLanguage   ��������
// ���:
//    pDevice     �豸ָ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
int __stdcall TBDeviceSelect( LPT_Device pDevice, int nLanguage )
{
   // ���庯��ָ��
   typedef int (__stdcall *TBDeviceSelect)(LPT_Device pDevice, int nLanguage);
   TBDeviceSelect pProc;
//   int ( __stdcall *pProc)(LPT_Device pDevice, int nLanguage);
   HMODULE hLibrary;
   
   // ���붯̬��
   hLibrary = LoadLibrary ("S700KDLL.dll");

   // ������ɹ������ش���
   if ( hLibrary == NULL )
      return -1;

   // ��λ������ַ
   pProc = (TBDeviceSelect)GetProcAddress (hLibrary, "TBDeviceSelect");
   // ���
   if ( pProc == NULL )
      return -1;

   // ���ú���
   (*pProc)(&g_Device, nLanguage);

   // �ͷŶ�̬��
   FreeLibrary (hLibrary);

   return 0;
}

//------------------------------------------------------------------------------------------------
// ����ת�޻�TypeNumberѡ����
// ����:
//    pData       �ַ���ָ��
//    nLanguage   ��������
// ���:
//    pData       �ַ���ָ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
int __stdcall TBTypeNumber( char* pData, int nLanguage )
{
   // ���庯��ָ��
   typedef int (__stdcall *TBTypeNumber)(char* pData, int nLanguage);
   TBTypeNumber pProc;
//   int ( __stdcall *pProc)( char* pData, int nLanguage );
   HMODULE hLibrary;
   // ���붯̬��
   hLibrary = LoadLibrary ("S700KDLL.dll");

   // ������ɹ������ش���
   if ( hLibrary == NULL )
      return -1;

   // ��λ������ַ
   pProc = (TBTypeNumber)GetProcAddress (hLibrary, "TBTypeNumber");
   if ( pProc == NULL )
      return -1;

   // ���ú���
   (*pProc)(pData, nLanguage);

   // �ͷŶ�̬��
   FreeLibrary (hLibrary);

   return 0;
}
//------------------------------------------------------------------------------------------------
// ����ת�޻����Խ��ѡ����
// ����:
//    pData       �ַ���ָ��
//    nLanguage   ��������
// ���:
//    pData       �ַ���ָ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
int __stdcall TBTestResult( char* pData, int nLanguage )
{
   // ���庯��ָ��
   typedef int (__stdcall *TBTestResult)(char* pData, int nLanguage);
   TBTestResult pProc;
//   int ( __stdcall *pProc)( char* pData, int nLanguage );
   HMODULE hLibrary;
   // ���붯̬��
   hLibrary = LoadLibrary ("S700KDLL.dll");

   // ������ɹ������ش���
   if ( hLibrary == NULL )
      return -1;

   // ��λ������ַ
   pProc = (TBTestResult)GetProcAddress (hLibrary, "TBTestResult");
   if ( pProc == NULL )
      return -1;

   // ���ú���
   (*pProc)(pData, nLanguage);

   // �ͷŶ�̬��
   FreeLibrary (hLibrary);

   return 0;
}
//------------------------------------------------------------------------------------------------
// ����ת�޻�������ѡ����
// ����:
//    pData       �ַ���ָ��
//    nLanguage   ��������
// ���:
//    pData       �ַ���ָ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
int __stdcall TBTesterName( char* pData, int nLanguage )
{
   // ���庯��ָ��
   typedef int (__stdcall *TBTesterName)(char* pData, int nLanguage);
   TBTesterName pProc;
//   int ( __stdcall *pProc)( char* pData, int nLanguage );
   HMODULE hLibrary;
   // ���붯̬��
   hLibrary = LoadLibrary ("S700KDLL.dll");

   // ������ɹ������ش���
   if ( hLibrary == NULL )
      return -1;

   // ��λ������ַ
   pProc = (TBTesterName)GetProcAddress (hLibrary, "TBTesterName");
   if ( pProc == NULL )
      return -1;

   // ���ú���
   (*pProc)(pData, nLanguage);

   // �ͷŶ�̬��
   FreeLibrary (hLibrary);

   return 0;
}

//------------------------------------------------------------------------------------------------
// ����ת�޻�����ѡ����
// ����:
//    pData       �ַ���ָ��
//    nLanguage   ��������
// ���:
//    pData       �ַ���ָ��
// ����:
//    0           �ɹ�
//    <0          ʧ��
//------------------------------------------------------------------------------------------------
int __stdcall TBSerialNumber( char* pData, int nLanguage )
{
   // ���庯��ָ��
   typedef int (__stdcall *TBSerialNumber)(char* pData, int nLanguage);
   TBSerialNumber pProc;
//   int ( __stdcall *pProc)( char* pData, int nLanguage );
   HMODULE hLibrary;
   // ���붯̬��
   hLibrary = LoadLibrary ("S700KDLL.dll");

   // ������ɹ������ش���
   if ( hLibrary == NULL )
      return -1;

   // ��λ������ַ
   pProc = (TBSerialNumber)GetProcAddress (hLibrary, "TBSerialNumber");
   if ( pProc == NULL )
      return -1;

   // ���ú���
   (*pProc)(pData, nLanguage);

   // �ͷŶ�̬��
   FreeLibrary (hLibrary);

   return 0;
}
//------------------------------------------------------------------------------------------------
