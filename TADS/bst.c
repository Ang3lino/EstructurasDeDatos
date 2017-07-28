
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

Bst *
bstRoot (Bst *bst) {
	while (bst->parent)
		bst = bst->parent;
	return bst;
}

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
		else if ((*tree)->parent->right == *tree) 
			(*tree)->parent->right = *tree;
	}
}

// Cambiamos el subarbol old por el subarbol new. Si old es hoja, puede usarse para quitar la 
// referencia de este haciendo que new sea NULL.
void 
bstTransplant (Bst *old, Bst *new) {
	if (old->parent) {
		if (old == old->parent->left)
			old->parent->left = new;
		else if (old == old->parent->right)
			old->parent->right = new;
	} 
	if (new)
		new->parent = old->parent;
	if (bstIsRoot (old) && !new) // Caso donde del sea hoja y raiz, no hace nada
		old = 0;
}

static void
deleteHelper (Bst *del) {
	if (!(del->left)) { // El caso donde del sea hoja es contemplado aqui
		bstTransplant (del, del->right); 
		free (del);
	} else if (!(del->right)) {
		bstTransplant (del, del->left);
		free (del);
	} else { // el nodo del tiene dos hijos 
		Bst *min = bstMin (del->right); // min sera hoja o tendra un subarbol derecho
		del->comparator = min->comparator;
		deleteHelper (min);
	}
}

void 
bstDelete (Bst *tree, const double data) {
	Bst *del = bstSearch (tree, data);
	if (del)
		deleteHelper (del);
	else
		puts ("bstDelete: No se puede borrar el vacio."); 
}

bool 
bstIsRoot (Bst *tree) {
	if (!(tree->parent))
		return true;
	return false; 
}

bool 
bstIsLeaf (const Bst *tree) {
	if (tree->left == NULL && tree->right == NULL)
		return true;
	return false;
}

bool 
bstExists (Bst *tree, const double data) {
	if (tree) {
		if (tree->comparator == data)
			return true;
		else if (data < tree->comparator)
			return bstExists (tree->left, data);
		else if (data > tree->comparator)
			return bstExists (tree->right, data);
	}
	return false;
}

static void 
inorderHelper (Bst *tree) {
	if (!tree)
		printf ("-");
	else {
		printf("( ");
		inorderHelper (tree->left);
		printf ("%.1f", tree->comparator);
		inorderHelper (tree->right);
		printf(" )");
	}
}

void 
bstInorder (Bst *tree) {
	inorderHelper (tree);
	puts ("");
}

void 
showHelper (Bst *tree, int cont) {
	if (!tree)
		return;
	else {
		int i;
		showHelper (tree->right, ++cont);
		for (i = 0; i < cont; i++)
			printf ("  ");
		printf ("%.0f \n", tree->comparator);
		showHelper (tree->left, ++cont);
	}
}

inline void bstShow (Bst *tree) {
	showHelper (tree, 0);
}

Bst *
bstSearch (Bst *bst, const double data) {
	if (bst) {
		if (bst->comparator == data) 
			return bst;
		if (data < bst->comparator)
			return bstSearch (bst->left, data);
		else
			return bstSearch (bst->right, data);
	} 
	puts ("\nbstSearch: No existe el elemento en el arbol ");
	return 0;
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

// Se asume que data pertenece al arbol, algo lenta pues se verifica que no 
// exista un predecesor o sucesor al valor data.
Bst *
bstSuccessor (Bst *bst, const double data) { 
	Bst *x = bstSearch (bst, data);
	if (bstIsRoot (x) || x == bstMax (bst)) {
		printf ("bstSuccessor: No existe un sucesor para %f \n", x->comparator);
		return 0;
	} 
	if (x->right)
		return bstMin (x->right);
	Bst *y = x->parent;
	while (y->parent && y->comparator < x->comparator)
		y = y->parent;
	return y;
}

Bst *
bstPredecessor (Bst *bst, const double data) {
	Bst *x = bstSearch (bst, data);
	if (bstIsRoot (x) || x == bstMin (bst)) {
		printf ("bstPredecessor: No existe un predecesor para %f \n", x->comparator);
		return 0;
	}
	if (x->left)
		return bstMax (x->left);
	Bst *y = x->parent;
	while (y->parent && y->comparator > x->comparator)
		y = y->parent;
	return y;
}

