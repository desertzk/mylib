#ifndef __LIST_H__
#define __LIST_H__
#include"def.h"
typedef void * Element;

//����������һ��������������λ�ò���Ĺ���,�±���0��ʼ

typedef struct tLinkListNode
{
	Element elem;
	struct tLinkListNode *next;
}LinkListNode;

typedef struct tLinkList
{
	int length;
	LinkListNode *header; //ͷ���
	LinkListNode *current; //�������һ�����
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
//����������һ��������������λ�ò���Ĺ���
int Insert(LinkList *plist, int index, Element elem);

Element Delete(LinkList *plist, int index);

Element DeleteLast(LinkList *plist);

int LinkListTraverse(LinkList *plist, foreachop);




#endif