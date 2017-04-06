/*
TORRES DE HANOI
Descripción: este problema consiste en mover n discos apilados de mayor a menor, de una
torre origen a otra torre destino. Contamos con tres torres: origen, auxiliar y destino.
Las reglas para mover un disco son:
-Solo podemos mover un disco a la vez
-Cada disco que movamos no puede quedar arriba de un disco de tamaño menor
Entonces, el problema consiste en dar la secuencia de movimientos mínimos para mover todos
los discos de la torre origen a la de destino.

VERSION: 1.0

FECHA: 6/04/2017

AUTORES:
Ontiveros Salazar Alan Enrique

INSTRUCCIONES DE COMPLIACION:
gcc hanoi.c presentacion[Lin|Win].c -o hanoi.exe
*/

//LIBRERIAS
#include <stdio.h>          //Entrada y salida estándar
#include "presentacion.h"   //Operaciones de manipulación de texto en consola

//Definimos una estructura torre, la cual contendrá los discos que se encuentran
//apilados en ella. Modelamos el enésimo disco con un entero n. Es similar a una pila.
typedef struct torre
{
	int A[100];
	int indice;
} torre;

//FUNCIONES PROPUESTAS

void anadir_disco(int n, torre * T){
	T->indice++;
	T->A[T->indice] = n;
}

int quitar_disco(torre * T){
	int n = T->A[T->indice];
	T->indice--;
	return n;
}

char * nombre_disco(int disco){
	switch(disco){
		case 0: return "origen";
		case 1: return "auxiliar";
		case 2: return "destino";
	}
}

void mostrar_torres(torre * torres){
	int alto = 0, nivel, i, j, n;
	for(i = 0; i < 3; i++){
		if(torres[i].indice > alto){
			alto = torres[i].indice;
		}
	}
	for(nivel = alto; nivel >= 0; nivel--){
		for(i = 0; i < 3; i++){
			if(alto - nivel <= torres[i].indice){
				n = torres[i].A[alto - nivel];
				for(j = 11 - n + 25 * i; j <= 9 + n + 25 * i; j++){
					MoverCursor(j + 5, nivel + 5);
					printf("*");
				}
			}
		}
	}
	EsperarMiliSeg(3000);
	MoverCursor(1, 1);
}

void mover(int n, int origen, int destino, torre * torres, int * movs, char tipo){
	(*movs)++;
	anadir_disco(quitar_disco(&torres[origen]), &torres[destino]);
	if(tipo == 'G')
		BorrarPantalla();
	printf("Movimiento %d: Mover el disco %d desde %s hasta %s.\n", *movs, n, nombre_disco(origen), nombre_disco(destino));
	if(tipo == 'G')
		mostrar_torres(torres);
}

void hanoi(int n, int origen, int auxiliar, int destino, torre * torres, int * movs, char tipo){
	if(n == 1){
		mover(n, origen, destino, torres, movs, tipo);
	}else{
		hanoi(n - 1, origen, destino, auxiliar, torres, movs, tipo);
		mover(n, origen, destino, torres, movs, tipo);
		hanoi(n - 1, auxiliar, origen, destino, torres, movs, tipo);
	}
}

int main(){
	int n, i, movs = 0;
	char tipo;
	torre torres[3];
	for(i = 0; i < 3; i++){
		torres[i].indice = -1;
	}
	printf("Introduce el numero de discos: ");
	scanf("%d", &n);
	for(i = n; i >= 1; i--){
		anadir_disco(i, &torres[0]);
	}
	printf("Introduce G para modo grafico, o T para modo texto: ");
	scanf(" %c", &tipo);
	setbuf(stdout, NULL);
	BorrarPantalla();
	if(tipo == 'G'){
		printf("Estado inicial:\n");
		mostrar_torres(torres);
	}
	hanoi(n, 0, 1, 2, torres, &movs, tipo);
	return 0;
}
