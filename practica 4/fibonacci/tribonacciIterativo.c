#include <stdio.h>
#define lli unsigned long long int

lli 
tribo (lli n){
	lli i = 2, w = 1, x = 1, y = 2, z;
	
	if (n == 0)
		return 1;
	if (n == 1)
		return 1;
	if (n == 2)
		return 2;

	while (i < n){
		z = w + x + y;
		w = x;
		x = y;
		y = z;
		i++;
	}

	return z;
}

int 
main (void){
	lli n = 0;

	printf ("Tribonacci (n) \n");
	printf ("n: ");
	scanf ("%llu", &n);

	printf ("El termino n-esimo es: %llu", tribo (n));
	return 0;
}
