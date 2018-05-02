#ifndef _menu_20140528_h_
#define _menu_20140528_h_

#include "CComponent.h"
#include "list2.h"
class CMenuBar:public CComponent
{
public:
	CMenuBar(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth);
	void Show();
	int KeyListener();


	void SetExit(bool isExit);
	static _P_DOUBLELIST_T list_Head;
protected:
	
private:
		int isExit;
	int flag;
};

class CMenu:public CComponent
{
public:
	CMenu(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,char *pName);

	void Show();
	int KeyListener();
//	void SetFlag(int flag);
	void LoseFocus();
	void GetFocus();
	_P_DOUBLELIST_T list_Head;
	char *pName;//到时改为私用
	void ActionFactory(char *id);

protected:
private:


};

#endif