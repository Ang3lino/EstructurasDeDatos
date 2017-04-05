#include <stdio.h>

int 
fibo (int n){
	if (n == 0 || n == 1)
		return n;
	return fibo (n - 1) + fibo (n - 2);
}

int 
main (void){
	int n = 0;

	printf ("Introduce el n-esimo termino de la serie de tribonacci: ");
	scanf ("%d", &n);

	while (n < 1){
		printf ("La funcion de fibonacci no esta definida para n < 1 \n");
		printf ("Introduzca un valor valido: ");
		scanf ("%d", &n);
	}

	printf ("El termino es: %d \n", fibo (n));

	return 0;
}
