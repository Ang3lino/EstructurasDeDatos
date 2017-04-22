#include <stdio.h>

lli 
fibo (lli n){
	lli i = 1, x = 0, y = 1, z;
	
	if(n == 0 || n == 1)
		return n;

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
	lli n = 0;

	printf ("Fibonacci (n) \n");
	printf ("n: ");
	scanf ("%llu", &n);

	printf ("El termino n-esimo es: %llu", fibo (n));
	return 0;
}
