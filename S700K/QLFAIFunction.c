// #########################################################################
// *************************************************************************

#include <cvirte.h>     
#include "S700K.h"
#include "..\include\Global.h"

extern int plMain;
extern int plInfo;
extern int plTest;
extern DWORD g_Measure;
extern int plTrend;

extern HANDLE g_DAQThread;
extern DWORD g_SystemTicks;

extern PT_DAQData       g_DAQData;
extern PT_ReportData    g_S700KData;


//------------------------------------------------------------------------------------------------
void CALLBACK GlintCallback( UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2 )
{
   static USHORT  usGlintStatus = 0;
   static double  dfValue;
   
//   DAQCheckMeasure( );
   usGlintStatus = !usGlintStatus;
   if ( g_S700KData.Control.usError )
   {
      SetCtrlVal( plMain, PANELMAIN_LED_ERROR, usGlintStatus );
   }
   else
   {
      SetCtrlVal( plMain, PANELMAIN_LED_ERROR, 0 );
   }
   if ( g_S700KData.Control.usRunStatus == RUNSTATUS_RUNING )
   {
//      SetCtrlVal( plMain, PANELMAIN_LED_RUNNING, usGlintStatus );
   }
   else
   {
//      SetCtrlVal( plMain, PANELMAIN_LED_RUNNING, 0 );
   }
}
//------------------------------------------------------------------------------------------------
