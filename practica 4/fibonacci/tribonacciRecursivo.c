#include <stdio.h>
#define lli long long;

int 
trib (int n){
	if (n == 1)
		return 0;
	if (n == 2)
		return 1;
	if (n == 3)
		return 1;

	return trib (n - 1) + trib (n - 2) + trib (n - 3); 
}

int 
main (void){
	int n, i = 0;

	printf ("Introduce el n-esimo termino de la serie de tribonacci: ");
	scanf ("%d", &n);

	while (n < 1){
		printf ("La funcion de tribonacci no esta definida para n < 1 \n");
		printf ("Introduzca un valor valido: ");
		scanf ("%d", &n);
	}

	printf ("El termino es: %d \n", trib (n));

	return 0;
}