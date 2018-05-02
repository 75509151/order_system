#include "CLoginDB.h"
#include <stdio.h>
#include <string.h>
#include "CMenu.h"
#include <ncurses.h>
#include "CSinDB.h"
//一级菜单的回调函数，用来生成二级菜单
int CMenu_CallBack(void *canshu,int iColumn,char ** colValue,char **colName )
{
	
	CMenu *pFmenu=(CMenu *)canshu;
	char sMenuName[30]={0};
	char *sMenuID=colValue[0];
	strcpy(sMenuName,colValue[1]);
	CMenu *pMenu=new CMenu(NULL,(pFmenu->list_Head->iLen+1)*3,pFmenu->GetStartX(),3,15,sMenuName);
	//printw("%s",pMenu->pName);
	//printw("%d,%d",pMenu->iStartY,pMenu->GetStartX());
	//	refresh();
	List_AddT(pFmenu->list_Head,pMenu);
	//并为菜单添加事件
	pMenu->ActionFactory(sMenuID);
	return 0;
}
//查找到一个一级菜单，则加入这个菜单栏
int CBar_CallBack(void *canshu,int iColumn,char ** colValue,char **colName )
{
	CMenuBar *pBar=(CMenuBar *)canshu;
	char sMenuName[30]={0};
	char *sMenuID=colValue[0];
	char sSql[1024]={0};
	CSinDB *pDB=CSinDB::GetSinDB();
	sMenuID=colValue[0];
	strcpy(sMenuName,colValue[1]);
//	printw(sMenuName);
//	refresh();
	//经验证可以进入Callback
	//生成菜单，并添加入链表头
	CMenu *pMenu=new CMenu(pBar,0,(pBar->list_Head->iLen)*15,3,15,sMenuName);
	List_AddT(pBar->list_Head,pMenu);//一级菜单加入菜单栏链表  //修改个函数名，不然使用者不知道怎么做
	//这时候需要二级菜单了
	//需要一个sql语句
	sprintf(sSql,"select * from menu_info where menu_ftid =\"%s\" ",sMenuID);
	//获取单例
	pDB->DoOpera(sSql,CMenu_CallBack,pMenu);

	return 0;
}



//获取用户id
int BtnOK_CallBack(void *canshu,int iColumn,char ** colValue,char **colName)
{
	//改变canshu的值
	strcpy((char *)canshu,colValue[0]);
	return 0;
}