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
	//把编辑框的两个数据获取
	char *acName=((CLoginForm *)owner)->GetName();
	char *acPsw=((CLoginForm *)owner)->GetPsw();
	char sSql[1024]={0};
	CMenuBar *pBar=NULL;
	//按下enter键以后进入这里
	//获取数据单例
	CSinDB *pDB=CSinDB::GetSinDB();
	//组合成sql语句
	sprintf(sSql,"select user_id from user_info where user_name = \"%s\" and user_psw= \"%s\"",acName,acPsw);
	//验证用户密码账号
	//也就是执行sql语句,若用则执行OK_CallBack
	pDB->DoOpera(sSql,BtnOK_CallBack,sId);

	//根据sId是否改变来提示
	if (0==strcmp(sId,sChek))
	{
		//则提示登陆失败，账号或者密码不正确
		printw("登陆失败");//可以改成一个小程序：为对话框窗口
		refresh();
	}
	else
	{
		//先提示登陆成功
		printw("登陆成功");
		printw("%s",sId);
		refresh();

		//目的：生产菜单栏
		//查询的sql语句生成
		sprintf(sSql,"select * from menu_info where menu_id in(select menu_id from role_power where role_id=(select role_id from user_role where user_id =\"%s\")) ",sId);
		//	printw(sSql);
		//	refresh();
		//生成一个菜单栏
		pBar=new CMenuBar(NULL,0,0,20,80);
		pDB->DoOpera(sSql,CBar_CallBack,pBar);
		pBar->Show();
		pBar->KeyListener();
	}	
}




/***********************************************
				用户管理菜单事件
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