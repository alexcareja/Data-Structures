#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>
#include <assert.h>

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------

typedef struct SortedList {
  T value;
  struct SortedList* next;
} SortedList;

// TODO : Cerința 1 & Cerința 2

void init(SortedList **list) {
	*list = NULL;
	
}

int isEmpty(SortedList *list) {
	if (list == NULL) {
		return 1;
	}
	return 0;
}

int contains(SortedList *list, T elem) {
	while (list != NULL) {
		if (list->value == elem) {
			return 1;
		}
		list = list->next;
	}
	return 0;
}

void insert(SortedList **list, T elem) {
	SortedList *newElement = (SortedList *) malloc(sizeof(SortedList));
	newElement->value = elem;
	newElement->next = NULL;
	if (*list == NULL) {
		*list = newElement;
		return;
	}
	SortedList *p1;
	SortedList *p2;
	p1 = *list;
	p2 = p1->next;
	if (p1->value > elem) {
		newElement->next = p1;
		*list = newElement;
		return;
	}
	while (1) {
		if (p2 == NULL) {
			p1->next = newElement;
			if(p1->value < newElement->value) {
				return;
			}
			newElement->value = p1->value;
			p1->value = elem;
			return;
		}
		if (p1->value < elem && elem < p2->value) {
			p1->next = newElement;
			newElement->next = p2;
			return;
		}
		p1 = p2;
		p2 = p2->next;
	}
	
}

void deleteOnce(SortedList **list, T elem) {
	SortedList *aux = *list;
	SortedList *a;
	if(*list == NULL) {
		return;
	}
	if ((*list)->value == elem) {
		*list = (*list)->next;
		free(aux);
		return;
	}
	while (aux != NULL) {
		if (aux->next == NULL) {
			return;
		}
		if (aux->next->value == elem) {
			a = aux->next;
			aux->next = aux->next->next;
			free(a);
			return;
		}
		aux = aux->next;
	}
}

long length(SortedList *list) {
	long n = 0;
	while (list != NULL) {
		n++;
		list = list->next;
	}
	return n;
}

T getNth(SortedList *list, long N) {
	for(; N > 1; N--) {
		if (list == NULL) {
			return 0;
		}
		list = list->next;
	}
	return list->value;
}

void freeSortedList(SortedList **list) {
	SortedList *aux;
	while(*list != NULL) {
		aux = *list;
		*list = (*list)->next;
		free(aux);
	}
}

#endif
