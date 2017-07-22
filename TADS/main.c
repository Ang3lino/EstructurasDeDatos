
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
	nodeB = bstSearch (treeA, 3);
	bstInorder (treeA);
	puts ("");
	bstInorder (treeB);
	puts ("");

	bstTransplant (treeA, nodeA, nodeB);
	bstInorder (treeA);
	puts ("");

	puts ("fin"); 
	return 0;
}

void 
f (Bst *treeA) {
	bstDelete (treeA, 5);
	bstDelete (treeA, 2);
	bstDelete (treeA, 1);
	bstDelete (treeA, 4);
	printf("%f \n", treeA->comparator);
	printf("%f \n", treeA->right->comparator);
	printf("%f \n", treeA->left->comparator);
	bstInorder (treeA);

}
