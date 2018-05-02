#ifndef __lable_20140515_H__
#define __lable_20140515_H__
#include "CComponent.h"

class CLable:public CComponent
{
public:
	CLable(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,char *pName,bool hasBox);
	CLable(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,char *pName,bool hasBox,bool isFocus);
	//~CLable();
	void Show();
	void SetContent(char *sContent);
	char *GetContent();
	int KeyListener();
private:
	bool hasBox;
	char *pName;
	
};

#endif