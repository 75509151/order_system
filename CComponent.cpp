
#include "CComponent.h"
#include "CForm.h"
CComponent::CComponent(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,/*char *pName,*/bool isFocus)
{ 
	this->cOwner=cOwner;
	this->pHandler=pHandler;
	this->iStartY=iStartY;
	this->iStartX=iStartX;
	this->iHeight=iHeight;
	this->iWidth=iWidth;
/*	this->pName=new char[strlen(pName)+1];
	strcpy(this->pName,pName);*/
	this->isFocus=isFocus;
	if (NULL==cOwner)
	{
		this->pHandler=newwin(iHeight,iWidth,iStartY,iStartX);

	}
	else
	{
		this->pHandler=derwin(cOwner->pHandler,iHeight,iWidth,iStartY,iStartX);
		
	}
}

CComponent::~CComponent()
{
	/*delete [] pName;*/
	//É¾³ý´°¿Ú
	delwin(this->pHandler);
	delete pHandler;
}

bool CComponent::IsFocus()
{
	if (isFocus==true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

WINDOW *CComponent::GetHandler()
{
	return pHandler;
}

int CComponent::KeyListener()
{
    return 1;
}

void CComponent::AddKeyActionListener(CActionListener *action)
{
	this->action=action;
}

void CComponent::LoseFocus()
{
	curs_set(1);
	wbkgd(pHandler,COLOR_PAIR(2));
	wrefresh(pHandler);
}
void CComponent::GetFocus()
{
	curs_set(1);
	wbkgd(pHandler,COLOR_PAIR(3));
	wrefresh(pHandler);
}

int CComponent::GetStartX()
{
	return iStartX;
}
CActionListener *CComponent::GetAction()
{
	return action;
}
//////////////////////////////////////////

CActionListener::CActionListener(CComponent *owner)
{
	this->owner=owner;
}


CComponent *CActionListener::GetOwner()
{
	return owner;
}

