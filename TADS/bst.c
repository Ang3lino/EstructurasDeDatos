
#include "bst.h"

Bst *
newBst(void) {
	Bst *tree = 0;
	return tree;
}

Bst *
bstNewNode (const double data) {
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
		*tree = bstNewNode (data);
		(*tree)->parent = parent;
	} else if (data <= (*tree)->comparator)
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
	*tree = bstNewNode (data);
	(*tree)->parent = before;
}

// Cambiamos el subarbol u por el subarbol v
void 
bstTransplant (Bst *tree, Bst *u, Bst *v) {
	if (u->parent == NULL)
		tree = v;
	else if (u == u->parent->left) 
		u->parent->left = v;
	else 
		u->parent->right = v;
	if (v) 
		v->parent = u->parent;
}

void 
bstDelete (Bst *tree, const double data) {
	Bst *z = bstSearch (tree, data);
	if (z) {
		if (z->left == NULL) 
			bstTransplant (tree, z, z->right);
		else if (z->right == NULL) 
			bstTransplant (tree, z, z->left);
		else { // Sigsegv error en este caso solucionado era la funcion bstMin
			Bst *y = bstMin (z->right);
			printf("%f\n", y->parent->comparator);
			if (y->parent != z) {	// Falta revisar este caso
				bstTransplant (tree, y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			y->left = z->left;
			y->left->parent = y;
			bstTransplant (tree, z, y);
		}
	}
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
		printf ("- ");
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
	} else return newBst(); // No se encontro tal nodo
}

Bst *bstMin (Bst *bst) {
	while (bst->left) 
		bst = bst->left;
	return bst;
}

Bst *bstMax (Bst *bst) {
	while (bst->right) 
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

