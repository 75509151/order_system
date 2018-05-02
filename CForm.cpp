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
	//���������Խ��հ�ť�ĵ�һ��
	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)list_Head->pHead;
	CComponent *pCCom=(CComponent *)currNode->pData;

	/////////////ע���ж����ж��޻�ȡ���㣬������ѭ��״��///////////////
	while (pCCom->IsFocus()!=true)
	{
		currNode=currNode->pNext;
		pCCom=(CComponent *)currNode->pData;
	}
//	keypad(pCCom->GetHandler(),TRUE);

	//���ݲ�ͬ�İ������ж���
	while (1)
	{
		if (true==isExit)
		{
			return EXITFLAG;		//�˳�
		}
		wmove(pCCom->GetHandler(),1,1);
		wrefresh(pCCom->GetHandler());
		keypad(pCCom->GetHandler(),TRUE);
		//��ȡ����
		pCCom->GetFocus();
		iKey=pCCom->KeyListener();
	//	this->Show();Ҫ��Ҫ
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