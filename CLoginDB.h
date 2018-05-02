#ifndef _CLoginDB_20140602_h_
#define _CLoginDB_20140602_h_

//typedef int(* Sql_Callback)(void *,int ,char **,char **);
//typedef int (* Sql_Callback)(void *canshu,int iColumn,char ** colValue,char **colName );
int CBar_CallBack(void *canshu,int iColumn,char ** colValue,char **colName );
int BtnOK_CallBack(void *canshu,int iColumn,char ** colValue,char **colName);
int CMenu_CallBack(void *canshu,int iColumn,char ** colValue,char **colName );
#endif