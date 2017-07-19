
#ifndef BST_H 
#define BST_H

#define NIL 0

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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
void insert (Bst **, const double);
void bstInorder (Bst *);
bool isLeaf (const Bst *);
bool bstExists (Bst *, const double);
Bst *newBst (void);
Bst *bstSearch (Bst *, const double);
Bst *bstMin (Bst *);
Bst *bstMax (Bst *);
Bst *bstPredecessor (Bst *, const double);
Bst *bstSuccessor (Bst *, const double);


#endif

