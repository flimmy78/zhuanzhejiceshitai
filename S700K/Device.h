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
#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>

#include "sqlext.h"

#ifndef __DEVICE_H__
#define __DEVICE_H__

//------------------------------------------------------------------------------------------------
#define CHK(x)                   if (x) goto Exit;
#define ERR(x)                   if (x) goto Error;
//------------------------------------------------------------------------------------------------
#define BUFFER_SIZE              256
#define STX                      0x02
#define ETX                      0x03
#define ACK                      0x06
#define NAK                      0x15
#define ENQ                      0x05
#define FN_DEVICE_READ           0x30
#define FN_DEVICE_WRITE          0x31
#define FN_FORCE_ON              0x37
#define FN_FORCE_OFF             0x38
//------------------------------------------------------------------------------------------------
#define FN_READ_OUTPUT_COILS     1  // 0X
#define FN_READ_INPUT_COILS      2  // 1X
#define FN_READ_HOLDING_REGS     3  // 4X
#define FN_READ_INPUT_REGS       4  // 3X
#define FN_WRITE_COIL            5  // 0X
#define FN_WRITE_REGISTER        6  // 4X
#define FN_READ_EXCEPTION        7  // 4X
#define FN_READ_COMM_EVENT_CTR   11 // Communication stats
#define FN_READ_COMM_EVENT_LOG   12 // Communication info
#define FN_WRITE_COILS           15 // 0X
#define FN_WRITE_REGISTERS       16 // 4X
#define FN_READ_DEVICE_ID        17 // Device specific
#define BYTES_IN_FLOAT           4  // Four Bytes in Float
//------------------------------------------------------------------------------------------------
#define MAX_METERS               3
#define MAX_DIOTAGS              128
#define MAX_AIOTAGS              16

//------------------------------------------------------------------------------------------------
typedef struct tagPT_Message
{
   BYTE           buffer[BUFFER_SIZE];
   WORD           length;
   BOOL           ok;
}PT_Message, far* LPT_Message;

//------------------------------------------------------------------------------------------------
typedef struct tagPT_Port
{
   HANDLE         hPort;
   WORD           wPort;
   WORD           wStop;
   WORD           wParity;
   WORD           wBaud;
   WORD           wBits;
   BOOL           bInit;
    CRITICAL_SECTION tagCS; // protect access to tag values (data) with this
}PT_Port, far* LPT_Port;

//------------------------------------------------------------------------------------------------
typedef struct tagPT_Tag
{
   char           address;
   char           name[64];
   short          offset;  // Address
   short          bit;     // Bit of data
   short          length;
   float          fData;
   short          wFlag;
   BOOL           bData;
   short          wData;
   BOOL           enable;
   BOOL           skip;
   float          k;
   float          b;
}PT_Tag, far* LPT_Tag;

//------------------------------------------------------------------------------------------------
typedef struct tagPT_Meter
{
   char           cName[32];
   char           cAddr;
   LPT_Port       pPort;
   PT_Tag         sTag;
   BOOL           bUsed;
}PT_Meter, far* LPT_Meter;

//------------------------------------------------------------------------------------------------
typedef struct tagPT_PLC
{
    char           cName[32];
    char           cAddr;
    LPT_Port       pPort;
    PT_Tag         sDIOTag[MAX_DIOTAGS];
    PT_Tag         sAIOTag[MAX_AIOTAGS];
    BOOL           bUsed;
}PT_PLC, far* LPT_PLC;

//------------------------------------------------------------------------------------------------
#define METER_IR              0
#define ADDR_IR               1
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
#define DOCH_OilBumpStart        220   // ������
#define DOCH_SimulateTrack       221   // ���ģ��
#define DOCH_ACForward           222   // ת�޻����
#define DOCH_ACBack              223   // ת�޻�����
#define DOCH_ForwardValve        224   // Һѹ�������
#define DOCH_BackValve           225   // Һѹ�����ط�
#define DOCH_TotalValve          226   // �ܷ�
#define DOCH_InsulateTest        227   // ��Ե����
#define DOCH_Error               230   // ����ָʾ

#define DOCH_LEFT				 231  //��װ
#define DOCH_RIGHT				 232  //��װ

//#define DOCH_FOUR				 233 //������,������
#define DOCH_FOUR				 231 //������
#define DOCH_FIVE				 232 //������

#define DICH_FR1                 200     // ȱ�ౣ��
#define DICH_FR2                 201     // ת�޻��ȱ����̵�����
#define DICH_FR3                 201     // ת�޻�ȱ�ౣ���̵���
#define DICH_SB7                 202     // �ֶ�/�Զ�
#define DICH_JA1                 203     // ��λָʾ
#define DICH_JA2                 204     // ��λָʾ

//------------------------------------------------------------------------------------------------
#define DO_KA01                  220   // JA2
#define DO_KA02                  221   // JA3
#define DO_KA03                  222   // 1o_03   
#define DO_KA04                  223   // 1o_04   
#define DO_KA05                  224   // 1o_05   
#define DO_KA06                  225   // 1o_06   
#define DO_KA07                  226   // 2o_01, 500W, 31V / 29V
#define DO_KA08                  227   // 2o_02   
#define DO_KA09                  230   // 2o_03   
#define DO_KA10                  231   // 2o_04   
#define DO_KA11                  232   // 2o_05   
#define DO_KA12                  233   // 2o_06   
                                          
#define DI_X000                  200   // �ϱ�
#define DI_X001                  201   // �ȱ�
#define DI_X002                  202   // �Զ�
#define DI_X003                  203   // ��λ
#define DI_X004                  204   // ��λ
#define DI_X005                  205   // 
#define DI_X006                  206   // 
#define DI_X007                  207   // 

//------------------------------------------------------------------------------------------------
#define AI_TRAVEL_TIME_A		100// A����ת��ʱ��D100   ��λ1ms
#define AI_TRAVEL_TIME_B		101// B����ת��ʱ��D101   ��λ1ms
//------------------------------------------------------------------------------------------------
#define DO_CLEARDATA             250
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
BOOL Port_Initialize(LPT_Port pPort);
//------------------------------------------------------------------------------------------------
BOOL __stdcall Meter_CreateThread(void);
BOOL __stdcall Meter_TerminateThread(void);
//------------------------------------------------------------------------------------------------
int Meter_Read(LPT_Meter meter);
int Meter_Read_IR(float* pData);
//------------------------------------------------------------------------------------------------
BOOL __stdcall CreateThread_PLC(void);
BOOL __stdcall TerminateThread_PLC(void);
//------------------------------------------------------------------------------------------------
void FX2N_InitTagList(void);

BOOL FX2N_ClearData(void); 
float FX2N_GetData(WORD wAddr);
BOOL FX2N_DOControl(WORD wAddr, WORD wData);
BOOL FX2N_RawOut(WORD wAddr, WORD wData);
BOOL FX2N_GetStatus(WORD wAddr);
//------------------------------------------------------------------------------------------------
HRESULT ClearObjHandle(CAObjHandle *objHandle);
//------------------------------------------------------------------------------------------------
int Meter_Read(LPT_Meter meter);
int Meter_Read_V(float* pData);
int Meter_Read_A(float* pData);
int FX2N_Read_AIO(void);
int FX2N_Read_DIO(void);
void Auto_Delay(long);
//------------------------------------------------------------------------------------------------
void SetMount(short mount);  // �趨ת�޻���װ��ʽ 0:δ���á�1����װ��2����װ
void SetWireType(short wireType);  // �趨ת�޻�������/������  0:δ���á�1�������ơ�2��������			
#endif
