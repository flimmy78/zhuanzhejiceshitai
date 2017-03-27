/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  DAQMAIN                          1
#define  DAQMAIN_NG_FORCE                 2       /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_POWER                 3       /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_DISTANCE              4       /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_IC                    5       /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_IB                    6       /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_IA                    7       /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_UCA                   8       /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_UBC                   9       /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_UAB                   10      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_F_2_2                 11      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_OILBUMPSTOP              12      /* control type: command, callback function: OilbumpStopCallback */
#define  DAQMAIN_NG_DISB_B                13      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_Stop                     14      /* control type: command, callback function: StopCallback */
#define  DAQMAIN_NG_F_2_1                 15      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_DISB_A                16      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_OILBUMPSTART             17      /* control type: command, callback function: OilbumpStartCallback */
#define  DAQMAIN_QUIT                     18      /* control type: command, callback function: QuitCallback */
#define  DAQMAIN_BACKVALVE                19      /* control type: command, callback function: backValveCallback */
#define  DAQMAIN_TOTALVALVE               20      /* control type: command, callback function: totalValveCallback */
#define  DAQMAIN_FORWARDVALVE             21      /* control type: command, callback function: forwardValveCallback */
#define  DAQMAIN_ACBACKCTRL               22      /* control type: command, callback function: backCtrlCallback */
#define  DAQMAIN_ACSELECT                 23      /* control type: command, callback function: callback_Control_ACSelect */
#define  DAQMAIN_TRACK                    24      /* control type: command, callback function: callback_Control_Track */
#define  DAQMAIN_ACFORWARDCTRL            25      /* control type: command, callback function: forwardCtrlCallback */
#define  DAQMAIN_DECORATION_8             26      /* control type: deco, callback function: (none) */
#define  DAQMAIN_LED_RIGHT                27      /* control type: LED, callback function: (none) */
#define  DAQMAIN_LED_LEFT                 28      /* control type: LED, callback function: (none) */
#define  DAQMAIN_LED_ERROR_2              29      /* control type: LED, callback function: (none) */
#define  DAQMAIN_LED_RUNNING_2            30      /* control type: LED, callback function: (none) */
#define  DAQMAIN_DECORATION_9             31      /* control type: deco, callback function: (none) */
#define  DAQMAIN_LED_REVISION             32      /* control type: LED, callback function: (none) */
#define  DAQMAIN_LED_TRAIL                33      /* control type: LED, callback function: (none) */
#define  DAQMAIN_LED_LOAD3                34      /* control type: LED, callback function: (none) */
#define  DAQMAIN_LED_LOAD1                35      /* control type: LED, callback function: (none) */
#define  DAQMAIN_DECORATION_3             36      /* control type: deco, callback function: (none) */
#define  DAQMAIN_LED_LOAD2                37      /* control type: LED, callback function: (none) */
#define  DAQMAIN_LED_CONFIG               38      /* control type: LED, callback function: (none) */
#define  DAQMAIN_LED_ControlOn            39      /* control type: LED, callback function: (none) */
#define  DAQMAIN_LED_RUNING               40      /* control type: LED, callback function: (none) */
#define  DAQMAIN_LED_AUTO                 41      /* control type: LED, callback function: (none) */
#define  DAQMAIN_NG_Time                  42      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_T_3_1                 43      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_T_1_1                 44      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_DA_A                  45      /* control type: numeric, callback function: dabCallBack */
#define  DAQMAIN_NG_T_3_2                 46      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_DA_B                  47      /* control type: numeric, callback function: dafCallBack */
#define  DAQMAIN_NG_F_4_2                 48      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_F_3_2                 49      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_T_1_2                 50      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_SPEED                 51      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_LOAD3_RF              52      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_AOB                   53      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_AOA                   54      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_F_4_1                 55      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_F_1_2                 56      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_F_3_1                 57      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_NG_F_1_1                 58      /* control type: numeric, callback function: (none) */
#define  DAQMAIN_DECORATION               59      /* control type: deco, callback function: (none) */

#define  MAIN                             2
#define  MAIN_DECORATION_10               2       /* control type: deco, callback function: (none) */
#define  MAIN_DECORATION_9                3       /* control type: deco, callback function: (none) */
#define  MAIN_DECORATION_8                4       /* control type: deco, callback function: (none) */
#define  MAIN_DECORATION_4                5       /* control type: deco, callback function: (none) */
#define  MAIN_TM_TITLE_2                  6       /* control type: textMsg, callback function: (none) */
#define  MAIN_TM_TITLE                    7       /* control type: textMsg, callback function: (none) */
#define  MAIN_STEP                        8       /* control type: textMsg, callback function: (none) */
#define  MAIN_STEP_TEXT                   9       /* control type: textMsg, callback function: (none) */
#define  MAIN_DATETIMER                   10      /* control type: timer, callback function: datetimeCallback */
#define  MAIN_TYPENAME                    11      /* control type: string, callback function: (none) */
#define  MAIN_PICTURE_7                   12      /* control type: picture, callback function: (none) */
#define  MAIN_MEASTIME                    13      /* control type: textMsg, callback function: (none) */
#define  MAIN_MEASTIME_TEXT               14      /* control type: textMsg, callback function: (none) */
#define  MAIN_STEPMSG                     15      /* control type: textMsg, callback function: (none) */
#define  MAIN_NG_FORCE                    16      /* control type: scale, callback function: (none) */
#define  MAIN_NG_IC                       17      /* control type: scale, callback function: (none) */
#define  MAIN_NG_IB                       18      /* control type: scale, callback function: (none) */
#define  MAIN_NG_IA                       19      /* control type: scale, callback function: (none) */
#define  MAIN_NG_S                        20      /* control type: scale, callback function: (none) */
#define  MAIN_NG_UCA                      21      /* control type: scale, callback function: (none) */
#define  MAIN_NG_UBC                      22      /* control type: scale, callback function: (none) */
#define  MAIN_NG_UAB                      23      /* control type: scale, callback function: (none) */
#define  MAIN_LED_JWXC                    24      /* control type: LED, callback function: (none) */
#define  MAIN_LED_ERROR                   25      /* control type: LED, callback function: (none) */
#define  MAIN_LED_F                       26      /* control type: LED, callback function: (none) */
#define  MAIN_LED_D                       27      /* control type: LED, callback function: (none) */
#define  MAIN_LED_RUNING                  28      /* control type: LED, callback function: (none) */
#define  MAIN_LED_CONFIG                  29      /* control type: LED, callback function: (none) */
#define  MAIN_LED_LOAD3                   30      /* control type: LED, callback function: (none) */
#define  MAIN_LED_LOAD1                   31      /* control type: LED, callback function: (none) */
#define  MAIN_LED_TRAIL                   32      /* control type: LED, callback function: (none) */
#define  MAIN_LED_REVISION                33      /* control type: LED, callback function: (none) */
#define  MAIN_TM_TIME                     34      /* control type: textMsg, callback function: (none) */
#define  MAIN_DECORATION_2                35      /* control type: deco, callback function: (none) */
#define  MAIN_LED_LOAD2                   36      /* control type: LED, callback function: (none) */
#define  MAIN_LED_FR2                     37      /* control type: LED, callback function: (none) */
#define  MAIN_TM_DATE                     38      /* control type: textMsg, callback function: (none) */
#define  MAIN_LED_FR1                     39      /* control type: LED, callback function: (none) */
#define  MAIN_LED_OilDuty                 40      /* control type: LED, callback function: (none) */
#define  MAIN_LED_AUTO                    41      /* control type: LED, callback function: (none) */
#define  MAIN_C_QUIT                      42      /* control type: pictButton, callback function: quitCallback */
#define  MAIN_C_SAVE                      43      /* control type: pictButton, callback function: saveCallback */
#define  MAIN_C_POWER                     44      /* control type: pictButton, callback function: powerCallback */
#define  MAIN_C_CURRENT                   45      /* control type: pictButton, callback function: currentCallback */
#define  MAIN_C_POSITION                  46      /* control type: pictButton, callback function: positionCallback */
#define  MAIN_C_TRAILLING                 47      /* control type: pictButton, callback function: traillingCallback */
#define  MAIN_C_REVISION                  48      /* control type: pictButton, callback function: revisionCallback */
#define  MAIN_C_LOAD3                     49      /* control type: pictButton, callback function: load3Callback */
#define  MAIN_C_LOAD1                     50      /* control type: pictButton, callback function: load1Callback */
#define  MAIN_C_LOAD2                     51      /* control type: pictButton, callback function: load2Callback */
#define  MAIN_C_TESTERNAME                52      /* control type: pictButton, callback function: testerNameCallback */
#define  MAIN_C_SERIALNUMBER              53      /* control type: pictButton, callback function: serialNumberCallback */
#define  MAIN_C_TYPENUMBER                54      /* control type: pictButton, callback function: typeNumberCallback */
#define  MAIN_C_TYPE                      55      /* control type: pictButton, callback function: typeCallback */
#define  MAIN_C_TABLE                     56      /* control type: pictButton, callback function: tableCallback */
#define  MAIN_C_RESULT                    57      /* control type: pictButton, callback function: resultCallback */
#define  MAIN_C_TRANSMIT                  58      /* control type: pictButton, callback function: transmitCallback */
#define  MAIN_C_HideTable                 59      /* control type: pictButton, callback function: HideTableCallback */
#define  MAIN_RIGHTTYPE                   60      /* control type: command, callback function: CallBack_Right */
#define  MAIN_Fourxz                      61      /* control type: command, callback function: CallBack_Four */
#define  MAIN_FIVEXZ                      62      /* control type: command, callback function: CallBack_Five */
#define  MAIN_MANUAL                      63      /* control type: command, callback function: Callback_Main_Manual */
#define  MAIN_LEFTTYPE                    64      /* control type: command, callback function: CallBack_Left */
#define  MAIN_IR                          65      /* control type: command, callback function: Callback_Main_IR */
#define  MAIN_COMMANDBUTTON_3             66      /* control type: command, callback function: OnQuanPing */
#define  MAIN_COMMANDBUTTON_2             67      /* control type: command, callback function: OnXiuMian */
#define  MAIN_COMMANDBUTTON               68      /* control type: command, callback function: OnExit */

#define  MODEL                            3
#define  MODEL_CANCEL                     2       /* control type: command, callback function: Callback_Model_Cancel */
#define  MODEL_OK                         3       /* control type: command, callback function: Callback_Model_Ok */
#define  MODEL_MODELNO                    4       /* control type: ring, callback function: (none) */
#define  MODEL_DECORATION                 5       /* control type: deco, callback function: (none) */
#define  MODEL_DEVICENO                   6       /* control type: string, callback function: (none) */

#define  PLCurrent                        4
#define  PLCurrent_NUMERICGAUGE           2       /* control type: scale, callback function: (none) */

#define  PLPosition                       5
#define  PLPosition_NUMERICGAUGE          2       /* control type: scale, callback function: (none) */

#define  PLPower                          6
#define  PLPower_NUMERICGAUGE             2       /* control type: scale, callback function: (none) */

#define  PLTABLE                          7
#define  PLTABLE_C_TABLE                  2       /* control type: picture, callback function: (none) */
#define  PLTABLE_E_TABLE                  3       /* control type: picture, callback function: (none) */
#define  PLTABLE_MIN_LOAD3B_F             4       /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MIN_LOAD3A_F             5       /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MIN_LOAD1A_F             6       /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MIN_LOAD1B_F             7       /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MAX_LOAD3A_I             8       /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MAX_LOAD3A_T             9       /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MAX_LOAD3B_I             10      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MAX_LOAD3B_T             11      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MAX_LOAD1A_I             12      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MAX_LOAD1A_T             13      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MAX_LOAD1B_I             14      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MAX_LOAD1B_T             15      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MAX_LOAD2A_I             16      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MAX_LOAD2A_F             17      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MAX_LOAD2B_I             18      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MAX_LOAD2B_F             19      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_NAME_TEXT_3              20      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_NAME_TEXT_2              21      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_NAME_TEXT                22      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MAX_STROKE               23      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_TRAILLINGA_F           24      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_TRAILLINGA_F             25      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_TEST_LOAD3               26      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_TEST_LOAD1               27      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_TEST_REVISION            28      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_TEST_TRAILLING           29      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_TEST_LOAD2               30      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MAX_TRAILLING            31      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_TRAILLINGB_F           32      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MIN_TRAILLING            33      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_TRAILLINGB_F             34      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD3A_I               35      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD3A_T               36      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD3A_F               37      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD3B_I               38      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD3B_T               39      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD3B_F               40      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD1A_I               41      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD1A_T               42      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD1A_F               43      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD1B_I               44      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD1B_T               45      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD1B_F               46      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD2A_I               47      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD2A_F               48      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD3A_I                 49      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD3A_T                 50      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD3A_F                 51      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD3B_I                 52      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD3B_T                 53      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD3B_F                 54      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD1A_I                 55      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD1A_T                 56      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD1A_F                 57      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD1B_I                 58      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD1B_T                 59      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD1B_F                 60      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD2A_I                 61      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD2A_F                 62      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_TEXTMSG                  63      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD2B_I               64      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_LOAD2B_F               65      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD2B_I                 66      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_LOAD2B_F                 67      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_CONA                   68      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_CONB                   69      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_R_STROKE                 70      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_STROKE                   71      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_MIN_STROKE               72      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_IR                       73      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_RESULT                   74      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_DATE                     75      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_TESTERNAME               76      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_SERIALNUMBER             77      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_TYPENAME                 78      /* control type: textMsg, callback function: (none) */
#define  PLTABLE_TYPENUMBER               79      /* control type: textMsg, callback function: (none) */

#define  PLTrend                          8
#define  PLTrend_FORCETREND               2       /* control type: graph, callback function: (none) */
#define  PLTrend_SAVEPICTURE              3       /* control type: command, callback function: savebitmapCallback */
#define  PLTrend_HIDE                     4       /* control type: command, callback function: HideCallback */
#define  PLTrend_PRINT                    5       /* control type: command, callback function: printtrendCallback */
#define  PLTrend_TAXISSCALETOTAL          6       /* control type: command, callback function: taxisscaletotalCallback */
#define  PLTrend_TAXISSCALEDOWN           7       /* control type: command, callback function: taxisscaledownCallback */
#define  PLTrend_FAXISSCALEDOWN           8       /* control type: command, callback function: faxisscaledownCallback */
#define  PLTrend_NEXT                     9       /* control type: command, callback function: nextCallback */
#define  PLTrend_TAXISSCALEHALF           10      /* control type: command, callback function: taxisscalehalfCallback */
#define  PLTrend_DECORATION_3             11      /* control type: deco, callback function: (none) */
#define  PLTrend_TAXISSCALEUP             12      /* control type: command, callback function: taxisscaleupCallback */
#define  PLTrend_RESUME                   13      /* control type: command, callback function: resumeCallback */
#define  PLTrend_FAXISSCALEUP             14      /* control type: command, callback function: faxisscaleupCallback */
#define  PLTrend_STOP                     15      /* control type: command, callback function: stopCallback */
#define  PLTrend_PREVIOUS                 16      /* control type: command, callback function: previousCallback */
#define  PLTrend_TRENDTIMER               17      /* control type: timer, callback function: trendtimeCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK backCtrlCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK backValveCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK callback_Control_ACSelect(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK callback_Control_Track(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CallBack_Five(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CallBack_Four(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CallBack_Left(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Main_IR(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Main_Manual(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Model_Cancel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Model_Ok(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CallBack_Right(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK currentCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK dabCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK dafCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK datetimeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK faxisscaledownCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK faxisscaleupCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK forwardCtrlCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK forwardValveCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK HideCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK HideTableCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK load1Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK load2Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK load3Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK nextCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OilbumpStartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OilbumpStopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnExit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnQuanPing(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnXiuMian(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK positionCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK powerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK previousCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK printtrendCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK resultCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK resumeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK revisionCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK savebitmapCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK saveCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK serialNumberCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK tableCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK taxisscaledownCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK taxisscalehalfCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK taxisscaletotalCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK taxisscaleupCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK testerNameCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK totalValveCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK traillingCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK transmitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK trendtimeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK typeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK typeNumberCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
