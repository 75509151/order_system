#include "CForm.h"
#ifndef _Cinfoform_20140604_h_
#define _Cinfoform_20140604_h_


typedef int (*pSql_CallBack)(void *,int ,char ** ,char ** );//������ʾ���Ļص�
typedef int (*pSql_CountCallBack)(void *,int ,char **,char ** );//���ɼ�����Ŀ�Ļص�
int CountPage(int iTotal,int iShowNum);//����ҳ���ĺ���

class CInfoForm:public CForm
{
public:
	CInfoForm(CComponent *owner,int iStartY,int iStartX,int iHeight,int iWidth);
	int KeyListener();
	void Flash();
	CComponent *pInfoLab;
	//������
	int iTotal;
	int iPage;
	char *GetInfo();
	char sSql[1024];
	char sSqlCount[1024];
	char *GetSql(char *sql);  //��ȡlimit֮ǰ�����
	pSql_CallBack  Show_CallBack;
	pSql_CountCallBack Count_CallBack;
protected:
private:

};
 


#endif