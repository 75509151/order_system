#include "CUsr_DB.h"
#include "CInfoForm.h"
#include "CLable.h"
#include <stdlib.h>
/////////////////////////*****************����һˢ������***************/
/*int BtnSearch_CallBack(void *canshu,int iColumn,char ** colValue,char **colName )
{
	CInfoForm  *pInForm=(CInfoForm *)canshu;
	pCurLable->SetContent(colValue[0]);
	pInForm->pCurNode=pInForm->pCurNode->pNext;
	printw("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
}*/


/************************������������new���Ʋ˵�*****************/
int BtnSearch_CallBack(void *canshu,int iColumn,char ** colValue,char **colName )
{
	CInfoForm  *pInForm=(CInfoForm *)canshu;
	char sInfo[250]={0};
	sprintf(sInfo,"%-8s%-8s%-8s%-8s",colValue[0],colValue[1],colValue[3],colValue[4],colValue[5]);

	CLable *pCom=new CLable(pInForm,pInForm->list_Head->iLen*3,0,3,40,sInfo,false,true);
	List_AddT(pInForm->list_Head,pCom);
	return 0;
}

int BtnSearch_CountCallBack(void *canshu,int iColumn,char ** colValue,char **colName )
{
	CInfoForm  *pInForm=(CInfoForm *)canshu;
	pInForm->iTotal=atoi(colValue[0]);  //����ܵ�����
	//pInForm->iPage=0;					//���õ�ǰҳ��Ϊ0
	return 0;
}
/******************************************
		������id
*******************************************/
int User_MaxIdCallBack(void *canshu,int iColumn,char ** colValue,char **colName )
{
	char *acMaxId=(char *)canshu;
	strcpy(acMaxId,colValue[0]);
	return 0;
}

/***************************************
			����û���Ϣ
*****************************************/
int CUser_InfoCallBack(void *canshu,int iColumn,char ** colValue,char **colName )
{
	char (*SUsrInfo)[20]=(char (*)[20])canshu;
	strcpy(SUsrInfo[0],colValue[0]);
	strcpy(SUsrInfo[1],colValue[1]);
	strcpy(SUsrInfo[2],colValue[2]);
	strcpy(SUsrInfo[3],colValue[3]);
	strcpy(SUsrInfo[4],colValue[4]);
	strcpy(SUsrInfo[5],colValue[5]);
	return 0;
}

int CheckAccount_Callback(void *canshu,int iColumn,char ** colValue,char **colName )
{
	bool *account_flag=(bool *)canshu;
	(*account_flag)=true;
	return 0;
}

int RoleId_CallBack(void *canshu,int iColumn,char ** colValue,char **colName )
{
	char *p=(char *)canshu;
	strcpy(p,colValue[0]);
	return 0;
}