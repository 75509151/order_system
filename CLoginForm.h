#ifndef __CLoginForm_20140515_h__
#define __CLoginForm_20140515_h__
#include "CForm.h"
#include "CComponent.h"

class CLoginForm :public CForm
{
public:
	CLoginForm(CComponent *owner);
	char *GetName();
	char *GetPsw();
private:
	char *acName;
	char *acPsw;
};

#endif