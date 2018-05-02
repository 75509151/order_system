#ifndef _userdb_20140604_h_
#define _userdb_20140604_h_
int RoleId_CallBack(void *canshu,int iColumn,char ** colValue,char **colName );
int CheckAccount_Callback(void *canshu,int iColumn,char ** colValue,char **colName );
int CUser_InfoCallBack(void *canshu,int iColumn,char ** colValue,char **colName );
int User_MaxIdCallBack(void *canshu,int iColumn,char ** colValue,char **colName );
int BtnSearch_CallBack(void *canshu,int iColumn,char ** colValue,char **colName );
int BtnSearch_CountCallBack(void *canshu,int iColumn,char ** colValue,char **colName );
#endif