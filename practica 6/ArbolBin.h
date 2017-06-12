//CABECERA DEL ARBOL BINARIO
#ifndef ArbolBin_H
#define ArbolBin_H

//BIBLIOTECA PARA EL MANEJO DE MEMORIA
#include <stdlib.h>

//Valores de verdadero y falso para el boolean
#define TRUE 1
#define FALSE 0

//Definimos un boolean
typedef unsigned char boolean;

/*Definimos un char sin signo, es más flexible a la hora
de realizar operaciones de bits*/
typedef unsigned char Char;

//Definimos un entero largo para almacenar grandes tamaños de archivo
typedef long long int ull;

/*
Definimos al nodo del árbol binario, el cuál contendrá dos
apuntadores a otro nodo: al de la izquierda y al de la derecha;
además de un Char c y una frecuencia, que es lo único que
necesitaremos para la codificación de Huffman
*/
typedef struct nodo{
	struct nodo * izq;
	struct nodo * der;
	Char c;
	ull frecuencia;
} nodo;

//FUNCIONES MÍNIMAS REQUERIDAS PARA EL ALGORITMO DE CODIFICACIÓN DE HUFFMAN

/*Devuelve un apuntador a un nuevo nodo listo para usar, inicializándolo
con el Char c*/
nodo * NewNode(Char c);

/*Dada una posición, devuelve TRUE si es una hoja, es decir, si tanto su
hijo izquierdo como derecho son nulos; en caso contrario devuelve FALSE*/
boolean IsLeaf(nodo * p);

#endif