#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__
#include"def.h"
typedef void*  Element;

//我这个链表比一般的链表多加了随机位置插入的功能,下标以0开始

//typedef struct tArrayListNode
//{
//	Element elem;
//	struct tArrayListNode *next;
//}ArrayListNode;

typedef struct tArrayList
{
	unsigned int * pelem;//对象首地址//void *实际上是指针也就是一个int值
	int length;//当前位置
	int capacity;//容量
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
//我这个链表比一般的链表多加了随机位置插入的功能
int ArrayListInsert(ArrayList *plist, int index, Element elem);

Element ArrayListDelete(ArrayList *plist, int index);

Element ArrayListDeleteLast(ArrayList *plist);

int ArrayListTraverse(ArrayList *plist, foreachop);




#endif