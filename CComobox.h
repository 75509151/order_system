#ifndef _combox_20140606_h_
#define _combox_20140606_h_

#include "CComponent.h"
#include "list2.h"
#include "CLable.h"
#include "CButton.h"
/*****************************************
			œ¬¿≠øÚ¿‡
*******************************************/
class CCombox:public CComponent
{
public:
	CCombox(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,char *pContent);
	void Show();
	void ChildShow();
	void Flush();
	int KeyListener();
	void ChildSelect();
	_P_DOUBLELIST_T list_Head;
	char *GetContent();
protected:
private:
	
	CLable infolable;
	CLable flaglable;
};
#endif