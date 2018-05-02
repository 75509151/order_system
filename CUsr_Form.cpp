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
	//�������ռ���ӵ�loginfrom
	pCom=new CLable(this,0,0,3,10,"�ʺ�",true);
	List_AddT(this->list_Head,pCom);
	
	pCom=new CEdit(this,0,10,3,20,false,10);
	List_AddT(this->list_Head,pCom);
	acAccount=((CEdit *)pCom)->GetContent();		//�ʺ�

	pCom=new CLable(this,0,30,3,10,"�û���",true);	
	List_AddT(this->list_Head,pCom);
	
	pCom=new CEdit(this,0,40,3,15,false,10);
	List_AddT(this->list_Head,pCom);
	acName=((CEdit *)pCom)->GetContent();		//�û���


	pCom=new CButton(this,0,60,3,10,"��ѯ");
	List_AddT(this->list_Head,pCom);
	pCom->AddKeyActionListener(new CUsr_SearAC(pCom));//����¼�
	

	pCom=new CButton(this,4,65,3,10,"����");
  	pCom->AddKeyActionListener(new CUsr_AddAC(this));//����¼�
	 List_AddT(this->list_Head,pCom);

	 pCom=new CButton(this,8,65,3,10,"ɾ��");
	 List_AddT(this->list_Head,pCom);	
	 pCom->AddKeyActionListener(new CUsr_DelAC(this));//Ϊɾ���¼�


	 pCom=new CButton(this,12,65,3,10,"�޸�");
	 List_AddT(this->list_Head,pCom);
	 pCom->AddKeyActionListener(new CUsr_UpdateAC(this));//�޸��¼�

	/********************�����˵�********************************/
// 	pCombox=new CCombox(this,5,45,3,20);
// 	 List_AddT(this->list_Head,pCombox);  	
// 
// 	 	pChild=new CLable(this,pCombox->iStartY+2,pCombox->iStartX,2,20,"ϵͳ����Ա",false,true);
// 	 	List_AddT(pCombox->list_Head,pChild);
// 		pChild=new CLable(this,pCombox->iStartY+4,pCombox->iStartX,2,20,"�ο�",false,true);
// 		List_AddT(pCombox->list_Head,pChild);
// 	 	pChild=new CLable(this,pCombox->iStartY+6,pCombox->iStartX,2,20,"�Ǻǹ�",false,true);
// 	  	List_AddT(pCombox->list_Head,pChild);
	 

	 pCom=new CButton(this,16,65,3,10,"Ȩ��");
	 List_AddT(this->list_Head,pCom);
	 pCom->AddKeyActionListener(new CUsr_PermissAC(this));//�޸��¼�
	


	 pInfoForm=new CInfoForm(this,5,0,15,40);//pForֱ��ָ�����λ�á�
	 List_AddT(this->list_Head,pInfoForm);
	 
}

int CUsr_Form::KeyListener()
{
	int iKey;
	//���������Խ��հ�ť�ĵ�һ��
	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)list_Head->pHead;
	CComponent *pCCom=(CComponent *)currNode->pData;

	/////////////ע���ж����ж��޻�ȡ���㣬������ѭ��״��///////////////
	while (pCCom->IsFocus()!=true)
	{
		currNode=currNode->pNext;
		pCCom=(CComponent *)currNode->pData;
	}
	//	keypad(pCCom->GetHandler(),TRUE);
	
	//���ݲ�ͬ�İ������ж���
	while (1)
	{
		if (true==this->isExit)
		{
			return EXITFLAG;
		}
		wmove(pCCom->GetHandler(),1,1);
		wrefresh(pCCom->GetHandler());
		keypad(pCCom->GetHandler(),TRUE);
		//��ȡ����
		pCCom->GetFocus();
		//iKey=wgetch(pCCom->GetHandler());
		iKey=pCCom->KeyListener();
		pCCom->LoseFocus();//ʧȥ
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
				�û���Ӵ���
****************************************************/
CUsr_AddForm::CUsr_AddForm(CComponent *owner):CForm(owner,0,0,20,80)
{
	CComponent *pCom=NULL;
	CActionListener *pAction=NULL;
	CCombox *pCombox=NULL;
	CComponent *pChild=NULL;
	char sUserId[10]={0};
	
	
	pCom=new CLable(this,0,10,3,40,"*��ǰλ�ã��û���ӽ���*",false);
	List_AddT(this->list_Head,pCom);

	//��һ��
	pCom=new CLable(this,4,2,3,10,"�û�ID",true);
	List_AddT(this->list_Head,pCom);

	pCom=new CLable(this,4,13,3,15,"",true);
	List_AddT(this->list_Head,pCom);
	strcpy(sUserId,	User_GetMaxId());
	sprintf(sUserId,"%d",atoi(sUserId)+1);//�����id�ϼ�һ
	((CLable *)pCom)->SetContent(sUserId);
	acId=((CLable *)pCom)->GetContent();		//��ȡid
	
	pCom=new CLable(this,4,33,3,10,"��������",true);	
	List_AddT(this->list_Head,pCom);	
	
	pCombox=new CCombox(this,4,44,3,20,"�칫��");
	List_AddT(this->list_Head,pCombox); 

	acDepartment=((CCombox *)pCombox)->GetContent();//��ȡ����
	
	/************������************************/
	pChild=new CLable(this,pCombox->iStartY+3,pCombox->iStartX,2,20,"�칫��",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+5,pCombox->iStartX,2,20,"������",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+7,pCombox->iStartX,2,20,"������",false,true);
	List_AddT(pCombox->list_Head,pChild);

//�ڶ���

	pCom=new CLable(this,8,2,3,10,"�˺�",true);	
	List_AddT(this->list_Head,pCom);
	pCom=new CEdit(this,8,13,3,15,false,10);
	List_AddT(this->list_Head,pCom);
	acAccount=((CEdit *)pCom)->GetContent();//��ȡ�ʺ�

	pCom=new CLable(this,8,33,3,10,"�û����",true);	
	List_AddT(this->list_Head,pCom);
	
	pCombox=new CCombox(this,8,44,3,20,"ϵͳ����Ա");
	List_AddT(this->list_Head,pCombox); 
	acType=((CCombox *)pCombox)->GetContent();		//�û�����
	//acRole=							//��ȡ���	
	
	//������
	pCom=new CLable(this,12,2,3,10,"����",true);	
	List_AddT(this->list_Head,pCom);
	pCom=new CEdit(this,12,13,3,15,false,10);
	List_AddT(this->list_Head,pCom);
	acName=((CEdit *)pCom)->GetContent();//��ȡ����

	pCom=new CLable(this,12,33,3,10,"���룺",true);	
	List_AddT(this->list_Head,pCom);
	
	pCom=new CEdit(this,12,44,3,15,true,10);
	List_AddT(this->list_Head,pCom);
	acPsw=((CEdit *)pCom)->GetContent();	//��ȡ����

	//������
	pCom=new CLable(this,16,2,3,10,"��ע",true);	
	List_AddT(this->list_Head,pCom);
	pCom=new CEdit(this,16,13,3,15,false,10);
	List_AddT(this->list_Head,pCom);
	acBeizhu=((CEdit *)pCom)->GetContent();//��ȡ��ע

	pCom=new CLable(this,16,33,3,10,"ȷ������",true);	
	List_AddT(this->list_Head,pCom);
	
	pCom=new CEdit(this,16,44,3,15,true,10);
	List_AddT(this->list_Head,pCom);
	acPswCheck=((CEdit *)pCom)->GetContent();	//ȷ������
	
	// 	pCom=new CLable(this,8,0,3,10,"�û����",true);	
	// 	List_AddT(this->list_Head,pCom);
	/********************�����˵�********************************/
	
		pChild=new CLable(this,pCombox->iStartY+3,pCombox->iStartX,2,20,"ϵͳ����Ա",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+5,pCombox->iStartX,2,20,"ҵ�����Ա",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+7,pCombox->iStartX,2,20,"����Ա",false,true);
	List_AddT(pCombox->list_Head,pChild);
	
	
	pCom=new CButton(this,12,65,3,10,"ȷ��");
	List_AddT(this->list_Head,pCom);		 
	 pCom->AddKeyActionListener(new CUsr_AddOKAC(this));//����¼�
	pCom=new CButton(this,16,65,3,10,"����");
	 List_AddT(this->list_Head,pCom);
	  pCom->AddKeyActionListener(new CBackAC(this));//�����¼�
		 
}

/************************************************
				�û��޸Ľ���
				char *acId;			//ID
				char *acDepartment;//����
				char *acAccount;	//�ʺ�
				char *acRole;		//��ɫ
				char *acName;		//����
				char *acPsw;		//����
				char *acBeizhu;		//��ע 
**************************************************/
CUsr_UpdateForm::CUsr_UpdateForm(CComponent *owner):CForm(owner,0,0,20,80)
{
	CComponent *pCom=NULL;
	CActionListener *pAction=NULL;
	CCombox *pCombox=NULL;
	CComponent *pChild=NULL;

	char sUser[6][20]={0};

	CInfoForm * pInfoForm= (CInfoForm *)((CUsr_Form *)(owner))->pInfoForm;//��ȡ����Ϣ��
	char *sInfo=pInfoForm->GetInfo();//��ȡ��Ϣ����õ���Ϣ
	CSinDB *pDB=CSinDB::GetSinDB();
	int iInfo;
	
	char sSql[1024]={0};

	char sUser_id[10]={0};//id
	iInfo=atoi(sInfo);
	sprintf(sUser_id,"%d",iInfo);		//����ǳ���
	sprintf(sSql,"select  * from user_info  where user_id = \"%s\" ",sUser_id);
	pDB->DoOpera(sSql,CUser_InfoCallBack,sUser);

	pCom=new CLable(this,0,10,3,40,"*��ǰλ�ã��û��޸Ľ���*",false);
	List_AddT(this->list_Head,pCom);
	
	//��һ��
	pCom=new CLable(this,4,2,3,10,"�û�ID",true);
	List_AddT(this->list_Head,pCom);
	
	pCom=new CLable(this,4,13,3,15,"",true);
	List_AddT(this->list_Head,pCom);
	((CLable *)pCom)->SetContent(sUser[0]);  
	acId=((CLable *)pCom)->GetContent();		//��ȡid
	
	pCom=new CLable(this,4,33,3,10,"��������",true);	
	List_AddT(this->list_Head,pCom);	
	


	pCombox=new CCombox(this,4,44,3,20,"�칫��");
	List_AddT(this->list_Head,pCombox); 

	acDepartment=((CCombox *)pCombox)->GetContent();//��ȡ����
	
	/************������************************/
	pChild=new CLable(this,pCombox->iStartY+3,pCombox->iStartX,2,20,"�칫��",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+5,pCombox->iStartX,2,20,"������",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+7,pCombox->iStartX,2,20,"������",false,true);
	List_AddT(pCombox->list_Head,pChild);

	//�ڶ���
	
	pCom=new CLable(this,8,2,3,10,"�˺�",true);	
	List_AddT(this->list_Head,pCom);
	pCom=new CEdit(this,8,13,3,15,false,10);
	List_AddT(this->list_Head,pCom);
	((CLable *)pCom)->SetContent(sUser[3]);

	acAccount=((CEdit *)pCom)->GetContent();//��ȡ�ʺ�
	
	pCom=new CLable(this,8,33,3,10,"�û����",true);	
	List_AddT(this->list_Head,pCom);
	
	pCombox=new CCombox(this,8,44,3,20,"ϵͳ����Ա");
	List_AddT(this->list_Head,pCombox); 
	acType=((CCombox *)pCombox)->GetContent();
	//acRole=							//��ȡ���	
	
	//������
	pCom=new CLable(this,12,2,3,10,"����",true);	
	List_AddT(this->list_Head,pCom);
	pCom=new CEdit(this,12,13,3,15,false,10);
	List_AddT(this->list_Head,pCom);
	((CEdit *)pCom)->SetContent(sUser[1]);
	acName=((CEdit *)pCom)->GetContent();//��ȡ����
	
	pCom=new CLable(this,12,33,3,10,"���룺",true);	
	List_AddT(this->list_Head,pCom);
	
	pCom=new CEdit(this,12,44,3,15,true,10);
	List_AddT(this->list_Head,pCom);
	acPsw=((CEdit *)pCom)->GetContent();	//��ȡ����
	
	//������
	pCom=new CLable(this,16,2,3,10,"��ע",true);	
	List_AddT(this->list_Head,pCom);
	pCom=new CEdit(this,16,13,3,15,false,10);
	List_AddT(this->list_Head,pCom);
		((CEdit *)pCom)->SetContent(sUser[5]);
	acBeizhu=((CEdit *)pCom)->GetContent();//��ȡ��ע
	
	pCom=new CLable(this,16,33,3,10,"ȷ������",true);	
	List_AddT(this->list_Head,pCom);
	
	pCom=new CEdit(this,16,44,3,15,true,10);
	List_AddT(this->list_Head,pCom);
	acPsw=((CEdit *)pCom)->GetContent();	//ȷ������
	
	// 	pCom=new CLable(this,8,0,3,10,"�û����",true);	
	// 	List_AddT(this->list_Head,pCom);
	/********************�����˵�********************************/
	
	
	pChild=new CLable(this,pCombox->iStartY+3,pCombox->iStartX,2,20,"ϵͳ����Ա",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+5,pCombox->iStartX,2,20,"��ְͨ��",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+7,pCombox->iStartX,2,20,"����",false,true);
	List_AddT(pCombox->list_Head,pChild);
	
	
	
	pCom=new CButton(this,12,65,3,10,"ȷ��");
	List_AddT(this->list_Head,pCom);		 
	pCom->AddKeyActionListener(new CUsr_UpdateOKAC(this));//����¼�
	pCom=new CButton(this,16,65,3,10,"����");
	List_AddT(this->list_Head,pCom);
	pCom->AddKeyActionListener(new CBackAC(this));//�����¼�
		 
		 
}


/****************************************
				Ȩ�����ý���
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
	CInfoForm * pInfoForm= (CInfoForm *)((CUsr_Form *)(owner))->pInfoForm;//��ȡ����Ϣ��
	char *sInfo=pInfoForm->GetInfo();//��ȡ��Ϣ����õ���Ϣ
	CSinDB *pDB=CSinDB::GetSinDB();
	int iInfo;
	
	char sSql[1024]={0};
	
	iInfo=atoi(sInfo);
	sprintf(sUser_id,"%d",iInfo);		//����ǳ���
	sprintf(sSql,"select  * from user_info  where user_id = \"%s\" ",sUser_id);
	pDB->DoOpera(sSql,CUser_InfoCallBack,sUser);
	
	pCom=new CLable(this,0,10,3,40,"*��ǰλ�ã�Ȩ�����ý���*",false);
	List_AddT(this->list_Head,pCom);
	
	//��һ��
	pCom=new CLable(this,4,2,2,10,"�û���",true);
	List_AddT(this->list_Head,pCom);
	
	pCom=new CLable(this,4,13,2,15,"",true);
	List_AddT(this->list_Head,pCom);
	((CLable *)pCom)->SetContent(sUser[1]);  
	
	
	pCom=new CLable(this,7,2,2,10,"�ʺ�",true);
	List_AddT(this->list_Head,pCom);
	
	pCom=new CLable(this,7,13,2,15,"",true);
	List_AddT(this->list_Head,pCom);
	((CLable *)pCom)->SetContent(sUser[3]);


	
	pCom=new CLable(this,4,33,2,10,"�û����",true);
	List_AddT(this->list_Head,pCom);
	

	pCombox=new CCombox(this,4,44,2,20,"ϵͳ����Ա");
	List_AddT(this->list_Head,pCombox); 
	acRole=((CCombox *)pCombox)->GetContent();
	

	pPerLable=new CPermissLable(this,9,2,11,60,true);
	List_AddT(this->list_Head,pPerLable); 
	pPerLable->whatshow=((CCombox *)pCombox)->GetContent();
	
	
	//acRole=//��ȡ���	
	
	/********************�����˵�********************************/
	
	
	pChild=new CLable(this,pCombox->iStartY+2,pCombox->iStartX,2,20,"ϵͳ����Ա",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+4,pCombox->iStartX,2,20,"ҵ�����Ա",false,true);
	List_AddT(pCombox->list_Head,pChild);
	pChild=new CLable(this,pCombox->iStartY+6,pCombox->iStartX,2,20,"����Ա",false,true);
	List_AddT(pCombox->list_Head,pChild);


	
	pCom=new CButton(this,12,65,3,10,"ȷ��");
	List_AddT(this->list_Head,pCom);
	pCom->AddKeyActionListener(new CUsr_UpdateOKAC(this));//����¼�
	pCom=new CButton(this,16,65,3,10,"����");
	List_AddT(this->list_Head,pCom);
	pCom->AddKeyActionListener(new CBackAC(this));//�����¼�
	
}


// 
// int CUsr_PermissForm::KeyListener()
// {
// 	int iKey;
// 	//���������Խ��հ�ť�ĵ�һ��
// 	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)list_Head->pHead;
// 	CComponent *pCCom=(CComponent *)currNode->pData;
// 	
// 	/////////////ע���ж����ж��޻�ȡ���㣬������ѭ��״��///////////////
// 	while (pCCom->IsFocus()!=true)
// 	{
// 		currNode=currNode->pNext;
// 		pCCom=(CComponent *)currNode->pData;
// 	}
// 	//	keypad(pCCom->GetHandler(),TRUE);
// 	
// 	//���ݲ�ͬ�İ������ж���
// 	while (1)
// 	{
// 		if (true==isExit)
// 		{
// 			return EXITFLAG;		//�˳�
// 		}
// 		wmove(pCCom->GetHandler(),1,1);
// 		wrefresh(pCCom->GetHandler());
// 		keypad(pCCom->GetHandler(),TRUE);
// 		
// 		//��ȡ����
// 		pCCom->GetFocus();
// 		iKey=pCCom->KeyListener();
// 		PermissShow(acRole);/////////////////������ʾ/////////////////////////////////////////////////////////
// 		//	this->Show();Ҫ��Ҫ
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
// 	//�����ݿ��ȡ��ɫID
// 	pDbSingle = CSinDB::GetSinDB();	
// 	sprintf(sql,"select role_id from role_info where role_name='%s'",cpRoleName);
// 
// 	pDbSingle->DoOpera(sql,RoleId_CallBack,sRole_ID);
// 	wbkgd(this->GetHandler(),COLOR_PAIR(2));
// 	wrefresh(this->GetHandler());
// 	wclear(this->GetHandler());
// 	
// 	if (0==strcmp(sRole_ID,"1001"))//ϵͳ����ԱȨ��
// 	{	
// 		mvwprintw(this->GetHandler(),0,8,"[*]ϵͳ����");
// 		mvwprintw(this->GetHandler(),1,10,"-[*]��֯��������");
// 		mvwprintw(this->GetHandler(),2,10,"-[*]�û�����");
// 		mvwprintw(this->GetHandler(),3,10,"-[*]ϵͳ��������");
// 		
// 		mvwprintw(this->GetHandler(),6,8,"[*]�ͻ��˹���");
// 		mvwprintw(this->GetHandler(),7,10,"-[*]�ͻ����û�����");
// 		mvwprintw(this->GetHandler(),8,10,"-[*]�û��㲥����");
// 		
// 		mvwprintw(this->GetHandler(),0,33,"[*]��Ƶ����");
// 		mvwprintw(this->GetHandler(),1,35,"-[*]Ƶ����Ϣ����");
// 		mvwprintw(this->GetHandler(),2,35,"-[*]������Ϣ����");
// 		mvwprintw(this->GetHandler(),3,35,"-[*]������Ϣ����");
// 		mvwprintw(this->GetHandler(),4,35,"-[*]��Ƶ��Ϣ����");
// 		
// 		mvwprintw(this->GetHandler(),6,33,"[*]����ͳ��");
// 		mvwprintw(this->GetHandler(),7,35,"-[*]�㲥����");				
// 	}
// 	else if (0==strcmp(sRole_ID,"1002"))//ҵ�����ԱȨ��
// 	{	
// 		mvwprintw(this->GetHandler(),0,8,"[*]ϵͳ����");
// 		mvwprintw(this->GetHandler(),1,10,"-[ ]��֯��������");
// 		mvwprintw(this->GetHandler(),2,10,"-[ ]�û�����");
// 		mvwprintw(this->GetHandler(),3,10,"-[ ]ϵͳ��������");
// 		
// 		mvwprintw(this->GetHandler(),6,8,"[*]�ͻ��˹���");
// 		mvwprintw(this->GetHandler(),7,10,"-[*]�ͻ����û�����");
// 		mvwprintw(this->GetHandler(),8,10,"-[*]�û��㲥����");
// 		
// 		mvwprintw(this->GetHandler(),0,33,"[*]��Ƶ����");
// 		mvwprintw(this->GetHandler(),1,35,"-[*]Ƶ����Ϣ����");
// 		mvwprintw(this->GetHandler(),2,35,"-[*]������Ϣ����");
// 		mvwprintw(this->GetHandler(),3,35,"-[*]������Ϣ����");
// 		mvwprintw(this->GetHandler(),4,35,"-[*]��Ƶ��Ϣ����");
// 		
// 		mvwprintw(this->GetHandler(),6,33,"[*]����ͳ��");
// 		mvwprintw(this->GetHandler(),7,35,"-[*]�㲥����");	
// 	}	
// 		
// 		if (0==strcmp(sRole_ID,"1003"))//����ԱȨ��
// 		{					
// 			mvwprintw(this->GetHandler(),0,8,"[*]ϵͳ����");
// 			mvwprintw(this->GetHandler(),1,10,"-[ ]��֯��������");
// 			mvwprintw(this->GetHandler(),2,10,"-[ ]�û�����");
// 			mvwprintw(this->GetHandler(),3,10,"-[ ]ϵͳ��������");
// 			
// 			mvwprintw(this->GetHandler(),6,8,"[*]�ͻ��˹���");
// 			mvwprintw(this->GetHandler(),7,10,"-[ ]�ͻ����û�����");
// 			mvwprintw(this->GetHandler(),8,10,"-[ ]�û��㲥����");
// 			
// 			mvwprintw(this->GetHandler(),0,33,"[ ]��Ƶ����");
// 			mvwprintw(this->GetHandler(),1,35,"-[ ]Ƶ����Ϣ����");
// 			mvwprintw(this->GetHandler(),2,35,"-[ ]������Ϣ����");
// 			mvwprintw(this->GetHandler(),3,35,"-[ ]������Ϣ����");
// 			mvwprintw(this->GetHandler(),4,35,"-[ ]��Ƶ��Ϣ����");
// 			
// 			mvwprintw(this->GetHandler(),6,33,"[*]����ͳ��");
// 			mvwprintw(this->GetHandler(),7,35,"-[*]�㲥����");	
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