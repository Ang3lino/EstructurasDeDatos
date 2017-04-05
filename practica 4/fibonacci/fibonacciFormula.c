/* Fibonacci por formula iterativa */

#include <stdio.h>
#include <math.h>

double fibo (double n){
	double a = (1 + sqrt(5)) / 2;
	double b = (1 - sqrt(5)) / 2;
	return (pow(a, n) - pow(b, n)) / (a - b);
}

/* Aproximacion
double fibo (double n){
	double por = 0.447213595, mas = 1.618033989, menos = -0.618033988;

	return por * (pow (mas, n) - pow (menos, n));
}
*/


int main (void){
	double n;

	printf ("n: ");
	scanf ("%lf", &n);

	printf ("f (n) = %lf", fibo (n));
	return 0;
}