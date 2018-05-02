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
                  查询事件
********************************************************/
CUsr_SearAC::CUsr_SearAC(CComponent *owner):CActionListener(owner)
{

}
void CUsr_SearAC::DoAction()
{
	//获取编辑框的内容
	CUsr_Form *pUsrForm=(CUsr_Form *)(owner->cOwner);
	CInfoForm *pInfoForm= (CInfoForm *)pUsrForm->pInfoForm;
	pInfoForm->iPage=0;
	char *acName=pUsrForm->GetName();
	char *acAccount=pUsrForm->GetAccount();
	pInfoForm->pInfoLab=NULL;
	//摧毁里面原有的链表
	char sSql[1024]={0};
	//获取数据单例
	CSinDB *pDB=CSinDB::GetSinDB();
	int iPage=0;

	sprintf(sSql,"select count(user_id) from user_info  where user_name like \"%%%s%\" 	and user_account like\"%%%s%\" and user_state='1'  ",acName,acAccount);
	pInfoForm->Show_CallBack=BtnSearch_CallBack;//为信息窗体的函数指针赋值
	
	strcpy(pInfoForm->sSqlCount,sSql);
	pDB->DoOpera(sSql,BtnSearch_CountCallBack,pInfoForm);
	pInfoForm->Count_CallBack=BtnSearch_CountCallBack;  //为信息窗体的函数指针赋值

	sprintf(sSql,"select  * from user_info  where user_name like \"%%%s%\" and user_account like\"%%%s%\" and user_state='1' limit 5 offset     %d ",acName,acAccount,0);
	strcpy(pInfoForm->sSql,sSql);

	pInfoForm->Flash();
	List_Free(pInfoForm->list_Head);
	pDB->DoOpera(sSql,BtnSearch_CallBack,pInfoForm);//将信息窗体传入
	
	
	
	pInfoForm->Show();
	
}

/************************************************************
                  修改
********************************************************/
CUsr_UpdateAC::CUsr_UpdateAC(CComponent *owner):CActionListener(owner)
{

}
void CUsr_UpdateAC::DoAction()
{
	//获取编辑框的内容
	CInfoForm * pInfoForm= (CInfoForm *)((CUsr_Form *)(owner))->pInfoForm;//获取到信息框
	
	char *sInfo=pInfoForm->GetInfo();//获取信息栏获得的信息
	int iInfo=0;
	//处理标签里面的内容
	if (NULL==sInfo)
	{
		//提示没有选中内容
		printf("没有被选中的");
		return;
	}
	else
	{
		//跳出修改窗体
		CUsr_UpdateForm *pUsrAddForm= new CUsr_UpdateForm(owner);
		pUsrAddForm->Show();
		pUsrAddForm->KeyListener();	
	}

}


/**************************************************
				添加事件
**************************************************/
CUsr_AddAC::CUsr_AddAC(CComponent *owner):CActionListener(owner)
{

}

void CUsr_AddAC::DoAction()
{
	//跳出添加员工的窗体
	CUsr_AddForm *pUsrAddForm= new CUsr_AddForm(owner);
	pUsrAddForm->Show();
	pUsrAddForm->KeyListener();
}

/**************************************************
				删除事件


**************************************************/
CUsr_DelAC::CUsr_DelAC(CComponent *owner):CActionListener(owner)
{

}

void CUsr_DelAC::DoAction()
{
	CUsr_Form *pUsrForm=(CUsr_Form *)(owner);
	CInfoForm *pInfoForm= (CInfoForm *)pUsrForm->pInfoForm;
	char *sInfo=pInfoForm->GetInfo();//获取信息栏获得的信息

	char *acName=pUsrForm->GetName();
	char *acAccount=pUsrForm->GetAccount();
	pInfoForm->pInfoLab=NULL;


	int iInfo=0;

	if (NULL==sInfo)
	{
		//提示没有选中内容
		printf("请选择员工");
		return;
	}
	else
	{
		//跳出修改窗体
		
		char sSql[1024]={0};
		//获取数据单例
		CSinDB *pDB=CSinDB::GetSinDB();
		iInfo=atoi(sInfo);
		sprintf(sInfo,"%d",iInfo);		//这个非常叼
		sprintf(sSql,"update user_info set user_state='0' where user_id=\"%s\" ",sInfo);
		pDB->DoOpera(sSql,NULL,NULL);//执行

		//sprintf(sSql,"select  * from user_info  limit 5 offset 3 ",sInfo);
		//	printf("%d",atoi(sSql));   //发现atoi只是将前面几个截取成数字，其他字符不管，后面的也不管

		pInfoForm->Flash();//刷新信息窗体
		List_Free(pInfoForm->list_Head);
		sprintf(sSql,"select count(user_id) from user_info  where user_name like \"%%%s%\" 	and user_account like\"%%%s%\" and user_state='1'  ",acName,acAccount);
		strcpy(pInfoForm->sSqlCount,sSql);
	    pDB->DoOpera(sSql,BtnSearch_CountCallBack,pInfoForm);
		sprintf(sSql,"select  * from user_info  where user_name like \"%%%s%\" and user_account like\"%%%s%\" and user_state='1' limit 5 offset %d ",acName,acAccount,(pInfoForm->iPage)*5);
		strcpy(pInfoForm->sSql,sSql);
		pDB->DoOpera(sSql,BtnSearch_CallBack,pInfoForm);//将信息窗体传入
		pInfoForm->Show();
		pInfoForm->pInfoLab=NULL;
	}

}

/**************************************************
				权限事件
**************************************************/
CUsr_PermissAC::CUsr_PermissAC(CComponent *owner):CActionListener(owner)
{

}

void CUsr_PermissAC::DoAction()
{

	//获取编辑框的内容
	CInfoForm * pInfoForm= (CInfoForm *)((CUsr_Form *)(owner))->pInfoForm;//获取到信息框
	
	char *sInfo=pInfoForm->GetInfo();//获取信息栏获得的信息
	int iInfo=0;
	//处理标签里面的内容
	if (NULL==sInfo)
	{
		//提示没有选中内容
		printf("没有被选中的");
		return;
	}
	else
	{
		//跳出修改窗体
		CUsr_PermissForm *pUsrAddForm= new CUsr_PermissForm(owner);
		pUsrAddForm->Show();
		pUsrAddForm->KeyListener();
		pInfoForm->Show();
		pInfoForm->pInfoLab=NULL;
	}

	 

}
/**************************************************
				确定添加按钮事件
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
	char *acDepartment=pForm->acDepartment;//部门
	char *acAccount=pForm->acAccount;	//帐号
	char *acRole=pForm->acRole;		//角色
	char *acName=pForm->acName;		//姓名
	char *acPsw=pForm->acPsw;		//密码
	char *acPswCheck=pForm->acPswCheck;		//密码
	char *acBeizhu=pForm->acBeizhu;		//备注
	bool acAccount_flag=false;
	char *acType=pForm->acType;
	int maxpage;
	//判断帐号是否唯一
	sprintf(sSql,"select * from user_info where user_account =\"%s\" ",acAccount);
	pDB->DoOpera(sSql,CheckAccount_Callback,&acAccount_flag);
	//判断密码是否一致
	if ((0==strcmp(acPsw,acPswCheck))&&(0!=strlen(acPsw)))
	{	
		//判断信息是否为空
		if ((false==acAccount_flag)&&(0!=strlen(acAccount))&&(0!=strlen(acName)))
		{
		//组成一条sql语句
			printf("%s",acType);
		sprintf(sSql,"insert into user_info values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",'1',\"%s\")",acId,acName,acPsw,acAccount,acDepartment,acBeizhu,acType);
		pDB->DoOpera(sSql,NULL,NULL);

		//刷新窗体
		pInfoForm->Flash();//刷新信息窗体
		List_Free(pInfoForm->list_Head);
		sprintf(sSql,"select count(user_id) from user_info  where user_state='1'  ");
		strcpy(pInfoForm->sSqlCount,sSql);
		
		pDB->DoOpera(sSql,BtnSearch_CountCallBack,pInfoForm);
		pInfoForm->Count_CallBack=BtnSearch_CountCallBack;  //为信息窗体的函数指针赋值
		pInfoForm->iPage=CountPage(pInfoForm->iTotal,5);
		maxpage=(pInfoForm->iPage)*5;
		
		sprintf(sSql,"select  * from user_info  where user_state='1' limit 5 offset %d ",maxpage);
		strcpy(pInfoForm->sSql,sSql);
		pDB->DoOpera(sSql,BtnSearch_CallBack,pInfoForm);//将信息窗体传入
		pInfoForm->Show_CallBack=BtnSearch_CallBack;//为信息窗体的函数指针赋值
		pForm->SetExit(true);
		pUsrForm->Show();
		pInfoForm->Show();
		pInfoForm->pInfoLab=NULL;
	
		}
		else
		{
		printf("帐号已经被注册或信息未补全");
		}
	}
	else
	{
		printf("密码必须一致而且不能为空");
	}


}
/**************************************************
				返回事件
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
			确定修改事件
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
	char *acDepartment=pForm->acDepartment;//部门
	char *acAccount=pForm->acAccount;	//帐号
	char *acRole=pForm->acRole;		//角色
	char *acName=pForm->acName;		//姓名
	char *acPsw=pForm->acPsw;		//密码
	char *acBeizhu=pForm->acBeizhu;		//备注
	char *acType=pForm->acType;
	
	//组成一条sql语句
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
		确定权限时间
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