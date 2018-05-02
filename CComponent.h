#ifndef _CCOMPONENT_20140514_H_
#define _CCOMPONENT_20140514_H_

#include <string.h>
#include <ncurses.h>


 class CComponent; //声明类

/******************************************************
		************事件基类***********
 ******************************************************/
class CActionListener
{
public:
	CActionListener(CComponent *owner);
	CComponent *GetOwner();
	virtual void DoAction()=0;
protected:
	CComponent *owner;
private:
	
};



/******************************************************
		************组件基类***********
 ******************************************************/
 class CComponent
{
public:
	
	CComponent(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,bool hasFoucs=false);
	virtual ~CComponent();
	virtual void Show()=0;
	bool IsFocus();
	WINDOW *GetHandler();
	virtual int KeyListener();
	virtual void GetFocus();
	virtual void LoseFocus();
	virtual void AddKeyActionListener(CActionListener *action);
	CComponent *cOwner;
	int GetStartX();
	int iStartY;
	int iHeight;
	int iWidth;
	
	int iStartX;
	CActionListener *GetAction();
protected:
	
	WINDOW *pHandler;
	char *pName;

	CActionListener *action;
private:
	bool isFocus;
};


#endif
