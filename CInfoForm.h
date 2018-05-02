#include "CForm.h"
#ifndef _Cinfoform_20140604_h_
#define _Cinfoform_20140604_h_


typedef int (*pSql_CallBack)(void *,int ,char ** ,char ** );//生成显示栏的回调
typedef int (*pSql_CountCallBack)(void *,int ,char **,char ** );//生成计算数目的回调
int CountPage(int iTotal,int iShowNum);//计算页数的函数

class CInfoForm:public CForm
{
public:
	CInfoForm(CComponent *owner,int iStartY,int iStartX,int iHeight,int iWidth);
	int KeyListener();
	void Flash();
	CComponent *pInfoLab;
	//总条数
	int iTotal;
	int iPage;
	char *GetInfo();
	char sSql[1024];
	char sSqlCount[1024];
	char *GetSql(char *sql);  //截取limit之前的语句
	pSql_CallBack  Show_CallBack;
	pSql_CountCallBack Count_CallBack;
protected:
private:

};
 


#endif