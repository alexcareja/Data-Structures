#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

/* We assume there is a defined primitive type Item. */
typedef struct {
	int prior; // Item priority
	Item data; // Item d
}ItemType;

typedef struct heap{
	long maxHeapSize; // capacity
	long size; // number of elements
	ItemType *elem; // array of elements
} PriQueue, *APriQueue;


PriQueue* makeQueue(int maxHeapSize){
	//TODO:
	PriQueue *pq = (PriQueue *) malloc(sizeof(PriQueue));
	pq->maxHeapSize = maxHeapSize;
	pq->size = 0;
	pq->elem = (ItemType *) malloc(maxHeapSize * sizeof(ItemType));
	return pq;
}

int getLeftChild(int i){
	//TODO:
	return 2 * i + 1;
}

int getRightChild(int i) {
	//TODO:
	return 2 * i + 2;
}

int getParent(int i) {
	//TODO:
	return (i - 1) / 2;
}

ItemType getMax(APriQueue h) {
	//TODO:
	return h->elem[0];
}

void siftUp(APriQueue h, int idx) {
	//TODO:
	if(h->elem[getParent(idx)].prior > h->elem[idx].prior || idx == 0){
		return;
	}
	// schimb datele intre nodul curent si parintele lui
	Item aux1;
	int aux2;

	aux2 = h->elem[getParent(idx)].prior;
	h->elem[getParent(idx)].prior = h->elem[idx].prior;
	h->elem[idx].prior = aux2;

	aux1 = h->elem[getParent(idx)].data;
	h->elem[getParent(idx)].data = h->elem[idx].data;
	h->elem[idx].data = aux1;

	siftUp(h, getParent(idx));
}


void insert(PriQueue *h, ItemType x) {
	//TODO:
	if(h->size == h->maxHeapSize){	// daca coada e plina
		h->maxHeapSize *= 2;
		h->elem = realloc(h->elem, h->maxHeapSize * sizeof(ItemType));
	}
	if(h->size == 0){		// daca e primul element introdus
		h->elem[0].prior = x.prior;
		h->elem[0].data = x.data;
		h->size = 1;
		return;
	}
	h->elem[h->size] = x;
	//h->elem[h->size].rior = x.prior;
	//h->elem[h->size].data = x.data;
	siftUp(h, h->size);
	h->size++;


}

void siftDown(APriQueue h, int idx){
	//TODO:
	int l = getLeftChild(idx);
	int r = getRightChild(idx);
	if ((h->elem[idx].prior > h->elem[l].prior 
		&& h->elem[idx].prior > h->elem[r].prior)
		|| r > h->size) {
		return;
	}
	Item aux1;
		int aux2;
	if (h->elem[l].prior > h->elem[r].prior) {
		aux2 = h->elem[l].prior;
		h->elem[l].prior = h->elem[idx].prior;
		h->elem[idx].prior = aux2;

		aux1 = h->elem[l].data;
		h->elem[l].data = h->elem[idx].data;
		h->elem[idx].data = aux1;
		siftDown(h, l);
	}
	else {
		aux2 = h->elem[r].prior;
		h->elem[r].prior = h->elem[idx].prior;
		h->elem[idx].prior = aux2;

		aux1 = h->elem[r].data;
		h->elem[r].data = h->elem[idx].data;
		h->elem[idx].data = aux1;
		siftDown(h, r);
	}
}

void removeMax(APriQueue h) {
	//TODO:
	h->size -= 1;
	h->elem[0].prior = h->elem[h->size].prior;
	h->elem[0].data = h->elem[h->size].data;
	siftDown(h, 0);

}

void freeQueue(APriQueue h){
	// TODO:
	free(h->elem);
	free(h);
}

#endif

