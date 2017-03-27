// #########################################################################
// *************************************************************************
// #########################################################################
// *************************************************************************
#include <cvirte.h>     
#include <userint.h>
//#include "DAQUDP.h"
#include "S700K.h"
#include "ADPCI1711.h"
#include "ADPCI1730.h"
#include "ADPCI1784.h"
//#include "DAUSB2833.h"
#include <utility.h>
#include "Device.h"
#include "..\include\global.h"

//------------------------------------------------------------------------------------------------
// 定义全局变量
int                     g_plDAQMain;
int                     g_plMain;
PT_DAQCard              g_PCI1711;
PT_DAQCard              g_PCI1724;
//PT_DAQCard              g_PCI1730;
PT_DAQCard              g_PCI1784;
PT_DAQData              g_DAQData;
PT_Record               g_MeasureData;
PT_Record               g_S700KData;
PT_DAQSystemData        g_DAQSystemData;
//------------------------------------------------------------------------------------------------
PT_Port                 g_Ports[2];
PT_Meter                g_Meters[MAX_METERS];
PT_PLC                  g_Fx2n;
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
int __stdcall Meter_Initialize(void)
{
   memset (&g_Ports[0], 0, sizeof (PT_Port));
   // Init g_Ports;
   g_Ports[0].wPort = 2;
   g_Ports[0].hPort = NULL;
   g_Ports[0].wBaud = CBR_9600;
   g_Ports[0].wParity = NOPARITY;
   g_Ports[0].wStop = ONESTOPBIT;
   g_Ports[0].wBits = 8;
   g_Ports[0].bInit = FALSE;
   
   memset (&g_Meters, 0, sizeof (g_Meters));
   strcpy (g_Meters[METER_IR].cName, "绝缘电阻");
   g_Meters[METER_IR].pPort = &g_Ports[0];
   g_Meters[METER_IR].cAddr = ADDR_IR;
   g_Meters[METER_IR].bUsed = TRUE;
   g_Meters[METER_IR].sTag.fData = 0.0;
   
   InitializeCriticalSection(&g_Ports[0].tagCS);
   return 0;
}

//------------------------------------------------------------------------------------------------
int __stdcall PLC_Initialize(void)
{
   memset (&g_Ports[1], 0, sizeof (PT_Port));
   // Init g_Ports;
   g_Ports[1].wPort = 4;
   g_Ports[1].hPort = NULL;
   g_Ports[1].wBaud = CBR_9600;
   g_Ports[1].wParity = EVENPARITY;
   g_Ports[1].wStop = ONESTOPBIT;
   g_Ports[1].wBits = 7;
   g_Ports[1].bInit = FALSE;
   
   strcpy(g_Fx2n.cName, "PLC");
   g_Fx2n.pPort = &g_Ports[1];
   g_Fx2n.cAddr = 0;
   g_Fx2n.bUsed = TRUE;

   InitializeCriticalSection(&g_Ports[1].tagCS);
   return 0;
}

//------------------------------------------------------------------------------------------------
// 主程序
//------------------------------------------------------------------------------------------------
int __stdcall DAQ_Initialize(void)
{
   // 读入主画面
   if ((g_plDAQMain = LoadPanel (0, "S700K.uir", DAQMAIN)) < 0)
      return -1;
   
   // 延时5秒
//   Sleep (5000);

   // 初始化全局变量
   memset (&g_DAQData, 0, sizeof (g_DAQData));
   
//   memset (&g_PCI1730, 0, sizeof (g_PCI1730));
//   g_PCI1730.dwIndex = 2;
   
   memset (&g_PCI1711, 0, sizeof (g_PCI1711));
   g_PCI1711.dwIndex = 0;
   g_PCI1711.usStart = FAI_ChannelStart;   // 从通道0开始采集
   g_PCI1711.usNumber = FAI_ChannelNumber; // 共采集8个通道
   g_PCI1711.ulPacerRate = FAI_PacerRate;  // 采样率：2048(次/秒)
   g_PCI1711.ulBufferSize = g_PCI1711.usNumber * g_PCI1711.ulPacerRate;
   g_PCI1711.usGainCode = 0; // 0:+/- 5V PCI-1713
   
   memset (&g_PCI1724, 0, sizeof (g_PCI1724));
   g_PCI1724.dwIndex = 1;
   
//   memset (&g_USB2833, 0, sizeof (g_USB2833));
//   g_USB2833.dwIndex = 0;
//   g_USB2833.usGainCode = 1; // 0 - 10V

   memset (&g_PCI1784, 0, sizeof (g_PCI1784));
   g_PCI1784.dwIndex = 2;
   
   memset (&g_S700KData, 0, sizeof (PT_Record));
//   g_S700KData.Control.usStep = -1;
   
   memset (&g_DAQSystemData, 0, sizeof (PT_DAQSystemData));
   
   Meter_Initialize ();
   PLC_Initialize ();

#if 0   // 测试研华板卡选择函数DRV_SelectDevice
   intptr_t hWnd;
   ULONG DeviceNum;
   UCHAR Description[40];
   hWnd = GetCVIWindowHandle();
   //hWnd = NULL;
   DRV_SelectDevice((HWND)hWnd,TRUE,&DeviceNum,Description);
   
#endif   
   // 初始化1711
   if (!ADCards_Open (&g_PCI1711))
   {
      MessageBox( NULL, "不能打开数据采集卡(PCI1711)!", "错误", MB_OK );
   }
   
   // 初始化1724
   if (!ADCards_Open (&g_PCI1724))
   {
      MessageBox( NULL, "不能打开数据采集卡(PCI1711)!", "错误", MB_OK );
   }
   
//   if (!USB2833_Open (&g_USB2833))
//   {
//      MessageBox( NULL, "不能打开数据采集卡(PCI1711)!", "错误", MB_OK );
//   }
   
   // 初始化1784
   if (!ADPCI1784_Open (&g_PCI1784))
   {
      MessageBox( NULL, "不能配置采集卡(PCI1784)!", "错误", MB_OK );
   }
   
   // 初始化1730
//   if (!ADCards_Open (&g_PCI1730))
//   {
//      MessageBox( NULL, "不能配置采集卡(PCI1730)!", "错误", MB_OK );
//   }
   // 启动PLC
   CreateThread_PLC ();

   // 启动快速数据采集线程。用于模拟量采集卡：PCI-1713(1711)
   FAI_ScanStart ();
   // 启动参数显示和转辙机测试线程
   DAQ_CreateThread ();
   
   Meter_CreateThread ();
   
   return 0;
}

//------------------------------------------------------------------------------------------------
// 主程序
//------------------------------------------------------------------------------------------------
void __stdcall PLC_Uninitialize(void)
{
	FX2N_DOControl(DOCH_FOUR, FALSE);
	FX2N_DOControl(DOCH_FIVE, FALSE);
	DeleteCriticalSection(&g_Ports[1].tagCS);
}
int __stdcall DAQ_Uninitialize(void)
{
   // 退出运行
   g_DAQSystemData.usTerminate = TRUE;
   // 停止参数显示和转辙机测试线程 
   DAQ_TerminateThread ();
   FAI_ScanStop ();   
   DiscardPanel (g_plDAQMain);
//   USB2833_Close (&g_USB2833);
   
   Meter_TerminateThread ();
   
   TerminateThread_PLC ();
   PLC_Uninitialize();
   
   ADCards_Close (&g_PCI1711);
   ADCards_Close (&g_PCI1724);
   ADPCI1784_Close (&g_PCI1784);

   return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 转辙机伸出按钮，鼠标左击输出，右击断开
//------------------------------------------------------------------------------------------------
int CVICALLBACK forwardCtrlCallback (int panel, int control, int event,
      void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
   case EVENT_LEFT_CLICK:
      // 不在自动模式下，不允许操作
      if (!g_DAQData.Data.usAutoMode)
         return 0;
      // 转辙机动作
      //DAQ_DCLineControl (0);
      DAQ_OutControl (1);
      // 禁止按钮操作
      SetCtrlAttribute (g_plDAQMain, DAQMAIN_ACBACKCTRL, ATTR_DIMMED, 1);
      break;
   case EVENT_RIGHT_CLICK:
      // 转辙机动作
      //DAQ_DCLineControl (0);
      DAQ_OutControl (0);
      // 禁止按钮操作
      SetCtrlAttribute (g_plDAQMain, DAQMAIN_ACBACKCTRL, ATTR_DIMMED, 0);
      break;
   case EVENT_COMMIT:
      break;
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 转辙机缩回按钮，鼠标左击输出，右击断开
//------------------------------------------------------------------------------------------------
int CVICALLBACK backCtrlCallback (int panel, int control, int event,
      void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
   case EVENT_LEFT_CLICK:
      if (!g_DAQData.Data.usAutoMode)
         return 0;
      //DAQ_DCLineControl (0);
      DAQ_InControl (1);
      SetCtrlAttribute (g_plDAQMain, DAQMAIN_ACFORWARDCTRL, ATTR_DIMMED, 1);
      break;
   case EVENT_RIGHT_CLICK:
     // DAQ_DCLineControl (0);
      DAQ_InControl (0);
      SetCtrlAttribute (g_plDAQMain, DAQMAIN_ACFORWARDCTRL, ATTR_DIMMED, 0);
      break;
   case EVENT_COMMIT:
      break;
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 程序退出
//------------------------------------------------------------------------------------------------
int CVICALLBACK QuitCallback (int panel, int control, int event,
      void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
      case EVENT_COMMIT:
         HidePanel (g_plDAQMain);
         DisplayPanel (g_plMain);
         break;
         //if (MessageBox (NULL, "是否退出运行?", "提示", MB_YESNO | MB_ICONQUESTION | MB_TOPMOST) == IDYES)
         //{
         //   FAI_ScanStop ();
         //   QuitUserInterface (0);
         //}
         break;
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 油泵启动按钮
//------------------------------------------------------------------------------------------------
int CVICALLBACK OilbumpStartCallback (int panel, int control, int event,
      void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
      case EVENT_COMMIT:
//         if (!g_DAQData.Data.usAutoMode)
//            return 0;
         DAQ_OilBumpControl (1);
         SetCtrlAttribute(g_plDAQMain, DAQMAIN_OILBUMPSTART, ATTR_CMD_BUTTON_COLOR, 0xFF0000);// ,0xECE9D8,0xFF0000		 
         SetCtrlAttribute(g_plDAQMain, DAQMAIN_OILBUMPSTOP , ATTR_CMD_BUTTON_COLOR, 0xECE9D8);// ,0xECE9D8,0xFF0000		 		 		 
         break;
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 油泵停止按钮
//------------------------------------------------------------------------------------------------
int CVICALLBACK OilbumpStopCallback (int panel, int control, int event,
      void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
      case EVENT_COMMIT:
         DAQ_OilBumpControl (0);
         SetCtrlAttribute(g_plDAQMain, DAQMAIN_OILBUMPSTART, ATTR_CMD_BUTTON_COLOR, 0xECE9D8);// ,0xECE9D8,0xFF0000		 
         SetCtrlAttribute(g_plDAQMain, DAQMAIN_OILBUMPSTOP , ATTR_CMD_BUTTON_COLOR, 0xECE9D8);// ,0xECE9D8,0xFF0000		 		 		 
         break;
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 测试终止按钮
//------------------------------------------------------------------------------------------------
int CVICALLBACK StopCallback (int panel, int control, int event,
      void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
      case EVENT_COMMIT:
         g_DAQSystemData.usTerminate = 1;
         break;
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 伸出换向阀按钮，鼠标左击输出，右击断开
//------------------------------------------------------------------------------------------------
int CVICALLBACK forwardValveCallback (int panel, int control, int event,
      void *callbackData, int eventData1, int eventData2)
{
   float fData;   
   switch (event)
   {
      case EVENT_LEFT_CLICK:
//         if (!g_DAQData.Data.usAutoMode)
//            return 0;
         DAQ_SetInValve (0); 	// 缩回换向阀控制
         DAQ_SetOutValve (1);	// 伸出换向阀控制
		 
         GetCtrlVal (g_plDAQMain, DAQMAIN_NG_DA_A, &fData);  // To A.DA
         DAQ_SetOutForce (fData); // 伸出换向阀开度控制		 
         GetCtrlVal (g_plDAQMain, DAQMAIN_NG_DA_B, &fData);  // To B.DA
         DAQ_SetInForce (fData);  // 缩回换向阀开度控制
		 
		 SetCtrlAttribute(panel, control, ATTR_CMD_BUTTON_COLOR, 0xFF0000);// ,0xECE9D8,0xFF0000
         break;
      case EVENT_RIGHT_CLICK:
         DAQ_SetOutValve (0);
         DAQ_SetInValve (0);
         DAQ_SetOutForce (0.0);
         DAQ_SetInForce (0.0);
		 SetCtrlAttribute(panel, control, ATTR_CMD_BUTTON_COLOR, 0xECE9D8);// ,0xECE9D8,0xFF0000		 
         break;
      case EVENT_COMMIT:
         break;
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 缩回换向阀按钮，鼠标左击输出，右击断开
//------------------------------------------------------------------------------------------------
int CVICALLBACK backValveCallback (int panel, int control, int event,
      void *callbackData, int eventData1, int eventData2)
{
   float fData;   
   switch (event)
   {
      case EVENT_LEFT_CLICK:
//         if (!g_DAQData.Data.usAutoMode)
//            return 0;
         DAQ_SetOutValve (0);
         DAQ_SetInValve (1);
		 
         GetCtrlVal (g_plDAQMain, DAQMAIN_NG_DA_A, &fData);  // To A.DA
         DAQ_SetOutForce (fData); // 伸出换向阀开度控制		 
         GetCtrlVal (g_plDAQMain, DAQMAIN_NG_DA_B, &fData);  // To B.DA
         DAQ_SetInForce (fData);   // 缩回换向阀开度控制

		 SetCtrlAttribute(panel, control, ATTR_CMD_BUTTON_COLOR, 0xFF0000);// ,0xECE9D8,0xFF0000		 
         break;
      case EVENT_RIGHT_CLICK:
         DAQ_SetOutValve (0);
         DAQ_SetInValve (0);
         DAQ_SetOutForce (0.0);
         DAQ_SetInForce (0.0);
		 SetCtrlAttribute(panel, control, ATTR_CMD_BUTTON_COLOR, 0xECE9D8);// ,0xECE9D8,0xFF0000		 		 
         break;
      case EVENT_COMMIT:
         break;
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 总油阀按钮，鼠标左击输出，右击断开
//------------------------------------------------------------------------------------------------
int CVICALLBACK totalValveCallback (int panel, int control, int event,
      void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
      case EVENT_LEFT_CLICK:
//         if (!g_DAQData.Data.usAutoMode)
//            return 0;
         DAQ_SetTotalValve (1);
		 SetCtrlAttribute(panel, control, ATTR_CMD_BUTTON_COLOR, 0xFF0000);// ,0xECE9D8,0xFF0000		 
         break;
      case EVENT_RIGHT_CLICK:
         DAQ_SetTotalValve (0);
         SetCtrlAttribute(panel, control, ATTR_CMD_BUTTON_COLOR, 0xECE9D8);// ,0xECE9D8,0xFF0000		 		 
         break;
      case EVENT_COMMIT:
         break;
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 缩回换向阀开度控制
//------------------------------------------------------------------------------------------------
int CVICALLBACK dafCallBack (int panel, int control, int event,
      void *callbackData, int eventData1, int eventData2)
{
   float fData;   
   switch (event)
   {
      case EVENT_COMMIT:
         GetCtrlVal (g_plDAQMain, DAQMAIN_NG_DA_B, &fData);
         DAQ_SetInForce (fData);
         break;
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
// 回调函数
// 伸出换向阀开度控制
//------------------------------------------------------------------------------------------------
int CVICALLBACK dabCallBack (int panel, int control, int event,
      void *callbackData, int eventData1, int eventData2)
{
   float fData;   
   switch (event)
   {
      case EVENT_COMMIT:
         GetCtrlVal (g_plDAQMain, DAQMAIN_NG_DA_A, &fData);
         DAQ_SetOutForce (fData);

         break;
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
int CVICALLBACK callback_Control_Track (int panel, int control, int event,
      void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
   case EVENT_LEFT_CLICK:
      // 不在自动模式下，不允许操作
      if (!g_DAQData.Data.usAutoMode)
         return 0;
      // 接入模拟电阻
      DAQ_SimulateTrack (1);
	  SetCtrlAttribute(panel, control, ATTR_CMD_BUTTON_COLOR, 0xFF0000);// ,0xECE9D8,0xFF0000		 
      break;
   case EVENT_RIGHT_CLICK:
      // 断开模拟电阻
      DAQ_SimulateTrack (0);
	  SetCtrlAttribute(panel, control , ATTR_CMD_BUTTON_COLOR, 0xECE9D8);// ,0xECE9D8,0xFF0000		 		 		 
      break;
   case EVENT_COMMIT:
      break;
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
int CVICALLBACK callback_Control_ACSelect (int panel, int control, int event,
      void *callbackData, int eventData1, int eventData2)
{
   switch (event)
   {
   case EVENT_LEFT_CLICK:
      // 不在自动模式下，不允许操作
      if (!g_DAQData.Data.usAutoMode)
         return 0;
      // 转辙机动作
 //     DAQ_DCSelect (0);
//      DAQ_ACSelect (1);
      break;
   case EVENT_RIGHT_CLICK:
      // 转辙机动作
//      DAQ_ACSelect (0);
      //DAQ_DCSelect (0);
      break;
   case EVENT_COMMIT:
      break;
   }
   return 0;
}

//------------------------------------------------------------------------------------------------
int CVICALLBACK Callback_Main_Manual (int panel, int control, int event,
      void *callbackData, int eventData1, int eventData2)
{
   if (event != EVENT_COMMIT)
      return 0;
   
   HidePanel (g_plMain);
   DisplayPanel (g_plDAQMain);
   
   return 0;
}

//------------------------------------------------------------------------------------------------
