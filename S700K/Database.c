// #########################################################################
// *************************************************************************
//                     Copyright (C) 2002-2020.
//   THIS IS AN UNPUBLISHED WORK CONTAINED CONFIDENTIAL, AND PROPRIETARY
//              INFORMATION WHICH IS THE PROPERTY OF TangBo.
// ANY DISCLOSURE, USE, OR REPRODUCTION, WITHOUT WRITTEN AUTHORIZATION FROM
//                        TangBo, IS STRICT.
// #########################################################################
// *************************************************************************

#include <ansi_c.h>
#include <windows.h>
#include <WinBase.h>
#include <userint.h>
#include <utility.h>
#include "Device.h"
#include <formatio.h>
#include <cvirte.h>
#include "..\include\global.h"
#include "toolbox.h"
#include "odbcinst.h"
#include "Database.h"  

//==============================================================================
// Constants

//==============================================================================
long DB_Initialize(LPT_Database db)
{
   char dbConnectString[128];
   int resCode;
   resCode = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &db->hEnvHandle);
   if (resCode != SQL_SUCCESS)
   {
      return FAIL;
   }
   
   resCode = SQLSetEnvAttr (db->hEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
   if (resCode != SQL_SUCCESS)
   {
      return FAIL;
   }
   
   resCode = SQLAllocHandle (SQL_HANDLE_DBC, db->hEnvHandle, &db->hDbcHandle);
   if (resCode != SQL_SUCCESS)
   {
      return FAIL;
   }
   
   sprintf(dbConnectString, "DSN=%s;DBQ=%s", db->cDSNName, db->cDatabase);
   resCode = SQLConfigDataSource (NULL, 
      ODBC_ADD_SYS_DSN, 
      "Microsoft Access Driver (*.mdb)\0",
      dbConnectString);
   
   return PASS;
}

//------------------------------------------------------------------------------------------------
//���ݿ�����
long DB_Connect(LPT_Database db)
{
   char dbConnectString[128];
   int resCode;
   
   sprintf(dbConnectString, "DSN=%s;DBQ=%s", db->cDSNName, db->cDatabase);
   
   resCode = SQLConnect (db->hDbcHandle, (UCHAR*)db->cDSNName, SQL_NTS,
      (UCHAR*)"admin", SQL_NTS,
      (UCHAR*)db->cPassword, SQL_NTS);
   
   if (resCode != SQL_SUCCESS)
   {
      return FAIL;
   }
   
   return PASS;
}
                 
//------------------------------------------------------------------------------------------------
//�ر����ݿ�
long DB_Deinitialize(LPT_Database db)
{
   char dbConnectString[128];
   int resCode;
   
   SQLDisconnect (db->hDbcHandle);
   
   if (db->hDbcHandle != SQL_NULL_HANDLE)
      SQLFreeHandle (SQL_HANDLE_DBC, db->hDbcHandle);
   
   if (db->hEnvHandle != SQL_NULL_HANDLE)
      SQLFreeHandle (SQL_HANDLE_ENV, db->hEnvHandle);

   db->hDbcHandle = SQL_NULL_HANDLE;
   db->hEnvHandle = SQL_NULL_HANDLE;

   sprintf(dbConnectString, "DSN=%s", db->cDSNName);
   resCode = SQLConfigDataSource (NULL, 
      ODBC_REMOVE_SYS_DSN, 
      "Microsoft Access Driver (*.mdb)\0",
      dbConnectString);
   
   return PASS;
}

//------------------------------------------------------------------------------------------------
//�ر����ݿ�
long DB_Disconnect(LPT_Database db)
{
   char dbConnectString[128];
   int resCode;
   
   resCode = SQLDisconnect (db->hDbcHandle);
   if (resCode != SQL_SUCCESS)
   {
      return FAIL;
   }
   return PASS;
}

//------------------------------------------------------------------------------------------------
SQLHANDLE DB_ActivateSQL(LPT_Database db, char* SQLText)
{
   int resCode;
   SQLHANDLE hStmt = SQL_NULL_HANDLE;
   char Command[256];
   
   //�������ݿ�
   resCode = SQLAllocHandle (SQL_HANDLE_STMT, db->hDbcHandle, &hStmt);
   if (resCode != SQL_SUCCESS)
      return SQL_NULL_HANDLE;
   
   resCode = SQLExecDirect (hStmt, SQLText, SQL_NTS);
   
   return hStmt;
}

//------------------------------------------------------------------------------------------------
long DB_DeactivateSQL(SQLHANDLE StateHandle)
{
   int resCode;
   
   if (StateHandle == SQL_NULL_HANDLE)
      return PASS;
   
   resCode = SQLFreeHandle (SQL_HANDLE_STMT, (SQLHANDLE)StateHandle);
   if (resCode != SQL_SUCCESS)
   {
      return FAIL;
   }
   return PASS;
}

//------------------------------------------------------------------------------------------------
// ��ȡ�ͺ�
void Database_ReadModel(LPT_Database db, int panel, int control)
{
   char Model[64];
   int Model_S;
   
   SQLHANDLE StateHandle;
   
   ClearListCtrl (panel, control);
   
   //�������ݿ�
   if (DB_Connect(db) != PASS)                
   {
      MessageBox(NULL, "��׼���ݿ��ļ���ʧ��", "����", MB_OK | MB_ICONERROR);
      return;
   }
   //���ݿ�ӳ��
   StateHandle = DB_ActivateSQL (db, "SELECT �ͺ� FROM �ֵ ORDER BY �ͺ�");
   if (StateHandle == SQL_NULL_HANDLE)
      goto Exit;
   SQLBindCol (StateHandle, 1, SQL_C_CHAR, Model, 51, &Model_S);
   
   //�����ֶ�ֵ     
   while (SQLFetch (StateHandle) == 0)
   {
      InsertListItem (panel, control, -1, Model, Model);
   }
   
   DB_DeactivateSQL (StateHandle);
   
Exit:   
   DB_Disconnect(db);
}

//------------------------------------------------------------------------------------------------
// ����ת��
void Str2Cell(LPT_CellData pCell, int nLen, char* pData)
{
   char *str1, *str2, *str3;
   
   if (nLen <= 0)
      pData[0] = '\x0';
   
   pData[50] = '\x0';
   RemoveSurroundingWhiteSpace (pData);
   StringUpperCase (pData);
   
   // Read data
   if ((strcmp (pData, "N") == 0) || (strlen (pData) == 0))
   {
      strcpy (pCell->cData, "");
      return;
   }
   
   str1 = strtok (pData, ",");
   str2 = strtok (NULL, ",");
   str3 = strtok (NULL, ",");
   
   strcpy (pCell->cData, str1);
      
   pCell->fData1 = strtod (str2, NULL); 
   pCell->fData2 = strtod (str3, NULL); 
}

//------------------------------------------------------------------------------------------------
// ����ת��
void Str2Cell2(LPT_Device pDevice, int nLen, char* pData)
{
   char *str1, *str2, *str3;
   
   if (nLen <= 0)
      pData[0] = '\x0';
   
   pData[50] = '\x0';
   RemoveSurroundingWhiteSpace (pData);
   StringUpperCase (pData);
   
   // Read data
   str1 = strtok (pData, "(");
   str2 = strtok (NULL, "(");
   
   strcpy (pDevice->Standard.acModelName, str1);
   if (str2 != NULL)
   {
      strncpy (pDevice->Standard.acLine, str2, strlen(str2) - 1);
   }
   else
      strcpy (pDevice->Standard.acLine, "");
}

//------------------------------------------------------------------------------------------------
// �����׼���ݿ�
int Database_ReadStandard(LPT_Database db, LPT_Device pDevice, char model[])
{
   int numRecord;
   SQLUSMALLINT iCol = 2;
   int Fields = 13;
   char Command[2048];
   
   char cModel[64];
   char cData[20][64] = {0};
   int cData_S[20] = {0};
   float fData;
   
   SQLHANDLE StateHandle;
   
   //�������ݿ�
   if (DB_Connect (db) != PASS)                
   {
      MessageBox(NULL, "��׼���ݿ��ļ���ʧ��", "����", MB_OK | MB_ICONERROR);
      return -1;
   }
   
   // Create SQL
   strcpy (Command, "SELECT ");
   strcat (Command, "�ͺ�, ������ѹ, ");
   strcat (Command, "��������, Ħ������, ");
   strcat (Command, "����ʱ��, ��������, ����, ��ѹ����, A���ŵ�ѹ1, B���ŵ�ѹ1, A���ŵ�ѹ2, B���ŵ�ѹ2, ��� ");
   strcat (Command, "FROM �ֵ WHERE �ͺ�='");
   strcat (Command, model);
   strcat (Command, "'");

   StateHandle = DB_ActivateSQL (db, Command);
   if (StateHandle == SQL_NULL_HANDLE)
      return FAIL;
   
   for (iCol = 0; iCol < Fields; iCol ++)
   {
      SQLBindCol (StateHandle, iCol + 1, SQL_C_CHAR, cData[iCol], 51, &cData_S[iCol]);
   }

   if (SQLFetch (StateHandle) != 0)
   {
      DB_DeactivateSQL (StateHandle);
      return FAIL;
   }
   
   // Read data
  
   iCol = 0;
   Str2Cell2 (pDevice, cData_S[0], cData[0]);
   Str2Cell (&pDevice->ssRatedVoltage, cData_S[1],  cData[1]);
   Str2Cell (&pDevice->ssRatedCurrent, cData_S[2],  cData[2]);
   Str2Cell (&pDevice->ssRatedCurrent_F, cData_S[3],  cData[3]);
   Str2Cell (&pDevice->ssRatedActionTime, cData_S[4],  cData[4]);
   Str2Cell (&pDevice->ssRatedForce, cData_S[5],  cData[5]);
   
   Str2Cell (&pDevice->ssRatedStroke, cData_S[6],  cData[6]);
   Str2Cell (&pDevice->ssDCVoltageSet, cData_S[7],  cData[7]);
   Str2Cell (&pDevice->ssAValveVoltage1, cData_S[8],  cData[8]);
   Str2Cell (&pDevice->ssBValveVoltage1, cData_S[9],  cData[9]);
   Str2Cell (&pDevice->ssAValveVoltage2, cData_S[10],  cData[10]);
   Str2Cell (&pDevice->ssBValveVoltage2, cData_S[11],  cData[11]);
   if (cData_S[12] <= 0)
      cData[12][0] = '\x0';
 
   pDevice->Standard.dwModelID = strtol (cData[12], NULL, 10);

   DB_DeactivateSQL (StateHandle);
   
   DB_Disconnect (db);
   return PASS;
}

//------------------------------------------------------------------------------------------------
