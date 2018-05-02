#include "list2.h"
#include <stdlib.h>
#include "CComponent.h"
//链表初始化
_P_DOUBLELIST_T List_Init()
{
	_P_DOUBLELIST_T head=(_P_DOUBLELIST_T)malloc(sizeof(DOUBLELIST_T));
	if (0==head)
	{
		return 0;
	}
	head->iLen=0;
	head->pHead=NULL;
	head->pTail=NULL;
}
//节点初始化

//链表末尾追加
_P_DOUBLENODE_T List_AddT(_P_DOUBLELIST_T head,void* data)//末尾加入数据
{
	_P_DOUBLENODE_T new_Node;
	
	if (0==head)				//如果头节点为空
	{
		return NULL;
	}
	if (NULL==head->pHead)		//第一次添加
	{
		new_Node=(_P_DOUBLENODE_T)malloc(sizeof(DOUBLELIST_T));//产生一个新的节点
		new_Node->pData=data;									//节点的数据域指向数据

		new_Node->pPre=new_Node;		//新节点成为尾节点
		new_Node->pNext=new_Node;
		
		head->pHead=new_Node;		//首节点赋值
		head->pTail=new_Node;		//尾结点改变
		head->iLen++;
		return new_Node;
	}
	else
	{
		new_Node=(_P_DOUBLENODE_T)malloc(sizeof(DOUBLELIST_T));//产生一个新的节点
		new_Node->pData=data;									//节点的数据域指向数据
		
		//加入末尾
		//末尾的后一个指针指向新
		head->pTail->pNext=new_Node;
		head->pHead->pPre=new_Node;
		//新加入的指针域修改
		new_Node->pPre=head->pTail;
		new_Node->pNext=head->pHead;

	

		head->pTail=new_Node;		//尾结点改变
		head->iLen++;
		return new_Node;
	}
	
}

//链表释放//未完成版//因为我数据域的东西没有释放
//应该传入函数指针进行delete,或者free;
void List_Free(_P_DOUBLELIST_T head)
{
	_P_DOUBLENODE_T curr_Node=head->pHead;
	//CComponent	*Data;
	_P_DOUBLENODE_T	Data;
	_P_DOUBLENODE_T tmp_Node;
	int i=0;
	for (i=0;i<head->iLen;i++)
	{
		tmp_Node=curr_Node->pNext;
	//	Data=(CComponent *)curr_Node->pData;
	//	delete Data;
		Data=(_P_DOUBLENODE_T)curr_Node->pData;
		free(Data);
		free(curr_Node);
		curr_Node=tmp_Node;

	}
	head->iLen=0;
	head->pHead=NULL;
	head->pTail=NULL;
}


//链表首位添加
/*_P_DOUBLENODE_T List_AddH(_P_DOUBLELIST_T head,void* data)//头部加入数据
{
	_P_DOUBLENODE_T new_Node;
	
	if (0==head)				//如果头节点为空
	{
		return NULL;
	}
	new_Node=(_P_DOUBLENODE_T)malloc(sizeof(DOUBLELIST_T));//产生一个新的节点
	new_Node->pData=data;									//节点的数据域指向数据

	new_Node->pPre=head->pTail;
	new_Node->pNext=head->pHead;	//新节点成为首节点
	
	head->pHead=new_Node;		//首结点改变
	head->iLen++;
	return new_Node;
}*/
