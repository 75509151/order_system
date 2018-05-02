#include "CPermissLable.h"
#include "CUsr_Form.h"
#include "CSinDB.h"
#include "CUsr_DB.h"
CPermissLable::CPermissLable(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,bool hasBox/*,char *whatshow*/)
:CComponent(cOwner,iStartY,iStartX,iHeight,iWidth)
{
	this->hasBox=hasBox;
// 	this->whatshow=new char[strlen(whatshow)+1];
// 	strcpy(this->whatshow,whatshow);
	whatshow=NULL;
}

void CPermissLable::Show()
{
	char sRole_ID[10]={0};
	CSinDB *pDB=CSinDB::GetSinDB();
	char sSql[1024]={0};
	sprintf(sSql,"select role_id from role_info where role_name='%s'",whatshow);
	pDB->DoOpera(sSql,RoleId_CallBack,sRole_ID);

	wbkgd(pHandler,COLOR_PAIR(2));


	box(pHandler,0,0);
// 	mvwprintw(pHandler,1,(iWidth-strlen(whatshow))/2,"%s",whatshow);
// 	wrefresh(pHandler);
 	//wclear(this->GetHandler());

	if (0==strcmp(sRole_ID,"1001"))//ϵͳ����ԱȨ��
	{	
		mvwprintw(this->GetHandler(),0,8,"[*]ϵͳ����");
		mvwprintw(this->GetHandler(),1,10,"-[*]��֯��������");
		mvwprintw(this->GetHandler(),2,10,"-[*]�û�����");
		mvwprintw(this->GetHandler(),3,10,"-[*]ϵͳ��������");
		
		mvwprintw(this->GetHandler(),6,8,"[*]�ͻ��˹���");
		mvwprintw(this->GetHandler(),7,10,"-[*]�ͻ����û�����");
		mvwprintw(this->GetHandler(),8,10,"-[*]�û��㲥����");
		
		mvwprintw(this->GetHandler(),0,33,"[*]��Ƶ����");
		mvwprintw(this->GetHandler(),1,35,"-[*]Ƶ����Ϣ����");
		mvwprintw(this->GetHandler(),2,35,"-[*]������Ϣ����");
		mvwprintw(this->GetHandler(),3,35,"-[*]������Ϣ����");
		mvwprintw(this->GetHandler(),4,35,"-[*]��Ƶ��Ϣ����");
		
		mvwprintw(this->GetHandler(),6,33,"[*]����ͳ��");
		mvwprintw(this->GetHandler(),7,35,"-[*]�㲥����");				
	}
	else if (0==strcmp(sRole_ID,"1002"))//ҵ�����ԱȨ��
	{	
		mvwprintw(this->GetHandler(),0,8,"[*]ϵͳ����");
		mvwprintw(this->GetHandler(),1,10,"-[ ]��֯��������");
		mvwprintw(this->GetHandler(),2,10,"-[ ]�û�����");
		mvwprintw(this->GetHandler(),3,10,"-[ ]ϵͳ��������");
		
		mvwprintw(this->GetHandler(),6,8,"[*]�ͻ��˹���");
		mvwprintw(this->GetHandler(),7,10,"-[*]�ͻ����û�����");
		mvwprintw(this->GetHandler(),8,10,"-[*]�û��㲥����");
		
		mvwprintw(this->GetHandler(),0,33,"[*]��Ƶ����");
		mvwprintw(this->GetHandler(),1,35,"-[*]Ƶ����Ϣ����");
		mvwprintw(this->GetHandler(),2,35,"-[*]������Ϣ����");
		mvwprintw(this->GetHandler(),3,35,"-[*]������Ϣ����");
		mvwprintw(this->GetHandler(),4,35,"-[*]��Ƶ��Ϣ����");
		
		mvwprintw(this->GetHandler(),6,33,"[*]����ͳ��");
		mvwprintw(this->GetHandler(),7,35,"-[*]�㲥����");	
	}	
	
	if (0==strcmp(sRole_ID,"1003"))//����ԱȨ��
	{					
		mvwprintw(this->GetHandler(),0,8,"[*]ϵͳ����");
		mvwprintw(this->GetHandler(),1,10,"-[ ]��֯��������");
		mvwprintw(this->GetHandler(),2,10,"-[ ]�û�����");
		mvwprintw(this->GetHandler(),3,10,"-[ ]ϵͳ��������");
		
		mvwprintw(this->GetHandler(),6,8,"[*]�ͻ��˹���");
		mvwprintw(this->GetHandler(),7,10,"-[ ]�ͻ����û�����");
		mvwprintw(this->GetHandler(),8,10,"-[ ]�û��㲥����");
		
		mvwprintw(this->GetHandler(),0,33,"[ ]��Ƶ����");
		mvwprintw(this->GetHandler(),1,35,"-[ ]Ƶ����Ϣ����");
		mvwprintw(this->GetHandler(),2,35,"-[ ]������Ϣ����");
		mvwprintw(this->GetHandler(),3,35,"-[ ]������Ϣ����");
		mvwprintw(this->GetHandler(),4,35,"-[ ]��Ƶ��Ϣ����");
		
		mvwprintw(this->GetHandler(),6,33,"[*]����ͳ��");
		mvwprintw(this->GetHandler(),7,35,"-[*]�㲥����");	
		
		}			
	wrefresh(this->GetHandler());
		
}