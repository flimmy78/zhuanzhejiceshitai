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
extern PT_Port        g_Ports[4];
extern PT_DAQSystemData  g_DAQSystemData;
extern PT_PLC         g_Fx2n;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void FX2N_InitAIOTagList(LPT_Tag pTag, WORD off, WORD len, float k, float b, BOOL skip, char* name)
{
   pTag->address = 'D';
   pTag->offset = off;
   pTag->bit = 0;
   pTag->k = k;
   pTag->b = b;
   pTag->length = len;
   strcpy(pTag->name, name);
   pTag->enable = TRUE;
   pTag->skip = skip;
}
//------------------------------------------------------------------------------------------------
void FX2N_InitDIOTagList(LPT_Tag pTag, WORD off, BOOL skip, char* name)
{
   pTag->address = 'M';
   pTag->offset = off / 8;
   pTag->bit = off % 8;
   pTag->length = 1;
   strcpy(pTag->name, name);
   pTag->enable = TRUE;
   pTag->skip = skip;
}

//------------------------------------------------------------------------------------------------
void FX2N_InitTagList(void)
{
   int   nIndex;
    
   memset(&g_Fx2n.sAIOTag, 0, sizeof(g_Fx2n.sAIOTag));
   memset(&g_Fx2n.sDIOTag, 0, sizeof(g_Fx2n.sDIOTag));
    
   nIndex = 0;   
//    FX2N_InitAIOTagList(&g_Fx2n.sAIOTag[nIndex ++], AO_T, 2, 0.1, 0.0, "温度设定");
   FX2N_InitAIOTagList(&g_Fx2n.sAIOTag[nIndex ++], AI_TRAVEL_TIME_A, 2, 1000.0, 0.0,FALSE, "A方向转换时间");// A方向转换时间D100  B方向转换时间D101   单位1ms
   FX2N_InitAIOTagList(&g_Fx2n.sAIOTag[nIndex ++], AI_TRAVEL_TIME_B, 2, 1000.0, 0.0,FALSE, "B方向转换时间");// A方向转换时间D100  B方向转换时间D101   单位1ms
       
   nIndex = 0;   
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DI_X000, FALSE, "1H状态");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DI_X001, FALSE, "2H状态");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DI_X002, FALSE, "3H状态");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DI_X003, FALSE, "4H状态");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DI_X004, FALSE, "200");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DI_X005, FALSE, "Y001");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DI_X006, FALSE, "Y002");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DI_X007, FALSE, "Y003");
   
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DO_KA01, TRUE, "400");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DO_KA02, TRUE, "Y001");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DO_KA03, TRUE, "Y002");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DO_KA04, TRUE, "Y003");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DO_KA05, TRUE, "Y004");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DO_KA06, TRUE, "Y005");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DO_KA07, TRUE, "Y006");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DO_KA08, TRUE, "Y007");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DO_KA09, TRUE, "220");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DO_KA10, TRUE, "224");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DO_KA11, TRUE, "1Q状态");
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DO_KA12, TRUE, "2Q状态");
   
   FX2N_InitDIOTagList(&g_Fx2n.sDIOTag[nIndex ++], DO_CLEARDATA, TRUE, "2Q状态");
}

//------------------------------------------------------------------------------------------------
void FX2N_Clear(LPT_Message pMsg)
{
   pMsg->ok = FALSE;
   memset(pMsg->buffer, 0, sizeof(pMsg->buffer));
   pMsg->length = 0;
}

//------------------------------------------------------------------------------------------------
// Build a message by adding bytes sequentially
void FX2N_Add(LPT_Message pMsg, BYTE byte)
{
   // convert value to 2 char hex number
   if ((byte >> 4) > 9)
      pMsg->buffer[pMsg->length++] = 'A' + (byte >> 4) - 10;
   else
      pMsg->buffer[pMsg->length++] = '0' + (byte >> 4);
   
   if ((byte & 0x0f) > 9)
      pMsg->buffer[pMsg->length++] = 'A' + (byte & 0x0f) - 10;
   else
      pMsg->buffer[pMsg->length++] = '0' + (byte & 0x0f);
}

//------------------------------------------------------------------------------------------------
BYTE Char2Byte(CHAR c)
{
   if ((c <= '9') && (c >= '0'))
      return c - '0';
   else if ((c <= 'F') && (c >= 'A'))
      return c - 'A' + 10;
   else
      return -1;
}

//------------------------------------------------------------------------------------------------
BOOL FX2N_GetBit(LPT_Message pMsg, int offset, int bit)
{   
   WORD  dataLength;
   BYTE value;
   BOOL discrete;
   dataLength = pMsg->length - 4;
   if (dataLength > 1)
      dataLength >>= 1;  // Get bytes count
    
   value = Char2Byte(pMsg->buffer[offset * 2 + 1]);
   value <<= 4;
   value |= Char2Byte(pMsg->buffer[offset * 2 + 2]);

   discrete =  value & (1<<bit);
   return (discrete > 0 ); // variant bool values, not TRUE/FALSE
}

//------------------------------------------------------------------------------------------------
WORD FX2N_GetWord(LPT_Message pMsg, int offset)
{
   WORD  dataLength;
   WORD value;
   dataLength = pMsg->length - 4;
   dataLength >>= 1;  // Get bytes count

   value = Char2Byte(pMsg->buffer[offset * 4 + 3]);
   value <<= 4;
   value |= Char2Byte(pMsg->buffer[offset * 4 + 4]);
   value <<= 4;
   value |= Char2Byte(pMsg->buffer[offset * 4 + 1]);
   value <<= 4;
   value |= Char2Byte(pMsg->buffer[offset * 4 + 2]);

   return value;
}

//------------------------------------------------------------------------------------------------
DWORD FX2N_GetDWord(LPT_Message pMsg, int offset)
{
   WORD  dataLength;
   DWORD value;
   dataLength = pMsg->length - 4;
   dataLength >>= 1;  // Get bytes count

   value = Char2Byte(pMsg->buffer[offset * 4 + 7]);
   value <<= 4;
   value |= Char2Byte(pMsg->buffer[offset * 4 + 8]);
   value <<= 4;
   value |= Char2Byte(pMsg->buffer[offset * 4 + 5]);
   value <<= 4;
   value |= Char2Byte(pMsg->buffer[offset * 4 + 6]);
   value <<= 4;
   value |= Char2Byte(pMsg->buffer[offset * 4 + 3]);
   value <<= 4;
   value |= Char2Byte(pMsg->buffer[offset * 4 + 4]);
   value <<= 4;
   value |= Char2Byte(pMsg->buffer[offset * 4 + 1]);
   value <<= 4;
   value |= Char2Byte(pMsg->buffer[offset * 4 + 2]);
   
   return value;
}

//------------------------------------------------------------------------------------------------
float FX2N_GetFloat(LPT_Message pMsg, int offset)
{
    WORD dataLength;
    DWORD value;
    float* fValue;
    dataLength = pMsg->length - 4;
    dataLength >>= 1;  // Get bytes count

    value = Char2Byte(pMsg->buffer[offset * 4 + 7]);
    value <<= 4;
    value |= Char2Byte(pMsg->buffer[offset * 4 + 8]);
    value <<= 4;
    value |= Char2Byte(pMsg->buffer[offset * 4 + 5]);
    value <<= 4;
    value |= Char2Byte(pMsg->buffer[offset * 4 + 6]);
    value <<= 4;
    value |= Char2Byte(pMsg->buffer[offset * 4 + 3]);
    value <<= 4;
    value |= Char2Byte(pMsg->buffer[offset * 4 + 4]);
    value <<= 4;
    value |= Char2Byte(pMsg->buffer[offset * 4 + 1]);
    value <<= 4;
    value |= Char2Byte(pMsg->buffer[offset * 4 + 2]);
    
    fValue = (float*)&value;

    return *fValue;
}

//------------------------------------------------------------------------------------------------
// Build a message by adding bytes sequentially
void FX2N_AddAsByte(LPT_Message pMsg, BYTE byte )
{
   pMsg->buffer[pMsg->length++] = byte;
}

//------------------------------------------------------------------------------------------------
void FX2N_Finish(LPT_Message pMsg)
{
   // compute the CRC and insert it
   BYTE sum = 0;
   int count;
   FX2N_AddAsByte(pMsg, ETX);
   for (count = 1; count < pMsg->length; count++)
   {
      sum += pMsg->buffer[count];
   }   
   FX2N_Add(pMsg, sum);
}

//------------------------------------------------------------------------------------------------
BOOL FX2N_MsgDone(LPT_Message pMsg)
{
   if (pMsg->length < 1)  // minimum length
      return FALSE;
   if (pMsg->buffer[0] == ACK)
      return TRUE;
   if (pMsg->buffer[0] == NAK)
      return TRUE;

   if (pMsg->buffer[0] != STX)
      return FALSE;

   if (pMsg->length < 4)
      return FALSE;

   if (pMsg->buffer[pMsg->length - 3] == ETX )
      return TRUE;

   return FALSE;
}

//------------------------------------------------------------------------------------------------
// check the validity of a message
BOOL FX2N_IsOk(LPT_Message pMsg)
{   
   char buf[18];
   BYTE sum = 0;
   int count;
   if (!pMsg->ok)
      return FALSE;
    
   if (pMsg->length < 1)  // minimum is < addr func crc>
      return FALSE;

   // Only sample ACK
   if (pMsg->buffer[0] == ACK)
      return TRUE;
   if (pMsg->buffer[0] == NAK)
      return TRUE;

   if (pMsg->buffer[0] != STX)
      return FALSE;

   if (pMsg->length < 4)
      return FALSE;

   if (pMsg->buffer[pMsg->length - 3] != ETX )
      return FALSE;

   for (count = 1; count < pMsg->length - 2; count++)
      sum += pMsg->buffer[count];

   // convert value to 2 char hex number
   if ((sum >> 4) > 9)
      buf[0] = 'A' + (sum >> 4) - 10;
   else
      buf[0] = '0' + (sum >> 4);
    
   if ((sum & 0x0f) > 9)
      buf[1] = 'A' + (sum & 0x0f) - 10;
   else
      buf[1] = '0' + (sum & 0x0f);
    
   // compute the CRC and compare with the message
   if (pMsg->buffer[pMsg->length - 2] != buf[0] || pMsg->buffer[pMsg->length - 1] != buf[1])
   {      
      return FALSE;
   }
    
   return TRUE;
}

//------------------------------------------------------------------------------------------------
void FX2N_CreateReadPacket(LPT_Tag pTag, LPT_Message msg, BYTE size)
{
   DWORD  dwAddr;
   FX2N_Clear(msg);
    
   FX2N_AddAsByte(msg, STX);
   FX2N_AddAsByte(msg, 'E');    // 0x45
   FX2N_AddAsByte(msg, FN_DEVICE_READ);
   FX2N_AddAsByte(msg, '0');   //  0x30
   switch(pTag->address)
   {
   case 'M':
      dwAddr = pTag->offset;
      FX2N_Add(msg, HIBYTE(dwAddr));
      FX2N_Add(msg, LOBYTE(dwAddr));
         
      FX2N_Add(msg, (BYTE)size); // 0x31, Length 8 bits
      break;
   case 'D':
      dwAddr = pTag->offset * 2 + 0x4000;
      FX2N_Add(msg, HIBYTE(dwAddr));
      FX2N_Add(msg, LOBYTE(dwAddr));
      FX2N_Add(msg, (BYTE)size); // 0x30 0x32, Length 16 bits
      break;
   }
   FX2N_Finish(msg);
    
   msg->ok = TRUE;
}

//------------------------------------------------------------------------------------------------
BOOL FX2N_Message(LPT_Port port, LPT_Message msg, BOOL onlywrite)
{
   DWORD written = 0;
   DWORD read = 0;
   BYTE input = 0;

   PurgeComm(port->hPort, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
//  ClearCommError(hPort,)
   if (!WriteFile(port->hPort, msg->buffer, msg->length, &written, NULL))
   {
      FX2N_Clear(msg);
      return FALSE;
   }
   if (msg->length != written)
   {
      FX2N_Clear(msg);
      return FALSE;
   }

   FX2N_Clear(msg);
   read = 0;
    
   while (!FX2N_MsgDone(msg))
   {
      if (!ReadFile(port->hPort, &input, 1, &read, NULL) || (read != 1))
      {
         return FALSE;
      }
      msg->buffer[msg->length++] = input;
   }
    
//  CoFileTimeNow(&msg->timestamp);
   msg->ok = TRUE;
    
   return TRUE;
}

//------------------------------------------------------------------------------------------------
int FX2N_Read_AIO(void)
{
   PT_Message msg;
   WORD tries;
   WORD pos;
   WORD groupSize;
   WORD groupStart;
   WORD IndexSize;
   BOOL done;
   int count;
   LPT_Tag pTag;
   LPT_Tag pNextTag;
   float fData = 0;
    
   // for each tag in the list
   pos = 0;
   while (pos < MAX_AIOTAGS && g_Fx2n.sAIOTag[pos].enable)
   {
      IndexSize = 1;
         
      // maybe reuse a msg, instead of new/delete each time
      pTag = &g_Fx2n.sAIOTag[pos];
         
      // search for tags to group with this one
      done = FALSE;
      count = 1;
      groupSize = 0;
      groupStart = pTag->offset;
         
      // Initial group size.
      groupSize = pTag->length;
         
      while ((pos + IndexSize < MAX_AIOTAGS - 1) && !done)
      {
         pNextTag = &g_Fx2n.sAIOTag[pos + IndexSize];
             
             // Can this tag be combined in a message?
             if (((pNextTag->offset - groupStart) < 32)
                  && (pNextTag->offset >= pTag->offset)
                  && pNextTag->enable)
             {
                  groupSize = (pNextTag->offset - groupStart) * 2 + pNextTag->length;
                  IndexSize ++;
             }
             else
             {
                  done = TRUE;
             }
         }
         
         Port_Initialize(g_Fx2n.pPort);
             
         // Read data
         tries = 0;
         EnterCriticalSection(&g_Fx2n.pPort->tagCS);
         while (tries ++ < 3)
         {
             // Create Packet
             FX2N_CreateReadPacket(&g_Fx2n.sAIOTag[pos], &msg, (BYTE)groupSize);
             INFO1("  读取转辙机动作时间,发送缓冲区：%s,长度：%d,isOk,%d",msg.buffer,msg.length,msg.ok);
             // send the message to the port and get response
             FX2N_Message(g_Fx2n.pPort, &msg, FALSE);
			 
             if (FX2N_IsOk(&msg)){
				 INFO1("                     接收缓冲区：%s,长度：%d,isOk,yes",msg.buffer,msg.length);
                  break;
			 }
             Sleep(10);
         }   
         LeaveCriticalSection(&g_Fx2n.pPort->tagCS);
         
         if (FX2N_IsOk(&msg))
         {
             for (count = 0; count < IndexSize; count++)
             {
                  if (g_Fx2n.sAIOTag[pos + count].length == 2)
                     fData = FX2N_GetWord(&msg, g_Fx2n.sAIOTag[pos + count].offset - groupStart);
                  if (g_Fx2n.sAIOTag[pos + count].length == 4)
                     fData = FX2N_GetFloat (&msg, g_Fx2n.sAIOTag[pos + count].offset - groupStart);
                  
                  fData = fData * g_Fx2n.sAIOTag[pos + count].k + g_Fx2n.sAIOTag[pos + count].b;
                  g_Fx2n.sAIOTag[pos + count].fData = fData;
				  INFO1("                     值：%f",fData);
             }
         }
         else
         {
             for (count = 0; count < IndexSize; count++)
                  g_Fx2n.sAIOTag[pos + count].fData = -0.000000001;
             
             return -1;
         }
         pos += IndexSize;
    }
    return 0;
}

//------------------------------------------------------------------------------------------------
int FX2N_Read_DIO(void)
{
    PT_Message msg;
    WORD tries;
    WORD pos;
    WORD groupSize;
    WORD groupStart;
    WORD IndexSize;
    BOOL done;
    
    int count;
    LPT_Tag pTag;
    LPT_Tag pNextTag;
    
    // for each tag in the list
    pos = 0;
    while (pos < MAX_DIOTAGS && g_Fx2n.sDIOTag[pos].enable)
    {
         IndexSize = 1;
         
         // maybe reuse a msg, instead of new/delete each time
         pTag = &g_Fx2n.sDIOTag[pos];
         
         // search for tags to group with this one
         done = FALSE;
         count = 1;
         groupSize = 0;
         groupStart = pTag->offset;
         
         // Initial group size.
         groupSize = pTag->length;
         
         while ((pos + IndexSize < MAX_DIOTAGS - 1) && !done)
         {
             pNextTag = &g_Fx2n.sDIOTag[pos + IndexSize];
             
             // Can this tag be combined in a message?
             if (((pNextTag->offset - groupStart) < 32)
                  && (pNextTag->offset >= pTag->offset)
                  && pNextTag->enable)
             {
                  if (groupSize < (pNextTag->offset - pTag->offset) + pNextTag->length)
                      groupSize = (pNextTag->offset - groupStart) + pNextTag->length;
                  IndexSize ++;
             }
             else
             {
                  done = TRUE;
             }
         }
         
         Port_Initialize(g_Fx2n.pPort);
             
         // Read data
         tries = 0;
         EnterCriticalSection(&g_Fx2n.pPort->tagCS);
         while (tries ++ < 3)
         {
             // Create Packet
             FX2N_CreateReadPacket(&g_Fx2n.sDIOTag[pos], &msg, (BYTE)groupSize);
             
             // send the message to the port and get response
             FX2N_Message(g_Fx2n.pPort, &msg, FALSE);
             if (FX2N_IsOk(&msg))
                  break;
             Sleep(10);
         }   
         LeaveCriticalSection(&g_Fx2n.pPort->tagCS);
         
         if (FX2N_IsOk(&msg))
         {
             for (count = 0; count < IndexSize; count++)
                  g_Fx2n.sDIOTag[pos + count].bData = FX2N_GetBit(&msg, g_Fx2n.sDIOTag[pos + count].offset - groupStart, g_Fx2n.sDIOTag[pos + count].bit);
         }
         else
         {
             for (count = 0; count < IndexSize; count++)
                  g_Fx2n.sDIOTag[pos + count].bData = 0;
             
             return -1;
         }
         pos += IndexSize;
    }
    return 0;
}

//------------------------------------------------------------------------------------------------
void FX2N_CreateWritePacket(LPT_Tag pTag, LPT_Message msg)
{
    DWORD data;
    DWORD  dwAddr;
    FX2N_Clear(msg);
    FX2N_AddAsByte(msg, STX);
    FX2N_AddAsByte(msg, 'E');    // 0x45
    switch(pTag->address)
    {
    case 'M':
         data = pTag->wData;
         if (data == 0)
             FX2N_AddAsByte(msg, FN_FORCE_OFF);
         else
             FX2N_AddAsByte(msg, FN_FORCE_ON);
         dwAddr = pTag->offset;
         dwAddr *= 8;
         dwAddr += pTag->bit;
         FX2N_Add(msg, LOBYTE(dwAddr));
         FX2N_Add(msg, HIBYTE(dwAddr));
         break;
    case 'D':
         data = pTag->wData;
         FX2N_AddAsByte(msg, FN_DEVICE_WRITE);
         FX2N_AddAsByte(msg, '0');    // 0x30
         dwAddr = pTag->offset * 2 + 0x4000;
         FX2N_Add(msg, HIBYTE(dwAddr));
         FX2N_Add(msg, LOBYTE(dwAddr));
       if (pTag->length == 2)
       {
            FX2N_Add(msg, 2); // 0x30 0x32, Length 16 bits
            FX2N_Add(msg, LOBYTE(data));
            FX2N_Add(msg, HIBYTE(data));
       }
       if (pTag->length == 4)
       {
            FX2N_Add(msg, 4); // 0x30 0x32, Length 16 bits
            FX2N_Add(msg, LOBYTE(LOWORD(data)));
            FX2N_Add(msg, HIBYTE(LOWORD(data)));
            FX2N_Add(msg, LOBYTE(HIWORD(data)));
            FX2N_Add(msg, HIBYTE(HIWORD(data)));
       }
         break;
    }
    
    FX2N_Finish(msg);
    msg->ok = TRUE;
}

//------------------------------------------------------------------------------------------------
BOOL FX2N_WriteTag(LPT_Tag pTag)
{
    UINT data;
    BOOL ret = FALSE;
    WORD dwAddr;
    WORD tries;
    
    PT_Message msg;
    
    Port_Initialize(g_Fx2n.pPort);
    
    tries = 0;
    EnterCriticalSection(&g_Fx2n.pPort->tagCS);
    while (tries ++ < 3)
    {
         FX2N_CreateWritePacket(pTag, &msg);
         FX2N_Message(g_Fx2n.pPort, &msg, FALSE);
         if (FX2N_IsOk(&msg))
             break;
         Sleep(10);
    }
    LeaveCriticalSection(&g_Fx2n.pPort->tagCS);
    if (FX2N_IsOk(&msg))
    {
         ret = TRUE;
    }
    else
    {
         ret = FALSE;
    }
    return ret;
}

//------------------------------------------------------------------------------------------------
DWORD WINAPI ThreadRoutine_PLC(DWORD arg)
{
   PT_Message msg;
   MSG Msg;
   WORD tries = 0;
   int i;
   while (g_DAQSystemData.ThreadLoop_PLC)
   {
      if (PeekMessage (&Msg, 0, 0, 0, PM_REMOVE))
      {
         TranslateMessage (&Msg);
         DispatchMessage (&Msg);
      }
         
      Sleep(500);
      FX2N_Read_AIO ();
      FX2N_Read_DIO ();
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
BOOL __stdcall CreateThread_PLC( void )
{
   FX2N_InitTagList ();
   // Enable thread loop
   g_DAQSystemData.ThreadLoop_PLC = TRUE;

   // Crate Device Test thread
   g_DAQSystemData.ThreadHandle_PLC = CreateThread (NULL, 0, 
      (LPTHREAD_START_ROUTINE)&ThreadRoutine_PLC, NULL, 0, NULL);
   if (g_DAQSystemData.ThreadHandle_PLC == NULL)
      return FALSE;

   return TRUE;
}
                                  
//------------------------------------------------------------------------------------------------
BOOL __stdcall TerminateThread_PLC( void )
{
    // Disable thread loop
    g_DAQSystemData.ThreadLoop_PLC = FALSE;
    
    // Terminate the thread
    WaitForSingleObject(g_DAQSystemData.ThreadHandle_PLC, 5000);
    CloseHandle (g_DAQSystemData.ThreadHandle_PLC);
    g_DAQSystemData.ThreadHandle_PLC = NULL;
    
    return TRUE;
}

//------------------------------------------------------------------------------------------------
LPT_Tag FX2N_FindTag(WORD wAddr, SHORT sType)
{
   int i;

   if (sType == 1)
      for (i = 0; i < MAX_AIOTAGS; i ++)
      {
         if (wAddr == g_Fx2n.sAIOTag[i].offset)
            return &g_Fx2n.sAIOTag[i];
      }
    
   if (sType == 2)
   for (i = 0; i < MAX_DIOTAGS; i ++)
   {
      if ((wAddr / 8 == g_Fx2n.sDIOTag[i].offset) && (wAddr % 8 == g_Fx2n.sDIOTag[i].bit))
         return &g_Fx2n.sDIOTag[i];
   }
   return NULL;
}

//------------------------------------------------------------------------------------------------
BOOL FX2N_GetStatus(WORD wAddr)
{
    int i;
    LPT_Tag pTag;
    
    pTag = FX2N_FindTag(wAddr, 2);
    
    if (pTag == NULL)
         return 0;
    
    return pTag->bData;
}

//------------------------------------------------------------------------------------------------
float FX2N_GetData(WORD wAddr)
{
    int i;
    LPT_Tag pTag;
    
    pTag = FX2N_FindTag(wAddr, 1);
    
    if (pTag == NULL)
         return 0.0;
    
    return pTag->fData;
}


//------------------------------------------------------------------------------------------------
BOOL FX2N_RawOut(WORD wAddr, WORD wData)
{
    LPT_Tag  pTag;
    BOOL ret = TRUE;
    
    pTag = FX2N_FindTag(wAddr, 1);
    if (!pTag)
         return FALSE;
    
    SetWaitCursor(1);
    
    pTag->wData = wData;
    ret = FX2N_WriteTag(pTag);
    SetWaitCursor(0);
    
    return ret;
}

//------------------------------------------------------------------------------------------------
BOOL FX2N_ClearData(void)
{
    LPT_Tag  pTag;
    BOOL ret = TRUE;
    
    pTag = FX2N_FindTag(DO_CLEARDATA, 2);
    if (!pTag)
         return FALSE;
    
    SetWaitCursor(1);
    pTag->wData = 1;
    ret = FX2N_WriteTag(pTag);
    SetWaitCursor(0);
    
    return ret;
}

//------------------------------------------------------------------------------------------------
BOOL FX2N_DOControl(WORD wAddr, WORD wData)
{
   LPT_Tag  pTag;
   BOOL ret = TRUE;
    
   pTag = FX2N_FindTag(wAddr, 2);
    
   if (!pTag)
   {
      MessagePopup ("错误", "指定地址无法找到!");
      return FALSE;
   }
    
    SetWaitCursor(1);
    pTag->wData = wData;
    pTag->bData = wData == 1;
    pTag->fData = wData;
    ret = FX2N_WriteTag(pTag);
    SetWaitCursor(0);
    
    return ret;
}

    
//------------------------------------------------------------------------------------------------

