


#ifndef _cusr_form_20140604_h_
#define _cusr_form_20140604_h_
#include "CComponent.h"
#include "CForm.h"
/*class CUsr_Form : public CForm
{
public:
	CUsr_Form();
	//注意析构
protected:
private:
};*/

char *User_GetMaxId();


class CUsr_Form:public CForm
{
public:
	CUsr_Form(CComponent *owner);
	CForm *pInfoForm;
	int KeyListener();
	char *GetName();
	char *GetAccount();
protected:
private:
	char *acName;
	char *acAccount;
};

/************************************
			用户添加界面
***************************************/
class CUsr_AddForm:public CForm
{
public:
	CUsr_AddForm(CComponent *owner);
	char *acId;			//ID
	char *acDepartment;//部门
	char *acAccount;	//帐号
	char *acRole;		//角色
	char *acName;		//姓名
	char *acPsw;		//密码
	char *acPswCheck;  //验证密码
	char *acBeizhu;		//备注
		char *acType;		//用户类型
protected:
private:

};


class  CUsr_UpdateForm:public CForm
{
public:
	CUsr_UpdateForm(CComponent *owner);
	char *acId;			//ID
	char *acDepartment;//部门
	char *acAccount;	//帐号
	char *acRole;		//角色
	char *acName;		//姓名
	char *acPsw;		//密码
	char *acPswCheck;  //验证密码
	char *acBeizhu;		//备注
		char *acType;		//用户类型
protected:
private:
};

/**********************************
			权限设置界面
***********************************/
class CUsr_PermissForm:public CForm
{
public:
	CUsr_PermissForm(CComponent *owner);
	char *acId;			//ID
	char *acDepartment;//部门
	char *acAccount;	//帐号
	char *acRole;		//角色


//	int KeyListener();
//	void PermissShow(char *iRole_ID);
protected:
private:
};

#endif