#include "CUsr_Ac.h"
#include "LoginAction.h"
#include "CSinDB.h"
#include "CLoginForm.h"
#include "CMenu.h"
#include "CLoginDB.h"
#include "CUsr_Form.h"
#include "CUsr_DB.h"
#include "CInfoForm.h"
#include "stdlib.h"
#include "CLable.h"
/************************************************************
                  ��ѯ�¼�
********************************************************/
CUsr_SearAC::CUsr_SearAC(CComponent *owner):CActionListener(owner)
{

}
void CUsr_SearAC::DoAction()
{
	//��ȡ�༭�������
	CUsr_Form *pUsrForm=(CUsr_Form *)(owner->cOwner);
	CInfoForm *pInfoForm= (CInfoForm *)pUsrForm->pInfoForm;
	pInfoForm->iPage=0;
	char *acName=pUsrForm->GetName();
	char *acAccount=pUsrForm->GetAccount();
	pInfoForm->pInfoLab=NULL;
	//�ݻ�����ԭ�е�����
	char sSql[1024]={0};
	//��ȡ���ݵ���
	CSinDB *pDB=CSinDB::GetSinDB();
	int iPage=0;

	sprintf(sSql,"select count(user_id) from user_info  where user_name like \"%%%s%\" 	and user_account like\"%%%s%\" and user_state='1'  ",acName,acAccount);
	pInfoForm->Show_CallBack=BtnSearch_CallBack;//Ϊ��Ϣ����ĺ���ָ�븳ֵ
	
	strcpy(pInfoForm->sSqlCount,sSql);
	pDB->DoOpera(sSql,BtnSearch_CountCallBack,pInfoForm);
	pInfoForm->Count_CallBack=BtnSearch_CountCallBack;  //Ϊ��Ϣ����ĺ���ָ�븳ֵ

	sprintf(sSql,"select  * from user_info  where user_name like \"%%%s%\" and user_account like\"%%%s%\" and user_state='1' limit 5 offset     %d ",acName,acAccount,0);
	strcpy(pInfoForm->sSql,sSql);

	pInfoForm->Flash();
	List_Free(pInfoForm->list_Head);
	pDB->DoOpera(sSql,BtnSearch_CallBack,pInfoForm);//����Ϣ���崫��
	
	
	
	pInfoForm->Show();
	
}

/************************************************************
                  �޸�
********************************************************/
CUsr_UpdateAC::CUsr_UpdateAC(CComponent *owner):CActionListener(owner)
{

}
void CUsr_UpdateAC::DoAction()
{
	//��ȡ�༭�������
	CInfoForm * pInfoForm= (CInfoForm *)((CUsr_Form *)(owner))->pInfoForm;//��ȡ����Ϣ��
	
	char *sInfo=pInfoForm->GetInfo();//��ȡ��Ϣ����õ���Ϣ
	int iInfo=0;
	//�����ǩ���������
	if (NULL==sInfo)
	{
		//��ʾû��ѡ������
		printf("û�б�ѡ�е�");
		return;
	}
	else
	{
		//�����޸Ĵ���
		CUsr_UpdateForm *pUsrAddForm= new CUsr_UpdateForm(owner);
		pUsrAddForm->Show();
		pUsrAddForm->KeyListener();	
	}

}


/**************************************************
				����¼�
**************************************************/
CUsr_AddAC::CUsr_AddAC(CComponent *owner):CActionListener(owner)
{

}

void CUsr_AddAC::DoAction()
{
	//�������Ա���Ĵ���
	CUsr_AddForm *pUsrAddForm= new CUsr_AddForm(owner);
	pUsrAddForm->Show();
	pUsrAddForm->KeyListener();
}

/**************************************************
				ɾ���¼�


**************************************************/
CUsr_DelAC::CUsr_DelAC(CComponent *owner):CActionListener(owner)
{

}

void CUsr_DelAC::DoAction()
{
	CUsr_Form *pUsrForm=(CUsr_Form *)(owner);
	CInfoForm *pInfoForm= (CInfoForm *)pUsrForm->pInfoForm;
	char *sInfo=pInfoForm->GetInfo();//��ȡ��Ϣ����õ���Ϣ

	char *acName=pUsrForm->GetName();
	char *acAccount=pUsrForm->GetAccount();
	pInfoForm->pInfoLab=NULL;


	int iInfo=0;

	if (NULL==sInfo)
	{
		//��ʾû��ѡ������
		printf("��ѡ��Ա��");
		return;
	}
	else
	{
		//�����޸Ĵ���
		
		char sSql[1024]={0};
		//��ȡ���ݵ���
		CSinDB *pDB=CSinDB::GetSinDB();
		iInfo=atoi(sInfo);
		sprintf(sInfo,"%d",iInfo);		//����ǳ���
		sprintf(sSql,"update user_info set user_state='0' where user_id=\"%s\" ",sInfo);
		pDB->DoOpera(sSql,NULL,NULL);//ִ��

		//sprintf(sSql,"select  * from user_info  limit 5 offset 3 ",sInfo);
		//	printf("%d",atoi(sSql));   //����atoiֻ�ǽ�ǰ�漸����ȡ�����֣������ַ����ܣ������Ҳ����

		pInfoForm->Flash();//ˢ����Ϣ����
		List_Free(pInfoForm->list_Head);
		sprintf(sSql,"select count(user_id) from user_info  where user_name like \"%%%s%\" 	and user_account like\"%%%s%\" and user_state='1'  ",acName,acAccount);
		strcpy(pInfoForm->sSqlCount,sSql);
	    pDB->DoOpera(sSql,BtnSearch_CountCallBack,pInfoForm);
		sprintf(sSql,"select  * from user_info  where user_name like \"%%%s%\" and user_account like\"%%%s%\" and user_state='1' limit 5 offset %d ",acName,acAccount,(pInfoForm->iPage)*5);
		strcpy(pInfoForm->sSql,sSql);
		pDB->DoOpera(sSql,BtnSearch_CallBack,pInfoForm);//����Ϣ���崫��
		pInfoForm->Show();
		pInfoForm->pInfoLab=NULL;
	}

}

/**************************************************
				Ȩ���¼�
**************************************************/
CUsr_PermissAC::CUsr_PermissAC(CComponent *owner):CActionListener(owner)
{

}

void CUsr_PermissAC::DoAction()
{

	//��ȡ�༭�������
	CInfoForm * pInfoForm= (CInfoForm *)((CUsr_Form *)(owner))->pInfoForm;//��ȡ����Ϣ��
	
	char *sInfo=pInfoForm->GetInfo();//��ȡ��Ϣ����õ���Ϣ
	int iInfo=0;
	//�����ǩ���������
	if (NULL==sInfo)
	{
		//��ʾû��ѡ������
		printf("û�б�ѡ�е�");
		return;
	}
	else
	{
		//�����޸Ĵ���
		CUsr_PermissForm *pUsrAddForm= new CUsr_PermissForm(owner);
		pUsrAddForm->Show();
		pUsrAddForm->KeyListener();
		pInfoForm->Show();
		pInfoForm->pInfoLab=NULL;
	}

	 

}
/**************************************************
				ȷ����Ӱ�ť�¼�
**************************************************/
CUsr_AddOKAC::CUsr_AddOKAC(CComponent *owner):CActionListener(owner)
{	

	
}
void CUsr_AddOKAC::DoAction()
{

	CUsr_AddForm *pForm=(CUsr_AddForm *)owner;
	CUsr_Form *pUsrForm=(CUsr_Form *)pForm->cOwner;
	CInfoForm *pInfoForm= (CInfoForm *)pUsrForm->pInfoForm;
	char *Name=pUsrForm->GetName();
	char *Account=pUsrForm->GetAccount();
	pInfoForm->pInfoLab=NULL;
	CSinDB *pDB=CSinDB::GetSinDB();
	char sSql[1024]={0};
	char *acId=pForm->acId;			//ID
	char *acDepartment=pForm->acDepartment;//����
	char *acAccount=pForm->acAccount;	//�ʺ�
	char *acRole=pForm->acRole;		//��ɫ
	char *acName=pForm->acName;		//����
	char *acPsw=pForm->acPsw;		//����
	char *acPswCheck=pForm->acPswCheck;		//����
	char *acBeizhu=pForm->acBeizhu;		//��ע
	bool acAccount_flag=false;
	char *acType=pForm->acType;
	int maxpage;
	//�ж��ʺ��Ƿ�Ψһ
	sprintf(sSql,"select * from user_info where user_account =\"%s\" ",acAccount);
	pDB->DoOpera(sSql,CheckAccount_Callback,&acAccount_flag);
	//�ж������Ƿ�һ��
	if ((0==strcmp(acPsw,acPswCheck))&&(0!=strlen(acPsw)))
	{	
		//�ж���Ϣ�Ƿ�Ϊ��
		if ((false==acAccount_flag)&&(0!=strlen(acAccount))&&(0!=strlen(acName)))
		{
		//���һ��sql���
			printf("%s",acType);
		sprintf(sSql,"insert into user_info values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",'1',\"%s\")",acId,acName,acPsw,acAccount,acDepartment,acBeizhu,acType);
		pDB->DoOpera(sSql,NULL,NULL);

		//ˢ�´���
		pInfoForm->Flash();//ˢ����Ϣ����
		List_Free(pInfoForm->list_Head);
		sprintf(sSql,"select count(user_id) from user_info  where user_state='1'  ");
		strcpy(pInfoForm->sSqlCount,sSql);
		
		pDB->DoOpera(sSql,BtnSearch_CountCallBack,pInfoForm);
		pInfoForm->Count_CallBack=BtnSearch_CountCallBack;  //Ϊ��Ϣ����ĺ���ָ�븳ֵ
		pInfoForm->iPage=CountPage(pInfoForm->iTotal,5);
		maxpage=(pInfoForm->iPage)*5;
		
		sprintf(sSql,"select  * from user_info  where user_state='1' limit 5 offset %d ",maxpage);
		strcpy(pInfoForm->sSql,sSql);
		pDB->DoOpera(sSql,BtnSearch_CallBack,pInfoForm);//����Ϣ���崫��
		pInfoForm->Show_CallBack=BtnSearch_CallBack;//Ϊ��Ϣ����ĺ���ָ�븳ֵ
		pForm->SetExit(true);
		pUsrForm->Show();
		pInfoForm->Show();
		pInfoForm->pInfoLab=NULL;
	
		}
		else
		{
		printf("�ʺ��Ѿ���ע�����Ϣδ��ȫ");
		}
	}
	else
	{
		printf("�������һ�¶��Ҳ���Ϊ��");
	}


}
/**************************************************
				�����¼�
**************************************************/
CBackAC::CBackAC(CComponent *owner):CActionListener(owner)
{
	
}
void CBackAC::DoAction()
{
	wclear(owner->GetHandler());
	CForm *pFrom=(CForm *)owner;
	pFrom->SetExit(true);
	owner->cOwner->Show();
	
}

/*******************************************
			ȷ���޸��¼�
*******************************************/
CUsr_UpdateOKAC::CUsr_UpdateOKAC(CComponent *owner):CActionListener(owner)
{

}

void CUsr_UpdateOKAC::DoAction()
{
	CUsr_UpdateForm *pForm=(CUsr_UpdateForm *)owner;
	CUsr_Form *pUsrForm=(CUsr_Form *)(owner->cOwner);
	CInfoForm *pInfoForm= (CInfoForm *)pUsrForm->pInfoForm;

	CSinDB *pDB=CSinDB::GetSinDB();
	char sSql[1024]={0};
	char *acId=pForm->acId;			//ID
	char *acDepartment=pForm->acDepartment;//����
	char *acAccount=pForm->acAccount;	//�ʺ�
	char *acRole=pForm->acRole;		//��ɫ
	char *acName=pForm->acName;		//����
	char *acPsw=pForm->acPsw;		//����
	char *acBeizhu=pForm->acBeizhu;		//��ע
	char *acType=pForm->acType;
	
	//���һ��sql���
	sprintf(sSql,"update user_info set user_name=\"%s\",user_psw=\"%s\",user_account=\"%s\",user_department=\"%s\",user_beizhu=\"%s\",user_type=\"%s\" where user_id=\"%s\" ",acName,acPsw,acAccount,acDepartment,acBeizhu,acType,acId);
	pDB->DoOpera(sSql,NULL,NULL);
	printf(pDB->GetErrmsg());
	sprintf(sSql,"%-8s%-8s%-8s%-8s%-8s",acId,acName,acAccount,acDepartment,acBeizhu);
	((CLable *)(pInfoForm->pInfoLab))->SetContent(sSql);
	pForm->SetExit(true);
	pUsrForm->Show();
	pInfoForm->Show();
	pInfoForm->pInfoLab=NULL;
}

/****************************************
		ȷ��Ȩ��ʱ��
***************************************/
// CUsr_PerOKAC::CUsr_PerOKAC(CComponent *owner)
// {
// 
// }
// 
// void CUsr_PerOKAC::DoAction()
// {
// 
// }