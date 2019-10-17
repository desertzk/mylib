#include"linklist.h"
#include<stdio.h>
#include<stdlib.h>

LinkList * InitLinkList()
{
	LinkList *plist = calloc(1,sizeof(LinkList));
	return plist;
}

int DestroyLinkList(LinkList *plist)
{
	ClearLinkList(plist);
	free(plist);
	return ERROR;
}

int ClearLinkList(LinkList *plist)
{
	if (plist == NULL)
	{
		return -1;
	}
	for (int i = 0; i < plist->length; i++)
	{
		DeleteLast(plist);
	}
	return 0;
}

int IsLinkListEmpty(LinkList *plist)
{
	return plist->header == NULL ? TRUE : FALSE;
}

int Length(LinkList *plist)
{
	return plist->length;
}

Element GetElementByIndex(LinkList *plist, int index)
{
	if (NULL == plist||index > plist->length)
	{
		return NULL;
	}
	LinkListNode *cur = plist->header;
	for (int i = 0; i < index; i++)
	{
		cur = cur->next;
	}
	return cur->elem;
}

int GetElement(LinkList *plist, Element elem, compare cmpfunc)
{
	if (plist == NULL || elem == NULL || cmpfunc == NULL)
		return -1;
	for (int i = 0; i < plist->length; i++)
	{
		if (!cmpfunc(elem, plist->current->elem))
		{
			return i;
		}
	}
	return -1;
}

LinkListNode * PriorNode(LinkList *plist, LinkListNode *node)
{
	/*if (plist || node)
		return NULL;*/

}

LinkListNode * NextNode(LinkList *plist, LinkListNode *node)
{
	return node->next;
}

//Appends the specified element to the end of this list 
int Add(LinkList *plist, Element elem)
{
	if (plist == NULL || elem == NULL)
	{
		return -1;
	}

	//first node
	if (plist->header == NULL)
	{
		plist->header = malloc(sizeof(LinkListNode));
		plist->header->elem = elem;
		plist->header->next = NULL;

		plist->current = plist->header;
		plist->length++;
		return 0;
	}


	while (plist->current->next == NULL)
	{
		//new node
		plist->current->next = malloc(sizeof(LinkListNode));
		plist->current->next->elem = elem;
		plist->current->next->next = NULL;
	}
	plist->current = plist->current->next;
	plist->length++;

	return 0;
}

//
int Remove(LinkList *plist, Element elem, compare cmpfunc)
{
	if (plist == NULL || elem == NULL || cmpfunc == NULL)
	{
		return -1;
	}
	LinkListNode *current = plist->header;
	LinkListNode *prenode = NULL;
	/**/while (current->next != NULL)
	{
		if (!cmpfunc(current->elem, elem))
		{
			break;
		}
		prenode = current;
		current = current->next;
	}
	if (plist->header == current)//first
	{
		//Element oldelem = plist->header;
		free(plist->header);
		plist->header = plist->current = NULL;
		plist->length = 0;
		return 0;
	}
	prenode->next = current->next;
	free(current);
	plist->length--;
	return 0;
	/*for (int i = 0; i < plist->length; ++i)
	{
		if (!cmpfunc(current->elem, elem))
		{
			break;
		}
	}*/


}

//insert in index place
int Insert(LinkList *plist, int index, Element elem)
{
	if (plist == NULL || elem == NULL || index<=0)
	{
		return -1;
	}
	if (index >= plist->length)
	{
		return Add(plist, elem);
	}

	LinkListNode *current = plist->header;
	for (int i = 0; i < index; i++)
	{
		current=current->next;
	}

	LinkListNode *newNode = malloc(sizeof(LinkListNode));
	newNode->elem = elem;
	newNode->next = current->next;

	current->next = newNode;
	plist->length++;
	return 0;
}

Element DeleteLast(LinkList *plist)
{
	LinkListNode *prenode = plist->header;
	//for (int i = 0; i < plist->length - 1; i++)
	while (prenode->next->next!=NULL)
	{
		prenode = prenode->next;
	}
	//循环到最后一个结点的前一个结点
	//if(prenode->next == NULL)/**/
	if (prenode->next == NULL)
	{
		return NULL;
	}
		
		
	Element elem = prenode->next->elem;
	free(prenode->next);
	plist->current = prenode;
	plist->length--;
	return elem;
}


Element Delete(LinkList *plist, int index)
{
	if (plist == NULL || index <= 0)
	{
		return NULL;
	}
	if (index >= plist->length)//delete last node
	{
		index = plist->length;
		return DeleteLast(plist);
	}
	//delete first node
	else if (index == 0)
	{
		if (plist->header == plist->current)//只有一个结点
		{
			Element oldelem = plist->header;
			free(plist->header);
			plist->header = plist->current = NULL;
			plist->length = 0;
			return oldelem;
		}
		LinkListNode *current = plist->header;//暂存要删除的结点
		plist->header = current->next;//跳过那个
		Element oldelem = current->elem;
		if (current != NULL)
			free(current);
		plist->length--;
		return oldelem;
	}

	

	LinkListNode *prenode = plist->header;
	//plist
	for (int i = 0; i < index-1; i++)
	{
		prenode = prenode->next;//这个其实是要删除的上一个
	}
	//delete
	LinkListNode *current = prenode->next;
	prenode->next = current->next;//跳过那个
	Element oldelem = current->elem;
	if (current != NULL)
		free(current);
	plist->length--;
	return oldelem;
}

int LinkListTraverse(LinkList *plist, foreachop foreachopfunc)
{

}
