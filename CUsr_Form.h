


#ifndef _cusr_form_20140604_h_
#define _cusr_form_20140604_h_
#include "CComponent.h"
#include "CForm.h"
/*class CUsr_Form : public CForm
{
public:
	CUsr_Form();
	//ע������
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
			�û���ӽ���
***************************************/
class CUsr_AddForm:public CForm
{
public:
	CUsr_AddForm(CComponent *owner);
	char *acId;			//ID
	char *acDepartment;//����
	char *acAccount;	//�ʺ�
	char *acRole;		//��ɫ
	char *acName;		//����
	char *acPsw;		//����
	char *acPswCheck;  //��֤����
	char *acBeizhu;		//��ע
		char *acType;		//�û�����
protected:
private:

};


class  CUsr_UpdateForm:public CForm
{
public:
	CUsr_UpdateForm(CComponent *owner);
	char *acId;			//ID
	char *acDepartment;//����
	char *acAccount;	//�ʺ�
	char *acRole;		//��ɫ
	char *acName;		//����
	char *acPsw;		//����
	char *acPswCheck;  //��֤����
	char *acBeizhu;		//��ע
		char *acType;		//�û�����
protected:
private:
};

/**********************************
			Ȩ�����ý���
***********************************/
class CUsr_PermissForm:public CForm
{
public:
	CUsr_PermissForm(CComponent *owner);
	char *acId;			//ID
	char *acDepartment;//����
	char *acAccount;	//�ʺ�
	char *acRole;		//��ɫ


//	int KeyListener();
//	void PermissShow(char *iRole_ID);
protected:
private:
};

#endif