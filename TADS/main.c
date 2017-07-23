
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

#define SIZE(X) (sizeof (X) / sizeof (X[0]))

void f (Bst *treeA);

int main (int argc, const char *argv[]) {
	Bst *treeA = newBst(),
		*treeB = 0, 
		*nodeA, 
		*nodeB;
	srand (time (0));
	int i = 0, n = 1e2;
	double v1[] = { 2, 4, 5, 2, 1 },
		   v2[] = { 3, 6, 2, 0, 7 };

	for (i = 0; i < SIZE (v1); i++) {
		bstInsert (&treeA, v1[i]);
		bstInsert (&treeB, v2[i]);
	}

	nodeA = bstSearch (treeA, 5);
	nodeB = bstSearch (treeB, 3);
	bstInorder (treeA);
	puts ("");
	bstInorder (treeB);
	puts ("");

	bstTransplant (nodeA, nodeB);
	bstInorder (treeA);
	puts ("");

	bstDelete (treeA, 6);
	bstDelete (treeA, 0);

	bstInorder (treeA);

	puts ("fin"); 
	return 0;
}

