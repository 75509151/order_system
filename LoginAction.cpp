#include "LoginAction.h"
#include "CSinDB.h"
#include "CLoginForm.h"
#include "CMenu.h"
#include "CLoginDB.h"
#include "CUsr_Form.h"
CLoginAction::CLoginAction(CComponent *owner):CActionListener(owner)
{
	
}

void CLoginAction::DoAction()
{
	char sId[10]={0};
	char sChek[10]={0};
	//�ѱ༭����������ݻ�ȡ
	char *acName=((CLoginForm *)owner)->GetName();
	char *acPsw=((CLoginForm *)owner)->GetPsw();
	char sSql[1024]={0};
	CMenuBar *pBar=NULL;
	//����enter���Ժ��������
	//��ȡ���ݵ���
	CSinDB *pDB=CSinDB::GetSinDB();
	//��ϳ�sql���
	sprintf(sSql,"select user_id from user_info where user_name = \"%s\" and user_psw= \"%s\"",acName,acPsw);
	//��֤�û������˺�
	//Ҳ����ִ��sql���,������ִ��OK_CallBack
	pDB->DoOpera(sSql,BtnOK_CallBack,sId);

	//����sId�Ƿ�ı�����ʾ
	if (0==strcmp(sId,sChek))
	{
		//����ʾ��½ʧ�ܣ��˺Ż������벻��ȷ
		printw("��½ʧ��");//���Ըĳ�һ��С����Ϊ�Ի��򴰿�
		refresh();
	}
	else
	{
		//����ʾ��½�ɹ�
		printw("��½�ɹ�");
		printw("%s",sId);
		refresh();

		//Ŀ�ģ������˵���
		//��ѯ��sql�������
		sprintf(sSql,"select * from menu_info where menu_id in(select menu_id from role_power where role_id=(select role_id from user_role where user_id =\"%s\")) ",sId);
		//	printw(sSql);
		//	refresh();
		//����һ���˵���
		pBar=new CMenuBar(NULL,0,0,20,80);
		pDB->DoOpera(sSql,CBar_CallBack,pBar);
		pBar->Show();
		pBar->KeyListener();
	}	
}




/***********************************************
				�û�����˵��¼�
***************************************************/
CMenu_UsrAc::CMenu_UsrAc(CComponent *owner):CActionListener(owner)
{

}

void CMenu_UsrAc::DoAction()
{
	CUsr_Form *pUsrForm= new CUsr_Form(NULL);
	pUsrForm->Show();
	pUsrForm->KeyListener();
}