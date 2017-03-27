#ifndef _USB2833_DEVICE_
#define _USB2833_DEVICE_

#include<windows.h>
//***********************************************************
// 用于AD采集的参数结构
typedef struct _USB2833_PARA_AD
{
   LONG FirstChannel;      // 首通道,取值范围为[0, 15]
   LONG LastChannel;    // 末通道,取值范围为[0, 15]
   LONG InputRange;     // 量程选择
   LONG Gains;          // 增益控制字
   LONG GroundingMode;     // 接地方式（单端或双端选择）
} USB2833_PARA_AD, *PUSB2833_PARA_AD;

//***********************************************************
// AD硬件参数USB2833_PARA_AD中的InputRange量程所使用的选项
const long USB2833_INPUT_N10000_P10000mV= 0x00; // ±10000mV
const long USB2833_INPUT_N5000_P5000mV = 0x01; // ±5000mV
const long USB2833_INPUT_N2500_P2500mV = 0x02; // ±2500mV
const long USB2833_INPUT_0_P10000mV    = 0x03; // 0～10000mV

//***********************************************************
// AD参数USB2833_PARA_AD中的Gains使用的硬件增益选项
const long USB2833_GAINS_1MULT         = 0x00; // 1倍增益(使用AD8251放大器)
const long USB2833_GAINS_2MULT         = 0x01; // 2倍增益(使用AD8251放大器)
const long USB2833_GAINS_4MULT         = 0x02; // 4倍增益(使用AD8251放大器)
const long USB2833_GAINS_8MULT         = 0x03; // 8倍增益(使用AD8251放大器)

//***********************************************************
// AD参数(USB2833_PARA_AD)中的GroundingMode使用的模拟信号接地方式选项
const long USB2833_GNDMODE_SE       = 0x00;  // 单端方式(SE:Single end)
const long USB2833_GNDMODE_DI       = 0x01;  // 双端方式(DI:Differential)

//***********************************************************
// DA输出函数USB2833_WriteDeviceDA的模拟量输出范围参数OutputRange所使用的选项
const long USB2833_OUTPUT_0_P5000mV    = 0x00;     // 0～5000mV
const long USB2833_OUTPUT_0_P10000mV   = 0x01;     // 0～10000mV
const long USB2833_OUTPUT_0_P10800mV   = 0x02;     // 0～10800mV
const long USB2833_OUTPUT_N5000_P5000mV   = 0x03;     // ±5000mV
const long USB2833_OUTPUT_N10000_P10000mV= 0x04;   // ±10000mV
const long USB2833_OUTPUT_N10800_P10800mV= 0x05;   // ±10800mV

//***********************************************************
// 用于计数器CNT的参数结构
// 硬件参数ControlMode控制字模式选项
const long USB2833_GATEMODE_POSITIVE_0 = 0x00;     // COUNTER:GATE高电平时计数，低电平时停止计数，计数时重新写入初值，按初值计数
                                       // 计数结束产生中断：写入初值开始计数时OUT开始为0，当计数到0时OUT为1

const long USB2833_GATEMODE_RISING_1   = 0x01;     // COUNTER:GATE上边沿触发计数，计数中出现GATE上升沿重新装入初值计数
                                       // 可编程单拍脉冲：当写入初值时OUT为1，当开始计数时OUT为0，当计数到0时OUT再次为1

const long USB2833_GATEMODE_POSITIVE_2 = 0x02;     // COUNTER:GATE高电平时计数，低电平时停止计数，计数时重新写入初值，按初值计数
                                       // 频率发生器：计数期间OUT为1，计数到0后输出一个周期的0，并重新装入计数值计数

const long USB2833_GATEMODE_POSITIVE_3 = 0x03;     // COUNTER:GATE高电平时计数，低电平时停止计数，计数时重新写入初值，按初值计数
                                       // 方波发生器：计数期间OUT为1，计数到0后输出一个周期的0，并重新装入计数值计数

const long USB2833_GATEMODE_POSITIVE_4 = 0x04;     // COUNTER:GATE高电平时计数，低电平时停止计数，计数时重新写入初值，按初值计数
                                       // 软件触发选通：写入初值OUT为1， 计数结束OUT输出一个周期低电平信号

const long USB2833_GATEMODE_RISING_5   = 0x05;     // COUNTER:GATE上边沿触发计数，计数中出现GATE上升沿重新装入初值计数
                                       // 硬件触发选通：写入初值OUT为1， 计数结束OUT输出一个周期低电平信号

//***********************************************************
// 驱动函数接口
#ifndef _USB2833_DRIVER_
#define DEVAPI __declspec(dllimport)
#else
#define DEVAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
   //######################## 常规通用函数 #################################
    HANDLE DEVAPI FAR PASCAL USB2833_CreateDevice(int DeviceLgcID); // 创建设备对象(该函数使用系统内逻辑设备ID）
    HANDLE DEVAPI FAR PASCAL USB2833_CreateDeviceEx(int DevicePhysID); // 创建设备对象(该函数使用板上物理ID,由拔码开关DID1实现)
   int DEVAPI FAR PASCAL USB2833_GetDeviceCount(HANDLE hDevice);      // 取得USB2833在系统中的设备数量
   BOOL DEVAPI FAR PASCAL USB2833_GetDeviceCurrentID(HANDLE hDevice, PLONG DeviceLgcID, PLONG DevicePhysID); // 取得当前设备的逻辑ID号和物理ID号
   BOOL DEVAPI FAR PASCAL USB2833_ListDeviceDlg(void); // 用对话框列表系统当中的所有USB2833设备
   BOOL DEVAPI FAR PASCAL USB2833_ResetDevice(HANDLE hDevice);     // 复位整个USB设备
    BOOL DEVAPI FAR PASCAL USB2833_ReleaseDevice(HANDLE hDevice);    // 设备句柄

   //####################### AD数据读取函数 #################################
    BOOL DEVAPI FAR PASCAL USB2833_InitDeviceAD(            // 初始化设备,当返回TRUE后,设备即刻开始传输.
                           HANDLE hDevice,            // 设备句柄,它应由CreateDevice函数创建
                           PUSB2833_PARA_AD pADPara);  // 硬件参数, 它仅在此函数中决定硬件状态                    

    BOOL DEVAPI FAR PASCAL USB2833_ReadDeviceAD(            // 初始化设备后，即可用此函数读取设备上的AD数据
                           HANDLE hDevice,            // 设备句柄,它应由CreateDevice函数创建
                           USHORT ADBuffer[],         // 将用于接受数据的用户缓冲区
                           LONG nReadSizeWords,    // 读取AD数据的长度(字)  
                           PLONG nRetSizeWords);// 实际返回数据的长度(字)

    BOOL DEVAPI FAR PASCAL USB2833_ReleaseDeviceAD( HANDLE hDevice); // 停止AD采集，释放AD对象所占资源

      //################# AD的硬件参数操作函数 ######################## 
   BOOL DEVAPI FAR PASCAL USB2833_SaveParaAD(HANDLE hDevice, PUSB2833_PARA_AD pADPara);  
    BOOL DEVAPI FAR PASCAL USB2833_LoadParaAD(HANDLE hDevice, PUSB2833_PARA_AD pADPara);
    BOOL DEVAPI FAR PASCAL USB2833_ResetParaAD(HANDLE hDevice, PUSB2833_PARA_AD pADPara); // 将AD采样参数恢复至出厂默认值

   //####################### DA数据输出函数 #################################
   // 适于大多数普通用户，这些接口最简单、最快捷、最可靠，让用户不必知道设备
   // 低层复杂的硬件控制协议和繁多的软件控制编程，仅用下面一个函数便能轻
   // 松实现高速、连续的DA数据输出
   BOOL DEVAPI FAR PASCAL USB2833_WriteDeviceDA(         // 写DA数据
                           HANDLE hDevice,         // 设备对象句柄,它由CreateDevice函数创建
                           LONG OutputRange,    // 输出量程，具体定义请参考上面的常量定义部分
                           SHORT nDAData,       // 输出的DA原始数据[0, 4095]
                           int nDAChannel);     // DA输出通道[0-3](写入4，代表四个通道都启动)

   //##################### 计数器控制函数 ##########################
    BOOL DEVAPI FAR PASCAL USB2833_SetDeviceCNT(            // 初始化计数器
                           HANDLE   hDevice,       // 设备句柄
                           ULONG ContrlMode,       // 计数器控制模式
                           ULONG CNTVal,           // 计数初值(16位)
                           ULONG ulChannel);       // 通道选择[0-2]        

   BOOL DEVAPI FAR PASCAL USB2833_GetDeviceCNT(          // 取得各路计数器的当前计数值
                           HANDLE   hDevice,       // 设备对象句柄,它由CreateDevice函数创建
                           PULONG   pCNTVal,       // 返回计数值(16位)
                           ULONG ulChannel);       // 通道选择[0-2]

   //####################### 数字I/O输入输出函数 #################################
   BOOL DEVAPI FAR PASCAL USB2833_GetDeviceDI(              // 取得开关量状态     
                           HANDLE hDevice,            // 设备句柄,它应由CreateDevice函数创建                              
                           BYTE bDISts[8]);        // 开关输入状态(注意: 必须定义为8个字节元素的数组)

    BOOL DEVAPI FAR PASCAL USB2833_SetDeviceDO(             // 输出开关量状态
                           HANDLE hDevice,            // 设备句柄,它应由CreateDevice函数创建                              
                           BYTE bDOSts[8]);        // 开关输出状态(注意: 必须定义为8个字节元素的数组)

   //############################################################################
   BOOL DEVAPI FAR PASCAL USB2833_GetDevVersion(            // 获取设备固件及程序版本
                           HANDLE hDevice,            // 设备对象句柄,它由CreateDevice函数创建
                           PULONG pulFmwVersion,      // 固件版本
                           PULONG pulDriverVersion);  // 驱动版本

   //############################ 线程操作函数 ################################
   DEVAPI HANDLE FAR PASCAL USB2833_CreateSystemEvent(void);   // 创建内核系统事件对象
   BOOL DEVAPI FAR PASCAL USB2833_ReleaseSystemEvent(HANDLE hEvent); // 释放内核事件对象

   //################# 其他附加函数 ########################

#ifdef __cplusplus
}
#endif

//#################### 辅助常量 #####################

const long USB2833_MAX_AD_CHANNELS = 16;

#ifndef _USB2833_FIFO_LENGTH_
#define _USB2833_FIFO_LENGTH_
// 本卡可以支持的各种FIFO存储器的长度(点)
const long FIFO_IDT7202_LENGTH            = 1024;
const long FIFO_IDT7203_LENGTH            = 2048;
const long FIFO_IDT7204_LENGTH            = 4096;
const long FIFO_IDT7205_LENGTH            = 8192;
const long FIFO_IDT7206_LENGTH            = 16384;
const long FIFO_IDT7207_LENGTH            = 32768;
#endif; // _USB2833_FIFO_LENGTH_

// 自动包含驱动函数导入库
// 自动包含驱动函数导入库
#ifndef _USB2833_DRIVER_
   #ifndef _WIN64
      #pragma comment(lib, "USB2833_32.lib")
      #pragma message("======== Welcome to use our art company's products!")
      #pragma message("======== Automatically linking with USB2833_32.dll...")
      #pragma message("======== Successfully linked with USB2833_32.dll")
   #else
      #pragma comment(lib, "USB2833_64.lib")
      #pragma message("======== Welcome to use our art company's products!")
      #pragma message("======== Automatically linking with USB2833_64.dll...")
      #pragma message("======== Successfully linked with USB2833_64.dll")
   #endif
#endif

#endif; // _USB2833_DEVICE_
