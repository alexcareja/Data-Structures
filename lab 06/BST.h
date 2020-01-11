#ifndef BST_H_
#define BST_H_

#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just assume
  some type T was previously defined.
 */

// -----------------------------------------------------------------------------

/*
 * !!!!ATENTION!!!!
 * 1. This implementation uses two sentinels (dummy nodes) root and nil.
 * 2. The convetion is that we always root the tree at root->l (the left of the root sentinel)
 */

typedef struct BSTNode{
	Item elem;
	struct BSTNode *p; // parent - not really needed, but simplifies implementation.
	struct BSTNode *l; // left child.
	struct BSTNode *r; // right child.
}BSTNode;

typedef struct BSTree{
	long size; // This inintially is 0, and is updated by insert/delete
	BSTNode *root; // The sentinel root (a sentinel not the actual root). The actual root node is root->l !
	BSTNode *nil; // The nil sentinel to avoid checks for NULL
}BSTree;

// TODO: Cerinta 1 si 2

/*
 * IMPLEMENTATION ORDER:
 * 1.  createTree
 * 2.  isEmpty
 * 3.  insert
 * 4.  search
 * 5.  minimum
 * 6.  maximum
 * 7.  successor 
 * 8.  predecessor
 * 9.  destroyTree
 */

BSTree *createTree() {
	BSTree *tree = (BSTree *) malloc(sizeof(BSTree));
	if(tree == NULL){
		return NULL;
	}
	tree->size = 0;
	tree->root = (BSTNode *) malloc(sizeof(BSTNode));
	if(tree->root == NULL){
		return NULL;
	}
	tree->root->p = NULL;
	tree->nil = (BSTNode *) malloc(sizeof(BSTNode));
	if(tree->nil == NULL){
		return NULL;
	}
	tree->root->l = tree->nil;
	tree->root->r = tree->nil;
	tree->nil->l = tree->nil;
	tree->nil->r = tree->nil;
	tree->nil->p = NULL;
	return tree;
}

int isEmpty(BSTree *t) {
	if (t->root->l == t->nil) {
		return 1;
	}
	return 0;
}

void insert(BSTree *t, Item elem) {
	BSTNode *node = (BSTNode *) malloc(sizeof(BSTNode));
	node->l = t->nil;
	node->r = t->nil;
	node->elem = elem;
	if (isEmpty(t)) {
		t->root->l = node;
		node->p = t->root;
		t->size += 1l;
		return;
	}
	BSTNode *aux = t->root->l;
	while(1) {
		if (aux == t->nil) {
			break;
		}
		if (elem < aux->elem) {
			if (aux->l == t->nil) {
				aux->l = node;
				node->p = aux;
				t->size += 1l;
				return;
			}
			aux = aux->l;
			continue;
		}
		if(elem > aux->elem) {
			if (aux->r == t->nil) {
				aux->r = node;
				node->p = aux;
				t->size += 1l;
				return;
			}
			aux = aux->r;
			continue;
		}
		break;
	}
}

BSTNode *search(BSTree *t, Item elem) {
	BSTNode *aux = t->root->l;
	while(1) {
		if (aux == t->nil) {
			return NULL;
		}
		if (aux->elem == elem) {
			break;
		}
		if (aux->elem > elem) {
			aux = aux->l;
			continue;
		}
		if (aux->elem < elem) {
			aux = aux->r;
			continue;
		}
	}
	return aux;
}

BSTNode *minimum(BSTree *tree, BSTNode *node){
	BSTNode *aux = node;
	if(node == NULL || tree == NULL){
		return NULL;
	}
	while(aux->l != tree->nil){
		aux = aux -> l;
	}
	return aux;
}

BSTNode *maximum(BSTree *tree, BSTNode *node){
	BSTNode *aux = node;
	if(node == NULL || tree == NULL){
		return NULL;
	}
	while(aux->r != tree->nil){
		aux = aux -> r;
	}
	return aux;
}

BSTNode *successor(BSTree *t, BSTNode *node) {
	if (node->r != t->nil) {
		return minimum(t, node->r);
	}
	Item elem = node->elem;
	while (node != t->root) {
		if (elem > node->elem) {
			break;
		}
		node = node->p;
	}
	if (node == t->root) {
		return NULL;
	}
	return node;
}

BSTNode *predecessor(BSTree *t, BSTNode *node) {
	return NULL;
}

void destroyTree(BSTree *t) {
	free(t->root);
	free(t->nil);
	free(t);
}

void delete(BSTree* tree, Item elem){
	BSTNode* z; // node to be deleted
	BSTNode* y; // Node that is spliced out
	BSTNode* x; // The child of the sliced out node

	// Needed to maintain a similar interface as in the previous labs
	if( (z = search(tree,elem)) == tree->nil)
		return;

	/*
	 * Note:
	 * Case 1: The node has no children
	 * Case 2: The node has one child
	 * Case 3: The node has two children
	 */

	// Are we in cases 1,2 or in case 3
	y = ( (z->l == tree->nil) || (z->r == tree->nil) ) ? z : successor(tree, z);

	// Set x to the child of y
	x = (y->l == tree->nil) ? y->r : y->l;

	/*
	 * Note:
	 * There is no need to check if x is a valid pointer, we have the sentinels!
	 */
	if (tree->root == (x->p = y->p)) // assignment of y->p to x->p is intentional
		tree->root->l = x;
	else if (y == y->p->l)
		y->p->l = x;
	else
		y->p->r = x;

	if (y != z){

		/*
		 * Note:
		 * The data type T might be a very big structure, thus copying the key
		 * from one node to another might be very inefficient. It is better to
		 * modify the actual links.
		 */

		// y is the node to splice out and x is its child
		y->l = z->l;
		y->r = z->r;
		y->p = z->p;
		z->l->p = z->r->p = y;
		if (z == z->p->l) z->p->l = y;
		else z->p->r = y;
		free(z);
	} else {
		free(y);
	}

	tree->size--;
}

#endif /* BST_H_ */

