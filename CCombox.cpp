#include "CComobox.h"

CCombox::CCombox(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,char *pContent)
	:CComponent(cOwner,iStartY,iStartX,iHeight,iWidth,true)
	,infolable(this,0,0,iHeight,iWidth-iWidth/4,pContent,false),flaglable(this,0,iWidth-iWidth/4,iHeight,iWidth/4,(char *)"+",false)
{
	
	this->list_Head=List_Init();
}

void CCombox::Show()
{
	box(pHandler,0,0);
	infolable.Show();
	flaglable.Show();
	wrefresh(pHandler);
}
int CCombox::KeyListener()
{
	int iKey;
	do 
	{
		iKey=wgetch(this->GetHandler());
		switch(iKey)
		{
		case KEY_UP:
			return KEY_UP;
		case KEY_DOWN:
			return KEY_DOWN;
		case KEY_LEFT:
			return KEY_LEFT;
		case KEY_RIGHT:
			return KEY_RIGHT;
		case '\n':
		//	wclear(flaglable.GetHandler());
			flaglable.SetContent((char *)"-");
			flaglable.Show();
			wrefresh(flaglable.GetHandler());
			wrefresh(pHandler);
			ChildShow();
			//powrshow(GetContent());
			ChildSelect();
			flaglable.SetContent((char *)"+");
			flaglable.Show();
			wrefresh(flaglable.GetHandler());
			this->GetFocus();
            break ;
		}
	} while(1);
	
}

void CCombox::Flush()
{
	CComponent *pC=NULL;
	int iCount=0;
	
	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)this->list_Head->pHead;
	for(iCount;iCount<list_Head->iLen;iCount++)
	{
		pC=(CLable *)currNode->pData;
		wclear(pC->GetHandler());
		wbkgd(pC->GetHandler(),COLOR_PAIR(4));
		wrefresh(pC->GetHandler());	
		wrefresh(pHandler);
		currNode=currNode->pNext;
	}
	wbkgd(stdscr,COLOR_PAIR(4));
		refresh();
}

void  CCombox::ChildShow()
{
	int iCount=0;
	CComponent *c=NULL;
	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)list_Head->pHead;
	for(iCount;iCount<list_Head->iLen;iCount++)
	{
		
		c=(CComponent *)currNode->pData;
		c->Show();
		wrefresh(c->GetHandler());
		currNode=currNode->pNext;
	}
	wrefresh(pHandler);
}

void  CCombox::ChildSelect()
{
	int iCount=0;
	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)list_Head->pHead;
	CLable *pCCom=(CLable *)currNode->pData;
	int iKey;
	while (1)
	{
		wclear(infolable.GetHandler());
		infolable.SetContent(pCCom->GetContent());
		infolable.Show();
		wrefresh(infolable.GetHandler());
		wmove(pCCom->GetHandler(),1,1);
		wrefresh(pCCom->GetHandler());
		keypad(pCCom->GetHandler(),TRUE);
		//»ñÈ¡½¹µã
		pCCom->GetFocus();
	
		iKey=wgetch(pCCom->GetHandler());
	

		pCCom->LoseFocus();
		

		
		switch(iKey)
		{
		case KEY_UP:
			{
				currNode=currNode->pPre;
				pCCom=(CLable *)currNode->pData;
				while (pCCom->IsFocus()!=true)
				{
					
					currNode=currNode->pPre;
					pCCom=(CLable *)currNode->pData;
				}
			
				break;
			}
		case KEY_DOWN:
			{
				currNode=currNode->pNext;
				pCCom=(CLable *)currNode->pData;
				while (pCCom->IsFocus()!=true)
				{
					currNode=currNode->pNext;
					pCCom=(CLable *)currNode->pData;
				}

				break;
			}

		case '\n':
			this->Flush();
			pCCom->cOwner->Show();
			
			return;
			
		}
		
	}


	wrefresh(pHandler);
}


char *CCombox::GetContent()
{

	return infolable.GetContent();
}
