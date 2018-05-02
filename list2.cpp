#include "list2.h"
#include <stdlib.h>
#include "CComponent.h"
//�����ʼ��
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
//�ڵ��ʼ��

//����ĩβ׷��
_P_DOUBLENODE_T List_AddT(_P_DOUBLELIST_T head,void* data)//ĩβ��������
{
	_P_DOUBLENODE_T new_Node;
	
	if (0==head)				//���ͷ�ڵ�Ϊ��
	{
		return NULL;
	}
	if (NULL==head->pHead)		//��һ�����
	{
		new_Node=(_P_DOUBLENODE_T)malloc(sizeof(DOUBLELIST_T));//����һ���µĽڵ�
		new_Node->pData=data;									//�ڵ��������ָ������

		new_Node->pPre=new_Node;		//�½ڵ��Ϊβ�ڵ�
		new_Node->pNext=new_Node;
		
		head->pHead=new_Node;		//�׽ڵ㸳ֵ
		head->pTail=new_Node;		//β���ı�
		head->iLen++;
		return new_Node;
	}
	else
	{
		new_Node=(_P_DOUBLENODE_T)malloc(sizeof(DOUBLELIST_T));//����һ���µĽڵ�
		new_Node->pData=data;									//�ڵ��������ָ������
		
		//����ĩβ
		//ĩβ�ĺ�һ��ָ��ָ����
		head->pTail->pNext=new_Node;
		head->pHead->pPre=new_Node;
		//�¼����ָ�����޸�
		new_Node->pPre=head->pTail;
		new_Node->pNext=head->pHead;

	

		head->pTail=new_Node;		//β���ı�
		head->iLen++;
		return new_Node;
	}
	
}

//�����ͷ�//δ��ɰ�//��Ϊ��������Ķ���û���ͷ�
//Ӧ�ô��뺯��ָ�����delete,����free;
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


//������λ���
/*_P_DOUBLENODE_T List_AddH(_P_DOUBLELIST_T head,void* data)//ͷ����������
{
	_P_DOUBLENODE_T new_Node;
	
	if (0==head)				//���ͷ�ڵ�Ϊ��
	{
		return NULL;
	}
	new_Node=(_P_DOUBLENODE_T)malloc(sizeof(DOUBLELIST_T));//����һ���µĽڵ�
	new_Node->pData=data;									//�ڵ��������ָ������

	new_Node->pPre=head->pTail;
	new_Node->pNext=head->pHead;	//�½ڵ��Ϊ�׽ڵ�
	
	head->pHead=new_Node;		//�׽��ı�
	head->iLen++;
	return new_Node;
}*/
