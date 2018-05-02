
#include "CMenu.h"
#include <stdlib.h>
#include "CUsr_Form.h"
#include "CForm.h"
#include "LoginAction.h"
_P_DOUBLELIST_T CMenuBar::list_Head=List_Init();

CMenuBar::CMenuBar(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth)
	:CComponent(cOwner,iStartY,iStartX,iHeight,iWidth)
{
	isExit=false;
}

void CMenuBar::Show()
{
	//菜单栏的显示
	//将第一级菜单显示。
	int iCount=0;
	CComponent *c=NULL;
	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)CMenuBar::list_Head->pHead;
	wbkgd(pHandler,COLOR_PAIR(4));
	wrefresh(pHandler);
	for(iCount;iCount<list_Head->iLen;iCount++)
	{
		c=(CComponent *)currNode->pData;		
		c->Show();
		wbkgd(c->GetHandler(),COLOR_PAIR(2));
		wrefresh(c->GetHandler());
		currNode=currNode->pNext;
	}

}

int CMenuBar::KeyListener()
{
	int iKey;
	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)CMenuBar::list_Head->pHead;
	CMenu *pCCom=(CMenu *)currNode->pData;

	while (1)
	{
		//移动到第一次菜单
		wmove(pCCom->GetHandler(),1,1);
		wrefresh(pCCom->GetHandler());
		keypad(pCCom->GetHandler(),TRUE);
		//获取焦点
		pCCom->GetFocus();
		iKey=wgetch(pCCom->GetHandler());
		//iKey=pCCom->KeyListener();
		wrefresh(pHandler);
		wrefresh(pCCom->GetHandler());
		//只有按下左右键时这一列才会被刷新。
		switch(iKey)
		{
			if (isExit)
			{
				return EXITFLAG;
			}
			case KEY_LEFT:
			{
				pCCom->LoseFocus();
				currNode=currNode->pPre;
				pCCom=(CMenu *)currNode->pData;
				while (pCCom->IsFocus()!=true)
				{
					currNode=currNode->pPre;
					pCCom=(CMenu *)currNode->pData;
				}
				break;
			}
		case KEY_RIGHT:
			{
				pCCom->LoseFocus();
				currNode=currNode->pNext;
				pCCom=(CMenu *)currNode->pData;
				while (pCCom->IsFocus()!=true)
				{
					currNode=currNode->pNext;
					pCCom=(CMenu *)currNode->pData;
				}
				
				break;
			}
		case '\n':
		case KEY_DOWN:		
			iKey=pCCom->KeyListener();
			break;
		case 0:
			break;
		default:
			break;
			
		}	
	}
	return 0;
}

void CMenuBar::SetExit(bool isExit)
{
	this->isExit=isExit;
}



//////////////////////////////////////////////////
CMenu::CMenu(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,char *pName)
	:CComponent(cOwner,iStartY,iStartX,iHeight,iWidth,true)
{
	list_Head=List_Init();
	this->pName=new char[strlen(pName)+1];
	strcpy(this->pName,pName);
}
void CMenu::Show()
{
	int iCount=0;
	CMenu *cm=NULL;
	box(pHandler,0,0);
	wbkgd(pHandler,COLOR_PAIR(4));
	mvwprintw(pHandler,1,(iWidth-strlen(pName))/2,"%s",pName);
	

	wrefresh(pHandler);
	
	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)list_Head->pHead;
	for(iCount;iCount<list_Head->iLen;iCount++)
	{
		cm=(CMenu *)currNode->pData;
		wbkgd(cm->GetHandler(),COLOR_PAIR(2));
		cm->Show();
		currNode=currNode->pNext;
	}

	wrefresh(pHandler);
}



int CMenu::KeyListener()
{
	int iKey;
	CComponent *pCCom=NULL;
	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)this->list_Head->pHead;
	if (NULL==currNode)
	{
		return 22222;
	}
	pCCom=(CComponent *)currNode->pData;
	
	while (1)
	{
	
		wmove(pCCom->GetHandler(),1,1);
		wrefresh(pCCom->GetHandler());
		keypad(pCCom->GetHandler(),TRUE);
		//获取焦点
		pCCom->GetFocus();
		iKey=wgetch(pCCom->GetHandler());
		wrefresh(pHandler);
		pCCom->LoseFocus();
		wrefresh(pCCom->GetHandler());
		switch(iKey)
		{
		case KEY_UP:
			{
				currNode=currNode->pPre;
				pCCom=(CComponent *)currNode->pData;
				while (pCCom->IsFocus()!=true)
				{
					
					currNode=currNode->pPre;
					pCCom=(CComponent *)currNode->pData;
				}
				
				break;
			}
		case KEY_DOWN:
			{
				currNode=currNode->pNext;
				pCCom=(CComponent *)currNode->pData;
				while (pCCom->IsFocus()!=true)
				{
					currNode=currNode->pNext;
					pCCom=(CComponent *)currNode->pData;
				}
				
				break;
			}
		case KEY_LEFT:
			return KEY_LEFT;
		case KEY_RIGHT:
			return KEY_RIGHT;
		case '\n':
			{
				pCCom->GetAction()->DoAction();
			//	iKey=pCCom->KeyListener();
			}
		
			
		default:
		
			break;
			
		}	
	}
	return 0;
}
/*void CMenu::SetFlag(int flag)
{
	this->flag=flag;
}*/
void CMenu::GetFocus()
{
	CMenu *pCCom=NULL;
	int iCount=0;
	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)list_Head->pHead;

	//获得焦点，将其包含的链表里面的节点颜色改变
	for(iCount;iCount<list_Head->iLen;iCount++)
	{
		pCCom=(CMenu *)currNode->pData;
		wbkgd(pCCom->GetHandler(),COLOR_PAIR(2));
		wrefresh(pCCom->GetHandler());
		currNode=currNode->pNext;
	}
		wbkgd(this->GetHandler(),COLOR_PAIR(3));
		wrefresh(this->GetHandler());

}

void CMenu::LoseFocus()
{
	CMenu *pCCom=NULL;
	int iCount=0;
	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)list_Head->pHead;
	//菜失去焦点会干什么呢。
	//将其的链表里面的	

	for(iCount;iCount<list_Head->iLen;iCount++)
	{
		pCCom=(CMenu *)currNode->pData;
		wbkgd(pCCom->GetHandler(),COLOR_PAIR(4));
		wrefresh(pCCom->GetHandler());
		currNode=currNode->pNext;
	}
	wbkgd(this->GetHandler(),COLOR_PAIR(2));
	wrefresh(this->GetHandler());

}

void CMenu::ActionFactory(char *id)
{
	//CActionListener *pAction=NULL;
	int iId=atoi(id);
	switch(iId)
	{
	case 1007:
	//	pAction=;
		this->AddKeyActionListener(new CMenu_UsrAc(this));
		break;
	default:
		//添加未开通窗体
	//	this->AddKeyActionListener(new CMenu_NoAc())
		this->AddKeyActionListener(new CMenu_UsrAc(this));
		break;
	}
}