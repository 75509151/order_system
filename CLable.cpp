/*
class CLable:public CComponent
{
public:
CLable(CComponent &cOwner,WINDOW &pHandler,int iStartY,int iStartX,int iHeight,int iWidth,char *pName,bool hasBox);
~CLable();
void Show();
protected:
private:
bool hasBox;
};
*/
#include "CLable.h"
#include "CForm.h"
CLable::CLable(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,char *pName,bool hasBox)
		:CComponent(cOwner,iStartY,iStartX,iHeight,iWidth)
{
	this->hasBox=hasBox;
	this->pName=new char[strlen(pName)+1];
	strcpy(this->pName,pName);
}

CLable::CLable(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,char *pName,bool hasBox,bool isFocus)
		:CComponent(cOwner,iStartY,iStartX,iHeight,iWidth,true)
{
	this->hasBox=hasBox;
	this->pName=new char[strlen(pName)+1];
	strcpy(this->pName,pName);
}
void CLable::SetContent(char *sContent)
{
	delete pName;
	this->pName=new char[strlen(sContent)+1];
	strcpy(this->pName,sContent);
}
char* CLable::GetContent()
{
	return pName;
}
void CLable::Show()
{

	if (TRUE==hasBox)
	{
	
	//	box(pHandler,0,0);
		wbkgd(pHandler,COLOR_PAIR(2));
		wrefresh(pHandler);//(iWidth-strlen(pName))/2
		mvwprintw(pHandler,1,(iWidth-strlen(pName))/2,"%s",pName);
		wrefresh(pHandler);
	}
	else
	{
		wbkgd(pHandler,COLOR_PAIR(2));
		mvwprintw(pHandler,1,(iWidth-strlen(pName))/2,"%s",pName);
		wrefresh(pHandler);
	}
}

int CLable::KeyListener()
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
		case KEY_PPAGE:
			return KEY_PPAGE;
		case KEY_NPAGE:
			return KEY_NPAGE;
		case '\n':
			return 0;
		}
	} while(1);
	
}