#include<stdio.h>
#include<stdlib.h>
#include"linklist.h"
#include"queue.h"
void PrintList(LinkList * plist)
{
	LinkListNode *tmp = plist->header;
	for (int i = 0; i < plist->length; i++)
	{
		printf("%d", tmp->elem);
		tmp = tmp->next;
	}
	printf("\n");
}

void mainlist(){
	LinkList *plist = InitLinkList();
	Add(plist, 1);
	Add(plist, 2);
	Add(plist, 3);
	Add(plist, 4);
	Add(plist, 5);
	Insert(plist, 2, 8);
	Insert(plist, 6, 10);

	
	PrintList(plist);


	Delete(plist, 2);
	Delete(plist, 9);
	DeleteLast(plist);
	PrintList(plist);

	system("pause");
}

void PrintQueue(Queue * plist)
{
	QueueNode *tmp = plist->headnode;
	for (int i = 0; i < plist->size; i++)
	{
		printf("%d", tmp->elem);
		tmp = tmp->next;
	}
	printf("\n");
}


void main(){
	Queue *plist = InitQueue();
	Push(plist, 1);
	Push(plist, 2);
	Push(plist, 3);
	Push(plist, 4);
	Push(plist, 5);
	Push(plist, 8);
	Push(plist, 10);


	PrintQueue(plist);
	printf("%d\n", front(plist));

	Pop(plist);
	printf("%d\n", front(plist));
	Pop(plist);
	printf("%d\n", front(plist));
	Pop(plist);
	
	PrintQueue(plist);

	system("pause");
}