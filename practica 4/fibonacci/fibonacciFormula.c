/* Fibonacci por formula */

#include <stdio.h>
#include <math.h>

double fibo (double n){
	double a = (1 + sqrt(5)) / 2;
	double b = (1 - sqrt(5)) / 2;
	return (pow(a, n) - pow(b, n)) / (a - b);
}


int main (void){
	double n;

	printf ("n: ");
	scanf ("%lf", &n);

	printf ("f (n) = %lf", fibo (n));
	return 0;
}