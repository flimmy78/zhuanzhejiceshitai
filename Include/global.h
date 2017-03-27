// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <windows.h>
#include <WinBase.h>
#include "..\S700K\log.h"  

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
// TCP Communicate constant
//------------------------------------------------------------------------------------------------
#define FAI_ChannelStart         0
#define FAI_ChannelNumber        8
#define FAI_DataBufferSize       2048   // 缓冲区大小
#define FAI_PacerRate            2048   // 采样率
//------------------------------------------------------------------------------------------------
#define MEASUREMODE_NONE         0
#define MEASUREMODE_NORMAL       1
#define MEASUREMODE_CYCLED       16
#define MEASUREMODE_IR           32
#define MEASUREMODE_LINE         64
#define MEASUREMODE_FRICTION_D   128
#define MEASUREMODE_FRICTION_F   256

//#define RUNSTATUS_RUNING         0x1000
//#define RUNSTATUS_COMPLETE       0x2000
//#define RUNSTATUS_TERMINATE      0x4000
#define RUNSTATUS_START          1
#define RUNSTATUS_RUNING         2
#define RUNSTATUS_TERMINATE      4
#define RUNSTATUS_COMPLETE       8
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
typedef struct tagPT_CellData
{
   char        cData[64];
   float       fData1;
   float       fData2;
}PT_CellData, *LPT_CellData;

//------------------------------------------------------------------------------------------------
// 设备定义，包括设备的额定数据
typedef struct tagPT_Device
{
   struct{
      short    usLoad2Test;
      short    usLoad1Test;
      short    usLoad3Test;
      short    usTraillingTest;
      short    usRevisionTest;
      char     acSerialNumber[ 32 ];
      char     acTesterName[ 32 ];
      char     acTestResult[ 16 ];
   }Config;
   
   //========================================
   PT_CellData ssRatedStroke;
   PT_CellData ssRatedVoltage;
   PT_CellData ssRatedCurrent;
   PT_CellData ssRatedCurrent_F;
   PT_CellData ssRatedActionTime;
   PT_CellData ssRatedForce;
   
   PT_CellData ssAValveVoltage1;
   PT_CellData ssBValveVoltage1;
   PT_CellData ssAValveVoltage2;
   PT_CellData ssBValveVoltage2;
   PT_CellData ssDCVoltageSet;
   //============================================
   
   struct{
      DWORD    dwModelID;
      char     acModelName[32];
      char     acSpecification[32];
      char     acLine[32];

      double   fStroke;
      double   fVoltage;
      double   fMaxTraillingForce;
      double   fMinTraillingForce;
      double   fLoad2_MaxForce;
      double   fLoad2_Current;
      double   fLoad2_A2B_AVoltage;
      double   fLoad2_A2B_BVoltage;
      double   fLoad2_B2A_AVoltage;
      double   fLoad2_B2A_BVoltage;
      double   fLoad2_Scale;

      double   fLoad1_OperateForce;
      double   fLoad1_Current;
      double   fLoad1_TravelTime;
      double   fLoad1_A2B_AVoltage;
      double   fLoad1_A2B_BVoltage;
      double   fLoad1_B2A_AVoltage;
      double   fLoad1_B2A_BVoltage;

      double   fLoad3_OperateForce;
      double   fLoad3_Current;
      double   fLoad3_TravelTime;
      double   fLoad3_A2B_AVoltage;
      double   fLoad3_A2B_BVoltage;
      double   fLoad3_B2A_AVoltage;
      double   fLoad3_B2A_BVoltage;
   }Standard;
}PT_Device, FAR* LPT_Device;

//------------------------------------------------------------------------------------------------
typedef struct tagPT_CheckData
{
   BOOL     bCheckState;
   double   dfInterval;
}PT_CheckData, far* LPT_CheckData;
//------------------------------------------------------------------------------------------------
typedef struct tagPT_Load2Data
{
   short    usCheckState;
   double   dfUab;
   double   dfUbc;
   double   dfUca;
   double   dfIa;
   double   dfIb;
   double   dfIc;
   double   dfForce;
   double   dfForce1;
   double   dfActionTime;
}PT_Load2Data, far* LPT_Load2Data;
//------------------------------------------------------------------------------------------------
typedef struct tagPT_Load1Data
{
   BOOL     bCheckState;
   double   dfUab;
   double   dfUbc;
   double   dfUca;
   double   dfIa;
   double   dfIb;
   double   dfIc;
   double   dfForce;
   double   dfActionTime;
}PT_Load1Data, far* LPT_Load1Data;

//------------------------------------------------------------------------------------------------
typedef struct tagPT_Load3Data
{
   BOOL     bCheckState;
   double   dfUab;
   double   dfUbc;
   double   dfUca;
   double   dfIa;
   double   dfIb;
   double   dfIc;
   double   dfForce;
   double   dfActionTime;
}PT_Load3Data, far* LPT_Load3Data;

//------------------------------------------------------------------------------------------------
typedef struct tagPT_TraillingData
{
   BOOL     bCheckState;
   double   dfForce;
}PT_TraillingData, far* LPT_TraillingData;

//------------------------------------------------------------------------------------------------
typedef struct tagPT_DataRecord
{
   BOOL     bCheckState;
   PT_CheckData         ptCheckData;
   PT_Load2Data         ptLoad2Data;
   PT_Load1Data         ptLoad1Data;
   PT_Load3Data         ptLoad3Data;
   PT_TraillingData     ptTraillingData;
   
   // DC
   double   dfU;
   double   dfI;
   double   dfI_F;
   double   dfForce;
   double   dfActionTime;
   double   dfStroke;
}PT_DataRecord, FAR* LPT_DataRecord;

//------------------------------------------------------------------------------------------------
typedef struct tagPT_Record
{
   struct{
      short    usMount;          // 0:未选择，1：左装，2：右装
	  short    usWireType;           // 0:未选择，1:四线制，2:五线制
      short    usAConnection;    // 方向A接线。0:未测试，1：正常，2:故障
      short    usBConnection;    // 方向B接线。0:未测试，1：正常，2:故障
      short    usStartStatus;
      short    usConfig;
      short    usStep;
      short    usError;
      short    usRunStatus;
      short    usTerminate;
      long     ulMeasTime;
   }Control;
   
//   PT_Device            ptDevice;         // 上位机配置程序
   SYSTEMTIME           ptStart;
   SYSTEMTIME           ptStop;
   float                fIR;
   PT_DataRecord        ptMeasureDataA;
   PT_DataRecord        ptMeasureDataB;
   PT_DataRecord        ptMeasureDataC;
   PT_DataRecord        ptMeasureDataD;  
   PT_DataRecord        ptMeasureDataF; 
}PT_Record, far* LPT_Record;

//------------------------------------------------------------------------------------------------
typedef struct tagPT_DAQData
{
   struct{
//      short    usTwoHand;
      short    usLeft;           // PositionLeft
      short    usRight;
      short    usFR1;
      short    usFR2;
      short    usJWXC;
      short    usAutoMode;
      short    usManualForward;
      short    usManualBack;
      short    usManualBumpForward;
      short    usManualBumpBack;
      short    usACLeft;
      short    usACRight;
      float    dfUab;
      float    dfUbc;
      float    dfUca;
      float    dfUdc;
      float    dfIa;
      float    dfIb;
      float    dfIc;
      float    dfIdc;
      float    dfPower;
      float    dfForce;
      float    dfStroke;
	  float    dfTravelTime; // 动作时间
   }Data;
}PT_DAQData, far* LPT_DAQData;

//-------------------------------------------------------------------------------------------------
typedef struct tagPT_InitStatus
{
   char     chInitStatus;
   char     chInit833;
   char     chInit1720;
   char     chInit4711;
   char     chInit4750;
}PT_InitStatus, FAR* LPT_InitStatus;

//-------------------------------------------------------------------------------------------------

#endif // __GLOBAL_H__
