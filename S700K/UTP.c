// #########################################################################
// *************************************************************************

#include <ansi_c.h>
#include <Winsock2.h>
#include "udp.h"
#include "..\include\global.h"
#include "Myfile.h"
#include "S700K.h"

//---------------------------------------------------------------------------
// ����ȫ�ֱ���
//------------------------------------------------------------------------------------------------
extern PT_Device        g_Device;
extern PT_SystemData    g_SystemData;
extern PT_InitStatus    g_InitStatus;
extern PT_DAQData       g_DAQData;
extern PT_ReportData    g_S700KData;
extern int              plTrend;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// ��ʼ��UDP�����׽���
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//------------------------------------------------------------------------------------------------
void InitializeWinsock( )
{
   WSADATA wsaData;
   WORD sockVersion=MAKEWORD( 2, 2 );
   
   // ʵʱ����
   g_SystemData.UDPRealtime.saSend.sin_family = AF_INET;
   g_SystemData.UDPRealtime.saSend.sin_port = htons( 20000 );                 // �����˿�
   g_SystemData.UDPRealtime.saSend.sin_addr.s_addr = inet_addr( UDPCLIENT ); // ����
   g_SystemData.UDPRealtime.saRecv.sin_family = AF_INET;
   g_SystemData.UDPRealtime.saRecv.sin_port = htons( 20001 );                 // �����˿�
   g_SystemData.UDPRealtime.saRecv.sin_addr.s_addr = inet_addr( UDPCLIENT ); // ����

   g_SystemData.UDPRealtime.saFrom.sin_family = AF_INET;
   g_SystemData.UDPRealtime.saFrom.sin_port = htons( 10000 );                // �����˿�
   g_SystemData.UDPRealtime.saFrom.sin_addr.s_addr = inet_addr( UDPSERVER ); // ����
   g_SystemData.UDPRealtime.saTo.sin_family = AF_INET;
   g_SystemData.UDPRealtime.saTo.sin_port = htons( 10001 );                   // �����˿�
   g_SystemData.UDPRealtime.saTo.sin_addr.s_addr = inet_addr( UDPSERVER );   // ����

   // ��������
   g_SystemData.UDPTrend.saSend.sin_family = AF_INET;
   g_SystemData.UDPTrend.saSend.sin_port = htons( 20010 );                    // �����˿�
   g_SystemData.UDPTrend.saSend.sin_addr.s_addr = inet_addr( UDPCLIENT );     // ����
   g_SystemData.UDPTrend.saRecv.sin_family = AF_INET;
   g_SystemData.UDPTrend.saRecv.sin_port = htons( 20011 );                    // �����˿�
   g_SystemData.UDPTrend.saRecv.sin_addr.s_addr = inet_addr( UDPCLIENT );     // ����

   g_SystemData.UDPTrend.saFrom.sin_family = AF_INET;
   g_SystemData.UDPTrend.saFrom.sin_port = htons( 10010 );                // �����˿�
   g_SystemData.UDPTrend.saFrom.sin_addr.s_addr = inet_addr( UDPSERVER ); // ����
   g_SystemData.UDPTrend.saTo.sin_family = AF_INET;
   g_SystemData.UDPTrend.saTo.sin_port = htons( 10011 );                   // �����˿�
   g_SystemData.UDPTrend.saTo.sin_addr.s_addr = inet_addr( UDPSERVER );   // ����

   if( WSAStartup( sockVersion, &wsaData ) !=0 )
   {  // Error
      return;
   }
   
   // ʵʱ���ݣ�����
   g_SystemData.UDPRealtime.socketSend = socket( AF_INET, SOCK_DGRAM, 0 );
   bind (g_SystemData.UDPRealtime.socketSend, (struct sockaddr*)&g_SystemData.UDPRealtime.saSend, sizeof (struct sockaddr_in));
   // ʵʱ���ݣ�����
   g_SystemData.UDPRealtime.socketRecv = socket( AF_INET, SOCK_DGRAM, 0 );
   bind (g_SystemData.UDPRealtime.socketRecv, (struct sockaddr*)&g_SystemData.UDPRealtime.saRecv, sizeof (struct sockaddr_in));

   // �������ݣ�����
   g_SystemData.UDPTrend.socketSend = socket( AF_INET, SOCK_DGRAM, 0 );
   bind (g_SystemData.UDPTrend.socketSend, (struct sockaddr*)&g_SystemData.UDPTrend.saSend, sizeof (struct sockaddr_in));
   // �������ݣ�����
   g_SystemData.UDPTrend.socketRecv = socket( AF_INET, SOCK_DGRAM, 0 );
   bind (g_SystemData.UDPTrend.socketRecv, (struct sockaddr*)&g_SystemData.UDPTrend.saRecv, sizeof (struct sockaddr_in));
}

//---------------------------------------------------------------------------
// �ر�UDP�����׽���
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//------------------------------------------------------------------------------------------------
void UninitializeWinsock( )
{
   // ʵʱ����
   closesocket (g_SystemData.UDPTrend.socketSend);
   closesocket (g_SystemData.UDPTrend.socketRecv);

   // ��������
   closesocket (g_SystemData.UDPTrend.socketSend);
   closesocket (g_SystemData.UDPTrend.socketRecv);

   // �������ݴ���
   WSACleanup();
}

//---------------------------------------------------------------------------
// UDP���ݴ���У���
// ����:
//    pData          ����ָ��
//    nLen           ���ݳ���
// ���:
//    ��
// ����:
//                   У���
//------------------------------------------------------------------------------------------------
short UDPCheckSum( char* pData, int nLen )
{
   // У��ͳ�ʼֵ
   short    shSum = 0x00;
   int      i;
   
   // ����ָ�벻��Ϊ��
   if ( pData == NULL )
      return shSum;
   
   // ����У���
   for ( i = 0; i < nLen; i ++ )
      shSum += pData[ i ];
   
   // ����
   shSum = shSum & 0xffff;
   
   return shSum;
}

//---------------------------------------------------------------------------
// UDP�˿ڽ����ַ���
// ����:
//    sock           �׽��ֽṹ
//    pData          ����ָ��
//    nDataLen       ���ݳ���
//    dwTimeout      ��ʱֵ
// ���:
//    ��
// ����:
//    >0            ��ȷ���������ݳ���
//    < 0           ����
//------------------------------------------------------------------------------------------------
int UDPGetChar(LPT_UDPSocket sock, char* pData, int nDataLen, DWORD dwTimeout)
{
   DWORD    dwTicks;
   int      nRetCode;
   int      nErrorCode = SOCKET_ERROR;
   int      nsaLen;
   int      nTotalBytes = 0;
   int      nBytes;
   int      nReads = 64000;
   fd_set   fdset;   
   TIMEVAL  tmval;   
   
   // ���ó�ʱֵ
   fdset.fd_count = 1;
   fdset.fd_array[0] = sock->socketRecv;
   tmval.tv_sec = dwTimeout / 1000;
   tmval.tv_usec = dwTimeout % 1000;   

   // �׽��ֳ���
   nsaLen = sizeof( sock->saFrom );
   
   // �������ָ��
   if ( pData == NULL )
      return nErrorCode;
   if (sock == NULL)
      return nErrorCode;
   
   // �ֶζ�ȡ���ݣ���ΪUDP�׽���ÿ�����ֻ�ܽ���64K�ֽ�
   // ����64Kʱ�Ͷ�ζ�ȡ
   nBytes = nDataLen;
   while (nBytes)
   {
      if (nBytes < 64000)
         nReads = nBytes;
      else
         nReads = 64000;
      
      // ���ڶ�ȡ����
      nBytes -= nReads;

      // ��ѯ�׽���״̬
      nRetCode = select(0, &fdset, NULL, NULL, &tmval);
      if (nRetCode != 1)
         break;
  
      // ���׽��ֶ�ȡָ�����ȵ�����
      nRetCode = recvfrom( sock->socketRecv, pData, nReads, 0, (struct sockaddr*)&sock->saFrom, &nsaLen );
      if ( nRetCode == nReads )
         nTotalBytes += nReads;
      else
         break;
   }
   
   // �����뵽ָ�����ȵ����ݺ󣬷��سɹ�
   if (nTotalBytes == nDataLen)
      nErrorCode = nTotalBytes;
   
   return nErrorCode;
}

//---------------------------------------------------------------------------
// UDP�˿ڷ����ַ���
// ����:
//    sock           �׽��ֽṹ
//    pData          ����ָ��
//    nDataLen       ���ݳ���
// ���:
//    ��
// ����:
//    >0            ��ȷ���������ݳ���
//    < 0           ����
//------------------------------------------------------------------------------------------------
int UDPPutChar(LPT_UDPSocket sock, char* pData, int nDataLen)
{
   DWORD    dwTicks;
   int      nRetCode;
   int      nErrorCode = SOCKET_ERROR;
   int      nsaLen;
   int      nTotalBytes = 0;
   int      nBytes;
   int      nWrites = 64000;
   
   // �׽��ֳ���
   nsaLen = sizeof( sock->saTo );
   
   // �������ָ��
   if (pData == NULL)
      return nErrorCode;
   if (sock == NULL)
      return nErrorCode;
   
   // �ֶη������ݣ���ΪUDP�׽���ÿ�����ֻ�ܷ���64K�ֽ�
   // ����64Kʱ�Ͷ�η���
   nBytes = nDataLen;
   while (nBytes)
   {
      if (nBytes < 64000)
         nWrites = nBytes;
      else
         nWrites = 64000;
      
      // ���ڷ��ͳ���
      nBytes -= nWrites;
         
      // ���׽��ַ���ָ�����ȵ�����
      nRetCode = sendto( sock->socketSend, pData, nWrites, 0, (struct sockaddr*)&sock->saTo, nsaLen );
      if ( nRetCode == nWrites )
         nTotalBytes += nWrites;
      else
         break;
   }
   
   // ������ָ�����ȵ����ݺ󣬷��سɹ�
   if (nTotalBytes == nDataLen)
      nErrorCode = nTotalBytes;
   
   return nErrorCode;
}

//---------------------------------------------------------------------------
// UDP�˿�������λ�����������´�
// ����:
//    dwTimeout      ��ʱֵ
// ���:
//    ��
// ����:
//    >0            ��ȷ���������ݳ���
//    < 0           ����
//------------------------------------------------------------------------------------------------
int UDPComm_Setup(DWORD dwTimeout)
{
   DWORD    dwTicks;
   int      nRetCode = SOCKET_ERROR;
   char     chData;
   int      nLen;
   int      nDataLen;
   static PT_UDPRequest     ssRequest;
   static PT_UDPResponse    ssResponse;
   
   // ����UDP�������ݰ�ͷ��
   ssRequest.Header.chCommand = CMD_SETUP;
   ssRequest.Header.chFlag = 0x100 - ssRequest.Header.chCommand;
   ssRequest.Header.shDataLen = sizeof( PT_Device );
   // ����UDP�������ݰ����ݲ�
   ssRequest.Header.lData = UDPCheckSum( (char*)&g_Device, sizeof( PT_Device ) );
   
   // ������ܴ��ͣ����ش���
   nDataLen = sizeof( ssRequest.Header );
   if ( UDPPutChar(&g_SystemData.UDPRealtime, (char*)&ssRequest, nDataLen ) != nDataLen )
      return nRetCode;
   
   // ���Ӧ����ȷ�����ش���
   nDataLen = sizeof( PT_Device );
   if ( UDPPutChar(&g_SystemData.UDPRealtime, (char*)&g_Device, nDataLen) != nDataLen)
      return nRetCode;
   
   // ����
   return nDataLen;
}

//---------------------------------------------------------------------------
// UDP�˿�����ʵʱ�����ϴ�
// ����:
//    dwTimeout      ��ʱֵ
// ���:
//    ��
// ����:
//    >0            ��ȷ���������ݳ���
//    < 0           ����
//------------------------------------------------------------------------------------------------
int UDPComm_Realtime(DWORD dwTimeout)
{
   int      nErrCode;
   int      nRetCode = SOCKET_ERROR;
   char     chData;
   int      nDataLen;
   static PT_UDPRequest     ssRequest;
   static PT_UDPResponse    ssResponse;
   
   // ����UDP�������ݰ�ͷ��
   ssRequest.Header.chCommand = CMD_REALTIME;
   ssRequest.Header.chFlag = 0x100 - ssRequest.Header.chCommand;
   ssRequest.Header.shDataLen = 0;
   ssRequest.Header.lData = 0;
   
   // ������ܴ��ͣ����ش���
   nDataLen = sizeof( ssRequest.Header );
   if ( UDPPutChar(&g_SystemData.UDPRealtime, (char*)&ssRequest, nDataLen ) != nDataLen )
      return nRetCode;
   
   // ���Ӧ����ȷ�����ش���
   nDataLen = sizeof( ssResponse.Header ) + sizeof( g_DAQData );
   nErrCode = UDPGetChar(&g_SystemData.UDPRealtime, (char*)&ssResponse, nDataLen, dwTimeout);
   if ( nErrCode != nDataLen )
      return nRetCode;
      
   // ���Ӧ�����ݳ��Ȳ���ȷ�����ش���
   nDataLen = ssResponse.Header.shDataLen;
   if ( nDataLen == 0 )
   return nRetCode;
      
   // ��ȷʱ������ʵʱ����
   memcpy( &g_DAQData, ssResponse.chData, sizeof( g_DAQData ) );
   
   // ��ȷ����
   nRetCode = nDataLen;
   return nRetCode;
}

//---------------------------------------------------------------------------
// UDP�˿����󱨱������ϴ�
// ����:
//    dwTimeout      ��ʱֵ
// ���:
//    ��
// ����:
//    >0            ��ȷ���������ݳ���
//    < 0           ����
//------------------------------------------------------------------------------------------------
int UDPComm_Report(DWORD dwTimeout )
{
   int      nErrCode;
   int      nRetCode = SOCKET_ERROR;
   char     chData;
   int      nDataLen;
   static PT_UDPRequest     ssRequest;
   static PT_UDPResponse    ssResponse;
   
   // ����UDP�������ݰ�ͷ��
   ssRequest.Header.chCommand = CMD_REPORT;
   ssRequest.Header.chFlag = 0x100 - ssRequest.Header.chCommand;
   ssRequest.Header.shDataLen = 0;
   ssRequest.Header.lData = 0;
   
   // ������ܴ��ͣ����ش���
   nDataLen = sizeof( ssRequest.Header );
   if ( UDPPutChar(&g_SystemData.UDPRealtime, (char*)&ssRequest, nDataLen ) != nDataLen )
      return nRetCode;
   
   // ���Ӧ����ȷ�����ش���
   nDataLen = sizeof( ssResponse.Header ) + sizeof( g_S700KData );
   nErrCode = UDPGetChar(&g_SystemData.UDPRealtime, (char*)&ssResponse, nDataLen, dwTimeout);
   if ( nErrCode != nDataLen )
      return nRetCode;
      
   // ���Ӧ�����ݳ��Ȳ���ȷ�����ش���
   nDataLen = ssResponse.Header.shDataLen;
   if ( nDataLen == 0 )
      return nRetCode;
      
   // ��ȷʱ�����汨������
   memcpy( &g_S700KData, ssResponse.chData, sizeof( g_S700KData ) );
      
   // ��ȷ����
   nRetCode = nDataLen;
   return nRetCode;
}

//---------------------------------------------------------------------------
// UDP�˿�������λ����ʼ��״̬�ϴ�
// ����:
//    dwTimeout      ��ʱֵ
// ���:
//    ��
// ����:
//    >0            ��ȷ���������ݳ���
//    < 0           ����
//------------------------------------------------------------------------------------------------
int UDPComm_Initialize(DWORD dwTimeout)
{
   int      nErrCode;
   int      nRetCode = SOCKET_ERROR;
   char     chData;
   int      nDataLen;
   static PT_UDPRequest     ssRequest;
   static PT_UDPResponse    ssResponse;
   
   // ����UDP�������ݰ�ͷ��
   ssRequest.Header.chCommand = CMD_INITIALIZE;
   ssRequest.Header.chFlag = 0x100 - ssRequest.Header.chCommand;
   ssRequest.Header.shDataLen = 0;
   ssRequest.Header.lData = 0;
   
   // ������ܴ��ͣ����ش���
   nDataLen = sizeof( ssRequest.Header );
   if ( UDPPutChar(&g_SystemData.UDPRealtime, (char*)&ssRequest, nDataLen ) != nDataLen )
      return nRetCode;
   
   // ���Ӧ����ȷ�����ش���
   nDataLen = sizeof (ssResponse.Header) + sizeof (g_InitStatus);
   nErrCode = UDPGetChar(&g_SystemData.UDPRealtime, (char*)&ssResponse, nDataLen, dwTimeout);
   if ( nErrCode != nDataLen )
      return nRetCode;
      
   // ���Ӧ�����ݳ��Ȳ���ȷ�����ش���
   nDataLen = sizeof (g_InitStatus);
   if (nDataLen != ssResponse.Header.shDataLen)
      return nRetCode;
      
   // ��ȷʱ����������
   memcpy (&g_InitStatus, ssResponse.chData, nDataLen);
      
   // ��ȷ����
   nRetCode = nDataLen;
   return nRetCode;
}

//---------------------------------------------------------------------------
// UDP�˿�������λ��ʵʱ���������ϴ�
// ����:
//    dwTimeout      ��ʱֵ
// ���:
//    ��
// ����:
//    >0            ��ȷ���������ݳ���
//    < 0           ����
//------------------------------------------------------------------------------------------------
int UDPComm_RealtimeTrend(DWORD dwTimeout)
{
   int      nErrCode;
   int      nRetCode = SOCKET_ERROR;
   char     chData;
   int      nDataLen;
   long     ulPointer;
   long     ulOffset;
   static PT_UDPRequest     ssRequest;
   static PT_UDPResponse    ssResponse;
   
   // ����UDP�������ݰ�ͷ��
   ssRequest.Header.chCommand = CMD_REALTIMETREND;
   ssRequest.Header.chFlag = 0x100 - ssRequest.Header.chCommand;
   ssRequest.Header.shDataLen = 0;
   ssRequest.Header.lData = 0;
   
   // ������ܴ��ͣ����ش���
   nDataLen = sizeof( ssRequest.Header );
   if ( UDPPutChar(&g_SystemData.UDPTrend, (char*)&ssRequest, nDataLen ) != nDataLen )
      return nRetCode;
   
   // ���Ӧ����ȷ�����ش���
   nDataLen = sizeof (float) * FAI_PacerRate + sizeof (ssResponse.Header);
   nErrCode = UDPGetChar(&g_SystemData.UDPTrend, (char*)&ssResponse, nDataLen, dwTimeout);
   if ( nErrCode != nDataLen )
      return nRetCode;
      
   // ���Ӧ�����ݳ��Ȳ���ȷ�����ش���
   nDataLen = sizeof (float) * FAI_PacerRate;
   if (nDataLen != ssResponse.Header.shDataLen)
      return nRetCode;
   
   // ����λ�Ʊ����
   nRetCode = nDataLen;
   ulPointer = ssResponse.Header.lData;
   
   // ����տ�ʼ��¼���ݣ����������
   if (g_SystemData.ulStartPointer == 0)
   {
      memset (&g_SystemData.ufDataBuffer, 0, FAI_DataBufferSize * FAI_PacerRate * sizeof (float));
      g_SystemData.ulStartPointer = ulPointer;
   }
   
   // ���㻺�������ݿ�ƫ��
   ulOffset = ulPointer - g_SystemData.ulStartPointer;
   
   // ���
   if (ulOffset < 0)
      return nRetCode;
   
   // �������������򲻼�¼
   if (ulOffset > (FAI_DataBufferSize * 2 - 2))
      return nRetCode;

   // ��ȷʱ����������
   memcpy (&g_SystemData.ufDataBuffer[ulOffset * (FAI_PacerRate / 2)], ssResponse.chData, nDataLen);
   
   // ��ȷ����
   g_SystemData.ulPointer = ulPointer;
   return nRetCode;
}

//---------------------------------------------------------------------------
// UDP�˿�������λ����������
// ����:
//    dwTimeout      ��ʱֵ
// ���:
//    ��
// ����:
//    >0            ��ȷ���������ݳ���
//    < 0           ����
//------------------------------------------------------------------------------------------------
int UDPComm_Restart(DWORD dwTimeout )
{
   DWORD    dwTicks;
   int      nRetCode = SOCKET_ERROR;
   char     chData;
   int      nLen;
   int      nDataLen;
   PT_UDPRequest     ssRequest;
   PT_UDPResponse    ssResponse;
   
   // ����UDP�������ݰ�ͷ��
   ssRequest.Header.chCommand = CMD_RESTART;
   ssRequest.Header.chFlag = 0x100 - ssRequest.Header.chCommand;
   ssRequest.Header.shDataLen = 0;
   ssRequest.Header.lData = 0;
   
   // ������ܴ��ͣ����ش���
   nDataLen = sizeof( ssRequest.Header );
   if ( UDPPutChar(&g_SystemData.UDPRealtime, (char*)&ssRequest, nDataLen ) != nDataLen )
      return nRetCode;
   
   return nRetCode;
}

//---------------------------------------------------------------------------
// UDP�˿�������λ���ػ�
// ����:
//    dwTimeout      ��ʱֵ
// ���:
//    ��
// ����:
//    >0            ��ȷ���������ݳ���
//    < 0           ����
//------------------------------------------------------------------------------------------------
int UDPComm_Shutdown(DWORD dwTimeout )
{
   DWORD    dwTicks;
   int      nRetCode = SOCKET_ERROR;
   char     chData;
   int      nLen;
   int      nDataLen;
   PT_UDPRequest     ssRequest;
   PT_UDPResponse    ssResponse;
   
   // ����UDP�������ݰ�ͷ��
   ssRequest.Header.chCommand = CMD_SHUTDOWN;
   ssRequest.Header.chFlag = 0x100 - ssRequest.Header.chCommand;
   ssRequest.Header.shDataLen = 0;
   ssRequest.Header.lData = 0;
   
   // ������ܴ��ͣ����ش���
   nDataLen = sizeof( ssRequest.Header );
   if ( UDPPutChar(&g_SystemData.UDPRealtime, (char*)&ssRequest, nDataLen ) != nDataLen )
      return nRetCode;
   
   return nRetCode;
}

//---------------------------------------------------------------------------
// UDPͨѶ������
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//---------------------------------------------------------------------------
DWORD TBStubUDPCom( LPVOID* arg )
{
   // �����Ҫ���˳��̣߳���ͣ��ѭ����飬��ȡ��λ���´���ָ�������λ��Ӧ��
   while (g_SystemData.usThreadLoop)
   {
      Sleep( 100 );
      // ϵͳ�������������´�
      if ( g_SystemData.usDownloadConfig == 1 )
      {
         // �´���������
         if ( UDPComm_Setup (200) == SOCKET_ERROR )
            g_InitStatus.chInitNetwork = FALSE;
         else
            g_SystemData.usDownloadConfig = 0;
         
         g_Device.Config.usTraillingTest = 0;
      }
      // �����ʼ��״̬�ϴ�
      if ( UDPComm_Initialize( 2000 ) == SOCKET_ERROR )
      {
         g_InitStatus.chInitNetwork = FALSE;
      }
      // ����ʵʱ�����ϴ�
      if ( UDPComm_Realtime( 2000 ) == SOCKET_ERROR )
      {
         g_InitStatus.chInitNetwork = FALSE;
      }
      // ���󱨱������ϴ�
      if ( UDPComm_Report( 2000 ) == SOCKET_ERROR )
      {
         g_InitStatus.chInitNetwork = FALSE;
      }
      continue;
   }
   return 0;
}

//---------------------------------------------------------------------------
// UDP�˿�������λ��ʵʱ���������ϴ�
// ����:
//    dwTimeout      ��ʱֵ
// ���:
//    ��
// ����:
//    >0            ��ȷ���������ݳ���
//    < 0           ����
//------------------------------------------------------------------------------------------------
int __stdcall UDPRealtimeTrend(void)
{
   return UDPComm_RealtimeTrend (1000);
}

//---------------------------------------------------------------------------
// UDPͨѶʵʱ���������ϴ��߳�
// ����:
//    dwTimeout      ��ʱֵ
// ���:
//    ��
// ����:
//    >0            ��ȷ���������ݳ���
//    < 0           ����
//------------------------------------------------------------------------------------------------
DWORD TBStubForceTrend(void* arg)
{
   // �����Ҫ���˳��̣߳���ͣ��ѭ����飬��ȡ��λ���´���ָ�������λ��Ӧ��
   while (g_SystemData.usThreadLoop)
   {
      Sleep (400);
      // �����Ҫ���ϴ��������ݣ������
      if (!g_SystemData.UDPTrend.usThreadLoop)
         continue;
      
      // �����ϴ���������
      if (UDPRealtimeTrend () == SOCKET_ERROR)
         continue;
   }
   
   return 0;
}

//---------------------------------------------------------------------------
// ����UDPͨѶ�߳�
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//---------------------------------------------------------------------------
int __stdcall InitializeUDPCom( void )
{
   DWORD ThreadID;
   // ��ʼ��UDP�׽���
   InitializeWinsock();

   // ����ʵʱ�����߳�
   g_SystemData.usThreadLoop = 1;
   g_SystemData.UDPRealtime.uhUDPComThread = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)&TBStubUDPCom, &g_SystemData.UDPRealtime, 0, &ThreadID ); 
   
   // ����ʵʱ���������߳�
   g_SystemData.UDPTrend.usThreadLoop = 0;
   g_SystemData.UDPTrend.usThreadLoop = 1;
   g_SystemData.UDPTrend.uhUDPComThread = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)&TBStubForceTrend, &g_SystemData.UDPTrend, 0, &ThreadID);
   return 0;
}

//---------------------------------------------------------------------------
// ֹͣUDPͨѶ�߳�
// ����:
//    ��
// ���:
//    ��
// ����:
//    ��
//---------------------------------------------------------------------------
int __stdcall UninitializeUDPCom( void )
{
   // ����ֹͣ����UDPͨѶ�߳�
   g_SystemData.usThreadLoop = 0;
   g_SystemData.UDPTrend.usThreadLoop = 0;

   // �ȴ�ʵʱ�����߳̽���
   WaitForSingleObject (g_SystemData.UDPRealtime.uhUDPComThread, 3000);
   CloseHandle (g_SystemData.UDPRealtime.uhUDPComThread);
   g_SystemData.UDPRealtime.uhUDPComThread = NULL;
   
   // �ȴ�ʵʱ�����߳̽���
   WaitForSingleObject (g_SystemData.UDPTrend.uhUDPComThread, 3000);
   CloseHandle (g_SystemData.UDPTrend.uhUDPComThread);
   g_SystemData.UDPTrend.uhUDPComThread = NULL;

   // ����UDP�׽���
   UninitializeWinsock( );
   
   return 0;
}

