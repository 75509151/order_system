#ifndef __Loginaction_20140516_h__
#define __Loginaction_20140516_h__

#include "CComponent.h"

class CLoginAction:public CActionListener
{
public:
	CLoginAction(CComponent *owner);
	void DoAction();
protected:
private:
};

class CMenu_UsrAc:public CActionListener
{
public:
	CMenu_UsrAc(CComponent *owner);
	void DoAction();
protected:
private:
};
#endif