/*class CButton:public CComponent
{
public:
CButton(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,char *pName);
~CButton();
void Show();
protected:
private:

  };
*/

#include "CButton.h"
#include <unistd.h>

CButton::CButton(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,char *pName)
	:CComponent(cOwner,iStartY,iStartX,iHeight,iWidth,true)
{

	this->pName=new char[strlen(pName)+1];
	strcpy(this->pName,pName);
}

void CButton::Show()
{
	wbkgd(pHandler,COLOR_PAIR(2));
	//box(pHandler,0,0);
	mvwprintw(pHandler,1,(iWidth-strlen(pName))/2,"%s",pName);
	wrefresh(pHandler);
}
int CButton::KeyListener()
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
			mvwin(pHandler,iStartY+1,iStartX+1);
			wrefresh(pHandler);
		
			usleep(200000);
			
			wbkgd(pHandler,COLOR_PAIR(4));
			wrefresh(pHandler);
			mvwin(pHandler,iStartY,iStartX);
		
			action->DoAction();//Ö´ÐÐ¶¯×÷
		return 0;
		}
	} while(1);
	
}

void CButton::LoseFocus()
{
	curs_set(0);
	wbkgd(pHandler,COLOR_PAIR(2));
	wrefresh(pHandler);
}
void CButton::GetFocus()
{
	curs_set(0);
	wbkgd(pHandler,COLOR_PAIR(3));
	wrefresh(pHandler);
}