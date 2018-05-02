#include "CInfoForm.h"
#include "CLable.h"
#include "CButton.h"
#include "CSinDB.h"
#include "CUsr_DB.h"

CInfoForm::CInfoForm(CComponent *cOwner,int iStartY,int iStartX,int iHeight,int iWidth):CForm(cOwner,iStartY,iStartX,iHeight,iWidth)
{

	memset(sSql,'\0',sizeof(sSql));
	memset(sSql,'\0',sizeof(sSqlCount));
	pInfoLab=NULL;
	iPage=0;
	Count_CallBack=NULL;
	Show_CallBack=NULL;
}
char *CInfoForm::GetSql(char *sSqlAll)
{
	char sTemp[1024]={0};
	char *pEnd=strstr(sSqlAll,"limit");//pEnd记录sql语句中limit的起始位置
	if (NULL==pEnd)
	{
	
	}
	else
	{
		strncpy(sTemp,sSqlAll,pEnd-sSqlAll);  //将limit之前的字符赋予sql

	}
	return sTemp;
}

int CInfoForm::KeyListener()
{
	int iKey;
	int iTatolPage=0;
	char sTmp[1024]={0};
	char sNowSql[1024]={0};
	CSinDB *pDB=CSinDB::GetSinDB();
	strcpy(sTmp,GetSql(sSql));
	



	//遍历到可以接收按钮的第一个
	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)list_Head->pHead;
	iTatolPage=CountPage(iTotal,5);			//得到总页数
	if (NULL==currNode)
	{
		return 2222;
	}
	pInfoLab=(CComponent *)currNode->pData;
	this->Show();

	//根据不同的按键进行动作
	while (1)
	{
		wmove(pInfoLab->GetHandler(),1,1);
		wrefresh(pInfoLab->GetHandler());
		keypad(pInfoLab->GetHandler(),TRUE);
		//获取焦点
		pInfoLab->GetFocus();
		iKey=pInfoLab->KeyListener();
	
		this->Show();
		wrefresh(pInfoLab->GetHandler());
		pDB->DoOpera(sSqlCount,Count_CallBack,this);   //计数
		iTatolPage=CountPage(iTotal,5);			//得到总页数
		switch(iKey)
		{
		case KEY_UP:
			{
			//	this->Show();
				pInfoLab->LoseFocus();
				wrefresh(pInfoLab->GetHandler());
				currNode=currNode->pPre;
				pInfoLab=(CComponent *)currNode->pData;
		
				break;
			}
		case KEY_DOWN:
			{
				//this->Show();
				pInfoLab->LoseFocus();
				wrefresh(pInfoLab->GetHandler());
				currNode=currNode->pNext;
				pInfoLab=(CComponent *)currNode->pData;
			
				break;
			}
		case KEY_LEFT:

				pInfoLab->GetFocus();
				wrefresh(pInfoLab->GetHandler());
				return KEY_LEFT;

		case KEY_RIGHT:

				pInfoLab->GetFocus();
				wrefresh(pInfoLab->GetHandler());
				return KEY_RIGHT;
	
	
		case KEY_NPAGE:
			{

				if (iPage<iTatolPage)
				{
			
				//先释放原来的链表:
					iPage++;					

					Flash();  //为什么进入了却不起作用
					
					List_Free(this->list_Head);
					
					sprintf(sNowSql,"%s limit 5 offset %d",sTmp,(iPage)*5);
			
					pDB->DoOpera(sNowSql,Show_CallBack,this);//将信息窗体传入
					currNode=(_P_DOUBLENODE_T)list_Head->pHead;//链表的首节点改为现在查询到的第一个
		  			pInfoLab=(CComponent *)currNode->pData;	
					this->Show();

					
				}
				else 
				{
					printf("   到达最后一页       到达最后一页");
					
				}
			

				break;
			}
			
			case KEY_PPAGE:	
				{

					if (iPage==0)
					{
					//提示第一页
				//	iPage=iTatolPage;
					}
					else
					{		
					iPage--;
					Flash(); 
					
					List_Free(this->list_Head);
					sprintf(sNowSql,"%s limit 5 offset %d",sTmp,(iPage)*5);
			
					pDB->DoOpera(sNowSql,Show_CallBack,this);//将信息窗体传入
					
					currNode=(_P_DOUBLENODE_T)list_Head->pHead;//链表的首节点改为现在查询到的第一个
					pInfoLab=(CComponent *)currNode->pData;	
					this->Show();

					break;
					}
		
				
				}
		
		default:
			
			break;
			
		}
		
	}
	return 0;
}


void CInfoForm::Flash()
{
	CLable *pC=NULL;
	int iCount=0;

	_P_DOUBLENODE_T currNode=(_P_DOUBLENODE_T)this->list_Head->pHead;
	for(iCount;iCount<list_Head->iLen;iCount++)
	{
		pC=(CLable *)currNode->pData;
	wbkgd(pC->GetHandler(),COLOR_PAIR(4));
		wrefresh(pC->GetHandler());	
		currNode=currNode->pNext;
	}


	wclear(pHandler);			//为什么这两句都不能少
//	wbkgd(pHandler,COLOR_PAIR(4));
	wrefresh(pHandler);

}


char *CInfoForm::GetInfo()
{
	if (NULL==pInfoLab)
	{
		return NULL;
	}
	CLable *pInfoLable=(CLable *)pInfoLab;
	return pInfoLable->GetContent();
}

	/*************************************************
					计算页数
	*************************************************/
int CountPage(int iTotal,int iShowNum)
{
	int iTotalPage=0;
	int i;
	if (iTotal<=iShowNum)
	{
		return 0;
	}
	else 
	{
		i=iTotal%iShowNum;
		iTotalPage=iTotal/iShowNum;
		if (0==i)
		{
			return iTotalPage-1;
		}
		else
		{
			return iTotalPage;
		}

	}
	
}