#ifndef TREE_H_D
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef struct Link
  {
    Item  elem;
    struct Link *l;
    struct Link *r;
  } TreeNode;


int max_value(int a, int b) {
	return a > b ? a : b;
}

void Init(TreeNode **t, Item x)
{
	*t = (TreeNode *) malloc(sizeof(TreeNode));
	(*t)->elem = x;
	(*t)->l = NULL;
	(*t)->r = NULL;
}

void Insert(TreeNode **t, Item x)
{

	if(*t == NULL){
		Init(t,x);
		return;
	}
	if((*t)->elem > x){
		if((*t)->l != NULL){
			Insert(&((*t)->l), x);
		}
		else{
			Init(&((*t)->l), x);
		}
	}
	else{
		if((*t)->r != NULL){
			Insert(&((*t)->r), x);
		}
		else{
			Init(&((*t)->r), x);
		}
	}

}

void PrintPostorder(TreeNode *t)
{
	if (t == NULL) {
		return;
	}
	PrintPostorder(t->l);
	PrintPostorder(t->r);
	printf("%d ", t->elem);
}

void PrintPreorder(TreeNode *t)
{
	if(t == NULL){
		return;
	}
	printf("%d ", t->elem);
	PrintPreorder(t->l);
	PrintPreorder(t->r);

}

void PrintInorder(TreeNode *t)
{
	if(t == NULL){
		return;
	}
	PrintInorder(t->l);
	printf("%d ", t->elem);
	PrintInorder(t->r);
 

}

void Free(TreeNode **t)
{
	if (*t == NULL) {
		return;
	}
	Free((*t)->l);
	Free((*t)->r);
	free(*t);

}

int Size(TreeNode* t)
{
	if (t == NULL) {
		return 0;
	}
	return 1 + Size(t->l) + Size(t->r);
}

int maxDepth(TreeNode *t)
{
	if (t == NULL) {
		return 0;
	}
	return 1 + max_value(maxDepth(t->l), maxDepth(t->r));
}

#endif // LINKEDSTACK_H_INCLUDED
