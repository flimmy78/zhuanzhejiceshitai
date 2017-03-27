// #########################################################################
// *************************************************************************

#include <cvirte.h>     
#include "Global.h"
#include <userint.h>
#include "S700K.h"
#include "inifile.h"

//------------------------------------------------------------------------------------------------
// 定义全局变量
//------------------------------------------------------------------------------------------------
extern PT_Device  g_Device;

//------------------------------------------------------------------------------------------------
// 调用转辙机型号选择画面
// 输入:
//    pDevice     设备指针
//    nLanguage   语言类型
// 输出:
//    pDevice     设备指针
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
int __stdcall TBDeviceSelect( LPT_Device pDevice, int nLanguage )
{
   // 定义函数指针
   typedef int (__stdcall *TBDeviceSelect)(LPT_Device pDevice, int nLanguage);
   TBDeviceSelect pProc;
//   int ( __stdcall *pProc)(LPT_Device pDevice, int nLanguage);
   HMODULE hLibrary;
   
   // 载入动态库
   hLibrary = LoadLibrary ("S700KDLL.dll");

   // 如果不成功，返回错误
   if ( hLibrary == NULL )
      return -1;

   // 定位函数地址
   pProc = (TBDeviceSelect)GetProcAddress (hLibrary, "TBDeviceSelect");
   // 检查
   if ( pProc == NULL )
      return -1;

   // 调用函数
   (*pProc)(&g_Device, nLanguage);

   // 释放动态库
   FreeLibrary (hLibrary);

   return 0;
}

//------------------------------------------------------------------------------------------------
// 调用转辙机TypeNumber选择画面
// 输入:
//    pData       字符串指针
//    nLanguage   语言类型
// 输出:
//    pData       字符串指针
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
int __stdcall TBTypeNumber( char* pData, int nLanguage )
{
   // 定义函数指针
   typedef int (__stdcall *TBTypeNumber)(char* pData, int nLanguage);
   TBTypeNumber pProc;
//   int ( __stdcall *pProc)( char* pData, int nLanguage );
   HMODULE hLibrary;
   // 载入动态库
   hLibrary = LoadLibrary ("S700KDLL.dll");

   // 如果不成功，返回错误
   if ( hLibrary == NULL )
      return -1;

   // 定位函数地址
   pProc = (TBTypeNumber)GetProcAddress (hLibrary, "TBTypeNumber");
   if ( pProc == NULL )
      return -1;

   // 调用函数
   (*pProc)(pData, nLanguage);

   // 释放动态库
   FreeLibrary (hLibrary);

   return 0;
}
//------------------------------------------------------------------------------------------------
// 调用转辙机测试结果选择画面
// 输入:
//    pData       字符串指针
//    nLanguage   语言类型
// 输出:
//    pData       字符串指针
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
int __stdcall TBTestResult( char* pData, int nLanguage )
{
   // 定义函数指针
   typedef int (__stdcall *TBTestResult)(char* pData, int nLanguage);
   TBTestResult pProc;
//   int ( __stdcall *pProc)( char* pData, int nLanguage );
   HMODULE hLibrary;
   // 载入动态库
   hLibrary = LoadLibrary ("S700KDLL.dll");

   // 如果不成功，返回错误
   if ( hLibrary == NULL )
      return -1;

   // 定位函数地址
   pProc = (TBTestResult)GetProcAddress (hLibrary, "TBTestResult");
   if ( pProc == NULL )
      return -1;

   // 调用函数
   (*pProc)(pData, nLanguage);

   // 释放动态库
   FreeLibrary (hLibrary);

   return 0;
}
//------------------------------------------------------------------------------------------------
// 调用转辙机测试人选择画面
// 输入:
//    pData       字符串指针
//    nLanguage   语言类型
// 输出:
//    pData       字符串指针
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
int __stdcall TBTesterName( char* pData, int nLanguage )
{
   // 定义函数指针
   typedef int (__stdcall *TBTesterName)(char* pData, int nLanguage);
   TBTesterName pProc;
//   int ( __stdcall *pProc)( char* pData, int nLanguage );
   HMODULE hLibrary;
   // 载入动态库
   hLibrary = LoadLibrary ("S700KDLL.dll");

   // 如果不成功，返回错误
   if ( hLibrary == NULL )
      return -1;

   // 定位函数地址
   pProc = (TBTesterName)GetProcAddress (hLibrary, "TBTesterName");
   if ( pProc == NULL )
      return -1;

   // 调用函数
   (*pProc)(pData, nLanguage);

   // 释放动态库
   FreeLibrary (hLibrary);

   return 0;
}

//------------------------------------------------------------------------------------------------
// 调用转辙机串号选择画面
// 输入:
//    pData       字符串指针
//    nLanguage   语言类型
// 输出:
//    pData       字符串指针
// 返回:
//    0           成功
//    <0          失败
//------------------------------------------------------------------------------------------------
int __stdcall TBSerialNumber( char* pData, int nLanguage )
{
   // 定义函数指针
   typedef int (__stdcall *TBSerialNumber)(char* pData, int nLanguage);
   TBSerialNumber pProc;
//   int ( __stdcall *pProc)( char* pData, int nLanguage );
   HMODULE hLibrary;
   // 载入动态库
   hLibrary = LoadLibrary ("S700KDLL.dll");

   // 如果不成功，返回错误
   if ( hLibrary == NULL )
      return -1;

   // 定位函数地址
   pProc = (TBSerialNumber)GetProcAddress (hLibrary, "TBSerialNumber");
   if ( pProc == NULL )
      return -1;

   // 调用函数
   (*pProc)(pData, nLanguage);

   // 释放动态库
   FreeLibrary (hLibrary);

   return 0;
}
//------------------------------------------------------------------------------------------------
