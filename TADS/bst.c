
#include "bst.h"

Bst *
newBst (void) {
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

inline void 
insert (Bst **tree, const double data) {
	insertBstHelper (&(*tree), NULL, data);
}

Bst *
bstRoot (Bst *bst) {
	while (bst->parent)
		bst = bst->parent;
	return bst;
}

// NO modifica al arbol (por que?)
void 
bstInsert (Bst **tree, const double data) {
	Bst *before = NULL;
	if (*tree) 
		*tree = bstRoot (*tree);
	while (*tree) {
		before = *tree;
		if (data <= (*tree)->comparator) 
			tree = &(*tree)->left;  // Solo hacia falta un &... por que no *tree = (*tree)->l ?
		else 
			tree = &(*tree)->right;
	}
	*tree = bstNewNode (data);
	(*tree)->parent = before;
	if (before) { // El arbol no estaba vacio al principio
		if ((*tree)->parent->left == *tree) 
			(*tree)->parent->left = *tree;
		else if ((*tree)->parent->right== *tree) 
			(*tree)->parent->right = *tree;
	}
}

// Cambiamos el subarbol u por el subarbol v
void 
bstTransplant (Bst *tree, Bst *u, Bst *v) {
	if (u->parent == NULL) {  // u es la raiz del arbol
		Bst *root = bstRoot (tree);	
		root = v;
	} else if (u == u->parent->left) 
		u->parent->left = v;
	else 
		u->parent->right = v;
	if (v) 
		v->parent = u->parent;
}

bool 
bstIsRoot (Bst *tree) {
	if (!(tree->parent))
		return true;
	return false; 
}

void 
bstDelete (Bst *tree, const double data) {
	Bst *del = bstSearch (tree, data);
	if (del) {
		if (del->left == NULL) 
			bstTransplant (tree, del, del->right);
		else if (del->right == NULL) 
			bstTransplant (tree, del, del->left);
		else { // el nodo del tiene dos hijos 
			Bst *rep = bstMin (del->right);
			rep->left = del->left;
			rep->right = del->right;
			del->left->parent = rep;
			del->right->parent = rep;
			rep->parent = del->parent;
			if (!bstIsRoot (del)) { 
				if (del->parent->left == del)
					del->parent->left = rep;
				else 
					del->parent->right = rep;
			}
			bstTransplant (tree, del, rep);
		}
		free (del);
	} else 
		puts ("No se puede borrar el vacio.");
}

//		Bst *min = bstMin (del->right);	// caso a checar pendiente
//		if (min->parent != del) {	// min no es hijo del nodo a borrar del
//			bstTransplant (tree, min, min->right);
//			min->right = del->right;
//			min->right->parent = min;
//		}
//		min->left = del->left;
//		min->left->parent = min;
//		bstTransplant (tree, del, min);
//	}
//	free (del);

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
	else {
		printf("(");
		bstInorder (tree->left);
		printf ("%.2f ", tree->comparator);
		bstInorder (tree->right);
		printf(")");
	}
}

Bst *
bstSearch (Bst *bst, const double data) {
	if (bst) {
		if (bst->comparator == data) 
			return bst;
		if (data <= bst->comparator)
			return bstSearch (bst->left, data);
		else
			return bstSearch (bst->right, data);
	} else 
		return newBst(); // No se encontro tal nodo
}

Bst *
bstMin (Bst *bst) {
	while (bst->left) 
		bst = bst->left;
	return bst;
}

Bst *
bstMax (Bst *bst) {
	while (bst->right) 
		bst = bst->right;
	return bst;
}

Bst *
bstSuccessor (Bst *bst, const double data) { 
	Bst *x = bstSearch (bst, data);
	if (x->right)
		return bstMin (x->right);
	// ...
}

Bst *
bstPredecessor (Bst *bst, const double data) {
	Bst *x = bstSearch (bst, data);
	if (x->left)
		return bstMax (x->left);
}

