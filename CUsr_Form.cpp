#include "CUsr_Form.h"

#include "CUsr_Ac.h"
#include "CButton.h"
#include "CLable.h"
#include "CEdit.h"
#include "CComponent.h"
#include "LoginAction.h"
#include "CInfoForm.h"
#include "CComobox.h"
#include "CSinDB.h"
#include "stdlib.h"
#include "CUsr_DB.h"
#include "CPermissLable.h"
CUsr_Form::CUsr_Form(CComponent *owner):CForm(owner,0,0,20,80)
{
	CComponent *pCom=NULL;
	CCombox *pCombox=NULL;
	CComponent *pChild=NULL;
	CActionListener *pAction=NULL;
	//将各个空间添加到loginfrom
	pCom=new CLable(this,0,0,3,10,"帐号",true);
	List_AddT(this->list_Head,pCom);
	
	pCom=new CEdit(this,0,10,3,20,false,10);
	List_AddT(this->list_Head,pCom);
	acAccount=((CEdit *)pCom)->GetContent();		//帐号

	pCom=new CLable(this,0,30,3,10,"用户名",true);	
	List_AddT(this->list_Head,pCom);
	
	pCom=new CEdit(this,0,40,3,15,false,10);
	List_AddT(this->list_Head,pCom);
	acName=((CEdit *)pCom)->GetContent();		//用户名


	pCom=new CButton(this,0,60,3,10,"查询");
	List_AddT(this->list_Head,pCom);
	pCom->AddKeyActionListener(new CUsr_SearAC(pCom));//添加事件
	

	pCom=new CButton(this,4,65,3,10,"增加");
  	pCom->AddKeyActionListener(new CUsr_AddAC(this));//添加事件
	 List_AddT(this->list_Head,pCom);

	 pCom=new CButton(this,8,65,3,10,"删除");
	 List_AddT(this->list_Head,pCom);	
	 pCom->AddKeyActionListener(new CUsr_DelAC(this));//为删除事件


	 pCom=new CButton(this,12,65,3,10,"修改");
	 List_AddT(this->list_Head,pCom);
	 pCom->AddKeyActionListener(new CUsr_UpdateAC(this));//修改事件

	/********************下拉菜单********************************/
// 	pCombox=new CCombox(this,5,45,3,20);
// 	 List_AddT(this->list_Head,pCombox);  	
// 
// 	 	pChild=new CLable(this,pCombox->iStartY+2,pCombox->iStartX,2,20,"系统管理员",false,true);
// 	 	List_AddT(pCombox->list_Head,pChild);
// 		pChild=new CLable(this,pCombox->iStartY+4,pCombox->iStartX,2,20,"游客",false,true);
// 		List_AddT(pCombox->list_Head,pChild);
// 	 	pChild=new CLable(this,pCombox->iStartY+6,pCombox->iStartX,2,20,"呵呵哈",false,true);
// 	  	List_AddT(pCombox->list_Head,pChild);
	 

	 pCom=new CButton(this,16,65,3,10,"权限");
	 List_AddT(this->list_Head,pCom);
	 pCom->AddKeyActionListener(new CUsr_PermissAC(this));//修改事件
	


	 pInfoForm=new CInfoForm(this,5,0,15,40);//pFor直接指向这个位置。
	 List_AddT(this->list_Head,pInfoForm);
	 
}

int CUsr_Form::KeyListener()
{
	int iKey;
	//遍历到可以接收按钮的第一个
	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)list_Head->pHead;
	CComponent *pCCom=(CComponent *)currNode->pData;

	/////////////注意判断所有都无获取焦点，陷入死循环状况///////////////
	while (pCCom->IsFocus()!=true)
	{
		currNode=currNode->pNext;
		pCCom=(CComponent *)currNode->pData;
	}
	//	keypad(pCCom->GetHandler(),TRUE);
	
	//根据不同的按键进行动作
	while (1)
	{
		if (true==this->isExit)
		{
			return EXITFLAG;
		}
		wmove(pCCom->GetHandler(),1,1);
		wrefresh(pCCom->GetHandler());
		keypad(pCCom->GetHandler(),TRUE);
		//获取焦点
		pCCom->GetFocus();
		//iKey=wgetch(pCCom->GetHandler());
		iKey=pCCom->KeyListener();
		pCCom->LoseFocus();//失去
		//	pCCom->LoseFocus();
		//this->Show();
	//	wrefresh(pHandler);
		
		switch(iKey)
		{
		case KEY_LEFT:
			{
				
				wrefresh(pCCom->GetHandler());
				currNode=currNode->pPre;
				pCCom=(CComponent *)currNode->pData;
				while (pCCom->IsFocus()!=true)
				{
					
					currNode=currNode->pPre;
					pCCom=(CComponent *)currNode->pData;
				}
				
				break;
			}
		case KEY_RIGHT:
			{
			//	pCCom->LoseFocus();
				wrefresh(pCCom->GetHandler());
				currNode=currNode->pNext;
				pCCom=(CComponent *)currNode->pData;
				while (pCCom->IsFocus()!=true)
				{
					currNode=currNode->pNext;
					pCCom=(CComponent *)currNode->pData;
				}
				
				break;
			}

		case KEY_UP:
				pInfoForm->KeyListener();
			break;
		case KEY_DOWN:
				pInfoForm->KeyListener();
			break;
		default:
			
			break;
			
		}
		
	}
	return 0;
}

char *CUsr_Form::GetName()
{
	return acName;
}
char *CUsr_Form::GetAccount()
{
	return acAccount;
}

/****************************************************
				用户添加窗口
****************************************************/
CUsr_AddForm::CUsr_AddForm(CComponent *owner):CForm(owner,0,0,20,80)
{
	CComponent *pCom=NULL;
	CActionListener *pAction=NULL;
	CCombox *pCombox=NULL;
	CComponent *pChild=NULL;
	char sUserId[10]={0};
	
	
	pCom=new CLable(this,0,10,3,40,"*当前位置：用户添加界面*",false);
	List_AddT(this->list_Head,pCom);

	//第一行
	pCom=new CLable(this,4,2,3,10,"用户ID",true);
	List_AddT(this->list_Head,pCom);

	pCom=new CLable(this,4,13,3,15,"",true);
	List_AddT(this->list_Head,pCom);
	strcpy(sUserId,	User_GetMaxId());
	sprintf(sUserId,"%d",atoi(sUserId)+1);//在最大id上加一
	((CLable *)pCom)->SetContent(sUserId);
	acId=((CLable *)pCom)->GetContent();		//获取id
	
	pCom=new CLable(this,4,33,3,10,"所属部门",true);	
	List_AddT(this->list_Head,pCom);	
	
	pCombox=new CCombox(this,4,44,3,20,"办公室");
	List_AddT(this->list_Head,pCombox); 

	acDepartment=((CCombox *)pCombox)->GetContent();//获取部门
	
	/************下拉框************************/
	pChild=new CLable(this,pCombox->iStartY+3,pCombox->iStartX,2,20,"办公室",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+5,pCombox->iStartX,2,20,"技术部",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+7,pCombox->iStartX,2,20,"人力部",false,true);
	List_AddT(pCombox->list_Head,pChild);

//第二行

	pCom=new CLable(this,8,2,3,10,"账号",true);	
	List_AddT(this->list_Head,pCom);
	pCom=new CEdit(this,8,13,3,15,false,10);
	List_AddT(this->list_Head,pCom);
	acAccount=((CEdit *)pCom)->GetContent();//获取帐号

	pCom=new CLable(this,8,33,3,10,"用户身份",true);	
	List_AddT(this->list_Head,pCom);
	
	pCombox=new CCombox(this,8,44,3,20,"系统管理员");
	List_AddT(this->list_Head,pCombox); 
	acType=((CCombox *)pCombox)->GetContent();		//用户类型
	//acRole=							//获取身份	
	
	//第三行
	pCom=new CLable(this,12,2,3,10,"姓名",true);	
	List_AddT(this->list_Head,pCom);
	pCom=new CEdit(this,12,13,3,15,false,10);
	List_AddT(this->list_Head,pCom);
	acName=((CEdit *)pCom)->GetContent();//获取姓名

	pCom=new CLable(this,12,33,3,10,"密码：",true);	
	List_AddT(this->list_Head,pCom);
	
	pCom=new CEdit(this,12,44,3,15,true,10);
	List_AddT(this->list_Head,pCom);
	acPsw=((CEdit *)pCom)->GetContent();	//获取密码

	//第四行
	pCom=new CLable(this,16,2,3,10,"备注",true);	
	List_AddT(this->list_Head,pCom);
	pCom=new CEdit(this,16,13,3,15,false,10);
	List_AddT(this->list_Head,pCom);
	acBeizhu=((CEdit *)pCom)->GetContent();//获取备注

	pCom=new CLable(this,16,33,3,10,"确认密码",true);	
	List_AddT(this->list_Head,pCom);
	
	pCom=new CEdit(this,16,44,3,15,true,10);
	List_AddT(this->list_Head,pCom);
	acPswCheck=((CEdit *)pCom)->GetContent();	//确认密码
	
	// 	pCom=new CLable(this,8,0,3,10,"用户身份",true);	
	// 	List_AddT(this->list_Head,pCom);
	/********************下拉菜单********************************/
	
		pChild=new CLable(this,pCombox->iStartY+3,pCombox->iStartX,2,20,"系统管理员",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+5,pCombox->iStartX,2,20,"业务管理员",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+7,pCombox->iStartX,2,20,"操作员",false,true);
	List_AddT(pCombox->list_Head,pChild);
	
	
	pCom=new CButton(this,12,65,3,10,"确定");
	List_AddT(this->list_Head,pCom);		 
	 pCom->AddKeyActionListener(new CUsr_AddOKAC(this));//添加事件
	pCom=new CButton(this,16,65,3,10,"返回");
	 List_AddT(this->list_Head,pCom);
	  pCom->AddKeyActionListener(new CBackAC(this));//返回事件
		 
}

/************************************************
				用户修改界面
				char *acId;			//ID
				char *acDepartment;//部门
				char *acAccount;	//帐号
				char *acRole;		//角色
				char *acName;		//姓名
				char *acPsw;		//密码
				char *acBeizhu;		//备注 
**************************************************/
CUsr_UpdateForm::CUsr_UpdateForm(CComponent *owner):CForm(owner,0,0,20,80)
{
	CComponent *pCom=NULL;
	CActionListener *pAction=NULL;
	CCombox *pCombox=NULL;
	CComponent *pChild=NULL;

	char sUser[6][20]={0};

	CInfoForm * pInfoForm= (CInfoForm *)((CUsr_Form *)(owner))->pInfoForm;//获取到信息框
	char *sInfo=pInfoForm->GetInfo();//获取信息栏获得的信息
	CSinDB *pDB=CSinDB::GetSinDB();
	int iInfo;
	
	char sSql[1024]={0};

	char sUser_id[10]={0};//id
	iInfo=atoi(sInfo);
	sprintf(sUser_id,"%d",iInfo);		//这个非常叼
	sprintf(sSql,"select  * from user_info  where user_id = \"%s\" ",sUser_id);
	pDB->DoOpera(sSql,CUser_InfoCallBack,sUser);

	pCom=new CLable(this,0,10,3,40,"*当前位置：用户修改界面*",false);
	List_AddT(this->list_Head,pCom);
	
	//第一行
	pCom=new CLable(this,4,2,3,10,"用户ID",true);
	List_AddT(this->list_Head,pCom);
	
	pCom=new CLable(this,4,13,3,15,"",true);
	List_AddT(this->list_Head,pCom);
	((CLable *)pCom)->SetContent(sUser[0]);  
	acId=((CLable *)pCom)->GetContent();		//获取id
	
	pCom=new CLable(this,4,33,3,10,"所属部门",true);	
	List_AddT(this->list_Head,pCom);	
	


	pCombox=new CCombox(this,4,44,3,20,"办公室");
	List_AddT(this->list_Head,pCombox); 

	acDepartment=((CCombox *)pCombox)->GetContent();//获取部门
	
	/************下拉框************************/
	pChild=new CLable(this,pCombox->iStartY+3,pCombox->iStartX,2,20,"办公室",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+5,pCombox->iStartX,2,20,"技术部",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+7,pCombox->iStartX,2,20,"人力部",false,true);
	List_AddT(pCombox->list_Head,pChild);

	//第二行
	
	pCom=new CLable(this,8,2,3,10,"账号",true);	
	List_AddT(this->list_Head,pCom);
	pCom=new CEdit(this,8,13,3,15,false,10);
	List_AddT(this->list_Head,pCom);
	((CLable *)pCom)->SetContent(sUser[3]);

	acAccount=((CEdit *)pCom)->GetContent();//获取帐号
	
	pCom=new CLable(this,8,33,3,10,"用户身份",true);	
	List_AddT(this->list_Head,pCom);
	
	pCombox=new CCombox(this,8,44,3,20,"系统管理员");
	List_AddT(this->list_Head,pCombox); 
	acType=((CCombox *)pCombox)->GetContent();
	//acRole=							//获取身份	
	
	//第三行
	pCom=new CLable(this,12,2,3,10,"姓名",true);	
	List_AddT(this->list_Head,pCom);
	pCom=new CEdit(this,12,13,3,15,false,10);
	List_AddT(this->list_Head,pCom);
	((CEdit *)pCom)->SetContent(sUser[1]);
	acName=((CEdit *)pCom)->GetContent();//获取姓名
	
	pCom=new CLable(this,12,33,3,10,"密码：",true);	
	List_AddT(this->list_Head,pCom);
	
	pCom=new CEdit(this,12,44,3,15,true,10);
	List_AddT(this->list_Head,pCom);
	acPsw=((CEdit *)pCom)->GetContent();	//获取密码
	
	//第四行
	pCom=new CLable(this,16,2,3,10,"备注",true);	
	List_AddT(this->list_Head,pCom);
	pCom=new CEdit(this,16,13,3,15,false,10);
	List_AddT(this->list_Head,pCom);
		((CEdit *)pCom)->SetContent(sUser[5]);
	acBeizhu=((CEdit *)pCom)->GetContent();//获取备注
	
	pCom=new CLable(this,16,33,3,10,"确认密码",true);	
	List_AddT(this->list_Head,pCom);
	
	pCom=new CEdit(this,16,44,3,15,true,10);
	List_AddT(this->list_Head,pCom);
	acPsw=((CEdit *)pCom)->GetContent();	//确认密码
	
	// 	pCom=new CLable(this,8,0,3,10,"用户身份",true);	
	// 	List_AddT(this->list_Head,pCom);
	/********************下拉菜单********************************/
	
	
	pChild=new CLable(this,pCombox->iStartY+3,pCombox->iStartX,2,20,"系统管理员",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+5,pCombox->iStartX,2,20,"普通职工",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+7,pCombox->iStartX,2,20,"经理",false,true);
	List_AddT(pCombox->list_Head,pChild);
	
	
	
	pCom=new CButton(this,12,65,3,10,"确定");
	List_AddT(this->list_Head,pCom);		 
	pCom->AddKeyActionListener(new CUsr_UpdateOKAC(this));//添加事件
	pCom=new CButton(this,16,65,3,10,"返回");
	List_AddT(this->list_Head,pCom);
	pCom->AddKeyActionListener(new CBackAC(this));//返回事件
		 
		 
}


/****************************************
				权限设置界面
****************************************/
CUsr_PermissForm::CUsr_PermissForm(CComponent *owner):CForm(owner,0,0,20,80)
{	
	CComponent *pCom=NULL;
	CActionListener *pAction=NULL;
	CCombox *pCombox=NULL;
	CComponent *pChild=NULL;
	CPermissLable *pPerLable=NULL;
	char sUser[6][20]={0};
	char sUser_id[10]={0};//id
	CInfoForm * pInfoForm= (CInfoForm *)((CUsr_Form *)(owner))->pInfoForm;//获取到信息框
	char *sInfo=pInfoForm->GetInfo();//获取信息栏获得的信息
	CSinDB *pDB=CSinDB::GetSinDB();
	int iInfo;
	
	char sSql[1024]={0};
	
	iInfo=atoi(sInfo);
	sprintf(sUser_id,"%d",iInfo);		//这个非常叼
	sprintf(sSql,"select  * from user_info  where user_id = \"%s\" ",sUser_id);
	pDB->DoOpera(sSql,CUser_InfoCallBack,sUser);
	
	pCom=new CLable(this,0,10,3,40,"*当前位置：权限设置界面*",false);
	List_AddT(this->list_Head,pCom);
	
	//第一行
	pCom=new CLable(this,4,2,2,10,"用户名",true);
	List_AddT(this->list_Head,pCom);
	
	pCom=new CLable(this,4,13,2,15,"",true);
	List_AddT(this->list_Head,pCom);
	((CLable *)pCom)->SetContent(sUser[1]);  
	
	
	pCom=new CLable(this,7,2,2,10,"帐号",true);
	List_AddT(this->list_Head,pCom);
	
	pCom=new CLable(this,7,13,2,15,"",true);
	List_AddT(this->list_Head,pCom);
	((CLable *)pCom)->SetContent(sUser[3]);


	
	pCom=new CLable(this,4,33,2,10,"用户身份",true);
	List_AddT(this->list_Head,pCom);
	

	pCombox=new CCombox(this,4,44,2,20,"系统管理员");
	List_AddT(this->list_Head,pCombox); 
	acRole=((CCombox *)pCombox)->GetContent();
	

	pPerLable=new CPermissLable(this,9,2,11,60,true);
	List_AddT(this->list_Head,pPerLable); 
	pPerLable->whatshow=((CCombox *)pCombox)->GetContent();
	
	
	//acRole=//获取身份	
	
	/********************下拉菜单********************************/
	
	
	pChild=new CLable(this,pCombox->iStartY+2,pCombox->iStartX,2,20,"系统管理员",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+4,pCombox->iStartX,2,20,"业务管理员",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+6,pCombox->iStartX,2,20,"操作员",false,true);
	List_AddT(pCombox->list_Head,pChild);


	
	pCom=new CButton(this,12,65,3,10,"确定");
	List_AddT(this->list_Head,pCom);
	pCom->AddKeyActionListener(new CUsr_UpdateOKAC(this));//添加事件
	pCom=new CButton(this,16,65,3,10,"返回");
	List_AddT(this->list_Head,pCom);
	pCom->AddKeyActionListener(new CBackAC(this));//返回事件
	
}


// 
// int CUsr_PermissForm::KeyListener()
// {
// 	int iKey;
// 	//遍历到可以接收按钮的第一个
// 	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)list_Head->pHead;
// 	CComponent *pCCom=(CComponent *)currNode->pData;
// 	
// 	/////////////注意判断所有都无获取焦点，陷入死循环状况///////////////
// 	while (pCCom->IsFocus()!=true)
// 	{
// 		currNode=currNode->pNext;
// 		pCCom=(CComponent *)currNode->pData;
// 	}
// 	//	keypad(pCCom->GetHandler(),TRUE);
// 	
// 	//根据不同的按键进行动作
// 	while (1)
// 	{
// 		if (true==isExit)
// 		{
// 			return EXITFLAG;		//退出
// 		}
// 		wmove(pCCom->GetHandler(),1,1);
// 		wrefresh(pCCom->GetHandler());
// 		keypad(pCCom->GetHandler(),TRUE);
// 		
// 		//获取焦点
// 		pCCom->GetFocus();
// 		iKey=pCCom->KeyListener();
// 		PermissShow(acRole);/////////////////调用显示/////////////////////////////////////////////////////////
// 		//	this->Show();要不要
// 		wrefresh(pHandler);
// 		pCCom->LoseFocus();
// 		
// 		wrefresh(pCCom->GetHandler());	
// 		
// 		switch(iKey)
// 		{
// 		case KEY_UP:
// 			{
// 				currNode=currNode->pPre;
// 				pCCom=(CComponent *)currNode->pData;
// 				while (pCCom->IsFocus()!=true)
// 				{
// 					
// 					currNode=currNode->pPre;
// 					pCCom=(CComponent *)currNode->pData;
// 				}
// 				
// 				break;
// 			}
// 		case KEY_DOWN:
// 			{
// 				currNode=currNode->pNext;
// 				pCCom=(CComponent *)currNode->pData;
// 				while (pCCom->IsFocus()!=true)
// 				{
// 					currNode=currNode->pNext;
// 					pCCom=(CComponent *)currNode->pData;
// 				}
// 				
// 				break;
// 			}
// 			
// 			
// 		default:
// 			
// 			break;
// 			
// 		}
// 		
// 	}
// 	return 0;
// }


// void CUsr_PermissForm::PermissShow(char *cpRoleName)
// {
// 	char sRole_ID[10]={0};
// 	char sql[1024] = {0};
// 	//char *RoleName = NULL;
// 	CSinDB *pDbSingle = NULL;
// 	//RoleName=new char[strlen(cpRoleName)+1];
// 	//strcpy(RoleName,cpRoleName);
// 	
// 	//打开数据库获取角色ID
// 	pDbSingle = CSinDB::GetSinDB();	
// 	sprintf(sql,"select role_id from role_info where role_name='%s'",cpRoleName);
// 
// 	pDbSingle->DoOpera(sql,RoleId_CallBack,sRole_ID);
// 	wbkgd(this->GetHandler(),COLOR_PAIR(2));
// 	wrefresh(this->GetHandler());
// 	wclear(this->GetHandler());
// 	
// 	if (0==strcmp(sRole_ID,"1001"))//系统管理员权限
// 	{	
// 		mvwprintw(this->GetHandler(),0,8,"[*]系统管理");
// 		mvwprintw(this->GetHandler(),1,10,"-[*]组织机构管理");
// 		mvwprintw(this->GetHandler(),2,10,"-[*]用户管理");
// 		mvwprintw(this->GetHandler(),3,10,"-[*]系统参数设置");
// 		
// 		mvwprintw(this->GetHandler(),6,8,"[*]客户端管理");
// 		mvwprintw(this->GetHandler(),7,10,"-[*]客户端用户管理");
// 		mvwprintw(this->GetHandler(),8,10,"-[*]用户点播管理");
// 		
// 		mvwprintw(this->GetHandler(),0,33,"[*]视频管理");
// 		mvwprintw(this->GetHandler(),1,35,"-[*]频道信息管理");
// 		mvwprintw(this->GetHandler(),2,35,"-[*]分类信息管理");
// 		mvwprintw(this->GetHandler(),3,35,"-[*]地区信息管理");
// 		mvwprintw(this->GetHandler(),4,35,"-[*]视频信息管理");
// 		
// 		mvwprintw(this->GetHandler(),6,33,"[*]报表统计");
// 		mvwprintw(this->GetHandler(),7,35,"-[*]点播报表");				
// 	}
// 	else if (0==strcmp(sRole_ID,"1002"))//业务管理员权限
// 	{	
// 		mvwprintw(this->GetHandler(),0,8,"[*]系统管理");
// 		mvwprintw(this->GetHandler(),1,10,"-[ ]组织机构管理");
// 		mvwprintw(this->GetHandler(),2,10,"-[ ]用户管理");
// 		mvwprintw(this->GetHandler(),3,10,"-[ ]系统参数设置");
// 		
// 		mvwprintw(this->GetHandler(),6,8,"[*]客户端管理");
// 		mvwprintw(this->GetHandler(),7,10,"-[*]客户端用户管理");
// 		mvwprintw(this->GetHandler(),8,10,"-[*]用户点播管理");
// 		
// 		mvwprintw(this->GetHandler(),0,33,"[*]视频管理");
// 		mvwprintw(this->GetHandler(),1,35,"-[*]频道信息管理");
// 		mvwprintw(this->GetHandler(),2,35,"-[*]分类信息管理");
// 		mvwprintw(this->GetHandler(),3,35,"-[*]地区信息管理");
// 		mvwprintw(this->GetHandler(),4,35,"-[*]视频信息管理");
// 		
// 		mvwprintw(this->GetHandler(),6,33,"[*]报表统计");
// 		mvwprintw(this->GetHandler(),7,35,"-[*]点播报表");	
// 	}	
// 		
// 		if (0==strcmp(sRole_ID,"1003"))//操作员权限
// 		{					
// 			mvwprintw(this->GetHandler(),0,8,"[*]系统管理");
// 			mvwprintw(this->GetHandler(),1,10,"-[ ]组织机构管理");
// 			mvwprintw(this->GetHandler(),2,10,"-[ ]用户管理");
// 			mvwprintw(this->GetHandler(),3,10,"-[ ]系统参数设置");
// 			
// 			mvwprintw(this->GetHandler(),6,8,"[*]客户端管理");
// 			mvwprintw(this->GetHandler(),7,10,"-[ ]客户端用户管理");
// 			mvwprintw(this->GetHandler(),8,10,"-[ ]用户点播管理");
// 			
// 			mvwprintw(this->GetHandler(),0,33,"[ ]视频管理");
// 			mvwprintw(this->GetHandler(),1,35,"-[ ]频道信息管理");
// 			mvwprintw(this->GetHandler(),2,35,"-[ ]分类信息管理");
// 			mvwprintw(this->GetHandler(),3,35,"-[ ]地区信息管理");
// 			mvwprintw(this->GetHandler(),4,35,"-[ ]视频信息管理");
// 			
// 			mvwprintw(this->GetHandler(),6,33,"[*]报表统计");
// 			mvwprintw(this->GetHandler(),7,35,"-[*]点播报表");	
// 			
// 		}			
//    	wrefresh(this->GetHandler());
// }



char *User_GetMaxId()
{
	CSinDB *pDB=CSinDB::GetSinDB();
	char sSql[1024]={0};
	char sUserId[10]={0};
	sprintf(sSql,"select max(user_id) from user_info");
	pDB->DoOpera(sSql,User_MaxIdCallBack,sUserId);
	return sUserId;
	
}