
#ifndef BST_H 
#define BST_H

#define NIL 0

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct element {
	/* what you want */
	double Double;
	int Integer;
	char Char;
} element;

typedef struct bst {
	element e;
	double comparator;
	struct bst *left,
			   *right,
			   *parent;
} Bst;

void bstInsert (Bst **, const double);
void bstInorder (Bst *);
void bstDelete (Bst *, const double); 
void bstTransplant (Bst *, Bst *); // Sustituye subarbol del primer parametro por el segundo
void bstShow (Bst *);

bool bstIsLeaf (const Bst *);
bool bstExists (Bst *, const double);
bool bstIsRoot (Bst *); 

Bst *newBst (void); // Se declara un arbol nuevo haciendo Bst *name = newBst();
Bst *bstSearch (Bst *, const double);
Bst *bstMin (Bst *);
Bst *bstMax (Bst *);
Bst *bstPredecessor (Bst *, const double);  // Faltan algunos detalles para los predecesores y sucesores
Bst *bstSuccessor (Bst *, const double);
Bst *bstRoot (Bst *);


#endif

