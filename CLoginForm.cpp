/*
class CLoginForm 
{
public:
CLoginForm(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,char *pName);
	CForm *cCom; 
protected:

  private:
};
  
*/


#include "CLoginForm.h"
#include "CButton.h"
#include "CLable.h"
#include "CEdit.h"
#include "CComponent.h"
#include "LoginAction.h"

CLoginForm::CLoginForm(CComponent *owner):CForm(owner,0,0,20,80)
{
	
	 CComponent *pCom=NULL;
	 CActionListener *pAction=NULL;
	 //将各个空间添加到loginfrom
	 pCom=new CLable(this,1,10,3,20,"media",false);

	 List_AddT(this->list_Head,pCom);
	 pCom=new CLable(this,4,10,3,20,"name:",true);
	
	 List_AddT(this->list_Head,pCom);
	 pCom=new CEdit(this,4,30,3,20,false,10);
	 acName=((CEdit *)pCom)->GetContent();		//指针指向编辑框内容的地址
	 List_AddT(this->list_Head,pCom);
	 pCom=new CLable(this,7,10,3,20,"password:",true);
		
	 List_AddT(this->list_Head,pCom);
	 pCom=new CEdit(this,7,30,3,20,true,10);
	 acPsw=((CEdit *)pCom)->GetContent();		//指针指向编辑框内容的地址
	 List_AddT(this->list_Head,pCom);
	 pCom=new CButton(this,12,10,3,10,"enter");
	 pAction=new CLoginAction(this);
	 pCom->AddKeyActionListener(pAction);//为确定添加事件

	 List_AddT(this->list_Head,pCom);
	 pCom=new CButton(this,12,25,3,10,"exit");
	 pAction=new CLoginAction(this);
	 pCom->AddKeyActionListener(pAction);//为退出添加事件
	 List_AddT(this->list_Head,pCom);

}


char *CLoginForm::GetName()
{
	return acName;
}

char *CLoginForm::GetPsw()
{
	return acPsw;
}