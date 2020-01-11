#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	Item elem;
	struct QueueNode *next;
}QueueNode;

typedef QueueNode TcelQ;
typedef QueueNode *ACelQ;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	long size;
}Queue;

typedef Queue TCoada;
typedef Queue *AQ;


Queue* createQueue(void){
	// TODO: Cerinta 2
	Queue *q = (Queue *) malloc(sizeof(Queue));
	q->front = NULL;
	q->rear = NULL;
	q->size = 0; 
	return q;
} 

int isQueueEmpty(Queue *q){
	// TODO: Cerinta 2
	if (q->front == NULL) {
		return 1;
	}
	return 0;
}

void enqueue(Queue *q, Item elem){
	// TODO: Cerinta 2
	q->size += 1;
	QueueNode *node = (QueueNode *) malloc(sizeof(QueueNode));
	node->elem = elem;
	node->next = NULL;
	if (isQueueEmpty(q)) {
		q->front = node;
		q->rear = node;
		return;
	}
	q->rear->next = node;
	q->rear = node;
}

Item front(Queue* q){
	// TODO: Cerinta 2
	return q->front->elem;
}

void dequeue(Queue* q){
	// TODO: Cerinta 2
	if (isQueueEmpty(q)) {
		return;
	}
	q->size -= 1;
	QueueNode *aux = q->front;
	q->front = q->front->next;
	if (q->front == NULL) {
		q->rear = NULL;
	}
	free(aux);
}

void destroyQueue(Queue *q){
	// TODO: Cerinta 2
	while(!isQueueEmpty) {
		dequeue(q);
		
	}
	free(q);
}

#endif
