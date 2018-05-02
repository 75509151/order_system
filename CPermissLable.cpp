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

	if (0==strcmp(sRole_ID,"1001"))//系统管理员权限
	{	
		mvwprintw(this->GetHandler(),0,8,"[*]系统管理");
		mvwprintw(this->GetHandler(),1,10,"-[*]组织机构管理");
		mvwprintw(this->GetHandler(),2,10,"-[*]用户管理");
		mvwprintw(this->GetHandler(),3,10,"-[*]系统参数设置");
		
		mvwprintw(this->GetHandler(),6,8,"[*]客户端管理");
		mvwprintw(this->GetHandler(),7,10,"-[*]客户端用户管理");
		mvwprintw(this->GetHandler(),8,10,"-[*]用户点播管理");
		
		mvwprintw(this->GetHandler(),0,33,"[*]视频管理");
		mvwprintw(this->GetHandler(),1,35,"-[*]频道信息管理");
		mvwprintw(this->GetHandler(),2,35,"-[*]分类信息管理");
		mvwprintw(this->GetHandler(),3,35,"-[*]地区信息管理");
		mvwprintw(this->GetHandler(),4,35,"-[*]视频信息管理");
		
		mvwprintw(this->GetHandler(),6,33,"[*]报表统计");
		mvwprintw(this->GetHandler(),7,35,"-[*]点播报表");				
	}
	else if (0==strcmp(sRole_ID,"1002"))//业务管理员权限
	{	
		mvwprintw(this->GetHandler(),0,8,"[*]系统管理");
		mvwprintw(this->GetHandler(),1,10,"-[ ]组织机构管理");
		mvwprintw(this->GetHandler(),2,10,"-[ ]用户管理");
		mvwprintw(this->GetHandler(),3,10,"-[ ]系统参数设置");
		
		mvwprintw(this->GetHandler(),6,8,"[*]客户端管理");
		mvwprintw(this->GetHandler(),7,10,"-[*]客户端用户管理");
		mvwprintw(this->GetHandler(),8,10,"-[*]用户点播管理");
		
		mvwprintw(this->GetHandler(),0,33,"[*]视频管理");
		mvwprintw(this->GetHandler(),1,35,"-[*]频道信息管理");
		mvwprintw(this->GetHandler(),2,35,"-[*]分类信息管理");
		mvwprintw(this->GetHandler(),3,35,"-[*]地区信息管理");
		mvwprintw(this->GetHandler(),4,35,"-[*]视频信息管理");
		
		mvwprintw(this->GetHandler(),6,33,"[*]报表统计");
		mvwprintw(this->GetHandler(),7,35,"-[*]点播报表");	
	}	
	
	if (0==strcmp(sRole_ID,"1003"))//操作员权限
	{					
		mvwprintw(this->GetHandler(),0,8,"[*]系统管理");
		mvwprintw(this->GetHandler(),1,10,"-[ ]组织机构管理");
		mvwprintw(this->GetHandler(),2,10,"-[ ]用户管理");
		mvwprintw(this->GetHandler(),3,10,"-[ ]系统参数设置");
		
		mvwprintw(this->GetHandler(),6,8,"[*]客户端管理");
		mvwprintw(this->GetHandler(),7,10,"-[ ]客户端用户管理");
		mvwprintw(this->GetHandler(),8,10,"-[ ]用户点播管理");
		
		mvwprintw(this->GetHandler(),0,33,"[ ]视频管理");
		mvwprintw(this->GetHandler(),1,35,"-[ ]频道信息管理");
		mvwprintw(this->GetHandler(),2,35,"-[ ]分类信息管理");
		mvwprintw(this->GetHandler(),3,35,"-[ ]地区信息管理");
		mvwprintw(this->GetHandler(),4,35,"-[ ]视频信息管理");
		
		mvwprintw(this->GetHandler(),6,33,"[*]报表统计");
		mvwprintw(this->GetHandler(),7,35,"-[*]点播报表");	
		
		}			
	wrefresh(this->GetHandler());
		
}