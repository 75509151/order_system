/*class CForm:public CComponent
{
public:
CForm(CComponent &cOwner,WINDOW &pHandler,int iStartY,int iStartX,int iHeight,int iWidth,char *pName);
~CForm();
void Show();
protected:
private:
_P_DOUBLELIST_T list_Head;	
};*/

#include "CForm.h"

CForm::CForm(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth)
		:CComponent(cOwner,iStartY,iStartX,iHeight,iWidth)
{
	this->list_Head=List_Init();
	this->isExit=false;
}

void CForm::Show()
{
	int iCount=0;
	CComponent *c=NULL;
	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)list_Head->pHead;
	
	wclear(pHandler);
	wbkgd(pHandler,COLOR_PAIR(1));

//	box(pHandler,0,0);
	
	for(iCount;iCount<list_Head->iLen;iCount++)
	{
	
		c=(CComponent *)currNode->pData;
	    c->Show();
		wrefresh(c->GetHandler());
		currNode=currNode->pNext;
	}
	wrefresh(pHandler);

}

int CForm::KeyListener()
{
	int iKey;
	//遍历到可以接收按钮的第一个
	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)list_Head->pHead;
	CComponent *pCCom=(CComponent *)currNode->pData;

	/////////////注意判断所有都无获取焦点，陷入死循环状况///////////////
	while (pCCom->IsFocus()!=true)
	{
		currNode=currNode->pNext;
		pCCom=(CComponent *)currNode->pData;
	}
//	keypad(pCCom->GetHandler(),TRUE);

	//根据不同的按键进行动作
	while (1)
	{
		if (true==isExit)
		{
			return EXITFLAG;		//退出
		}
		wmove(pCCom->GetHandler(),1,1);
		wrefresh(pCCom->GetHandler());
		keypad(pCCom->GetHandler(),TRUE);
		//获取焦点
		pCCom->GetFocus();
		iKey=pCCom->KeyListener();
	//	this->Show();要不要
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

			
		default:
			
			break;
			
		}
		
	}
		return 0;
}


void CForm::SetExit(bool isExit)
{
	this->isExit=isExit;
}