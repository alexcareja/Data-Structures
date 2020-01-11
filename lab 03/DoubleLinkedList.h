#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------
/**
 *  Linked list representation -- R2 Curs2 (Slide 8)
 */
typedef struct ListNode{
	Item elem; // Stored node value
	struct ListNode* next; // link to next node
	struct ListNode* prev; // link to prev node
} ListNode;

/**
 *  Double linked list representation -- desen Curs 3 (Slide 19)
 */
typedef struct List{
	ListNode* first; // link to the first node
	ListNode* last; // link to the last node
} List;
// -----------------------------------------------------------------------------

/**
 * Create a new (empty)  list  -- Silde-urile 13/14 Curs 2
 *  [input]: None
 *  [output]: List*
 */
List* createList(void){
	List *list = (List *) malloc(sizeof(List));
	list->first = NULL;
	list->last = NULL;
	return list;
}
// -----------------------------------------------------------------------------


/**
 * Determines if the list is empty
 *  [input]: List*
 *  [output]: 1 - empty/ 0 - not empty
 */
int isEmpty(List *list){
	if (list->first == NULL) {
		return 1;
	}
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Determines if a list contains a specified element
 *  [input]: List*, Item
 *  [output]: int (1 - contains/ 0 - not contains)
 */
int contains(List *list, Item elem){
	ListNode *aux = list->first;
	while(aux != NULL) {
		if (aux->elem == elem) {
			return 1;
		}
		aux = aux->next;
	}
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Insert a new element in the list at the specified position.
 * Note: Position numbering starts with the position at index zero
 *  [input]: List*, Item, int
 *  [output]: void
 */
void insertAt(List* list, Item elem, int pos){

	// Guard against young player errors
	if (pos < 0 || length(list) < pos) {
		return;
	}
	ListNode *node = (ListNode *) malloc(sizeof(ListNode));
	if (node == NULL) {
		return;
	}
	node->elem = elem;
	node->next = NULL;
	node->prev = NULL;
	if (isEmpty(list) && pos == 0) {
		list->first = node;
		list->last = node;
		return;
	}
	ListNode *aux = list->first;
	if (list == NULL) return;
	if (pos == 0) {
		node->next = aux;
		aux->prev = node;
		list->first = node;
		return;
	}
	int i;
	for (i = 0; i < pos - 1; i++) {
		aux = aux->next;
	}
	if (aux->next == NULL) {
		aux->next = node;
		node->prev = aux;
		list->last = node;
		return;
	}
	node->prev = aux;
	node->next = aux->next;
	aux->next->prev = node;
	aux->next = node;


	// TODO: Cerinta 1d
}
// -----------------------------------------------------------------------------


/**
 * Delete the first element instance form a list.
 *  [input]: List*, Item
 *  [output]: void
 */
void deleteOnce(List *list, Item elem){
	// Guard against young player errors
	if (list == NULL) return;
	if (length(list) == 1 && list->first->elem == elem) {
		free(list->first);
		list->first = NULL;
		list->last = NULL;
		return;
	}
	ListNode *aux = list->first;
	while (aux != NULL) {
		if (aux->elem == elem) {
			if (aux->prev != NULL) {
				aux->prev->next = aux->next;
			}
			else {
				list->first = aux->next;
				aux->next->prev = NULL;
			}
			if (aux->next != NULL) {
				aux->next->prev = aux->prev;
			}
			else {
				list->last = aux->prev;
				aux->prev->next = NULL;
			}
			free(aux);
			return;
		}
		aux = aux->next;
	}
	//TODO: Cerinta 1e
}
// -----------------------------------------------------------------------------


/**
 * Compute list length
 *  [input]: List*
 *  [output]: int
 */
int length(List *list){
	// Guard against young player errors
	if(list == NULL) return 0;
	int i = 0;
	ListNode *aux = list->first;
	while(aux != NULL) {
		i++;
		aux = aux->next;
	}
	return i;
}
// -----------------------------------------------------------------------------



/**
 * Destroy a list.
 *  [input]: List*
 *  [output]: void
 */
void destroyList(List* list){
	// Guard against young player errors
	if(list == NULL) return;
	free(list);

	//TODO: Cerinta 1g
}
// -----------------------------------------------------------------------------


#endif //_DOUBLE_LINKED_LIST_H_
