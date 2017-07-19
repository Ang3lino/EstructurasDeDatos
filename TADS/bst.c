
#include "bst.h"

Bst *
newBst(void) {
	Bst *tree = 0;
	return tree;
}

Bst *
bstCreateNode (const double data) {
	Bst *tree = (Bst *) calloc (sizeof (Bst), 1);
	tree->left = NULL;
	tree->right = NULL;
	tree->parent = NULL;
	tree->comparator = data;
	return tree;
}

static void 
insertBstHelper (Bst **tree, Bst *parent, const double data) {
	if (*tree == NULL) {
		*tree = bstCreateNode (data);
		(*tree)->parent = parent;
	} else if ((*tree)->comparator >= data)
		insertBstHelper (&(*tree)->left, *tree, data);
	else 
		insertBstHelper (&(*tree)->right, *tree, data);
}

void 
bstInsert (Bst **tree, const double data) {
	insertBstHelper (&(*tree), NULL, data);
}

void 
insert (Bst **tree, const double data) {
	Bst *before = NULL;
	while (*tree) {
		before = *tree;
		if (data <= (*tree)->comparator) 
			*tree = (*tree)->left;
		else 
			*tree = (*tree)->right;
	}
	*tree = bstCreateNode (data);
	(*tree)->parent = before;
}

void 
bstTransplant (Bst *tree, Bst *u, Bst *v) {
	if (u->parent == NULL)
		tree = u;

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
bstInorder (Bst *tree) {
	if (!tree)
		printf ("-");
	else if (tree) {
		printf("(");
		bstInorder (tree->left);
		printf ("%.2f ", tree->comparator);
		bstInorder (tree->right);
		printf(")");
	}
}

Bst *bstSearch (Bst *bst, const double data) {
	if (bst) {
		if (bst->comparator == data) 
			return bst;
		if (data <= bst->comparator)
			return bstSearch (bst->left, data);
		else
			return bstSearch (bst->right, data);
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
	Bst *x = bstSearch (bst, data);
	return bstMin (x->right);
}

Bst *bstPredecessor (Bst *bst, const double data) {
	Bst *x = bstSearch (bst, data);
	return bstMax (x->left);
}

