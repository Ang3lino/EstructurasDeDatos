
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

#define SIZE(X) (sizeof (X) / sizeof (X[0]))

int main(int argc, char *argv[])
{
	double v1[] = { 10, 5, 3, 8, 6, 7, 9, 15 }; 
	int i = 0;
	Bst *tree = newBst();

	for (i = 0; i < SIZE (v1); i++)
		bstInsert (&tree, v1[i]);
	bstShow (tree);

	bstDelete (tree, 5);
	bstShow (tree);
	puts ("");

	bstDelete (tree, 3);
	bstShow (tree);
	puts ("");
	
	bstDelete (tree, 10);
	bstShow (tree);
	puts ("");

	bstDelete (tree, 8);
	bstShow (tree);
	puts ("");

	bstDelete (tree, 6);
	bstShow (tree);
	puts ("");

	bstDelete (tree, 7);
	bstShow (tree);
	puts ("");

	bstDelete (tree, 9);
	bstShow (tree);
	puts ("");
	
	bstDelete (tree, 15);
	bstShow (tree);
	puts ("");
	
	return 0;
}
