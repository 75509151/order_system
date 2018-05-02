#include "CComponent.h"
#ifndef _CUsr_AC_20140604_H_
#define _CUsr_AC_20140604_H_
/*************************************
	查询按钮事件
***************************************/
class CUsr_SearAC :public CActionListener
{
public:
	CUsr_SearAC(CComponent *owner);
	void DoAction();
protected:
private:
};

/*************************************
		修改事件
***************************************/

class CUsr_UpdateAC:public CActionListener
{
public:
	CUsr_UpdateAC(CComponent *owner);
	void DoAction();
protected:
private:
};
/************************************
		添加事件
************************************/
class CUsr_AddAC:public CActionListener
{
	public:
		CUsr_AddAC(CComponent *owner);
		void DoAction();
};
/************************************
		删除事件
************************************/
class CUsr_DelAC:public CActionListener
{
	public:
		CUsr_DelAC(CComponent *owner);
		void DoAction();
};

/************************************
		权限事件
***************************************/

class  CUsr_PermissAC:public CActionListener
{
public:
	CUsr_PermissAC(CComponent *owner);
	void DoAction();
protected:
private:
};


/************************************
		 确定添加按钮
************************************/
class CUsr_AddOKAC:public CActionListener
{
public:
	CUsr_AddOKAC(CComponent *owner);
	void DoAction();
protected:
private:
};


/************************************
		 确定修改按钮
************************************/
class CUsr_UpdateOKAC:public CActionListener
{
public:
	CUsr_UpdateOKAC(CComponent *owner);
	void DoAction();
protected:
private:
};



/************************************
		返回事件
************************************/
class CBackAC:public CActionListener
{
public:
	CBackAC(CComponent *owner);
	void DoAction();
protected:
private:
};


#endif