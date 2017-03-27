// #########################################################################
// *************************************************************************
//                     Copyright (C) 2002-2020.
//   THIS IS AN UNPUBLISHED WORK CONTAINED CONFIDENTIAL, AND PROPRIETARY
//              INFORMATION WHICH IS THE PROPERTY OF TangBo.
// ANY DISCLOSURE, USE, OR REPRODUCTION, WITHOUT WRITTEN AUTHORIZATION FROM
//                        TangBo, IS STRICT.
// #########################################################################
// *************************************************************************

#include <windows.h>
#include "COMM.h"
#include <ansi_c.h>
#include <WinBase.h>
#include <userint.h>

//------------------------------------------------------------------------------------------------
BOOL Port_Initialize(LPT_Port pPort)
{
   CHAR         name[40];
   DCB          dcb;
   COMMTIMEOUTS cts;
   
   sprintf(name, "COM%d:", pPort->wPort);
   
   if (pPort->hPort == NULL)
   {
      pPort->hPort = CreateFile(name,
         GENERIC_READ | GENERIC_WRITE,
         0,
         NULL,   // security
         OPEN_EXISTING,
         FILE_ATTRIBUTE_NORMAL,
         NULL);
      if (pPort->hPort == INVALID_HANDLE_VALUE)
      {
         pPort->hPort = NULL;
         return FALSE;
      }
      pPort->bInit = FALSE;
   }
   
   if (pPort->bInit == TRUE)
      return TRUE;
   
   if (!GetCommState(pPort->hPort, &dcb))
   {
      return FALSE;
   }
   dcb.BaudRate = pPort->wBaud;
   dcb.fBinary = TRUE;
   dcb.fParity = (pPort->wParity == NOPARITY ? FALSE : TRUE);
   dcb.fNull = FALSE;
   dcb.ByteSize = (UCHAR)pPort->wBits;
   dcb.Parity = (UCHAR)pPort->wParity;
   dcb.fOutxCtsFlow = FALSE;
   dcb.fRtsControl = RTS_CONTROL_DISABLE;
   
   if (!SetCommState(pPort->hPort, &dcb))
   {
      return FALSE;
   }
   
   if (!GetCommTimeouts(pPort->hPort, &cts))
   {
      return FALSE;
   }
   //  Timeout between two consecutive characters.
   cts.ReadIntervalTimeout = (DWORD)((3.5 * 10.0 * 1000) / pPort->wBaud);
   cts.ReadTotalTimeoutMultiplier = 1;
   cts.ReadTotalTimeoutConstant = 200;
   cts.WriteTotalTimeoutMultiplier = 1;
   cts.WriteTotalTimeoutConstant = 200;
   if (!SetCommTimeouts(pPort->hPort, &cts))
   {
      return FALSE;
   }
   
   pPort->bInit = TRUE;

   return TRUE;
}

//------------------------------------------------------------------------------------------------
BOOL __stdcall COM_Open( LPT_Port pPort )
{
   CHAR       szName[ 40 ];
   COMMTIMEOUTS      CommTimeOuts ;
   DCB               dcb;
   
   if ( pPort->hPort != NULL )
      return TRUE;
   
   sprintf(szName, "COM%d", pPort->wPort);
   
   pPort->hPort = CreateFile( 
                           szName,
                           GENERIC_READ | GENERIC_WRITE,
                           ((1) ? FILE_SHARE_READ | FILE_SHARE_WRITE : 0),
                           NULL, 
                           OPEN_EXISTING, 
                           0, 
                           NULL );

   if( pPort->hPort == INVALID_HANDLE_VALUE )
   {
      pPort->hPort = NULL;
      return FALSE;
   }
   
   SetupComm( pPort->hPort, 1024, 1024 );
   
   PurgeComm( pPort->hPort, PURGE_TXABORT | PURGE_RXABORT |
      PURGE_TXCLEAR | PURGE_RXCLEAR ) ;
   
   // set up for overlapped I/O
//   CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF ;
//   CommTimeOuts.ReadTotalTimeoutMultiplier = 0 ;
//   CommTimeOuts.ReadTotalTimeoutConstant = 1000 ;

   // CBR_9600 is approximately 1byte/ms. For our purposes, allow
   // double the expected time per character for a fudge factor.
//   CommTimeOuts.WriteTotalTimeoutMultiplier = 2*CBR_9600/CBR_9600 ;
//   CommTimeOuts.WriteTotalTimeoutConstant = 0 ;
   CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
   CommTimeOuts.ReadTotalTimeoutMultiplier = 1;
   CommTimeOuts.ReadTotalTimeoutConstant = 10;
   
   // CBR_9600 is approximately 1byte/ms. For our purposes, allow
   // double the expected time per character for a fudge factor.
   CommTimeOuts.WriteTotalTimeoutMultiplier = 2*CBR_9600/CBR_9600;
   CommTimeOuts.WriteTotalTimeoutConstant = 0;

   SetCommTimeouts( pPort->hPort, &CommTimeOuts );
   
   dcb.DCBlength = sizeof( DCB ) ;
   
   GetCommState( pPort->hPort, &dcb ) ;
   
   dcb.BaudRate   = CBR_9600;
   dcb.ByteSize   = 8;
   dcb.Parity     = NOPARITY;
   dcb.StopBits   = TWOSTOPBITS;
   
   // other various settings   
   dcb.fBinary    = FALSE;
   dcb.fParity    = FALSE;
   
   SetCommState( pPort->hPort, &dcb ) ;

   return TRUE;
}

//------------------------------------------------------------------------------------------------
BOOL __stdcall COM_Close( LPT_Port pPort )
{
//   CHAR        achCommand[ 100 ];
   if ( pPort->hPort == NULL )
      return TRUE;

//   strcpy( achCommand, "SYST:BEEP;DISP OFF;DISP:TEXT \"The End.\"\n" );
//   if ( !WriteFile( meter->hDevice, achCommand, strlen( achCommand ), &g_dwBytes, NULL ) )
//      return FALSE;

   // purge any outstanding reads/writes and close device handle
   
   PurgeComm( pPort->hPort, PURGE_TXABORT | PURGE_RXABORT |
      PURGE_TXCLEAR | PURGE_RXCLEAR ) ;
  
   if ( !CloseHandle( pPort->hPort ) )
      return FALSE;
   
   pPort->hPort = NULL;

   return TRUE;
}

//------------------------------------------------------------------------------------------------
DWORD __stdcall COM_Write( HANDLE hComm, CHAR* pBuffer, DWORD dwLen )
{
   DWORD dwBytesWrite;
   DWORD dwError;
   COMSTAT cs;
   DWORD dwCommError;
   PurgeComm( hComm, PURGE_RXABORT | PURGE_TXABORT | PURGE_RXCLEAR | PURGE_TXCLEAR );
   
   if ( WriteFile( hComm, pBuffer, dwLen, &dwBytesWrite, NULL ) == 0 )
   {
      dwError = GetLastError();
      
      ClearCommError( hComm, &dwCommError, &cs );
   }
   
   if ( dwBytesWrite != dwLen )
      return -1;
   
   return dwBytesWrite;
   
}

//------------------------------------------------------------------------------------------------
DWORD __stdcall COM_Read(HANDLE hComm, CHAR* pBuffer, DWORD dwTimeout)
{
   DWORD dwTemp = 0x50e;
   DWORD dwBytesRead;
   DWORD dwError;
   DWORD dwBytesReadTotal;
   COMSTAT cs;
   DWORD dwCommError;
   DWORD dwLen = 0;
   BYTE input = '\x0';
   DWORD read = 0;
   DWORD dwTicks;
   
   dwTicks = GetTickCount();
   
   while ( 1 )
   {
      if ( ( dwLen > 2 ) && ( pBuffer[ dwLen - 1 ] == '\xa' )
         && ( pBuffer[ dwLen - 2 ] == '\xd' ) )
      {
         break;
      }
      if ( GetTickCount() - dwTicks >= dwTimeout )
         break;
      
      if( !ReadFile( hComm, &input, 1, &read, NULL ) || ( read != 1 ) )
      {
         dwLen = 0;
         dwError = GetLastError();
         ClearCommError( hComm, &dwCommError, &cs );
         break;
      }
      
      pBuffer[ dwLen++ ] = input;
   }
   
   pBuffer[ dwLen ] = '\x0';
   
   return dwLen;
}

//------------------------------------------------------------------------------------------------
