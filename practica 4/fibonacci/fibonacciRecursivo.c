/*
PROGRAMA QUE CALCULA EL N-ÉSIMO TÉRMINO DE LA SUCESIÓN DE FIBONACCI
Sea n un entero positivo. Definimos a la sucesión de fibonacci como:
 f(n) = 
   0 si n = 0
   1 si n = 1
   f(n - 1) + f(n - 2) si n > 1
Mediante la definición anterior, implementaremos el cálculo de f(n)
usando recursividad.

AUTORES: Equipo Quick-Coding

FECHA: 12/04/2016

VERSION: 1.0

COMPILACION: gcc fibonacciRecursivo.c -o fibonacciRecursivo.exe
*/

//BIBLIOTECA DE ENTRADA Y SALIDA ESTÁNDAR
#include <stdio.h>

//Para trabajar con enteros positivos grandes, usamos un
//entero long long sin signo, que va desde 0 hasta 2^64-1
//aproximadamente a 1.8*10^19
typedef unsigned long long int ull;

/*
Descripción: dado un entero positivo n, realiza el cálculo
de f(n) de forma recursiva, de acuerdo a la especificación
del problema
Recibe: entero n
Devuelve: f(n)
Observaciones: de forma teórica, el valor máximo que se podrá
calcular es f(93)
*/
ull 
fibo (int n){
	if (n == 0 || n == 1)
		return n;
	return fibo (n - 1) + fibo (n - 2);
}

//PROGRAMA PRINCIPAL
int 
main (void){
	//Declaramos la variable n
	int n;

	//Leemos n
	printf ("Introduce el valor de n para calcular el n-esimo termino de la serie de fibonacci: ");
	scanf ("%d", &n);

	//Forzamos que n >= 1
	while (n < 1){
		printf ("La funcion de fibonacci no esta definida para n < 1 \n");
		printf ("Introduzca un valor valido: ");
		scanf ("%d", &n);
	}

	//Imprimimos f(n)
	printf ("El termino %d es: %llu \n", n, fibo (n));

	return 0; //FIN
}
