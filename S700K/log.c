/*
log���ݡ������¹���
1.ERR(),INFO(),DEBUG()�����������������Ϣ��
	�����Ĳ�����printf��ȫһ��.
2.��������ļ���debugview������������
	PRINT_LOG�궨���������
	Ĭ��Ϊ.\log\log.txt�ͱ�debugview������ӡ�
3.���Ե��������Ϣ���𡣷�����Թ����к͵��Խ����󣬶�����ɾ��������Ϣ��
��Ϊ��ȫ�ر�/�� CONFIG_ENABLE_DEBUG
	DEBUG_LEVEL_ERR,	ֻ���ERR��Ϣ
	DEBUG_LEVEL_INFO,   ֻ���ERR��INFO��Ϣ
	DEBUG_LEVEL_DEBUG,    ���ERR��INFO��DEBUG��Ϣ��
*/

//#include <ansi_c.h>
//#include <utility.h>


#include <WINDOWS.H>

#include "log.h"
#include <TIME.H>

#ifdef __cplusplus
extern "C" {
#endif

//#define	LOG_APPEND     // ׷�Ӽ�¼��log.txt�ļ�
#define	LOG_ONLY_ONCE  // �����ǰ�����ݣ�ֻ���汾�����е����ݡ�


#define CONFIG_ENABLE_DEBUG
#define DEBUG_LEVEL DEBUG_LEVEL_DEBUG

	static char* TitleInfo[]=
	{
		"SKQ-DISABLE:","SKQ-ERR:","SKQ-INFO:","SKQ-DEBUG:"
	};

	void ERR1(char fmt[],...)
	{
#if defined CONFIG_ENABLE_DEBUG && (DEBUG_LEVEL >= DEBUG_LEVEL_ERR)
		va_list args;

		va_start(args,fmt);
		PRINT(DEBUG_LEVEL_ERR,fmt,args);
		va_end(args);
#endif
	}


	void INFO1(char fmt[],...)
	{
#if defined CONFIG_ENABLE_DEBUG && (DEBUG_LEVEL >= DEBUG_LEVEL_INFO)
		va_list args;

		va_start(args,fmt);
		PRINT(DEBUG_LEVEL_INFO,fmt,args);
		va_end(args);
#endif
	}

	void DEBUG1(char fmt[],...)
	{
#if defined CONFIG_ENABLE_DEBUG && (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG)
		va_list args;

		va_start(args,fmt);
		PRINT(DEBUG_LEVEL_DEBUG,fmt,args);
		va_end(args);
#endif
	}







# if 0
	void ASSERT()
	{
		//PRINT("ASSERT: %s %s %d",__FILE__, __FUNCTION__, __LINE__);
		while (1);
	}
	void INFO(x)
	{
		if (debug >= DEBUG_LEVEL_INFO)
		{
			PRINT(x);
		}
	}

	void DEBUG(x)
	{
		if (debug >= DEBUG_LEVEL_DEBUG)
		{
			PRINT(x);
		}
	}
#endif




//int ToLog (char file_name[],char error_type[],char function[])
#define LogErr(x)								\
	{												\
		LogErr2File("log.txt",x);					\
	}

	int Log2StrAndPrint(DebugLevel debuglevel,char * fmt,va_list args)
	{
		char buffer[1024];
		char *pbuf = buffer;

		sprintf(pbuf,"%s",TitleInfo[debuglevel]);
		pbuf += strlen(pbuf);

		vsprintf(pbuf,fmt,args);
		pbuf += strlen(pbuf);

		PRINT_LOG (buffer);

		return 0;
	}


	int Str2FileWithTime(char file_name[],char *str)
	{
		/*
			strftime( timebuf, sizeof(timebuf), " %Y/%m/%d %X %A �����%j�� %z" , localtime(&t) );
			%Y����		%m����		%d����		%A������
			%X��ʱ����	%j������ڼ���
		*/

		FILE *fileHandle;
		char timebuf[100];
		static isFirst=1;

		time_t t =time(0);

		strftime( timebuf, sizeof(timebuf), "%Y/%m/%d %X --- " , localtime(&t) );

		//
#ifdef LOG_SAVE_APPEND
		fileHandle = fopen (file_name, "a");
#elif defined  LOG_ONLY_ONCE
		if(isFirst)
		{
			isFirst = 0;
			fileHandle = fopen (file_name, "w");
		}
		else
		{
			fileHandle = fopen (file_name, "a");
		}
#else
		{
			return 0;
		}
#endif
		//fileHandle = fopen (file_name, "a");
		//

		fputs(timebuf,fileHandle);
		fputs (str, fileHandle);
		fputs("\n",fileHandle);
		fclose (fileHandle);
		return 0;
	}


	int Str2File(char file_name[],char *str)
	{

		FILE *fileHandle;

		fileHandle = fopen (file_name, "a");
		fputs (str, fileHandle);
		fclose (fileHandle);
		return 0;
	}


	int LogErr2File(char file_name[],char * fmt,va_list args)
	{

		char *datee;
		char *timee;
		FILE *fileHandle;
		int sec,min,hour,year,day,mon;

		char buffer[200];
		char report[200];

		//sprintf(report_name,"%s\\",Result_folder);
		//sprintf(report,"Log\\%s","Note.txt");
		sprintf(report,"%s",file_name);

		fileHandle = fopen (report, "a");

		//GetSystemDate (&mon, &day, &year);
		//GetSystemTime (&hour, &min, &sec);

		//strcpy(buffer,"");
		//sprintf(buffer,"\t%d/%.2d/%.2d%  .2d:%.2d:%.2d\n",year,mon,day,hour,min,sec);
		//fputs (buffer, fileHandle);

		//va_start(args,fmt);
		vsprintf(buffer,fmt,args);
		//va_end(args);
		fputs (buffer, fileHandle);

		sprintf(buffer,"\n");
		fputs (buffer, fileHandle);
		fclose (fileHandle);

		return 0;
	}


# if 0
#define DEBUGERROR   DebugError(__FILE__,__LINE__

	UINT8 DebugError(UINT8 *file, UINT32 line, UINT8 * fmt,...)
	{
		char    buf[PARAM_LEN] = {0};
		va_list    args;

		va_start(args,fmt);
		vsprintf(buf,fmt,args);
		va_end(args);

		return  DEBUG_LOG(DEBUG_ERROR, DEBUG_ERROR,  file, line, buf);
	}

	UINT8 DEBUG_LOG(UINT8 logLevel, UINT8 printLevel, UINT8 *file, UINT32 line, UINT8 *fmt, ...)
	{
		UINT8 pname[PNAME_LEN] = {'\0'};
		MODOPT *ptDebugOpt = NULL;
		UINT8 buffer[PARAM_LEN] = {'\0'};
		va_list    args;

		va_start(args, fmt);
		vsnprintf(buffer, PARAM_LEN-1, fmt, args);
		va_end(args);

		strncpy(pname, ptDebugOpt->; pname, PNAME_LEN);
		write_log(pname, buffer, file, line);

		return ((INT8)-1);
	}
#endif

#if 0
	int ToLog (char file_name[],char error_type[],char function[])
	{
		char *datee;
		char *timee;
		FILE *fileHandle;
		int sec,min,hour,year,day,mon;
		char buffer[200];
		char report[200];

		//sprintf(report_name,"%s\\",Result_folder);
		//sprintf(report,"Log\\%s","Note.txt");
		sprintf(report,"%s",file_name);

		//LOG_SAVE_APPEND, // ��׷�ӷ�ʽ���浽log.txt�ļ�
		//LOG_SAVE_WRITE,  // �����ǰ�����ݣ�ֻ���汾�����е����ݡ�

		fileHandle = fopen (report, "a");
		//GetSystemDate (&mon, &day, &year);
		//GetSystemTime (&hour, &min, &sec);

		strcpy(buffer,"");
		sprintf(buffer,"[%s]\n",error_type);
		fputs (buffer, fileHandle);

		strcpy(buffer,"");
		sprintf(buffer,"\t%d/%.2d/%.2d%  .2d:%.2d:%.2d\n",year,mon,day,hour,min,sec);
		fputs (buffer, fileHandle);

		strcpy(buffer,"");
		sprintf(buffer,"\t%s\n",function);
		fputs (buffer, fileHandle);

		sprintf(buffer,"\n");
		fputs (buffer, fileHandle);
		fclose (fileHandle);

		return 0;
	}
#endif

// ��������д��Log�ļ���
	void TestPara2Log(double dfDistance,  // ����
					  double dfCurrentForce,  // ��ǰ��
					  double dfRatedForce,	 // Ŀ����
					  double fAOAForce,       // ������A��ѹ
					  double fAOBForce)       // ������B��ѹ
	{
		INFO1("    ����:%f(mm)����ǰ��:%f(KN)��Ŀ����:%f(KN)��������A��ѹ:%f(V)��������B��ѹ:%f(V)",
			  dfDistance,
			  dfCurrentForce,dfRatedForce,
			  fAOAForce,
			  fAOBForce
			 );
	}
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
)
{
	INFO1("    ʱ��:%u(ms)������:%s������:%f(mm)���ٶ�:%f(mm/s)��"
		  "����:%d����ǰ��:%f(KN)��Ŀ����:%f(KN)��"
		  "������A��ѹ:%f(V)��������B��ѹ:%f(V)��"
		  "A�����:%f(A)��B�����:%f(A)��C�����:%f(A)��"
		  "�ۼƴ���:%d�Σ��ۼ���:%f(KN)���ۼ�A�����:%f(A)��"
		  "�ۼ�B�����:%f(A)���ۼ�C�����:%f(A)",
		  Ticks,	//���β���ʱ��(tick)(mm)
		  logbuf,	//�����ı�
		  dfDistance,	//����(mm)
		  dfSpeed,		//�ٶ�(mm/s)
		  
		  bOk,			 //����
		  dfCurrentForce,//��ǰ��(KN)
		  dfRatedForce,	 //Ŀ����
		  fAOAForce,	 //������A��ѹ
		  fAOBForce,	 //������B��ѹ
		  
		  dfIa,//A�����(A)
		  dfIb,//B�����(A)
		  dfIc,//C�����(A)
		  dwCount,		//�ۼƴ���
		  dfForceCount,	//�ۼ���(KN)
		  dfIaCount,		//�ۼ�A�����(A)
		  dfIbCount,		//�ۼ�B�����(A)
		  dfIcCount 		//�ۼ�C�����(A)
		 );

}


#ifdef __cplusplus
}
#endif
