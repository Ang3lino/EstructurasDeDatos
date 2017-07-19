
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

#define SIZE(X) (sizeof (X) / sizeof (X[0]))

int main (int argc, const char *argv[]) {
	Bst *t = 0;
	int array[] = { 1, 3, 5, 2, 7, 8 }; 
	int i = 0, n = SIZE (array);
	
	for (i = 0; i < n; i++) 
		bstInsert (&t,  array[i]);
	puts ("array");
	for (i = 0; i < n; i++) 
		printf("%d ", array[i]);
	puts ("Recorrido en inorden");
	bstInorder (t);
	bstDelete (t, 3);
	puts ("Borrado el 3");
	bstInorder (t);
	puts ("fin");
	return 0;
}

