#include "CLoginDB.h"
#include <stdio.h>
#include <string.h>
#include "CMenu.h"
#include <ncurses.h>
#include "CSinDB.h"
//һ���˵��Ļص��������������ɶ����˵�
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
	//��Ϊ�˵�����¼�
	pMenu->ActionFactory(sMenuID);
	return 0;
}
//���ҵ�һ��һ���˵������������˵���
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
	//����֤���Խ���Callback
	//���ɲ˵��������������ͷ
	CMenu *pMenu=new CMenu(pBar,0,(pBar->list_Head->iLen)*15,3,15,sMenuName);
	List_AddT(pBar->list_Head,pMenu);//һ���˵�����˵�������  //�޸ĸ�����������Ȼʹ���߲�֪����ô��
	//��ʱ����Ҫ�����˵���
	//��Ҫһ��sql���
	sprintf(sSql,"select * from menu_info where menu_ftid =\"%s\" ",sMenuID);
	//��ȡ����
	pDB->DoOpera(sSql,CMenu_CallBack,pMenu);

	return 0;
}



//��ȡ�û�id
int BtnOK_CallBack(void *canshu,int iColumn,char ** colValue,char **colName)
{
	//�ı�canshu��ֵ
	strcpy((char *)canshu,colValue[0]);
	return 0;
}