/*
PROGRAMA QUE CALCULA EL N-ÉSIMO TÉRMINO DE LA SUCESIÓN DE TRIBONACCI
Sea n un entero positivo. Definimos a la sucesión de tribonacci como:
 t(n) = 
   1 si n = 0
   1 si n = 1
   2 si n = 1
   t(n - 1) + t(n - 2) + t(n - 3) si n > 2
Mediante la definición anterior, implementaremos el cálculo de t(n)
usando recursividad.

AUTORES: Equipo Quick-Coding

FECHA: 12/04/2016

VERSION: 1.0

COMPILACION: gcc tribonacciRecursivo.c -o tribonacciRecursivo.exe
*/

//BIBLIOTECA DE ENTRADA Y SALIDA ESTÁNDAR
#include <stdio.h>

//Para trabajar con enteros positivos grandes, usamos un
//entero long long sin signo, que va desde 0 hasta 2^64-1
//aproximadamente a 1.8*10^19
typedef unsigned long long int ull;

/*
Descripción: dado un entero positivo n, realiza el cálculo
de t(n) de forma recursiva, de acuerdo a la especificación
del problema
Recibe: entero n
Devuelve: t(n)
Observaciones: de forma teórica, el valor máximo que se podrá
calcular es t(73)
*/
ull 
trib (int n){
	if (n == 0)
		return 1;
	if (n == 1)
		return 1;
	if (n == 2)
		return 2;

	return trib (n - 1) + trib (n - 2) + trib (n - 3); 
}

//PROGRAMA PRINCIPAL
int 
main (void){
	//Declaramos la variable n
	int n;

	//Leemos n
	printf ("Introduce el valor de n para calcular el n-esimo termino de la serie de tribonacci: ");
	scanf ("%d", &n);

	//Forzamos que n >= 1
	while (n < 1){
		printf ("La funcion de tribonacci no esta definida para n < 1 \n");
		printf ("Introduzca un valor valido: ");
		scanf ("%d", &n);
	}

	//Imprimimos t(n)
	printf ("El termino %d es: %llu \n", n, trib (n));

	return 0; //FIN
}