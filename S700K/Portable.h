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

#define  MAIN                             1
#define  MAIN_STEP                        2       /* control type: textMsg, callback function: (none) */
#define  MAIN_STEP_TEXT                   3       /* control type: textMsg, callback function: (none) */
#define  MAIN_DATETIMER                   4       /* control type: timer, callback function: datetimeCallback */
#define  MAIN_TYPENAME                    5       /* control type: string, callback function: (none) */
#define  MAIN_STEPMSG                     6       /* control type: textMsg, callback function: (none) */
#define  MAIN_LED_ERROR                   7       /* control type: LED, callback function: (none) */
#define  MAIN_LED_RUNING_2                8       /* control type: LED, callback function: (none) */
#define  MAIN_LED_RUNING                  9       /* control type: LED, callback function: (none) */
#define  MAIN_TM_TIME                     10      /* control type: textMsg, callback function: (none) */
#define  MAIN_DECORATION_2                11      /* control type: deco, callback function: (none) */
#define  MAIN_LED_AUTO                    12      /* control type: LED, callback function: (none) */
#define  MAIN_TM_TITLE_2                  13      /* control type: textMsg, callback function: (none) */
#define  MAIN_DECORATION_3                14      /* control type: deco, callback function: (none) */
#define  MAIN_PICTURE_2                   15      /* control type: picture, callback function: (none) */
#define  MAIN_PICTURE_4                   16      /* control type: picture, callback function: (none) */
#define  MAIN_PICTURE_6                   17      /* control type: picture, callback function: (none) */
#define  MAIN_PICTURE_5                   18      /* control type: picture, callback function: (none) */
#define  MAIN_DECORATION                  19      /* control type: deco, callback function: (none) */
#define  MAIN_PICTURE_7                   20      /* control type: picture, callback function: (none) */
#define  MAIN_STRIPCHART                  21      /* control type: strip, callback function: (none) */
#define  MAIN_PICTURE_8                   22      /* control type: picture, callback function: (none) */
#define  MAIN_PICTURE_3                   23      /* control type: picture, callback function: (none) */
#define  MAIN_PICTURE                     24      /* control type: picture, callback function: (none) */

#define  MAIN_2                           2
#define  MAIN_2_DECORATION                2       /* control type: deco, callback function: (none) */
#define  MAIN_2_PICTURE_7                 3       /* control type: picture, callback function: (none) */
#define  MAIN_2_PICTURE                   4       /* control type: picture, callback function: (none) */
#define  MAIN_2_STRING_5                  5       /* control type: string, callback function: (none) */
#define  MAIN_2_STRING_4                  6       /* control type: string, callback function: (none) */
#define  MAIN_2_STRING_3                  7       /* control type: string, callback function: (none) */
#define  MAIN_2_STRING_6                  8       /* control type: string, callback function: (none) */
#define  MAIN_2_STRING_2                  9       /* control type: string, callback function: (none) */
#define  MAIN_2_RADIOBUTTON               10      /* control type: radioButton, callback function: (none) */
#define  MAIN_2_RING                      11      /* control type: ring, callback function: (none) */

#define  MAIN_3                           3
#define  MAIN_3_DECORATION                2       /* control type: deco, callback function: (none) */
#define  MAIN_3_PICTURE                   3       /* control type: picture, callback function: (none) */
#define  MAIN_3_LED_ERROR_2               4       /* control type: LED, callback function: (none) */
#define  MAIN_3_STRING_3                  5       /* control type: string, callback function: (none) */
#define  MAIN_3_LED_USB                   6       /* control type: LED, callback function: (none) */
#define  MAIN_3_LED_ControlOn             7       /* control type: LED, callback function: (none) */
#define  MAIN_3_LED_RUNING                8       /* control type: LED, callback function: (none) */
#define  MAIN_3_LED_AUTO                  9       /* control type: LED, callback function: (none) */
#define  MAIN_3_STRING_6                  10      /* control type: string, callback function: (none) */
#define  MAIN_3_STRING_2                  11      /* control type: string, callback function: (none) */
#define  MAIN_3_TEXTMSG                   12      /* control type: textMsg, callback function: (none) */
#define  MAIN_3_TEXTMSG_2                 13      /* control type: textMsg, callback function: (none) */
#define  MAIN_3_TEXTMSG_3                 14      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK datetimeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
