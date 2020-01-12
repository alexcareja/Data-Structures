
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include<stdlib.h>

// An AVL tree node
typedef struct AVLNode{
	Item elem;
	int height;
	struct AVLNode *l;
	struct AVLNode *r;
	struct AVLNode *p;

}AVLNode;

typedef struct AVLTree{
	long size;
	AVLNode* root;
	AVLNode* nil;
	int (*comp)(Item a, Item b);
}AVLTree;

AVLTree* avlCreateTree(int (*comp) (Item1,Item1))
{
	AVLTree* newTree = (AVLTree*) malloc(sizeof(AVLTree));
	newTree->comp = comp;
	newTree->nil = (AVLNode*) malloc(sizeof(AVLNode));
	newTree->nil->p = newTree->nil->l = newTree->nil->r = newTree->nil;
	newTree->nil->height = 0;
	newTree->root = (AVLNode*) malloc(sizeof(AVLNode));
	newTree->root->p = newTree->root->l = newTree->root->r = newTree->nil;
	newTree->root->height = 0;
	newTree->size = 0;

	return newTree;
}

int avlIsEmpty(AVLTree* tree){
	return (tree->root->l == tree->nil);
}

AVLNode* avlNewNode(AVLTree* tree){
	AVLNode* newNode = (AVLNode*) malloc(sizeof(AVLNode));
	// Initialize the new node to be used in the tree
	newNode->p = newNode->r = newNode->l = tree->nil;
	newNode->height = 1;

	return newNode;
}



// A utility function to get maximum of two integers
int max(int a, int b){
	return (a > b)? a : b;
}

// A utility function to right rotate subtree rooted with y
void avlRightRotate(AVLTree *tree,  AVLNode *y){
	//TO DO HERE
	if(y->l == tree->nil){
		return;
	}
	if (y->p->l == y) {
		y->p->l = y->l;
		y->l->p = y->p;
	}
	if (y->p->r == y) {
		y->p->r = y->l;
		y->l->p = y->p;
	}
	AVLNode *aux = y->l->r;
	y->l->r = y;
	y->p = y->l;
	y->l = aux;
	if (aux != NULL) {
		aux->p = y;
	}

}

// A utility function to left rotate subtree rooted with x
void avlLeftRotate(AVLTree *tree, AVLNode *x){
	//TO DO HERE
	if(x->r == tree->nil){
		return;
	}
	if (x->p->l == x) {
		x->p->l = x->r;
		x->r->p = x->p;
	}
	if (x->p->r == x) {
		x->p->r = x->r;
		x->r->p = x->p;
	}
	AVLNode *aux = x->r->l;
	x->r->l = x;
	x->p = x->r;
	x->r = aux;
	if (aux != NULL) {
		aux->p = x;
	}
}

// Get Balance factor of node x
int avlGetBalance(AVLNode *x){
	if (x == NULL)
		return 0;
	return x->l->height - x->r->height;
}

AVLNode * avlMinimum(AVLTree* tree, AVLNode* x){
	while (x->l != tree->nil)
		x = x->l;
	return x;
}

AVLNode* avlMaximum(AVLTree* tree, AVLNode* x){
	while(x->r != tree->nil){
		x = x->r;
	}
	return x;
}



void avlInsert(struct AVLTree* tree, Item elem){
	//TO DO HERE
	AVLNode *node;
	if (avlIsEmpty(tree)) {
		tree->size = 1;
		node = avlNewNode(tree);
		node->elem = elem;
		tree->root->l = node;
		node->p = tree->root;
		return;
	}
	AVLNode *aux = tree->root->l;
	while (1) {
		if (*(aux->elem) > *elem) {
			if (aux->l == tree->nil) {
				tree->size += 1;
				node = avlNewNode(tree);
				node->elem = elem;
				node->p = aux;
				aux->l = node;
				//recalc heights
				break;
			}
			aux = aux->l;
			continue;
		}
		if (*(aux->elem) < *elem) {
			if (aux->r == tree->nil) {
				tree->size += 1;
				node = avlNewNode(tree);
				node->elem = elem;
				node->p = aux;
				aux->r = node;
				//recalc heights
				break;
			}
			aux = aux->r;
			continue;
		}
		return;
	}
	while(aux != tree->root) {
		aux->height = 1 + max(aux->l->height, aux->r->height);
		aux = aux->p;
	}
	// Caut un nod dezechilibrat
	char poz[100];
	int i = 0;
	aux = node;
	if(aux->p->r == aux){
		strcpy(poz, "r");
		i++;
	}
	else{
		strcpy(poz, "l");
		i++;
	}
	aux = aux->p;
	while(aux != tree->root){
		if(aux->p != tree->root){
			if(aux->p->r == aux){
				strcat(poz, "r");
				i++;
			}
			else{
				strcat(poz, "l");
				i++;
			}
		}
		if((aux->l->height - aux->r->height) == 2){
			// cazul stanga stanga
			if(poz[i-1] == 'l'){
				//printf("cazul stanga stanga \n");
				//printf("rotesc in %ld\n", *(aux->elem));
				avlRightRotate(tree, aux);
			}
			// cazul stanga dreapta
			if(poz[i-1] == 'r'){
				//printf("cazul stanga dreapta \n");
				avlLeftRotate(tree,aux->l);
				avlRightRotate(tree,aux);
				
			}
			break;
		}
		if((aux->l->height - aux->r->height) == -2){
			// cazul dreapta dreapta
			if(poz[i-1] == 'r'){
				//printf("cazul dreapta dreapta \n");
				avlLeftRotate(tree, aux);
			}
			// cazul dreapta stanga
			if(poz[i-1] == 'l'){
				//printf("cazul dreapta stanga \n");
				avlRightRotate(tree, aux->r);
				avlLeftRotate(tree, aux);
			}
			break;
		}
		aux = aux->p;
	}
	tree->root->l->height = update_height(tree, tree->root->l);

}

int update_height(AVLTree *tree, AVLNode *node){
	if(node == tree->nil){
		return 0;
	}
	int left, right;
	left = update_height(tree, node->l) + 1;
	right = update_height(tree, node->r) + 1;
	if(left >= right){
		node->height = left;
		return node->height;
	}
	else{
		node->height = right;
		return node->height;
	}
	
}



void avlDeleteNode(AVLTree *tree, AVLNode* node){
	destroyElem(node->elem);
	free(node);
}


void avlDestroyTreeHelper(AVLTree* tree, AVLNode* x) {
	if (x != tree->nil) {
		avlDestroyTreeHelper(tree,x->l);
		avlDestroyTreeHelper(tree,x->r);
		avlDeleteNode(tree,x);
	}
}

void avlDestroyTree(AVLTree* tree){
	avlDestroyTreeHelper(tree, tree->root->l);
	free(tree->root);
	free(tree->nil);
	free(tree);
}

#endif /* AVLTREE_H_ */
