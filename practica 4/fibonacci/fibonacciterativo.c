#include <stdio.h>
#define lli long long int

lli 
fibo (int n){
	int i = 0, j = 0, x = 0, y = 1, z = 0;

	while (i < n){
		z = x + y;
		x = y;
		y = z;
		i++;
	}

	return z;
}

int 
main (void){
	int n = 0;

	printf ("Fibonacci (n) \n");
	printf ("n: ");
	scanf ("%d", &n);

	printf ("El termino n-esimo es: %lld", fibo (n));
	return 0;
}