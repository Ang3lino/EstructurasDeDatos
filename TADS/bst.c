
#include "bst.h"

Bst *newBst(void) {
	Bst *tree = 0;
	return tree;
}

void 
insert (Bst **tree, const double data) {
	if (*tree == NULL) {
		*tree = calloc (sizeof (Bst), 1);
		(*tree)->comparator = data;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
	} else if ((*tree)->comparator >= data)
		insert (&(*tree)->left, data);
	else 
		insert (&(*tree)->right, data);
}

bool 
isLeaf (const Bst *tree) {
	if (tree->left == NULL && tree->right == NULL)
		return true;
	return false;
}

bool 
bstExists (Bst *tree, const double data) {
	if (tree) {
		if (tree->comparator == data)
			return true;
		else if (data <= tree->comparator)
			bstExists (tree->left, data);
		else if (data > tree->comparator)
			bstExists (tree->right, data);
	} else 
		return false;
}

void 
inorderBst (Bst *tree) {
	if (tree) {
		inorderBst (tree->left);
		printf ("%f ", tree->comparator);
		inorderBst (tree->right);
	}
}

Bst *searchBst (Bst *bst, const double data) {
	if (bst) {
		if (bst->comparator == data) 
			return bst;
		if (data <= bst->comparator)
			return searchBst (bst->left, data);
		else
			return searchBst (bst->right, data);
	} 
	return newBst();
}

Bst *bstMin (Bst *bst) {
	while (bst) 
		bst = bst->left;
	return bst;
}

Bst *bstMax (Bst *bst) {
	while (bst) 
		bst = bst->right;
	return bst;
}

Bst *bstSuccessor (Bst *bst, const double data) { 
	Bst *x = searchBst (bst, data);
	return bstMin (x->right);
}

Bst *bstPredecessor (Bst *bst, const double data) {
	Bst *x = searchBst (bst, data);
	return bstMax (x->left);
}

