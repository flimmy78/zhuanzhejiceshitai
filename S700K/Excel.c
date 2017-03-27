#include "Excel.h"
#include <userint.h>
#define __ActiveXCtrlErrorHandler() \
if ((ctrlId) > 0) \
   { \
   if (controlID) \
      *controlID = (ctrlId); \
   if (UILError) \
      *UILError = 0; \
   __result = S_OK; \
   } \
else if ((ctrlId) == UIEActiveXError) \
   { \
   if (controlID) \
      *controlID = 0; \
   if (UILError) \
      *UILError = 0; \
   } \
else \
   { \
   if (controlID) \
      *controlID = 0; \
   if (UILError) \
      *UILError = (ctrlId); \
   __result = E_CVIAUTO_CVI_UI_ERROR; \
   }

const IID Excel_IID_QueryTable =
   {
      0x24428, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_App =
   {
      0x208D5, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Chart =
   {
      0x208D6, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Worksheet =
   {
      0x208D8, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Global =
   {
      0x208D9, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Workbook =
   {
      0x208DA, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_OLEObject =
   {
      0x208A2, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_RefreshEvents =
   {
      0x2441B, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_AppEvents =
   {
      0x24413, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ChartEvents =
   {
      0x2440F, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DocEvents =
   {
      0x24411, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_WorkbkEvents =
   {
      0x24412, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_OLEObjectEvents =
   {
      0x24410, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Adjustments =
   {
      0xC0310, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_CalloutFormat =
   {
      0xC0311, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ColorFormat =
   {
      0xC0312, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_LineFormat =
   {
      0xC0317, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ShapeNode =
   {
      0xC0318, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ShapeNodes =
   {
      0xC0319, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PictureFmt =
   {
      0xC031A, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ShadowFormat =
   {
      0xC031B, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_TextEffectFmt =
   {
      0xC031F, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ThreeDFmt =
   {
      0xC0321, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_FillFormat =
   {
      0xC0314, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DiagramNodes =
   {
      0xC036E, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DiagramNodeChildren =
   {
      0xC036F, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DiagramNode =
   {
      0xC0370, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_IRTDUpdateEvent =
   {
      0xA43788C1, 0xD91B, 0x11D3, 0x8F, 0x39, 0x0, 0xC0, 0x4F, 0x36, 0x51, 0xB8
   };

const IID Excel_IID_IRtdServer =
   {
      0xEC0E6191, 0xDB51, 0x11D3, 0x8F, 0x3E, 0x0, 0xC0, 0x4F, 0x36, 0x51, 0xB8
   };

const IID Excel_IID_Sheets =
   {
      0x208D7, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Workbooks =
   {
      0x208DB, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PublishObject =
   {
      0x24444, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DefaultWebOptions =
   {
      0x24448, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_WebOptions =
   {
      0x24449, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_TreeviewControl =
   {
      0x2444B, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_CubeField =
   {
      0x2444C, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_CubeFields =
   {
      0x2444D, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Font =
   {
      0x2084D, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Window =
   {
      0x20893, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Windows =
   {
      0x20892, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_WorksheetFunction =
   {
      0x20845, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Range =
   {
      0x20846, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_VPageBreak =
   {
      0x24402, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_HPageBreak =
   {
      0x24401, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_HPageBreaks =
   {
      0x24404, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_VPageBreaks =
   {
      0x24405, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_RecentFile =
   {
      0x24407, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_RecentFiles =
   {
      0x24406, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Style =
   {
      0x20852, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Styles =
   {
      0x20853, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Borders =
   {
      0x20855, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_AddIn =
   {
      0x20857, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_AddIns =
   {
      0x20858, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Toolbar =
   {
      0x2085C, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Toolbars =
   {
      0x2085D, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ToolbarButton =
   {
      0x2085E, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ToolbarButtons =
   {
      0x2085F, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Areas =
   {
      0x20860, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_MenuBars =
   {
      0x20863, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_MenuBar =
   {
      0x20864, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Menus =
   {
      0x20865, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Menu =
   {
      0x20866, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_MenuItems =
   {
      0x20867, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_MenuItem =
   {
      0x20868, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Charts =
   {
      0x2086D, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DrawingObjects =
   {
      0x2086F, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PivotCache =
   {
      0x2441C, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PivotCaches =
   {
      0x2441D, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PivotFormula =
   {
      0x2441E, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PivotFormulas =
   {
      0x2441F, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PivotTable =
   {
      0x20872, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PivotTables =
   {
      0x20873, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PivotField =
   {
      0x20874, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PivotFields =
   {
      0x20875, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_CalculatedFields =
   {
      0x24420, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PivotItem =
   {
      0x20876, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PivotItems =
   {
      0x20877, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_CalculatedItems =
   {
      0x24421, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Characters =
   {
      0x20878, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Dialogs =
   {
      0x20879, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Dialog =
   {
      0x2087A, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_SoundNote =
   {
      0x2087B, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Button =
   {
      0x2087D, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Buttons =
   {
      0x2087E, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_CheckBox =
   {
      0x2087F, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_CheckBoxes =
   {
      0x20880, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_OptionButton =
   {
      0x20881, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_OptionButtons =
   {
      0x20882, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_EditBox =
   {
      0x20883, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_EditBoxes =
   {
      0x20884, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ScrollBar =
   {
      0x20885, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ScrollBars =
   {
      0x20886, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ListBox =
   {
      0x20887, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ListBoxes =
   {
      0x20888, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_GroupBox =
   {
      0x20889, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_GroupBoxes =
   {
      0x2088A, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DropDown =
   {
      0x2088B, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DropDowns =
   {
      0x2088C, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Spinner =
   {
      0x2088D, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Spinners =
   {
      0x2088E, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DialogFrame =
   {
      0x2088F, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Label =
   {
      0x20890, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Labels =
   {
      0x20891, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Panes =
   {
      0x20894, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Pane =
   {
      0x20895, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Scenarios =
   {
      0x20896, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Scenario =
   {
      0x20897, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_GroupObject =
   {
      0x20898, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_GroupObjects =
   {
      0x20899, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Line =
   {
      0x2089A, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Lines =
   {
      0x2089B, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Rectangle =
   {
      0x2089C, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Rectangles =
   {
      0x2089D, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Oval =
   {
      0x2089E, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Ovals =
   {
      0x2089F, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Arc =
   {
      0x208A0, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Arcs =
   {
      0x208A1, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_OLEObjects =
   {
      0x208A3, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_TextBox =
   {
      0x208A4, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_TextBoxes =
   {
      0x208A5, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Picture =
   {
      0x208A6, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Pictures =
   {
      0x208A7, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Drawing =
   {
      0x208A8, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Drawings =
   {
      0x208A9, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_RoutingSlip =
   {
      0x208AA, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Outline =
   {
      0x208AB, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Module =
   {
      0x208AD, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Modules =
   {
      0x208AE, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DialogSheet =
   {
      0x208AF, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DialogSheets =
   {
      0x208B0, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Worksheets =
   {
      0x208B1, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PageSetup =
   {
      0x208B4, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Names =
   {
      0x208B8, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Name =
   {
      0x208B9, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ChartObject =
   {
      0x208CF, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ChartObjects =
   {
      0x208D0, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Mailer =
   {
      0x208D1, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_CustomViews =
   {
      0x24422, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_CustomView =
   {
      0x24423, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_FormatConditions =
   {
      0x24424, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_FormatCondition =
   {
      0x24425, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Comments =
   {
      0x24426, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Comment =
   {
      0x24427, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_QueryTables =
   {
      0x24429, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Parameter =
   {
      0x2442A, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Parameters =
   {
      0x2442B, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ODBCError =
   {
      0x2442C, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ODBCErrors =
   {
      0x2442D, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Validation =
   {
      0x2442F, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Hyperlinks =
   {
      0x24430, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Hyperlink =
   {
      0x24431, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_AutoFilter =
   {
      0x24432, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Filters =
   {
      0x24433, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Filter =
   {
      0x24434, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_AutoCorrect =
   {
      0x208D4, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Border =
   {
      0x20854, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Interior =
   {
      0x20870, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ChartFillFormat =
   {
      0x24435, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ChartColorFormat =
   {
      0x24436, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Axis =
   {
      0x20848, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ChartTitle =
   {
      0x20849, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_AxisTitle =
   {
      0x2084A, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ChartGroup =
   {
      0x20859, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ChartGroups =
   {
      0x2085A, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Axes =
   {
      0x2085B, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Points =
   {
      0x20869, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Point =
   {
      0x2086A, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Series =
   {
      0x2086B, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_SeriesCollection =
   {
      0x2086C, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DataLabel =
   {
      0x208B2, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DataLabels =
   {
      0x208B3, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_LegendEntry =
   {
      0x208BA, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_LegendEntries =
   {
      0x208BB, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_LegendKey =
   {
      0x208BC, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Trendlines =
   {
      0x208BD, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Trendline =
   {
      0x208BE, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Corners =
   {
      0x208C0, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_SeriesLines =
   {
      0x208C1, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_HiLoLines =
   {
      0x208C2, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Gridlines =
   {
      0x208C3, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DropLines =
   {
      0x208C4, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_LeaderLines =
   {
      0x24437, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_UpBars =
   {
      0x208C5, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DownBars =
   {
      0x208C6, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Floor =
   {
      0x208C7, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Walls =
   {
      0x208C8, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_TickLabels =
   {
      0x208C9, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PlotArea =
   {
      0x208CB, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ChartArea =
   {
      0x208CC, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Legend =
   {
      0x208CD, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ErrorBars =
   {
      0x208CE, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DataTable =
   {
      0x20843, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Phonetic =
   {
      0x24438, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Shape =
   {
      0x24439, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Shapes =
   {
      0x2443A, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ShapeRange =
   {
      0x2443B, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_GroupShapes =
   {
      0x2443C, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_TextFrame =
   {
      0x2443D, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ConnectorFormat =
   {
      0x2443E, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_FreeformBuilder =
   {
      0x2443F, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ControlFormat =
   {
      0x24440, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_OLEFormat =
   {
      0x24441, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_LinkFormat =
   {
      0x24442, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PublishObjects =
   {
      0x24443, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_OLEDBError =
   {
      0x24445, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_OLEDBErrors =
   {
      0x24446, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Phonetics =
   {
      0x24447, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PivotLayout =
   {
      0x2444A, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DisplayUnitLabel =
   {
      0x2084C, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_CellFormat =
   {
      0x24450, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_UsedObjects =
   {
      0x24451, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_CustomProperties =
   {
      0x24452, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_CustomProperty =
   {
      0x24453, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_CalculatedMembers =
   {
      0x24454, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_CalculatedMember =
   {
      0x24455, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Watches =
   {
      0x24456, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Watch =
   {
      0x24457, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PivotCell =
   {
      0x24458, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Graphic =
   {
      0x24459, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_AutoRecover =
   {
      0x2445A, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ErrorCheckingOptions =
   {
      0x2445B, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Errors =
   {
      0x2445C, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Error =
   {
      0x2445D, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_SmartTagAction =
   {
      0x2445E, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_SmartTagActions =
   {
      0x2445F, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_SmartTag =
   {
      0x24460, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_SmartTags =
   {
      0x24461, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_SmartTagRecognizer =
   {
      0x24462, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_SmartTagRecognizers =
   {
      0x24463, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_SmartTagOptions =
   {
      0x24464, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_SpellingOptions =
   {
      0x24465, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Speech =
   {
      0x24466, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Protection =
   {
      0x24467, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_PivotItemList =
   {
      0x24468, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Tab =
   {
      0x24469, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_AllowEditRanges =
   {
      0x2446A, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_AllowEditRange =
   {
      0x2446B, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_UserAccessList =
   {
      0x2446C, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_UserAccess =
   {
      0x2446D, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_RTD =
   {
      0x2446E, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Diagram =
   {
      0x2446F, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ListObjects =
   {
      0x24470, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ListObject =
   {
      0x24471, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ListColumns =
   {
      0x24472, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ListColumn =
   {
      0x24473, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ListRows =
   {
      0x24474, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ListRow =
   {
      0x24475, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_XmlNamespace =
   {
      0x24476, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_XmlNamespaces =
   {
      0x24477, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_XmlDataBinding =
   {
      0x24478, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_XmlSchema =
   {
      0x24479, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_XmlSchemas =
   {
      0x2447A, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_XmlMap =
   {
      0x2447B, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_XmlMaps =
   {
      0x2447C, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_ListDataFormat =
   {
      0x2447D, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_XPath =
   {
      0x2447E, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Assistant =
   {
      0xC0322, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID__CommandBars =
   {
      0xC0302, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_FileSearch =
   {
      0xC0332, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_IFind =
   {
      0xC0337, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_VBE =
   {
      0x2E166, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_COMAddIns =
   {
      0xC0339, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_LanguageSettings =
   {
      0xC0353, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_AnswerWizard =
   {
      0xC0360, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_FileDialog =
   {
      0xC0362, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_NewFile =
   {
      0xC0936, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Scripts =
   {
      0xC0340, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_IMsoEnvelopeVB =
   {
      0x672AC, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID__VBProject =
   {
      0xEEE00915, 0xE393, 0x11D1, 0xBB, 0x3, 0x0, 0xC0, 0x4F, 0xB6, 0xC4, 0xA6
   };

const IID Excel_IID_HTMLProject =
   {
      0xC0356, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Permission =
   {
      0xC0376, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_SharedWorkspace =
   {
      0xC0385, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Sync =
   {
      0xC0386, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_SmartDocument =
   {
      0xC0377, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_DocumentLibraryVersions =
   {
      0xC0388, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_IMsoDiagram =
   {
      0xC036D, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_Script =
   {
      0xC0341, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_CanvasShapes =
   {
      0xC0371, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

const IID Excel_IID_WebPageFonts =
   {
      0xC0914, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46
   };

HRESULT CVIFUNC Excel_Get_ApplicationProperty (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               unsigned int propertyID,
                                               unsigned int propertyType,
                                               void *value)
{
   HRESULT __result = S_OK;

   __result = CA_PropertyGetEx (objectHandle, errorInfo, 0, propertyID,
                                propertyType, value);

   return __result;
}

HRESULT CVIFUNC Excel_Set_ApplicationProperty (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               unsigned int propertyID,
                                               unsigned int propertyType, ...)
{
   HRESULT __result = S_OK;
   va_list args;

   va_start (args, propertyType);

   __result = CA_PropertySetVEx (objectHandle, errorInfo, 0, propertyID,
                                 propertyType, args);

   va_end (args);

   return __result;
}

HRESULT CVIFUNC Excel_Set_ApplicationPropertyByRef (CAObjHandle objectHandle,
                                                    ERRORINFO *errorInfo,
                                                    unsigned int propertyID,
                                                    unsigned int propertyType,
                                                    ...)
{
   HRESULT __result = S_OK;
   va_list args;

   va_start (args, propertyType);

   __result = CA_PropertySetByRefVEx (objectHandle, errorInfo, 0, propertyID,
                                      propertyType, args);

   va_end (args);

   return __result;
}

HRESULT CVIFUNC Excel_Get_WorksheetProperty (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             unsigned int propertyID,
                                             unsigned int propertyType,
                                             void *value)
{
   HRESULT __result = S_OK;

   __result = CA_PropertyGetEx (objectHandle, errorInfo, 0, propertyID,
                                propertyType, value);

   return __result;
}

HRESULT CVIFUNC Excel_Set_WorksheetProperty (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             unsigned int propertyID,
                                             unsigned int propertyType, ...)
{
   HRESULT __result = S_OK;
   va_list args;

   va_start (args, propertyType);

   __result = CA_PropertySetVEx (objectHandle, errorInfo, 0, propertyID,
                                 propertyType, args);

   va_end (args);

   return __result;
}

HRESULT CVIFUNC Excel_Get_GlobalProperty (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          unsigned int propertyID,
                                          unsigned int propertyType, void *value)
{
   HRESULT __result = S_OK;

   __result = CA_PropertyGetEx (objectHandle, errorInfo, 0, propertyID,
                                propertyType, value);

   return __result;
}

HRESULT CVIFUNC Excel_Set_GlobalProperty (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          unsigned int propertyID,
                                          unsigned int propertyType, ...)
{
   HRESULT __result = S_OK;
   va_list args;

   va_start (args, propertyType);

   __result = CA_PropertySetVEx (objectHandle, errorInfo, 0, propertyID,
                                 propertyType, args);

   va_end (args);

   return __result;
}

HRESULT CVIFUNC Excel_Get_WorkbookProperty (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            unsigned int propertyID,
                                            unsigned int propertyType,
                                            void *value)
{
   HRESULT __result = S_OK;

   __result = CA_PropertyGetEx (objectHandle, errorInfo, 0, propertyID,
                                propertyType, value);

   return __result;
}

HRESULT CVIFUNC Excel_Set_WorkbookProperty (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            unsigned int propertyID,
                                            unsigned int propertyType, ...)
{
   HRESULT __result = S_OK;
   va_list args;

   va_start (args, propertyType);

   __result = CA_PropertySetVEx (objectHandle, errorInfo, 0, propertyID,
                                 propertyType, args);

   va_end (args);

   return __result;
}

HRESULT CVIFUNC Excel_GetSheetsProperty (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         unsigned int propertyID,
                                         unsigned int propertyType, void *value)
{
   HRESULT __result = S_OK;

   __result = CA_PropertyGetEx (objectHandle, errorInfo, 0, propertyID,
                                propertyType, value);

   return __result;
}

HRESULT CVIFUNC Excel_SetSheetsProperty (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         unsigned int propertyID,
                                         unsigned int propertyType, ...)
{
   HRESULT __result = S_OK;
   va_list args;

   va_start (args, propertyType);

   __result = CA_PropertySetVEx (objectHandle, errorInfo, 0, propertyID,
                                 propertyType, args);

   va_end (args);

   return __result;
}

HRESULT CVIFUNC Excel_GetWorkbooksProperty (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            unsigned int propertyID,
                                            unsigned int propertyType,
                                            void *value)
{
   HRESULT __result = S_OK;

   __result = CA_PropertyGetEx (objectHandle, errorInfo, 0, propertyID,
                                propertyType, value);

   return __result;
}

HRESULT CVIFUNC Excel_GetFontProperty (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo,
                                       unsigned int propertyID,
                                       unsigned int propertyType, void *value)
{
   HRESULT __result = S_OK;

   __result = CA_PropertyGetEx (objectHandle, errorInfo, 0, propertyID,
                                propertyType, value);

   return __result;
}

HRESULT CVIFUNC Excel_SetFontProperty (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo,
                                       unsigned int propertyID,
                                       unsigned int propertyType, ...)
{
   HRESULT __result = S_OK;
   va_list args;

   va_start (args, propertyType);

   __result = CA_PropertySetVEx (objectHandle, errorInfo, 0, propertyID,
                                 propertyType, args);

   va_end (args);

   return __result;
}

HRESULT CVIFUNC Excel_GetRangeProperty (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        unsigned int propertyID,
                                        unsigned int propertyType, void *value)
{
   HRESULT __result = S_OK;

   __result = CA_PropertyGetEx (objectHandle, errorInfo, 0, propertyID,
                                propertyType, value);

   return __result;
}

HRESULT CVIFUNC Excel_SetRangeProperty (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        unsigned int propertyID,
                                        unsigned int propertyType, ...)
{
   HRESULT __result = S_OK;
   va_list args;

   va_start (args, propertyType);

   __result = CA_PropertySetVEx (objectHandle, errorInfo, 0, propertyID,
                                 propertyType, args);

   va_end (args);

   return __result;
}

HRESULT CVIFUNC Excel_NewApp (const char *server, int supportMultithreading,
                              LCID locale, int reserved,
                              CAObjHandle *objectHandle)
{
   HRESULT __result = S_OK;
   GUID clsid = {0x24500, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46};

   __result = CA_CreateObjectByClassIdEx (&clsid, server, &Excel_IID_App,
                                          supportMultithreading, locale,
                                          reserved, objectHandle);

   return __result;
}

HRESULT CVIFUNC Excel_OpenApp (const char *fileName, const char *server,
                               int supportMultithreading, LCID locale,
                               int reserved, CAObjHandle *objectHandle)
{
   HRESULT __result = S_OK;
   GUID clsid = {0x24500, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46};

   __result = CA_LoadObjectFromFileByClassIdEx (fileName, &clsid, server,
                                                &Excel_IID_App,
                                                supportMultithreading, locale,
                                                reserved, objectHandle);

   return __result;
}

HRESULT CVIFUNC Excel_ActiveApp (const char *server, int supportMultithreading,
                                 LCID locale, int reserved,
                                 CAObjHandle *objectHandle)
{
   HRESULT __result = S_OK;
   GUID clsid = {0x24500, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46};

   __result = CA_GetActiveObjectByClassIdEx (&clsid, server, &Excel_IID_App,
                                             supportMultithreading, locale,
                                             reserved, objectHandle);

   return __result;
}

HRESULT CVIFUNC Excel_AppCalculate (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x117, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppDDEExecute (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, long channel,
                                     const char *string)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x14D, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 channel, string);

   return __result;
}

HRESULT CVIFUNC Excel_AppDDEInitiate (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, const char *app,
                                      const char *topic, long *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x14E, CAVT_LONG, returnValue, 2,
                                 __paramTypes, app, topic);

   return __result;
}

HRESULT CVIFUNC Excel_AppDDEPoke (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  long channel, VARIANT item, VARIANT data)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x14F, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 channel, item, data);

   return __result;
}

HRESULT CVIFUNC Excel_AppDDERequest (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, long channel,
                                     const char *item, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x150, CAVT_VARIANT, returnValue, 2,
                                 __paramTypes, channel, item);

   return __result;
}

HRESULT CVIFUNC Excel_AppDDETerminate (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, long channel)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x151, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 channel);

   return __result;
}

HRESULT CVIFUNC Excel_AppEvaluate (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT name,
                                   VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App, 0x1,
                                 CAVT_VARIANT, returnValue, 1, __paramTypes,
                                 name);

   return __result;
}

HRESULT CVIFUNC Excel_App_Evaluate (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT name,
                                    VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0xFFFFFFFB, CAVT_VARIANT, returnValue, 1,
                                 __paramTypes, name);

   return __result;
}

HRESULT CVIFUNC Excel_AppExecuteExcel4Macro (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             const char *string,
                                             VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x15E, CAVT_VARIANT, returnValue, 1,
                                 __paramTypes, string);

   return __result;
}

HRESULT CVIFUNC Excel_AppIntersect (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, ExcelObj_Range arg1,
                                    ExcelObj_Range arg2, VARIANT arg3,
                                    VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                    VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                    VARIANT arg10, VARIANT arg11, VARIANT arg12,
                                    VARIANT arg13, VARIANT arg14, VARIANT arg15,
                                    VARIANT arg16, VARIANT arg17, VARIANT arg18,
                                    VARIANT arg19, VARIANT arg20, VARIANT arg21,
                                    VARIANT arg22, VARIANT arg23, VARIANT arg24,
                                    VARIANT arg25, VARIANT arg26, VARIANT arg27,
                                    VARIANT arg28, VARIANT arg29, VARIANT arg30,
                                    ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_OBJHANDLE, CAVT_OBJHANDLE,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x2FE, CAVT_OBJHANDLE, returnValue, 30,
                                 __paramTypes, arg1, arg2, arg3, arg4, arg5,
                                 arg6, arg7, arg8, arg9, arg10, arg11, arg12,
                                 arg13, arg14, arg15, arg16, arg17, arg18,
                                 arg19, arg20, arg21, arg22, arg23, arg24,
                                 arg25, arg26, arg27, arg28, arg29, arg30);

   return __result;
}

HRESULT CVIFUNC Excel_AppRange (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                VARIANT cell1, VARIANT cell2,
                                ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0xC5, DISPATCH_PROPERTYGET, CAVT_OBJHANDLE,
                                 returnValue, 2, __paramTypes, cell1, cell2);

   return __result;
}

HRESULT CVIFUNC Excel_AppRun (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                              VARIANT macro, VARIANT arg1, VARIANT arg2,
                              VARIANT arg3, VARIANT arg4, VARIANT arg5,
                              VARIANT arg6, VARIANT arg7, VARIANT arg8,
                              VARIANT arg9, VARIANT arg10, VARIANT arg11,
                              VARIANT arg12, VARIANT arg13, VARIANT arg14,
                              VARIANT arg15, VARIANT arg16, VARIANT arg17,
                              VARIANT arg18, VARIANT arg19, VARIANT arg20,
                              VARIANT arg21, VARIANT arg22, VARIANT arg23,
                              VARIANT arg24, VARIANT arg25, VARIANT arg26,
                              VARIANT arg27, VARIANT arg28, VARIANT arg29,
                              VARIANT arg30, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x103, CAVT_VARIANT, returnValue, 31,
                                 __paramTypes, macro, arg1, arg2, arg3, arg4,
                                 arg5, arg6, arg7, arg8, arg9, arg10, arg11,
                                 arg12, arg13, arg14, arg15, arg16, arg17,
                                 arg18, arg19, arg20, arg21, arg22, arg23,
                                 arg24, arg25, arg26, arg27, arg28, arg29,
                                 arg30);

   return __result;
}

HRESULT CVIFUNC Excel_App_Run2 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                VARIANT macro, VARIANT arg1, VARIANT arg2,
                                VARIANT arg3, VARIANT arg4, VARIANT arg5,
                                VARIANT arg6, VARIANT arg7, VARIANT arg8,
                                VARIANT arg9, VARIANT arg10, VARIANT arg11,
                                VARIANT arg12, VARIANT arg13, VARIANT arg14,
                                VARIANT arg15, VARIANT arg16, VARIANT arg17,
                                VARIANT arg18, VARIANT arg19, VARIANT arg20,
                                VARIANT arg21, VARIANT arg22, VARIANT arg23,
                                VARIANT arg24, VARIANT arg25, VARIANT arg26,
                                VARIANT arg27, VARIANT arg28, VARIANT arg29,
                                VARIANT arg30, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x326, CAVT_VARIANT, returnValue, 31,
                                 __paramTypes, macro, arg1, arg2, arg3, arg4,
                                 arg5, arg6, arg7, arg8, arg9, arg10, arg11,
                                 arg12, arg13, arg14, arg15, arg16, arg17,
                                 arg18, arg19, arg20, arg21, arg22, arg23,
                                 arg24, arg25, arg26, arg27, arg28, arg29,
                                 arg30);

   return __result;
}

HRESULT CVIFUNC Excel_AppSendKeys (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT keys,
                                   VARIANT wait)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x17F, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 keys, wait);

   return __result;
}

HRESULT CVIFUNC Excel_AppShortcutMenus (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, long index,
                                        ExcelObj_Menu *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x308, DISPATCH_PROPERTYGET, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_AppUnion (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                ExcelObj_Range arg1, ExcelObj_Range arg2,
                                VARIANT arg3, VARIANT arg4, VARIANT arg5,
                                VARIANT arg6, VARIANT arg7, VARIANT arg8,
                                VARIANT arg9, VARIANT arg10, VARIANT arg11,
                                VARIANT arg12, VARIANT arg13, VARIANT arg14,
                                VARIANT arg15, VARIANT arg16, VARIANT arg17,
                                VARIANT arg18, VARIANT arg19, VARIANT arg20,
                                VARIANT arg21, VARIANT arg22, VARIANT arg23,
                                VARIANT arg24, VARIANT arg25, VARIANT arg26,
                                VARIANT arg27, VARIANT arg28, VARIANT arg29,
                                VARIANT arg30, ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_OBJHANDLE, CAVT_OBJHANDLE,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x30B, CAVT_OBJHANDLE, returnValue, 30,
                                 __paramTypes, arg1, arg2, arg3, arg4, arg5,
                                 arg6, arg7, arg8, arg9, arg10, arg11, arg12,
                                 arg13, arg14, arg15, arg16, arg17, arg18,
                                 arg19, arg20, arg21, arg22, arg23, arg24,
                                 arg25, arg26, arg27, arg28, arg29, arg30);

   return __result;
}

HRESULT CVIFUNC Excel_AppActivateMicrosoftApp (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               enum ExcelEnum_XlMSApplication index)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x447, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 index);

   return __result;
}

HRESULT CVIFUNC Excel_AppAddChartAutoFormat (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo, VARIANT chart,
                                             const char *name,
                                             VARIANT description)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_CSTRING, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0xD8, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 chart, name, description);

   return __result;
}

HRESULT CVIFUNC Excel_AppAddCustomList (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT listArray,
                                        VARIANT byRow)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x30C, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 listArray, byRow);

   return __result;
}

HRESULT CVIFUNC Excel_AppCaller (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT index, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x13D, DISPATCH_PROPERTYGET, CAVT_VARIANT,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_AppCentimetersToPoints (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              double centimeters,
                                              double *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_DOUBLE};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x43E, CAVT_DOUBLE, returnValue, 1,
                                 __paramTypes, centimeters);

   return __result;
}

HRESULT CVIFUNC Excel_AppCheckSpelling (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, const char *word,
                                        VARIANT customDictionary,
                                        VARIANT ignoreUppercase,
                                        VBOOL *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x1F9, CAVT_BOOL, returnValue, 3,
                                 __paramTypes, word, customDictionary,
                                 ignoreUppercase);

   return __result;
}

HRESULT CVIFUNC Excel_AppClipboardFormats (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT index,
                                           VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x141, DISPATCH_PROPERTYGET, CAVT_VARIANT,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_AppConvertFormula (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT formula,
                                         enum ExcelEnum_XlReferenceStyle fromReferenceStyle,
                                         VARIANT toReferenceStyle,
                                         VARIANT toAbsolute, VARIANT relativeTo,
                                         VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_LONG, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x145, CAVT_VARIANT, returnValue, 5,
                                 __paramTypes, formula, fromReferenceStyle,
                                 toReferenceStyle, toAbsolute, relativeTo);

   return __result;
}

HRESULT CVIFUNC Excel_AppDummy1 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT arg1, VARIANT arg2, VARIANT arg3,
                                 VARIANT arg4, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x6F6, CAVT_VARIANT, returnValue, 4,
                                 __paramTypes, arg1, arg2, arg3, arg4);

   return __result;
}

HRESULT CVIFUNC Excel_AppDummy2 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT arg1, VARIANT arg2, VARIANT arg3,
                                 VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                 VARIANT arg7, VARIANT arg8,
                                 VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x6F7, CAVT_VARIANT, returnValue, 8,
                                 __paramTypes, arg1, arg2, arg3, arg4, arg5,
                                 arg6, arg7, arg8);

   return __result;
}

HRESULT CVIFUNC Excel_AppDummy3 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x6F8, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppDummy4 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT arg1, VARIANT arg2, VARIANT arg3,
                                 VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                 VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                 VARIANT arg10, VARIANT arg11, VARIANT arg12,
                                 VARIANT arg13, VARIANT arg14, VARIANT arg15,
                                 VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x6F9, CAVT_VARIANT, returnValue, 15,
                                 __paramTypes, arg1, arg2, arg3, arg4, arg5,
                                 arg6, arg7, arg8, arg9, arg10, arg11, arg12,
                                 arg13, arg14, arg15);

   return __result;
}

HRESULT CVIFUNC Excel_AppDummy5 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT arg1, VARIANT arg2, VARIANT arg3,
                                 VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                 VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                 VARIANT arg10, VARIANT arg11, VARIANT arg12,
                                 VARIANT arg13, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x6FA, CAVT_VARIANT, returnValue, 13,
                                 __paramTypes, arg1, arg2, arg3, arg4, arg5,
                                 arg6, arg7, arg8, arg9, arg10, arg11, arg12,
                                 arg13);

   return __result;
}

HRESULT CVIFUNC Excel_AppDummy6 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x6FB, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppDummy7 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x6FC, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppDummy8 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT arg1, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x6FD, CAVT_VARIANT, returnValue, 1,
                                 __paramTypes, arg1);

   return __result;
}

HRESULT CVIFUNC Excel_AppDummy9 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x6FE, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppDummy10 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT arg, VBOOL *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x6FF, CAVT_BOOL, returnValue, 1,
                                 __paramTypes, arg);

   return __result;
}

HRESULT CVIFUNC Excel_AppDummy11 (CAObjHandle objectHandle, ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x700, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppDeleteChartAutoFormat (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                const char *name)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0xD9, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 name);

   return __result;
}

HRESULT CVIFUNC Excel_AppDeleteCustomList (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, long listNum)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x30F, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 listNum);

   return __result;
}

HRESULT CVIFUNC Excel_AppDoubleClick (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x15D, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppFileConverters (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT index1,
                                         VARIANT index2, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x3A3, DISPATCH_PROPERTYGET, CAVT_VARIANT,
                                 returnValue, 2, __paramTypes, index1, index2);

   return __result;
}

HRESULT CVIFUNC Excel_App_FindFile (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x42C, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppGetCustomListContents (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                long listNum,
                                                VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x312, CAVT_VARIANT, returnValue, 1,
                                 __paramTypes, listNum);

   return __result;
}

HRESULT CVIFUNC Excel_AppGetCustomListNum (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           VARIANT listArray, long *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x311, CAVT_LONG, returnValue, 1,
                                 __paramTypes, listArray);

   return __result;
}

HRESULT CVIFUNC Excel_AppGetOpenFilename (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT fileFilter,
                                          VARIANT filterIndex, VARIANT title,
                                          VARIANT buttonText,
                                          VARIANT multiSelect,
                                          VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x433, CAVT_VARIANT, returnValue, 5,
                                 __paramTypes, fileFilter, filterIndex, title,
                                 buttonText, multiSelect);

   return __result;
}

HRESULT CVIFUNC Excel_AppGetSaveAsFilename (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            VARIANT initialFilename,
                                            VARIANT fileFilter,
                                            VARIANT filterIndex, VARIANT title,
                                            VARIANT buttonText,
                                            VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x434, CAVT_VARIANT, returnValue, 5,
                                 __paramTypes, initialFilename, fileFilter,
                                 filterIndex, title, buttonText);

   return __result;
}

HRESULT CVIFUNC Excel_AppGoto (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                               VARIANT reference, VARIANT scroll)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x1DB, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 reference, scroll);

   return __result;
}

HRESULT CVIFUNC Excel_AppHelp (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                               VARIANT helpFile, VARIANT helpContextID)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x162, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 helpFile, helpContextID);

   return __result;
}

HRESULT CVIFUNC Excel_AppInchesToPoints (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, double inches,
                                         double *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_DOUBLE};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x43F, CAVT_DOUBLE, returnValue, 1,
                                 __paramTypes, inches);

   return __result;
}

HRESULT CVIFUNC Excel_AppInputBox (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, const char *prompt,
                                   VARIANT title, VARIANT _default, VARIANT left,
                                   VARIANT top, VARIANT helpFile,
                                   VARIANT helpContextID, VARIANT type,
                                   VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x165, CAVT_VARIANT, returnValue, 8,
                                 __paramTypes, prompt, title, _default, left,
                                 top, helpFile, helpContextID, type);

   return __result;
}

HRESULT CVIFUNC Excel_AppInternational (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT index,
                                        VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x16A, DISPATCH_PROPERTYGET, CAVT_VARIANT,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_AppMacroOptions (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT macro,
                                       VARIANT description, VARIANT hasMenu,
                                       VARIANT menuText, VARIANT hasShortcutKey,
                                       VARIANT shortcutKey, VARIANT category,
                                       VARIANT statusBar, VARIANT helpContextID,
                                       VARIANT helpFile)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x46F, CAVT_EMPTY, NULL, 10, __paramTypes,
                                 macro, description, hasMenu, menuText,
                                 hasShortcutKey, shortcutKey, category,
                                 statusBar, helpContextID, helpFile);

   return __result;
}

HRESULT CVIFUNC Excel_AppMailLogoff (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x3B1, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppMailLogon (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT name,
                                    VARIANT password, VARIANT downloadNewMail)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x3AF, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 name, password, downloadNewMail);

   return __result;
}

HRESULT CVIFUNC Excel_AppNextLetter (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo,
                                     ExcelObj_Workbook *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x3CC, CAVT_OBJHANDLE, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppOnKey (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                const char *key, VARIANT procedure)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x272, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 key, procedure);

   return __result;
}

HRESULT CVIFUNC Excel_AppOnRepeat (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, const char *text,
                                   const char *procedure)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x301, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 text, procedure);

   return __result;
}

HRESULT CVIFUNC Excel_AppOnTime (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT earliestTime, const char *procedure,
                                 VARIANT latestTime, VARIANT schedule)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_CSTRING, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x270, CAVT_EMPTY, NULL, 4, __paramTypes,
                                 earliestTime, procedure, latestTime,
                                 schedule);

   return __result;
}

HRESULT CVIFUNC Excel_AppOnUndo (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 const char *text, const char *procedure)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x302, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 text, procedure);

   return __result;
}

HRESULT CVIFUNC Excel_AppPreviousSelections (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo, VARIANT index,
                                             VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x17A, DISPATCH_PROPERTYGET, CAVT_VARIANT,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_AppQuit (CAObjHandle objectHandle, ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x12E, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppRecordMacro (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT basicCode,
                                      VARIANT xlmCode)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x305, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 basicCode, xlmCode);

   return __result;
}

HRESULT CVIFUNC Excel_AppRegisteredFunctions (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              VARIANT index1, VARIANT index2,
                                              VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x307, DISPATCH_PROPERTYGET, CAVT_VARIANT,
                                 returnValue, 2, __paramTypes, index1, index2);

   return __result;
}

HRESULT CVIFUNC Excel_AppRegisterXLL (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, const char *filename,
                                      VBOOL *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x1E, CAVT_BOOL, returnValue, 1,
                                 __paramTypes, filename);

   return __result;
}

HRESULT CVIFUNC Excel_AppRepeat (CAObjHandle objectHandle, ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x12D, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppResetTipWizard (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x3A0, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppSave (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                               VARIANT filename)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x11B, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 filename);

   return __result;
}

HRESULT CVIFUNC Excel_AppSaveWorkspace (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT filename)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0xD4, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 filename);

   return __result;
}

HRESULT CVIFUNC Excel_AppSetDefaultChart (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT formatName, VARIANT gallery)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0xDB, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 formatName, gallery);

   return __result;
}

HRESULT CVIFUNC Excel_AppUndo (CAObjHandle objectHandle, ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x12F, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppVolatile (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT _volatile)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x314, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 _volatile);

   return __result;
}

HRESULT CVIFUNC Excel_App_Wait (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                VARIANT time)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x189, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 time);

   return __result;
}

HRESULT CVIFUNC Excel_App_WSFunction (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT arg1,
                                      VARIANT arg2, VARIANT arg3, VARIANT arg4,
                                      VARIANT arg5, VARIANT arg6, VARIANT arg7,
                                      VARIANT arg8, VARIANT arg9, VARIANT arg10,
                                      VARIANT arg11, VARIANT arg12,
                                      VARIANT arg13, VARIANT arg14,
                                      VARIANT arg15, VARIANT arg16,
                                      VARIANT arg17, VARIANT arg18,
                                      VARIANT arg19, VARIANT arg20,
                                      VARIANT arg21, VARIANT arg22,
                                      VARIANT arg23, VARIANT arg24,
                                      VARIANT arg25, VARIANT arg26,
                                      VARIANT arg27, VARIANT arg28,
                                      VARIANT arg29, VARIANT arg30,
                                      VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0xA9, CAVT_VARIANT, returnValue, 30,
                                 __paramTypes, arg1, arg2, arg3, arg4, arg5,
                                 arg6, arg7, arg8, arg9, arg10, arg11, arg12,
                                 arg13, arg14, arg15, arg16, arg17, arg18,
                                 arg19, arg20, arg21, arg22, arg23, arg24,
                                 arg25, arg26, arg27, arg28, arg29, arg30);

   return __result;
}

HRESULT CVIFUNC Excel_AppWait (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                               VARIANT time, VBOOL *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x6EA, CAVT_BOOL, returnValue, 1,
                                 __paramTypes, time);

   return __result;
}

HRESULT CVIFUNC Excel_AppGetPhonetic (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT text,
                                      char **returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x703, CAVT_CSTRING, returnValue, 1,
                                 __paramTypes, text);

   return __result;
}

HRESULT CVIFUNC Excel_AppDummy12 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  ExcelObj_PivotTable p1, ExcelObj_PivotTable p2)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_OBJHANDLE, CAVT_OBJHANDLE};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x70B, CAVT_EMPTY, NULL, 2, __paramTypes, p1,
                                 p2);

   return __result;
}

HRESULT CVIFUNC Excel_AppCalculateFull (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x70D, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppFindFile (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VBOOL *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x6EB, CAVT_BOOL, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppDummy13 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT arg1, VARIANT arg2, VARIANT arg3,
                                  VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                  VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                  VARIANT arg10, VARIANT arg11, VARIANT arg12,
                                  VARIANT arg13, VARIANT arg14, VARIANT arg15,
                                  VARIANT arg16, VARIANT arg17, VARIANT arg18,
                                  VARIANT arg19, VARIANT arg20, VARIANT arg21,
                                  VARIANT arg22, VARIANT arg23, VARIANT arg24,
                                  VARIANT arg25, VARIANT arg26, VARIANT arg27,
                                  VARIANT arg28, VARIANT arg29, VARIANT arg30,
                                  VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x78D, CAVT_VARIANT, returnValue, 30,
                                 __paramTypes, arg1, arg2, arg3, arg4, arg5,
                                 arg6, arg7, arg8, arg9, arg10, arg11, arg12,
                                 arg13, arg14, arg15, arg16, arg17, arg18,
                                 arg19, arg20, arg21, arg22, arg23, arg24,
                                 arg25, arg26, arg27, arg28, arg29, arg30);

   return __result;
}

HRESULT CVIFUNC Excel_AppFileDialog (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo,
                                     enum ExcelEnum_MsoFileDialogType fileDialogType,
                                     ExcelObj_FileDialog *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x796, DISPATCH_PROPERTYGET, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, fileDialogType);

   return __result;
}

HRESULT CVIFUNC Excel_AppDummy14 (CAObjHandle objectHandle, ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x798, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppCalculateFullRebuild (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x799, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_AppCheckAbort (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT keepAbort)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x7A0, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 keepAbort);

   return __result;
}

HRESULT CVIFUNC Excel_AppDisplayXMLSourcePane (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               VARIANT xmlMap)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x8CC, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 xmlMap);

   return __result;
}

HRESULT CVIFUNC Excel_AppSupport (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  CAObjHandle object, long ID, VARIANT arg,
                                  VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_OBJHANDLE, CAVT_LONG, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_App,
                                 0x8CF, CAVT_VARIANT, returnValue, 3,
                                 __paramTypes, object, ID, arg);

   return __result;
}

HRESULT CVIFUNC Excel_NewWorksheet (int panel, const char *label, int top,
                                    int left, int *controlID, int *UILError)
{
   HRESULT __result = S_OK;
   int ctrlId;
   GUID clsid = {0x20820, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46};
   const char * licStr = NULL;

   ctrlId = NewActiveXCtrl (panel, label, top, left, &clsid, &IID_IDispatch,
                            licStr, &__result);

   __ActiveXCtrlErrorHandler();

   return __result;
}

HRESULT CVIFUNC Excel_OpenWorksheet (const char *fileName, int panel,
                                     const char *label, int top, int left,
                                     int *controlID, int *UILError)
{
   HRESULT __result = S_OK;
   int ctrlId;

   ctrlId = NewActiveXCtrlFromFile (panel, label, top, left, fileName,
                                    &IID_IDispatch, &__result);

   __ActiveXCtrlErrorHandler();

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetActivate (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x130, CAVT_EMPTY,
                                 NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetCopy (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT before,
                                     VARIANT after)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x227, CAVT_EMPTY,
                                 NULL, 2, __paramTypes, before, after);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetDelete (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x75, CAVT_EMPTY, NULL,
                                 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetMove (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT before,
                                     VARIANT after)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x27D, CAVT_EMPTY,
                                 NULL, 2, __paramTypes, before, after);

   return __result;
}

HRESULT CVIFUNC Excel_Worksheet_PrintOut (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT from,
                                          VARIANT to, VARIANT copies,
                                          VARIANT preview, VARIANT activePrinter,
                                          VARIANT printToFile, VARIANT collate)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x389, CAVT_EMPTY,
                                 NULL, 7, __paramTypes, from, to, copies,
                                 preview, activePrinter, printToFile, collate);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetPrintPreview (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             VARIANT enableChanges)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x119, CAVT_EMPTY,
                                 NULL, 1, __paramTypes, enableChanges);

   return __result;
}

HRESULT CVIFUNC Excel_Worksheet_Protect (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT password,
                                         VARIANT drawingObjects,
                                         VARIANT contents, VARIANT scenarios,
                                         VARIANT userInterfaceOnly)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x11A, CAVT_EMPTY,
                                 NULL, 5, __paramTypes, password,
                                 drawingObjects, contents, scenarios,
                                 userInterfaceOnly);

   return __result;
}

HRESULT CVIFUNC Excel_Worksheet_SaveAs (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        const char *filename, VARIANT fileFormat,
                                        VARIANT password,
                                        VARIANT writeResPassword,
                                        VARIANT readOnlyRecommended,
                                        VARIANT createBackup, VARIANT addToMru,
                                        VARIANT textCodepage,
                                        VARIANT textVisualLayout)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x11C, CAVT_EMPTY,
                                 NULL, 9, __paramTypes, filename, fileFormat,
                                 password, writeResPassword,
                                 readOnlyRecommended, createBackup, addToMru,
                                 textCodepage, textVisualLayout);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetSelect (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT replace)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0xEB, CAVT_EMPTY, NULL,
                                 1, __paramTypes, replace);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetUnprotect (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT password)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x11D, CAVT_EMPTY,
                                 NULL, 1, __paramTypes, password);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetArcs (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT index,
                                     CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x2F8, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetSetBackgroundPicture (CAObjHandle objectHandle,
                                                     ERRORINFO *errorInfo,
                                                     const char *filename)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x4A4, CAVT_EMPTY,
                                 NULL, 1, __paramTypes, filename);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetButtons (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT index,
                                        CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x22D, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetCalculate (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x117, CAVT_EMPTY,
                                 NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetChartObjects (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo, VARIANT index,
                                             CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x424, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetCheckBoxes (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT index,
                                           CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x338, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetCheckSpelling (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              VARIANT customDictionary,
                                              VARIANT ignoreUppercase,
                                              VARIANT alwaysSuggest,
                                              VARIANT spellLang)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x1F9, CAVT_EMPTY,
                                 NULL, 4, __paramTypes, customDictionary,
                                 ignoreUppercase, alwaysSuggest, spellLang);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetClearArrows (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x3CA, CAVT_EMPTY,
                                 NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetDrawings (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT index,
                                         CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x304, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetDrawingObjects (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               VARIANT index,
                                               CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x58, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetDropDowns (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT index,
                                          CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x344, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetEvaluate (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT name,
                                         VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x1, CAVT_VARIANT,
                                 returnValue, 1, __paramTypes, name);

   return __result;
}

HRESULT CVIFUNC Excel_Worksheet_Evaluate (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT name,
                                          VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0xFFFFFFFB,
                                 CAVT_VARIANT, returnValue, 1, __paramTypes,
                                 name);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetResetAllPageBreaks (CAObjHandle objectHandle,
                                                   ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x592, CAVT_EMPTY,
                                 NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetGroupBoxes (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT index,
                                           CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x342, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetGroupObjects (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo, VARIANT index,
                                             CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x459, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetLabels (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT index,
                                       CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x349, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetLines (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT index,
                                      CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x2FF, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetListBoxes (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT index,
                                          CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x340, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetOLEObjects (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT index,
                                           CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x31F, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetOptionButtons (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              VARIANT index,
                                              CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x33A, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetOvals (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT index,
                                      CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x321, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetPaste (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT destination,
                                      VARIANT link)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0xD3, CAVT_EMPTY, NULL,
                                 2, __paramTypes, destination, link);

   return __result;
}

HRESULT CVIFUNC Excel_Worksheet_PasteSpecial (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              VARIANT format, VARIANT link,
                                              VARIANT displayAsIcon,
                                              VARIANT iconFileName,
                                              VARIANT iconIndex,
                                              VARIANT iconLabel)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x403, CAVT_EMPTY,
                                 NULL, 6, __paramTypes, format, link,
                                 displayAsIcon, iconFileName, iconIndex,
                                 iconLabel);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetPictures (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT index,
                                         CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x303, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetPivotTables (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo, VARIANT index,
                                            CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x2B2, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetPivotTableWizard (CAObjHandle objectHandle,
                                                 ERRORINFO *errorInfo,
                                                 VARIANT sourceType,
                                                 VARIANT sourceData,
                                                 VARIANT tableDestination,
                                                 VARIANT tableName,
                                                 VARIANT rowGrand,
                                                 VARIANT columnGrand,
                                                 VARIANT saveData,
                                                 VARIANT hasAutoFormat,
                                                 VARIANT autoPage,
                                                 VARIANT reserved,
                                                 VARIANT backgroundQuery,
                                                 VARIANT optimizeCache,
                                                 VARIANT pageFieldOrder,
                                                 VARIANT pageFieldWrapCount,
                                                 VARIANT readData,
                                                 VARIANT connection,
                                                 ExcelObj_PivotTable *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x2AC, CAVT_OBJHANDLE,
                                 returnValue, 16, __paramTypes, sourceType,
                                 sourceData, tableDestination, tableName,
                                 rowGrand, columnGrand, saveData,
                                 hasAutoFormat, autoPage, reserved,
                                 backgroundQuery, optimizeCache,
                                 pageFieldOrder, pageFieldWrapCount, readData,
                                 connection);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetRange (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT cell1,
                                      VARIANT cell2, ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0xC5,
                                 DISPATCH_PROPERTYGET, CAVT_OBJHANDLE,
                                 returnValue, 2, __paramTypes, cell1, cell2);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetRectangles (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT index,
                                           CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x306, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetScenarios (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT index,
                                          CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x38C, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetScrollBars (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT index,
                                           CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x33E, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetShowAllData (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x31A, CAVT_EMPTY,
                                 NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetShowDataForm (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x199, CAVT_EMPTY,
                                 NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetSpinners (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT index,
                                         CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x346, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetTextBoxes (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT index,
                                          CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x309, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetClearCircles (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x59C, CAVT_EMPTY,
                                 NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetCircleInvalid (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x59D, CAVT_EMPTY,
                                 NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetPrintOut (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT from,
                                         VARIANT to, VARIANT copies,
                                         VARIANT preview, VARIANT activePrinter,
                                         VARIANT printToFile, VARIANT collate,
                                         VARIANT prToFileName)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x6EC, CAVT_EMPTY,
                                 NULL, 8, __paramTypes, from, to, copies,
                                 preview, activePrinter, printToFile, collate,
                                 prToFileName);

   return __result;
}

HRESULT CVIFUNC Excel_Worksheet_CheckSpelling (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               VARIANT customDictionary,
                                               VARIANT ignoreUppercase,
                                               VARIANT alwaysSuggest,
                                               VARIANT spellLang,
                                               VARIANT ignoreFinalYaa,
                                               VARIANT spellScript)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x719, CAVT_EMPTY,
                                 NULL, 6, __paramTypes, customDictionary,
                                 ignoreUppercase, alwaysSuggest, spellLang,
                                 ignoreFinalYaa, spellScript);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetSaveAs (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo,
                                       const char *filename, VARIANT fileFormat,
                                       VARIANT password,
                                       VARIANT writeResPassword,
                                       VARIANT readOnlyRecommended,
                                       VARIANT createBackup, VARIANT addToMru,
                                       VARIANT textCodepage,
                                       VARIANT textVisualLayout, VARIANT local)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x785, CAVT_EMPTY,
                                 NULL, 10, __paramTypes, filename, fileFormat,
                                 password, writeResPassword,
                                 readOnlyRecommended, createBackup, addToMru,
                                 textCodepage, textVisualLayout, local);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetPasteSpecial (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             VARIANT format, VARIANT link,
                                             VARIANT displayAsIcon,
                                             VARIANT iconFileName,
                                             VARIANT iconIndex,
                                             VARIANT iconLabel,
                                             VARIANT noHTMLFormatting)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x788, CAVT_EMPTY,
                                 NULL, 7, __paramTypes, format, link,
                                 displayAsIcon, iconFileName, iconIndex,
                                 iconLabel, noHTMLFormatting);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetProtect (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT password,
                                        VARIANT drawingObjects, VARIANT contents,
                                        VARIANT scenarios,
                                        VARIANT userInterfaceOnly,
                                        VARIANT allowFormattingCells,
                                        VARIANT allowFormattingColumns,
                                        VARIANT allowFormattingRows,
                                        VARIANT allowInsertingColumns,
                                        VARIANT allowInsertingRows,
                                        VARIANT allowInsertingHyperlinks,
                                        VARIANT allowDeletingColumns,
                                        VARIANT allowDeletingRows,
                                        VARIANT allowSorting,
                                        VARIANT allowFiltering,
                                        VARIANT allowUsingPivotTables)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x7ED, CAVT_EMPTY,
                                 NULL, 16, __paramTypes, password,
                                 drawingObjects, contents, scenarios,
                                 userInterfaceOnly, allowFormattingCells,
                                 allowFormattingColumns, allowFormattingRows,
                                 allowInsertingColumns, allowInsertingRows,
                                 allowInsertingHyperlinks,
                                 allowDeletingColumns, allowDeletingRows,
                                 allowSorting, allowFiltering,
                                 allowUsingPivotTables);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetXmlDataQuery (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             const char *XPath,
                                             VARIANT selectionNamespaces,
                                             VARIANT map,
                                             ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x8D4, CAVT_OBJHANDLE,
                                 returnValue, 3, __paramTypes, XPath,
                                 selectionNamespaces, map);

   return __result;
}

HRESULT CVIFUNC Excel_WorksheetXmlMapQuery (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            const char *XPath,
                                            VARIANT selectionNamespaces,
                                            VARIANT map,
                                            ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Worksheet, 0x8D7, CAVT_OBJHANDLE,
                                 returnValue, 3, __paramTypes, XPath,
                                 selectionNamespaces, map);

   return __result;
}

HRESULT CVIFUNC Excel_NewGlobal (const char *server, int supportMultithreading,
                                 LCID locale, int reserved,
                                 CAObjHandle *objectHandle)
{
   HRESULT __result = S_OK;
   GUID clsid = {0x20812, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46};

   __result = CA_CreateObjectByClassIdEx (&clsid, server, &Excel_IID_Global,
                                          supportMultithreading, locale,
                                          reserved, objectHandle);

   return __result;
}

HRESULT CVIFUNC Excel_OpenGlobal (const char *fileName, const char *server,
                                  int supportMultithreading, LCID locale,
                                  int reserved, CAObjHandle *objectHandle)
{
   HRESULT __result = S_OK;
   GUID clsid = {0x20812, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46};

   __result = CA_LoadObjectFromFileByClassIdEx (fileName, &clsid, server,
                                                &Excel_IID_Global,
                                                supportMultithreading, locale,
                                                reserved, objectHandle);

   return __result;
}

HRESULT CVIFUNC Excel_ActiveGlobal (const char *server,
                                    int supportMultithreading, LCID locale,
                                    int reserved, CAObjHandle *objectHandle)
{
   HRESULT __result = S_OK;
   GUID clsid = {0x20812, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46};

   __result = CA_GetActiveObjectByClassIdEx (&clsid, server,
                                             &Excel_IID_Global,
                                             supportMultithreading, locale,
                                             reserved, objectHandle);

   return __result;
}

HRESULT CVIFUNC Excel_GlobalCalculate (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0x117, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_GlobalDDEExecute (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, long channel,
                                        const char *string)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0x14D, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 channel, string);

   return __result;
}

HRESULT CVIFUNC Excel_GlobalDDEInitiate (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, const char *app,
                                         const char *topic, long *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0x14E, CAVT_LONG, returnValue, 2,
                                 __paramTypes, app, topic);

   return __result;
}

HRESULT CVIFUNC Excel_GlobalDDEPoke (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, long channel,
                                     VARIANT item, VARIANT data)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0x14F, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 channel, item, data);

   return __result;
}

HRESULT CVIFUNC Excel_GlobalDDERequest (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, long channel,
                                        const char *item, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0x150, CAVT_VARIANT, returnValue, 2,
                                 __paramTypes, channel, item);

   return __result;
}

HRESULT CVIFUNC Excel_GlobalDDETerminate (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, long channel)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0x151, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 channel);

   return __result;
}

HRESULT CVIFUNC Excel_GlobalEvaluate (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT name,
                                      VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0x1, CAVT_VARIANT, returnValue, 1,
                                 __paramTypes, name);

   return __result;
}

HRESULT CVIFUNC Excel_Global_Evaluate (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT name,
                                       VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0xFFFFFFFB, CAVT_VARIANT, returnValue, 1,
                                 __paramTypes, name);

   return __result;
}

HRESULT CVIFUNC Excel_GlobalExecuteExcel4Macro (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                const char *string,
                                                VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0x15E, CAVT_VARIANT, returnValue, 1,
                                 __paramTypes, string);

   return __result;
}

HRESULT CVIFUNC Excel_GlobalIntersect (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, ExcelObj_Range arg1,
                                       ExcelObj_Range arg2, VARIANT arg3,
                                       VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                       VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                       VARIANT arg10, VARIANT arg11,
                                       VARIANT arg12, VARIANT arg13,
                                       VARIANT arg14, VARIANT arg15,
                                       VARIANT arg16, VARIANT arg17,
                                       VARIANT arg18, VARIANT arg19,
                                       VARIANT arg20, VARIANT arg21,
                                       VARIANT arg22, VARIANT arg23,
                                       VARIANT arg24, VARIANT arg25,
                                       VARIANT arg26, VARIANT arg27,
                                       VARIANT arg28, VARIANT arg29,
                                       VARIANT arg30,
                                       ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_OBJHANDLE, CAVT_OBJHANDLE,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0x2FE, CAVT_OBJHANDLE, returnValue, 30,
                                 __paramTypes, arg1, arg2, arg3, arg4, arg5,
                                 arg6, arg7, arg8, arg9, arg10, arg11, arg12,
                                 arg13, arg14, arg15, arg16, arg17, arg18,
                                 arg19, arg20, arg21, arg22, arg23, arg24,
                                 arg25, arg26, arg27, arg28, arg29, arg30);

   return __result;
}

HRESULT CVIFUNC Excel_GlobalRange (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT cell1,
                                   VARIANT cell2, ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0xC5, DISPATCH_PROPERTYGET, CAVT_OBJHANDLE,
                                 returnValue, 2, __paramTypes, cell1, cell2);

   return __result;
}

HRESULT CVIFUNC Excel_GlobalRun (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT macro, VARIANT arg1, VARIANT arg2,
                                 VARIANT arg3, VARIANT arg4, VARIANT arg5,
                                 VARIANT arg6, VARIANT arg7, VARIANT arg8,
                                 VARIANT arg9, VARIANT arg10, VARIANT arg11,
                                 VARIANT arg12, VARIANT arg13, VARIANT arg14,
                                 VARIANT arg15, VARIANT arg16, VARIANT arg17,
                                 VARIANT arg18, VARIANT arg19, VARIANT arg20,
                                 VARIANT arg21, VARIANT arg22, VARIANT arg23,
                                 VARIANT arg24, VARIANT arg25, VARIANT arg26,
                                 VARIANT arg27, VARIANT arg28, VARIANT arg29,
                                 VARIANT arg30, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0x103, CAVT_VARIANT, returnValue, 31,
                                 __paramTypes, macro, arg1, arg2, arg3, arg4,
                                 arg5, arg6, arg7, arg8, arg9, arg10, arg11,
                                 arg12, arg13, arg14, arg15, arg16, arg17,
                                 arg18, arg19, arg20, arg21, arg22, arg23,
                                 arg24, arg25, arg26, arg27, arg28, arg29,
                                 arg30);

   return __result;
}

HRESULT CVIFUNC Excel_Global_Run2 (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT macro,
                                   VARIANT arg1, VARIANT arg2, VARIANT arg3,
                                   VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                   VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                   VARIANT arg10, VARIANT arg11, VARIANT arg12,
                                   VARIANT arg13, VARIANT arg14, VARIANT arg15,
                                   VARIANT arg16, VARIANT arg17, VARIANT arg18,
                                   VARIANT arg19, VARIANT arg20, VARIANT arg21,
                                   VARIANT arg22, VARIANT arg23, VARIANT arg24,
                                   VARIANT arg25, VARIANT arg26, VARIANT arg27,
                                   VARIANT arg28, VARIANT arg29, VARIANT arg30,
                                   VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0x326, CAVT_VARIANT, returnValue, 31,
                                 __paramTypes, macro, arg1, arg2, arg3, arg4,
                                 arg5, arg6, arg7, arg8, arg9, arg10, arg11,
                                 arg12, arg13, arg14, arg15, arg16, arg17,
                                 arg18, arg19, arg20, arg21, arg22, arg23,
                                 arg24, arg25, arg26, arg27, arg28, arg29,
                                 arg30);

   return __result;
}

HRESULT CVIFUNC Excel_GlobalSendKeys (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT keys,
                                      VARIANT wait)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0x17F, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 keys, wait);

   return __result;
}

HRESULT CVIFUNC Excel_GlobalShortcutMenus (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, long index,
                                           ExcelObj_Menu *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0x308, DISPATCH_PROPERTYGET, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_GlobalUnion (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, ExcelObj_Range arg1,
                                   ExcelObj_Range arg2, VARIANT arg3,
                                   VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                   VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                   VARIANT arg10, VARIANT arg11, VARIANT arg12,
                                   VARIANT arg13, VARIANT arg14, VARIANT arg15,
                                   VARIANT arg16, VARIANT arg17, VARIANT arg18,
                                   VARIANT arg19, VARIANT arg20, VARIANT arg21,
                                   VARIANT arg22, VARIANT arg23, VARIANT arg24,
                                   VARIANT arg25, VARIANT arg26, VARIANT arg27,
                                   VARIANT arg28, VARIANT arg29, VARIANT arg30,
                                   ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_OBJHANDLE, CAVT_OBJHANDLE,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Global,
                                 0x30B, CAVT_OBJHANDLE, returnValue, 30,
                                 __paramTypes, arg1, arg2, arg3, arg4, arg5,
                                 arg6, arg7, arg8, arg9, arg10, arg11, arg12,
                                 arg13, arg14, arg15, arg16, arg17, arg18,
                                 arg19, arg20, arg21, arg22, arg23, arg24,
                                 arg25, arg26, arg27, arg28, arg29, arg30);

   return __result;
}

HRESULT CVIFUNC Excel_NewWorkbook (const char *server, int supportMultithreading,
                                   LCID locale, int reserved,
                                   CAObjHandle *objectHandle)
{
   HRESULT __result = S_OK;
   GUID clsid = {0x20819, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46};

   __result = CA_CreateObjectByClassIdEx (&clsid, server, &Excel_IID_Workbook,
                                          supportMultithreading, locale,
                                          reserved, objectHandle);

   return __result;
}

HRESULT CVIFUNC Excel_OpenWorkbook (const char *fileName, const char *server,
                                    int supportMultithreading, LCID locale,
                                    int reserved, CAObjHandle *objectHandle)
{
   HRESULT __result = S_OK;
   GUID clsid = {0x20819, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46};

   __result = CA_LoadObjectFromFileByClassIdEx (fileName, &clsid, server,
                                                &Excel_IID_Workbook,
                                                supportMultithreading, locale,
                                                reserved, objectHandle);

   return __result;
}

HRESULT CVIFUNC Excel_ActiveWorkbook (const char *server,
                                      int supportMultithreading, LCID locale,
                                      int reserved, CAObjHandle *objectHandle)
{
   HRESULT __result = S_OK;
   GUID clsid = {0x20819, 0x0, 0x0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46};

   __result = CA_GetActiveObjectByClassIdEx (&clsid, server,
                                             &Excel_IID_Workbook,
                                             supportMultithreading, locale,
                                             reserved, objectHandle);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookActivate (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x130, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookChangeFileAccess (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                enum ExcelEnum_XlFileAccess mode,
                                                VARIANT writePassword,
                                                VARIANT notify)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x3DD, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 mode, writePassword, notify);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookChangeLink (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, const char *name,
                                          const char *newName,
                                          enum ExcelEnum_XlLinkType type)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_CSTRING, CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x322, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 name, newName, type);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookClose (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT saveChanges,
                                     VARIANT filename, VARIANT routeWorkbook)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x115, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 saveChanges, filename, routeWorkbook);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookGetColors (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT index,
                                         VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x11E, DISPATCH_PROPERTYGET, CAVT_VARIANT,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookSetColors (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT index,
                                         VARIANT newValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x11E, DISPATCH_PROPERTYPUT, CAVT_EMPTY,
                                 NULL, 2, __paramTypes, index, newValue);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookDeleteNumberFormat (CAObjHandle objectHandle,
                                                  ERRORINFO *errorInfo,
                                                  const char *numberFormat)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x18D, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 numberFormat);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookExclusiveAccess (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               VBOOL *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x490, CAVT_BOOL, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookForwardMailer (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x3CD, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookLinkInfo (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, const char *name,
                                        enum ExcelEnum_XlLinkInfo linkInfo,
                                        VARIANT type, VARIANT editionRef,
                                        VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_LONG, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x327, CAVT_VARIANT, returnValue, 4,
                                 __paramTypes, name, linkInfo, type,
                                 editionRef);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookLinkSources (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT type,
                                           VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x328, CAVT_VARIANT, returnValue, 1,
                                 __paramTypes, type);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookMergeWorkbook (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             VARIANT filename)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x5A6, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 filename);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookNewWindow (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         ExcelObj_Window *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x118, CAVT_OBJHANDLE, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookOpenLinks (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, const char *name,
                                         VARIANT readOnly, VARIANT type)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x323, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 name, readOnly, type);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookPivotCaches (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           ExcelObj_PivotCaches *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x5A9, CAVT_OBJHANDLE, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookPost (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT destName)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x48E, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 destName);

   return __result;
}

HRESULT CVIFUNC Excel_Workbook_PrintOut (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT from,
                                         VARIANT to, VARIANT copies,
                                         VARIANT preview, VARIANT activePrinter,
                                         VARIANT printToFile, VARIANT collate)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x389, CAVT_EMPTY, NULL, 7, __paramTypes,
                                 from, to, copies, preview, activePrinter,
                                 printToFile, collate);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookPrintPreview (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            VARIANT enableChanges)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x119, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 enableChanges);

   return __result;
}

HRESULT CVIFUNC Excel_Workbook_Protect (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT password,
                                        VARIANT structure, VARIANT windows)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x11A, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 password, structure, windows);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookProtectSharing (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              VARIANT filename, VARIANT password,
                                              VARIANT writeResPassword,
                                              VARIANT readOnlyRecommended,
                                              VARIANT createBackup,
                                              VARIANT sharingPassword)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x5AA, CAVT_EMPTY, NULL, 6, __paramTypes,
                                 filename, password, writeResPassword,
                                 readOnlyRecommended, createBackup,
                                 sharingPassword);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookRefreshAll (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x5AC, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookReply (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x3D1, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookReplyAll (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x3D2, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookRemoveUser (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, long index)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x5AD, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 index);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookRoute (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x3B2, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookRunAutoMacros (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             enum ExcelEnum_XlRunAutoMacro which)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x27A, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 which);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookSave (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x11B, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_Workbook_SaveAs (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT filename,
                                       VARIANT fileFormat, VARIANT password,
                                       VARIANT writeResPassword,
                                       VARIANT readOnlyRecommended,
                                       VARIANT createBackup,
                                       enum ExcelEnum_XlSaveAsAccessMode accessMode,
                                       VARIANT conflictResolution,
                                       VARIANT addToMru, VARIANT textCodepage,
                                       VARIANT textVisualLayout)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_LONG, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x11C, CAVT_EMPTY, NULL, 11, __paramTypes,
                                 filename, fileFormat, password,
                                 writeResPassword, readOnlyRecommended,
                                 createBackup, accessMode, conflictResolution,
                                 addToMru, textCodepage, textVisualLayout);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookSaveCopyAs (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT filename)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0xAF, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 filename);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookSendMail (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT recipients,
                                        VARIANT subject, VARIANT returnReceipt)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x3B3, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 recipients, subject, returnReceipt);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookSendMailer (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT fileFormat,
                                          enum ExcelEnum_XlPriority priority)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x3D4, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 fileFormat, priority);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookSetLinkOnData (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             const char *name, VARIANT procedure)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x329, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 name, procedure);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookUnprotect (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT password)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x11D, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 password);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookUnprotectSharing (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                VARIANT sharingPassword)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x5AF, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 sharingPassword);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookUpdateFromFile (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x3E3, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookUpdateLink (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT name,
                                          VARIANT type)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x324, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 name, type);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookHighlightChangesOptions (CAObjHandle objectHandle,
                                                       ERRORINFO *errorInfo,
                                                       VARIANT when, VARIANT who,
                                                       VARIANT where)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x5B2, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 when, who, where);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookPurgeChangeHistoryNow (CAObjHandle objectHandle,
                                                     ERRORINFO *errorInfo,
                                                     long days,
                                                     VARIANT sharingPassword)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x5B8, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 days, sharingPassword);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookAcceptAllChanges (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                VARIANT when, VARIANT who,
                                                VARIANT where)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x5BA, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 when, who, where);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookRejectAllChanges (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                VARIANT when, VARIANT who,
                                                VARIANT where)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x5BB, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 when, who, where);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookPivotTableWizard (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                VARIANT sourceType,
                                                VARIANT sourceData,
                                                VARIANT tableDestination,
                                                VARIANT tableName,
                                                VARIANT rowGrand,
                                                VARIANT columnGrand,
                                                VARIANT saveData,
                                                VARIANT hasAutoFormat,
                                                VARIANT autoPage,
                                                VARIANT reserved,
                                                VARIANT backgroundQuery,
                                                VARIANT optimizeCache,
                                                VARIANT pageFieldOrder,
                                                VARIANT pageFieldWrapCount,
                                                VARIANT readData,
                                                VARIANT connection)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x2AC, CAVT_EMPTY, NULL, 16, __paramTypes,
                                 sourceType, sourceData, tableDestination,
                                 tableName, rowGrand, columnGrand, saveData,
                                 hasAutoFormat, autoPage, reserved,
                                 backgroundQuery, optimizeCache,
                                 pageFieldOrder, pageFieldWrapCount, readData,
                                 connection);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookResetColors (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x5BC, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookFollowHyperlink (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               const char *address,
                                               VARIANT subAddress,
                                               VARIANT newWindow,
                                               VARIANT addHistory,
                                               VARIANT extraInfo, VARIANT method,
                                               VARIANT headerInfo)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x5BE, CAVT_EMPTY, NULL, 7, __paramTypes,
                                 address, subAddress, newWindow, addHistory,
                                 extraInfo, method, headerInfo);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookAddToFavorites (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x5C4, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookPrintOut (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT from,
                                        VARIANT to, VARIANT copies,
                                        VARIANT preview, VARIANT activePrinter,
                                        VARIANT printToFile, VARIANT collate,
                                        VARIANT prToFileName)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x6EC, CAVT_EMPTY, NULL, 8, __paramTypes,
                                 from, to, copies, preview, activePrinter,
                                 printToFile, collate, prToFileName);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookWebPagePreview (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x71A, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookReloadAs (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        enum ExcelEnum_MsoEncoding encoding)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x71D, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 encoding);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookDummy17 (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, long calcid)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x7FC, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 calcid);

   return __result;
}

HRESULT CVIFUNC Excel_Workbooksblt (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, const char *s)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x722, CAVT_EMPTY, NULL, 1, __paramTypes, s);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookBreakLink (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, const char *name,
                                         enum ExcelEnum_XlLinkType type)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x7FF, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 name, type);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookDummy16 (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x800, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookSaveAs (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT filename,
                                      VARIANT fileFormat, VARIANT password,
                                      VARIANT writeResPassword,
                                      VARIANT readOnlyRecommended,
                                      VARIANT createBackup,
                                      enum ExcelEnum_XlSaveAsAccessMode accessMode,
                                      VARIANT conflictResolution,
                                      VARIANT addToMru, VARIANT textCodepage,
                                      VARIANT textVisualLayout, VARIANT local)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_LONG, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x785, CAVT_EMPTY, NULL, 12, __paramTypes,
                                 filename, fileFormat, password,
                                 writeResPassword, readOnlyRecommended,
                                 createBackup, accessMode, conflictResolution,
                                 addToMru, textCodepage, textVisualLayout,
                                 local);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookCheckIn (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT saveChanges,
                                       VARIANT comments, VARIANT makePublic)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x803, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 saveChanges, comments, makePublic);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookCanCheckIn (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VBOOL *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x805, CAVT_BOOL, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookSendForReview (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             VARIANT recipients, VARIANT subject,
                                             VARIANT showMessage,
                                             VARIANT includeAttachment)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x806, CAVT_EMPTY, NULL, 4, __paramTypes,
                                 recipients, subject, showMessage,
                                 includeAttachment);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookReplyWithChanges (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                VARIANT showMessage)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x809, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 showMessage);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookEndReview (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x80A, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookSetPasswordEncryptionOptions (CAObjHandle objectHandle,
                                                            ERRORINFO *errorInfo,
                                                            VARIANT passwordEncryptionProvider,
                                                            VARIANT passwordEncryptionAlgorithm,
                                                            VARIANT passwordEncryptionKeyLength,
                                                            VARIANT passwordEncryptionFilePropertie)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x80E, CAVT_EMPTY, NULL, 4, __paramTypes,
                                 passwordEncryptionProvider,
                                 passwordEncryptionAlgorithm,
                                 passwordEncryptionKeyLength,
                                 passwordEncryptionFilePropertie);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookProtect (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT password,
                                       VARIANT structure, VARIANT windows)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x7ED, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 password, structure, windows);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookRecheckSmartTags (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x811, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookSendFaxOverInternet (CAObjHandle objectHandle,
                                                   ERRORINFO *errorInfo,
                                                   VARIANT recipients,
                                                   VARIANT subject,
                                                   VARIANT showMessage)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x8DB, CAVT_EMPTY, NULL, 3, __paramTypes,
                                 recipients, subject, showMessage);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookXmlImport (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, const char *url,
                                         ExcelObj_XmlMap *importMap,
                                         VARIANT overwrite, VARIANT destination,
                                         enum ExcelEnum_XlXmlImportResult *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_OBJHANDLE | CAVT_BYREFO,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x8DE, CAVT_LONG, returnValue, 4,
                                 __paramTypes, url, importMap, overwrite,
                                 destination);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookXmlImportXml (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            const char *data,
                                            ExcelObj_XmlMap *importMap,
                                            VARIANT overwrite,
                                            VARIANT destination,
                                            enum ExcelEnum_XlXmlImportResult *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_OBJHANDLE | CAVT_BYREFO,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x8E5, CAVT_LONG, returnValue, 4,
                                 __paramTypes, data, importMap, overwrite,
                                 destination);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookSaveAsXMLData (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             const char *filename,
                                             ExcelObj_XmlMap map)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_OBJHANDLE};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x8E6, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 filename, map);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbookToggleFormsDesign (CAObjHandle objectHandle,
                                                 ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Workbook,
                                 0x8E7, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_SheetsAdd (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT before, VARIANT after, VARIANT count,
                                 VARIANT type, CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Sheets,
                                 0xB5, CAVT_OBJHANDLE, returnValue, 4,
                                 __paramTypes, before, after, count, type);

   return __result;
}

HRESULT CVIFUNC Excel_SheetsCopy (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT before, VARIANT after)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Sheets,
                                 0x227, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 before, after);

   return __result;
}

HRESULT CVIFUNC Excel_SheetsDelete (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Sheets,
                                 0x75, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_SheetsFillAcrossSheets (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              ExcelObj_Range range,
                                              enum ExcelEnum_XlFillWith type)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_OBJHANDLE, CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Sheets,
                                 0x1D5, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 range, type);

   return __result;
}

HRESULT CVIFUNC Excel_SheetsItem (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT index, CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Sheets,
                                 0xAA, DISPATCH_PROPERTYGET, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_SheetsMove (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT before, VARIANT after)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Sheets,
                                 0x27D, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 before, after);

   return __result;
}

HRESULT CVIFUNC Excel_Sheets_PrintOut (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT from,
                                       VARIANT to, VARIANT copies,
                                       VARIANT preview, VARIANT activePrinter,
                                       VARIANT printToFile, VARIANT collate)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Sheets,
                                 0x389, CAVT_EMPTY, NULL, 7, __paramTypes,
                                 from, to, copies, preview, activePrinter,
                                 printToFile, collate);

   return __result;
}

HRESULT CVIFUNC Excel_SheetsPrintPreview (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT enableChanges)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Sheets,
                                 0x119, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 enableChanges);

   return __result;
}

HRESULT CVIFUNC Excel_SheetsSelect (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT replace)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Sheets,
                                 0xEB, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 replace);

   return __result;
}

HRESULT CVIFUNC Excel_Sheets_Default (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT index,
                                      CAObjHandle *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Sheets,
                                 0x0, DISPATCH_PROPERTYGET, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_SheetsPrintOut (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT from,
                                      VARIANT to, VARIANT copies,
                                      VARIANT preview, VARIANT activePrinter,
                                      VARIANT printToFile, VARIANT collate,
                                      VARIANT prToFileName)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Sheets,
                                 0x6EC, CAVT_EMPTY, NULL, 8, __paramTypes,
                                 from, to, copies, preview, activePrinter,
                                 printToFile, collate, prToFileName);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbooksAdd (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT template,
                                    ExcelObj_Workbook *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Workbooks, 0xB5, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, template);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbooksClose (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Workbooks, 0x115, CAVT_EMPTY,
                                 NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbooksItem (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT index,
                                     ExcelObj_Workbook *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo,
                                 &Excel_IID_Workbooks, 0xAA,
                                 DISPATCH_PROPERTYGET, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_Workbooks_Open (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, const char *filename,
                                      VARIANT updateLinks, VARIANT readOnly,
                                      VARIANT format, VARIANT password,
                                      VARIANT writeResPassword,
                                      VARIANT ignoreReadOnlyRecommended,
                                      VARIANT origin, VARIANT delimiter,
                                      VARIANT editable, VARIANT notify,
                                      VARIANT converter, VARIANT addToMru,
                                      ExcelObj_Workbook *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Workbooks, 0x2AA, CAVT_OBJHANDLE,
                                 returnValue, 13, __paramTypes, filename,
                                 updateLinks, readOnly, format, password,
                                 writeResPassword, ignoreReadOnlyRecommended,
                                 origin, delimiter, editable, notify,
                                 converter, addToMru);

   return __result;
}

HRESULT CVIFUNC Excel_Workbooks__OpenText (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           const char *filename, VARIANT origin,
                                           VARIANT startRow, VARIANT dataType,
                                           enum ExcelEnum_XlTextQualifier textQualifier,
                                           VARIANT consecutiveDelimiter,
                                           VARIANT tab, VARIANT semicolon,
                                           VARIANT comma, VARIANT space,
                                           VARIANT other, VARIANT otherChar,
                                           VARIANT fieldInfo,
                                           VARIANT textVisualLayout)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_LONG, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Workbooks, 0x2AB, CAVT_EMPTY,
                                 NULL, 14, __paramTypes, filename, origin,
                                 startRow, dataType, textQualifier,
                                 consecutiveDelimiter, tab, semicolon, comma,
                                 space, other, otherChar, fieldInfo,
                                 textVisualLayout);

   return __result;
}

HRESULT CVIFUNC Excel_Workbooks_Default (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT index,
                                         ExcelObj_Workbook *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo,
                                 &Excel_IID_Workbooks, 0x0,
                                 DISPATCH_PROPERTYGET, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, index);

   return __result;
}

HRESULT CVIFUNC Excel_Workbooks_OpenText (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          const char *filename, VARIANT origin,
                                          VARIANT startRow, VARIANT dataType,
                                          enum ExcelEnum_XlTextQualifier textQualifier,
                                          VARIANT consecutiveDelimiter,
                                          VARIANT tab, VARIANT semicolon,
                                          VARIANT comma, VARIANT space,
                                          VARIANT other, VARIANT otherChar,
                                          VARIANT fieldInfo,
                                          VARIANT textVisualLayout,
                                          VARIANT decimalSeparator,
                                          VARIANT thousandsSeparator)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_LONG, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Workbooks, 0x6ED, CAVT_EMPTY,
                                 NULL, 16, __paramTypes, filename, origin,
                                 startRow, dataType, textQualifier,
                                 consecutiveDelimiter, tab, semicolon, comma,
                                 space, other, otherChar, fieldInfo,
                                 textVisualLayout, decimalSeparator,
                                 thousandsSeparator);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbooksOpen (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, const char *filename,
                                     VARIANT updateLinks, VARIANT readOnly,
                                     VARIANT format, VARIANT password,
                                     VARIANT writeResPassword,
                                     VARIANT ignoreReadOnlyRecommended,
                                     VARIANT origin, VARIANT delimiter,
                                     VARIANT editable, VARIANT notify,
                                     VARIANT converter, VARIANT addToMru,
                                     VARIANT local, VARIANT corruptLoad,
                                     ExcelObj_Workbook *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Workbooks, 0x783, CAVT_OBJHANDLE,
                                 returnValue, 15, __paramTypes, filename,
                                 updateLinks, readOnly, format, password,
                                 writeResPassword, ignoreReadOnlyRecommended,
                                 origin, delimiter, editable, notify,
                                 converter, addToMru, local, corruptLoad);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbooksOpenText (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         const char *filename, VARIANT origin,
                                         VARIANT startRow, VARIANT dataType,
                                         enum ExcelEnum_XlTextQualifier textQualifier,
                                         VARIANT consecutiveDelimiter,
                                         VARIANT tab, VARIANT semicolon,
                                         VARIANT comma, VARIANT space,
                                         VARIANT other, VARIANT otherChar,
                                         VARIANT fieldInfo,
                                         VARIANT textVisualLayout,
                                         VARIANT decimalSeparator,
                                         VARIANT thousandsSeparator,
                                         VARIANT trailingMinusNumbers,
                                         VARIANT local)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_LONG, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Workbooks, 0x784, CAVT_EMPTY,
                                 NULL, 18, __paramTypes, filename, origin,
                                 startRow, dataType, textQualifier,
                                 consecutiveDelimiter, tab, semicolon, comma,
                                 space, other, otherChar, fieldInfo,
                                 textVisualLayout, decimalSeparator,
                                 thousandsSeparator, trailingMinusNumbers,
                                 local);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbooksOpenDatabase (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             const char *filename,
                                             VARIANT commandText,
                                             VARIANT commandType,
                                             VARIANT backgroundQuery,
                                             VARIANT importDataAs,
                                             ExcelObj_Workbook *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Workbooks, 0x813, CAVT_OBJHANDLE,
                                 returnValue, 5, __paramTypes, filename,
                                 commandText, commandType, backgroundQuery,
                                 importDataAs);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbooksCheckOut (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         const char *filename)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Workbooks, 0x815, CAVT_EMPTY,
                                 NULL, 1, __paramTypes, filename);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbooksCanCheckOut (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            const char *filename,
                                            VBOOL *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Workbooks, 0x816, CAVT_BOOL,
                                 returnValue, 1, __paramTypes, filename);

   return __result;
}

HRESULT CVIFUNC Excel_Workbooks_OpenXML (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         const char *filename,
                                         VARIANT stylesheets,
                                         ExcelObj_Workbook *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Workbooks, 0x817, CAVT_OBJHANDLE,
                                 returnValue, 2, __paramTypes, filename,
                                 stylesheets);

   return __result;
}

HRESULT CVIFUNC Excel_WorkbooksOpenXML (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        const char *filename,
                                        VARIANT stylesheets, VARIANT loadOption,
                                        ExcelObj_Workbook *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo,
                                 &Excel_IID_Workbooks, 0x8E8, CAVT_OBJHANDLE,
                                 returnValue, 3, __paramTypes, filename,
                                 stylesheets, loadOption);

   return __result;
}

HRESULT CVIFUNC Excel_RangeActivate (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x130, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeAddress (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT rowAbsolute,
                                    VARIANT columnAbsolute,
                                    enum ExcelEnum_XlReferenceStyle referenceStyle,
                                    VARIANT external, VARIANT relativeTo,
                                    char **returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_LONG,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xEC, DISPATCH_PROPERTYGET, CAVT_CSTRING,
                                 returnValue, 5, __paramTypes, rowAbsolute,
                                 columnAbsolute, referenceStyle, external,
                                 relativeTo);

   return __result;
}

HRESULT CVIFUNC Excel_RangeAddressLocal (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         VARIANT rowAbsolute,
                                         VARIANT columnAbsolute,
                                         enum ExcelEnum_XlReferenceStyle referenceStyle,
                                         VARIANT external, VARIANT relativeTo,
                                         char **returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_LONG,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1B5, DISPATCH_PROPERTYGET, CAVT_CSTRING,
                                 returnValue, 5, __paramTypes, rowAbsolute,
                                 columnAbsolute, referenceStyle, external,
                                 relativeTo);

   return __result;
}

HRESULT CVIFUNC Excel_RangeAdvancedFilter (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           enum ExcelEnum_XlFilterAction action,
                                           VARIANT criteriaRange,
                                           VARIANT copyToRange, VARIANT unique,
                                           VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x36C, CAVT_VARIANT, returnValue, 4,
                                 __paramTypes, action, criteriaRange,
                                 copyToRange, unique);

   return __result;
}

HRESULT CVIFUNC Excel_RangeApplyNames (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT names,
                                       VARIANT ignoreRelativeAbsolute,
                                       VARIANT useRowColumnNames,
                                       VARIANT omitColumn, VARIANT omitRow,
                                       enum ExcelEnum_XlApplyNamesOrder order,
                                       VARIANT appendLast, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_LONG,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1B9, CAVT_VARIANT, returnValue, 7,
                                 __paramTypes, names, ignoreRelativeAbsolute,
                                 useRowColumnNames, omitColumn, omitRow,
                                 order, appendLast);

   return __result;
}

HRESULT CVIFUNC Excel_RangeApplyOutlineStyles (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1C0, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeAutoComplete (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         const char *string, char **returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x4A1, CAVT_CSTRING, returnValue, 1,
                                 __paramTypes, string);

   return __result;
}

HRESULT CVIFUNC Excel_RangeAutoFill (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo,
                                     ExcelObj_Range destination,
                                     enum ExcelEnum_XlAutoFillType type,
                                     VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_OBJHANDLE, CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1C1, CAVT_VARIANT, returnValue, 2,
                                 __paramTypes, destination, type);

   return __result;
}

HRESULT CVIFUNC Excel_RangeAutoFilter (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT field,
                                       VARIANT criteria1,
                                       enum ExcelEnum_XlAutoFilterOperator operator,
                                       VARIANT criteria2,
                                       VARIANT visibleDropDown,
                                       VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_LONG,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x319, CAVT_VARIANT, returnValue, 5,
                                 __paramTypes, field, criteria1, operator,
                                 criteria2, visibleDropDown);

   return __result;
}

HRESULT CVIFUNC Excel_RangeAutoFit (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xED, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeAutoFormat (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo,
                                       enum ExcelEnum_XlRangeAutoFormat format,
                                       VARIANT number, VARIANT font,
                                       VARIANT alignment, VARIANT border,
                                       VARIANT pattern, VARIANT width,
                                       VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x72, CAVT_VARIANT, returnValue, 7,
                                 __paramTypes, format, number, font,
                                 alignment, border, pattern, width);

   return __result;
}

HRESULT CVIFUNC Excel_RangeAutoOutline (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x40C, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeBorderAround (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT lineStyle,
                                         enum ExcelEnum_XlBorderWeight weight,
                                         enum ExcelEnum_XlColorIndex colorIndex,
                                         VARIANT color, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_LONG, CAVT_LONG,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x42B, CAVT_VARIANT, returnValue, 4,
                                 __paramTypes, lineStyle, weight, colorIndex,
                                 color);

   return __result;
}

HRESULT CVIFUNC Excel_RangeCalculate (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x117, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeCharacters (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT start,
                                       VARIANT length,
                                       ExcelObj_Characters *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x25B, DISPATCH_PROPERTYGET, CAVT_OBJHANDLE,
                                 returnValue, 2, __paramTypes, start, length);

   return __result;
}

HRESULT CVIFUNC Excel_RangeCheckSpelling (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT customDictionary,
                                          VARIANT ignoreUppercase,
                                          VARIANT alwaysSuggest,
                                          VARIANT spellLang,
                                          VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1F9, CAVT_VARIANT, returnValue, 4,
                                 __paramTypes, customDictionary,
                                 ignoreUppercase, alwaysSuggest, spellLang);

   return __result;
}

HRESULT CVIFUNC Excel_RangeClear (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x6F, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeClearContents (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x71, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeClearFormats (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x70, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeClearNotes (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo,
                                       VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xEF, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeClearOutline (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x40D, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeColumnDifferences (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              VARIANT comparison,
                                              ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1FE, CAVT_OBJHANDLE, returnValue, 1,
                                 __paramTypes, comparison);

   return __result;
}

HRESULT CVIFUNC Excel_RangeConsolidate (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT sources,
                                        VARIANT function, VARIANT topRow,
                                        VARIANT leftColumn, VARIANT createLinks,
                                        VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1E2, CAVT_VARIANT, returnValue, 5,
                                 __paramTypes, sources, function, topRow,
                                 leftColumn, createLinks);

   return __result;
}

HRESULT CVIFUNC Excel_RangeCopy (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT destination, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x227, CAVT_VARIANT, returnValue, 1,
                                 __paramTypes, destination);

   return __result;
}

HRESULT CVIFUNC Excel_RangeCopyFromRecordset (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              LPUNKNOWN data, VARIANT maxRows,
                                              VARIANT maxColumns,
                                              long *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_UNKNOWN, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x480, CAVT_LONG, returnValue, 3,
                                 __paramTypes, data, maxRows, maxColumns);

   return __result;
}

HRESULT CVIFUNC Excel_RangeCopyPicture (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        enum ExcelEnum_XlPictureAppearance appearance,
                                        enum ExcelEnum_XlCopyPictureFormat format,
                                        VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xD5, CAVT_VARIANT, returnValue, 2,
                                 __paramTypes, appearance, format);

   return __result;
}

HRESULT CVIFUNC Excel_RangeCreateNames (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT top,
                                        VARIANT left, VARIANT bottom,
                                        VARIANT right, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1C9, CAVT_VARIANT, returnValue, 4,
                                 __paramTypes, top, left, bottom, right);

   return __result;
}

HRESULT CVIFUNC Excel_RangeCreatePublisher (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            VARIANT edition,
                                            enum ExcelEnum_XlPictureAppearance appearance,
                                            VARIANT containsPICT,
                                            VARIANT containsBIFF,
                                            VARIANT containsRTF,
                                            VARIANT containsVALU,
                                            VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_LONG, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1CA, CAVT_VARIANT, returnValue, 6,
                                 __paramTypes, edition, appearance,
                                 containsPICT, containsBIFF, containsRTF,
                                 containsVALU);

   return __result;
}

HRESULT CVIFUNC Excel_RangeCut (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                VARIANT destination, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x235, CAVT_VARIANT, returnValue, 1,
                                 __paramTypes, destination);

   return __result;
}

HRESULT CVIFUNC Excel_RangeDataSeries (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT rowcol,
                                       enum ExcelEnum_XlDataSeriesType type,
                                       enum ExcelEnum_XlDataSeriesDate date,
                                       VARIANT step, VARIANT stop, VARIANT trend,
                                       VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_LONG, CAVT_LONG,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1D0, CAVT_VARIANT, returnValue, 6,
                                 __paramTypes, rowcol, type, date, step, stop,
                                 trend);

   return __result;
}

HRESULT CVIFUNC Excel_RangeGet_Default (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT rowIndex,
                                        VARIANT columnIndex,
                                        VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x0, DISPATCH_PROPERTYGET, CAVT_VARIANT,
                                 returnValue, 2, __paramTypes, rowIndex,
                                 columnIndex);

   return __result;
}

HRESULT CVIFUNC Excel_RangeSet_Default (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT rowIndex,
                                        VARIANT columnIndex, VARIANT newValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x0, DISPATCH_PROPERTYPUT, CAVT_EMPTY, NULL,
                                 3, __paramTypes, rowIndex, columnIndex,
                                 newValue);

   return __result;
}

HRESULT CVIFUNC Excel_RangeDelete (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT shift,
                                   VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x75, CAVT_VARIANT, returnValue, 1,
                                 __paramTypes, shift);

   return __result;
}

HRESULT CVIFUNC Excel_RangeDialogBox (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xF5, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeEditionOptions (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           enum ExcelEnum_XlEditionType type,
                                           enum ExcelEnum_XlEditionOptionsOption option,
                                           VARIANT name, VARIANT reference,
                                           enum ExcelEnum_XlPictureAppearance appearance,
                                           enum ExcelEnum_XlPictureAppearance chartSize,
                                           VARIANT format, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_LONG, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_LONG, CAVT_LONG,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x46B, CAVT_VARIANT, returnValue, 7,
                                 __paramTypes, type, option, name, reference,
                                 appearance, chartSize, format);

   return __result;
}

HRESULT CVIFUNC Excel_RangeEnd (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                enum ExcelEnum_XlDirection direction,
                                ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1F4, DISPATCH_PROPERTYGET, CAVT_OBJHANDLE,
                                 returnValue, 1, __paramTypes, direction);

   return __result;
}

HRESULT CVIFUNC Excel_RangeFillDown (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xF8, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeFillLeft (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xF9, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeFillRight (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xFA, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeFillUp (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xFB, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeFind (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT what, VARIANT after, VARIANT lookIn,
                                 VARIANT lookAt, VARIANT searchOrder,
                                 enum ExcelEnum_XlSearchDirection searchDirection,
                                 VARIANT matchCase, VARIANT matchByte,
                                 VARIANT searchFormat,
                                 ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_LONG,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x18E, CAVT_OBJHANDLE, returnValue, 9,
                                 __paramTypes, what, after, lookIn, lookAt,
                                 searchOrder, searchDirection, matchCase,
                                 matchByte, searchFormat);

   return __result;
}

HRESULT CVIFUNC Excel_RangeFindNext (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT after,
                                     ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x18F, CAVT_OBJHANDLE, returnValue, 1,
                                 __paramTypes, after);

   return __result;
}

HRESULT CVIFUNC Excel_RangeFindPrevious (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT after,
                                         ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x190, CAVT_OBJHANDLE, returnValue, 1,
                                 __paramTypes, after);

   return __result;
}

HRESULT CVIFUNC Excel_RangeFunctionWizard (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x23B, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeGoalSeek (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT goal,
                                     ExcelObj_Range changingCell,
                                     VBOOL *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_OBJHANDLE};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1D8, CAVT_BOOL, returnValue, 2,
                                 __paramTypes, goal, changingCell);

   return __result;
}

HRESULT CVIFUNC Excel_RangeGroup (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT start, VARIANT end, VARIANT by,
                                  VARIANT periods, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x2E, CAVT_VARIANT, returnValue, 4,
                                 __paramTypes, start, end, by, periods);

   return __result;
}

HRESULT CVIFUNC Excel_RangeInsertIndent (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, long insertAmount)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x565, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 insertAmount);

   return __result;
}

HRESULT CVIFUNC Excel_RangeInsert (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT shift,
                                   VARIANT copyOrigin, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xFC, CAVT_VARIANT, returnValue, 2,
                                 __paramTypes, shift, copyOrigin);

   return __result;
}

HRESULT CVIFUNC Excel_RangeGetItem (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT rowIndex,
                                    VARIANT columnIndex, VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xAA, DISPATCH_PROPERTYGET, CAVT_VARIANT,
                                 returnValue, 2, __paramTypes, rowIndex,
                                 columnIndex);

   return __result;
}

HRESULT CVIFUNC Excel_RangeSetItem (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT rowIndex,
                                    VARIANT columnIndex, VARIANT newValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xAA, DISPATCH_PROPERTYPUT, CAVT_EMPTY, NULL,
                                 3, __paramTypes, rowIndex, columnIndex,
                                 newValue);

   return __result;
}

HRESULT CVIFUNC Excel_RangeJustify (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1EF, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeListNames (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xFD, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeMerge (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT across)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x234, CAVT_EMPTY, NULL, 1, __paramTypes,
                                 across);

   return __result;
}

HRESULT CVIFUNC Excel_RangeUnMerge (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x568, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeNavigateArrow (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT towardPrecedent,
                                          VARIANT arrowNumber,
                                          VARIANT linkNumber,
                                          VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x408, CAVT_VARIANT, returnValue, 3,
                                 __paramTypes, towardPrecedent, arrowNumber,
                                 linkNumber);

   return __result;
}

HRESULT CVIFUNC Excel_RangeNoteText (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT text,
                                     VARIANT start, VARIANT length,
                                     char **returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x467, CAVT_CSTRING, returnValue, 3,
                                 __paramTypes, text, start, length);

   return __result;
}

HRESULT CVIFUNC Excel_RangeOffset (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT rowOffset,
                                   VARIANT columnOffset,
                                   ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xFE, DISPATCH_PROPERTYGET, CAVT_OBJHANDLE,
                                 returnValue, 2, __paramTypes, rowOffset,
                                 columnOffset);

   return __result;
}

HRESULT CVIFUNC Excel_RangeParse (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT parseLine, VARIANT destination,
                                  VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1DD, CAVT_VARIANT, returnValue, 2,
                                 __paramTypes, parseLine, destination);

   return __result;
}

HRESULT CVIFUNC Excel_Range_PasteSpecial (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          enum ExcelEnum_XlPasteType paste,
                                          enum ExcelEnum_XlPasteSpecialOperation operation,
                                          VARIANT skipBlanks, VARIANT transpose,
                                          VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_LONG, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x403, CAVT_VARIANT, returnValue, 4,
                                 __paramTypes, paste, operation, skipBlanks,
                                 transpose);

   return __result;
}

HRESULT CVIFUNC Excel_Range_PrintOut (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT from,
                                      VARIANT to, VARIANT copies,
                                      VARIANT preview, VARIANT activePrinter,
                                      VARIANT printToFile, VARIANT collate,
                                      VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x389, CAVT_VARIANT, returnValue, 7,
                                 __paramTypes, from, to, copies, preview,
                                 activePrinter, printToFile, collate);

   return __result;
}

HRESULT CVIFUNC Excel_RangePrintPreview (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         VARIANT enableChanges,
                                         VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x119, CAVT_VARIANT, returnValue, 1,
                                 __paramTypes, enableChanges);

   return __result;
}

HRESULT CVIFUNC Excel_RangeRange (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT cell1, VARIANT cell2,
                                  ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xC5, DISPATCH_PROPERTYGET, CAVT_OBJHANDLE,
                                 returnValue, 2, __paramTypes, cell1, cell2);

   return __result;
}

HRESULT CVIFUNC Excel_RangeRemoveSubtotal (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x373, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeReplace (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT what,
                                    VARIANT replacement, VARIANT lookAt,
                                    VARIANT searchOrder, VARIANT matchCase,
                                    VARIANT matchByte, VARIANT searchFormat,
                                    VARIANT replaceFormat, VBOOL *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xE2, CAVT_BOOL, returnValue, 8,
                                 __paramTypes, what, replacement, lookAt,
                                 searchOrder, matchCase, matchByte,
                                 searchFormat, replaceFormat);

   return __result;
}

HRESULT CVIFUNC Excel_RangeResize (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT rowSize,
                                   VARIANT columnSize,
                                   ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x100, DISPATCH_PROPERTYGET, CAVT_OBJHANDLE,
                                 returnValue, 2, __paramTypes, rowSize,
                                 columnSize);

   return __result;
}

HRESULT CVIFUNC Excel_RangeRowDifferences (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           VARIANT comparison,
                                           ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1FF, CAVT_OBJHANDLE, returnValue, 1,
                                 __paramTypes, comparison);

   return __result;
}

HRESULT CVIFUNC Excel_RangeRun (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                VARIANT arg1, VARIANT arg2, VARIANT arg3,
                                VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                VARIANT arg10, VARIANT arg11, VARIANT arg12,
                                VARIANT arg13, VARIANT arg14, VARIANT arg15,
                                VARIANT arg16, VARIANT arg17, VARIANT arg18,
                                VARIANT arg19, VARIANT arg20, VARIANT arg21,
                                VARIANT arg22, VARIANT arg23, VARIANT arg24,
                                VARIANT arg25, VARIANT arg26, VARIANT arg27,
                                VARIANT arg28, VARIANT arg29, VARIANT arg30,
                                VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x103, CAVT_VARIANT, returnValue, 30,
                                 __paramTypes, arg1, arg2, arg3, arg4, arg5,
                                 arg6, arg7, arg8, arg9, arg10, arg11, arg12,
                                 arg13, arg14, arg15, arg16, arg17, arg18,
                                 arg19, arg20, arg21, arg22, arg23, arg24,
                                 arg25, arg26, arg27, arg28, arg29, arg30);

   return __result;
}

HRESULT CVIFUNC Excel_RangeSelect (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xEB, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeShow (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1F0, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeShowDependents (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT remove,
                                           VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x36D, CAVT_VARIANT, returnValue, 1,
                                 __paramTypes, remove);

   return __result;
}

HRESULT CVIFUNC Excel_RangeShowErrors (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo,
                                       VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x36E, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeShowPrecedents (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT remove,
                                           VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x36F, CAVT_VARIANT, returnValue, 1,
                                 __paramTypes, remove);

   return __result;
}

HRESULT CVIFUNC Excel_RangeSort (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT key1, enum ExcelEnum_XlSortOrder order1,
                                 VARIANT key2, VARIANT type,
                                 enum ExcelEnum_XlSortOrder order2, VARIANT key3,
                                 enum ExcelEnum_XlSortOrder order3,
                                 enum ExcelEnum_XlYesNoGuess header,
                                 VARIANT orderCustom, VARIANT matchCase,
                                 enum ExcelEnum_XlSortOrientation orientation,
                                 enum ExcelEnum_XlSortMethod sortMethod,
                                 enum ExcelEnum_XlSortDataOption dataOption1,
                                 enum ExcelEnum_XlSortDataOption dataOption2,
                                 enum ExcelEnum_XlSortDataOption dataOption3,
                                 VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_LONG, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_LONG, CAVT_VARIANT,
                                  CAVT_LONG, CAVT_LONG, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_LONG, CAVT_LONG,
                                  CAVT_LONG, CAVT_LONG, CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x370, CAVT_VARIANT, returnValue, 15,
                                 __paramTypes, key1, order1, key2, type,
                                 order2, key3, order3, header, orderCustom,
                                 matchCase, orientation, sortMethod,
                                 dataOption1, dataOption2, dataOption3);

   return __result;
}

HRESULT CVIFUNC Excel_RangeSortSpecial (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        enum ExcelEnum_XlSortMethod sortMethod,
                                        VARIANT key1,
                                        enum ExcelEnum_XlSortOrder order1,
                                        VARIANT type, VARIANT key2,
                                        enum ExcelEnum_XlSortOrder order2,
                                        VARIANT key3,
                                        enum ExcelEnum_XlSortOrder order3,
                                        enum ExcelEnum_XlYesNoGuess header,
                                        VARIANT orderCustom, VARIANT matchCase,
                                        enum ExcelEnum_XlSortOrientation orientation,
                                        enum ExcelEnum_XlSortDataOption dataOption1,
                                        enum ExcelEnum_XlSortDataOption dataOption2,
                                        enum ExcelEnum_XlSortDataOption dataOption3,
                                        VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_VARIANT, CAVT_LONG,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_LONG,
                                  CAVT_VARIANT, CAVT_LONG, CAVT_LONG,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_LONG,
                                  CAVT_LONG, CAVT_LONG, CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x371, CAVT_VARIANT, returnValue, 15,
                                 __paramTypes, sortMethod, key1, order1, type,
                                 key2, order2, key3, order3, header,
                                 orderCustom, matchCase, orientation,
                                 dataOption1, dataOption2, dataOption3);

   return __result;
}

HRESULT CVIFUNC Excel_RangeSpecialCells (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         enum ExcelEnum_XlCellType type,
                                         VARIANT value,
                                         ExcelObj_Range *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x19A, CAVT_OBJHANDLE, returnValue, 2,
                                 __paramTypes, type, value);

   return __result;
}

HRESULT CVIFUNC Excel_RangeSubscribeTo (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        const char *edition,
                                        enum ExcelEnum_XlSubscribeToFormat format,
                                        VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_CSTRING, CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1E1, CAVT_VARIANT, returnValue, 2,
                                 __paramTypes, edition, format);

   return __result;
}

HRESULT CVIFUNC Excel_RangeSubtotal (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, long groupBy,
                                     enum ExcelEnum_XlConsolidationFunction function,
                                     VARIANT totalList, VARIANT replace,
                                     VARIANT pageBreaks,
                                     enum ExcelEnum_XlSummaryRow summaryBelowData,
                                     VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_LONG, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_LONG};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x372, CAVT_VARIANT, returnValue, 6,
                                 __paramTypes, groupBy, function, totalList,
                                 replace, pageBreaks, summaryBelowData);

   return __result;
}

HRESULT CVIFUNC Excel_RangeTable (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT rowInput, VARIANT columnInput,
                                  VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x1F1, CAVT_VARIANT, returnValue, 2,
                                 __paramTypes, rowInput, columnInput);

   return __result;
}

HRESULT CVIFUNC Excel_RangeTextToColumns (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT destination,
                                          enum ExcelEnum_XlTextParsingType dataType,
                                          enum ExcelEnum_XlTextQualifier textQualifier,
                                          VARIANT consecutiveDelimiter,
                                          VARIANT tab, VARIANT semicolon,
                                          VARIANT comma, VARIANT space,
                                          VARIANT other, VARIANT otherChar,
                                          VARIANT fieldInfo,
                                          VARIANT decimalSeparator,
                                          VARIANT thousandsSeparator,
                                          VARIANT trailingMinusNumbers,
                                          VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_LONG, CAVT_LONG,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x410, CAVT_VARIANT, returnValue, 14,
                                 __paramTypes, destination, dataType,
                                 textQualifier, consecutiveDelimiter, tab,
                                 semicolon, comma, space, other, otherChar,
                                 fieldInfo, decimalSeparator,
                                 thousandsSeparator, trailingMinusNumbers);

   return __result;
}

HRESULT CVIFUNC Excel_RangeUngroup (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT *returnValue)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0xF4, CAVT_VARIANT, returnValue, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeGetValue (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo,
                                     VARIANT rangeValueDataType,
                                     VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x6, DISPATCH_PROPERTYGET, CAVT_VARIANT,
                                 returnValue, 1, __paramTypes,
                                 rangeValueDataType);

   return __result;
}

HRESULT CVIFUNC Excel_RangeSetValue (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo,
                                     VARIANT rangeValueDataType,
                                     VARIANT newValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_InvokeHelperEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x6, DISPATCH_PROPERTYPUT, CAVT_EMPTY, NULL,
                                 2, __paramTypes, rangeValueDataType,
                                 newValue);

   return __result;
}

HRESULT CVIFUNC Excel_RangeAddComment (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT text,
                                       ExcelObj_Comment *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x56D, CAVT_OBJHANDLE, returnValue, 1,
                                 __paramTypes, text);

   return __result;
}

HRESULT CVIFUNC Excel_RangeClearComments (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x56E, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeSetPhonetic (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x714, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangePrintOut (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT from,
                                     VARIANT to, VARIANT copies, VARIANT preview,
                                     VARIANT activePrinter, VARIANT printToFile,
                                     VARIANT collate, VARIANT prToFileName,
                                     VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT, CAVT_VARIANT,
                                  CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x6EC, CAVT_VARIANT, returnValue, 8,
                                 __paramTypes, from, to, copies, preview,
                                 activePrinter, printToFile, collate,
                                 prToFileName);

   return __result;
}

HRESULT CVIFUNC Excel_RangeDirty (CAObjHandle objectHandle, ERRORINFO *errorInfo)
{
   HRESULT __result = S_OK;

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x7DE, CAVT_EMPTY, NULL, 0, NULL);

   return __result;
}

HRESULT CVIFUNC Excel_RangeSpeak (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT speakDirection, VARIANT speakFormulas)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_VARIANT, CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x7E1, CAVT_EMPTY, NULL, 2, __paramTypes,
                                 speakDirection, speakFormulas);

   return __result;
}

HRESULT CVIFUNC Excel_RangePasteSpecial (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         enum ExcelEnum_XlPasteType paste,
                                         enum ExcelEnum_XlPasteSpecialOperation operation,
                                         VARIANT skipBlanks, VARIANT transpose,
                                         VARIANT *returnValue)
{
   HRESULT __result = S_OK;
   unsigned int __paramTypes[] = {CAVT_LONG, CAVT_LONG, CAVT_VARIANT,
                                  CAVT_VARIANT};

   __result = CA_MethodInvokeEx (objectHandle, errorInfo, &Excel_IID_Range,
                                 0x788, CAVT_VARIANT, returnValue, 4,
                                 __paramTypes, paste, operation, skipBlanks,
                                 transpose);

   return __result;
}
