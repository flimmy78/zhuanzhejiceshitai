/*
 * Name:    log.h
 *
 * Purpose: general debug system
 *
 */
#ifndef __LOG_H__1234__
#define __LOG_H__1234__

#ifdef __cplusplus
	extern "C"{
#endif

#include "stdio.h"
#include "stdarg.h"

typedef enum _debug_level {
	DEBUG_LEVEL_DISABLE = 0,
	DEBUG_LEVEL_ERR,
	DEBUG_LEVEL_INFO,
	DEBUG_LEVEL_DEBUG,
}DebugLevel;

int ToLog (char file_name[],char error_type[],char function[]);
int LogErr2File(char file_name[],char * fmt,va_list args);
int Log2StrAndPrint(DebugLevel debuglevel,char * fmt,va_list args);
int Str2FileWithTime(char file_name[],char *str);

void INFO1(char fmt[],...);
void DEBUG1(char fmt[],...);
void ERR1(char fmt[],...);

//#define PRINT(fmt,args)               LogErr2File("log.txt",fmt,args)
#define PRINT(debuglevel,fmt,args)		Log2StrAndPrint(debuglevel,fmt,args)
#define PRINT_LOG(str)	Str2FileWithTime(".\\log\\log.txt",str);OutputDebugString(str)


/////////////////////////
// ��������д��Log�ļ����汾1��
void TestPara2Log(double dfDistance,  // ����
		 double dfCurrentForce,  // ��ǰ��
		 double dfRatedForce,	 // Ŀ����
		 double fAOAForce,       // ������A��ѹ
		 double fAOBForce);      // ������B��ѹ
// ��������д��Log�ļ����汾2��д��������ݡ�
void TestParaV2ToLog(
	DWORD Ticks,	//���β���ʱ��(tick)(mm)
	char* logbuf,	//�����ı�
	double dfDistance,	//����(mm)
	double dfSpeed,						//�ٶ�(mm/s)
	BOOL   bOk,							//����
	double dfCurrentForce,
	double dfRatedForce,	//��ǰ��(KN),Ŀ����
	double fAOAForce,	//������A��ѹ
	double fAOBForce,	//������B��ѹ
	double dfIa,//A�����(A)
	double dfIb,//B�����(A)
	double dfIc,//C�����(A)
	int    dwCount,		//�ۼƴ���
	double dfForceCount,//�ۼ���(KN)
	double dfIaCount,	//�ۼ�A�����(A)
	double dfIbCount,	//�ۼ�B�����(A)
	double dfIcCount 	//�ۼ�C�����(A)
);
#ifdef __cplusplus
	}
#endif
#endif
