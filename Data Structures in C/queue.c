#include"queue.h"

int isEmpty(Queue *q)
{
	return q->size == 0;
}

Queue *InitQueue()
{
	Queue *q = calloc(1, sizeof(Queue));
	
	return q;
}

int DestroyQueue(Queue *q)
{
	QueueNode *deletenode=NULL; 
	for (deletenode = q->headnode; deletenode; deletenode = deletenode->next)
	{
		free(deletenode);
	}
	return 0;
}

int Size(Queue *q)
{
	return q->size;
}

Element front(Queue *q)
{
	return q->headnode->elem;
}

int Pop(Queue *q)
{
	int ret = 0;
	QueueNode *deletenode = q->headnode;
	q->headnode = q->headnode->next;
	if (deletenode)
		free(deletenode);
	--q->size;
	return ret;
}

QueueNode *CreateNode(Element e)
{
	QueueNode *newnode = malloc(sizeof(QueueNode));
	if (newnode == NULL)
	{
		printf("malloc error");
		return NULL;
	}
	newnode->elem = e;
	newnode->next = NULL;
	return newnode;
}


int Push(Queue *q,Element e)
{
	QueueNode *newnode = CreateNode(e);
	
	//first time
	if (q->headnode == NULL)
	{
		q->headnode = newnode;	
		q->currentnode = newnode;
		++q->size;
		return SUCCESS;
	}
	//not first time
	q->currentnode->next = newnode;
	q->currentnode = newnode;
	++q->size;
	return SUCCESS;
}
