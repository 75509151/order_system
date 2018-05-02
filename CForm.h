#ifndef __CFORM_20140515_H_
#define __CFORM_20140515_H_
#include "CComponent.h"
#include "list2.h"


#define EXITFLAG 3333;
class CForm:public CComponent
{
public:
	CForm(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth);
	//~CForm();
	virtual	void Show();
	
	virtual	int KeyListener();
	void SetExit(bool isExit);
	_P_DOUBLELIST_T list_Head;
protected:
		bool isExit;
private:

	
};
#endif