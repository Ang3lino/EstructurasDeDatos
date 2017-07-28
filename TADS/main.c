
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

#define SIZE(X) (sizeof (X) / sizeof (X[0]))

int main(int argc, char *argv[])
{
	double v1[] = { 10, 5, 3 }; 
	int i = 0;
	Bst *tree = newBst();

	for (i = 0; i < SIZE (v1); i++)
		bstInsert (&tree, v1[i]);
	bstShow (tree);

	bstDelete (tree, 5);
	bstShow (tree);

	bstDelete (tree, 3);
	bstShow (tree);
	
	bstDelete (tree, 10);
	bstShow (tree);
	return 0;
}
