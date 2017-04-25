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

AUTORES: Equipo Quick-Coding

INSTRUCCIONES DE COMPLIACION:
gcc hanoi.c presentacion[Lin|Win].c -o hanoi.exe
*/

//LIBRERIAS
#include <stdio.h>          //Entrada y salida estándar
#include "presentacion.h"   //Operaciones de manipulación de texto en consola

//FUNCIONES PROPUESTAS PARA ANIMACIÓN

//Definimos una estructura torre, la cual contendrá los discos que se encuentran
//apilados en ella. Modelamos el enésimo disco con un entero n. Es similar a una pila.
//Unicamente sirve como auxiliar a la hora de animar los movimientos entre las
//torres, no es requerida para la resolución del problema en sí.
typedef struct torre
{
	int A[100];
	int indice;
} torre;

/*
Descripción: dado un disco y una torre, añade el disco arriba de la torre
Recibe: entero n (disco), apuntador a torre T
Observaciones: el índice de la torre debe ser mayor o igual a -1
*/
void anadir_disco(int n, torre * T){
	T->A[++T->indice] = n;
}

/*
Descripción: dada una torre, remueve el disco que se encuentra hasta el tope
Recibe: apuntador a torre T
Devuelve: entero, el disco que se removió del tope de la torre
Observaciones: el índice de la torre debe ser mayor o igual a 0
*/
int quitar_disco(torre * T){
	return T->A[T->indice--];
}

/*
Descripción: dado un índice de torre, devuelve el nombre asociado a esta
Recibe: entero indice (el índice de la torre)
Devuelve: cadena, indicando el nombre de la torre
Observaciones: el índice debe estar entre 0 y 2, inclusive
*/
char * nombre_torre(int indice){
	switch(indice){
		case 0: return "origen";
		case 1: return "auxiliar";
		case 2: return "destino";
		default: return "";
	}
}

/*
Descripción: dado un arreglo de torres y un tiempo, esta función imprime en pantalla
de manera gráfica cómo se verían las torres de hanoi en un momento determinado, al leer el
contenido de cada torre. Asumimos que el n-ésimo disco tiene un ancho en
pantalla de 2n-1. Por cada estado, esperamos unos segundos y borramos la pantalla
Recibe: arreglo de torres, entero tiempo
Observaciones: el tiempo se da en milisegundos
*/
void mostrar_torres(torre * torres, int tiempo){
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
	EsperarMiliSeg(tiempo);
	MoverCursor(1, 1);
}

//FUNCIONES PRINCIPALES

/*
Descripción: dado un número de disco, los índices de las torres (origen, destino),
un arreglo de torres, un apuntador al número de movimientos, un char tipo y un entero tiempo;
esta función mueve el n-ésimo disco desde origen hasta destino, incrementando en 1 el
número de movimientos. Si el char tipo es 'T', solo se mostrará la secuencia de
movimientos requerida para resolver el problema, si es 'G', además se animará en
pantalla el estado de cada movimiento.
Recibe: int n, int origen, int destino, torre * torres, int * movs, char tipo, int tiempo
Observaciones: el tiempo se da en milisegundos
*/
void mover(int n, int origen, int destino, torre * torres, int * movs, char tipo, int tiempo){
	(*movs)++;
	anadir_disco(quitar_disco(&torres[origen]), &torres[destino]);
	if(tipo == 'G')
		BorrarPantalla();
	printf("Movimiento %d: Mover el disco %d desde %s hasta %s.\n", *movs, n, nombre_torre(origen), nombre_torre(destino));
	if(tipo == 'G')
		mostrar_torres(torres, tiempo);
}

/*
Descripción: esta es la función más importante. Resuelve de manera recursiva el problema
de las torres de hanoi dado el número de discos, los índices de las torres (origen, auxiliar, destino),
un arreglo de torres, un apuntador a entero del número de movimientos, un char tipo y un tiempo.
Si el char tipo es 'T', solo se mostrará la secuencia de movimientos requerida para resolver el
problema, si es 'G', además se animará en pantalla el estado de cada movimiento.
Recibe: int n, int origen, int auxiliar, int destino, torre * torres, int * movs, char tipo, int tiempo
Observaciones: el tiempo se da en milisegundos
*/
void hanoi(int n, int origen, int auxiliar, int destino, torre * torres, int * movs, char tipo, int tiempo){
	if(n == 1){
		//Caso base de la recursión: si solo debemos mover un disco, lo movemos
		//directamente desde origen a destino
		mover(n, origen, destino, torres, movs, tipo, tiempo);
	}else{
		//Movemos los n-1 discos arriba del n-ésimo disco desde origen
		//hasta auxiliar, pasando por destino
		hanoi(n - 1, origen, destino, auxiliar, torres, movs, tipo, tiempo);
		//Movemos el n-ésimo disco directo desde origen a destino
		mover(n, origen, destino, torres, movs, tipo, tiempo);
		//Ahora movemos los n-1 discos desde auxiliar a destino,
		//pasando por origen
		hanoi(n - 1, auxiliar, origen, destino, torres, movs, tipo, tiempo);
	}
}

//PROGRAMA PRINCIPAL
int main(){
	//Declaración de variables
	int n, i;
	int movs = 0;
	int tiempo = 0;
	char tipo;

	//Inicializamos un arreglo de torres
	torre torres[3];
	for(i = 0; i < 3; i++){
		torres[i].indice = -1;
	}

	//Leemos el número de discos
	printf("Introduce el numero de discos: ");
	scanf("%d", &n);

	//Agregamos los n discos en la torre de origen,
	//esto con el único fin de lograr la animación
	for(i = n; i >= 1; i--){
		anadir_disco(i, &torres[0]);
	}

	//Leemos si el usuario quiere la animación o solo la secuencia de movimientos
	printf("Introduce G para modo grafico, o T para modo texto: ");
	scanf(" %c", &tipo);

	//Esta función evita conflictos a la hora de limpiar pantalla
	//y esperar cierto tiempo en milisegundos
	setbuf(stdout, NULL);

	//Borramos la pantalla por primera vez
	BorrarPantalla();

	//Si el usuario quiso animar, pedimos el tiempo de transición entre cada estado
	//y mostramos el estado inicial de las torres
	if(tipo == 'G'){
		printf("Introduce el tiempo de transicion entre cada movimiento (en milisegundos): ");
		scanf(" %d", &tiempo);

		printf("Estado inicial:\n");
		mostrar_torres(torres, tiempo);
	}

	//Resolvemos recursivamente el problema
	hanoi(n, 0, 1, 2, torres, &movs, tipo, tiempo);
	
	return 0; //FIN
}