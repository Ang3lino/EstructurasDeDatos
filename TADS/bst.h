
#ifndef BST_H 
#define BST_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct element {
	/* what you want */

} element;

typedef struct bst {
	element e;
	double comparator;
	struct bst *left;
	struct bst *right;
} Bst;

Bst *newBst (void);
void insert (Bst **, const double);
bool isLeaf (const Bst *);
bool bstExists (Bst *, const double);
void inorderBst (Bst *);
Bst *bstSearch (Bst *, const double);
Bst *bstMin (Bst *);
Bst *bstMax (Bst *);
Bst *bstPredecessor (Bst *, const double);
Bst *bstSuccessor (Bst *, const double);


#endif

