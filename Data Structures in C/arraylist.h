#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__
#include"def.h"
typedef void*  Element;

//����������һ��������������λ�ò���Ĺ���,�±���0��ʼ

//typedef struct tArrayListNode
//{
//	Element elem;
//	struct tArrayListNode *next;
//}ArrayListNode;

typedef struct tArrayList
{
	unsigned int * pelem;//�����׵�ַ//void *ʵ������ָ��Ҳ����һ��intֵ
	int length;//��ǰλ��
	int capacity;//����
}ArrayList;



typedef int(*compare)(Element elem1, Element elem2);

typedef int(*foreachop)();

ArrayList * InitArrayList(int size);

int DestroyArrayList(ArrayList *plist);

int ClearArrayList(ArrayList *plist);

int IsArrayListEmpty(ArrayList *plist);

//int Length(ArrayList *plist);
int Capacity(ArrayList *plist);


Element ArrayListGetElementByIndex(ArrayList *plist, int index);

int ArrayListGetElement(ArrayList *plist, Element elem, compare);

//ArrayListNode * PriorNode(ArrayList *plist, ArrayListNode *);
//
//ArrayListNode * NextNode(ArrayList *plist, ArrayListNode *);

int ArrayListAdd(ArrayList *plist, Element elem);
//����������һ��������������λ�ò���Ĺ���
int ArrayListInsert(ArrayList *plist, int index, Element elem);

Element ArrayListDelete(ArrayList *plist, int index);

Element ArrayListDeleteLast(ArrayList *plist);

int ArrayListTraverse(ArrayList *plist, foreachop);




#endif