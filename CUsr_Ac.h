#include "CComponent.h"
#ifndef _CUsr_AC_20140604_H_
#define _CUsr_AC_20140604_H_
/*************************************
	��ѯ��ť�¼�
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
		�޸��¼�
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
		����¼�
************************************/
class CUsr_AddAC:public CActionListener
{
	public:
		CUsr_AddAC(CComponent *owner);
		void DoAction();
};
/************************************
		ɾ���¼�
************************************/
class CUsr_DelAC:public CActionListener
{
	public:
		CUsr_DelAC(CComponent *owner);
		void DoAction();
};

/************************************
		Ȩ���¼�
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
		 ȷ����Ӱ�ť
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
		 ȷ���޸İ�ť
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
		�����¼�
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