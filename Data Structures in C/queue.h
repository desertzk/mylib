#pragma once
#include<stdio.h>
#include"def.h"
typedef void * Element;


typedef struct queuenode
{
	Element elem;
	struct queuenode *next;
}QueueNode;

typedef struct queue 
{
	QueueNode *headnode;
	QueueNode *currentnode;
	int size;
}Queue;



int isEmpty(Queue *q);

Queue *InitQueue();

int DestroyQueue(Queue *q);

int Size(Queue *q);

Element front(Queue *q);

int Pop(Queue *q);

QueueNode *CreateNode(Element e);


int Push(Queue *q, Element e);

