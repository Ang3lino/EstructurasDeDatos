
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

#define SIZE(X) (sizeof (X) / sizeof (X[0]))

void oneChild (void) {  // o hijo
	Bst *treeA = newBst(),
		*treeB = 0; 
	int i = 0;
	double v1[] = { 2, 4, 5, 3, 1 },
		   v2[] = { 3, 6, 2, 0, 7 };

	for (i = 0; i < SIZE (v1); i++) {
		bstInsert (&treeA, v1[i]);
		bstInsert (&treeB, v2[i]);
	}

	bstInorder (treeA);
	puts ("");
	bstInorder (treeB);
	puts ("");

	bstDelete (treeA, 1);
	bstInorder (treeA);
	puts ("");
	
    bstDelete (treeB, 6);
	bstInorder (treeB);
	puts (""); 
}

void childs (void) {
	Bst *treeA = newBst(),
		*treeB = 0; 
	int i = 0;
	double v1[] = { 10, 5, 3, 8, 6, 7, 9, 15 },
		   v2[] = { 3, 6, 2, 0, 7 };

	for (i = 0; i < SIZE (v1); i++) {
		bstInsert (&treeA, v1[i]);
	}

	bstDelete (treeA, 5);
	bstInorder (treeA);
	puts ("");
}

void 
transplant(Bst **old, Bst **new) {
	if (!(*old)) {
		puts ("\nbstTransplant: (*old) es vacio por dentro u-u");
		return;
	}
	if ((*new)) {
		(*old)->left = (*new)->left;
		(*old)->right = (*new)->right;
		(*old)->comparator = (*new)->comparator;
		//(*new)->parent = (*old)->parent;
	} else if (!(*new)) {
		if (!bstIsRoot ((*old))) {
				if ((*old) == (*old)->parent->right)
					(*old)->parent->right = 0;
				else
					(*old)->parent->left = 0;
		}
	} 
	free ((*old));
}

int main (int argc, const char *argv[]) {
	Bst *treeA = newBst(),
		*treeB = 0,
		*nodeA = 0, 
		*nodeB = 0;
	int i = 0;
	double v1[] = { 2, 4, 5, 3, 1 },
		   v2[] = { 3, 6, 2, 0, 7 };

	for (i = 0; i < SIZE (v1); i++) {
		bstInsert (&treeA, v1[i]);
		bstInsert (&treeB, v2[i]);
	}

	bstInorder (treeA);
	puts ("");
	bstInorder (treeB);
	puts ("");

	nodeA = bstSearch (treeA, 5);
	nodeB = bstSearch (treeB, 3);
	transplant (&nodeA, &nodeB);
	printf ("%f \n", nodeB->parent->comparator);

	return 0;
}

