#ifndef _double_list_hh__
#define _double_list_hh__

typedef	struct DoubleNode_T{
	void * pData;		//������
	struct DoubleNode_T *pPre;//ָ��ǰһ���ڵ�
	struct DoubleNode_T *pNext;//ָ���һ���ڵ�
}DOUBLENODE_T,*_P_DOUBLENODE_T;


typedef struct DoubleList_T{
	int iLen;				//������
	_P_DOUBLENODE_T pHead;	//�׸��ڵ�ָ��
	_P_DOUBLENODE_T pTail;	//���һ���ڵ�ָ��

}DOUBLELIST_T,*_P_DOUBLELIST_T;

//�����ʼ��
_P_DOUBLELIST_T List_Init();

//****************�������ӽڵ�******************

_P_DOUBLENODE_T List_AddT(_P_DOUBLELIST_T head,void* data);//ĩβ��������

void List_Free(_P_DOUBLELIST_T head);//�����ͷţ�δ��ɰ�
//_P_DOUBLENODE_T List_AddH(_P_DOUBLELIST_T head,void* data);//ͷ����������

//****************����ɾ���ڵ�******************

//****************�����޸Ľڵ�******************

//****************�����ѯ�ڵ�******************

//****************�������***********************

#endif