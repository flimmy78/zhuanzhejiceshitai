// #########################################################################
// *************************************************************************
//                     Copyright (C) 2002-2020.
//   THIS IS AN UNPUBLISHED WORK CONTAINED CONFIDENTIAL, AND PROPRIETARY
//              INFORMATION WHICH IS THE PROPERTY OF TangBo.
// ANY DISCLOSURE, USE, OR REPRODUCTION, WITHOUT WRITTEN AUTHORIZATION FROM
//                        TangBo, IS STRICT.
// #########################################################################
// *************************************************************************

#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>
#include <objbase.h>
#include "COMM.h"
#include "Device.h"
#include "DAQDefine.h"

//------------------------------------------------------------------------------------------------
extern BYTE CRCHI[];
extern BYTE CRCLO[];
//------------------------------------------------------------------------------------------------
extern PT_DAQSystemData g_DAQSystemData;
extern PT_Meter         g_Meters[MAX_METERS];
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void ModBus_Clear(LPT_Message pMsg)
{
   pMsg->ok = FALSE;
   memset(pMsg->buffer, 0, sizeof(pMsg->buffer));
   pMsg->length = 0;
//   CoFileTimeNow(&pMsg->timestamp);
}

//------------------------------------------------------------------------------------------------
// Build a message by adding bytes sequentially
void ModBus_Add(LPT_Message pMsg, BYTE byte)
{
   pMsg->buffer[pMsg->length++] = byte;
}

//------------------------------------------------------------------------------------------------
// Build a message by adding bytes sequentially
void ModBus_AddAsByte(LPT_Message pMsg, BYTE byte)
{
   pMsg->buffer[pMsg->length++] = byte;
}

//------------------------------------------------------------------------------------------------
FLOAT ModBus_GetFloat(LPT_Message pMsg, int offset)
{
   DOUBLE fData;
   FLOAT FData[10];

   if (offset > 5)
      return 0.0;
   
   // Check Len
   if (pMsg->buffer[2] != 0x0a)
      return 0.0;
   
   FData[0] = (FLOAT)(pMsg->buffer[4] | (pMsg->buffer[3] << 8));
   FData[1] = (FLOAT)((signed short)(pMsg->buffer[6] | (pMsg->buffer[5] << 8)));
   FData[2] = (FLOAT)(pMsg->buffer[8] | (pMsg->buffer[7] << 8));
   FData[3] = (FLOAT)(pMsg->buffer[10] | (pMsg->buffer[9] << 8));
   FData[4] = (FLOAT)(pMsg->buffer[12] | (pMsg->buffer[11] << 8));
      
   fData = FData[1];
            
   if (FData[2] == 0)
      fData /= 1.0;
   else if (FData[2] == 1)
      fData /= 10.0;
   else if (FData[2] == 2)
      fData /= 100.0;
   else if (FData[2] == 3)
      fData /= 1000.0;
   else if (FData[2] == 4)
      fData /= 10000.0;
      
   if (FData[3] == 0)
      fData *= 1e-12;
   else if (FData[3] == 1)
      fData *= 1e-9;
   else if (FData[3] == 2)
      fData *= 1e-6;
   else if (FData[3] == 3)
      fData *= 1e-3;
   else if (FData[3] == 4)
      fData *= 1e-0;
   else if (FData[3] == 5)
      fData *= 1e+3;
   else if (FData[3] == 6)
      fData *= 1e+6;
   else if (FData[3] == 7)
      fData *= 1e+9;
      
   FData[5] = (float)fData;
   
   return fData;   
}

//------------------------------------------------------------------------------------------------
WORD ModBus_GetWord(LPT_Message pMsg, int offset)
{
   WORD fData;

   if (offset > 5)
      return 0;
   
   // Check Len
   if (pMsg->buffer[2] != 0x0a)
      return 0.0;
   
   fData = (WORD)(pMsg->buffer[4 + offset * 2] | (pMsg->buffer[3 + offset * 2] << 8));

   return fData;   
}

//------------------------------------------------------------------------------------------------
void ModBus_Finish(LPT_Message pMsg)
{
   // compute the CRC and insert it
   BYTE hi = 0xFF;
   BYTE lo = 0xFF;
   int count;
   UINT index;
   for (count = 0; count < pMsg->length; count ++)
   {
      index = hi ^ pMsg->buffer[count];
      hi = lo ^ CRCHI[index];
      lo = CRCLO[index];
   }
   
   pMsg->buffer[pMsg->length++] = hi;
   pMsg->buffer[pMsg->length++] = lo;
}

//------------------------------------------------------------------------------------------------
BOOL ModBus_MsgDone(LPT_Message pMsg)
{
   if( pMsg->length < 4 )  // minimum length
      return FALSE;
   
   if( pMsg->buffer[1] & 0x80 )  // error bit in function code
      if( pMsg->length == 5 )
         return TRUE;
      else
         return FALSE;
      
      switch( pMsg->buffer[1] & 0x7F ) // regular function code
      {
      case 1:
      case 2:
      case 3:
      case 4:
      case 12:
      case 17:
      case 20:
      case 21:
         if( pMsg->length == pMsg->buffer[2]+5 )
            return TRUE;
         break;
         
      case 5:
      case 6:
      case 11:
      case 15:
      case 16:
         if( pMsg->length == 8 )
            return TRUE;
         break;
      case 7:
         if( pMsg->length == 5 )
            return TRUE;
         break;
      case 22:
         if( pMsg->length == 10 )
            return TRUE;
         break;
      }
      return FALSE;
}

//------------------------------------------------------------------------------------------------
// check the validity of a message
BOOL ModBus_IsOk(LPT_Message pMsg)
{   
   int count;
   UINT index;
   BYTE hi = 0xFF;
   BYTE lo = 0xFF;
   if( !pMsg->ok )
      return FALSE;
   
   if (pMsg->length < 4)  // minimum is < addr func crc>
      return FALSE;
   // check error bit in function
   if (pMsg->buffer[1] & 0x80)
   {
      return FALSE;
   }
   
   // compute the CRC and compare with the message
   for (count = 0; count < pMsg->length - 2; count ++)
   {
      index = hi ^ pMsg->buffer[count];
      hi = lo ^ CRCHI[index];
      lo = CRCLO[index];
   }
   if (pMsg->buffer[pMsg->length - 2] != hi || pMsg->buffer[pMsg->length - 1] != lo)
   {
      return FALSE;
   }
   
   return TRUE;
}

//------------------------------------------------------------------------------------------------
BOOL ModBus_Message(LPT_Port port, LPT_Message msg, BOOL onlywrite)
{
   DWORD written = 0;
   DWORD read = 0;
   BYTE input = 0;

   PurgeComm(port->hPort, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
//   ClearCommError(hPort,)
   if (!WriteFile(port->hPort, msg->buffer, msg->length, &written, NULL))
   {
      ModBus_Clear(msg);
      return FALSE;
   }
   if (msg->length != written)
   {
      ModBus_Clear(msg);
      return FALSE;
   }

   ModBus_Clear(msg);
   read = 0;
   
   while (!ModBus_MsgDone(msg))
   {
      if (!ReadFile(port->hPort, &input, 1, &read, NULL) || (read != 1))
      {
         return FALSE;
      }
      msg->buffer[msg->length++] = input;
   }
   
//   CoFileTimeNow(&msg->timestamp);
   msg->ok = TRUE;
   
   return TRUE;
}

//------------------------------------------------------------------------------------------------
void ModBus_CreateReadPacket(LPT_Meter meter, LPT_Message msg)
{
   ModBus_Clear(msg);
   ModBus_Add(msg, meter->cAddr);
   ModBus_Add(msg, FN_READ_HOLDING_REGS);
   ModBus_Add(msg, HIBYTE(1 - 1));
   ModBus_Add(msg, LOBYTE(1 - 1));
   ModBus_Add(msg, HIBYTE(5));
   ModBus_Add(msg, LOBYTE(5));
   ModBus_Finish(msg);
   msg->ok = TRUE;
}

//------------------------------------------------------------------------------------------------
int Meter_Read_IR(float* pData)
{
   PT_Message msg;
   int tries;
   LPT_Meter  meter;
   
   meter = &g_Meters[METER_IR];
   if (!meter->bUsed)
      return -1;
         
   Port_Initialize(meter->pPort);
         
   // Read data
   tries = 0;
   while (tries ++ < 3)
   {
      // Create Packet
      ModBus_CreateReadPacket(meter, &msg);
            
      // send the message to the port and get response
      ModBus_Message(meter->pPort, &msg, FALSE);
      if (ModBus_IsOk(&msg))
         break;
      Sleep( 100 );
   }
   if (ModBus_IsOk(&msg))
   {
      meter->sTag.fData = ModBus_GetFloat(&msg, 0);
      meter->sTag.wFlag = ModBus_GetWord(&msg, 4);
      if (pData)*pData = meter->sTag.fData;
   }
   else
   {
      meter->sTag.fData = -1.0;
      if (pData)*pData = meter->sTag.fData;
      return -1;
   }
      
   return 0;
}

//------------------------------------------------------------------------------------------------
int Meter_Read(LPT_Meter meter)
{
   switch (meter->cAddr)
   {
   case ADDR_IR:
      if (Meter_Read_IR (NULL))
         return -1;
      break;
   default:
      return -1;
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
DWORD WINAPI ThreadRoutine_Meter(DWORD arg)
{
   PT_Message msg;
   WORD tries = 0;
   MSG Msg;
   int i;
   while (g_DAQSystemData.ThreadLoop_Meter)
   {
      if (PeekMessage (&Msg, 0, 0, 0, PM_REMOVE))
      {
         TranslateMessage (&Msg);
         DispatchMessage (&Msg);
      }
      Sleep (500);
      
//      if (g_DAQSystemData.AutoTesting)
//         continue;
      
      Meter_Read_IR (NULL);
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
BOOL __stdcall Meter_CreateThread( void )
{
   // Enable thread loop
   g_DAQSystemData.ThreadLoop_Meter = TRUE;

   // Crate Device Test thread
   g_DAQSystemData.ThreadHandle_Meter = CreateThread(NULL, 0, 
      (LPTHREAD_START_ROUTINE)&ThreadRoutine_Meter, NULL, 0, NULL);
   if ( g_DAQSystemData.ThreadHandle_Meter == NULL )
      return FALSE;

   return TRUE;
}
                       
//------------------------------------------------------------------------------------------------
BOOL __stdcall Meter_TerminateThread( void )
{
   // Disable thread loop
   g_DAQSystemData.ThreadLoop_Meter = FALSE;
   
   // Terminate the thread
   WaitForSingleObject(g_DAQSystemData.ThreadHandle_Meter, 5000);
   CloseHandle (g_DAQSystemData.ThreadHandle_Meter);
   g_DAQSystemData.ThreadHandle_Meter = NULL;
   
   return TRUE;
}
//------------------------------------------------------------------------------------------------
