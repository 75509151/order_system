#ifndef __CEDIT_20140515_H_
#define __CEDIT_20140515_H_
#include "CComponent.h"
class CEdit:public CComponent
{
public:
	CEdit(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,bool isPwd,int iMaxLen);
	//~CEdit();
	void Show();
	int KeyListener();
	char *GetContent();
	void SetContent(char *pContent);
private:
	bool isPwd;
	char *pContent;
	//是否要文字类型
	int iMaxLen;
};

#endif