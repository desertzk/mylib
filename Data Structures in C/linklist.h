#ifndef __LIST_H__
#define __LIST_H__
#include"def.h"
typedef void * Element;

//我这个链表比一般的链表多加了随机位置插入的功能,下标以0开始

typedef struct tLinkListNode
{
	Element elem;
	struct tLinkListNode *next;
}LinkListNode;

typedef struct tLinkList
{
	int length;
	LinkListNode *header; //头结点
	LinkListNode *current; //链表最后一个结点
}LinkList;



typedef int(*compare)(Element elem1, Element elem2);

typedef int(*foreachop)();

LinkList * InitLinkList();

int DestroyLinkList(LinkList *plist);

int ClearLinkList(LinkList *plist);

int IsLinkListEmpty(LinkList *plist);

int Length(LinkList *plist);

Element GetElementByIndex(LinkList *plist, int index);

int GetElement(LinkList *plist, Element elem, compare);

LinkListNode * PriorNode(LinkList *plist, LinkListNode *);

LinkListNode * NextNode(LinkList *plist, LinkListNode *);
//Appends the specified element to the end of this list 
int Add(LinkList *plist, Element elem);
//我这个链表比一般的链表多加了随机位置插入的功能
int Insert(LinkList *plist, int index, Element elem);

Element Delete(LinkList *plist, int index);

Element DeleteLast(LinkList *plist);

int LinkListTraverse(LinkList *plist, foreachop);




#endif