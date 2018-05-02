/*class CEdit:public CComponent
{
public:
	CEdit(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,char *pName,bool isPwd,int iMaxLen);
	~CEdit();
	void Show();
protected:
private:
	bool isPwd;
	char *pContent;
	//是否要文字类型
	int iMaxLen;
};*/
#include "CEdit.h"
CEdit::CEdit(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth,bool isPwd,int iMaxLen)
	:CComponent(cOwner,iStartY,iStartX,iHeight,iWidth,true)
{
	this->isPwd=isPwd;
	this->iMaxLen=iMaxLen;
	this->pContent=new char[iMaxLen+1];
	memset(pContent,0,iMaxLen+1);
}

void CEdit::Show()
{
	wbkgd(pHandler,COLOR_PAIR(2));
	mvwprintw(pHandler,1,1,"%s",pContent);
	//box(pHandler,0,0);
	wrefresh(pHandler);
}


int CEdit::KeyListener()
{
	int iKey=0;
	int iCount=strlen(pContent);
	keypad(this->GetHandler(),TRUE);
	wmove(this->GetHandler(),1,strlen(pContent)+1);
	
	do 
	{
		iKey=wgetch(this->GetHandler());
		if (KEY_UP==iKey)
		{
			return KEY_UP;
		}
		else if (KEY_DOWN==iKey)
		{
			return KEY_DOWN;
		}
		else if (KEY_LEFT==iKey)
		{
			return KEY_LEFT;
		}
		else if (KEY_RIGHT==iKey)
		{
			return KEY_RIGHT;
		}

		if (iCount>0)
		{
			if (KEY_BACKSPACE==iKey)
			{
				--iCount;
				*(pContent+iCount)='\0';
				wprintw(this->GetHandler(),"\b \b");//删除
				continue;
			}
		}
		if (KEY_BACKSPACE==iKey)
		{
			continue;
		}
		else if ('\b'==iKey||'\n'==iKey)//table或者回车键
		{	
			*(pContent+iCount)='\0';
			return KEY_DOWN;
		}
		if (iMaxLen==iCount)
		{
			continue;
		}
		//只能是数字和字母之类的可以输出
		if (iKey>='a'&&iKey<='z'||iKey>='A'&&iKey<='Z'||iKey>='0'&&iKey<='9')
		{
			if (true==isPwd)
			{
				wprintw(this->GetHandler(),"*",iKey);
			}
			else
			{
				wprintw(this->GetHandler(),"%c",iKey);
			}
			*(pContent+iCount)=iKey;
			wrefresh(this->GetHandler());
			iCount++;
		}

	} while(1);

}

char *CEdit::GetContent()
{
	return pContent;
}

void CEdit::SetContent(char *sContent)
{
	delete pContent;
	this->pContent=new char[strlen(sContent)+1];
	strcpy(this->pContent,sContent);
}