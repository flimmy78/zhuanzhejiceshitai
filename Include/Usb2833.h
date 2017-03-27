#ifndef _USB2833_DEVICE_
#define _USB2833_DEVICE_

#include<windows.h>
//***********************************************************
// ����AD�ɼ��Ĳ����ṹ
typedef struct _USB2833_PARA_AD
{
   LONG FirstChannel;      // ��ͨ��,ȡֵ��ΧΪ[0, 15]
   LONG LastChannel;    // ĩͨ��,ȡֵ��ΧΪ[0, 15]
   LONG InputRange;     // ����ѡ��
   LONG Gains;          // ���������
   LONG GroundingMode;     // �ӵط�ʽ�����˻�˫��ѡ��
} USB2833_PARA_AD, *PUSB2833_PARA_AD;

//***********************************************************
// ADӲ������USB2833_PARA_AD�е�InputRange������ʹ�õ�ѡ��
const long USB2833_INPUT_N10000_P10000mV= 0x00; // ��10000mV
const long USB2833_INPUT_N5000_P5000mV = 0x01; // ��5000mV
const long USB2833_INPUT_N2500_P2500mV = 0x02; // ��2500mV
const long USB2833_INPUT_0_P10000mV    = 0x03; // 0��10000mV

//***********************************************************
// AD����USB2833_PARA_AD�е�Gainsʹ�õ�Ӳ������ѡ��
const long USB2833_GAINS_1MULT         = 0x00; // 1������(ʹ��AD8251�Ŵ���)
const long USB2833_GAINS_2MULT         = 0x01; // 2������(ʹ��AD8251�Ŵ���)
const long USB2833_GAINS_4MULT         = 0x02; // 4������(ʹ��AD8251�Ŵ���)
const long USB2833_GAINS_8MULT         = 0x03; // 8������(ʹ��AD8251�Ŵ���)

//***********************************************************
// AD����(USB2833_PARA_AD)�е�GroundingModeʹ�õ�ģ���źŽӵط�ʽѡ��
const long USB2833_GNDMODE_SE       = 0x00;  // ���˷�ʽ(SE:Single end)
const long USB2833_GNDMODE_DI       = 0x01;  // ˫�˷�ʽ(DI:Differential)

//***********************************************************
// DA�������USB2833_WriteDeviceDA��ģ���������Χ����OutputRange��ʹ�õ�ѡ��
const long USB2833_OUTPUT_0_P5000mV    = 0x00;     // 0��5000mV
const long USB2833_OUTPUT_0_P10000mV   = 0x01;     // 0��10000mV
const long USB2833_OUTPUT_0_P10800mV   = 0x02;     // 0��10800mV
const long USB2833_OUTPUT_N5000_P5000mV   = 0x03;     // ��5000mV
const long USB2833_OUTPUT_N10000_P10000mV= 0x04;   // ��10000mV
const long USB2833_OUTPUT_N10800_P10800mV= 0x05;   // ��10800mV

//***********************************************************
// ���ڼ�����CNT�Ĳ����ṹ
// Ӳ������ControlMode������ģʽѡ��
const long USB2833_GATEMODE_POSITIVE_0 = 0x00;     // COUNTER:GATE�ߵ�ƽʱ�������͵�ƽʱֹͣ����������ʱ����д���ֵ������ֵ����
                                       // �������������жϣ�д���ֵ��ʼ����ʱOUT��ʼΪ0����������0ʱOUTΪ1

const long USB2833_GATEMODE_RISING_1   = 0x01;     // COUNTER:GATE�ϱ��ش��������������г���GATE����������װ���ֵ����
                                       // �ɱ�̵������壺��д���ֵʱOUTΪ1������ʼ����ʱOUTΪ0����������0ʱOUT�ٴ�Ϊ1

const long USB2833_GATEMODE_POSITIVE_2 = 0x02;     // COUNTER:GATE�ߵ�ƽʱ�������͵�ƽʱֹͣ����������ʱ����д���ֵ������ֵ����
                                       // Ƶ�ʷ������������ڼ�OUTΪ1��������0�����һ�����ڵ�0��������װ�����ֵ����

const long USB2833_GATEMODE_POSITIVE_3 = 0x03;     // COUNTER:GATE�ߵ�ƽʱ�������͵�ƽʱֹͣ����������ʱ����д���ֵ������ֵ����
                                       // �����������������ڼ�OUTΪ1��������0�����һ�����ڵ�0��������װ�����ֵ����

const long USB2833_GATEMODE_POSITIVE_4 = 0x04;     // COUNTER:GATE�ߵ�ƽʱ�������͵�ƽʱֹͣ����������ʱ����д���ֵ������ֵ����
                                       // �������ѡͨ��д���ֵOUTΪ1�� ��������OUT���һ�����ڵ͵�ƽ�ź�

const long USB2833_GATEMODE_RISING_5   = 0x05;     // COUNTER:GATE�ϱ��ش��������������г���GATE����������װ���ֵ����
                                       // Ӳ������ѡͨ��д���ֵOUTΪ1�� ��������OUT���һ�����ڵ͵�ƽ�ź�

//***********************************************************
// ���������ӿ�
#ifndef _USB2833_DRIVER_
#define DEVAPI __declspec(dllimport)
#else
#define DEVAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
   //######################## ����ͨ�ú��� #################################
    HANDLE DEVAPI FAR PASCAL USB2833_CreateDevice(int DeviceLgcID); // �����豸����(�ú���ʹ��ϵͳ���߼��豸ID��
    HANDLE DEVAPI FAR PASCAL USB2833_CreateDeviceEx(int DevicePhysID); // �����豸����(�ú���ʹ�ð�������ID,�ɰ��뿪��DID1ʵ��)
   int DEVAPI FAR PASCAL USB2833_GetDeviceCount(HANDLE hDevice);      // ȡ��USB2833��ϵͳ�е��豸����
   BOOL DEVAPI FAR PASCAL USB2833_GetDeviceCurrentID(HANDLE hDevice, PLONG DeviceLgcID, PLONG DevicePhysID); // ȡ�õ�ǰ�豸���߼�ID�ź�����ID��
   BOOL DEVAPI FAR PASCAL USB2833_ListDeviceDlg(void); // �öԻ����б�ϵͳ���е�����USB2833�豸
   BOOL DEVAPI FAR PASCAL USB2833_ResetDevice(HANDLE hDevice);     // ��λ����USB�豸
    BOOL DEVAPI FAR PASCAL USB2833_ReleaseDevice(HANDLE hDevice);    // �豸���

   //####################### AD���ݶ�ȡ���� #################################
    BOOL DEVAPI FAR PASCAL USB2833_InitDeviceAD(            // ��ʼ���豸,������TRUE��,�豸���̿�ʼ����.
                           HANDLE hDevice,            // �豸���,��Ӧ��CreateDevice��������
                           PUSB2833_PARA_AD pADPara);  // Ӳ������, �����ڴ˺����о���Ӳ��״̬                    

    BOOL DEVAPI FAR PASCAL USB2833_ReadDeviceAD(            // ��ʼ���豸�󣬼����ô˺�����ȡ�豸�ϵ�AD����
                           HANDLE hDevice,            // �豸���,��Ӧ��CreateDevice��������
                           USHORT ADBuffer[],         // �����ڽ������ݵ��û�������
                           LONG nReadSizeWords,    // ��ȡAD���ݵĳ���(��)  
                           PLONG nRetSizeWords);// ʵ�ʷ������ݵĳ���(��)

    BOOL DEVAPI FAR PASCAL USB2833_ReleaseDeviceAD( HANDLE hDevice); // ֹͣAD�ɼ����ͷ�AD������ռ��Դ

      //################# AD��Ӳ�������������� ######################## 
   BOOL DEVAPI FAR PASCAL USB2833_SaveParaAD(HANDLE hDevice, PUSB2833_PARA_AD pADPara);  
    BOOL DEVAPI FAR PASCAL USB2833_LoadParaAD(HANDLE hDevice, PUSB2833_PARA_AD pADPara);
    BOOL DEVAPI FAR PASCAL USB2833_ResetParaAD(HANDLE hDevice, PUSB2833_PARA_AD pADPara); // ��AD���������ָ�������Ĭ��ֵ

   //####################### DA����������� #################################
   // ���ڴ������ͨ�û�����Щ�ӿ���򵥡����ݡ���ɿ������û�����֪���豸
   // �Ͳ㸴�ӵ�Ӳ������Э��ͷ����������Ʊ�̣���������һ������������
   // ��ʵ�ָ��١�������DA�������
   BOOL DEVAPI FAR PASCAL USB2833_WriteDeviceDA(         // дDA����
                           HANDLE hDevice,         // �豸������,����CreateDevice��������
                           LONG OutputRange,    // ������̣����嶨����ο�����ĳ������岿��
                           SHORT nDAData,       // �����DAԭʼ����[0, 4095]
                           int nDAChannel);     // DA���ͨ��[0-3](д��4�������ĸ�ͨ��������)

   //##################### ���������ƺ��� ##########################
    BOOL DEVAPI FAR PASCAL USB2833_SetDeviceCNT(            // ��ʼ��������
                           HANDLE   hDevice,       // �豸���
                           ULONG ContrlMode,       // ����������ģʽ
                           ULONG CNTVal,           // ������ֵ(16λ)
                           ULONG ulChannel);       // ͨ��ѡ��[0-2]        

   BOOL DEVAPI FAR PASCAL USB2833_GetDeviceCNT(          // ȡ�ø�·�������ĵ�ǰ����ֵ
                           HANDLE   hDevice,       // �豸������,����CreateDevice��������
                           PULONG   pCNTVal,       // ���ؼ���ֵ(16λ)
                           ULONG ulChannel);       // ͨ��ѡ��[0-2]

   //####################### ����I/O����������� #################################
   BOOL DEVAPI FAR PASCAL USB2833_GetDeviceDI(              // ȡ�ÿ�����״̬     
                           HANDLE hDevice,            // �豸���,��Ӧ��CreateDevice��������                              
                           BYTE bDISts[8]);        // ��������״̬(ע��: ���붨��Ϊ8���ֽ�Ԫ�ص�����)

    BOOL DEVAPI FAR PASCAL USB2833_SetDeviceDO(             // ���������״̬
                           HANDLE hDevice,            // �豸���,��Ӧ��CreateDevice��������                              
                           BYTE bDOSts[8]);        // �������״̬(ע��: ���붨��Ϊ8���ֽ�Ԫ�ص�����)

   //############################################################################
   BOOL DEVAPI FAR PASCAL USB2833_GetDevVersion(            // ��ȡ�豸�̼�������汾
                           HANDLE hDevice,            // �豸������,����CreateDevice��������
                           PULONG pulFmwVersion,      // �̼��汾
                           PULONG pulDriverVersion);  // �����汾

   //############################ �̲߳������� ################################
   DEVAPI HANDLE FAR PASCAL USB2833_CreateSystemEvent(void);   // �����ں�ϵͳ�¼�����
   BOOL DEVAPI FAR PASCAL USB2833_ReleaseSystemEvent(HANDLE hEvent); // �ͷ��ں��¼�����

   //################# �������Ӻ��� ########################

#ifdef __cplusplus
}
#endif

//#################### �������� #####################

const long USB2833_MAX_AD_CHANNELS = 16;

#ifndef _USB2833_FIFO_LENGTH_
#define _USB2833_FIFO_LENGTH_
// ��������֧�ֵĸ���FIFO�洢���ĳ���(��)
const long FIFO_IDT7202_LENGTH            = 1024;
const long FIFO_IDT7203_LENGTH            = 2048;
const long FIFO_IDT7204_LENGTH            = 4096;
const long FIFO_IDT7205_LENGTH            = 8192;
const long FIFO_IDT7206_LENGTH            = 16384;
const long FIFO_IDT7207_LENGTH            = 32768;
#endif; // _USB2833_FIFO_LENGTH_

// �Զ������������������
// �Զ������������������
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
