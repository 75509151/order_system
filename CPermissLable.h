#ifndef __cpermiss_20140612_h_
#define	__cpermiss_20140612_h_

#include "CComponent.h"
class CPermissLable:public CComponent
{
public:
	CPermissLable(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,bool hasBox/*,char *whatshow*/);

	void Show();
	char *whatshow;
protected:
private:
	
	bool hasBox;
};

#endif
