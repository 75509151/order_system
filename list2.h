#ifndef _double_list_hh__
#define _double_list_hh__

typedef	struct DoubleNode_T{
	void * pData;		//数据域
	struct DoubleNode_T *pPre;//指向前一个节点
	struct DoubleNode_T *pNext;//指向后一个节点
}DOUBLENODE_T,*_P_DOUBLENODE_T;


typedef struct DoubleList_T{
	int iLen;				//链表长度
	_P_DOUBLENODE_T pHead;	//首个节点指针
	_P_DOUBLENODE_T pTail;	//最后一个节点指针

}DOUBLELIST_T,*_P_DOUBLELIST_T;

//链表初始化
_P_DOUBLELIST_T List_Init();

//****************链表增加节点******************

_P_DOUBLENODE_T List_AddT(_P_DOUBLELIST_T head,void* data);//末尾加入数据

void List_Free(_P_DOUBLELIST_T head);//链表释放，未完成版
//_P_DOUBLENODE_T List_AddH(_P_DOUBLELIST_T head,void* data);//头部加入数据

//****************链表删除节点******************

//****************链表修改节点******************

//****************链表查询节点******************

//****************链表遍历***********************

#endif