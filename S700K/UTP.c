// #########################################################################
// *************************************************************************

#include <ansi_c.h>
#include <Winsock2.h>
#include "udp.h"
#include "..\include\global.h"
#include "Myfile.h"
#include "S700K.h"

//---------------------------------------------------------------------------
// 定义全局变量
//------------------------------------------------------------------------------------------------
extern PT_Device        g_Device;
extern PT_SystemData    g_SystemData;
extern PT_InitStatus    g_InitStatus;
extern PT_DAQData       g_DAQData;
extern PT_ReportData    g_S700KData;
extern int              plTrend;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// 初始化UDP传送套接字
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void InitializeWinsock( )
{
   WSADATA wsaData;
   WORD sockVersion=MAKEWORD( 2, 2 );
   
   // 实时数据
   g_SystemData.UDPRealtime.saSend.sin_family = AF_INET;
   g_SystemData.UDPRealtime.saSend.sin_port = htons( 20000 );                 // 监听端口
   g_SystemData.UDPRealtime.saSend.sin_addr.s_addr = inet_addr( UDPCLIENT ); // 本机
   g_SystemData.UDPRealtime.saRecv.sin_family = AF_INET;
   g_SystemData.UDPRealtime.saRecv.sin_port = htons( 20001 );                 // 监听端口
   g_SystemData.UDPRealtime.saRecv.sin_addr.s_addr = inet_addr( UDPCLIENT ); // 本机

   g_SystemData.UDPRealtime.saFrom.sin_family = AF_INET;
   g_SystemData.UDPRealtime.saFrom.sin_port = htons( 10000 );                // 监听端口
   g_SystemData.UDPRealtime.saFrom.sin_addr.s_addr = inet_addr( UDPSERVER ); // 本机
   g_SystemData.UDPRealtime.saTo.sin_family = AF_INET;
   g_SystemData.UDPRealtime.saTo.sin_port = htons( 10001 );                   // 监听端口
   g_SystemData.UDPRealtime.saTo.sin_addr.s_addr = inet_addr( UDPSERVER );   // 本机

   // 趋势数据
   g_SystemData.UDPTrend.saSend.sin_family = AF_INET;
   g_SystemData.UDPTrend.saSend.sin_port = htons( 20010 );                    // 监听端口
   g_SystemData.UDPTrend.saSend.sin_addr.s_addr = inet_addr( UDPCLIENT );     // 本机
   g_SystemData.UDPTrend.saRecv.sin_family = AF_INET;
   g_SystemData.UDPTrend.saRecv.sin_port = htons( 20011 );                    // 监听端口
   g_SystemData.UDPTrend.saRecv.sin_addr.s_addr = inet_addr( UDPCLIENT );     // 本机

   g_SystemData.UDPTrend.saFrom.sin_family = AF_INET;
   g_SystemData.UDPTrend.saFrom.sin_port = htons( 10010 );                // 监听端口
   g_SystemData.UDPTrend.saFrom.sin_addr.s_addr = inet_addr( UDPSERVER ); // 本机
   g_SystemData.UDPTrend.saTo.sin_family = AF_INET;
   g_SystemData.UDPTrend.saTo.sin_port = htons( 10011 );                   // 监听端口
   g_SystemData.UDPTrend.saTo.sin_addr.s_addr = inet_addr( UDPSERVER );   // 本机

   if( WSAStartup( sockVersion, &wsaData ) !=0 )
   {  // Error
      return;
   }
   
   // 实时数据，发送
   g_SystemData.UDPRealtime.socketSend = socket( AF_INET, SOCK_DGRAM, 0 );
   bind (g_SystemData.UDPRealtime.socketSend, (struct sockaddr*)&g_SystemData.UDPRealtime.saSend, sizeof (struct sockaddr_in));
   // 实时数据，接收
   g_SystemData.UDPRealtime.socketRecv = socket( AF_INET, SOCK_DGRAM, 0 );
   bind (g_SystemData.UDPRealtime.socketRecv, (struct sockaddr*)&g_SystemData.UDPRealtime.saRecv, sizeof (struct sockaddr_in));

   // 趋势数据，发送
   g_SystemData.UDPTrend.socketSend = socket( AF_INET, SOCK_DGRAM, 0 );
   bind (g_SystemData.UDPTrend.socketSend, (struct sockaddr*)&g_SystemData.UDPTrend.saSend, sizeof (struct sockaddr_in));
   // 趋势数据，接收
   g_SystemData.UDPTrend.socketRecv = socket( AF_INET, SOCK_DGRAM, 0 );
   bind (g_SystemData.UDPTrend.socketRecv, (struct sockaddr*)&g_SystemData.UDPTrend.saRecv, sizeof (struct sockaddr_in));
}

//---------------------------------------------------------------------------
// 关闭UDP传送套接字
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//------------------------------------------------------------------------------------------------
void UninitializeWinsock( )
{
   // 实时数据
   closesocket (g_SystemData.UDPTrend.socketSend);
   closesocket (g_SystemData.UDPTrend.socketRecv);

   // 趋势数据
   closesocket (g_SystemData.UDPTrend.socketSend);
   closesocket (g_SystemData.UDPTrend.socketRecv);

   // 清理数据传输
   WSACleanup();
}

//---------------------------------------------------------------------------
// UDP数据传输校验和
// 输入:
//    pData          数据指针
//    nLen           数据长度
// 输出:
//    无
// 返回:
//                   校验和
//------------------------------------------------------------------------------------------------
short UDPCheckSum( char* pData, int nLen )
{
   // 校验和初始值
   short    shSum = 0x00;
   int      i;
   
   // 数据指针不能为空
   if ( pData == NULL )
      return shSum;
   
   // 计算校验和
   for ( i = 0; i < nLen; i ++ )
      shSum += pData[ i ];
   
   // 修正
   shSum = shSum & 0xffff;
   
   return shSum;
}

//---------------------------------------------------------------------------
// UDP端口接受字符串
// 输入:
//    sock           套接字结构
//    pData          数据指针
//    nDataLen       数据长度
//    dwTimeout      超时值
// 输出:
//    无
// 返回:
//    >0            正确，接受数据长度
//    < 0           错误
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
   
   // 设置超时值
   fdset.fd_count = 1;
   fdset.fd_array[0] = sock->socketRecv;
   tmval.tv_sec = dwTimeout / 1000;
   tmval.tv_usec = dwTimeout % 1000;   

   // 套接字长度
   nsaLen = sizeof( sock->saFrom );
   
   // 检查数据指针
   if ( pData == NULL )
      return nErrorCode;
   if (sock == NULL)
      return nErrorCode;
   
   // 分段读取数据，因为UDP套接字每次最大只能接受64K字节
   // 超过64K时就多次读取
   nBytes = nDataLen;
   while (nBytes)
   {
      if (nBytes < 64000)
         nReads = nBytes;
      else
         nReads = 64000;
      
      // 调节读取长度
      nBytes -= nReads;

      // 查询套接字状态
      nRetCode = select(0, &fdset, NULL, NULL, &tmval);
      if (nRetCode != 1)
         break;
  
      // 从套接字读取指定长度的数据
      nRetCode = recvfrom( sock->socketRecv, pData, nReads, 0, (struct sockaddr*)&sock->saFrom, &nsaLen );
      if ( nRetCode == nReads )
         nTotalBytes += nReads;
      else
         break;
   }
   
   // 当读入到指定长度的数据后，返回成功
   if (nTotalBytes == nDataLen)
      nErrorCode = nTotalBytes;
   
   return nErrorCode;
}

//---------------------------------------------------------------------------
// UDP端口发送字符串
// 输入:
//    sock           套接字结构
//    pData          数据指针
//    nDataLen       数据长度
// 输出:
//    无
// 返回:
//    >0            正确，接受数据长度
//    < 0           错误
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
   
   // 套接字长度
   nsaLen = sizeof( sock->saTo );
   
   // 检查数据指针
   if (pData == NULL)
      return nErrorCode;
   if (sock == NULL)
      return nErrorCode;
   
   // 分段发送数据，因为UDP套接字每次最大只能发送64K字节
   // 超过64K时就多次发送
   nBytes = nDataLen;
   while (nBytes)
   {
      if (nBytes < 64000)
         nWrites = nBytes;
      else
         nWrites = 64000;
      
      // 调节发送长度
      nBytes -= nWrites;
         
      // 从套接字发送指定长度的数据
      nRetCode = sendto( sock->socketSend, pData, nWrites, 0, (struct sockaddr*)&sock->saTo, nsaLen );
      if ( nRetCode == nWrites )
         nTotalBytes += nWrites;
      else
         break;
   }
   
   // 当发送指定长度的数据后，返回成功
   if (nTotalBytes == nDataLen)
      nErrorCode = nTotalBytes;
   
   return nErrorCode;
}

//---------------------------------------------------------------------------
// UDP端口请求上位机配置数据下传
// 输入:
//    dwTimeout      超时值
// 输出:
//    无
// 返回:
//    >0            正确，接受数据长度
//    < 0           错误
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
   
   // 生成UDP请求数据包头部
   ssRequest.Header.chCommand = CMD_SETUP;
   ssRequest.Header.chFlag = 0x100 - ssRequest.Header.chCommand;
   ssRequest.Header.shDataLen = sizeof( PT_Device );
   // 生成UDP请求数据包数据部
   ssRequest.Header.lData = UDPCheckSum( (char*)&g_Device, sizeof( PT_Device ) );
   
   // 如果不能传送，返回错误
   nDataLen = sizeof( ssRequest.Header );
   if ( UDPPutChar(&g_SystemData.UDPRealtime, (char*)&ssRequest, nDataLen ) != nDataLen )
      return nRetCode;
   
   // 如果应答不正确，返回错误
   nDataLen = sizeof( PT_Device );
   if ( UDPPutChar(&g_SystemData.UDPRealtime, (char*)&g_Device, nDataLen) != nDataLen)
      return nRetCode;
   
   // 返回
   return nDataLen;
}

//---------------------------------------------------------------------------
// UDP端口请求实时数据上传
// 输入:
//    dwTimeout      超时值
// 输出:
//    无
// 返回:
//    >0            正确，接受数据长度
//    < 0           错误
//------------------------------------------------------------------------------------------------
int UDPComm_Realtime(DWORD dwTimeout)
{
   int      nErrCode;
   int      nRetCode = SOCKET_ERROR;
   char     chData;
   int      nDataLen;
   static PT_UDPRequest     ssRequest;
   static PT_UDPResponse    ssResponse;
   
   // 生成UDP请求数据包头部
   ssRequest.Header.chCommand = CMD_REALTIME;
   ssRequest.Header.chFlag = 0x100 - ssRequest.Header.chCommand;
   ssRequest.Header.shDataLen = 0;
   ssRequest.Header.lData = 0;
   
   // 如果不能传送，返回错误
   nDataLen = sizeof( ssRequest.Header );
   if ( UDPPutChar(&g_SystemData.UDPRealtime, (char*)&ssRequest, nDataLen ) != nDataLen )
      return nRetCode;
   
   // 如果应答不正确，返回错误
   nDataLen = sizeof( ssResponse.Header ) + sizeof( g_DAQData );
   nErrCode = UDPGetChar(&g_SystemData.UDPRealtime, (char*)&ssResponse, nDataLen, dwTimeout);
   if ( nErrCode != nDataLen )
      return nRetCode;
      
   // 如果应答数据长度不正确，返回错误
   nDataLen = ssResponse.Header.shDataLen;
   if ( nDataLen == 0 )
   return nRetCode;
      
   // 正确时，保存实时数据
   memcpy( &g_DAQData, ssResponse.chData, sizeof( g_DAQData ) );
   
   // 正确返回
   nRetCode = nDataLen;
   return nRetCode;
}

//---------------------------------------------------------------------------
// UDP端口请求报表数据上传
// 输入:
//    dwTimeout      超时值
// 输出:
//    无
// 返回:
//    >0            正确，接受数据长度
//    < 0           错误
//------------------------------------------------------------------------------------------------
int UDPComm_Report(DWORD dwTimeout )
{
   int      nErrCode;
   int      nRetCode = SOCKET_ERROR;
   char     chData;
   int      nDataLen;
   static PT_UDPRequest     ssRequest;
   static PT_UDPResponse    ssResponse;
   
   // 生成UDP请求数据包头部
   ssRequest.Header.chCommand = CMD_REPORT;
   ssRequest.Header.chFlag = 0x100 - ssRequest.Header.chCommand;
   ssRequest.Header.shDataLen = 0;
   ssRequest.Header.lData = 0;
   
   // 如果不能传送，返回错误
   nDataLen = sizeof( ssRequest.Header );
   if ( UDPPutChar(&g_SystemData.UDPRealtime, (char*)&ssRequest, nDataLen ) != nDataLen )
      return nRetCode;
   
   // 如果应答不正确，返回错误
   nDataLen = sizeof( ssResponse.Header ) + sizeof( g_S700KData );
   nErrCode = UDPGetChar(&g_SystemData.UDPRealtime, (char*)&ssResponse, nDataLen, dwTimeout);
   if ( nErrCode != nDataLen )
      return nRetCode;
      
   // 如果应答数据长度不正确，返回错误
   nDataLen = ssResponse.Header.shDataLen;
   if ( nDataLen == 0 )
      return nRetCode;
      
   // 正确时，保存报表数据
   memcpy( &g_S700KData, ssResponse.chData, sizeof( g_S700KData ) );
      
   // 正确返回
   nRetCode = nDataLen;
   return nRetCode;
}

//---------------------------------------------------------------------------
// UDP端口请求下位机初始化状态上传
// 输入:
//    dwTimeout      超时值
// 输出:
//    无
// 返回:
//    >0            正确，接受数据长度
//    < 0           错误
//------------------------------------------------------------------------------------------------
int UDPComm_Initialize(DWORD dwTimeout)
{
   int      nErrCode;
   int      nRetCode = SOCKET_ERROR;
   char     chData;
   int      nDataLen;
   static PT_UDPRequest     ssRequest;
   static PT_UDPResponse    ssResponse;
   
   // 生成UDP请求数据包头部
   ssRequest.Header.chCommand = CMD_INITIALIZE;
   ssRequest.Header.chFlag = 0x100 - ssRequest.Header.chCommand;
   ssRequest.Header.shDataLen = 0;
   ssRequest.Header.lData = 0;
   
   // 如果不能传送，返回错误
   nDataLen = sizeof( ssRequest.Header );
   if ( UDPPutChar(&g_SystemData.UDPRealtime, (char*)&ssRequest, nDataLen ) != nDataLen )
      return nRetCode;
   
   // 如果应答不正确，返回错误
   nDataLen = sizeof (ssResponse.Header) + sizeof (g_InitStatus);
   nErrCode = UDPGetChar(&g_SystemData.UDPRealtime, (char*)&ssResponse, nDataLen, dwTimeout);
   if ( nErrCode != nDataLen )
      return nRetCode;
      
   // 如果应答数据长度不正确，返回错误
   nDataLen = sizeof (g_InitStatus);
   if (nDataLen != ssResponse.Header.shDataLen)
      return nRetCode;
      
   // 正确时，保存数据
   memcpy (&g_InitStatus, ssResponse.chData, nDataLen);
      
   // 正确返回
   nRetCode = nDataLen;
   return nRetCode;
}

//---------------------------------------------------------------------------
// UDP端口请求下位机实时趋势数据上传
// 输入:
//    dwTimeout      超时值
// 输出:
//    无
// 返回:
//    >0            正确，接受数据长度
//    < 0           错误
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
   
   // 生成UDP请求数据包头部
   ssRequest.Header.chCommand = CMD_REALTIMETREND;
   ssRequest.Header.chFlag = 0x100 - ssRequest.Header.chCommand;
   ssRequest.Header.shDataLen = 0;
   ssRequest.Header.lData = 0;
   
   // 如果不能传送，返回错误
   nDataLen = sizeof( ssRequest.Header );
   if ( UDPPutChar(&g_SystemData.UDPTrend, (char*)&ssRequest, nDataLen ) != nDataLen )
      return nRetCode;
   
   // 如果应答不正确，返回错误
   nDataLen = sizeof (float) * FAI_PacerRate + sizeof (ssResponse.Header);
   nErrCode = UDPGetChar(&g_SystemData.UDPTrend, (char*)&ssResponse, nDataLen, dwTimeout);
   if ( nErrCode != nDataLen )
      return nRetCode;
      
   // 如果应答数据长度不正确，返回错误
   nDataLen = sizeof (float) * FAI_PacerRate;
   if (nDataLen != ssResponse.Header.shDataLen)
      return nRetCode;
   
   // 计算位移保存点
   nRetCode = nDataLen;
   ulPointer = ssResponse.Header.lData;
   
   // 如果刚开始记录数据，清除缓冲区
   if (g_SystemData.ulStartPointer == 0)
   {
      memset (&g_SystemData.ufDataBuffer, 0, FAI_DataBufferSize * FAI_PacerRate * sizeof (float));
      g_SystemData.ulStartPointer = ulPointer;
   }
   
   // 计算缓冲区数据块偏移
   ulOffset = ulPointer - g_SystemData.ulStartPointer;
   
   // 检查
   if (ulOffset < 0)
      return nRetCode;
   
   // 缓冲区已满，则不记录
   if (ulOffset > (FAI_DataBufferSize * 2 - 2))
      return nRetCode;

   // 正确时，保存数据
   memcpy (&g_SystemData.ufDataBuffer[ulOffset * (FAI_PacerRate / 2)], ssResponse.chData, nDataLen);
   
   // 正确返回
   g_SystemData.ulPointer = ulPointer;
   return nRetCode;
}

//---------------------------------------------------------------------------
// UDP端口请求下位机重新启动
// 输入:
//    dwTimeout      超时值
// 输出:
//    无
// 返回:
//    >0            正确，接受数据长度
//    < 0           错误
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
   
   // 生成UDP请求数据包头部
   ssRequest.Header.chCommand = CMD_RESTART;
   ssRequest.Header.chFlag = 0x100 - ssRequest.Header.chCommand;
   ssRequest.Header.shDataLen = 0;
   ssRequest.Header.lData = 0;
   
   // 如果不能传送，返回错误
   nDataLen = sizeof( ssRequest.Header );
   if ( UDPPutChar(&g_SystemData.UDPRealtime, (char*)&ssRequest, nDataLen ) != nDataLen )
      return nRetCode;
   
   return nRetCode;
}

//---------------------------------------------------------------------------
// UDP端口请求下位机关机
// 输入:
//    dwTimeout      超时值
// 输出:
//    无
// 返回:
//    >0            正确，接受数据长度
//    < 0           错误
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
   
   // 生成UDP请求数据包头部
   ssRequest.Header.chCommand = CMD_SHUTDOWN;
   ssRequest.Header.chFlag = 0x100 - ssRequest.Header.chCommand;
   ssRequest.Header.shDataLen = 0;
   ssRequest.Header.lData = 0;
   
   // 如果不能传送，返回错误
   nDataLen = sizeof( ssRequest.Header );
   if ( UDPPutChar(&g_SystemData.UDPRealtime, (char*)&ssRequest, nDataLen ) != nDataLen )
      return nRetCode;
   
   return nRetCode;
}

//---------------------------------------------------------------------------
// UDP通讯主程序
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//---------------------------------------------------------------------------
DWORD TBStubUDPCom( LPVOID* arg )
{
   // 如果不要求退出线程，不停的循环检查，读取上位机下传的指令，发送下位机应答
   while (g_SystemData.usThreadLoop)
   {
      Sleep( 100 );
      // 系统请求配置数据下传
      if ( g_SystemData.usDownloadConfig == 1 )
      {
         // 下传配置数据
         if ( UDPComm_Setup (200) == SOCKET_ERROR )
            g_InitStatus.chInitNetwork = FALSE;
         else
            g_SystemData.usDownloadConfig = 0;
         
         g_Device.Config.usTraillingTest = 0;
      }
      // 请求初始化状态上传
      if ( UDPComm_Initialize( 2000 ) == SOCKET_ERROR )
      {
         g_InitStatus.chInitNetwork = FALSE;
      }
      // 请求实时数据上传
      if ( UDPComm_Realtime( 2000 ) == SOCKET_ERROR )
      {
         g_InitStatus.chInitNetwork = FALSE;
      }
      // 请求报表数据上传
      if ( UDPComm_Report( 2000 ) == SOCKET_ERROR )
      {
         g_InitStatus.chInitNetwork = FALSE;
      }
      continue;
   }
   return 0;
}

//---------------------------------------------------------------------------
// UDP端口请求下位机实时趋势数据上传
// 输入:
//    dwTimeout      超时值
// 输出:
//    无
// 返回:
//    >0            正确，接受数据长度
//    < 0           错误
//------------------------------------------------------------------------------------------------
int __stdcall UDPRealtimeTrend(void)
{
   return UDPComm_RealtimeTrend (1000);
}

//---------------------------------------------------------------------------
// UDP通讯实时趋势数据上传线程
// 输入:
//    dwTimeout      超时值
// 输出:
//    无
// 返回:
//    >0            正确，接受数据长度
//    < 0           错误
//------------------------------------------------------------------------------------------------
DWORD TBStubForceTrend(void* arg)
{
   // 如果不要求退出线程，不停的循环检查，读取上位机下传的指令，发送下位机应答
   while (g_SystemData.usThreadLoop)
   {
      Sleep (400);
      // 如果不要求上传趋势数据，则继续
      if (!g_SystemData.UDPTrend.usThreadLoop)
         continue;
      
      // 请求上传趋势数据
      if (UDPRealtimeTrend () == SOCKET_ERROR)
         continue;
   }
   
   return 0;
}

//---------------------------------------------------------------------------
// 启动UDP通讯线程
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//---------------------------------------------------------------------------
int __stdcall InitializeUDPCom( void )
{
   DWORD ThreadID;
   // 初始化UDP套接字
   InitializeWinsock();

   // 启动实时数据线程
   g_SystemData.usThreadLoop = 1;
   g_SystemData.UDPRealtime.uhUDPComThread = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)&TBStubUDPCom, &g_SystemData.UDPRealtime, 0, &ThreadID ); 
   
   // 启动实时趋势数据线程
   g_SystemData.UDPTrend.usThreadLoop = 0;
   g_SystemData.UDPTrend.usThreadLoop = 1;
   g_SystemData.UDPTrend.uhUDPComThread = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)&TBStubForceTrend, &g_SystemData.UDPTrend, 0, &ThreadID);
   return 0;
}

//---------------------------------------------------------------------------
// 停止UDP通讯线程
// 输入:
//    无
// 输出:
//    无
// 返回:
//    无
//---------------------------------------------------------------------------
int __stdcall UninitializeUDPCom( void )
{
   // 请求停止两个UDP通讯线程
   g_SystemData.usThreadLoop = 0;
   g_SystemData.UDPTrend.usThreadLoop = 0;

   // 等待实时数据线程结束
   WaitForSingleObject (g_SystemData.UDPRealtime.uhUDPComThread, 3000);
   CloseHandle (g_SystemData.UDPRealtime.uhUDPComThread);
   g_SystemData.UDPRealtime.uhUDPComThread = NULL;
   
   // 等待实时趋势线程结束
   WaitForSingleObject (g_SystemData.UDPTrend.uhUDPComThread, 3000);
   CloseHandle (g_SystemData.UDPTrend.uhUDPComThread);
   g_SystemData.UDPTrend.uhUDPComThread = NULL;

   // 清理UDP套接字
   UninitializeWinsock( );
   
   return 0;
}

