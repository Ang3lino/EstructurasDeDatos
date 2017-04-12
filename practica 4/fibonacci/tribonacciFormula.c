#include <stdio.h>
#include <math.h>
#include <complex.h>

typedef unsigned long long int ull;

ull tribo(ull n){
	long double u = cbrt(19 + 3 * sqrt(33));
	long double v = cbrt(19 - 3 * sqrt(33));
	long double complex w = -0.5 + sqrt(0.75) * I;
	long double complex x1 = (u + v + 1) / 3;
	long double complex x2 = (u * w + v * w * w + 1) / 3;
	long double complex x3 = (u * w * w + v * w + 1) / 3;
	long double complex s = -2 * sqrt(11) * I;
	long double complex c1 = (x2 * x3 * x3 + x2 * x2 + 2 * x3 - 2 * x2 - x2 * x2 * x3 - x3 * x3) / s;
	long double complex c2 = (x3 * x3 + 2 * x1 + x1 * x1 * x3 - x1 * x1 - 2 * x3 - x1 * x3 * x3) / s;
	long double complex c3 = (2 * x2 + x1 * x2 * x2 + x1 * x1 - x1 * x1 * x2 - x2 * x2 - 2 * x1) / s;
	return round(creal(c1 * cpow(x1, n) + c2 * cpow(x2, n) + c3 * cpow(x3, n)));
}

int main(){
	ull n;

	printf ("n: ");
	scanf ("%llu", &n);

	printf ("f (n) = %llu", tribo (n));
	return 0;
}