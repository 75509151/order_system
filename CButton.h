#ifndef __CButton__20140515__h__
#define __CButton__20140515__h__
#include "CComponent.h"

class CButton:public CComponent
{
public:
	CButton(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,char *pName);
	//~CButton();
	void Show();
	int KeyListener();
	void GetFocus();
	void LoseFocus();
private:
	char *pName;
};

#endif

