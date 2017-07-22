
#ifndef BST_H 
#define BST_H

#define NIL 0

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct element {
	/* what you want */
	double comparator;
} element;

typedef struct bst {
	element e;
	double comparator;
	struct bst *left,
			   *right,
			   *parent;
} Bst;

void bstInsert (Bst **, const double);
void insert (Bst **, const double);  // Hace lo mismo que bstInorder
void bstInorder (Bst *);
void bstDelete (Bst *, const double); // Las dos funciones no hacen su trabajo
void bstTransplant (Bst *, Bst *, Bst *);
bool bstIsLeaf (const Bst *);
bool bstExists (Bst *, const double);
bool bstIsRoot (Bst *); 
Bst *newBst (void);
Bst *bstSearch (Bst *, const double);
Bst *bstMin (Bst *);
Bst *bstMax (Bst *);
Bst *bstPredecessor (Bst *, const double);  // Faltan algunos detalles para los predecesores y sucesores
Bst *bstSuccessor (Bst *, const double);
Bst *bstRoot (Bst *);


#endif

