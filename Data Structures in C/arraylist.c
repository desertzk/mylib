#include"arraylist.h"
#include<stdio.h>
#include<stdlib.h>
#define EXTEND 32

ArrayList * InitArrayList(int size)
{
	if (size < 0)
	{
		return NULL;
	}
	ArrayList *plist = calloc(1,sizeof(ArrayList));
	plist->capacity = size;
	plist->pelem = calloc(1,sizeof(Element)*plist->capacity);
	return plist;
}

int DestroyArrayList(ArrayList *plist)
{
	if (!plist)
	{
		return ERROR;
	}
	ClearArrayList(plist);
	free(plist);
	return SUCCESS;
}

int ClearArrayList(ArrayList *plist)
{
	if (!plist)
	{
		return ERROR;
	}
	if (plist->pelem)
		free(plist->pelem);
	return 0;
}

int IsArrayListEmpty(ArrayList *plist)
{
	if (!plist)
		return ERROR;
	return  plist->length == 0 ? TRUE : FALSE;
}


Element ArrayListGetElementByIndex(ArrayList *plist, int index)
{
	if (!plist || index >= plist->length)
		return NULL;

	//Element elem = (Element)plist->elem + index;
	return plist->pelem[index];
}

int ArrayListGetElement(ArrayList *plist, Element elem, compare comparefunc)
{
	for (int i = 0; i < plist->length; ++i)
	{
		if (comparefunc(elem, plist->pelem[i])==0)//void *实际上是指针也就是一个int值
		{
			return i;
		}
	}
	return -1;//没找到
}



int ArrayListInsert(ArrayList *plist, int index, Element elem)
{
	if (!plist || index<0 || !elem)
	{
		return ERROR;
	}
	if (index <= plist->capacity)
	{
		plist->pelem[index] = elem;
		plist->length++;
	}
	else{
		int *oldpelem = plist->pelem;
		int oldcapacity = plist->capacity;
		plist->capacity += EXTEND;
		plist->pelem=realloc(plist->pelem, plist->capacity + sizeof(Element));
		for (int i = 0; i < oldcapacity; i++)//把原来的项全部拷贝过来
		{
			plist->pelem[i]=oldpelem[i];
		}
		plist->pelem[oldcapacity] = elem;
		plist->length = oldcapacity;
	}
}


int ArrayListAdd(ArrayList *plist, Element elem)
{
	ArrayListInsert(plist, plist->length, elem);
}

Element ArrayListDelete(ArrayList *plist, int index)
{
	if (!plist || index < 0)
	{
		return ERROR;
	}
	Element old = plist->pelem[index];
	for (int i = index; i < plist->length; i++)
	{
		plist->pelem[index] = plist->pelem[index + 1];
	}
	plist->length--;
	return old;
}

Element ArrayListDeleteLast(ArrayList *plist)
{
	ArrayListDelete(plist, plist->length);
}

int ArrayListTraverse(ArrayList *plist, foreachop opfunc)
{

}

int Capacity(ArrayList *plist)
{
	if (!plist)
	{
		return ERROR;
	}
	return plist->capacity;
}

